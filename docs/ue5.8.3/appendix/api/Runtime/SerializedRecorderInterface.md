# Runtime / SerializedRecorderInterface

- module root: `Source/Runtime/SerializedRecorderInterface`
- headers: 11; symbols: 333
- symbol kinds: class=7, enum=3, enumerator=17, externvar=3, function=100, macro=1, member=120, namespace=1, prototype=25, struct=21, typedef=35
- PublicDependencyModuleNames: Core, CoreUObject, LiveLinkInterface

### `Source/Runtime/SerializedRecorderInterface/Public/ISerializedRecorder.h` (Public)


#### class `ISerializedRecorder`  
`class ISerializedRecorder : public IModularFeature`  
_L13-20_
- inherits: `IModularFeature`
- L16 _public prototype_ `virtual ~ISerializedRecorder() = default;`
- L18 _public member_ `static FName ModularFeatureName;`
- L19 _public prototype_ `virtual bool LoadRecordedSequencerFile(UMovieSceneSequence* InMovieSceneSequence, UWorld *PlaybackContext, const FString& InFileName, TFunction<void()> InCompletionCallback) = 0;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API SERIALIZEDRECORDERINTERFACE_API`

### `Source/Runtime/SerializedRecorderInterface/Public/ISerializedRecorderInterfaceModule.h` (Public)


#### class `ISerializedRecorderInterfaceModule`  
`class ISerializedRecorderInterfaceModule : public IModuleInterface`  
_L9-28_
- inherits: `IModuleInterface`
- L14 _public function_ `static ISerializedRecorderInterfaceModule& Get()`
- L27 _public prototype_ `virtual ~ISerializedRecorderInterfaceModule() = default;` — Virtual destructor.

### `Source/Runtime/SerializedRecorderInterface/Public/Serializers/MovieSceneActorSerialization.h` (Public)


#### struct `FActorFileHeader`  
`struct FActorFileHeader`  
_L10-60_
- L12 _public member_ `static const int32 cVersion = 1;`
- L14 _public function_ `FActorFileHeader() : Version(cVersion)`
- L19 _public function_ `FActorFileHeader(const FString& InName, const FString& InLabel, const FName& InSerializedType, const FString& InClassName, bool SpawnedPost) : Version(cVersion) , SerializedType(InSerializedType) , UObjectName(InName) , Label(InLabel) , bRecordToPossessable(false) , bWasSpawnedPostRecord(SpawnedPost) , ClassName(InClassName) , TemplateName("None")`
- L49 _public member_ `int32 Version;` — DATA
- L50 _public member_ `FName SerializedType;`
- L51 _public member_ `FGuid Guid;`
- L53 _public member_ `FString UObjectName;`
- L54 _public member_ `FString Label;`
- L55 _public member_ `bool bRecordToPossessable;`
- L56 _public member_ `bool bWasSpawnedPostRecord;`
- L57 _public member_ `FString ClassName;`
- L58 _public member_ `FString TemplateName;`
- L59 _public member_ `FName FolderName;`

#### enum `EActoryPropertyType`  
`enum class EActoryPropertyType : uint8`  
_L62-67_
- L64 _public enumerator_ `ComponentType`
- L65 _public enumerator_ `PropertyType`
- L66 _public enumerator_ `OtherType`

#### struct `FActorProperty`  
`struct FActorProperty`  
_L69-109_
- L71 _public prototype_ `FActorProperty() = default;`
- L72 _public function_ `FActorProperty(const FString &InObjectName, const FName& InSerializedType, const FGuid& InGuid) : UObjectName(InObjectName) , SerializedType(InSerializedType) , Guid(InGuid) , Type(EActoryPropertyType::OtherType)`
- L101 _public member_ `FString UObjectName;`
- L102 _public member_ `FName SerializedType;`
- L103 _public member_ `FGuid Guid;`
- L104 _public member_ `EActoryPropertyType Type;`
- L105 _public member_ `FString PropertyName;`
- L106 _public member_ `FString BindingName;`
- L107 _public member_ `FString ClassName;`

#### Free symbols / members of external scopes

- L31 _function_ `friend FArchive& operator<<(FArchive& Ar, FActorFileHeader& Header)`
- L78 _function_ `friend FArchive& operator<<(FArchive& Ar, FActorProperty& Property)`
- L112 _typedef_ `using FActorSerializedFrame = TMovieSceneSerializedFrame<FActorProperty>;`
- L113 _typedef_ `using FActorSerializer = TMovieSceneSerializer<FActorFileHeader, FActorProperty>;`

### `Source/Runtime/SerializedRecorderInterface/Public/Serializers/MovieSceneAnimationSerialization.h` (Public)


