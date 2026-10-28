# Programs / OSSTestsCore

- module root: `Source/Programs/Online/OSSTestsCore`
- headers: 82; symbols: 1298
- symbol kinds: class=11, enum=57, enumerator=268, function=310, macro=8, member=459, prototype=99, struct=83, typedef=2, variable=1
- PrivateDependencyModuleNames: ApplicationCore, Core, CoreUObject, EngineSettings, OnlineSubsystem, OnlineSubsystemNull, Projects

### `Source/Programs/Online/OSSTestsCore/Helpers/Achievements/AchievementsGetCachedAchievementDescriptionHelper.h` (Other)


#### struct `FAchievementsGetCachedAchievementDescriptionStep`  
`struct FAchievementsGetCachedAchievementDescriptionStep : public FTestPipeline::FStep`  
_L11-44_
- inherits: `FTestPipeline::FStep`
- L13 _public function_ `FAchievementsGetCachedAchievementDescriptionStep(const FString& InAchievementId, TFunction<void(FOnlineAchievementDesc*)>&& InStateSaver) : AchievementId(InAchievementId) , StateSaver(MoveTemp(InStateSaver))`
- L18 _public function_ `FAchievementsGetCachedAchievementDescriptionStep(const FString& InAchievementId) : AchievementId(InAchievementId) , StateSaver([](FOnlineAchievementDesc*) {})`
- L20 _public function_ `, StateSaver([](FOnlineAchievementDesc*) {})`
- L23 _public prototype_ `virtual ~FAchievementsGetCachedAchievementDescriptionStep() = default;`
- L25 _public function_ `virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override`
- L39 _protected member_ `IOnlineAchievementsPtr OnlineAchievementsPtr = nullptr;`
- L40 _protected member_ `FString AchievementId = FString(TEXT(""));`
- L41 _protected member_ `FOnlineAchievementDesc OutAchievementDesc;`
- L42 _protected member_ `TFunction<void(FOnlineAchievementDesc*)> StateSaver;`

### `Source/Programs/Online/OSSTestsCore/Helpers/Achievements/AchievementsGetCachedAchievementHelper.h` (Other)


#### struct `FAchievementsGetCachedAchievementStep`  
`struct FAchievementsGetCachedAchievementStep : public FTestPipeline::FStep`  
_L11-47_
- inherits: `FTestPipeline::FStep`
- L13 _public function_ `FAchievementsGetCachedAchievementStep(FUniqueNetIdPtr* InPlayerId, const FString& InAchievementId, TFunction<void(FOnlineAchievement*)>&& InStateSaver) : PlayerId(InPlayerId) , AchievementId(InAchievementId) , StateSaver(MoveTemp(InStateSaver))`
- L19 _public function_ `FAchievementsGetCachedAchievementStep(FUniqueNetIdPtr* InPlayerId, const FString& InAchievementId) : PlayerId(InPlayerId) , AchievementId(InAchievementId) , StateSaver([](FOnlineAchievement*) {})`
- L22 _public function_ `, StateSaver([](FOnlineAchievement*) {})`
- L25 _public prototype_ `virtual ~FAchievementsGetCachedAchievementStep() = default;`
- L27 _public function_ `virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override`
- L41 _protected member_ `IOnlineAchievementsPtr OnlineAchievementsPtr = nullptr;`
- L42 _protected member_ `FUniqueNetIdPtr* PlayerId = nullptr;`
- L43 _protected member_ `FString AchievementId = FString(TEXT(""));`
- L44 _protected member_ `FOnlineAchievement OutAchievement;`
- L45 _protected member_ `TFunction<void(FOnlineAchievement*)> StateSaver;`

### `Source/Programs/Online/OSSTestsCore/Helpers/Achievements/AchievementsGetCachedAchievementsHelper.h` (Other)


#### struct `FAchievementsGetCachedAchievementsStep`  
`struct FAchievementsGetCachedAchievementsStep : public FTestPipeline::FStep`  
_L11-44_
- inherits: `FTestPipeline::FStep`
- L13 _public function_ `FAchievementsGetCachedAchievementsStep(FUniqueNetIdPtr* InPlayerId, TFunction<void(TArray<FOnlineAchievement>*)>&& InStateSaver) : PlayerId(InPlayerId) , StateSaver(MoveTemp(InStateSaver))`
- L18 _public function_ `FAchievementsGetCachedAchievementsStep(FUniqueNetIdPtr* InPlayerId) : PlayerId(InPlayerId) , StateSaver([](TArray<FOnlineAchievement>*) {})`
- L20 _public function_ `, StateSaver([](TArray<FOnlineAchievement>*) {})`
- L23 _public prototype_ `virtual ~FAchievementsGetCachedAchievementsStep() = default;`
- L25 _public function_ `virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override`
- L39 _protected member_ `IOnlineAchievementsPtr OnlineAchievementsPtr = nullptr;`
- L40 _protected member_ `FUniqueNetIdPtr* PlayerId = nullptr;`
- L41 _protected member_ `TArray<FOnlineAchievement> OutAchievements;`
- L42 _protected member_ `TFunction<void(TArray<FOnlineAchievement>*)> StateSaver;`

### `Source/Programs/Online/OSSTestsCore/Helpers/Achievements/AchievementsQueryAchievementDescriptionsHelper.h` (Other)


#### struct `FAchievementsQueryAchievementDescriptionsStep`  
`struct FAchievementsQueryAchievementDescriptionsStep : public FTestPipeline::FStep`  
_L10-65_
- inherits: `FTestPipeline::FStep`
- L12 _public function_ `FAchievementsQueryAchievementDescriptionsStep(FUniqueNetIdPtr* InPlayerId) : PlayerId(InPlayerId)`
- L16 _public prototype_ `virtual ~FAchievementsQueryAchievementDescriptionsStep() = default;`
- L18 _public member_ `enum class EState { Init, QueryAchievementDescriptionsCall, QueryAchievementDescriptionsCalled, Done } State = EState::Init;`
- L20 _public member_ `FOnQueryAchievementsCompleteDelegate OnQueryAchievementsCompleteDelegate = FOnQueryAchievementsCompleteDelegate::CreateLambda([this](const FUniqueNetId& QueryAchievementDescriptionsPlayerId, const bool bQueryAchievementDescriptionsWasSuccessful) { CHECK(State == EState::QueryAchievementDescriptionsCalled); CHECK(bQueryAchievementDescriptionsWasSuccessful); CHECK(QueryAchievementDescriptionsPlayerId == *PlayerId->Get()); State = EState::Done; });`
- L21 _public function_ ``
- L29 _public function_ `virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override`
- L63 _protected member_ `IOnlineAchievementsPtr OnlineAchievementsPtr = nullptr;`
- L64 _protected member_ `FUniqueNetIdPtr* PlayerId = nullptr;`

#### enum `FAchievementsQueryAchievementDescriptionsStep::EState`  
`enum class EState`  
_L18-18_
- L18 _public enumerator_ `enum class EState { Init, QueryAchievementDescriptionsCall, QueryAchievementDescriptionsCalled, Done } State = EState::Init; FOnQueryAchievementsCompleteDelegate OnQueryAchievementsCompleteDelegate = FOnQueryAchievementsCompleteDelegate::CreateLambda([this](const FUniqueNetId& QueryAchievementDescriptionsPlayerId, const bool bQueryAchievementDescriptionsWasSuccessful) { CHECK(State == EState::QueryAchievementDescriptionsCalled); CHECK(bQueryAchievementDescriptionsWasSuccessful); CHECK(QueryAchievementDescriptionsPlayerId == *PlayerId->Get());`
- L18 _public enumerator_ `enum class EState { Init, QueryAchievementDescriptionsCall, QueryAchievementDescriptionsCalled, Done } State = EState::Init; FOnQueryAchievementsCompleteDelegate OnQueryAchievementsCompleteDelegate = FOnQueryAchievementsCompleteDelegate::CreateLambda([this](const FUniqueNetId& QueryAchievementDescriptionsPlayerId, const bool bQueryAchievementDescriptionsWasSuccessful) { CHECK(State == EState::QueryAchievementDescriptionsCalled); CHECK(bQueryAchievementDescriptionsWasSuccessful); CHECK(QueryAchievementDescriptionsPlayerId == *PlayerId->Get());`
- L18 _public enumerator_ `enum class EState { Init, QueryAchievementDescriptionsCall, QueryAchievementDescriptionsCalled, Done } State = EState::Init; FOnQueryAchievementsCompleteDelegate OnQueryAchievementsCompleteDelegate = FOnQueryAchievementsCompleteDelegate::CreateLambda([this](const FUniqueNetId& QueryAchievementDescriptionsPlayerId, const bool bQueryAchievementDescriptionsWasSuccessful) { CHECK(State == EState::QueryAchievementDescriptionsCalled); CHECK(bQueryAchievementDescriptionsWasSuccessful); CHECK(QueryAchievementDescriptionsPlayerId == *PlayerId->Get());`
- L18 _public enumerator_ `enum class EState { Init, QueryAchievementDescriptionsCall, QueryAchievementDescriptionsCalled, Done } State = EState::Init; FOnQueryAchievementsCompleteDelegate OnQueryAchievementsCompleteDelegate = FOnQueryAchievementsCompleteDelegate::CreateLambda([this](const FUniqueNetId& QueryAchievementDescriptionsPlayerId, const bool bQueryAchievementDescriptionsWasSuccessful) { CHECK(State == EState::QueryAchievementDescriptionsCalled); CHECK(bQueryAchievementDescriptionsWasSuccessful); CHECK(QueryAchievementDescriptionsPlayerId == *PlayerId->Get());`

### `Source/Programs/Online/OSSTestsCore/Helpers/Achievements/AchievementsQueryAchievementsHelper.h` (Other)


#### struct `FAchievementsQueryAchievementsStep`  
`struct FAchievementsQueryAchievementsStep : public FTestPipeline::FStep`  
_L10-66_
- inherits: `FTestPipeline::FStep`
- L12 _public function_ `FAchievementsQueryAchievementsStep(FUniqueNetIdPtr* InPlayerId) : PlayerId(InPlayerId)`
- L16 _public prototype_ `virtual ~FAchievementsQueryAchievementsStep() = default;`
- L18 _public member_ `enum class EState { Init, QueryAchievementsCall, QueryAchievementsCalled, Done } State = EState::Init;`
- L20 _public member_ `FOnQueryAchievementsCompleteDelegate OnQueryAchievementsCompleteDelegate = FOnQueryAchievementsCompleteDelegate::CreateLambda([this](const FUniqueNetId& SecondQueryAchievementsPlayerId, const bool bSecondQueryAchievementsWasSuccessful) { CHECK(State == EState::QueryAchievementsCalled); CHECK(bSecondQueryAchievementsWasSuccessful); CHECK(SecondQueryAchievementsPlayerId == *PlayerId->Get()); State = EState::Done; });`
- L21 _public function_ ``
- L29 _public function_ `virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override`
- L64 _protected member_ `IOnlineAchievementsPtr OnlineAchievementsPtr = nullptr;`
- L65 _protected member_ `FUniqueNetIdPtr* PlayerId = nullptr;`

#### enum `FAchievementsQueryAchievementsStep::EState`  
`enum class EState`  
_L18-18_
- L18 _public enumerator_ `enum class EState { Init, QueryAchievementsCall, QueryAchievementsCalled, Done } State = EState::Init; FOnQueryAchievementsCompleteDelegate OnQueryAchievementsCompleteDelegate = FOnQueryAchievementsCompleteDelegate::CreateLambda([this](const FUniqueNetId& SecondQueryAchievementsPlayerId, const bool bSecondQueryAchievementsWasSuccessful) { CHECK(State == EState::QueryAchievementsCalled); CHECK(bSecondQueryAchievementsWasSuccessful); CHECK(SecondQueryAchievementsPlayerId == *PlayerId->Get());`
- L18 _public enumerator_ `enum class EState { Init, QueryAchievementsCall, QueryAchievementsCalled, Done } State = EState::Init; FOnQueryAchievementsCompleteDelegate OnQueryAchievementsCompleteDelegate = FOnQueryAchievementsCompleteDelegate::CreateLambda([this](const FUniqueNetId& SecondQueryAchievementsPlayerId, const bool bSecondQueryAchievementsWasSuccessful) { CHECK(State == EState::QueryAchievementsCalled); CHECK(bSecondQueryAchievementsWasSuccessful); CHECK(SecondQueryAchievementsPlayerId == *PlayerId->Get());`
- L18 _public enumerator_ `enum class EState { Init, QueryAchievementsCall, QueryAchievementsCalled, Done } State = EState::Init; FOnQueryAchievementsCompleteDelegate OnQueryAchievementsCompleteDelegate = FOnQueryAchievementsCompleteDelegate::CreateLambda([this](const FUniqueNetId& SecondQueryAchievementsPlayerId, const bool bSecondQueryAchievementsWasSuccessful) { CHECK(State == EState::QueryAchievementsCalled); CHECK(bSecondQueryAchievementsWasSuccessful); CHECK(SecondQueryAchievementsPlayerId == *PlayerId->Get());`
- L18 _public enumerator_ `enum class EState { Init, QueryAchievementsCall, QueryAchievementsCalled, Done } State = EState::Init; FOnQueryAchievementsCompleteDelegate OnQueryAchievementsCompleteDelegate = FOnQueryAchievementsCompleteDelegate::CreateLambda([this](const FUniqueNetId& SecondQueryAchievementsPlayerId, const bool bSecondQueryAchievementsWasSuccessful) { CHECK(State == EState::QueryAchievementsCalled); CHECK(bSecondQueryAchievementsWasSuccessful); CHECK(SecondQueryAchievementsPlayerId == *PlayerId->Get());`

### `Source/Programs/Online/OSSTestsCore/Helpers/Achievements/AchievementsWriteAchievementsHelper.h` (Other)


#### struct `FAchievementsWriteAchievementsStep`  
`struct FAchievementsWriteAchievementsStep : public FTestPipeline::FStep`  
_L10-68_
- inherits: `FTestPipeline::FStep`
- L12 _public function_ `FAchievementsWriteAchievementsStep(FUniqueNetIdPtr* InPlayerId, FOnlineAchievementsWriteRef& InWriteObject) : PlayerId(InPlayerId) , WriteObject(InWriteObject)`
- L17 _public prototype_ `virtual ~FAchievementsWriteAchievementsStep() = default;`
- L19 _public member_ `enum class EState { Init, WriteAchievementsCall, WriteAchievementsCalled, Done } State = EState::Init;`
- L21 _public member_ `FOnAchievementsWrittenDelegate OnOnAchievementsWrittenDelegate = FOnAchievementsWrittenDelegate::CreateLambda([this](const FUniqueNetId& WriteAchievementsPlayerId, bool bWriteAchievementsWasSuccessful) { CHECK(State == EState::WriteAchievementsCalled); CHECK(bWriteAchievementsWasSuccessful); CHECK(WriteAchievementsPlayerId == *PlayerId->Get()); State = EState::Done; });`
- L22 _public function_ ``
- L30 _public function_ `virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override`
- L65 _protected member_ `IOnlineAchievementsPtr OnlineAchievementsPtr = nullptr;`
- L66 _protected member_ `FUniqueNetIdPtr* PlayerId = nullptr;`
- L67 _protected member_ `FOnlineAchievementsWriteRef& WriteObject;`

#### enum `FAchievementsWriteAchievementsStep::EState`  
`enum class EState`  
_L19-19_
- L19 _public enumerator_ `enum class EState { Init, WriteAchievementsCall, WriteAchievementsCalled, Done } State = EState::Init; FOnAchievementsWrittenDelegate OnOnAchievementsWrittenDelegate = FOnAchievementsWrittenDelegate::CreateLambda([this](const FUniqueNetId& WriteAchievementsPlayerId, bool bWriteAchievementsWasSuccessful) { CHECK(State == EState::WriteAchievementsCalled); CHECK(bWriteAchievementsWasSuccessful); CHECK(WriteAchievementsPlayerId == *PlayerId->Get());`
- L19 _public enumerator_ `enum class EState { Init, WriteAchievementsCall, WriteAchievementsCalled, Done } State = EState::Init; FOnAchievementsWrittenDelegate OnOnAchievementsWrittenDelegate = FOnAchievementsWrittenDelegate::CreateLambda([this](const FUniqueNetId& WriteAchievementsPlayerId, bool bWriteAchievementsWasSuccessful) { CHECK(State == EState::WriteAchievementsCalled); CHECK(bWriteAchievementsWasSuccessful); CHECK(WriteAchievementsPlayerId == *PlayerId->Get());`
- L19 _public enumerator_ `enum class EState { Init, WriteAchievementsCall, WriteAchievementsCalled, Done } State = EState::Init; FOnAchievementsWrittenDelegate OnOnAchievementsWrittenDelegate = FOnAchievementsWrittenDelegate::CreateLambda([this](const FUniqueNetId& WriteAchievementsPlayerId, bool bWriteAchievementsWasSuccessful) { CHECK(State == EState::WriteAchievementsCalled); CHECK(bWriteAchievementsWasSuccessful); CHECK(WriteAchievementsPlayerId == *PlayerId->Get());`
- L19 _public enumerator_ `enum class EState { Init, WriteAchievementsCall, WriteAchievementsCalled, Done } State = EState::Init; FOnAchievementsWrittenDelegate OnOnAchievementsWrittenDelegate = FOnAchievementsWrittenDelegate::CreateLambda([this](const FUniqueNetId& WriteAchievementsPlayerId, bool bWriteAchievementsWasSuccessful) { CHECK(State == EState::WriteAchievementsCalled); CHECK(bWriteAchievementsWasSuccessful); CHECK(WriteAchievementsPlayerId == *PlayerId->Get());`

### `Source/Programs/Online/OSSTestsCore/Helpers/AutoRestoreConfig.h` (Other)


#### class `TAutoRestoreGConfig`  
`template<typename T> class TAutoRestoreGConfig`  
_L6-75_
- L9 _public function_ `TAutoRestoreGConfig(const TCHAR* InSectionName, const TCHAR* InKeyName, const FString& InFileName) : SectionName(InSectionName), KeyName(InKeyName), FileName(InFileName)`
- L14 _public function_ `~TAutoRestoreGConfig()`
- L19 _public function_ `void Reset()`
- L38 _public function_ `bool IsSet()`
- L43 _public function_ `void SetValue(const T& NewValue)`
- L70 _private member_ `TOptional<T> InitialValue;`
- L71 _private member_ `bool bRetrievedInitialValue = false;`
- L72 _private member_ `const TCHAR* SectionName;`
- L73 _private member_ `const TCHAR* KeyName;`
- L74 _private member_ `const FString& FileName;`

### `Source/Programs/Online/OSSTestsCore/Helpers/CommonHelper.h` (Other)


#### struct `FInnerStepArrayBuilder`  
`template<typename TBaseInnerStep> struct FInnerStepArrayBuilder`  
_L6-19_
- L8 _public function_ `FInnerStepArrayBuilder()`
- L12 _public function_ `template<typename T, typename... TArguments> FInnerStepArrayBuilder&& EmplaceInnerStep(TArguments&&... Args)`
- L18 _public member_ `TArray<TUniquePtr<TBaseInnerStep>> Steps;`

### `Source/Programs/Online/OSSTestsCore/Helpers/Friends/FriendsAcceptInviteHelper.h` (Other)


#### struct `FFriendsAcceptInviteStep`  
`struct FFriendsAcceptInviteStep : public FTestPipeline::FStep`  
_L10-73_
- inherits: `FTestPipeline::FStep`
- L12 _public function_ `FFriendsAcceptInviteStep(int32 InUserNum, FUniqueNetIdPtr* InLocalUserId, FString& InListName) : UserNum(InUserNum) , UserId(InLocalUserId) , ListName(InListName)`
- L18 _public prototype_ `virtual ~FFriendsAcceptInviteStep() = default;`
- L20 _public member_ `enum class EState { Init, AcceptInviteCalled, ClearDelegates, Done } State = EState::Init;`
- L22 _public member_ `FOnAcceptInviteComplete AcceptInvite = FOnAcceptInviteComplete::CreateLambda([this](int32 InUserNum, bool bInWasSuccessful, const FUniqueNetId& InUserId, const FString& InListName, const FString& InErrorStr) { CHECK(State == EState::AcceptInviteCalled); CHECK(InUserNum == UserNum); CHECK(bInWasSuccessful); CHECK(InUserId == *UserId->Get()); CHECK(InListName == ListName); CHECK(InErrorStr.Len() == 0); State = EState::ClearDelegates; });`
- L23 _public function_ ``
- L34 _public function_ `virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override`
- L69 _protected member_ `int32 UserNum;`
- L70 _protected member_ `FUniqueNetIdPtr* UserId = nullptr;`
- L71 _protected member_ `FString ListName;`
- L72 _protected member_ `IOnlineFriendsPtr OnlineFriendsPtr = nullptr;`

#### enum `FFriendsAcceptInviteStep::EState`  
`enum class EState`  
_L20-20_
- L20 _public enumerator_ `enum class EState { Init, AcceptInviteCalled, ClearDelegates, Done } State = EState::Init; FOnAcceptInviteComplete AcceptInvite = FOnAcceptInviteComplete::CreateLambda([this](int32 InUserNum, bool bInWasSuccessful, const FUniqueNetId& InUserId, const FString& InListName, const FString& InErrorStr) { CHECK(State == EState::AcceptInviteCalled); CHECK(InUserNum == UserNum); CHECK(bInWasSuccessful); CHECK(InUserId == *UserId->Get());`
- L20 _public enumerator_ `enum class EState { Init, AcceptInviteCalled, ClearDelegates, Done } State = EState::Init; FOnAcceptInviteComplete AcceptInvite = FOnAcceptInviteComplete::CreateLambda([this](int32 InUserNum, bool bInWasSuccessful, const FUniqueNetId& InUserId, const FString& InListName, const FString& InErrorStr) { CHECK(State == EState::AcceptInviteCalled); CHECK(InUserNum == UserNum); CHECK(bInWasSuccessful); CHECK(InUserId == *UserId->Get());`
- L20 _public enumerator_ `enum class EState { Init, AcceptInviteCalled, ClearDelegates, Done } State = EState::Init; FOnAcceptInviteComplete AcceptInvite = FOnAcceptInviteComplete::CreateLambda([this](int32 InUserNum, bool bInWasSuccessful, const FUniqueNetId& InUserId, const FString& InListName, const FString& InErrorStr) { CHECK(State == EState::AcceptInviteCalled); CHECK(InUserNum == UserNum); CHECK(bInWasSuccessful); CHECK(InUserId == *UserId->Get());`
- L20 _public enumerator_ `enum class EState { Init, AcceptInviteCalled, ClearDelegates, Done } State = EState::Init; FOnAcceptInviteComplete AcceptInvite = FOnAcceptInviteComplete::CreateLambda([this](int32 InUserNum, bool bInWasSuccessful, const FUniqueNetId& InUserId, const FString& InListName, const FString& InErrorStr) { CHECK(State == EState::AcceptInviteCalled); CHECK(InUserNum == UserNum); CHECK(bInWasSuccessful); CHECK(InUserId == *UserId->Get());`

### `Source/Programs/Online/OSSTestsCore/Helpers/Friends/FriendsBlockPlayerHelper.h` (Other)


#### struct `FFriendsBlockPlayerStep`  
`struct FFriendsBlockPlayerStep : public FTestPipeline::FStep`  
_L10-79_
- inherits: `FTestPipeline::FStep`
- L12 _public function_ `FFriendsBlockPlayerStep(int32 InLocalUserNum, FUniqueNetIdPtr* InLocalUserId) : UserNum(InLocalUserNum) , UserId(InLocalUserId)`
- L17 _public prototype_ `virtual ~FFriendsBlockPlayerStep() = default;`
- L19 _public member_ `enum class EState { Init, BlockPlayerCall, BlockPlayerCalled, ClearDelegates, Done } State = EState::Init;`
- L21 _public member_ `FOnBlockedPlayerCompleteDelegate BlockPlayer = FOnBlockedPlayerCompleteDelegate::CreateLambda([this](int32 InUserNum, bool bInWasSuccessful, const FUniqueNetId& InUserId, const FString& InListName, const FString& InErrorStr) { CHECK(State == EState::BlockPlayerCalled); CHECK(InUserNum == UserNum); CHECK(bInWasSuccessful); CHECK(InUserId == *UserId->Get()); CHECK(InListName == TEXT("BlockedPlayers")); CHECK(InErrorStr.Len() == 0); State = EState::ClearDelegates; });`
- L22 _public function_ ``
- L33 _public function_ `virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override`
- L75 _protected member_ `int32 UserNum;`
- L76 _protected member_ `FUniqueNetIdPtr* UserId = nullptr;`
- L77 _protected member_ `IOnlineFriendsPtr OnlineFriendsPtr = nullptr;`
- L78 _protected member_ `FDelegateHandle OnBlockedPlayerCompleteDelegateHandle;`

#### enum `FFriendsBlockPlayerStep::EState`  
`enum class EState`  
_L19-19_
- L19 _public enumerator_ `enum class EState { Init, BlockPlayerCall, BlockPlayerCalled, ClearDelegates, Done } State = EState::Init; FOnBlockedPlayerCompleteDelegate BlockPlayer = FOnBlockedPlayerCompleteDelegate::CreateLambda([this](int32 InUserNum, bool bInWasSuccessful, const FUniqueNetId& InUserId, const FString& InListName, const FString& InErrorStr) { CHECK(State == EState::BlockPlayerCalled); CHECK(InUserNum == UserNum); CHECK(bInWasSuccessful); CHECK(InUserId == *UserId->Get());`
- L19 _public enumerator_ `enum class EState { Init, BlockPlayerCall, BlockPlayerCalled, ClearDelegates, Done } State = EState::Init; FOnBlockedPlayerCompleteDelegate BlockPlayer = FOnBlockedPlayerCompleteDelegate::CreateLambda([this](int32 InUserNum, bool bInWasSuccessful, const FUniqueNetId& InUserId, const FString& InListName, const FString& InErrorStr) { CHECK(State == EState::BlockPlayerCalled); CHECK(InUserNum == UserNum); CHECK(bInWasSuccessful); CHECK(InUserId == *UserId->Get());`
- L19 _public enumerator_ `enum class EState { Init, BlockPlayerCall, BlockPlayerCalled, ClearDelegates, Done } State = EState::Init; FOnBlockedPlayerCompleteDelegate BlockPlayer = FOnBlockedPlayerCompleteDelegate::CreateLambda([this](int32 InUserNum, bool bInWasSuccessful, const FUniqueNetId& InUserId, const FString& InListName, const FString& InErrorStr) { CHECK(State == EState::BlockPlayerCalled); CHECK(InUserNum == UserNum); CHECK(bInWasSuccessful); CHECK(InUserId == *UserId->Get());`
- L19 _public enumerator_ `enum class EState { Init, BlockPlayerCall, BlockPlayerCalled, ClearDelegates, Done } State = EState::Init; FOnBlockedPlayerCompleteDelegate BlockPlayer = FOnBlockedPlayerCompleteDelegate::CreateLambda([this](int32 InUserNum, bool bInWasSuccessful, const FUniqueNetId& InUserId, const FString& InListName, const FString& InErrorStr) { CHECK(State == EState::BlockPlayerCalled); CHECK(InUserNum == UserNum); CHECK(bInWasSuccessful); CHECK(InUserId == *UserId->Get());`
- L19 _public enumerator_ `enum class EState { Init, BlockPlayerCall, BlockPlayerCalled, ClearDelegates, Done } State = EState::Init; FOnBlockedPlayerCompleteDelegate BlockPlayer = FOnBlockedPlayerCompleteDelegate::CreateLambda([this](int32 InUserNum, bool bInWasSuccessful, const FUniqueNetId& InUserId, const FString& InListName, const FString& InErrorStr) { CHECK(State == EState::BlockPlayerCalled); CHECK(InUserNum == UserNum); CHECK(bInWasSuccessful); CHECK(InUserId == *UserId->Get());`

### `Source/Programs/Online/OSSTestsCore/Helpers/Friends/FriendsDeleteFriendAliasHelper.h` (Other)


#### struct `FFriendsDeleteFriendAliasStep`  
`struct FFriendsDeleteFriendAliasStep : public FTestPipeline::FStep`  
_L11-77_
- inherits: `FTestPipeline::FStep`
- L13 _public function_ `FFriendsDeleteFriendAliasStep(int32 InLocalUserNum, FUniqueNetIdPtr* InLocalUserId, FString& InLocalListName) : UserNum(InLocalUserNum) , UserId(InLocalUserId) , ListName(InLocalListName)`
- L19 _public prototype_ `virtual ~FFriendsDeleteFriendAliasStep() = default;`
- L21 _public member_ `enum class EState { Init, DeleteFriendAliasCall, DeleteFriendAliasCalled, ClearDelegates, Done } State = EState::Init;`
- L23 _public member_ `FOnDeleteFriendAliasComplete DeleteFriendAlias = FOnDeleteFriendAliasComplete::CreateLambda([this](int32 InUserNum, const FUniqueNetId& InUserId, const FString& InListName, const FOnlineError& InError) { CHECK(State == EState::DeleteFriendAliasCalled); CHECK(InUserNum == UserNum); CHECK(InUserId == *UserId->Get()); CHECK(InListName == ListName); CHECK(InError == FOnlineError::Success()); State = EState::ClearDelegates; });`
- L24 _public function_ ``
- L34 _public function_ `virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override`
- L72 _protected member_ `int32 UserNum;`
- L73 _protected member_ `FUniqueNetIdPtr* UserId = nullptr;`
- L74 _protected member_ `FString ListName;`
- L75 _protected member_ `TArray<FUniqueNetIdRef> Players;`
- L76 _protected member_ `IOnlineFriendsPtr OnlineFriendsPtr = nullptr;`

#### enum `FFriendsDeleteFriendAliasStep::EState`  
`enum class EState`  
_L21-21_
- L21 _public enumerator_ `enum class EState { Init, DeleteFriendAliasCall, DeleteFriendAliasCalled, ClearDelegates, Done } State = EState::Init; FOnDeleteFriendAliasComplete DeleteFriendAlias = FOnDeleteFriendAliasComplete::CreateLambda([this](int32 InUserNum, const FUniqueNetId& InUserId, const FString& InListName, const FOnlineError& InError) { CHECK(State == EState::DeleteFriendAliasCalled); CHECK(InUserNum == UserNum); CHECK(InUserId == *UserId->Get()); CHECK(InListName == ListName);`
- L21 _public enumerator_ `enum class EState { Init, DeleteFriendAliasCall, DeleteFriendAliasCalled, ClearDelegates, Done } State = EState::Init; FOnDeleteFriendAliasComplete DeleteFriendAlias = FOnDeleteFriendAliasComplete::CreateLambda([this](int32 InUserNum, const FUniqueNetId& InUserId, const FString& InListName, const FOnlineError& InError) { CHECK(State == EState::DeleteFriendAliasCalled); CHECK(InUserNum == UserNum); CHECK(InUserId == *UserId->Get()); CHECK(InListName == ListName);`
- L21 _public enumerator_ `enum class EState { Init, DeleteFriendAliasCall, DeleteFriendAliasCalled, ClearDelegates, Done } State = EState::Init; FOnDeleteFriendAliasComplete DeleteFriendAlias = FOnDeleteFriendAliasComplete::CreateLambda([this](int32 InUserNum, const FUniqueNetId& InUserId, const FString& InListName, const FOnlineError& InError) { CHECK(State == EState::DeleteFriendAliasCalled); CHECK(InUserNum == UserNum); CHECK(InUserId == *UserId->Get()); CHECK(InListName == ListName);`
- L21 _public enumerator_ `enum class EState { Init, DeleteFriendAliasCall, DeleteFriendAliasCalled, ClearDelegates, Done } State = EState::Init; FOnDeleteFriendAliasComplete DeleteFriendAlias = FOnDeleteFriendAliasComplete::CreateLambda([this](int32 InUserNum, const FUniqueNetId& InUserId, const FString& InListName, const FOnlineError& InError) { CHECK(State == EState::DeleteFriendAliasCalled); CHECK(InUserNum == UserNum); CHECK(InUserId == *UserId->Get()); CHECK(InListName == ListName);`
- L21 _public enumerator_ `enum class EState { Init, DeleteFriendAliasCall, DeleteFriendAliasCalled, ClearDelegates, Done } State = EState::Init; FOnDeleteFriendAliasComplete DeleteFriendAlias = FOnDeleteFriendAliasComplete::CreateLambda([this](int32 InUserNum, const FUniqueNetId& InUserId, const FString& InListName, const FOnlineError& InError) { CHECK(State == EState::DeleteFriendAliasCalled); CHECK(InUserNum == UserNum); CHECK(InUserId == *UserId->Get()); CHECK(InListName == ListName);`

### `Source/Programs/Online/OSSTestsCore/Helpers/Friends/FriendsDeleteFriendHelper.h` (Other)


#### struct `FFriendsDeleteFriendStep`  
`struct FFriendsDeleteFriendStep : public FTestPipeline::FStep`  
_L10-98_
- inherits: `FTestPipeline::FStep`
- L12 _public function_ `FFriendsDeleteFriendStep(int32 InLocalUserNum, FUniqueNetIdPtr* InLocalUserId, FString& InLocalListName) : UserNum(InLocalUserNum) , UserId(InLocalUserId) , ListName(InLocalListName)`
- L18 _public function_ `virtual ~FFriendsDeleteFriendStep()`
- L30 _public member_ `enum class EState { Init, DeleteFriendCall, DeleteFriendCalled, ClearDelegates, Done } State = EState::Init;`
- L32 _public member_ `FOnDeleteFriendCompleteDelegate DeleteFriend = FOnDeleteFriendCompleteDelegate::CreateLambda([this](int32 InUserNum, bool bInWasSuccessful, const FUniqueNetId& InUserId, const FString& InListName, const FString& InErrorStr) { CHECK(State == EState::DeleteFriendCalled); CHECK(InUserNum == UserNum);`
- L33 _public function_ ``
- L52 _public function_ `virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override`
- L93 _protected member_ `int32 UserNum;`
- L94 _protected member_ `FUniqueNetIdPtr* UserId = nullptr;`
- L95 _protected member_ `FString ListName;`
- L96 _protected member_ `IOnlineFriendsPtr OnlineFriendsPtr = nullptr;`
- L97 _protected member_ `FDelegateHandle OnDeleteFriendCompleteDelegateHandle;`

