# Developer / AnimationDataController

- module root: `Source/Developer/AnimationDataController`
- headers: 3; symbols: 294
- symbol kinds: class=30, function=51, macro=1, member=60, namespace=2, prototype=150
- PrivateDependencyModuleNames: CurveEditor, Engine, MovieScene, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject

### `Source/Developer/AnimationDataController/Public/AnimDataController.h` (Public)


#### class `UAnimDataController`  
`class UAnimDataController : public UObject, public IAnimationDataController`  
_L19-126_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UObject,IAnimationDataController`
- L24 _public function_ `UAnimDataController() #if WITH_EDITOR : BracketDepth(0) #endif`
- L32 _public prototype_ `virtual void SetModel(TScriptInterface<IAnimationDataModel> InModel) override;` — Begin IAnimationDataController overrides
- L33 _public function_ `virtual TScriptInterface<IAnimationDataModel> GetModelInterface() const override`
- L34 _public function_ `virtual const IAnimationDataModel* const GetModel() const override`
- L35 _public prototype_ `virtual void OpenBracket(const FText& InTitle, bool bShouldTransact = true) override;`
- L36 _public prototype_ `virtual void CloseBracket(bool bShouldTransact = true) override;`
- L37 _public prototype_ `virtual void SetNumberOfFrames(FFrameNumber Length, bool bShouldTransact = true) override;`
- L38 _public prototype_ `virtual void ResizeNumberOfFrames(FFrameNumber NewLength, FFrameNumber T0, FFrameNumber T1, bool bShouldTransact = true) override;`
- L39 _public prototype_ `virtual void ResizeInFrames(FFrameNumber Length, FFrameNumber T0, FFrameNumber T1, bool bShouldTransact = true) override;`
- L40 _public prototype_ `virtual void SetFrameRate(FFrameRate FrameRate, bool bShouldTransact = true) override;`
- L41 _public prototype_ `virtual void SetPlayLength(float Length, bool bShouldTransact = true) override;`
- L42 _public prototype_ `virtual void ResizePlayLength(float NewLength, float T0, float T1, bool bShouldTransact = true) override;`
- L43 _public prototype_ `virtual void Resize(float Length, float T0, float T1, bool bShouldTransact = true) override;`
- L44 _public prototype_ `virtual bool AddBoneCurve(FName BoneName, bool bShouldTransact = true) override;`
- L45 _public prototype_ `virtual int32 InsertBoneTrack(FName BoneName, int32 DesiredIndex, bool bShouldTransact = true) override;`
- L46 _public prototype_ `virtual bool RemoveBoneTrack(FName BoneName, bool bShouldTransact = true) override;`
- L47 _public prototype_ `virtual void RemoveAllBoneTracks(bool bShouldTransact = true) override;`
- L48 _public prototype_ `virtual bool SetBoneTrackKeys(FName BoneName, const TArray<FVector3f>& PositionalKeys, const TArray<FQuat4f>& RotationalKeys, const TArray<FVector3f>& ScalingKeys, bool bShouldTransact = true) override;`
- L49 _public prototype_ `virtual bool SetBoneTrackKeys(FName BoneName, const TArray<FVector>& PositionalKeys, const TArray<FQuat>& RotationalKeys, const TArray<FVector>& ScalingKeys, bool bShouldTransact = true) override;`
- L50 _public prototype_ `virtual bool UpdateBoneTrackKeys(FName BoneName, const FInt32Range& KeyRangeToSet, const TArray<FVector3f>& PositionalKeys, const TArray<FQuat4f>& RotationalKeys, const TArray<FVector3f>& ScalingKeys, bool bShouldTransact = true) override;`
- L51 _public prototype_ `virtual bool UpdateBoneTrackKeys(FName BoneName, const FInt32Range& KeyRangeToSet, const TArray<FVector>& PositionalKeys, const TArray<FQuat>& RotationalKeys, const TArray<FVector>& ScalingKeys, bool bShouldTransact = true) override;`
- L52 _public prototype_ `virtual bool AddCurve(const FAnimationCurveIdentifier& CurveId, int32 CurveFlags = 0x00000004, bool bShouldTransact = true) override;`
- L53 _public prototype_ `virtual bool DuplicateCurve(const FAnimationCurveIdentifier& CopyCurveId, const FAnimationCurveIdentifier& NewCurveId, bool bShouldTransact = true) override;`
- L54 _public prototype_ `virtual bool RemoveCurve(const FAnimationCurveIdentifier& CurveId, bool bShouldTransact = true) override;`
- L55 _public prototype_ `virtual void RemoveAllCurvesOfType(ERawCurveTrackTypes SupportedCurveType, bool bShouldTransact = true) override;`
- L56 _public prototype_ `virtual bool SetCurveFlag(const FAnimationCurveIdentifier& CurveId, EAnimAssetCurveFlags Flag, bool bState = true, bool bShouldTransact = true) override;`
- L57 _public prototype_ `virtual bool SetCurveFlags(const FAnimationCurveIdentifier& CurveId, int32 Flags, bool bShouldTransact = true) override;`
- L58 _public prototype_ `virtual bool SetTransformCurveKeys(const FAnimationCurveIdentifier& CurveId, const TArray<FTransform>& TransformValues, const TArray<float>& TimeKeys, bool bShouldTransact = true) override;`
- L59 _public prototype_ `virtual bool SetTransformCurveKey(const FAnimationCurveIdentifier& CurveId, float Time, const FTransform& Value, bool bShouldTransact = true) override;`
- L60 _public prototype_ `virtual bool RemoveTransformCurveKey(const FAnimationCurveIdentifier& CurveId, float Time, bool bShouldTransact = true) override;`
- L61 _public prototype_ `virtual bool RenameCurve(const FAnimationCurveIdentifier& CurveToRenameId, const FAnimationCurveIdentifier& NewCurveId, bool bShouldTransact = true) override;`
- L62 _public prototype_ `virtual bool SetCurveColor(const FAnimationCurveIdentifier& CurveId, FLinearColor Color, bool bShouldTransact = true) override;`
- L63 _public prototype_ `virtual bool SetCurveComment(const FAnimationCurveIdentifier& CurveId, const FString& Comment, bool bShouldTransact = true) override;`
- L64 _public prototype_ `virtual bool ScaleCurve(const FAnimationCurveIdentifier& CurveId, float Origin, float Factor, bool bShouldTransact = true) override;`
- L65 _public prototype_ `virtual bool SetCurveKey(const FAnimationCurveIdentifier& CurveId, const FRichCurveKey& Key, bool bShouldTransact = true) override;`
- L66 _public prototype_ `virtual bool RemoveCurveKey(const FAnimationCurveIdentifier& CurveId, float Time, bool bShouldTransact = true) override;`
- L67 _public prototype_ `virtual bool SetCurveKeys(const FAnimationCurveIdentifier& CurveId, const TArray<FRichCurveKey>& CurveKeys, bool bShouldTransact = true) override;`
- L68 _public prototype_ `virtual bool SetCurveAttributes(const FAnimationCurveIdentifier& CurveId, const FCurveAttributes& Attributes, bool bShouldTransact = true) override;`
- L69 _public prototype_ `virtual bool RemoveBoneTracksMissingFromSkeleton(const USkeleton* Skeleton, bool bShouldTransact = true) override;`
- L70 _public prototype_ `virtual void UpdateAttributesFromSkeleton(const USkeleton* Skeleton, bool bShouldTransact = true) override;`
- L71 _public prototype_ `virtual void NotifyPopulated() override;`
- L72 _public prototype_ `virtual void ResetModel(bool bShouldTransact = true) override;`
- L73 _public prototype_ `virtual bool AddAttribute(const FAnimationAttributeIdentifier& AttributeIdentifier, bool bShouldTransact = true) override;`
- L74 _public prototype_ `virtual bool RemoveAttribute(const FAnimationAttributeIdentifier& AttributeIdentifier, bool bShouldTransact = true) override;`
- L75 _public prototype_ `virtual int32 RemoveAllAttributesForBone(const FName& BoneName, bool bShouldTransact = true) override;`
- L76 _public prototype_ `virtual int32 RemoveAllAttributes(bool bShouldTransact = true) override;`
- L77 _public function_ `virtual bool SetAttributeKey(const FAnimationAttributeIdentifier& AttributeIdentifier, float Time, const void* KeyValue, const UScriptStruct* TypeStruct, bool bShouldTransact = true) override`
- L81 _public function_ `virtual bool SetAttributeKeys(const FAnimationAttributeIdentifier& AttributeIdentifier, TArrayView<const float> Times, TArrayView<const void*> KeyValues, const UScriptStruct* TypeStruct, bool bShouldTransact = true) override`
- L85 _public prototype_ `virtual bool RemoveAttributeKey(const FAnimationAttributeIdentifier& AttributeIdentifier, float Time, bool bShouldTransact = true) override;`
- L86 _public prototype_ `virtual bool DuplicateAttribute(const FAnimationAttributeIdentifier& AttributeIdentifier, const FAnimationAttributeIdentifier& NewAttributeIdentifier, bool bShouldTransact = true) override;`
- L87 _public prototype_ `virtual void UpdateWithSkeleton(USkeleton* TargetSkeleton, bool bShouldTransact = true) override;`
- L88 _public prototype_ `virtual void PopulateWithExistingModel(TScriptInterface<IAnimationDataModel> InModel) override;`
- L89 _public function_ `virtual void InitializeModel() override`
- L91 _protected prototype_ `virtual void NotifyBracketOpen() override;`
- L92 _protected prototype_ `virtual void NotifyBracketClosed() override;`
- L97 _private prototype_ `bool SetAttributeKey_Internal(const FAnimationAttributeIdentifier& AttributeIdentifier, float Time, const void* KeyValue, const UScriptStruct* TypeStruct, bool bShouldTransact = true);` — Internal functionality for setting Attribute curve key(s)
- L98 _private prototype_ `bool SetAttributeKeys_Internal(const FAnimationAttributeIdentifier& AttributeIdentifier, TArrayView<const float> Times, TArrayView<const void*> KeyValues, const UScriptStruct* TypeStruct, bool bShouldTransact = true);`
- L101 _private prototype_ `void ResizeCurves(float NewLength, bool bInserted, float T0, float T1, bool bShouldTransact = true);` — Resizes the curve/attribute data stored on the model according to the provided new length and time at which to insert or remove time
- L102 _private prototype_ `void ResizeAttributes(float NewLength, bool bInserted, float T0, float T1, bool bShouldTransact = true);`
- L104 _private prototype_ `virtual bool ShouldTransact(bool bInLocalShouldTransact) const override;`
- L109 _private member_ `int32 BracketDepth;`
- L110 _private member_ `bool bShouldTransactBracket = false;`
- L115 _private member_ `TWeakObjectPtr<UAnimDataModel> Model;` — `UPROPERTY(transient)`
- L118 _private member_ `TScriptInterface<IAnimationDataModel> ModelInterface;` — `UPROPERTY(transient)`