#### struct `FAnimationFileHeader`  
`struct FAnimationFileHeader`  
_L10-52_
- L12 _public member_ `static const int32 cVersion = 1;`
- L14 _public function_ `FAnimationFileHeader() : Version(cVersion)`
- L19 _public function_ `FAnimationFileHeader(const FName& InSerializedType, FGuid& InGuid, float InIntervalTime) : Version(cVersion) , SerializedType(InSerializedType) , Guid(InGuid) , IntervalTime(InIntervalTime)`
- L39 _public function_ `void AddNewRawTrack(const FName& BoneTreeName)`
- L45 _public member_ `int32 Version;` — DATA
- L46 _public member_ `FName SerializedType;`
- L47 _public member_ `FGuid Guid;`
- L48 _public member_ `FGuid ActorGuid;`
- L49 _public member_ `float IntervalTime;`
- L50 _public member_ `float StartTime;`
- L51 _public member_ `TArray<FName> AnimationTrackNames;`

#### struct `FSerializedAnimationPerFrame`  
`struct FSerializedAnimationPerFrame`  
_L54-72_
- L56 _public prototype_ `FSerializedAnimationPerFrame() = default;`
- L67 _public member_ `int32 BoneIndex;`
- L68 _public member_ `FVector PosKey;`
- L69 _public member_ `FQuat RotKey;`
- L70 _public member_ `FVector ScaleKey;`

#### struct `FSerializedAnimation`  
`struct FSerializedAnimation`  
_L74-95_
- L76 _public prototype_ `FSerializedAnimation() = default;`
- L78 _public function_ `void AddTransform(int32 BoneIndex, const FTransform& InTransform)`
- L93 _public member_ `TArray<FSerializedAnimationPerFrame> AnimationData;`

#### Free symbols / members of external scopes

- L27 _function_ `friend FArchive& operator<<(FArchive& Ar, FAnimationFileHeader& Header)`
- L58 _function_ `friend FArchive& operator<<(FArchive& Ar, FSerializedAnimationPerFrame& Animation)`
- L88 _function_ `friend FArchive& operator<<(FArchive& Ar, FSerializedAnimation& Animation)`
- L97 _typedef_ `using FAnimationSerializedFrame = TMovieSceneSerializedFrame<FSerializedAnimation>;`
- L98 _typedef_ `using FAnimationSerializer = TMovieSceneSerializer<FAnimationFileHeader, FSerializedAnimation>;`

### `Source/Runtime/SerializedRecorderInterface/Public/Serializers/MovieSceneLiveLinkSerialization.h` (Public)


#### struct `FLiveLinkManifestHeader`  
`struct FLiveLinkManifestHeader`  
_L16-46_
- L19 _public member_ `static const int32 cVersion = 2;`
- L21 _public function_ `FLiveLinkManifestHeader() : Version(cVersion)`
- L26 _public function_ `FLiveLinkManifestHeader(const FName& InSerializedType) : Version(cVersion) , SerializedType(InSerializedType) , bIsManifest(true)`
- L42 _public member_ `int32 Version;`
- L43 _public member_ `FName SerializedType;`
- L44 _public member_ `bool bIsManifest;`
- L45 _public member_ `TArray<FName> SubjectNames;`

#### struct `FLiveLinkFileHeader`  
`struct FLiveLinkFileHeader`  
_L53-96_
- desc: Header and data for individual subjects that contain the data.
- L55 _public prototype_ `FLiveLinkFileHeader() = default;`
- L57 _public function_ `FLiveLinkFileHeader(const FName& InSubjectName, double InSecondsDiff, TSubclassOf<ULiveLinkRole> InSubjectRole, const TSharedPtr<FLiveLinkStaticDataStruct>& InStaticData, const FName& InSerializedType, const FGuid& InGuid) : bIsManifest(false) , SecondsDiff(InSecondsDiff) , SubjectName(InSubjectName) , SerializedType(InSerializedType) , Guid(InGuid)`
- L88 _public member_ `bool bIsManifest;`
- L89 _public member_ `double SecondsDiff;`
- L90 _public member_ `FName SubjectName;`
- L91 _public member_ `FName SerializedType;`
- L92 _public member_ `FGuid Guid;`
- L94 _public member_ `TArray<FName> CurveNames;`
- L95 _public member_ `FLiveLinkRefSkeleton RefSkeleton;`

#### Free symbols / members of external scopes

- L33 _function_ `friend FArchive& operator<<(FArchive& Ar, FLiveLinkManifestHeader& Header)`
- L48 _typedef_ `using FLiveLinkManifestSerializer = TMovieSceneSerializer<FLiveLinkManifestHeader, FLiveLinkManifestHeader>;`
- L66 _function_ `friend FArchive& operator<<(FArchive& Ar, FLiveLinkFileHeader& Header)`

### `Source/Runtime/SerializedRecorderInterface/Public/Serializers/MovieSceneManifestSerialization.h` (Public)