#### enum `FFriendsDeleteFriendStep::EState`  
`enum class EState`  
_L30-30_
- L30 _public enumerator_ `enum class EState { Init, DeleteFriendCall, DeleteFriendCalled, ClearDelegates, Done } State = EState::Init; FOnDeleteFriendCompleteDelegate DeleteFriend = FOnDeleteFriendCompleteDelegate::CreateLambda([this](int32 InUserNum, bool bInWasSuccessful, const FUniqueNetId& InUserId, const FString& InListName, const FString& InErrorStr) { CHECK(State == EState::DeleteFriendCalled); CHECK(InUserNum == UserNum);`
- L30 _public enumerator_ `enum class EState { Init, DeleteFriendCall, DeleteFriendCalled, ClearDelegates, Done } State = EState::Init; FOnDeleteFriendCompleteDelegate DeleteFriend = FOnDeleteFriendCompleteDelegate::CreateLambda([this](int32 InUserNum, bool bInWasSuccessful, const FUniqueNetId& InUserId, const FString& InListName, const FString& InErrorStr) { CHECK(State == EState::DeleteFriendCalled); CHECK(InUserNum == UserNum);`
- L30 _public enumerator_ `enum class EState { Init, DeleteFriendCall, DeleteFriendCalled, ClearDelegates, Done } State = EState::Init; FOnDeleteFriendCompleteDelegate DeleteFriend = FOnDeleteFriendCompleteDelegate::CreateLambda([this](int32 InUserNum, bool bInWasSuccessful, const FUniqueNetId& InUserId, const FString& InListName, const FString& InErrorStr) { CHECK(State == EState::DeleteFriendCalled); CHECK(InUserNum == UserNum);`
- L30 _public enumerator_ `enum class EState { Init, DeleteFriendCall, DeleteFriendCalled, ClearDelegates, Done } State = EState::Init; FOnDeleteFriendCompleteDelegate DeleteFriend = FOnDeleteFriendCompleteDelegate::CreateLambda([this](int32 InUserNum, bool bInWasSuccessful, const FUniqueNetId& InUserId, const FString& InListName, const FString& InErrorStr) { CHECK(State == EState::DeleteFriendCalled); CHECK(InUserNum == UserNum);`
- L30 _public enumerator_ `enum class EState { Init, DeleteFriendCall, DeleteFriendCalled, ClearDelegates, Done } State = EState::Init; FOnDeleteFriendCompleteDelegate DeleteFriend = FOnDeleteFriendCompleteDelegate::CreateLambda([this](int32 InUserNum, bool bInWasSuccessful, const FUniqueNetId& InUserId, const FString& InListName, const FString& InErrorStr) { CHECK(State == EState::DeleteFriendCalled); CHECK(InUserNum == UserNum);`

### `Source/Programs/Online/OSSTestsCore/Helpers/Friends/FriendsDeleteFriendListHelper.h` (Other)


#### struct `FFriendsDeleteFriendListStep`  
`struct FFriendsDeleteFriendListStep : public FTestPipeline::FStep`  
_L10-80_
- inherits: `FTestPipeline::FStep`
- L12 _public function_ `FFriendsDeleteFriendListStep(int32 InLocalUserNum, FString& InLocalListName) : UserNum(InLocalUserNum) , ListName(InLocalListName)`
- L17 _public prototype_ `virtual ~FFriendsDeleteFriendListStep() = default;`
- L19 _public member_ `enum class EState { Init, DeleteFriendListCall, DeleteFriendListCalled, ClearDelegates, Done } State = EState::Init;`
- L21 _public member_ `FOnReadFriendsListComplete DeleteFriendsList = FOnDeleteFriendsListComplete::CreateLambda([this](int32 InUserNum, bool bInWasSuccessful, const FString& InListName, const FString& InErrorStr) { CHECK(State == EState::DeleteFriendListCalled); CHECK(InUserNum == UserNum); CHECK(bInWasSuccessful); CHECK(InListName == ListName); CHECK(InErrorStr.Len() == 0); TArray<TSharedRef<FOnlineFriend>> FriendsList; OnlineFriendsPtr->GetFriendsList(UserNum, ListName, FriendsList); CHECK(FriendsList.Num() == 0); State = EState::ClearDelegates; });`
- L22 _public function_ ``
- L37 _public function_ `virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override`
- L76 _protected member_ `int32 UserNum;`
- L77 _protected member_ `FUniqueNetIdPtr* UserId = nullptr;`
- L78 _protected member_ `FString ListName;`
- L79 _protected member_ `IOnlineFriendsPtr OnlineFriendsPtr = nullptr;`

#### enum `FFriendsDeleteFriendListStep::EState`  
`enum class EState`  
_L19-19_
- L19 _public enumerator_ `enum class EState { Init, DeleteFriendListCall, DeleteFriendListCalled, ClearDelegates, Done } State = EState::Init; FOnReadFriendsListComplete DeleteFriendsList = FOnDeleteFriendsListComplete::CreateLambda([this](int32 InUserNum, bool bInWasSuccessful, const FString& InListName, const FString& InErrorStr) { CHECK(State == EState::DeleteFriendListCalled); CHECK(InUserNum == UserNum); CHECK(bInWasSuccessful); CHECK(InListName == ListName);`
- L19 _public enumerator_ `enum class EState { Init, DeleteFriendListCall, DeleteFriendListCalled, ClearDelegates, Done } State = EState::Init; FOnReadFriendsListComplete DeleteFriendsList = FOnDeleteFriendsListComplete::CreateLambda([this](int32 InUserNum, bool bInWasSuccessful, const FString& InListName, const FString& InErrorStr) { CHECK(State == EState::DeleteFriendListCalled); CHECK(InUserNum == UserNum); CHECK(bInWasSuccessful); CHECK(InListName == ListName);`
- L19 _public enumerator_ `enum class EState { Init, DeleteFriendListCall, DeleteFriendListCalled, ClearDelegates, Done } State = EState::Init; FOnReadFriendsListComplete DeleteFriendsList = FOnDeleteFriendsListComplete::CreateLambda([this](int32 InUserNum, bool bInWasSuccessful, const FString& InListName, const FString& InErrorStr) { CHECK(State == EState::DeleteFriendListCalled); CHECK(InUserNum == UserNum); CHECK(bInWasSuccessful); CHECK(InListName == ListName);`
- L19 _public enumerator_ `enum class EState { Init, DeleteFriendListCall, DeleteFriendListCalled, ClearDelegates, Done } State = EState::Init; FOnReadFriendsListComplete DeleteFriendsList = FOnDeleteFriendsListComplete::CreateLambda([this](int32 InUserNum, bool bInWasSuccessful, const FString& InListName, const FString& InErrorStr) { CHECK(State == EState::DeleteFriendListCalled); CHECK(InUserNum == UserNum); CHECK(bInWasSuccessful); CHECK(InListName == ListName);`
- L19 _public enumerator_ `enum class EState { Init, DeleteFriendListCall, DeleteFriendListCalled, ClearDelegates, Done } State = EState::Init; FOnReadFriendsListComplete DeleteFriendsList = FOnDeleteFriendsListComplete::CreateLambda([this](int32 InUserNum, bool bInWasSuccessful, const FString& InListName, const FString& InErrorStr) { CHECK(State == EState::DeleteFriendListCalled); CHECK(InUserNum == UserNum); CHECK(bInWasSuccessful); CHECK(InListName == ListName);`

### `Source/Programs/Online/OSSTestsCore/Helpers/Friends/FriendsEnsureFriendshipHelper.h` (Other)


#### struct `FFriendsEnsureFriendshipStep`  
`struct FFriendsEnsureFriendshipStep : public FTestPipeline::FStep`  
_L20-78_
- inherits: `FTestPipeline::FStep`
- L22 _public function_ `FFriendsEnsureFriendshipStep(int32 InLocalUserNum, int32 InTargetUserNum, FUniqueNetIdPtr* InLocalUserId, FUniqueNetIdPtr* InTargetUserId, FString& InLocalListName, bool InbIsFriendsListPopulated = false) : InnerSteps( TInnerStepArrayBuilder<FTestPipeline::FStep>() .EmplaceInnerStep<FFriendsDeleteFriendListStep>(InLocalUserNum, InLocalListName) .EmplaceInnerStep<FFriendsDeleteFriendListStep>(InTargetUserNum, InLocalListName) .EmplaceInnerStep<FFriendsUnblockPlayerStep>(InLocalUserNum, InTargetUserId) .EmplaceInnerStep<FFriendsRejectInviteStep>(InTargetUserNum, InLocalUserId, InLocalListName) .EmplaceInnerStep<FFriendsSendInviteStep>(InLocalUserNum, InTargetUserId, InLocalListName) .EmplaceInnerStep<FFriendsReadFriendsListStep>(InTargetUserNum, InLocalListName) .EmplaceInnerStep<FFriendsAcceptInviteStep>(InTargetUserNum, InLocalUserId, InLocalListName) .EmplaceInnerStep<FFriendsReadFriendsListStep>(InTargetUserNum, InLocalListName, InbIsFriendsListPopulated) .EmplaceInnerStep<FFriendsIsFriendStep>(InTargetUserNum, InLocalUserId, InLocalListName) .Steps) , OldVerbosity(LogOnlineFriend.GetVerbosity()) , CurrentVerbosity([]() { LogOnlineFriend.SetVerbosity(ELogVerbosity::Error); return ELogVerbosity::Error; }())`
- L37 _public function_ ``
- L43 _public function_ `virtual ~FFriendsEnsureFriendshipStep()`
- L51 _public function_ `virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override`
- L73 _protected member_ `FStep::EContinuance CurrentStepContinuanceResult = FStep::EContinuance::ContinueStepping;`
- L74 _protected member_ `IOnlineFriendsPtr OnlineFriendsPtr = nullptr;`
- L75 _protected member_ `TArray<TUniquePtr<FTestPipeline::FStep>> InnerSteps;`
- L76 _protected member_ `ELogVerbosity::Type OldVerbosity;`
- L77 _protected member_ `ELogVerbosity::Type CurrentVerbosity;`

### `Source/Programs/Online/OSSTestsCore/Helpers/Friends/FriendsGetBlockedPlayersHelper.h` (Other)


#### struct `FFriendsGetBlockedPlayersStep`  
`struct FFriendsGetBlockedPlayersStep : public FTestPipeline::FStep`  
_L10-81_
- inherits: `FTestPipeline::FStep`
- L12 _public function_ `FFriendsGetBlockedPlayersStep(FUniqueNetIdPtr* InLocalUserId, FUniqueNetIdPtr* InTargetUserId = nullptr) : UserId(InLocalUserId) , TargetUserId(InTargetUserId)`
- L17 _public prototype_ `virtual ~FFriendsGetBlockedPlayersStep() = default;`
- L19 _public member_ `enum class EState { Init, GetBlockedPlayersCall, GetBlockedPlayersCalled, ClearDelegates, Done } State = EState::Init;`
- L21 _public function_ `virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override`
- L77 _protected member_ `FUniqueNetIdPtr* UserId = nullptr;`
- L78 _protected member_ `FUniqueNetIdPtr* TargetUserId = nullptr;`
- L79 _protected member_ `IOnlineFriendsPtr OnlineFriendsPtr = nullptr;`
- L80 _protected member_ `TArray<TSharedRef<FOnlineBlockedPlayer>> OutBlockedPlayers;`

#### enum `FFriendsGetBlockedPlayersStep::EState`  
`enum class EState`  
_L19-19_
- L19 _public enumerator_ `enum class EState { Init, GetBlockedPlayersCall, GetBlockedPlayersCalled, ClearDelegates, Done } State = EState::Init; virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override { switch (State) { case EState::Init: {`
- L19 _public enumerator_ `enum class EState { Init, GetBlockedPlayersCall, GetBlockedPlayersCalled, ClearDelegates, Done } State = EState::Init; virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override { switch (State) { case EState::Init: {`
- L19 _public enumerator_ `enum class EState { Init, GetBlockedPlayersCall, GetBlockedPlayersCalled, ClearDelegates, Done } State = EState::Init; virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override { switch (State) { case EState::Init: {`
- L19 _public enumerator_ `enum class EState { Init, GetBlockedPlayersCall, GetBlockedPlayersCalled, ClearDelegates, Done } State = EState::Init; virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override { switch (State) { case EState::Init: {`
- L19 _public enumerator_ `enum class EState { Init, GetBlockedPlayersCall, GetBlockedPlayersCalled, ClearDelegates, Done } State = EState::Init; virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override { switch (State) { case EState::Init: {`

### `Source/Programs/Online/OSSTestsCore/Helpers/Friends/FriendsGetFriendHelper.h` (Other)


#### struct `FFriendsGetFriendStep`  
`struct FFriendsGetFriendStep : public FTestPipeline::FStep`  
_L9-72_
- inherits: `FTestPipeline::FStep`
- L11 _public function_ `FFriendsGetFriendStep(int32 InLocalUserNum, FUniqueNetIdPtr* InLocalUserId, FString& InLocalListName) : UserNum(InLocalUserNum) , UserId(InLocalUserId) , ListName(InLocalListName)`
- L17 _public prototype_ `virtual ~FFriendsGetFriendStep() = default;`
- L19 _public member_ `enum class EState { Init, GetFriendCall, GetFriendCalled, ClearDelegates, Done } State = EState::Init;`
- L21 _public function_ `virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override`
- L68 _protected member_ `int32 UserNum;`
- L69 _protected member_ `FUniqueNetIdPtr* UserId = nullptr;`
- L70 _protected member_ `FString ListName;`
- L71 _protected member_ `IOnlineFriendsPtr OnlineFriendsPtr = nullptr;`

#### enum `FFriendsGetFriendStep::EState`  
`enum class EState`  
_L19-19_
- L19 _public enumerator_ `enum class EState { Init, GetFriendCall, GetFriendCalled, ClearDelegates, Done } State = EState::Init; virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override { switch (State) { case EState::Init:`
- L19 _public enumerator_ `enum class EState { Init, GetFriendCall, GetFriendCalled, ClearDelegates, Done } State = EState::Init; virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override { switch (State) { case EState::Init:`
- L19 _public enumerator_ `enum class EState { Init, GetFriendCall, GetFriendCalled, ClearDelegates, Done } State = EState::Init; virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override { switch (State) { case EState::Init:`
- L19 _public enumerator_ `enum class EState { Init, GetFriendCall, GetFriendCalled, ClearDelegates, Done } State = EState::Init; virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override { switch (State) { case EState::Init:`
- L19 _public enumerator_ `enum class EState { Init, GetFriendCall, GetFriendCalled, ClearDelegates, Done } State = EState::Init; virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override { switch (State) { case EState::Init:`

### `Source/Programs/Online/OSSTestsCore/Helpers/Friends/FriendsGetFriendInvitePolicyHelper.h` (Other)


#### struct `FFriendsGetFriendInvitePolicyStep`  
`struct FFriendsGetFriendInvitePolicyStep : public FTestPipeline::FStep`  
_L9-64_
- inherits: `FTestPipeline::FStep`
- L11 _public function_ `FFriendsGetFriendInvitePolicyStep(FUniqueNetIdPtr* InLocalUserId, const EFriendInvitePolicy& InLocalExpectedInvitePolicy) : UserId(InLocalUserId) , ExpectedInvitePolicy(InLocalExpectedInvitePolicy)`
- L16 _public prototype_ `virtual ~FFriendsGetFriendInvitePolicyStep() = default;`
- L18 _public member_ `enum class EState { Init, GetFriendInvitePolicyCall, GetFriendInvitePolicyCalled, ClearDelegates, Done } State = EState::Init;`
- L20 _public function_ `virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override`
- L61 _protected member_ `FUniqueNetIdPtr* UserId = nullptr;`
- L62 _protected member_ `EFriendInvitePolicy ExpectedInvitePolicy = EFriendInvitePolicy::InvalidOrMax;`
- L63 _protected member_ `IOnlineFriendsPtr OnlineFriendsPtr = nullptr;`

#### enum `FFriendsGetFriendInvitePolicyStep::EState`  
`enum class EState`  
_L18-18_
- L18 _public enumerator_ `enum class EState { Init, GetFriendInvitePolicyCall, GetFriendInvitePolicyCalled, ClearDelegates, Done } State = EState::Init; virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override { switch (State) { case EState::Init:`
- L18 _public enumerator_ `enum class EState { Init, GetFriendInvitePolicyCall, GetFriendInvitePolicyCalled, ClearDelegates, Done } State = EState::Init; virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override { switch (State) { case EState::Init:`
- L18 _public enumerator_ `enum class EState { Init, GetFriendInvitePolicyCall, GetFriendInvitePolicyCalled, ClearDelegates, Done } State = EState::Init; virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override { switch (State) { case EState::Init:`
- L18 _public enumerator_ `enum class EState { Init, GetFriendInvitePolicyCall, GetFriendInvitePolicyCalled, ClearDelegates, Done } State = EState::Init; virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override { switch (State) { case EState::Init:`
- L18 _public enumerator_ `enum class EState { Init, GetFriendInvitePolicyCall, GetFriendInvitePolicyCalled, ClearDelegates, Done } State = EState::Init; virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override { switch (State) { case EState::Init:`

### `Source/Programs/Online/OSSTestsCore/Helpers/Friends/FriendsGetFriendSettingsHelper.h` (Other)


#### struct `FFriendsGetFriendSettingsStep`  
`struct FFriendsGetFriendSettingsStep : public FTestPipeline::FStep`  
_L10-66_
- inherits: `FTestPipeline::FStep`
- L12 _public function_ `FFriendsGetFriendSettingsStep(FUniqueNetIdPtr* InLocalUserId, const FString& InLocalSource) : UserId(InLocalUserId) , Source(InLocalSource)`
- L17 _public prototype_ `virtual ~FFriendsGetFriendSettingsStep() = default;`
- L19 _public member_ `enum class EState { Init, GetFriendSettingsCall, GetFriendSettingsCalled, ClearDelegates, Done } State = EState::Init;`
- L21 _public function_ `virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override`
- L62 _protected member_ `FUniqueNetIdPtr* UserId = nullptr;`
- L63 _protected member_ `FString Source;`
- L64 _protected member_ `TMap<FString, TSharedRef<FOnlineFriendSettingsSourceData>> OutSettings;`
- L65 _protected member_ `IOnlineFriendsPtr OnlineFriendsPtr = nullptr;`

#### enum `FFriendsGetFriendSettingsStep::EState`  
`enum class EState`  
_L19-19_
- L19 _public enumerator_ `enum class EState { Init, GetFriendSettingsCall, GetFriendSettingsCalled, ClearDelegates, Done } State = EState::Init; virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override { switch (State) { case EState::Init: {`
- L19 _public enumerator_ `enum class EState { Init, GetFriendSettingsCall, GetFriendSettingsCalled, ClearDelegates, Done } State = EState::Init; virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override { switch (State) { case EState::Init: {`
- L19 _public enumerator_ `enum class EState { Init, GetFriendSettingsCall, GetFriendSettingsCalled, ClearDelegates, Done } State = EState::Init; virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override { switch (State) { case EState::Init: {`
- L19 _public enumerator_ `enum class EState { Init, GetFriendSettingsCall, GetFriendSettingsCalled, ClearDelegates, Done } State = EState::Init; virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override { switch (State) { case EState::Init: {`
- L19 _public enumerator_ `enum class EState { Init, GetFriendSettingsCall, GetFriendSettingsCalled, ClearDelegates, Done } State = EState::Init; virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override { switch (State) { case EState::Init: {`

### `Source/Programs/Online/OSSTestsCore/Helpers/Friends/FriendsGetFriendsListHelper.h` (Other)


#### struct `FFriendsGetFriendsListStep`  
`struct FFriendsGetFriendsListStep : public FTestPipeline::FStep`  
_L10-77_
- inherits: `FTestPipeline::FStep`
- L12 _public function_ `FFriendsGetFriendsListStep(int32 InLocalUserNum, FString& InLocalListName) : UserNum(InLocalUserNum) , ListName(InLocalListName)`
- L17 _public function_ `virtual ~FFriendsGetFriendsListStep()`
- L29 _public member_ `enum class EState { Init, GetFriendsListCall, GetFriendsListCalled, ClearDelegates, Done } State = EState::Init;`
- L31 _public function_ `virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override`
- L73 _protected member_ `int32 UserNum;`
- L74 _protected member_ `FString ListName;`
- L75 _protected member_ `IOnlineFriendsPtr OnlineFriendsPtr = nullptr;`
- L76 _protected member_ `TArray<TSharedRef<FOnlineFriend>> OutFriends;`

#### enum `FFriendsGetFriendsListStep::EState`  
`enum class EState`  
_L29-29_
- L29 _public enumerator_ `enum class EState { Init, GetFriendsListCall, GetFriendsListCalled, ClearDelegates, Done } State = EState::Init; virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override { switch (State) { case EState::Init:`
- L29 _public enumerator_ `enum class EState { Init, GetFriendsListCall, GetFriendsListCalled, ClearDelegates, Done } State = EState::Init; virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override { switch (State) { case EState::Init:`
- L29 _public enumerator_ `enum class EState { Init, GetFriendsListCall, GetFriendsListCalled, ClearDelegates, Done } State = EState::Init; virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override { switch (State) { case EState::Init:`
- L29 _public enumerator_ `enum class EState { Init, GetFriendsListCall, GetFriendsListCalled, ClearDelegates, Done } State = EState::Init; virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override { switch (State) { case EState::Init:`
- L29 _public enumerator_ `enum class EState { Init, GetFriendsListCall, GetFriendsListCalled, ClearDelegates, Done } State = EState::Init; virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override { switch (State) { case EState::Init:`

### `Source/Programs/Online/OSSTestsCore/Helpers/Friends/FriendsIsFriendHelper.h` (Other)


#### struct `FFriendsIsFriendStep`  
`struct FFriendsIsFriendStep : public FTestPipeline::FStep`  
_L10-61_
- inherits: `FTestPipeline::FStep`
- L12 _public function_ `FFriendsIsFriendStep(int32 InLocalUserNum, FUniqueNetIdPtr* InLocalUserId, FString& InLocalListName) : UserNum(InLocalUserNum) , UserId(InLocalUserId) , ListName(InLocalListName)`
- L18 _public prototype_ `virtual ~FFriendsIsFriendStep() = default;`
- L20 _public member_ `enum class EState { Init, IsFriendCall, IsFriendCalled, ClearDelegates, Done } State = EState::Init;`
- L22 _public function_ `virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override`
- L57 _protected member_ `int32 UserNum;`
- L58 _protected member_ `FUniqueNetIdPtr* UserId = nullptr;`
- L59 _protected member_ `FString ListName;`
- L60 _protected member_ `IOnlineFriendsPtr OnlineFriendsPtr = nullptr;`

#### enum `FFriendsIsFriendStep::EState`  
`enum class EState`  
_L20-20_
- L20 _public enumerator_ `enum class EState { Init, IsFriendCall, IsFriendCalled, ClearDelegates, Done } State = EState::Init; virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override { switch (State) { case EState::Init: {`
- L20 _public enumerator_ `enum class EState { Init, IsFriendCall, IsFriendCalled, ClearDelegates, Done } State = EState::Init; virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override { switch (State) { case EState::Init: {`
- L20 _public enumerator_ `enum class EState { Init, IsFriendCall, IsFriendCalled, ClearDelegates, Done } State = EState::Init; virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override { switch (State) { case EState::Init: {`
- L20 _public enumerator_ `enum class EState { Init, IsFriendCall, IsFriendCalled, ClearDelegates, Done } State = EState::Init; virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override { switch (State) { case EState::Init: {`
- L20 _public enumerator_ `enum class EState { Init, IsFriendCall, IsFriendCalled, ClearDelegates, Done } State = EState::Init; virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override { switch (State) { case EState::Init: {`

### `Source/Programs/Online/OSSTestsCore/Helpers/Friends/FriendsQueryBlockedPlayersHelper.h` (Other)


#### struct `FFriendsQueryBlockedPlayersStep`  
`struct FFriendsQueryBlockedPlayersStep : public FTestPipeline::FStep`  
_L10-84_
- inherits: `FTestPipeline::FStep`
- L12 _public function_ `FFriendsQueryBlockedPlayersStep(FUniqueNetIdPtr* InLocalUserId, bool InLocalIsBlockedPlayersListPopulated = false) : UserId(InLocalUserId) , IsBlockedPlayersListPopulated(InLocalIsBlockedPlayersListPopulated)`
- L17 _public prototype_ `virtual ~FFriendsQueryBlockedPlayersStep() = default;`
- L19 _public member_ `enum class EState { Init, QueryBlockedPlayersCall, QueryBlockedPlayersCalled, ClearDelegates, Done } State = EState::Init;`
- L21 _public member_ `FOnQueryBlockedPlayersCompleteDelegate QueryBlockedPlayers = FOnQueryBlockedPlayersCompleteDelegate::CreateLambda([this](const FUniqueNetId& InUserId, bool bInWasSuccessful, const FString& InErrorStr) { CHECK(State == EState::QueryBlockedPlayersCalled); CHECK(InUserId == *UserId->Get()); CHECK(InErrorStr.Len() == 0); if (IsBlockedPlayersListPopulated) { TArray<TSharedRef<FOnlineBlockedPlayer>> BlockedPlayersList; OnlineFriendsPtr->GetBlockedPlayers(InUserId, BlockedPlayersList); CHECK(BlockedPlayersList.Num() > 0); } State = EState::ClearDelegates; });`
- L22 _public function_ ``
- L38 _public function_ `virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override`
- L80 _protected member_ `FUniqueNetIdPtr* UserId = nullptr;`
- L81 _protected member_ `IOnlineFriendsPtr OnlineFriendsPtr = nullptr;`
- L82 _protected member_ `bool IsBlockedPlayersListPopulated = false;`
- L83 _protected member_ `FDelegateHandle OnQueryBlockedPlayersCompleteDelegateHandle;`

#### enum `FFriendsQueryBlockedPlayersStep::EState`  
`enum class EState`  
_L19-19_
- L19 _public enumerator_ `enum class EState { Init, QueryBlockedPlayersCall, QueryBlockedPlayersCalled, ClearDelegates, Done } State = EState::Init; FOnQueryBlockedPlayersCompleteDelegate QueryBlockedPlayers = FOnQueryBlockedPlayersCompleteDelegate::CreateLambda([this](const FUniqueNetId& InUserId, bool bInWasSuccessful, const FString& InErrorStr) { CHECK(State == EState::QueryBlockedPlayersCalled); CHECK(InUserId == *UserId->Get()); CHECK(InErrorStr.Len() == 0);`
- L19 _public enumerator_ `enum class EState { Init, QueryBlockedPlayersCall, QueryBlockedPlayersCalled, ClearDelegates, Done } State = EState::Init; FOnQueryBlockedPlayersCompleteDelegate QueryBlockedPlayers = FOnQueryBlockedPlayersCompleteDelegate::CreateLambda([this](const FUniqueNetId& InUserId, bool bInWasSuccessful, const FString& InErrorStr) { CHECK(State == EState::QueryBlockedPlayersCalled); CHECK(InUserId == *UserId->Get()); CHECK(InErrorStr.Len() == 0);`
- L19 _public enumerator_ `enum class EState { Init, QueryBlockedPlayersCall, QueryBlockedPlayersCalled, ClearDelegates, Done } State = EState::Init; FOnQueryBlockedPlayersCompleteDelegate QueryBlockedPlayers = FOnQueryBlockedPlayersCompleteDelegate::CreateLambda([this](const FUniqueNetId& InUserId, bool bInWasSuccessful, const FString& InErrorStr) { CHECK(State == EState::QueryBlockedPlayersCalled); CHECK(InUserId == *UserId->Get()); CHECK(InErrorStr.Len() == 0);`
- L19 _public enumerator_ `enum class EState { Init, QueryBlockedPlayersCall, QueryBlockedPlayersCalled, ClearDelegates, Done } State = EState::Init; FOnQueryBlockedPlayersCompleteDelegate QueryBlockedPlayers = FOnQueryBlockedPlayersCompleteDelegate::CreateLambda([this](const FUniqueNetId& InUserId, bool bInWasSuccessful, const FString& InErrorStr) { CHECK(State == EState::QueryBlockedPlayersCalled); CHECK(InUserId == *UserId->Get()); CHECK(InErrorStr.Len() == 0);`
- L19 _public enumerator_ `enum class EState { Init, QueryBlockedPlayersCall, QueryBlockedPlayersCalled, ClearDelegates, Done } State = EState::Init; FOnQueryBlockedPlayersCompleteDelegate QueryBlockedPlayers = FOnQueryBlockedPlayersCompleteDelegate::CreateLambda([this](const FUniqueNetId& InUserId, bool bInWasSuccessful, const FString& InErrorStr) { CHECK(State == EState::QueryBlockedPlayersCalled); CHECK(InUserId == *UserId->Get()); CHECK(InErrorStr.Len() == 0);`

### `Source/Programs/Online/OSSTestsCore/Helpers/Friends/FriendsQueryFriendSettingsHelper.h` (Other)


#### struct `FFriendsQueryFriendSettingsStep`  
`struct FFriendsQueryFriendSettingsStep : public FTestPipeline::FStep`  
_L10-107_
- inherits: `FTestPipeline::FStep`
- L12 _public function_ `FFriendsQueryFriendSettingsStep(FUniqueNetIdPtr* InLocalUserId, const FString& InLocalSource) : UserId(InLocalUserId) , Source(InLocalSource)`
- L17 _public function_ `FFriendsQueryFriendSettingsStep(FUniqueNetIdPtr* InLocalUserId, FFriendSettings& InLocalNewSettings) : UserId(InLocalUserId) , ExpectedSettings(InLocalNewSettings) , bUseOverload(true)`
- L23 _public prototype_ `virtual ~FFriendsQueryFriendSettingsStep() = default;`
- L25 _public member_ `enum class EState { Init, QueryFriendSettingsCall, QueryFriendSettingsCalled, ClearDelegates, Done } State = EState::Init;`
- L27 _public member_ `FOnQueryFriendSettingsComplete OnQueryFriendSettings = FOnQueryFriendSettingsComplete::CreateLambda([this](const FUniqueNetId& InUserId, bool bInWasSuccessful, const FString& InErrorStr) { CHECK(State == EState::QueryFriendSettingsCalled); CHECK(InUserId == *UserId->Get()); CHECK(bInWasSuccessful); CHECK(InErrorStr.Len() == 0); State = EState::ClearDelegates; });`
- L28 _public function_ ``
- L37 _public member_ `FOnSettingsOperationComplete OnSettingsOperation = FOnSettingsOperationComplete::CreateLambda([this](const FUniqueNetId& InUserId, bool bInWasSuccessful, bool bInWasUpdate, const FFriendSettings& InSettings, const FString& InErrorStr) { CHECK(State == EState::QueryFriendSettingsCalled); CHECK(InUserId == *UserId->Get()); CHECK(bInWasSuccessful);`
- L55 _public function_ `virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override`
- L102 _protected member_ `FUniqueNetIdPtr* UserId = nullptr;`
- L103 _protected member_ `FString Source;`
- L104 _protected member_ `FFriendSettings ExpectedSettings;`
- L105 _protected member_ `bool bUseOverload = false;`
- L106 _protected member_ `IOnlineFriendsPtr OnlineFriendsPtr = nullptr;`

#### enum `FFriendsQueryFriendSettingsStep::EState`  
`enum class EState`  
_L25-25_
- L25 _public enumerator_ `enum class EState { Init, QueryFriendSettingsCall, QueryFriendSettingsCalled, ClearDelegates, Done } State = EState::Init; FOnQueryFriendSettingsComplete OnQueryFriendSettings = FOnQueryFriendSettingsComplete::CreateLambda([this](const FUniqueNetId& InUserId, bool bInWasSuccessful, const FString& InErrorStr) { CHECK(State == EState::QueryFriendSettingsCalled); CHECK(InUserId == *UserId->Get()); CHECK(bInWasSuccessful); CHECK(InErrorStr.Len() == 0);`
- L25 _public enumerator_ `enum class EState { Init, QueryFriendSettingsCall, QueryFriendSettingsCalled, ClearDelegates, Done } State = EState::Init; FOnQueryFriendSettingsComplete OnQueryFriendSettings = FOnQueryFriendSettingsComplete::CreateLambda([this](const FUniqueNetId& InUserId, bool bInWasSuccessful, const FString& InErrorStr) { CHECK(State == EState::QueryFriendSettingsCalled); CHECK(InUserId == *UserId->Get()); CHECK(bInWasSuccessful); CHECK(InErrorStr.Len() == 0);`
- L25 _public enumerator_ `enum class EState { Init, QueryFriendSettingsCall, QueryFriendSettingsCalled, ClearDelegates, Done } State = EState::Init; FOnQueryFriendSettingsComplete OnQueryFriendSettings = FOnQueryFriendSettingsComplete::CreateLambda([this](const FUniqueNetId& InUserId, bool bInWasSuccessful, const FString& InErrorStr) { CHECK(State == EState::QueryFriendSettingsCalled); CHECK(InUserId == *UserId->Get()); CHECK(bInWasSuccessful); CHECK(InErrorStr.Len() == 0);`
- L25 _public enumerator_ `enum class EState { Init, QueryFriendSettingsCall, QueryFriendSettingsCalled, ClearDelegates, Done } State = EState::Init; FOnQueryFriendSettingsComplete OnQueryFriendSettings = FOnQueryFriendSettingsComplete::CreateLambda([this](const FUniqueNetId& InUserId, bool bInWasSuccessful, const FString& InErrorStr) { CHECK(State == EState::QueryFriendSettingsCalled); CHECK(InUserId == *UserId->Get()); CHECK(bInWasSuccessful); CHECK(InErrorStr.Len() == 0);`
- L25 _public enumerator_ `enum class EState { Init, QueryFriendSettingsCall, QueryFriendSettingsCalled, ClearDelegates, Done } State = EState::Init; FOnQueryFriendSettingsComplete OnQueryFriendSettings = FOnQueryFriendSettingsComplete::CreateLambda([this](const FUniqueNetId& InUserId, bool bInWasSuccessful, const FString& InErrorStr) { CHECK(State == EState::QueryFriendSettingsCalled); CHECK(InUserId == *UserId->Get()); CHECK(bInWasSuccessful); CHECK(InErrorStr.Len() == 0);`

### `Source/Programs/Online/OSSTestsCore/Helpers/Friends/FriendsReadFriendsListHelper.h` (Other)