### `Source/Developer/AnimationDataController/Public/AnimDataControllerActions.h` (Public)


#### class `UE::Anim::FAnimDataBaseAction`  
`class FAnimDataBaseAction : public FSwapChange`  
_L30-40_
- inherits: `FSwapChange`
- desc: UAnimDataController instanced FChange-based objects used for storing mutations to an IAnimationDataModel within the Transaction Buffer. Each Action class represents an (invertable) operation mutating an IAnimationDataModel object utilizing a UAnimDataController. Allowing for a more granular approach to undo/redo-ing changes while also allowing for script-based interoperability.
- L33 _public prototype_ `virtual TUniquePtr<FChange> Execute(UObject* Object) final;`
- L34 _public prototype_ `virtual ~FAnimDataBaseAction() = default;`
- L35 _public prototype_ `virtual FString ToString() const override;`
- L38 _protected prototype_ `virtual TUniquePtr<FChange> ExecuteInternal(IAnimationDataModel* Model, IAnimationDataController* Controller) = 0;`
- L39 _protected prototype_ `virtual FString ToStringInternal() const = 0;`

#### class `UE::Anim::FOpenBracketAction`  
`class FOpenBracketAction : public FAnimDataBaseAction`  
_L42-54_
- inherits: `FAnimDataBaseAction`
- L45 _public function_ `explicit FOpenBracketAction(const FString& InDescription) : Description(InDescription)`
- L46 _public prototype_ `virtual ~FOpenBracketAction() = default;`
- L48 _protected function_ `FOpenBracketAction()`
- L49 _protected prototype_ `virtual TUniquePtr<FChange> ExecuteInternal(IAnimationDataModel* Model, IAnimationDataController* Controller) override;`
- L50 _protected prototype_ `virtual FString ToStringInternal() const override;`
- L53 _protected member_ `FString Description;`