#### struct `FManifestFileHeader`  
`struct FManifestFileHeader`  
_L10-41_
- L12 _public member_ `static const int32 cVersion = 1;`
- L14 _public function_ `FManifestFileHeader() : Version(cVersion)`
- L18 _public function_ `FManifestFileHeader(const FString& InName, const FName& InSerializedType, const FGuid& InGuid) : Version(cVersion) , SerializedType(InSerializedType) , Guid(InGuid) , Name(InName)`
- L37 _public member_ `int32 Version;`
- L38 _public member_ `FName SerializedType;`
- L39 _public member_ `FGuid Guid;`
- L40 _public member_ `FString Name;`

#### struct `FManifestProperty`  
`struct FManifestProperty`  
_L45-69_
- desc: since we can't use function templates with TFunctions need to use a variant or union.
- L47 _public prototype_ `FManifestProperty() = default;`
- L48 _public function_ `FManifestProperty(const FString &InObjectName, const FName& InSerializedType, const FGuid& InGuid) : UObjectName(InObjectName) , SerializedType(InSerializedType) , Guid(InGuid)`
- L65 _public member_ `FString UObjectName;`
- L66 _public member_ `FName SerializedType;`
- L67 _public member_ `FGuid Guid;`

#### Free symbols / members of external scopes

- L27 _function_ `friend FArchive& operator<<(FArchive& Ar, FManifestFileHeader& Header)`
- L53 _function_ `friend FArchive& operator<<(FArchive& Ar, FManifestProperty& Property)`
- L72 _typedef_ `using FManifestSerializedFrame = TMovieSceneSerializedFrame<FManifestProperty>;`
- L73 _typedef_ `using FManifestSerializer = TMovieSceneSerializer<FManifestFileHeader, FManifestProperty>;`

### `Source/Runtime/SerializedRecorderInterface/Public/Serializers/MovieScenePropertySerialization.h` (Public)


#### enum `ESerializedPropertyType`  
`enum class ESerializedPropertyType : uint8`  
_L11-24_
- L13 _public enumerator_ `BoolType`
- L14 _public enumerator_ `ByteType`
- L15 _public enumerator_ `EnumType`
- L16 _public enumerator_ `FloatType`
- L17 _public enumerator_ `DoubleType`
- L18 _public enumerator_ `Vector3fType`
- L19 _public enumerator_ `Vector3dType`
- L20 _public enumerator_ `ColorType`
- L21 _public enumerator_ `IntegerType`
- L22 _public enumerator_ `StringType`
- L23 _public enumerator_ `LinearColorType`

#### struct `FPropertyFileHeader`  
`struct FPropertyFileHeader`  
_L26-131_
- L29 _public member_ `static const int32 cVersion = 1;`
- L31 _public function_ `FPropertyFileHeader() : Version(cVersion)`
- L36 _public function_ `FPropertyFileHeader(const FFrameRate &InFrameRate, const FName& InSerializedType, const FGuid& InGuid) : Version(cVersion) , SerializedType(InSerializedType) , Guid(InGuid) , TickResolution(InFrameRate)`
- L59 _public function_ `void SetProperty(const FProperty* Property, const FName& InPropertyName)`
- L124 _public member_ `int32 Version;` — DATA
- L125 _public member_ `FName SerializedType;`
- L126 _public member_ `FGuid Guid;`
- L127 _public member_ `FFrameRate TickResolution;`
- L128 _public member_ `FName PropertyName;`
- L129 _public member_ `ESerializedPropertyType PropertyType;`
- L130 _public member_ `FString TrackDisplayName;`

#### struct `FSerializedProperty`  
`template <typename PropertyType> struct FSerializedProperty`  
_L135-149_
- L137 _public prototype_ `FSerializedProperty() = default;`
- L146 _public member_ `FFrameNumber Time;`
- L147 _public member_ `PropertyType Value;`

#### Free symbols / members of external scopes