#### struct `FFriendsReadFriendsListStep`  
`struct FFriendsReadFriendsListStep : public FTestPipeline::FStep`  
_L10-83_
- inherits: `FTestPipeline::FStep`
- L12 _public function_ `FFriendsReadFriendsListStep(int32 InLocalUserNum, FString& InLocalListName, bool bInIsFriendsListPopulated = false) : UserNum(InLocalUserNum) , ListName(InLocalListName) , bIsFriendsListPopulated(bInIsFriendsListPopulated)`
- L18 _public prototype_ `virtual ~FFriendsReadFriendsListStep() = default;`
- L20 _public member_ `enum class EState { Init, ReadFriendsListCall, ReadFriendsListCalled, ClearDelegates, Done } State = EState::Init;`
- L22 _public member_ `FOnReadFriendsListComplete ReadFriendsList = FOnReadFriendsListComplete::CreateLambda([this](int32 InUserNum, bool bInWasSuccessful, const FString& InListName, const FString& InErrorStr) { CHECK(State == EState::ReadFriendsListCalled); CHECK(InUserNum == UserNum); CHECK(bInWasSuccessful); CHECK(InListName == ListName); CHECK(InErrorStr.Len() == 0); if (bIsFriendsListPopulated) { TArray<TSharedRef<FOnlineFriend>> FriendsList; OnlineFriendsPtr->GetFriendsList(UserNum, ListName, FriendsList); CHECK(FriendsList.Num() > 0); } State = EState::ClearDelegates; });`
- L23 _public function_ ``
- L40 _public function_ `virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override`
- L79 _protected member_ `int32 UserNum;`
- L80 _protected member_ `FString ListName;`
- L81 _protected member_ `bool bIsFriendsListPopulated = false;`
- L82 _protected member_ `IOnlineFriendsPtr OnlineFriendsPtr = nullptr;`

#### enum `FFriendsReadFriendsListStep::EState`  
`enum class EState`  
_L20-20_
- L20 _public enumerator_ `enum class EState { Init, ReadFriendsListCall, ReadFriendsListCalled, ClearDelegates, Done } State = EState::Init; FOnReadFriendsListComplete ReadFriendsList = FOnReadFriendsListComplete::CreateLambda([this](int32 InUserNum, bool bInWasSuccessful, const FString& InListName, const FString& InErrorStr) { CHECK(State == EState::ReadFriendsListCalled); CHECK(InUserNum == UserNum); CHECK(bInWasSuccessful); CHECK(InListName == ListName);`
- L20 _public enumerator_ `enum class EState { Init, ReadFriendsListCall, ReadFriendsListCalled, ClearDelegates, Done } State = EState::Init; FOnReadFriendsListComplete ReadFriendsList = FOnReadFriendsListComplete::CreateLambda([this](int32 InUserNum, bool bInWasSuccessful, const FString& InListName, const FString& InErrorStr) { CHECK(State == EState::ReadFriendsListCalled); CHECK(InUserNum == UserNum); CHECK(bInWasSuccessful); CHECK(InListName == ListName);`
- L20 _public enumerator_ `enum class EState { Init, ReadFriendsListCall, ReadFriendsListCalled, ClearDelegates, Done } State = EState::Init; FOnReadFriendsListComplete ReadFriendsList = FOnReadFriendsListComplete::CreateLambda([this](int32 InUserNum, bool bInWasSuccessful, const FString& InListName, const FString& InErrorStr) { CHECK(State == EState::ReadFriendsListCalled); CHECK(InUserNum == UserNum); CHECK(bInWasSuccessful); CHECK(InListName == ListName);`
- L20 _public enumerator_ `enum class EState { Init, ReadFriendsListCall, ReadFriendsListCalled, ClearDelegates, Done } State = EState::Init; FOnReadFriendsListComplete ReadFriendsList = FOnReadFriendsListComplete::CreateLambda([this](int32 InUserNum, bool bInWasSuccessful, const FString& InListName, const FString& InErrorStr) { CHECK(State == EState::ReadFriendsListCalled); CHECK(InUserNum == UserNum); CHECK(bInWasSuccessful); CHECK(InListName == ListName);`
- L20 _public enumerator_ `enum class EState { Init, ReadFriendsListCall, ReadFriendsListCalled, ClearDelegates, Done } State = EState::Init; FOnReadFriendsListComplete ReadFriendsList = FOnReadFriendsListComplete::CreateLambda([this](int32 InUserNum, bool bInWasSuccessful, const FString& InListName, const FString& InErrorStr) { CHECK(State == EState::ReadFriendsListCalled); CHECK(InUserNum == UserNum); CHECK(bInWasSuccessful); CHECK(InListName == ListName);`

### `Source/Programs/Online/OSSTestsCore/Helpers/Friends/FriendsRejectInviteHelper.h` (Other)


#### struct `FFriendsRejectInviteStep`  
`struct FFriendsRejectInviteStep : public FTestPipeline::FStep`  
_L10-97_
- inherits: `FTestPipeline::FStep`
- L12 _public function_ `FFriendsRejectInviteStep(int32 InLocalUserNum, FUniqueNetIdPtr* InLocalUserId, FString& InLocalListName) : UserNum(InLocalUserNum) , UserId(InLocalUserId) , ListName(InLocalListName)`
- L18 _public function_ `virtual ~FFriendsRejectInviteStep()`
- L30 _public member_ `enum class EState { Init, RejectInviteCall, RejectInviteCalled, ClearDelegates, Done } State = EState::Init;`
- L32 _public member_ `FOnRejectInviteCompleteDelegate RejectInvite = FOnRejectInviteCompleteDelegate::CreateLambda([this](int32 InUserNum, bool bInWasSuccessful, const FUniqueNetId& InUserId, const FString& InListName, const FString& InErrorStr) { CHECK(State == EState::RejectInviteCalled); CHECK(InUserNum == UserNum);`
- L33 _public function_ ``
- L51 _public function_ `virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override`
- L92 _protected member_ `int32 UserNum;`
- L93 _protected member_ `FUniqueNetIdPtr* UserId = nullptr;`
- L94 _protected member_ `FString ListName;`
- L95 _protected member_ `IOnlineFriendsPtr OnlineFriendsPtr = nullptr;`
- L96 _protected member_ `FDelegateHandle OnRejectInviteCompleteDelegateHandle;`

#### enum `FFriendsRejectInviteStep::EState`  
`enum class EState`  
_L30-30_
- L30 _public enumerator_ `enum class EState { Init, RejectInviteCall, RejectInviteCalled, ClearDelegates, Done } State = EState::Init; FOnRejectInviteCompleteDelegate RejectInvite = FOnRejectInviteCompleteDelegate::CreateLambda([this](int32 InUserNum, bool bInWasSuccessful, const FUniqueNetId& InUserId, const FString& InListName, const FString& InErrorStr) { CHECK(State == EState::RejectInviteCalled); CHECK(InUserNum == UserNum);`
- L30 _public enumerator_ `enum class EState { Init, RejectInviteCall, RejectInviteCalled, ClearDelegates, Done } State = EState::Init; FOnRejectInviteCompleteDelegate RejectInvite = FOnRejectInviteCompleteDelegate::CreateLambda([this](int32 InUserNum, bool bInWasSuccessful, const FUniqueNetId& InUserId, const FString& InListName, const FString& InErrorStr) { CHECK(State == EState::RejectInviteCalled); CHECK(InUserNum == UserNum);`
- L30 _public enumerator_ `enum class EState { Init, RejectInviteCall, RejectInviteCalled, ClearDelegates, Done } State = EState::Init; FOnRejectInviteCompleteDelegate RejectInvite = FOnRejectInviteCompleteDelegate::CreateLambda([this](int32 InUserNum, bool bInWasSuccessful, const FUniqueNetId& InUserId, const FString& InListName, const FString& InErrorStr) { CHECK(State == EState::RejectInviteCalled); CHECK(InUserNum == UserNum);`
- L30 _public enumerator_ `enum class EState { Init, RejectInviteCall, RejectInviteCalled, ClearDelegates, Done } State = EState::Init; FOnRejectInviteCompleteDelegate RejectInvite = FOnRejectInviteCompleteDelegate::CreateLambda([this](int32 InUserNum, bool bInWasSuccessful, const FUniqueNetId& InUserId, const FString& InListName, const FString& InErrorStr) { CHECK(State == EState::RejectInviteCalled); CHECK(InUserNum == UserNum);`
- L30 _public enumerator_ `enum class EState { Init, RejectInviteCall, RejectInviteCalled, ClearDelegates, Done } State = EState::Init; FOnRejectInviteCompleteDelegate RejectInvite = FOnRejectInviteCompleteDelegate::CreateLambda([this](int32 InUserNum, bool bInWasSuccessful, const FUniqueNetId& InUserId, const FString& InListName, const FString& InErrorStr) { CHECK(State == EState::RejectInviteCalled); CHECK(InUserNum == UserNum);`

### `Source/Programs/Online/OSSTestsCore/Helpers/Friends/FriendsSendInviteHelper.h` (Other)


#### struct `FFriendsSendInviteStep`  
`struct FFriendsSendInviteStep : public FTestPipeline::FStep`  
_L10-72_
- inherits: `FTestPipeline::FStep`
- L12 _public function_ `FFriendsSendInviteStep(int32 InLocalUserNum, FUniqueNetIdPtr* InLocalUserId, FString& InLocalListName) : UserNum(InLocalUserNum) , UserId(InLocalUserId) , ListName(InLocalListName)`
- L18 _public prototype_ `virtual ~FFriendsSendInviteStep() = default;`
- L20 _public member_ `enum class EState { Init, SendInviteCall, SendInviteCalled, ClearDelegates, Done } State = EState::Init;`
- L22 _public member_ `FOnSendInviteComplete SendInvite = FOnSendInviteComplete::CreateLambda([this](int32 InUserNum, bool bInWasSuccessful, const FUniqueNetId& InUserId, const FString& InListName, const FString& InErrorStr) { CHECK(State == EState::SendInviteCalled); CHECK(InUserNum == UserNum); CHECK(bInWasSuccessful); CHECK(InUserId == *UserId->Get()); CHECK(InListName == ListName); CHECK(InErrorStr.Len() == 0); State = EState::ClearDelegates; });`
- L23 _public function_ ``
- L34 _public function_ `virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override`
- L68 _protected member_ `int32 UserNum;`
- L69 _protected member_ `FUniqueNetIdPtr* UserId = nullptr;`
- L70 _protected member_ `FString ListName;`
- L71 _protected member_ `IOnlineFriendsPtr OnlineFriendsPtr = nullptr;`

#### enum `FFriendsSendInviteStep::EState`  
`enum class EState`  
_L20-20_
- L20 _public enumerator_ `enum class EState { Init, SendInviteCall, SendInviteCalled, ClearDelegates, Done } State = EState::Init; FOnSendInviteComplete SendInvite = FOnSendInviteComplete::CreateLambda([this](int32 InUserNum, bool bInWasSuccessful, const FUniqueNetId& InUserId, const FString& InListName, const FString& InErrorStr) { CHECK(State == EState::SendInviteCalled); CHECK(InUserNum == UserNum); CHECK(bInWasSuccessful); CHECK(InUserId == *UserId->Get());`
- L20 _public enumerator_ `enum class EState { Init, SendInviteCall, SendInviteCalled, ClearDelegates, Done } State = EState::Init; FOnSendInviteComplete SendInvite = FOnSendInviteComplete::CreateLambda([this](int32 InUserNum, bool bInWasSuccessful, const FUniqueNetId& InUserId, const FString& InListName, const FString& InErrorStr) { CHECK(State == EState::SendInviteCalled); CHECK(InUserNum == UserNum); CHECK(bInWasSuccessful); CHECK(InUserId == *UserId->Get());`
- L20 _public enumerator_ `enum class EState { Init, SendInviteCall, SendInviteCalled, ClearDelegates, Done } State = EState::Init; FOnSendInviteComplete SendInvite = FOnSendInviteComplete::CreateLambda([this](int32 InUserNum, bool bInWasSuccessful, const FUniqueNetId& InUserId, const FString& InListName, const FString& InErrorStr) { CHECK(State == EState::SendInviteCalled); CHECK(InUserNum == UserNum); CHECK(bInWasSuccessful); CHECK(InUserId == *UserId->Get());`
- L20 _public enumerator_ `enum class EState { Init, SendInviteCall, SendInviteCalled, ClearDelegates, Done } State = EState::Init; FOnSendInviteComplete SendInvite = FOnSendInviteComplete::CreateLambda([this](int32 InUserNum, bool bInWasSuccessful, const FUniqueNetId& InUserId, const FString& InListName, const FString& InErrorStr) { CHECK(State == EState::SendInviteCalled); CHECK(InUserNum == UserNum); CHECK(bInWasSuccessful); CHECK(InUserId == *UserId->Get());`
- L20 _public enumerator_ `enum class EState { Init, SendInviteCall, SendInviteCalled, ClearDelegates, Done } State = EState::Init; FOnSendInviteComplete SendInvite = FOnSendInviteComplete::CreateLambda([this](int32 InUserNum, bool bInWasSuccessful, const FUniqueNetId& InUserId, const FString& InListName, const FString& InErrorStr) { CHECK(State == EState::SendInviteCalled); CHECK(InUserNum == UserNum); CHECK(bInWasSuccessful); CHECK(InUserId == *UserId->Get());`

### `Source/Programs/Online/OSSTestsCore/Helpers/Friends/FriendsSetFriendAliasHelper.h` (Other)


#### struct `FFriendsSetFriendAliasStep`  
`struct FFriendsSetFriendAliasStep : public FTestPipeline::FStep`  
_L10-77_
- inherits: `FTestPipeline::FStep`
- L12 _public function_ `FFriendsSetFriendAliasStep(int32 InLocalUserNum, FUniqueNetIdPtr* InLocalUserId, FString& InLocalListName, FString& InLocalAlias) : UserNum(InLocalUserNum) , UserId(InLocalUserId) , ListName(InLocalListName) , Alias(InLocalAlias)`
- L19 _public prototype_ `virtual ~FFriendsSetFriendAliasStep() = default;`
- L21 _public member_ `enum class EState { Init, SetFriendAliasCall, SetFriendAliasCalled, ClearDelegates, Done } State = EState::Init;`
- L23 _public member_ `FOnSetFriendAliasComplete SetFriendAlias = FOnSetFriendAliasComplete::CreateLambda([this](int32 InUserNum, const FUniqueNetId& InUserId, const FString& InListName, const FOnlineError& InError) { CHECK(State == EState::SetFriendAliasCalled); CHECK(InUserNum == UserNum); CHECK(InUserId == *UserId->Get()); CHECK(InListName == ListName); CHECK(InError == FOnlineError::Success()); State = EState::ClearDelegates; });`
- L24 _public function_ ``
- L34 _public function_ `virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override`
- L72 _protected member_ `int32 UserNum;`
- L73 _protected member_ `FUniqueNetIdPtr* UserId = nullptr;`
- L74 _protected member_ `FString ListName;`
- L75 _protected member_ `FString Alias;`
- L76 _protected member_ `IOnlineFriendsPtr OnlineFriendsPtr = nullptr;`

#### enum `FFriendsSetFriendAliasStep::EState`  
`enum class EState`  
_L21-21_
- L21 _public enumerator_ `enum class EState { Init, SetFriendAliasCall, SetFriendAliasCalled, ClearDelegates, Done } State = EState::Init; FOnSetFriendAliasComplete SetFriendAlias = FOnSetFriendAliasComplete::CreateLambda([this](int32 InUserNum, const FUniqueNetId& InUserId, const FString& InListName, const FOnlineError& InError) { CHECK(State == EState::SetFriendAliasCalled); CHECK(InUserNum == UserNum); CHECK(InUserId == *UserId->Get()); CHECK(InListName == ListName);`
- L21 _public enumerator_ `enum class EState { Init, SetFriendAliasCall, SetFriendAliasCalled, ClearDelegates, Done } State = EState::Init; FOnSetFriendAliasComplete SetFriendAlias = FOnSetFriendAliasComplete::CreateLambda([this](int32 InUserNum, const FUniqueNetId& InUserId, const FString& InListName, const FOnlineError& InError) { CHECK(State == EState::SetFriendAliasCalled); CHECK(InUserNum == UserNum); CHECK(InUserId == *UserId->Get()); CHECK(InListName == ListName);`
- L21 _public enumerator_ `enum class EState { Init, SetFriendAliasCall, SetFriendAliasCalled, ClearDelegates, Done } State = EState::Init; FOnSetFriendAliasComplete SetFriendAlias = FOnSetFriendAliasComplete::CreateLambda([this](int32 InUserNum, const FUniqueNetId& InUserId, const FString& InListName, const FOnlineError& InError) { CHECK(State == EState::SetFriendAliasCalled); CHECK(InUserNum == UserNum); CHECK(InUserId == *UserId->Get()); CHECK(InListName == ListName);`
- L21 _public enumerator_ `enum class EState { Init, SetFriendAliasCall, SetFriendAliasCalled, ClearDelegates, Done } State = EState::Init; FOnSetFriendAliasComplete SetFriendAlias = FOnSetFriendAliasComplete::CreateLambda([this](int32 InUserNum, const FUniqueNetId& InUserId, const FString& InListName, const FOnlineError& InError) { CHECK(State == EState::SetFriendAliasCalled); CHECK(InUserNum == UserNum); CHECK(InUserId == *UserId->Get()); CHECK(InListName == ListName);`
- L21 _public enumerator_ `enum class EState { Init, SetFriendAliasCall, SetFriendAliasCalled, ClearDelegates, Done } State = EState::Init; FOnSetFriendAliasComplete SetFriendAlias = FOnSetFriendAliasComplete::CreateLambda([this](int32 InUserNum, const FUniqueNetId& InUserId, const FString& InListName, const FOnlineError& InError) { CHECK(State == EState::SetFriendAliasCalled); CHECK(InUserNum == UserNum); CHECK(InUserId == *UserId->Get()); CHECK(InListName == ListName);`

### `Source/Programs/Online/OSSTestsCore/Helpers/Friends/FriendsSetFriendSettingsHelper.h` (Other)


#### struct `FFriendsSetFriendSettingsStep`  
`struct FFriendsSetFriendSettingsStep : public FTestPipeline::FStep`  
_L10-75_
- inherits: `FTestPipeline::FStep`
- L12 _public function_ `FFriendsSetFriendSettingsStep(FUniqueNetIdPtr* InLocalUserId, const FString& InLocalSource, bool bInLocalNeverShowAgain) : UserId(InLocalUserId) , Source(InLocalSource) , bNeverShowAgain(bInLocalNeverShowAgain)`
- L18 _public prototype_ `virtual ~FFriendsSetFriendSettingsStep() = default;`
- L20 _public member_ `enum class EState { Init, SetFriendSettingsCall, SetFriendSettingsCalled, ClearDelegates, Done } State = EState::Init;`
- L22 _public member_ `FOnSetFriendSettingsComplete SetFriendSettings = FOnSetFriendSettingsComplete::CreateLambda([this](const FUniqueNetId& InUserId, bool bInWasSuccessful, const FString& InErrorStr) { CHECK(State == EState::SetFriendSettingsCalled); CHECK(InUserId == *UserId->Get()); CHECK(bInWasSuccessful); CHECK(InErrorStr.Len() == 0); State = EState::ClearDelegates; });`
- L23 _public function_ ``
- L32 _public function_ `virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override`
- L71 _protected member_ `FUniqueNetIdPtr* UserId = nullptr;`
- L72 _protected member_ `FString Source;`
- L73 _protected member_ `bool bNeverShowAgain;`
- L74 _protected member_ `IOnlineFriendsPtr OnlineFriendsPtr = nullptr;`

#### enum `FFriendsSetFriendSettingsStep::EState`  
`enum class EState`  
_L20-20_
- L20 _public enumerator_ `enum class EState { Init, SetFriendSettingsCall, SetFriendSettingsCalled, ClearDelegates, Done } State = EState::Init; FOnSetFriendSettingsComplete SetFriendSettings = FOnSetFriendSettingsComplete::CreateLambda([this](const FUniqueNetId& InUserId, bool bInWasSuccessful, const FString& InErrorStr) { CHECK(State == EState::SetFriendSettingsCalled); CHECK(InUserId == *UserId->Get()); CHECK(bInWasSuccessful); CHECK(InErrorStr.Len() == 0);`
- L20 _public enumerator_ `enum class EState { Init, SetFriendSettingsCall, SetFriendSettingsCalled, ClearDelegates, Done } State = EState::Init; FOnSetFriendSettingsComplete SetFriendSettings = FOnSetFriendSettingsComplete::CreateLambda([this](const FUniqueNetId& InUserId, bool bInWasSuccessful, const FString& InErrorStr) { CHECK(State == EState::SetFriendSettingsCalled); CHECK(InUserId == *UserId->Get()); CHECK(bInWasSuccessful); CHECK(InErrorStr.Len() == 0);`
- L20 _public enumerator_ `enum class EState { Init, SetFriendSettingsCall, SetFriendSettingsCalled, ClearDelegates, Done } State = EState::Init; FOnSetFriendSettingsComplete SetFriendSettings = FOnSetFriendSettingsComplete::CreateLambda([this](const FUniqueNetId& InUserId, bool bInWasSuccessful, const FString& InErrorStr) { CHECK(State == EState::SetFriendSettingsCalled); CHECK(InUserId == *UserId->Get()); CHECK(bInWasSuccessful); CHECK(InErrorStr.Len() == 0);`
- L20 _public enumerator_ `enum class EState { Init, SetFriendSettingsCall, SetFriendSettingsCalled, ClearDelegates, Done } State = EState::Init; FOnSetFriendSettingsComplete SetFriendSettings = FOnSetFriendSettingsComplete::CreateLambda([this](const FUniqueNetId& InUserId, bool bInWasSuccessful, const FString& InErrorStr) { CHECK(State == EState::SetFriendSettingsCalled); CHECK(InUserId == *UserId->Get()); CHECK(bInWasSuccessful); CHECK(InErrorStr.Len() == 0);`
- L20 _public enumerator_ `enum class EState { Init, SetFriendSettingsCall, SetFriendSettingsCalled, ClearDelegates, Done } State = EState::Init; FOnSetFriendSettingsComplete SetFriendSettings = FOnSetFriendSettingsComplete::CreateLambda([this](const FUniqueNetId& InUserId, bool bInWasSuccessful, const FString& InErrorStr) { CHECK(State == EState::SetFriendSettingsCalled); CHECK(InUserId == *UserId->Get()); CHECK(bInWasSuccessful); CHECK(InErrorStr.Len() == 0);`

### `Source/Programs/Online/OSSTestsCore/Helpers/Friends/FriendsUnblockPlayerHelper.h` (Other)


#### struct `FFriendsUnblockPlayerStep`  
`struct FFriendsUnblockPlayerStep : public FTestPipeline::FStep`  
_L10-80_
- inherits: `FTestPipeline::FStep`
- L12 _public function_ `FFriendsUnblockPlayerStep(int32 InLocalUserNum, FUniqueNetIdPtr* InLocalUserId) : UserNum(InLocalUserNum) , UserId(InLocalUserId)`
- L17 _public prototype_ `virtual ~FFriendsUnblockPlayerStep() = default;`
- L19 _public member_ `enum class EState { Init, UnblockPlayerCall, UnblockPlayerCalled, ClearDelegates, Done } State = EState::Init;`
- L21 _public member_ `FOnUnblockedPlayerCompleteDelegate UnblockPlayer = FOnUnblockedPlayerCompleteDelegate::CreateLambda([this](int32 InUserNum, bool bInWasSuccessful, const FUniqueNetId& InUserId, const FString& InListName, const FString& InErrorStr) { CHECK(State == EState::UnblockPlayerCalled); CHECK(InUserNum == UserNum); CHECK(bInWasSuccessful); CHECK(InUserId == *UserId->Get()); CHECK(InListName == TEXT("BlockedPlayers")); CHECK(InErrorStr.Len() == 0); State = EState::ClearDelegates; });`
- L22 _public function_ ``
- L33 _public function_ `virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override`
- L76 _protected member_ `int32 UserNum;`
- L77 _protected member_ `FUniqueNetIdPtr* UserId = nullptr;`
- L78 _protected member_ `IOnlineFriendsPtr OnlineFriendsPtr = nullptr;`
- L79 _protected member_ `FDelegateHandle OnUnblockPlayerCompleteDelegateHandle;`

#### enum `FFriendsUnblockPlayerStep::EState`  
`enum class EState`  
_L19-19_
- L19 _public enumerator_ `enum class EState { Init, UnblockPlayerCall, UnblockPlayerCalled, ClearDelegates, Done } State = EState::Init; FOnUnblockedPlayerCompleteDelegate UnblockPlayer = FOnUnblockedPlayerCompleteDelegate::CreateLambda([this](int32 InUserNum, bool bInWasSuccessful, const FUniqueNetId& InUserId, const FString& InListName, const FString& InErrorStr) { CHECK(State == EState::UnblockPlayerCalled); CHECK(InUserNum == UserNum); CHECK(bInWasSuccessful); CHECK(InUserId == *UserId->Get());`
- L19 _public enumerator_ `enum class EState { Init, UnblockPlayerCall, UnblockPlayerCalled, ClearDelegates, Done } State = EState::Init; FOnUnblockedPlayerCompleteDelegate UnblockPlayer = FOnUnblockedPlayerCompleteDelegate::CreateLambda([this](int32 InUserNum, bool bInWasSuccessful, const FUniqueNetId& InUserId, const FString& InListName, const FString& InErrorStr) { CHECK(State == EState::UnblockPlayerCalled); CHECK(InUserNum == UserNum); CHECK(bInWasSuccessful); CHECK(InUserId == *UserId->Get());`
- L19 _public enumerator_ `enum class EState { Init, UnblockPlayerCall, UnblockPlayerCalled, ClearDelegates, Done } State = EState::Init; FOnUnblockedPlayerCompleteDelegate UnblockPlayer = FOnUnblockedPlayerCompleteDelegate::CreateLambda([this](int32 InUserNum, bool bInWasSuccessful, const FUniqueNetId& InUserId, const FString& InListName, const FString& InErrorStr) { CHECK(State == EState::UnblockPlayerCalled); CHECK(InUserNum == UserNum); CHECK(bInWasSuccessful); CHECK(InUserId == *UserId->Get());`
- L19 _public enumerator_ `enum class EState { Init, UnblockPlayerCall, UnblockPlayerCalled, ClearDelegates, Done } State = EState::Init; FOnUnblockedPlayerCompleteDelegate UnblockPlayer = FOnUnblockedPlayerCompleteDelegate::CreateLambda([this](int32 InUserNum, bool bInWasSuccessful, const FUniqueNetId& InUserId, const FString& InListName, const FString& InErrorStr) { CHECK(State == EState::UnblockPlayerCalled); CHECK(InUserNum == UserNum); CHECK(bInWasSuccessful); CHECK(InUserId == *UserId->Get());`
- L19 _public enumerator_ `enum class EState { Init, UnblockPlayerCall, UnblockPlayerCalled, ClearDelegates, Done } State = EState::Init; FOnUnblockedPlayerCompleteDelegate UnblockPlayer = FOnUnblockedPlayerCompleteDelegate::CreateLambda([this](int32 InUserNum, bool bInWasSuccessful, const FUniqueNetId& InUserId, const FString& InListName, const FString& InErrorStr) { CHECK(State == EState::UnblockPlayerCalled); CHECK(InUserNum == UserNum); CHECK(bInWasSuccessful); CHECK(InUserId == *UserId->Get());`

### `Source/Programs/Online/OSSTestsCore/Helpers/Friends/FriendsUpdateFriendInvitePolicySettingsHelper.h` (Other)


#### struct `FFriendsUpdateFriendInvitePolicySettingsStep`  
`struct FFriendsUpdateFriendInvitePolicySettingsStep : public FTestPipeline::FStep`  
_L10-73_
- inherits: `FTestPipeline::FStep`
- L12 _public function_ `FFriendsUpdateFriendInvitePolicySettingsStep(FUniqueNetIdPtr* InLocalUserId, EFriendInvitePolicy& InLocalNewInvitesPolicyValue, bool bInAffectsExistingInvites) : UserId(InLocalUserId) , NewInvitesPolicyValue(InLocalNewInvitesPolicyValue)`
- L17 _public prototype_ `virtual ~FFriendsUpdateFriendInvitePolicySettingsStep() = default;`
- L19 _public member_ `enum class EState { Init, UpdateFriendSettingsCalled, ClearDelegates, Done } State = EState::Init;`
- L21 _public member_ `FOnSettingsOperationComplete UpdateFriendInvitePolicySettings = FOnSettingsOperationComplete::CreateLambda([this](const FUniqueNetId& InUserId, bool bInWasSuccessful, bool bInWasUpdate, const FFriendSettings& InSettings, const FString& InErrorStr) { CHECK(State == EState::UpdateFriendSettingsCalled); CHECK(InUserId == *UserId->Get()); CHECK(bInWasSuccessful); CHECK(bInWasUpdate);`
- L22 _public function_ ``
- L37 _public function_ `virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override`
- L70 _protected member_ `FUniqueNetIdPtr* UserId = nullptr;`
- L71 _protected member_ `EFriendInvitePolicy NewInvitesPolicyValue;`
- L72 _protected member_ `IOnlineFriendsPtr OnlineFriendsPtr = nullptr;`

#### enum `FFriendsUpdateFriendInvitePolicySettingsStep::EState`  
`enum class EState`  
_L19-19_
- L19 _public enumerator_ `enum class EState { Init, UpdateFriendSettingsCalled, ClearDelegates, Done } State = EState::Init; FOnSettingsOperationComplete UpdateFriendInvitePolicySettings = FOnSettingsOperationComplete::CreateLambda([this](const FUniqueNetId& InUserId, bool bInWasSuccessful, bool bInWasUpdate, const FFriendSettings& InSettings, const FString& InErrorStr) { CHECK(State == EState::UpdateFriendSettingsCalled); CHECK(InUserId == *UserId->Get()); CHECK(bInWasSuccessful); CHECK(bInWasUpdate);`
- L19 _public enumerator_ `enum class EState { Init, UpdateFriendSettingsCalled, ClearDelegates, Done } State = EState::Init; FOnSettingsOperationComplete UpdateFriendInvitePolicySettings = FOnSettingsOperationComplete::CreateLambda([this](const FUniqueNetId& InUserId, bool bInWasSuccessful, bool bInWasUpdate, const FFriendSettings& InSettings, const FString& InErrorStr) { CHECK(State == EState::UpdateFriendSettingsCalled); CHECK(InUserId == *UserId->Get()); CHECK(bInWasSuccessful); CHECK(bInWasUpdate);`
- L19 _public enumerator_ `enum class EState { Init, UpdateFriendSettingsCalled, ClearDelegates, Done } State = EState::Init; FOnSettingsOperationComplete UpdateFriendInvitePolicySettings = FOnSettingsOperationComplete::CreateLambda([this](const FUniqueNetId& InUserId, bool bInWasSuccessful, bool bInWasUpdate, const FFriendSettings& InSettings, const FString& InErrorStr) { CHECK(State == EState::UpdateFriendSettingsCalled); CHECK(InUserId == *UserId->Get()); CHECK(bInWasSuccessful); CHECK(bInWasUpdate);`
- L19 _public enumerator_ `enum class EState { Init, UpdateFriendSettingsCalled, ClearDelegates, Done } State = EState::Init; FOnSettingsOperationComplete UpdateFriendInvitePolicySettings = FOnSettingsOperationComplete::CreateLambda([this](const FUniqueNetId& InUserId, bool bInWasSuccessful, bool bInWasUpdate, const FFriendSettings& InSettings, const FString& InErrorStr) { CHECK(State == EState::UpdateFriendSettingsCalled); CHECK(InUserId == *UserId->Get()); CHECK(bInWasSuccessful); CHECK(bInWasUpdate);`

### `Source/Programs/Online/OSSTestsCore/Helpers/Identity/IdentityAutoLoginHelper.h` (Other)


#### struct `FIdentityAutoLoginStep`  
`struct FIdentityAutoLoginStep : public FTestPipeline::FStep`  
_L10-87_
- inherits: `FTestPipeline::FStep`
- L12 _public function_ `FIdentityAutoLoginStep(int32 InLocalUserNum) :LocalUserNum(InLocalUserNum)`
- L16 _public function_ `virtual ~FIdentityAutoLoginStep()`
- L28 _public member_ `enum class EState { Init, AutoLoginCall, AutoLoginCalled, ClearDelegates, Done } State = EState::Init;`
- L30 _public member_ `FOnLoginCompleteDelegate LoginDelegate = FOnLoginCompleteDelegate::CreateLambda([this](int32 LoginLocalUserNum, bool bLoginWasSuccessful, const FUniqueNetId& LoginUserId, const FString& LoginError) { CHECK(State == EState::AutoLoginCalled); CHECK(bLoginWasSuccessful); CHECK(LoginLocalUserNum == LocalUserNum); State = EState::ClearDelegates; });`
- L31 _public function_ ``
- L40 _public function_ `virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override`
- L84 _protected member_ `int32 LocalUserNum = 0;`
- L85 _protected member_ `IOnlineIdentityPtr OnlineIdentityPtr = nullptr;`
- L86 _protected member_ `FDelegateHandle OnLoginCompleteDelegateHandle;`

#### enum `FIdentityAutoLoginStep::EState`  
`enum class EState`  
_L28-28_
- L28 _public enumerator_ `enum class EState { Init, AutoLoginCall, AutoLoginCalled, ClearDelegates, Done } State = EState::Init; FOnLoginCompleteDelegate LoginDelegate = FOnLoginCompleteDelegate::CreateLambda([this](int32 LoginLocalUserNum, bool bLoginWasSuccessful, const FUniqueNetId& LoginUserId, const FString& LoginError) { CHECK(State == EState::AutoLoginCalled); CHECK(bLoginWasSuccessful); CHECK(LoginLocalUserNum == LocalUserNum);`
- L28 _public enumerator_ `enum class EState { Init, AutoLoginCall, AutoLoginCalled, ClearDelegates, Done } State = EState::Init; FOnLoginCompleteDelegate LoginDelegate = FOnLoginCompleteDelegate::CreateLambda([this](int32 LoginLocalUserNum, bool bLoginWasSuccessful, const FUniqueNetId& LoginUserId, const FString& LoginError) { CHECK(State == EState::AutoLoginCalled); CHECK(bLoginWasSuccessful); CHECK(LoginLocalUserNum == LocalUserNum);`
- L28 _public enumerator_ `enum class EState { Init, AutoLoginCall, AutoLoginCalled, ClearDelegates, Done } State = EState::Init; FOnLoginCompleteDelegate LoginDelegate = FOnLoginCompleteDelegate::CreateLambda([this](int32 LoginLocalUserNum, bool bLoginWasSuccessful, const FUniqueNetId& LoginUserId, const FString& LoginError) { CHECK(State == EState::AutoLoginCalled); CHECK(bLoginWasSuccessful); CHECK(LoginLocalUserNum == LocalUserNum);`
- L28 _public enumerator_ `enum class EState { Init, AutoLoginCall, AutoLoginCalled, ClearDelegates, Done } State = EState::Init; FOnLoginCompleteDelegate LoginDelegate = FOnLoginCompleteDelegate::CreateLambda([this](int32 LoginLocalUserNum, bool bLoginWasSuccessful, const FUniqueNetId& LoginUserId, const FString& LoginError) { CHECK(State == EState::AutoLoginCalled); CHECK(bLoginWasSuccessful); CHECK(LoginLocalUserNum == LocalUserNum);`
- L28 _public enumerator_ `enum class EState { Init, AutoLoginCall, AutoLoginCalled, ClearDelegates, Done } State = EState::Init; FOnLoginCompleteDelegate LoginDelegate = FOnLoginCompleteDelegate::CreateLambda([this](int32 LoginLocalUserNum, bool bLoginWasSuccessful, const FUniqueNetId& LoginUserId, const FString& LoginError) { CHECK(State == EState::AutoLoginCalled); CHECK(bLoginWasSuccessful); CHECK(LoginLocalUserNum == LocalUserNum);`