#### class `UE::Anim::FCloseBracketAction`  
`class FCloseBracketAction : public FAnimDataBaseAction`  
_L56-68_
- inherits: `FAnimDataBaseAction`
- L59 _public function_ `explicit FCloseBracketAction(const FString& InDescription) : Description(InDescription)`
- L60 _public prototype_ `virtual ~FCloseBracketAction() = default;`
- L62 _protected function_ `FCloseBracketAction()`
- L63 _protected prototype_ `virtual TUniquePtr<FChange> ExecuteInternal(IAnimationDataModel* Model, IAnimationDataController* Controller) override;`
- L64 _protected prototype_ `virtual FString ToStringInternal() const override;`
- L67 _protected member_ `FString Description;`

#### class `UE::Anim::FAddTrackAction`  
`class FAddTrackAction : public FAnimDataBaseAction`  
_L70-83_
- inherits: `FAnimDataBaseAction`
- L73 _public prototype_ `explicit FAddTrackAction(const FName& InName, TArray<FTransform>&& InTransformData);`
- L74 _public prototype_ `virtual ~FAddTrackAction() = default;`
- L76 _protected function_ `FAddTrackAction()`
- L77 _protected prototype_ `virtual TUniquePtr<FChange> ExecuteInternal(IAnimationDataModel* Model, IAnimationDataController* Controller) override;`
- L78 _protected prototype_ `virtual FString ToStringInternal() const override;`
- L81 _protected member_ `FName Name;`
- L82 _protected member_ `TArray<FTransform> TransformData;`

