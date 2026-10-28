# Plugins / LiveLinkMovieScene

- module root: `Plugins/Animation/LiveLink/Source/LiveLinkMovieScene`
- headers: 16; symbols: 269
- symbol kinds: class=12, delegate=1, enum=2, enumerator=2, function=39, macro=6, member=65, namespace=2, prototype=131, struct=9
- PrivateDependencyModuleNames: Engine
- PublicDependencyModuleNames: Core, CoreUObject, LiveLinkInterface, MovieScene, MovieSceneTracks

### `Plugins/Animation/LiveLink/Source/LiveLinkMovieScene/Private/LiveLinkMovieScenePrivate.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogLiveLinkMovieScene, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogLiveLinkMovieScene, Log, All);`

### `Plugins/Animation/LiveLink/Source/LiveLinkMovieScene/Private/MovieScene/MovieSceneLiveLinkSectionTemplate.h` (Private)


#### struct `FMovieSceneLiveLinkSectionTemplate`  
`struct FMovieSceneLiveLinkSectionTemplate : public FMovieScenePropertySectionTemplate`  
_L24-87_
- reflection: `USTRUCT()`
- inherits: `FMovieScenePropertySectionTemplate`
- desc: A movie scene evaluation template for post move settings live link sections.
- L29 _public prototype_ `FMovieSceneLiveLinkSectionTemplate();`
- L30 _public prototype_ `FMovieSceneLiveLinkSectionTemplate(const UMovieSceneLiveLinkSection& Section, const UMovieScenePropertyTrack& Track);`
- L33 _public prototype_ `FMovieSceneLiveLinkSectionTemplate(const FMovieSceneLiveLinkSectionTemplate& InOther);` — Template is copied after being created. We need to re-link property storage to property handler
- L35 _public prototype_ `virtual ~FMovieSceneLiveLinkSectionTemplate() = default;`
- L39 _public prototype_ `bool Serialize(FArchive& Ar);` — Implementing Serialize to adjust old data and save static data
- L42 _protected prototype_ `bool GetLiveLinkFrameArray(const FFrameTime &FrameTime, const FFrameTime& LowerBound, const FFrameTime& UpperBound, TArray<FLiveLinkFrameDataStruct>& LiveLinkFrameDataArray, const FFrameRate& FrameRate) const;`
- L43 _protected prototype_ `void FillFrame(int32 InKeyIndex, const FLiveLinkWorldTime& InWorldTime, const TOptional<FQualifiedFrameTime>& InTimecodeTime, FLiveLinkFrameDataStruct& OutFrame) const;`
- L44 _protected prototype_ `void FillFrameInterpolated(const FFrameTime& InFrameTime, const FLiveLinkWorldTime& InWorldTime, const TOptional<FQualifiedFrameTime>& InTimecodeTime, FLiveLinkFrameDataStruct& OutFrame) const;`
- L47 _private function_ `virtual UScriptStruct& GetScriptStructImpl() const override`
- L48 _private prototype_ `virtual void Evaluate(const FMovieSceneEvaluationOperand& Operand, const FMovieSceneContext& Context, const FPersistentEvaluationData& PersistentData, FMovieSceneExecutionTokens& ExecutionTokens) const override;`
- L50 _private prototype_ `virtual void EvaluateSwept(const FMovieSceneEvaluationOperand& Operand, const FMovieSceneContext& Context, const TRange<FFrameNumber>& SweptRange, const FPersistentEvaluationData& PersistentData, FMovieSceneExecutionTokens& ExecutionTokens) const override;`
- L52 _private function_ `virtual void SetupOverrides() override`
- L56 _private prototype_ `virtual void Setup(FPersistentEvaluationData& PersistentData, IMovieScenePlayer& Player) const override;`
- L57 _private prototype_ `virtual void TearDown(FPersistentEvaluationData& PersistentData, IMovieScenePlayer& Player) const override;`
- L60 _private prototype_ `void FillPropertyArray(int32 InKeyIndex, const FLiveLinkPropertyData& InSourceData, FArrayProperty* InSourceArray, void* InDestinationAddress);`
- L61 _private prototype_ `void FillPropertyArrayInterpolated(const FFrameTime& InFrameTime, const FLiveLinkPropertyData& InSourceData, FArrayProperty* InSourceArray, void* InDestinationAddress);`
- L63 _private prototype_ `void InitializePropertyHandlers();`
- L65 _private prototype_ `bool AreChannelKeyCountEqual() const;`
- L66 _private prototype_ `bool CacheIsSectionUsable() const;`
- L67 _private prototype_ `void GetFirstTimeArray(TArrayView<const FFrameNumber>& OutKeyTimes) const;`
- L72 _public member_ `FLiveLinkSubjectPreset SubjectPreset;` — `UPROPERTY()`
- L75 _public member_ `TArray<bool> ChannelMask;` — `UPROPERTY()`
- L78 _public member_ `TArray<FLiveLinkSubSectionData> SubSectionsData;` — `UPROPERTY()`
- L80 _public member_ `bool bMustDoInterpolation;`
- L82 _public member_ `bool bIsSectionUsable;`
- L84 _public member_ `TArray<TSharedPtr<IMovieSceneLiveLinkPropertyHandler>> PropertyHandlers;`
- L86 _public member_ `TSharedPtr<FLiveLinkStaticDataStruct> StaticData;`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FMovieSceneLiveLinkSectionTemplate> : public TStructOpsTypeTraitsBase2<FMovieSceneLiveLinkSectionTemplate>`  
_L89-92_
- inherits: `TStructOpsTypeTraitsBase2<FMovieSceneLiveLinkSectionTemplate>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
`enum`  
_L91-91_