### `Source/Programs/Online/OSSTestsCore/Helpers/Identity/IdentityCreateUniquePlayerIdFromBinaryDataHelper.h` (Other)


#### struct `FIdentityCreateUniquePlayerIdFromBinaryDataStep`  
`struct FIdentityCreateUniquePlayerIdFromBinaryDataStep : public FTestPipeline::FStep`  
_L10-45_
- inherits: `FTestPipeline::FStep`
- L12 _public function_ `FIdentityCreateUniquePlayerIdFromBinaryDataStep(uint8* InBytes, int32 InSize, TFunction<void(FUniqueNetIdPtr)>&& InStateSaver) : Bytes(InBytes) , Size(InSize) , StateSaver(MoveTemp(InStateSaver))`
- L18 _public function_ `FIdentityCreateUniquePlayerIdFromBinaryDataStep(uint8* InBytes, int32 InSize) : Bytes(InBytes) , Size(InSize) , StateSaver([](FUniqueNetIdPtr) {})`
- L21 _public function_ `, StateSaver([](FUniqueNetIdPtr) {})`
- L24 _public prototype_ `virtual ~FIdentityCreateUniquePlayerIdFromBinaryDataStep() = default;`
- L26 _public function_ `virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override`
- L41 _protected member_ `uint8* Bytes = nullptr;`
- L42 _protected member_ `int32 Size = 0;`
- L43 _protected member_ `FUniqueNetIdPtr UniqueNetId = nullptr;`
- L44 _protected member_ `TFunction<void(FUniqueNetIdPtr)> StateSaver;`

### `Source/Programs/Online/OSSTestsCore/Helpers/Identity/IdentityCreateUniquePlayerIdFromStringHelper.h` (Other)


#### struct `FIdentityCreateUniquePlayerIdFromStringStep`  
`struct FIdentityCreateUniquePlayerIdFromStringStep : public FTestPipeline::FStep`  
_L10-43_
- inherits: `FTestPipeline::FStep`
- L12 _public function_ `FIdentityCreateUniquePlayerIdFromStringStep(const FString& InString, TFunction<void(FUniqueNetIdPtr)>&& InStateSaver) : String(InString) , StateSaver(MoveTemp(InStateSaver))`
- L17 _public function_ `FIdentityCreateUniquePlayerIdFromStringStep(const FString& InString) : String(InString) , StateSaver([](FUniqueNetIdPtr) {})`
- L19 _public function_ `, StateSaver([](FUniqueNetIdPtr) {})`
- L22 _public prototype_ `virtual ~FIdentityCreateUniquePlayerIdFromStringStep() = default;`
- L24 _public function_ `virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override`
- L40 _protected member_ `FString String = TEXT("");`
- L41 _protected member_ `FUniqueNetIdPtr UniqueNetIdPtr = nullptr;`
- L42 _protected member_ `TFunction<void(FUniqueNetIdPtr)> StateSaver;`

### `Source/Programs/Online/OSSTestsCore/Helpers/Identity/IdentityGetAllUserAccountsHelper.h` (Other)


#### struct `FIdentityGetAllUserAccountsStep`  
`struct FIdentityGetAllUserAccountsStep : public FTestPipeline::FStep`  
_L10-49_
- inherits: `FTestPipeline::FStep`
- L12 _public function_ `FIdentityGetAllUserAccountsStep(TArray<FUniqueNetIdPtr>* InUserUniqueNetIds, TFunction<void(TArray<TSharedPtr<FUserOnlineAccount>>)>&& InStateSaver) : UserUniqueNetIds(InUserUniqueNetIds) , StateSaver(MoveTemp(InStateSaver))`
- L17 _public function_ `FIdentityGetAllUserAccountsStep(TArray<FUniqueNetIdPtr>* InUserUniqueNetIds) : UserUniqueNetIds(InUserUniqueNetIds) , StateSaver([](TArray<TSharedPtr<FUserOnlineAccount>>){})`
- L19 _public function_ `, StateSaver([](TArray<TSharedPtr<FUserOnlineAccount>>){})`
- L22 _public prototype_ `virtual ~FIdentityGetAllUserAccountsStep() = default;`
- L24 _public function_ `virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override`
- L47 _protected member_ `TArray<FUniqueNetIdPtr>* UserUniqueNetIds = nullptr;`
- L48 _protected member_ `TFunction<void(TArray<TSharedPtr<FUserOnlineAccount>>)> StateSaver;`

#### Free symbols / members of external scopes

- L35 _function_ `` (scope `FIdentityGetAllUserAccountsStep::Tick`)

### `Source/Programs/Online/OSSTestsCore/Helpers/Identity/IdentityGetAuthTokenHelper.h` (Other)


#### struct `FIdentityGetAuthTokenStep`  
`struct FIdentityGetAuthTokenStep : public FTestPipeline::FStep`  
_L10-45_
- inherits: `FTestPipeline::FStep`
- L12 _public function_ `FIdentityGetAuthTokenStep(int32 InLocalUserNum, TFunction<void(FString)>&& InStateSaver) : LocalUserNum(InLocalUserNum) , StateSaver(MoveTemp(InStateSaver))`
- L17 _public function_ `FIdentityGetAuthTokenStep(int32 InLocalUserNum) : LocalUserNum(InLocalUserNum) , StateSaver([](FString) {})`
- L19 _public function_ `, StateSaver([](FString) {})`
- L22 _public prototype_ `virtual ~FIdentityGetAuthTokenStep() = default;`
- L24 _public function_ `virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override`
- L42 _protected member_ `int32 LocalUserNum = 0;`
- L43 _protected member_ `FString AuthToken = TEXT("");`
- L44 _protected member_ `TFunction<void(FString)> StateSaver;`

### `Source/Programs/Online/OSSTestsCore/Helpers/Identity/IdentityGetAuthTypeHelper.h` (Other)


#### struct `FIdentityGetAuthTypeStep`  
`struct FIdentityGetAuthTypeStep : public FTestPipeline::FStep`  
_L10-44_
- inherits: `FTestPipeline::FStep`
- L12 _public function_ `FIdentityGetAuthTypeStep(TFunction<void(FString)>&& InStateSaver) : StateSaver(MoveTemp(InStateSaver))`
- L16 _public function_ `FIdentityGetAuthTypeStep() : StateSaver([](FString) {})`
- L17 _public function_ `: StateSaver([](FString) {})`
- L20 _public prototype_ `virtual ~FIdentityGetAuthTypeStep() = default;`
- L22 _public function_ `virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override`
- L42 _protected member_ `FString AuthType = FString(TEXT(""));`
- L43 _protected member_ `TFunction<void(FString)> StateSaver;`

### `Source/Programs/Online/OSSTestsCore/Helpers/Identity/IdentityGetLoginStatusByLocalUserNumHelper.h` (Other)


#### struct `FIdentityGetLoginStatusByLocalUserNumStep`  
`struct FIdentityGetLoginStatusByLocalUserNumStep : public FTestPipeline::FStep`  
_L10-33_
- inherits: `FTestPipeline::FStep`
- L12 _public function_ `FIdentityGetLoginStatusByLocalUserNumStep(int32 InLocalUserNum, ELoginStatus::Type InExpectedStatusType) : LocalUserNum(InLocalUserNum) , ExpectedStatusType(InExpectedStatusType)`
- L17 _public prototype_ `virtual ~FIdentityGetLoginStatusByLocalUserNumStep() = default;`
- L19 _public function_ `virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override`
- L30 _protected member_ `int32 LocalUserNum = 0;`
- L31 _protected member_ `ELoginStatus::Type LoginStatusType = ELoginStatus::Type::NotLoggedIn;`
- L32 _protected member_ `ELoginStatus::Type ExpectedStatusType = ELoginStatus::Type::NotLoggedIn;`

### `Source/Programs/Online/OSSTestsCore/Helpers/Identity/IdentityGetLoginStatusByUserIdHelper.h` (Other)


#### struct `FIdentityGetLoginStatusByUserIdStep`  
`struct FIdentityGetLoginStatusByUserIdStep : public FTestPipeline::FStep`  
_L10-35_
- inherits: `FTestPipeline::FStep`
- L12 _public function_ `FIdentityGetLoginStatusByUserIdStep(FUniqueNetIdPtr* InUserId, ELoginStatus::Type InExpectedStatus) : UserId(InUserId) , ExpectedStatus(InExpectedStatus)`
- L17 _public prototype_ `virtual ~FIdentityGetLoginStatusByUserIdStep() = default;`
- L19 _public function_ `virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override`
- L32 _protected member_ `FUniqueNetIdPtr* UserId = nullptr;`
- L33 _protected member_ `ELoginStatus::Type LoginStatusType = ELoginStatus::Type::NotLoggedIn;`
- L34 _protected member_ `ELoginStatus::Type ExpectedStatus = ELoginStatus::Type::NotLoggedIn;`

### `Source/Programs/Online/OSSTestsCore/Helpers/Identity/IdentityGetPlatformUserIdFromUniqueNetIdHelper.h` (Other)


#### struct `FIdentityGetPlatformUserIdFromUniqueNetIdStep`  
`struct FIdentityGetPlatformUserIdFromUniqueNetIdStep : public FTestPipeline::FStep`  
_L10-42_
- inherits: `FTestPipeline::FStep`
- L12 _public function_ `FIdentityGetPlatformUserIdFromUniqueNetIdStep(FUniqueNetIdPtr* InUserId, TFunction<void(FPlatformUserId)>&& InStateSaver) : UserId(InUserId) , StateSaver(MoveTemp(InStateSaver))`
- L17 _public function_ `FIdentityGetPlatformUserIdFromUniqueNetIdStep(FUniqueNetIdPtr* InUserId) : UserId(InUserId) , StateSaver([](FPlatformUserId) {})`
- L19 _public function_ `, StateSaver([](FPlatformUserId) {})`
- L22 _public prototype_ `virtual ~FIdentityGetPlatformUserIdFromUniqueNetIdStep() = default;`
- L24 _public function_ `virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override`
- L39 _protected member_ `FUniqueNetIdPtr* UserId = nullptr;`
- L40 _protected member_ `FPlatformUserId PlatformUserId = FPlatformUserId::CreateFromInternalId(0);`
- L41 _protected member_ `TFunction<void(FPlatformUserId)> StateSaver;`

### `Source/Programs/Online/OSSTestsCore/Helpers/Identity/IdentityGetPlayerNicknameByLocalUserNumHelper.h` (Other)


#### struct `FIdentityGetPlayerNicknameByLocalUserNumStep`  
`struct FIdentityGetPlayerNicknameByLocalUserNumStep : public FTestPipeline::FStep`  
_L10-42_
- inherits: `FTestPipeline::FStep`
- L12 _public function_ `FIdentityGetPlayerNicknameByLocalUserNumStep(int32 InLocalUserNum, TFunction<void(FString)>&& InStateSaver) : LocalUserNum(InLocalUserNum) , StateSaver(MoveTemp(InStateSaver))`
- L17 _public function_ `FIdentityGetPlayerNicknameByLocalUserNumStep(int32 InLocalUserNum) : LocalUserNum(InLocalUserNum) , StateSaver([](FString) {})`
- L19 _public function_ `, StateSaver([](FString) {})`
- L22 _public prototype_ `virtual ~FIdentityGetPlayerNicknameByLocalUserNumStep() = default;`
- L24 _public function_ `virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override`
- L39 _protected member_ `int32 LocalUserNum = 0;`
- L40 _protected member_ `FString Nickname = TEXT("");`
- L41 _protected member_ `TFunction<void(FString)> StateSaver;`

### `Source/Programs/Online/OSSTestsCore/Helpers/Identity/IdentityGetPlayerNicknameByUserIdHelper.h` (Other)


#### struct `FIdentityGetPlayerNicknameByUserIdStep`  
`struct FIdentityGetPlayerNicknameByUserIdStep : public FTestPipeline::FStep`  
_L10-42_
- inherits: `FTestPipeline::FStep`
- L12 _public function_ `FIdentityGetPlayerNicknameByUserIdStep(FUniqueNetIdPtr* InUserId, TFunction<void(FString)>&& InStateSaver) : UserId(InUserId) , StateSaver(MoveTemp(InStateSaver))`
- L17 _public function_ `FIdentityGetPlayerNicknameByUserIdStep(FUniqueNetIdPtr* InUserId) : UserId(InUserId) , StateSaver([](FString) {})`
- L19 _public function_ `, StateSaver([](FString) {})`
- L22 _public prototype_ `virtual ~FIdentityGetPlayerNicknameByUserIdStep() = default;`
- L24 _public function_ `virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override`
- L39 _protected member_ `FUniqueNetIdPtr* UserId = nullptr;`
- L40 _protected member_ `FString Nickname = TEXT("");`
- L41 _protected member_ `TFunction<void(FString)> StateSaver;`

### `Source/Programs/Online/OSSTestsCore/Helpers/Identity/IdentityGetUniquePlayerIdHelper.h` (Other)


#### struct `FIdentityGetUniquePlayerIdStep`  
`struct FIdentityGetUniquePlayerIdStep : public FTestPipeline::FStep`  
_L10-40_
- inherits: `FTestPipeline::FStep`
- L12 _public function_ `FIdentityGetUniquePlayerIdStep(int32 InLocalUserNum, TFunction<void(FUniqueNetIdPtr)>&& InStateSaver) : LocalUserNum(InLocalUserNum) , StateSaver(MoveTemp(InStateSaver))`
- L17 _public function_ `FIdentityGetUniquePlayerIdStep(int32 InLocalUserNum) : LocalUserNum(InLocalUserNum) , StateSaver([](FUniqueNetIdPtr) {})`
- L19 _public function_ `, StateSaver([](FUniqueNetIdPtr) {})`
- L22 _public prototype_ `virtual ~FIdentityGetUniquePlayerIdStep() = default;`
- L24 _public function_ `virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override`
- L37 _protected member_ `int32 LocalUserNum = 0;`
- L38 _protected member_ `FUniqueNetIdPtr UserId = nullptr;`
- L39 _protected member_ `TFunction<void(FUniqueNetIdPtr)> StateSaver;`

### `Source/Programs/Online/OSSTestsCore/Helpers/Identity/IdentityGetUserAccountHelper.h` (Other)


#### struct `FIdentityGetUserAccountStep`  
`struct FIdentityGetUserAccountStep : public FTestPipeline::FStep`  
_L10-43_
- inherits: `FTestPipeline::FStep`
- L12 _public function_ `FIdentityGetUserAccountStep(FUniqueNetIdPtr* InUniqueNetId, TFunction<void(TSharedPtr<FUserOnlineAccount>)>&& InStateSaver) : UniqueNetId(InUniqueNetId) , StateSaver(MoveTemp(InStateSaver))`
- L17 _public function_ `FIdentityGetUserAccountStep(FUniqueNetIdPtr* InUniqueNetId) : UniqueNetId(InUniqueNetId) , StateSaver([](TSharedPtr<FUserOnlineAccount>) {})`
- L19 _public function_ `, StateSaver([](TSharedPtr<FUserOnlineAccount>) {})`
- L22 _public prototype_ `virtual ~FIdentityGetUserAccountStep() = default;`
- L24 _public function_ `virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override`
- L40 _protected member_ `TSharedPtr<FUserOnlineAccount> UserAccount = nullptr;`
- L41 _protected member_ `FUniqueNetIdPtr* UniqueNetId = nullptr;`
- L42 _protected member_ `TFunction<void(TSharedPtr<FUserOnlineAccount>)> StateSaver;`

### `Source/Programs/Online/OSSTestsCore/Helpers/Identity/IdentityGetUserPrivilegeHelper.h` (Other)


#### struct `FIdentityGetUserPrivilegeStep`  
`struct FIdentityGetUserPrivilegeStep : public FTestPipeline::FStep`  
_L10-53_
- inherits: `FTestPipeline::FStep`
- L12 _public function_ `FIdentityGetUserPrivilegeStep(FUniqueNetIdPtr* InUserId, EUserPrivileges::Type InPrivilege) : UserId(InUserId) , Privilege(InPrivilege)`
- L17 _public prototype_ `virtual ~FIdentityGetUserPrivilegeStep() = default;`
- L19 _public member_ `enum class EState { CallGetUserPrivilege, Done } State = EState::CallGetUserPrivilege;`
- L21 _public function_ `virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override`
- L51 _protected member_ `FUniqueNetIdPtr* UserId = nullptr;`
- L52 _protected member_ `EUserPrivileges::Type Privilege = EUserPrivileges::Type::CanUseUserGeneratedContent;`

#### enum `FIdentityGetUserPrivilegeStep::EState`  
`enum class EState`  
_L19-19_
- L19 _public enumerator_ `enum class EState { CallGetUserPrivilege, Done } State = EState::CallGetUserPrivilege; virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override { switch (State) { case EState::CallGetUserPrivilege: {`
- L19 _public enumerator_ `enum class EState { CallGetUserPrivilege, Done } State = EState::CallGetUserPrivilege; virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override { switch (State) { case EState::CallGetUserPrivilege: {`

#### Free symbols / members of external scopes

- L30 _function_ `` (scope `FIdentityGetUserPrivilegeStep::Tick`)

### `Source/Programs/Online/OSSTestsCore/Helpers/Identity/IdentityLoginHelper.h` (Other)


#### struct `FIdentityLoginStep`  
`struct FIdentityLoginStep : public FTestPipeline::FStep`  
_L10-88_
- inherits: `FTestPipeline::FStep`
- L12 _public function_ `FIdentityLoginStep(int32 InLocalUserNum, const FOnlineAccountCredentials& InLocalAccount) : LocalUserNum(InLocalUserNum) , LocalAccount(InLocalAccount)`
- L17 _public function_ `virtual ~FIdentityLoginStep()`
- L29 _public member_ `enum class EState { Init, LoginCall, LoginCalled, ClearDelegates, Done } State = EState::Init;`
- L31 _public member_ `FOnLoginCompleteDelegate LoginDelegate = FOnLoginCompleteDelegate::CreateLambda([this](int32 LoginLocalUserNum, bool bLoginWasSuccessful, const FUniqueNetId& LoginUserId, const FString& LoginError) { CHECK(State == EState::LoginCalled); CHECK(bLoginWasSuccessful); CHECK(LoginLocalUserNum == LocalUserNum); State = EState::ClearDelegates; });`
- L32 _public function_ ``
- L40 _public function_ `virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override`
- L84 _protected member_ `int32 LocalUserNum = 0;`
- L85 _protected member_ `FOnlineAccountCredentials LocalAccount = {};`
- L86 _protected member_ `IOnlineIdentityPtr OnlineIdentityPtr = nullptr;`
- L87 _protected member_ `FDelegateHandle OnLoginCompleteDelegateHandle;`

#### enum `FIdentityLoginStep::EState`  
`enum class EState`  
_L29-29_
- L29 _public enumerator_ `enum class EState { Init, LoginCall, LoginCalled, ClearDelegates, Done } State = EState::Init; FOnLoginCompleteDelegate LoginDelegate = FOnLoginCompleteDelegate::CreateLambda([this](int32 LoginLocalUserNum, bool bLoginWasSuccessful, const FUniqueNetId& LoginUserId, const FString& LoginError) { CHECK(State == EState::LoginCalled); CHECK(bLoginWasSuccessful); CHECK(LoginLocalUserNum == LocalUserNum);`
- L29 _public enumerator_ `enum class EState { Init, LoginCall, LoginCalled, ClearDelegates, Done } State = EState::Init; FOnLoginCompleteDelegate LoginDelegate = FOnLoginCompleteDelegate::CreateLambda([this](int32 LoginLocalUserNum, bool bLoginWasSuccessful, const FUniqueNetId& LoginUserId, const FString& LoginError) { CHECK(State == EState::LoginCalled); CHECK(bLoginWasSuccessful); CHECK(LoginLocalUserNum == LocalUserNum);`
- L29 _public enumerator_ `enum class EState { Init, LoginCall, LoginCalled, ClearDelegates, Done } State = EState::Init; FOnLoginCompleteDelegate LoginDelegate = FOnLoginCompleteDelegate::CreateLambda([this](int32 LoginLocalUserNum, bool bLoginWasSuccessful, const FUniqueNetId& LoginUserId, const FString& LoginError) { CHECK(State == EState::LoginCalled); CHECK(bLoginWasSuccessful); CHECK(LoginLocalUserNum == LocalUserNum);`
- L29 _public enumerator_ `enum class EState { Init, LoginCall, LoginCalled, ClearDelegates, Done } State = EState::Init; FOnLoginCompleteDelegate LoginDelegate = FOnLoginCompleteDelegate::CreateLambda([this](int32 LoginLocalUserNum, bool bLoginWasSuccessful, const FUniqueNetId& LoginUserId, const FString& LoginError) { CHECK(State == EState::LoginCalled); CHECK(bLoginWasSuccessful); CHECK(LoginLocalUserNum == LocalUserNum);`
- L29 _public enumerator_ `enum class EState { Init, LoginCall, LoginCalled, ClearDelegates, Done } State = EState::Init; FOnLoginCompleteDelegate LoginDelegate = FOnLoginCompleteDelegate::CreateLambda([this](int32 LoginLocalUserNum, bool bLoginWasSuccessful, const FUniqueNetId& LoginUserId, const FString& LoginError) { CHECK(State == EState::LoginCalled); CHECK(bLoginWasSuccessful); CHECK(LoginLocalUserNum == LocalUserNum);`

### `Source/Programs/Online/OSSTestsCore/Helpers/Identity/IdentityLogoutHelper.h` (Other)


#### struct `FIdentityLogoutStep`  
`struct FIdentityLogoutStep : public FTestPipeline::FStep`  
_L11-88_
- inherits: `FTestPipeline::FStep`
- L13 _public function_ `FIdentityLogoutStep(int32 InLocalUserNum) : LocalUserNum(InLocalUserNum)`
- L17 _public function_ `virtual ~FIdentityLogoutStep()`
- L29 _public member_ `enum class EState { Init, LogoutCall, LogoutCalled, ClearDelegates, Done } State = EState::Init;`
- L31 _public member_ `FOnLogoutCompleteDelegate LogoutDelegate = FOnLogoutCompleteDelegate::CreateLambda([this](int32 LogoutLocalUserNum, bool bLogoutWasSuccessful) { CHECK(State == EState::LogoutCalled); CHECK(bLogoutWasSuccessful); CHECK(LogoutLocalUserNum == LocalUserNum); State = EState::ClearDelegates; });`
- L32 _public function_ ``
- L41 _public function_ `virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override`
- L85 _protected member_ `int32 LocalUserNum = 0;`
- L86 _protected member_ `IOnlineIdentityPtr OnlineIdentityPtr = nullptr;`
- L87 _protected member_ `FDelegateHandle OnLogoutCompleteDelegateHandle;`

#### enum `FIdentityLogoutStep::EState`  
`enum class EState`  
_L29-29_
- L29 _public enumerator_ `enum class EState { Init, LogoutCall, LogoutCalled, ClearDelegates, Done } State = EState::Init; FOnLogoutCompleteDelegate LogoutDelegate = FOnLogoutCompleteDelegate::CreateLambda([this](int32 LogoutLocalUserNum, bool bLogoutWasSuccessful) { CHECK(State == EState::LogoutCalled); CHECK(bLogoutWasSuccessful); CHECK(LogoutLocalUserNum == LocalUserNum);`
- L29 _public enumerator_ `enum class EState { Init, LogoutCall, LogoutCalled, ClearDelegates, Done } State = EState::Init; FOnLogoutCompleteDelegate LogoutDelegate = FOnLogoutCompleteDelegate::CreateLambda([this](int32 LogoutLocalUserNum, bool bLogoutWasSuccessful) { CHECK(State == EState::LogoutCalled); CHECK(bLogoutWasSuccessful); CHECK(LogoutLocalUserNum == LocalUserNum);`
- L29 _public enumerator_ `enum class EState { Init, LogoutCall, LogoutCalled, ClearDelegates, Done } State = EState::Init; FOnLogoutCompleteDelegate LogoutDelegate = FOnLogoutCompleteDelegate::CreateLambda([this](int32 LogoutLocalUserNum, bool bLogoutWasSuccessful) { CHECK(State == EState::LogoutCalled); CHECK(bLogoutWasSuccessful); CHECK(LogoutLocalUserNum == LocalUserNum);`
- L29 _public enumerator_ `enum class EState { Init, LogoutCall, LogoutCalled, ClearDelegates, Done } State = EState::Init; FOnLogoutCompleteDelegate LogoutDelegate = FOnLogoutCompleteDelegate::CreateLambda([this](int32 LogoutLocalUserNum, bool bLogoutWasSuccessful) { CHECK(State == EState::LogoutCalled); CHECK(bLogoutWasSuccessful); CHECK(LogoutLocalUserNum == LocalUserNum);`
- L29 _public enumerator_ `enum class EState { Init, LogoutCall, LogoutCalled, ClearDelegates, Done } State = EState::Init; FOnLogoutCompleteDelegate LogoutDelegate = FOnLogoutCompleteDelegate::CreateLambda([this](int32 LogoutLocalUserNum, bool bLogoutWasSuccessful) { CHECK(State == EState::LogoutCalled); CHECK(bLogoutWasSuccessful); CHECK(LogoutLocalUserNum == LocalUserNum);`

### `Source/Programs/Online/OSSTestsCore/Helpers/Identity/IdentityRevokeAuthTokenHelper.h` (Other)


#### struct `FIdentityRevokeAuthTokenStep`  
`struct FIdentityRevokeAuthTokenStep : public FTestPipeline::FStep`  
_L11-49_
- inherits: `FTestPipeline::FStep`
- L13 _public function_ `FIdentityRevokeAuthTokenStep(FUniqueNetIdPtr* InLocalUserId) : UserId(InLocalUserId)`
- L17 _public prototype_ `virtual ~FIdentityRevokeAuthTokenStep() = default;`
- L19 _public member_ `enum class EState { CallRevokeUserToken, Done } State = EState::CallRevokeUserToken;`
- L21 _public function_ `virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override`
- L48 _protected member_ `FUniqueNetIdPtr* UserId = nullptr;`

#### enum `FIdentityRevokeAuthTokenStep::EState`  
`enum class EState`  
_L19-19_
- L19 _public enumerator_ `enum class EState { CallRevokeUserToken, Done } State = EState::CallRevokeUserToken; virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override { switch (State) { case EState::CallRevokeUserToken: {`
- L19 _public enumerator_ `enum class EState { CallRevokeUserToken, Done } State = EState::CallRevokeUserToken; virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override { switch (State) { case EState::CallRevokeUserToken: {`

#### Free symbols / members of external scopes

- L30 _function_ `` (scope `FIdentityRevokeAuthTokenStep::Tick`)

### `Source/Programs/Online/OSSTestsCore/Helpers/Identity/McpIdentity/McpIdentityCreateAccountHelper.h` (Other)


#### struct `FMcpIdentityCreateAccountStep`  
`struct FMcpIdentityCreateAccountStep : public FTestPipeline::FStep`  
_L10-87_
- inherits: `FTestPipeline::FStep`
- L12 _public function_ `FMcpIdentityCreateAccountStep(int32 InLocalUserNum, const FCreateAccountInfoMcp& InAccountInfo, TFunction<void(FOnlineAccountCredentials)>&& InStateSaver) : LocalUserNum(InLocalUserNum) , AccountInfo(InAccountInfo) , StateSaver(MoveTemp(InStateSaver))`
- L18 _public function_ `FMcpIdentityCreateAccountStep(int32 InLocalUserNum, const FCreateAccountInfoMcp& InAccountInfo) : LocalUserNum(InLocalUserNum) , AccountInfo(InAccountInfo) , StateSaver([](FOnlineAccountCredentials) {})`
- L21 _public function_ `, StateSaver([](FOnlineAccountCredentials) {})`
- L24 _public function_ `virtual ~FMcpIdentityCreateAccountStep()`
- L32 _public member_ `enum class EState { CreateAccount, Called, Done } State = EState::CreateAccount;`
- L34 _public member_ `FOnCreateAccountCompleteDelegate OnCreateAccountCompleteDelegate = FOnCreateAccountCompleteDelegate::CreateLambda([this](const FUniqueNetId& UserId, const FOnlineAccountCredentials& Credentials, const FOnlineError& Error) { REQUIRE(State == EState::Called); REQUIRE(Error.WasSuccessful()); TestCredentials = Credentials; StateSaver(TestCredentials); State = EState::Done; });`
- L35 _public function_ ``
- L45 _public function_ `virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override`
- L80 _protected member_ `int32 LocalUserNum = 0;`
- L81 _protected member_ `FOnlineSubsystemMcp* OnlineSubsystemMcp = nullptr;`
- L82 _protected member_ `FCreateAccountInfoMcp AccountInfo = {};`
- L83 _protected member_ `FOnlineAccountCredentials TestCredentials = {};`
- L84 _protected member_ `FOnlineIdentityMcpPtr OnlineIdentityMcp = nullptr;`
- L85 _protected member_ `FDelegateHandle OnCreateAccountCompleteDelegateHandle;`
- L86 _protected member_ `TFunction<void(FOnlineAccountCredentials)> StateSaver;`

#### enum `FMcpIdentityCreateAccountStep::EState`  
`enum class EState`  
_L32-32_
- L32 _public enumerator_ `enum class EState { CreateAccount, Called, Done } State = EState::CreateAccount; FOnCreateAccountCompleteDelegate OnCreateAccountCompleteDelegate = FOnCreateAccountCompleteDelegate::CreateLambda([this](const FUniqueNetId& UserId, const FOnlineAccountCredentials& Credentials, const FOnlineError& Error) { REQUIRE(State == EState::Called); REQUIRE(Error.WasSuccessful()); TestCredentials = Credentials;`
- L32 _public enumerator_ `enum class EState { CreateAccount, Called, Done } State = EState::CreateAccount; FOnCreateAccountCompleteDelegate OnCreateAccountCompleteDelegate = FOnCreateAccountCompleteDelegate::CreateLambda([this](const FUniqueNetId& UserId, const FOnlineAccountCredentials& Credentials, const FOnlineError& Error) { REQUIRE(State == EState::Called); REQUIRE(Error.WasSuccessful()); TestCredentials = Credentials;`
- L32 _public enumerator_ `enum class EState { CreateAccount, Called, Done } State = EState::CreateAccount; FOnCreateAccountCompleteDelegate OnCreateAccountCompleteDelegate = FOnCreateAccountCompleteDelegate::CreateLambda([this](const FUniqueNetId& UserId, const FOnlineAccountCredentials& Credentials, const FOnlineError& Error) { REQUIRE(State == EState::Called); REQUIRE(Error.WasSuccessful()); TestCredentials = Credentials;`

### `Source/Programs/Online/OSSTestsCore/Helpers/InnerStepBuilder.h` (Other)


#### struct `TInnerStepArrayBuilder`  
`template<typename TBaseInnerStep> struct TInnerStepArrayBuilder`  
_L6-19_
- L8 _public function_ `TInnerStepArrayBuilder()`
- L12 _public function_ `template<typename T, typename... TArguments> TInnerStepArrayBuilder&& EmplaceInnerStep(TArguments&&... Args)`
- L18 _public member_ `TArray<TUniquePtr<TBaseInnerStep>> Steps;`

### `Source/Programs/Online/OSSTestsCore/Helpers/Leaderboards/LeaderboardsFlushLeaderboardsHelper.h` (Other)


#### struct `FLeaderboardsFlushLeaderboardsStep`  
`struct FLeaderboardsFlushLeaderboardsStep : public FTestPipeline::FStep`  
_L10-89_
- inherits: `FTestPipeline::FStep`
- L12 _public function_ `FLeaderboardsFlushLeaderboardsStep(FName& InSessionName) : SessionName(InSessionName)`
- L16 _public function_ `virtual ~FLeaderboardsFlushLeaderboardsStep()`
- L28 _public member_ `enum class EState { Init, FlushLeaderboardsCall, FlushLeaderboardsCalled, ClearDelegates, Done } State = EState::Init;`
- L30 _public member_ `FOnLeaderboardFlushCompleteDelegate FlushDelegate = FOnLeaderboardFlushCompleteDelegate::CreateLambda([this](const FName& InSessionName, bool bFlushWasSuccessful) { CHECK(State == EState::FlushLeaderboardsCalled); CHECK(bFlushWasSuccessful); CHECK(InSessionName == SessionName); State = EState::ClearDelegates; });`
- L31 _public function_ ``
- L39 _public function_ `virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override`
- L84 _protected member_ `IOnlineLeaderboardsPtr OnlineLeaderboardsPtr;`
- L85 _protected member_ `FName SessionName;`
- L86 _protected member_ `FUniqueNetIdPtr* PlayerId = nullptr;`
- L87 _protected member_ `FOnlineLeaderboardWrite WriteObject;`
- L88 _protected member_ `FDelegateHandle OnFlushCompleteDelegateHandle;`