- L45 _function_ `friend FArchive& operator<<(FArchive& Ar, FPropertyFileHeader& Header)`
- L139 _function_ `friend FArchive& operator<<(FArchive& Ar, FSerializedProperty& Property)`
- L151 _typedef_ `using FPropertySerializedBool = FSerializedProperty<bool>;`
- L152 _typedef_ `using FPropertySerializedBoolFrame = TMovieSceneSerializedFrame<FSerializedProperty<bool>>;`
- L154 _typedef_ `using FPropertySerializedByte = FSerializedProperty<uint8>;`
- L155 _typedef_ `using FPropertySerializedByteFrame = TMovieSceneSerializedFrame<FSerializedProperty<uint8>>;`
- L157 _typedef_ `using FPropertySerializedEnum = FSerializedProperty<int64>;`
- L158 _typedef_ `using FPropertySerializedEnumFrame = TMovieSceneSerializedFrame<FSerializedProperty<int64>>;`
- L159 _typedef_ `using FPropertySerializerEnum = TMovieSceneSerializer<FPropertyFileHeader, FSerializedProperty<int64>>;`
- L161 _typedef_ `using FPropertySerializedDouble = FSerializedProperty<double>;`
- L162 _typedef_ `using FPropertySerializedDoubleFrame = TMovieSceneSerializedFrame<FSerializedProperty<double>>;`
- L164 _typedef_ `using FPropertySerializedFloat = FSerializedProperty<float>;`
- L165 _typedef_ `using FPropertySerializedFloatFrame = TMovieSceneSerializedFrame<FSerializedProperty<float>>;`
- L167 _typedef_ `using FPropertySerializedVector3f = FSerializedProperty<FVector3f>;`
- L168 _typedef_ `using FPropertySerializedVector3fFrame = TMovieSceneSerializedFrame<FSerializedProperty<FVector3f>>;`
- L170 _typedef_ `using FPropertySerializedVector3d = FSerializedProperty<FVector3d>;`
- L171 _typedef_ `using FPropertySerializedVector3dFrame = TMovieSceneSerializedFrame<FSerializedProperty<FVector3d>>;`
- L173 _typedef_ `using FPropertySerializedColor = FSerializedProperty<FColor>;`
- L174 _typedef_ `using FPropertySerializedColorFrame = TMovieSceneSerializedFrame<FSerializedProperty<FColor>>;`
- L176 _typedef_ `using FPropertySerializedInteger = FSerializedProperty<int32>;`
- L177 _typedef_ `using FPropertySerializedIntegerFrame = TMovieSceneSerializedFrame<FSerializedProperty<int32>>;`
- L179 _typedef_ `using FPropertySerializedString = FSerializedProperty<FString>;`
- L180 _typedef_ `using FPropertySerializedStringFrame = TMovieSceneSerializedFrame<FSerializedProperty<FString>>;`
- L182 _typedef_ `using FPropertySerializedLinearColor = FSerializedProperty<FLinearColor>;`
- L183 _typedef_ `using FPropertySerializedLinearColorFrame = TMovieSceneSerializedFrame<FSerializedProperty<FLinearColor>>;`

### `Source/Runtime/SerializedRecorderInterface/Public/Serializers/MovieSceneSectionSerialization.h` (Public)


#### struct `TMovieSceneSerializedFrame`  
`template <typename FrameData> struct TMovieSceneSerializedFrame`  
_L58-69_
- L60 _public member_ `uint64 FrameId;`
- L61 _public member_ `FrameData Frame;`

#### struct `FMovieSceneSerializedFrameHeader`  
`struct FMovieSceneSerializedFrameHeader`  
_L73-105_
- desc: Header (non-tagged property serialized) for a frame
- L75 _public function_ `FMovieSceneSerializedFrameHeader() : NextFrameOffset(MovieSceneSerializationNamespace::InvalidOffset) , PrevFrameOffset(MovieSceneSerializationNamespace::InvalidOffset) , FrameId(0)`
- L81 _public function_ `FMovieSceneSerializedFrameHeader(int64 InNextFrameOffset, int64 InPrevFrameOffset, uint64 InFrameId) : NextFrameOffset(InNextFrameOffset) , PrevFrameOffset(InPrevFrameOffset) , FrameId(InFrameId)`
- L88 _public member_ `int64 NextFrameOffset;` — Offset within the archive that the next frame can be found. -1 if this is the last frame.
- L91 _public member_ `int64 PrevFrameOffset;` — Offset within the archive that the next frame can be found. -1 if this is the first frame.
- L94 _public member_ `uint64 FrameId;` — ID of this frame

#### class `FMovieSceneArchiveFileReader`  
`class FMovieSceneArchiveFileReader : public FArchiveFileReaderGeneric`  
_L107-128_
- inherits: `FArchiveFileReaderGeneric`
- L110 _public function_ `FMovieSceneArchiveFileReader(IFileHandle* InHandle, const TCHAR* InFilename) : FArchiveFileReaderGeneric(InHandle, InFilename, InHandle->Size())`
- L114 _public function_ `void BeginArchiving()`
- L123 _public function_ `virtual void CloseLowLevel() override` — FArchiveFileReaderGeneric interface

#### class `FMovieSceneArchiveFileWriter`  
`class FMovieSceneArchiveFileWriter : public FArchiveFileWriterGeneric`  
_L130-150_
- inherits: `FArchiveFileWriterGeneric`
- L133 _public function_ `FMovieSceneArchiveFileWriter(IFileHandle* InHandle, const TCHAR* InFilename) : FArchiveFileWriterGeneric(InHandle, InFilename, InHandle->Tell())`
- L137 _public function_ `void BeginArchiving()`
- L144 _public function_ `virtual bool CloseLowLevel() override` — FArchiveFileWriterGeneric interface