#### Free symbols / members of external scopes

- L91 _enumerator_ `enum { WithSerializer = true };` (scope `TStructOpsTypeTraits::__anond0b453780103`)

### `Plugins/Animation/LiveLink/Source/LiveLinkMovieScene/Private/MovieScene/MovieSceneLiveLinkSource.h` (Private)


#### class `FMovieSceneLiveLinkSource`  
`class FMovieSceneLiveLinkSource : public ILiveLinkSource, public TSharedFromThis<FMovieSceneLiveLinkSource>`  
_L11-44_
- inherits: `ILiveLinkSource,TSharedFromThis<FMovieSceneLiveLinkSource>`
- desc: Publishes LiveLink From Sequencer
- L14 _public prototype_ `FMovieSceneLiveLinkSource();`
- L15 _public prototype_ `virtual ~FMovieSceneLiveLinkSource() = default;`
- L16 _public prototype_ `static TSharedPtr<FMovieSceneLiveLinkSource> CreateLiveLinkSource(const FLiveLinkSubjectPreset& SubjectPreset);`
- L17 _public prototype_ `static void RemoveLiveLinkSource(TSharedPtr<FMovieSceneLiveLinkSource> Source);`
- L18 _public prototype_ `void PublishLiveLinkStaticData(FLiveLinkStaticDataStruct& StaticData);`
- L19 _public prototype_ `void PublishLiveLinkFrameData(TArray<FLiveLinkFrameDataStruct>& LiveLinkFrameDataArray);`
- L23 _public prototype_ `virtual void ReceiveClient(ILiveLinkClient* InClient, FGuid InSourceGuid) override;` — ILiveLinkSource interface
- L24 _public prototype_ `virtual void InitializeSettings(ULiveLinkSourceSettings* Settings) override;`
- L25 _public prototype_ `virtual bool IsSourceStillValid() const override;`
- L26 _public prototype_ `virtual bool RequestSourceShutdown() override;`
- L27 _public prototype_ `virtual FText GetSourceMachineName() const override;`
- L28 _public prototype_ `virtual FText GetSourceStatus() const override;`
- L29 _public prototype_ `virtual FText GetSourceType() const override;`
- L34 _public member_ `ILiveLinkClient* Client;` — The local client to push data updates to
- L37 _public member_ `FGuid SourceGuid;` — Our identifier in LiveLink
- L40 _public member_ `FLiveLinkSubjectPreset SubjectPreset;` — Our subject preset in LiveLink
- L43 _public member_ `FLiveLinkSubjectKey PreviousSubjectEnabled;` — Previously enabled subject with the same name than us when we were added to livelink. Used to put it back up when we tear down

### `Plugins/Animation/LiveLink/Source/LiveLinkMovieScene/Public/MovieScene/IMovieSceneLiveLinkPropertyHandler.h` (Public)


#### struct `FLiveLinkPropertyKey`  
`template<typename PropertyType> struct FLiveLinkPropertyKey`  
_L20-24_
- desc: Helper struct for recording properties
- L22 _public member_ `PropertyType Value;`
- L23 _public member_ `FFrameNumber Time;`

#### class `IMovieSceneLiveLinkPropertyHandler`  
`class IMovieSceneLiveLinkPropertyHandler`  
_L27-42_
- desc: Interface for live link property handlers (recording and evaluating)
- L31 _public prototype_ `virtual ~IMovieSceneLiveLinkPropertyHandler() = default;`
- L34 _public prototype_ `virtual void CreateChannels(const UScriptStruct& InStruct, int32 InElementCount) = 0;` — Methods used when creating the tracks and filling the channels
- L35 _public prototype_ `virtual void RecordFrame(const FFrameNumber& InFrameNumber, const UScriptStruct& InStruct, const FLiveLinkBaseFrameData* InFrameData) = 0;`
- L36 _public prototype_ `virtual void Finalize(bool bInReduceKeys, const FKeyDataOptimizationParams& InOptimizationParams) = 0;`
- L39 _public prototype_ `virtual void InitializeFromExistingChannels(const UScriptStruct& InStruct) = 0;` — Methods used when playing back a track
- L40 _public prototype_ `virtual void FillFrame(int32 InKeyIndex, const FLiveLinkWorldTime& InWorldTime, const TOptional<FQualifiedFrameTime>& InTimecodeTime, const UScriptStruct& InStruct, FLiveLinkBaseFrameData* OutFrame) = 0;`
- L41 _public prototype_ `virtual void FillFrameInterpolated(const FFrameTime& InFrameTime, const FLiveLinkWorldTime& InWorldTime, const TOptional<FQualifiedFrameTime>& InTimecodeTime, const UScriptStruct& InStruct, FLiveLinkBaseFrameData* OutFrame) = 0;`

### `Plugins/Animation/LiveLink/Source/LiveLinkMovieScene/Public/MovieScene/MovieSceneLiveLinkBufferData.h` (Public)


