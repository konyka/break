# Plugins / OnlineServicesEOSGS

- module root: `Plugins/Online/OnlineServicesEOSGS/Source`
- headers: 24; symbols: 835
- symbol kinds: class=41, enum=5, enumerator=19, function=59, macro=3, member=204, namespace=71, prototype=317, struct=86, typedef=24, variable=6
- PrivateDependencyModuleNames: ApplicationCore, CoreOnline, CoreUObject, EOSShared, SocketSubsystemEOS, Sockets
- PublicDependencyModuleNames: Core, EOSSDK, OnlineBase, OnlineServicesCommon, OnlineServicesCommonEngineUtils, OnlineServicesEpicCommon, OnlineServicesInterface

### `Plugins/Online/OnlineServicesEOSGS/Source/Private/Online/IOS/IOSEOSAuthLoginOptions.h` (Private)


#### class `UE::Online::FIOSEOSAuthLoginOptions`  
`class FIOSEOSAuthLoginOptions : public FEOSAuthLoginOptionsCommon`  
_L12-25_
- inherits: `FEOSAuthLoginOptionsCommon`
- L15 _public prototype_ `FIOSEOSAuthLoginOptions(FIOSEOSAuthLoginOptions&&);`
- L16 _public prototype_ `FIOSEOSAuthLoginOptions& operator=(FIOSEOSAuthLoginOptions&&);`
- L19 _protected prototype_ `FIOSEOSAuthLoginOptions() = default;`
- L21 _protected prototype_ `static bool InitSystemAuthCredentialOptions(FIOSEOSAuthLoginOptions& Options);`
- L24 _private member_ `EOS_IOS_Auth_CredentialsOptions CredentialsOptions = {};`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Online` (scope `UE`)
- L27 _typedef_ `using FPlatformEOSAuthLoginOptions = FIOSEOSAuthLoginOptions;` (scope `UE::Online`)

### `Plugins/Online/OnlineServicesEOSGS/Source/Private/Online/LobbiesEOSGSTypes.h` (Private)


#### class `UE::Online::FLobbyBucketIdEOS`  
`class FLobbyBucketIdEOS`  
_L37-65_
- L40 _public prototype_ `FLobbyBucketIdEOS() = default;`
- L41 _public prototype_ `FLobbyBucketIdEOS(const FString& ProductName, int32 ProductVersion);`
- L43 _public prototype_ `FLobbyBucketIdEOS(const FLobbyBucketIdEOS&) = default;`
- L44 _public prototype_ `FLobbyBucketIdEOS(FLobbyBucketIdEOS&&) = default;`
- L45 _public prototype_ `FLobbyBucketIdEOS& operator=(const FLobbyBucketIdEOS&) = default;`
- L46 _public prototype_ `FLobbyBucketIdEOS& operator=(FLobbyBucketIdEOS&&) = default;`
- L48 _public function_ `bool operator==(const FLobbyBucketIdEOS& Other) const`
- L53 _public function_ `bool operator!=(const FLobbyBucketIdEOS& Other) const`
- L58 _public function_ `const FString& GetProductName() const`
- L59 _public function_ `int32 GetProductVersion() const`
- L60 _public function_ `bool IsValid() const`
- L63 _private member_ `FString ProductName;`
- L64 _private member_ `int32 ProductVersion;`

#### enum `UE::Online::ELobbyTranslationType`  
`enum class ELobbyTranslationType`  
_L72-76_
- L74 _public enumerator_ `ToService`
- L75 _public enumerator_ `FromService`

#### class `UE::Online::FLobbyAttributeTranslator`  
`template <ELobbyTranslationType> class FLobbyAttributeTranslator`  
_L82-85_
- L91 _public prototype_ `FLobbyAttributeTranslator(const FSchemaServiceAttributeData& FromAttributeData);`
- L93 _public function_ `const EOS_Lobby_AttributeData& GetAttributeData() const`
- L94 _public function_ `const EOS_ELobbyAttributeVisibility& GetAttributeVisibility() const`
- L97 _private member_ `FTCHARToUTF8 KeyConverterStorage;`
- L98 _private member_ `TOptional<FTCHARToUTF8> ValueConverterStorage;`
- L99 _private member_ `EOS_Lobby_AttributeData AttributeData;`
- L100 _private member_ `EOS_ELobbyAttributeVisibility AttributeVisibility;`
- L107 _public prototype_ `FLobbyAttributeTranslator(const EOS_Lobby_AttributeData& FromAttributeData);`
- L109 _public function_ `const TPair<FSchemaAttributeId, FSchemaVariant>& GetAttributeData() const`
- L110 _public function_ `TPair<FSchemaAttributeId, FSchemaVariant>& GetMutableAttributeData()`
- L113 _private member_ `TPair<FSchemaAttributeId, FSchemaVariant> AttributeData;`

#### class `UE::Online::FLobbyAttributeTranslator`  
`template <> class FLobbyAttributeTranslator<ELobbyTranslationType::ToService>`  
_L88-101_
- L91 _public prototype_ `FLobbyAttributeTranslator(const FSchemaServiceAttributeData& FromAttributeData);`
- L93 _public function_ `const EOS_Lobby_AttributeData& GetAttributeData() const`
- L94 _public function_ `const EOS_ELobbyAttributeVisibility& GetAttributeVisibility() const`
- L97 _private member_ `FTCHARToUTF8 KeyConverterStorage;`
- L98 _private member_ `TOptional<FTCHARToUTF8> ValueConverterStorage;`
- L99 _private member_ `EOS_Lobby_AttributeData AttributeData;`
- L100 _private member_ `EOS_ELobbyAttributeVisibility AttributeVisibility;`
- L107 _public prototype_ `FLobbyAttributeTranslator(const EOS_Lobby_AttributeData& FromAttributeData);`
- L109 _public function_ `const TPair<FSchemaAttributeId, FSchemaVariant>& GetAttributeData() const`
- L110 _public function_ `TPair<FSchemaAttributeId, FSchemaVariant>& GetMutableAttributeData()`
- L113 _private member_ `TPair<FSchemaAttributeId, FSchemaVariant> AttributeData;`

#### class `UE::Online::FLobbyAttributeTranslator`  
`template <> class FLobbyAttributeTranslator<ELobbyTranslationType::FromService>`  
_L104-114_
- L91 _public prototype_ `FLobbyAttributeTranslator(const FSchemaServiceAttributeData& FromAttributeData);`
- L93 _public function_ `const EOS_Lobby_AttributeData& GetAttributeData() const`
- L94 _public function_ `const EOS_ELobbyAttributeVisibility& GetAttributeVisibility() const`
- L97 _private member_ `FTCHARToUTF8 KeyConverterStorage;`
- L98 _private member_ `TOptional<FTCHARToUTF8> ValueConverterStorage;`
- L99 _private member_ `EOS_Lobby_AttributeData AttributeData;`
- L100 _private member_ `EOS_ELobbyAttributeVisibility AttributeVisibility;`
- L107 _public prototype_ `FLobbyAttributeTranslator(const EOS_Lobby_AttributeData& FromAttributeData);`
- L109 _public function_ `const TPair<FSchemaAttributeId, FSchemaVariant>& GetAttributeData() const`
- L110 _public function_ `TPair<FSchemaAttributeId, FSchemaVariant>& GetMutableAttributeData()`
- L113 _private member_ `TPair<FSchemaAttributeId, FSchemaVariant> AttributeData;`

#### class `UE::Online::FLobbyBucketIdTranslator`  
`template <> class FLobbyBucketIdTranslator<ELobbyTranslationType::ToService>`  
_L123-132_
- L126 _public prototype_ `FLobbyBucketIdTranslator(const FLobbyBucketIdEOS& BucketId);`
- L128 _public function_ `const char* GetBucketIdEOS() const`
- L131 _private member_ `FTCHARToUTF8 BucketConverterStorage;`
- L138 _public prototype_ `FLobbyBucketIdTranslator(const char* BucketIdEOS);`
- L140 _public function_ `const FLobbyBucketIdEOS& GetBucketId() const`
- L141 _public function_ `FLobbyBucketIdEOS& GetMutableBucketId()`
- L144 _private member_ `FLobbyBucketIdEOS BucketId;`

#### class `UE::Online::FLobbyBucketIdTranslator`  
`template <> class FLobbyBucketIdTranslator<ELobbyTranslationType::FromService>`  
_L135-145_
- L126 _public prototype_ `FLobbyBucketIdTranslator(const FLobbyBucketIdEOS& BucketId);`
- L128 _public function_ `const char* GetBucketIdEOS() const`
- L131 _private member_ `FTCHARToUTF8 BucketConverterStorage;`
- L138 _public prototype_ `FLobbyBucketIdTranslator(const char* BucketIdEOS);`
- L140 _public function_ `const FLobbyBucketIdEOS& GetBucketId() const`
- L141 _public function_ `FLobbyBucketIdEOS& GetMutableBucketId()`
- L144 _private member_ `FLobbyBucketIdEOS BucketId;`

#### struct `UE::Online::FLobbyPrerequisitesEOS`  
`struct FLobbyPrerequisitesEOS`  
_L183-189_
- desc: Common components required to handle lobby requests. To handle lifetime issues, only FLobbiesEOS should contain a strong reference to prerequisites. Any other component should only store a weak reference.
- L185 _public member_ `EOS_HLobby LobbyInterfaceHandle = {};`
- L186 _public member_ `IEpicProductUserIdResolver* ResolverInterface;`
- L187 _public member_ `FLobbyBucketIdEOS BucketId;`
- L188 _public member_ `TSharedRef<FSchemaRegistry> SchemaRegistry;`

#### enum `UE::Online::ELobbyDetailsSource`  
`enum class ELobbyDetailsSource`  
_L196-221_
- desc: Lobby details are created for each user within the EOS lobby client. Certain operations such as joining a lobby or applying an update to a lobby / member attributes require using the correct lobby details handle.
- L202 _public enumerator_ `Active` — The lobby has been joined and is considered active. Valid for lobby / member updates.
- L208 _public enumerator_ `Invite` — The details originated from an invitation sent to the user. Valid for joining.
- L214 _public enumerator_ `UiEvent` — The details originated from an event generated by the EOS overlay. Valid for joining.
- L220 _public enumerator_ `Search` — The details originated from a lobby search result. Valid for joining.

#### class `UE::Online::FLobbyDetailsEOS`  
`class FLobbyDetailsEOS final : public TSharedFromThis<FLobbyDetailsEOS>`  
_L224-297_
- inherits: `TSharedFromThis<FLobbyDetailsEOS>`
- desc: Lobby details is created based on the passed in user and is required to join a lobby.
- L229 _public prototype_ `static TDefaultErrorResultInternal<TSharedRef<FLobbyDetailsEOS>> CreateFromLobbyId( const TSharedRef<FLobbyPrerequisitesEOS>& Prerequisites, FAccountId LocalAccountId, EOS_LobbyId LobbyIdEOS);`
- L233 _public prototype_ `static TDefaultErrorResultInternal<TSharedRef<FLobbyDetailsEOS>> CreateFromLobbyId( const TSharedRef<FLobbyPrerequisitesEOS>& Prerequisites, FAccountId LocalAccountId, const FString& LobbyId);`
- L237 _public prototype_ `static TDefaultErrorResultInternal<TSharedRef<FLobbyDetailsEOS>> CreateFromInviteId( const TSharedRef<FLobbyPrerequisitesEOS>& Prerequisites, FAccountId LocalAccountId, const char* InviteId);`
- L241 _public prototype_ `static TDefaultErrorResultInternal<TSharedRef<FLobbyDetailsEOS>> CreateFromUiEventId( const TSharedRef<FLobbyPrerequisitesEOS>& Prerequisites, FAccountId LocalAccountId, EOS_UI_EventId UiEventId);`
- L245 _public prototype_ `static TDefaultErrorResultInternal<TSharedRef<FLobbyDetailsEOS>> CreateFromSearchResult( const TSharedRef<FLobbyPrerequisitesEOS>& Prerequisites, FAccountId LocalAccountId, EOS_HLobbySearch SearchHandle, uint32_t ResultIndex);`
- L251 _public prototype_ `FLobbyDetailsEOS() = delete;`
- L252 _public prototype_ `~FLobbyDetailsEOS();`
- L254 _public function_ `EOS_HLobbyDetails GetEOSHandle() const`
- L255 _public function_ `const TSharedRef<FLobbyDetailsInfoEOS>& GetInfo() const`
- L256 _public function_ `ELobbyDetailsSource GetDetailsSource() const`
- L257 _public function_ `FAccountId GetAssociatedUser() const`
- L262 _public prototype_ `bool IsBucketCompatible() const;` — Check whether this lobbies bucket is compatible with the currently running application.
- L268 _public prototype_ `TFuture<TDefaultErrorResultInternal<FLobbyServiceSnapshot>> GetLobbySnapshot(bool bCopyMemberData) const;` — Retrieve a lobby data snapshot from the EOS lobby details object. The lobby schema will be used to translate attribute data before returning.
- L274 _public prototype_ `TDefaultErrorResultInternal<FLobbyMemberServiceSnapshot> GetLobbyMemberSnapshot(FAccountId MemberAccountId) const;` — Retrieve lobby member data snapshot from the EOS lobby details object. The lobby schema will be used to translate attribute data before returning.
- L279 _public prototype_ `TFuture<EOS_EResult> ApplyLobbyDataUpdateFromLocalChanges(FAccountId LocalAccountId, const FLobbyClientServiceChanges& ServiceChanges) const;` — Apply client side lobby changes to the lobby service.
- L284 _private prototype_ `FLobbyDetailsEOS( const TSharedRef<FLobbyPrerequisitesEOS>& Prerequisites, const TSharedRef<FLobbyDetailsInfoEOS>& LobbyDetailsInfo, FAccountId LocalAccountId, ELobbyDetailsSource LobbyDetailsSource, EOS_HLobbyDetails LobbyDetailsHandle);`
- L291 _private member_ `static const EOS_HLobbyDetails InvalidLobbyDetailsHandle;`
- L292 _private member_ `TSharedRef<FLobbyPrerequisitesEOS> Prerequisites;`
- L293 _private member_ `TSharedRef<FLobbyDetailsInfoEOS> LobbyDetailsInfo;`
- L294 _private member_ `FAccountId AssociatedLocalUser;`
- L295 _private member_ `ELobbyDetailsSource LobbyDetailsSource;`
- L296 _private member_ `EOS_HLobbyDetails LobbyDetailsHandle = InvalidLobbyDetailsHandle;`

#### class `UE::Online::FLobbyDetailsInfoEOS`  
`class FLobbyDetailsInfoEOS final`  
_L300-330_
- desc: Lobby details info allows direct access to some of the lobby properties.
- L304 _public prototype_ `FLobbyDetailsInfoEOS() = delete;`
- L306 _public prototype_ `static TDefaultErrorResultInternal<TSharedRef<FLobbyDetailsInfoEOS>> Create(EOS_HLobbyDetails LobbyDetailsHandle);`
- L308 _public function_ `EOS_LobbyId GetLobbyIdEOS() const`
- L309 _public function_ `int32 GetMaxMembers() const`
- L310 _public function_ `EOS_ELobbyPermissionLevel GetPermissionLevel() const`
- L311 _public function_ `const FLobbyBucketIdEOS& GetBucketId() const`
- L322 _private typedef_ `using FLobbyDetailsInfoPtr = TUniquePtr<EOS_LobbyDetails_Info, FEOSLobbyDetailsInfoDeleter>;`
- L326 _private prototype_ `FLobbyDetailsInfoEOS(FLobbyDetailsInfoPtr&& LobbyDetailsInfo);`
- L328 _private member_ `TUniquePtr<EOS_LobbyDetails_Info, FEOSLobbyDetailsInfoDeleter> LobbyDetailsInfo;`
- L329 _private member_ `FLobbyBucketIdEOS BucketId;`

#### struct `UE::Online::FLobbyDetailsInfoEOS::FEOSLobbyDetailsInfoDeleter`  
`struct FEOSLobbyDetailsInfoDeleter`  
_L314-320_
- L316 _public function_ `void operator()(EOS_LobbyDetails_Info* Ptr) const`

#### class `UE::Online::FLobbyDataEOS`  
`class FLobbyDataEOS final : public TSharedFromThis<FLobbyDataEOS>`  
_L333-376_
- inherits: `TSharedFromThis<FLobbyDataEOS>`
- desc: Lobby data is the bookkeeping object for a lobby. It contains the client-side representation of a lobby.
- L336 _public typedef_ `using FUnregisterFn = TFunction<void(FLobbyId)>;`
- L338 _public prototype_ `FLobbyDataEOS() = delete;`
- L340 _public prototype_ `static TFuture<TDefaultErrorResultInternal<TSharedRef<FLobbyDataEOS>>> Create( TSharedRef<FLobbyPrerequisitesEOS> Prerequisites, FLobbyId LobbyId, const TSharedRef<FLobbyDetailsEOS>& LobbyDetails, FUnregisterFn UnregisterFn = FUnregisterFn());`
- L346 _public prototype_ `~FLobbyDataEOS();`
- L348 _public function_ `FLobbyId GetLobbyIdHandle() const`
- L349 _public function_ `const TSharedRef<FLobbyClientData>& GetLobbyClientData() const`
- L350 _public function_ `EOS_LobbyId GetLobbyIdEOS() const`
- L351 _public function_ `const FString& GetLobbyIdString() const`
- L353 _public prototype_ `void AddUserLobbyDetails(FAccountId LocalAccountId, const TSharedPtr<FLobbyDetailsEOS>& LobbyDetails);`
- L354 _public prototype_ `TSharedPtr<FLobbyDetailsEOS> GetUserLobbyDetails(FAccountId LocalAccountId) const;`
- L360 _public prototype_ `TSharedPtr<FLobbyDetailsEOS> GetActiveLobbyDetails() const;` — Active lobby details are needed to process lobby notifications. Search for and return active lobby details if available.
- L366 _private prototype_ `FLobbyDataEOS( const TSharedRef<FLobbyClientData>& LobbyClientData, const TSharedRef<FLobbyDetailsInfoEOS>& LobbyDetailsInfo, FUnregisterFn UnregisterFn);`
- L371 _private member_ `TSharedRef<FLobbyClientData> LobbyClientData;`
- L372 _private member_ `TSharedRef<FLobbyDetailsInfoEOS> LobbyDetailsInfo;`
- L373 _private member_ `FUnregisterFn UnregisterFn;`
- L374 _private member_ `FString LobbyIdString;`
- L375 _private member_ `TMap<FAccountId, TSharedPtr<FLobbyDetailsEOS>> UserLobbyDetails;`

#### class `UE::Online::FLobbyDataRegistryEOS`  
`class FLobbyDataRegistryEOS : public TSharedFromThis<FLobbyDataRegistryEOS>`  
_L379-397_
- inherits: `TSharedFromThis<FLobbyDataRegistryEOS>`
- desc: Todo: implement handling for FOnlineIdRegistryRegistry.
- L382 _public prototype_ `FLobbyDataRegistryEOS(const TSharedRef<FLobbyPrerequisitesEOS>& Prerequisites);`
- L384 _public prototype_ `TSharedPtr<FLobbyDataEOS> Find(EOS_LobbyId LobbyIdEOS) const;`
- L385 _public prototype_ `TSharedPtr<FLobbyDataEOS> Find(FLobbyId LobbyId) const;`
- L386 _public prototype_ `TFuture<TDefaultErrorResultInternal<TSharedRef<FLobbyDataEOS>>> FindOrCreateFromLobbyDetails(FAccountId LocalAccountId, const TSharedRef<FLobbyDetailsEOS>& LobbyDetails);`
- L389 _private prototype_ `void Register(const TSharedRef<FLobbyDataEOS>& LobbyIdHandleData);`
- L390 _private prototype_ `void Unregister(FLobbyId LobbyId);`
- L391 _private prototype_ `FLobbyDataEOS::FUnregisterFn MakeUnregisterFn();`
- L393 _private member_ `TSharedRef<FLobbyPrerequisitesEOS> Prerequisites;`
- L394 _private member_ `TMap<FString, TWeakPtr<FLobbyDataEOS>> LobbyIdIndex;`
- L395 _private member_ `TMap<FLobbyId, TWeakPtr<FLobbyDataEOS>> LobbyIdHandleIndex;`
- L396 _private member_ `uint32 NextHandleIndex = 1;`

#### class `UE::Online::FLobbyInviteIdEOS`  
`class FLobbyInviteIdEOS final`  
_L399-413_
- L402 _public prototype_ `FLobbyInviteIdEOS() = default;`
- L403 _public function_ `FLobbyInviteIdEOS(const char* InviteIdEOS)`
- L408 _public function_ `const char* Get() const`
- L411 _private member_ `static const int MaxLobbyInviteIdSize = 256;`
- L412 _private member_ `char Data[MaxLobbyInviteIdSize] = {};`

#### class `UE::Online::FLobbyInviteDataEOS`  
`class FLobbyInviteDataEOS final`  
_L418-456_
- desc: Lobby invite data will keep the lobby object valid until the invitation has been accepted or rejected.
- L421 _public prototype_ `FLobbyInviteDataEOS() = delete;`
- L423 _public prototype_ `static TFuture<TDefaultErrorResultInternal<TSharedRef<FLobbyInviteDataEOS>>> CreateFromInviteId( const TSharedRef<FLobbyPrerequisitesEOS>& Prerequisites, const TSharedRef<FLobbyDataRegistryEOS>& LobbyDataRegistry, FAccountId LocalAccountId, const char* InviteIdEOS, EOS_ProductUserId Sender);`
- L430 _public function_ `TSharedRef<FLobbyDetailsEOS> GetLobbyDetails() const`
- L431 _public function_ `TSharedRef<FLobbyDataEOS> GetLobbyData() const`
- L433 _public function_ `const char* GetInviteIdEOS() const`
- L434 _public function_ `const FString& GetInviteId() const`
- L436 _public function_ `FAccountId GetReceiver() const`
- L437 _public function_ `FAccountId GetSender() const`
- L443 _private prototype_ `FLobbyInviteDataEOS( const TSharedRef<FLobbyInviteIdEOS>& InviteIdEOS, FAccountId Receiver, FAccountId Sender, const TSharedRef<FLobbyDetailsEOS>& LobbyDetails, const TSharedRef<FLobbyDataEOS>& LobbyData);`
- L450 _private member_ `TSharedRef<FLobbyInviteIdEOS> InviteIdEOS;`
- L451 _private member_ `FAccountId Receiver;`
- L452 _private member_ `FAccountId Sender;`
- L453 _private member_ `TSharedRef<FLobbyDetailsEOS> LobbyDetails;`
- L454 _private member_ `TSharedRef<FLobbyDataEOS> LobbyData;`
- L455 _private member_ `FString InviteId;`

#### class `UE::Online::FLobbySearchEOS`  
`class FLobbySearchEOS final`  
_L462-502_
- desc: The lobby search object is meant to hold the lifetimes of lobby search results so that the lobby details will be discoverable during a join operation.
- L465 _public prototype_ `FLobbySearchEOS() = delete;`
- L467 _public prototype_ `static TFuture<TDefaultErrorResultInternal<TSharedRef<FLobbySearchEOS>>> Create( const TSharedRef<FLobbyPrerequisitesEOS>& Prerequisites, const TSharedRef<FLobbyDataRegistryEOS>& LobbyRegistry, const FLobbySearchParameters& Params);`
- L472 _public prototype_ `TArray<TSharedRef<const FLobby>> GetLobbyResults() const;`
- L473 _public prototype_ `const TArray<TSharedRef<FLobbyDataEOS>>& GetLobbyData();`
- L498 _private prototype_ `FLobbySearchEOS(const TSharedRef<FSearchHandle>& SearchHandle, TArray<TSharedRef<FLobbyDataEOS>>&& Lobbies);`
- L500 _private member_ `TSharedRef<FSearchHandle> SearchHandle;`
- L501 _private member_ `TArray<TSharedRef<FLobbyDataEOS>> Lobbies;`

#### class `UE::Online::FLobbySearchEOS::FSearchHandle`  
`class FSearchHandle`  
_L476-494_
- L480 _public prototype_ `FSearchHandle() = default;`
- L482 _public function_ `~FSearchHandle()`
- L487 _public function_ `EOS_HLobbySearch& Get()`
- L493 _private member_ `EOS_HLobbySearch SearchHandle = {};`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Online` (scope `UE`)
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace Online` (scope `UE`)
- L35 _macro_ `#define UE_ONLINE_LOBBIES_BUCKET_ID_EOS_SEPARATOR TEXT("|")`
- L67 _prototype_ `FString ToLogString(const FLobbyBucketIdEOS& BucketId);` (scope `UE::Online`)
- L150 _function_ `inline EOS_ELobbyPermissionLevel TranslateJoinPolicy(ELobbyJoinPolicy JoinPolicy)` (scope `UE::Online`)
- L161 _function_ `inline ELobbyJoinPolicy TranslateJoinPolicy(EOS_ELobbyPermissionLevel JoinPolicy)` (scope `UE::Online`)
- L176 _typedef_ `using FLobbySearchParameters = FFindLobbies::Params;` (scope `UE::Online`)
- L504 _prototype_ `FString ToLogString(const FLobbyDataEOS& LobbyData);` (scope `UE::Online`)
- L506 _function_ `inline FString LexToString(const FLobbyDataEOS& LobbyData)` (scope `UE::Online`)

