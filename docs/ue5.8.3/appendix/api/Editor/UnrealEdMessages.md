# Editor / UnrealEdMessages

- module root: `Source/Editor/UnrealEdMessages`
- headers: 3; symbols: 9
- symbol kinds: function=4, member=3, struct=2
- PrivateDependencyModuleNames: Core
- PublicDependencyModuleNames: CoreUObject

### `Source/Editor/UnrealEdMessages/Classes/AssetEditorMessages.h` (Public)


#### struct `FAssetEditorRequestOpenAsset`  
`struct FAssetEditorRequestOpenAsset`  
_L14-32_
- reflection: `USTRUCT()`
- desc: Implements a message for opening an asset in the asset browser.
- L22 _public member_ `FString AssetName;` — `UPROPERTY(EditAnywhere, Category="Message")` — Holds the name of the asset to open.
- L26 _public function_ `FAssetEditorRequestOpenAsset()` — Default constructor.
- L29 _public function_ `FAssetEditorRequestOpenAsset(const FString& InAssetName) : AssetName(InAssetName)` — Creates and initializes a new instance.

### `Source/Editor/UnrealEdMessages/Classes/FileServerMessages.h` (Public)


#### struct `FFileServerReady`  
`struct FFileServerReady`  
_L15-35_
- reflection: `USTRUCT()`
- desc: Implements a message that is published by file servers when they're ready to accept connections.
- L21 _public member_ `TArray<FString> AddressList;` — `UPROPERTY(EditAnywhere, Category="Message")` — Holds the list of IP addresses that the file server is listening on.
- L25 _public member_ `FGuid InstanceId;` — `UPROPERTY(EditAnywhere, Category="Message")` — Holds the file server's application identifier.
- L28 _public function_ `FFileServerReady()` — Default constructor.
- L31 _public function_ `FFileServerReady(const TArray<FString>& InAddressList, const FGuid& InInstanceId) : AddressList(InAddressList) , InstanceId(InInstanceId)` — Creates and initializes a new instance.

### `Source/Editor/UnrealEdMessages/Public/UnrealEdMessages.h` (Public)
_(no declarations extracted)_