#### struct `FMovieSceneSessionInfo`  
`struct FMovieSceneSessionInfo`  
_L156-205_
- desc: Information about a captured session
- L158 _public function_ `FMovieSceneSessionInfo() : BuildVersion(0)`
- L162 _public function_ `FMovieSceneSessionInfo(const FGuid& InInstanceId, FDateTime InTimeStamp, int32 InBuildVersion, const FString& InDeviceName, const FString& InPlatformName, const FString& InInstanceName, const FString& InBuildDate) : InstanceId(InInstanceId) , TimeStamp(InTimeStamp) , BuildVersion(InBuildVersion) , DeviceName(InDeviceName) , PlatformName(InPlatformName) , InstanceName(InInstanceName) , BuildDate(InBuildDate)`
- L173 _public member_ `FGuid InstanceId;` — The ID of the session instance the file was captured with
- L176 _public member_ `FDateTime TimeStamp;` — The timestamp of this capture at creation time. @see FDateTime::UtcNow()
- L179 _public member_ `int32 BuildVersion;` — The engine version the file was captured with. @see ISessionInstanceInfo
- L182 _public member_ `FString DeviceName;` — Name of the device the file was captured on. @see ISessionInstanceInfo
- L185 _public member_ `FString PlatformName;` — Name of the platform the file was captured on. @see ISessionInstanceInfo
- L188 _public member_ `FString InstanceName;` — Name of the engine instance the file was captured on. @see ISessionInstanceInfo
- L191 _public member_ `FString BuildDate;` — The build date for the capture. @see ISessionInstanceInfo

#### class `FMovieSceneSerializerContext`  
`class FMovieSceneSerializerContext`  
_L211-266_
- desc: Archive context maintained when the serializer is running
- L215 _public function_ `FMovieSceneSerializerContext(IFileHandle* InHandle, const FString& InFilename) : Filename(InFilename) , Handle(InHandle) , ArReaderInner(InHandle, *Filename) , ArWriterInner(InHandle, *Filename) , ArReader(ArReaderInner) , ArWriter(ArWriterInner) , LastFrameWritePos(MovieSceneSerializationNamespace::InvalidOffset) , MinFrameId(0xffffffffffffffff) , MaxFrameId(0)`
- L227 _public prototype_ `~FMovieSceneSerializerContext() = default;`
- L229 _public function_ `void Close()`
- L241 _public member_ `FString Filename;` — Filename
- L244 _public member_ `IFileHandle* Handle;` — Read/write handles
- L247 _public member_ `FMovieSceneArchiveFileReader ArReaderInner;` — Inner file reader/writer archives
- L248 _public member_ `FMovieSceneArchiveFileWriter ArWriterInner;`
- L251 _public member_ `FNameAsStringProxyArchive ArReader;` — Reader/writer archives
- L252 _public member_ `FNameAsStringProxyArchive ArWriter;`
- L255 _public member_ `int64 LastFrameWritePos;` — Offset within the archive that the last frame was written
- L258 _public member_ `TArray<TPair<uint64, int64>> FrameIdToFrameOffset;` — Frame IDs used to access specific times quickly
- L261 _public member_ `uint64 MinFrameId;` — The min frame ID contained in the file
- L264 _public member_ `uint64 MaxFrameId;` — The max frame ID contained in the file

#### struct `FTempCustomVersion`  
`struct FTempCustomVersion`  
_L271-287_
- L284 _public member_ `const static FGuid GUID;` — The GUID for this custom version number
- L286 _private function_ `FTempCustomVersion()`

#### enum `FTempCustomVersion::Type`  
`enum Type`  
_L273-281_
- L276 _public enumerator_ `FirstVersion = 0` — Initial version
- L279 _public enumerator_ `VersionPlusOne` — -----new versions can be added above this line-------------------------------------------------
- L280 _public enumerator_ `LatestVersion = VersionPlusOne - 1`

#### struct `FContextAndCommands`  
`template <typename HeaderData, typename FrameData> struct FContextAndCommands`  
_L291-468_
- L293 _public function_ `FContextAndCommands(IFileHandle* InHandle, const FString& InFilename) : Context(InHandle, InFilename)`
- L298 _public function_ `~FContextAndCommands()`
- L316 _public member_ `FGuid Guid;` — Unique ID of this Guid, key for a map of Context
- L318 _public member_ `FMovieSceneSerializerContext Context;`
- L321 _public member_ `TLockFreePointerListFIFO<FSerializerCommand, 0> ReadCommands;` — Read command queue - pushed on any thread, popped on the serializer worker thread
- L324 _public member_ `TLockFreePointerListFIFO<FSerializerCommand, 0> WriteCommands;` — Write command queue - pushed on any thread, popped on the serializer worker thread
- L327 _public member_ `TLockFreePointerListFIFO<FSerializerCommand, 0> FreeCommands;` — Free command queue - pushed on any thread, popped on any thread
- L329 _public function_ `void Close()`
- L334 _public function_ `void Run()`
- L377 _public function_ `bool CheckHeader(bool bInFileExisted, TArray<FMovieSceneSessionInfo>& SessionInfos, HeaderData& InOutHeader, int64& ReadHeaderPos, FText& OutFailReason)`
- L442 _public function_ `template <typename... ArgsType> FORCEINLINE FSerializerCommand* GetFreeCommand(ArgsType&&... Args)` — Gets a free command from the free list, if any. Otherwise allocates a new command. This means that the number of commands grows unbounded to the high watermark of all commands.
- L458 _public function_ `template <typename... ArgsType> FORCEINLINE void AddReadCommand(ArgsType&&... Args)`
- L464 _public function_ `template <typename... ArgsType> FORCEINLINE void AddWriteCommand(ArgsType&&... Args)`