### `Plugins/Online/OnlineServicesEOSGS/Source/Private/Online/SocketSubsystemEOSUtils_OnlineServicesEOSGS.h` (Private)


#### class `UE::Online::FSocketSubsystemEOSUtils_OnlineServicesEOS`  
`class FSocketSubsystemEOSUtils_OnlineServicesEOS : public ISocketSubsystemEOSUtils`  
_L13-28_
- inherits: `ISocketSubsystemEOSUtils`
- L16 _public prototype_ `FSocketSubsystemEOSUtils_OnlineServicesEOS(FOnlineServicesEOSGS& InServicesEOS);`
- L17 _public prototype_ `virtual ~FSocketSubsystemEOSUtils_OnlineServicesEOS();`
- L20 _public prototype_ `virtual EOS_ProductUserId GetLocalUserId() override;`
- L22 _public prototype_ `virtual FString GetSessionId() override;`
- L23 _public prototype_ `virtual FName GetSubsystemInstanceName() override;`
- L24 _public prototype_ `virtual bool IsLoggedIn() override;`
- L27 _private member_ `FOnlineServicesEOSGS& ServicesEOSGS;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Online` (scope `UE`)

### `Plugins/Online/OnlineServicesEOSGS/Source/Public/Online/AchievementsEOSGS.h` (Public)


