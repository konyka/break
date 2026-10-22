# Plugins / AnimationData

- module root: `Plugins/Animation/AnimationData/Source/AnimationData`
- headers: 4; symbols: 210
- symbol kinds: class=4, function=20, macro=1, member=24, prototype=159, struct=2
- PrivateDependencyModuleNames: AnimGraph, AnimationBlueprintLibrary, AnimationCore, AnimationDataController, AnimationEditor, ControlRig, ControlRigDeveloper, CoreUObject, Engine, MovieScene, MovieSceneTracks, Sequencer, TimeManagement, UnrealEd
- PublicDependencyModuleNames: AnimGraphRuntime, Core, MovieSceneTools

### `Plugins/Animation/AnimationData/Source/AnimationData/Private/AnimSequencerController.h` (Private)


#### class `UAnimSequencerController`  
`class UAnimSequencerController : public UObject, public IAnimationDataController`  
_L14-142_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UObject,IAnimationDataController`
- L18 _public function_ `UAnimSequencerController() : BracketDepth(0)`
- L24 _public prototype_ `static void DeclareConstructClasses(TArray<FTopLevelAssetPath>& OutConstructClasses, const UClass* SpecificSubclass);`
- L29 _public prototype_ `virtual void SetModel(TScriptInterface<IAnimationDataModel> InModel) override;` — Begin IAnimationDataController overrides
- L30 _public function_ `virtual TScriptInterface<IAnimationDataModel> GetModelInterface() const override`
- L31 _public function_ `virtual const IAnimationDataModel* const GetModel() const override`
- L32 _public prototype_ `virtual void OpenBracket(const FText& InTitle, bool bShouldTransact = true) override;`
- L33 _public prototype_ `virtual void CloseBracket(bool bShouldTransact = true) override;`
- L34 _public prototype_ `virtual void SetNumberOfFrames(FFrameNumber Length, bool bShouldTransact = true) override;`
- L35 _public prototype_ `virtual void ResizeNumberOfFrames(FFrameNumber NewLength, FFrameNumber T0, FFrameNumber T1, bool bShouldTransact = true) override;`
- L36 _public prototype_ `virtual void ResizeInFrames(FFrameNumber Length, FFrameNumber T0, FFrameNumber T1, bool bShouldTransact = true) override;`
- L37 _public prototype_ `virtual void SetFrameRate(FFrameRate FrameRate, bool bShouldTransact = true) override;`
- L39 _public prototype_ `virtual void SetPlayLength(float Length, bool bShouldTransact = true) override;`
- L40 _public prototype_ `virtual void ResizePlayLength(float NewLength, float T0, float T1, bool bShouldTransact = true) override;`
- L41 _public prototype_ `virtual void Resize(float Length, float T0, float T1, bool bShouldTransact = true) override;`
- L43 _public prototype_ `virtual bool AddBoneCurve(FName BoneName, bool bShouldTransact = true) override;`
- L44 _public prototype_ `virtual int32 InsertBoneTrack(FName BoneName, int32 DesiredIndex, bool bShouldTransact = true) override;`
- L45 _public prototype_ `virtual bool RemoveBoneTrack(FName BoneName, bool bShouldTransact = true) override;`
- L46 _public prototype_ `virtual void RemoveAllBoneTracks(bool bShouldTransact = true) override;`
- L47 _public prototype_ `virtual bool SetBoneTrackKeys(FName BoneName, const TArray<FVector3f>& PositionalKeys, const TArray<FQuat4f>& RotationalKeys, const TArray<FVector3f>& ScalingKeys, bool bShouldTransact = true) override;`
- L48 _public prototype_ `virtual bool SetBoneTrackKeys(FName BoneName, const TArray<FVector>& PositionalKeys, const TArray<FQuat>& RotationalKeys, const TArray<FVector>& ScalingKeys, bool bShouldTransact = true) override;`
- L49 _public prototype_ `virtual bool UpdateBoneTrackKeys(FName BoneName, const FInt32Range& KeyRangeToSet, const TArray<FVector3f>& PositionalKeys, const TArray<FQuat4f>& RotationalKeys, const TArray<FVector3f>& ScalingKeys, bool bShouldTransact = true) override;`
- L50 _public prototype_ `virtual bool UpdateBoneTrackKeys(FName BoneName, const FInt32Range& KeyRangeToSet, const TArray<FVector>& PositionalKeys, const TArray<FQuat>& RotationalKeys, const TArray<FVector>& ScalingKeys, bool bShouldTransact = true) override;`
- L51 _public prototype_ `virtual bool AddCurve(const FAnimationCurveIdentifier& CurveId, int32 CurveFlags = 0x00000004, bool bShouldTransact = true) override;`
- L52 _public prototype_ `virtual bool DuplicateCurve(const FAnimationCurveIdentifier& CopyCurveId, const FAnimationCurveIdentifier& NewCurveId, bool bShouldTransact = true) override;`
- L53 _public prototype_ `virtual bool RemoveCurve(const FAnimationCurveIdentifier& CurveId, bool bShouldTransact = true) override;`
- L54 _public prototype_ `virtual void RemoveAllCurvesOfType(ERawCurveTrackTypes SupportedCurveType, bool bShouldTransact = true) override;`
- L55 _public prototype_ `virtual bool SetCurveFlag(const FAnimationCurveIdentifier& CurveId, EAnimAssetCurveFlags Flag, bool bState = true, bool bShouldTransact = true) override;`
- L56 _public prototype_ `virtual bool SetCurveFlags(const FAnimationCurveIdentifier& CurveId, int32 Flags, bool bShouldTransact = true) override;`
- L57 _public prototype_ `virtual bool SetTransformCurveKeys(const FAnimationCurveIdentifier& CurveId, const TArray<FTransform>& TransformValues, const TArray<float>& TimeKeys, bool bShouldTransact = true) override;`
- L58 _public prototype_ `virtual bool SetTransformCurveKey(const FAnimationCurveIdentifier& CurveId, float Time, const FTransform& Value, bool bShouldTransact = true) override;`
- L59 _public prototype_ `virtual bool RemoveTransformCurveKey(const FAnimationCurveIdentifier& CurveId, float Time, bool bShouldTransact = true) override;`
- L60 _public prototype_ `virtual bool RenameCurve(const FAnimationCurveIdentifier& CurveToRenameId, const FAnimationCurveIdentifier& NewCurveId, bool bShouldTransact = true) override;`
- L61 _public prototype_ `virtual bool SetCurveColor(const FAnimationCurveIdentifier& CurveId, FLinearColor Color, bool bShouldTransact = true) override;`
- L62 _public prototype_ `virtual bool SetCurveComment(const FAnimationCurveIdentifier& CurveId, const FString& Comment, bool bShouldTransact = true) override;`
- L63 _public prototype_ `virtual bool ScaleCurve(const FAnimationCurveIdentifier& CurveId, float Origin, float Factor, bool bShouldTransact = true) override;`
- L64 _public prototype_ `virtual bool SetCurveKey(const FAnimationCurveIdentifier& CurveId, const FRichCurveKey& Key, bool bShouldTransact = true) override;`
- L65 _public prototype_ `virtual bool RemoveCurveKey(const FAnimationCurveIdentifier& CurveId, float Time, bool bShouldTransact = true) override;`
- L66 _public prototype_ `virtual bool SetCurveKeys(const FAnimationCurveIdentifier& CurveId, const TArray<FRichCurveKey>& CurveKeys, bool bShouldTransact = true) override;`
- L67 _public prototype_ `virtual bool SetCurveAttributes(const FAnimationCurveIdentifier& CurveId, const FCurveAttributes& Attributes, bool bShouldTransact = true) override;`
- L68 _public prototype_ `virtual bool RemoveBoneTracksMissingFromSkeleton(const USkeleton* Skeleton, bool bShouldTransact = true) override;`
- L69 _public prototype_ `virtual void UpdateAttributesFromSkeleton(const USkeleton* Skeleton, bool bShouldTransact = true) override;`
- L70 _public prototype_ `virtual void NotifyPopulated() override;`
- L71 _public prototype_ `virtual void ResetModel(bool bShouldTransact = true) override;`
- L72 _public prototype_ `virtual bool AddAttribute(const FAnimationAttributeIdentifier& AttributeIdentifier, bool bShouldTransact = true) override;`
- L73 _public prototype_ `virtual bool RemoveAttribute(const FAnimationAttributeIdentifier& AttributeIdentifier, bool bShouldTransact = true) override;`
- L74 _public prototype_ `virtual int32 RemoveAllAttributesForBone(const FName& BoneName, bool bShouldTransact = true) override;`
- L75 _public prototype_ `virtual int32 RemoveAllAttributes(bool bShouldTransact = true) override;`
- L76 _public function_ `virtual bool SetAttributeKey(const FAnimationAttributeIdentifier& AttributeIdentifier, float Time, const void* KeyValue, const UScriptStruct* TypeStruct, bool bShouldTransact = true) override`
- L80 _public function_ `virtual bool SetAttributeKeys(const FAnimationAttributeIdentifier& AttributeIdentifier, TArrayView<const float> Times, TArrayView<const void*> KeyValues, const UScriptStruct* TypeStruct, bool bShouldTransact = true) override`
- L84 _public prototype_ `virtual bool RemoveAttributeKey(const FAnimationAttributeIdentifier& AttributeIdentifier, float Time, bool bShouldTransact = true) override;`
- L85 _public prototype_ `virtual bool DuplicateAttribute(const FAnimationAttributeIdentifier& AttributeIdentifier, const FAnimationAttributeIdentifier& NewAttributeIdentifier, bool bShouldTransact = true) override;`
- L86 _public prototype_ `virtual void UpdateWithSkeleton(USkeleton* TargetSkeleton, bool bShouldTransact = true) override;`
- L87 _public prototype_ `virtual void PopulateWithExistingModel(TScriptInterface<IAnimationDataModel> InModel) override;`
- L88 _public prototype_ `virtual void InitializeModel() override;`
- L90 _protected prototype_ `virtual void NotifyBracketOpen() override;`
- L91 _protected prototype_ `virtual void NotifyBracketClosed() override;`
- L95 _private prototype_ `bool SetAttributeKey_Internal(const FAnimationAttributeIdentifier& AttributeIdentifier, float Time, const void* KeyValue, const UScriptStruct* TypeStruct, bool bShouldTransact = true);` — Internal functionality for setting Attribute curve key(s)
- L96 _private prototype_ `bool SetAttributeKeys_Internal(const FAnimationAttributeIdentifier& AttributeIdentifier, TArrayView<const float> Times, TArrayView<const void*> KeyValues, const UScriptStruct* TypeStruct, bool bShouldTransact = true);`
- L98 _private prototype_ `void RemoveUnusedControlsAndCurves() const;`
- L101 _private prototype_ `void ResizeCurves(float NewLength, bool bInserted, float T0, float T1, bool bShouldTransact = true);` — Resizes the curve/attribute data stored on the model according to the provided new length and time at which to insert or remove time
- L102 _private prototype_ `void ResizeAttributes(float NewLength, bool bInserted, float T0, float T1, bool bShouldTransact = true);`
- L105 _private prototype_ `bool AddBoneControl(const FName& BoneName) const;` — Internal functionality which handles the Sequencer/ControlRig representation of Bone Animation data
- L106 _private prototype_ `bool RemoveBoneControl(const FName& BoneName) const;`
- L107 _private prototype_ `bool SetBoneCurveKeys(const FName& BoneName, const TArray<FVector3f>& PositionalKeys, const TArray<FQuat4f>& RotationalKeys, const TArray<FVector3f>& ScalingKeys) const;`
- L108 _private prototype_ `bool UpdateBoneCurveKeys(const FName& BoneName, const TArray<FTransform>& Keys, const TArray<float>& TimeValue) const;`
- L109 _private prototype_ `bool RemoveBoneCurveKey(const FName& BoneName, float Time);`
- L112 _private prototype_ `bool AddCurveControl(const FName& CurveName) const;` — Internal functionality which handles the Sequencer/ControlRig representation of Animation Curve data
- L113 _private prototype_ `bool RenameCurveControl(const FName& CurveName, const FName& NewCurveName) const;`
- L114 _private prototype_ `bool RemoveCurveControl(const FName& CurveName) const;`
- L115 _private prototype_ `bool SetCurveControlKeys(const FName& CurveName, const TArray<FRichCurveKey>& CurveKeys) const;`
- L116 _private prototype_ `bool SetCurveControlKey(const FName& CurveName, const FRichCurveKey& Key, bool bUpdateKey, float& OutKeyTiming) const;`
- L117 _private prototype_ `bool RemoveCurveControlKey(const FName& CurveName, float Time) const;`
- L118 _private prototype_ `bool DuplicateCurveControl(const FName& CurveName, const FName& DuplicateCurveName) const;`
- L120 _private prototype_ `void SetMovieSceneRange(FFrameNumber InFrameNumber) const;`
- L121 _private prototype_ `void EnsureModelIsInitialized() const;`
- L123 _private prototype_ `bool IgnoreSkeletonValidation() const;`
- L124 _private prototype_ `virtual bool ShouldTransact(bool bInLocalShouldTransact) const override;`
- L126 _private member_ `int32 BracketDepth;`
- L127 _private member_ `bool bShouldTransactBracket = false;`
- L131 _private member_ `TWeakObjectPtr<UAnimationSequencerDataModel> Model;` — `UPROPERTY(transient)` — UObject (typed) pointer to Model
- L134 _private member_ `TScriptInterface<IAnimationDataModel> ModelInterface;` — `UPROPERTY(transient)`

### `Plugins/Animation/AnimationData/Source/AnimationData/Private/AnimSequencerDataModel.h` (Private)


#### struct `FAnimationCurveMetaData`  
`struct FAnimationCurveMetaData`  
_L21-33_
- reflection: `USTRUCT()`
- L26 _public member_ `int32 Flags = 0;` — `UPROPERTY()`
- L29 _public member_ `FLinearColor Color = FLinearColor::White;` — `UPROPERTY()`
- L32 _public member_ `FString Comment;` — `UPROPERTY()`

#### class `UAnimationSequencerDataModel`  
`class UAnimationSequencerDataModel : public UMovieSceneSequence, public IAnimationDataModel`  
_L36-220_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneSequence,IAnimationDataModel`
- L41 _public member_ `static int32 RetainFloatCurves;`
- L42 _public member_ `static int32 ValidationMode;`
- L43 _public member_ `static int32 UseDirectFKControlRigMode;`
- L44 _public member_ `static int32 LazyRigHierarchyInitializationMode;`
- L47 _public prototype_ `virtual void GetPreloadDependencies(TArray<UObject*>& OutDeps) override;` — Begin UObject overrides
- L48 _public prototype_ `virtual void PostDuplicate(bool bDuplicateForPIE) override;`
- L49 _public prototype_ `virtual void PreSave(FObjectPreSaveContext ObjectSaveContext) override;`
- L50 _public function_ `virtual bool IsEditorOnly() const override`
- L52 _public prototype_ `virtual void WillNeverCacheCookedPlatformDataAgain() override;`
- L53 _public prototype_ `virtual void PreEditUndo() override;`
- L54 _public prototype_ `virtual void PostEditUndo() override;`
- L59 _public function_ `virtual void BindPossessableObject(const FGuid& ObjectId, UObject& PossessedObject, UObject* Context) override` — Begin UMovieSceneSequence overrides
- L60 _public function_ `virtual bool CanPossessObject(UObject& Object, UObject* InPlaybackContext) const override`
- L61 _public function_ `virtual void LocateBoundObjects(const FGuid& ObjectId, UObject* Context, TArray<UObject*, TInlineAllocator<1>>& OutObjects) const override`
- L62 _public prototype_ `virtual UMovieScene* GetMovieScene() const override;`
- L63 _public prototype_ `virtual UObject* GetParentObject(UObject* Object) const override;`
- L64 _public function_ `virtual void UnbindPossessableObjects(const FGuid& ObjectId) override`
- L65 _public function_ `virtual void UnbindObjects(const FGuid& ObjectId, const TArray<UObject*>& InObjects, UObject* Context) override`
- L66 _public function_ `virtual void UnbindInvalidObjects(const FGuid& ObjectId, UObject* Context) override`
- L67 _public prototype_ `virtual void PostLoad() override;`
- L69 _public prototype_ `static void DeclareConstructClasses(TArray<FTopLevelAssetPath>& OutConstructClasses, const UClass* SpecificSubclass);`
- L74 _public prototype_ `virtual double GetPlayLength() const override;` — Begin IAnimationDataModel overrides
- L75 _public prototype_ `virtual int32 GetNumberOfFrames() const override;`
- L76 _public prototype_ `virtual int32 GetNumberOfKeys() const override;`
- L77 _public prototype_ `virtual FFrameRate GetFrameRate() const override;`
- L79 _public prototype_ `virtual const TArray<FBoneAnimationTrack>& GetBoneAnimationTracks() const override;`
- L80 _public prototype_ `virtual const FBoneAnimationTrack& GetBoneTrackByIndex(int32 TrackIndex) const override;`
- L81 _public prototype_ `virtual const FBoneAnimationTrack& GetBoneTrackByName(FName TrackName) const override;`
- L82 _public prototype_ `virtual int32 GetBoneTrackIndex(const FBoneAnimationTrack& Track) const override;`
- L83 _public prototype_ `virtual int32 GetBoneTrackIndexByName(FName TrackName) const override;`
- L84 _public prototype_ `virtual bool IsValidBoneTrackIndex(int32 TrackIndex) const override;`
- L85 _public prototype_ `virtual int32 GetNumBoneTracks() const override;`
- L86 _public prototype_ `virtual void GetBoneTrackNames(TArray<FName>& OutNames) const override;`
- L87 _public prototype_ `virtual const FAnimCurveBase* FindCurve(const FAnimationCurveIdentifier& CurveIdentifier) const override;`
- L88 _public prototype_ `virtual const FFloatCurve* FindFloatCurve(const FAnimationCurveIdentifier& CurveIdentifier) const override;`
- L89 _public prototype_ `virtual const FTransformCurve* FindTransformCurve(const FAnimationCurveIdentifier& CurveIdentifier) const override;`
- L90 _public prototype_ `virtual const FRichCurve* FindRichCurve(const FAnimationCurveIdentifier& CurveIdentifier) const override;`
- L92 _public prototype_ `virtual bool IsValidBoneTrackName(const FName& TrackName) const override;`
- L93 _public prototype_ `virtual FTransform GetBoneTrackTransform(FName TrackName, const FFrameNumber& FrameNumber) const override;`
- L94 _public prototype_ `virtual void GetBoneTrackTransforms(FName TrackName, const TArray<FFrameNumber>& FrameNumbers, TArray<FTransform>& OutTransforms) const override;`
- L95 _public prototype_ `virtual void GetBoneTrackTransforms(FName TrackName, TArray<FTransform>& OutTransforms) const override;`
- L96 _public prototype_ `virtual void GetBoneTracksTransform(const TArray<FName>& TrackNames, const FFrameNumber& FrameNumber, TArray<FTransform>& OutTransforms) const override;`
- L97 _public prototype_ `virtual FTransform EvaluateBoneTrackTransform(FName TrackName, const FFrameTime& FrameTime, const EAnimInterpolationType& Interpolation) const override;`
- L98 _public prototype_ `virtual const FAnimationCurveData& GetCurveData() const override;`
- L99 _public prototype_ `virtual int32 GetNumberOfTransformCurves() const override;`
- L100 _public prototype_ `virtual int32 GetNumberOfFloatCurves() const override;`
- L101 _public prototype_ `virtual const TArray<struct FFloatCurve>& GetFloatCurves() const override;`
- L102 _public prototype_ `virtual const TArray<struct FTransformCurve>& GetTransformCurves() const override;`
- L103 _public prototype_ `virtual const FAnimCurveBase& GetCurve(const FAnimationCurveIdentifier& CurveIdentifier) const override;`
- L104 _public prototype_ `virtual const FFloatCurve& GetFloatCurve(const FAnimationCurveIdentifier& CurveIdentifier) const override;`
- L105 _public prototype_ `virtual const FTransformCurve& GetTransformCurve(const FAnimationCurveIdentifier& CurveIdentifier) const override;`
- L106 _public prototype_ `virtual const FRichCurve& GetRichCurve(const FAnimationCurveIdentifier& CurveIdentifier) const override;`
- L107 _public prototype_ `virtual TArrayView<const FAnimatedBoneAttribute> GetAttributes() const override;`
- L108 _public prototype_ `virtual int32 GetNumberOfAttributes() const override;`
- L109 _public prototype_ `virtual int32 GetNumberOfAttributesForBoneIndex(const int32 BoneIndex) const override;`
- L110 _public prototype_ `virtual void GetAttributesForBone(const FName& BoneName, TArray<const FAnimatedBoneAttribute*>& OutBoneAttributes) const override;`
- L111 _public prototype_ `virtual const FAnimatedBoneAttribute& GetAttribute(const FAnimationAttributeIdentifier& AttributeIdentifier) const override;`
- L112 _public prototype_ `virtual const FAnimatedBoneAttribute* FindAttribute(const FAnimationAttributeIdentifier& AttributeIdentifier) const override;`
- L113 _public prototype_ `virtual UAnimSequence* GetAnimationSequence() const override;`
- L114 _public function_ `virtual FAnimDataModelModifiedEvent& GetModifiedEvent() override`
- L115 _public prototype_ `virtual FGuid GenerateGuid(const FGuidGenerationSettings& InSettings) const override;`
- L117 _public prototype_ `virtual FString GenerateDebugStateString() const override;`
- L119 _public prototype_ `virtual TScriptInterface<IAnimationDataController> GetController() override;`
- L120 _public prototype_ `virtual IAnimationDataModel::FModelNotifier& GetNotifier() override;`
- L121 _public function_ `virtual FAnimDataModelModifiedDynamicEvent& GetModifiedDynamicEvent() override`
- L122 _public prototype_ `virtual void Evaluate(FAnimationPoseData& InOutPoseData, const UE::Anim::DataModel::FEvaluationContext& EvaluationContext) const override;`
- L123 _public function_ `virtual bool HasBeenPopulated() const override`
- L124 _public prototype_ `virtual void IterateBoneKeys(const FName& BoneName, TFunction<bool(const FVector3f& Pos, const FQuat4f&, const FVector3f, const FFrameNumber&)> IterationFunction) const override;`
- L126 _protected prototype_ `virtual void OnNotify(const EAnimDataModelNotifyType& NotifyType, const FAnimDataModelNotifPayload& Payload) override final;`
- L128 _protected function_ `virtual void LockEvaluationAndModification() const override final`
- L133 _protected function_ `virtual bool TryLockEvaluationAndModification() const override final`
- L138 _protected function_ `virtual void UnlockEvaluationAndModification() const override final`
- L143 _protected function_ `virtual bool& GetPopulationFlag() override final`
- L150 _protected prototype_ `FTransformCurve* FindMutableTransformCurveById(const FAnimationCurveIdentifier& CurveIdentifier);` — Controller helper functionality
- L151 _protected prototype_ `FFloatCurve* FindMutableFloatCurveById(const FAnimationCurveIdentifier& CurveIdentifier);`
- L152 _protected prototype_ `FAnimCurveBase* FindMutableCurveById(const FAnimationCurveIdentifier& CurveIdentifier);`
- L153 _protected prototype_ `FRichCurve* GetMutableRichCurve(const FAnimationCurveIdentifier& CurveIdentifier);`
- L155 _protected prototype_ `void RegenerateLegacyCurveData();`
- L156 _protected prototype_ `void UpdateLegacyCurveData();`
- L158 _protected prototype_ `void ValidateData() const;`
- L159 _protected prototype_ `void ValidateSequencerData() const;`
- L160 _protected prototype_ `void ValidateControlRigData() const;`
- L161 _protected prototype_ `void ValidateLegacyAgainstControlRigData() const;`
- L163 _protected prototype_ `void GeneratePoseData(UControlRig* ControlRig, FAnimationPoseData& InOutPoseData, const UE::Anim::DataModel::FEvaluationContext& EvaluationContext) const;`
- L164 _protected prototype_ `void EvaluateTrack(UMovieSceneControlRigParameterTrack* CR_Track, const UE::Anim::DataModel::FEvaluationContext& EvaluationContext) const;`
- L166 _protected prototype_ `UMovieSceneControlRigParameterTrack* GetControlRigTrack() const;`
- L167 _protected prototype_ `UMovieSceneControlRigParameterSection* GetFKControlRigSection() const;`
- L168 _protected prototype_ `URigHierarchy* GetControlRigHierarchy() const;`
- L169 _protected prototype_ `USkeleton* GetSkeleton() const;`
- L170 _protected prototype_ `void InitializeFKControlRig(UFKControlRig* FKControlRig, USkeleton* Skeleton, bool bForceHierarchyInitialization=false) const;`
- L171 _protected prototype_ `UControlRig* GetControlRig() const;`
- L173 _protected prototype_ `void IterateTransformControlCurve(const FName& BoneName, TFunction<void(const FTransform&, const FFrameNumber&)> IterationFunction, const TArray<FFrameNumber>* InFrameNumbers = nullptr) const;`
- L174 _protected prototype_ `void GenerateTransformKeysForControl(const FName& BoneName, TArray<FTransform>& InOutTransforms, TArray<FFrameNumber>& InOutFrameNumbers) const;`
- L175 _protected prototype_ `void RemoveOutOfDateControls() const;`
- L177 _protected prototype_ `void GenerateTransformKeysForControl(const FName& BoneName, const TArray<FFrameNumber>& FrameNumbers, TArray<FTransform>& InOutTransforms) const;`
- L178 _protected prototype_ `void ClearControlRigData();`
- L181 _private prototype_ `template <typename HasherType> void GenerateStateHash(HasherType& Hasher, const FGuidGenerationSettings& InSettings) const;`
- L183 _private prototype_ `void InitializeRigHierarchy(UFKControlRig* FKControlRig, const USkeleton* Skeleton) const;`
- L187 _private member_ `FAnimDataModelModifiedDynamicEvent ModifiedEventDynamic;` — `UPROPERTY(BlueprintAssignable, Transient, Category = AnimationDataModel, meta = (ScriptName = "ModifiedEvent", AllowPrivateAccess = "true"))` — Dynamic delegate event allows scripting to register to any broadcast-ed notify.
- L188 _private member_ `FAnimDataModelModifiedEvent ModifiedEvent;`
- L189 _private member_ `TUniquePtr<IAnimationDataModel::FModelNotifier> Notifier;`
- L190 _private member_ `UE::Anim::FAnimDataModelNotifyCollector Collector;`
- L193 _private member_ `FAnimationCurveData LegacyCurveData;` — `UPROPERTY(VisibleAnywhere, Category=AnimSequencer)`
- L196 _private member_ `TArray<FAnimatedBoneAttribute> AnimatedBoneAttributes;` — `UPROPERTY(VisibleAnywhere, Category=AnimSequencer)`
- L200 _private member_ `TObjectPtr<UMovieScene> MovieScene = nullptr;` — `UPROPERTY(VisibleAnywhere, Category=AnimSequencer)` — Movie scene instance containing FK Control rig and section representing the animation data
- L204 _private member_ `TMap<FAnimationCurveIdentifier, FAnimationCurveMetaData> CurveIdentifierToMetaData;` — `UPROPERTY(VisibleAnywhere, Category=AnimSequencer)` — Per-curve information holding flags/color, due to be deprecated in the future
- L207 _private member_ `bool bPopulated = false;` — `UPROPERTY(VisibleAnywhere, Category=AnimSequencer)`
- L211 _private member_ `FGuid CachedRawDataGUID;` — `UPROPERTY(VisibleAnywhere, Category=AnimSequencer)` — Raw data GUID taken from UAnimSequence when initially populating - this allows for retaining compressed data state initially
- L214 _private member_ `mutable bool bRigHierarchyInitialized = false;` — `UPROPERTY(VisibleAnywhere, Transient, Category=AnimSequencer)`
- L217 _private member_ `mutable FCriticalSection EvaluationLock;` — Scope lock to prevent contention around ControlRig->Evaluation()

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API ANIMATIONDATA_API`

### `Plugins/Animation/AnimationData/Source/AnimationData/Private/AnimSequencerHelpers.h` (Private)


#### struct `AnimSequencerHelpers`  
`struct AnimSequencerHelpers`  
_L15-27_
- L18 _public prototype_ `static void ConvertRichCurveKeyToFloatValue(const FRichCurveKey& RichCurveKey, FMovieSceneFloatValue& OutMovieSceneKey, double TangentRatio = 1.0, double SecondsPerFrame = 1.0);` — Converts an individual rich-curve key to its sequencer (moviescene channel) equivalent
- L20 _public prototype_ `static void ConvertFloatChannelToRichCurve(const FMovieSceneFloatChannel& Channel, FRichCurve& OutCurve, const FFrameRate& TargetFrameRate);` — Converts all keys from a FMovieSceneFloatChannel to its RichCurve equivalent, converting the source (moviescene) frame numbers to the target seconds-based representation
- L22 _public prototype_ `static void ConvertRichCurveKeysToFloatChannel(const TArray<FRichCurveKey>& CurveKeys, FMovieSceneFloatChannel& OutChannel);` — Converts all keys from a FRichCurveKey to its sequencer (moviescene equivalent), converting the source seconds-based time representation to (moviescene channel) frame numbers
- L24 _public prototype_ `static void GenerateUniqueFramesForTransformCurve(const FTransformParameterNameAndCurves& TransformParameter, TSet<FFrameNumber>& InOutFrames);` — Generates unique frame numbers found across all channels of a (moviescene) transform curve
- L26 _protected prototype_ `static void ConvertFloatValueToRichCurveKey(const FMovieSceneFloatValue& MovieSceneKey, FRichCurveKey& OutRichCurveKey, double TangentRatio = 1.0);`

### `Plugins/Animation/AnimationData/Source/AnimationData/Private/AnimationDataModule.h` (Private)


#### class `FSequencerBasedDataModel`  
`class FSequencerBasedDataModel : public UE::Anim::DataModel::IAnimationDataModels`  
_L12-25_
- inherits: `UE::Anim::DataModel::IAnimationDataModels`
- L14 _private function_ `virtual UClass* GetModelClass(UAnimSequenceBase* OwningAnimationAsset) const override`

#### class `FAnimationDataModule`  
`class FAnimationDataModule : public IModuleInterface`  
_L27-34_
- inherits: `IModuleInterface`
- L30 _public prototype_ `virtual void StartupModule() override;`
- L31 _public prototype_ `virtual void ShutdownModule() override;`
- L33 _protected member_ `FSequencerBasedDataModel SequencerBasedDataModelFeature;`