#### class `FMovieSceneSerializerRunnable`  
`template <typename HeaderData, typename FrameData> class FMovieSceneSerializerRunnable : public FRunnable`  
_L472-583_
- inherits: `FRunnable`
- desc: Runnable to run threaded I/O
- L475 _public function_ `FMovieSceneSerializerRunnable() : bRunning(true), bStopping(false)`
- L479 _public function_ `~FMovieSceneSerializerRunnable()`
- L486 _public function_ `void AddContext(const FGuid& InGuid, IFileHandle* InHandle, const FString& InFileName)`
- L494 _public function_ `virtual uint32 Run() override` — FRunnable interface
- L519 _public function_ `virtual void Stop() override`
- L525 _public function_ `bool CheckHeader(const FGuid& InGuid, bool bInFileExisted, TArray<FMovieSceneSessionInfo>& SessionInfos, HeaderData& InOutHeader, int64& ReadHeaderPos, FText& OutFailReason)`
- L537 _public function_ `FContextAndCommands<HeaderData,FrameData> & GetContext(const FGuid& InGuid)`
- L544 _public function_ `void Close(const FGuid& InGuid)`
- L555 _public function_ `void CloseContexts()`
- L568 _public member_ `TMap<FGuid, TSharedPtr<FContextAndCommands<HeaderData, FrameData>>> ContextMap;` — The contexts we are using
- L571 _public member_ `FThreadSafeBool bRunning;` — Thread safe bool for running the thread
- L574 _public member_ `FThreadSafeBool bStopping;` — Thread safe bool for stopping the thread
- L577 _public member_ `FThreadSafeBool bOpenForRead;` — Read/write access flags
- L578 _public member_ `FThreadSafeBool bOpenForWrite;`
- L581 _public member_ `FCriticalSection ContextMapCriticalSection;` — Lock

