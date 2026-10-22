# Plugins / LiveLinkFaceImporter

- module root: `Plugins/Experimental/LiveLinkFaceImporter/Source/LiveLinkFaceImporter`
- headers: 2; symbols: 10
- symbol kinds: class=1, delegate=1, prototype=8
- PrivateDependencyModuleNames: CoreUObject, Engine, LevelSequence, LiveLink, LiveLinkInterface, LiveLinkMovieScene, MovieScene, MovieSceneTracks, Slate, SlateCore, UnrealEd
- PublicDependencyModuleNames: Core, LiveLink

### `Plugins/Experimental/LiveLinkFaceImporter/Source/LiveLinkFaceImporter/Private/LiveLinkFaceImporterFactory.h` (Private)


#### class `ULiveLinkFaceImporterFactory`  
`class ULiveLinkFaceImporterFactory : public UFactory`  
_L12-27_
- reflection: `UCLASS()`
- inherits: `UFactory`
- desc: Imports a CSV file created by the Live Link Face iOS app when recording facial animation.
- L17 _private prototype_ `virtual FText GetToolTip() const override;` — UFactory interface
- L18 _private prototype_ `virtual bool FactoryCanImport(const FString& Filename) override;`
- L19 _private prototype_ `virtual UObject* FactoryCreateText(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, const TCHAR* Type, const TCHAR*& Buffer, const TCHAR* BufferEnd, FFeedbackContext* Warn) override;`
- L23 _protected prototype_ `bool LoadCSV(const FString& FileContent, TArray<FString>& KeyArray, TArray<FString>& LineArray, FString& OutLogMessage);`
- L24 _protected prototype_ `FString CreateSubjectString(const FString& InName);`
- L25 _protected prototype_ `bool ParseTimecode(const FString& InTimecodeString, int32& OutHours, int32& OutMinutes, int32& OutSeconds, double& OutFrames);`
- L26 _protected prototype_ `bool InferFrameRate(const TArray<TArray<FString>>& InLineValuesArray, int8& OutInferredFrameRate);`

### `Plugins/Experimental/LiveLinkFaceImporter/Source/LiveLinkFaceImporter/Private/LiveLinkFaceImporterLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogLiveLinkFaceImporter, Verbose, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogLiveLinkFaceImporter, Verbose, All);`