#### class `UE::Anim::FRemoveTrackAction`  
`class FRemoveTrackAction : public FAnimDataBaseAction`  
_L85-97_
- inherits: `FAnimDataBaseAction`
- L88 _public prototype_ `explicit FRemoveTrackAction(const FName& InName);`
- L89 _public prototype_ `virtual ~FRemoveTrackAction() = default;`
- L91 _protected function_ `FRemoveTrackAction()`
- L92 _protected prototype_ `virtual TUniquePtr<FChange> ExecuteInternal(IAnimationDataModel* Model, IAnimationDataController* Controller) override;`
- L93 _protected prototype_ `virtual FString ToStringInternal() const override;`
- L96 _protected member_ `FName Name;`

#### class `UE::Anim::FSetTrackKeysAction`  
`class FSetTrackKeysAction : public FAnimDataBaseAction`  
_L99-112_
- inherits: `FAnimDataBaseAction`
- L102 _public prototype_ `explicit FSetTrackKeysAction(const FName& InName, TArray<FTransform>& InTransformData);`
- L103 _public prototype_ `virtual ~FSetTrackKeysAction() = default;`
- L105 _protected function_ `FSetTrackKeysAction()`
- L106 _protected prototype_ `virtual TUniquePtr<FChange> ExecuteInternal(IAnimationDataModel* Model, IAnimationDataController* Controller) override;`
- L107 _protected prototype_ `virtual FString ToStringInternal() const override;`
- L110 _protected member_ `FName Name;`
- L111 _protected member_ `TArray<FTransform> TransformData;`

#### class `UE::Anim::FResizePlayLengthInFramesAction`  
`class FResizePlayLengthInFramesAction : public FAnimDataBaseAction`  
_L114-128_
- inherits: `FAnimDataBaseAction`
- L117 _public prototype_ `explicit FResizePlayLengthInFramesAction(const IAnimationDataModel* InModel, FFrameNumber F0, FFrameNumber F1);`
- L118 _public prototype_ `virtual ~FResizePlayLengthInFramesAction() override = default;`
- L120 _protected function_ `FResizePlayLengthInFramesAction()`
- L121 _protected prototype_ `virtual TUniquePtr<FChange> ExecuteInternal(IAnimationDataModel* Model, IAnimationDataController* Controller) override;`
- L122 _protected prototype_ `virtual FString ToStringInternal() const override;`
- L125 _protected member_ `FFrameNumber Length;`
- L126 _protected member_ `FFrameNumber Frame0;`
- L127 _protected member_ `FFrameNumber Frame1;`

#### class `UE::Anim::FSetFrameRateAction`  
`class FSetFrameRateAction : public FAnimDataBaseAction`  
_L130-142_
- inherits: `FAnimDataBaseAction`
- L133 _public prototype_ `explicit FSetFrameRateAction(const IAnimationDataModel* InModel);`
- L134 _public prototype_ `virtual ~FSetFrameRateAction() override = default;`
- L136 _protected function_ `FSetFrameRateAction()`
- L137 _protected prototype_ `virtual TUniquePtr<FChange> ExecuteInternal(IAnimationDataModel* Model, IAnimationDataController* Controller) override;`
- L138 _protected prototype_ `virtual FString ToStringInternal() const override;`
- L141 _protected member_ `FFrameRate FrameRate;`

#### class `UE::Anim::FAddCurveAction`  
`class FAddCurveAction : public FAnimDataBaseAction`  
_L144-158_
- inherits: `FAnimDataBaseAction`
- L147 _public function_ `explicit FAddCurveAction(const FAnimationCurveIdentifier& InCurveId, int32 InFlags) : CurveId(InCurveId), Flags(InFlags)`
- L149 _public prototype_ `virtual ~FAddCurveAction() = default;`
- L151 _protected function_ `FAddCurveAction()`
- L152 _protected prototype_ `virtual TUniquePtr<FChange> ExecuteInternal(IAnimationDataModel* Model, IAnimationDataController* Controller) override;`
- L153 _protected prototype_ `virtual FString ToStringInternal() const override;`
- L156 _protected member_ `FAnimationCurveIdentifier CurveId;`
- L157 _protected member_ `int32 Flags;`