#### class `UE::Online::FAchievementsEOSGS`  
`class FAchievementsEOSGS : public FAchievementsCommon`  
_L17-48_
- inherits: `FAchievementsCommon`
- L20 _public typedef_ `using Super = FAchievementsCommon;`
- L22 _public prototype_ `FAchievementsEOSGS(FOnlineServicesEpicCommon& InOwningSubsystem);`
- L23 _public prototype_ `virtual ~FAchievementsEOSGS() = default;`
- L26 _public prototype_ `virtual void Initialize() override;` — IOnlineComponent
- L27 _public prototype_ `virtual void Shutdown() override;`
- L30 _public prototype_ `virtual TOnlineAsyncOpHandle<FQueryAchievementDefinitions> QueryAchievementDefinitions(FQueryAchievementDefinitions::Params&& Params) override;` — IAchievements
- L31 _public prototype_ `virtual TOnlineResult<FGetAchievementIds> GetAchievementIds(FGetAchievementIds::Params&& Params) override;`
- L32 _public prototype_ `virtual TOnlineResult<FGetAchievementDefinition> GetAchievementDefinition(FGetAchievementDefinition::Params&& Params) override;`
- L33 _public prototype_ `virtual TOnlineAsyncOpHandle<FQueryAchievementStates> QueryAchievementStates(FQueryAchievementStates::Params&& Params) override;`
- L34 _public prototype_ `virtual TOnlineResult<FGetAchievementState> GetAchievementState(FGetAchievementState::Params&& Params) const override;`
- L35 _public prototype_ `virtual TOnlineAsyncOpHandle<FUnlockAchievements> UnlockAchievements(FUnlockAchievements::Params&& Params) override;`
- L38 _protected prototype_ `void HandleAchievementsUnlocked(const EOS_Achievements_OnAchievementsUnlockedCallbackV2Info* Data);`
- L40 _protected prototype_ `FAccountId FindAccountId(const EOS_ProductUserId ProductUserId);`
- L42 _protected member_ `EOS_HAchievements AchievementsHandle = nullptr;`
- L44 _protected typedef_ `using FAchievementDefinitionMap = TMap<FString, FAchievementDefinition>;`
- L45 _protected member_ `TOptional<FAchievementDefinitionMap> AchievementDefinitions;`
- L47 _protected member_ `FEOSEventRegistrationPtr OnAchievementsUnlocked;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Online` (scope `UE`)

### `Plugins/Online/OnlineServicesEOSGS/Source/Public/Online/AuthEOSGS.h` (Public)


#### struct `UE::Online::FAuthLoginEASImpl`  
`struct FAuthLoginEASImpl`  
_L20-38_
- L22 _public member_ `static constexpr TCHAR Name[] = TEXT("Log`

#### struct `UE::Online::FAuthLoginEASImpl::Params`  
`struct Params`  
_L24-32_
- L26 _public member_ `FPlatformUserId PlatformUserId = PLATFORMUSERID_NONE;`
- L27 _public member_ `FName CredentialsType;`
- L28 _public member_ `FString CredentialsId;`
- L29 _public member_ `TVariant<FString, FExternalAuthToken> CredentialsToken;`
- L30 _public member_ `TArray<FString> Scopes;`
- L31 _public member_ `bool bAutoLinkAccount = true;`

#### struct `UE::Online::FAuthLoginEASImpl::Result`  
`struct Result`  
_L34-37_
- L36 _public member_ `EOS_EpicAccountId EpicAccountId = nullptr;`

#### struct `UE::Online::FAuthLogoutEASImpl`  
`struct FAuthLogoutEASImpl`  
_L40-52_
- L42 _public member_ `static constexpr TCHAR Name[] = TEXT("Log`

#### struct `UE::Online::FAuthLogoutEASImpl::Params`  
`struct Params`  
_L44-47_
- L46 _public member_ `EOS_EpicAccountId EpicAccountId = nullptr;`

#### struct `UE::Online::FAuthLogoutEASImpl::Result`  
`struct Result`  
_L49-51_

#### struct `UE::Online::FAuthLogoutConnectImpl`  
`struct FAuthLogoutConnectImpl`  
_L54-66_
- L56 _public member_ `static constexpr TCHAR Name[] = TEXT("Log`

#### struct `UE::Online::FAuthLogoutConnectImpl::Params`  
`struct Params`  
_L58-61_
- L60 _public member_ `EOS_ProductUserId ProductUserId = nullptr;`

#### struct `UE::Online::FAuthLogoutConnectImpl::Result`  
`struct Result`  
_L63-65_

#### struct `UE::Online::FAuthGetExternalAuthTokenImpl`  
`struct FAuthGetExternalAuthTokenImpl`  
_L68-81_
- L70 _public member_ `static constexpr TCHAR Name[] = TEXT("Get`

#### struct `UE::Online::FAuthGetExternalAuthTokenImpl::Params`  
`struct Params`  
_L72-75_
- L74 _public member_ `EOS_EpicAccountId EpicAccountId = nullptr;`

#### struct `UE::Online::FAuthGetExternalAuthTokenImpl::Result`  
`struct Result`  
_L77-80_
- L79 _public member_ `FExternalAuthToken Token;`

#### struct `UE::Online::FAuthLoginConnectImpl`  
`struct FAuthLoginConnectImpl`  
_L83-97_
- L85 _public member_ `static constexpr TCHAR Name[] = TEXT("Log`

#### struct `UE::Online::FAuthLoginConnectImpl::Params`  
`struct Params`  
_L87-91_
- L89 _public member_ `FPlatformUserId PlatformUserId = PLATFORMUSERID_NONE;`
- L90 _public member_ `FExternalAuthToken ExternalAuthToken;`

#### struct `UE::Online::FAuthLoginConnectImpl::Result`  
`struct Result`  
_L93-96_
- L95 _public member_ `EOS_ProductUserId ProductUserId = nullptr;`

#### struct `UE::Online::FAuthConnectLoginRecoveryImpl`  
`struct FAuthConnectLoginRecoveryImpl`  
_L99-112_
- L101 _public member_ `static constexpr TCHAR Name[] = TEXT("Con`

#### struct `UE::Online::FAuthConnectLoginRecoveryImpl::Params`  
`struct Params`  
_L103-107_
- L106 _public member_ `EOS_EpicAccountId LocalUserId = nullptr;` — The Epic Account ID of the local user whose connect login should be recovered.

#### struct `UE::Online::FAuthConnectLoginRecoveryImpl::Result`  
`struct Result`  
_L109-111_

#### struct `UE::Online::FAuthHandleConnectLoginStatusChangedImpl`  
`struct FAuthHandleConnectLoginStatusChangedImpl`  
_L114-131_
- L116 _public member_ `static constexpr TCHAR Name[] = TEXT("Han`

#### struct `UE::Online::FAuthHandleConnectLoginStatusChangedImpl::Params`  
`struct Params`  
_L118-126_
- L121 _public member_ `EOS_ProductUserId LocalUserId = nullptr;` — The Product User ID of the local player whose status has changed.
- L123 _public member_ `EOS_ELoginStatus PreviousStatus = EOS_ELoginStatus::EOS_LS_NotLoggedIn;` — The status prior to the change.
- L125 _public member_ `EOS_ELoginStatus CurrentStatus = EOS_ELoginStatus::EOS_LS_NotLoggedIn;` — The status at the time of the notification.

#### struct `UE::Online::FAuthHandleConnectLoginStatusChangedImpl::Result`  
`struct Result`  
_L128-130_

#### struct `UE::Online::FAuthHandleConnectAuthNotifyExpirationImpl`  
`struct FAuthHandleConnectAuthNotifyExpirationImpl`  
_L133-146_
- L135 _public member_ `static constexpr TCHAR Name[] = TEXT("Han`

#### struct `UE::Online::FAuthHandleConnectAuthNotifyExpirationImpl::Params`  
`struct Params`  
_L137-141_
- L140 _public member_ `EOS_ProductUserId LocalUserId = nullptr;` — The Product User ID of the local player whose status has changed.

#### struct `UE::Online::FAuthHandleConnectAuthNotifyExpirationImpl::Result`  
`struct Result`  
_L143-145_

#### struct `UE::Online::FAuthHandleEASLoginStatusChangedImpl`  
`struct FAuthHandleEASLoginStatusChangedImpl`  
_L148-165_
- L150 _public member_ `static constexpr TCHAR Name[] = TEXT("Han`

#### struct `UE::Online::FAuthHandleEASLoginStatusChangedImpl::Params`  
`struct Params`  
_L152-160_
- L155 _public member_ `EOS_EpicAccountId LocalUserId = nullptr;` — The Epic Account ID of the local user whose status has changed
- L157 _public member_ `EOS_ELoginStatus PreviousStatus = EOS_ELoginStatus::EOS_LS_NotLoggedIn;` — The status prior to the change
- L159 _public member_ `EOS_ELoginStatus CurrentStatus = EOS_ELoginStatus::EOS_LS_NotLoggedIn;` — The status at the time of the notification

#### struct `UE::Online::FAuthHandleEASLoginStatusChangedImpl::Result`  
`struct Result`  
_L162-164_

#### struct `UE::Online::FAccountInfoEOS`  
`struct FAccountInfoEOS final : public FAccountInfo`  
_L167-172_
- inherits: `FAccountInfo`
- L169 _public member_ `FTSTicker::FDelegateHandle RestoreLoginTimer;`
- L170 _public member_ `EOS_EpicAccountId EpicAccountId = nullptr;`
- L171 _public member_ `EOS_ProductUserId ProductUserId = nullptr;`

#### class `UE::Online::FAccountInfoRegistryEOS`  
`class FAccountInfoRegistryEOS final : public FAccountInfoRegistry`  
_L174-196_
- inherits: `FAccountInfoRegistry`
- L177 _public typedef_ `using Super = FAccountInfoRegistry;`
- L179 _public prototype_ `virtual ~FAccountInfoRegistryEOS() = default;`
- L181 _public prototype_ `TSharedPtr<FAccountInfoEOS> Find(FPlatformUserId PlatformUserId) const;`
- L182 _public prototype_ `TSharedPtr<FAccountInfoEOS> Find(FAccountId AccountId) const;`
- L183 _public prototype_ `TSharedPtr<FAccountInfoEOS> Find(EOS_EpicAccountId EpicAccountId) const;`
- L184 _public prototype_ `TSharedPtr<FAccountInfoEOS> Find(EOS_ProductUserId ProductUserId) const;`
- L186 _public prototype_ `void Register(const TSharedRef<FAccountInfoEOS>& UserAuthData);`
- L187 _public prototype_ `void Unregister(FAccountId AccountId);`
- L190 _protected prototype_ `virtual void DoRegister(const TSharedRef<FAccountInfo>& AccountInfo);`
- L191 _protected prototype_ `virtual void DoUnregister(const TSharedRef<FAccountInfo>& AccountInfo);`
- L194 _private member_ `TMap<EOS_EpicAccountId, TSharedRef<FAccountInfoEOS>> AuthDataByEpicAccountId;`
- L195 _private member_ `TMap<EOS_ProductUserId, TSharedRef<FAccountInfoEOS>> AuthDataByProductUserId;`

#### class `UE::Online::FAuthEOSGS`  
`class FAuthEOSGS : public FAuthCommon`  
_L198-282_
- inherits: `FAuthCommon`
- L201 _public typedef_ `using Super = FAuthCommon;`
- L203 _public prototype_ `FAuthEOSGS(FOnlineServicesCommon& InOwningSubsystem);`
- L204 _public prototype_ `virtual ~FAuthEOSGS() = default;`
- L207 _public prototype_ `virtual void Initialize() override;`
- L211 _public prototype_ `virtual void PreShutdown() override;`
- L212 _public prototype_ `virtual TOnlineAsyncOpHandle<FAuthLogin> Login(FAuthLogin::Params&& Params) override;`
- L213 _public prototype_ `virtual TOnlineAsyncOpHandle<FAuthLogout> Logout(FAuthLogout::Params&& Params) override;`
- L214 _public prototype_ `virtual TOnlineAsyncOpHandle<FAuthQueryVerifiedAuthTicket> QueryVerifiedAuthTicket(FAuthQueryVerifiedAuthTicket::Params&& Params) override;`
- L215 _public prototype_ `virtual TOnlineAsyncOpHandle<FAuthCancelVerifiedAuthTicket> CancelVerifiedAuthTicket(FAuthCancelVerifiedAuthTicket::Params&& Params) override;`
- L216 _public prototype_ `virtual TOnlineAsyncOpHandle<FAuthBeginVerifiedAuthSession> BeginVerifiedAuthSession(FAuthBeginVerifiedAuthSession::Params&& Params) override;`
- L217 _public prototype_ `virtual TOnlineAsyncOpHandle<FAuthEndVerifiedAuthSession> EndVerifiedAuthSession(FAuthEndVerifiedAuthSession::Params&& Params) override;`
- L218 _public prototype_ `virtual TOnlineResult<FAuthGetRelyingParty> GetRelyingParty(FAuthGetRelyingParty::Params&& Params) const override;`
- L224 _protected prototype_ `TFuture<TDefaultErrorResult<FAuthLoginEASImpl>> LoginEASImpl(const FAuthLoginEASImpl::Params& LoginParams);`
- L225 _protected prototype_ `TFuture<TDefaultErrorResult<FAuthLogoutEASImpl>> LogoutEASImpl(const FAuthLogoutEASImpl::Params& LogoutParams);`
- L226 _protected prototype_ `TDefaultErrorResult<FAuthGetExternalAuthTokenImpl> GetExternalAuthTokenImpl(const FAuthGetExternalAuthTokenImpl::Params& Params);`
- L227 _protected prototype_ `TFuture<TDefaultErrorResult<FAuthLoginConnectImpl>> LoginConnectImpl(const FAuthLoginConnectImpl::Params& LoginParams);`
- L228 _protected prototype_ `TFuture<TDefaultErrorResult<FAuthLogoutConnectImpl>> LogoutConnectImpl(const FAuthLogoutConnectImpl::Params& LogoutParams);`
- L229 _protected prototype_ `TOnlineAsyncOpHandle<FAuthConnectLoginRecoveryImpl> ConnectLoginRecoveryImplOp(FAuthConnectLoginRecoveryImpl::Params&& Params);`
- L230 _protected prototype_ `TOnlineAsyncOpHandle<FAuthHandleConnectLoginStatusChangedImpl> HandleConnectLoginStatusChangedImplOp(FAuthHandleConnectLoginStatusChangedImpl::Params&& Params);`
- L231 _protected prototype_ `TOnlineAsyncOpHandle<FAuthHandleConnectAuthNotifyExpirationImpl> HandleConnectAuthNotifyExpirationImplOp(FAuthHandleConnectAuthNotifyExpirationImpl::Params&& Params);`
- L232 _protected prototype_ `TOnlineAsyncOpHandle<FAuthHandleEASLoginStatusChangedImpl> HandleEASLoginStatusChangedImplOp(FAuthHandleEASLoginStatusChangedImpl::Params&& Params);`
- L236 _protected prototype_ `void RegisterHandlers();` — Service event handling.
- L237 _protected prototype_ `void UnregisterHandlers();`
- L238 _protected prototype_ `void OnConnectLoginStatusChanged(const EOS_Connect_LoginStatusChangedCallbackInfo* Data);`
- L239 _protected prototype_ `void OnConnectAuthNotifyExpiration(const EOS_Connect_AuthExpirationCallbackInfo* Data);`
- L240 _protected prototype_ `void OnEASLoginStatusChanged(const EOS_Auth_LoginStatusChangedCallbackInfo* Data);`
- L244 _protected typedef_ `template <typename ValueType> using TLocalUserArray = TSparseArray<ValueType, TInlineSparseArrayAllocator<MAX_LOCAL_PLAYERS>>;`
- L259 _protected member_ `uint32 NextLoginContinuationId = 1;`
- L262 _protected prototype_ `static void CheckMetadata();`
- L265 _protected prototype_ `virtual const FAccountInfoRegistry& GetAccountInfoRegistry() const override;`
- L267 _protected prototype_ `void InitializeConnectLoginRecoveryTimer(const TSharedRef<FAccountInfoEOS>& UserAuthData);`
- L269 _protected prototype_ `static FAccountId CreateAccountId(const EOS_ProductUserId ProductUserId);`
- L271 _protected prototype_ `FUserScopedData* GetUserScopedData(FPlatformUserId PlatformUserId);`
- L272 _protected prototype_ `const FUserScopedData* GetUserScopedData(FPlatformUserId PlatformUserId) const;`
- L273 _protected prototype_ `FUserScopedData* GetOrCreateUserScopedData(FPlatformUserId PlatformUserId);`
- L275 _protected member_ `EOS_HAuth AuthHandle = nullptr;`
- L276 _protected member_ `EOS_HConnect ConnectHandle = nullptr;`
- L277 _protected member_ `FEOSEventRegistrationPtr OnConnectLoginStatusChangedEOSEventRegistration;`
- L278 _protected member_ `FEOSEventRegistrationPtr OnConnectAuthNotifyExpirationEOSEventRegistration;`
- L279 _protected member_ `FEOSEventRegistrationPtr OnAuthLoginStatusChangedEOSEventRegistration;`
- L280 _protected member_ `FAccountInfoRegistryEOS AccountInfoRegistryEOS;`
- L281 _protected member_ `TLocalUserArray<FUserScopedData> UserScopedData;`

