# Programs / LiveLinkFbxProvider

- module root: `Source/Programs/LiveLinkFbxProvider/Source`
- headers: 1; symbols: 51
- symbol kinds: class=1, function=5, member=25, namespace=1, prototype=14, struct=4, typedef=1
- PrivateDependencyModuleNames: ApplicationCore, Core, CoreUObject, LiveLinkInterface, LiveLinkMessageBusFramework, Messaging, Projects, UdpMessaging
- PrivateIncludePathModuleNames: Launch

### `Source/Programs/LiveLinkFbxProvider/Source/Private/LiveLinkFbxProviderLoop.h` (Private)


#### struct `FLiveLinkFbxProviderLoopInitArgs`  
`struct FLiveLinkFbxProviderLoopInitArgs`  
_L18-44_
- reflection: `USTRUCT()`
- L22 _public function_ `FLiveLinkFbxProviderLoopInitArgs()`
- L23 _public prototype_ `FLiveLinkFbxProviderLoopInitArgs(int32 ArgC, TCHAR* ArgV[]);`
- L26 _public member_ `FString FbxFile;` — Path to FBX file to stream.
- L30 _public member_ `FString SourceName = TEXT("Liv` — `UPROPERTY()` — Name to use for the provided Live Link source.
- L34 _public member_ `TOptional<FFrameRate> FrameRate;` — `UPROPERTY()` — Frame rate override.
- L38 _public member_ `bool bTimecodeJamSync = false;` — `UPROPERTY()` — Rebase the timecode each playback loop to roughly align it to system time.
- L40 _public member_ `int32 ArgC = 0;`
- L41 _public member_ `TCHAR** ArgV = nullptr;`
- L43 _public prototype_ `FString GetUsage() const;`

#### class `FLiveLinkFbxSubject`  
`class FLiveLinkFbxSubject`  
_L47-67_
- L50 _public prototype_ `FLiveLinkFbxSubject(FName InSubjectName);`
- L52 _public prototype_ `bool InitializeFromFbxNode(fbxsdk::FbxNode* InSkelNode);`
- L54 _public function_ `FName GetSubjectName() const`
- L55 _public function_ `const TArray<FName>& GetBoneNames() const`
- L56 _public function_ `const TArray<int32>& GetBoneParents() const`
- L57 _public function_ `const TArray<fbxsdk::FbxNode*>& GetBoneNodes() const`
- L60 _private prototype_ `void RecursiveGatherBones(fbxsdk::FbxNode* InNode, int32 InParentIdx = -1);`
- L63 _private member_ `FName SubjectName;`
- L64 _private member_ `TArray<FName> BoneNames;`
- L65 _private member_ `TArray<int32> BoneParents;`
- L66 _private member_ `TArray<fbxsdk::FbxNode*> BoneNodes;`

#### struct `FLiveLinkFbxSubjectFrame`  
`struct FLiveLinkFbxSubjectFrame`  
_L70-73_
- L72 _public member_ `TArray<FTransform> FramePose;`

#### struct `FLiveLinkFbxFrame`  
`struct FLiveLinkFbxFrame`  
_L76-83_
- L78 _public member_ `double FrameTimeSeconds;`
- L79 _public member_ `TOptional<FTimecode> Timecode;`
- L81 _public typedef_ `using FSubjectPair = TPair<TWeakPtr<FLiveLinkFbxSubject>, FLiveLinkFbxSubjectFrame>;`
- L82 _public member_ `TMap<TWeakPtr<FLiveLinkFbxSubject>, FLiveLinkFbxSubjectFrame> SubjectFrameData;`

#### struct `FLiveLinkFbxProviderLoop`  
`struct FLiveLinkFbxProviderLoop`  
_L89-122_
- desc: Blocking main loop for running the provider application.
- L91 _public prototype_ `FLiveLinkFbxProviderLoop(const FLiveLinkFbxProviderLoopInitArgs& InitArgs);`
- L93 _public prototype_ `int32 Run(int32 ArgC, TCHAR** ArgV);`
- L96 _private prototype_ `bool ReadFbx(const FString& InFbxFilename);`
- L97 _private prototype_ `void RecursiveGatherSkeletons(fbxsdk::FbxNode* InNode);`
- L98 _private prototype_ `void SnapSubframesToCleanFractions(int32 InSubframeDivisor);`
- L100 _private prototype_ `void StartProvider();`
- L101 _private prototype_ `void StopProvider();`
- L103 _private prototype_ `double Tick();`
- L105 _private prototype_ `FFrameTime GetSystemFrameTimeWithOffset(double InDeltaSec) const;`
- L108 _private member_ `const FLiveLinkFbxProviderLoopInitArgs InitArgs;`
- L110 _private member_ `TSharedPtr<ILiveLinkProvider> LiveLinkProvider;`
- L112 _private member_ `TArray<TSharedRef<FLiveLinkFbxSubject>> Subjects;`
- L113 _private member_ `TArray<FLiveLinkFbxFrame> Frames;`
- L115 _private member_ `FFrameRate FrameRate;`
- L116 _private member_ `bool bDropFrame = false;`
- L117 _private member_ `double NominalFramePeriodSec = 0.0;`
- L118 _private member_ `TOptional<FQualifiedFrameTime> FirstFrameTime;`
- L119 _private member_ `double LoopStartTime = 0.0;`
- L120 _private member_ `FFrameTime FrameTimeOffset;`
- L121 _private member_ `int32 NextFrameIdx = 0;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace fbxsdk`