#### class `TMovieSceneSerializer`  
`template <typename HeaderData,typename FrameData> class TMovieSceneSerializer`  
_L587-676_
- desc: A class to asynchronously read and write to serialized frame debugger data files
- L591 _public prototype_ `TMovieSceneSerializer();`
- L594 _public prototype_ `bool DoesFileExist(const FString& InFileName);` — Get whether file exists
- L597 _public prototype_ `FString GetLocalCaptureDir();` — Get the local capture directory
- L600 _public prototype_ `void SetLocalCaptureDir(const FString& PathIn);` — Set the local capture directory
- L606 _public prototype_ `bool OpenForWrite(const FString& InFilename, HeaderData& Header, FText& OutFailReason);` — Open the serializer for writing @return false if the operation was not successful with regards to opening the file, if we have saving turned off it will still return true.
- L612 _public prototype_ `bool OpenForRead(const FString& InFileName, HeaderData& OutHeader, FText& OutFailReason);`
- L615 _public prototype_ `void Close();` — Close the serializer, flushes any commands and shuts down threads
- L618 _public prototype_ `bool IsOpen() const;` — Check whether this serializer is currently open
- L621 _public prototype_ `void WriteFrameData(uint64 InFrameId, const FrameData &InFrame);` — Write one frame data out to disk
- L624 _public prototype_ `void WriteFrameData(uint64 InFrameId, const TArray<FrameData> &InFrames);` — Write array of frame data out to disk
- L627 _public prototype_ `void ReadFramesAtFrameRange(uint64 InStartFrameId, uint64 InEndFrameId, TFunction<void()> InCompletionCallback);` — Read a frame range. Completion callback will be called on the game thread.
- L630 _public prototype_ `void GetDataRanges(TFunction<void(uint64 , uint64 )> InCompletionCallback);` — Query the range of data in the file. Completion callback will be called on the game thread.
- L633 _public function_ `int32 GetNumSessions()` — Get the number of sessions that were captured to this file
- L636 _public function_ `FGuid GetSessionId(int32 InSessionIndex) const` — Get the engine version the file was captured with. @see ISessionInstanceInfo
- L639 _public function_ `int32 GetBuildVersion(int32 InSessionIndex) const` — Get the engine version the file was captured with. @see ISessionInstanceInfo
- L642 _public function_ `FString GetDeviceName(int32 InSessionIndex) const` — Get the name of the device the file was captured on. @see ISessionInstanceInfo
- L645 _public function_ `FString GetPlatformName(int32 InSessionIndex) const` — Get the name of the platform the file was captured on. @see ISessionInstanceInfo
- L648 _public function_ `FString GetInstanceName(int32 InSessionIndex) const` — Get the name of the engine instance the file was captured on. @see ISessionInstanceInfo
- L651 _public function_ `FString GetBuildDate(int32 InSessionIndex) const` — Get the build date for the capture. @see ISessionInstanceInfo
- L654 _public member_ `int FramesWritten;` — How many frames have been written
- L658 _public member_ `TArray<TMovieSceneSerializedFrame<FrameData>> ResultData;` — Data from a read.  Be carefule if reading multiple times this data will get replaced and modified, so need to come up with different way to get data in that case
- L661 _public member_ `static FRunnableThread* Thread;` — Thread we run on
- L664 _public member_ `static FMovieSceneSerializerRunnable<HeaderData, FrameData>* Runnable;` — Runnable that the thread runs
- L669 _private member_ `TArray<FMovieSceneSessionInfo> SessionInfos;` — The session infos
- L672 _private member_ `FString LocalCaptureDir;` — Local Directory
- L675 _private member_ `FGuid Guid;` — Unique guid for this serializer
- L680 _function_ `template<typename HeaderData, typename FrameData> TMovieSceneSerializer<HeaderData, FrameData>::TMovieSceneSerializer() : FramesWritten(0) , LocalCaptureDir(FPaths::ProjectSavedDir()) , Guid(FGuid::NewGuid())`
- L688 _function_ `template<typename HeaderData, typename FrameData> FString TMovieSceneSerializer<HeaderData, FrameData>::GetLocalCaptureDir()`
- L693 _function_ `template<typename HeaderData, typename FrameData> void TMovieSceneSerializer<HeaderData, FrameData>::SetLocalCaptureDir(const FString& PathIn)`
- L698 _function_ `template<typename HeaderData, typename FrameData> bool TMovieSceneSerializer<HeaderData, FrameData>::DoesFileExist(const FString& AbsoluteFilePath)`
- L705 _function_ `template<typename HeaderData, typename FrameData> bool TMovieSceneSerializer<HeaderData, FrameData>::OpenForWrite(const FString& InFilename, HeaderData& Header, FText& OutFailReason)`
- L774 _function_ `template<typename HeaderData, typename FrameData> bool TMovieSceneSerializer<HeaderData, FrameData>::OpenForRead(const FString& AbsoluteFilePath, HeaderData& OutHeader, FText& OutFailReason)`
- L863 _function_ `template<typename HeaderData, typename FrameData> void TMovieSceneSerializer<HeaderData, FrameData>::Close()`
- L884 _function_ `template<typename HeaderData, typename FrameData> bool TMovieSceneSerializer<HeaderData, FrameData>::IsOpen() const`
- L890 _function_ `template<typename HeaderData, typename FrameData> void TMovieSceneSerializer<HeaderData, FrameData>::GetDataRanges(TFunction<void(uint64 , uint64 )> InCompletionCallback)`
- L910 _function_ `template <typename HeaderData, typename FrameData> void TMovieSceneSerializer<HeaderData, FrameData>::ReadFramesAtFrameRange(uint64 InStartFrameId, uint64 InEndFrameId, TFunction<void()> InCompletionCallback)`
- L967 _function_ `template<typename HeaderData, typename FrameData> void TMovieSceneSerializer<HeaderData, FrameData>::WriteFrameData(uint64 InFrameId, const FrameData &InFrame)`
- L1011 _function_ `template<typename HeaderData, typename FrameData> void TMovieSceneSerializer<HeaderData, FrameData>::WriteFrameData(uint64 InFrameId, const TArray<FrameData> &InFrames)`

#### Free symbols / members of external scopes