#### struct `UE::Online::FAuthEOSGS::FLoginContinuationData`  
`struct FLoginContinuationData`  
_L246-251_
- L248 _public member_ `FLoginContinuationId ContinuationId;`
- L249 _public member_ `EOS_ContinuanceToken ContinuanceToken;`
- L250 _public member_ `EOS_ELinkAccountFlags LinkAccountFlags = EOS_ELinkAccountFlags::EOS_LA_NoFlags;`

#### struct `UE::Online::FAuthEOSGS::FUserScopedData`  
`struct FUserScopedData`  
_L253-257_
- L255 _public member_ `FLoginContinuationId LastLoginContinuationId;`
- L256 _public member_ `TArray<FLoginContinuationData> LoginContinuations;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Online` (scope `UE`)
- L284 _namespace_ `namespace Meta` (scope `UE::Online`)

### `Plugins/Online/OnlineServicesEOSGS/Source/Public/Online/EpicProductUserIdResolverEOSGS.h` (Public)


#### class `UE::Online::FEpicProductUserIdResolverEOSGS`  
`class FEpicProductUserIdResolverEOSGS : public TOnlineComponent<IEpicProductUserIdResolver>`  
_L10-19_
- inherits: `TOnlineComponent<IEpicProductUserIdResolver>`
- L13 _public prototype_ `FEpicProductUserIdResolverEOSGS(class FOnlineServicesEOSGS& InServices);`
- L16 _public prototype_ `virtual TFuture<FAccountId> ResolveAccountId(const FAccountId LocalAccountId, const EOS_ProductUserId ProductUserId) override;`
- L17 _public prototype_ `virtual TFuture<TArray<FAccountId>> ResolveAccountIds(const FAccountId LocalAccountId, const TArray<EOS_ProductUserId>& ProductUserIds) override;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Online` (scope `UE`)

### `Plugins/Online/OnlineServicesEOSGS/Source/Public/Online/ExternalUIEOSGS.h` (Public)


#### struct `UE::Online::FExternalUIProcessDisplaySettingsUpdatedImp`  
`struct FExternalUIProcessDisplaySettingsUpdatedImp`  
_L17-35_
- L19 _public member_ `static constexpr TCHAR Name[] = TEXT("Pro`

#### struct `UE::Online::FExternalUIProcessDisplaySettingsUpdatedImp::Params`  
`struct Params`  
_L21-30_
- L24 _public member_ `bool bIsVisible = false;` — True when any portion of the overlay is visible.
- L29 _public member_ `bool bIsExclusiveInput = false;` — True when the overlay has switched to exclusive input mode. While in exclusive input mode, no keyboard or mouse input will be sent to the game.

#### struct `UE::Online::FExternalUIProcessDisplaySettingsUpdatedImp::Result`  
`struct Result`  
_L32-34_

#### class `UE::Online::FExternalUIEOSGS`  
`class FExternalUIEOSGS : public FExternalUICommon`  
_L37-59_
- inherits: `FExternalUICommon`
- L40 _public typedef_ `using Super = FExternalUICommon;`
- L42 _public prototype_ `FExternalUIEOSGS(FOnlineServicesEpicCommon& InOwningSubsystem);`
- L43 _public prototype_ `virtual ~FExternalUIEOSGS();`
- L45 _public prototype_ `virtual void Initialize() override;`
- L46 _public prototype_ `virtual void PreShutdown() override;`
- L49 _protected prototype_ `void RegisterEventHandlers();`
- L50 _protected prototype_ `void UnregisterEventHandlers();`
- L52 _protected prototype_ `void HandleDisplaySettingsUpdated(const EOS_UI_OnDisplaySettingsUpdatedCallbackInfo* Data);`
- L54 _protected prototype_ `TOnlineAsyncOpHandle<FExternalUIProcessDisplaySettingsUpdatedImp> ProcessDisplaySettingsUpdatedImplOp(FExternalUIProcessDisplaySettingsUpdatedImp::Params&& Params);`
- L56 _protected member_ `EOS_HUI UIInterfaceHandle = nullptr;`
- L57 _protected member_ `FEOSEventRegistrationPtr OnDisplaySettingsUpdated;`
- L58 _protected member_ `bool bLastReportedExclusiveInput = false;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API ONLINESERVICESEOSGS_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Online` (scope `UE`)
- L61 _namespace_ `namespace Meta` (scope `UE::Online`)

### `Plugins/Online/OnlineServicesEOSGS/Source/Public/Online/LeaderboardsEOSGS.h` (Public)


#### class `UE::Online::FLeaderboardsEOSGS`  
`class FLeaderboardsEOSGS : public FLeaderboardsCommon`  
_L16-35_
- inherits: `FLeaderboardsCommon`
- L19 _public typedef_ `using Super = FLeaderboardsCommon;`
- L21 _public prototype_ `FLeaderboardsEOSGS(FOnlineServicesEpicCommon& InOwningSubsystem);`
- L24 _public prototype_ `virtual void Initialize() override;` — TOnlineComponent
- L27 _public prototype_ `virtual TOnlineAsyncOpHandle<FReadEntriesForUsers> ReadEntriesForUsers(FReadEntriesForUsers::Params&& Params) override;` — ILeaderboards
- L28 _public prototype_ `virtual TOnlineAsyncOpHandle<FReadEntriesAroundRank> ReadEntriesAroundRank(FReadEntriesAroundRank::Params&& Params) override;`
- L29 _public prototype_ `virtual TOnlineAsyncOpHandle<FReadEntriesAroundUser> ReadEntriesAroundUser(FReadEntriesAroundUser::Params&& Params) override;`
- L32 _private prototype_ `void ReadEntriesInRange(uint32 StartIndex, uint32 EndIndex, TArray<FLeaderboardEntry>& OutEntries);`
- L34 _private member_ `EOS_HLeaderboards LeaderboardsHandle = nullptr;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Online` (scope `UE`)

### `Plugins/Online/OnlineServicesEOSGS/Source/Public/Online/LobbiesEOSGS.h` (Public)


#### struct `UE::Online::FLobbiesLeaveLobbyImpl`  
`struct FLobbiesLeaveLobbyImpl`  
_L24-40_
- L26 _public member_ `static constexpr TCHAR Name[] = TEXT("Lea`

#### struct `UE::Online::FLobbiesLeaveLobbyImpl::Params`  
`struct Params`  
_L28-35_
- L31 _public member_ `TSharedPtr<FLobbyDataEOS> LobbyData;` — The lobby handle data.
- L34 _public member_ `FAccountId LocalAccountId;` — The local user agent which will perform the action.

#### struct `UE::Online::FLobbiesLeaveLobbyImpl::Result`  
`struct Result`  
_L37-39_

#### struct `UE::Online::FLobbiesDestroyLobbyImpl`  
`struct FLobbiesDestroyLobbyImpl`  
_L42-58_
- L44 _public member_ `static constexpr TCHAR Name[] = TEXT("Des`

#### struct `UE::Online::FLobbiesDestroyLobbyImpl::Params`  
`struct Params`  
_L46-53_
- L49 _public member_ `FString LobbyIdString;` — The name of the lobby to be destroyed.
- L52 _public member_ `FAccountId LocalAccountId;` — The local user agent which will perform the action.

#### struct `UE::Online::FLobbiesDestroyLobbyImpl::Result`  
`struct Result`  
_L55-57_

#### struct `UE::Online::FLobbiesInviteLobbyMemberImpl`  
`struct FLobbiesInviteLobbyMemberImpl`  
_L60-79_
- L62 _public member_ `static constexpr TCHAR Name[] = TEXT("Inv`

#### struct `UE::Online::FLobbiesInviteLobbyMemberImpl::Params`  
`struct Params`  
_L64-74_
- L67 _public member_ `TSharedPtr<FLobbyDataEOS> LobbyData;` — The lobby handle data.
- L70 _public member_ `FAccountId LocalAccountId;` — The local user agent which will perform the action.
- L73 _public member_ `FAccountId TargetAccountId;` — The target user for the invitation.

#### struct `UE::Online::FLobbiesInviteLobbyMemberImpl::Result`  
`struct Result`  
_L76-78_

#### struct `UE::Online::FLobbiesDeclineLobbyInvitationImpl`  
`struct FLobbiesDeclineLobbyInvitationImpl`  
_L81-97_
- L83 _public member_ `static constexpr TCHAR Name[] = TEXT("Dec`

#### struct `UE::Online::FLobbiesDeclineLobbyInvitationImpl::Params`  
`struct Params`  
_L85-92_
- L88 _public member_ `FAccountId LocalAccountId;` — The local user agent which will perform the action.
- L91 _public member_ `FLobbyId LobbyId;` — Id of the lobby for which the invitations will be declined.

#### struct `UE::Online::FLobbiesDeclineLobbyInvitationImpl::Result`  
`struct Result`  
_L94-96_

#### struct `UE::Online::FLobbiesKickLobbyMemberImpl`  
`struct FLobbiesKickLobbyMemberImpl`  
_L99-118_
- L101 _public member_ `static constexpr TCHAR Name[] = TEXT("Kic`

#### struct `UE::Online::FLobbiesKickLobbyMemberImpl::Params`  
`struct Params`  
_L103-113_
- L106 _public member_ `TSharedPtr<FLobbyDataEOS> LobbyData;` — The lobby handle data.
- L109 _public member_ `FAccountId LocalAccountId;` — The local user agent which will perform the action.
- L112 _public member_ `FAccountId TargetAccountId;` — The target user to be kicked.

#### struct `UE::Online::FLobbiesKickLobbyMemberImpl::Result`  
`struct Result`  
_L115-117_

#### struct `UE::Online::FLobbiesPromoteLobbyMemberImpl`  
`struct FLobbiesPromoteLobbyMemberImpl`  
_L120-139_
- L122 _public member_ `static constexpr TCHAR Name[] = TEXT("Pro`

#### struct `UE::Online::FLobbiesPromoteLobbyMemberImpl::Params`  
`struct Params`  
_L124-134_
- L127 _public member_ `TSharedPtr<FLobbyDataEOS> LobbyData;` — The lobby handle data.
- L130 _public member_ `FAccountId LocalAccountId;` — The local user agent which will perform the action.
- L133 _public member_ `FAccountId TargetAccountId;` — The target user to be promoted to owner.

#### struct `UE::Online::FLobbiesPromoteLobbyMemberImpl::Result`  
`struct Result`  
_L136-138_

#### struct `UE::Online::FLobbiesModifyLobbyDataImpl`  
`struct FLobbiesModifyLobbyDataImpl`  
_L141-160_
- L143 _public member_ `static constexpr TCHAR Name[] = TEXT("Mod`

#### struct `UE::Online::FLobbiesModifyLobbyDataImpl::Params`  
`struct Params`  
_L145-155_
- L148 _public member_ `TSharedPtr<FLobbyDataEOS> LobbyData;` — The lobby handle data.
- L151 _public member_ `FAccountId LocalAccountId;` — The local user agent which will perform the action.
- L154 _public member_ `FLobbyClientServiceChanges ServiceChanges;` — Translated changes to be applied to the service.

#### struct `UE::Online::FLobbiesModifyLobbyDataImpl::Result`  
`struct Result`  
_L157-159_

#### struct `UE::Online::FLobbiesProcessLobbyNotificationImpl`  
`struct FLobbiesProcessLobbyNotificationImpl`  
_L162-184_
- L164 _public member_ `static constexpr TCHAR Name[] = TEXT("Pro`