#### class `UE::Anim::FAddFloatCurveAction`  
`class FAddFloatCurveAction : public FAnimDataBaseAction`  
_L160-175_
- inherits: `FAnimDataBaseAction`
- L163 _public function_ `explicit FAddFloatCurveAction(const FAnimationCurveIdentifier& InCurveId, int32 InFlags, const TArray<FRichCurveKey>& InKeys, const FLinearColor& InColor) : CurveId(InCurveId), Flags(InFlags), Keys(InKeys), Color(InColor)`
- L164 _public prototype_ `virtual ~FAddFloatCurveAction() = default;`
- L166 _protected function_ `FAddFloatCurveAction()`
- L167 _protected prototype_ `virtual TUniquePtr<FChange> ExecuteInternal(IAnimationDataModel* Model, IAnimationDataController* Controller) override;`
- L168 _protected prototype_ `virtual FString ToStringInternal() const override;`
- L171 _protected member_ `FAnimationCurveIdentifier CurveId;`
- L172 _protected member_ `int32 Flags;`
- L173 _protected member_ `TArray<FRichCurveKey> Keys;`
- L174 _protected member_ `FLinearColor Color;`

#### class `UE::Anim::FAddTransformCurveAction`  
`class FAddTransformCurveAction : public FAnimDataBaseAction`  
_L177-192_
- inherits: `FAnimDataBaseAction`
- L180 _public prototype_ `explicit FAddTransformCurveAction(const FAnimationCurveIdentifier& InCurveId, int32 InFlags, const FTransformCurve& InTransformCurve);`
- L181 _public prototype_ `virtual ~FAddTransformCurveAction() = default;`
- L183 _protected function_ `FAddTransformCurveAction()`
- L184 _protected prototype_ `virtual TUniquePtr<FChange> ExecuteInternal(IAnimationDataModel* Model, IAnimationDataController* Controller) override;`
- L185 _protected prototype_ `virtual FString ToStringInternal() const override;`
- L188 _protected member_ `FAnimationCurveIdentifier CurveId;`
- L189 _protected member_ `int32 Flags;`
- L191 _protected member_ `TArray<FRichCurveKey> SubCurveKeys[9];`

#### class `UE::Anim::FRemoveCurveAction`  
`class FRemoveCurveAction : public FAnimDataBaseAction`  
_L194-206_
- inherits: `FAnimDataBaseAction`
- L197 _public function_ `explicit FRemoveCurveAction(const FAnimationCurveIdentifier& InCurveId) : CurveId(InCurveId)`
- L198 _public prototype_ `virtual ~FRemoveCurveAction() = default;`
- L200 _protected function_ `FRemoveCurveAction()`
- L201 _protected prototype_ `virtual TUniquePtr<FChange> ExecuteInternal(IAnimationDataModel* Model, IAnimationDataController* Controller) override;`
- L202 _protected prototype_ `virtual FString ToStringInternal() const override;`
- L205 _protected member_ `FAnimationCurveIdentifier CurveId;`

#### class `UE::Anim::FSetCurveFlagsAction`  
`class FSetCurveFlagsAction : public FAnimDataBaseAction`  
_L208-222_
- inherits: `FAnimDataBaseAction`
- L211 _public function_ `explicit FSetCurveFlagsAction(const FAnimationCurveIdentifier& InCurveId, int32 InFlags, ERawCurveTrackTypes InCurveType) : CurveId(InCurveId), Flags(InFlags), CurveType(InCurveType)`
- L212 _public prototype_ `virtual ~FSetCurveFlagsAction() = default;`
- L214 _protected function_ `FSetCurveFlagsAction()`
- L215 _protected prototype_ `virtual TUniquePtr<FChange> ExecuteInternal(IAnimationDataModel* Model, IAnimationDataController* Controller) override;`
- L216 _protected prototype_ `virtual FString ToStringInternal() const override;`
- L219 _protected member_ `FAnimationCurveIdentifier CurveId;`
- L220 _protected member_ `int32 Flags;`
- L221 _protected member_ `ERawCurveTrackTypes CurveType;`

#### class `UE::Anim::FRenameCurveAction`  
`class FRenameCurveAction : public FAnimDataBaseAction`  
_L224-237_
- inherits: `FAnimDataBaseAction`
- L227 _public function_ `explicit FRenameCurveAction(const FAnimationCurveIdentifier& InCurveId, const FAnimationCurveIdentifier& InNewCurveId) : CurveId(InCurveId), NewCurveId(InNewCurveId)`
- L228 _public prototype_ `virtual ~FRenameCurveAction() = default;`
- L230 _protected function_ `FRenameCurveAction()`
- L231 _protected prototype_ `virtual TUniquePtr<FChange> ExecuteInternal(IAnimationDataModel* Model, IAnimationDataController* Controller) override;`
- L232 _protected prototype_ `virtual FString ToStringInternal() const override;`
- L235 _protected member_ `FAnimationCurveIdentifier CurveId;`
- L236 _protected member_ `FAnimationCurveIdentifier NewCurveId;`

