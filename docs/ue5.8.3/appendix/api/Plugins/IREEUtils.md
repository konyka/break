# Plugins / IREEUtils

- module root: `Plugins/Experimental/NNERuntimeIREE/Source/IREEUtils`
- headers: 2; symbols: 11
- symbol kinds: delegate=1, namespace=2, prototype=8
- PrivateDependencyModuleNames: Core

### `Plugins/Experimental/NNERuntimeIREE/Source/IREEUtils/Internal/IREEUtils.h` (Internal)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace IREEUtils` (scope `UE`)
- L11 _prototype_ `bool ResolveSdkPaths(FString& String);` (scope `UE::IREEUtils`)
- L13 _prototype_ `bool ResolveEnvironmentVariables(FString& String);` (scope `UE::IREEUtils`)
- L15 _prototype_ `void RunCommand(const FString& Command, const FString& Arguments, const FString& WorkingDir, const FString& LogFilePath = FString());` (scope `UE::IREEUtils`)
- L17 _prototype_ `bool ImportOnnx(const FString& ImporterCommand, const FString& ImporterArguments, TConstArrayView<uint8> InFileData, const FString& InModelName, const FString& InOutputDir, TArray64<uint8>& OutMlirData);` (scope `UE::IREEUtils`)
- L24 _prototype_ `bool HashAppendFile(FMD5& Hash, const FString& InFilePath);` (scope `UE::IREEUtils`) — Hashes the contents of the entire file. Depending on the file size this might be a slow operation. @return true on success, false otherwise
- L31 _prototype_ `bool HashAppendFileStat(FMD5& Hash, const FString& InFilePath);` (scope `UE::IREEUtils`) — Hashes the modification time and the file size. @return true on success, false otherwise
- L36 _prototype_ `void HashAppendString(FMD5& Hash, const FString& Data);` (scope `UE::IREEUtils`) — Hashes the char array of an FString. This isn't guaranteed to produce the same hash for the same string on different platforms.

### `Plugins/Experimental/NNERuntimeIREE/Source/IREEUtils/Internal/IREEUtilsLog.h` (Internal)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogIREEUtils, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogIREEUtils, Log, All);`