#### struct `UE::Online::FLobbiesProcessLobbyNotificationImpl::Params`  
`struct Params`  
_L166-176_
- L169 _public member_ `TSharedPtr<FLobbyDataEOS> LobbyData;` — The lobby handle data.
- L172 _public member_ `TSet<EOS_ProductUserId> MutatedMembers;` — Joining / mutated members.
- L175 _public member_ `TMap<EOS_ProductUserId, ELobbyMemberLeaveReason> LeavingMembers;` — Leaving members.

#### struct `UE::Online::FLobbiesProcessLobbyNotificationImpl::Result`  
`struct Result`  
_L181-183_

#### class `UE::Online::FLobbiesEOSGS`  
`class FLobbiesEOSGS : public FLobbiesCommon`  
_L186-258_
- inherits: `FLobbiesCommon`
- L189 _public typedef_ `using Super = FLobbiesCommon;`
- L191 _public prototype_ `FLobbiesEOSGS(FOnlineServicesEpicCommon& InServices);`
- L193 _public prototype_ `virtual void Initialize() override;`
- L194 _public prototype_ `virtual void PreShutdown() override;`
- L196 _public prototype_ `virtual TOnlineAsyncOpHandle<FCreateLobby> CreateLobby(FCreateLobby::Params&& Params) override;`
- L197 _public prototype_ `virtual TOnlineAsyncOpHandle<FFindLobbies> FindLobbies(FFindLobbies::Params&& Params) override;`
- L198 _public prototype_ `virtual TOnlineAsyncOpHandle<FJoinLobby> JoinLobby(FJoinLobby::Params&& Params) override;`
- L199 _public prototype_ `virtual TOnlineAsyncOpHandle<FLeaveLobby> LeaveLobby(FLeaveLobby::Params&& Params) override;`
- L200 _public prototype_ `virtual TOnlineAsyncOpHandle<FInviteLobbyMember> InviteLobbyMember(FInviteLobbyMember::Params&& Params) override;`
- L201 _public prototype_ `virtual TOnlineAsyncOpHandle<FDeclineLobbyInvitation> DeclineLobbyInvitation(FDeclineLobbyInvitation::Params&& Params) override;`
- L202 _public prototype_ `virtual TOnlineAsyncOpHandle<FKickLobbyMember> KickLobbyMember(FKickLobbyMember::Params&& Params) override;`
- L203 _public prototype_ `virtual TOnlineAsyncOpHandle<FPromoteLobbyMember> PromoteLobbyMember(FPromoteLobbyMember::Params&& Params) override;`
- L204 _public prototype_ `virtual TOnlineAsyncOpHandle<FModifyLobbyJoinPolicy> ModifyLobbyJoinPolicy(FModifyLobbyJoinPolicy::Params&& Params) override;`
- L205 _public prototype_ `virtual TOnlineAsyncOpHandle<FModifyLobbyAttributes> ModifyLobbyAttributes(FModifyLobbyAttributes::Params&& Params) override;`
- L206 _public prototype_ `virtual TOnlineAsyncOpHandle<FModifyLobbyMemberAttributes> ModifyLobbyMemberAttributes(FModifyLobbyMemberAttributes::Params&& Params) override;`
- L207 _public prototype_ `virtual TOnlineResult<FGetJoinedLobbies> GetJoinedLobbies(FGetJoinedLobbies::Params&& Params) override;`
- L210 _private prototype_ `void HandleLobbyUpdated(const EOS_Lobby_LobbyUpdateReceivedCallbackInfo* Data);`
- L211 _private prototype_ `void HandleLobbyMemberUpdated(const EOS_Lobby_LobbyMemberUpdateReceivedCallbackInfo* Data);`
- L212 _private prototype_ `void HandleLobbyMemberStatusReceived(const EOS_Lobby_LobbyMemberStatusReceivedCallbackInfo* Data);`
- L213 _private prototype_ `void HandleLobbyInviteReceived(const EOS_Lobby_LobbyInviteReceivedCallbackInfo* Data);`
- L214 _private prototype_ `void HandleLobbyInviteAccepted(const EOS_Lobby_LobbyInviteAcceptedCallbackInfo* Data);`
- L215 _private prototype_ `void HandleJoinLobbyAccepted(const EOS_Lobby_JoinLobbyAcceptedCallbackInfo* Data);`
- L217 _private prototype_ `FAccountId FindAccountId(const EOS_ProductUserId ProductUserId);`
- L221 _protected prototype_ `static void CheckMetadata();`
- L224 _protected prototype_ `void RegisterHandlers();`
- L225 _protected prototype_ `void UnregisterHandlers();`
- L227 _protected prototype_ `void AddActiveLobby(FAccountId LocalAccountId, bool bPresenceEnabled, const TSharedRef<FLobbyDataEOS>& LobbyData);`
- L228 _protected prototype_ `void RemoveActiveLobby(FAccountId LocalAccountId, const TSharedRef<FLobbyDataEOS>& LobbyData);`
- L231 _protected prototype_ `void AddActiveInvite(const TSharedRef<FLobbyInviteDataEOS>& Invite);` — Todo: store list of invites per lobby.
- L232 _protected prototype_ `void RemoveActiveInvite(const TSharedRef<FLobbyInviteDataEOS>& Invite);`
- L233 _protected prototype_ `TSharedPtr<FLobbyInviteDataEOS> GetActiveInvite(FAccountId TargetUser, FLobbyId TargetLobbyId);`
- L236 _protected prototype_ `TFuture<TDefaultErrorResult<FLobbiesLeaveLobbyImpl>> LeaveLobbyImpl(FLobbiesLeaveLobbyImpl::Params&& Params);` — LobbyData will be fetched from the operation data if not set in Params.
- L237 _protected prototype_ `TFuture<TDefaultErrorResult<FLobbiesDestroyLobbyImpl>> DestroyLobbyImpl(FLobbiesDestroyLobbyImpl::Params&& Params);`
- L238 _protected prototype_ `TFuture<TDefaultErrorResult<FLobbiesInviteLobbyMemberImpl>> InviteLobbyMemberImpl(FLobbiesInviteLobbyMemberImpl::Params&& Params);`
- L239 _protected prototype_ `TFuture<TDefaultErrorResult<FLobbiesDeclineLobbyInvitationImpl>> DeclineLobbyInvitationImpl(FLobbiesDeclineLobbyInvitationImpl::Params&& Params);`
- L240 _protected prototype_ `TFuture<TDefaultErrorResult<FLobbiesKickLobbyMemberImpl>> KickLobbyMemberImpl(FLobbiesKickLobbyMemberImpl::Params&& Params);`
- L241 _protected prototype_ `TFuture<TDefaultErrorResult<FLobbiesPromoteLobbyMemberImpl>> PromoteLobbyMemberImpl(FLobbiesPromoteLobbyMemberImpl::Params&& Params);`
- L242 _protected prototype_ `TFuture<TDefaultErrorResult<FLobbiesModifyLobbyDataImpl>> ModifyLobbyDataImpl(FLobbiesModifyLobbyDataImpl::Params&& Params);`
- L243 _protected prototype_ `TOnlineAsyncOpHandle<FLobbiesProcessLobbyNotificationImpl> ProcessLobbyNotificationImplOp(FLobbiesProcessLobbyNotificationImpl::Params&& Params);`
- L245 _protected member_ `FEOSEventRegistrationPtr OnLobbyUpdatedEOSEventRegistration;`
- L246 _protected member_ `FEOSEventRegistrationPtr OnLobbyMemberUpdatedEOSEventRegistration;`
- L247 _protected member_ `FEOSEventRegistrationPtr OnLobbyMemberStatusReceivedEOSEventRegistration;`
- L248 _protected member_ `FEOSEventRegistrationPtr OnLobbyInviteReceivedEOSEventRegistration;`
- L249 _protected member_ `FEOSEventRegistrationPtr OnLobbyInviteAcceptedEOSEventRegistration;`
- L250 _protected member_ `FEOSEventRegistrationPtr OnJoinLobbyAcceptedEOSEventRegistration;`
- L252 _protected member_ `TSharedPtr<FLobbyPrerequisitesEOS> LobbyPrerequisites;`
- L253 _protected member_ `TSharedPtr<FLobbyDataRegistryEOS> LobbyDataRegistry;`
- L255 _protected member_ `TMap<FAccountId, TSet<TSharedRef<FLobbyDataEOS>>> ActiveLobbies;`
- L256 _protected member_ `TMap<FAccountId, TMap<FLobbyId, TSharedRef<FLobbyInviteDataEOS>>> ActiveInvites;`
- L257 _protected member_ `TMap<FAccountId, TSharedRef<FLobbySearchEOS>> ActiveSearchResults;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Online` (scope `UE`)
- L260 _namespace_ `namespace Meta` (scope `UE::Online`)

### `Plugins/Online/OnlineServicesEOSGS/Source/Public/Online/NboSerializerEOSGSSvc.h` (Public)


#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Online` (scope `UE`)
- L19 _namespace_ `namespace NboSerializerEOSGSSvc` (scope `UE::Online`)
- L23 _function_ `inline void SerializeToBuffer(FNboSerializeToBuffer& Ar, const EOnlineServices ServicesType)` (scope `UE::Online::NboSerializerEOSGSSvc`)
- L28 _function_ `inline void SerializeToBuffer(FNboSerializeToBuffer& Ar, const FAccountId& UniqueId)` (scope `UE::Online::NboSerializerEOSGSSvc`)
- L38 _function_ `inline void SerializeToBuffer(FNboSerializeToBuffer& Ar, const FOnlineSessionId& SessionId)` (scope `UE::Online::NboSerializerEOSGSSvc`)
- L48 _function_ `inline void SerializeToBuffer(FNboSerializeToBuffer& Packet, const FSessionMemberIdsSet& SessionMembersSet)` (scope `UE::Online::NboSerializerEOSGSSvc`)
- L60 _function_ `inline void SerializeFromBuffer(FNboSerializeFromBuffer& Ar, EOnlineServices& ServicesType)` (scope `UE::Online::NboSerializerEOSGSSvc`)
- L62 _typedef_ `using UnderlyingType = __underlying_type(EOnlineServices);` (scope `UE::Online::NboSerializerEOSGSSvc::SerializeFromBuffer`)
- L69 _function_ `inline void SerializeFromBuffer(FNboSerializeFromBuffer& Ar, FAccountId& UniqueId)` (scope `UE::Online::NboSerializerEOSGSSvc`)
- L83 _function_ `inline void SerializeFromBuffer(FNboSerializeFromBuffer& Ar, FOnlineSessionId& SessionId)` (scope `UE::Online::NboSerializerEOSGSSvc`)
- L97 _function_ `inline void SerializeFromBuffer(FNboSerializeFromBuffer& Packet, FSessionMemberIdsSet& SessionMembersSet)` (scope `UE::Online::NboSerializerEOSGSSvc`)

### `Plugins/Online/OnlineServicesEOSGS/Source/Public/Online/OnlineErrorEOSGS.h` (Public)
_(no declarations extracted)_

### `Plugins/Online/OnlineServicesEOSGS/Source/Public/Online/OnlineIdEOSGS.h` (Public)


#### class `UE::Online::IOnlineAccountIdRegistryEOSGS`  
`class IOnlineAccountIdRegistryEOSGS : public IOnlineAccountIdRegistry`  
_L15-21_
- inherits: `IOnlineAccountIdRegistry`
- L18 _public prototype_ `virtual FAccountId FindOrAddAccountId(const EOS_ProductUserId ProductUserId) = 0;`
- L19 _public prototype_ `virtual FAccountId FindAccountId(EOS_ProductUserId ProductUserId) const = 0;`
- L20 _public prototype_ `virtual EOS_ProductUserId GetProductUserId(const FAccountId& AccountId) const = 0;`

#### class `UE::Online::FOnlineAccountIdRegistryEOSGS`  
`class FOnlineAccountIdRegistryEOSGS : public IOnlineAccountIdRegistryEOSGS`  
_L26-57_
- inherits: `IOnlineAccountIdRegistryEOSGS`
- desc: Account id registry specifically for EOS id's which are segmented.
- L31 _public prototype_ `FOnlineAccountIdRegistryEOSGS();` — `UE_DEPRECATED(5.6, "This method is deprecated, please use the new version taking a EOnlineServices parameter")`
- L32 _public prototype_ `FOnlineAccountIdRegistryEOSGS(EOnlineServices Services);`
- L34 _public prototype_ `virtual ~FOnlineAccountIdRegistryEOSGS() = default;`
- L37 _public prototype_ `virtual FAccountId FindOrAddAccountId(const EOS_ProductUserId ProductUserId) override;`
- L38 _public prototype_ `virtual FAccountId FindAccountId(const EOS_ProductUserId ProductUserId) const override;`
- L39 _public prototype_ `virtual EOS_ProductUserId GetProductUserId(const FAccountId& AccountId) const override;`
- L43 _public prototype_ `virtual FString ToString(const FAccountId& AccountId) const override;`
- L44 _public prototype_ `virtual FString ToLogString(const FAccountId& AccountId) const override;`
- L45 _public prototype_ `virtual TArray<uint8> ToReplicationData(const FAccountId& AccountId) const override;`
- L46 _public prototype_ `virtual FAccountId FromReplicationData(const TArray<uint8>& ReplicationData) override;`
- L47 _public prototype_ `virtual FAccountId FromStringData(const FString& StringData) override;`
- L51 _public prototype_ `static IOnlineAccountIdRegistryEOSGS& GetRegistered();` — `UE_DEPRECATED(5.6, "This method is deprecated, please use the new version taking a EOnlineServices parameter")`
- L53 _public prototype_ `static IOnlineAccountIdRegistryEOSGS& GetRegistered(EOnlineServices Services);`
- L56 _private member_ `TOnlineBasicAccountIdRegistry<EOS_ProductUserId> Registry;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Online` (scope `UE`)
- L59 _prototype_ `EOS_ProductUserId GetProductUserId(const FAccountId& AccountId);` (scope `UE::Online`)
- L60 _prototype_ `EOS_ProductUserId GetProductUserIdChecked(const FAccountId& AccountId);` (scope `UE::Online`)
- L63 _prototype_ `FAccountId FindAccountId(const EOS_ProductUserId ProductUserId);` (scope `UE::Online`) — `UE_DEPRECATED(5.6, "This method is deprecated, please use the new version taking a EOnlineServices parameter")`
- L64 _prototype_ `FAccountId FindAccountId(EOnlineServices Services, const EOS_ProductUserId ProductUserId);` (scope `UE::Online`)
- L67 _prototype_ `FAccountId FindAccountIdChecked(const EOS_ProductUserId ProductUserId);` (scope `UE::Online`) — `UE_DEPRECATED(5.6, "This method is deprecated, please use the new version taking a EOnlineServices parameter")`
- L68 _prototype_ `FAccountId FindAccountIdChecked(EOnlineServices Services, const EOS_ProductUserId ProductUserId);` (scope `UE::Online`)
- L72 _function_ `inline bool ValidateOnlineId(const TOnlineId<IdType> OnlineId)` (scope `UE::Online`) — `UE_DEPRECATED(5.6, "This method is deprecated, please add an equivalent method or perform the relevant checks in your calling code")`