#### class `UE::Anim::FScaleCurveAction`  
`class FScaleCurveAction : public FAnimDataBaseAction`  
_L239-254_
- inherits: `FAnimDataBaseAction`
- L242 _public prototype_ `explicit FScaleCurveAction(const FAnimationCurveIdentifier& InCurveId, float InOrigin, float InFactor, ERawCurveTrackTypes InCurveType);`
- L243 _public prototype_ `virtual ~FScaleCurveAction() = default;`
- L245 _protected function_ `FScaleCurveAction()`
- L246 _protected prototype_ `virtual TUniquePtr<FChange> ExecuteInternal(IAnimationDataModel* Model, IAnimationDataController* Controller) override;`
- L247 _protected prototype_ `virtual FString ToStringInternal() const override;`
- L250 _protected member_ `FAnimationCurveIdentifier CurveId;`
- L251 _protected member_ `ERawCurveTrackTypes CurveType;`
- L252 _protected member_ `float Origin;`
- L253 _protected member_ `float Factor;`

#### class `UE::Anim::FAddRichCurveKeyAction`  
`class FAddRichCurveKeyAction : public FAnimDataBaseAction`  
_L256-270_
- inherits: `FAnimDataBaseAction`
- L259 _public function_ `explicit FAddRichCurveKeyAction(const FAnimationCurveIdentifier& InCurveId, const FRichCurveKey& InKey) : CurveId(InCurveId), Key(InKey)`
- L260 _public prototype_ `virtual ~FAddRichCurveKeyAction() = default;`
- L262 _protected function_ `FAddRichCurveKeyAction()`
- L263 _protected prototype_ `virtual TUniquePtr<FChange> ExecuteInternal(IAnimationDataModel* Model, IAnimationDataController* Controller) override;`
- L264 _protected prototype_ `virtual FString ToStringInternal() const override;`
- L267 _protected member_ `FAnimationCurveIdentifier CurveId;`
- L268 _protected member_ `ERawCurveTrackTypes CurveType;`
- L269 _protected member_ `FRichCurveKey Key;`

#### class `UE::Anim::FSetRichCurveKeyAction`  
`class FSetRichCurveKeyAction : public FAnimDataBaseAction`  
_L272-285_
- inherits: `FAnimDataBaseAction`
- L275 _public function_ `explicit FSetRichCurveKeyAction(const FAnimationCurveIdentifier& InCurveId, const FRichCurveKey& InKey) : CurveId(InCurveId), Key(InKey)`
- L276 _public prototype_ `virtual ~FSetRichCurveKeyAction() = default;`
- L278 _protected function_ `FSetRichCurveKeyAction()`
- L279 _protected prototype_ `virtual TUniquePtr<FChange> ExecuteInternal(IAnimationDataModel* Model, IAnimationDataController* Controller) override;`
- L280 _protected prototype_ `virtual FString ToStringInternal() const override;`
- L283 _protected member_ `FAnimationCurveIdentifier CurveId;`
- L284 _protected member_ `FRichCurveKey Key;`

#### class `UE::Anim::FRemoveRichCurveKeyAction`  
`class FRemoveRichCurveKeyAction : public FAnimDataBaseAction`  
_L287-300_
- inherits: `FAnimDataBaseAction`
- L290 _public function_ `explicit FRemoveRichCurveKeyAction(const FAnimationCurveIdentifier& InCurveId, const float InTime) : CurveId(InCurveId), Time(InTime)`
- L291 _public prototype_ `virtual ~FRemoveRichCurveKeyAction() = default;`
- L293 _protected function_ `FRemoveRichCurveKeyAction()`
- L294 _protected prototype_ `virtual TUniquePtr<FChange> ExecuteInternal(IAnimationDataModel* Model, IAnimationDataController* Controller) override;`
- L295 _protected prototype_ `virtual FString ToStringInternal() const override;`
- L298 _protected member_ `FAnimationCurveIdentifier CurveId;`
- L299 _protected member_ `float Time;`

#### class `UE::Anim::FSetRichCurveKeysAction`  
`class FSetRichCurveKeysAction : public FAnimDataBaseAction`  
_L302-315_
- inherits: `FAnimDataBaseAction`
- L305 _public function_ `explicit FSetRichCurveKeysAction(const FAnimationCurveIdentifier& InCurveId, const TArray<FRichCurveKey>& InKeys) : CurveId(InCurveId), Keys(InKeys)`
- L306 _public prototype_ `virtual ~FSetRichCurveKeysAction() = default;`
- L308 _protected function_ `FSetRichCurveKeysAction()`
- L309 _protected prototype_ `virtual TUniquePtr<FChange> ExecuteInternal(IAnimationDataModel* Model, IAnimationDataController* Controller) override;`
- L310 _protected prototype_ `virtual FString ToStringInternal() const override;`
- L313 _protected member_ `FAnimationCurveIdentifier CurveId;`
- L314 _protected member_ `TArray<FRichCurveKey> Keys;`