#### struct `FLiveLinkTransformKeys`  
`struct FLiveLinkTransformKeys`  
_L9-138_
- desc: Data structure to handle buffering transform keys. Inspired from 3d Transform Track Recorder
- L11 _public member_ `TArray<FFrameNumber> Times;`
- L12 _public member_ `TArray<FMovieSceneFloatValue> LocationX, LocationY, LocationZ;`
- L12 _public member_ `TArray<FMovieSceneFloatValue> LocationX, LocationY, LocationZ;`
- L12 _public member_ `TArray<FMovieSceneFloatValue> LocationX, LocationY, LocationZ;`
- L13 _public member_ `TArray<FMovieSceneFloatValue> RotationX, RotationY, RotationZ;`
- L13 _public member_ `TArray<FMovieSceneFloatValue> RotationX, RotationY, RotationZ;`
- L13 _public member_ `TArray<FMovieSceneFloatValue> RotationX, RotationY, RotationZ;`
- L14 _public member_ `TArray<FMovieSceneFloatValue> ScaleX, ScaleY, ScaleZ;`
- L14 _public member_ `TArray<FMovieSceneFloatValue> ScaleX, ScaleY, ScaleZ;`
- L14 _public member_ `TArray<FMovieSceneFloatValue> ScaleX, ScaleY, ScaleZ;`
- L17 _public function_ `FVector GetNormalizedRotation(float X, float Y, float Z)` — returns rotation as -180 to 180.
- L24 _public function_ `void FixEulerFlips(int32 StartIndex, TArray<FMovieSceneFloatChannel>& FloatChannels)`
- L61 _public function_ `void Add(const FTransform& InTransform, FFrameNumber InKeyTime)`
- L67 _public function_ `void Add(const FTransform& InTransform)`
- L108 _public function_ `void AppendToFloatChannelsAndReset(int32 StartIndex, TArray<FMovieSceneFloatChannel>& FloatChannels)` — This function is the one that's called when recording live link incrementally. We move the values over from our saved Location, Rotation and Scale buffers into the specified float channels and then reset our buffers, re-using it's memory for the next iteration. We also fix any euler flips during this process, avoiding iterating over the data once again during Finalize.

### `Plugins/Animation/LiveLink/Source/LiveLinkMovieScene/Public/MovieScene/MovieSceneLiveLinkEnumHandler.h` (Public)


#### class `FMovieSceneLiveLinkEnumHandler`  
`class FMovieSceneLiveLinkEnumHandler : public IMovieSceneLiveLinkPropertyHandler`  
_L15-55_
- inherits: `IMovieSceneLiveLinkPropertyHandler`
- L18 _public function_ `FMovieSceneLiveLinkEnumHandler(const FLiveLinkStructPropertyBindings& InBinding, FLiveLinkPropertyData* PropertyStorage) : PropertyStorage(PropertyStorage) , PropertyBinding(InBinding) , ElementCount(0)`
- L25 _public prototype_ `virtual ~FMovieSceneLiveLinkEnumHandler() = default;`
- L29 _public prototype_ `virtual void CreateChannels(const UScriptStruct& InStruct, int32 InElementCount) override;`
- L30 _public prototype_ `virtual void RecordFrame(const FFrameNumber& InFrameNumber, const UScriptStruct& InStruct, const FLiveLinkBaseFrameData* InFrameData) override;`
- L31 _public prototype_ `virtual void Finalize(bool bInReduceKeys, const FKeyDataOptimizationParams& InOptimizationParams) override;`
- L34 _public prototype_ `virtual void InitializeFromExistingChannels(const UScriptStruct& InStruct) override;`
- L35 _public prototype_ `virtual void FillFrame(int32 InKeyIndex, const FLiveLinkWorldTime& InWorldTime, const TOptional<FQualifiedFrameTime>& InTimecodeTime, const UScriptStruct& InStruct, FLiveLinkBaseFrameData* OutFrame) override;`
- L36 _public prototype_ `virtual void FillFrameInterpolated(const FFrameTime& InFrameTime, const FLiveLinkWorldTime& InWorldTime, const TOptional<FQualifiedFrameTime>& InTimecodeTime, const UScriptStruct& InStruct, FLiveLinkBaseFrameData* OutFrame) override;`
- L39 _protected prototype_ `int64 GetChannelValue(int32 InKeyIndex, int32 InChannelIndex);`
- L40 _protected prototype_ `int64 GetChannelValueInterpolated(const FFrameTime& InFrameTime, int32 InChannelIndex);`
- L45 _protected member_ `FLiveLinkPropertyData* PropertyStorage;` — Channel storage for this property
- L48 _protected member_ `FLiveLinkStructPropertyBindings PropertyBinding;` — Binding for this property
- L51 _protected member_ `int32 ElementCount;` — Number of elements to record each frame
- L54 _protected member_ `TArray<TArray<FLiveLinkPropertyKey<int64>>> Keys;` — Enum property value are interacted as int64. We store keys like this but channel used will be a byte one

### `Plugins/Animation/LiveLink/Source/LiveLinkMovieScene/Public/MovieScene/MovieSceneLiveLinkPropertyHandler.h` (Public)