#### enum `FLeaderboardsFlushLeaderboardsStep::EState`  
`enum class EState`  
_L28-28_
- L28 _public enumerator_ `enum class EState { Init, FlushLeaderboardsCall, FlushLeaderboardsCalled, ClearDelegates, Done } State = EState::Init; FOnLeaderboardFlushCompleteDelegate FlushDelegate = FOnLeaderboardFlushCompleteDelegate::CreateLambda([this](const FName& InSessionName, bool bFlushWasSuccessful) { CHECK(State == EState::FlushLeaderboardsCalled); CHECK(bFlushWasSuccessful); CHECK(InSessionName == SessionName);`
- L28 _public enumerator_ `enum class EState { Init, FlushLeaderboardsCall, FlushLeaderboardsCalled, ClearDelegates, Done } State = EState::Init; FOnLeaderboardFlushCompleteDelegate FlushDelegate = FOnLeaderboardFlushCompleteDelegate::CreateLambda([this](const FName& InSessionName, bool bFlushWasSuccessful) { CHECK(State == EState::FlushLeaderboardsCalled); CHECK(bFlushWasSuccessful); CHECK(InSessionName == SessionName);`
- L28 _public enumerator_ `enum class EState { Init, FlushLeaderboardsCall, FlushLeaderboardsCalled, ClearDelegates, Done } State = EState::Init; FOnLeaderboardFlushCompleteDelegate FlushDelegate = FOnLeaderboardFlushCompleteDelegate::CreateLambda([this](const FName& InSessionName, bool bFlushWasSuccessful) { CHECK(State == EState::FlushLeaderboardsCalled); CHECK(bFlushWasSuccessful); CHECK(InSessionName == SessionName);`
- L28 _public enumerator_ `enum class EState { Init, FlushLeaderboardsCall, FlushLeaderboardsCalled, ClearDelegates, Done } State = EState::Init; FOnLeaderboardFlushCompleteDelegate FlushDelegate = FOnLeaderboardFlushCompleteDelegate::CreateLambda([this](const FName& InSessionName, bool bFlushWasSuccessful) { CHECK(State == EState::FlushLeaderboardsCalled); CHECK(bFlushWasSuccessful); CHECK(InSessionName == SessionName);`
- L28 _public enumerator_ `enum class EState { Init, FlushLeaderboardsCall, FlushLeaderboardsCalled, ClearDelegates, Done } State = EState::Init; FOnLeaderboardFlushCompleteDelegate FlushDelegate = FOnLeaderboardFlushCompleteDelegate::CreateLambda([this](const FName& InSessionName, bool bFlushWasSuccessful) { CHECK(State == EState::FlushLeaderboardsCalled); CHECK(bFlushWasSuccessful); CHECK(InSessionName == SessionName);`

### `Source/Programs/Online/OSSTestsCore/Helpers/Leaderboards/LeaderboardsReadLeaderboardsForFriendsHelper.h` (Other)


#### struct `FLeaderboardsReadLeaderboardsForFriendsStep`  
`struct FLeaderboardsReadLeaderboardsForFriendsStep : public FTestPipeline::FStep`  
_L10-77_
- inherits: `FTestPipeline::FStep`
- L12 _public function_ `FLeaderboardsReadLeaderboardsForFriendsStep(int32 InLocalUserNum, FOnlineLeaderboardReadRef& InReadObject) : ReadObject(InReadObject) , LocalUserNum(InLocalUserNum)`
- L17 _public prototype_ `virtual ~FLeaderboardsReadLeaderboardsForFriendsStep() = default;`
- L19 _public member_ `enum class EState { Init, ReadLeaderboardsForFriendsCall, ReadLeaderboardsForFriendsCalled, ClearDelegates, Done } State = EState::Init;`
- L21 _public member_ `FOnLeaderboardReadCompleteDelegate ReadDelegate = FOnLeaderboardReadCompleteDelegate::CreateLambda([this](bool bReadWasSuccessful) { CHECK(State == EState::ReadLeaderboardsForFriendsCalled); CHECK(bReadWasSuccessful); State = EState::ClearDelegates; });`
- L22 _public function_ ``
- L29 _public function_ `virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override`
- L73 _protected member_ `IOnlineLeaderboardsPtr OnlineLeaderboardsPtr;`
- L74 _protected member_ `FOnlineLeaderboardReadRef ReadObject;`
- L75 _protected member_ `FDelegateHandle OnReadCompleteDelegateHandle;`
- L76 _protected member_ `int32 LocalUserNum;`

#### enum `FLeaderboardsReadLeaderboardsForFriendsStep::EState`  
`enum class EState`  
_L19-19_
- L19 _public enumerator_ `enum class EState { Init, ReadLeaderboardsForFriendsCall, ReadLeaderboardsForFriendsCalled, ClearDelegates, Done } State = EState::Init; FOnLeaderboardReadCompleteDelegate ReadDelegate = FOnLeaderboardReadCompleteDelegate::CreateLambda([this](bool bReadWasSuccessful) { CHECK(State == EState::ReadLeaderboardsForFriendsCalled); CHECK(bReadWasSuccessful); State = EState::ClearDelegates;`
- L19 _public enumerator_ `enum class EState { Init, ReadLeaderboardsForFriendsCall, ReadLeaderboardsForFriendsCalled, ClearDelegates, Done } State = EState::Init; FOnLeaderboardReadCompleteDelegate ReadDelegate = FOnLeaderboardReadCompleteDelegate::CreateLambda([this](bool bReadWasSuccessful) { CHECK(State == EState::ReadLeaderboardsForFriendsCalled); CHECK(bReadWasSuccessful); State = EState::ClearDelegates;`
- L19 _public enumerator_ `enum class EState { Init, ReadLeaderboardsForFriendsCall, ReadLeaderboardsForFriendsCalled, ClearDelegates, Done } State = EState::Init; FOnLeaderboardReadCompleteDelegate ReadDelegate = FOnLeaderboardReadCompleteDelegate::CreateLambda([this](bool bReadWasSuccessful) { CHECK(State == EState::ReadLeaderboardsForFriendsCalled); CHECK(bReadWasSuccessful); State = EState::ClearDelegates;`
- L19 _public enumerator_ `enum class EState { Init, ReadLeaderboardsForFriendsCall, ReadLeaderboardsForFriendsCalled, ClearDelegates, Done } State = EState::Init; FOnLeaderboardReadCompleteDelegate ReadDelegate = FOnLeaderboardReadCompleteDelegate::CreateLambda([this](bool bReadWasSuccessful) { CHECK(State == EState::ReadLeaderboardsForFriendsCalled); CHECK(bReadWasSuccessful); State = EState::ClearDelegates;`
- L19 _public enumerator_ `enum class EState { Init, ReadLeaderboardsForFriendsCall, ReadLeaderboardsForFriendsCalled, ClearDelegates, Done } State = EState::Init; FOnLeaderboardReadCompleteDelegate ReadDelegate = FOnLeaderboardReadCompleteDelegate::CreateLambda([this](bool bReadWasSuccessful) { CHECK(State == EState::ReadLeaderboardsForFriendsCalled); CHECK(bReadWasSuccessful); State = EState::ClearDelegates;`

### `Source/Programs/Online/OSSTestsCore/Helpers/Leaderboards/LeaderboardsReadLeaderboardsHelper.h` (Other)


#### struct `FLeaderboardsReadLeaderboardsStep`  
`struct FLeaderboardsReadLeaderboardsStep : public FTestPipeline::FStep`  
_L10-93_
- inherits: `FTestPipeline::FStep`
- L12 _public function_ `FLeaderboardsReadLeaderboardsStep(TArray<FUniqueNetIdRef>& InPlayers, FOnlineLeaderboardReadRef& InReadObject, TFunction<void(TArray<FUniqueNetIdRef>&)>&& InStateSaver) : ReadObject(InReadObject) , Players(InPlayers) , StateSaver(MoveTemp(InStateSaver))`
- L18 _public function_ `FLeaderboardsReadLeaderboardsStep(TArray<FUniqueNetIdRef>& InPlayers, FOnlineLeaderboardReadRef& InReadObject) : ReadObject(InReadObject) , Players(InPlayers) , StateSaver([](TArray<FUniqueNetIdRef>&) {})`
- L21 _public function_ `, StateSaver([](TArray<FUniqueNetIdRef>&) {})`
- L24 _public function_ `virtual ~FLeaderboardsReadLeaderboardsStep()`
- L33 _public member_ `enum class EState { Init, ReadLeaderboardsCall, ReadLeaderboardsCalled, ClearDelegates, Done } State = EState::Init;`
- L35 _public member_ `FOnLeaderboardReadCompleteDelegate ReadDelegate = FOnLeaderboardReadCompleteDelegate::CreateLambda([this](bool bReadhWasSuccessful) { CHECK(State == EState::ReadLeaderboardsCalled); CHECK(bReadhWasSuccessful); State = EState::ClearDelegates; });`
- L36 _public function_ ``
- L43 _public function_ `virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override`
- L88 _protected member_ `IOnlineLeaderboardsPtr OnlineLeaderboardsPtr;`
- L89 _protected member_ `FOnlineLeaderboardReadRef ReadObject;`
- L90 _protected member_ `TArray<FUniqueNetIdRef> Players;`
- L91 _protected member_ `TFunction<void(TArray<FUniqueNetIdRef>&)> StateSaver;`
- L92 _protected member_ `FDelegateHandle OnReadCompleteDelegateHandle;`

#### enum `FLeaderboardsReadLeaderboardsStep::EState`  
`enum class EState`  
_L33-33_
- L33 _public enumerator_ `enum class EState { Init, ReadLeaderboardsCall, ReadLeaderboardsCalled, ClearDelegates, Done } State = EState::Init; FOnLeaderboardReadCompleteDelegate ReadDelegate = FOnLeaderboardReadCompleteDelegate::CreateLambda([this](bool bReadhWasSuccessful) { CHECK(State == EState::ReadLeaderboardsCalled); CHECK(bReadhWasSuccessful); State = EState::ClearDelegates;`
- L33 _public enumerator_ `enum class EState { Init, ReadLeaderboardsCall, ReadLeaderboardsCalled, ClearDelegates, Done } State = EState::Init; FOnLeaderboardReadCompleteDelegate ReadDelegate = FOnLeaderboardReadCompleteDelegate::CreateLambda([this](bool bReadhWasSuccessful) { CHECK(State == EState::ReadLeaderboardsCalled); CHECK(bReadhWasSuccessful); State = EState::ClearDelegates;`
- L33 _public enumerator_ `enum class EState { Init, ReadLeaderboardsCall, ReadLeaderboardsCalled, ClearDelegates, Done } State = EState::Init; FOnLeaderboardReadCompleteDelegate ReadDelegate = FOnLeaderboardReadCompleteDelegate::CreateLambda([this](bool bReadhWasSuccessful) { CHECK(State == EState::ReadLeaderboardsCalled); CHECK(bReadhWasSuccessful); State = EState::ClearDelegates;`
- L33 _public enumerator_ `enum class EState { Init, ReadLeaderboardsCall, ReadLeaderboardsCalled, ClearDelegates, Done } State = EState::Init; FOnLeaderboardReadCompleteDelegate ReadDelegate = FOnLeaderboardReadCompleteDelegate::CreateLambda([this](bool bReadhWasSuccessful) { CHECK(State == EState::ReadLeaderboardsCalled); CHECK(bReadhWasSuccessful); State = EState::ClearDelegates;`
- L33 _public enumerator_ `enum class EState { Init, ReadLeaderboardsCall, ReadLeaderboardsCalled, ClearDelegates, Done } State = EState::Init; FOnLeaderboardReadCompleteDelegate ReadDelegate = FOnLeaderboardReadCompleteDelegate::CreateLambda([this](bool bReadhWasSuccessful) { CHECK(State == EState::ReadLeaderboardsCalled); CHECK(bReadhWasSuccessful); State = EState::ClearDelegates;`

### `Source/Programs/Online/OSSTestsCore/Helpers/Leaderboards/LeaderboardsWriteLeaderboardsHelper.h` (Other)


#### struct `FLeaderboardsWriteLeaderboardsStep`  
`struct FLeaderboardsWriteLeaderboardsStep : public FTestPipeline::FStep`  
_L10-61_
- inherits: `FTestPipeline::FStep`
- L12 _public function_ `FLeaderboardsWriteLeaderboardsStep(FName& InSessionName, FUniqueNetIdPtr* InPlayerId, FOnlineLeaderboardWrite& InWriteObject) : SessionName(InSessionName) , PlayerId(InPlayerId) , WriteObject(InWriteObject)`
- L18 _public prototype_ `virtual ~FLeaderboardsWriteLeaderboardsStep() = default;`
- L20 _public member_ `enum class EState { Init, WriteLeaderboardsCall, WriteLeaderboardsCalled, Done } State = EState::Init;`
- L22 _public function_ `virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override`
- L57 _protected member_ `IOnlineLeaderboardsPtr OnlineLeaderboardsPtr;`
- L58 _protected member_ `FName SessionName;`
- L59 _protected member_ `FUniqueNetIdPtr* PlayerId = nullptr;`
- L60 _protected member_ `FOnlineLeaderboardWrite WriteObject;`

#### enum `FLeaderboardsWriteLeaderboardsStep::EState`  
`enum class EState`  
_L20-20_
- L20 _public enumerator_ `enum class EState { Init, WriteLeaderboardsCall, WriteLeaderboardsCalled, Done } State = EState::Init; virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override { switch (State) { case EState::Init: {`
- L20 _public enumerator_ `enum class EState { Init, WriteLeaderboardsCall, WriteLeaderboardsCalled, Done } State = EState::Init; virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override { switch (State) { case EState::Init: {`
- L20 _public enumerator_ `enum class EState { Init, WriteLeaderboardsCall, WriteLeaderboardsCalled, Done } State = EState::Init; virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override { switch (State) { case EState::Init: {`
- L20 _public enumerator_ `enum class EState { Init, WriteLeaderboardsCall, WriteLeaderboardsCalled, Done } State = EState::Init; virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override { switch (State) { case EState::Init: {`

### `Source/Programs/Online/OSSTestsCore/Helpers/Purchase/PurchaseCheckoutHelper.h` (Other)


#### struct `FPurchaseCheckoutStep`  
`struct FPurchaseCheckoutStep : public FTestPipeline::FStep`  
_L11-82_
- inherits: `FTestPipeline::FStep`
- L13 _public function_ `FPurchaseCheckoutStep(FUniqueNetIdPtr* InUserId, FPurchaseCheckoutRequest* InCheckoutRequest, const FString& InUniqueId, const FString& InItemName) : UserId(InUserId) , CheckoutRequest(InCheckoutRequest) , UniqueId(InUniqueId) , ItemName(InItemName)`
- L20 _public prototype_ `virtual ~FPurchaseCheckoutStep() = default;`
- L22 _public member_ `enum class EState { Init, CheckoutCall, CheckoutCalled, FinalizePurchaseCall, FinalizePurchaseCalled, Done } State = EState::Init;`
- L24 _public member_ `FOnPurchaseCheckoutComplete CheckoutDelegate = FOnPurchaseCheckoutComplete::CreateLambda([this](const FOnlineError& Result, const TSharedRef<FPurchaseReceipt>& Receipt) { CHECK(State == EState::CheckoutCall); CHECK(Result.bSucceeded == true); CHECK(Receipt->ReceiptOffers[0].LineItems[0].UniqueId == UniqueId); CHECK(Receipt->ReceiptOffers[0].LineItems[0].ItemName == ItemName); State = EState::FinalizePurchaseCall; });`
- L25 _public function_ ``
- L34 _public function_ `virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override`
- L77 _protected member_ `FUniqueNetIdPtr* UserId = nullptr;`
- L78 _protected member_ `IOnlinePurchasePtr OnlinePurchasePtr = nullptr;`
- L79 _protected member_ `FPurchaseCheckoutRequest* CheckoutRequest = nullptr;`
- L80 _protected member_ `FString UniqueId;`
- L81 _protected member_ `FString ItemName;`

#### enum `FPurchaseCheckoutStep::EState`  
`enum class EState`  
_L22-22_
- L22 _public enumerator_ `enum class EState { Init, CheckoutCall, CheckoutCalled, FinalizePurchaseCall, FinalizePurchaseCalled, Done } State = EState::Init; FOnPurchaseCheckoutComplete CheckoutDelegate = FOnPurchaseCheckoutComplete::CreateLambda([this](const FOnlineError& Result, const TSharedRef<FPurchaseReceipt>& Receipt) { CHECK(State == EState::CheckoutCall); CHECK(Result.bSucceeded == true); CHECK(Receipt->ReceiptOffers[0].LineItems[0].UniqueId == UniqueId);`
- L22 _public enumerator_ `enum class EState { Init, CheckoutCall, CheckoutCalled, FinalizePurchaseCall, FinalizePurchaseCalled, Done } State = EState::Init; FOnPurchaseCheckoutComplete CheckoutDelegate = FOnPurchaseCheckoutComplete::CreateLambda([this](const FOnlineError& Result, const TSharedRef<FPurchaseReceipt>& Receipt) { CHECK(State == EState::CheckoutCall); CHECK(Result.bSucceeded == true); CHECK(Receipt->ReceiptOffers[0].LineItems[0].UniqueId == UniqueId);`
- L22 _public enumerator_ `enum class EState { Init, CheckoutCall, CheckoutCalled, FinalizePurchaseCall, FinalizePurchaseCalled, Done } State = EState::Init; FOnPurchaseCheckoutComplete CheckoutDelegate = FOnPurchaseCheckoutComplete::CreateLambda([this](const FOnlineError& Result, const TSharedRef<FPurchaseReceipt>& Receipt) { CHECK(State == EState::CheckoutCall); CHECK(Result.bSucceeded == true); CHECK(Receipt->ReceiptOffers[0].LineItems[0].UniqueId == UniqueId);`
- L22 _public enumerator_ `enum class EState { Init, CheckoutCall, CheckoutCalled, FinalizePurchaseCall, FinalizePurchaseCalled, Done } State = EState::Init; FOnPurchaseCheckoutComplete CheckoutDelegate = FOnPurchaseCheckoutComplete::CreateLambda([this](const FOnlineError& Result, const TSharedRef<FPurchaseReceipt>& Receipt) { CHECK(State == EState::CheckoutCall); CHECK(Result.bSucceeded == true); CHECK(Receipt->ReceiptOffers[0].LineItems[0].UniqueId == UniqueId);`
- L22 _public enumerator_ `enum class EState { Init, CheckoutCall, CheckoutCalled, FinalizePurchaseCall, FinalizePurchaseCalled, Done } State = EState::Init; FOnPurchaseCheckoutComplete CheckoutDelegate = FOnPurchaseCheckoutComplete::CreateLambda([this](const FOnlineError& Result, const TSharedRef<FPurchaseReceipt>& Receipt) { CHECK(State == EState::CheckoutCall); CHECK(Result.bSucceeded == true); CHECK(Receipt->ReceiptOffers[0].LineItems[0].UniqueId == UniqueId);`
- L22 _public enumerator_ `enum class EState { Init, CheckoutCall, CheckoutCalled, FinalizePurchaseCall, FinalizePurchaseCalled, Done } State = EState::Init; FOnPurchaseCheckoutComplete CheckoutDelegate = FOnPurchaseCheckoutComplete::CreateLambda([this](const FOnlineError& Result, const TSharedRef<FPurchaseReceipt>& Receipt) { CHECK(State == EState::CheckoutCall); CHECK(Result.bSucceeded == true); CHECK(Receipt->ReceiptOffers[0].LineItems[0].UniqueId == UniqueId);`

### `Source/Programs/Online/OSSTestsCore/Helpers/Purchase/PurchaseGetReceiptsHelper.h` (Other)


#### struct `FPurchaseGetReceiptsStep`  
`struct FPurchaseGetReceiptsStep : public FTestPipeline::FStep`  
_L11-84_
- inherits: `FTestPipeline::FStep`
- L13 _public function_ `FPurchaseGetReceiptsStep(FUniqueNetIdPtr* InUserId, TFunction<void(TArray<FPurchaseReceipt>*)>&& InStateSaver, const FString& InUniqueId = FString("")) : UserId(InUserId) , StateSaver(MoveTemp(InStateSaver)) , UniqueId(InUniqueId)`
- L20 _public function_ `FPurchaseGetReceiptsStep(FUniqueNetIdPtr* InUserId) : UserId(InUserId) , StateSaver([](TArray<FPurchaseReceipt>*) {})`
- L22 _public function_ `, StateSaver([](TArray<FPurchaseReceipt>*) {})`
- L27 _public prototype_ `virtual ~FPurchaseGetReceiptsStep() = default;`
- L29 _public member_ `enum class EState { Init, GetReceiptsCall, GetReceiptsCalled, FinalizePurchaseCall, FinalizePurchaseCalled, Done } State = EState::Init;`
- L31 _public function_ `virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override`
- L79 _protected member_ `FUniqueNetIdPtr* UserId = nullptr;`
- L80 _protected member_ `TArray<FPurchaseReceipt> OutReceipt = {};`
- L81 _protected member_ `IOnlinePurchasePtr OnlinePurchasePtr = nullptr;`
- L82 _protected member_ `TFunction<void(TArray<FPurchaseReceipt>*)> StateSaver;`
- L83 _protected member_ `FString UniqueId;`

#### enum `FPurchaseGetReceiptsStep::EState`  
`enum class EState`  
_L29-29_
- L29 _public enumerator_ `enum class EState { Init, GetReceiptsCall, GetReceiptsCalled, FinalizePurchaseCall, FinalizePurchaseCalled, Done } State = EState::Init; virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override { switch (State) { case EState::Init: {`
- L29 _public enumerator_ `enum class EState { Init, GetReceiptsCall, GetReceiptsCalled, FinalizePurchaseCall, FinalizePurchaseCalled, Done } State = EState::Init; virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override { switch (State) { case EState::Init: {`
- L29 _public enumerator_ `enum class EState { Init, GetReceiptsCall, GetReceiptsCalled, FinalizePurchaseCall, FinalizePurchaseCalled, Done } State = EState::Init; virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override { switch (State) { case EState::Init: {`
- L29 _public enumerator_ `enum class EState { Init, GetReceiptsCall, GetReceiptsCalled, FinalizePurchaseCall, FinalizePurchaseCalled, Done } State = EState::Init; virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override { switch (State) { case EState::Init: {`
- L29 _public enumerator_ `enum class EState { Init, GetReceiptsCall, GetReceiptsCalled, FinalizePurchaseCall, FinalizePurchaseCalled, Done } State = EState::Init; virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override { switch (State) { case EState::Init: {`
- L29 _public enumerator_ `enum class EState { Init, GetReceiptsCall, GetReceiptsCalled, FinalizePurchaseCall, FinalizePurchaseCalled, Done } State = EState::Init; virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override { switch (State) { case EState::Init: {`

### `Source/Programs/Online/OSSTestsCore/Helpers/Purchase/PurchaseQueryReceiptsHelper.h` (Other)


#### struct `FPurchaseQueryReceiptsStep`  
`struct FPurchaseQueryReceiptsStep : public FTestPipeline::FStep`  
_L11-86_
- inherits: `FTestPipeline::FStep`
- L13 _public function_ `FPurchaseQueryReceiptsStep(FUniqueNetIdPtr* InUserId, const bool& bInRestoreReceipts, const FString& InReceiptId) : UserId(InUserId) , bRestoreReceipts(bInRestoreReceipts) , ReceiptId(InReceiptId)`
- L19 _public function_ `FPurchaseQueryReceiptsStep(FUniqueNetIdPtr* InUserId, const bool& bInRestoreReceipts) : UserId(InUserId) , bRestoreReceipts(bInRestoreReceipts)`
- L25 _public prototype_ `virtual ~FPurchaseQueryReceiptsStep() = default;`
- L27 _public member_ `enum class EState { Init, QueryReceiptsCall, QueryReceiptsCalled, FinalizePurchaseCall, FinalizePurchaseCalled, Done } State = EState::Init;`
- L29 _public member_ `FOnQueryReceiptsComplete QueryReceipts = FOnQueryReceiptsComplete::CreateLambda([this](const FOnlineError& Result) { CHECK(State == EState::QueryReceiptsCalled); CHECK(Result.bSucceeded == true); State = EState::FinalizePurchaseCall; });`
- L30 _public function_ ``
- L37 _public function_ `virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override`
- L82 _protected member_ `FUniqueNetIdPtr* UserId = nullptr;`
- L83 _protected member_ `IOnlinePurchasePtr OnlinePurchasePtr = nullptr;`
- L84 _protected member_ `bool bRestoreReceipts = false;`
- L85 _protected member_ `FString ReceiptId;`

#### enum `FPurchaseQueryReceiptsStep::EState`  
`enum class EState`  
_L27-27_
- L27 _public enumerator_ `enum class EState { Init, QueryReceiptsCall, QueryReceiptsCalled, FinalizePurchaseCall, FinalizePurchaseCalled, Done } State = EState::Init; FOnQueryReceiptsComplete QueryReceipts = FOnQueryReceiptsComplete::CreateLambda([this](const FOnlineError& Result) { CHECK(State == EState::QueryReceiptsCalled); CHECK(Result.bSucceeded == true); State = EState::FinalizePurchaseCall;`
- L27 _public enumerator_ `enum class EState { Init, QueryReceiptsCall, QueryReceiptsCalled, FinalizePurchaseCall, FinalizePurchaseCalled, Done } State = EState::Init; FOnQueryReceiptsComplete QueryReceipts = FOnQueryReceiptsComplete::CreateLambda([this](const FOnlineError& Result) { CHECK(State == EState::QueryReceiptsCalled); CHECK(Result.bSucceeded == true); State = EState::FinalizePurchaseCall;`
- L27 _public enumerator_ `enum class EState { Init, QueryReceiptsCall, QueryReceiptsCalled, FinalizePurchaseCall, FinalizePurchaseCalled, Done } State = EState::Init; FOnQueryReceiptsComplete QueryReceipts = FOnQueryReceiptsComplete::CreateLambda([this](const FOnlineError& Result) { CHECK(State == EState::QueryReceiptsCalled); CHECK(Result.bSucceeded == true); State = EState::FinalizePurchaseCall;`
- L27 _public enumerator_ `enum class EState { Init, QueryReceiptsCall, QueryReceiptsCalled, FinalizePurchaseCall, FinalizePurchaseCalled, Done } State = EState::Init; FOnQueryReceiptsComplete QueryReceipts = FOnQueryReceiptsComplete::CreateLambda([this](const FOnlineError& Result) { CHECK(State == EState::QueryReceiptsCalled); CHECK(Result.bSucceeded == true); State = EState::FinalizePurchaseCall;`
- L27 _public enumerator_ `enum class EState { Init, QueryReceiptsCall, QueryReceiptsCalled, FinalizePurchaseCall, FinalizePurchaseCalled, Done } State = EState::Init; FOnQueryReceiptsComplete QueryReceipts = FOnQueryReceiptsComplete::CreateLambda([this](const FOnlineError& Result) { CHECK(State == EState::QueryReceiptsCalled); CHECK(Result.bSucceeded == true); State = EState::FinalizePurchaseCall;`
- L27 _public enumerator_ `enum class EState { Init, QueryReceiptsCall, QueryReceiptsCalled, FinalizePurchaseCall, FinalizePurchaseCalled, Done } State = EState::Init; FOnQueryReceiptsComplete QueryReceipts = FOnQueryReceiptsComplete::CreateLambda([this](const FOnlineError& Result) { CHECK(State == EState::QueryReceiptsCalled); CHECK(Result.bSucceeded == true); State = EState::FinalizePurchaseCall;`

### `Source/Programs/Online/OSSTestsCore/Helpers/Purchase/PurchaseRedeemCodeHelper.h` (Other)


#### struct `FPurchaseRedeemCodeStep`  
`struct FPurchaseRedeemCodeStep : public FTestPipeline::FStep`  
_L10-72_
- inherits: `FTestPipeline::FStep`
- L12 _public function_ `FPurchaseRedeemCodeStep(FUniqueNetIdPtr* InUserId, const FRedeemCodeRequest& InRedeemCodeRequest, const FString& InUniqueId, const FString& InItemName) : UserId(InUserId) , RedeemCodeRequest(InRedeemCodeRequest) , UniqueId(InUniqueId) , ItemName(InItemName)`
- L19 _public prototype_ `virtual ~FPurchaseRedeemCodeStep() = default;`
- L21 _public member_ `FOnPurchaseRedeemCodeComplete PurchaseRedeemCode = FOnPurchaseRedeemCodeComplete::CreateLambda([this](const FOnlineError& Result, const TSharedRef<FPurchaseReceipt>& Receipt) { CHECK(State == EState::RedeemCodeCall); CHECK(Result.bSucceeded == true); CHECK(Receipt->ReceiptOffers[0].LineItems[0].UniqueId == UniqueId); CHECK(Receipt->ReceiptOffers[0].LineItems[0].ItemName == ItemName); State = EState::RedeemCodeCalled; });`
- L22 _public function_ ``
- L32 _public member_ `enum class EState { Init, RedeemCodeCall,RedeemCodeCalled, Done } State = EState::Init;`
- L34 _public function_ `virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override`
- L67 _protected member_ `FUniqueNetIdPtr* UserId = nullptr;`
- L68 _protected member_ `IOnlinePurchasePtr OnlinePurchasePtr = nullptr;`
- L69 _protected member_ `FRedeemCodeRequest RedeemCodeRequest;`
- L70 _protected member_ `FString UniqueId;`
- L71 _protected member_ `FString ItemName;`

#### enum `FPurchaseRedeemCodeStep::EState`  
`enum class EState`  
_L32-32_
- L32 _public enumerator_ `enum class EState { Init, RedeemCodeCall,RedeemCodeCalled, Done } State = EState::Init; virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override { switch (State) { case EState::Init: {`
- L32 _public enumerator_ `enum class EState { Init, RedeemCodeCall,RedeemCodeCalled, Done } State = EState::Init; virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override { switch (State) { case EState::Init: {`
- L32 _public enumerator_ `enum class EState { Init, RedeemCodeCall,RedeemCodeCalled, Done } State = EState::Init; virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override { switch (State) { case EState::Init: {`
- L32 _public enumerator_ `enum class EState { Init, RedeemCodeCall,RedeemCodeCalled, Done } State = EState::Init; virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override { switch (State) { case EState::Init: {`

### `Source/Programs/Online/OSSTestsCore/Helpers/Session/SessionCancelFindSessionHelper.h` (Other)


#### struct `FSessionCancelFindSessionStep`  
`struct FSessionCancelFindSessionStep : public FTestPipeline::FStep`  
_L10-100_
- inherits: `FTestPipeline::FStep`
- L12 _public function_ `FSessionCancelFindSessionStep(FUniqueNetIdPtr* InSearchingUserId, FUniqueNetIdPtr* InFriendId, const TSharedRef<FOnlineSessionSearch>& InSearchSettings) : SearchingUserId(InSearchingUserId) , FriendId(InFriendId) , SearchSettings(InSearchSettings)`
- L18 _public function_ `virtual ~FSessionCancelFindSessionStep()`
- L30 _public member_ `enum class EState { Init, CancelFindSessionCall, CancelFindSessionCalled, ClearDelegates, Done } State = EState::Init;`
- L32 _public function_ `FOnFindSessionsCompleteDelegate FindSessionsDelegate = FOnFindSessionsCompleteDelegate::CreateLambda([this](bool bWasSuccessful){});`
- L32 _public member_ `FOnFindSessionsCompleteDelegate FindSessionsDelegate = FOnFindSessionsCompleteDelegate::CreateLambda([this](bool bWasSuccessful){});`
- L34 _public member_ `FOnCancelFindSessionsCompleteDelegate CancelFindSessionsDelegate = FOnCancelFindSessionsCompleteDelegate::CreateLambda([this](bool bWasSuccessful) { REQUIRE(State == EState::CancelFindSessionCalled); CHECK(bWasSuccessful); State = EState::ClearDelegates; });`
- L35 _public function_ ``
- L42 _public function_ `virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override`
- L91 _protected member_ `int32 LocalUserNum = 0;`
- L92 _protected member_ `FUniqueNetIdPtr* SearchingUserId = nullptr;`
- L93 _protected member_ `FUniqueNetIdPtr* FriendId = nullptr;`
- L94 _protected member_ `TSharedPtr<FNamedOnlineSession>* NamedOnlineSession = nullptr;`
- L95 _protected member_ `FString SessionKey = TEXT("");`
- L96 _protected member_ `TSharedRef<FOnlineSessionSearch> SearchSettings;`
- L97 _protected member_ `IOnlineSessionPtr OnlineSessionPtr = nullptr;`
- L98 _protected member_ `FDelegateHandle OnFindSessionsCompleteDelegateHandle;`
- L99 _protected member_ `FDelegateHandle OnCancelFindSessionsCompleteDelegateHandle;`

#### enum `FSessionCancelFindSessionStep::EState`  
`enum class EState`  
_L30-30_
- L30 _public enumerator_ `enum class EState { Init, CancelFindSessionCall, CancelFindSessionCalled, ClearDelegates, Done } State = EState::Init; FOnFindSessionsCompleteDelegate FindSessionsDelegate = FOnFindSessionsCompleteDelegate::CreateLambda([this](bool bWasSuccessful){}); FOnCancelFindSessionsCompleteDelegate CancelFindSessionsDelegate = FOnCancelFindSessionsCompleteDelegate::CreateLambda([this](bool bWasSuccessful) { REQUIRE(State == EState::CancelFindSessionCalled); CHECK(bWasSuccessful);`
- L30 _public enumerator_ `enum class EState { Init, CancelFindSessionCall, CancelFindSessionCalled, ClearDelegates, Done } State = EState::Init; FOnFindSessionsCompleteDelegate FindSessionsDelegate = FOnFindSessionsCompleteDelegate::CreateLambda([this](bool bWasSuccessful){}); FOnCancelFindSessionsCompleteDelegate CancelFindSessionsDelegate = FOnCancelFindSessionsCompleteDelegate::CreateLambda([this](bool bWasSuccessful) { REQUIRE(State == EState::CancelFindSessionCalled); CHECK(bWasSuccessful);`
- L30 _public enumerator_ `enum class EState { Init, CancelFindSessionCall, CancelFindSessionCalled, ClearDelegates, Done } State = EState::Init; FOnFindSessionsCompleteDelegate FindSessionsDelegate = FOnFindSessionsCompleteDelegate::CreateLambda([this](bool bWasSuccessful){}); FOnCancelFindSessionsCompleteDelegate CancelFindSessionsDelegate = FOnCancelFindSessionsCompleteDelegate::CreateLambda([this](bool bWasSuccessful) { REQUIRE(State == EState::CancelFindSessionCalled); CHECK(bWasSuccessful);`
- L30 _public enumerator_ `enum class EState { Init, CancelFindSessionCall, CancelFindSessionCalled, ClearDelegates, Done } State = EState::Init; FOnFindSessionsCompleteDelegate FindSessionsDelegate = FOnFindSessionsCompleteDelegate::CreateLambda([this](bool bWasSuccessful){}); FOnCancelFindSessionsCompleteDelegate CancelFindSessionsDelegate = FOnCancelFindSessionsCompleteDelegate::CreateLambda([this](bool bWasSuccessful) { REQUIRE(State == EState::CancelFindSessionCalled); CHECK(bWasSuccessful);`
- L30 _public enumerator_ `enum class EState { Init, CancelFindSessionCall, CancelFindSessionCalled, ClearDelegates, Done } State = EState::Init; FOnFindSessionsCompleteDelegate FindSessionsDelegate = FOnFindSessionsCompleteDelegate::CreateLambda([this](bool bWasSuccessful){}); FOnCancelFindSessionsCompleteDelegate CancelFindSessionsDelegate = FOnCancelFindSessionsCompleteDelegate::CreateLambda([this](bool bWasSuccessful) { REQUIRE(State == EState::CancelFindSessionCalled); CHECK(bWasSuccessful);`