- L48 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(MovieSceneSerialization, Verbose, All);`
- L50 _namespace_ `namespace MovieSceneSerializationNamespace`
- L52 _externvar_ `extern const int64 InvalidOffset;` (scope `MovieSceneSerializationNamespace`)
- L53 _externvar_ `extern const float SerializerSleepTime;` (scope `MovieSceneSerializationNamespace`)
- L54 _externvar_ `extern bool bAutoSerialize;` (scope `MovieSceneSerializationNamespace`)
- L63 _function_ `friend FArchive& operator<<(FArchive& Ar, TMovieSceneSerializedFrame& InFrame)`
- L97 _function_ `friend FArchive& operator<<(FArchive& Ar, FMovieSceneSerializedFrameHeader& Header)`
- L193 _function_ `friend FArchive& operator<<(FArchive& Ar, FMovieSceneSessionInfo& InOutSessionInfo)`
- L269 _typedef_ `typedef TFunction<void(FMovieSceneSerializerContext& )> FSerializerCommand;`
- L811 _function_ `` (scope `TMovieSceneSerializer::OpenForRead`)
- L896 _function_ `` (scope `TMovieSceneSerializer::GetDataRanges`)
- L902 _function_ `` (scope `TMovieSceneSerializer::GetDataRanges::__anon254ee7ec0202`)
- L918 _function_ `` (scope `TMovieSceneSerializer::ReadFramesAtFrameRange`)
- L920 _function_ `int32 FoundFirstFramePos = Algo::LowerBoundBy(InContext.FrameIdToFrameOffset, InStartFrameId, [](const TPair<uint64, int64>& InItem) { return InItem.Key; }, TLess<>());` (scope `TMovieSceneSerializer::ReadFramesAtFrameRange::__anon254ee7ec0402`) — First we need to skip to our frame
- L948 _function_ `` (scope `TMovieSceneSerializer::ReadFramesAtFrameRange::__anon254ee7ec0402`)
- L974 _function_ `` (scope `TMovieSceneSerializer::WriteFrameData`)

### `Source/Runtime/SerializedRecorderInterface/Public/Serializers/MovieSceneSerializedType.h` (Public)


#### struct `FSerializedTypeFileHeader`  
`struct FSerializedTypeFileHeader`  
_L11-30_
- desc: Though we are embedding the serialized type of the data into the file name they may not match so we go ahead and read the type from the file by mocking a header that just reads in the type.
- L13 _public member_ `static const int32 cVersion = 1;`
- L15 _public function_ `FSerializedTypeFileHeader() : Version(cVersion)`
- L28 _public member_ `int32 Version;`
- L29 _public member_ `FName SerializedType;`

#### Free symbols / members of external scopes

- L20 _function_ `friend FArchive& operator<<(FArchive& Ar, FSerializedTypeFileHeader& Header)`

### `Source/Runtime/SerializedRecorderInterface/Public/Serializers/MovieSceneSpawnSerialization.h` (Public)


#### struct `FSpawnFileHeader`  
`struct FSpawnFileHeader`  
_L10-43_
- L12 _public member_ `static const int32 cVersion = 1;`
- L14 _public function_ `FSpawnFileHeader() : Version(cVersion)`
- L19 _public function_ `FSpawnFileHeader(FFrameRate &InTickResolution, const FName& InSerializedType, const FGuid& InGuid) : Version(cVersion) , SerializedType(InSerializedType) , Guid(InGuid) , TickResolution(InTickResolution)`
- L39 _public member_ `int32 Version;` — DATA
- L40 _public member_ `FName SerializedType;`
- L41 _public member_ `FGuid Guid;`
- L42 _public member_ `FFrameRate TickResolution;`

#### struct `FSpawnProperty`  
`struct FSpawnProperty`  
_L47-65_
- desc: since we can't use function templates with TFunctions need to use a variant or union.
- L49 _public prototype_ `FSpawnProperty() = default;`
- L50 _public function_ `FSpawnProperty( FFrameNumber InKeyTime, bool InVal)`
- L63 _public member_ `FFrameNumber Time;` — DATA
- L64 _public member_ `bool bVal;`

#### Free symbols / members of external scopes

- L28 _function_ `friend FArchive& operator<<(FArchive& Ar, FSpawnFileHeader& Header)`
- L55 _function_ `friend FArchive& operator<<(FArchive& Ar, FSpawnProperty& Property)`
- L68 _typedef_ `using FSpawnSerializedFrame = TMovieSceneSerializedFrame<FSpawnProperty>;`
- L69 _typedef_ `using FSpawnSerializer = TMovieSceneSerializer<FSpawnFileHeader, FSpawnProperty>;`

### `Source/Runtime/SerializedRecorderInterface/Public/Serializers/MovieSceneTransformSerialization.h` (Public)


#### struct `FTransformFileHeader`  
`struct FTransformFileHeader`  
_L10-44_
- L12 _public member_ `static const int32 cVersion = 1;`
- L14 _public function_ `FTransformFileHeader() : Version(cVersion)`
- L18 _public function_ `FTransformFileHeader(FFrameRate &InTickResolution, const FName& InSerializedType, const FGuid& InGuid) : Version(cVersion) , SerializedType(InSerializedType) , Guid(InGuid) , TickResolution(InTickResolution)`
- L39 _public member_ `int32 Version;` — DATA
- L40 _public member_ `FName SerializedType;`
- L41 _public member_ `FGuid Guid;`
- L42 _public member_ `FFrameRate TickResolution;`

#### struct `FSerializedTransform`  
`struct FSerializedTransform`  
_L46-88_
- L48 _public prototype_ `FSerializedTransform() = default;`
- L50 _public function_ `FSerializedTransform(const FTransform& InTransform, FFrameNumber InKeyTime)`
- L54 _public function_ `void Set(const FTransform& InTransform, FFrameNumber InKeyTime)`
- L86 _public member_ `FFrameNumber Time;`
- L87 _public member_ `double Values[9];` — location, rotation, scale.

#### Free symbols / members of external scopes

- L27 _function_ `friend FArchive& operator<<(FArchive& Ar, FTransformFileHeader& Header)`
- L71 _function_ `friend FArchive& operator<<(FArchive& Ar, FSerializedTransform& Transform)`
- L90 _typedef_ `using FTransformSerializedFrame = TMovieSceneSerializedFrame<FSerializedTransform>;`
- L91 _typedef_ `using FTransformSerializer = TMovieSceneSerializer<FTransformFileHeader, FSerializedTransform>;`