#### class `FMovieSceneLiveLinkPropertyHandler`  
`template <typename PropertyType> class FMovieSceneLiveLinkPropertyHandler : public IMovieSceneLiveLinkPropertyHandler`  
_L15-86_
- inherits: `IMovieSceneLiveLinkPropertyHandler`
- L19 _public function_ `FMovieSceneLiveLinkPropertyHandler(const FLiveLinkStructPropertyBindings& InBinding , FLiveLinkPropertyData* InOutPropertyStorage) : PropertyStorage(InOutPropertyStorage) , PropertyBinding(InBinding) , ElementCount(0)`
- L27 _public prototype_ `virtual ~FMovieSceneLiveLinkPropertyHandler() = default;`
- L31 _public prototype_ `virtual void CreateChannels(const UScriptStruct& InStruct, int32 InElementCount) override;`
- L32 _public function_ `virtual void RecordFrame(const FFrameNumber& InFrameNumber, const UScriptStruct& InStruct, const FLiveLinkBaseFrameData* InFrameData) override`
- L48 _public prototype_ `virtual void Finalize(bool bInReduceKeys, const FKeyDataOptimizationParams& InOptimizationParams) override;`
- L50 _public prototype_ `virtual void InitializeFromExistingChannels(const UScriptStruct& InStruct) override;`
- L51 _public function_ `virtual void FillFrame(int32 InKeyIndex, const FLiveLinkWorldTime& InWorldTime, const TOptional<FQualifiedFrameTime>& InTimecodeTime, const UScriptStruct& InStruct, FLiveLinkBaseFrameData* OutFrame) override`
- L60 _public function_ `virtual void FillFrameInterpolated(const FFrameTime& InFrameTime, const FLiveLinkWorldTime& InWorldTime, const TOptional<FQualifiedFrameTime>& InTimecodeTime, const UScriptStruct& InStruct, FLiveLinkBaseFrameData* OutFrame) override`
- L70 _protected prototype_ `PropertyType GetChannelValue(int32 InKeyIndex, int32 InChannelIndex);`
- L71 _protected prototype_ `PropertyType GetChannelValueInterpolated(const FFrameTime& InFrameTime, int32 InChannelIndex);`
- L76 _protected member_ `FLiveLinkPropertyData* PropertyStorage;` — Channel storage for this property
- L79 _protected member_ `FLiveLinkStructPropertyBindings PropertyBinding;` — Binding for this property
- L82 _protected member_ `int32 ElementCount;` — Number of elements to record each frame
- L85 _protected member_ `TArray<TArray<FLiveLinkPropertyKey<PropertyType>>> Keys;` — The keys that are being recorded

### `Plugins/Animation/LiveLink/Source/LiveLinkMovieScene/Public/MovieScene/MovieSceneLiveLinkSection.h` (Public)