### `Source/Programs/Online/OSSTestsCore/Helpers/Session/SessionCreateSessionHelper.h` (Other)


#### struct `FSessionCreateSessionStep`  
`struct FSessionCreateSessionStep : public FTestPipeline::FStep`  
_L11-115_
- inherits: `FTestPipeline::FStep`
- L13 _public function_ `FSessionCreateSessionStep(FUniqueNetIdPtr* InLocalUserId, FName InSessionName, const FOnlineSessionSettings& InNewSessionSettings, TFunction<void(TSharedPtr<FNamedOnlineSession>)>&& InStateSaver = [](TSharedPtr<FNamedOnlineSession>){}) : LocalUserId(InLocalUserId) , TestSessionName(InSessionName) , NewSessionSettings(InNewSessionSettings) , StateSaver(MoveTemp(InStateSaver))`
- L13 _public function_ `FSessionCreateSessionStep(FUniqueNetIdPtr* InLocalUserId, FName InSessionName, const FOnlineSessionSettings& InNewSessionSettings, TFunction<void(TSharedPtr<FNamedOnlineSession>)>&& InStateSaver = [](TSharedPtr<FNamedOnlineSession>){}) : LocalUserId(InLocalUserId) , TestSessionName(InSessionName) , NewSessionSettings(InNewSessionSettings) , StateSaver(MoveTemp(InStateSaver))`
- L20 _public function_ `FSessionCreateSessionStep(int32 InLocalUserNum, FName InSessionName, const FOnlineSessionSettings& InNewSessionSettings, TFunction<void(TSharedPtr<FNamedOnlineSession>)>&& InStateSaver = [](TSharedPtr<FNamedOnlineSession>) {}) : LocalUserNum(InLocalUserNum) , TestSessionName(InSessionName) , NewSessionSettings(InNewSessionSettings) , StateSaver(MoveTemp(InStateSaver)) , bUseOverload(true)`
- L20 _public function_ `FSessionCreateSessionStep(int32 InLocalUserNum, FName InSessionName, const FOnlineSessionSettings& InNewSessionSettings, TFunction<void(TSharedPtr<FNamedOnlineSession>)>&& InStateSaver = [](TSharedPtr<FNamedOnlineSession>) {}) : LocalUserNum(InLocalUserNum) , TestSessionName(InSessionName) , NewSessionSettings(InNewSessionSettings) , StateSaver(MoveTemp(InStateSaver)) , bUseOverload(true)`
- L28 _public function_ `virtual ~FSessionCreateSessionStep()`
- L40 _public member_ `enum class EState { Init, CreateSessionCall, CreateSessionCalled, ClearDelegates, Done } State = EState::Init;`
- L42 _public member_ `FOnCreateSessionCompleteDelegate CreateSessionDelegate = FOnCreateSessionCompleteDelegate::CreateLambda([this](FName SessionName, bool bWasSuccessful) { REQUIRE(State == EState::CreateSessionCalled); CHECK(bWasSuccessful); CHECK(SessionName.ToString() == TestSessionName.ToString()); TSharedPtr<FNamedOnlineSession> NamedOnlineSession = MakeShared<FNamedOnlineSession>(*OnlineSessionPtr->GetNamedSession(TestSessionName)); StateSaver(MoveTemp(NamedOnlineSession)); State = EState::ClearDelegates; });`
- L43 _public function_ ``
- L54 _public function_ `virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override`
- L106 _protected member_ `int32 LocalUserNum = 0;`
- L107 _protected member_ `FUniqueNetIdPtr* LocalUserId = nullptr;`
- L108 _protected member_ `FName TestSessionName = {};`
- L109 _protected member_ `FOnlineSessionSettings NewSessionSettings = {};`
- L110 _protected member_ `TFunction<void(TSharedPtr<FNamedOnlineSession>)> StateSaver;`
- L111 _protected member_ `bool bUseOverload = false;`
- L112 _protected member_ `IOnlineSessionPtr OnlineSessionPtr = nullptr;`
- L113 _protected member_ `FDelegateHandle OnCreateSessionCompleteDelegateHandle;`

#### enum `FSessionCreateSessionStep::EState`  
`enum class EState`  
_L40-40_
- L40 _public enumerator_ `enum class EState { Init, CreateSessionCall, CreateSessionCalled, ClearDelegates, Done } State = EState::Init; FOnCreateSessionCompleteDelegate CreateSessionDelegate = FOnCreateSessionCompleteDelegate::CreateLambda([this](FName SessionName, bool bWasSuccessful) { REQUIRE(State == EState::CreateSessionCalled); CHECK(bWasSuccessful); CHECK(SessionName.ToString() == TestSessionName.ToString());`
- L40 _public enumerator_ `enum class EState { Init, CreateSessionCall, CreateSessionCalled, ClearDelegates, Done } State = EState::Init; FOnCreateSessionCompleteDelegate CreateSessionDelegate = FOnCreateSessionCompleteDelegate::CreateLambda([this](FName SessionName, bool bWasSuccessful) { REQUIRE(State == EState::CreateSessionCalled); CHECK(bWasSuccessful); CHECK(SessionName.ToString() == TestSessionName.ToString());`
- L40 _public enumerator_ `enum class EState { Init, CreateSessionCall, CreateSessionCalled, ClearDelegates, Done } State = EState::Init; FOnCreateSessionCompleteDelegate CreateSessionDelegate = FOnCreateSessionCompleteDelegate::CreateLambda([this](FName SessionName, bool bWasSuccessful) { REQUIRE(State == EState::CreateSessionCalled); CHECK(bWasSuccessful); CHECK(SessionName.ToString() == TestSessionName.ToString());`
- L40 _public enumerator_ `enum class EState { Init, CreateSessionCall, CreateSessionCalled, ClearDelegates, Done } State = EState::Init; FOnCreateSessionCompleteDelegate CreateSessionDelegate = FOnCreateSessionCompleteDelegate::CreateLambda([this](FName SessionName, bool bWasSuccessful) { REQUIRE(State == EState::CreateSessionCalled); CHECK(bWasSuccessful); CHECK(SessionName.ToString() == TestSessionName.ToString());`
- L40 _public enumerator_ `enum class EState { Init, CreateSessionCall, CreateSessionCalled, ClearDelegates, Done } State = EState::Init; FOnCreateSessionCompleteDelegate CreateSessionDelegate = FOnCreateSessionCompleteDelegate::CreateLambda([this](FName SessionName, bool bWasSuccessful) { REQUIRE(State == EState::CreateSessionCalled); CHECK(bWasSuccessful); CHECK(SessionName.ToString() == TestSessionName.ToString());`

### `Source/Programs/Online/OSSTestsCore/Helpers/Session/SessionDestroySessionHelper.h` (Other)


#### struct `FSessionDestroySessionStep`  
`struct FSessionDestroySessionStep : public FTestPipeline::FStep`  
_L11-80_
- inherits: `FTestPipeline::FStep`
- L13 _public function_ `FSessionDestroySessionStep(FName InSessionName) : TestSessionName(InSessionName)`
- L17 _public function_ `virtual ~FSessionDestroySessionStep()`
- L29 _public member_ `enum class EState { DestroySessionCall, DestroySessionCalled, ClearDelegates, Done } State = EState::DestroySessionCall;`
- L31 _public member_ `FOnDestroySessionCompleteDelegate DestroySessionDelegate = FOnDestroySessionCompleteDelegate::CreateLambda([this](FName SessionName, bool bWasSuccessful) { REQUIRE(State == EState::DestroySessionCalled); CHECK(bWasSuccessful); CHECK(SessionName.ToString() == TestSessionName.ToString()); State = EState::ClearDelegates; });`
- L32 _public function_ ``
- L40 _public function_ `virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override`
- L77 _protected member_ `FName TestSessionName = {};`
- L78 _protected member_ `IOnlineSessionPtr OnlineSessionPtr = nullptr;`
- L79 _protected member_ `FDelegateHandle OnDestroySessionCompleteDelegateHandle;`

#### enum `FSessionDestroySessionStep::EState`  
`enum class EState`  
_L29-29_
- L29 _public enumerator_ `enum class EState { DestroySessionCall, DestroySessionCalled, ClearDelegates, Done } State = EState::DestroySessionCall; FOnDestroySessionCompleteDelegate DestroySessionDelegate = FOnDestroySessionCompleteDelegate::CreateLambda([this](FName SessionName, bool bWasSuccessful) { REQUIRE(State == EState::DestroySessionCalled); CHECK(bWasSuccessful); CHECK(SessionName.ToString() == TestSessionName.ToString());`
- L29 _public enumerator_ `enum class EState { DestroySessionCall, DestroySessionCalled, ClearDelegates, Done } State = EState::DestroySessionCall; FOnDestroySessionCompleteDelegate DestroySessionDelegate = FOnDestroySessionCompleteDelegate::CreateLambda([this](FName SessionName, bool bWasSuccessful) { REQUIRE(State == EState::DestroySessionCalled); CHECK(bWasSuccessful); CHECK(SessionName.ToString() == TestSessionName.ToString());`
- L29 _public enumerator_ `enum class EState { DestroySessionCall, DestroySessionCalled, ClearDelegates, Done } State = EState::DestroySessionCall; FOnDestroySessionCompleteDelegate DestroySessionDelegate = FOnDestroySessionCompleteDelegate::CreateLambda([this](FName SessionName, bool bWasSuccessful) { REQUIRE(State == EState::DestroySessionCalled); CHECK(bWasSuccessful); CHECK(SessionName.ToString() == TestSessionName.ToString());`
- L29 _public enumerator_ `enum class EState { DestroySessionCall, DestroySessionCalled, ClearDelegates, Done } State = EState::DestroySessionCall; FOnDestroySessionCompleteDelegate DestroySessionDelegate = FOnDestroySessionCompleteDelegate::CreateLambda([this](FName SessionName, bool bWasSuccessful) { REQUIRE(State == EState::DestroySessionCalled); CHECK(bWasSuccessful); CHECK(SessionName.ToString() == TestSessionName.ToString());`

### `Source/Programs/Online/OSSTestsCore/Helpers/Session/SessionEndSessionHelper.h` (Other)


#### struct `FSessionEndSessionStep`  
`struct FSessionEndSessionStep : public FTestPipeline::FStep`  
_L11-88_
- inherits: `FTestPipeline::FStep`
- L13 _public function_ `FSessionEndSessionStep(FName InSessionName) : TestSessionName(InSessionName)`
- L17 _public function_ `virtual ~FSessionEndSessionStep()`
- L29 _public member_ `enum class EState { Init, EndSessionCall, EndSessionCalled, ClearDelegates, Done } State = EState::Init;`
- L31 _public member_ `FOnEndSessionCompleteDelegate EndSessionDelegate = FOnEndSessionCompleteDelegate::CreateLambda([this](FName SessionName, bool bWasSuccessful) { REQUIRE(State == EState::EndSessionCalled); CHECK(bWasSuccessful); CHECK(SessionName.ToString() == TestSessionName.ToString()); State = EState::ClearDelegates; });`
- L32 _public function_ ``
- L40 _public function_ `virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override`
- L85 _protected member_ `FName TestSessionName = {};`
- L86 _protected member_ `IOnlineSessionPtr OnlineSessionPtr = nullptr;`
- L87 _protected member_ `FDelegateHandle OnEndSessionCompleteDelegateHandle;`

#### enum `FSessionEndSessionStep::EState`  
`enum class EState`  
_L29-29_
- L29 _public enumerator_ `enum class EState { Init, EndSessionCall, EndSessionCalled, ClearDelegates, Done } State = EState::Init; FOnEndSessionCompleteDelegate EndSessionDelegate = FOnEndSessionCompleteDelegate::CreateLambda([this](FName SessionName, bool bWasSuccessful) { REQUIRE(State == EState::EndSessionCalled); CHECK(bWasSuccessful); CHECK(SessionName.ToString() == TestSessionName.ToString());`
- L29 _public enumerator_ `enum class EState { Init, EndSessionCall, EndSessionCalled, ClearDelegates, Done } State = EState::Init; FOnEndSessionCompleteDelegate EndSessionDelegate = FOnEndSessionCompleteDelegate::CreateLambda([this](FName SessionName, bool bWasSuccessful) { REQUIRE(State == EState::EndSessionCalled); CHECK(bWasSuccessful); CHECK(SessionName.ToString() == TestSessionName.ToString());`
- L29 _public enumerator_ `enum class EState { Init, EndSessionCall, EndSessionCalled, ClearDelegates, Done } State = EState::Init; FOnEndSessionCompleteDelegate EndSessionDelegate = FOnEndSessionCompleteDelegate::CreateLambda([this](FName SessionName, bool bWasSuccessful) { REQUIRE(State == EState::EndSessionCalled); CHECK(bWasSuccessful); CHECK(SessionName.ToString() == TestSessionName.ToString());`
- L29 _public enumerator_ `enum class EState { Init, EndSessionCall, EndSessionCalled, ClearDelegates, Done } State = EState::Init; FOnEndSessionCompleteDelegate EndSessionDelegate = FOnEndSessionCompleteDelegate::CreateLambda([this](FName SessionName, bool bWasSuccessful) { REQUIRE(State == EState::EndSessionCalled); CHECK(bWasSuccessful); CHECK(SessionName.ToString() == TestSessionName.ToString());`
- L29 _public enumerator_ `enum class EState { Init, EndSessionCall, EndSessionCalled, ClearDelegates, Done } State = EState::Init; FOnEndSessionCompleteDelegate EndSessionDelegate = FOnEndSessionCompleteDelegate::CreateLambda([this](FName SessionName, bool bWasSuccessful) { REQUIRE(State == EState::EndSessionCalled); CHECK(bWasSuccessful); CHECK(SessionName.ToString() == TestSessionName.ToString());`

### `Source/Programs/Online/OSSTestsCore/Helpers/Session/SessionFindFriendSessionHelper.h` (Other)


#### struct `FSessionFindFriendSessionStep`  
`struct FSessionFindFriendSessionStep : public FTestPipeline::FStep`  
_L10-90_
- inherits: `FTestPipeline::FStep`
- L12 _public function_ `FSessionFindFriendSessionStep(FUniqueNetIdPtr* InUserId, int32 InUserNum, FUniqueNetIdPtr* InFriendId) : UserNum(InUserNum) , UserId(InUserId) , FriendId(InFriendId)`
- L18 _public function_ `virtual ~FSessionFindFriendSessionStep()`
- L30 _public member_ `enum class EState { Init, FindFriendSessionCall, FindFriendSessionCalled, ClearDelegates, Done } State = EState::Init;`
- L32 _public member_ `FOnFindFriendSessionCompleteDelegate FindFriendSessionDelegate = FOnFindFriendSessionCompleteDelegate::CreateLambda([this](int32 InLocalUserNum, bool bWasSuccessful, const TArray<FOnlineSessionSearchResult>& InSearchResult) { REQUIRE(State == EState::FindFriendSessionCalled); CHECK(UserNum == InLocalUserNum); CHECK(bWasSuccessful); CHECK(InSearchResult.Num() > 0); State = EState::ClearDelegates; });`
- L33 _public function_ ``
- L42 _public function_ `virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override`
- L84 _protected member_ `int32 UserNum = 0;`
- L85 _protected member_ `FUniqueNetIdPtr* UserId = nullptr;`
- L86 _protected member_ `FUniqueNetIdPtr* FriendId = nullptr;`
- L87 _protected member_ `bool bUseOverload = false;`
- L88 _protected member_ `IOnlineSessionPtr OnlineSessionPtr = nullptr;`
- L89 _protected member_ `FDelegateHandle OnFindFriendSessionCompleteDelegateHandle;`

#### enum `FSessionFindFriendSessionStep::EState`  
`enum class EState`  
_L30-30_
- L30 _public enumerator_ `enum class EState { Init, FindFriendSessionCall, FindFriendSessionCalled, ClearDelegates, Done } State = EState::Init; FOnFindFriendSessionCompleteDelegate FindFriendSessionDelegate = FOnFindFriendSessionCompleteDelegate::CreateLambda([this](int32 InLocalUserNum, bool bWasSuccessful, const TArray<FOnlineSessionSearchResult>& InSearchResult) { REQUIRE(State == EState::FindFriendSessionCalled); CHECK(UserNum == InLocalUserNum); CHECK(bWasSuccessful); CHECK(InSearchResult.Num() > 0);`
- L30 _public enumerator_ `enum class EState { Init, FindFriendSessionCall, FindFriendSessionCalled, ClearDelegates, Done } State = EState::Init; FOnFindFriendSessionCompleteDelegate FindFriendSessionDelegate = FOnFindFriendSessionCompleteDelegate::CreateLambda([this](int32 InLocalUserNum, bool bWasSuccessful, const TArray<FOnlineSessionSearchResult>& InSearchResult) { REQUIRE(State == EState::FindFriendSessionCalled); CHECK(UserNum == InLocalUserNum); CHECK(bWasSuccessful); CHECK(InSearchResult.Num() > 0);`
- L30 _public enumerator_ `enum class EState { Init, FindFriendSessionCall, FindFriendSessionCalled, ClearDelegates, Done } State = EState::Init; FOnFindFriendSessionCompleteDelegate FindFriendSessionDelegate = FOnFindFriendSessionCompleteDelegate::CreateLambda([this](int32 InLocalUserNum, bool bWasSuccessful, const TArray<FOnlineSessionSearchResult>& InSearchResult) { REQUIRE(State == EState::FindFriendSessionCalled); CHECK(UserNum == InLocalUserNum); CHECK(bWasSuccessful); CHECK(InSearchResult.Num() > 0);`
- L30 _public enumerator_ `enum class EState { Init, FindFriendSessionCall, FindFriendSessionCalled, ClearDelegates, Done } State = EState::Init; FOnFindFriendSessionCompleteDelegate FindFriendSessionDelegate = FOnFindFriendSessionCompleteDelegate::CreateLambda([this](int32 InLocalUserNum, bool bWasSuccessful, const TArray<FOnlineSessionSearchResult>& InSearchResult) { REQUIRE(State == EState::FindFriendSessionCalled); CHECK(UserNum == InLocalUserNum); CHECK(bWasSuccessful); CHECK(InSearchResult.Num() > 0);`
- L30 _public enumerator_ `enum class EState { Init, FindFriendSessionCall, FindFriendSessionCalled, ClearDelegates, Done } State = EState::Init; FOnFindFriendSessionCompleteDelegate FindFriendSessionDelegate = FOnFindFriendSessionCompleteDelegate::CreateLambda([this](int32 InLocalUserNum, bool bWasSuccessful, const TArray<FOnlineSessionSearchResult>& InSearchResult) { REQUIRE(State == EState::FindFriendSessionCalled); CHECK(UserNum == InLocalUserNum); CHECK(bWasSuccessful); CHECK(InSearchResult.Num() > 0);`

### `Source/Programs/Online/OSSTestsCore/Helpers/Session/SessionFindSessionByIdHelper.h` (Other)


#### struct `FSessionFindSessionByIdStep`  
`struct FSessionFindSessionByIdStep : public FTestPipeline::FStep`  
_L10-114_
- inherits: `FTestPipeline::FStep`
- L12 _public function_ `FSessionFindSessionByIdStep(FUniqueNetIdPtr* InSearchingUserId, FUniqueNetIdPtr* InFriendId, TSharedPtr<FNamedOnlineSession>* InNamedOnlineSession, TFunction<void(TSharedPtr<FOnlineSessionSearchResult>)>&& InStateSaver = [](TSharedPtr<FOnlineSessionSearchResult>) {}) : SearchingUserId(InSearchingUserId) , FriendId(InFriendId) , NamedOnlineSession(InNamedOnlineSession) , StateSaver(InStateSaver)`
- L12 _public function_ `FSessionFindSessionByIdStep(FUniqueNetIdPtr* InSearchingUserId, FUniqueNetIdPtr* InFriendId, TSharedPtr<FNamedOnlineSession>* InNamedOnlineSession, TFunction<void(TSharedPtr<FOnlineSessionSearchResult>)>&& InStateSaver = [](TSharedPtr<FOnlineSessionSearchResult>) {}) : SearchingUserId(InSearchingUserId) , FriendId(InFriendId) , NamedOnlineSession(InNamedOnlineSession) , StateSaver(InStateSaver)`
- L19 _public function_ `FSessionFindSessionByIdStep(FUniqueNetIdPtr* InSearchingUserId, FUniqueNetIdPtr* InFriendId, TSharedPtr<FNamedOnlineSession>* InNamedOnlineSession, const FString& InSessionKey, TFunction<void(TSharedPtr<FOnlineSessionSearchResult>)>&& InStateSaver = [](TSharedPtr<FOnlineSessionSearchResult>) {}) : SearchingUserId(InSearchingUserId) , FriendId(InFriendId) , NamedOnlineSession(InNamedOnlineSession) , SessionKey(InSessionKey) , StateSaver(InStateSaver) , bUseOverload(true)`
- L19 _public function_ `FSessionFindSessionByIdStep(FUniqueNetIdPtr* InSearchingUserId, FUniqueNetIdPtr* InFriendId, TSharedPtr<FNamedOnlineSession>* InNamedOnlineSession, const FString& InSessionKey, TFunction<void(TSharedPtr<FOnlineSessionSearchResult>)>&& InStateSaver = [](TSharedPtr<FOnlineSessionSearchResult>) {}) : SearchingUserId(InSearchingUserId) , FriendId(InFriendId) , NamedOnlineSession(InNamedOnlineSession) , SessionKey(InSessionKey) , StateSaver(InStateSaver) , bUseOverload(true)`
- L28 _public function_ `virtual ~FSessionFindSessionByIdStep()`
- L40 _public member_ `enum class EState { Init, FindSessionByIdCall, FindSessionByIdCalled, ClearDelegates, Done } State = EState::Init;`
- L42 _public member_ `FOnSingleSessionResultCompleteDelegate FindSessionsByIdDelegate = FOnSingleSessionResultCompleteDelegate::CreateLambda([this](int32 InLocalUserNum, bool bWasSuccessful, const FOnlineSessionSearchResult& InSearchResult) { REQUIRE(State == EState::FindSessionByIdCalled); CHECK(LocalUserNum == InLocalUserNum); CHECK(bWasSuccessful); REQUIRE(NamedOnlineSession != nullptr); REQUIRE(NamedOnlineSession->IsValid() == true); REQUIRE(NamedOnlineSession->ToSharedRef()->SessionInfo.IsValid() == true); REQUIRE(InSearchResult.Session.SessionInfo.IsValid() == true); CHECK(NamedOnlineSession->ToSharedRef()->SessionInfo->GetSessionId() == InSearchResult.Session.SessionInfo->GetSessionId()); TSharedPtr<FOnlineSessionSearchResult> SearchResultPtr = MakeShared<FOnlineSessionSearchResult>(InSearchResult); StateSaver(MoveTemp(SearchResultPtr)); State = EState::ClearDelegates; });`
- L43 _public function_ ``
- L59 _public function_ `virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override`
- L106 _protected member_ `int32 LocalUserNum = 0;`
- L107 _protected member_ `FUniqueNetIdPtr* SearchingUserId = nullptr;`
- L108 _protected member_ `FUniqueNetIdPtr* FriendId = nullptr;`
- L109 _protected member_ `TSharedPtr<FNamedOnlineSession>* NamedOnlineSession = nullptr;`
- L110 _protected member_ `FString SessionKey = TEXT("");`
- L111 _protected member_ `TFunction<void(TSharedPtr<FOnlineSessionSearchResult>)> StateSaver;`
- L112 _protected member_ `bool bUseOverload = false;`
- L113 _protected member_ `IOnlineSessionPtr OnlineSessionPtr = nullptr;`

#### enum `FSessionFindSessionByIdStep::EState`  
`enum class EState`  
_L40-40_
- L40 _public enumerator_ `enum class EState { Init, FindSessionByIdCall, FindSessionByIdCalled, ClearDelegates, Done } State = EState::Init; FOnSingleSessionResultCompleteDelegate FindSessionsByIdDelegate = FOnSingleSessionResultCompleteDelegate::CreateLambda([this](int32 InLocalUserNum, bool bWasSuccessful, const FOnlineSessionSearchResult& InSearchResult) { REQUIRE(State == EState::FindSessionByIdCalled); CHECK(LocalUserNum == InLocalUserNum); CHECK(bWasSuccessful); REQUIRE(NamedOnlineSession != nullptr);`
- L40 _public enumerator_ `enum class EState { Init, FindSessionByIdCall, FindSessionByIdCalled, ClearDelegates, Done } State = EState::Init; FOnSingleSessionResultCompleteDelegate FindSessionsByIdDelegate = FOnSingleSessionResultCompleteDelegate::CreateLambda([this](int32 InLocalUserNum, bool bWasSuccessful, const FOnlineSessionSearchResult& InSearchResult) { REQUIRE(State == EState::FindSessionByIdCalled); CHECK(LocalUserNum == InLocalUserNum); CHECK(bWasSuccessful); REQUIRE(NamedOnlineSession != nullptr);`
- L40 _public enumerator_ `enum class EState { Init, FindSessionByIdCall, FindSessionByIdCalled, ClearDelegates, Done } State = EState::Init; FOnSingleSessionResultCompleteDelegate FindSessionsByIdDelegate = FOnSingleSessionResultCompleteDelegate::CreateLambda([this](int32 InLocalUserNum, bool bWasSuccessful, const FOnlineSessionSearchResult& InSearchResult) { REQUIRE(State == EState::FindSessionByIdCalled); CHECK(LocalUserNum == InLocalUserNum); CHECK(bWasSuccessful); REQUIRE(NamedOnlineSession != nullptr);`
- L40 _public enumerator_ `enum class EState { Init, FindSessionByIdCall, FindSessionByIdCalled, ClearDelegates, Done } State = EState::Init; FOnSingleSessionResultCompleteDelegate FindSessionsByIdDelegate = FOnSingleSessionResultCompleteDelegate::CreateLambda([this](int32 InLocalUserNum, bool bWasSuccessful, const FOnlineSessionSearchResult& InSearchResult) { REQUIRE(State == EState::FindSessionByIdCalled); CHECK(LocalUserNum == InLocalUserNum); CHECK(bWasSuccessful); REQUIRE(NamedOnlineSession != nullptr);`
- L40 _public enumerator_ `enum class EState { Init, FindSessionByIdCall, FindSessionByIdCalled, ClearDelegates, Done } State = EState::Init; FOnSingleSessionResultCompleteDelegate FindSessionsByIdDelegate = FOnSingleSessionResultCompleteDelegate::CreateLambda([this](int32 InLocalUserNum, bool bWasSuccessful, const FOnlineSessionSearchResult& InSearchResult) { REQUIRE(State == EState::FindSessionByIdCalled); CHECK(LocalUserNum == InLocalUserNum); CHECK(bWasSuccessful); REQUIRE(NamedOnlineSession != nullptr);`

### `Source/Programs/Online/OSSTestsCore/Helpers/Session/SessionFindSessionHelper.h` (Other)


#### struct `FSessionFindSessionStep`  
`struct FSessionFindSessionStep : public FTestPipeline::FStep`  
_L11-92_
- inherits: `FTestPipeline::FStep`
- L13 _public function_ `FSessionFindSessionStep(int32 InLocalUserNum, const TSharedRef<FOnlineSessionSearch>& InSearchSettings) : LocalUserNum(InLocalUserNum) , SearchSettings(InSearchSettings)`
- L17 _public function_ `FSessionFindSessionStep(FUniqueNetIdPtr* InSearchingPlayerId, const TSharedRef<FOnlineSessionSearch>& InSearchSettings) : SearchingPlayerId(InSearchingPlayerId) , SearchSettings(InSearchSettings) , bUseOverload(true)`
- L22 _public function_ `virtual ~FSessionFindSessionStep()`
- L33 _public member_ `enum class EState { Init, FindSessionsCall, FindSessionsCalled, ClearDelegates, Done } State = EState::Init;`
- L34 _public member_ `FOnFindSessionsCompleteDelegate FindSessionsDelegate = FOnFindSessionsCompleteDelegate::CreateLambda([this](bool bWasSuccessful) { REQUIRE(State == EState::FindSessionsCalled); REQUIRE(SearchSettings->SearchState == EOnlineAsyncTaskState::Done); CHECK(bWasSuccessful); State = EState::ClearDelegates; });`
- L35 _public function_ ``
- L41 _public function_ `virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override`
- L86 _protected member_ `int32 LocalUserNum = 0;`
- L87 _protected member_ `FUniqueNetIdPtr* SearchingPlayerId = nullptr;`
- L88 _protected member_ `TSharedRef<FOnlineSessionSearch> SearchSettings;`
- L89 _protected member_ `bool bUseOverload = false;`
- L90 _protected member_ `FDelegateHandle OnFindSessionsCompleteDelegateHandle;`
- L91 _protected member_ `IOnlineSessionPtr OnlineSessionPtr = nullptr;`

#### enum `FSessionFindSessionStep::EState`  
`enum class EState`  
_L33-33_
- L33 _public enumerator_ `enum class EState { Init, FindSessionsCall, FindSessionsCalled, ClearDelegates, Done } State = EState::Init; FOnFindSessionsCompleteDelegate FindSessionsDelegate = FOnFindSessionsCompleteDelegate::CreateLambda([this](bool bWasSuccessful) { REQUIRE(State == EState::FindSessionsCalled); REQUIRE(SearchSettings->SearchState == EOnlineAsyncTaskState::Done); CHECK(bWasSuccessful); State = EState::ClearDelegates; });`
- L33 _public enumerator_ `enum class EState { Init, FindSessionsCall, FindSessionsCalled, ClearDelegates, Done } State = EState::Init; FOnFindSessionsCompleteDelegate FindSessionsDelegate = FOnFindSessionsCompleteDelegate::CreateLambda([this](bool bWasSuccessful) { REQUIRE(State == EState::FindSessionsCalled); REQUIRE(SearchSettings->SearchState == EOnlineAsyncTaskState::Done); CHECK(bWasSuccessful); State = EState::ClearDelegates; });`
- L33 _public enumerator_ `enum class EState { Init, FindSessionsCall, FindSessionsCalled, ClearDelegates, Done } State = EState::Init; FOnFindSessionsCompleteDelegate FindSessionsDelegate = FOnFindSessionsCompleteDelegate::CreateLambda([this](bool bWasSuccessful) { REQUIRE(State == EState::FindSessionsCalled); REQUIRE(SearchSettings->SearchState == EOnlineAsyncTaskState::Done); CHECK(bWasSuccessful); State = EState::ClearDelegates; });`
- L33 _public enumerator_ `enum class EState { Init, FindSessionsCall, FindSessionsCalled, ClearDelegates, Done } State = EState::Init; FOnFindSessionsCompleteDelegate FindSessionsDelegate = FOnFindSessionsCompleteDelegate::CreateLambda([this](bool bWasSuccessful) { REQUIRE(State == EState::FindSessionsCalled); REQUIRE(SearchSettings->SearchState == EOnlineAsyncTaskState::Done); CHECK(bWasSuccessful); State = EState::ClearDelegates; });`
- L33 _public enumerator_ `enum class EState { Init, FindSessionsCall, FindSessionsCalled, ClearDelegates, Done } State = EState::Init; FOnFindSessionsCompleteDelegate FindSessionsDelegate = FOnFindSessionsCompleteDelegate::CreateLambda([this](bool bWasSuccessful) { REQUIRE(State == EState::FindSessionsCalled); REQUIRE(SearchSettings->SearchState == EOnlineAsyncTaskState::Done); CHECK(bWasSuccessful); State = EState::ClearDelegates; });`

### `Source/Programs/Online/OSSTestsCore/Helpers/Session/SessionGetNumSessionsHelper.h` (Other)


#### struct `FSessionGetNumSessionsStep`  
`struct FSessionGetNumSessionsStep : public FTestPipeline::FStep`  
_L10-32_
- inherits: `FTestPipeline::FStep`
- L12 _public function_ `FSessionGetNumSessionsStep(int32 InExpectedSessionsNum) : ExpectedSessionsNum(InExpectedSessionsNum)`
- L16 _public prototype_ `virtual ~FSessionGetNumSessionsStep() = default;`
- L18 _public function_ `virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override`
- L30 _protected member_ `int32 ExpectedSessionsNum = 0;`
- L31 _protected member_ `IOnlineSessionPtr OnlineSessionPtr = nullptr;`

### `Source/Programs/Online/OSSTestsCore/Helpers/Session/SessionGetResolvedConnectStringHelper.h` (Other)


#### struct `FSessionGetResolvedConnectStringStep`  
`struct FSessionGetResolvedConnectStringStep : public FTestPipeline::FStep`  
_L10-85_
- inherits: `FTestPipeline::FStep`
- L12 _public function_ `FSessionGetResolvedConnectStringStep(FName InSessionName, FString& InConnectInfo, FName InPortType) : PortType(InPortType) , ConnectInfo(InConnectInfo) , SessionName(InSessionName)`
- L18 _public function_ `FSessionGetResolvedConnectStringStep(TSharedPtr<FOnlineSessionSearchResult>* InSearchResult, FName InPortType, FString& InConnectInfo) : SearchResult(InSearchResult) , PortType(InPortType) , ConnectInfo(InConnectInfo) , bUseOverload(true)`
- L25 _public prototype_ `virtual ~FSessionGetResolvedConnectStringStep() = default;`
- L27 _public member_ `enum class EState { Init, GetResolvedConnectStringCall, GetResolvedConnectStringCalled, ClearDelegates, Done } State = EState::Init;`
- L29 _public function_ `virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override`
- L79 _protected member_ `TSharedPtr<FOnlineSessionSearchResult>* SearchResult = nullptr;`
- L80 _protected member_ `FName PortType = TEXT("");`
- L81 _protected member_ `FString ConnectInfo = TEXT("");`
- L82 _protected member_ `FName SessionName = TEXT("");`
- L83 _protected member_ `bool bUseOverload = false;`
- L84 _protected member_ `IOnlineSessionPtr OnlineSessionPtr = nullptr;`

#### enum `FSessionGetResolvedConnectStringStep::EState`  
`enum class EState`  
_L27-27_
- L27 _public enumerator_ `enum class EState { Init, GetResolvedConnectStringCall, GetResolvedConnectStringCalled, ClearDelegates, Done } State = EState::Init; virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override { switch (State) { case EState::Init: {`
- L27 _public enumerator_ `enum class EState { Init, GetResolvedConnectStringCall, GetResolvedConnectStringCalled, ClearDelegates, Done } State = EState::Init; virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override { switch (State) { case EState::Init: {`
- L27 _public enumerator_ `enum class EState { Init, GetResolvedConnectStringCall, GetResolvedConnectStringCalled, ClearDelegates, Done } State = EState::Init; virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override { switch (State) { case EState::Init: {`
- L27 _public enumerator_ `enum class EState { Init, GetResolvedConnectStringCall, GetResolvedConnectStringCalled, ClearDelegates, Done } State = EState::Init; virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override { switch (State) { case EState::Init: {`
- L27 _public enumerator_ `enum class EState { Init, GetResolvedConnectStringCall, GetResolvedConnectStringCalled, ClearDelegates, Done } State = EState::Init; virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override { switch (State) { case EState::Init: {`