### `Plugins/Online/OnlineServicesEOSGS/Source/Public/Online/OnlineServicesEOSGS.h` (Public)


#### class `UE::Online::FOnlineServicesEOSGS`  
`class FOnlineServicesEOSGS : public FOnlineServicesEpicCommon`  
_L23-47_
- inherits: `FOnlineServicesEpicCommon`
- L26 _public typedef_ `using Super = FOnlineServicesEpicCommon;`
- L28 _public prototype_ `FOnlineServicesEOSGS(FName InstanceName, FName InstanceConfigName);`
- L29 _public prototype_ `virtual ~FOnlineServicesEOSGS() = default;`
- L31 _public prototype_ `virtual bool PreInit() override;`
- L32 _public prototype_ `virtual void Destroy() override;`
- L33 _public prototype_ `virtual void RegisterComponents() override;`
- L34 _public prototype_ `virtual TOnlineResult<FGetResolvedConnectString> GetResolvedConnectString(FGetResolvedConnectString::Params&& Params) override;`
- L35 _public function_ `virtual EOnlineServices GetServicesProvider() const override`
- L37 _public prototype_ `IPlayerReportsPtr GetPlayerReportsInterface();`
- L38 _public prototype_ `IPlayerSanctionsPtr GetPlayerSanctionsInterface();`
- L40 _public function_ `static const TCHAR* GetServiceConfigNameStatic()`
- L45 _protected member_ `TSharedPtr<FSocketSubsystemEOS, ESPMode::ThreadSafe> SocketSubsystem;`

#### Free symbols / members of external scopes