#### class `UMovieSceneLiveLinkSection`  
`class UMovieSceneLiveLinkSection : public UMovieSceneSection`  
_L27-105_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneSection`
- desc: A movie scene section for all live link recorded data
- L33 _public prototype_ `UMovieSceneLiveLinkSection(const FObjectInitializer& ObjectInitializer);`
- L35 _public prototype_ `void Initialize(const FLiveLinkSubjectPreset& SubjectPreset, const TSharedPtr<FLiveLinkStaticDataStruct>& InStaticData);`
- L36 _public function_ `void SetSubjectName(const FName& InSubjectName)`
- L43 _public prototype_ `int32 CreateChannelProxy();` — Called when first created. Creates the channels required to represent this section
- L48 _public prototype_ `void UpdateChannelProxy();` — Called during loading.
- L50 _public prototype_ `void SetMask(const TArray<bool>& InChannelMask);`
- L52 _public prototype_ `void RecordFrame(FFrameNumber InFrameNumber, const FLiveLinkFrameDataStruct& InFrameData);`
- L53 _public prototype_ `void FinalizeSection(bool bReduceKeys, const FKeyDataOptimizationParams& OptimizationParams);`
- L56 _public prototype_ `static TArray<TSubclassOf<UMovieSceneLiveLinkSection>> GetMovieSectionForRole(const TSubclassOf<ULiveLinkRole>& RoleToSupport);`
- L58 _public prototype_ `virtual FMovieSceneEvalTemplatePtr CreateSectionTemplate(const UMovieScenePropertyTrack& InTrack) const;`
- L62 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L63 _public prototype_ `virtual void PostEditImport() override;`
- L64 _public prototype_ `virtual void PostLoad() override;`
- L67 _public prototype_ `virtual bool Modify(bool bAlwaysMarkDirty = true) override;`
- L68 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L69 _public prototype_ `virtual void ExportCustomProperties(FOutputDevice& Out, uint32 Indent) override;`
- L70 _public prototype_ `virtual void ImportCustomProperties(const TCHAR* SourceText, FFeedbackContext* Warn) override;`
- L76 _protected prototype_ `virtual int32 GetChannelCount() const;`
- L79 _private prototype_ `void ConvertPreRoleData();`
- L84 _public member_ `FLiveLinkSubjectPreset SubjectPreset;` — `UPROPERTY()`
- L88 _public member_ `TArray<bool> ChannelMask;` — `UPROPERTY()` — Channels that we may not send to live link or they are sent but not priority (MattH to do).
- L91 _public member_ `TArray<TObjectPtr<UMovieSceneLiveLinkSubSection>> SubSections;` — `UPROPERTY()`
- L93 _public member_ `TSharedPtr<FLiveLinkStaticDataStruct> StaticData;`
- L96 _public member_ `FName SubjectName_DEPRECATED;` — `UPROPERTY()`
- L98 _public member_ `FLiveLinkFrameData TemplateToPush_DEPRECATED;` — `UPROPERTY()`
- L100 _public member_ `FLiveLinkRefSkeleton RefSkeleton_DEPRECATED;` — `UPROPERTY()`
- L102 _public member_ `TArray<FName> CurveNames_DEPRECATED;` — `UPROPERTY()`
- L104 _public member_ `TArray <FMovieSceneFloatChannel> PropertyFloatChannels_DEPRECATED;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API LIVELINKMOVIESCENE_API`

### `Plugins/Animation/LiveLink/Source/LiveLinkMovieScene/Public/MovieScene/MovieSceneLiveLinkStructProperties.h` (Public)


#### struct `FLiveLinkPropertyData`  
`struct FLiveLinkPropertyData`  
_L22-52_
- reflection: `USTRUCT()`
- L27 _public prototype_ `FLiveLinkPropertyData();`
- L28 _public prototype_ `~FLiveLinkPropertyData();`
- L31 _public member_ `FName PropertyName;` — `UPROPERTY()`
- L34 _public member_ `TArray<FMovieSceneFloatChannel> FloatChannel;` — `UPROPERTY()`
- L37 _public member_ `TArray<FMovieSceneStringChannel> StringChannel;` — `UPROPERTY()`
- L40 _public member_ `TArray<FMovieSceneIntegerChannel> IntegerChannel;` — `UPROPERTY()`
- L43 _public member_ `TArray<FMovieSceneBoolChannel> BoolChannel;` — `UPROPERTY()`
- L46 _public member_ `TArray<FMovieSceneByteChannel> ByteChannel;` — `UPROPERTY()`
- L48 _public function_ `int32 GetChannelCount() const`

#### struct `FLiveLinkSubSectionData`  
`struct FLiveLinkSubSectionData`  
_L55-65_
- reflection: `USTRUCT()`
- L61 _public member_ `TArray<FLiveLinkPropertyData> Properties;` — `UPROPERTY()`
- L64 _public prototype_ `bool Serialize(FArchive& Archive);` — Custom serializer that compresses property data before serializing it when doing persistent serialization.

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FLiveLinkSubSectionData> : public TStructOpsTypeTraitsBase2<FLiveLinkSubSectionData>`  
_L69-75_
- inherits: `TStructOpsTypeTraitsBase2<FLiveLinkSubSectionData>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L72-74_

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace LiveLinkPropertiesUtils`
- L18 _prototype_ `TSharedPtr< IMovieSceneLiveLinkPropertyHandler> CreatePropertyHandler(const UScriptStruct& InStruct, FLiveLinkPropertyData* InPropertyData);` (scope `LiveLinkPropertiesUtils`)
- L73 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anon1b61b4dd0103`)

### `Plugins/Animation/LiveLink/Source/LiveLinkMovieScene/Public/MovieScene/MovieSceneLiveLinkStructPropertyBindings.h` (Public)


#### class `FLiveLinkStructPropertyBindings`  
`class FLiveLinkStructPropertyBindings`  
_L15-273_
- desc: Manages bindings to keyed properties of LiveLink UStructs.
- L18 _public prototype_ `FLiveLinkStructPropertyBindings(FName InPropertyName, const FString& InPropertyPath);`
- L25 _public prototype_ `void CacheBinding(const UScriptStruct& InStruct);` — Rebuilds the property mappings for a specific UStruct, and adds them to the cache @param InContainer The type to cache property for
- L33 _public prototype_ `FProperty* GetProperty(const UScriptStruct& InStruct) const;` — Gets the FProperty that is bound to the container @param InContainer	The Struct that owns the property @return				The property on the Struct if it exists
- L44 _public function_ `ValueType GetCurrentValue(const UScriptStruct& InStruct, const void* InSourceAddress)` — `UE_DEPRECATED(4.24, "This function is deprecated. Use a GetCurrentValueAt with InIndex set to 0 for the same result.")`
- L58 _public function_ `template <typename ValueType> ValueType GetCurrentValueAt(int32 InIndex, const UScriptStruct& InStruct, const void* InSourceAddress)` — Gets the current value of a property at desired Index. Must be on ArrayProperty @param InIndex	The index of the desired value in the ArrayProperty @param InStruct	The struct to get the property from @param InSourceAddress	The source address of the struct instance @return ValueType	The current value
- L90 _public function_ `int64 GetCurrentValueForEnum(const UScriptStruct& InStruct, const void* InSourceAddress)` — `UE_DEPRECATED(4.24, "This function is deprecated. Use a GetCurrentValueForEnumAt with InIndex set to 0 for the same result.")` — Gets the current value of an enum property on a struct @param InStruct	The struct to get the property from @param InSourceAddress	The address of the instanced struct @return ValueType	The current value
- L103 _public prototype_ `int64 GetCurrentValueForEnumAt(int32 InIndex, const UScriptStruct& InStruct, const void* InSourceAddress);` — Gets the current value of an enum property at desired index @param InIndex	The index of the desired value in the ArrayProperty @param InStruct	The struct to get the property from @param InSourceAddress	The address of the instanced struct @return ValueType	The current value
- L115 _public function_ `void SetCurrentValue(const UScriptStruct& InStruct, void* InSourceAddress, typename TCallTraits<ValueType>::ParamType InValue)` — `UE_DEPRECATED(4.24, "This function is deprecated. Use a SetCurrentValueAt with InIndex set to 0 for the same result.")`
- L129 _public function_ `template <typename ValueType> void SetCurrentValueAt(int32 InIndex, const UScriptStruct& InStruct, void* InSourceAddress, typename TCallTraits<ValueType>::ParamType InValue)` — Sets the current value of a property on an instance of a UStruct @param InIndex	The index in the array property to set the value on @param InStruct	The struct to set the property on @param InSourceAddress	The address of the instanced struct @param InValue   The value to set
- L166 _public function_ `void SetCurrentValueForEnum(const UScriptStruct& InStruct, void* InSourceAddress, int64 InValue)` — `UE_DEPRECATED(4.24, "This function is deprecated. Use a SetCurrentValueForEnumAt with InIndex set to 0 for the same result.")` — Sets the current value of an Enum property on an instance of a UStruct @param InStruct	The struct to set the property on @param InSourceAddress	The address of the instanced struct @param InValue   The value to set
- L179 _public prototype_ `void SetCurrentValueForEnumAt(int32 InIndex, const UScriptStruct& InStruct, void* InSourceAddress, int64 InValue);` — Sets the current value of an Enum property on an instance of a UStruct to a certain Index @param InIndex, Index where to write the value @param InStruct	The struct to set the property on @param InSourceAddress	The address of the instanced struct @param InValue   The value to set
- L182 _public function_ `const FString& GetPropertyPath() const` — @return the property path that this binding was initialized from
- L188 _public function_ `const FName& GetPropertyName() const` — @return the property name that this binding was initialized from
- L205 _private function_ `friend uint32 GetTypeHash(const FPropertyNameKey& Key)`
- L246 _private prototype_ `static FPropertyWrapper FindPropertyRecursive(const UScriptStruct* InStruct, TArray<FString>& InPropertyNames, uint32 Index, void* ContainerAddress, int32 PreviousDelta);`
- L247 _private prototype_ `static FPropertyWrapper FindProperty(const UScriptStruct& InStruct, const FString& InPropertyName);`
- L250 _private function_ `FPropertyWrapper FindOrAdd(const UScriptStruct& InStruct)` — Find or add the FPropertyWrapper for the specified struct
- L266 _private member_ `static TMap<FPropertyNameKey, FPropertyWrapper> PropertyCache;` — Mapping of UStructs property
- L269 _private member_ `FString PropertyPath;` — Path to the property we are bound to
- L272 _private member_ `FName PropertyName;` — Actual name of the property we are bound to
- L278 _prototype_ `bool FLiveLinkStructPropertyBindings::GetCurrentValue<bool>(const UScriptStruct& InStruct, const void* InSourceAddress);` — `UE_DEPRECATED(4.24, "This function is deprecated. Use a GetCurrentValueAt with InIndex set to 0 for the same result.")`
- L282 _prototype_ `void FLiveLinkStructPropertyBindings::SetCurrentValue<bool>(const UScriptStruct& InStruct, void* InSourceAddress, TCallTraits<bool>::ParamType InValue);` — `UE_DEPRECATED(4.24, "This function is deprecated. Use a SetCurrentValueAt with InIndex set to 0 for the same result.")`
- L285 _prototype_ `template<> bool FLiveLinkStructPropertyBindings::GetCurrentValueAt<bool>(int32 InIndex, const UScriptStruct& InStruct, const void* InSourceAddress);`
- L286 _prototype_ `template<> bool FLiveLinkStructPropertyBindings::GetCurrentValueAt<bool>(int32 InIndex, const UScriptStruct& InStruct, const void* InSourceAddress);`

#### struct `FLiveLinkStructPropertyBindings::FPropertyNameKey`  
`struct FPropertyNameKey`  
_L194-212_
- L196 _public function_ `FPropertyNameKey(FName InStructName, FName InPropertyName) : StructName(InStructName), PropertyName(InPropertyName)`
- L200 _public function_ `bool operator==(const FPropertyNameKey& Other) const`
- L210 _public member_ `FName StructName;`
- L211 _public member_ `FName PropertyName;`

#### struct `FLiveLinkStructPropertyBindings::FPropertyWrapper`  
`struct FPropertyWrapper`  
_L214-244_
- L216 _public member_ `TWeakFieldPtr<FProperty> Property;`
- L217 _public member_ `int64 DeltaAddress;`
- L219 _public function_ `FProperty* GetProperty() const`
- L225 _public function_ `template<typename ValueType> ValueType* GetPropertyAddress(void* BaseContainerAddress, int32 Index) const`
- L233 _public function_ `template<typename ValueType> const ValueType* GetPropertyAddress(const void* BaseContainerAddress, int32 Index) const`
- L240 _public function_ `FPropertyWrapper() : Property(nullptr) , DeltaAddress(0)`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API LIVELINKMOVIESCENE_API`