#### class `UE::Anim::FSetRichCurveAttributesAction`  
`class FSetRichCurveAttributesAction : public FAnimDataBaseAction`  
_L317-330_
- inherits: `FAnimDataBaseAction`
- L320 _public function_ `explicit FSetRichCurveAttributesAction(const FAnimationCurveIdentifier& InCurveId, const FCurveAttributes& InAttributes) : CurveId(InCurveId), Attributes(InAttributes)`
- L321 _public prototype_ `virtual ~FSetRichCurveAttributesAction() = default;`
- L323 _protected function_ `FSetRichCurveAttributesAction()`
- L324 _protected prototype_ `virtual TUniquePtr<FChange> ExecuteInternal(IAnimationDataModel* Model, IAnimationDataController* Controller) override;`
- L325 _protected prototype_ `virtual FString ToStringInternal() const override;`
- L328 _protected member_ `FAnimationCurveIdentifier CurveId;`
- L329 _protected member_ `FCurveAttributes Attributes;`

#### class `UE::Anim::FSetCurveColorAction`  
`class FSetCurveColorAction : public FAnimDataBaseAction`  
_L332-345_
- inherits: `FAnimDataBaseAction`
- L335 _public function_ `explicit FSetCurveColorAction(const FAnimationCurveIdentifier& InCurveId, const FLinearColor& InColor) : CurveId(InCurveId), Color(InColor)`
- L336 _public prototype_ `virtual ~FSetCurveColorAction() = default;`
- L338 _protected function_ `FSetCurveColorAction()`
- L339 _protected prototype_ `virtual TUniquePtr<FChange> ExecuteInternal(IAnimationDataModel* Model, IAnimationDataController* Controller) override;`
- L340 _protected prototype_ `virtual FString ToStringInternal() const override;`
- L343 _protected member_ `FAnimationCurveIdentifier CurveId;`
- L344 _protected member_ `FLinearColor Color;`

#### class `UE::Anim::FSetCurveCommentAction`  
`class FSetCurveCommentAction : public FAnimDataBaseAction`  
_L347-360_
- inherits: `FAnimDataBaseAction`
- L350 _public function_ `explicit FSetCurveCommentAction(const FAnimationCurveIdentifier& InCurveId, const FString& InComment) : CurveId(InCurveId), Comment(InComment)`
- L351 _public prototype_ `virtual ~FSetCurveCommentAction() = default;`
- L353 _protected function_ `FSetCurveCommentAction()`
- L354 _protected prototype_ `virtual TUniquePtr<FChange> ExecuteInternal(IAnimationDataModel* Model, IAnimationDataController* Controller) override;`
- L355 _protected prototype_ `virtual FString ToStringInternal() const override;`
- L358 _protected member_ `FAnimationCurveIdentifier CurveId;`
- L359 _protected member_ `FString Comment;`

#### class `UE::Anim::FAddAtributeAction`  
`class FAddAtributeAction : public FAnimDataBaseAction`  
_L362-375_
- inherits: `FAnimDataBaseAction`
- L365 _public prototype_ `explicit FAddAtributeAction(const FAnimatedBoneAttribute& InAttribute);`
- L366 _public prototype_ `virtual ~FAddAtributeAction() = default;`
- L368 _protected function_ `FAddAtributeAction()`
- L369 _protected prototype_ `virtual TUniquePtr<FChange> ExecuteInternal(IAnimationDataModel* Model, IAnimationDataController* Controller) override;`
- L370 _protected prototype_ `virtual FString ToStringInternal() const override;`
- L373 _protected member_ `FAnimationAttributeIdentifier AttributeId;`
- L374 _protected member_ `TArray<FAttributeKey> Keys;`

#### class `UE::Anim::FRemoveAtributeAction`  
`class FRemoveAtributeAction : public FAnimDataBaseAction`  
_L377-389_
- inherits: `FAnimDataBaseAction`
- L380 _public function_ `explicit FRemoveAtributeAction(const FAnimationAttributeIdentifier& InAttributeId) : AttributeId(InAttributeId)`
- L381 _public prototype_ `virtual ~FRemoveAtributeAction() = default;`
- L383 _protected function_ `FRemoveAtributeAction()`
- L384 _protected prototype_ `virtual TUniquePtr<FChange> ExecuteInternal(IAnimationDataModel* Model, IAnimationDataController* Controller) override;`
- L385 _protected prototype_ `virtual FString ToStringInternal() const override;`
- L388 _protected member_ `FAnimationAttributeIdentifier AttributeId;`

