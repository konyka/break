# Plugins / AsyncMessageSystemTests

- module root: `Plugins/Experimental/AsyncMessageSystemTests/Source/AsyncMessageSystemTests`
- headers: 2; symbols: 20
- symbol kinds: class=3, member=9, prototype=6, struct=2
- PublicDependencyModuleNames: AsyncMessageSystem, Core, CoreUObject, Engine, GameplayTags, RuntimeTests

### `Plugins/Experimental/AsyncMessageSystemTests/Source/AsyncMessageSystemTests/Private/AsyncMessageSystemPerformanceTests.h` (Private)


#### struct `FAsyncMessagePerfTestPayload`  
`struct FAsyncMessagePerfTestPayload`  
_L20-28_
- reflection: `USTRUCT(NotBlueprintType, meta=(Hidden))`
- desc: A very simple test payload referencing an actor
- L24 _public member_ `TWeakObjectPtr<AEngineTestTickActor> TargetActor = nullptr;`
- L27 _public member_ `bool bDoLessWork = false;` — If true, then the test actor will simulate less work

#### class `AASyncMessagePerfTest`  
`class AASyncMessagePerfTest : public AEngineTestTickActor`  
_L34-53_
- reflection: `UCLASS(NotBlueprintable, NotBlueprintType, meta=(Hidden))`
- inherits: `AEngineTestTickActor`
- desc: A test actor class which is to be used for async mesage performance testing
- L39 _public prototype_ `void SetupBindingToMessage(const FAsyncMessageId& MessageToBindTo, const FAsyncMessageBindingOptions& BindingOpts);`
- L40 _public prototype_ `void HandleTestCallback(const FAsyncMessage& Message);`
- L41 _public prototype_ `virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;`
- L43 _public member_ `TArray<FAsyncMessageHandle> BoundHandles;`
- L46 _public prototype_ `void DoTestWork();` — A function which simulates doing some CPU floating point work
- L48 _public member_ `float MathCounter = 0.0f;` — Properties used in the DoTestWork function above
- L49 _public member_ `float MathIncrement = 0.01f;`
- L50 _public member_ `float MathLimit = 1.0f;`
- L52 _public prototype_ `void DoSimpleTestWork();`

#### struct `FTest_RefCollection_Payload`  
`struct FTest_RefCollection_Payload`  
_L57-66_
- reflection: `USTRUCT(NotBlueprintType, meta=(Hidden))`
- L62 _public member_ `TObjectPtr<UObject> ObjPoint = nullptr;` — `UPROPERTY()`
- L65 _public member_ `TWeakObjectPtr<UObject> WeakObjPointer = nullptr;` — `UPROPERTY()`

#### class `UTestRefCollectionObject`  
`class UTestRefCollectionObject : public UObject`  
_L72-79_
- reflection: `UCLASS(NotBlueprintable, NotBlueprintType)`
- inherits: `UObject`
- desc: A test UObject type which we will use to test ref counting of payload data
- L78 _public member_ `int32 TestValue = 5;` — `UPROPERTY()`

### `Plugins/Experimental/AsyncMessageSystemTests/Source/AsyncMessageSystemTests/Private/AsyncMessageSystemTestsModule.h` (Private)


#### class `FAsyncMessageSystemTestsModule`  
`class FAsyncMessageSystemTestsModule final : public IModuleInterface`  
_L7-16_
- inherits: `IModuleInterface`
- L15 _public prototype_ `static bool IsAvailable();` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
