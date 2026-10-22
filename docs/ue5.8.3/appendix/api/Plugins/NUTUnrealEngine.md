# Plugins / NUTUnrealEngine

- module root: `Plugins/NetcodeUnitTest/NUTUnrealEngine/Source/NUTUnrealEngine`
- headers: 7; symbols: 31
- symbol kinds: class=7, function=13, member=2, prototype=9
- PublicDependencyModuleNames: Core, CoreUObject, Engine, NetcodeUnitTest

### `Plugins/NetcodeUnitTest/NUTUnrealEngine/Source/NUTUnrealEngine/Classes/UnitTests/FTextCrash.h` (Public)


#### class `UFTextCrash`  
`class UFTextCrash : public UClientUnitTest`  
_L28-38_
- reflection: `UCLASS()`
- inherits: `UClientUnitTest`
- desc: Tests an RPC crash caused by empty FText's, as reported on the UDN here: https://udn.unrealengine.com/questions/213120/using-empty-ftexts-within-rpcs.html UDN Post: "Using Empty FTexts within RPCs" Hey, we're using FTexts within RPCs functions (server -> client in my specific case) to pass localized strings. That works fine until the point when the server sends an empty FText. In that case both the FText members SourceString and DisplayString are null on client side which lead to crashes whenever you use something like ToString which assumes those are valid. Is this the intended behavior? I'm using FTextInspector::GetSourceString(text) to run checks on these replicated FTexts now to catch this case. FTexts that are not empty work just fine. Thanks, Oliver
- L33 _public prototype_ `virtual void InitializeEnvironmentSettings() override;`
- L35 _public prototype_ `virtual void ExecuteClientUnitTest() override;`
- L37 _public prototype_ `virtual void NotifyProcessLog(TWeakPtr<FUnitTestProcess> InProcess, const TArray<FString>& InLogLines) override;`

### `Plugins/NetcodeUnitTest/NUTUnrealEngine/Source/NUTUnrealEngine/Classes/UnitTests/NetBitsTest.h` (Public)


#### class `UNetBitsTest`  
`class UNetBitsTest : public UUnitTest`  
_L16-22_
- reflection: `UCLASS()`
- inherits: `UUnitTest`
- desc: @todo JohnB
- L21 _public prototype_ `virtual bool ExecuteUnitTest() override;`

### `Plugins/NetcodeUnitTest/NUTUnrealEngine/Source/NUTUnrealEngine/Classes/UnitTests/Obsolete/UTT61_DebugReplicateData.h` (Public)


#### class `UUTT61_DebugReplicateData`  
`class UUTT61_DebugReplicateData : public UClientUnitTest`  
_L39-63_
- reflection: `UCLASS()`
- inherits: `UClientUnitTest`
- desc: Implements UTT GameplayDebuggingComponent/ServerReplicateData crash Command: UTT -b 61 127.0.0.1 Documentation from Luigi: - TEST VULNERABILITY: ServerReplicateData array overflow 07 May 2014 ServerReplicateData array overflow The ServerReplicateMessageToAIDebugView function used for some debugging features is affected by an array overflow with the InMessages: ActivateDataView and DeactivateDataView. This is the same function that was affected by the bug 55 reported the 27 March, anyway remember that it's NOT used in shipping builds.
- L46 _protected member_ `TObjectPtr<UClass> RepClass;` — `UPROPERTY()` — Reference to the GameplayDebuggingReplicator class
- L51 _private member_ `TWeakObjectPtr<AActor> Replicator;` — `UPROPERTY()` — Once the GameplayDebuggingReplicator is received, cache it
- L54 _public prototype_ `virtual void InitializeEnvironmentSettings() override;`
- L56 _public prototype_ `virtual void NotifyAllowNetActor(UClass* ActorClass, bool bActorChannel, bool& bBlockActor);`
- L58 _public prototype_ `virtual void NotifyNetActor(UActorChannel* ActorChannel, AActor* Actor);`
- L60 _public prototype_ `virtual void ExecuteClientUnitTest() override;`
- L62 _public prototype_ `virtual void NotifyProcessLog(TWeakPtr<FUnitTestProcess> InProcess, const TArray<FString>& InLogLines) override;`

### `Plugins/NetcodeUnitTest/NUTUnrealEngine/Source/NUTUnrealEngine/Classes/UnitTests/PacketLimitTest.h` (Public)
_(no declarations extracted)_

### `Plugins/NetcodeUnitTest/NUTUnrealEngine/Source/NUTUnrealEngine/Classes/UnitTests/PacketLimitTest_Oodle.h` (Public)
_(no declarations extracted)_

### `Plugins/NetcodeUnitTest/NUTUnrealEngine/Source/NUTUnrealEngine/Public/INUTUnrealEngine.h` (Public)


#### class `INUTUnrealEngine`  
`class INUTUnrealEngine : public FNUTModuleInterface`  
_L12-29_
- inherits: `FNUTModuleInterface`
- L15 _public function_ `INUTUnrealEngine() : FNUTModuleInterface(TEXT("NUTUnrealEngine"))`
- L20 _public function_ `static inline INUTUnrealEngine& Get()`
- L25 _public function_ `static inline bool IsAvailable()`

### `Plugins/NetcodeUnitTest/NUTUnrealEngine/Source/NUTUnrealEngine/Public/UnrealEngineEnvironment.h` (Public)


#### class `FShooterGameEnvironment`  
`class FShooterGameEnvironment : public FUnitTestEnvironment`  
_L17-42_
- inherits: `FUnitTestEnvironment`
- desc: Implements unit test environment settings, for ShooterGame
- L20 _public function_ `FShooterGameEnvironment()`
- L24 _public function_ `static void Register()`
- L30 _public function_ `virtual FString GetDefaultMap(EUnitTestFlags UnitTestFlags) override`

#### class `FQAGameEnvironment`  
`class FQAGameEnvironment : public FUnitTestEnvironment`  
_L47-72_
- inherits: `FUnitTestEnvironment`
- desc: Implements unit test environment settings, for QAGame
- L50 _public function_ `FQAGameEnvironment()`
- L54 _public function_ `static void Register()`
- L60 _public function_ `virtual FString GetDefaultMap(EUnitTestFlags UnitTestFlags) override`

#### class `FUTEnvironment`  
`class FUTEnvironment : public FUnitTestEnvironment`  
_L79-117_
- inherits: `FUnitTestEnvironment`
- desc: Implements unit test environment settings, for UnrealTournament
- L82 _public function_ `FUTEnvironment()`
- L86 _public function_ `static void Register()`
- L92 _public function_ `virtual FString GetDefaultMap(EUnitTestFlags UnitTestFlags) override`
- L105 _public function_ `virtual FString GetDefaultClientConnectURL() override`