#### class `UE::Anim::FAddAtributeKeyAction`  
`class FAddAtributeKeyAction : public FAnimDataBaseAction`  
_L391-404_
- inherits: `FAnimDataBaseAction`
- L394 _public function_ `explicit FAddAtributeKeyAction(const FAnimationAttributeIdentifier& InAttributeId, const FAttributeKey& InKey) : AttributeId(InAttributeId), Key(InKey)`
- L395 _public prototype_ `virtual ~FAddAtributeKeyAction() = default;`
- L397 _protected function_ `FAddAtributeKeyAction()`
- L398 _protected prototype_ `virtual TUniquePtr<FChange> ExecuteInternal(IAnimationDataModel* Model, IAnimationDataController* Controller) override;`
- L399 _protected prototype_ `virtual FString ToStringInternal() const override;`
- L402 _protected member_ `FAnimationAttributeIdentifier AttributeId;`
- L403 _protected member_ `FAttributeKey Key;`

#### class `UE::Anim::FSetAtributeKeyAction`  
`class FSetAtributeKeyAction : public FAnimDataBaseAction`  
_L406-419_
- inherits: `FAnimDataBaseAction`
- L409 _public function_ `explicit FSetAtributeKeyAction(const FAnimationAttributeIdentifier& InAttributeId, const FAttributeKey& InKey) : AttributeId(InAttributeId), Key(InKey)`
- L410 _public prototype_ `virtual ~FSetAtributeKeyAction() = default;`
- L412 _protected function_ `FSetAtributeKeyAction()`
- L413 _protected prototype_ `virtual TUniquePtr<FChange> ExecuteInternal(IAnimationDataModel* Model, IAnimationDataController* Controller) override;`
- L414 _protected prototype_ `virtual FString ToStringInternal() const override;`
- L417 _protected member_ `FAnimationAttributeIdentifier AttributeId;`
- L418 _protected member_ `FAttributeKey Key;`

#### class `UE::Anim::FRemoveAtributeKeyAction`  
`class FRemoveAtributeKeyAction : public FAnimDataBaseAction`  
_L421-434_
- inherits: `FAnimDataBaseAction`
- L424 _public function_ `explicit FRemoveAtributeKeyAction(const FAnimationAttributeIdentifier& InAttributeId, float InTime) : AttributeId(InAttributeId), Time(InTime)`
- L425 _public prototype_ `virtual ~FRemoveAtributeKeyAction() = default;`
- L427 _protected function_ `FRemoveAtributeKeyAction()`
- L428 _protected prototype_ `virtual TUniquePtr<FChange> ExecuteInternal(IAnimationDataModel* Model, IAnimationDataController* Controller) override;`
- L429 _protected prototype_ `virtual FString ToStringInternal() const override;`
- L432 _protected member_ `FAnimationAttributeIdentifier AttributeId;`
- L433 _protected member_ `float Time;`

#### class `UE::Anim::FSetAtributeKeysAction`  
`class FSetAtributeKeysAction : public FAnimDataBaseAction`  
_L436-449_
- inherits: `FAnimDataBaseAction`
- L439 _public prototype_ `explicit FSetAtributeKeysAction(const FAnimatedBoneAttribute& InAttribute);`
- L440 _public prototype_ `virtual ~FSetAtributeKeysAction() = default;`
- L442 _protected function_ `FSetAtributeKeysAction()`
- L443 _protected prototype_ `virtual TUniquePtr<FChange> ExecuteInternal(IAnimationDataModel* Model, IAnimationDataController* Controller) override;`
- L444 _protected prototype_ `virtual FString ToStringInternal() const override;`
- L447 _protected member_ `FAnimationAttributeIdentifier AttributeId;`
- L448 _protected member_ `TArray<FAttributeKey> Keys;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API ANIMATIONDATACONTROLLER_API`
- L21 _namespace_ `namespace UE`
- L23 _namespace_ `namespace Anim` (scope `UE`)

### `Source/Developer/AnimationDataController/Public/IAnimationDataControllerModule.h` (Public)


#### class `IAnimationDataControllerModule`  
`class IAnimationDataControllerModule : public IModuleInterface`  
_L12-17_
- inherits: `IModuleInterface`
- L16 _public prototype_ `virtual TScriptInterface<IAnimationDataController> GetController(UObject* Outer = GetTransientPackage()) = 0;` — Returns UAnimationDataController instance, with optional outer, wrapped in a TScriptInterface of its implement IAnimationDataController interface