### `Source/Programs/Online/OSSTestsCore/Helpers/Session/SessionGetSessionSettingsHelper.h` (Other)


#### struct `FSessionGetSessionSettingsStep`  
`struct FSessionGetSessionSettingsStep : public FTestPipeline::FStep`  
_L11-50_
- inherits: `FTestPipeline::FStep`
- L13 _public function_ `FSessionGetSessionSettingsStep(FName InSessionName, const FOnlineSessionSettings& InExpectedSessionSettings, TFunction<void(FOnlineSessionSettings)>&& InStateSaver) : SessionName(InSessionName) , ExpectedSessionSettings(InExpectedSessionSettings) , StateSaver(MoveTemp(InStateSaver))`
- L19 _public function_ `FSessionGetSessionSettingsStep(FName InSessionName, const FOnlineSessionSettings& InExpectedSessionSettings) : SessionName(InSessionName) , ExpectedSessionSettings(InExpectedSessionSettings) , StateSaver([](FOnlineSessionSettings) {})`
- L22 _public function_ `, StateSaver([](FOnlineSessionSettings) {})`
- L25 _public prototype_ `virtual ~FSessionGetSessionSettingsStep() = default;`
- L27 _public function_ `virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override`
- L46 _protected member_ `FName SessionName = {};`
- L47 _protected member_ `FOnlineSessionSettings ExpectedSessionSettings = {};`
- L48 _protected member_ `TFunction<void(FOnlineSessionSettings)> StateSaver;`
- L49 _protected member_ `IOnlineSessionPtr OnlineSessionPtr = nullptr;`

### `Source/Programs/Online/OSSTestsCore/Helpers/Session/SessionGetSessionStateHelper.h` (Other)


#### struct `FSessionGetSessionStateStep`  
`struct FSessionGetSessionStateStep : public FTestPipeline::FStep`  
_L11-35_
- inherits: `FTestPipeline::FStep`
- L13 _public function_ `FSessionGetSessionStateStep(FName InSessionName, const EOnlineSessionState::Type InExpectedSessionState) : SessionName(InSessionName) , ExpectedSessionState(InExpectedSessionState)`
- L18 _public prototype_ `virtual ~FSessionGetSessionStateStep() = default;`
- L20 _public function_ `virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override`
- L32 _protected member_ `FName SessionName = {};`
- L33 _protected member_ `EOnlineSessionState::Type ExpectedSessionState = EOnlineSessionState::Type::NoSession;`
- L34 _protected member_ `IOnlineSessionPtr OnlineSessionPtr = nullptr;`

### `Source/Programs/Online/OSSTestsCore/Helpers/Session/SessionIsPlayerInSessionHelper.h` (Other)


#### struct `FSessionIsPlayerInSessionStep`  
`struct FSessionIsPlayerInSessionStep : public FTestPipeline::FStep`  
_L10-35_
- inherits: `FTestPipeline::FStep`
- L12 _public function_ `FSessionIsPlayerInSessionStep(FName InSessionName, FUniqueNetIdPtr* InPlayer) : TestSessionName(InSessionName) , Player(InPlayer)`
- L17 _public prototype_ `virtual ~FSessionIsPlayerInSessionStep() = default;`
- L19 _public function_ `virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override`
- L31 _protected member_ `FName TestSessionName = {};`
- L32 _protected member_ `FUniqueNetIdPtr* Player = nullptr;`
- L33 _protected member_ `bool bIsPlayerInSession = false;`
- L34 _protected member_ `IOnlineSessionPtr OnlineSessionPtr = nullptr;`

### `Source/Programs/Online/OSSTestsCore/Helpers/Session/SessionJoinSessionHelper.h` (Other)


#### struct `FSessionJoinSessionStep`  
`struct FSessionJoinSessionStep : public FTestPipeline::FStep`  
_L10-107_
- inherits: `FTestPipeline::FStep`
- L12 _public function_ `FSessionJoinSessionStep(int32 InPlayerNum, const FName& InSessionName, TSharedPtr<FOnlineSessionSearchResult>* InDesiredSession) : PlayerNum(InPlayerNum) , SessionName(InSessionName) , DesiredSession(InDesiredSession) , bUseOverload(true)`
- L20 _public function_ `FSessionJoinSessionStep(FUniqueNetIdPtr* InPlayerId,const FName& InSessionName, TSharedPtr<FOnlineSessionSearchResult>* InDesiredSession) : PlayerId(InPlayerId) , SessionName(InSessionName) , DesiredSession(InDesiredSession)`
- L26 _public function_ `virtual ~FSessionJoinSessionStep()`
- L38 _public member_ `enum class EState { Init, JoinSessionCall, JoinSessionCalled, ClearDelegates, Done } State = EState::Init;`
- L40 _public member_ `FOnJoinSessionCompleteDelegate JoinSessionsDelegate = FOnJoinSessionCompleteDelegate::CreateLambda([this](FName InSessionName, EOnJoinSessionCompleteResult::Type InResult) { REQUIRE(State == EState::JoinSessionCalled); CHECK(SessionName == InSessionName); CHECK(InResult == EOnJoinSessionCompleteResult::Type::Success); State = EState::ClearDelegates; });`
- L41 _public function_ ``
- L49 _public function_ `virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override`
- L100 _protected member_ `int32 PlayerNum = 0;`
- L101 _protected member_ `FUniqueNetIdPtr* PlayerId = nullptr;`
- L102 _protected member_ `FName SessionName = TEXT("");`
- L103 _protected member_ `TSharedPtr<FOnlineSessionSearchResult>* DesiredSession = nullptr;`
- L104 _protected member_ `bool bUseOverload = false;`
- L105 _protected member_ `FDelegateHandle OnJoinSessionsCompleteDelegateHandle;`
- L106 _protected member_ `IOnlineSessionPtr OnlineSessionPtr = nullptr;`

#### enum `FSessionJoinSessionStep::EState`  
`enum class EState`  
_L38-38_
- L38 _public enumerator_ `enum class EState { Init, JoinSessionCall, JoinSessionCalled, ClearDelegates, Done } State = EState::Init; FOnJoinSessionCompleteDelegate JoinSessionsDelegate = FOnJoinSessionCompleteDelegate::CreateLambda([this](FName InSessionName, EOnJoinSessionCompleteResult::Type InResult) { REQUIRE(State == EState::JoinSessionCalled); CHECK(SessionName == InSessionName); CHECK(InResult == EOnJoinSessionCompleteResult::Type::Success);`
- L38 _public enumerator_ `enum class EState { Init, JoinSessionCall, JoinSessionCalled, ClearDelegates, Done } State = EState::Init; FOnJoinSessionCompleteDelegate JoinSessionsDelegate = FOnJoinSessionCompleteDelegate::CreateLambda([this](FName InSessionName, EOnJoinSessionCompleteResult::Type InResult) { REQUIRE(State == EState::JoinSessionCalled); CHECK(SessionName == InSessionName); CHECK(InResult == EOnJoinSessionCompleteResult::Type::Success);`
- L38 _public enumerator_ `enum class EState { Init, JoinSessionCall, JoinSessionCalled, ClearDelegates, Done } State = EState::Init; FOnJoinSessionCompleteDelegate JoinSessionsDelegate = FOnJoinSessionCompleteDelegate::CreateLambda([this](FName InSessionName, EOnJoinSessionCompleteResult::Type InResult) { REQUIRE(State == EState::JoinSessionCalled); CHECK(SessionName == InSessionName); CHECK(InResult == EOnJoinSessionCompleteResult::Type::Success);`
- L38 _public enumerator_ `enum class EState { Init, JoinSessionCall, JoinSessionCalled, ClearDelegates, Done } State = EState::Init; FOnJoinSessionCompleteDelegate JoinSessionsDelegate = FOnJoinSessionCompleteDelegate::CreateLambda([this](FName InSessionName, EOnJoinSessionCompleteResult::Type InResult) { REQUIRE(State == EState::JoinSessionCalled); CHECK(SessionName == InSessionName); CHECK(InResult == EOnJoinSessionCompleteResult::Type::Success);`
- L38 _public enumerator_ `enum class EState { Init, JoinSessionCall, JoinSessionCalled, ClearDelegates, Done } State = EState::Init; FOnJoinSessionCompleteDelegate JoinSessionsDelegate = FOnJoinSessionCompleteDelegate::CreateLambda([this](FName InSessionName, EOnJoinSessionCompleteResult::Type InResult) { REQUIRE(State == EState::JoinSessionCalled); CHECK(SessionName == InSessionName); CHECK(InResult == EOnJoinSessionCompleteResult::Type::Success);`

### `Source/Programs/Online/OSSTestsCore/Helpers/Session/SessionRegisterLocalPlayerHelper.h` (Other)


#### struct `FSessionRegisterLocalPlayerStep`  
`struct FSessionRegisterLocalPlayerStep : public FTestPipeline::FStep`  
_L10-73_
- inherits: `FTestPipeline::FStep`
- L12 _public function_ `FSessionRegisterLocalPlayerStep(FUniqueNetIdPtr* InPlayer, FName InSessionName, EOnJoinSessionCompleteResult::Type InExpectedSessionCompleteType) : TestSessionName(InSessionName) , Player(InPlayer) , ExpectedSessionCompleteType(InExpectedSessionCompleteType)`
- L18 _public prototype_ `virtual ~FSessionRegisterLocalPlayerStep() = default;`
- L20 _public member_ `enum class EState { Init, RegisterLocalPlayerCall, RegisterLocalPlayerCalled, ClearDelegates, Done } State = EState::Init;`
- L22 _public member_ `FOnRegisterLocalPlayerCompleteDelegate RegisterLocalPlayerDelegate = FOnRegisterLocalPlayerCompleteDelegate::CreateLambda([this](const FUniqueNetId& InPlayer, EOnJoinSessionCompleteResult::Type InJoinSessionComplete) { REQUIRE(State == EState::RegisterLocalPlayerCalled); CHECK(*Player->Get() == InPlayer); CHECK(EOnJoinSessionCompleteResult::Type::Success == InJoinSessionComplete); State = EState::ClearDelegates; });`
- L23 _public function_ ``
- L31 _public function_ `virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override`
- L69 _protected member_ `FName TestSessionName = {};`
- L70 _protected member_ `FUniqueNetIdPtr* Player = nullptr;`
- L71 _protected member_ `EOnJoinSessionCompleteResult::Type ExpectedSessionCompleteType = EOnJoinSessionCompleteResult::UnknownError;`
- L72 _protected member_ `IOnlineSessionPtr OnlineSessionPtr = nullptr;`

#### enum `FSessionRegisterLocalPlayerStep::EState`  
`enum class EState`  
_L20-20_
- L20 _public enumerator_ `enum class EState { Init, RegisterLocalPlayerCall, RegisterLocalPlayerCalled, ClearDelegates, Done } State = EState::Init; FOnRegisterLocalPlayerCompleteDelegate RegisterLocalPlayerDelegate = FOnRegisterLocalPlayerCompleteDelegate::CreateLambda([this](const FUniqueNetId& InPlayer, EOnJoinSessionCompleteResult::Type InJoinSessionComplete) { REQUIRE(State == EState::RegisterLocalPlayerCalled); CHECK(*Player->Get() == InPlayer); CHECK(EOnJoinSessionCompleteResult::Type::Success == InJoinSessionComplete);`
- L20 _public enumerator_ `enum class EState { Init, RegisterLocalPlayerCall, RegisterLocalPlayerCalled, ClearDelegates, Done } State = EState::Init; FOnRegisterLocalPlayerCompleteDelegate RegisterLocalPlayerDelegate = FOnRegisterLocalPlayerCompleteDelegate::CreateLambda([this](const FUniqueNetId& InPlayer, EOnJoinSessionCompleteResult::Type InJoinSessionComplete) { REQUIRE(State == EState::RegisterLocalPlayerCalled); CHECK(*Player->Get() == InPlayer); CHECK(EOnJoinSessionCompleteResult::Type::Success == InJoinSessionComplete);`
- L20 _public enumerator_ `enum class EState { Init, RegisterLocalPlayerCall, RegisterLocalPlayerCalled, ClearDelegates, Done } State = EState::Init; FOnRegisterLocalPlayerCompleteDelegate RegisterLocalPlayerDelegate = FOnRegisterLocalPlayerCompleteDelegate::CreateLambda([this](const FUniqueNetId& InPlayer, EOnJoinSessionCompleteResult::Type InJoinSessionComplete) { REQUIRE(State == EState::RegisterLocalPlayerCalled); CHECK(*Player->Get() == InPlayer); CHECK(EOnJoinSessionCompleteResult::Type::Success == InJoinSessionComplete);`
- L20 _public enumerator_ `enum class EState { Init, RegisterLocalPlayerCall, RegisterLocalPlayerCalled, ClearDelegates, Done } State = EState::Init; FOnRegisterLocalPlayerCompleteDelegate RegisterLocalPlayerDelegate = FOnRegisterLocalPlayerCompleteDelegate::CreateLambda([this](const FUniqueNetId& InPlayer, EOnJoinSessionCompleteResult::Type InJoinSessionComplete) { REQUIRE(State == EState::RegisterLocalPlayerCalled); CHECK(*Player->Get() == InPlayer); CHECK(EOnJoinSessionCompleteResult::Type::Success == InJoinSessionComplete);`
- L20 _public enumerator_ `enum class EState { Init, RegisterLocalPlayerCall, RegisterLocalPlayerCalled, ClearDelegates, Done } State = EState::Init; FOnRegisterLocalPlayerCompleteDelegate RegisterLocalPlayerDelegate = FOnRegisterLocalPlayerCompleteDelegate::CreateLambda([this](const FUniqueNetId& InPlayer, EOnJoinSessionCompleteResult::Type InJoinSessionComplete) { REQUIRE(State == EState::RegisterLocalPlayerCalled); CHECK(*Player->Get() == InPlayer); CHECK(EOnJoinSessionCompleteResult::Type::Success == InJoinSessionComplete);`

### `Source/Programs/Online/OSSTestsCore/Helpers/Session/SessionRegisterPlayerHelper.h` (Other)


#### struct `FSessionRegisterPlayerStep`  
`struct FSessionRegisterPlayerStep : public FTestPipeline::FStep`  
_L10-89_
- inherits: `FTestPipeline::FStep`
- L12 _public function_ `FSessionRegisterPlayerStep(FName InSessionName, FUniqueNetIdPtr* InPlayer, bool bInWasInvited = false) : TestSessionName(InSessionName) , Player(InPlayer) , bWasInvited(bInWasInvited)`
- L18 _public function_ `virtual ~FSessionRegisterPlayerStep()`
- L30 _public member_ `enum class EState { Init, RegisterPlayerCall, RegisterPlayerCalled, ClearDelegates, Done } State = EState::Init;`
- L32 _public member_ `FOnRegisterPlayersCompleteDelegate RegisterPlayerDelegate = FOnRegisterPlayersCompleteDelegate::CreateLambda([this](FName SessionName, const TArray<FUniqueNetIdRef>& Players,bool bWasSuccessful) { REQUIRE(State == EState::RegisterPlayerCalled); CHECK(bWasSuccessful); CHECK(SessionName.ToString() == TestSessionName.ToString()); State = EState::ClearDelegates; });`
- L33 _public function_ ``
- L41 _public function_ `virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override`
- L84 _protected member_ `FName TestSessionName = {};`
- L85 _protected member_ `FUniqueNetIdPtr* Player = nullptr;`
- L86 _protected member_ `bool bWasInvited = false;`
- L87 _protected member_ `FDelegateHandle OnRegisterPlayerCompleteDelegateHandle;`
- L88 _protected member_ `IOnlineSessionPtr OnlineSessionPtr = nullptr;`

#### enum `FSessionRegisterPlayerStep::EState`  
`enum class EState`  
_L30-30_
- L30 _public enumerator_ `enum class EState { Init, RegisterPlayerCall, RegisterPlayerCalled, ClearDelegates, Done } State = EState::Init; FOnRegisterPlayersCompleteDelegate RegisterPlayerDelegate = FOnRegisterPlayersCompleteDelegate::CreateLambda([this](FName SessionName, const TArray<FUniqueNetIdRef>& Players,bool bWasSuccessful) { REQUIRE(State == EState::RegisterPlayerCalled); CHECK(bWasSuccessful); CHECK(SessionName.ToString() == TestSessionName.ToString());`
- L30 _public enumerator_ `enum class EState { Init, RegisterPlayerCall, RegisterPlayerCalled, ClearDelegates, Done } State = EState::Init; FOnRegisterPlayersCompleteDelegate RegisterPlayerDelegate = FOnRegisterPlayersCompleteDelegate::CreateLambda([this](FName SessionName, const TArray<FUniqueNetIdRef>& Players,bool bWasSuccessful) { REQUIRE(State == EState::RegisterPlayerCalled); CHECK(bWasSuccessful); CHECK(SessionName.ToString() == TestSessionName.ToString());`
- L30 _public enumerator_ `enum class EState { Init, RegisterPlayerCall, RegisterPlayerCalled, ClearDelegates, Done } State = EState::Init; FOnRegisterPlayersCompleteDelegate RegisterPlayerDelegate = FOnRegisterPlayersCompleteDelegate::CreateLambda([this](FName SessionName, const TArray<FUniqueNetIdRef>& Players,bool bWasSuccessful) { REQUIRE(State == EState::RegisterPlayerCalled); CHECK(bWasSuccessful); CHECK(SessionName.ToString() == TestSessionName.ToString());`
- L30 _public enumerator_ `enum class EState { Init, RegisterPlayerCall, RegisterPlayerCalled, ClearDelegates, Done } State = EState::Init; FOnRegisterPlayersCompleteDelegate RegisterPlayerDelegate = FOnRegisterPlayersCompleteDelegate::CreateLambda([this](FName SessionName, const TArray<FUniqueNetIdRef>& Players,bool bWasSuccessful) { REQUIRE(State == EState::RegisterPlayerCalled); CHECK(bWasSuccessful); CHECK(SessionName.ToString() == TestSessionName.ToString());`
- L30 _public enumerator_ `enum class EState { Init, RegisterPlayerCall, RegisterPlayerCalled, ClearDelegates, Done } State = EState::Init; FOnRegisterPlayersCompleteDelegate RegisterPlayerDelegate = FOnRegisterPlayersCompleteDelegate::CreateLambda([this](FName SessionName, const TArray<FUniqueNetIdRef>& Players,bool bWasSuccessful) { REQUIRE(State == EState::RegisterPlayerCalled); CHECK(bWasSuccessful); CHECK(SessionName.ToString() == TestSessionName.ToString());`

### `Source/Programs/Online/OSSTestsCore/Helpers/Session/SessionRegisterPlayersHelper.h` (Other)


#### struct `FSessionRegisterPlayersStep`  
`struct FSessionRegisterPlayersStep : public FTestPipeline::FStep`  
_L10-89_
- inherits: `FTestPipeline::FStep`
- L12 _public function_ `FSessionRegisterPlayersStep(FName InSessionName, TArray<FUniqueNetIdRef>* InPlayers, bool bInWasInvited = false) : TestSessionName(InSessionName) , Players(InPlayers) , bWasInvited(bInWasInvited)`
- L18 _public function_ `virtual ~FSessionRegisterPlayersStep()`
- L30 _public member_ `enum class EState { Init, RegisterPlayersCall, RegisterPlayersCalled, ClearDelegates, Done } State = EState::Init;`
- L32 _public member_ `FOnRegisterPlayersCompleteDelegate RegisterPlayersDelegate = FOnRegisterPlayersCompleteDelegate::CreateLambda([this](FName SessionName, const TArray<FUniqueNetIdRef>& InPlayers,bool bWasSuccessful) { REQUIRE(State == EState::RegisterPlayersCalled); CHECK(bWasSuccessful); CHECK(SessionName.ToString() == TestSessionName.ToString()); State = EState::ClearDelegates; });`
- L33 _public function_ ``
- L41 _public function_ `virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override`
- L84 _protected member_ `FName TestSessionName = {};`
- L85 _protected member_ `TArray<FUniqueNetIdRef>* Players = nullptr;`
- L86 _protected member_ `bool bWasInvited = false;`
- L87 _protected member_ `FDelegateHandle OnRegisterPlayersCompleteDelegateHandle;`
- L88 _protected member_ `IOnlineSessionPtr OnlineSessionPtr = nullptr;`

#### enum `FSessionRegisterPlayersStep::EState`  
`enum class EState`  
_L30-30_
- L30 _public enumerator_ `enum class EState { Init, RegisterPlayersCall, RegisterPlayersCalled, ClearDelegates, Done } State = EState::Init; FOnRegisterPlayersCompleteDelegate RegisterPlayersDelegate = FOnRegisterPlayersCompleteDelegate::CreateLambda([this](FName SessionName, const TArray<FUniqueNetIdRef>& InPlayers,bool bWasSuccessful) { REQUIRE(State == EState::RegisterPlayersCalled); CHECK(bWasSuccessful); CHECK(SessionName.ToString() == TestSessionName.ToString());`
- L30 _public enumerator_ `enum class EState { Init, RegisterPlayersCall, RegisterPlayersCalled, ClearDelegates, Done } State = EState::Init; FOnRegisterPlayersCompleteDelegate RegisterPlayersDelegate = FOnRegisterPlayersCompleteDelegate::CreateLambda([this](FName SessionName, const TArray<FUniqueNetIdRef>& InPlayers,bool bWasSuccessful) { REQUIRE(State == EState::RegisterPlayersCalled); CHECK(bWasSuccessful); CHECK(SessionName.ToString() == TestSessionName.ToString());`
- L30 _public enumerator_ `enum class EState { Init, RegisterPlayersCall, RegisterPlayersCalled, ClearDelegates, Done } State = EState::Init; FOnRegisterPlayersCompleteDelegate RegisterPlayersDelegate = FOnRegisterPlayersCompleteDelegate::CreateLambda([this](FName SessionName, const TArray<FUniqueNetIdRef>& InPlayers,bool bWasSuccessful) { REQUIRE(State == EState::RegisterPlayersCalled); CHECK(bWasSuccessful); CHECK(SessionName.ToString() == TestSessionName.ToString());`
- L30 _public enumerator_ `enum class EState { Init, RegisterPlayersCall, RegisterPlayersCalled, ClearDelegates, Done } State = EState::Init; FOnRegisterPlayersCompleteDelegate RegisterPlayersDelegate = FOnRegisterPlayersCompleteDelegate::CreateLambda([this](FName SessionName, const TArray<FUniqueNetIdRef>& InPlayers,bool bWasSuccessful) { REQUIRE(State == EState::RegisterPlayersCalled); CHECK(bWasSuccessful); CHECK(SessionName.ToString() == TestSessionName.ToString());`
- L30 _public enumerator_ `enum class EState { Init, RegisterPlayersCall, RegisterPlayersCalled, ClearDelegates, Done } State = EState::Init; FOnRegisterPlayersCompleteDelegate RegisterPlayersDelegate = FOnRegisterPlayersCompleteDelegate::CreateLambda([this](FName SessionName, const TArray<FUniqueNetIdRef>& InPlayers,bool bWasSuccessful) { REQUIRE(State == EState::RegisterPlayersCalled); CHECK(bWasSuccessful); CHECK(SessionName.ToString() == TestSessionName.ToString());`

### `Source/Programs/Online/OSSTestsCore/Helpers/Session/SessionSendSessionInviteToFriendHelper.h` (Other)


#### struct `FSessionSendSessionInviteToFriendStep`  
`struct FSessionSendSessionInviteToFriendStep : public FTestPipeline::FStep`  
_L11-82_
- inherits: `FTestPipeline::FStep`
- L13 _public function_ `FSessionSendSessionInviteToFriendStep(FUniqueNetIdPtr* InLocalUserId, const FName& InSessionName, FUniqueNetIdPtr* InFriendId) : LocalUserId(InLocalUserId) , FriendId(InFriendId) , SessionName(InSessionName)`
- L19 _public function_ `FSessionSendSessionInviteToFriendStep(int32 InLocalUserNum, const FName& InSessionName, FUniqueNetIdPtr* InFriendId) : LocalUserNum(InLocalUserNum) , FriendId(InFriendId) , SessionName(InSessionName) , bUseOverload(true)`
- L26 _public prototype_ `virtual ~FSessionSendSessionInviteToFriendStep() = default;`
- L28 _public member_ `enum class EState { Init, SendSessionInviteToFriendCall, SendSessionInviteToFriendCalled, ClearDelegates, Done } State = EState::Init;`
- L30 _public function_ `virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override`
- L76 _protected member_ `int32 LocalUserNum = 0;`
- L77 _protected member_ `FUniqueNetIdPtr* LocalUserId = nullptr;`
- L78 _protected member_ `FUniqueNetIdPtr* FriendId = nullptr;`
- L79 _protected member_ `FName SessionName = TEXT("");`
- L80 _protected member_ `bool bUseOverload = false;`
- L81 _protected member_ `IOnlineSessionPtr OnlineSessionPtr = nullptr;`

#### enum `FSessionSendSessionInviteToFriendStep::EState`  
`enum class EState`  
_L28-28_
- L28 _public enumerator_ `enum class EState { Init, SendSessionInviteToFriendCall, SendSessionInviteToFriendCalled, ClearDelegates, Done } State = EState::Init; virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override { switch (State) { case EState::Init: {`
- L28 _public enumerator_ `enum class EState { Init, SendSessionInviteToFriendCall, SendSessionInviteToFriendCalled, ClearDelegates, Done } State = EState::Init; virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override { switch (State) { case EState::Init: {`
- L28 _public enumerator_ `enum class EState { Init, SendSessionInviteToFriendCall, SendSessionInviteToFriendCalled, ClearDelegates, Done } State = EState::Init; virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override { switch (State) { case EState::Init: {`
- L28 _public enumerator_ `enum class EState { Init, SendSessionInviteToFriendCall, SendSessionInviteToFriendCalled, ClearDelegates, Done } State = EState::Init; virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override { switch (State) { case EState::Init: {`
- L28 _public enumerator_ `enum class EState { Init, SendSessionInviteToFriendCall, SendSessionInviteToFriendCalled, ClearDelegates, Done } State = EState::Init; virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override { switch (State) { case EState::Init: {`

### `Source/Programs/Online/OSSTestsCore/Helpers/Session/SessionStartSessionHelper.h` (Other)


#### struct `FSessionStartSessionStep`  
`struct FSessionStartSessionStep : public FTestPipeline::FStep`  
_L11-86_
- inherits: `FTestPipeline::FStep`
- L13 _public function_ `FSessionStartSessionStep(FName InSessionName) : SessionName(InSessionName)`
- L17 _public function_ `virtual ~FSessionStartSessionStep()`
- L29 _public member_ `enum class EState { Init, StartSessionCall, StartSessionCalled, ClearDelegates, Done } State = EState::Init;`
- L31 _public member_ `FOnStartSessionCompleteDelegate StartSessionDelegate = FOnStartSessionCompleteDelegate::CreateLambda([this](FName InSessionName, bool bWasSuccessful) { REQUIRE(State == EState::StartSessionCalled); CHECK(bWasSuccessful); CHECK(SessionName.ToString() == InSessionName.ToString()); State = EState::ClearDelegates; });`
- L32 _public function_ ``
- L40 _public function_ `virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override`
- L83 _protected member_ `FName SessionName = {};`
- L84 _protected member_ `FDelegateHandle OnStartSessionCompleteDelegateHandle;`
- L85 _protected member_ `IOnlineSessionPtr OnlineSessionPtr = nullptr;`

#### enum `FSessionStartSessionStep::EState`  
`enum class EState`  
_L29-29_
- L29 _public enumerator_ `enum class EState { Init, StartSessionCall, StartSessionCalled, ClearDelegates, Done } State = EState::Init; FOnStartSessionCompleteDelegate StartSessionDelegate = FOnStartSessionCompleteDelegate::CreateLambda([this](FName InSessionName, bool bWasSuccessful) { REQUIRE(State == EState::StartSessionCalled); CHECK(bWasSuccessful); CHECK(SessionName.ToString() == InSessionName.ToString());`
- L29 _public enumerator_ `enum class EState { Init, StartSessionCall, StartSessionCalled, ClearDelegates, Done } State = EState::Init; FOnStartSessionCompleteDelegate StartSessionDelegate = FOnStartSessionCompleteDelegate::CreateLambda([this](FName InSessionName, bool bWasSuccessful) { REQUIRE(State == EState::StartSessionCalled); CHECK(bWasSuccessful); CHECK(SessionName.ToString() == InSessionName.ToString());`
- L29 _public enumerator_ `enum class EState { Init, StartSessionCall, StartSessionCalled, ClearDelegates, Done } State = EState::Init; FOnStartSessionCompleteDelegate StartSessionDelegate = FOnStartSessionCompleteDelegate::CreateLambda([this](FName InSessionName, bool bWasSuccessful) { REQUIRE(State == EState::StartSessionCalled); CHECK(bWasSuccessful); CHECK(SessionName.ToString() == InSessionName.ToString());`
- L29 _public enumerator_ `enum class EState { Init, StartSessionCall, StartSessionCalled, ClearDelegates, Done } State = EState::Init; FOnStartSessionCompleteDelegate StartSessionDelegate = FOnStartSessionCompleteDelegate::CreateLambda([this](FName InSessionName, bool bWasSuccessful) { REQUIRE(State == EState::StartSessionCalled); CHECK(bWasSuccessful); CHECK(SessionName.ToString() == InSessionName.ToString());`
- L29 _public enumerator_ `enum class EState { Init, StartSessionCall, StartSessionCalled, ClearDelegates, Done } State = EState::Init; FOnStartSessionCompleteDelegate StartSessionDelegate = FOnStartSessionCompleteDelegate::CreateLambda([this](FName InSessionName, bool bWasSuccessful) { REQUIRE(State == EState::StartSessionCalled); CHECK(bWasSuccessful); CHECK(SessionName.ToString() == InSessionName.ToString());`

### `Source/Programs/Online/OSSTestsCore/Helpers/Session/SessionUnregisterLocalPlayerHelper.h` (Other)


#### struct `FSessionUnregisterLocalPlayerStep`  
`struct FSessionUnregisterLocalPlayerStep : public FTestPipeline::FStep`  
_L10-71_
- inherits: `FTestPipeline::FStep`
- L12 _public function_ `FSessionUnregisterLocalPlayerStep(FUniqueNetIdPtr* InPlayer, FName InSessionName) : TestSessionName(InSessionName) , Player(InPlayer)`
- L17 _public prototype_ `virtual ~FSessionUnregisterLocalPlayerStep() = default;`
- L19 _public member_ `enum class EState { Init, UnregisterLocalPlayerCall, UnregisterLocalPlayerCalled, ClearDelegates, Done } State = EState::Init;`
- L21 _public member_ `FOnUnregisterLocalPlayerCompleteDelegate UnregisterLocalPlayerDelegate = FOnUnregisterLocalPlayerCompleteDelegate::CreateLambda([this](const FUniqueNetId& InPlayer, const bool bWasSuccessful) { REQUIRE(State == EState::UnregisterLocalPlayerCalled); CHECK(*Player->Get() == InPlayer); CHECK(bWasSuccessful); State = EState::ClearDelegates; });`
- L22 _public function_ ``
- L30 _public function_ `virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override`
- L68 _protected member_ `FName TestSessionName = {};`
- L69 _protected member_ `FUniqueNetIdPtr* Player = nullptr;`
- L70 _protected member_ `IOnlineSessionPtr OnlineSessionPtr = nullptr;`

#### enum `FSessionUnregisterLocalPlayerStep::EState`  
`enum class EState`  
_L19-19_
- L19 _public enumerator_ `enum class EState { Init, UnregisterLocalPlayerCall, UnregisterLocalPlayerCalled, ClearDelegates, Done } State = EState::Init; FOnUnregisterLocalPlayerCompleteDelegate UnregisterLocalPlayerDelegate = FOnUnregisterLocalPlayerCompleteDelegate::CreateLambda([this](const FUniqueNetId& InPlayer, const bool bWasSuccessful) { REQUIRE(State == EState::UnregisterLocalPlayerCalled); CHECK(*Player->Get() == InPlayer); CHECK(bWasSuccessful);`
- L19 _public enumerator_ `enum class EState { Init, UnregisterLocalPlayerCall, UnregisterLocalPlayerCalled, ClearDelegates, Done } State = EState::Init; FOnUnregisterLocalPlayerCompleteDelegate UnregisterLocalPlayerDelegate = FOnUnregisterLocalPlayerCompleteDelegate::CreateLambda([this](const FUniqueNetId& InPlayer, const bool bWasSuccessful) { REQUIRE(State == EState::UnregisterLocalPlayerCalled); CHECK(*Player->Get() == InPlayer); CHECK(bWasSuccessful);`
- L19 _public enumerator_ `enum class EState { Init, UnregisterLocalPlayerCall, UnregisterLocalPlayerCalled, ClearDelegates, Done } State = EState::Init; FOnUnregisterLocalPlayerCompleteDelegate UnregisterLocalPlayerDelegate = FOnUnregisterLocalPlayerCompleteDelegate::CreateLambda([this](const FUniqueNetId& InPlayer, const bool bWasSuccessful) { REQUIRE(State == EState::UnregisterLocalPlayerCalled); CHECK(*Player->Get() == InPlayer); CHECK(bWasSuccessful);`
- L19 _public enumerator_ `enum class EState { Init, UnregisterLocalPlayerCall, UnregisterLocalPlayerCalled, ClearDelegates, Done } State = EState::Init; FOnUnregisterLocalPlayerCompleteDelegate UnregisterLocalPlayerDelegate = FOnUnregisterLocalPlayerCompleteDelegate::CreateLambda([this](const FUniqueNetId& InPlayer, const bool bWasSuccessful) { REQUIRE(State == EState::UnregisterLocalPlayerCalled); CHECK(*Player->Get() == InPlayer); CHECK(bWasSuccessful);`
- L19 _public enumerator_ `enum class EState { Init, UnregisterLocalPlayerCall, UnregisterLocalPlayerCalled, ClearDelegates, Done } State = EState::Init; FOnUnregisterLocalPlayerCompleteDelegate UnregisterLocalPlayerDelegate = FOnUnregisterLocalPlayerCompleteDelegate::CreateLambda([this](const FUniqueNetId& InPlayer, const bool bWasSuccessful) { REQUIRE(State == EState::UnregisterLocalPlayerCalled); CHECK(*Player->Get() == InPlayer); CHECK(bWasSuccessful);`