### `Plugins/Animation/LiveLink/Source/LiveLinkMovieScene/Public/MovieScene/MovieSceneLiveLinkSubSection.h` (Public)


#### class `UMovieSceneLiveLinkSubSection`  
`class UMovieSceneLiveLinkSubSection : public UObject`  
_L43-106_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UObject`
- desc: Base class to manage recording live link data structure properties If user specifics data need to be managed in a certain way, create your own sub section
- L49 _public prototype_ `UMovieSceneLiveLinkSubSection(const FObjectInitializer& ObjectInitializer);`
- L58 _public prototype_ `virtual void Initialize(TSubclassOf<ULiveLinkRole> InSubjectRole, const TSharedPtr<FLiveLinkStaticDataStruct>& InStaticData);` — Called when creating the section for the first time. Will setup the subject role and the static data Should create the channels associated with the subsection
- L63 _public function_ `virtual int32 CreateChannelProxy(int32 InChannelIndex, TArray<bool>& OutChannelMask, FMovieSceneChannelProxyData& OutChannelData)` — Links the channels of the subsection to the sections's channels proxy
- L68 _public function_ `virtual void RecordFrame(FFrameNumber InFrameNumber, const FLiveLinkFrameDataStruct& InFrameData)` — Adds keyframe to channels associated to sub section from the incoming frame data
- L73 _public function_ `virtual void FinalizeSection(bool bReduceKeys, const FKeyDataOptimizationParams& OptimizationParams)` — Wraps up the sub section's channels. May optimize keyframes if requested
- L78 _public prototype_ `virtual int32 GetChannelCount() const;` — Gets the number of channels associated with this sub section
- L83 _public function_ `virtual bool IsRoleSupported(const TSubclassOf<ULiveLinkRole>& RoleToSupport) const` — Return true if this sub section can manage the specified role
- L84 _public prototype_ `static TArray<TSubclassOf<UMovieSceneLiveLinkSubSection>> GetLiveLinkSubSectionForRole(const TSubclassOf<ULiveLinkRole>& RoleToSupport);`
- L86 _public prototype_ `void SetStaticData(const TSharedPtr<FLiveLinkStaticDataStruct>& InStaticData);`
- L88 _public prototype_ `FLiveLinkPropertyData* GetPropertyData(int32 InPropertyIndex);`
- L92 _public prototype_ `virtual void PostLoad() override;`
- L99 _public member_ `FLiveLinkSubSectionData SubSectionData;` — `UPROPERTY()` — Data associated to properties managed by this sub section
- L102 _public member_ `TSubclassOf<ULiveLinkRole> SubjectRole;` — `UPROPERTY()`
- L105 _protected member_ `TSharedPtr<FLiveLinkStaticDataStruct> StaticData;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API LIVELINKMOVIESCENE_API`
- L20 _namespace_ `namespace MovieSceneLiveLinkSectionUtils`
- L27 _function_ `template<typename ChannelType, typename ExtendedEditorDataType> void CreateChannelEditor(const FText& InDisplayName, ChannelType& InChannel, int32 InChannelIndex, ExtendedEditorDataType&& InExtendedEditorDataType, TArray<bool>& OutChannelMask, FMovieSceneChannelProxyData& OutChannelData)` (scope `MovieSceneLiveLinkSectionUtils`) — Add a channel with editor data filled out. Channel mask value will be used to enable / disable the channel

### `Plugins/Animation/LiveLink/Source/LiveLinkMovieScene/Public/MovieScene/MovieSceneLiveLinkSubSectionAnimation.h` (Public)


#### class `UMovieSceneLiveLinkSubSectionAnimation`  
`class UMovieSceneLiveLinkSubSectionAnimation : public UMovieSceneLiveLinkSubSection`  
_L19-43_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneLiveLinkSubSection`
- desc: A LiveLinkSubSection managing array of transforms contained in the Animation Frame Data structure
- L25 _public prototype_ `UMovieSceneLiveLinkSubSectionAnimation(const FObjectInitializer& ObjectInitializer);`
- L27 _public prototype_ `virtual void Initialize(TSubclassOf<ULiveLinkRole> InSubjectRole, const TSharedPtr<FLiveLinkStaticDataStruct>& InStaticData);`
- L28 _public prototype_ `virtual int32 CreateChannelProxy(int32 InChannelIndex, TArray<bool>& OutChannelMask, FMovieSceneChannelProxyData& OutChannelData);`
- L29 _public prototype_ `virtual void RecordFrame(FFrameNumber InFrameNumber, const FLiveLinkFrameDataStruct& InFrameData) override;`
- L30 _public prototype_ `virtual void FinalizeSection(bool bReduceKeys, const FKeyDataOptimizationParams& OptimizationParams) override;`
- L34 _public prototype_ `virtual bool IsRoleSupported(const TSubclassOf<ULiveLinkRole>& RoleToSupport) const override;`
- L37 _private prototype_ `void CreatePropertiesChannel();`
- L42 _protected member_ `TSharedPtr<FMovieSceneLiveLinkTransformHandler> TransformHandler;` — Helper struct to manage filling channels from transforms

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API LIVELINKMOVIESCENE_API`

### `Plugins/Animation/LiveLink/Source/LiveLinkMovieScene/Public/MovieScene/MovieSceneLiveLinkSubSectionBasicRole.h` (Public)


#### class `UMovieSceneLiveLinkSubSectionBasicRole`  
`class UMovieSceneLiveLinkSubSectionBasicRole : public UMovieSceneLiveLinkSubSection`  
_L17-41_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneLiveLinkSubSection`
- desc: A LiveLinkSubSection managing special properties of the BasicRole
- L23 _public prototype_ `UMovieSceneLiveLinkSubSectionBasicRole(const FObjectInitializer& ObjectInitializer);`
- L25 _public prototype_ `virtual void Initialize(TSubclassOf<ULiveLinkRole> InSubjectRole, const TSharedPtr<FLiveLinkStaticDataStruct>& InStaticData) override;`
- L26 _public prototype_ `virtual int32 CreateChannelProxy(int32 InChannelIndex, TArray<bool>& OutChannelMask, FMovieSceneChannelProxyData& OutChannelData) override;`
- L27 _public prototype_ `virtual void RecordFrame(FFrameNumber InFrameNumber, const FLiveLinkFrameDataStruct& InFrameData) override;`
- L28 _public prototype_ `virtual void FinalizeSection(bool bReduceKeys, const FKeyDataOptimizationParams& OptimizationParams) override;`
- L32 _public prototype_ `virtual bool IsRoleSupported(const TSubclassOf<ULiveLinkRole>& RoleToSupport) const override;`
- L35 _private prototype_ `void CreatePropertiesChannel();`
- L40 _protected member_ `TSharedPtr<IMovieSceneLiveLinkPropertyHandler> PropertyHandler;` — Helper struct to manage filling channels from property array

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API LIVELINKMOVIESCENE_API`

### `Plugins/Animation/LiveLink/Source/LiveLinkMovieScene/Public/MovieScene/MovieSceneLiveLinkSubSectionProperties.h` (Public)


#### class `UMovieSceneLiveLinkSubSectionProperties`  
`class UMovieSceneLiveLinkSubSectionProperties : public UMovieSceneLiveLinkSubSection`  
_L17-46_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneLiveLinkSubSection`
- desc: A LiveLinkSubSection managing properties marked as Interp in the data struct associated with the subject role
- L23 _public prototype_ `UMovieSceneLiveLinkSubSectionProperties(const FObjectInitializer& ObjectInitializer);`
- L25 _public prototype_ `virtual void Initialize(TSubclassOf<ULiveLinkRole> InSubjectRole, const TSharedPtr<FLiveLinkStaticDataStruct>& InStaticData) override;`
- L26 _public prototype_ `virtual int32 CreateChannelProxy(int32 InChannelIndex, TArray<bool>& OutChannelMask, FMovieSceneChannelProxyData& OutChannelData) override;`
- L27 _public prototype_ `virtual void RecordFrame(FFrameNumber InFrameNumber, const FLiveLinkFrameDataStruct& InFrameData) override;`
- L28 _public prototype_ `virtual void FinalizeSection(bool bReduceKeys, const FKeyDataOptimizationParams& OptimizationParams) override;`
- L32 _public prototype_ `virtual bool IsRoleSupported(const TSubclassOf<ULiveLinkRole>& RoleToSupport) const override;`
- L37 _private prototype_ `void CreatePropertyList(UScriptStruct* InScriptStruct, bool bCheckInterpFlag, const FString& InOwner);`
- L38 _private prototype_ `void CreatePropertiesChannel(UScriptStruct* InScriptStruct);`
- L39 _private prototype_ `bool IsPropertyTypeSupported(const FProperty* InProperty) const;`
- L40 _private prototype_ `int32 CreateChannelProxyInternal(FProperty* InPropertyPtr, FLiveLinkPropertyData& OutPropertyData, int32 InPropertyIndex, int32 GlobalIndex, TArray<bool>& OutChannelMask, FMovieSceneChannelProxyData& OutChannelData, const FText& InPropertyName);`
- L45 _protected member_ `TArray<TSharedPtr<IMovieSceneLiveLinkPropertyHandler>> PropertyHandlers;` — Helper struct to manage filling channels for each properties

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API LIVELINKMOVIESCENE_API`

### `Plugins/Animation/LiveLink/Source/LiveLinkMovieScene/Public/MovieScene/MovieSceneLiveLinkTrack.h` (Public)


#### class `UMovieSceneLiveLinkTrack`  
`class UMovieSceneLiveLinkTrack : public UMovieScenePropertyTrack, public IMovieSceneTrackTemplateProducer`  
_L15-42_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieScenePropertyTrack,IMovieSceneTrackTemplateProducer`
- desc: A track for animating FMoveSceneLiveLinkTrack properties.
- L21 _public prototype_ `UMovieSceneLiveLinkTrack(const FObjectInitializer& ObjectInitializer);`
- L23 _public function_ `void SetTrackRole(const TSubclassOf<ULiveLinkRole>& InTrackRole)`
- L24 _public function_ `TSubclassOf<ULiveLinkRole> GetTrackRole() const`
- L27 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const override;` — UMovieSceneTrack interface
- L28 _public prototype_ `virtual UMovieSceneSection* CreateNewSection() override;`
- L29 _public prototype_ `virtual FMovieSceneEvalTemplatePtr CreateTemplateForSection(const UMovieSceneSection& InSection) const override;`
- L30 _public prototype_ `virtual void PostCompile(FMovieSceneEvaluationTrack& Track, const FMovieSceneTrackCompilerArgs& Args) const override;`
- L33 _public function_ `virtual bool CanRename() const override`
- L35 _public prototype_ `virtual void SetDisplayName(const FText& NewDisplayName) override;`
- L41 _protected member_ `TSubclassOf<ULiveLinkRole> TrackRole;` — `UPROPERTY()`

### `Plugins/Animation/LiveLink/Source/LiveLinkMovieScene/Public/MovieScene/MovieSceneLiveLinkTransformHandler.h` (Public)


#### class `FMovieSceneLiveLinkTransformHandler`  
`class FMovieSceneLiveLinkTransformHandler : public IMovieSceneLiveLinkPropertyHandler`  
_L16-50_
- inherits: `IMovieSceneLiveLinkPropertyHandler`
- L19 _public function_ `FMovieSceneLiveLinkTransformHandler(const FLiveLinkStructPropertyBindings& InBinding, FLiveLinkPropertyData* PropertyStorage) : PropertyStorage(PropertyStorage) , PropertyBinding(InBinding) , ElementCount(0)`
- L26 _public prototype_ `virtual ~FMovieSceneLiveLinkTransformHandler() = default;`
- L30 _public prototype_ `virtual void CreateChannels(const UScriptStruct& InStruct, int32 InElementCount) override;`
- L31 _public prototype_ `virtual void RecordFrame(const FFrameNumber& InFrameNumber, const UScriptStruct& InStruct, const FLiveLinkBaseFrameData* InFrameData) override;`
- L32 _public prototype_ `virtual void Finalize(bool bInReduceKeys, const FKeyDataOptimizationParams& InOptimizationParams) override;`
- L34 _public prototype_ `virtual void InitializeFromExistingChannels(const UScriptStruct& InStruct) override;`
- L35 _public prototype_ `virtual void FillFrame(int32 InKeyIndex, const FLiveLinkWorldTime& InWorldTime, const TOptional<FQualifiedFrameTime>& InTimecodeTime, const UScriptStruct& InStruct, FLiveLinkBaseFrameData* OutFrame) override;`
- L36 _public prototype_ `virtual void FillFrameInterpolated(const FFrameTime& InFrameTime, const FLiveLinkWorldTime& InWorldTime, const TOptional<FQualifiedFrameTime>& InTimecodeTime, const UScriptStruct& InStruct, FLiveLinkBaseFrameData* OutFrame) override;`
- L40 _protected member_ `FLiveLinkPropertyData* PropertyStorage;` — Channel storage for this property
- L43 _protected member_ `FLiveLinkStructPropertyBindings PropertyBinding;` — Binding for this property
- L46 _protected member_ `int32 ElementCount;` — Number of elements to record each frame
- L49 _protected member_ `TArray<FLiveLinkTransformKeys> BufferedTransformsPerElement;` — Buffer of transform keys. Keys are inserted into tracks in FinalizeTrack()
