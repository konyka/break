# Plugins / DirectLinkTest

- module root: `Plugins/Enterprise/DatasmithImporter/Source/DirectLinkTest`
- headers: 4; symbols: 25
- symbol kinds: class=3, delegate=1, function=2, macro=1, member=1, prototype=17
- PrivateDependencyModuleNames: CoreUObject, Engine
- PublicDependencyModuleNames: Core, DatasmithCore, DatasmithTranslator, DirectLink

### `Plugins/Enterprise/DatasmithImporter/Source/DirectLinkTest/Private/DirectLinkTestLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDirectLinkTest, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDirectLinkTest, Log, All);`

### `Plugins/Enterprise/DatasmithImporter/Source/DirectLinkTest/Private/TestSceneProvider.h` (Private)


#### class `FTestSceneProvider`  
`class FTestSceneProvider : public DirectLink::IConnectionRequestHandler`  
_L11-18_
- inherits: `DirectLink::IConnectionRequestHandler`
- L14 _public prototype_ `virtual bool CanOpenNewConnection(const FSourceInformation& Source) override;`
- L15 _public prototype_ `virtual TSharedPtr<DirectLink::ISceneReceiver> GetSceneReceiver(const FSourceInformation& Source) override;`
- L17 _public member_ `TMap<FGuid, TSharedPtr<FDatasmithSceneReceiver>> SceneReceivers;`

### `Plugins/Enterprise/DatasmithImporter/Source/DirectLinkTest/Public/DirectLinkTestLibrary.h` (Public)


#### class `UDirectLinkTestLibrary`  
`class UDirectLinkTestLibrary : public UBlueprintFunctionLibrary`  
_L13-67_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- L19 _public prototype_ `static bool TestParameters();` — `UFUNCTION(BlueprintCallable, Category = "DirectLink")`
- L23 _public prototype_ `static bool StartReceiver();` — `UFUNCTION(BlueprintCallable, Category = "DirectLink")`
- L26 _public prototype_ `static bool SetupReceiver();` — `UFUNCTION(BlueprintCallable, Category = "DirectLink")`
- L29 _public prototype_ `static bool StopReceiver();` — `UFUNCTION(BlueprintCallable, Category = "DirectLink")`
- L33 _public prototype_ `static bool StartSender();` — `UFUNCTION(BlueprintCallable, Category = "DirectLink")`
- L36 _public prototype_ `static bool SetupSender();` — `UFUNCTION(BlueprintCallable, Category = "DirectLink")`
- L39 _public prototype_ `static bool StopSender();` — `UFUNCTION(BlueprintCallable, Category = "DirectLink")`
- L43 _public prototype_ `static bool SendScene(const FString& InFilePath);` — `UFUNCTION(BlueprintCallable, Category = "DirectLink")`
- L46 _public prototype_ `static bool DumpReceivedScene();` — `UFUNCTION(BlueprintCallable, Category = "DirectLink")`
- L53 _public prototype_ `static int MakeEndpoint(const FString& NiceName, bool bVerbose=true);` — `UFUNCTION(BlueprintCallable, Category = "DirectLink")`
- L56 _public prototype_ `static bool DeleteEndpoint(int32 EndpointId);` — `UFUNCTION(BlueprintCallable, Category = "DirectLink")`
- L59 _public prototype_ `static bool AddPublicSource(int32 EndpointId, FString SourceName);` — `UFUNCTION(BlueprintCallable, Category = "DirectLink")`
- L62 _public prototype_ `static bool AddPublicDestination(int32 EndpointId, FString DestName);` — `UFUNCTION(BlueprintCallable, Category = "DirectLink")`
- L65 _public prototype_ `static bool DeleteAllEndpoint();` — `UFUNCTION(BlueprintCallable, Category = "DirectLink")`

### `Plugins/Enterprise/DatasmithImporter/Source/DirectLinkTest/Public/DirectLinkTestModule.h` (Public)


#### class `FDirectLinkTestModule`  
`class FDirectLinkTestModule : public IModuleInterface`  
_L14-26_
- inherits: `IModuleInterface`
- desc: TODO: Module description
- L17 _public function_ `static inline FDirectLinkTestModule& Get()`
- L22 _public function_ `static inline bool IsAvailable()`

#### Free symbols / members of external scopes

- L9 _macro_ `#define DIRECTLINKTEST_MODULE_NAME TEXT("DirectLinkTest")`