### `Source/Programs/Online/OSSTestsCore/Helpers/Session/SessionUnregisterPlayerHelper.h` (Other)


#### struct `FSessionUnregisterPlayerStep`  
`struct FSessionUnregisterPlayerStep : public FTestPipeline::FStep`  
_L10-88_
- inherits: `FTestPipeline::FStep`
- L12 _public function_ `FSessionUnregisterPlayerStep(FName InSessionName, FUniqueNetIdPtr* InPlayer) : TestSessionName(InSessionName) , Player(InPlayer)`
- L17 _public function_ `virtual ~FSessionUnregisterPlayerStep()`
- L29 _public member_ `enum class EState { Init, UnregisterPlayerCall, UnregisterPlayerCalled, ClearDelegates, Done } State = EState::Init;`
- L31 _public member_ `FOnUnregisterPlayersCompleteDelegate UnregisterPlayerDelegate = FOnUnregisterPlayersCompleteDelegate::CreateLambda([this](FName SessionName, const TArray<FUniqueNetIdRef>& Players, bool bWasSuccessful) { REQUIRE(State == EState::UnregisterPlayerCalled); CHECK(bWasSuccessful); CHECK(SessionName.ToString() == TestSessionName.ToString()); State = EState::ClearDelegates; });`
- L32 _public function_ ``
- L40 _public function_ `virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override`
- L84 _protected member_ `FName TestSessionName = {};`
- L85 _protected member_ `FUniqueNetIdPtr* Player = nullptr;`
- L86 _protected member_ `FDelegateHandle OnUnregisterPlayerCompleteDelegateHandle;`
- L87 _protected member_ `IOnlineSessionPtr OnlineSessionPtr = nullptr;`

#### enum `FSessionUnregisterPlayerStep::EState`  
`enum class EState`  
_L29-29_
- L29 _public enumerator_ `enum class EState { Init, UnregisterPlayerCall, UnregisterPlayerCalled, ClearDelegates, Done } State = EState::Init; FOnUnregisterPlayersCompleteDelegate UnregisterPlayerDelegate = FOnUnregisterPlayersCompleteDelegate::CreateLambda([this](FName SessionName, const TArray<FUniqueNetIdRef>& Players, bool bWasSuccessful) { REQUIRE(State == EState::UnregisterPlayerCalled); CHECK(bWasSuccessful); CHECK(SessionName.ToString() == TestSessionName.ToString());`
- L29 _public enumerator_ `enum class EState { Init, UnregisterPlayerCall, UnregisterPlayerCalled, ClearDelegates, Done } State = EState::Init; FOnUnregisterPlayersCompleteDelegate UnregisterPlayerDelegate = FOnUnregisterPlayersCompleteDelegate::CreateLambda([this](FName SessionName, const TArray<FUniqueNetIdRef>& Players, bool bWasSuccessful) { REQUIRE(State == EState::UnregisterPlayerCalled); CHECK(bWasSuccessful); CHECK(SessionName.ToString() == TestSessionName.ToString());`
- L29 _public enumerator_ `enum class EState { Init, UnregisterPlayerCall, UnregisterPlayerCalled, ClearDelegates, Done } State = EState::Init; FOnUnregisterPlayersCompleteDelegate UnregisterPlayerDelegate = FOnUnregisterPlayersCompleteDelegate::CreateLambda([this](FName SessionName, const TArray<FUniqueNetIdRef>& Players, bool bWasSuccessful) { REQUIRE(State == EState::UnregisterPlayerCalled); CHECK(bWasSuccessful); CHECK(SessionName.ToString() == TestSessionName.ToString());`
- L29 _public enumerator_ `enum class EState { Init, UnregisterPlayerCall, UnregisterPlayerCalled, ClearDelegates, Done } State = EState::Init; FOnUnregisterPlayersCompleteDelegate UnregisterPlayerDelegate = FOnUnregisterPlayersCompleteDelegate::CreateLambda([this](FName SessionName, const TArray<FUniqueNetIdRef>& Players, bool bWasSuccessful) { REQUIRE(State == EState::UnregisterPlayerCalled); CHECK(bWasSuccessful); CHECK(SessionName.ToString() == TestSessionName.ToString());`
- L29 _public enumerator_ `enum class EState { Init, UnregisterPlayerCall, UnregisterPlayerCalled, ClearDelegates, Done } State = EState::Init; FOnUnregisterPlayersCompleteDelegate UnregisterPlayerDelegate = FOnUnregisterPlayersCompleteDelegate::CreateLambda([this](FName SessionName, const TArray<FUniqueNetIdRef>& Players, bool bWasSuccessful) { REQUIRE(State == EState::UnregisterPlayerCalled); CHECK(bWasSuccessful); CHECK(SessionName.ToString() == TestSessionName.ToString());`

### `Source/Programs/Online/OSSTestsCore/Helpers/Session/SessionUnregisterPlayersHelper.h` (Other)


#### struct `FSessionUnregisterPlayersStep`  
`struct FSessionUnregisterPlayersStep : public FTestPipeline::FStep`  
_L10-88_
- inherits: `FTestPipeline::FStep`
- L12 _public function_ `FSessionUnregisterPlayersStep(FName InSessionName, TArray<FUniqueNetIdRef>* InPlayers) : TestSessionName(InSessionName) , Players(InPlayers)`
- L17 _public function_ `virtual ~FSessionUnregisterPlayersStep()`
- L29 _public member_ `enum class EState { Init, UnregisterPlayersCall, UnregisterPlayersCalled, ClearDelegates, Done } State = EState::Init;`
- L31 _public member_ `FOnUnregisterPlayersCompleteDelegate UnregisterPlayersDelegate = FOnUnregisterPlayersCompleteDelegate::CreateLambda([this](FName SessionName, const TArray<FUniqueNetIdRef>& InPlayers, bool bWasSuccessful) { REQUIRE(State == EState::UnregisterPlayersCalled); CHECK(bWasSuccessful); CHECK(SessionName.ToString() == TestSessionName.ToString()); State = EState::ClearDelegates; });`
- L32 _public function_ ``
- L40 _public function_ `virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override`
- L84 _protected member_ `FName TestSessionName = {};`
- L85 _protected member_ `TArray<FUniqueNetIdRef>* Players = nullptr;`
- L86 _protected member_ `FDelegateHandle OnUnregisterPlayersCompleteDelegateHandle;`
- L87 _protected member_ `IOnlineSessionPtr OnlineSessionPtr = nullptr;`

#### enum `FSessionUnregisterPlayersStep::EState`  
`enum class EState`  
_L29-29_
- L29 _public enumerator_ `enum class EState { Init, UnregisterPlayersCall, UnregisterPlayersCalled, ClearDelegates, Done } State = EState::Init; FOnUnregisterPlayersCompleteDelegate UnregisterPlayersDelegate = FOnUnregisterPlayersCompleteDelegate::CreateLambda([this](FName SessionName, const TArray<FUniqueNetIdRef>& InPlayers, bool bWasSuccessful) { REQUIRE(State == EState::UnregisterPlayersCalled); CHECK(bWasSuccessful); CHECK(SessionName.ToString() == TestSessionName.ToString());`
- L29 _public enumerator_ `enum class EState { Init, UnregisterPlayersCall, UnregisterPlayersCalled, ClearDelegates, Done } State = EState::Init; FOnUnregisterPlayersCompleteDelegate UnregisterPlayersDelegate = FOnUnregisterPlayersCompleteDelegate::CreateLambda([this](FName SessionName, const TArray<FUniqueNetIdRef>& InPlayers, bool bWasSuccessful) { REQUIRE(State == EState::UnregisterPlayersCalled); CHECK(bWasSuccessful); CHECK(SessionName.ToString() == TestSessionName.ToString());`
- L29 _public enumerator_ `enum class EState { Init, UnregisterPlayersCall, UnregisterPlayersCalled, ClearDelegates, Done } State = EState::Init; FOnUnregisterPlayersCompleteDelegate UnregisterPlayersDelegate = FOnUnregisterPlayersCompleteDelegate::CreateLambda([this](FName SessionName, const TArray<FUniqueNetIdRef>& InPlayers, bool bWasSuccessful) { REQUIRE(State == EState::UnregisterPlayersCalled); CHECK(bWasSuccessful); CHECK(SessionName.ToString() == TestSessionName.ToString());`
- L29 _public enumerator_ `enum class EState { Init, UnregisterPlayersCall, UnregisterPlayersCalled, ClearDelegates, Done } State = EState::Init; FOnUnregisterPlayersCompleteDelegate UnregisterPlayersDelegate = FOnUnregisterPlayersCompleteDelegate::CreateLambda([this](FName SessionName, const TArray<FUniqueNetIdRef>& InPlayers, bool bWasSuccessful) { REQUIRE(State == EState::UnregisterPlayersCalled); CHECK(bWasSuccessful); CHECK(SessionName.ToString() == TestSessionName.ToString());`
- L29 _public enumerator_ `enum class EState { Init, UnregisterPlayersCall, UnregisterPlayersCalled, ClearDelegates, Done } State = EState::Init; FOnUnregisterPlayersCompleteDelegate UnregisterPlayersDelegate = FOnUnregisterPlayersCompleteDelegate::CreateLambda([this](FName SessionName, const TArray<FUniqueNetIdRef>& InPlayers, bool bWasSuccessful) { REQUIRE(State == EState::UnregisterPlayersCalled); CHECK(bWasSuccessful); CHECK(SessionName.ToString() == TestSessionName.ToString());`

### `Source/Programs/Online/OSSTestsCore/Helpers/Session/SessionUpdateSessionHelper.h` (Other)


#### struct `FSessionUpdateSessionStep`  
`struct FSessionUpdateSessionStep : public FTestPipeline::FStep`  
_L11-91_
- inherits: `FTestPipeline::FStep`
- L13 _public function_ `FSessionUpdateSessionStep(FName InSessionName, FOnlineSessionSettings& InUpdatedSessionSettings, bool bInShouldRefreshOnlineData) : TestSessionName(InSessionName) , NewSessionSettings(InUpdatedSessionSettings) , bShouldRefreshOnlineData(bInShouldRefreshOnlineData)`
- L19 _public function_ `virtual ~FSessionUpdateSessionStep()`
- L31 _public member_ `enum class EState { Init, UpdateSessionCall, UpdateSessionCalled, ClearDelegates, Done } State = EState::Init;`
- L33 _public member_ `FOnUpdateSessionCompleteDelegate UpdateSessionDelegate = FOnUpdateSessionCompleteDelegate::CreateLambda([this](FName SessionName, bool bWasSuccessful) { REQUIRE(State == EState::UpdateSessionCalled); CHECK(bWasSuccessful); CHECK(SessionName.ToString() == TestSessionName.ToString()); State = EState::ClearDelegates; });`
- L34 _public function_ ``
- L42 _public function_ `virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override`
- L86 _protected member_ `FName TestSessionName = {};`
- L87 _protected member_ `FOnlineSessionSettings NewSessionSettings = {};`
- L88 _protected member_ `bool bShouldRefreshOnlineData = false;`
- L89 _protected member_ `FDelegateHandle OnUpdateSessionCompleteDelegateHandle;`
- L90 _protected member_ `IOnlineSessionPtr OnlineSessionPtr = nullptr;`

#### enum `FSessionUpdateSessionStep::EState`  
`enum class EState`  
_L31-31_
- L31 _public enumerator_ `enum class EState { Init, UpdateSessionCall, UpdateSessionCalled, ClearDelegates, Done } State = EState::Init; FOnUpdateSessionCompleteDelegate UpdateSessionDelegate = FOnUpdateSessionCompleteDelegate::CreateLambda([this](FName SessionName, bool bWasSuccessful) { REQUIRE(State == EState::UpdateSessionCalled); CHECK(bWasSuccessful); CHECK(SessionName.ToString() == TestSessionName.ToString());`
- L31 _public enumerator_ `enum class EState { Init, UpdateSessionCall, UpdateSessionCalled, ClearDelegates, Done } State = EState::Init; FOnUpdateSessionCompleteDelegate UpdateSessionDelegate = FOnUpdateSessionCompleteDelegate::CreateLambda([this](FName SessionName, bool bWasSuccessful) { REQUIRE(State == EState::UpdateSessionCalled); CHECK(bWasSuccessful); CHECK(SessionName.ToString() == TestSessionName.ToString());`
- L31 _public enumerator_ `enum class EState { Init, UpdateSessionCall, UpdateSessionCalled, ClearDelegates, Done } State = EState::Init; FOnUpdateSessionCompleteDelegate UpdateSessionDelegate = FOnUpdateSessionCompleteDelegate::CreateLambda([this](FName SessionName, bool bWasSuccessful) { REQUIRE(State == EState::UpdateSessionCalled); CHECK(bWasSuccessful); CHECK(SessionName.ToString() == TestSessionName.ToString());`
- L31 _public enumerator_ `enum class EState { Init, UpdateSessionCall, UpdateSessionCalled, ClearDelegates, Done } State = EState::Init; FOnUpdateSessionCompleteDelegate UpdateSessionDelegate = FOnUpdateSessionCompleteDelegate::CreateLambda([this](FName SessionName, bool bWasSuccessful) { REQUIRE(State == EState::UpdateSessionCalled); CHECK(bWasSuccessful); CHECK(SessionName.ToString() == TestSessionName.ToString());`
- L31 _public enumerator_ `enum class EState { Init, UpdateSessionCall, UpdateSessionCalled, ClearDelegates, Done } State = EState::Init; FOnUpdateSessionCompleteDelegate UpdateSessionDelegate = FOnUpdateSessionCompleteDelegate::CreateLambda([this](FName SessionName, bool bWasSuccessful) { REQUIRE(State == EState::UpdateSessionCalled); CHECK(bWasSuccessful); CHECK(SessionName.ToString() == TestSessionName.ToString());`

### `Source/Programs/Online/OSSTestsCore/Helpers/TickForTime.h` (Other)


#### struct `FTickForTime`  
`struct FTickForTime : public FTestPipeline::FStep`  
_L7-40_
- inherits: `FTestPipeline::FStep`
- L10 _public function_ `FTickForTime(const FTimespan InTimeToWaitMilliseconds) : TimeToWaitMilliseconds(InTimeToWaitMilliseconds)`
- L15 _public function_ `virtual EContinuance Tick(IOnlineSubsystem* OnlineSubsystem) override`
- L34 _public prototype_ `virtual ~FTickForTime() = default;`
- L37 _protected member_ `double StartTime;`
- L38 _protected member_ `bool bHasSetStartTime = false;`
- L39 _protected member_ `FTimespan TimeToWaitMilliseconds;`

### `Source/Programs/Online/OSSTestsCore/OnlineSubsystemCatchHelper.h` (Other)


#### class `FOnlineSubsystemFixtureInvoker`  
`class FOnlineSubsystemFixtureInvoker : public Catch::ITestInvoker`  
_L16-79_
- inherits: `Catch::ITestInvoker`
- L41 _public prototype_ `virtual void invoke() const = 0;`
- L43 _public prototype_ `virtual Catch::Detail::unique_ptr<FOnlineSubsystemFixtureInvoker> clone() = 0;`
- L45 _public prototype_ `void SetSubsystem(const FString& InStoredSubsystem);`
- L48 _public prototype_ `static TArray<FApplicableServicesConfig> GetApplicableServices();` — TODO: This should poll some info from the tags and generate the list based on that
- L49 _public prototype_ `static TArray<FApplicableSubsystemConfig> GetApplicableSubsystems();`
- L59 _public prototype_ `static bool CheckAllTagsIsIn(const TArray<FString>& TestTags, const FString& RawTagString);` — Helper function that calls CheckAllTagsIsIn(const TArray<FString>&, const TArray<FString>&); @param  TestTags			The array of test tags we wish to test against. @param  RawTagString		Comma seperated string of elemnets we wish to convert to an array. @return true if all elements of RawTagString prased as an comma sperated array is in TestTags.
- L69 _public prototype_ `static bool CheckAllTagsIsIn(const TArray<FString>& TestTags, const TArray<FString>& InputTags);` — Checks if every element of InputTags is in TestTags. @param  TestTags       The array of test tags we wish to test against. @param  InputTags	  The array of tags we wish to see if all elements of are present in TestTags. @return  true if all elements of InputTags is in TestTags.
- L71 _public prototype_ `static FString GenerateTags(const FString& ServiceName, const FReportingSkippableTags& SkippableTags, const TCHAR* InTag);`
- L73 _public prototype_ `static EDisableReason ShouldDisableTest(const FString& ServiceName, const FReportingSkippableTags& SkippableTags, FString& InTag);`
- L74 _public prototype_ `static EDisableReason ShouldSkipTest(const FString& ServiceName, const FReportingSkippableTags& SkippableTags, FString& InTag);`
- L75 _public prototype_ `static bool IsRunningTestSkipOnTags(const FString& ServiceName, const FReportingSkippableTags& SkippableTags, FString& InTag);`
- L78 _protected member_ `FString StoredSubsystem;`

#### struct `FOnlineSubsystemFixtureInvoker::FReportingSkippableTags`  
`struct FReportingSkippableTags`  
_L20-25_
- L22 _public member_ `TArray<FString> MayFailTags;`
- L23 _public member_ `TArray<FString> ShouldFailTags;`
- L24 _public member_ `TArray<FString> DisableTestTags;`

#### struct `FOnlineSubsystemFixtureInvoker::FApplicableServicesConfig`  
`struct FApplicableServicesConfig`  
_L27-32_
- L29 _public member_ `FString Tag;`
- L30 _public member_ `UE::Online::EOnlineServices ServicesType;`
- L31 _public member_ `TArray<FString> ModulesToLoad;`

#### struct `FOnlineSubsystemFixtureInvoker::FApplicableSubsystemConfig`  
`struct FApplicableSubsystemConfig`  
_L34-37_
- L36 _public member_ `FString Name;`

#### enum `FOnlineSubsystemFixtureInvoker::EDisableReason`  
`enum class EDisableReason`  
_L39-39_
- L39 _public enumerator_ `enum class EDisableReason { Success, AgainstService, ExclusiveService, DisableTagPresence }; virtual void invoke() const = 0; virtual Catch::Detail::unique_ptr<FOnlineSubsystemFixtureInvoker> clone() = 0; void SetSubsystem(const FString& InStoredSubsystem);`
- L39 _public enumerator_ `enum class EDisableReason { Success, AgainstService, ExclusiveService, DisableTagPresence }; virtual void invoke() const = 0; virtual Catch::Detail::unique_ptr<FOnlineSubsystemFixtureInvoker> clone() = 0; void SetSubsystem(const FString& InStoredSubsystem);`
- L39 _public enumerator_ `enum class EDisableReason { Success, AgainstService, ExclusiveService, DisableTagPresence }; virtual void invoke() const = 0; virtual Catch::Detail::unique_ptr<FOnlineSubsystemFixtureInvoker> clone() = 0; void SetSubsystem(const FString& InStoredSubsystem);`
- L39 _public enumerator_ `enum class EDisableReason { Success, AgainstService, ExclusiveService, DisableTagPresence }; virtual void invoke() const = 0; virtual Catch::Detail::unique_ptr<FOnlineSubsystemFixtureInvoker> clone() = 0; void SetSubsystem(const FString& InStoredSubsystem);`

#### class `TestInvokerFixture`  
`template <typename C> class TestInvokerFixture : public FOnlineSubsystemFixtureInvoker`  
_L82-117_
- inherits: `FOnlineSubsystemFixtureInvoker`
- L85 _public function_ `constexpr TestInvokerFixture(void (C::* InTestAsMethod)()) noexcept : TestAsMethod(InTestAsMethod)`
- L90 _public function_ `void PrepareTestCase() const`
- L96 _public function_ `void TearDownTestCase() const`
- L101 _public function_ `void invoke() const override`
- L109 _public function_ `Catch::Detail::unique_ptr<FOnlineSubsystemFixtureInvoker> clone() override`
- L115 _private member_ `void (C::* TestAsMethod)();`
- L116 _private member_ `mutable Catch::Detail::unique_ptr<C> Fixture = nullptr;`

#### class `FOnlineSubsystemTestBaseFixture`  
`class FOnlineSubsystemTestBaseFixture : public Catch::ITestInvoker`  
_L124-178_
- inherits: `Catch::ITestInvoker`
- L127 _public prototype_ `void ConstructInternal(FString ServiceName);`
- L128 _public prototype_ `virtual ~FOnlineSubsystemTestBaseFixture();`
- L131 _public prototype_ `static void LoadServiceModules();` — Loads all necessary services for the current test run
- L134 _public prototype_ `static void UnloadServiceModules();` — Unloads all necessary services for the current test run
- L138 _protected prototype_ `FOnlineSubsystemTestBaseFixture();`
- L140 _protected prototype_ `FString GetSubsystem() const;`
- L142 _protected prototype_ `IOnlineSubsystem* GetSubsystemPtr() const;`
- L144 _protected prototype_ `virtual void DestroyCurrentOnlineSubsystemModule() const;`
- L147 _protected prototype_ `TArray<FOnlineAccountCredentials> CustomCredentials(int32 TestAccountIndex, int32 NumUsers) const;`
- L150 _protected prototype_ `TArray<FOnlineAccountCredentials> GetIniCredentials(int32 TestAccountIndex) const;`
- L152 _protected prototype_ `TArray<FOnlineAccountCredentials> GetCredentials(int32 TestAccountIndex, int32 NumUsers) const;`
- L155 _protected prototype_ `void AssignLoginUsers(int32 LocalUserNum, FUniqueNetIdPtr& OutAccountId) const;` — Attempts to assign OutAccountId to what LocalUserId is logged in as.
- L157 _protected prototype_ `FTestPipeline& GetLoginPipeline(uint32 NumUsersToLogin = 1, bool MultiLogin = false) const;`
- L158 _protected prototype_ `FTestPipeline& GetLoginPipeline(uint32 TestAccountIndex, std::initializer_list<std::reference_wrapper<FUniqueNetIdPtr>> AccountIds) const;`
- L159 _protected prototype_ `FTestPipeline& GetLoginPipeline(std::initializer_list<std::reference_wrapper<FUniqueNetIdPtr>> AccountIds) const;`
- L160 _protected prototype_ `FTestPipeline& GetPipeline() const;`
- L163 _protected prototype_ `FString GetLoginCredentialCategory() const;` — Returns the ini login category name for the configured service
- L165 _protected prototype_ `void RunToCompletion(bool bLogout = true, bool bWaitBeforeLogout = false, const FTimespan TimeToWaitMilliseconds = FTimespan::FromMilliseconds(1000), const FString SubsystemInstanceName = TEXT("")) const;`
- L168 _protected prototype_ `virtual void invoke() const override = 0;` — ITestInvoker
- L171 _private member_ `FString Tags;`
- L172 _private member_ `FString Subsystem;`
- L174 _private member_ `mutable FTestDriver Driver;` — Catch's ITestInvoker is a const interface but we'll be changing stuff (emplacing steps into the driver, setting flags, etc.) so we make these mutable
- L175 _private member_ `mutable FTestPipeline Pipeline;`
- L176 _private member_ `mutable uint32 NumLocalUsers = -1;`
- L177 _private member_ `mutable uint32 NumUsersToLogout = -1;`

#### class `FOnlineSubsystemAutoReg`  
`class FOnlineSubsystemAutoReg`  
_L180-185_
- L184 _public prototype_ `FOnlineSubsystemAutoReg(Catch::Detail::unique_ptr<FOnlineSubsystemFixtureInvoker> TestInvoker, Catch::SourceLineInfo LineInfo, const char* Name, const char* Tags, const char* AddlOnlineInfo);` — This code is kept identical to Catch internals so that there is as little deviation from OSS_TESTS and Online_OSS_TESTS as possible

#### Free symbols / members of external scopes

- L120 _function_ `template<typename C> Catch::Detail::unique_ptr<FOnlineSubsystemFixtureInvoker> MakeTestInvokerFixture(void (C::* TestAsMethod)())`
- L187 _prototype_ `TArray<TFunction<void()>>* GetGlobalInitalizers();`
- L189 _macro_ `#define INTERNAL_ONLINESUBSYSTEM_TEST_CASE_NAMED_FIXTURE(RegName, ClassName, Name, Tags, ...)\`
- L204 _macro_ `#define ONLINESUBSYSTEM_TEST_CASE_FIXTURE(ClassName, Name, Tags, ...) \`
- L207 _macro_ `#define ONLINESUBSYSTEM_TEST_CASE(Name, Tags, ...) \`
- L210 _macro_ `#define REQUIRE_OP(Op)\`

### `Source/Programs/Online/OSSTestsCore/TestDriver.h` (Other)


#### struct `FPipelineTestContextInitOptions`  
`struct FPipelineTestContextInitOptions`  
_L22-26_
- L24 _public member_ `FString SubsystemType;`
- L25 _public member_ `FString InstanceName;`

#### class `FPipelineTestContext`  
`class FPipelineTestContext`  
_L28-40_
- L32 _public member_ `FPipelineTestContextInitOptions InitOptions;`
- L34 _public function_ `FPipelineTestContext(const FString& SubsystemType, const FString& InstanceName = TEXT(""))`

#### class `FTestPipeline`  
`class FTestPipeline`  
_L45-226_
- L114 _public typedef_ `using FStepPtr = TUniquePtr<FStep>;`
- L133 _public prototype_ `FTestPipeline(FTestPipeline&&) = default;`
- L134 _public prototype_ `FTestPipeline(const FTestPipeline&) = delete;`
- L137 _public function_ `FTestPipeline&& WithTimeout(FTimespan&& InTimeout)` — Adds an overall test timeout value to the pipeline.
- L144 _public function_ `FTestPipeline&& WithoutEvaluateTickCheck()` — Disables the per tick timer checks.
- L151 _public function_ `FTestPipeline&& WithEvaluateTickCheck(FTimespan&& InExpectedAverageTick, FTimespan&& InAbsoluteMaximumTick, uint32_t InMinimumTickCount = 10)` — Changes and enables the per tick timer checks based on the provided arguments.
- L159 _public function_ `template <typename T, typename... TArguments> FTestPipeline&& EmplaceStep(TArguments&&... Args)` — Adds a test step.
- L169 _public function_ `FTestPipeline&& EmplaceLambda(TUniqueFunction<void(IOnlineSubsystem*)> Lambda)`
- L175 _public prototype_ `FString InfoString() const;` — Generates a string suitable for INFO which will help identify where and when a specific failure has occurred.
- L177 _public prototype_ `void operator()(IOnlineSubsystem* Subsystem);`
- L179 _public prototype_ `void OnPreRelease();`
- L182 _public function_ `void EvaluatePlatformTickTime(const FTimespan& InDuration)` — Given the time points before Tick and after, perform the configured excess tick check.
- L187 _public function_ `void Start()`
- L193 _private function_ `FTestPipeline(FTestDriver& InDriver, FTimespan&& InTimeout) : Driver(InDriver) , PipelineTimeout(MoveTemp(InTimeout))`
- L199 _private function_ `FTestPipeline(FTestDriver& InDriver, FTimespan&& InTimeout, FEvaluateTickConfig&& InEvaluateTickConfig) : Driver(InDriver) , PipelineTimeout(MoveTemp(InTimeout)) , EvaluateTickConfig(MoveTemp(InEvaluateTickConfig))`
- L207 _private prototype_ `void EvaluatePlatformTickTime(double&& TickTime);` — Given the duration of the call to Tick, perform the configured excess tick check.
- L208 _private prototype_ `bool CheckStepTimedOut(FStepPtr& Step, double CurrentTime, IOnlineSubsystem* Subsystem);`
- L211 _private member_ `FTestDriver& Driver;`
- L212 _private member_ `TArray<FStepPtr> TestSteps;`
- L213 _private member_ `TArray<FStepPtr> CompletedSteps;`
- L214 _private member_ `TArray<FStepPtr> TimedoutSteps;`
- L215 _private member_ `TArray<FStepPtr> DeletePostReleaseSteps;`
- L216 _private member_ `FTimespan PipelineTimeout;`
- L217 _private member_ `double PipelineStartTime;`
- L219 _private member_ `FEvaluateTickConfig EvaluateTickConfig;` — Current excess tick config.
- L221 _private member_ `FTimespan SubsystemTickSum = FTimespan::FromMilliseconds(0);` — Sum of time to process all calls to Subsystem Tick.
- L223 _private member_ `uint32 SubsystemTickCount = 0;` — Number of calls to Subsystem Tick.

#### struct `FTestPipeline::FEvaluateTickConfig`  
`struct FEvaluateTickConfig`  
_L53-96_
- desc: Defines the configuration used when checking for excess tick lengths. The default setup is relatively lenient.  We should tighten this up then determine the specific test cases that are allowed to deviate.
- L56 _public member_ `bool bEvaluateTickCheckActive = true;` — If true then the excess tick check will be used.
- L62 _public member_ `FTimespan ExpectedAverageTick = FTimespan::FromMilliseconds(5);` — The expected average tick length. After the MinimumTickCount ticks, if the average tick exceeds this value then a CHECK failure will occurr. The default is changed for debug.
- L68 _public member_ `FTimespan AbsoluteMaximumTick = FTimespan::FromMilliseconds(75);` — The absolute maximum tick length. If the current tick exceeds this value then a CHECK failure will occurr. The default is changed for debug.
- L73 _public member_ `uint32_t MinimumTickCount = 10;` — The minimum number of ticks per test before the average tick is evaluated against ExpectedAvergateTick. The default is changed for debug.
- L79 _public function_ `FEvaluateTickConfig(bool bInEvaluateTickCheckActive = true) : bEvaluateTickCheckActive(bInEvaluateTickCheckActive) #if defined(UE_BUILD_DEBUG) && UE_BUILD_DEBUG , ExpectedAverageTick(FTimespan::FromMilliseconds(10)) , AbsoluteMaximumTick(FTimespan::FromMilliseconds(150)) , MinimumTickCount(10) #endif` — Basic constructor used as the default with enabled tick check and settings, or when disabling the tick check.
- L89 _public function_ `FEvaluateTickConfig(FTimespan&& InExpectedAverageTick, FTimespan&& InAbsoluteMaximumTick, uint32_t InMinimumTickCount = 10) : bEvaluateTickCheckActive(true) , ExpectedAverageTick(MoveTemp(InExpectedAverageTick)) , AbsoluteMaximumTick(MoveTemp(InAbsoluteMaximumTick)) , MinimumTickCount(InMinimumTickCount)` — Full constructor which allows changing all settings for an enabled tick check.

#### class `FTestPipeline::FStep`  
`class FStep`  
_L98-113_
- L101 _public member_ `uint32_t Index = 0;`
- L103 _public function_ `virtual ~FStep()`
- L104 _public function_ `virtual bool IsOptional() const`
- L106 _public function_ `bool StepWaitsForCompletion() const` — Wait to complete before next steps can Tick
- L107 _public function_ `virtual bool RequiresDeletePostRelease() const`
- L109 _public function_ `virtual void OnPreRelease()` — Called only if RequestDeletePostRelease is true and the FStep is being stored.
- L110 _public prototype_ `virtual EContinuance Tick(IOnlineSubsystem* Subsystem) = 0;`
- L112 _protected member_ `bool WaitForCompletion = false;` — wait before next steps can Tick

#### enum `FTestPipeline::FStep::EContinuance`  
`enum class EContinuance`  
_L102-102_
- L102 _public enumerator_ `enum class EContinuance { ContinueStepping, Done }; virtual ~FStep() {} virtual bool IsOptional() const { return false; } bool StepWaitsForCompletion() const { return WaitForCompletion; } virtual bool RequiresDeletePostRelease() const { return false; } virtual void OnPreRelease() {}`
- L102 _public enumerator_ `enum class EContinuance { ContinueStepping, Done }; virtual ~FStep() {} virtual bool IsOptional() const { return false; } bool StepWaitsForCompletion() const { return WaitForCompletion; } virtual bool RequiresDeletePostRelease() const { return false; } virtual void OnPreRelease() {}`

#### class `FTestPipeline::FLambdaStep`  
`class FLambdaStep : public FStep`  
_L116-131_
- inherits: `FStep`
- L119 _public function_ `FLambdaStep(TUniqueFunction<void(IOnlineSubsystem*)>&& InLambda) : Lambda(MoveTemp(InLambda))`
- L123 _public function_ `virtual EContinuance Tick(IOnlineSubsystem* Subsystem) override`
- L130 _private member_ `TUniqueFunction<void(IOnlineSubsystem*)> Lambda;`

#### class `FTestDriver`  
`class FTestDriver`  
_L228-275_
- L231 _public typedef_ `using FSubsystemInstanceMap = TMap<IOnlineSubsystem*, FTestPipeline>;`
- L233 _public prototype_ `~FTestDriver();`
- L236 _public function_ `template <typename Func> void ForeachSubsystemInstance(Func&& Fn)`
- L244 _public function_ `FTestPipeline MakePipeline()`
- L250 _public function_ `template <typename... TArgs> FTestPipeline MakePipeline(TArgs&&... Args)`
- L255 _public prototype_ `bool AddPipeline(FTestPipeline&& Pipeline, const FPipelineTestContext& TestContext = FPipelineTestContext(NULL_SUBSYSTEM.ToString()));`
- L257 _public prototype_ `void MarkComplete(IOnlineSubsystem* Key);`
- L259 _public prototype_ `void RunToCompletion();`
- L261 _public function_ `void SetDriverTimedOut(bool InValue)`
- L263 _public prototype_ `FString TimeoutFailedTestInfo() const;`
- L265 _public member_ `int32 FailedStepNum = 0;`
- L269 _private prototype_ `void FlushCompleted();`
- L271 _private member_ `FSubsystemInstanceMap SubsystemInstances;`
- L272 _private member_ `TSet<IOnlineSubsystem*> CompletedInstances;`
- L273 _private member_ `bool bDidTimeout = false;`
- L274 _private member_ `double LastTickTime = 0.0;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_BUILD_DEBUG 0`
- L11 _prototype_ `DEFINE_LOG_CATEGORY_STATIC(LogOSSTests, Log, Log);`
- L13 _macro_ `#define UE_LOG_OSSTESTS(Verbosity, Format, ...) \`
- L18 _variable_ `static const FTimespan TICK_DURATION = FTimespan::FromMilliseconds(1);`
- L42 _macro_ `#define INFO_TEST_STEP() INFO("Test Step Index: " << Index)`
- L43 _macro_ `#define INFO_TEST_STEP_OF(InTestStep) INFO("Test Step Index: " << InTestStep->Index)`

### `Source/Programs/Online/OSSTestsCore/TestUtilities.h` (Other)


#### class `FTestUtilities`  
`class FTestUtilities`  
_L6-24_
- L9 _public function_ `static FString GetUniqueTestString()`
- L18 _public function_ `static int32 GetUniqueTestInteger()`