- L16 _typedef_ `using IEOSPlatformHandlePtr = TSharedPtr<class IEOSPlatformHandle>;`
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Online` (scope `UE`)
- L20 _typedef_ `using IPlayerReportsPtr = TSharedPtr<class IPlayerReports>;` (scope `UE::Online`)
- L21 _typedef_ `using IPlayerSanctionsPtr = TSharedPtr<class IPlayerSanctions>;` (scope `UE::Online`)

### `Plugins/Online/OnlineServicesEOSGS/Source/Public/Online/OnlineServicesEOSGSInterfaces/PlayerReports.h` (Public)


#### enum `UE::Online::EPlayerReportCategory`  
`enum class EPlayerReportCategory`  
_L14-23_
- L16 _public enumerator_ `Cheating`
- L17 _public enumerator_ `Exploiting`
- L18 _public enumerator_ `OffensiveProfile`
- L19 _public enumerator_ `VerbalAbuse`
- L20 _public enumerator_ `Scamming`
- L21 _public enumerator_ `Spamming`
- L22 _public enumerator_ `Other`

#### struct `UE::Online::FSendPlayerReport`  
`struct FSendPlayerReport`  
_L28-49_
- L30 _public member_ `static constexpr TCHAR Name[] = TEXT("Sen`

#### struct `UE::Online::FSendPlayerReport::Params`  
`struct Params`  
_L32-44_
- L35 _public member_ `FAccountId LocalAccountId;` — Required - Local user performing the operation
- L37 _public member_ `FAccountId TargetAccountId;` — Required - Target user of the player report
- L39 _public member_ `EPlayerReportCategory Category;` — Required - The category of the player
- L41 _public member_ `FString Message = "";` — Optional - Message from the player describing the issue being reported
- L43 _public member_ `FString Context = "";` — Optional - Context information around the issue being reported the game can send. This needs to be in a valid JSON format otherwise the EOS SDK will throw an error

#### struct `UE::Online::FSendPlayerReport::Result`  
`struct Result`  
_L46-48_

#### class `UE::Online::IPlayerReports`  
`class IPlayerReports`  
_L54-61_
- desc: Interface definition for the EOS player reports service
- L60 _public prototype_ `virtual TOnlineAsyncOpHandle<FSendPlayerReport> SendPlayerReport(FSendPlayerReport::Params&& Params) = 0;` — Send a player report for a player cheating, misconduct, etc...

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
- L25 _prototype_ `const TCHAR* LexToString(EPlayerReportCategory Value);` (scope `UE::Online`)
- L26 _prototype_ `void LexFromString(EPlayerReportCategory& OutValue, const TCHAR* InStr);` (scope `UE::Online`)
- L63 _namespace_ `namespace Meta` (scope `UE::Online`)

### `Plugins/Online/OnlineServicesEOSGS/Source/Public/Online/OnlineServicesEOSGSInterfaces/PlayerSanctions.h` (Public)


#### enum `UE::Online::EPlayerSanctionAppealReason`  
`enum class EPlayerSanctionAppealReason`  
_L14-20_
- L16 _public enumerator_ `IncorrectSanction`
- L17 _public enumerator_ `CompromisedAccount`
- L18 _public enumerator_ `UnfairPunishment`
- L19 _public enumerator_ `AppealForForgiveness`

#### struct `UE::Online::FCreatePlayerSanctionAppeal`  
`struct FCreatePlayerSanctionAppeal`  
_L25-42_
- L27 _public member_ `static constexpr TCHAR Name[] = TEXT("Cre`

#### struct `UE::Online::FCreatePlayerSanctionAppeal::Params`  
`struct Params`  
_L29-37_
- L32 _public member_ `FAccountId LocalAccountId;` — Local user id
- L34 _public member_ `EPlayerSanctionAppealReason Reason;` — The reason of the appeal
- L36 _public member_ `FString ReferenceId;` — The sanction id for the sanction that is being appealed

#### struct `UE::Online::FCreatePlayerSanctionAppeal::Result`  
`struct Result`  
_L39-41_

#### struct `UE::Online::FActivePlayerSanctionEntry`  
`struct FActivePlayerSanctionEntry`  
_L44-54_
- L47 _public member_ `int64_t TimePlaced;` — The time the sanction was placed
- L49 _public member_ `int64_t TimeExpires;` — The time the sanction expires
- L51 _public member_ `FString Action;` — The action associated with this sanction
- L53 _public member_ `FString ReferenceId;` — The sanction id for the sanction that is being appealed. This needs to be set

#### struct `UE::Online::FReadActivePlayerSanctions`  
`struct FReadActivePlayerSanctions`  
_L56-73_
- L58 _public member_ `static constexpr TCHAR Name[] = TEXT("Rea`

#### struct `UE::Online::FReadActivePlayerSanctions::Params`  
`struct Params`  
_L60-66_
- L63 _public member_ `FAccountId LocalAccountId;` — Local user id
- L65 _public member_ `FAccountId TargetAccountId;` — The account ids of the user we are querying active sanctions for

#### struct `UE::Online::FReadActivePlayerSanctions::Result`  
`struct Result`  
_L68-72_
- L71 _public member_ `TArray<FActivePlayerSanctionEntry> Entries;` — The result leaderboard entries

#### class `UE::Online::IPlayerSanctions`  
`class IPlayerSanctions`  
_L78-90_
- desc: Interface definition for the EOS player reports service
- L84 _public prototype_ `virtual TOnlineAsyncOpHandle<FCreatePlayerSanctionAppeal> CreatePlayerSanctionAppeal(FCreatePlayerSanctionAppeal::Params&& Params) = 0;` — Send a player sanction appeal
- L89 _public prototype_ `virtual TOnlineAsyncOpHandle<FReadActivePlayerSanctions> ReadEntriesForUser(FReadActivePlayerSanctions::Params&& Params) = 0;` — Read active player sanction for a specific user

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
- L22 _prototype_ `const TCHAR* LexToString(EPlayerSanctionAppealReason Value);` (scope `UE::Online`)
- L23 _prototype_ `void LexFromString(EPlayerSanctionAppealReason& OutValue, const TCHAR* InStr);` (scope `UE::Online`)
- L92 _namespace_ `namespace Meta` (scope `UE::Online`)

### `Plugins/Online/OnlineServicesEOSGS/Source/Public/Online/OnlineServicesEOSGSModule.h` (Public)


#### class `UE::Online::FOnlineServicesEOSGSModule`  
`class FOnlineServicesEOSGSModule : public IModuleInterface`  
_L9-19_
- inherits: `IModuleInterface`
- L12 _public prototype_ `static int GetRegistryPriority();`
- L16 _private prototype_ `virtual void StartupModule() override;`
- L17 _private prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Online` (scope `UE`)

### `Plugins/Online/OnlineServicesEOSGS/Source/Public/Online/OnlineServicesEOSGSTypes.h` (Public)


#### Free symbols / members of external scopes

- L9 _macro_ `#define LOBBIESEOSGS_LOBBY_ID_OVERRIDE_ATTRIBUTE_KEY TEXT("LOBBY_ID_OVERRIDE")`

### `Plugins/Online/OnlineServicesEOSGS/Source/Public/Online/PlayerReportsEOSGS.h` (Public)


#### class `UE::Online::FPlayerReportsEOSGS`  
`class FPlayerReportsEOSGS : public TOnlineComponent<IPlayerReports>`  
_L22-39_
- inherits: `TOnlineComponent<IPlayerReports>`
- L25 _public typedef_ `using Super = TOnlineComponent<IPlayerReports>;`
- L27 _public prototype_ `FPlayerReportsEOSGS(FOnlineServicesEOSGS& InOwningSubsystem);`
- L28 _public prototype_ `virtual ~FPlayerReportsEOSGS() = default;`
- L31 _public prototype_ `virtual void Initialize() override;` — IOnlineComponent
- L32 _public prototype_ `virtual void RegisterCommands() override;`
- L35 _public prototype_ `virtual TOnlineAsyncOpHandle<FSendPlayerReport> SendPlayerReport(FSendPlayerReport::Params&& Params) override;` — IPlayerReports
- L38 _private member_ `EOS_HReports PlayerReportsHandle = nullptr;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Online` (scope `UE`)
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Online` (scope `UE`)
- L41 _prototype_ `FString ToLogString(const FSendPlayerReport::Result& PlayerReports);` (scope `UE::Online`)

### `Plugins/Online/OnlineServicesEOSGS/Source/Public/Online/PlayerSanctionsEOSGS.h` (Public)


#### class `UE::Online::FPlayerSanctionsEOSGS`  
`class FPlayerSanctionsEOSGS : public TOnlineComponent<IPlayerSanctions>`  
_L20-38_
- inherits: `TOnlineComponent<IPlayerSanctions>`
- L23 _public typedef_ `using Super = TOnlineComponent<IPlayerSanctions>;`
- L25 _public prototype_ `FPlayerSanctionsEOSGS(FOnlineServicesEOSGS& InOwningSubsystem);`
- L26 _public prototype_ `virtual ~FPlayerSanctionsEOSGS() = default;`
- L29 _public prototype_ `virtual void Initialize() override;` — IOnlineComponent
- L30 _public prototype_ `virtual void RegisterCommands() override;`
- L33 _public prototype_ `virtual TOnlineAsyncOpHandle<FCreatePlayerSanctionAppeal> CreatePlayerSanctionAppeal(FCreatePlayerSanctionAppeal::Params&& Params) override;` — IPlayerSanctions
- L34 _public prototype_ `virtual TOnlineAsyncOpHandle<FReadActivePlayerSanctions> ReadEntriesForUser(FReadActivePlayerSanctions::Params&& Params) override;`
- L37 _private member_ `EOS_HSanctions PlayerSanctionsHandle = nullptr;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Online` (scope `UE`)
- L40 _prototype_ `FString ToLogString(const FReadActivePlayerSanctions::Result& ReadPlayerSanctionResult);` (scope `UE::Online`)

### `Plugins/Online/OnlineServicesEOSGS/Source/Public/Online/SessionsEOSGS.h` (Public)


#### class `UE::Online::FOnlineSessionIdRegistryEOSGS`  
`class FOnlineSessionIdRegistryEOSGS : public FOnlineSessionIdRegistryLAN`  
_L20-32_
- inherits: `FOnlineSessionIdRegistryLAN`
- L24 _public function_ `static FOnlineSessionIdRegistryEOSGS& Get()` — `UE_DEPRECATED(5.6, "This method is deprecated, please use GetRegistered(EOnlineServices)")`
- L26 _public prototype_ `static FOnlineSessionIdRegistryEOSGS& GetRegistered(EOnlineServices Services);`
- L31 _private prototype_ `FOnlineSessionIdRegistryEOSGS(EOnlineServices ServicesType);`

#### class `UE::Online::FOnlineSessionInviteIdRegistryEOSGS`  
`class FOnlineSessionInviteIdRegistryEOSGS : public FOnlineSessionInviteIdStringRegistry`  
_L34-46_
- inherits: `FOnlineSessionInviteIdStringRegistry`
- L38 _public function_ `static FOnlineSessionInviteIdRegistryEOSGS& Get()` — `UE_DEPRECATED(5.6, "This method is deprecated, please use GetRegistered(EOnlineServices)")`
- L40 _public prototype_ `static FOnlineSessionInviteIdRegistryEOSGS& GetRegistered(EOnlineServices Services);`
- L45 _private prototype_ `FOnlineSessionInviteIdRegistryEOSGS(EOnlineServices ServicesType);`

#### struct `UE::Online::FSessionModificationHandleEOSGS`  
`struct FSessionModificationHandleEOSGS : FNoncopyable`  
_L48-61_
- inherits: `FNoncopyable`
- L50 _public member_ `EOS_HSessionModification ModificationHandle;`
- L52 _public function_ `FSessionModificationHandleEOSGS(EOS_HSessionModification InModificationHandle) : ModificationHandle(InModificationHandle)`
- L57 _public function_ `~FSessionModificationHandleEOSGS()`

#### struct `UE::Online::FSessionSearchHandleEOSGS`  
`struct FSessionSearchHandleEOSGS : FNoncopyable`  
_L63-76_
- inherits: `FNoncopyable`
- L65 _public member_ `EOS_HSessionSearch SearchHandle;`
- L67 _public function_ `FSessionSearchHandleEOSGS(EOS_HSessionSearch InSearchHandle) : SearchHandle(InSearchHandle)`
- L72 _public function_ `~FSessionSearchHandleEOSGS()`

#### struct `UE::Online::FSessionDetailsHandleEOSGS`  
`struct FSessionDetailsHandleEOSGS : FNoncopyable`  
_L78-91_
- inherits: `FNoncopyable`
- L80 _public member_ `EOS_HSessionDetails SessionDetailsHandle;`
- L82 _public function_ `FSessionDetailsHandleEOSGS(EOS_HSessionDetails InSessionDetailsHandle) : SessionDetailsHandle(InSessionDetailsHandle)`
- L87 _public function_ `~FSessionDetailsHandleEOSGS()`

#### class `UE::Online::FSessionEOSGS`  
`class FSessionEOSGS : public FSessionLAN`  
_L93-107_
- inherits: `FSessionLAN`
- L96 _public prototype_ `FSessionEOSGS() = default;`
- L97 _public prototype_ `FSessionEOSGS(const FSessionEOSGS& InSession) = default;`
- L100 _public prototype_ `FSessionEOSGS(const FSessionsEOSGS& SessionsInstance, const TSharedPtr<FSessionDetailsHandleEOSGS>& InSessionDetailsHandle);` — This constructor should only be used by BuildSessionFromDetailsHandle, after all user ids in the session have been resolved.
- L102 _public prototype_ `static const FSessionEOSGS& Cast(const ISession& InSession);`
- L106 _public member_ `TSharedPtr<FSessionDetailsHandleEOSGS> SessionDetailsHandle;` — Session details handle

#### struct `UE::Online::FUpdateSessionJoinabilityImpl`  
`struct FUpdateSessionJoinabilityImpl`  
_L109-125_
- L111 _public member_ `static constexpr TCHAR Name[] = TEXT("Upd`

#### struct `UE::Online::FUpdateSessionJoinabilityImpl::Params`  
`struct Params`  
_L113-120_
- L116 _public member_ `FName SessionName;` — Name for the session, needed to start or end it
- L119 _public member_ `bool bAllowNewMembers;` — Whether players are accepted as new members in the session.

#### struct `UE::Online::FUpdateSessionJoinabilityImpl::Result`  
`struct Result`  
_L122-124_

#### struct `UE::Online::FUpdateSessionImplEOSGS`  
`struct FUpdateSessionImplEOSGS`  
_L129-147_
- L131 _public member_ `static constexpr TCHAR Name[] = TEXT("Upd`

#### struct `UE::Online::FUpdateSessionImplEOSGS::Params`  
`struct Params`  
_L133-140_
- L136 _public member_ `TSharedRef<FSessionModificationHandleEOSGS> SessionModificationHandle;` — Handle for the session modification operation
- L139 _public member_ `TOptional<FUpdateSessionJoinabilityParams> UpdateJoinabilitySettings;` — If set, it will use the values set in the struct to update the session's joinability

#### struct `UE::Online::FUpdateSessionImplEOSGS::Result`  
`struct Result`  
_L142-146_
- L145 _public member_ `FString NewSessionId;` — EOSGS Session Id for the created or modified session

#### struct `UE::Online::FSendSingleSessionInviteImpl`  
`struct FSendSingleSessionInviteImpl`  
_L149-165_
- L151 _public member_ `static constexpr TCHAR Name[] = TEXT("Sen`

#### struct `UE::Online::FSendSingleSessionInviteImpl::Params`  
`struct Params`  
_L153-160_
- L155 _public member_ `FAccountId LocalAccountId;`
- L157 _public member_ `FName SessionName;`
- L159 _public member_ `FAccountId TargetAccountId;`

#### struct `UE::Online::FSendSingleSessionInviteImpl::Result`  
`struct Result`  
_L162-164_

#### struct `UE::Online::FBuildSessionFromDetailsHandle`  
`struct FBuildSessionFromDetailsHandle`  
_L167-188_
- L169 _public member_ `static constexpr TCHAR Name[] = TEXT("Bui`

#### struct `UE::Online::FBuildSessionFromDetailsHandle::Params`  
`struct Params`  
_L171-178_
- L174 _public member_ `FAccountId LocalAccountId;` — User which will drive the id resolution
- L177 _public member_ `TSharedRef<FSessionDetailsHandleEOSGS> SessionDetailsHandleEOSGS;` — EOS session details handle used to extract the data

#### struct `UE::Online::FBuildSessionFromDetailsHandle::Result`  
`struct Result`  
_L180-187_
- L183 _public member_ `FAccountId LocalAccountId;` — User which started the resolution operation
- L186 _public member_ `TSharedRef<FSessionCommon> Session;` — Session built from the details handle

#### class `UE::Online::FSessionsEOSGS`  
`class FSessionsEOSGS : public FSessionsLAN`  
_L190-304_
- inherits: `FSessionsLAN`
- L195 _public typedef_ `using Super = FSessionsLAN;`
- L197 _public prototype_ `FSessionsEOSGS(FOnlineServicesEpicCommon& InOwningSubsystem);`
- L198 _public prototype_ `virtual ~FSessionsEOSGS() = default;`
- L201 _public prototype_ `void Initialize() override;` — TOnlineComponent
- L202 _public prototype_ `void Shutdown() override;`
- L205 _public prototype_ `virtual TOnlineResult<FSetPresenceSession> SetPresenceSession(FSetPresenceSession::Params&& Params) override;` — FSessionsCommon
- L206 _public prototype_ `virtual TOnlineResult<FClearPresenceSession> ClearPresenceSession(FClearPresenceSession::Params&& Params) override;`
- L207 _public prototype_ `virtual TFuture<TOnlineResult<FCreateSession>> CreateSessionImpl(const FCreateSession::Params& Params) override;`
- L208 _public prototype_ `virtual TFuture<TOnlineResult<FUpdateSessionSettings>> UpdateSessionSettingsImpl(const FUpdateSessionSettings::Params& Params) override;`
- L209 _public prototype_ `virtual TFuture<TOnlineResult<FLeaveSession>> LeaveSessionImpl(const FLeaveSession::Params& Params) override;`
- L210 _public prototype_ `virtual TFuture<TOnlineResult<FFindSessions>> FindSessionsImpl(const FFindSessions::Params& Params) override;`
- L211 _public prototype_ `virtual TFuture<TOnlineResult<FJoinSession>> JoinSessionImpl(const FJoinSession::Params& Params) override;`
- L212 _public prototype_ `virtual TFuture<TOnlineResult<FAddSessionMember>> AddSessionMemberImpl(const FAddSessionMember::Params& Params) override;`
- L213 _public prototype_ `virtual TFuture<TOnlineResult<FRemoveSessionMember>> RemoveSessionMemberImpl(const FRemoveSessionMember::Params& Params) override;`
- L214 _public prototype_ `virtual TFuture<TOnlineResult<FSendSessionInvite>> SendSessionInviteImpl(const FSendSessionInvite::Params& Params) override;`
- L215 _public prototype_ `virtual TFuture<TOnlineResult<FRejectSessionInvite>> RejectSessionInviteImpl(const FRejectSessionInvite::Params& Params) override;`
- L218 _protected prototype_ `virtual TOptional<FOnlineError> CheckState(const FCreateSession::Params& Params) const override;`
- L219 _protected prototype_ `virtual TOptional<FOnlineError> CheckState(const FJoinSession::Params& Params) const override;`
- L221 _protected prototype_ `void RegisterEventHandlers();`
- L222 _protected prototype_ `void UnregisterEventHandlers();`
- L223 _protected prototype_ `void HandleSessionInviteReceived(const EOS_Sessions_SessionInviteReceivedCallbackInfo* Data);`
- L224 _protected prototype_ `void HandleSessionInviteAccepted(const EOS_Sessions_SessionInviteAcceptedCallbackInfo* Data);`
- L225 _protected prototype_ `void HandleJoinSessionAccepted(const EOS_Sessions_JoinSessionAcceptedCallbackInfo* Data);`
- L227 _protected prototype_ `void SetHostAddress(EOS_HSessionModification& SessionModHAndle, FString HostAddress);`
- L228 _protected prototype_ `void SetJoinInProgressAllowed(EOS_HSessionModification& SessionModHandle, bool bIsJoinInProgressAllowed);`
- L229 _protected prototype_ `void SetInvitesAllowed(EOS_HSessionModification& SessionModHandle, bool bAreInvitesAllowed);`
- L230 _protected prototype_ `void SetPermissionLevel(EOS_HSessionModification& SessionModHandle, const ESessionJoinPolicy& JoinPolicy);`
- L231 _protected prototype_ `void SetBucketId(EOS_HSessionModification& SessionModHandle, const FString& NewBucketId);`
- L232 _protected prototype_ `void SetMaxPlayers(EOS_HSessionModification& SessionModHandle, const uint32& NewMaxPlayers);`
- L233 _protected prototype_ `void AddAttribute(EOS_HSessionModification& SessionModificationHandle, const FSchemaAttributeId& Key, const FCustomSessionSetting& Value);`
- L234 _protected prototype_ `void RemoveAttribute(EOS_HSessionModification& SessionModificationHandle, const FSchemaAttributeId& Key);`
- L236 _protected prototype_ `void SetSessionSearchMaxResults(FSessionSearchHandleEOSGS& SessionSearchHandle, uint32 MaxResults);`
- L237 _protected prototype_ `void SetSessionSearchParameters(FSessionSearchHandleEOSGS& SessionSearchHandle, TArray<FFindSessionsSearchFilter> Filters);`
- L238 _protected prototype_ `void SetSessionSearchSessionId(FSessionSearchHandleEOSGS& SessionSearchHandle, const FOnlineSessionId& SessionId);`
- L239 _protected prototype_ `void SetSessionSearchTargetId(FSessionSearchHandleEOSGS& SessionSearchHandle, const FAccountId& TargetAccountId);`
- L244 _protected prototype_ `void WriteCreateSessionModificationHandle(EOS_HSessionModification& SessionModificationHandle, const FCreateSession::Params& Params);` — Writes all values in the passed SessionSettings to the SessionModificationHandle
- L249 _protected prototype_ `void WriteUpdateSessionModificationHandle(EOS_HSessionModification& SessionModificationHandle, const FSessionSettingsUpdate& NewSettings);` — Writes only the new values for all updated session settings to the SessionModificationHandle
- L254 _protected prototype_ `void WriteSessionSearchHandle(FSessionSearchHandleEOSGS& SessionSearchHandle, const FFindSessions::Params& Params);` — Writes all relevant values set in the FindSessions parameters into the SessionSearchHandle
- L259 _protected prototype_ `TFuture<TDefaultErrorResult<FUpdateSessionImplEOSGS>> UpdateSessionImplEOSGS(FUpdateSessionImplEOSGS::Params&& Params);` — Internal method used by both CreateSession and UpdateSession to process a session update at the API level
- L264 _protected prototype_ `TFuture<TDefaultErrorResult<FUpdateSessionJoinabilityImpl>> UpdateSessionJoinabilityImpl(FUpdateSessionJoinabilityImpl::Params&& Params);` — Internal method called after UpdateSessionImpl to update joinability options for a session
- L269 _protected prototype_ `TFuture<TDefaultErrorResult<FSendSingleSessionInviteImpl>> SendSingleSessionInviteImpl(FSendSingleSessionInviteImpl::Params&& Params);` — Internal method called by SendSessionInvite for every user
- L271 _protected prototype_ `FOnlineSessionId CreateSessionId(const FString& SessionId) const;`
- L272 _protected prototype_ `FSessionInviteId CreateSessionInviteId(const FString& SessionInviteId) const;`
- L277 _protected prototype_ `TOnlineAsyncOpHandle<FBuildSessionFromDetailsHandle> BuildSessionFromDetailsHandle(FBuildSessionFromDetailsHandle::Params&& Params);` — Builds a session from an EOS Session Details Handle. Asynchronous due to the id resolution process
- L282 _protected prototype_ `TOnlineAsyncOpHandle<FBuildSessionFromDetailsHandle> BuildSessionFromInvite(const FAccountId& LocalAccountId, const FString& InInviteId);` — Builds a session from an invite id, calling BuildSessionFromDetailsHandle
- L287 _protected prototype_ `TOnlineAsyncOpHandle<FBuildSessionFromDetailsHandle> BuildSessionFromUIEvent(const FAccountId& LocalAccountId, const EOS_UI_EventId& UIEventId);` — Builds a session from a UI event id, calling BuildSessionFromDetailsHandle
- L291 _private prototype_ `virtual void AppendSessionToPacket(FNboSerializeToBuffer& Packet, const FSessionLAN& Session) override;` — FSessionsLAN
- L292 _private prototype_ `virtual void ReadSessionFromPacket(FNboSerializeFromBuffer& Packet, FSessionLAN& Session) override;`
- L294 _private prototype_ `FAccountId FindAccountId(const EOS_ProductUserId ProductUserId);`
- L297 _protected member_ `EOS_HSessions SessionsHandle = nullptr;`
- L299 _protected member_ `FEOSEventRegistrationPtr OnSessionInviteReceivedEventRegistration;`
- L300 _protected member_ `FEOSEventRegistrationPtr OnSessionInviteAcceptedEventRegistration;`
- L301 _protected member_ `FEOSEventRegistrationPtr OnJoinSessionAcceptedEventRegistration;`
- L303 _protected member_ `TMap<FAccountId, TSharedRef<FSessionSearchHandleEOSGS>> CurrentSessionSearchHandleEOSGSUserMap;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Online` (scope `UE`)
- L127 _typedef_ `typedef FUpdateSessionJoinabilityImpl::Params FUpdateSessionJoinabilityParams;` (scope `UE::Online`)
- L306 _namespace_ `namespace Meta` (scope `UE::Online`)

### `Plugins/Online/OnlineServicesEOSGS/Source/Public/Online/SessionsEOSGSTypes.h` (Public)


#### enum `UE::Online::ESessionAttributeConversionType`  
`enum class ESessionAttributeConversionType`  
_L31-35_
- L33 _public enumerator_ `ToService`
- L34 _public enumerator_ `FromService`

#### class `UE::Online::FSessionAttributeConverter`  
`template <ESessionAttributeConversionType> class FSessionAttributeConverter`  
_L38-41_
- L47 _public prototype_ `FSessionAttributeConverter(const FSchemaAttributeId& Key, const FSchemaVariant& Value);`
- L49 _public prototype_ `FSessionAttributeConverter(const TPair<FSchemaAttributeId, FSchemaVariant>& InData);`
- L51 _public function_ `const EOS_Sessions_AttributeData& GetAttributeData() const`
- L54 _private member_ `FTCHARToUTF8 KeyConverterStorage;`
- L55 _private member_ `TOptional<FTCHARToUTF8> ValueConverterStorage;` — TOptional because we'll only use it if the FSessionVariant type is FString
- L56 _private member_ `EOS_Sessions_AttributeData AttributeData;`
- L63 _public prototype_ `FSessionAttributeConverter(const EOS_Sessions_AttributeData& InData);`
- L65 _public function_ `const TPair<FSchemaAttributeId, FSchemaVariant>& GetAttributeData() const`
- L68 _private member_ `TPair<FSchemaAttributeId, FSchemaVariant> AttributeData;`

#### class `UE::Online::FSessionAttributeConverter`  
`template<> class FSessionAttributeConverter<ESessionAttributeConversionType::ToService>`  
_L44-57_
- L47 _public prototype_ `FSessionAttributeConverter(const FSchemaAttributeId& Key, const FSchemaVariant& Value);`
- L49 _public prototype_ `FSessionAttributeConverter(const TPair<FSchemaAttributeId, FSchemaVariant>& InData);`
- L51 _public function_ `const EOS_Sessions_AttributeData& GetAttributeData() const`
- L54 _private member_ `FTCHARToUTF8 KeyConverterStorage;`
- L55 _private member_ `TOptional<FTCHARToUTF8> ValueConverterStorage;` — TOptional because we'll only use it if the FSessionVariant type is FString
- L56 _private member_ `EOS_Sessions_AttributeData AttributeData;`
- L63 _public prototype_ `FSessionAttributeConverter(const EOS_Sessions_AttributeData& InData);`
- L65 _public function_ `const TPair<FSchemaAttributeId, FSchemaVariant>& GetAttributeData() const`
- L68 _private member_ `TPair<FSchemaAttributeId, FSchemaVariant> AttributeData;`

#### class `UE::Online::FSessionAttributeConverter`  
`template<> class FSessionAttributeConverter<ESessionAttributeConversionType::FromService>`  
_L60-69_
- L47 _public prototype_ `FSessionAttributeConverter(const FSchemaAttributeId& Key, const FSchemaVariant& Value);`
- L49 _public prototype_ `FSessionAttributeConverter(const TPair<FSchemaAttributeId, FSchemaVariant>& InData);`
- L51 _public function_ `const EOS_Sessions_AttributeData& GetAttributeData() const`
- L54 _private member_ `FTCHARToUTF8 KeyConverterStorage;`
- L55 _private member_ `TOptional<FTCHARToUTF8> ValueConverterStorage;` — TOptional because we'll only use it if the FSessionVariant type is FString
- L56 _private member_ `EOS_Sessions_AttributeData AttributeData;`
- L63 _public prototype_ `FSessionAttributeConverter(const EOS_Sessions_AttributeData& InData);`
- L65 _public function_ `const TPair<FSchemaAttributeId, FSchemaVariant>& GetAttributeData() const`
- L68 _private member_ `TPair<FSchemaAttributeId, FSchemaVariant> AttributeData;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Online` (scope `UE`)
- L15 _variable_ `static FName EOSGS_ALLOW_NEW_MEMBERS_ATTRIBUTE_KEY = TEXT("EOS` (scope `UE::Online`)
- L16 _variable_ `static FName EOSGS_ANTI_CHEAT_PROTECTED_ATTRIBUTE_KEY = TEXT("EOS` (scope `UE::Online`)
- L17 _variable_ `static FName EOSGS_IS_DEDICATED_SERVER_SESSION_ATTRIBUTE_KEY = TEXT("EOS` (scope `UE::Online`)
- L18 _variable_ `static FName EOSGS_SCHEMA_NAME_ATTRIBUTE_KEY = TEXT("EOS` (scope `UE::Online`)
- L20 _variable_ `static FName EOSGS_BUCKET_ID_ATTRIBUTE_KEY = TEXT("EOS` (scope `UE::Online`)
- L21 _variable_ `static FName EOSGS_HOST_ADDRESS_ATTRIBUTE_KEY = TEXT("EOS` (scope `UE::Online`)
- L23 _prototype_ `EOS_EOnlineSessionPermissionLevel ToServiceType(const ESessionJoinPolicy& Value);` (scope `UE::Online`)
- L24 _prototype_ `ESessionJoinPolicy FromServiceType(const EOS_EOnlineSessionPermissionLevel& Value);` (scope `UE::Online`)
- L26 _prototype_ `EOS_ESessionAttributeAdvertisementType ToServiceType(const ESchemaAttributeVisibility& Value);` (scope `UE::Online`)
- L27 _prototype_ `ESchemaAttributeVisibility FromServiceType(const EOS_ESessionAttributeAdvertisementType& Value);` (scope `UE::Online`)
- L29 _prototype_ `EOS_EOnlineComparisonOp ToServiceType(const ESchemaAttributeComparisonOp& Value);` (scope `UE::Online`)

### `Plugins/Online/OnlineServicesEOSGS/Source/Public/Online/StatsEOSGS.h` (Public)


#### class `UE::Online::FStatsEOSGS`  
`class FStatsEOSGS : public FStatsCommon`  
_L22-42_
- inherits: `FStatsCommon`
- desc: Because the value type is int32 in EOS, stats types are converted to int32. So these are limitations: - String type of Stats is not supported; - double type of Stats is casted to int32, and precision is UE_ONLINE_STAT_EOS_DOUBLE_PRECISION. Out of range value will be clamped; - int64 type of Stats is casted to int32. Out of range value will be clamped;
- L25 _public typedef_ `using Super = FStatsCommon;`
- L27 _public prototype_ `FStatsEOSGS(FOnlineServicesEpicCommon& InOwningSubsystem);`
- L30 _public prototype_ `virtual void Initialize() override;` — TOnlineComponent
- L33 _public prototype_ `virtual TOnlineAsyncOpHandle<FUpdateStats> UpdateStats(FUpdateStats::Params&& Params) override;` — IStats
- L34 _public prototype_ `virtual TOnlineAsyncOpHandle<FQueryStats> QueryStats(FQueryStats::Params&& Params) override;`
- L35 _public prototype_ `virtual TOnlineAsyncOpHandle<FBatchQueryStats> BatchQueryStats(FBatchQueryStats::Params&& Params) override;`
- L38 _protected prototype_ `void ReadStatsFromEOSResult(const EOS_Stats_OnQueryStatsCompleteCallbackInfo* Data, const TArray<FString>& StatNames, TMap<FString, FStatValue>& OutStats);`
- L40 _protected member_ `EOS_HStats StatsHandle = nullptr;`
- L41 _protected member_ `TArray<FUserStats> BatchQueriedUsersStats;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Online` (scope `UE`)

### `Plugins/Online/OnlineServicesEOSGS/Source/Public/Online/TitleFileEOSGS.h` (Public)


#### struct `UE::Online::FTitleFileEOSGSConfig`  
`struct FTitleFileEOSGSConfig`  
_L16-20_
- L18 _public member_ `FString SearchTag;`
- L19 _public member_ `int32 ReadChunkLengthBytes = 4096;`

#### class `UE::Online::FTitleFileEOSGS`  
`class FTitleFileEOSGS : public FTitleFileCommon`  
_L31-58_
- inherits: `FTitleFileCommon`
- L34 _public typedef_ `using Super = FTitleFileCommon;`
- L36 _public prototype_ `FTitleFileEOSGS(FOnlineServicesEpicCommon& InOwningSubsystem);`
- L37 _public prototype_ `virtual ~FTitleFileEOSGS() = default;`
- L40 _public prototype_ `virtual void Initialize() override;` — IOnlineComponent
- L41 _public prototype_ `virtual void UpdateConfig() override;`
- L44 _public prototype_ `virtual TOnlineAsyncOpHandle<FTitleFileEnumerateFiles> EnumerateFiles(FTitleFileEnumerateFiles::Params&& Params) override;` — ITitleFile
- L45 _public prototype_ `virtual TOnlineResult<FTitleFileGetEnumeratedFiles> GetEnumeratedFiles(FTitleFileGetEnumeratedFiles::Params&& Params) override;`
- L46 _public prototype_ `virtual TOnlineAsyncOpHandle<FTitleFileReadFile> ReadFile(FTitleFileReadFile::Params&& Params) override;`
- L49 _protected member_ `EOS_HTitleStorage TitleStorageHandle = nullptr;`
- L51 _protected member_ `FTitleFileEOSGSConfig Config;`
- L53 _protected member_ `TOptional<TArray<FString>> EnumeratedFiles;`
- L55 _protected prototype_ `static EOS_TitleStorage_EReadResult EOS_CALL OnReadFileDataStatic(const EOS_TitleStorage_ReadFileDataCallbackInfo* Data);`
- L56 _protected prototype_ `static void EOS_CALL OnFileTransferProgressStatic(const EOS_TitleStorage_FileTransferProgressCallbackInfo* Data);`
- L57 _protected prototype_ `static void EOS_CALL OnReadFileCompleteStatic(const EOS_TitleStorage_ReadFileCallbackInfo* Data);`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Online` (scope `UE`)
- L22 _namespace_ `namespace Meta` (scope `UE::Online`)

### `Plugins/Online/OnlineServicesEOSGS/Source/Public/Online/UserFileEOSGS.h` (Public)


#### struct `UE::Online::FUserFileEOSGSConfig`  
`struct FUserFileEOSGSConfig`  
_L16-19_
- L18 _public member_ `int32 ChunkLengthBytes = 4096;`

#### class `UE::Online::FUserFileEOSGS`  
`class FUserFileEOSGS : public FUserFileCommon`  
_L29-63_
- inherits: `FUserFileCommon`
- L32 _public typedef_ `using Super = FUserFileCommon;`
- L34 _public prototype_ `FUserFileEOSGS(FOnlineServicesEpicCommon& InOwningSubsystem);`
- L35 _public prototype_ `virtual ~FUserFileEOSGS() = default;`
- L38 _public prototype_ `virtual void Initialize() override;` — IOnlineComponent
- L39 _public prototype_ `virtual void UpdateConfig() override;`
- L42 _public prototype_ `virtual TOnlineAsyncOpHandle<FUserFileEnumerateFiles> EnumerateFiles(FUserFileEnumerateFiles::Params&& Params) override;` — IUserFile
- L43 _public prototype_ `virtual TOnlineResult<FUserFileGetEnumeratedFiles> GetEnumeratedFiles(FUserFileGetEnumeratedFiles::Params&& Params) override;`
- L44 _public prototype_ `virtual TOnlineAsyncOpHandle<FUserFileReadFile> ReadFile(FUserFileReadFile::Params&& Params) override;`
- L45 _public prototype_ `virtual TOnlineAsyncOpHandle<FUserFileWriteFile> WriteFile(FUserFileWriteFile::Params&& Params) override;`
- L46 _public prototype_ `virtual TOnlineAsyncOpHandle<FUserFileCopyFile> CopyFile(FUserFileCopyFile::Params&& Params) override;`
- L47 _public prototype_ `virtual TOnlineAsyncOpHandle<FUserFileDeleteFile> DeleteFile(FUserFileDeleteFile::Params&& Params) override;`
- L50 _protected member_ `EOS_HPlayerDataStorage PlayerDataStorageHandle = nullptr;`
- L52 _protected member_ `FUserFileEOSGSConfig Config;`
- L54 _protected member_ `TMap<FAccountId, TArray<FString>> UserToFiles;`
- L56 _protected prototype_ `static EOS_PlayerDataStorage_EReadResult EOS_CALL OnReadFileDataStatic(const EOS_PlayerDataStorage_ReadFileDataCallbackInfo* Data);`
- L57 _protected prototype_ `static void EOS_CALL OnReadFileCompleteStatic(const EOS_PlayerDataStorage_ReadFileCallbackInfo* Data);`
- L59 _protected prototype_ `static EOS_PlayerDataStorage_EWriteResult EOS_CALL OnWriteFileDataStatic(const EOS_PlayerDataStorage_WriteFileDataCallbackInfo* Data, void* OutDataBuffer, uint32_t* OutDataWritten);`
- L60 _protected prototype_ `static void EOS_CALL OnWriteFileCompleteStatic(const EOS_PlayerDataStorage_WriteFileCallbackInfo* Data);`
- L62 _protected prototype_ `static void EOS_CALL OnFileTransferProgressStatic(const EOS_PlayerDataStorage_FileTransferProgressCallbackInfo* Data);`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Online` (scope `UE`)
- L21 _namespace_ `namespace Meta` (scope `UE::Online`)
