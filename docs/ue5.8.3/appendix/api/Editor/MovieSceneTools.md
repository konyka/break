# Editor / MovieSceneTools

- module root: `Source/Editor/MovieSceneTools`
- headers: 169; symbols: 4021
- symbol kinds: class=201, delegate=18, enum=20, enumerator=83, function=478, macro=53, member=827, namespace=75, prototype=2136, struct=102, typedef=28
- DynamicallyLoadedModuleNames: AssetRegistry, AssetTools, MainFrame
- PrivateDependencyModuleNames: ActorPickerMode, AnimGraphRuntime, AnimationBlueprintLibrary, AnimationCore, AppFramework, BlueprintGraph, CinematicCamera, ClassViewer, ContentBrowser, CurveEditor, DataLayerEditor, DesktopPlatform, EditorFramework, EditorStyle, EditorSubsystem, GraphEditor, Json, JsonUtilities, Kismet, KismetCompiler, LiveLinkInterface, MaterialEditor, MessageLog, MovieScene, MovieSceneTracks, PropertyEditor, RHI, RenderCore, SceneOutliner, SequenceRecorder, SequencerCore, Slate, SlateCore, TimeManagement, ToolMenus, ToolWidgets, XmlParser
- PrivateIncludePathModuleNames: Analytics, AssetRegistry, AssetTools, MainFrame, Settings
- PublicDependencyModuleNames: Constraints, Core, CoreUObject, EditorWidgets, Engine, InputCore, LevelSequence, MovieSceneCapture, Sequencer, SequencerCore, UnrealEd

### `Source/Editor/MovieSceneTools/Private/Baker/AnimSequenceBaker.h` (Private)


#### class `UE::Sequencer::FAnimSequenceBakeRecorder`  
`class FAnimSequenceBakeRecorder : public ISequencerBakeRecorder, public TSharedFromThis<FAnimSequenceBakeRecorder>`  
_L22-91_
- inherits: `ISequencerBakeRecorder,TSharedFromThis<FAnimSequenceBakeRecorder>`
- L26 _public function_ `FAnimSequenceBakeRecorder() : WeakBaker(nullptr) , WeakComponent(nullptr) , WeakAnimSequence(nullptr)`
- L31 _public function_ `FAnimSequenceBakeRecorder(TSharedPtr<FSequencerBaker>& InBaker, FGuid InBindingID, UAnimSequence* InAnimSequencer, FLevelSequenceAnimSequenceLinkItem& InItem) : WeakBaker(InBaker) , BindingID(InBindingID) , WeakComponent(nullptr) , WeakAnimSequence(InAnimSequencer) , LinkItem(InItem)`
- L39 _public function_ `virtual ~FAnimSequenceBakeRecorder()`
- L42 _public prototype_ `virtual void BakeStarted(const UE::AIE::FBakeTimeRange& InRange) override;` — ISequencerBakeRecorder
- L43 _public prototype_ `virtual void BakeFrame(const UE::AIE::FBakeTimeIndex& InIndex) override;`
- L44 _public prototype_ `virtual void BakeCancelled() override;`
- L45 _public prototype_ `virtual void BakeFinished() override;`
- L46 _public prototype_ `virtual bool HasSequencerBinding(FGuid InGuid) override;`
- L47 _public prototype_ `virtual bool IsolateBakeResult(bool bIsolate) override;`
- L48 _public prototype_ `virtual void SetRecordingEnabled(bool bInEnabled) override;`
- L49 _public function_ `virtual bool GetRecordingEnabled() override`
- L53 _public prototype_ `virtual uint32 GetHash() override;`
- L54 _public prototype_ `virtual void ReadyToBake() override;`
- L55 _public prototype_ `virtual void RemovedFromBake() override;`
- L57 _public prototype_ `static TSharedPtr<ISequencerBakeRecorder> CreateRecorderAndAddToBaker(TSharedPtr<FSequencerBaker>& InBaker, FGuid InBindingID, UAnimSequence* InAnimSequence, FLevelSequenceAnimSequenceLinkItem& InItem);`
- L62 _private member_ `bool bRecordingEnabled = true;` — may want to turn it off
- L68 _private member_ `bool bProviderHandledBake = false;` — True when a linked-anim track provider performed the bake itself (e.g. the animation mixer composites root motion onto the root bone via its dedicated bake helper). When true the recorder skips its per-frame skeletal mesh sampling path so we don't overwrite the provider's output.
- L70 _private member_ `TWeakPtr<FSequencerBaker> WeakBaker;`
- L72 _private member_ `FGuid BindingID;` — id in sequencer of skelmeshcomp we are baking
- L73 _private member_ `TWeakObjectPtr<USkeletalMeshComponent> WeakComponent;`
- L74 _private member_ `TWeakObjectPtr<UAnimSequence> WeakAnimSequence;`
- L77 _private member_ `TSet<TWeakObjectPtr<UMovieSceneSignedObject>> Dependencies;` — list of tracks we are dependent upon
- L79 _private member_ `int32 StartIndex = INDEX_NONE;`
- L80 _private member_ `int32 EndIndex = INDEX_NONE;`
- L82 _private member_ `FLevelSequenceAnimSequenceLinkItem LinkItem;` — containts baking options
- L84 _private member_ `FAnimRecorderInstance AnimationRecorder;`
- L87 _private prototype_ `void InitRecorder(const UE::AIE::FBakeTimeRange& InRange);`
- L89 _private prototype_ `void AddDependencies(UMovieSceneTrack* InTrack, const TSharedPtr<ISequencer>& SequencerPtr);` — add dependencies recursively

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API MOVIESCENETOOLS_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Sequencer` (scope `UE`)

### `Source/Editor/MovieSceneTools/Private/Cache/MovieSceneCachedCurve.h` (Private)


#### enum `UE::MovieSceneTools::EMovieSceneCurveCacheChangeFlags`  
`enum class EMovieSceneCurveCacheChangeFlags : uint32`  
_L20-30_
- desc: Flags defining how the cache changed when it was last updated
- L22 _public enumerator_ `None = 0`
- L23 _public enumerator_ `ChangedPosition = 1 << 0`
- L24 _public enumerator_ `ChangedSize = 1 << 1`
- L25 _public enumerator_ `ChangedKeyIndices = 1 << 2`
- L26 _public enumerator_ `ChangedTangentVisibility = 1 << 3`
- L27 _public enumerator_ `ChangedSelection = 1 << 4`
- L28 _public enumerator_ `ChangedCurveData = 1 << 5`
- L29 _public enumerator_ `ChangedInterpolatingPoints = 1 << 6`

#### class `UE::MovieSceneTools::FMovieSceneCachedCurve`  
`template <typename ChannelType> class FMovieSceneCachedCurve : public IMovieSceneCachedCurve`  
_L35-230_
- inherits: `IMovieSceneCachedCurve`
- desc: Class holding cached curve data to speed up drawing the curve
- L40 _private typedef_ `using ChannelValueType = typename ChannelType::ChannelValueType;` — The type of channel value structs
- L43 _public prototype_ `FMovieSceneCachedCurve(const FCurveModelID& InCurveModelID);`
- L44 _public prototype_ `virtual ~FMovieSceneCachedCurve();`
- L47 _public prototype_ `void Initialize(TWeakPtr<const FCurveEditor> WeakCurveEditor);` — Initializes the cached curve
- L50 _public function_ `bool HasChanged() const` — Returns true when the curve changed
- L53 _public prototype_ `void UpdateCachedCurve(const FMovieSceneUpdateCachedCurveData<ChannelType>& UpdateData, const UE::CurveEditor::FCurveDrawParamsHandle& CurveDrawParamsHandle);` — Updates the cached curve data. Doesn't draw the curve
- L56 _public prototype_ `virtual void DrawCachedCurve() override;` — Draws the cached curve to the actual draw params
- L59 _public function_ `virtual const FCurveModelID& GetID() const override` — Returns the curve model ID that corresponds to the cached curve
- L62 _public function_ `const FCurveEditorScreenSpace& GetScreenSpace() const` — Returns the cached screen space
- L65 _public function_ `const FFrameRate& GetTickResolution() const` — Returns the cached tick resolution
- L68 _public function_ `int32 GetStartingIndex() const` — Cached first index of the visible space in keys / values
- L71 _public function_ `int32 GetEndingIndex() const` — Cached last index of the visible space in keys / values
- L74 _public function_ `TArray<const FFrameNumber> GetTimes() const` — Returns cached curve times
- L77 _public function_ `TArray<const ChannelValueType> GetValues() const` — Returns cached curve values
- L80 _public function_ `double GetTimeThreshold() const` — Returns the threshold of visible pixels per time
- L83 _public function_ `double GetValueThreshold() const` — Returns the threshold of visible pixels per value
- L86 _public function_ `const TSharedPtr<UE::MovieScene::FPiecewiseCurve>& GetPiecewiseCurve() const` — Returns the cached piecewise curve
- L89 _public prototype_ `virtual uint32 GetInterpolatingPointsHash() const override;` — IMovieSceneCachedCurve interface
- L90 _public prototype_ `virtual const UE::CurveEditor::FCurveDrawParamsHandle& GetDrawParamsHandle() const override;`
- L94 _public member_ `const FCurveModelID CurveModelID;` — The curve model ID that corresponds to the cached curve
- L98 _private prototype_ `void UpdateScreenSpace(const FCurveEditorScreenSpace& NewScreenSpace);` — Updates the cached screen space
- L101 _private prototype_ `void UpdateTickResolution(const FFrameRate& NewTickResolution);` — Updates the cached tick resolution
- L104 _private prototype_ `void UpdateInputDisplayOffset(const double NewInputDisplayOffset);` — Updates the cached input display offset
- L107 _private prototype_ `void UpdateSelection(const FMovieSceneUpdateCachedCurveData<ChannelType>& UpdateData);` — Updates the cached selection
- L110 _private prototype_ `void UpdateTangentVisibility(const ECurveEditorTangentVisibility NewTangentVisibility);` — Updates the tangent visiblity
- L113 _private prototype_ `void UpdateCurveData(const FMovieSceneUpdateCachedCurveData<ChannelType>& UpdateData, const FFrameNumber& StartFrame, const FFrameNumber& EndFrame);` — Updates cached curve data such as keys, values, key handles and key attributes
- L116 _private prototype_ `void UpdatePrePostInfinityExtrapolation(const FMovieSceneUpdateCachedCurveData<ChannelType>& UpdateData, const FFrameNumber& StartFrame, const FFrameNumber& EndFrame);` — Updates the cached pre and post inifinity extrapolation
- L119 _private prototype_ `void ConditionallyUpdateKeyDrawInfos(const FMovieSceneUpdateCachedCurveData<ChannelType>& UpdateData);` — Updates key draw info depending on flags
- L122 _private prototype_ `void ConditionallyUpdatePiecewiseCurve(const FMovieSceneUpdateCachedCurveData<ChannelType>& Data);` — Updates the piecewise cuve depending on flags
- L128 _private prototype_ `void ConditionallyPaintCurve(const ChannelType& Channel);` — When the curve is being edited interactively, paints the visible part synchronous. When curve data changed in any way, paints the whole range of the curve async.
- L131 _private prototype_ `void DrawInterpolatingPointsFromFullRange();` — Draws the interpolating points from the currently cached full range interpolating points
- L134 _private prototype_ `void DrawPreInfinityInterpolatingPoints();` — Draws the pre-infinity interpolating points
- L137 _private prototype_ `void DrawPostInfinityInterpolatingPoints();` — Draws the post-infinity interpolating points
- L140 _private prototype_ `[[nodiscard]] bool TryDrawPreInfinityExtentFast();` — Tries to draw a single pre-infinity interpolating point fast
- L143 _private prototype_ `[[nodiscard]] bool TryDrawPostInfinityExtentFast();` — Tries to draw a single post-infinity interpolating point fast
- L146 _private prototype_ `void DrawKeys();` — Draws the keys of the curve
- L149 _private prototype_ `void ApplyDrawParams();` — Applies the cached draw params to the actual draw params
- L152 _private member_ `FCurveEditorScreenSpace ScreenSpace;` — Cached screen space
- L155 _private member_ `FFrameRate TickResolution;` — Cached tick resolution
- L158 _private member_ `double InputDisplayOffset = TNumericLimits<double>::Max();` — Cached input display offset
- L161 _private member_ `int32 StartingIndex = INDEX_NONE;` — Cached first index of the visible space in keys / values
- L164 _private member_ `int32 EndingIndex = INDEX_NONE;` — Cached last index of the visible space in keys / values
- L167 _private member_ `FKeyHandleSet Selection;` — Cached selection
- L170 _private member_ `TOptional<ECurveEditorTangentVisibility> TangentVisibility;` — Cached tangent visibility. Optional soley to detect the initial change
- L173 _private member_ `double DefaultValue = 0.0;` — Cached default value
- L176 _private member_ `TArray<const FFrameNumber> Times;` — Cached curve times
- L179 _private member_ `TArray<const ChannelValueType> Values;` — Cached curve values
- L182 _private member_ `TArray<FKeyHandle> KeyHandles;` — Cached key handles
- L185 _private member_ `TArray<FKeyAttributes> KeyAttributes;` — Cached key attributes
- L188 _private member_ `TArray<TTuple<FKeyDrawInfo, TOptional<FKeyDrawInfo>, TOptional<FKeyDrawInfo>>> KeyDrawInfos;` — Key draw info as a tuple of the key, an optional arrive tangent and an optional leave tangent
- L191 _private member_ `TSharedPtr<UE::MovieScene::FPiecewiseCurve> PiecewiseCurve;` — The curve as piecewise curve.
- L214 _private member_ `FFullRangeinterpolatingPoints FullRangeInterpolation;` — The whole range of interpolating points. Useful to avoid drawing the visible range when curve and zoom don't change.
- L217 _private member_ `mutable FCriticalSection LockInterpolatingPoints;` — Critical section to enter when accessing the whole range or the cached draw params interpolating points
- L220 _private member_ `FCurveDrawParams CachedDrawParams;` — Cached curve draw params
- L223 _private member_ `bool bInvertInterpolatingPointsY = false;` — If true inverts interpolating points on the Y-axis, useful to draw LUF in UEFN
- L226 _private member_ `UE::CurveEditor::FCurveDrawParamsHandle DrawParamsHandle;` — Handle to the actual draw params we're drawing to
- L229 _private member_ `std::atomic<EMovieSceneCurveCacheChangeFlags> Flags = EMovieSceneCurveCacheChangeFlags::ChangedCurveData;` — Flags defining how the cache changed since it last was updated
- L233 _function_ `template <typename ChannelType> FMovieSceneCachedCurve<ChannelType>::FMovieSceneCachedCurve(const FCurveModelID& InCurveModelID) : CurveModelID(InCurveModelID) , ScreenSpace(FVector2D::ZeroVector, 0.0, 1.0, 0.0, 1.0) , CachedDrawParams(InCurveModelID)`
- L240 _function_ `template <typename ChannelType> FMovieSceneCachedCurve<ChannelType>::~FMovieSceneCachedCurve()`
- L246 _function_ `template <typename ChannelType> void FMovieSceneCachedCurve<ChannelType>::Initialize(TWeakPtr<const FCurveEditor> WeakCurveEditor)`
- L252 _function_ `template <typename ChannelType> void FMovieSceneCachedCurve<ChannelType>::UpdateCachedCurve(const FMovieSceneUpdateCachedCurveData<ChannelType>& UpdateData, const UE::CurveEditor::FCurveDrawParamsHandle& CurveDrawParamsHandle)`
- L281 _function_ `template <typename ChannelType> void FMovieSceneCachedCurve<ChannelType>::DrawCachedCurve()`
- L300 _function_ `template <typename ChannelType> uint32 FMovieSceneCachedCurve<ChannelType>::GetInterpolatingPointsHash() const`
- L306 _function_ `template <typename ChannelType> const UE::CurveEditor::FCurveDrawParamsHandle& FMovieSceneCachedCurve<ChannelType>::GetDrawParamsHandle() const`
- L313 _function_ `template <typename ChannelType> void FMovieSceneCachedCurve<ChannelType>::UpdateScreenSpace(const FCurveEditorScreenSpace& NewScreenSpace)`
- L337 _function_ `template <typename ChannelType> void FMovieSceneCachedCurve<ChannelType>::UpdateTickResolution(const FFrameRate& NewTickResolution)`
- L347 _function_ `template <typename ChannelType> void FMovieSceneCachedCurve<ChannelType>::UpdateInputDisplayOffset(const double NewInputDisplayOffset)`
- L357 _function_ `template <typename ChannelType> void FMovieSceneCachedCurve<ChannelType>::UpdateSelection(const FMovieSceneUpdateCachedCurveData<ChannelType>& UpdateData)`
- L373 _function_ `template <typename ChannelType> void FMovieSceneCachedCurve<ChannelType>::UpdateTangentVisibility(const ECurveEditorTangentVisibility NewTangentVisibility)`
- L384 _function_ `template <typename ChannelType> void FMovieSceneCachedCurve<ChannelType>::UpdateCurveData(const FMovieSceneUpdateCachedCurveData<ChannelType>& UpdateData, const FFrameNumber& StartFrame, const FFrameNumber& EndFrame)`
- L457 _function_ `template <typename ChannelType> void FMovieSceneCachedCurve<ChannelType>::UpdatePrePostInfinityExtrapolation(const FMovieSceneUpdateCachedCurveData<ChannelType>& UpdateData, const FFrameNumber& StartFrame, const FFrameNumber& EndFrame)`
- L473 _function_ `template <typename ChannelType> void FMovieSceneCachedCurve<ChannelType>::ConditionallyUpdateKeyDrawInfos(const FMovieSceneUpdateCachedCurveData<ChannelType>& UpdateData)`
- L534 _function_ `template <typename ChannelType> void FMovieSceneCachedCurve<ChannelType>::ConditionallyUpdatePiecewiseCurve(const FMovieSceneUpdateCachedCurveData<ChannelType>& Data)`
- L544 _function_ `template <typename ChannelType> void FMovieSceneCachedCurve<ChannelType>::ConditionallyPaintCurve(const ChannelType& Channel)`
- L642 _function_ `template <typename ChannelType> void FMovieSceneCachedCurve<ChannelType>::DrawInterpolatingPointsFromFullRange()`
- L714 _function_ `template <typename ChannelType> void FMovieSceneCachedCurve<ChannelType>::DrawPreInfinityInterpolatingPoints()`
- L793 _function_ `template <typename ChannelType> void FMovieSceneCachedCurve<ChannelType>::DrawPostInfinityInterpolatingPoints()`
- L873 _function_ `template <typename ChannelType> bool FMovieSceneCachedCurve<ChannelType>::TryDrawPreInfinityExtentFast()`
- L979 _function_ `template <typename ChannelType> bool FMovieSceneCachedCurve<ChannelType>::TryDrawPostInfinityExtentFast()`
- L1087 _function_ `template <typename ChannelType> void FMovieSceneCachedCurve<ChannelType>::DrawKeys()`
- L1201 _function_ `template <typename ChannelType> void FMovieSceneCachedCurve<ChannelType>::ApplyDrawParams()`

#### struct `UE::MovieSceneTools::FMovieSceneCachedCurve::FFullRangeinterpolatingPoints`  
`struct FFullRangeinterpolatingPoints`  
_L194-211_
- desc: Struct holding the whole range of interpolating points.
- L197 _public member_ `TArray<FVector2D> Points;` — The interpolating points in the finite curve range
- L200 _public member_ `TArray<int32> KeyOffsets;` — Offsets of keys in the points array
- L203 _public member_ `std::atomic<uint32> Hash = 0;` — Hash of the full range interpolating points
- L206 _public member_ `ERichCurveExtrapolation PreInfinityExtrapolation = ERichCurveExtrapolation::RCCE_None;` — How pre-infinity should be extrapolated
- L209 _public member_ `ERichCurveExtrapolation PostInfinityExtrapolation = ERichCurveExtrapolation::RCCE_None;` — How post-infinity should be extrapolated

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace MovieSceneTools` (scope `UE`)
- L31 _prototype_ `ENUM_CLASS_FLAGS(EMovieSceneCurveCacheChangeFlags);` (scope `UE::MovieSceneTools`)
- L436 _function_ `` (scope `UE::MovieSceneTools::FMovieSceneCachedCurve::UpdateCurveData`)
- L615 _function_ `` (scope `UE::MovieSceneTools::FMovieSceneCachedCurve::ConditionallyPaintCurve`)

### `Source/Editor/MovieSceneTools/Private/Cache/MovieSceneCurveCachePool.h` (Private)


#### class `UE::MovieSceneTools::IMovieSceneCachedCurve`  
`class IMovieSceneCachedCurve : public TSharedFromThis<IMovieSceneCachedCurve>`  
_L13-31_
- inherits: `TSharedFromThis<IMovieSceneCachedCurve>`
- desc: Interface for a cached curve in the curve cache pool
- L17 _public prototype_ `IMovieSceneCachedCurve() = default;`
- L18 _public prototype_ `virtual ~IMovieSceneCachedCurve() = default;`
- L21 _public prototype_ `virtual const FCurveModelID& GetID() const = 0;` — Returns the curve model ID that corresponds to this curve
- L24 _public prototype_ `virtual void DrawCachedCurve() = 0;` — Draws the cached curve
- L27 _public prototype_ `virtual uint32 GetInterpolatingPointsHash() const = 0;` — Returns a hash of the currently visible interpolated points
- L30 _public prototype_ `virtual const UE::CurveEditor::FCurveDrawParamsHandle& GetDrawParamsHandle() const = 0;` — Returns a handle to the actual draw params

#### enum `UE::MovieSceneTools::ECurvePainterTaskStateFlags`  
`enum class ECurvePainterTaskStateFlags : uint8`  
_L34-46_
- desc: States of a task in the pool
- L36 _public enumerator_ `None = 0`
- L39 _public enumerator_ `Interactive = 1 << 0` — The visible part was written immediately, synchronous
- L42 _public enumerator_ `Completed = 1 << 1` — The task successfully finished
- L45 _public enumerator_ `Void = 1 << 2` — The task is running but no longer useful

#### class `UE::MovieSceneTools::IMovieSceneInterpolatingPointsDrawTask`  
`class IMovieSceneInterpolatingPointsDrawTask : public TSharedFromThis<IMovieSceneInterpolatingPointsDrawTask>`  
_L50-64_
- inherits: `TSharedFromThis<IMovieSceneInterpolatingPointsDrawTask>`
- desc: Interface for tasks the curve cache pool can handle
- L54 _public prototype_ `virtual ~IMovieSceneInterpolatingPointsDrawTask() = default;`
- L57 _public prototype_ `virtual void SetFlags(ECurvePainterTaskStateFlags NewFlags) = 0;` — Sets flags for this task
- L60 _public prototype_ `virtual bool HasAnyFlags(ECurvePainterTaskStateFlags Flags) const = 0;` — Returns true if the task has the specified flag set
- L63 _public prototype_ `virtual void RefineFullRangeInterpolatingPoints() = 0;` — Refines the full range of the interpolating points

#### class `UE::MovieSceneTools::FMovieSceneCurveCachePool`  
`class FMovieSceneCurveCachePool : public UE::CurveEditor::ICurveEditorCurveCachePool , public TSharedFromThis<FMovieSceneCurveCachePool>`  
_L67-110_
- inherits: `UE::CurveEditor::ICurveEditorCurveCachePool,TSharedFromThis<FMovieSceneCurveCachePool>`
- desc: A pool of cached curves in a curve editor
- L72 _public prototype_ `virtual ~FMovieSceneCurveCachePool() = default;`
- L74 _public prototype_ `static FMovieSceneCurveCachePool& Get();`
- L77 _public prototype_ `virtual void DrawCachedCurves(TWeakPtr<const FCurveEditor> WeakCurveEditor) override;` — ICurveEditorCurveCachePool Interface
- L81 _public prototype_ `void Join(TWeakPtr<const FCurveEditor> WeakCurveEditor, const TSharedRef<IMovieSceneCachedCurve>& CachedCurve);` — Lets a cached curve join the cache pool. Curves that joined should also leave
- L84 _public prototype_ `void Leave(const IMovieSceneCachedCurve& CachedCurve);` — Lets a cached curve leave the cache pool
- L87 _public prototype_ `void AddTask(const TSharedRef<IMovieSceneCachedCurve>& CachedCurve, const TSharedRef<IMovieSceneInterpolatingPointsDrawTask>& Task);` — Adds a task to the curve cache pool
- L91 _private prototype_ `void DrawCachedCurves(const TArray<TWeakPtr<IMovieSceneCachedCurve>>& CachedCurves) const;` — Lets cached curves draw to their draw params
- L94 _private prototype_ `void CullCachedCurves(const TArray<TWeakPtr<IMovieSceneCachedCurve>>& CachedCurves) const;` — Culls cached curves
- L97 _private prototype_ `void OnEndFrame();` — Called on end frame. Updates work on tick
- L100 _private member_ `TMap<TWeakPtr<const FCurveEditor>, TArray<TWeakPtr<IMovieSceneCachedCurve>>> CurveEditorToCachedCurvesMap;` — Cached curves per curve editor
- L103 _private member_ `TMap<TWeakPtr<IMovieSceneCachedCurve>, TSharedPtr<IMovieSceneInterpolatingPointsDrawTask>> CachedCurveToTaskMap;` — A map of cached curves with their related tasks that need to be performed asynchronous
- L106 _private member_ `std::atomic<bool> bWorking = false;` — True while work is ongoing
- L109 _private member_ `FCriticalSection AccessTasksCritSec;` — Critical section to access tasks

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace CurveEditor` (scope `UE`)
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace MovieSceneTools` (scope `UE`)
- L47 _prototype_ `ENUM_CLASS_FLAGS(ECurvePainterTaskStateFlags);` (scope `UE::MovieSceneTools`)

### `Source/Editor/MovieSceneTools/Private/Cache/MovieSceneInterpolatingPointsDrawTask.h` (Private)


#### struct `UE::MovieSceneTools::FMovieSceneInterpolatingPointsDrawTask`  
`template <typename ChannelType> struct FMovieSceneInterpolatingPointsDrawTask : public IMovieSceneInterpolatingPointsDrawTask`  
_L23-81_
- inherits: `IMovieSceneInterpolatingPointsDrawTask`
- desc: A task to draw interpolating points. Draws interpolation for the visible space when interactive, but also the full range of the curve.
- L27 _public typedef_ `using ChannelValueType = typename ChannelType::ChannelValueType;` — The type of channel value structs
- L28 _public typedef_ `using CurveValueType = typename ChannelType::CurveValueType;`
- L31 _public prototype_ `FMovieSceneInterpolatingPointsDrawTask( const TSharedRef<FMovieSceneCachedCurve<ChannelType>>& InCachedCurve, const bool bInInvertInterpolatingPointsY, const TFunction<void(TArray<FVector2D> , TArray<int32> )>& InCallback);`
- L37 _public prototype_ `virtual void SetFlags(ECurvePainterTaskStateFlags NewFlags) override;`
- L38 _public prototype_ `virtual bool HasAnyFlags(ECurvePainterTaskStateFlags Flags) const override;`
- L39 _public prototype_ `virtual void RefineFullRangeInterpolatingPoints() override;`
- L44 _private prototype_ `void RefineFullRangeInterpolatingPointsInternal();` — Refines the full range of the interpolating points.
- L47 _private prototype_ `void InvokeCallback();` — Calls back to the cached curve, forwarding interpolated points
- L50 _private member_ `const TFunction<void(TArray<FVector2D> , TArray<int32> )> Callback;` — The callback to execute on completion
- L53 _private member_ `FCurveEditorScreenSpace ScreenSpace;` — The screenspace in which we paint
- L56 _private member_ `FFrameRate TickResolution;` — The current tick resolution
- L59 _private member_ `double TimeThreshold = 0.0;` — Threshold of visible times
- L62 _private member_ `double ValueThreshold = 0.0;` — Threshold of visible values
- L65 _private member_ `TSharedPtr<UE::MovieScene::FPiecewiseCurve> PiecewiseCurve;` — The curve as piecewise curve
- L68 _private member_ `const bool bInvertInterpolatingPointsY;` — If true, interpolating points should be painted inverted vertically, useful to show LUF in UEFN
- L71 _private member_ `TArray<FVector2D> KeyPoints;` — The initial points that are being interpolated
- L74 _private member_ `TArray<FVector2D> InterpolatingPoints;` — The (possibly not yet fully interpolated) interpolating points
- L77 _private member_ `FCriticalSection AccessCurvePointsMutex;` — Critical section to enter when accessing curve points
- L80 _private member_ `std::atomic<ECurvePainterTaskStateFlags> StateFlags = ECurvePainterTaskStateFlags::None;` — True if the task needs to iterate again

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace MovieScene` (scope `UE`)
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace MovieSceneTools` (scope `UE`)

### `Source/Editor/MovieSceneTools/Private/Cache/MovieSceneUpdateCachedCurveData.h` (Private)


#### struct `UE::MovieSceneTools::FMovieSceneUpdateCachedCurveData`  
`template <typename ChannelType> struct FMovieSceneUpdateCachedCurveData : public FNoncopyable`  
_L16-51_
- inherits: `FNoncopyable`
- desc: A struct that holds relevant parameters to cache a curve
- L21 _private typedef_ `using ChannelValueType = typename ChannelType::ChannelValueType;` — The type of channel value structs
- L24 _public function_ `FMovieSceneUpdateCachedCurveData( const FCurveEditor& InCurveEditor, const FCurveModel& InCurveModel, const ChannelType& InChannel, const FCurveEditorScreenSpace& InScreenSpace, const FFrameRate& InTickResolution, const bool bInInvertInterpolatingPointsY) : CurveEditor(InCurveEditor) , CurveModel(InCurveModel) , Channel(InChannel) , ScreenSpace(InScreenSpace) , TickResolution(InTickResolution) , Times(InChannel.GetTimes()) , Values(InChannel.GetValues()) , bInvertInterpolatingPointsY(bInInvertInterpolatingPointsY)`
- L41 _public member_ `const FCurveEditor& CurveEditor;`
- L42 _public member_ `const FCurveModel& CurveModel;`
- L43 _public member_ `const ChannelType& Channel;`
- L44 _public member_ `const FCurveEditorScreenSpace& ScreenSpace;`
- L45 _public member_ `const FFrameRate& TickResolution;`
- L47 _public member_ `const TArrayView<const FFrameNumber> Times;`
- L48 _public member_ `const TArrayView<const ChannelValueType> Values;`
- L50 _public member_ `const bool bInvertInterpolatingPointsY;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace MovieSceneTools` (scope `UE`)

### `Source/Editor/MovieSceneTools/Private/Channels/BoolChannelKeyProxy.h` (Private)


#### class `UBoolChannelKeyProxy`  
`class UBoolChannelKeyProxy : public UObject, public ICurveEditorKeyProxy, public IMovieSceneKeyProxy`  
_L21-57_
- reflection: `UCLASS()`
- inherits: `UObject,ICurveEditorKeyProxy,IMovieSceneKeyProxy`
- L29 _public prototype_ `void Initialize(FKeyHandle InKeyHandle, TMovieSceneChannelHandle<FMovieSceneBoolChannel> InChannelHandle, TWeakObjectPtr<UMovieSceneSection> InWeakSection);` — Initialize this key proxy object by caching the underlying key object, and retrieving the time/value each tick
- L34 _private prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;` — Apply this class's properties to the underlying key
- L37 _private prototype_ `virtual void UpdateValuesFromRawData() override;` — Update this class's properties from the underlying key
- L43 _private member_ `FFrameNumber Time;` — `UPROPERTY(EditAnywhere, Category="Key")` — User-facing time of the key, applied to the actual key on PostEditChange, and updated every tick
- L47 _private member_ `bool bValue;` — `UPROPERTY(EditAnywhere, Category="Key", meta=(ShowOnlyInnerProperties))` — User-facing value of the key, applied to the actual key on PostEditChange, and updated every tick
- L52 _private member_ `FKeyHandle KeyHandle;` — Cached key handle that this key proxy relates to
- L54 _private member_ `TMovieSceneChannelHandle<FMovieSceneBoolChannel> ChannelHandle;` — Cached channel in which the key resides
- L56 _private member_ `TWeakObjectPtr<UMovieSceneSection> WeakSection;` — Cached section in which the channel resides

### `Source/Editor/MovieSceneTools/Private/Channels/ByteChannelKeyProxy.h` (Private)


#### class `UByteChannelKeyProxy`  
`class UByteChannelKeyProxy : public UObject, public ICurveEditorKeyProxy, public IMovieSceneKeyProxy`  
_L22-58_
- reflection: `UCLASS()`
- inherits: `UObject,ICurveEditorKeyProxy,IMovieSceneKeyProxy`
- L30 _public prototype_ `void Initialize(FKeyHandle InKeyHandle, TMovieSceneChannelHandle<FMovieSceneByteChannel> InChannelHandle, TWeakObjectPtr<UMovieSceneSection> InWeakSection);` — Initialize this key proxy object by caching the underlying key object, and retrieving the time/value each tick
- L35 _private prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;` — Apply this class's properties to the underlying key
- L38 _private prototype_ `virtual void UpdateValuesFromRawData() override;` — Update this class's properties from the underlying key
- L44 _private member_ `FFrameNumber Time;` — `UPROPERTY(EditAnywhere, Category="Key")` — User-facing time of the key, applied to the actual key on PostEditChange, and updated every tick
- L48 _private member_ `uint8 Value;` — `UPROPERTY(EditAnywhere, Category="Key", meta=(ShowOnlyInnerProperties))` — User-facing value of the key, applied to the actual key on PostEditChange, and updated every tick
- L53 _private member_ `FKeyHandle KeyHandle;` — Cached key handle that this key proxy relates to
- L55 _private member_ `TMovieSceneChannelHandle<FMovieSceneByteChannel> ChannelHandle;` — Cached channel in which the key resides
- L57 _private member_ `TWeakObjectPtr<UMovieSceneSection> WeakSection;` — Cached section in which the channel resides

### `Source/Editor/MovieSceneTools/Private/Channels/ConstraintChannelEditor.h` (Private)


#### struct `FConstraintChannelEditor`  
`struct FConstraintChannelEditor`  
_L27-30_
- desc: Should concillidate this with the FCosntraintChannelHelper once that moves out of the control rig module
- L29 _public prototype_ `static TArray<FKeyBarCurveModel::FBarRange> GetBarRanges(FMovieSceneConstraintChannel* Channel, const UMovieSceneSection* Owner);`

#### Free symbols / members of external scopes

- L33 _prototype_ `void DrawKeys( FMovieSceneConstraintChannel* Channel, TArrayView<const FKeyHandle> InKeyHandles, const UMovieSceneSection* InOwner, TArrayView<FKeyDrawParams> OutKeyDrawParams);` — Key drawing overrides
- L39 _prototype_ `int32 DrawExtra( FMovieSceneConstraintChannel* Channel, const UMovieSceneSection* Owner, const FSequencerChannelPaintArgs& PaintArgs, int32 LayerId);`
- L46 _prototype_ `FKeyHandle AddOrUpdateKey( FMovieSceneConstraintChannel* Channel, UMovieSceneSection* SectionToKey, FFrameNumber Time, ISequencer& Sequencer, const FGuid& ObjectBindingID, FTrackInstancePropertyBindings* PropertyBindings);` — Overrides for adding or updating a key for non-standard channels
- L54 _prototype_ `FKeyHandle AddOrUpdateKey( FMovieSceneConstraintChannel* Channel, UMovieSceneSection* SectionToKey, const TMovieSceneExternalValue<bool>& EditorData, FFrameNumber InTime, ISequencer& Sequencer, const FGuid& InObjectBindingID, FTrackInstancePropertyBindings* PropertyBindings);`
- L64 _prototype_ `bool CanCreateKeyEditor(const FMovieSceneConstraintChannel* InChannel);` — Key editor overrides
- L66 _prototype_ `TSharedRef<SWidget> CreateKeyEditor( const TMovieSceneChannelHandle<FMovieSceneConstraintChannel>& InChannel, const UE::Sequencer::FCreateKeyEditorParams& Params);`
- L71 _function_ `inline bool SupportsCurveEditorModels(const TMovieSceneChannelHandle<FMovieSceneConstraintChannel>& Channel)` — Curve editor models
- L72 _prototype_ `TUniquePtr<FCurveModel> CreateCurveEditorModel(const TMovieSceneChannelHandle<FMovieSceneConstraintChannel>& Channel, const UE::Sequencer::FCreateCurveEditorModelParams& Params);`

### `Source/Editor/MovieSceneTools/Private/Channels/CurveModelHelpers.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace MovieSceneTools` (scope `UE`)
- L8 _namespace_ `namespace CurveHelpers` (scope `UE::MovieSceneTools`)
- L11 _member_ `template <typename T> concept CCurveValueTypeable = requires { typename T::CurveValueType; };` (scope `UE::MovieSceneTools::CurveHelpers::T`)
- L15 _function_ `template <CCurveValueTypeable ChannelType> bool Evaluate( double InTime, double& OutValue, const ChannelType& Channel, const TWeakObjectPtr<UMovieSceneSection> WeakSection )` (scope `UE::MovieSceneTools::CurveHelpers`) — Shared implementation for evaluating a ChannelType. Useful helper for evaluating IBufferedCurveModel.
- L23 _typedef_ `using KeyType = typename ChannelType::CurveValueType;` (scope `UE::MovieSceneTools::CurveHelpers::Evaluate`)

### `Source/Editor/MovieSceneTools/Private/Channels/DoubleChannelKeyProxy.h` (Private)


#### class `UDoubleChannelKeyProxy`  
`class UDoubleChannelKeyProxy : public UObject, public ICurveEditorKeyProxy, public IMovieSceneKeyProxy`  
_L21-57_
- reflection: `UCLASS()`
- inherits: `UObject,ICurveEditorKeyProxy,IMovieSceneKeyProxy`
- L29 _public prototype_ `void Initialize(FKeyHandle InKeyHandle, TMovieSceneChannelHandle<FMovieSceneDoubleChannel> InChannelHandle, TWeakObjectPtr<UMovieSceneSignedObject> InWeakSignedObject);` — Initialize this key proxy object by caching the underlying key object, and retrieving the time/value each tick
- L34 _private prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;` — Apply this class's properties to the underlying key
- L37 _private prototype_ `virtual void UpdateValuesFromRawData() override;` — Update this class's properties from the underlying key
- L43 _private member_ `FFrameNumber Time;` — `UPROPERTY(EditAnywhere, Category="Key")` — User-facing time of the key, applied to the actual key on PostEditChange, and updated every tick
- L47 _private member_ `FMovieSceneDoubleValue Value;` — `UPROPERTY(EditAnywhere, Category="Key", meta=(ShowOnlyInnerProperties))` — User-facing value of the key, applied to the actual key on PostEditChange, and updated every tick
- L52 _private member_ `FKeyHandle KeyHandle;` — Cached key handle that this key proxy relates to
- L54 _private member_ `TMovieSceneChannelHandle<FMovieSceneDoubleChannel> ChannelHandle;` — Cached channel in which the key resides
- L56 _private member_ `TWeakObjectPtr<UMovieSceneSignedObject> WeakSignedObject;` — Cached signed object in which the channel resides

### `Source/Editor/MovieSceneTools/Private/Channels/EventChannelCurveModel.h` (Private)


#### class `FEventChannelCurveModel`  
`class FEventChannelCurveModel : public FCurveModel`  
_L30-68_
- inherits: `FCurveModel`
- L33 _public member_ `static ECurveEditorViewID EventView;`
- L35 _public prototype_ `FEventChannelCurveModel(TMovieSceneChannelHandle<FMovieSceneEventChannel> InChannel, UMovieSceneSection* InOwningSection, TWeakPtr<ISequencer> InWeakSequencer);`
- L37 _public prototype_ `virtual const void* GetCurve() const override;`
- L39 _public prototype_ `virtual void Modify() override;`
- L41 _public prototype_ `virtual void DrawCurve(const FCurveEditor& CurveEditor, const FCurveEditorScreenSpace& ScreenSpace, TArray<TTuple<double, double>>& InterpolatingPoints) const override;`
- L42 _public prototype_ `virtual void GetKeys(double MinTime, double MaxTime, double MinValue, double MaxValue, TArray<FKeyHandle>& OutKeyHandles) const override;`
- L43 _public prototype_ `virtual void GetKeyDrawInfo(ECurvePointType PointType, const FKeyHandle InKeyHandle, FKeyDrawInfo& OutDrawInfo) const override;`
- L45 _public prototype_ `virtual void GetKeyPositions(TArrayView<const FKeyHandle> InKeys, TArrayView<FKeyPosition> OutKeyPositions) const override;`
- L46 _public prototype_ `virtual void SetKeyPositions(TArrayView<const FKeyHandle> InKeys, TArrayView<const FKeyPosition> InKeyPositions, EPropertyChangeType::Type ChangeType) override;`
- L48 _public prototype_ `virtual void GetKeyAttributes(TArrayView<const FKeyHandle> InKeys, TArrayView<FKeyAttributes> OutAttributes) const override;`
- L49 _public prototype_ `virtual void SetKeyAttributes(TArrayView<const FKeyHandle> InKeys, TArrayView<const FKeyAttributes> InAttributes, EPropertyChangeType::Type ChangeType = EPropertyChangeType::Unspecified) override;`
- L51 _public prototype_ `virtual void GetCurveAttributes(FCurveAttributes& OutCurveAttributes) const override;`
- L52 _public prototype_ `virtual void SetCurveAttributes(const FCurveAttributes& InCurveAttributes) override;`
- L53 _public prototype_ `virtual void GetTimeRange(double& MinTime, double& MaxTime) const override;`
- L54 _public prototype_ `virtual void GetValueRange(double& MinValue, double& MaxValue) const override;`
- L55 _public prototype_ `virtual int32 GetNumKeys() const override;`
- L56 _public function_ `virtual void GetNeighboringKeys(const FKeyHandle InKeyHandle, TOptional<FKeyHandle>& OutPreviousKeyHandle, TOptional<FKeyHandle>& OutNextKeyHandle) const override`
- L57 _public prototype_ `virtual bool Evaluate(double ProspectiveTime, double& OutValue) const override;`
- L58 _public prototype_ `virtual void AddKeys(TArrayView<const FKeyPosition> InKeyPositions, TArrayView<const FKeyAttributes> InAttributes, TArrayView<TOptional<FKeyHandle>>* OutKeyHandles) override;`
- L59 _public prototype_ `virtual void RemoveKeys(TArrayView<const FKeyHandle> InKeys, double InCurrentTime) override;`
- L61 _public prototype_ `virtual void CreateKeyProxies(TWeakPtr<FCurveEditor> InWeakCurveEditor, FCurveModelID InCurveModelID, TArrayView<const FKeyHandle> InKeyHandles, TArrayView<UObject*> OutObjects) override;`
- L65 _private member_ `TMovieSceneChannelHandle<FMovieSceneEventChannel> ChannelHandle;`
- L66 _private member_ `TWeakObjectPtr<UMovieSceneSection> WeakSection;`
- L67 _private member_ `TWeakPtr<ISequencer> WeakSequencer;`

### `Source/Editor/MovieSceneTools/Private/Channels/FloatChannelKeyProxy.h` (Private)


#### class `UFloatChannelKeyProxy`  
`class UFloatChannelKeyProxy : public UObject, public ICurveEditorKeyProxy, public IMovieSceneKeyProxy`  
_L21-57_
- reflection: `UCLASS()`
- inherits: `UObject,ICurveEditorKeyProxy,IMovieSceneKeyProxy`
- L29 _public prototype_ `void Initialize(FKeyHandle InKeyHandle, TMovieSceneChannelHandle<FMovieSceneFloatChannel> InChannelHandle, TWeakObjectPtr<UMovieSceneSection> InWeakSection);` — Initialize this key proxy object by caching the underlying key object, and retrieving the time/value each tick
- L34 _private prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;` — Apply this class's properties to the underlying key
- L37 _private prototype_ `virtual void UpdateValuesFromRawData() override;` — Update this class's properties from the underlying key
- L43 _private member_ `FFrameNumber Time;` — `UPROPERTY(EditAnywhere, Category="Key")` — User-facing time of the key, applied to the actual key on PostEditChange, and updated every tick
- L47 _private member_ `FMovieSceneFloatValue Value;` — `UPROPERTY(EditAnywhere, Category="Key", meta=(ShowOnlyInnerProperties))` — User-facing value of the key, applied to the actual key on PostEditChange, and updated every tick
- L52 _private member_ `FKeyHandle KeyHandle;` — Cached key handle that this key proxy relates to
- L54 _private member_ `TMovieSceneChannelHandle<FMovieSceneFloatChannel> ChannelHandle;` — Cached channel in which the key resides
- L56 _private member_ `TWeakObjectPtr<UMovieSceneSection> WeakSection;` — Cached section in which the channel resides

### `Source/Editor/MovieSceneTools/Private/Channels/IntegerChannelKeyProxy.h` (Private)


#### class `UIntegerChannelKeyProxy`  
`class UIntegerChannelKeyProxy : public UObject, public ICurveEditorKeyProxy, public IMovieSceneKeyProxy`  
_L22-58_
- reflection: `UCLASS()`
- inherits: `UObject,ICurveEditorKeyProxy,IMovieSceneKeyProxy`
- L30 _public prototype_ `void Initialize(FKeyHandle InKeyHandle, TMovieSceneChannelHandle<FMovieSceneIntegerChannel> InChannelHandle, TWeakObjectPtr<UMovieSceneSection> InWeakSection);` — Initialize this key proxy object by caching the underlying key object, and retrieving the time/value each tick
- L35 _private prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;` — Apply this class's properties to the underlying key
- L38 _private prototype_ `virtual void UpdateValuesFromRawData() override;` — Update this class's properties from the underlying key
- L44 _private member_ `FFrameNumber Time;` — `UPROPERTY(EditAnywhere, Category="Key")` — User-facing time of the key, applied to the actual key on PostEditChange, and updated every tick
- L48 _private member_ `int32 Value;` — `UPROPERTY(EditAnywhere, Category="Key", meta=(ShowOnlyInnerProperties))` — User-facing value of the key, applied to the actual key on PostEditChange, and updated every tick
- L53 _private member_ `FKeyHandle KeyHandle;` — Cached key handle that this key proxy relates to
- L55 _private member_ `TMovieSceneChannelHandle<FMovieSceneIntegerChannel> ChannelHandle;` — Cached channel in which the key resides
- L57 _private member_ `TWeakObjectPtr<UMovieSceneSection> WeakSection;` — Cached section in which the channel resides

### `Source/Editor/MovieSceneTools/Private/Channels/InvertedBezierChannelCurveModel.h` (Private)


#### class `UE::MovieSceneTools::TInvertedBezierChannelCurveModel`  
`template <typename TBase> class TInvertedBezierChannelCurveModel : public UE::CurveEditor::TInvertedCurveModel<TBase>`  
_L18-59_
- inherits: `UE::CurveEditor::TInvertedCurveModel<TBase>`
- L23 _public function_ `template <typename... TArg> explicit TInvertedBezierChannelCurveModel(TArg&&... Arg) : UE::CurveEditor::TInvertedCurveModel<TBase>(Forward<TArg>(Arg)...)`
- L27 _public function_ `virtual UE::CurveEditor::ICurveEditorCurveCachePool* DrawCurveToCachePool(const TSharedRef<FCurveEditor>& CurveEditor, const UE::CurveEditor::FCurveDrawParamsHandle& CurveDrawParamsHandle, const FCurveEditorScreenSpace& ScreenSpace) override`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace MovieSceneTools` (scope `UE`)
- L29 _typedef_ `using ChannelType = std::remove_pointer_t<decltype(this->GetChannelHandle().Get())>;` (scope `UE::MovieSceneTools::TInvertedBezierChannelCurveModel::DrawCurveToCachePool`)

### `Source/Editor/MovieSceneTools/Private/Conditions/MovieSceneDirectorBlueprintConditionExtension.h` (Private)


#### class `UMovieSceneDirectorBlueprintConditionExtension`  
`class UMovieSceneDirectorBlueprintConditionExtension : public UBlueprintExtension`  
_L23-49_
- reflection: `UCLASS()`
- inherits: `UBlueprintExtension`
- desc: An extension for a sequence's director blueprint to compile director blueprint condition endpoints.
- L33 _public prototype_ `void BindTo(TWeakObjectPtr<UMovieSceneSequence> InMovieSceneSequence);` — Bind this extension to the given sequence. This may be called multiple times, but the extension must only be bound to one sequence.
- L37 _private prototype_ `virtual void PostLoad() override;`
- L39 _private prototype_ `virtual void HandlePreloadObjectsForCompilation(UBlueprint* OwningBlueprint) override final;`
- L40 _private prototype_ `virtual void HandleGenerateFunctionGraphs(FKismetCompilerContext* CompilerContext) override final;`
- L42 _private prototype_ `void HandleGenerateFunctionGraphs(FKismetCompilerContext* CompilerContext, UMovieSceneSequence* MovieSceneSequence);`
- L48 _private member_ `TArray<TWeakObjectPtr<UMovieSceneSequence>> WeakMovieSceneSequences;` — `UPROPERTY()` — List of movie scenes that are bound to the director blueprint

### `Source/Editor/MovieSceneTools/Private/Constraints/ComponentConstraintChannelInterface.h` (Private)


#### struct `FComponentConstraintChannelInterface`  
`struct FComponentConstraintChannelInterface : ITransformConstraintChannelInterface`  
_L15-49_
- inherits: `ITransformConstraintChannelInterface`
- L17 _public prototype_ `virtual ~FComponentConstraintChannelInterface() = default;`
- L20 _public prototype_ `virtual UMovieSceneSection* GetHandleSection(const UTransformableHandle* InHandle, const TSharedPtr<ISequencer>& InSequencer) override;` — Get the UMovieScene3DTransformSection from the component.
- L21 _public prototype_ `virtual UMovieSceneSection* GetHandleConstraintSection(const UTransformableHandle* InHandle, const TSharedPtr<ISequencer>& InSequencer) override;`
- L24 _public prototype_ `virtual UWorld* GetHandleWorld(UTransformableHandle* InHandle) override;` — Get the world from the component.
- L27 _public prototype_ `virtual bool SmartConstraintKey( UTickableTransformConstraint* InConstraint, const TOptional<bool>& InOptActive, const TRange<FFrameNumber>& InTimeRange, const TSharedPtr<ISequencer>& InSequencer) override;` — Add an active/inactive key to the constraint channel if needed and does the transform compensation on the component's transform channels.
- L32 _public prototype_ `virtual void AddHandleTransformKeys( const TSharedPtr<ISequencer>& InSequencer, const UTransformableHandle* InHandle, const TArray<FFrameNumber>& InFrames, const TArray<FTransform>& InLocalTransforms, const EMovieSceneTransformChannel& InChannels) override;` — Add keys on the component's transform channels.
- L40 _protected prototype_ `virtual void UnregisterTrack(UMovieSceneTrack* InTrack, UWorld* InWorld) override;`
- L43 _private prototype_ `static UMovieScene3DTransformSection* GetComponentSection(const UTransformableComponentHandle* InHandle, const TSharedPtr<ISequencer>& InSequencer, const bool bInConstraint);`
- L45 _private prototype_ `void RecomposeTransforms( const TSharedPtr<ISequencer>& InSequencer, USceneComponent* SceneComponent, UMovieSceneSection* Section, const TArray<FFrameNumber>& InFrames, TArray<FTransform>& InOutTransforms) const;`

### `Source/Editor/MovieSceneTools/Private/CurveKeyEditors/SBoolCurveKeyEditor.h` (Private)


#### class `SBoolCurveKeyEditor`  
`class SBoolCurveKeyEditor : public SCompoundWidget`  
_L16-30_
- inherits: `SCompoundWidget`
- desc: A widget for editing a curve representing bool keys.
- L19 _public function_ `SLATE_BEGIN_ARGS(SBoolCurveKeyEditor)`
- L20 _public prototype_ `SLATE_END_ARGS();`
- L22 _public prototype_ `void Construct(const FArguments& InArgs, const TSequencerKeyEditor<FMovieSceneBoolChannel, bool>& InKeyEditor);`
- L26 _private prototype_ `ECheckBoxState IsChecked() const;`
- L27 _private prototype_ `void OnCheckStateChanged(ECheckBoxState);`
- L29 _private member_ `TSequencerKeyEditor<FMovieSceneBoolChannel, bool> KeyEditor;`

### `Source/Editor/MovieSceneTools/Private/CurveKeyEditors/SEnumKeyEditor.h` (Private)


#### class `SEnumCurveKeyEditor`  
`class SEnumCurveKeyEditor : public SCompoundWidget`  
_L10-24_
- inherits: `SCompoundWidget`
- L13 _public function_ `SLATE_BEGIN_ARGS(SEnumCurveKeyEditor)`
- L14 _public prototype_ `SLATE_END_ARGS();`
- L16 _public prototype_ `void Construct(const FArguments& InArgs, const TSequencerKeyEditor<FMovieSceneByteChannel, uint8>& InKeyEditor, UEnum* Enum);`
- L20 _private function_ `int32 OnGetCurrentValueAsInt() const`
- L21 _private prototype_ `void OnChangeKey(int32 Selection, ESelectInfo::Type SelectionType);`
- L23 _private member_ `TSequencerKeyEditor<FMovieSceneByteChannel, uint8> KeyEditor;`

### `Source/Editor/MovieSceneTools/Private/CurveKeyEditors/SNumericKeyEditor.h` (Private)


#### struct `SNonThrottledSpinBox`  
`template<typename T> struct SNonThrottledSpinBox : SSpinBox<T>`  
_L18-44_
- inherits: `SSpinBox<T>`
- L20 _public function_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override`
- L30 _public function_ `virtual FReply OnFocusReceived(const FGeometry& MyGeometry, const FFocusEvent& InFocusEvent) override`
- L36 _public function_ `void SetKeyEditor(TSharedPtr<ISequencerKeyEditor<T>> InKeyEditor)`
- L43 _private member_ `TSharedPtr<ISequencerKeyEditor<T>> KeyEditor;`

#### class `SNumericKeyEditorWidget`  
`template<typename NumericType> class SNumericKeyEditorWidget : public SCompoundWidget`  
_L50-179_
- inherits: `SCompoundWidget`
- desc: A widget for editing a curve representing integer keys.
- L53 _public function_ `SLATE_BEGIN_ARGS(SNumericKeyEditorWidget)`
- L54 _public function_ `SLATE_END_ARGS() template<typename ChannelType> void Construct(const FArguments& InArgs, const TSequencerKeyEditor<ChannelType, NumericType>& InKeyEditor)`
- L65 _public function_ `void Construct(const FArguments& InArgs, const TSharedRef<ISequencerKeyEditor<NumericType>>& InKeyEditor)`
- L121 _private function_ `virtual FSlateColor GetForegroundColor() const override`
- L133 _private function_ `void OnBeginSliderMovement()`
- L139 _private function_ `void OnEndSliderMovement(NumericType Value)`
- L149 _private function_ `void OnValueChanged(NumericType Value)`
- L159 _private function_ `void OnValueCommitted(NumericType Value, ETextCommit::Type CommitInfo)`
- L176 _private member_ `TSharedPtr<ISequencerKeyEditor<NumericType>> KeyEditor;`
- L177 _private member_ `TSharedPtr<SNonThrottledSpinBox<NumericType>> SpinBox;`
- L178 _private member_ `bool bSliding = false;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define LOCTEXT_NAMESPACE "NumericKeyEditor"`
- L88 _function_ `` (scope `SNumericKeyEditorWidget::Construct`)
- L182 _typedef_ `template<typename ChannelType, typename NumericType> using SNumericKeyEditor = SNumericKeyEditorWidget<NumericType>;`

### `Source/Editor/MovieSceneTools/Private/CurveKeyEditors/SStringCurveKeyEditor.h` (Private)


#### class `SStringCurveKeyEditor`  
`class SStringCurveKeyEditor : public SCompoundWidget`  
_L16-30_
- inherits: `SCompoundWidget`
- desc: A widget for editing a curve representing string keys.
- L19 _public function_ `SLATE_BEGIN_ARGS(SStringCurveKeyEditor)`
- L20 _public prototype_ `SLATE_END_ARGS();`
- L22 _public prototype_ `void Construct(const FArguments& InArgs, const TSequencerKeyEditor<FMovieSceneStringChannel, FString>& InKeyEditor);`
- L26 _private prototype_ `FText GetText() const;`
- L27 _private prototype_ `void OnTextCommitted(const FText& InText, ETextCommit::Type InCommitType);`
- L29 _private member_ `TSequencerKeyEditor<FMovieSceneStringChannel, FString> KeyEditor;`

### `Source/Editor/MovieSceneTools/Private/CurveKeyEditors/STextCurveKeyEditor.h` (Private)


#### class `STextCurveKeyEditor`  
`class STextCurveKeyEditor : public SCompoundWidget`  
_L15-31_
- inherits: `SCompoundWidget`
- desc: A widget for editing a curve representing text keys.
- L18 _public function_ `SLATE_BEGIN_ARGS(STextCurveKeyEditor)`
- L19 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSequencerKeyEditor<FMovieSceneTextChannel, FText>& InKeyEditor);`
- L25 _private prototype_ `FText GetText() const;` — Gets the evaluated Text value at the current sequencer time
- L28 _private prototype_ `void OnTextCommitted(const FText& InText, ETextCommit::Type InCommitType);` — Updates the CachedText result to the committed text and adds/updates a key to the text channel at the current sequencer time
- L30 _private member_ `TSequencerKeyEditor<FMovieSceneTextChannel, FText> KeyEditor;`

### `Source/Editor/MovieSceneTools/Private/CurveKeyEditors/SequencerKeyEditor.h` (Private)


#### struct `ISequencerKeyEditor`  
`template<typename ValueType> struct ISequencerKeyEditor`  
_L22-39_
- L24 _public prototype_ `virtual ~ISequencerKeyEditor()= default;`
- L26 _public prototype_ `virtual TSharedPtr<INumericTypeInterface<ValueType>> GetNumericTypeInterface() const = 0;`
- L27 _public prototype_ `virtual TOptional<ValueType> GetExternalValue() const = 0;`
- L28 _public prototype_ `virtual ValueType GetCurrentValue() const = 0;`
- L29 _public prototype_ `virtual void SetValue(const ValueType& InValue) = 0;`
- L30 _public prototype_ `virtual void SetValueWithNotify(const ValueType& InValue, EMovieSceneDataChangeType NotifyType = EMovieSceneDataChangeType::TrackValueChanged) = 0;`
- L31 _public prototype_ `virtual const FGuid& GetObjectBindingID() const = 0;`
- L32 _public prototype_ `virtual ISequencer* GetSequencer() const = 0;`
- L33 _public prototype_ `virtual FTrackInstancePropertyBindings* GetPropertyBindings() const = 0;`
- L34 _public prototype_ `virtual FString GetMetaData(const FName& Key) const = 0;`
- L35 _public prototype_ `virtual bool GetEditingKeySelection() const = 0;`
- L36 _public prototype_ `virtual FFrameTime GetCurrentTime() const = 0;`
- L37 _public prototype_ `virtual void BeginEditing(FFrameTime) = 0;`
- L38 _public prototype_ `virtual void EndEditing() = 0;`

#### struct `TSequencerKeyEditor`  
`template<typename ChannelType, typename ValueType> struct TSequencerKeyEditor`  
_L42-538_
- L44 _public function_ `TSequencerKeyEditor()`
- L47 _public function_ `TSequencerKeyEditor( FGuid InObjectBindingID, TMovieSceneChannelHandle<ChannelType> InChannelHandle, TWeakObjectPtr<UMovieSceneSection> InWeakSection, TWeakPtr<ISequencer> InWeakSequencer, TWeakPtr<FTrackInstancePropertyBindings> InWeakPropertyBindings, TFunction<TOptional<ValueType>(UObject&, FTrackInstancePropertyBindings*)> InOnGetExternalValue ) : ObjectBindingID(InObjectBindingID) , ChannelHandle(InChannelHandle) , WeakSection(InWeakSection) , WeakSequencer(InWeakSequencer) , WeakPropertyBindings(InWeakPropertyBindings) , OnGetExternalValue(InOnGetExternalValue)`
- L63 _public function_ `static TOptional<ValueType> Get(const FGuid& ObjectBindingID, ISequencer* Sequencer, FTrackInstancePropertyBindings* PropertyBindings, const TFunction<TOptional<ValueType>(UObject&, FTrackInstancePropertyBindings*)>& OnGetExternalValue)`
- L85 _public function_ `void SetOwningObject(TWeakObjectPtr<UMovieSceneSignedObject> InWeakOwningObject)`
- L90 _public function_ `void SetNumericTypeInterface(TSharedPtr<INumericTypeInterface<ValueType>> InNumericTypeInterface)`
- L95 _public function_ `TSharedPtr<INumericTypeInterface<ValueType>> GetNumericTypeInterface() const`
- L100 _public function_ `TOptional<ValueType> GetExternalValue() const`
- L105 _public function_ `ValueType GetCurrentValue() const`
- L142 _public function_ `void InitializeChannelGroups()`
- L187 _public function_ `bool GetEditingKeySelection() const`
- L218 _public function_ `TArray<FMovieSceneChannelHandle> GetGroupedChannels(const FMovieSceneChannelProxy& ChannelProxy, const FText& Group)`
- L234 _public function_ `void SetValue(const ValueType& InValue)`
- L437 _public function_ `void SetValueWithNotify(const ValueType& InValue, EMovieSceneDataChangeType NotifyType = EMovieSceneDataChangeType::TrackValueChanged)`
- L446 _public function_ `void SetApplyInUnwarpedLocalSpace(bool bInApplyInUnwarpedLocalSpace)`
- L451 _public function_ `const FGuid& GetObjectBindingID() const`
- L456 _public function_ `ISequencer* GetSequencer() const`
- L461 _public function_ `FTrackInstancePropertyBindings* GetPropertyBindings() const`
- L466 _public function_ `FString GetMetaData(const FName& Key) const`
- L492 _public function_ `FFrameTime GetCurrentTime() const`
- L509 _public function_ `void BeginEditing(FFrameTime InEditingTime)`
- L516 _public function_ `void EndEditing()`
- L523 _private member_ `FGuid ObjectBindingID;`
- L524 _private member_ `TMovieSceneChannelHandle<ChannelType> ChannelHandle;`
- L525 _private member_ `TWeakObjectPtr<UMovieSceneSection> WeakSection;`
- L526 _private member_ `TWeakObjectPtr<UMovieSceneSignedObject> WeakOwningObject;`
- L527 _private member_ `TWeakPtr<ISequencer> WeakSequencer;`
- L528 _private member_ `TWeakPtr<FTrackInstancePropertyBindings> WeakPropertyBindings;`
- L529 _private member_ `TFunction<TOptional<ValueType>(UObject&, FTrackInstancePropertyBindings*)> OnGetExternalValue;`
- L530 _private member_ `TSharedPtr<INumericTypeInterface<ValueType>> NumericTypeInterface;`
- L531 _private member_ `bool bApplyInUnwarpedLocalSpace = false;`
- L536 _private member_ `TOptional<FFrameTime> EditingTime;` — The time at which to edit the key value. This can be enforced when receiving focus on the spin box so that when focus is lost and the value is commited, the value is committed at the editing time rather than the Sequencer time which could have changed.
- L537 _private member_ `TMap<FName, ValueType> ChannelNameToInitialValue;`

#### struct `TSequencerKeyEditorWrapper`  
`template<typename ChannelType, typename ValueType> struct TSequencerKeyEditorWrapper : ISequencerKeyEditor<ValueType>`  
_L544-606_
- inherits: `ISequencerKeyEditor<ValueType>`
- L546 _public function_ `TSequencerKeyEditorWrapper(const TSequencerKeyEditor<ChannelType, ValueType>& InKeyEditor) : Impl(InKeyEditor)`
- L550 _public function_ `TSharedPtr<INumericTypeInterface<ValueType>> GetNumericTypeInterface() const override`
- L554 _public function_ `TOptional<ValueType> GetExternalValue() const override`
- L558 _public function_ `ValueType GetCurrentValue() const override`
- L562 _public function_ `void SetValue(const ValueType& InValue) override`
- L566 _public function_ `void SetValueWithNotify(const ValueType& InValue, EMovieSceneDataChangeType NotifyType) override`
- L570 _public function_ `const FGuid& GetObjectBindingID() const override`
- L574 _public function_ `ISequencer* GetSequencer() const override`
- L578 _public function_ `FTrackInstancePropertyBindings* GetPropertyBindings() const override`
- L582 _public function_ `FString GetMetaData(const FName& Key) const override`
- L586 _public function_ `bool GetEditingKeySelection() const override`
- L590 _public function_ `FFrameTime GetCurrentTime() const override`
- L594 _public function_ `void BeginEditing(FFrameTime InFrameTime) override`
- L598 _public function_ `void EndEditing() override`
- L605 _private member_ `TSequencerKeyEditor<ChannelType, ValueType> Impl;`

### `Source/Editor/MovieSceneTools/Private/EditModes/SkeletalAnimationTrackEditMode.h` (Private)


#### struct `FSelectedRootData`  
`struct FSelectedRootData`  
_L16-24_
- L18 _public prototype_ `FSelectedRootData(UMovieSceneSkeletalAnimationSection* InSection, USkeletalMeshComponent* InComp);`
- L19 _public function_ `bool operator == (const FSelectedRootData& InData) const`
- L20 _public prototype_ `void CalcTransform(const FFrameTime& Frametime, FTransform& OutTransform, FTransform& OutParentTransform);`
- L22 _public member_ `TWeakObjectPtr<UMovieSceneSkeletalAnimationSection> SelectedSection;`
- L23 _public member_ `TWeakObjectPtr<USkeletalMeshComponent> SelectedMeshComp;`

#### class `FSkeletalAnimationTrackEditMode`  
`class FSkeletalAnimationTrackEditMode : public FEdMode`  
_L26-91_
- inherits: `FEdMode`
- L29 _public member_ `static FName ModeName;`
- L31 _public prototype_ `FSkeletalAnimationTrackEditMode();`
- L32 _public prototype_ `~FSkeletalAnimationTrackEditMode();`
- L35 _public prototype_ `virtual bool UsesToolkits() const override;` — FEdMode interface
- L36 _public prototype_ `virtual void Enter() override;`
- L37 _public prototype_ `virtual void Exit() override;`
- L38 _public prototype_ `virtual void Tick(FEditorViewportClient* ViewportClient, float DeltaTime) override;`
- L39 _public prototype_ `virtual void Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI) override;`
- L40 _public prototype_ `virtual bool InputKey(FEditorViewportClient* InViewportClient, FViewport* InViewport, FKey InKey, EInputEvent InEvent) override;`
- L41 _public prototype_ `virtual bool EndTracking(FEditorViewportClient* InViewportClient, FViewport* InViewport) override;`
- L42 _public prototype_ `virtual bool StartTracking(FEditorViewportClient* InViewportClient, FViewport* InViewport) override;`
- L43 _public prototype_ `virtual bool BeginTransform(const FGizmoState& InState) override;`
- L44 _public prototype_ `virtual bool EndTransform(const FGizmoState& InState) override;`
- L45 _public prototype_ `virtual bool HandleClick(FEditorViewportClient* InViewportClient, HHitProxy *HitProxy, const FViewportClick &Click) override;`
- L46 _public prototype_ `virtual void SelectNone() override;`
- L47 _public prototype_ `virtual bool InputDelta(FEditorViewportClient* InViewportClient, FViewport* InViewport, FVector& InDrag, FRotator& InRot, FVector& InScale) override;`
- L48 _public prototype_ `virtual bool UsesTransformWidget() const override;`
- L49 _public prototype_ `virtual bool UsesTransformWidget(UE::Widget::EWidgetMode CheckMode) const;`
- L50 _public prototype_ `virtual FVector GetWidgetLocation() const override;`
- L51 _public prototype_ `virtual bool ShouldDrawWidget() const override;`
- L52 _public prototype_ `virtual bool GetPivotForOrbit(FVector& OutPivot) const override;`
- L53 _public prototype_ `virtual bool GetCustomDrawingCoordinateSystem(FMatrix& OutMatrix, void* InData) override;`
- L54 _public prototype_ `virtual bool GetCustomInputCoordinateSystem(FMatrix& OutMatrix, void* InData) override;`
- L55 _public prototype_ `virtual bool IsCompatibleWith(FEditorModeID OtherModeID) const override;`
- L56 _public function_ `virtual bool RequiresLegacyViewportInteractions() const override`
- L59 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — GCObject
- L61 _public prototype_ `void OnKeySelected(FViewport* Viewport, HMovieSceneSkeletalAnimationRootHitProxy* KeyProxy);`
- L64 _public function_ `void SetSequencer(const TSharedPtr<ISequencer>& InSequencer)` — Set The owning sequencer
- L68 _protected prototype_ `bool IsSomethingSelected() const;`
- L69 _protected prototype_ `bool GetTransformAtFirstSectionStart(FTransform& OutWorld, FTransform& OutParent) const;`
- L70 _protected prototype_ `bool IsRootSelected(UMovieSceneSkeletalAnimationSection* Section) const;`
- L74 _protected member_ `UE::MovieScene::FSystemInterrogator InterrogationLinker;` — Interrogator that is an gc object
- L77 _protected member_ `TWeakPtr<ISequencer> WeakSequencer;` — Sequencer that owns me
- L80 _protected member_ `bool bIsTransacting;` — Whether we are in the middle of a transaction
- L83 _protected member_ `bool bManipulatorMadeChange;` — Whether a manipulator actually made a change when transacting
- L86 _protected member_ `TArray<FSelectedRootData> SelectedRootData;` — Array of Selected Root Setions
- L89 _protected member_ `FTransform RootTransform;` — Cached location of root transform

### `Source/Editor/MovieSceneTools/Private/EditModes/SubTrackEditorMode.h` (Private)


#### class `FSubTrackEditorMode`  
`class FSubTrackEditorMode : public FEdMode`  
_L8-93_
- inherits: `FEdMode`
- L11 _public member_ `static FName ModeName;`
- L13 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnOriginValueChanged, FVector, FRotator) FSubTrackEditorMode();`
- L19 _public prototype_ `virtual void Initialize() override;` — FEdMode interface
- L20 _public prototype_ `virtual bool InputDelta(FEditorViewportClient* InViewportClient, FViewport* InViewport, FVector& InDrag, FRotator& InRot, FVector& InScale) override;`
- L21 _public prototype_ `virtual bool StartTracking(FEditorViewportClient* InViewportClient, FViewport* InViewport) override;`
- L22 _public prototype_ `virtual bool EndTracking(FEditorViewportClient* InViewportClient, FViewport* InViewport) override;`
- L23 _public prototype_ `virtual bool UsesTransformWidget() const override;`
- L24 _public prototype_ `virtual bool UsesTransformWidget(UE::Widget::EWidgetMode CheckMode) const override;`
- L25 _public prototype_ `virtual FVector GetWidgetLocation() const override;`
- L26 _public prototype_ `virtual bool ShouldDrawWidget() const override;`
- L27 _public prototype_ `virtual bool GetPivotForOrbit(FVector& OutPivot) const override;`
- L28 _public prototype_ `virtual bool GetCustomDrawingCoordinateSystem(FMatrix& OutMatrix, void* InData) override;`
- L29 _public prototype_ `virtual bool GetCustomInputCoordinateSystem(FMatrix& OutMatrix, void* InData) override;`
- L30 _public prototype_ `virtual bool IsCompatibleWith(FEditorModeID OtherModeID) const override;`
- L31 _public function_ `virtual bool RequiresLegacyViewportInteractions() const override`
- L33 _public function_ `void SetSequencer(const TSharedPtr<ISequencer>& InSequencer)`
- L34 _public function_ `FOnOriginValueChanged& GetOnOriginValueChanged()`
- L36 _public prototype_ `void ClearCachedCoordinates();`
- L39 _public prototype_ `virtual bool BeginTransform(const FGizmoState& InState) override;` — Start IGizmoEdModeInterface overrides
- L40 _public prototype_ `virtual bool EndTransform(const FGizmoState& InState) override;`
- L45 _private prototype_ `static bool DoesSubSectionHaveTransformOverrides(const UMovieSceneSubSection& SubSection);` — Returns true if there are any sub tracks with active transform origin overrides.
- L48 _private prototype_ `TOptional<FMovieSceneSequenceID> GetSequenceIDForSubSection(const UMovieSceneSubSection* InSubSection) const;` — Gets the sequence ID from the context of the subsection in the current hierarchy.
- L50 _private prototype_ `TOptional<FMovieSceneSequenceID> GetFocusedSequenceID() const;` — Gets the sequence ID of the currently focused sequence.
- L52 _private prototype_ `FTransform GetFinalTransformOriginForSubSection(const UMovieSceneSubSection* SubSection) const;` — Gets the transform origin of the provided section, after all parent transforms have been applied.
- L54 _private prototype_ `FTransform GetTransformOriginForSequence(TOptional<FMovieSceneSequenceID> InSequenceID) const;` — Gets the transform origin corresponding to the sequence in the current hierarchy matching the provided sequence ID.
- L56 _private prototype_ `bool AreAnyActorsSelected() const;` — returns true if any actors are selected in the level editor. This is used to prevent this editor mode from being active when actors are selected.
- L58 _private prototype_ `FVector GetAverageLocationOfBindingsInSubSection(const UMovieSceneSubSection* SubSection) const;` — Gets the average location of the objects in a subsection.
- L60 _private prototype_ `void RecursiveAccumulateBindingPositions(const UMovieSceneSubSection* SubSection, FVector& AccumulatedLocation, int32& ActorCount, const FMovieSceneSequenceHierarchy* Hierarchy, const FMovieSceneSequenceID FocusedSequenceID, const FMovieSceneSequenceID ParentSequenceID, const TSharedPtr<ISequencer> Sequencer) const;` — Accumulate the positions and counts of all bound objects in and descended from the given SubSection
- L64 _private prototype_ `UMovieSceneSubSection* GetSelectedSection() const;` — Returns the currently selected section.
- L66 _private prototype_ `UMovieSceneSubSection* GetSectionToEdit() const;` — Returns the selected section, if its origin overrides can be edited, and there are no selected actors.
- L69 _private member_ `TWeakPtr<ISequencer> WeakSequencer;` — Sequencer that owns this editor mode
- L72 _private member_ `FOnOriginValueChanged OnOriginValueChanged;` — Delegate called when the origin is modified from the editor gizmo
- L75 _private member_ `mutable TOptional<FVector> CachedLocation;` — Used to tell if the gizmo has moved, and if the editor hit proxies need to be invalidated as a result
- L78 _private member_ `bool bIsTracking = false;` — Used to ensure that we mirror the behavior in StartTracking if the selection were to change mid-drag.
- L82 _private member_ `TOptional<FMatrix> PreviewCoordinateSpaceRotation;` — Caches the transform space to use for editing with the gizmo. Updates to the channel data aren't reflected in time for the UI, so keeping the preview space up-to-date prevents the gizmo from flickering.
- L86 _private member_ `TOptional<FVector> PreviewLocation;` — Caches the location to use for editing with the gizmo. When rotating, the average location of the actors in a subsequence can change, so instead of querying it every frame, the value is cached when an edit begins, and is only updated if the gizmo is dragged.
- L88 _private member_ `const TArray<FName> IncompatibleEditorModes = TArray<FName>({ "EditMode.`
- L91 _private prototype_ `bool HandleBeginTransform();` — Manages the start and end of a transform action in the viewport
- L92 _private prototype_ `bool HandleEndTransform();`

#### Free symbols / members of external scopes

- L13 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnOriginValueChanged, FVector, FRotator) FSubTrackEditorMode();`

### `Source/Editor/MovieSceneTools/Private/FCPXML/FCPXMLExport.h` (Private)


#### class `FFCPXMLExportVisitor`  
`class FFCPXMLExportVisitor : public FFCPXMLNodeVisitor`  
_L21-144_
- inherits: `FFCPXMLNodeVisitor`
- L25 _public prototype_ `FFCPXMLExportVisitor(FString InSaveFilename, TSharedRef<FMovieSceneExportData> InExportData, TSharedRef<FMovieSceneTranslatorContext> InExportContext);` — Constructor
- L27 _public prototype_ `virtual ~FFCPXMLExportVisitor();` — Destructor
- L32 _public prototype_ `virtual bool VisitNode(TSharedRef<FFCPXMLBasicNode> InBasicNode) override final;` — Called when visiting a FFCPXMLBasicNode during visitor traversal.
- L34 _public prototype_ `virtual bool VisitNode(TSharedRef<FFCPXMLXmemlNode> InXmemlNode) override final;` — Called when visiting a FFCPXMLXmemlNode during visitor traversal.
- L36 _public prototype_ `virtual bool VisitNode(TSharedRef<FFCPXMLSequenceNode> InSequenceNode) override final;` — Called when visiting a FFCPXMLSequenceNode during visitor traversal.
- L38 _public prototype_ `virtual bool VisitNode(TSharedRef<FFCPXMLVideoNode> InVideoNode) override final;` — Called when visiting a FFCPXMLVideoNode during visitor traversal.
- L40 _public prototype_ `virtual bool VisitNode(TSharedRef<FFCPXMLAudioNode> InAudioNode) override final;` — Called when visiting a FFCPXMLAudioNode during visitor traversal.
- L42 _public prototype_ `virtual bool VisitNode(TSharedRef<FFCPXMLTrackNode> InTrackNode) override final;` — Called when visiting a FFCPXMLTrackNode during visitor traversal.
- L44 _public prototype_ `virtual bool VisitNode(TSharedRef<FFCPXMLClipNode> InClipNode) override final;` — Called when visiting a FFCPXMLClipNode during visitor traversal.
- L46 _public prototype_ `virtual bool VisitNode(TSharedRef<FFCPXMLClipItemNode> InClipItemNode) override final;` — Called when visiting a FFCPXMLClipItemNode during visitor traversal.
- L48 _public prototype_ `virtual bool VisitNode(TSharedRef<FFCPXMLFileNode> InFileNode) override final;` — Called when visiting a FFCPXMLFileNode during visitor traversal.
- L52 _public prototype_ `bool ConstructProjectNode(TSharedRef<FFCPXMLNode> InParentNode);` — Creates project node.
- L54 _public prototype_ `virtual bool ConstructMasterVideoClipNodes(TSharedRef<FFCPXMLNode> InParentNode);` — Creates master video clip nodes.
- L56 _public prototype_ `bool ConstructMasterAudioClipNodes(TSharedRef<FFCPXMLNode> InParentNode);` — Creates master audio clip nodes.
- L58 _public prototype_ `bool ConstructMasterClipNode(TSharedRef<FFCPXMLNode> InParentNode, const TSharedPtr<FMovieSceneExportCinematicSectionData> InCinematicSectionData, const TSharedPtr<FMovieSceneExportCinematicData> InCinematicData);` — Creates master video clip node.
- L60 _public prototype_ `bool ConstructMasterClipNode(TSharedRef<FFCPXMLNode> InParentNode, const TSharedPtr<FMovieSceneExportAudioSectionData> InAudioSectionData, const TSharedPtr<FMovieSceneExportAudioData> InCinematicData);` — Creates master audio clip node.
- L62 _public prototype_ `bool ConstructColorInfoNode(TSharedRef<FFCPXMLNode> InParentNode);` — Creates colorinfo node.
- L64 _public prototype_ `bool ConstructLoggingInfoNode(TSharedRef<FFCPXMLNode> InParentNode, const UMovieSceneSection* InMovieSceneSection);` — Creates logginginfo node.
- L66 _public prototype_ `bool ConstructLoggingInfoNode(TSharedRef<FFCPXMLNode> InParentNode, const TSharedPtr<FMovieSceneExportAudioSectionData> InSectionData);` — Creates logginginfo node.
- L68 _public prototype_ `bool ConstructSequenceNode(TSharedRef<FFCPXMLNode> InParentNode);` — Creates sequence node.
- L70 _public prototype_ `bool ConstructVideoNode(TSharedRef<FFCPXMLNode> InParentNode);` — Creates video node.
- L72 _public prototype_ `bool ConstructAudioNode(TSharedRef<FFCPXMLNode> InParentNode);` — Creates audio node.
- L74 _public prototype_ `virtual bool ConstructVideoTrackNode(TSharedRef<FFCPXMLNode> InParentNode, const TSharedPtr<FMovieSceneExportCinematicTrackData> InCinematicTrackData, const TSharedPtr<FMovieSceneExportCinematicData> InCinematicData);` — Creates video track node.
- L76 _public prototype_ `bool ConstructAudioTrackNode(TSharedRef<FFCPXMLNode> InParentNode, const TSharedPtr<FMovieSceneExportAudioTrackData> InAudioTrackData, const TSharedPtr<FMovieSceneExportAudioData> InAudioData, uint32 InTrackIndex, uint32 OutNumTracks);` — Creates audio track node.
- L78 _public prototype_ `bool ConstructVideoClipItemNode(TSharedRef<FFCPXMLNode> InParentNode, const TSharedPtr<FMovieSceneExportCinematicSectionData> InCinematicSectionData, const TSharedPtr<FMovieSceneExportCinematicData> InCinematicData, bool bInMasterClip);` — Creates video clip item node.
- L80 _public prototype_ `bool ConstructAudioClipItemNode(TSharedRef<FFCPXMLNode> InParentNode, const TSharedPtr<FMovieSceneExportAudioSectionData> InAudioSectionData, const TSharedPtr<FMovieSceneExportAudioData> InAudioData, int32 InChannel, bool bInMasterClip, const FString& InClipItemIdName1, const FString& InClipItemIdName2, int32 InClipIndex1, int32 InClipIndex2, int32 InTrackIndex1, int32 InTrackIndex2);` — Creates audio clip item node.
- L84 _public prototype_ `bool ConstructVideoFileNode(TSharedRef<FFCPXMLNode> InParentNode, const TSharedPtr<FMovieSceneExportCinematicSectionData> InCinematicSectionData, int32 InDuration, bool bInMasterClip);` — Creates video file node.
- L86 _public prototype_ `bool ConstructAudioFileNode(TSharedRef<FFCPXMLNode> InParentNode, const TSharedPtr<FMovieSceneExportAudioSectionData> InAudioSectionData, int32 InChannel);` — Creates audio file node.
- L88 _public prototype_ `bool ConstructVideoSampleCharacteristicsNode(TSharedRef<FFCPXMLNode> InParentNode, int InWidth, int InHeight);` — Creates video sample characteristics node
- L90 _public prototype_ `bool ConstructAudioSampleCharacteristicsNode(TSharedRef<FFCPXMLNode> InParentNode, int InDepth, int InSampleRate);` — Creates audio video sample characteristics node
- L92 _public prototype_ `bool ConstructRateNode(TSharedRef<FFCPXMLNode> InParentNode);` — Creates rate node.
- L94 _public prototype_ `bool ConstructTimecodeNode(TSharedRef<FFCPXMLNode> InParentNode);` — Creates timecode node.
- L96 _public prototype_ `void ConstructLoggingInfoElements(TSharedRef<FFCPXMLNode> InLoggingInfoNode, const UObject* InObject = nullptr);` — Creates logginginfo elements.
- L98 _public prototype_ `void SetLoggingInfoElementValue(TSharedPtr<FFCPXMLNode> InNode, const UObject* InObject, const FString& InElement);` — Set logginginfo element value.
- L100 _public prototype_ `bool GetCinematicSectionFrames(const TSharedPtr<FMovieSceneExportCinematicSectionData> InCinematicSectionData, int32& OutDuration, int32& OutStartFrame, int32& OutEndFrame, int32& OutInFrame, int32& OutOutFrame);` — Get cinematic duration, start, end, in, out frames for a given cinematic shot section
- L102 _public prototype_ `bool GetAudioSectionFrames(const TSharedPtr<FMovieSceneExportAudioSectionData> InAudioSectionData, int32& OutDuration, int32& OutStartFrame, int32& OutEndFrame, int32& OutInFrame, int32& OutOutFrame);` — Get audio duration, start, end, in, out frames for a given cinematic shot section
- L107 _protected prototype_ `bool HasMasterClipIdName(const TSharedPtr<FMovieSceneExportSectionData> InSection, FString& OutName, bool& bOutMasterClipExists);` — Has master clip id for given section
- L109 _protected prototype_ `bool GetMasterClipIdName(const TSharedPtr<FMovieSceneExportSectionData> InSection, FString& OutName);` — Get master clip id name for section
- L111 _protected prototype_ `bool GetFileIdName(const TSharedPtr<FMovieSceneExportSectionData> InSection, FString& OutName, bool& bFileExists);` — Get file id name for section, adds to file map if a new id name is created
- L113 _protected prototype_ `void GetNextClipItemIdName(FString& OutName);` — Get next clip item name
- L116 _protected prototype_ `bool ComposeFileKey(const TSharedPtr<FMovieSceneExportSectionData> InSection, FString& OutName);` — Compose key for section file
- L119 _protected prototype_ `bool HasStereoAudioSections(const TArray<TSharedPtr<FMovieSceneExportAudioSectionData>>& InAudioTrackData) const;` — Returns true if audio track data contains sections with 2 channels
- L122 _protected prototype_ `bool CreateCinematicSectionMetadata(const UMovieSceneCinematicShotSection* InSection, FString& OutMetadata) const;` — Get metadata section name from sequencer shot name - format is "[UESection=sectionobjectname]", whitespace ok.
- L124 _protected prototype_ `bool CreateSoundWaveMetadata(const USoundWave* InSoundWave, const TArray<const UMovieSceneAudioSection*> InAudioSections, FString& OutMetadata) const;` — Get metadata section name from sequencer shot name - format is "[UESoundWave=soundwaveobjectname]", whitespace ok.
- L126 _protected prototype_ `static FString GetAudioSectionTopLevelName(const UMovieSceneAudioSection* InAudioSection);` — Get id for audio top level section
- L128 _protected prototype_ `static FString GetAudioSectionName(const UMovieSceneSection* InAudioSection);` — Get audio section group name
- L132 _protected member_ `TSharedRef<FMovieSceneExportData> ExportData;`
- L133 _protected member_ `TSharedRef<FMovieSceneTranslatorContext> ExportContext;`
- L134 _protected member_ `FString SaveFilePath;`
- L135 _protected member_ `uint32 SequenceId;`
- L136 _protected member_ `uint32 MasterClipId;`
- L137 _protected member_ `uint32 ClipItemId;`
- L138 _protected member_ `uint32 FileId;`
- L141 _protected member_ `TMap<FString, uint32> MasterClipIdMap;` — Map section's unique key string to the id used for masterclip element names
- L143 _protected member_ `TMap<FString, uint32> FileIdMap;` — Map section's source file name to its file element name

### `Source/Editor/MovieSceneTools/Private/FCPXML/FCPXMLFile.h` (Private)


#### class `FFCPXMLFile`  
`class FFCPXMLFile : public TSharedFromThis<FFCPXMLFile>`  
_L20-96_
- inherits: `TSharedFromThis<FFCPXMLFile>`
- desc: The FFCPXMLFile class represents the overall FCP 7 XML file and is the containing class for the node tree structure. The FCP 7 XML Translator uses the FXmlParser classes to parse and write out XML. It constructs its own representation using the classes FFCPXMLFile and FFCPXMLNode so the import and export can manipulate the XML data as needed.
- L25 _public prototype_ `FFCPXMLFile();` — Default constructor
- L28 _public function_ `~FFCPXMLFile()` — Destructor
- L33 _public prototype_ `void ConstructFile(const FString& InProjectName);` — Initializes the file root in preparation to construct XML file
- L41 _public prototype_ `bool LoadFile(const FString& InPath, EConstructMethod::Type InConstructMethod = EConstructMethod::ConstructFromFile);` — Loads the file with the passed path. Path is either treated as a filename to open, or as a text buffer to load. @param	Path				The path/text to use @param	ConstructMethod		Whether to load a file of use the string as a buffer of xml data
- L44 _public prototype_ `FText GetLastError() const;` — Gets the last error message from the class
- L47 _public prototype_ `void Clear();` — Clears the file of all internals. Note: Makes any existing pointers to file and nodes INVALID
- L50 _public prototype_ `bool IsValidFile() const;` — Checks to see if a file is loaded
- L53 _public prototype_ `bool Accept(FFCPXMLNodeVisitor& InNodeVisitor);` — Accepts a node visitor
- L60 _public prototype_ `const TSharedPtr<FFCPXMLNode> GetRootNode() const;` — Returns the root node of the loaded file. nullptr if no file loaded. It is assumed that there will always be one and only one root node. @return						Pointer to root node
- L67 _public prototype_ `TSharedPtr<FFCPXMLNode> GetRootNode();` — Returns the root node of the loaded file. nullptr if no file loaded. It is assumed that there will always be one and only one root node. @return						Pointer to root node
- L74 _public prototype_ `bool Save(const FString& InPath);` — Write to disk, UTF-8 format @param	Path				File path to save to @return						Whether writing the XML to a file succeeded
- L77 _public prototype_ `bool AddReference(const FString& InElement, const FString &InId, TSharedPtr<FFCPXMLNode>);` — Add reference id to map
- L80 _public prototype_ `TSharedPtr<FFCPXMLNode> GetReference(const FString &InElement, const FString &InId);` — Get node associated with reference id
- L85 _private prototype_ `FString ComposeKey(const FString& A, const FString& B);` — Compose single map key using two string inputs
- L89 _private member_ `FString LoadedFile;` — The passed-in path of the loaded file (might be absolute or relative)
- L91 _private member_ `FText ErrorMessage;` — An error message generated on errors to return to the client
- L93 _private member_ `TSharedPtr<FFCPXMLNode> RootNode;` — A pointer to the root node
- L95 _private member_ `TMap<FString, TSharedPtr<FFCPXMLNode>> ReferenceMap;` — Map of reference ids in currently loaded file

#### class `FFCPXMLFileSetupVisitor`  
`class FFCPXMLFileSetupVisitor : public FFCPXMLNodeVisitor`  
_L99-130_
- inherits: `FFCPXMLNodeVisitor`
- desc: Node visitor class used to set up reference id map for loaded file
- L103 _public prototype_ `FFCPXMLFileSetupVisitor();` — Constructor
- L105 _public prototype_ `~FFCPXMLFileSetupVisitor();` — Destructor
- L109 _public prototype_ `virtual bool VisitNode(TSharedRef<FFCPXMLBasicNode> InBasicNode) override final;` — Called when visiting a FFCPXMLBasicNode during visitor traversal.
- L111 _public prototype_ `virtual bool VisitNode(TSharedRef<FFCPXMLXmemlNode> InXmemlNode) override final;` — Called when visiting a FFCPXMLMemlNode during visitor traversal.
- L113 _public prototype_ `virtual bool VisitNode(TSharedRef<FFCPXMLSequenceNode> InSequenceNode) override final;` — Called when visiting a FFCPXMLSequenceNode during visitor traversal.
- L115 _public prototype_ `virtual bool VisitNode(TSharedRef<FFCPXMLVideoNode> InVideoNode) override final;` — Called when visiting a FFCPXMLVideoNode during visitor traversal.
- L117 _public prototype_ `virtual bool VisitNode(TSharedRef<FFCPXMLAudioNode> InAudioNode) override final;` — Called when visiting a FFCPXMLAudioNode during visitor traversal.
- L119 _public prototype_ `virtual bool VisitNode(TSharedRef<FFCPXMLTrackNode> InTrackNode) override final;` — Called when visiting a FFCPXMLTrackNode during visitor traversal.
- L121 _public prototype_ `virtual bool VisitNode(TSharedRef<FFCPXMLClipNode> InClipNode) override final;` — Called when visiting a FFCPXMLClipNode during visitor traversal.
- L123 _public prototype_ `virtual bool VisitNode(TSharedRef<FFCPXMLClipItemNode> InClipItemNode) override final;` — Called when visiting a FFCPXMLClipItemNode during visitor traversal.
- L125 _public prototype_ `virtual bool VisitNode(TSharedRef<FFCPXMLFileNode> InFileNode) override final;` — Called when visiting a FFCPXMLFileNode during visitor traversal.
- L129 _private prototype_ `void AddReferenceId(FString InType, TSharedRef<FFCPXMLNode> InNode);` — Adds a reference id to node common data, if id does not already exist

### `Source/Editor/MovieSceneTools/Private/FCPXML/FCPXMLImport.h` (Private)


#### struct `FFCPXMLImportAudioTrackListItem`  
`struct FFCPXMLImportAudioTrackListItem`  
_L12-18_
- L14 _public function_ `FFCPXMLImportAudioTrackListItem(TSharedPtr<FMovieSceneImportAudioData> InAudioTrackData, int InRowIndex) : AudioTrackData(InAudioTrackData), RowIndex(InRowIndex)`
- L16 _public member_ `TSharedPtr<FMovieSceneImportAudioData> AudioTrackData;`
- L17 _public member_ `int32 RowIndex;`

#### struct `FFCPXMLImportAudioSectionMetadata`  
`struct FFCPXMLImportAudioSectionMetadata`  
_L20-26_
- L22 _public function_ `FFCPXMLImportAudioSectionMetadata(const FString& InAudioSectionPathName) : AudioSectionPathName(InAudioSectionPathName), bAudioSectionUpdated(false)`
- L24 _public member_ `FString AudioSectionPathName;`
- L25 _public member_ `bool bAudioSectionUpdated;`

#### struct `FFCPXMLImportAudioMetadata`  
`struct FFCPXMLImportAudioMetadata`  
_L28-35_
- L30 _public function_ `FFCPXMLImportAudioMetadata(const FString& InSoundPathName) : SoundPathName(InSoundPathName)`
- L31 _public function_ `FFCPXMLImportAudioMetadata() : SoundPathName(TEXT(""))`
- L33 _public member_ `FString SoundPathName;`
- L34 _public member_ `TArray< TSharedPtr<FFCPXMLImportAudioSectionMetadata> > AudioSections;`

#### class `FFCPXMLImportVisitor`  
`class FFCPXMLImportVisitor : public FFCPXMLNodeVisitor`  
_L39-156_
- inherits: `FFCPXMLNodeVisitor`
- L43 _public prototype_ `FFCPXMLImportVisitor(TSharedRef<FMovieSceneImportData> InImportData, TSharedRef<FMovieSceneTranslatorContext> InImportContext);` — Constructor
- L45 _public prototype_ `~FFCPXMLImportVisitor();` — Destructor
- L49 _public prototype_ `virtual bool VisitNode(TSharedRef<FFCPXMLBasicNode> InBasicNode) override final;` — Called when visiting a FFCPXMLBasicNode during visitor traversal.
- L51 _public prototype_ `virtual bool VisitNode(TSharedRef<FFCPXMLXmemlNode> InXmemlNode) override final;` — Called when visiting a FFCPXMLMemlNode during visitor traversal.
- L53 _public prototype_ `virtual bool VisitNode(TSharedRef<FFCPXMLSequenceNode> InSequenceNode) override final;` — Called when visiting a FFCPXMLSequenceNode during visitor traversal.
- L55 _public prototype_ `virtual bool VisitNode(TSharedRef<FFCPXMLVideoNode> InVideoNode) override final;` — Called when visiting a FFCPXMLVideoNode during visitor traversal.
- L57 _public prototype_ `virtual bool VisitNode(TSharedRef<FFCPXMLAudioNode> InAudioNode) override final;` — Called when visiting a FFCPXMLAudioNode during visitor traversal.
- L59 _public prototype_ `virtual bool VisitNode(TSharedRef<FFCPXMLTrackNode> InTrackNode) override final;` — Called when visiting a FFCPXMLTrackNode during visitor traversal.
- L61 _public prototype_ `virtual bool VisitNode(TSharedRef<FFCPXMLClipNode> InClipNode) override final;` — Called when visiting a FFCPXMLClipNode during visitor traversal.
- L63 _public prototype_ `virtual bool VisitNode(TSharedRef<FFCPXMLClipItemNode> InClipItemNode) override final;` — Called when visiting a FFCPXMLClipItemNode during visitor traversal.
- L65 _public prototype_ `virtual bool VisitNode(TSharedRef<FFCPXMLFileNode> InFileNode) override final;` — Called when visiting a FFCPXMLFileNode during visitor traversal.
- L69 _private prototype_ `bool VisitVideoClipItemNode(TSharedRef<FFCPXMLClipItemNode> InClipItemNode);` — Called when visiting a video FFCPXMLClipItemNode during visitor traversal.
- L71 _private prototype_ `bool VisitAudioClipItemNode(TSharedRef<FFCPXMLClipItemNode> InClipItemNode);` — Called when visiting an audio FFCPXMLClipItemNode during visitor traversal.
- L73 _private prototype_ `bool GetClipItemNodeData(TSharedRef<FFCPXMLClipItemNode> InClipItemNode, FString& OutClipItemName, FString& OutClipItemId, FString& OutMasterClipId, TSharedPtr<FFCPXMLNode>& OutLoggingInfoNode, FString& OutLogNote, FString& OutFilename, FFrameRate& OutFrameRate, FFrameNumber& StartOffset, FFrameNumber& Start, FFrameNumber &End);` — Get clipitem node data used by both video and audio clipitems
- L76 _private prototype_ `int32 GetAudioClipItemNodeChannel(TSharedRef<FFCPXMLClipItemNode> InClipItemNode, const FString& InClipItemId);` — Query which channel audio clipitem node represents
- L79 _private prototype_ `bool ConstructAudioTrackList();` — Construct list of audio tracks and row indexes
- L82 _private prototype_ `bool AddMasterClipCinematicSectionPathName(const FString& InMasterClipIdName, const FString& InSectionPathName);` — Add entry to master cinematic clip section name map
- L84 _private prototype_ `bool GetMasterClipCinematicSectionPathName(const FString& InMasterClipIdName, FString& OutSectionPathName) const;` — Query master cinematic clip section name map
- L86 _private prototype_ `FString GetCinematicSectionPathName(const FString& InMetadata, const FString& InMasterClipId);` — Get cinematic section path name based on node metadata and masterclip id
- L89 _private prototype_ `bool AddMasterClipAudioMetadata(const FString& InMasterClipIdName, TSharedPtr<FFCPXMLImportAudioMetadata> InAudioMetadata);` — Add entry to master clip audio section map
- L91 _private prototype_ `bool GetMasterClipAudioMetadata(const FString& InMasterClipIdName, TSharedPtr<FFCPXMLImportAudioMetadata>& OutAudioMetadata) const;` — Query master clip audio section map
- L93 _private prototype_ `TSharedPtr<FFCPXMLImportAudioMetadata> GetAudioMetadataObject(const FString& InLogNote, const FString& InMasterClipId);` — Get audio metadata object based on log note and master clip id
- L95 _private prototype_ `bool GetNextAudioSection(TSharedPtr<FFCPXMLImportAudioMetadata> InAudioMetadata, TSharedPtr<FMovieSceneImportAudioData>& OutAudioData, TSharedPtr<FMovieSceneImportAudioSectionData>& OutAudioSectionData);` — Get next audio section based on audio metadata
- L98 _private prototype_ `bool AddMasterClipLoggingNode(const FString& InMasterClipIdName, TSharedPtr<FFCPXMLNode> InLoggingInfoNode);` — Add entry to metadata map
- L100 _private prototype_ `bool GetMasterClipLoggingNode(const FString& InMasterClipIdName, TSharedPtr<FFCPXMLNode>& InLoggingInfoNode) const;` — Query master clip logging node
- L103 _private prototype_ `bool SetMetaDataValue(TSharedPtr<FFCPXMLNode> InNode, const FString& InElement, FMetaData& InMetaData, const UMovieSceneSection* InSection) const;` — Helper method
- L105 _private prototype_ `bool ImportSectionMetaData(const TSharedPtr<FFCPXMLNode>& InLoggingInfoNode, const UMovieSceneSection* InSection) const;` — Import logging info metadata to sequencer section
- L108 _private prototype_ `bool ParseMetadata(const FString& InMetadata, const FString& InKey, FString& OutValue, FString& OutMetadata) const;` — parse metadata of the format "[tag=value]", whitespace ok.
- L110 _private prototype_ `bool ParseMetadata(const FString& InMetadata, const FString& InKey, FString& OutValue) const;` — parse metadata of the format "[tag=value]", whitespace ok.
- L112 _private prototype_ `bool GetCinematicSectionPathNameFromMetadata(const FString& InMetadata, FString& OutSectionObjectName) const;` — Get sequencer section id from section metadata. Format is "[UEShotSection=sectionobjectname]", whitespace ok.
- L114 _private prototype_ `bool GetCinematicSectionHandleFramesFromMetadata(const FString& InMetadata, int32& OutHandleFrames) const;` — Get sequencer shot handle frames from section metadata. Format is "[UEShotHandleFrames=handleframes]", whitespace ok.
- L116 _private prototype_ `bool GetCinematicSectionStartOffsetFromMetadata(const FString& InMetadata, int32& OutStartOffset) const;` — Get sequencer shot start offset frame from section metadata. Format is "[UEShotStartOffset=startoffset]", whitespace ok.
- L118 _private prototype_ `bool GetAudioFromMetadata(const FString& InMetadata, TSharedPtr<FFCPXMLImportAudioMetadata>& OutAudioMetadata) const;` — Get sequencer sound wave id and audio section ids from metadata. Format is "[UESoundWave=trackobjectname][UEAudioSectionTopLevel=toplevelobjectname][UEAudioSection=audiosectionobjectname]", whitespace ok.
- L122 _public function_ `int32 GetMaxVideoTrackRowIndex() const`
- L123 _public function_ `int32 GetMaxAudioTrackRowIndex() const`
- L126 _private member_ `TSharedRef<FMovieSceneImportData> ImportData;`
- L127 _private member_ `TSharedRef<FMovieSceneTranslatorContext> ImportContext;`
- L130 _private member_ `TMap<FString, FString> MasterClipCinematicSectionMap;` — Map of masterclip names to sequencer section id names.
- L133 _private member_ `TMap<FString, TSharedPtr<FFCPXMLImportAudioMetadata>> MasterClipAudioSectionMap;` — Map of masterclip names to sequencer audio metadata
- L136 _private member_ `TMap<FString, TSharedPtr<FFCPXMLNode>> MasterClipLoggingNodeMap;` — Map of masterclip names to logging info nodes
- L139 _private member_ `TArray< TSharedPtr<FFCPXMLImportAudioTrackListItem> > AudioTrackList;` — List of existing audio tracks including row index
- L142 _private member_ `bool bInSequenceNode;` — Traversal state variables
- L143 _private member_ `bool bInVideoNode;`
- L144 _private member_ `bool bInAudioNode;`
- L145 _private member_ `bool bInVideoTrackNode;`
- L146 _private member_ `bool bInAudioTrackNode;`
- L148 _private member_ `int32 CurrVideoTrackRowIndex;`
- L149 _private member_ `int32 CurrAudioTrackListIndex;`
- L150 _private member_ `TSharedPtr<FMovieSceneImportAudioData> CurrAudioData;`
- L151 _private member_ `int32 CurrAudioTrackRowIndex;`
- L152 _private member_ `bool bCurrImportAudioTrackIsStereoChannel;`
- L154 _private member_ `int32 MaxVideoTrackRowIndex;`
- L155 _private member_ `int32 MaxAudioTrackRowIndex;`

### `Source/Editor/MovieSceneTools/Private/FCPXML/FCPXMLMetadataExport.h` (Private)


#### class `FFCPXMLMetadataExportVisitor`  
`class FFCPXMLMetadataExportVisitor : public FFCPXMLExportVisitor`  
_L11-32_
- inherits: `FFCPXMLExportVisitor`
- L15 _public prototype_ `FFCPXMLMetadataExportVisitor(FString InSaveFilename, TSharedRef<FMovieSceneExportData> InExportData, TSharedRef<FMovieSceneTranslatorContext> InExportContext, const FMovieSceneExportMetadata* InMovieSceneExportMetadata);` — Constructor
- L17 _public prototype_ `virtual ~FFCPXMLMetadataExportVisitor();` — Destructor
- L20 _public prototype_ `virtual bool ConstructMasterVideoClipNodes(TSharedRef<FFCPXMLNode> InParentNode) override;` — Creates master video clip nodes.
- L21 _public prototype_ `virtual bool ConstructVideoTrackNode(TSharedRef<FFCPXMLNode> InParentNode, const TSharedPtr<FMovieSceneExportCinematicTrackData> InCinematicTrackData, const TSharedPtr<FMovieSceneExportCinematicData> InCinematicData) override;`
- L23 _public prototype_ `bool ConstructMasterClipNode(TSharedRef<FFCPXMLNode> InParentNode, const FString& InClipName, const FMovieSceneExportMetadataShot& InShotMetadata, const FMovieSceneExportMetadataClip& InClipMetadata, const int32 HandleFrames);`
- L24 _public prototype_ `bool ConstructVideoClipItemNode(TSharedRef<FFCPXMLNode> InParentNode, const FString& InClipName, const FMovieSceneExportMetadataClip& InClipMetadata, const int32 HandleFrames, bool bInMasterClip);`
- L25 _public prototype_ `bool GetMasterClipIdName(const FString& InClipName, FString& OutName);`
- L26 _public prototype_ `bool GetFileIdName(const FString& InFileName, FString& OutFileIdName, bool& OutFileExists);`
- L27 _public prototype_ `bool ConstructVideoFileNode(TSharedRef<FFCPXMLNode> InParentNode, const FString& InClipName, int32 Duration, bool bInMasterClip);`
- L30 _protected member_ `const FMovieSceneExportMetadata* MovieSceneExportMetadata;`

### `Source/Editor/MovieSceneTools/Private/FCPXML/FCPXMLNode.h` (Private)


#### enum `ENodeInherit`  
`enum class ENodeInherit : uint8`  
_L38-42_
- L40 _public enumerator_ `NoInherit`
- L41 _public enumerator_ `CheckInherit`

#### enum `ENodeReference`  
`enum class ENodeReference : uint8`  
_L44-48_
- L46 _public enumerator_ `NoReferences`
- L47 _public enumerator_ `CheckReferences`

#### class `FFCPXMLAttribute`  
`class FFCPXMLAttribute`  
_L51-77_
- desc: FCP XML attribute class.
- L55 _public function_ `FFCPXMLAttribute(const FString& InTag, const FString& InValue) : Tag(InTag), Value(InValue)` — Default constructor
- L58 _public prototype_ `const FString& GetTag() const;` — Gets the tag of the attribute
- L61 _public prototype_ `const FString& GetValue() const;` — Gets the value of the attribute
- L63 _public prototype_ `bool GetValue(FString& OutValue) const;` — Gets the value of the node
- L65 _public prototype_ `bool GetValue(float& OutValue) const;` — Gets the value of the node
- L67 _public prototype_ `bool GetValue(int32& OutValue) const;` — Gets the value of the node
- L69 _public prototype_ `bool GetValue(bool& OutValue) const;` — Gets the value of the node
- L73 _private member_ `FString Tag;` — The tag string
- L76 _private member_ `FString Value;` — The value string

#### class `FFCPXMLNode`  
`class FFCPXMLNode : public TSharedFromThis<FFCPXMLNode>`  
_L80-236_
- inherits: `TSharedFromThis<FFCPXMLNode>`
- desc: FCP XML node class. This supports traversal by a visitor object which may modify the node tree's structure.
- L86 _public prototype_ `FFCPXMLNode(const FString InTag, TSharedPtr<FFCPXMLNode> InParent, TSharedPtr<FFCPXMLFile> InFile);` — Constructor
- L89 _public prototype_ `virtual ~FFCPXMLNode() = default;` — Destructor
- L94 _private function_ `FFCPXMLNode()` — No default constructor allowed
- L97 _private function_ `FFCPXMLNode(const FFCPXMLNode& rhs)` — No copy constructor allowed
- L101 _public prototype_ `static TSharedRef<FFCPXMLNode> CreateFFCPXMLNode(FString tag, TSharedPtr<FFCPXMLNode> InParent, TSharedPtr<FFCPXMLFile> InFile);` — Factory method to create new FCPXMLNode based on xml tag.
- L104 _public prototype_ `void CopyFrom(FXmlNode* InNode);` — Recursive copy of data from XmlNode to this node
- L107 _public prototype_ `void GetXmlBuffer(const FString& Indent, FString& Output) const;` — Write data from this node into an Xml string
- L113 _public prototype_ `bool Accept(FFCPXMLNodeVisitor& NodeVisitor);` — Calls the appropriate visit method for a given visitor node. @param	NodeVisitor				Visitor object
- L120 _public prototype_ `bool VisitChildren(FFCPXMLNodeVisitor& NodeVisitor, bool VisitRefNodeChildren = false);` — Visits the children of this node. @param	NodeVisitor				Visitor object @param    VisitRefIdChildren      When true, node will traverse refId node elements if they do not exist in current node
- L125 _public prototype_ `const FString& GetTag() const;` — Gets the tag of the node
- L128 _public prototype_ `const FString& GetContent() const;` — Gets the value of the node
- L130 _public prototype_ `bool GetContent(FString& OutValue) const;` — Gets the value of the node
- L132 _public prototype_ `bool GetContent(float& OutValue) const;` — Gets the value of the node
- L134 _public prototype_ `bool GetContent(int32& OutValue) const;` — Gets the value of the node
- L136 _public prototype_ `bool GetContent(bool& OutValue) const;` — Gets the value of the node
- L139 _public prototype_ `void SetContent(const FString& InContent);` — Sets the new value of the node
- L141 _public prototype_ `void SetContent(float InContent);` — Sets the new value of the node
- L143 _public prototype_ `void SetContent(int32 InContent);` — Sets the new value of the node
- L145 _public prototype_ `void SetContent(bool InContent);` — Sets the new value of the node
- L148 _public function_ `FORCEINLINE void SetContent(const TCHAR* InContent)` — Sets the new value of the node
- L155 _public prototype_ `const TArray<TSharedRef<FFCPXMLNode>>& GetChildNodes() const;` — Gets a list of child nodes
- L157 _public function_ `uint32 GetChildCount()` — Gets number of child nodes
- L160 _public prototype_ `void AppendChildNode(TSharedRef<FFCPXMLNode> InNode);` — Appends input node to children nodes
- L162 _public prototype_ `TSharedRef<FFCPXMLNode> CreateChildNode(const FString& InTag);` — Creates a child node with the given tag and appends node to children.
- L166 _public prototype_ `template <typename T> bool GetChildValue(const FString& InElement, T& OutValue, ENodeInherit CheckInherit = ENodeInherit::CheckInherit, ENodeReference CheckRefIds = ENodeReference::CheckReferences) const;` — Retrieves child content, returning false if not found.
- L170 _public prototype_ `template <typename T> bool GetChildSubValue(const FString& InElement, const FString& InSubElement, T& OutValue, ENodeInherit CheckInherit = ENodeInherit::CheckInherit, ENodeReference CheckRefIds = ENodeReference::CheckReferences) const;` — Retrieves child content, returning false if not found.
- L173 _public prototype_ `TSharedPtr<FFCPXMLNode> GetChildNode(const FString& InElement, ENodeInherit CheckInherit = ENodeInherit::CheckInherit, ENodeReference CheckRefIds = ENodeReference::CheckReferences) const;` — Retrieves child node, checking references and inheritance if specified.
- L176 _public prototype_ `TSharedPtr<FFCPXMLNode> GetChildNode(const FString& InElement, const FString& InSubElement, ENodeInherit CheckInherit = ENodeInherit::CheckInherit, ENodeReference CheckRefIds = ENodeReference::CheckReferences) const;` — Retrieves child node, checking references and inheritance if specified.
- L179 _public prototype_ `void AddAttribute(const FString &InTag, const FString &InValue);` — Adds an attribute
- L185 _public prototype_ `const TArray<FFCPXMLAttribute>& GetAttributes() const;` — Gets all of the attributes in this node @return	List of attributes in this node
- L188 _public prototype_ `bool GetAttribute(const FString& InTag, FFCPXMLAttribute& OutAttr) const;` — Gets an attribute that corresponds with the passed-in tag
- L192 _public prototype_ `template <typename T> bool GetAttributeValue(const FString& InTag, T& OutValue) const;` — Retrieves attribute value, returning false if not found.
- L196 _public prototype_ `bool AddReference(const FString& InElement, const FString &InId, TSharedPtr<FFCPXMLNode> InNode);` — Adds reference to file's reference map if it does not already exist
- L199 _public prototype_ `TSharedPtr<FFCPXMLNode> GetReference(const FString &InElement, const FString &InId) const;` — Gets reference from file's reference map
- L204 _protected member_ `TArray<TSharedRef<FFCPXMLNode>> Children;` — The list of children nodes
- L206 _protected member_ `TArray<FFCPXMLAttribute> Attributes;` — Attributes of this node
- L208 _protected member_ `TWeakPtr<FFCPXMLNode> Parent;` — Weak pointer to parent node
- L210 _protected member_ `TWeakPtr<FFCPXMLFile> ContainingFile;` — Weak pointer to file object
- L212 _protected member_ `FString Tag;` — Tag of the node
- L214 _protected member_ `FString Content;` — Content of the node
- L219 _private prototype_ `TSharedPtr<FFCPXMLNode> GetChildNodeOnly(const FString& InElement) const;` — Retrieves child node without checking references and inheritance.
- L221 _private prototype_ `TSharedPtr<FFCPXMLNode> GetChildNodeOnly(const FString& InElement, const FString& InSubElement) const;` — Retrieves child node without checking references and inheritance.
- L223 _private prototype_ `TSharedPtr<FFCPXMLNode> GetChildNodeReference(const FString& InElement) const;` — Retrieves child node from a reference, if it exists.
- L225 _private prototype_ `TSharedPtr<FFCPXMLNode> GetChildNodeReference(const FString& InElement, const FString& InSubElement) const;` — Retrieves child node from a reference, if it exists.
- L227 _private prototype_ `TSharedPtr<FFCPXMLNode> GetChildNodeInherit(const FString& InElement) const;` — Retrieves child node via inheritance, if it exists.
- L229 _private prototype_ `TSharedPtr<FFCPXMLNode> GetChildNodeInherit(const FString& InElement, const FString& InSubElement) const;` — Retrieves child node via inheritance, if it exists.
- L232 _private prototype_ `TSharedPtr<FFCPXMLNode> GetReferenceNode() const;` — Retrieves corresponding reference node, if it exists.
- L235 _private prototype_ `virtual bool DoAccept(FFCPXMLNodeVisitor& NodeVisitor) = 0;` — Pure virtual method that accepts a visitor to visit this node
- L240 _function_ `template <typename T> bool FFCPXMLNode::GetChildValue(const FString& InElement, T& OutValue, ENodeInherit CheckInherit, ENodeReference CheckRefIds) const` — Retrieves child value, returning false if not found.
- L253 _function_ `template <typename T> bool FFCPXMLNode::GetChildSubValue(const FString& InElement, const FString& InSubElement, T& OutValue, ENodeInherit CheckInherit, ENodeReference CheckRefIds) const` — Retrieves child value, returning false if not found.
- L265 _function_ `template <typename T> bool FFCPXMLNode::GetAttributeValue(const FString& InTag, T& OutValue) const`

#### class `FFCPXMLBasicNode`  
`class FFCPXMLBasicNode : public FFCPXMLNode`  
_L278-287_
- inherits: `FFCPXMLNode`
- desc: FCP XML Node class for any node type
- L282 _public prototype_ `FFCPXMLBasicNode(FString InTag, TSharedPtr<FFCPXMLNode> InParent, TSharedPtr<FFCPXMLFile> InFile);` — Constructor
- L286 _private prototype_ `virtual bool DoAccept(FFCPXMLNodeVisitor& NodeVisitor) override final;` — Accepts a node visitor object

#### class `FFCPXMLXmemlNode`  
`class FFCPXMLXmemlNode : public FFCPXMLNode`  
_L290-299_
- inherits: `FFCPXMLNode`
- desc: FCP XML Node class for the xmeml node which is the root of every XML file
- L294 _public prototype_ `FFCPXMLXmemlNode(TSharedPtr<FFCPXMLNode> InParent, TSharedPtr<FFCPXMLFile> InFile);` — Constructor
- L298 _private prototype_ `virtual bool DoAccept(FFCPXMLNodeVisitor& NodeVisitor) override final;` — Accepts a node visitor object

#### class `FFCPXMLSequenceNode`  
`class FFCPXMLSequenceNode : public FFCPXMLNode`  
_L302-311_
- inherits: `FFCPXMLNode`
- desc: FCP XML Node class for sequence nodes
- L306 _public prototype_ `FFCPXMLSequenceNode(TSharedPtr<FFCPXMLNode> InParent, TSharedPtr<FFCPXMLFile> InFile);` — Constructor
- L310 _private prototype_ `virtual bool DoAccept(FFCPXMLNodeVisitor& NodeVisitor) override final;` — Accepts a node visitor object

#### class `FFCPXMLVideoNode`  
`class FFCPXMLVideoNode : public FFCPXMLNode`  
_L314-323_
- inherits: `FFCPXMLNode`
- desc: FCP XML Node class for video nodes
- L318 _public prototype_ `FFCPXMLVideoNode(TSharedPtr<FFCPXMLNode> InParent, TSharedPtr<FFCPXMLFile> InFile);` — Constructor
- L322 _private prototype_ `virtual bool DoAccept(FFCPXMLNodeVisitor& NodeVisitor) override final;` — Accepts a node visitor object

#### class `FFCPXMLAudioNode`  
`class FFCPXMLAudioNode : public FFCPXMLNode`  
_L326-335_
- inherits: `FFCPXMLNode`
- desc: FCP XML Node class for audio nodes
- L330 _public prototype_ `FFCPXMLAudioNode(TSharedPtr<FFCPXMLNode> InParent, TSharedPtr<FFCPXMLFile> InFile);` — Constructor
- L334 _private prototype_ `virtual bool DoAccept(FFCPXMLNodeVisitor& NodeVisitor) override final;` — Accepts a node visitor object

#### class `FFCPXMLTrackNode`  
`class FFCPXMLTrackNode : public FFCPXMLNode`  
_L338-347_
- inherits: `FFCPXMLNode`
- desc: FCP XML Node class for track nodes
- L342 _public prototype_ `FFCPXMLTrackNode(TSharedPtr<FFCPXMLNode> InParent, TSharedPtr<FFCPXMLFile> InFile);` — Constructor
- L346 _private prototype_ `virtual bool DoAccept(FFCPXMLNodeVisitor& NodeVisitor) override final;` — Accepts a node visitor object

#### class `FFCPXMLClipNode`  
`class FFCPXMLClipNode : public FFCPXMLNode`  
_L350-359_
- inherits: `FFCPXMLNode`
- desc: FCP XML Node class for clip nodes
- L354 _public prototype_ `FFCPXMLClipNode(TSharedPtr<FFCPXMLNode> InParent, TSharedPtr<FFCPXMLFile> InFile);` — Constructor
- L358 _private prototype_ `virtual bool DoAccept(FFCPXMLNodeVisitor& NodeVisitor) override final;` — Accepts a node visitor object

#### class `FFCPXMLClipItemNode`  
`class FFCPXMLClipItemNode : public FFCPXMLNode`  
_L362-371_
- inherits: `FFCPXMLNode`
- desc: FCP XML Node class for clipitem nodes
- L366 _public prototype_ `FFCPXMLClipItemNode(TSharedPtr<FFCPXMLNode> InParent, TSharedPtr<FFCPXMLFile> InFile);` — Constructor
- L370 _private prototype_ `virtual bool DoAccept(FFCPXMLNodeVisitor& NodeVisitor) override final;` — Accepts a node visitor object

#### class `FFCPXMLFileNode`  
`class FFCPXMLFileNode : public FFCPXMLNode`  
_L374-383_
- inherits: `FFCPXMLNode`
- desc: FCP XML Node class for file nodes
- L378 _public prototype_ `FFCPXMLFileNode(TSharedPtr<FFCPXMLNode> InParent, TSharedPtr<FFCPXMLFile> InFile);` — Constructor
- L382 _private prototype_ `virtual bool DoAccept(FFCPXMLNodeVisitor& NodeVisitor) override final;` — Accepts a node visitor object

#### class `FFCPXMLNodeVisitor`  
`class FFCPXMLNodeVisitor`  
_L390-417_
- desc: FCP XML node visitor abstract base class. This must contain a method for every node type that will be visiting the object. These inherited visitors can then be used to traverse the FCP XML node structure.
- L394 _public function_ `FFCPXMLNodeVisitor()` — Constructor
- L396 _public prototype_ `virtual ~FFCPXMLNodeVisitor() = default;` — Destructor
- L400 _public prototype_ `virtual bool VisitNode(TSharedRef<FFCPXMLBasicNode> Node) = 0;` — Visit anonymous node.
- L402 _public prototype_ `virtual bool VisitNode(TSharedRef<FFCPXMLXmemlNode> Node) = 0;` — Visit xmeml node.
- L404 _public prototype_ `virtual bool VisitNode(TSharedRef<FFCPXMLSequenceNode> Node) = 0;` — Visit sequence node.
- L406 _public prototype_ `virtual bool VisitNode(TSharedRef<FFCPXMLVideoNode> Node) = 0;` — Visit video node.
- L408 _public prototype_ `virtual bool VisitNode(TSharedRef<FFCPXMLAudioNode> Node) = 0;` — Visit audio node.
- L410 _public prototype_ `virtual bool VisitNode(TSharedRef<FFCPXMLTrackNode> Node) = 0;` — Visit track node.
- L412 _public prototype_ `virtual bool VisitNode(TSharedRef<FFCPXMLClipNode> Node) = 0;` — Visit clip node.
- L414 _public prototype_ `virtual bool VisitNode(TSharedRef<FFCPXMLClipItemNode> Node) = 0;` — Visit clip item node.
- L416 _public prototype_ `virtual bool VisitNode(TSharedRef<FFCPXMLFileNode> Node) = 0;` — Visit file node.

### `Source/Editor/MovieSceneTools/Private/MVVM/ViewModels/CameraCutTrackModel.h` (Private)


#### class `UE::Sequencer::FCameraCutTrackModel`  
`class FCameraCutTrackModel : public FTrackModel`  
_L21-33_
- inherits: `FTrackModel`
- L28 _public prototype_ `static TSharedPtr<FTrackModel> CreateTrackModel(UMovieSceneTrack* Track);`
- L30 _public prototype_ `explicit FCameraCutTrackModel(UMovieSceneCameraCutTrack* Track);`
- L32 _public prototype_ `FSortingKey GetSortingKey() const override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MOVIESCENETOOLS_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Sequencer` (scope `UE`)
- L16 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Sequencer` (scope `UE`)

### `Source/Editor/MovieSceneTools/Private/MVVM/ViewModels/CinematicShotTrackModel.h` (Private)


#### class `UE::Sequencer::FCinematicShotTrackModel`  
`class FCinematicShotTrackModel : public FTrackModel`  
_L21-33_
- inherits: `FTrackModel`
- L28 _public prototype_ `static TSharedPtr<FTrackModel> CreateTrackModel(UMovieSceneTrack* Track);`
- L30 _public prototype_ `explicit FCinematicShotTrackModel(UMovieSceneCinematicShotTrack* Track);`
- L32 _public prototype_ `FSortingKey GetSortingKey() const override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MOVIESCENETOOLS_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Sequencer` (scope `UE`)
- L16 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Sequencer` (scope `UE`)

### `Source/Editor/MovieSceneTools/Private/MVVM/ViewModels/ScalingAnchorsModel.h` (Private)


#### class `UE::Sequencer::FScalingAnchorsModel`  
`class FScalingAnchorsModel : public FViewModel , public IObjectModelExtension , public ITrackAreaViewSpaceProviderExtension`  
_L22-48_
- inherits: `FViewModel,IObjectModelExtension,ITrackAreaViewSpaceProviderExtension`
- L32 _public prototype_ `virtual void InitializeObject(TWeakObjectPtr<> InWeakObject) override;` — ~ Begin IObjectModelExtension
- L33 _public prototype_ `virtual UObject* GetObject() const override;`
- L37 _public prototype_ `virtual void UpdateViewSpaces(FTrackAreaViewModel& TrackAreaViewModel) override;` — ~ Begin ITrackAreaViewSpaceProviderExtension
- L42 _private prototype_ `void ExtendSectionMenu(UToolMenu* InMenu);`
- L43 _private prototype_ `void CreateScalingGroup(TWeakPtr<ISequencer> InWeakSequencer);`
- L47 _private member_ `TWeakObjectPtr<UMovieSceneScalingAnchors> WeakAnchors;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MOVIESCENETOOLS_API`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Sequencer` (scope `UE`)

### `Source/Editor/MovieSceneTools/Private/MVVM/ViewModels/TimeWarpChannelModel.h` (Private)


#### struct `UE::Sequencer::FTimeWarpChannelModel`  
`struct FTimeWarpChannelModel : FChannelModel`  
_L19-34_
- inherits: `FChannelModel`
- L21 _public prototype_ `UE_SEQUENCER_DECLARE_CASTABLE(FTimeWarpChannelModel, FChannelModel);`
- L23 _public prototype_ `FTimeWarpChannelModel(FName InChannelName, TWeakPtr<ISequencerSection> InSection, FMovieSceneChannelHandle InChannel);`
- L26 _public prototype_ `TSharedPtr<SWidget> CreateOutlinerViewForColumn(const FCreateOutlinerViewParams& InParams, const FName& InColumnName) override;` — ~ Begin FChannelModel API
- L27 _public prototype_ `void BuildContextMenu(FMenuBuilder& MenuBuilder, TViewModelPtr<FChannelGroupOutlinerModel> GroupOwner) override;`
- L32 _private prototype_ `TSharedRef<SWidget> BuildReplaceTimeWarpSubMenu();`
- L33 _private prototype_ `void PopulateReplaceTimeWarpSubMenu(FMenuBuilder& MenuBuilder);`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Sequencer` (scope `UE`)

### `Source/Editor/MovieSceneTools/Private/MovieSceneAlphaBlendOptionCustomization.h` (Private)


#### class `FAlphaBlendPropertyCustomization`  
`class FAlphaBlendPropertyCustomization : public IPropertyTypeCustomization`  
_L13-31_
- inherits: `IPropertyTypeCustomization`
- L16 _public prototype_ `virtual ~FAlphaBlendPropertyCustomization() = default;`
- L18 _public function_ `void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override final`
- L19 _public prototype_ `void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L21 _public prototype_ `void SetAlphaBlendOption(const EAlphaBlendOption NewBlendOption);`
- L22 _public prototype_ `EAlphaBlendOption GetAlphaBlendOption() const;`
- L25 _private prototype_ `void SetType(EMovieSceneBuiltInEasing NewType);`
- L26 _private prototype_ `EMovieSceneBuiltInEasing ConvertToEasingType(EAlphaBlendOption In) const;`
- L27 _private prototype_ `EAlphaBlendOption ConvertFromEasingType(EMovieSceneBuiltInEasing In) const;`
- L29 _private member_ `TSharedPtr<IPropertyHandle> TypeProperty;`
- L30 _private member_ `TSharedPtr<SBuiltInFunctionVisualizerWithText> ButtonContent;`

### `Source/Editor/MovieSceneTools/Private/MovieSceneBuiltInEasingFunctionCustomization.h` (Private)


#### class `FMovieSceneBuiltInEasingFunctionCustomization`  
`class FMovieSceneBuiltInEasingFunctionCustomization : public IDetailCustomization`  
_L19-28_
- inherits: `IDetailCustomization`
- L22 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L24 _public prototype_ `void SetType(EMovieSceneBuiltInEasing NewType);`
- L27 _private member_ `TSharedPtr<IPropertyHandle> TypeProperty;`

#### class `SBuiltInFunctionVisualizerWithText`  
`class SBuiltInFunctionVisualizerWithText : public SCompoundWidget`  
_L31-43_
- inherits: `SCompoundWidget`
- desc: Widget showing the curve graph, and the curve name below it
- L34 _public function_ `SLATE_BEGIN_ARGS(SBuiltInFunctionVisualizerWithText)`
- L35 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, EMovieSceneBuiltInEasing InValue);`
- L38 _public prototype_ `void SetType(EMovieSceneBuiltInEasing InValue);`
- L41 _private member_ `TSharedPtr<SBuiltInFunctionVisualizer> FunctionVisualizer;`
- L42 _private member_ `TSharedPtr<STextBlock> FunctionName;`

### `Source/Editor/MovieSceneTools/Private/MovieSceneBuiltInEasingFunctionGridWidget.h` (Private)


#### class `SEasingFunctionGridWidget`  
`class SEasingFunctionGridWidget : public SCompoundWidget`  
_L23-50_
- inherits: `SCompoundWidget`
- desc: Widget showing a grid of curves including their names. Curves are grouped within rows, e.g. Exponential in, out, in-out in one row. A filter can be used to exclude several curves from the grid.
- L26 _public function_ `SLATE_BEGIN_ARGS(SEasingFunctionGridWidget)`
- L29 _public prototype_ `SLATE_ATTRIBUTE(TSet<EMovieSceneBuiltInEasing>, FilterExclude) SLATE_EVENT(FEasingFunctionGridWidget_OnClicked, OnTypeChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — The easing curve filter containing all curve types that should be excluded.In case the filter is empty, all curve types will be shown.
- L43 _private prototype_ `FGroup& FindOrAddGroup(TArray<FGroup>& Groups, const FString& GroupName);`
- L44 _private prototype_ `TArray<FGroup> ConstructGroups(const TSet<EMovieSceneBuiltInEasing>& FilterExclude);`
- L46 _private prototype_ `FReply OnTypeButtonClicked(EMovieSceneBuiltInEasing type);`
- L48 _private member_ `FEasingFunctionGridWidget_OnClicked OnClickedDelegate;`
- L49 _private member_ `TAttribute<TSet<EMovieSceneBuiltInEasing>> FilterExcludeAttribute;`

#### struct `SEasingFunctionGridWidget::FGroup`  
`struct FGroup`  
_L37-41_
- L39 _public member_ `FString GroupName;`
- L40 _public member_ `TArray<EMovieSceneBuiltInEasing, TInlineAllocator<3>> Values;`

#### Free symbols / members of external scopes

- L17 _delegate_ `DECLARE_DELEGATE_OneParam(FEasingFunctionGridWidget_OnClicked, EMovieSceneBuiltInEasing);`
- L17 _prototype_ `DECLARE_DELEGATE_OneParam(FEasingFunctionGridWidget_OnClicked, EMovieSceneBuiltInEasing);`

### `Source/Editor/MovieSceneTools/Private/MovieSceneBuiltInEasingFunctionVisualizer.h` (Private)


#### class `SBuiltInFunctionVisualizer`  
`class SBuiltInFunctionVisualizer : public SCompoundWidget`  
_L18-46_
- inherits: `SCompoundWidget`
- desc: Widget showing the curve graph
- L21 _public function_ `SLATE_BEGIN_ARGS(SBuiltInFunctionVisualizer)`
- L22 _public prototype_ `SLATE_END_ARGS();`
- L24 _public prototype_ `virtual ~SBuiltInFunctionVisualizer() = default;`
- L26 _public prototype_ `void Construct(const FArguments& InArgs, EMovieSceneBuiltInEasing InValue);`
- L28 _public prototype_ `void SetType(EMovieSceneBuiltInEasing InValue);`
- L29 _public function_ `void SetAnimationDuration(float TimeInSeconds)`
- L32 _private prototype_ `void OnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override final;`
- L33 _private prototype_ `void OnMouseLeave(const FPointerEvent& MouseEvent) override final;`
- L35 _private prototype_ `EActiveTimerReturnType TickInterp(const double InCurrentTime, const float InDeltaTime);`
- L37 _private prototype_ `int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyClippingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const;`
- L39 _private member_ `TSharedPtr<FActiveTimerHandle> TimerHandle;`
- L40 _private member_ `double MouseOverTime;`
- L41 _private member_ `EMovieSceneBuiltInEasing EasingType;`
- L43 _private member_ `FVector2D InterpValue;`
- L44 _private member_ `TArray<FVector2D> Samples;`
- L45 _private member_ `float AnimationDuration = 0.5f;`

### `Source/Editor/MovieSceneTools/Private/MovieSceneCVarOverridesPropertyTypeCustomization.h` (Private)


#### struct `UE::MovieScene::FCVarOverridesPropertyTypeCustomization`  
`struct FCVarOverridesPropertyTypeCustomization : public IPropertyTypeCustomization`  
_L19-33_
- inherits: `IPropertyTypeCustomization`
- L21 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L23 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L24 _public function_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override`
- L28 _private prototype_ `void OnCVarsCommitted(const FText& NewText, ETextCommit::Type);`
- L29 _private prototype_ `void OnCVarsChanged(const FText& NewText);`
- L30 _private prototype_ `FText GetCVarText() const;`
- L32 _private member_ `TSharedPtr<IPropertyHandle> PropertyHandle;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L16 _namespace_ `namespace MovieScene` (scope `UE`)

### `Source/Editor/MovieSceneTools/Private/MovieSceneDynamicBindingBlueprintExtension.h` (Private)


#### class `UMovieSceneDynamicBindingBlueprintExtension`  
`class UMovieSceneDynamicBindingBlueprintExtension : public UBlueprintExtension`  
_L23-54_
- reflection: `UCLASS()`
- inherits: `UBlueprintExtension`
- desc: An extension for a sequence's director blueprint to compile dynamic binding endpoints.
- L33 _public prototype_ `void BindTo(TWeakObjectPtr<UMovieSceneSequence> InMovieSceneSequence);` — Bind this extension to the given sequence. This may be called multiple times, but the extension must only be bound to one sequence.
- L37 _private prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L38 _private prototype_ `virtual void PostLoad() override;`
- L40 _private prototype_ `virtual void HandlePreloadObjectsForCompilation(UBlueprint* OwningBlueprint) override final;`
- L41 _private prototype_ `virtual void HandleGenerateFunctionGraphs(FKismetCompilerContext* CompilerContext) override final;`
- L43 _private prototype_ `void HandleGenerateFunctionGraphs(FKismetCompilerContext* CompilerContext, UMovieSceneSequence* MovieSceneSequence);`
- L49 _private member_ `TArray<TWeakObjectPtr<UMovieSceneSequence>> WeakMovieSceneSequences;` — `UPROPERTY()` — List of movie scenes that are bound to the director blueprint
- L53 _private member_ `TWeakObjectPtr<UMovieSceneSequence> WeakMovieSceneSequence_DEPRECATED;` — `UPROPERTY()` — The movie scene that is bound to the director blueprint

### `Source/Editor/MovieSceneTools/Private/MovieSceneEventBlueprintExtension.h` (Private)


#### class `UMovieSceneEventBlueprintExtension`  
`class UMovieSceneEventBlueprintExtension : public UBlueprintExtension`  
_L19-39_
- reflection: `UCLASS()`
- inherits: `UBlueprintExtension`
- L25 _public function_ `void Add(TWeakObjectPtr<UMovieSceneEventSectionBase> EventSection)`
- L32 _private prototype_ `virtual void PostLoad() override final;`
- L33 _private prototype_ `virtual void HandlePreloadObjectsForCompilation(UBlueprint* OwningBlueprint) override final;`
- L34 _private prototype_ `virtual void HandleGenerateFunctionGraphs(FKismetCompilerContext* CompilerContext) override final;`
- L38 _private member_ `TArray<TWeakObjectPtr<UMovieSceneEventSectionBase>> EventSections;` — `UPROPERTY()` — List of event sections that are bound to the blueprint

### `Source/Editor/MovieSceneTools/Private/MovieSceneTimeWarpVariantCustomization.h` (Private)


#### class `UE::MovieScene::FMovieSceneTimeWarpVariantCustomization`  
`class FMovieSceneTimeWarpVariantCustomization : public IPropertyTypeCustomization`  
_L17-44_
- inherits: `IPropertyTypeCustomization`
- L21 _public prototype_ `void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L22 _public prototype_ `void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L26 _private prototype_ `bool IsFixed() const;`
- L27 _private prototype_ `void SetFixed();`
- L29 _private prototype_ `void SetFixedPlayRate(double InValue);`
- L30 _private prototype_ `void OnCommitFixedPlayRate(double InValue, ETextCommit::Type Type = ETextCommit::Default);`
- L31 _private prototype_ `double GetFixedPlayRate() const;`
- L33 _private prototype_ `FText GetTypeComboLabel() const;`
- L35 _private prototype_ `EVisibility GetFixedVisibility() const;`
- L37 _private prototype_ `TSharedRef<SWidget> BuildTypePickerMenu();`
- L39 _private prototype_ `void ChangeClassType(UClass* InClass);`
- L41 _private member_ `TSharedPtr<IPropertyHandle> PropertyHandle;`
- L42 _private member_ `TOptional<UClass*> Class;`
- L43 _private member_ `bool bIsFixed = true;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace MovieScene` (scope `UE`)

### `Source/Editor/MovieSceneTools/Private/MovieSceneToolsProjectSettingsCustomization.h` (Private)


#### class `FMovieSceneToolsProjectSettingsCustomization`  
`class FMovieSceneToolsProjectSettingsCustomization : public IDetailCustomization`  
_L10-18_
- inherits: `IDetailCustomization`
- L13 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L14 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L17 _private prototype_ `void OnTakeSeparatorUpdated();`

### `Source/Editor/MovieSceneTools/Private/SComponentChooser.h` (Private)


#### class `SComponentChooserPopup`  
`class SComponentChooserPopup : public SCompoundWidget`  
_L26-119_
- inherits: `SCompoundWidget`
- L29 _public prototype_ `DECLARE_DELEGATE_OneParam( FOnComponentChosen, FName );`
- L31 _public function_ `SLATE_BEGIN_ARGS( SComponentChooserPopup ) : _Actor(NULL)`
- L36 _public prototype_ `SLATE_ARGUMENT( AActor*, Actor ) SLATE_EVENT( FOnComponentChosen, OnComponentChosen ) SLATE_END_ARGS() FOnComponentChosen OnComponentChosen;` — An actor with components
- L47 _public member_ `TArray< TSharedPtr<FName> > ComponentNames;` — List of tag names selected in the tag containers
- L50 _private function_ `TSharedRef<ITableRow> MakeListViewWidget(TSharedPtr<FName> InItem, const TSharedRef<STableViewBase>& OwnerTable)`
- L58 _private function_ `void OnComponentSelected(TSharedPtr<FName> InItem, ESelectInfo::Type InSelectInfo)`
- L69 _public function_ `void Construct( const FArguments& InArgs )`

#### Free symbols / members of external scopes

- L29 _delegate_ `DECLARE_DELEGATE_OneParam( FOnComponentChosen, FName );`

### `Source/Editor/MovieSceneTools/Private/Sections/BindingLifetimeSection.h` (Private)


#### class `FBindingLifetimeSection`  
`class FBindingLifetimeSection : public FSequencerSection`  
_L10-28_
- inherits: `FSequencerSection`
- L15 _public function_ `FBindingLifetimeSection(UMovieSceneSection& InSectionObject, TWeakPtr<ISequencer> InSequencer) : FSequencerSection(InSectionObject) , Sequencer(InSequencer)`
- L22 _protected prototype_ `bool IsSectionSelected() const;`
- L23 _protected prototype_ `virtual int32 OnPaintSection(FSequencerSectionPainter& Painter) const override;`
- L27 _protected member_ `TWeakPtr<ISequencer> Sequencer;`

### `Source/Editor/MovieSceneTools/Private/Sections/CameraCutSection.h` (Private)


#### class `FCameraCutSection`  
`class FCameraCutSection : public FViewportThumbnailSection`  
_L17-57_
- inherits: `FViewportThumbnailSection`
- desc: CameraCut section, which paints and ticks the appropriate section.
- L23 _public prototype_ `FCameraCutSection(TSharedPtr<ISequencer> InSequencer, TSharedPtr<FTrackEditorThumbnailPool> InThumbnailPool, UMovieSceneSection& InSection);` — Create and initialize a new instance.
- L26 _public prototype_ `virtual ~FCameraCutSection();` — Virtual destructor.
- L31 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const FGeometry& ClippedGeometry, const double InCurrentTime, const float InDeltaTime) override;` — ISequencerSection interface
- L32 _public prototype_ `virtual void BuildSectionContextMenu(FMenuBuilder& MenuBuilder, const FGuid& ObjectBinding) override;`
- L33 _public prototype_ `virtual FText GetSectionTitle() const override;`
- L34 _public prototype_ `virtual float GetSectionHeight(const UE::Sequencer::FViewDensityInfo& ViewDensity) const override;`
- L35 _public prototype_ `virtual int32 OnPaintSection(FSequencerSectionPainter& InPainter) const override;`
- L36 _public prototype_ `virtual FMargin GetContentPadding() const override;`
- L39 _public prototype_ `virtual void SetSingleTime(double GlobalTime) override;`
- L40 _public prototype_ `virtual FText HandleThumbnailTextBlockText() const override;`
- L41 _public prototype_ `virtual UCameraComponent* GetViewCamera() override;`
- L46 _private prototype_ `AActor* GetCameraForFrame(FFrameNumber Time) const;` — Get a representative camera for the given time
- L49 _private prototype_ `void HandleSelectCameraMenuEntryExecute(AActor* InCamera);` — Callback for executing a "Select Camera" menu entry in the context menu.
- L52 _private prototype_ `bool CanSelectCameraActor(AActor* InCamera) const;` — Callback for determining if the specified camera can actually be selected in the World.
- L56 _private prototype_ `void HandleSetCameraMenuEntryExecute(AActor* InCamera);` — Callback for executing a "Set Camera" menu entry in the context menu.

### `Source/Editor/MovieSceneTools/Private/Sections/CinematicShotSection.h` (Private)


#### class `FCinematicShotSection`  
`class FCinematicShotSection : public TSubSectionMixin<FViewportThumbnailSection>`  
_L20-75_
- inherits: `TSubSectionMixin<FViewportThumbnailSection>`
- desc: CinematicShot section, which paints and ticks the appropriate section.
- L26 _public prototype_ `FCinematicShotSection(TSharedPtr<ISequencer> InSequencer, UMovieSceneCinematicShotSection& InSection, TSharedPtr<FCinematicShotTrackEditor> InCinematicShotTrackEditor, TSharedPtr<FTrackEditorThumbnailPool> InThumbnailPool);` — Create and initialize a new instance.
- L29 _public prototype_ `virtual ~FCinematicShotSection();` — Virtual destructor.
- L35 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const FGeometry& ClippedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L36 _public prototype_ `virtual int32 OnPaintSection( FSequencerSectionPainter& Painter ) const override;`
- L37 _public prototype_ `virtual void BuildSectionContextMenu(FMenuBuilder& MenuBuilder, const FGuid& ObjectBinding) override;`
- L38 _public prototype_ `virtual void BuildSectionSidebarMenu(FMenuBuilder& MenuBuilder, const FGuid& ObjectBinding) override;`
- L39 _public prototype_ `virtual FText GetSectionTitle() const override;`
- L40 _public prototype_ `virtual float GetSectionHeight(const UE::Sequencer::FViewDensityInfo& ViewDensity) const override;`
- L41 _public prototype_ `virtual FMargin GetContentPadding() const override;`
- L42 _public prototype_ `virtual bool IsReadOnly() const override;`
- L45 _public prototype_ `virtual void SetSingleTime(double GlobalTime) override;` — FThumbnail interface
- L46 _public function_ `virtual bool CanRename() const override`
- L47 _public prototype_ `virtual FText HandleThumbnailTextBlockText() const override;`
- L48 _public prototype_ `virtual void HandleThumbnailTextBlockTextCommitted(const FText& NewThumbnailName, ETextCommit::Type CommitType) override;`
- L49 _public prototype_ `virtual UCameraComponent* GetViewCamera() override;`
- L53 _private prototype_ `void AddShotMenuSection(FMenuBuilder& MenuBuilder, const FGuid& ObjectBinding);`
- L56 _private member_ `TWeakPtr<FCinematicShotTrackEditor> CinematicShotTrackEditor;` — The cinematic shot track editor that contains this section
- L74 _private member_ `FCinematicSectionCache ThumbnailCacheData;` — Cached section thumbnail data

#### struct `FCinematicShotSection::FCinematicSectionCache`  
`struct FCinematicSectionCache`  
_L58-71_
- L60 _public prototype_ `FCinematicSectionCache(UMovieSceneCinematicShotSection* Section = nullptr);`
- L62 _public function_ `bool operator!=(const FCinematicSectionCache& RHS) const`
- L67 _public member_ `FFrameRate InnerFrameRate;`
- L68 _public member_ `FFrameNumber InnerFrameOffset;`
- L69 _public member_ `FFrameNumber SectionStartFrame;`
- L70 _public member_ `FMovieSceneTimeWarpVariant TimeScale;`

### `Source/Editor/MovieSceneTools/Private/Sections/ComponentMaterialParameterSection.h` (Private)


#### class `FComponentMaterialParameterSection`  
`class FComponentMaterialParameterSection : public FSequencerSection`  
_L19-42_
- inherits: `FSequencerSection`
- desc: A movie scene section for material parameters.
- L24 _public function_ `FComponentMaterialParameterSection(UMovieSceneSection& InSectionObject, TWeakPtr<ISequencer> InSequencer) : FSequencerSection(InSectionObject) , WeakSequencer(InSequencer)`
- L32 _public prototype_ `virtual FReply OnKeyDoubleClicked(const TArray<FKeyHandle>& KeyHandles) override;`
- L33 _public prototype_ `virtual bool RequestDeleteCategory(const TArray<FName>& CategoryNamePath) override;`
- L34 _public prototype_ `virtual bool RequestDeleteKeyArea(const TArray<FName>& KeyAreaNamePath) override;`
- L36 _public prototype_ `virtual TSharedPtr<UE::Sequencer::FCategoryModel> ConstructCategoryModel(FName InCategoryName, const FText& InDisplayText, TArrayView<const FChannelData> Channels) const;`
- L41 _private member_ `TWeakPtr<ISequencer> WeakSequencer;` — Weak pointer to the sequencer this section is for

### `Source/Editor/MovieSceneTools/Private/Sections/EventSection.h` (Private)


#### class `FEventSectionBase`  
`class FEventSectionBase : public FSequencerSection`  
_L10-29_
- inherits: `FSequencerSection`
- L15 _public function_ `FEventSectionBase(UMovieSceneSection& InSectionObject, TWeakPtr<ISequencer> InSequencer) : FSequencerSection(InSectionObject) , Sequencer(InSequencer)`
- L22 _protected prototype_ `void PaintEventName(FSequencerSectionPainter& Painter, int32 LayerId, const FString& EventString, float PixelPosition, bool bIsEventValid = true) const;`
- L24 _protected prototype_ `bool IsSectionSelected() const;`
- L28 _protected member_ `TWeakPtr<ISequencer> Sequencer;`

#### class `FEventSection`  
`class FEventSection : public FEventSectionBase`  
_L34-45_
- inherits: `FEventSectionBase`
- desc: An implementation of event sections.
- L38 _public function_ `FEventSection(UMovieSceneSection& InSectionObject, TWeakPtr<ISequencer> InSequencer) : FEventSectionBase(InSectionObject, InSequencer)`
- L44 _public prototype_ `virtual int32 OnPaintSection(FSequencerSectionPainter& Painter) const override;`

#### class `FEventTriggerSection`  
`class FEventTriggerSection : public FEventSectionBase`  
_L47-60_
- inherits: `FEventSectionBase`
- L52 _public function_ `FEventTriggerSection(UMovieSceneSection& InSectionObject, TWeakPtr<ISequencer> InSequencer) : FEventSectionBase(InSectionObject, InSequencer)`
- L58 _public prototype_ `virtual int32 OnPaintSection(FSequencerSectionPainter& Painter) const override;`
- L59 _public prototype_ `virtual FReply OnKeyDoubleClicked(const TArray<FKeyHandle>& KeyHandles) override;`

#### class `FEventRepeaterSection`  
`class FEventRepeaterSection : public FEventSectionBase`  
_L62-76_
- inherits: `FEventSectionBase`
- L67 _public function_ `FEventRepeaterSection(UMovieSceneSection& InSectionObject, TWeakPtr<ISequencer> InSequencer) : FEventSectionBase(InSectionObject, InSequencer)`
- L74 _public prototype_ `virtual int32 OnPaintSection(FSequencerSectionPainter& Painter) const override;`
- L75 _public prototype_ `virtual FReply OnSectionDoubleClicked(const FGeometry& SectionGeometry, const FPointerEvent& MouseEvent) override;`

### `Source/Editor/MovieSceneTools/Private/Sections/LevelVisibilitySection.h` (Private)


#### class `FLevelVisibilitySection`  
`class FLevelVisibilitySection : public ISequencerSection , public TSharedFromThis<FLevelVisibilitySection>`  
_L23-55_
- inherits: `ISequencerSection,TSharedFromThis<FLevelVisibilitySection>`
- desc: A seqeuencer section for displaying and interacting with level visibility movie scene sections.
- L29 _public prototype_ `FLevelVisibilitySection( UMovieSceneLevelVisibilitySection& InSectionObject );`
- L34 _public prototype_ `virtual UMovieSceneSection* GetSectionObject() override;` — ISequencerSectionInterface
- L35 _public prototype_ `virtual TSharedRef<SWidget> GenerateSectionWidget() override;`
- L36 _public prototype_ `virtual int32 OnPaintSection( FSequencerSectionPainter& InPainter ) const override;`
- L40 _private prototype_ `FSlateColor GetBackgroundColor() const;`
- L41 _private prototype_ `FText GetVisibilityText() const;`
- L42 _private prototype_ `FText GetVisibilityToolTip() const;`
- L44 _private prototype_ `bool OnAllowDrop( TSharedPtr<FDragDropOperation> DragDropOperation );`
- L45 _private prototype_ `FReply OnDrop( const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent );`
- L49 _private member_ `FText VisibleText;`
- L50 _private member_ `FText HiddenText;`
- L52 _private member_ `UMovieSceneLevelVisibilitySection& SectionObject;`
- L54 _private member_ `FText DisplayName;`

### `Source/Editor/MovieSceneTools/Private/Sections/MovieSceneSectionHelpers.h` (Private)


#### class `MovieSceneSectionHelpers`  
`class MovieSceneSectionHelpers`  
_L16-22_
- L21 _public prototype_ `static void ConsolidateColorCurves(TArray< TTuple<float, FLinearColor> >& OutColorKeys, const FLinearColor& DefaultColor, TArrayView<const FMovieSceneFloatChannel* const> ColorChannels, const FTimeToPixel& TimeConverter);` — Consolidate color curves for all track sections.

#### class `FMovieSceneKeyColorPicker`  
`class FMovieSceneKeyColorPicker`  
_L24-40_
- L27 _public prototype_ `FMovieSceneKeyColorPicker(UMovieSceneSection* Section, FMovieSceneFloatChannel* RChannel, FMovieSceneFloatChannel* GChannel, FMovieSceneFloatChannel* BChannel, FMovieSceneFloatChannel* AChannel, const TArray<FKeyHandle>& KeyHandles, TWeakPtr<ISequencer> InSequencer);`
- L31 _private prototype_ `void OnColorPickerPicked(FLinearColor NewColor, UMovieSceneSection* Section, FMovieSceneFloatChannel* RChannel, FMovieSceneFloatChannel* GChannel, FMovieSceneFloatChannel* BChannel, FMovieSceneFloatChannel* AChannel, TWeakPtr<ISequencer> InSequencer);`
- L32 _private prototype_ `void OnColorPickerClosed(const TSharedRef<SWindow>& Window, UMovieSceneSection* Section, FMovieSceneFloatChannel* RChannel, FMovieSceneFloatChannel* GChannel, FMovieSceneFloatChannel* BChannel, FMovieSceneFloatChannel* AChannel, TWeakPtr<ISequencer> InSequencer);`
- L33 _private prototype_ `void OnColorPickerCancelled(FLinearColor NewColor, UMovieSceneSection* Section, FMovieSceneFloatChannel* RChannel, FMovieSceneFloatChannel* GChannel, FMovieSceneFloatChannel* BChannel, FMovieSceneFloatChannel* AChannel, TWeakPtr<ISequencer> InSequencer);`
- L37 _private member_ `static FFrameNumber KeyTime;`
- L38 _private member_ `static FLinearColor InitialColor;`
- L39 _private member_ `static bool bColorPickerWasCancelled;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MOVIESCENETOOLS_API`

### `Source/Editor/MovieSceneTools/Private/Sections/ParameterSection.h` (Private)


#### class `FParameterSection`  
`class FParameterSection : public FSequencerSection`  
_L19-42_
- inherits: `FSequencerSection`
- desc: A movie scene section for generic parameters.
- L24 _public function_ `FParameterSection(UMovieSceneSection& InSectionObject, TWeakPtr<ISequencer> InSequencer) : FSequencerSection(InSectionObject) , WeakSequencer(InSequencer)`
- L32 _public prototype_ `virtual FReply OnKeyDoubleClicked(const TArray<FKeyHandle>& KeyHandles) override;`
- L33 _public prototype_ `virtual bool RequestDeleteCategory(const TArray<FName>& CategoryNamePath) override;`
- L34 _public prototype_ `virtual bool RequestDeleteKeyArea(const TArray<FName>& KeyAreaNamePath) override;`
- L36 _public prototype_ `virtual TSharedPtr<UE::Sequencer::FCategoryModel> ConstructCategoryModel(FName InCategoryName, const FText& InDisplayText, TArrayView<const FChannelData> Channels) const;`
- L41 _private member_ `TWeakPtr<ISequencer> WeakSequencer;` — Weak pointer to the sequencer this section is for

### `Source/Editor/MovieSceneTools/Private/Sections/TransformPropertySection.h` (Private)


#### class `FTransformSection`  
`class FTransformSection : public FSequencerSection`  
_L18-46_
- inherits: `FSequencerSection`
- desc: An implementation of transform property sections.
- L28 _public function_ `FTransformSection(UMovieSceneSection& InSection, TWeakPtr<ISequencer> InSequencer) : FSequencerSection(InSection), WeakSequencer(InSequencer)` — Creates a new transform property section. @param InSection The section object which is being displayed and edited. @param InSequencer The sequencer which is controlling this property section.
- L35 _public prototype_ `virtual void BuildSectionContextMenu(FMenuBuilder& MenuBuilder, const FGuid& InObjectBinding) override;`
- L39 _public prototype_ `virtual bool RequestDeleteCategory(const TArray<FName>& CategoryNamePath) override;`
- L40 _public prototype_ `virtual bool RequestDeleteKeyArea(const TArray<FName>& KeyAreaNamePath) override;`
- L45 _protected member_ `TWeakPtr<ISequencer> WeakSequencer;` — The sequencer which is controlling this section.

### `Source/Editor/MovieSceneTools/Private/TrackEditors/ActorPickerTrackEditor.h` (Private)


#### class `FActorPickerTrackEditor`  
`class FActorPickerTrackEditor : public FMovieSceneTrackEditor`  
_L21-67_
- inherits: `FMovieSceneTrackEditor`
- desc: Track editor actor picker
- L33 _public prototype_ `FActorPickerTrackEditor(TSharedRef<ISequencer> InSequencer);`
- L36 _public prototype_ `virtual FText GetDisplayName() const override;`
- L40 _public function_ `virtual bool IsActorPickable( const AActor* const ParentActor, FGuid ObjectBinding, UMovieSceneSection* InSection)` — Is this actor pickable?
- L43 _public function_ `virtual void ActorSocketPicked(const FName SocketName, USceneComponent* Component, FActorPickerID ActorPickerID, TArray<FGuid> ObjectBinding, UMovieSceneSection* Section)` — Actor socket was picked
- L46 _public prototype_ `void ShowActorSubMenu(FMenuBuilder& MenuBuilder, TArray<FGuid> ObjectBindings, UMovieSceneSection* Section);` — Show a sub menu of the pickable actors
- L51 _private prototype_ `void ActorPicked(AActor* ParentActor, TArray<FGuid> ObjectBinding, UMovieSceneSection* Section);` — Actor was picked
- L54 _private prototype_ `void ExistingBindingPicked(FMovieSceneObjectBindingID ExistingBindingID, TArray<FGuid> ObjectBindings, UMovieSceneSection* Section);` — Existing binding was picked
- L57 _private prototype_ `void ActorPickerIDPicked(FActorPickerID, const TArray<FGuid>& ObjectBindings, UMovieSceneSection* Section);` — Actor and/or existing binding was picked
- L60 _private prototype_ `void ActorComponentPicked(FName ComponentName, FActorPickerID ActorPickerID, TArray<FGuid> ObjectBindings, UMovieSceneSection* Section);` — Actor component was picked
- L63 _private prototype_ `void PickActorInteractive(const TArray<FGuid>& ObjectBindings, UMovieSceneSection* Section);` — Interactively pick an actor from the viewport
- L66 _private member_ `TSharedPtr<FTrackEditorBindingIDPicker> BindingIDPicker;` — A binding ID picker that allows us to create a new section from an existing binding

#### struct `FActorPickerTrackEditor::FActorPickerID`  
`struct FActorPickerID`  
_L25-31_
- L27 _public function_ `FActorPickerID(AActor* InActorPicked, const FMovieSceneObjectBindingID& InExistingBindingID) : ActorPicked(InActorPicked), ExistingBindingID(InExistingBindingID)`
- L29 _public member_ `TWeakObjectPtr<AActor> ActorPicked;`
- L30 _public member_ `FMovieSceneObjectBindingID ExistingBindingID;`

### `Source/Editor/MovieSceneTools/Private/TrackEditors/AttachTrackEditor.h` (Private)


#### enum `ETransformPreserveType`  
`enum class ETransformPreserveType`  
_L29-35_
- L31 _public enumerator_ `CurrentKey`
- L32 _public enumerator_ `AllKeys`
- L33 _public enumerator_ `Bake`
- L34 _public enumerator_ `None`

#### class `F3DAttachTrackEditor`  
`class F3DAttachTrackEditor : public FActorPickerTrackEditor`  
_L40-99_
- inherits: `FActorPickerTrackEditor`
- desc: Tools for attaching an object to another object
- L50 _public prototype_ `F3DAttachTrackEditor( TSharedRef<ISequencer> InSequencer );` — Constructor @param InSequencer The sequencer instance to be used by this tool
- L53 _public prototype_ `virtual ~F3DAttachTrackEditor();` — Virtual destructor.
- L61 _public prototype_ `static TSharedRef<ISequencerTrackEditor> CreateTrackEditor( TSharedRef<ISequencer> OwningSequencer );` — Creates an instance of this class.  Called by a sequencer @param OwningSequencer The sequencer instance to be used by this tool @return The new instance of this class
- L67 _public prototype_ `virtual void BuildObjectBindingTrackMenu(FMenuBuilder& MenuBuilder, const TArray<FGuid>& ObjectBindings, const UClass* ObjectClass) override;`
- L68 _public prototype_ `virtual TSharedRef<ISequencerSection> MakeSectionInterface( UMovieSceneSection& SectionObject, UMovieSceneTrack& Track, FGuid ObjectBinding ) override;`
- L69 _public prototype_ `virtual bool SupportsType( TSubclassOf<UMovieSceneTrack> Type ) const override;`
- L70 _public prototype_ `virtual bool SupportsSequence(UMovieSceneSequence* InSequence) const override;`
- L73 _public prototype_ `virtual bool IsActorPickable( const AActor* const ParentActor, FGuid ObjectBinding, UMovieSceneSection* InSection ) override;` — FTrackEditorActorPicker
- L74 _public prototype_ `virtual void ActorSocketPicked(const FName SocketName, USceneComponent* Component, FActorPickerID ActorPickerID, TArray<FGuid> ObjectBindings, UMovieSceneSection* Section) override;`
- L77 _public prototype_ `void TrimAndPreserve(const FGuid InObjectBinding, UMovieSceneSection* InSection, bool bInTrimLeft);` — Trims an attach track on the left/right and preserves the world space transform immediately before/after attach/detach
- L81 _private prototype_ `void ShowPickerSubMenu(FMenuBuilder& MenuBuilder, TArray<FGuid> ObjectBindings, UMovieSceneSection* Section);`
- L84 _private prototype_ `void FindOrCreateTransformTrack(const TRange<FFrameNumber>& InAttachRange, UMovieScene* InMovieScene, const FGuid& InObjectHandle, UMovieScene3DTransformTrack*& OutTransformTrack, UMovieScene3DTransformSection*& OutTransformSection);` — Helper for AddKeyInternal to get transform tracks for child
- L88 _private prototype_ `template<typename ModifierFuncType> void CompensateChildTrack(const TRange<FFrameNumber>& InAttachRange, TArrayView<FMovieSceneDoubleChannel*> Channels, TOptional<TArrayView<FMovieSceneDoubleChannel*>> ParentChannels, const ITransformEvaluator& InParentTransformEval, const ITransformEvaluator& InChildTransformEval, ETransformPreserveType InPreserveType, ModifierFuncType InModifyTransform);` — Helper for AddKeyInternal to offset child track's keys
- L92 _private prototype_ `FKeyPropertyResult AddKeyInternal(FFrameNumber KeyTime, const TArray<TWeakObjectPtr<UObject>> Objects, const FName SocketName, const FName ComponentName, FActorPickerID ActorPickerID);` — Delegate for AnimatablePropertyChanged in AddKey
- L95 _private member_ `ETransformPreserveType PreserveType;`
- L98 _public member_ `TUniquePtr<UE::MovieScene::FSystemInterrogator> Interrogator;`

### `Source/Editor/MovieSceneTools/Private/TrackEditors/CVarTrackEditor.h` (Private)


#### class `FCVarTrackEditor`  
`class FCVarTrackEditor : public FMovieSceneTrackEditor`  
_L23-63_
- inherits: `FMovieSceneTrackEditor`
- desc: Tools for Console Variable tracks
- L33 _public prototype_ `FCVarTrackEditor(TSharedRef<ISequencer> InSequencer);` — Constructor @param InSequencer The sequencer instance to be used by this tool.
- L36 _public prototype_ `virtual ~FCVarTrackEditor() = default;` — Virtual destructor.
- L44 _public prototype_ `static TSharedRef<ISequencerTrackEditor> CreateTrackEditor(TSharedRef<ISequencer> OwningSequencer);` — Creates an instance of this class.  Called by a sequencer . @param OwningSequencer The sequencer instance to be used by this tool. @return The new instance of this class.
- L50 _public prototype_ `virtual FText GetDisplayName() const override;`
- L51 _public prototype_ `virtual void BuildAddTrackMenu(FMenuBuilder& MenuBuilder) override;`
- L52 _public prototype_ `virtual TSharedPtr<SWidget> BuildOutlinerEditWidget(const FGuid& ObjectBinding, UMovieSceneTrack* Track, const FBuildEditWidgetParams& Params) override;`
- L53 _public prototype_ `virtual TSharedRef<ISequencerSection> MakeSectionInterface(UMovieSceneSection& SectionObject, UMovieSceneTrack& Track, FGuid ObjectBinding) override;`
- L54 _public prototype_ `virtual void OnRelease() override;`
- L55 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneTrack> Type) const override;`
- L56 _public prototype_ `virtual bool SupportsSequence(UMovieSceneSequence* InSequence) const override;`
- L58 _public prototype_ `virtual const FSlateBrush* GetIconBrush() const override;`
- L62 _private prototype_ `void HandleAddCVarTrackMenuEntryExecute();` — Callback for executing the "Add Console Variable Track" menu entry.

#### class `FCVarSection`  
`class FCVarSection : public ISequencerSection , public TSharedFromThis<FCVarSection>`  
_L68-101_
- inherits: `ISequencerSection,TSharedFromThis<FCVarSection>`
- desc: Class for Console Variable sections
- L75 _public prototype_ `FCVarSection(UMovieSceneSection& InSection, TWeakPtr<ISequencer> InSequencer);` — Constructor.
- L78 _public prototype_ `virtual ~FCVarSection();` — Virtual destructor.
- L83 _public prototype_ `virtual UMovieSceneSection* GetSectionObject() override;` — ISequencerSection interface
- L84 _public prototype_ `virtual int32 OnPaintSection( FSequencerSectionPainter& Painter ) const override;`
- L85 _public prototype_ `virtual FText GetSectionTitle() const override;`
- L86 _public prototype_ `virtual FText GetSectionToolTip() const override;`
- L87 _public prototype_ `virtual void BeginResizeSection() override;`
- L88 _public prototype_ `virtual void ResizeSection(ESequencerSectionResizeMode ResizeMode, FFrameNumber ResizeTime) override;`
- L89 _public prototype_ `virtual void BeginSlipSection() override;`
- L90 _public prototype_ `virtual void SlipSection(FFrameNumber SlipTime) override;`
- L91 _public function_ `virtual float GetSectionHeight() const`
- L95 _private prototype_ `FText GetCVarText() const;`
- L98 _private member_ `UMovieSceneSection& Section;` — The section we are visualizing.
- L100 _private member_ `TWeakPtr<ISequencer> Sequencer;`

### `Source/Editor/MovieSceneTools/Private/TrackEditors/CameraCutTrackEditor.h` (Private)


#### class `FCameraCutTrackEditor`  
`class FCameraCutTrackEditor : public FMovieSceneTrackEditor`  
_L29-125_
- inherits: `FMovieSceneTrackEditor`
- desc: Tools for camera cut tracks.
- L39 _public prototype_ `FCameraCutTrackEditor(TSharedRef<ISequencer> InSequencer);` — Constructor @param InSequencer The sequencer instance to be used by this tool.
- L42 _public prototype_ `virtual ~FCameraCutTrackEditor() = default;` — Virtual destructor.
- L50 _public prototype_ `static TSharedRef<ISequencerTrackEditor> CreateTrackEditor(TSharedRef<ISequencer> OwningSequencer);` — Creates an instance of this class.  Called by a sequencer . @param OwningSequencer The sequencer instance to be used by this tool. @return The new instance of this class.
- L56 _public prototype_ `virtual FText GetDisplayName() const override;`
- L57 _public prototype_ `virtual void BindCommands(TSharedRef<FUICommandList> SequencerCommandBindings) override;`
- L58 _public prototype_ `virtual void BuildAddTrackMenu(FMenuBuilder& MenuBuilder) override;`
- L59 _public prototype_ `virtual void BuildTrackContextMenu(FMenuBuilder& MenuBuilder, UMovieSceneTrack* Track) override;`
- L60 _public prototype_ `virtual TSharedPtr<SWidget> BuildOutlinerColumnWidget(const FBuildColumnWidgetParams& Params, const FName& ColumnName) override;`
- L61 _public prototype_ `virtual TSharedRef<ISequencerSection> MakeSectionInterface(UMovieSceneSection& SectionObject, UMovieSceneTrack& Track, FGuid ObjectBinding) override;`
- L62 _public prototype_ `virtual void OnRelease() override;`
- L63 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneTrack> Type) const override;`
- L64 _public prototype_ `virtual bool SupportsSequence(UMovieSceneSequence* InSequence) const override;`
- L65 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L66 _public prototype_ `virtual const FSlateBrush* GetIconBrush() const override;`
- L67 _public prototype_ `virtual bool OnAllowDrop(const FDragDropEvent& DragDropEvent, FSequencerDragDropParams& DragDropParams) override;`
- L68 _public prototype_ `virtual FReply OnDrop(const FDragDropEvent& DragDropEvent, const FSequencerDragDropParams& DragDropParams) override;`
- L73 _protected prototype_ `FKeyPropertyResult AddKeyInternal(FFrameNumber AutoKeyTime, const FGuid ObjectGuid);` — Delegate for AnimatablePropertyChanged in AddKey
- L76 _protected prototype_ `UMovieSceneCameraCutTrack* FindOrCreateCameraCutTrack();` — Find or create a camera cut track in the currently focused movie scene.
- L78 _protected prototype_ `UFactory* GetAssetFactoryForNewCameraCut(UClass* SequenceClass);`
- L83 _private prototype_ `bool HandleAddCameraCutTrackMenuEntryCanExecute() const;` — Callback for determining whether the "Add Camera Cut" menu entry can execute.
- L86 _private prototype_ `void HandleAddCameraCutTrackMenuEntryExecute();` — Callback for executing the "Add Camera Cut Track" menu entry.
- L89 _private prototype_ `TSharedRef<SWidget> HandleAddCameraCutComboButtonGetMenuContent();` — Callback for generating the menu of the "Add Camera Cut" combo button.
- L92 _private prototype_ `bool IsCameraPickable( const AActor* const PickableActor );` — Callback for whether a camera is pickable.
- L95 _private prototype_ `void HandleAddCameraCutComboButtonMenuEntryExecute(AActor* Camera);` — Callback for executing a menu entry in the "Add Camera Cut" combo button.
- L98 _private prototype_ `void CreateNewSectionFromBinding(FMovieSceneObjectBindingID InBindingID);` — Called to create a new section for the specified binding ID.
- L101 _private prototype_ `void HandleToggleCanBlendExecute(UMovieSceneCameraCutTrack* CameraCutTrack);` — Called when toggling whether the track can blend camera cuts.
- L104 _private prototype_ `void HandleToggleAutoArrangeSectionsExecute(UMovieSceneCameraCutTrack* CameraCutTrack);` — Called when toggling whether the track auto-manages camera cuts.
- L107 _private prototype_ `ECheckBoxState IsCameraLocked() const;` — Delegate for camera button lock state
- L110 _private prototype_ `void OnLockCameraClicked(ECheckBoxState CheckBoxState);` — Delegate for locked camera button
- L113 _private prototype_ `void ToggleLockCamera();` — Toggle the state of the camera lock
- L116 _private prototype_ `FText GetLockCameraToolTip() const;` — Delegate for camera button lock tooltip
- L121 _private member_ `TSharedPtr<FTrackEditorThumbnailPool> ThumbnailPool;` — The Thumbnail pool which draws all the viewport thumbnails for the camera cut track.
- L124 _private member_ `TSharedPtr<FTrackEditorBindingIDPicker> BindingIDPicker;` — A binding ID picker that allows us to create a new section from an existing binding

### `Source/Editor/MovieSceneTools/Private/TrackEditors/CameraShakeSourceShakeTrackEditor.h` (Private)


#### class `FCameraShakeSourceShakeTrackEditor`  
`class FCameraShakeSourceShakeTrackEditor : public FMovieSceneTrackEditor`  
_L29-69_
- inherits: `FMovieSceneTrackEditor`
- L32 _public prototype_ `static TSharedRef<ISequencerTrackEditor> CreateTrackEditor(TSharedRef<ISequencer> OwningSequencer);`
- L34 _public prototype_ `FCameraShakeSourceShakeTrackEditor(TSharedRef<ISequencer> InSequencer);`
- L35 _public prototype_ `virtual ~FCameraShakeSourceShakeTrackEditor() = default;`
- L38 _public prototype_ `virtual FText GetDisplayName() const override;` — ISequencerTrackEditor interface
- L39 _public prototype_ `virtual UMovieSceneTrack* AddTrack(UMovieScene* FocusedMovieScene, const FGuid& ObjectHandle, TSubclassOf<class UMovieSceneTrack> TrackClass, FName UniqueTypeName) override;`
- L40 _public prototype_ `virtual void BuildObjectBindingTrackMenu(FMenuBuilder& MenuBuilder, const TArray<FGuid>& ObjectBindings, const UClass* ObjectClass) override;`
- L41 _public prototype_ `virtual TSharedRef<ISequencerSection> MakeSectionInterface(UMovieSceneSection& SectionObject, UMovieSceneTrack& Track, FGuid ObjectBinding) override;`
- L42 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneTrack> Type) const override;`
- L43 _public prototype_ `virtual TSharedPtr<SWidget> BuildOutlinerEditWidget(const FGuid& ObjectBinding, UMovieSceneTrack* Track, const FBuildEditWidgetParams& Params) override;`
- L47 _private prototype_ `FKeyPropertyResult AddCameraShakeSectionKeyInternal(FFrameNumber KeyTime, const TArray<TWeakObjectPtr<UObject>> Objects, bool bSelect);` — Shake section members
- L48 _private prototype_ `FKeyPropertyResult AddCameraShakeSectionKeyInternal(FFrameNumber KeyTime, const TArray<TWeakObjectPtr<UObject>> Objects, TSubclassOf<UCameraShakeBase> CameraShake, bool bSelect);`
- L50 _private prototype_ `void AddCameraShakeSection(TArray<FGuid> ObjectHandles);`
- L52 _private prototype_ `TSharedRef<SWidget> BuildCameraShakeSubMenu(FGuid ObjectBinding);`
- L53 _private prototype_ `void AddCameraShakeSubMenu(FMenuBuilder& MenuBuilder, TArray<FGuid> ObjectBindings);`
- L54 _private prototype_ `void AddOtherCameraShakeBrowserSubMenu(FMenuBuilder& MenuBuilder, TArray<FGuid> ObjectBindings);`
- L55 _private prototype_ `void OnCameraShakeAssetSelected(const FAssetData& AssetData, TArray<FGuid> ObjectBindings);`
- L56 _private prototype_ `void OnCameraShakeAssetEnterPressed(const TArray<FAssetData>& AssetData, TArray<FGuid> ObjectBindings);`
- L57 _private prototype_ `void OnAutoCameraShakeSelected(TArray<FGuid> ObjectBindings);`
- L58 _private prototype_ `bool OnShouldFilterCameraShake(const FAssetData& AssetData);`
- L61 _private prototype_ `FKeyPropertyResult AddCameraShakeTriggerTrackInternal(FFrameNumber Time, const TArray<TWeakObjectPtr<UObject>> Objects, TSubclassOf<UCameraShakeBase> CameraShake);` — Shake trigger members
- L63 _private prototype_ `void AddCameraShakeTriggerTrack(const TArray<FGuid> ObjectBindings);`
- L66 _private prototype_ `UCameraShakeSourceComponent* AcquireCameraShakeSourceComponentFromGuid(const FGuid& Guid);` — Utility
- L67 _private prototype_ `void AddCameraShakeTracksMenu(FMenuBuilder& MenuBuilder, TArray<FGuid> ObjectBindings);`
- L68 _private prototype_ `TSharedRef<SWidget> BuildCameraShakeTracksMenu(FGuid ObjectBinding);`

### `Source/Editor/MovieSceneTools/Private/TrackEditors/CameraShakeTrackEditor.h` (Private)


#### class `FCameraShakeTrackEditor`  
`class FCameraShakeTrackEditor : public FMovieSceneTrackEditor`  
_L29-77_
- inherits: `FMovieSceneTrackEditor`
- desc: Tools for playing a camera shake
- L38 _public prototype_ `FCameraShakeTrackEditor(TSharedRef<ISequencer> InSequencer);` — Constructor @param InSequencer The sequencer instance to be used by this tool
- L41 _public prototype_ `virtual ~FCameraShakeTrackEditor() = default;` — Virtual destructor.
- L49 _public prototype_ `static TSharedRef<ISequencerTrackEditor> CreateTrackEditor(TSharedRef<ISequencer> OwningSequencer);` — Creates an instance of this class.  Called by a sequencer @param OwningSequencer The sequencer instance to be used by this tool @return The new instance of this class
- L54 _public prototype_ `virtual FText GetDisplayName() const override;` — ISequencerTrackEditor interface
- L55 _public prototype_ `virtual void BuildObjectBindingTrackMenu(FMenuBuilder& MenuBuilder, const TArray<FGuid>& ObjectBindings, const UClass* ObjectClass) override;`
- L56 _public prototype_ `virtual bool HandleAssetAdded(UObject* Asset, const FGuid& TargetObjectGuid) override;`
- L57 _public prototype_ `virtual TSharedRef<ISequencerSection> MakeSectionInterface(UMovieSceneSection& SectionObject, UMovieSceneTrack& Track, FGuid ObjectBinding) override;`
- L58 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneTrack> Type) const override;`
- L59 _public prototype_ `virtual TSharedPtr<SWidget> BuildOutlinerEditWidget(const FGuid& ObjectBinding, UMovieSceneTrack* Track, const FBuildEditWidgetParams& Params) override;`
- L64 _private prototype_ `FKeyPropertyResult AddKeyInternal(FFrameNumber KeyTime, const TArray<TWeakObjectPtr<UObject>> Objects, TSubclassOf<UCameraShakeBase> ShakeClass);` — Delegate for AnimatablePropertyChanged in AddKey
- L67 _private prototype_ `TSharedRef<SWidget> BuildCameraShakeSubMenu(FGuid ObjectBinding);` — Animation sub menu
- L68 _private prototype_ `void AddCameraShakeSubMenu(FMenuBuilder& MenuBuilder, TArray<FGuid> ObjectBindings);`
- L71 _private prototype_ `void OnCameraShakeAssetSelected(const FAssetData& AssetData, TArray<FGuid> ObjectBindings);` — Animation asset selected
- L74 _private prototype_ `void OnCameraShakeAssetEnterPressed(const TArray<FAssetData>& AssetData, TArray<FGuid> ObjectBindings);` — Animation asset enter pressed
- L76 _private prototype_ `class UCameraComponent* AcquireCameraComponentFromObjectGuid(const FGuid& Guid);`

### `Source/Editor/MovieSceneTools/Private/TrackEditors/CameraShakeTrackEditorBase.h` (Private)


#### class `FCameraShakeSectionBase`  
`class FCameraShakeSectionBase : public ISequencerSection`  
_L23-52_
- inherits: `ISequencerSection`
- desc: Section interface for shake sections
- L26 _public prototype_ `FCameraShakeSectionBase(const TSharedPtr<ISequencer> InSequencer, UMovieSceneSection& InSection, const FGuid& InObjectBindingId);`
- L28 _public prototype_ `virtual FText GetSectionTitle() const override;`
- L29 _public prototype_ `virtual UMovieSceneSection* GetSectionObject() override;`
- L30 _public prototype_ `virtual bool IsReadOnly() const override;`
- L31 _public prototype_ `virtual int32 OnPaintSection(FSequencerSectionPainter& Painter) const override;`
- L34 _protected prototype_ `virtual TSubclassOf<UCameraShakeBase> GetCameraShakeClass() const = 0;`
- L36 _protected prototype_ `TSharedPtr<ISequencer> GetSequencer() const;`
- L37 _protected prototype_ `FGuid GetObjectBinding() const;`
- L40 _protected function_ `template<typename SectionClass> SectionClass* GetSectionObjectAs() const`
- L46 _private prototype_ `const UCameraShakeBase* GetCameraShakeDefaultObject() const;`
- L49 _private member_ `TWeakPtr<ISequencer> SequencerPtr;`
- L50 _private member_ `TWeakObjectPtr<UMovieSceneSection> SectionPtr;`
- L51 _private member_ `FGuid ObjectBindingId;`

### `Source/Editor/MovieSceneTools/Private/TrackEditors/DataLayerTrackEditor.h` (Private)


#### class `FDataLayerTrackEditor`  
`class FDataLayerTrackEditor : public FMovieSceneTrackEditor`  
_L16-49_
- inherits: `FMovieSceneTrackEditor`
- desc: A sequencer track editor for data layer tracks.
- L21 _public prototype_ `FDataLayerTrackEditor(TSharedRef<ISequencer> InSequencer);`
- L23 _public prototype_ `static TSharedRef<ISequencerTrackEditor> CreateTrackEditor(TSharedRef<ISequencer> OwningSequencer);`
- L28 _public prototype_ `virtual FText GetDisplayName() const override;` — ISequencerTrackEditor interface
- L29 _public prototype_ `virtual TSharedRef<ISequencerSection> MakeSectionInterface(UMovieSceneSection& SectionObject, UMovieSceneTrack& Track, FGuid ObjectBinding) override;`
- L30 _public prototype_ `virtual bool SupportsSequence(UMovieSceneSequence* InSequence) const override;`
- L31 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneTrack> Type) const override;`
- L32 _public prototype_ `virtual const FSlateBrush* GetIconBrush() const override;`
- L33 _public prototype_ `virtual void BuildAddTrackMenu(FMenuBuilder& MenuBuilder) override;`
- L34 _public prototype_ `TSharedPtr<SWidget> BuildOutlinerEditWidget(const FGuid& ObjectBinding, UMovieSceneTrack* Track, const FBuildEditWidgetParams& Params) override;`
- L39 _private prototype_ `UMovieSceneDataLayerSection* AddNewSection(UMovieScene* MovieScene, UMovieSceneTrack* DataLayerTrack, EDataLayerRuntimeState DesiredState);` — Adds a new section which spans the length of the owning movie scene with the specified desired state.
- L42 _private prototype_ `void HandleAddTrack();` — Handles when the add track menu item is activated.
- L45 _private prototype_ `TSharedRef<SWidget> BuildAddDataLayerMenu(UMovieSceneTrack* DataLayerTrack);` — Builds the add data layer menu which is displayed on the track.
- L48 _private prototype_ `void HandleAddNewSection(UMovieSceneTrack* DataLayerTrack, EDataLayerRuntimeState DesiredState);` — Called to add a new section with a desired state.

### `Source/Editor/MovieSceneTools/Private/TrackEditors/DefaultLinkedAnimTrackProvider.h` (Private)


#### class `FDefaultLinkedAnimTrackProvider`  
`class FDefaultLinkedAnimTrackProvider : public IMovieSceneLinkedAnimTrackProvider`  
_L12-24_
- inherits: `IMovieSceneLinkedAnimTrackProvider`
- desc: Default implementation of IMovieSceneLinkedAnimTrackProvider. Handles the standard case where the linked animation track is a standalone UMovieSceneSkeletalAnimationTrack on the binding (not inside a mixer).
- L17 _public function_ `virtual int32 GetLinkedAnimTrackPriority() const override`
- L18 _public prototype_ `virtual bool CanHandleBinding(const TWeakPtr<ISequencer>& InSequencer, FGuid BindingID) const override;`
- L19 _public prototype_ `virtual UMovieSceneTrack* GetLinkedAnimTrack(const TWeakPtr<ISequencer>& InSequencer, FGuid BindingID) const override;`
- L20 _public prototype_ `virtual UMovieSceneTrack* GetOrCreateLinkedAnimTrack(const TWeakPtr<ISequencer>& InSequencer, FGuid BindingID, UE::Sequencer::FCommonAnimationTrackEditor& TrackEditor) override;`
- L21 _public prototype_ `virtual bool IsolateLinkedAnimTrack(const TWeakPtr<ISequencer>& InSequencer, FGuid BindingID, bool bIsolate) override;`
- L22 _public prototype_ `virtual void UpdateLinkedAnimSectionRange(const TWeakPtr<ISequencer>& InSequencer, FGuid BindingID) override;`
- L23 _public prototype_ `virtual bool DeleteLinkedAnimTrack(const TWeakPtr<ISequencer>& InSequencer, FGuid BindingID) override;`

### `Source/Editor/MovieSceneTools/Private/TrackEditors/EventTrackEditor.h` (Private)


#### class `FEventTrackEditor`  
`class FEventTrackEditor : public FMovieSceneTrackEditor`  
_L19-65_
- inherits: `FMovieSceneTrackEditor`
- desc: A property track editor for named events.
- L30 _public prototype_ `static TSharedRef<ISequencerTrackEditor> CreateTrackEditor(TSharedRef<ISequencer> InSequencer);` — Factory function to create an instance of this class (called by a sequencer). @param InSequencer The sequencer instance to be used by this tool. @return The new instance of this class.
- L39 _public prototype_ `FEventTrackEditor(TSharedRef<ISequencer> InSequencer);` — Creates and initializes a new instance. @param InSequencer The sequencer instance to be used by this tool.
- L45 _public prototype_ `virtual FText GetDisplayName() const override;`
- L46 _public prototype_ `virtual void BuildAddTrackMenu(FMenuBuilder& MenuBuilder) override;`
- L47 _public prototype_ `virtual void BuildObjectBindingTrackMenu(FMenuBuilder& MenuBuilder, const TArray<FGuid>& ObjectBindings, const UClass* ObjectClass) override;`
- L48 _public prototype_ `virtual bool SupportsType( TSubclassOf<UMovieSceneTrack> Type ) const override;`
- L49 _public prototype_ `virtual bool SupportsSequence(UMovieSceneSequence* InSequence) const override;`
- L50 _public prototype_ `virtual const FSlateBrush* GetIconBrush() const override;`
- L51 _public prototype_ `virtual void BuildTrackContextMenu( FMenuBuilder& MenuBuilder, UMovieSceneTrack* Track ) override;`
- L52 _public prototype_ `virtual TSharedPtr<SWidget> BuildOutlinerEditWidget(const FGuid& ObjectBinding, UMovieSceneTrack* Track, const FBuildEditWidgetParams& Params) override;`
- L55 _public prototype_ `virtual TSharedRef<ISequencerSection> MakeSectionInterface(UMovieSceneSection& SectionObject, UMovieSceneTrack& Track, FGuid ObjectBinding) override;`
- L59 _private prototype_ `void AddEventSubMenu(FMenuBuilder& MenuBuilder, TArray<FGuid>);`
- L62 _private prototype_ `void HandleAddEventTrackMenuEntryExecute(TArray<FGuid> InObjectBindingIDs, UClass* SectionType);` — Callback for executing the "Add Event Track" menu entry.
- L64 _private prototype_ `void CreateNewSection(UMovieSceneTrack* Track, int32 RowIndex, UClass* SectionType, bool bSelect);`

### `Source/Editor/MovieSceneTools/Private/TrackEditors/FadeTrackEditor.h` (Private)


#### class `FFadeTrackEditor`  
`class FFadeTrackEditor : public FKeyframeTrackEditor<UMovieSceneFadeTrack>`  
_L23-61_
- inherits: `FKeyframeTrackEditor<UMovieSceneFadeTrack>`
- desc: A property track editor for fade control.
- L34 _public prototype_ `static TSharedRef<ISequencerTrackEditor> CreateTrackEditor(TSharedRef<ISequencer> InSequencer);` — Factory function to create an instance of this class (called by a sequencer). @param InSequencer The sequencer instance to be used by this tool. @return The new instance of this class.
- L43 _public prototype_ `FFadeTrackEditor(TSharedRef<ISequencer> InSequencer);` — Creates and initializes a new instance. @param InSequencer The sequencer instance to be used by this tool.
- L49 _public prototype_ `virtual FText GetDisplayName() const override;`
- L50 _public prototype_ `virtual TSharedRef<ISequencerSection> MakeSectionInterface(UMovieSceneSection& SectionObject, UMovieSceneTrack& Track, FGuid ObjectBinding) override;`
- L51 _public prototype_ `virtual void BuildAddTrackMenu(FMenuBuilder& MenuBuilder) override;`
- L52 _public prototype_ `virtual bool SupportsSequence(UMovieSceneSequence* InSequence) const override;`
- L53 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneTrack> Type) const override;`
- L54 _public prototype_ `virtual const FSlateBrush* GetIconBrush() const override;`
- L59 _private prototype_ `void HandleAddFadeTrackMenuEntryExecute();` — Callback for executing the "Add Fade Track" menu entry.
- L60 _private prototype_ `bool HandleAddFadeTrackMenuEntryCanExecute() const;`

### `Source/Editor/MovieSceneTools/Private/TrackEditors/LevelVisibilityTrackEditor.h` (Private)


#### class `FLevelVisibilityTrackEditor`  
`class FLevelVisibilityTrackEditor : public FMovieSceneTrackEditor`  
_L22-78_
- inherits: `FMovieSceneTrackEditor`
- desc: A sequencer track editor for level visibility movie scene tracks.
- L32 _public prototype_ `FLevelVisibilityTrackEditor( TSharedRef<ISequencer> InSequencer );` — Constructor. @param InSequencer The sequencer instance to be used by this tool.
- L35 _public prototype_ `virtual ~FLevelVisibilityTrackEditor() = default;` — Virtual destructor.
- L43 _public prototype_ `static TSharedRef<ISequencerTrackEditor> CreateTrackEditor( TSharedRef<ISequencer> OwningSequencer );` — Creates an instance of this class.  Called by a sequencer. @param OwningSequencer The sequencer instance to be used by this tool. @return The new instance of this class.
- L49 _public prototype_ `virtual FText GetDisplayName() const override;`
- L50 _public prototype_ `virtual TSharedRef<ISequencerSection> MakeSectionInterface( UMovieSceneSection& SectionObject, UMovieSceneTrack& Track, FGuid ObjectBinding ) override;`
- L51 _public prototype_ `virtual bool SupportsSequence(UMovieSceneSequence* InSequence) const override;`
- L52 _public prototype_ `virtual bool SupportsType( TSubclassOf<UMovieSceneTrack> Type ) const override;`
- L53 _public prototype_ `virtual const FSlateBrush* GetIconBrush() const override;`
- L54 _public prototype_ `virtual void BuildAddTrackMenu( FMenuBuilder& MenuBuilder ) override;`
- L55 _public prototype_ `TSharedPtr<SWidget> BuildOutlinerEditWidget( const FGuid& ObjectBinding, UMovieSceneTrack* Track, const FBuildEditWidgetParams& Params ) override;`
- L56 _public prototype_ `virtual void BuildTrackContextMenu( FMenuBuilder& MenuBuilder, UMovieSceneTrack* Track ) override;`
- L60 _private prototype_ `UMovieSceneLevelVisibilitySection* AddNewSection(UMovieScene* MovieScene, UMovieSceneTrack* LevelVisibilityTrack, ELevelVisibility Visibility );` — Adds a new section which spans the length of the owning movie scene with the specified visibility.
- L63 _private prototype_ `void OnAddTrack();` — Handles when the add track menu item is activated.
- L66 _private prototype_ `TSharedRef<SWidget> BuildAddVisibilityTriggerMenu( UMovieSceneTrack* LevelVisibilityTrack );` — Builds the add visibility trigger menu which is displayed on the track.
- L69 _private prototype_ `void OnAddNewSection( UMovieSceneTrack* LevelVisibilityTrack, ELevelVisibility Visibility );` — Handles when the add visibility trigger menu item is activated.
- L72 _private prototype_ `void OnAddCurrentLevelVisibility(UMovieSceneTrack* LevelVisibilityTrack);` — Handles when the add current level visibility menu item is activated.
- L75 _private prototype_ `void OnSetCurrentLevelVisibility(UMovieSceneTrack* LevelVisibilityTrack);` — Handles when the replace current level visibility menu item is activated.
- L77 _private prototype_ `void GetCurrentLevelVisibility(TArray<FName>& OutVisibleLevelNames, TArray<FName>& OutHiddenLevelNames);`

### `Source/Editor/MovieSceneTools/Private/TrackEditors/MaterialParameterCollectionTrackEditor.h` (Private)


#### class `FMaterialParameterCollectionTrackEditor`  
`class FMaterialParameterCollectionTrackEditor : public FMovieSceneTrackEditor`  
_L33-67_
- inherits: `FMovieSceneTrackEditor`
- desc: Track editor for material parameter collections.
- L39 _public prototype_ `FMaterialParameterCollectionTrackEditor(TSharedRef<ISequencer> InSequencer);` — Constructor.
- L42 _public prototype_ `static TSharedRef<ISequencerTrackEditor> CreateTrackEditor(TSharedRef<ISequencer> OwningSequencer);` — Factory function
- L47 _public prototype_ `virtual FText GetDisplayName() const override;`
- L48 _public prototype_ `virtual TSharedPtr<SWidget> BuildOutlinerEditWidget(const FGuid& ObjectBinding, UMovieSceneTrack* Track, const FBuildEditWidgetParams& Params) override;`
- L49 _public prototype_ `virtual TSharedPtr<SWidget> BuildOutlinerEditColumnWidget(const FGuid& ObjectBinding, UMovieSceneTrack* Track, const FBuildEditWidgetParams& Params) override;`
- L50 _public prototype_ `virtual TSharedRef<ISequencerSection> MakeSectionInterface(UMovieSceneSection& SectionObject, UMovieSceneTrack& Track, FGuid ObjectBinding) override;`
- L51 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneTrack> Type) const override;`
- L52 _public prototype_ `virtual bool SupportsSequence(UMovieSceneSequence* InSequence) const override;`
- L53 _public prototype_ `virtual void BuildAddTrackMenu(FMenuBuilder& MenuBuilder) override;`
- L54 _public prototype_ `virtual const FSlateBrush* GetIconBrush() const override;`
- L55 _public prototype_ `virtual bool HandleAssetAdded(UObject* Asset, const FGuid& TargetObjectGuid) override;`
- L60 _private prototype_ `TSharedRef<SWidget> OnGetAddParameterMenuContent(UMovieSceneMaterialParameterCollectionTrack* MaterialTrack, int32 RowIndex, int32 TrackInsertRowIndex);` — Provides the contents of the add parameter menu.
- L62 _private prototype_ `void AddScalarParameter(UMovieSceneMaterialParameterCollectionTrack* Track, int32 RowIndex, FCollectionScalarParameter Parameter);`
- L63 _private prototype_ `void AddVectorParameter(UMovieSceneMaterialParameterCollectionTrack* Track, int32 RowIndex, FCollectionVectorParameter Parameter);`
- L65 _private prototype_ `void AddTrackToSequence(const FAssetData& InAssetData);`
- L66 _private prototype_ `void AddTrackToSequenceEnterPressed(const TArray<FAssetData>& InAssetData);`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MOVIESCENETOOLS_API`

### `Source/Editor/MovieSceneTools/Private/TrackEditors/ObjectPropertyTrackEditor.h` (Private)


#### class `FObjectPropertyTrackEditor`  
`class FObjectPropertyTrackEditor : public FPropertyTrackEditor<UMovieSceneObjectPropertyTrack>`  
_L22-46_
- inherits: `FPropertyTrackEditor<UMovieSceneObjectPropertyTrack>`
- L27 _public prototype_ `FObjectPropertyTrackEditor(TSharedRef<ISequencer> InSequencer);` — Constructor.
- L32 _public function_ `static TArray<FAnimatedPropertyKey, TInlineAllocator<1>> GetAnimatedPropertyTypes()` — Retrieve a list of all property types that this track editor animates
- L38 _public prototype_ `static TSharedRef<ISequencerTrackEditor> CreateTrackEditor(TSharedRef<ISequencer> OwningSequencer);` — Factory function
- L43 _public prototype_ `virtual FText GetDisplayName() const override;`
- L44 _public prototype_ `virtual void GenerateKeysFromPropertyChanged(const FPropertyChangedParams& PropertyChangedParams, UMovieSceneSection* SectionToKey, FGeneratedTrackKeys& OutGeneratedKeys) override;`
- L45 _public prototype_ `virtual void InitializeNewTrack(UMovieSceneObjectPropertyTrack* NewTrack, FPropertyChangedParams PropertyChangedParams) override;`

### `Source/Editor/MovieSceneTools/Private/TrackEditors/ParticleParameterTrackEditor.h` (Private)


#### class `FParticleParameterTrackEditor`  
`class FParticleParameterTrackEditor : public FMovieSceneTrackEditor`  
_L24-105_
- inherits: `FMovieSceneTrackEditor`
- desc: Track editor for material parameters.
- L30 _public prototype_ `FParticleParameterTrackEditor( TSharedRef<ISequencer> InSequencer );` — Constructor.
- L33 _public prototype_ `virtual ~FParticleParameterTrackEditor() = default;` — Virtual destructor.
- L41 _public prototype_ `static TSharedRef<ISequencerTrackEditor> CreateTrackEditor( TSharedRef<ISequencer> OwningSequencer );` — Creates an instance of this class.  Called by a sequencer. @param OwningSequencer The sequencer instance to be used by this tool. @return The new instance of this class.
- L45 _public prototype_ `virtual FText GetDisplayName() const override;`
- L46 _public prototype_ `virtual TSharedPtr<SWidget> BuildOutlinerEditWidget( const FGuid& ObjectBinding, UMovieSceneTrack* Track, const FBuildEditWidgetParams& Params ) override;`
- L47 _public prototype_ `virtual TSharedRef<ISequencerSection> MakeSectionInterface( UMovieSceneSection& SectionObject, UMovieSceneTrack& Track, FGuid ObjectBinding ) override;`
- L48 _public prototype_ `virtual bool SupportsType( TSubclassOf<UMovieSceneTrack> Type ) const override;`
- L52 _private member_ `static FName TrackName;`
- L72 _private prototype_ `void BuildObjectBindingTrackMenu( FMenuBuilder& MenuBuilder, const TArray<FGuid>& ObjectBindings, const UClass* ObjectClass );`
- L75 _private prototype_ `TSharedRef<SWidget> OnGetAddParameterMenuContent( FGuid ObjectBinding, UMovieSceneParticleParameterTrack* ParticleParameterTrack );` — Provides the contents of the add parameter menu.
- L77 _private prototype_ `bool CanAddParticleParameterTrack (FGuid ObjectBinding );`
- L79 _private prototype_ `void AddParticleParameterTrack( TArray<FGuid> ObjectBindings );`
- L86 _private prototype_ `void AddScalarParameter( FGuid ObjectBinding, UMovieSceneParticleParameterTrack* ParticleParameterTrack, FName ParameterName );` — Adds a scalar parameter and initial key to a material track. @param ObjectBinding The object binding which owns the material track. @param ParticleParameterTrack The track to Add the section to. @param ParameterName The name of the parameter to add an initial key for.
- L93 _private prototype_ `void AddVectorParameter( FGuid ObjectBinding, UMovieSceneParticleParameterTrack* ParticleParameterTrack, FName ParameterName );` — Adds a vector parameter and initial key to a material track. @param ObjectBinding The object binding which owns the material track. @param ParticleParameterTrack The track to Add the section to. @param ParameterName The name of the parameter to add an initial key for.
- L100 _private prototype_ `void AddColorParameter( FGuid ObjectBinding, UMovieSceneParticleParameterTrack* ParticleParameterTrack, FName ParameterName );` — Adds a Color parameter and initial key to a material track. @param ObjectBinding The object binding which owns the material track. @param ParticleParameterTrack The track to Add the section to. @param ParameterName The name of the parameter to add an initial key for.
- L104 _private prototype_ `UParticleSystemComponent* GetParticleSystemComponentForBinding(FGuid ObjectBinding);` — Gets the particle system component for the supplied object binding.  This works for emitter actors and directly bound particle components.

#### struct `FParticleParameterTrackEditor::FParameterNameAndAction`  
`struct FParameterNameAndAction`  
_L55-70_
- desc: Struct used for building the parameter menu.
- L57 _public member_ `FName ParameterName;`
- L58 _public member_ `FUIAction Action;`
- L60 _public function_ `FParameterNameAndAction( FName InParameterName, FUIAction InAction )`
- L66 _public function_ `bool operator<( FParameterNameAndAction const& Other ) const`

### `Source/Editor/MovieSceneTools/Private/TrackEditors/ParticleTrackEditor.h` (Private)


#### class `FParticleTrackEditor`  
`class FParticleTrackEditor : public FMovieSceneTrackEditor`  
_L21-62_
- inherits: `FMovieSceneTrackEditor`
- desc: Tools for particle tracks
- L31 _public prototype_ `FParticleTrackEditor( TSharedRef<ISequencer> InSequencer );` — Constructor. @param InSequencer The sequencer instance to be used by this tool.
- L34 _public prototype_ `virtual ~FParticleTrackEditor() = default;` — Virtual destructor.
- L42 _public prototype_ `static TSharedRef<ISequencerTrackEditor> CreateTrackEditor( TSharedRef<ISequencer> OwningSequencer );` — Creates an instance of this class.  Called by a sequencer. @param OwningSequencer The sequencer instance to be used by this tool. @return The new instance of this class.
- L46 _public prototype_ `void AddParticleKey(const FGuid ObjectGuid, bool bTrigger);`
- L52 _public prototype_ `virtual FText GetDisplayName() const override;`
- L53 _public prototype_ `virtual void BuildObjectBindingTrackMenu(FMenuBuilder& MenuBuilder, const TArray<FGuid>& ObjectBindings, const UClass* ObjectClass) override;`
- L54 _public prototype_ `virtual TSharedRef<ISequencerSection> MakeSectionInterface( UMovieSceneSection& SectionObject, UMovieSceneTrack& Track, FGuid ObjectBinding ) override;`
- L55 _public prototype_ `virtual bool SupportsType( TSubclassOf<UMovieSceneTrack> Type ) const override;`
- L57 _public prototype_ `void AddParticleKey(TArray<FGuid> ObjectGuids);`
- L61 _private prototype_ `FKeyPropertyResult AddKeyInternal( FFrameNumber KeyTime, UObject* Object);` — Delegate for AnimatablePropertyChanged in AddKey.

#### class `FParticleSection`  
`class FParticleSection : public ISequencerSection , public TSharedFromThis<FParticleSection>`  
_L68-92_
- inherits: `ISequencerSection,TSharedFromThis<FParticleSection>`
- desc: Class for particle sections.
- L74 _public prototype_ `FParticleSection( UMovieSceneSection& InSection, TSharedRef<ISequencer> InOwningSequencer );`
- L75 _public prototype_ `~FParticleSection();`
- L80 _public prototype_ `virtual UMovieSceneSection* GetSectionObject() override;` — ISequencerSection interface
- L81 _public prototype_ `virtual float GetSectionHeight(const UE::Sequencer::FViewDensityInfo& ViewDensity) const override;`
- L82 _public prototype_ `virtual int32 OnPaintSection( FSequencerSectionPainter& InPainter ) const override;`
- L83 _public function_ `virtual bool SectionIsResizable() const override`
- L88 _private member_ `UMovieSceneSection& Section;` — The section we are visualizing.
- L91 _private member_ `TWeakPtr<ISequencer> OwningSequencerPtr;` — The sequencer that owns this section

### `Source/Editor/MovieSceneTools/Private/TrackEditors/PathTrackEditor.h` (Private)


#### class `F3DPathTrackEditor`  
`class F3DPathTrackEditor : public FActorPickerTrackEditor`  
_L21-61_
- inherits: `FActorPickerTrackEditor`
- desc: Tools for animating a transform with a path curve
- L31 _public prototype_ `F3DPathTrackEditor( TSharedRef<ISequencer> InSequencer );` — Constructor @param InSequencer The sequencer instance to be used by this tool
- L34 _public prototype_ `virtual ~F3DPathTrackEditor() = default;` — Virtual destructor.
- L42 _public prototype_ `static TSharedRef<ISequencerTrackEditor> CreateTrackEditor( TSharedRef<ISequencer> OwningSequencer );` — Creates an instance of this class.  Called by a sequencer @param OwningSequencer The sequencer instance to be used by this tool @return The new instance of this class
- L48 _public prototype_ `virtual void BuildObjectBindingTrackMenu(FMenuBuilder& MenuBuilder, const TArray<FGuid>& ObjectBindings, const UClass* ObjectClass) override;`
- L49 _public prototype_ `virtual TSharedRef<ISequencerSection> MakeSectionInterface( UMovieSceneSection& SectionObject, UMovieSceneTrack& Track, FGuid ObjectBinding ) override;`
- L50 _public prototype_ `virtual bool SupportsType( TSubclassOf<UMovieSceneTrack> Type ) const override;`
- L51 _public prototype_ `virtual bool SupportsSequence(UMovieSceneSequence* InSequence) const override;`
- L54 _public prototype_ `virtual bool IsActorPickable( const AActor* const ParentActor, FGuid ObjectBinding, UMovieSceneSection* InSection ) override;` — FTrackEditorActorPicker
- L55 _public prototype_ `virtual void ActorSocketPicked(const FName SocketName, USceneComponent* Component, FActorPickerID ActorPickerID, TArray<FGuid> ObjectBindings, UMovieSceneSection* Section) override;`
- L60 _private prototype_ `FKeyPropertyResult AddKeyInternal(FFrameNumber KeyTime, const TArray<TWeakObjectPtr<UObject>> Objects, FActorPickerID ActorPickerID);` — Delegate for AnimatablePropertyChanged in AddKey

### `Source/Editor/MovieSceneTools/Private/TrackEditors/PrimitiveMaterialTrackEditor.h` (Private)


#### class `FPrimitiveMaterialTrackEditor`  
`class FPrimitiveMaterialTrackEditor : public FKeyframeTrackEditor<UMovieScenePrimitiveMaterialTrack>`  
_L10-32_
- inherits: `FKeyframeTrackEditor<UMovieScenePrimitiveMaterialTrack>`
- L15 _public prototype_ `FPrimitiveMaterialTrackEditor(TSharedRef<ISequencer> InSequencer);` — Constructor.
- L18 _public prototype_ `static TSharedRef<ISequencerTrackEditor> CreateTrackEditor(TSharedRef<ISequencer> OwningSequencer);` — Factory function
- L23 _public prototype_ `virtual FText GetDisplayName() const override;`
- L25 _public prototype_ `virtual void ExtendObjectBindingTrackMenu(TSharedRef<FExtender> Extender, const TArray<FGuid>& ObjectBindings, const UClass* ObjectClass) override;`
- L26 _public prototype_ `virtual void BuildTrackContextMenu(FMenuBuilder& MenuBuilder, UMovieSceneTrack* Track) override;`
- L28 _public prototype_ `void ConstructObjectBindingTrackMenu(FMenuBuilder& MenuBuilder, TArray<FGuid> ObjectBindings);`
- L29 _public prototype_ `void CreateTrackForElement(TArray<FGuid> ObjectBindingIDs, FComponentMaterialInfo MaterialInfo);`
- L31 _public prototype_ `void FillRebindMaterialTrackMenu(FMenuBuilder& MenuBuilder, class UMovieScenePrimitiveMaterialTrack* MaterialTrack, class UPrimitiveComponent* Component, FGuid ObjectBinding);` — Callback for rebinding a component material track to a different material slot

### `Source/Editor/MovieSceneTools/Private/TrackEditors/PropertyTrackEditors/ActorReferencePropertyTrackEditor.h` (Private)


#### class `FActorReferencePropertyTrackEditor`  
`class FActorReferencePropertyTrackEditor : public FPropertyTrackEditor<UMovieSceneActorReferenceTrack>`  
_L29-70_
- inherits: `FPropertyTrackEditor<UMovieSceneActorReferenceTrack>`
- desc: A property track editor for actor references.
- L39 _public function_ `FActorReferencePropertyTrackEditor(TSharedRef<ISequencer> InSequencer) : FPropertyTrackEditor(InSequencer, GetAnimatedPropertyTypes())` — Constructor. @param InSequencer The sequencer instance to be used by this tool.
- L47 _public function_ `static TArray<FAnimatedPropertyKey, TInlineAllocator<1>> GetAnimatedPropertyTypes()` — Retrieve a list of all property types that this track editor animates
- L61 _public prototype_ `static TSharedRef<ISequencerTrackEditor> CreateTrackEditor(TSharedRef<ISequencer> OwningSequencer);` — Creates an instance of this class (called by a sequencer). @param OwningSequencer The sequencer instance to be used by this tool. @return The new instance of this class.
- L66 _protected prototype_ `virtual FText GetDisplayName() const override;`
- L67 _protected prototype_ `virtual void ProcessKeyOperation(FFrameNumber InKeyTime, const UE::Sequencer::FKeyOperation& Operation, ISequencer& InSequencer, TArray<UE::Sequencer::FAddKeyResult>* OutResults = nullptr) override;`
- L68 _protected prototype_ `virtual void GenerateKeysFromPropertyChanged(const FPropertyChangedParams& PropertyChangedParams, UMovieSceneSection* SectionToKey, FGeneratedTrackKeys& OutGeneratedKeys) override;`
- L69 _protected prototype_ `virtual void OnAnimatedPropertyChanged(const FPropertyChangedParams& PropertyChangedParams) override;`

### `Source/Editor/MovieSceneTools/Private/TrackEditors/PropertyTrackEditors/BytePropertyTrackEditor.h` (Private)


#### class `FBytePropertyTrackEditor`  
`class FBytePropertyTrackEditor : public FPropertyTrackEditor<UMovieSceneByteTrack>`  
_L31-72_
- inherits: `FPropertyTrackEditor<UMovieSceneByteTrack>`
- desc: A property track editor for byte and enumerations.
- L41 _public function_ `FBytePropertyTrackEditor(TSharedRef<ISequencer> InSequencer) : FPropertyTrackEditor(InSequencer, GetAnimatedPropertyTypes())` — Constructor. @param InSequencer The sequencer instance to be used by this tool.
- L48 _public function_ `static TArray<FAnimatedPropertyKey, TInlineAllocator<2>> GetAnimatedPropertyTypes()` — Retrieve a list of all property types that this track editor animates
- L62 _public prototype_ `static TSharedRef<ISequencerTrackEditor> CreateTrackEditor(TSharedRef<ISequencer> OwningSequencer);` — Creates an instance of this class (called by a sequencer). @param OwningSequencer The sequencer instance to be used by this tool. @return The new instance of this class.
- L68 _protected prototype_ `virtual FText GetDisplayName() const override;`
- L69 _protected prototype_ `virtual void GenerateKeysFromPropertyChanged(const FPropertyChangedParams& PropertyChangedParams, UMovieSceneSection* SectionToKey, FGeneratedTrackKeys& OutGeneratedKeys) override;`
- L70 _protected prototype_ `virtual void InitializeNewTrack(UMovieSceneByteTrack* NewTrack, FPropertyChangedParams PropertyChangedParams) override;`

### `Source/Editor/MovieSceneTools/Private/TrackEditors/PropertyTrackEditors/RotatorPropertyTrackEditor.h` (Private)


#### class `FRotatorPropertyTrackEditor`  
`class FRotatorPropertyTrackEditor : public FPropertyTrackEditor<UMovieSceneRotatorTrack>`  
_L14-37_
- inherits: `FPropertyTrackEditor<UMovieSceneRotatorTrack>`
- desc: Property track editor for rotator properties
- L17 _public function_ `FRotatorPropertyTrackEditor(TSharedRef<ISequencer> InSequencer) : FPropertyTrackEditor(InSequencer, GetAnimatedPropertyTypes())`
- L21 _public function_ `static TArray<FAnimatedPropertyKey, TInlineAllocator<1>> GetAnimatedPropertyTypes()`
- L30 _public prototype_ `static TSharedRef<ISequencerTrackEditor> CreateTrackEditor(TSharedRef<ISequencer> InOwningSequencer);`
- L34 _protected prototype_ `virtual FText GetDisplayName() const override;`
- L35 _protected prototype_ `virtual void GenerateKeysFromPropertyChanged(const FPropertyChangedParams& InPropertyChangedParams, UMovieSceneSection* InSectionToKey, FGeneratedTrackKeys& OutGeneratedKeys) override;`

### `Source/Editor/MovieSceneTools/Private/TrackEditors/PropertyTrackEditors/StringPropertyTrackEditor.h` (Private)


#### class `FStringPropertyTrackEditor`  
`class FStringPropertyTrackEditor : public FPropertyTrackEditor<UMovieSceneStringTrack>`  
_L26-61_
- inherits: `FPropertyTrackEditor<UMovieSceneStringTrack>`
- desc: A property track editor for strings.
- L36 _public function_ `FStringPropertyTrackEditor(TSharedRef<ISequencer> InSequencer) : FPropertyTrackEditor(InSequencer, GetAnimatedPropertyTypes())` — Constructor. @param InSequencer The sequencer instance to be used by this tool.
- L43 _public function_ `static TArray<FAnimatedPropertyKey, TInlineAllocator<1>> GetAnimatedPropertyTypes()` — Retrieve a list of all property types that this track editor animates
- L54 _public prototype_ `static TSharedRef<ISequencerTrackEditor> CreateTrackEditor(TSharedRef<ISequencer> OwningSequencer);` — Creates an instance of this class (called by a sequencer). @param OwningSequencer The sequencer instance to be used by this tool @return The new instance of this class
- L59 _protected prototype_ `virtual FText GetDisplayName() const override;`
- L60 _protected prototype_ `virtual void GenerateKeysFromPropertyChanged(const FPropertyChangedParams& PropertyChangedParams, UMovieSceneSection* SectionToKey, FGeneratedTrackKeys& OutGeneratedKeys) override;`

### `Source/Editor/MovieSceneTools/Private/TrackEditors/PropertyTrackEditors/TextPropertyTrackEditor.h` (Private)


#### class `FTextPropertyTrackEditor`  
`class FTextPropertyTrackEditor : public FPropertyTrackEditor<UMovieSceneTextTrack>`  
_L13-38_
- inherits: `FPropertyTrackEditor<UMovieSceneTextTrack>`
- desc: Track Editor for Text Property
- L16 _public function_ `FTextPropertyTrackEditor(TSharedRef<ISequencer> InSequencer) : FPropertyTrackEditor(InSequencer, GetAnimatedPropertyTypes())`
- L22 _public function_ `static TArray<FAnimatedPropertyKey, TInlineAllocator<1>> GetAnimatedPropertyTypes()` — Retrieve a list of all property types that this track editor animates
- L32 _public prototype_ `static TSharedRef<ISequencerTrackEditor> CreateTrackEditor(TSharedRef<ISequencer> OwningSequencer);` — Creates an instance of this class (called by a sequencer). @param OwningSequencer The sequencer instance to be used by this tool @return The new instance of this class
- L36 _protected prototype_ `virtual void GenerateKeysFromPropertyChanged(const FPropertyChangedParams& PropertyChangedParams, UMovieSceneSection* SectionToKey, FGeneratedTrackKeys& OutGeneratedKeys) override;`

### `Source/Editor/MovieSceneTools/Private/TrackEditors/PropertyTrackEditors/VisibilityPropertyTrackEditor.h` (Private)


#### class `FVisibilityPropertyTrackEditor`  
`class FVisibilityPropertyTrackEditor : public FPropertyTrackEditor<UMovieSceneVisibilityTrack>`  
_L31-57_
- inherits: `FPropertyTrackEditor<UMovieSceneVisibilityTrack>`
- desc: A property track for bool properties which have been set to use a UMovieSceneVisibilityTrack through metadata.
- L37 _public function_ `FVisibilityPropertyTrackEditor(TSharedRef<ISequencer> InSequencer) : FPropertyTrackEditor(InSequencer)` — Constructor.
- L47 _public prototype_ `static TSharedRef<ISequencerTrackEditor> CreateTrackEditor(TSharedRef<ISequencer> OwningSequencer);` — Creates an instance of this class.  Called by a sequencer @param OwningSequencer The sequencer instance to be used by this tool @return The new instance of this class
- L53 _protected prototype_ `virtual FText GetDisplayName() const override;`
- L54 _protected prototype_ `virtual TSharedRef<ISequencerSection> MakeSectionInterface(UMovieSceneSection& SectionObject, UMovieSceneTrack& Track, FGuid ObjectBinding) override;`
- L55 _protected prototype_ `virtual void GenerateKeysFromPropertyChanged(const FPropertyChangedParams& PropertyChangedParams, UMovieSceneSection* SectionToKey, FGeneratedTrackKeys& OutGeneratedKeys) override;`
- L56 _protected function_ `virtual bool ForCustomizedUseOnly()`

### `Source/Editor/MovieSceneTools/Private/TrackEditors/SkeletalAnimationTrackEditor.h` (Private)


#### class `FSkeletalAnimationTrackEditor`  
`class FSkeletalAnimationTrackEditor : public UE::Sequencer::FCommonAnimationTrackEditor , public IMovieSceneAnimMixerItemMenuProvider`  
_L11-56_
- inherits: `UE::Sequencer::FCommonAnimationTrackEditor,IMovieSceneAnimMixerItemMenuProvider`
- desc: Tools for animation tracks
- L22 _public prototype_ `FSkeletalAnimationTrackEditor( TSharedRef<ISequencer> InSequencer );` — Constructor @param InSequencer The sequencer instance to be used by this tool
- L24 _public prototype_ `static TSharedRef<ISequencerTrackEditor> CreateTrackEditor(TSharedRef<ISequencer> InSequencer);`
- L26 _public prototype_ `virtual void OnInitialize() override;`
- L27 _public prototype_ `virtual void OnRelease() override;`
- L29 _public prototype_ `virtual void BuildTrackContextMenu(FMenuBuilder& MenuBuilder, UMovieSceneTrack* Track) override;`
- L30 _public prototype_ `virtual void BuildTrackSidebarMenu(FMenuBuilder& MenuBuilder, UMovieSceneTrack* Track) override;`
- L31 _public prototype_ `virtual bool SupportsSequence(UMovieSceneSequence* InSequence) const override;`
- L32 _public prototype_ `virtual bool SupportsType( TSubclassOf<UMovieSceneTrack> Type ) const override;`
- L33 _public prototype_ `virtual TSharedRef<ISequencerSection> MakeSectionInterface(UMovieSceneSection& SectionObject, UMovieSceneTrack& Track, FGuid ObjectBinding) override;`
- L34 _public prototype_ `virtual TSubclassOf<UMovieSceneCommonAnimationTrack> GetTrackClass() const override;`
- L37 _public prototype_ `virtual const UClass* GetHandledMixerItemClass() const override;` — IMovieSceneAnimMixerItemMenuProvider interface
- L38 _public prototype_ `virtual void PopulateAddMixerItemMenu(FMenuBuilder& MenuBuilder, TArray<FGuid> ObjectBindings, UMovieSceneTrack* Track, TSharedPtr<ISequencer> Sequencer, int32 RowIndex) override;`
- L39 _public prototype_ `virtual void PopulateObjectBindingAnimationMenu(FMenuBuilder& MenuBuilder, const TArray<FGuid>& ObjectBindings, const UClass* ObjectClass, bool bIsInsideSubmenu) override;`
- L42 _public function_ `virtual int32 GetMixerItemMenuPriority() const override` — Appear last in the Animation submenu so the large embedded asset picker sits at the bottom, keeping the discrete menu entries (Animation Mixer, Control Rig, Stitch Animation, etc.) grouped at the top.
- L43 _public function_ `virtual int32 GetObjectBindingAnimationMenuPriority() const override`
- L44 _public prototype_ `virtual void BuildObjectBindingContextMenu(FMenuBuilder& MenuBuilder, const TArray<FGuid>& ObjectBindings, const UClass* ObjectClass) override;`
- L45 _public prototype_ `virtual void BuildObjectBindingColumnWidgets( TFunctionRef<TSharedRef<SHorizontalBox>()> GetEditBox, const UE::Sequencer::TViewModelPtr<UE::Sequencer::FObjectBindingModel>& ObjectBinding, const UE::Sequencer::FCreateOutlinerViewParams& InParams, const FName& InColumnName) override;`
- L52 _private prototype_ `void OnPostPropertyChanged(UObject* InObject, struct FPropertyChangedEvent& InPropertyChangedEvent);`
- L55 _private prototype_ `void BuildTrackContextMenu_Internal(FMenuBuilder& MenuBuilder, UMovieSceneTrack* const InTrack, const bool bAddSeparatorAtEnd);` — Common function used to build context and sidebar menus

#### class `FSkeletalAnimationSection`  
`class FSkeletalAnimationSection : public UE::Sequencer::FCommonAnimationSection`  
_L60-67_
- inherits: `UE::Sequencer::FCommonAnimationSection`
- desc: Class for animation sections
- L66 _public prototype_ `FSkeletalAnimationSection( UMovieSceneSection& InSection, TWeakPtr<ISequencer> InSequencer);` — Constructor.

### `Source/Editor/MovieSceneTools/Private/TrackEditors/SlomoTrackEditor.h` (Private)


#### class `FSlomoTrackEditor`  
`class FSlomoTrackEditor : public FKeyframeTrackEditor<UMovieSceneSlomoTrack>`  
_L20-57_
- inherits: `FKeyframeTrackEditor<UMovieSceneSlomoTrack>`
- desc: A property track editor for slow motion control.
- L31 _public prototype_ `static TSharedRef<ISequencerTrackEditor> CreateTrackEditor(TSharedRef<ISequencer> InSequencer);` — Factory function to create an instance of this class (called by a sequencer). @param InSequencer The sequencer instance to be used by this tool. @return The new instance of this class.
- L40 _public prototype_ `FSlomoTrackEditor(TSharedRef<ISequencer> InSequencer);` — Creates and initializes a new instance. @param InSequencer The sequencer instance to be used by this tool.
- L46 _public prototype_ `virtual FText GetDisplayName() const override;`
- L47 _public prototype_ `virtual void BuildAddTrackMenu(FMenuBuilder& MenuBuilder) override;`
- L48 _public prototype_ `virtual bool SupportsSequence(UMovieSceneSequence* InSequence) const override;`
- L49 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneTrack> Type) const override;`
- L50 _public prototype_ `virtual const FSlateBrush* GetIconBrush() const override;`
- L55 _private prototype_ `void HandleAddSlomoTrackMenuEntryExecute();` — Callback for executing the "Add Slomo Track" menu entry.
- L56 _private prototype_ `bool HandleAddSlomoTrackMenuEntryCanExecute() const;`

### `Source/Editor/MovieSceneTools/Private/TrackEditors/TransformTrackEditor.h` (Private)


#### class `F3DTransformTrackEditor`  
`class F3DTransformTrackEditor : public FKeyframeTrackEditor<UMovieScene3DTransformTrack>, public FEditorUndoClient`  
_L31-235_
- inherits: `FKeyframeTrackEditor<UMovieScene3DTransformTrack>,FEditorUndoClient`
- desc: Tools for animatable transforms
- L41 _public prototype_ `F3DTransformTrackEditor( TSharedRef<ISequencer> InSequencer );` — Constructor @param InSequencer	The sequencer instance to be used by this tool
- L44 _public prototype_ `virtual ~F3DTransformTrackEditor();` — Virtual destructor.
- L52 _public prototype_ `static TSharedRef<ISequencerTrackEditor> CreateTrackEditor( TSharedRef<ISequencer> OwningSequencer );` — Creates an instance of this class.  Called by a sequencer @param OwningSequencer The sequencer instance to be used by this tool @return The new instance of this class
- L61 _public member_ `static F3DTransformTrackEditor* CurrentEditor;` — Cached version of the current track editor, that lets other animaiton tools call specific functions. in particularly setting keys on current values
- L66 _public prototype_ `virtual FText GetDisplayName() const override;` — ISequencerTrackEditor interface
- L67 _public prototype_ `virtual void ProcessKeyOperation(FFrameNumber InKeyTime, const UE::Sequencer::FKeyOperation& Operation, ISequencer& InSequencer, TArray<UE::Sequencer::FAddKeyResult>* OutResults = nullptr) override;`
- L68 _public prototype_ `virtual void BuildObjectBindingColumnWidgets(TFunctionRef<TSharedRef<SHorizontalBox>()> GetEditBox, const UE::Sequencer::TViewModelPtr<UE::Sequencer::FObjectBindingModel>& ObjectBinding, const UE::Sequencer::FCreateOutlinerViewParams& InParams, const FName& InColumnName) override;`
- L69 _public prototype_ `virtual void BuildObjectBindingTrackMenu(FMenuBuilder& MenuBuilder, const TArray<FGuid>& ObjectBindinsg, const UClass* ObjectClass) override;`
- L70 _public prototype_ `virtual TSharedRef<ISequencerSection> MakeSectionInterface( UMovieSceneSection& SectionObject, UMovieSceneTrack& Track, FGuid ObjectBinding ) override;`
- L71 _public prototype_ `virtual void OnRelease() override;`
- L72 _public prototype_ `virtual bool SupportsType( TSubclassOf<UMovieSceneTrack> Type ) const override;`
- L73 _public prototype_ `virtual void BuildTrackContextMenu( FMenuBuilder& MenuBuilder, UMovieSceneTrack* Track ) override;`
- L74 _public function_ `virtual bool HasTransformKeyBindings() const override`
- L75 _public prototype_ `virtual bool CanAddTransformKeysForSelectedObjects() const override;`
- L76 _public prototype_ `virtual void OnAddTransformKeysForSelectedObjects(EMovieSceneTransformChannel Channel) override;`
- L77 _public prototype_ `virtual void OnDeleteTransformKeysForSelectedObjects(EMovieSceneTransformChannel Channel) override;`
- L78 _public prototype_ `virtual void OnPreSaveWorld(UWorld* World) override;`
- L79 _public prototype_ `virtual void OnPostSaveWorld(UWorld* World) override;`
- L82 _public prototype_ `virtual bool MatchesContext(const FTransactionContext& InContext, const TArray<TPair<UObject*, FTransactionObjectEvent>>& TransactionObjects) const override;` — FEditorUndoClient Interface
- L83 _public prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L84 _public function_ `virtual void PostRedo(bool bSuccess) override`
- L87 _private prototype_ `EPropertyKeyedStatus GetKeyedStatusInSection(const UMovieScene3DTransformSection& Section, const TRange<FFrameNumber>& Range, EMovieSceneTransformChannel TransformChannel, TConstArrayView<int32> ChannelIndices) const;`
- L89 _private prototype_ `EPropertyKeyedStatus GetPropertyKeyedStatus(const IPropertyHandle& PropertyHandle, EMovieSceneTransformChannel TransformChannel) const;`
- L91 _private prototype_ `void OnTransformPropertyChanged(const FPropertyChangedParams& PropertyChangedParams, EMovieSceneTransformChannel TransformChannel);`
- L93 _private prototype_ `void ProcessKeyOperation(UObject* ObjectToKey, TArrayView<const UE::Sequencer::FKeySectionOperation> SectionsToKey, ISequencer& InSequencer, FFrameNumber KeyTime, TArray<UE::Sequencer::FAddKeyResult>* OutResults = nullptr);`
- L96 _private prototype_ `bool HasTransformTrack( UObject& InObject ) const;` — Whether the object has an existing transform track
- L103 _private prototype_ `void OnPreTransformChanged( UObject& InObject );` — Called before an actor or component transform changes @param Object The object whose transform is about to change
- L110 _private prototype_ `void OnTransformChanged( UObject& InObject );` — Called when an actor or component transform changes @param Object The object whose transform has changed
- L119 _private prototype_ `void OnPrePropertyChanged(UObject* InObject, const class FEditPropertyChain& InPropertyChain);` — Called before an actor or component property changes. Forward to OnPreTransformChanged if the property is transform related. @param InObject The object whose property is about to change @param InPropertyChain the property that is about to change
- L128 _private prototype_ `void OnPostPropertyChanged(UObject* InObject, struct FPropertyChangedEvent& InPropertyChangedEvent);` — Called before an actor or component property changes. Forward to OnTransformChanged if the property is transform related. @param InObject The object whose property is about to change @param InPropertyChangedEvent the property that changed
- L132 _private prototype_ `EVisibility IsCameraVisible(FGuid ObjectGuid) const;` — Delegate for camera button visible state
- L135 _private prototype_ `ECheckBoxState IsCameraLocked(FGuid ObjectGuid) const;` — Delegate for camera button lock state
- L138 _private prototype_ `void OnLockCameraClicked(ECheckBoxState CheckBoxState, FGuid ObjectGuid);` — Delegate for locked camera button
- L141 _private prototype_ `FText GetLockCameraToolTip(FGuid ObjectGuid) const;` — Delegate for camera button lock tooltip
- L144 _private prototype_ `bool IsCameraBindingLocked(FGuid ObjectGuid) const;` — Implementation of checking if a camera is locked
- L147 _private prototype_ `void LockCameraBinding(bool bLock, FGuid ObjectGuid, FLevelEditorViewportClient* ViewportClient = nullptr, bool bRemoveCinematicLock = true);` — Toggle whether a camera is locked in the given viewport (or the active viewport if not provided)
- L151 _private prototype_ `void GetTransformKeys( const TOptional<FTransformData>& LastTransform, const FTransformData& CurrentTransform, EMovieSceneTransformChannel ChannelsToKey, UObject* Object, UMovieSceneSection* Section, FGeneratedTrackKeys& OutGeneratedKeys );` — Generates transform keys based on the last transform, the current transform, and other options. One transform key is generated for each individual key to be added to the section.
- L154 _private prototype_ `FTransform GetTransformOrigin() const;` — Transform origin which may be set for the current level sequence
- L157 _private prototype_ `FTransform GetRootMotionOffset(UObject* AnimatedObject) const;` — In the case the object is being animated with root motion, return the offset from the keyed transform value that root motion is currently applying.
- L160 _private prototype_ `void UpdateRootMotionOffset(UObject* AnimatedObject);` — In the case the object is being animated with root motion, updates the offset based on the current object position.
- L169 _private prototype_ `void AddTransformKeysForHandle( TArray<FGuid> ObjectHandles, EMovieSceneTransformChannel ChannelToKey, ESequencerKeyMode KeyMode );` — Adds transform keys to an object represented by a handle. @param ObjectHandle The handle to the object to add keys to. @param ChannelToKey The channels to add keys to. @param KeyParams Parameters which control how the keys are added.
- L180 _private prototype_ `void AddTransformKeys( UObject* ObjectToKey, const TOptional<FTransformData>& LastTransform, const FTransformData& CurrentTransform, EMovieSceneTransformChannel ChannelsToKey, ESequencerKeyMode KeyMode );` — Adds keys to a specific actor. @param LastTransform The last known transform of the actor if any. @param CurrentTransform The current transform of the actor. @param ChannelToKey The channels to add keys to. @param KeyParams Parameters which control how the keys are added.
- L182 _private prototype_ `FTransformData RecomposeTransform(const FTransformData& InTransformData, UObject* AnimatedObject, UMovieSceneSection* Section);`
- L192 _public prototype_ `void AddTransformKeysForObject(UObject* Object, EMovieSceneTransformChannel ChannelToKey, ESequencerKeyMode KeyMode);` — Adds transform keys to a specific object. @param Object The object to add keys to. @param ChannelToKey The channels to add keys to. @param KeyParams Parameters which control how the keys are added.
- L196 _private member_ `FDelegateHandle OnSceneComponentConstrainedHandle;` — ConstraintChannel Delegates
- L197 _private prototype_ `void HandleOnConstraintAdded(IMovieSceneConstrainedSection* InSection, FMovieSceneConstraintChannel* InConstraintChannel);`
- L198 _private prototype_ `void HandleConstraintKeyDeleted(IMovieSceneConstrainedSection* InSection, const FMovieSceneConstraintChannel* InConstraintChannel, const TArray<FKeyAddOrDeleteEventItem>& InDeletedItems) const;`
- L200 _private prototype_ `void HandleConstraintKeyMoved(IMovieSceneConstrainedSection* InSection, const FMovieSceneConstraintChannel* InConstraintChannel, const TArray<FKeyMoveEventItem>& InMovedItems);`
- L202 _private prototype_ `void HandleConstraintRemoved(IMovieSceneConstrainedSection* InSection);`
- L203 _private prototype_ `void HandleConstraintPropertyChanged(UTickableTransformConstraint* InConstraint, const FPropertyChangedEvent& InPropertyChangedEvent) const;`
- L205 _private prototype_ `void ClearOutConstraintDelegates();`
- L207 _private prototype_ `void BuildAssetPickerSubMenu(FMenuBuilder& InMenuBuilder, UMovieScene3DTransformTrack* InTransformTrack);`
- L211 _private member_ `static FName TransformPropertyName;`
- L214 _private member_ `TMap< TWeakObjectPtr<UObject>, FTransformData > ObjectToExistingTransform;` — Mapping of objects to their existing transform data (for comparing against new transform data)
- L222 _private member_ `TArray<FTransformPropertyInfo, TFixedAllocator<3>> TransformProperties;` — Array of transform property info for the scene component transform properties for explicit support
- L225 _private member_ `TSharedPtr<FUICommandList> CommandBindings;` — Command Bindings added by the Transform Track Editor to Sequencer and curve editor.
- L228 _private member_ `TMap<FLevelEditorViewportClient*, FGuid> LockedCameraBindings;` — List of locked cameras to restore after save
- L231 _private member_ `mutable TArray<TWeakObjectPtr<UMovieScene3DTransformSection>> SectionsGettingUndone;` — Array of sections that are getting undone, we need to recreate any constraint channel add, move key delegates to them
- L234 _private member_ `TSet<FDelegateHandle> ConstraintHandlesToClear;` — Set of delegate handles we have added delegate's too, need to clear them

#### struct `F3DTransformTrackEditor::FTransformPropertyInfo`  
`struct FTransformPropertyInfo`  
_L216-220_
- L218 _public member_ `const FProperty* Property;`
- L219 _public member_ `EMovieSceneTransformChannel TransformChannel;`

#### Free symbols / members of external scopes

- L26 _namespace_ `namespace UE`
- L26 _namespace_ `namespace Sequencer` (scope `UE`)

### `Source/Editor/MovieSceneTools/Public/AutomatedLevelSequenceCapture.h` (Public)


#### class `UAutomatedLevelSequenceCapture`  
`class UAutomatedLevelSequenceCapture : public UMovieSceneCapture`  
_L21-214_
- reflection: `UCLASS(MinimalAPI, config=EditorPerProjectUserSettings, PerObjectConfig, BlueprintType)`
- inherits: `UMovieSceneCapture`
- L24 _public prototype_ `UAutomatedLevelSequenceCapture(const FObjectInitializer&);`
- L29 _public member_ `static const FName AutomatedLevelSequenceCaptureUIName;` — This name is used by the UI to save/load a specific instance of the settings from config that doesn't affect the CDO which would affect scripting environments.
- L33 _public member_ `FSoftObjectPath LevelSequenceAsset;` — `UPROPERTY(BlueprintReadWrite, Category=Animation)` — A level sequence asset to playback at runtime - used where the level sequence does not already exist in the world.
- L37 _public member_ `FString ShotName;` — `UPROPERTY(BlueprintReadWrite, Category=Animation)` — Optional shot name to render. The frame range to render will be set to the shot frame range.
- L41 _public member_ `bool bUseCustomStartFrame;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category=Animation, AdvancedDisplay)` — When enabled, the StartFrame setting will override the default starting frame number
- L45 _public member_ `FFrameNumber CustomStartFrame;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category=Animation, AdvancedDisplay, meta=(EditCondition="bUseCustomStartFrame", DisplayName="Start Frame"))` — Frame number to start capturing.
- L49 _public member_ `bool bUseCustomEndFrame;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category=Animation, AdvancedDisplay)` — When enabled, the EndFrame setting will override the default ending frame number
- L53 _public member_ `FFrameNumber CustomEndFrame;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category=Animation, AdvancedDisplay, meta=(EditCondition="bUseCustomEndFrame", DisplayName="End Frame"))` — Frame number to end capturing.
- L58 _public member_ `int32 WarmUpFrameCount;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category=Animation, AdvancedDisplay)` — The number of extra frames to play before the sequence's start frame, to "warm up" the animation.  This is useful if your animation contains particles or other runtime effects that are spawned into the scene earlier than your capture start frame
- L62 _public member_ `float DelayBeforeWarmUp;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category=Animation, AdvancedDisplay, meta=(Units=Seconds, ClampMin=0))` — The number of seconds to wait (in real-time) before we start playing back the warm up frames.  Useful for allowing post processing effects to settle down before capturing the animation.
- L66 _public member_ `float DelayBeforeShotWarmUp;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = Animation, AdvancedDisplay, meta = (Units = Seconds, ClampMin = 0))` — The number of seconds to wait (in real-time) at shot boundaries.  Useful for allowing post processing effects to settle down before capturing the animation.
- L70 _public member_ `float DelayEveryFrame;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = Animation, AdvancedDisplay, meta = (Units = Seconds, ClampMin = 0))` — The number of seconds to wait (in real-time) at every frame.  Useful for allowing post processing effects to settle down before capturing the animation.
- L73 _public member_ `TObjectPtr<ULevelSequenceBurnInOptions> BurnInOptions;` — `UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite, Category=CaptureSettings, AdvancedDisplay, meta=(EditInline))`
- L77 _public member_ `bool bWriteEditDecisionList;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category=Sequence)` — Whether to write edit decision lists (EDLs) if the sequence contains shots
- L81 _public member_ `bool bWriteFinalCutProXML;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category=Sequence)` — Whether to write Final Cut Pro XML files (XMLs) if the sequence contains shots
- L85 _public prototype_ `virtual void Initialize(TSharedPtr<FSceneViewport> InViewport, int32 PIEInstance = -1) override;` — UMovieSceneCapture interface
- L87 _public prototype_ `virtual void LoadFromConfig() override;`
- L89 _public prototype_ `virtual void SaveToConfig() override;`
- L91 _public prototype_ `virtual void Close() override;`
- L93 _public prototype_ `double GetEstimatedCaptureDurationSeconds() const override;`
- L96 _public prototype_ `void SetFrameOverrides(FFrameNumber InStartFrame, FFrameNumber InEndFrame);` — Override the render frames with the given start/end frames. Restore the values when done rendering.
- L100 _protected prototype_ `virtual void AddFormatMappings(TMap<FString, FStringFormatArg>& OutFormatMappings, const FFrameMetrics& FrameMetrics) const override;`
- L103 _protected prototype_ `virtual void SerializeAdditionalJson(FJsonObject& Object);` — Custom, additional json serialization
- L106 _protected prototype_ `virtual void DeserializeAdditionalJson(const FJsonObject& Object);` — Custom, additional json deserialization
- L111 _private prototype_ `void UpdateFrameState();` — Update any cached information we need from the level sequence actor
- L114 _private prototype_ `void SequenceUpdated(const UMovieSceneSequencePlayer& Player, FFrameTime CurrentTime, FFrameTime PreviousTime);` — Called when the level sequence has updated the world
- L117 _private prototype_ `void SetupFrameRange();` — Called to set up the player's playback range
- L120 _private prototype_ `void EnableCinematicMode();` — Enable cinematic mode override
- L123 _private prototype_ `void ExportEDL();` — Export EDL if requested
- L126 _private prototype_ `void ExportFCPXML();` — Export FCPXML if requested
- L129 _private member_ `FDelegateHandle OnPlayerUpdatedBinding;` — Delegate binding for the above callback
- L133 _private prototype_ `virtual void OnTick(float DeltaSeconds) override;`
- L136 _private prototype_ `bool InitializeShots();` — Initialize all the shots to be recorded, ie. expand section ranges with handle frames
- L139 _private prototype_ `bool SetupShot(FFrameNumber& StartTime, FFrameNumber& EndTime);` — Set up the current shot to be recorded, ie. expand playback range to the section range
- L142 _private prototype_ `void RestoreShots();` — Restore any modification to shots
- L145 _private prototype_ `bool RestoreFrameOverrides();` — Restore frame settings from overridden shot frames
- L147 _private prototype_ `void DelayBeforeWarmupFinished();`
- L149 _private prototype_ `void PauseFinished();`
- L154 _private member_ `TWeakObjectPtr<ALevelSequenceActor> LevelSequenceActor;` — `UPROPERTY()` — The pre-existing level sequence actor to use for capture that specifies playback settings
- L157 _private member_ `TWeakPtr<FSceneViewport> Viewport;` — The viewport being captured.
- L169 _private member_ `FinishedWarmUp, Paused, FinishedPause, } CaptureState;`
- L172 _private member_ `int32 RemainingWarmUpFrames;` — The number of warm up frames left before we actually start saving out images
- L175 _private member_ `int32 NumShots;` — The number of individual shot movies to render
- L178 _private member_ `int32 ShotIndex;` — The current shot movie that is rendering
- L180 _private member_ `FLevelSequencePlayerSnapshot CachedState;`
- L182 _private member_ `FTimerHandle DelayTimer;`
- L200 _private member_ `TArray<FCinematicShotCache> CachedShotStates;`
- L201 _private member_ `TRange<FFrameNumber> CachedPlaybackRange;`
- L203 _private member_ `TOptional<FFrameNumber> CachedStartFrame;`
- L204 _private member_ `TOptional<FFrameNumber> CachedEndFrame;`
- L205 _private member_ `TOptional<bool> bCachedUseCustomStartFrame;`
- L206 _private member_ `TOptional<bool> bCachedUseCustomEndFrame;`
- L208 _private member_ `TSharedPtr<FMovieSceneTimeController_FrameStep> TimeController;`
- L211 _private member_ `int32 CachedWarmUpFrameCount;` — We cache these off on initialization so we can restore to them after running an audio pass.
- L212 _private member_ `int32 CachedDelayBeforeWarmUp;`
- L213 _private member_ `int32 CachedDelayBeforeShotWarmUp;`

#### enum `UAutomatedLevelSequenceCapture::ELevelSequenceCaptureState`  
`enum class ELevelSequenceCaptureState`  
_L160-169_
- desc: Which state we're in right now
- L162 _public enumerator_ `Setup`
- L163 _public enumerator_ `DelayBeforeWarmUp`
- L164 _public enumerator_ `ReadyToWarmUp`
- L165 _public enumerator_ `WarmingUp`
- L166 _public enumerator_ `FinishedWarmUp`
- L167 _public enumerator_ `Paused`
- L168 _public enumerator_ `FinishedPause`

#### struct `UAutomatedLevelSequenceCapture::FCinematicShotCache`  
`struct FCinematicShotCache`  
_L184-198_
- L186 _public function_ `FCinematicShotCache(bool bInActive, bool bInLocked, const TRange<FFrameNumber>& InShotRange, const TRange<FFrameNumber>& InMovieSceneRange) : bActive(bInActive) , bLocked(bInLocked) , ShotRange(InShotRange) , MovieSceneRange(InMovieSceneRange)`
- L194 _public member_ `bool bActive;`
- L195 _public member_ `bool bLocked;`
- L196 _public member_ `TRange<FFrameNumber> ShotRange;`
- L197 _public member_ `TRange<FFrameNumber> MovieSceneRange;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MOVIESCENETOOLS_API`

### `Source/Editor/MovieSceneTools/Public/Baker/ISequencerBaker.h` (Public)


#### struct `UE::AIE::FBakeTimeRange`  
`struct FBakeTimeRange`  
_L22-40_
- desc: FBakeTimeRange Object that contains a range of frame numbers that specify an interval to bake over
- L24 _public function_ `FBakeTimeRange() : StartFrame(0), EndFrame(0), DisplayRate(1, 1), TickResolution(1, 1)`
- L29 _public prototype_ `~FBakeTimeRange() = default;`
- L30 _public member_ `FFrameNumber StartFrame;`
- L31 _public member_ `FFrameNumber EndFrame;`
- L32 _public member_ `FFrameNumber FrameStep;`
- L33 _public member_ `FFrameRate DisplayRate;`
- L34 _public member_ `FFrameRate TickResolution;`
- L35 _public member_ `int32 NumFrames = 0;`
- L36 _public member_ `TRange<FFrameNumber> IncomingRange;`
- L38 _public prototype_ `bool UpdateIfNeeded(const TRange<FFrameNumber>& InRange, const FFrameRate& InDisplayRate, const FFrameRate& InTickResolution);`
- L39 _public prototype_ `int32 CalculateIndex(const FFrameNumber& InCurrentFrame) const;`

#### struct `UE::AIE::FBakeTimeIndex`  
`struct FBakeTimeIndex`  
_L48-53_
- desc: FBakeTimeIndex A specific index in the FBakeTimeRange, used to eaily keep track of an index and how it relates to a frame number or a second. This is passed into the recorders on each frame baked.
- L50 _public member_ `int32 Index;`
- L51 _public member_ `FFrameNumber FrameNumber;`
- L52 _public member_ `double DeltaTime;`

#### class `USequencerBakeRecorder`  
`class USequencerBakeRecorder : public UInterface`  
_L57-60_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `ISequencerBakeRecorder`  
`class ISequencerBakeRecorder`  
_L68-86_
- desc: ISequencerBakeRecorder Main interface for an object that records a specific set of data when the bake happens.  For eample an AnimationSequenceBaker would record a specific animation sequence for a specific skel mesh component that you want to record.
- L75 _public prototype_ `virtual uint32 GetHash() = 0;` — virtual ~ISequencerBakeRecorder() is defined above unique ID
- L76 _public prototype_ `virtual void BakeStarted(const UE::AIE::FBakeTimeRange& InRange) = 0;`
- L77 _public prototype_ `virtual void BakeFrame(const UE::AIE::FBakeTimeIndex& InIndex) = 0;`
- L78 _public prototype_ `virtual void BakeCancelled() = 0;`
- L79 _public prototype_ `virtual void BakeFinished() = 0;`
- L80 _public prototype_ `virtual bool HasSequencerBinding(FGuid InGuid) = 0;`
- L81 _public prototype_ `virtual bool IsolateBakeResult(bool bIsolate) = 0;`
- L82 _public prototype_ `virtual void SetRecordingEnabled(bool bInEnabled) = 0;`
- L83 _public prototype_ `virtual bool GetRecordingEnabled() = 0;`
- L84 _public prototype_ `virtual void ReadyToBake() = 0;`
- L85 _public prototype_ `virtual void RemovedFromBake() = 0;`

#### class `UE::AIE::ISequencerBaker`  
`class ISequencerBaker`  
_L97-113_
- L105 _public function_ `virtual ~ISequencerBaker()`
- L106 _public prototype_ `virtual void AddRecorder(TSharedPtr<ISequencerBakeRecorder>& InRecorder, const FRecorderOptions& InOptions) = 0;`
- L107 _public prototype_ `virtual void RemoveRecorder(TSharedPtr<ISequencerBakeRecorder>& InRecorder) = 0;`
- L108 _public prototype_ `virtual FBakeTimeRange GetTimeRange() = 0;`
- L110 _public prototype_ `virtual bool IsBakeRunning(TOptional<float>& OutPercentageDone) = 0;`
- L111 _public prototype_ `virtual void CancelBake() = 0;`

#### struct `UE::AIE::ISequencerBaker::FRecorderOptions`  
`struct FRecorderOptions`  
_L100-104_
- L102 _public member_ `FFrameNumber WarmupFrames = FFrameNumber(0);`
- L103 _public member_ `FFrameNumber DelayBeforeStart = FFrameNumber(0);`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API MOVIESCENETOOLS_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace AIE` (scope `UE`)
- L88 _namespace_ `namespace UE`
- L88 _namespace_ `namespace AIE` (scope `UE`)

### `Source/Editor/MovieSceneTools/Public/Baker/SequencerBaker.h` (Public)


#### class `UE::Sequencer::FSequencerBaker`  
`class FSequencerBaker : public UE::AIE::ISequencerBaker , public FTickableEditorObject , public TSharedFromThis<FSequencerBaker>`  
_L34-207_
- inherits: `UE::AIE::ISequencerBaker,FTickableEditorObject,TSharedFromThis<FSequencerBaker>`
- desc: FSequencerBaker Main object that Bakes within ISequencer, using Sequencer evaluation over the range. It keeps track of track signatures for each recorder to seek if they need to get baked when we switch over to using the baked track
- L41 _public prototype_ `FSequencerBaker();`
- L42 _public function_ `virtual ~FSequencerBaker()`
- L44 _public prototype_ `void Initialize(TSharedPtr<ISequencer>& InSequencer);`
- L45 _public prototype_ `void Release();`
- L48 _public prototype_ `virtual UE::AIE::FBakeTimeRange GetTimeRange() override;`
- L49 _public prototype_ `virtual bool IsBakeRunning(TOptional<float>& OutPercentageDone) override;`
- L50 _public prototype_ `virtual void CancelBake() override;`
- L51 _public prototype_ `virtual void AddRecorder(TSharedPtr<ISequencerBakeRecorder>& InRecorder, const UE::AIE::ISequencerBaker::FRecorderOptions& InOptions) override;`
- L52 _public prototype_ `virtual void RemoveRecorder(TSharedPtr<ISequencerBakeRecorder>& InRecorder) override;`
- L55 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L56 _public function_ `virtual ETickableTickType GetTickableTickType() const override`
- L57 _public function_ `virtual TStatId GetStatId() const override`
- L62 _public prototype_ `void AddAllRecordersToBake();` — add all existing recorders to get baked
- L64 _public prototype_ `void AddExtraRecordersToBake(const TArray<TSharedPtr<ISequencerBakeRecorder>>& InExtraRecorders);` — add extra recorders to get baked just once on next bake
- L66 _public prototype_ `void BakeFullRange();` — bake everything and will remove recorders from bake queue
- L69 _public prototype_ `bool AddRecorderToBake(TSharedPtr<ISequencerBakeRecorder>& InRecorder);` — this adds that recorder that was already added to be baked on next bake time
- L71 _public prototype_ `void IsolateRecorderWithGuid(FGuid InGuid, bool bIsolate);`
- L73 _public prototype_ `void AddSkelMeshCompsToTick(TArray<USkeletalMeshComponent*>& InSkelMeshCompArray);`
- L75 _public prototype_ `void AddSignedObjectsToTrack(TArray<TWeakObjectPtr<UMovieSceneSignedObject>>& InSignedObjects, TSharedPtr<ISequencerBakeRecorder>& Owner);`
- L76 _public prototype_ `void RemoveSignedObjectsFromTrack(TArray<TWeakObjectPtr<UMovieSceneSignedObject>>& InSignedObjects, TSharedPtr<ISequencerBakeRecorder>& Owner);`
- L79 _public prototype_ `void IgnoreLastChange();` — ignore the last change, used mostly for when we isolate the tracks we don't want to trigger a re-baking
- L81 _public function_ `TWeakPtr<ISequencer> GetWeakSequencer() const`
- L85 _public function_ `template<typename... Args> TSharedPtr<ISequencerBakeRecorder>* FindRecorder(Args&&... InArgs)` — finds the recorder by it's signature of arguments
- L95 _public member_ `FOnAddBakeRecorder OnAddBakeRecorder;` — public delegates folks can subscribe for when recorders are added or removed
- L96 _public member_ `FOnRemoveBakeRecorder OnRemoveBakeRecorder;`
- L100 _private prototype_ `void OnPreNavigateToSequenceChanged();` — delegates we subscribe
- L101 _private prototype_ `void OnActivateSequenceChanged(FMovieSceneSequenceIDRef ID);`
- L102 _private prototype_ `void OnMovieSceneBindingsChanged();`
- L103 _private member_ `FDelegateHandle OnPreNavigateToSequenceChangedHandle;`
- L104 _private member_ `FDelegateHandle OnActivateSequenceChangedHandle;`
- L105 _private member_ `FDelegateHandle OnMovieSceneBindingsChangedHandle;`
- L108 _private prototype_ `void SetUpBakeRecorders();` — called when we activate a new sequence
- L158 _private prototype_ `bool CheckForChanges();`
- L159 _private member_ `FGuid LastValidMovieSceneGuid;`
- L164 _private member_ `TWeakPtr<ISequencer> WeakSequencer;` — sequencer and it's interval to bake
- L165 _private member_ `FBakeInterval BakeInterval;`
- L168 _private member_ `FRecorderOptions RecorderOptions;` — contains full set of options e.g. if one anim sequence has delay frame others will also
- L172 _private member_ `TMap<uint32, TSharedPtr<ISequencerBakeRecorder>> Recorders;` — Registered Recorders uses hash as key
- L175 _private member_ `TSet<TSharedPtr<ISequencerBakeRecorder>> BakingRecorders;` — Recorders that are baking
- L176 _private member_ `TArray<TSharedPtr<ISequencerBakeRecorder>> LastBakedRecorders;`
- L179 _private member_ `TSet<TWeakObjectPtr<USkeletalMeshComponent>> SkeletalMeshCompsTick;` — skel meshes to tick that comes from the recorders
- L182 _private member_ `FSignedObjectChanges SignedObjectsToTrack;` — tracked objecs for guid changes
- L186 _private member_ `TArray<IMovieSceneToolsAnimationBakeHelper*> BakeHelpers;` — cached items during the bake
- L187 _private member_ `FMovieSceneInverseSequenceTransform LocalToRootTransform;`
- L189 _private member_ `UWorld* World;` — this is cached during set of functions
- L194 _private member_ `bool bNeedsBaking = false;` — functions used during the Bake
- L195 _private member_ `bool bIsBaking = false;`
- L196 _private prototype_ `void BakeStarted();`
- L197 _private prototype_ `void BakeFrame();`
- L198 _private prototype_ `void BakeCancelled();`
- L199 _private prototype_ `void BakeFinished();`
- L200 _private prototype_ `void BakeFramesTillDone();`
- L201 _private prototype_ `bool TickFrameInternal(const FFrameNumber& FrameNumber, float DeltaTime);`
- L206 _private prototype_ `void IsolateBakedTracks(TArray<TSharedPtr<ISequencerBakeRecorder>>& InRecorders, bool bIsolate);` — used when we navigate to another sequence, we isolate and turn on the baked items for performance

#### struct `UE::Sequencer::FSequencerBaker::FBakeInterval`  
`struct FBakeInterval`  
_L113-133_
- desc: internal struct to set up time range based upon sequencer frame range
- L115 _public prototype_ `FBakeInterval() = default;`
- L117 _public prototype_ `bool SetFromSequencer(ISequencer* InSequencer);`
- L118 _public prototype_ `void Clear();`
- L119 _public prototype_ `bool IsFrameCalcuated(int32 Index);`
- L120 _public prototype_ `void SetFrameCalculated(int32 Index);`
- L123 _public prototype_ `int32 NextFrameToCalculate();` — will return INDEX_NONE if no more to calculate
- L124 _public prototype_ `bool IsDoneCalculating() const;`
- L126 _public member_ `UE::AIE::FBakeTimeRange TimeRange;`
- L127 _public member_ `FFrameNumber DelayBeforeStart = FFrameNumber(0);`
- L128 _public member_ `FFrameNumber WarmupFrames = FFrameNumber(0);`
- L131 _private member_ `TBitArray<> CalculatedFrames;`

#### struct `UE::Sequencer::FSequencerBaker::FSignedObjectState`  
`struct FSignedObjectState`  
_L139-144_
- desc: internal objects that contains a movie scene signed object(track) last guid and the bakers that reference we keep of these guids and if the LastValidMovieSceneGuid changes we see which of these track guids have changed. this was we only re-bake what's needed.
- L141 _public member_ `TSet<TSharedPtr<ISequencerBakeRecorder>> Owners;`
- L142 _public member_ `FGuid Guid;`
- L143 _public member_ `TArray<bool> DisabledArray;` — if it's a track we keep track of this since if it get's enabled/disabled we ignore the change

#### struct `UE::Sequencer::FSequencerBaker::FSignedObjectChanges`  
`struct FSignedObjectChanges`  
_L145-156_
- L147 _public prototype_ `void AddObject(UMovieSceneSignedObject* InObject, TSharedPtr<ISequencerBakeRecorder>& Owner);`
- L148 _public prototype_ `void RemoveObject(UMovieSceneSignedObject* InObject, TSharedPtr<ISequencerBakeRecorder>& Owner);`
- L149 _public function_ `void AddIgnoreObject(UMovieSceneSignedObject* InObject)`
- L150 _public function_ `void RemoveIgnoreObject(UMovieSceneSignedObject* InObject)`
- L153 _public prototype_ `TArray<TSharedPtr<ISequencerBakeRecorder>> UpdateSignatures();` — returns list of recorders that have changed
- L154 _public member_ `TMap<TWeakObjectPtr<UMovieSceneSignedObject>, FSignedObjectState> ObjectSignatures;`
- L155 _public member_ `TSet <TWeakObjectPtr<UMovieSceneSignedObject>> IgnoredObjects;`

#### Free symbols / members of external scopes

- L20 _macro_ `#define UE_API MOVIESCENETOOLS_API`
- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace Sequencer` (scope `UE`)
- L25 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnAddBakeRecorder, ISequencerBakeRecorder*);` — delegates fired when we add or remove a bake recorder
- L25 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnAddBakeRecorder, ISequencerBakeRecorder*);` (scope `UE::Sequencer`) — delegates fired when we add or remove a bake recorder
- L26 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnRemoveBakeRecorder, ISequencerBakeRecorder*);`
- L26 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnRemoveBakeRecorder, ISequencerBakeRecorder*);` (scope `UE::Sequencer`)

### `Source/Editor/MovieSceneTools/Public/Baker/SequencerBakerSubsystem.h` (Public)


#### class `USequencerBakeSubsystem`  
`class USequencerBakeSubsystem : public UEditorSubsystem`  
_L25-47_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEditorSubsystem`
- desc: USequencerBakeSubsystem Simple Editor Subsystem that acts like a Singleton, that holds a Sequencer Baker object for each open ISequencer object.
- L32 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L33 _public prototype_ `virtual void Deinitialize() override;`
- L35 _public prototype_ `void OnSequencerCreated(TSharedRef<ISequencer> InSequencer);`
- L37 _public prototype_ `void OnSequencerClosed(TSharedRef<ISequencer> InSequencer);`
- L39 _public prototype_ `TSharedPtr<UE::Sequencer::FSequencerBaker> GetSequencerBaker(const TSharedPtr<ISequencer>& InSequencer);`
- L42 _private member_ `FDelegateHandle OnSequencerCreatedHandle;`
- L45 _private member_ `TMap<TWeakPtr<ISequencer>, TSharedPtr<UE::Sequencer::FSequencerBaker>> Sequencers;` — list of created sequencers

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Sequencer` (scope `UE`)
- L17 _macro_ `#define UE_API MOVIESCENETOOLS_API`

### `Source/Editor/MovieSceneTools/Public/BakingAnimationKeySettings.h` (Public)


#### enum `EBakingKeySettings`  
`enum class EBakingKeySettings : uint8`  
_L9-13_
- reflection: `UENUM(Blueprintable)`
- L11 _public enumerator_ `KeysOnly UMETA(DisplayName = "Keys Only")`
- L12 _public enumerator_ `AllFrames UMETA(DisplayName = "All Frames")`

#### struct `FBakingAnimationKeySettings`  
`struct FBakingAnimationKeySettings`  
_L16-56_
- reflection: `USTRUCT(BlueprintType)`
- L20 _public function_ `FBakingAnimationKeySettings()`
- L32 _public member_ `FFrameNumber StartFrame;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Bake")`
- L35 _public member_ `FFrameNumber EndFrame;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Bake")`
- L39 _public member_ `EBakingKeySettings BakingKeySettings;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Bake")` — Bake on keyed frames only or bake all frames between start and end
- L43 _public member_ `int32 FrameIncrement;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Bake", meta = (ClampMin = "1", UIMin = "1", EditCondition = "BakingKeySettings == EBakingKeySettings::AllFrames"))` — Frames to increment when baking
- L47 _public member_ `bool bReduceKeys;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Bake", meta = (EditCondition = "BakingKeySettings == EBakingKeySettings::AllFrames"))` — Reduce keys after baking
- L51 _public member_ `float Tolerance;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Bake", meta = (EditCondition = "BakingKeySettings == EBakingKeySettings::AllFrames || bReduceKeys"))` — Tolerance to use when reducing keys
- L55 _public member_ `bool bTimeWarp;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Bake")` — Bake with time warp applied. If there is time warp on the sequence, you will need to disable it manually after baking, otherwise times will be warped twice.

### `Source/Editor/MovieSceneTools/Public/Bindings/MovieSceneSpawnableActorBindingCustomization.h` (Public)


#### class `FMovieSceneSpawnableActorBindingBaseCustomization`  
`class FMovieSceneSpawnableActorBindingBaseCustomization : public FMovieSceneSpawnableBindingCustomization`  
_L15-39_
- inherits: `FMovieSceneSpawnableBindingCustomization`
- L19 _public function_ `FMovieSceneSpawnableActorBindingBaseCustomization(TWeakPtr<ISequencer> InSequencer, UMovieScene* InMovieScene, FGuid InBindingGuid) : FMovieSceneSpawnableBindingCustomization(InMovieScene, InBindingGuid) , SequencerPtr(InSequencer)`
- L23 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance(TWeakPtr<ISequencer> InSequencer, UMovieScene* InMovieScene, FGuid InBindingGuid);`
- L24 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L26 _public member_ `TWeakPtr<ISequencer> SequencerPtr;`
- L28 _public member_ `TSharedPtr<IPropertyHandle> SpawnLevelProperty;`
- L31 _public member_ `TSharedPtr<STextComboBox> LevelNameComboBox;` — level names
- L32 _public member_ `TArray< TSharedPtr< FString > > LevelNameComboListItems;`
- L33 _public member_ `TArray<FName> LevelNameList;`
- L34 _public member_ `FName LevelNameComboSelectedName;`
- L36 _public prototype_ `void OnLevelNameChanged(TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo);`
- L37 _public prototype_ `void RefreshComboList();`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace ESelectInfo`

### `Source/Editor/MovieSceneTools/Public/Bindings/MovieSceneSpawnableBindingCustomization.h` (Public)


#### class `FMovieSceneSpawnableBindingCustomization`  
`class FMovieSceneSpawnableBindingCustomization : public IDetailCustomization`  
_L13-33_
- inherits: `IDetailCustomization`
- L17 _public function_ `FMovieSceneSpawnableBindingCustomization(UMovieScene* InMovieScene, FGuid InBindingGuid) : MovieScene(InMovieScene) , BindingGuid(InBindingGuid)`
- L22 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance(UMovieScene* InMovieScene, FGuid InBindingGuid);`
- L23 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L28 _private prototype_ `void OnSpawnOwnershipChanged();`
- L29 _private member_ `TObjectPtr<UMovieScene> MovieScene = nullptr;`
- L30 _private member_ `FGuid BindingGuid;`
- L32 _private member_ `TSharedPtr<IPropertyHandle> SpawnOwnershipProperty;`

### `Source/Editor/MovieSceneTools/Public/Channels/BezierChannelCurveModel.h` (Public)


#### class `FBezierChannelBufferedCurveModel`  
`template<typename ChannelType> class FBezierChannelBufferedCurveModel : public IBufferedCurveModel`  
_L39-52_
- inherits: `IBufferedCurveModel`
- desc: Buffered curve implementation for a bezier curve model, stores a copy of the bezier curve channel in order to draw itself.
- L43 _public prototype_ `FBezierChannelBufferedCurveModel(const ChannelType* InChannel, TWeakObjectPtr<UMovieSceneSection> InWeakSection, TArray<FKeyPosition>&& InKeyPositions, TArray<FKeyAttributes>&& InKeyAttributes, const FString& InLongDisplayName, const double InValueMin, const double InValueMax);` — Create a copy of the channel while keeping the reference to the section
- L46 _public prototype_ `virtual void DrawCurve(const FCurveEditor& InCurveEditor, const FCurveEditorScreenSpace& InScreenSpace, TArray<TTuple<double, double>>& OutInterpolatingPoints) const override;`
- L47 _public prototype_ `virtual bool Evaluate(double InTime, double& OutValue) const override;`
- L50 _private member_ `ChannelType Channel;`
- L51 _private member_ `TWeakObjectPtr<UMovieSceneSection> WeakSection;`

#### class `FBezierChannelCurveModel`  
`template<typename ChannelType, typename ChannelValue, typename KeyType> class FBezierChannelCurveModel : public FChannelCurveModel<ChannelType, ChannelValue, KeyType>`  
_L58-100_
- inherits: `FChannelCurveModel<ChannelType,ChannelValue,KeyType>`
- desc: Implementation of a bezier curve model.
- L60 _private typedef_ `using Super = FChannelCurveModel<ChannelType, ChannelValue, KeyType>;`
- L63 _public prototype_ `FBezierChannelCurveModel(TMovieSceneChannelHandle<ChannelType> InChannel, UMovieSceneSection* InOwningSection, TWeakPtr<ISequencer> InWeakSequencer);`
- L64 _public prototype_ `FBezierChannelCurveModel(TMovieSceneChannelHandle<ChannelType> InChannel, UMovieSceneSection* InOwningSection, UObject* InOwningObject, TWeakPtr<ISequencer> InWeakSequencer);`
- L67 _public prototype_ `virtual void DrawCurve(const FCurveEditor& CurveEditor, const FCurveEditorScreenSpace& ScreenSpace, TArray<TTuple<double, double>>& InterpolatingPoints) const override;` — FCurveModel
- L68 _public prototype_ `virtual UE::CurveEditor::ICurveEditorCurveCachePool* DrawCurveToCachePool(const TSharedRef<FCurveEditor>& CurveEditor, const UE::CurveEditor::FCurveDrawParamsHandle& CurveDrawParamsHandle, const FCurveEditorScreenSpace& ScreenSpace) override;`
- L69 _public prototype_ `virtual bool HasChangedAndResetTest() override;`
- L70 _public prototype_ `virtual void GetKeyDrawInfo(ECurvePointType PointType, const FKeyHandle InKeyHandle, FKeyDrawInfo& OutDrawInfo) const override;`
- L72 _public prototype_ `virtual void GetKeyAttributes(TArrayView<const FKeyHandle> InKeys, TArrayView<FKeyAttributes> OutAttributes) const override;`
- L73 _public prototype_ `virtual void GetKeyAttributesExcludingAutoComputed(TArrayView<const FKeyHandle> InKeys, TArrayView<FKeyAttributes> OutAttributes) const override;`
- L74 _public prototype_ `virtual void SetKeyAttributes(TArrayView<const FKeyHandle> InKeys, TArrayView<const FKeyAttributes> InAttributes, EPropertyChangeType::Type ChangeType = EPropertyChangeType::Unspecified) override;`
- L76 _public prototype_ `virtual TPair<ERichCurveInterpMode, ERichCurveTangentMode> GetInterpolationMode(const double& InTime, ERichCurveInterpMode DefaultInterpolationMode, ERichCurveTangentMode DefaultTangentMode) const override;`
- L77 _public prototype_ `virtual void GetCurveAttributes(FCurveAttributes& OutCurveAttributes) const override;`
- L78 _public prototype_ `virtual void SetCurveAttributes(const FCurveAttributes& InCurveAttributes) override;`
- L79 _public prototype_ `virtual void GetValueRange(double& MinValue, double& MaxValue) const override;`
- L80 _public prototype_ `virtual void GetValueRange(double InMinTime, double InMaxTime, double& MinValue, double& MaxValue) const override;`
- L82 _public prototype_ `virtual bool HasDefaultValue() const override;`
- L83 _public prototype_ `virtual double GetDefaultValue() const override;`
- L87 _protected prototype_ `virtual double GetKeyValue(TArrayView<const ChannelValue> Values, int32 Index) const override;` — FChannelCurveModel
- L88 _protected prototype_ `virtual void SetKeyValue(int32 Index, double KeyValue) const override;`
- L90 _protected member_ `TSharedPtr<UE::MovieSceneTools::FMovieSceneCachedCurve<ChannelType>> CachedCurve;`
- L96 _protected prototype_ `void OnPostOwnerChanged(TNotNull<UMovieSceneSignedObject*> InSignedOwner);` — Updates all dependent systems after a change has been made to owning object. Calls MarkAsChanged, dirties the package, and FCurveModel::OnCurvesModified.
- L99 _private prototype_ `void FeaturePointMethod(double StartTime, double EndTime, double StartValue, double Mu, int Depth, int MaxDepth, double& MaxV, double& MinVal) const;`

#### Free symbols / members of external scopes

- L33 _namespace_ `namespace UE`
- L33 _namespace_ `namespace MovieSceneTools` (scope `UE`)

### `Source/Editor/MovieSceneTools/Public/Channels/BoolChannelCurveModel.h` (Public)


#### class `FBoolChannelCurveModel`  
`class FBoolChannelCurveModel : public FChannelCurveModel<FMovieSceneBoolChannel, bool, bool>`  
_L25-41_
- inherits: `FChannelCurveModel<FMovieSceneBoolChannel,bool,bool>`
- L28 _public prototype_ `FBoolChannelCurveModel(TMovieSceneChannelHandle<FMovieSceneBoolChannel> InChannel, UMovieSceneSection* InOwningSection, TWeakPtr<ISequencer> InWeakSequencer);`
- L31 _public prototype_ `virtual void CreateKeyProxies(TWeakPtr<FCurveEditor> InWeakCurveEditor, FCurveModelID InCurveModelID, TArrayView<const FKeyHandle> InKeyHandles, TArrayView<UObject*> OutObjects) override;` — FCurveModel
- L32 _public prototype_ `virtual TUniquePtr<IBufferedCurveModel> CreateBufferedCurveCopy() const override;`
- L33 _public prototype_ `virtual void GetCurveAttributes(FCurveAttributes& OutAttributes) const override;`
- L34 _public prototype_ `virtual void SetCurveAttributes(const FCurveAttributes& InAttributes) override;`
- L39 _protected prototype_ `virtual double GetKeyValue(TArrayView<const bool> Values, int32 Index) const override;` — FChannelCurveModel
- L40 _protected prototype_ `virtual void SetKeyValue(int32 Index, double KeyValue) const override;`

### `Source/Editor/MovieSceneTools/Public/Channels/BuiltInChannelEditors.h` (Public)


#### Free symbols / members of external scopes

- L39 _prototype_ `FKeyHandle AddOrUpdateKey(FMovieSceneDoubleChannel* Channel, UMovieSceneSection* SectionToKey, const TMovieSceneExternalValue<double>& EditorData, FFrameNumber InTime, ISequencer& Sequencer, const FGuid& InObjectBindingID, FTrackInstancePropertyBindings* PropertyBindings);` — Overrides for adding or updating a key for non-standard channels
- L40 _prototype_ `FKeyHandle AddOrUpdateKey(FMovieSceneFloatChannel* Channel, UMovieSceneSection* SectionToKey, const TMovieSceneExternalValue<float>& EditorData, FFrameNumber InTime, ISequencer& Sequencer, const FGuid& InObjectBindingID, FTrackInstancePropertyBindings* PropertyBindings);`
- L41 _prototype_ `FKeyHandle AddOrUpdateKey(FMovieSceneActorReferenceChannel* Channel, UMovieSceneSection* SectionToKey, FFrameNumber InTime, ISequencer& Sequencer, const FGuid& InObjectBindingID, FTrackInstancePropertyBindings* PropertyBindings);`
- L42 _prototype_ `FKeyHandle AddOrUpdateKey(FMovieSceneTimeWarpChannel* Channel, UMovieSceneSection* SectionToKey, FFrameNumber InTime, ISequencer& Sequencer, const FGuid& InObjectBindingID, FTrackInstancePropertyBindings* PropertyBindings);`
- L45 _prototype_ `bool CanCreateKeyEditor(const FMovieSceneBoolChannel* Channel);` — Key editor overrides
- L46 _prototype_ `bool CanCreateKeyEditor(const FMovieSceneByteChannel* Channel);`
- L47 _prototype_ `bool CanCreateKeyEditor(const FMovieSceneIntegerChannel* Channel);`
- L48 _prototype_ `bool CanCreateKeyEditor(const FMovieSceneDoubleChannel* Channel);`
- L49 _prototype_ `bool CanCreateKeyEditor(const FMovieSceneFloatChannel* Channel);`
- L50 _prototype_ `bool CanCreateKeyEditor(const FMovieSceneStringChannel* Channel);`
- L51 _prototype_ `bool CanCreateKeyEditor(const FMovieSceneTextChannel* Channel);`
- L52 _prototype_ `bool CanCreateKeyEditor(const FMovieSceneObjectPathChannel* Channel);`
- L53 _prototype_ `bool CanCreateKeyEditor(const FMovieSceneActorReferenceChannel* Channel);`
- L55 _prototype_ `TSharedRef<SWidget> CreateKeyEditor(const TMovieSceneChannelHandle<FMovieSceneBoolChannel>& Channel, const UE::Sequencer::FCreateKeyEditorParams& Params);`
- L56 _prototype_ `TSharedRef<SWidget> CreateKeyEditor(const TMovieSceneChannelHandle<FMovieSceneByteChannel>& Channel, const UE::Sequencer::FCreateKeyEditorParams& Params);`
- L57 _prototype_ `TSharedRef<SWidget> CreateKeyEditor(const TMovieSceneChannelHandle<FMovieSceneIntegerChannel>& Channel, const UE::Sequencer::FCreateKeyEditorParams& Params);`
- L58 _prototype_ `TSharedRef<SWidget> CreateKeyEditor(const TMovieSceneChannelHandle<FMovieSceneDoubleChannel>& Channel, const UE::Sequencer::FCreateKeyEditorParams& Params);`
- L59 _prototype_ `TSharedRef<SWidget> CreateKeyEditor(const TMovieSceneChannelHandle<FMovieSceneFloatChannel>& Channel, const UE::Sequencer::FCreateKeyEditorParams& Params);`
- L60 _prototype_ `TSharedRef<SWidget> CreateKeyEditor(const TMovieSceneChannelHandle<FMovieSceneStringChannel>& Channel, const UE::Sequencer::FCreateKeyEditorParams& Params);`
- L61 _prototype_ `TSharedRef<SWidget> CreateKeyEditor(const TMovieSceneChannelHandle<FMovieSceneTextChannel>& Channel, const UE::Sequencer::FCreateKeyEditorParams& Params);`
- L62 _prototype_ `TSharedRef<SWidget> CreateKeyEditor(const TMovieSceneChannelHandle<FMovieSceneObjectPathChannel>& Channel, const UE::Sequencer::FCreateKeyEditorParams& Params);`
- L63 _prototype_ `TSharedRef<SWidget> CreateKeyEditor(const TMovieSceneChannelHandle<FMovieSceneActorReferenceChannel>& Channel, const UE::Sequencer::FCreateKeyEditorParams& Params);`
- L64 _prototype_ `TSharedRef<SWidget> CreateKeyEditor(const TMovieSceneChannelHandle<FMovieSceneTimeWarpChannel>& Channel, const UE::Sequencer::FCreateKeyEditorParams& Params);`
- L66 _prototype_ `UMovieSceneKeyStructType* InstanceGeneratedStruct(FMovieSceneByteChannel* Channel, FSequencerKeyStructGenerator* Generator);`
- L67 _prototype_ `UMovieSceneKeyStructType* InstanceGeneratedStruct(FMovieSceneTimeWarpChannel* Channel, FSequencerKeyStructGenerator* Generator);`
- L68 _prototype_ `UMovieSceneKeyStructType* InstanceGeneratedStruct(FMovieSceneTextChannel* Channel, FSequencerKeyStructGenerator* Generator);`
- L69 _prototype_ `UMovieSceneKeyStructType* InstanceGeneratedStruct(FMovieSceneObjectPathChannel* Channel, FSequencerKeyStructGenerator* Generator);`
- L71 _prototype_ `void PostConstructKeyInstance(const TMovieSceneChannelHandle<FMovieSceneTimeWarpChannel>& ChannelHandle, FKeyHandle InHandle, FStructOnScope* Struct);`
- L72 _prototype_ `void PostConstructKeyInstance(const TMovieSceneChannelHandle<FMovieSceneObjectPathChannel>& ChannelHandle, FKeyHandle InHandle, FStructOnScope* Struct);`
- L73 _prototype_ `void PostConstructKeyInstance(const TMovieSceneChannelHandle<FMovieSceneDoubleChannel>& ChannelHandle, FKeyHandle InHandle, FStructOnScope* Struct);`
- L74 _prototype_ `void PostConstructKeyInstance(const TMovieSceneChannelHandle<FMovieSceneTextChannel>& ChannelHandle, FKeyHandle InHandle, FStructOnScope* Struct);`
- L77 _prototype_ `void DrawKeys(FMovieSceneDoubleChannel* Channel, TArrayView<const FKeyHandle> InKeyHandles, const UMovieSceneSection* InOwner, TArrayView<FKeyDrawParams> OutKeyDrawParams);` — Key drawing overrides
- L78 _prototype_ `void DrawKeys(FMovieSceneFloatChannel* Channel, TArrayView<const FKeyHandle> InKeyHandles, const UMovieSceneSection* InOwner, TArrayView<FKeyDrawParams> OutKeyDrawParams);`
- L79 _prototype_ `void DrawKeys(FMovieSceneParticleChannel* Channel, TArrayView<const FKeyHandle> InKeyHandles, const UMovieSceneSection* InOwner, TArrayView<FKeyDrawParams> OutKeyDrawParams);`
- L80 _prototype_ `void DrawKeys(FMovieSceneEventChannel* Channel, TArrayView<const FKeyHandle> InKeyHandles, const UMovieSceneSection* InOwner, TArrayView<FKeyDrawParams> OutKeyDrawParams);`
- L83 _prototype_ `void ExtendSectionMenu(FMenuBuilder& OuterMenuBuilder, TSharedPtr<FExtender> MenuExtender, TArray<TMovieSceneChannelHandle<FMovieSceneDoubleChannel>>&& Channels, const TArray<TWeakObjectPtr<UMovieSceneSection>>& InWeakSections, TWeakPtr<ISequencer> InWeakSequencer);` — Context menu overrides
- L84 _prototype_ `void ExtendSectionMenu(FMenuBuilder& OuterMenuBuilder, TSharedPtr<FExtender> MenuExtender, TArray<TMovieSceneChannelHandle<FMovieSceneFloatChannel>>&& Channels, const TArray<TWeakObjectPtr<UMovieSceneSection>>& InWeakSections, TWeakPtr<ISequencer> InWeakSequencer);`
- L85 _prototype_ `void ExtendSectionMenu(FMenuBuilder& OuterMenuBuilder, TSharedPtr<FExtender> MenuExtender, TArray<TMovieSceneChannelHandle<FMovieSceneIntegerChannel>>&& Channels, const TArray<TWeakObjectPtr<UMovieSceneSection>>& InWeakSections, TWeakPtr<ISequencer> InWeakSequencer);`
- L86 _prototype_ `void ExtendSectionMenu(FMenuBuilder& OuterMenuBuilder, TSharedPtr<FExtender> MenuExtender, TArray<TMovieSceneChannelHandle<FMovieSceneBoolChannel>>&& Channels, const TArray<TWeakObjectPtr<UMovieSceneSection>>& InWeakSections, TWeakPtr<ISequencer> InWeakSequencer);`
- L87 _prototype_ `void ExtendSectionMenu(FMenuBuilder& OuterMenuBuilder, TSharedPtr<FExtender> MenuExtender, TArray<TMovieSceneChannelHandle<FMovieSceneByteChannel>>&& Channels, const TArray<TWeakObjectPtr<UMovieSceneSection>>& InWeakSections, TWeakPtr<ISequencer> InWeakSequencer);`
- L89 _prototype_ `TSharedPtr<ISidebarChannelExtension> ExtendSidebarMenu(FMenuBuilder& OuterMenuBuilder, TSharedPtr<FExtender> MenuExtender, TArray<TMovieSceneChannelHandle<FMovieSceneDoubleChannel>>&& InChannels, const TArray<TWeakObjectPtr<UMovieSceneSection>>& InWeakSections, TWeakPtr<ISequencer> InWeakSequencer);`
- L90 _prototype_ `TSharedPtr<ISidebarChannelExtension> ExtendSidebarMenu(FMenuBuilder& OuterMenuBuilder, TSharedPtr<FExtender> MenuExtender, TArray<TMovieSceneChannelHandle<FMovieSceneFloatChannel>>&& InChannels,const TArray<TWeakObjectPtr<UMovieSceneSection>>& InWeakSections, TWeakPtr<ISequencer> InWeakSequencer);`
- L91 _prototype_ `TSharedPtr<ISidebarChannelExtension> ExtendSidebarMenu(FMenuBuilder& OuterMenuBuilder, TSharedPtr<FExtender> MenuExtender, TArray<TMovieSceneChannelHandle<FMovieSceneIntegerChannel>>&& InChannels, const TArray<TWeakObjectPtr<UMovieSceneSection>>& InWeakSections, TWeakPtr<ISequencer> InWeakSequencer);`
- L92 _prototype_ `TSharedPtr<ISidebarChannelExtension> ExtendSidebarMenu(FMenuBuilder& OuterMenuBuilder, TSharedPtr<FExtender> MenuExtender, TArray<TMovieSceneChannelHandle<FMovieSceneBoolChannel>>&& InChannels, const TArray<TWeakObjectPtr<UMovieSceneSection>>& InWeakSections, TWeakPtr<ISequencer> InWeakSequencer);`
- L93 _prototype_ `TSharedPtr<ISidebarChannelExtension> ExtendSidebarMenu(FMenuBuilder& OuterMenuBuilder, TSharedPtr<FExtender> MenuExtender, TArray<TMovieSceneChannelHandle<FMovieSceneByteChannel>>&& InChannels, const TArray<TWeakObjectPtr<UMovieSceneSection>>& InWeakSections, TWeakPtr<ISequencer> InWeakSequencer);`
- L95 _prototype_ `void ExtendKeyMenu(FMenuBuilder& OuterMenuBuilder, TSharedPtr<FExtender> MenuExtender, TArray<TExtendKeyMenuParams<FMovieSceneDoubleChannel>>&& Channels, TWeakPtr<ISequencer> InSequencer);`
- L96 _prototype_ `void ExtendKeyMenu(FMenuBuilder& OuterMenuBuilder, TSharedPtr<FExtender> MenuExtender, TArray<TExtendKeyMenuParams<FMovieSceneFloatChannel>>&& Channels, TWeakPtr<ISequencer> InSequencer);`
- L97 _prototype_ `void ExtendKeyMenu(FMenuBuilder& OuterMenuBuilder, TSharedPtr<FExtender> MenuExtender, TArray<TExtendKeyMenuParams<FMovieSceneTimeWarpChannel>>&& Channels, TWeakPtr<ISequencer> InSequencer);`
- L100 _function_ `inline bool SupportsCurveEditorModels(const TMovieSceneChannelHandle<FMovieSceneDoubleChannel>& DoubleChannel)` — Curve editor models
- L101 _function_ `inline bool SupportsCurveEditorModels(const TMovieSceneChannelHandle<FMovieSceneFloatChannel>& FloatChannel)`
- L102 _function_ `inline bool SupportsCurveEditorModels(const TMovieSceneChannelHandle<FMovieSceneIntegerChannel>& IntegerChannel)`
- L103 _function_ `inline bool SupportsCurveEditorModels(const TMovieSceneChannelHandle<FMovieSceneBoolChannel>& BoolChannel)`
- L104 _function_ `inline bool SupportsCurveEditorModels(const TMovieSceneChannelHandle<FMovieSceneByteChannel>& ByteChannel)`
- L105 _function_ `inline bool SupportsCurveEditorModels(const TMovieSceneChannelHandle<FMovieSceneEventChannel>& EventChannel)`
- L106 _function_ `inline bool SupportsCurveEditorModels(const TMovieSceneChannelHandle<FMovieSceneTimeWarpChannel>& TimeWarpChannel)`
- L108 _prototype_ `TUniquePtr<FCurveModel> CreateCurveEditorModel(const TMovieSceneChannelHandle<FMovieSceneDoubleChannel>& DoubleChannel, const UE::Sequencer::FCreateCurveEditorModelParams& Params);`
- L109 _prototype_ `TUniquePtr<FCurveModel> CreateCurveEditorModel(const TMovieSceneChannelHandle<FMovieSceneFloatChannel>& FloatChannel, const UE::Sequencer::FCreateCurveEditorModelParams& Params);`
- L110 _prototype_ `TUniquePtr<FCurveModel> CreateCurveEditorModel(const TMovieSceneChannelHandle<FMovieSceneIntegerChannel>& IntegerChannel, const UE::Sequencer::FCreateCurveEditorModelParams& Params);`
- L111 _prototype_ `TUniquePtr<FCurveModel> CreateCurveEditorModel(const TMovieSceneChannelHandle<FMovieSceneBoolChannel>& BoolChannel, const UE::Sequencer::FCreateCurveEditorModelParams& Params);`
- L112 _prototype_ `TUniquePtr<FCurveModel> CreateCurveEditorModel(const TMovieSceneChannelHandle<FMovieSceneByteChannel>& ByteChannel, const UE::Sequencer::FCreateCurveEditorModelParams& Params);`
- L113 _prototype_ `TUniquePtr<FCurveModel> CreateCurveEditorModel(const TMovieSceneChannelHandle<FMovieSceneEventChannel>& EventChannel, const UE::Sequencer::FCreateCurveEditorModelParams& Params);`
- L114 _prototype_ `TUniquePtr<FCurveModel> CreateCurveEditorModel(const TMovieSceneChannelHandle<FMovieSceneTimeWarpChannel>& TimeWarpChannel, const UE::Sequencer::FCreateCurveEditorModelParams& Params);`
- L116 _prototype_ `bool ShouldShowCurve(const FMovieSceneFloatChannel* Channel, UMovieSceneSection* InSection);`
- L117 _prototype_ `bool ShouldShowCurve(const FMovieSceneDoubleChannel* Channel, UMovieSceneSection* InSection);`
- L119 _prototype_ `TSharedPtr<UE::Sequencer::FChannelModel> CreateChannelModel(const TMovieSceneChannelHandle<FMovieSceneTimeWarpChannel>& InChannelHandle, const UE::Sequencer::FSectionModel& InSection, FName InChannelName);`

### `Source/Editor/MovieSceneTools/Public/Channels/ByteChannelCurveModel.h` (Public)


#### class `FByteChannelCurveModel`  
`class FByteChannelCurveModel : public FChannelCurveModel<FMovieSceneByteChannel, uint8, uint8>`  
_L21-37_
- inherits: `FChannelCurveModel<FMovieSceneByteChannel,uint8,uint8>`
- L24 _public prototype_ `FByteChannelCurveModel(TMovieSceneChannelHandle<FMovieSceneByteChannel> InChannel, UMovieSceneSection* InOwningSection, TWeakPtr<ISequencer> InWeakSequencer);`
- L27 _public prototype_ `virtual void CreateKeyProxies(TWeakPtr<FCurveEditor> InWeakCurveEditor, FCurveModelID InCurveModelID, TArrayView<const FKeyHandle> InKeyHandles, TArrayView<UObject*> OutObjects) override;` — FCurveModel
- L28 _public prototype_ `virtual TUniquePtr<IBufferedCurveModel> CreateBufferedCurveCopy() const override;`
- L29 _public prototype_ `virtual void GetCurveAttributes(FCurveAttributes& OutAttributes) const override;`
- L30 _public prototype_ `virtual void SetCurveAttributes(const FCurveAttributes& InAttributes) override;`
- L34 _protected prototype_ `virtual double GetKeyValue(TArrayView<const uint8> Values, int32 Index) const override;` — FChannelCurveModel
- L35 _protected prototype_ `virtual void SetKeyValue(int32 Index, double KeyValue) const override;`

### `Source/Editor/MovieSceneTools/Public/Channels/ChannelCurveModel.h` (Public)


#### class `FChannelCurveModel`  
`template <class ChannelType, class ChannelValue, class KeyType> class FChannelCurveModel : public FCurveModel`  
_L40-141_
- inherits: `FCurveModel`
- L43 _public prototype_ `FChannelCurveModel(TMovieSceneChannelHandle<ChannelType> InChannel, UMovieSceneSection* InOwningSection, TWeakPtr<ISequencer> InWeakSequencer);`
- L44 _public prototype_ `FChannelCurveModel(TMovieSceneChannelHandle<ChannelType> InChannel, UMovieSceneSection* InOwningSection, UObject* InOwningObject, TWeakPtr<ISequencer> InWeakSequencer);`
- L46 _public prototype_ `~FChannelCurveModel();`
- L48 _public prototype_ `virtual const void* GetCurve() const override;`
- L50 _public prototype_ `virtual void Modify() override;`
- L51 _public prototype_ `virtual void OnCloseRootChangeScope() override;`
- L53 _public prototype_ `virtual void DrawCurve(const FCurveEditor& CurveEditor, const FCurveEditorScreenSpace& ScreenSpace, TArray<TTuple<double, double>>& OutInterpolatingPoints) const override;`
- L54 _public prototype_ `virtual void GetKeys(double MinTime, double MaxTime, double MinValue, double MaxValue, TArray<FKeyHandle>& OutKeyHandles) const override;`
- L55 _public prototype_ `virtual void GetAllKeys(TArray<FKeyHandle>& OutKeyHandles) const override;`
- L56 _public prototype_ `virtual void GetKeyDrawInfo(ECurvePointType PointType, const FKeyHandle InKeyHandle, FKeyDrawInfo& OutDrawInfo) const override;`
- L58 _public prototype_ `virtual void GetKeyPositions(TArrayView<const FKeyHandle> InKeys, TArrayView<FKeyPosition> OutKeyPositions) const override;`
- L59 _public prototype_ `virtual void SetKeyPositions(TArrayView<const FKeyHandle> InKeys, TArrayView<const FKeyPosition> InKeyPositions, EPropertyChangeType::Type ChangeType = EPropertyChangeType::Unspecified) override;`
- L61 _public prototype_ `virtual void GetCurveAttributes(FCurveAttributes& OutCurveAttributes) const override;`
- L62 _public prototype_ `virtual void GetTimeRange(double& MinTime, double& MaxTime) const override;`
- L63 _public prototype_ `virtual void GetValueRange(double& MinValue, double& MaxValue) const override;`
- L64 _public prototype_ `virtual int32 GetNumKeys() const override;`
- L65 _public prototype_ `virtual void GetNeighboringKeys(const FKeyHandle InKeyHandle, TOptional<FKeyHandle>& OutPreviousKeyHandle, TOptional<FKeyHandle>& OutNextKeyHandle) const override;`
- L66 _public prototype_ `virtual bool Evaluate(double ProspectiveTime, double& OutValue) const override;`
- L68 _public prototype_ `virtual void AddKeys(TArrayView<const FKeyPosition> InKeyPositions, TArrayView<const FKeyAttributes> InAttributes, TArrayView<TOptional<FKeyHandle>>* OutKeyHandles) override;`
- L69 _public prototype_ `virtual void RemoveKeys(TArrayView<const FKeyHandle> InKeys, double InCurrentTime) override;`
- L71 _public prototype_ `virtual void ReplaceKeyHandles(TConstArrayView<FKeyHandle> InCurrentHandles, TConstArrayView<FKeyHandle> InNewHandles) override;`
- L73 _public prototype_ `virtual FTransform2d GetCurveTransform() const override;`
- L74 _public prototype_ `virtual bool IsReadOnly() const override;`
- L75 _public function_ `virtual UObject* GetOwningObject() const override`
- L83 _public function_ `virtual bool HasChangedAndResetTest() override`
- L103 _public prototype_ `virtual void GetCurveColorObjectAndName(UObject** OutObject, FString& OutName) const override;`
- L107 _protected prototype_ `virtual double GetKeyValue(TArrayView<const ChannelValue> Values, int32 Index) const = 0;`
- L108 _protected prototype_ `virtual void SetKeyValue(int32 Index, double KeyValue) const = 0;`
- L111 _protected prototype_ `void PostProcessChanges(TNotNull<ChannelType*> Channel, TNotNull<UMovieSceneSection*> Section);` — Performs actions that should take place after any mutating call, like SetKeyPositions, etc.
- L123 _protected prototype_ `void InvokePostChannelChangedEvents(TNotNull<UMovieSceneSection*> Section);` — Updates all dependent systems after a change has been made to the channel, namely: - Invalidate LastSignature, - ChannelType::PostEditChange, - ChannelType::OnChannelChanged(), - UMovieSceneSection::MarkAsChanged, - MarkPackageDirty: this is required so the user is prompted to save the package after editing keys. If currently recording a transaction, the generated transaction will undo this flag when the user performs an undo op. - FCurveModel::OnCurvesModified
- L127 _public function_ `const TMovieSceneChannelHandle<ChannelType>& GetChannelHandle() const`
- L131 _private prototype_ `void FixupCurve();`
- L135 _protected member_ `TMovieSceneChannelHandle<ChannelType> ChannelHandle;`
- L136 _protected member_ `TWeakObjectPtr<UMovieSceneSection> WeakSection;`
- L137 _protected member_ `TWeakObjectPtr<> WeakOwningObject;`
- L138 _protected member_ `TWeakPtr<ISequencer> WeakSequencer;`
- L139 _protected member_ `FDelegateHandle OnDestroyHandle;`
- L140 _protected member_ `FGuid LastSignature;`

### `Source/Editor/MovieSceneTools/Public/Channels/ConstraintChannelCurveModel.h` (Public)


#### class `FConstraintChannelCurveModel`  
`class FConstraintChannelCurveModel : public FKeyBarCurveModel`  
_L35-89_
- inherits: `FKeyBarCurveModel`
- L38 _public member_ `static ECurveEditorViewID ViewID;`
- L40 _public prototype_ `FConstraintChannelCurveModel(TMovieSceneChannelHandle<FMovieSceneConstraintChannel> InChannel, UMovieSceneSection* InOwningSection, TWeakPtr<ISequencer> InWeakSequencer);`
- L41 _public prototype_ `~FConstraintChannelCurveModel();`
- L43 _public prototype_ `virtual const void* GetCurve() const override;` — FCurveModel
- L45 _public prototype_ `virtual void Modify() override;`
- L47 _public prototype_ `virtual void DrawCurve(const FCurveEditor& CurveEditor, const FCurveEditorScreenSpace& ScreenSpace, TArray<TTuple<double, double>>& InterpolatingPoints) const override;`
- L48 _public prototype_ `virtual void GetKeys(double MinTime, double MaxTime, double MinValue, double MaxValue, TArray<FKeyHandle>& OutKeyHandles) const override;`
- L49 _public prototype_ `virtual void GetKeyDrawInfo(ECurvePointType PointType, const FKeyHandle InKeyHandle, FKeyDrawInfo& OutDrawInfo) const override;`
- L51 _public prototype_ `virtual void GetKeyPositions(TArrayView<const FKeyHandle> InKeys, TArrayView<FKeyPosition> OutKeyPositions) const override;`
- L52 _public prototype_ `virtual void SetKeyPositions(TArrayView<const FKeyHandle> InKeys, TArrayView<const FKeyPosition> InKeyPositions, EPropertyChangeType::Type ChangeType) override;`
- L54 _public prototype_ `virtual void GetKeyAttributes(TArrayView<const FKeyHandle> InKeys, TArrayView<FKeyAttributes> OutAttributes) const override;`
- L55 _public prototype_ `virtual void SetKeyAttributes(TArrayView<const FKeyHandle> InKeys, TArrayView<const FKeyAttributes> InAttributes, EPropertyChangeType::Type ChangeType = EPropertyChangeType::Unspecified) override;`
- L57 _public prototype_ `virtual void GetCurveAttributes(FCurveAttributes& OutCurveAttributes) const override;`
- L58 _public prototype_ `virtual void SetCurveAttributes(const FCurveAttributes& InCurveAttributes) override;`
- L59 _public prototype_ `virtual void GetTimeRange(double& MinTime, double& MaxTime) const override;`
- L60 _public prototype_ `virtual void GetValueRange(double& MinValue, double& MaxValue) const override;`
- L61 _public prototype_ `virtual int32 GetNumKeys() const override;`
- L62 _public function_ `virtual void GetNeighboringKeys(const FKeyHandle InKeyHandle, TOptional<FKeyHandle>& OutPreviousKeyHandle, TOptional<FKeyHandle>& OutNextKeyHandle) const override`
- L63 _public prototype_ `virtual bool Evaluate(double ProspectiveTime, double& OutValue) const override;`
- L64 _public prototype_ `virtual void AddKeys(TArrayView<const FKeyPosition> InKeyPositions, TArrayView<const FKeyAttributes> InAttributes, TArrayView<TOptional<FKeyHandle>>* OutKeyHandles) override;`
- L65 _public prototype_ `virtual void RemoveKeys(TArrayView<const FKeyHandle> InKeys, double InCurrentTime) override;`
- L67 _public prototype_ `virtual void CreateKeyProxies(TWeakPtr<FCurveEditor> InWeakCurveEditor, FCurveModelID InCurveModelID, TArrayView<const FKeyHandle> InKeyHandles, TArrayView<UObject*> OutObjects) override;`
- L69 _public prototype_ `virtual UObject* GetOwningObject() const override;`
- L70 _public prototype_ `virtual bool HasChangedAndResetTest() override;`
- L73 _public prototype_ `virtual void BuildContextMenu(const FCurveEditor& CurveEditor, FMenuBuilder& MenuBuilder, TOptional<FCurvePointHandle> ClickedPoint);` — FKeyBarCurveModel
- L74 _public prototype_ `virtual TArray<FKeyBarCurveModel::FBarRange> FindRanges();`
- L78 _private prototype_ `void FixupCurve();`
- L79 _private prototype_ `FMovieSceneConstraintChannel* GetChannel() const;`
- L82 _private member_ `mutable TMovieSceneChannelHandle<FMovieSceneConstraintChannel> ChannelHandle;`
- L83 _private member_ `TWeakObjectPtr<UMovieSceneSection> WeakSection;`
- L84 _private member_ `FGuid LastSignature;`
- L85 _private member_ `TWeakPtr<ISequencer> WeakSequencer;`
- L86 _private member_ `TWeakObjectPtr<UTickableConstraint> Constraint;`
- L88 _private member_ `FDelegateHandle OnDestroyHandle;`

### `Source/Editor/MovieSceneTools/Public/Channels/DoubleChannelCurveModel.h` (Public)


#### class `FDoubleChannelCurveModel`  
`class FDoubleChannelCurveModel : public FBezierChannelCurveModel<FMovieSceneDoubleChannel, FMovieSceneDoubleValue, double>`  
_L20-32_
- inherits: `FBezierChannelCurveModel<FMovieSceneDoubleChannel,FMovieSceneDoubleValue,double>`
- L23 _public prototype_ `FDoubleChannelCurveModel(TMovieSceneChannelHandle<FMovieSceneDoubleChannel> InChannel, UMovieSceneSection* InOwningSection, TWeakPtr<ISequencer> InWeakSequencer);`
- L24 _public prototype_ `FDoubleChannelCurveModel(TMovieSceneChannelHandle<FMovieSceneDoubleChannel> InChannel, UMovieSceneSection* InOwningSection, UObject* InOwningObject, TWeakPtr<ISequencer> InWeakSequencer);`
- L27 _public prototype_ `virtual void CreateKeyProxies(TWeakPtr<FCurveEditor> InWeakCurveEditor, FCurveModelID InCurveModelID, TArrayView<const FKeyHandle> InKeyHandles, TArrayView<UObject*> OutObjects) override;` — FCurveModel
- L28 _public prototype_ `virtual TUniquePtr<IBufferedCurveModel> CreateBufferedCurveCopy() const override;`
- L30 _public prototype_ `virtual void GetValueRange(double& MinValue, double& MaxValue) const override;`
- L31 _public prototype_ `virtual void GetValueRange(double InMinTime, double InMaxTime, double& MinValue, double& MaxValue) const override;`

### `Source/Editor/MovieSceneTools/Public/Channels/FloatChannelCurveModel.h` (Public)


#### class `FFloatChannelCurveModel`  
`class FFloatChannelCurveModel : public FBezierChannelCurveModel<FMovieSceneFloatChannel, FMovieSceneFloatValue, float>`  
_L20-28_
- inherits: `FBezierChannelCurveModel<FMovieSceneFloatChannel,FMovieSceneFloatValue,float>`
- L23 _public prototype_ `FFloatChannelCurveModel(TMovieSceneChannelHandle<FMovieSceneFloatChannel> InChannel, UMovieSceneSection* InOwningSection, TWeakPtr<ISequencer> InWeakSequencer);`
- L26 _public prototype_ `virtual void CreateKeyProxies(TWeakPtr<FCurveEditor> InWeakCurveEditor, FCurveModelID InCurveModelID, TArrayView<const FKeyHandle> InKeyHandles, TArrayView<UObject*> OutObjects) override;` — FCurveModel
- L27 _public prototype_ `virtual TUniquePtr<IBufferedCurveModel> CreateBufferedCurveCopy() const override;`

### `Source/Editor/MovieSceneTools/Public/Channels/IntegerChannelCurveModel.h` (Public)


#### class `FIntegerChannelCurveModel`  
`class FIntegerChannelCurveModel : public FChannelCurveModel<FMovieSceneIntegerChannel, int32, int32>`  
_L25-42_
- inherits: `FChannelCurveModel<FMovieSceneIntegerChannel,int32,int32>`
- L28 _public prototype_ `FIntegerChannelCurveModel(TMovieSceneChannelHandle<FMovieSceneIntegerChannel> InChannel, UMovieSceneSection* InOwningSection, TWeakPtr<ISequencer> InWeakSequencer);`
- L31 _public prototype_ `virtual void DrawCurve(const FCurveEditor& CurveEditor, const FCurveEditorScreenSpace& ScreenSpace, TArray<TTuple<double, double>>& InterpolatingPoints) const override;` — FCurveModel
- L32 _public prototype_ `virtual void CreateKeyProxies(TWeakPtr<FCurveEditor> InWeakCurveEditor, FCurveModelID InCurveModelID, TArrayView<const FKeyHandle> InKeyHandles, TArrayView<UObject*> OutObjects) override;`
- L33 _public prototype_ `virtual TUniquePtr<IBufferedCurveModel> CreateBufferedCurveCopy() const override;`
- L34 _public prototype_ `virtual void GetCurveAttributes(FCurveAttributes& OutAttributes) const override;`
- L35 _public prototype_ `virtual void SetCurveAttributes(const FCurveAttributes& InAttributes) override;`
- L39 _protected prototype_ `virtual double GetKeyValue(TArrayView<const int32> Values, int32 Index) const override;` — FChannelCurveModel
- L40 _protected prototype_ `virtual void SetKeyValue(int32 Index, double KeyValue) const override;`

### `Source/Editor/MovieSceneTools/Public/Channels/PerlinNoiseChannelDetailsCustomization.h` (Public)


#### class `FMovieSceneFloatPerlinNoiseChannelDetailsCustomization`  
`class FMovieSceneFloatPerlinNoiseChannelDetailsCustomization : public IDetailCustomization`  
_L16-24_
- inherits: `IDetailCustomization`
- L19 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L20 _public prototype_ `static FName GetPerlinNoiseChannelParamsPropertyName();`
- L23 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface

#### class `FMovieSceneDoublePerlinNoiseChannelDetailsCustomization`  
`class FMovieSceneDoublePerlinNoiseChannelDetailsCustomization : public IDetailCustomization`  
_L26-34_
- inherits: `IDetailCustomization`
- L29 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L30 _public prototype_ `static FName GetPerlinNoiseChannelParamsPropertyName();`
- L33 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface

### `Source/Editor/MovieSceneTools/Public/Channels/PerlinNoiseChannelInterface.h` (Public)


#### class `SNumericTextBlockKeyEditor`  
`template<typename ChannelType, typename NumericType> class SNumericTextBlockKeyEditor : public SCompoundWidget`  
_L18-45_
- inherits: `SCompoundWidget`
- L20 _private typedef_ `using FKeyEditor = TSequencerKeyEditor<ChannelType, NumericType>;`
- L22 _private member_ `FKeyEditor KeyEditor;`
- L23 _private member_ `TSharedPtr<INumericTypeInterface<NumericType>> Interface;`
- L25 _private function_ `SLATE_BEGIN_ARGS(SNumericTextBlockKeyEditor)`
- L26 _private function_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const FKeyEditor& InKeyEditor)`
- L40 _private function_ `FText GetValueAsText() const`

#### struct `FPerlinNoiseChannelSectionMenuExtension`  
`struct FPerlinNoiseChannelSectionMenuExtension : TSharedFromThis<FPerlinNoiseChannelSectionMenuExtension>, ISidebarChannelExtension`  
_L47-77_
- inherits: `TSharedFromThis<FPerlinNoiseChannelSectionMenuExtension>,ISidebarChannelExtension`
- L49 _public prototype_ `FPerlinNoiseChannelSectionMenuExtension(TArrayView<const FMovieSceneChannelHandle> InChannelHandles, const TArray<TWeakObjectPtr<UMovieSceneSection>>& InWeakSections);`
- L50 _public prototype_ `virtual ~FPerlinNoiseChannelSectionMenuExtension() = default;`
- L52 _public prototype_ `virtual TSharedPtr<ISidebarChannelExtension> ExtendMenu(FMenuBuilder& MenuBuilder, const bool bInSubMenu) override;`
- L56 _private prototype_ `void Initialize();`
- L58 _private prototype_ `void BuildChannelsMenu(FMenuBuilder& MenuBuilder);`
- L59 _private prototype_ `void BuildParametersMenu(FMenuBuilder& MenuBuilder, int32 ChannelHandleIndex);`
- L73 _private member_ `TArray<FMovieSceneChannelHandle> ChannelHandles;`
- L74 _private member_ `TArray<int32> ChannelHandleSectionIndexes;`
- L75 _private member_ `TArray<TWeakObjectPtr<UMovieSceneSection>> WeakSections;`
- L76 _private member_ `TArray<FChannelNotifyHook> NotifyHooks;`

#### struct `FPerlinNoiseChannelSectionMenuExtension::FChannelNotifyHook`  
`struct FChannelNotifyHook : FNotifyHook`  
_L63-71_
- inherits: `FNotifyHook`
- L65 _public member_ `TWeakObjectPtr<UObject> WeakObjectToModify;`
- L67 _public function_ `FChannelNotifyHook(UObject* InObjectToModify) : WeakObjectToModify(InObjectToModify)`
- L69 _public prototype_ `virtual void NotifyPreChange(FProperty* PropertyAboutToChange) override;`
- L70 _public prototype_ `virtual void NotifyPostChange(const FPropertyChangedEvent& PropertyChangedEvent, FProperty* PropertyThatChanged) override;`

#### struct `TPerlinNoiseChannelInterface`  
`template<typename ChannelContainerType> struct TPerlinNoiseChannelInterface : ISequencerChannelInterface`  
_L80-214_
- inherits: `ISequencerChannelInterface`
- L82 _public typedef_ `using ChannelType = typename ChannelContainerType::ChannelType;`
- L84 _public function_ `virtual FKeyHandle AddOrUpdateKey_Raw(FMovieSceneChannel* Channel, UMovieSceneSection* SectionToKey, const void* ExtendedEditorData, FFrameNumber InTime, ISequencer& InSequencer, const FGuid& ObjectBindingID, FTrackInstancePropertyBindings* PropertyBindings) const override`
- L89 _public function_ `virtual void DeleteKeys_Raw(FMovieSceneChannel* Channel, TArrayView<const FKeyHandle> InHandles, FFrameNumber InTime) const override`
- L93 _public function_ `virtual void CopyKeys_Raw(FMovieSceneChannel* Channel, const UMovieSceneSection* Section, FName KeyAreaName, FMovieSceneClipboardBuilder& ClipboardBuilder, TArrayView<const FKeyHandle> KeyMask) const override`
- L97 _public function_ `virtual void PasteKeys_Raw(FMovieSceneChannel* Channel, UMovieSceneSection* Section, const FMovieSceneClipboardKeyTrack& KeyTrack, const FMovieSceneClipboardEnvironment& SrcEnvironment, const FSequencerPasteEnvironment& DstEnvironment, TArray<FKeyHandle>& OutPastedKeys) const override`
- L101 _public function_ `virtual TSharedPtr<FStructOnScope> GetKeyStruct_Raw(FMovieSceneChannelHandle Channel, FKeyHandle KeyHandle) const override`
- L106 _public function_ `virtual bool CanCreateKeyEditor_Raw(const FMovieSceneChannel* Channel) const override`
- L111 _public function_ `virtual TSharedRef<SWidget> CreateKeyEditor_Raw(const FMovieSceneChannelHandle& Channel, const UE::Sequencer::FCreateKeyEditorParams& Params) const override`
- L128 _public function_ `virtual void ExtendKeyMenu_Raw(FMenuBuilder& MenuBuilder, TSharedPtr<FExtender> MenuExtender, TArrayView<const FExtendKeyMenuParams> Parameters, TWeakPtr<ISequencer> InSequencer) const override`
- L132 _public function_ `virtual void ExtendSectionMenu_Raw(FMenuBuilder& MenuBuilder, TSharedPtr<FExtender> InMenuExtender, TArrayView<const FMovieSceneChannelHandle> InChannels, const TArray<TWeakObjectPtr<UMovieSceneSection>>& InWeakSections, TWeakPtr<ISequencer> InWeakSequencer) const override`
- L143 _public function_ `virtual TSharedPtr<ISidebarChannelExtension> ExtendSidebarMenu_Raw(FMenuBuilder& MenuBuilder, TSharedPtr<FExtender> InMenuExtender, TArrayView<const FMovieSceneChannelHandle> InChannels, const TArray<TWeakObjectPtr<UMovieSceneSection>>& InWeakSections, TWeakPtr<ISequencer> InWeakSequencer) const override`
- L150 _public function_ `virtual void DrawKeys_Raw(FMovieSceneChannel* Channel, TArrayView<const FKeyHandle> InKeyHandles, const UMovieSceneSection* InOwner, TArrayView<FKeyDrawParams> OutKeyDrawParams) const override`
- L154 _public function_ `virtual bool ShouldShowCurve_Raw(const FMovieSceneChannel* Channel, UMovieSceneSection* InSection) const override`
- L159 _public function_ `virtual bool SupportsCurveEditorModels_Raw(const FMovieSceneChannelHandle& InChannel) const override`
- L164 _public function_ `virtual TUniquePtr<FCurveModel> CreateCurveEditorModel_Raw(const FMovieSceneChannelHandle& Channel, const UE::Sequencer::FCreateCurveEditorModelParams& Params) const override`
- L169 _public function_ `virtual int32 DrawExtra_Raw(FMovieSceneChannel* InChannel, const UMovieSceneSection* InOwner, const FSequencerChannelPaintArgs& PaintArgs, int32 LayerId) const override`
- L202 _public function_ `virtual TSharedPtr<UE::Sequencer::FChannelModel> CreateChannelModel_Raw(const FMovieSceneChannelHandle& InChannelHandle, const UE::Sequencer::FSectionModel& InSection, FName InChannelName) const override`
- L206 _public function_ `virtual TSharedPtr<UE::Sequencer::STrackAreaLaneView> CreateChannelView_Raw(const FMovieSceneChannelHandle& InChannelHandle, TWeakPtr<UE::Sequencer::FChannelModel> InWeakModel, const UE::Sequencer::FCreateTrackLaneViewParams& Parameters) const override`
- L210 _public function_ `virtual EMovieSceneKeyInterpolation GetInterpolationMode_Raw(FMovieSceneChannel* InChannel, FFrameNumber InTime, EMovieSceneKeyInterpolation InDefaultMode) const override`

#### Free symbols / members of external scopes

- L124 _typedef_ `using KeyEditorType = SNumericTextBlockKeyEditor<ChannelType, typename ChannelType::CurveValueType>;` (scope `TPerlinNoiseChannelInterface::CreateKeyEditor_Raw`)
- L138 _function_ `` (scope `TPerlinNoiseChannelInterface::ExtendSectionMenu_Raw`)

### `Source/Editor/MovieSceneTools/Public/Channels/PiecewiseCurveModel.h` (Public)


#### class `UE::MovieScene::FPiecewiseCurveModel`  
`class FPiecewiseCurveModel : public FCurveModel`  
_L13-66_
- inherits: `FCurveModel`
- L17 _public member_ `TAttribute<const UE::MovieScene::FPiecewiseCurve*> CurveAttribute;`
- L18 _public member_ `TAttribute<FFrameRate> FrameRateAttribute;`
- L19 _public member_ `TAttribute<FTransform2d> CurveTransformAttribute;`
- L21 _public function_ `FPiecewiseCurveModel()`
- L27 _public function_ `const void* GetCurve() const override` — FCurveModel
- L31 _public function_ `void Modify() override`
- L34 _public function_ `void GetKeys(double MinTime, double MaxTime, double MinValue, double MaxValue, TArray<FKeyHandle>& OutKeyHandles) const override`
- L37 _public function_ `void AddKeys(TArrayView<const FKeyPosition> InPositions, TArrayView<const FKeyAttributes> InAttributes, TArrayView<TOptional<FKeyHandle>>* OutKeyHandles) override`
- L40 _public function_ `void RemoveKeys(TArrayView<const FKeyHandle> InKeys, double InCurrentTime) override`
- L43 _public function_ `void GetKeyPositions(TArrayView<const FKeyHandle> InKeys, TArrayView<FKeyPosition> OutKeyPositions) const override`
- L46 _public function_ `void SetKeyPositions(TArrayView<const FKeyHandle> InKeys, TArrayView<const FKeyPosition> InKeyPositions, EPropertyChangeType::Type ChangeType = EPropertyChangeType::Unspecified) override`
- L49 _public function_ `void GetKeyDrawInfo(ECurvePointType PointType, const FKeyHandle InKeyHandle, FKeyDrawInfo& OutDrawInfo) const override`
- L52 _public function_ `int32 GetNumKeys() const override`
- L56 _public function_ `void GetNeighboringKeys(const FKeyHandle InKeyHandle, TOptional<FKeyHandle>& OutPreviousKeyHandle, TOptional<FKeyHandle>& OutNextKeyHandle) const override`
- L60 _public function_ `bool IsReadOnly() const override`
- L61 _public function_ `FTransform2d GetCurveTransform() const override`
- L62 _public prototype_ `bool Evaluate(double InTime, double& OutValue) const override;`
- L63 _public prototype_ `void DrawCurve(const FCurveEditor& CurveEditor, const FCurveEditorScreenSpace& ScreenSpace, TArray<TTuple<double, double>>& InterpolatingPoints) const override;`
- L64 _public prototype_ `void GetTimeRange(double& MinTime, double& MaxTime) const override;`
- L65 _public prototype_ `void GetValueRange(double& MinValue, double& MaxValue) const override;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace MovieScene` (scope `UE`)

### `Source/Editor/MovieSceneTools/Public/Channels/SCurveEditorEventChannelView.h` (Public)


#### class `SCurveEditorEventChannelView`  
`class SCurveEditorEventChannelView : public SInteractiveCurveEditorView`  
_L22-43_
- inherits: `SInteractiveCurveEditorView`
- L26 _public prototype_ `void Construct(const FArguments& InArgs, TWeakPtr<FCurveEditor> InCurveEditor);`
- L28 _public prototype_ `virtual void GetGridLinesY(TSharedRef<const FCurveEditor> CurveEditor, TArray<float>& MajorGridLines, TArray<float>& MinorGridLines, TArray<FText>* MajorGridLabels) const override;`
- L33 _private prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L34 _private prototype_ `virtual FVector2D ComputeDesiredSize(float LayoutScaleMultiplier) const override;`
- L37 _private prototype_ `virtual void PaintView(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 BaseLayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L38 _private function_ `virtual bool IsValueSnapEnabled() const override`
- L40 _private prototype_ `void DrawLabels(const FGeometry& AllottedGeometry, FSlateWindowElementList& OutDrawElements, int32 BaseLayerId, ESlateDrawEffect DrawEffects) const;`
- L42 _private member_ `static float TrackHeight;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MOVIESCENETOOLS_API`

### `Source/Editor/MovieSceneTools/Public/Channels/SCurveEditorKeyBarView.h` (Public)


#### class `SCurveEditorKeyBarView`  
`class SCurveEditorKeyBarView : public SInteractiveCurveEditorView`  
_L26-47_
- inherits: `SInteractiveCurveEditorView`
- L29 _public prototype_ `void Construct(const FArguments& InArgs, TWeakPtr<FCurveEditor> InCurveEditor);`
- L31 _public prototype_ `virtual void GetGridLinesY(TSharedRef<const FCurveEditor> CurveEditor, TArray<float>& MajorGridLines, TArray<float>& MinorGridLines, TArray<FText>* MajorGridLabels) const override;`
- L36 _private prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L37 _private prototype_ `virtual FVector2D ComputeDesiredSize(float LayoutScaleMultiplier) const override;`
- L40 _private prototype_ `virtual void PaintView(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 BaseLayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L41 _private function_ `virtual bool IsValueSnapEnabled() const override`
- L42 _private prototype_ `virtual void BuildContextMenu(FMenuBuilder& MenuBuilder, TOptional<FCurvePointHandle> ClickedPoint, TOptional<FCurveModelID> HoveredCurveID) override;`
- L44 _private prototype_ `void DrawLabels(const FGeometry& AllottedGeometry, FSlateWindowElementList& OutDrawElements, int32 BaseLayerId, ESlateDrawEffect DrawEffects) const;`
- L46 _private member_ `static float TrackHeight;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API MOVIESCENETOOLS_API`

### `Source/Editor/MovieSceneTools/Public/Channels/TimeWarpChannelCurveModel.h` (Public)


#### class `FTimeWarpChannelCurveModel`  
`class FTimeWarpChannelCurveModel : public FDoubleChannelCurveModel`  
_L9-27_
- inherits: `FDoubleChannelCurveModel`
- L13 _public prototype_ `FTimeWarpChannelCurveModel(TMovieSceneChannelHandle<FMovieSceneTimeWarpChannel> InChannel, UMovieSceneSection* InOwningSection, UObject* InOwningObject, TWeakPtr<ISequencer> InWeakSequencer);`
- L15 _public prototype_ `void SetCurveAttributes(const FCurveAttributes& InCurveAttributes) override;`
- L17 _public prototype_ `void GetCurveAttributes(FCurveAttributes& OutCurveAttributes) const override;`
- L19 _public prototype_ `void AllocateAxes(FCurveEditor* InCurveEditor, TSharedPtr<FCurveEditorAxis>& OutHorizontalAxis, TSharedPtr<FCurveEditorAxis>& OutVerticalAxis) const override;`
- L21 _public prototype_ `void MakeChildCurves(TArray<TUniquePtr<FCurveModel>>& OutChildCurves) const override;`
- L26 _public prototype_ `virtual UObject* GetOwningObjectOrOuter(UClass* Class) const override;` — Time warp getters are parented to UMovieSceneSequence (not a UMovieSceneSection), so the default outer-chain walk fails to find the section. When a caller asks for a section (or any of its bases) we return our directly-stored section instead.

### `Source/Editor/MovieSceneTools/Public/ClipboardTypes.h` (Public)


#### Free symbols / members of external scopes

- L19 _namespace_ `namespace MovieSceneClipboard`
- L21 _function_ `template<> inline FName GetKeyTypeName<uint8>()` (scope `MovieSceneClipboard`)
- L26 _function_ `template<> inline FName GetKeyTypeName<int32>()` (scope `MovieSceneClipboard`)
- L31 _function_ `template<> inline FName GetKeyTypeName<int64>()` (scope `MovieSceneClipboard`)
- L36 _function_ `template<> inline FName GetKeyTypeName<FMovieSceneFloatValue>()` (scope `MovieSceneClipboard`)
- L41 _function_ `template<> inline FName GetKeyTypeName<FMovieSceneDoubleValue>()` (scope `MovieSceneClipboard`)
- L46 _function_ `template<> inline FName GetKeyTypeName<FName>()` (scope `MovieSceneClipboard`)
- L51 _function_ `template<> inline FName GetKeyTypeName<bool>()` (scope `MovieSceneClipboard`)
- L56 _function_ `template<> inline FName GetKeyTypeName<FString>()` (scope `MovieSceneClipboard`)
- L61 _function_ `template<> inline FName GetKeyTypeName<FText>()` (scope `MovieSceneClipboard`)
- L66 _function_ `template<> inline FName GetKeyTypeName<FMovieSceneActorReferenceKey>()` (scope `MovieSceneClipboard`)
- L71 _function_ `template<> inline FName GetKeyTypeName<FEventPayload>()` (scope `MovieSceneClipboard`)
- L75 _function_ `template<> inline FName GetKeyTypeName<FMovieSceneObjectPathChannelKeyValue>()` (scope `MovieSceneClipboard`)
- L79 _function_ `template<> inline FName GetKeyTypeName<FMovieSceneEvent>()` (scope `MovieSceneClipboard`)
- L83 _function_ `template<> inline FName GetKeyTypeName<FMovieSceneCameraShakeSourceTrigger>()` (scope `MovieSceneClipboard`)

### `Source/Editor/MovieSceneTools/Public/CommonMovieSceneTools.h` (Public)
_(no declarations extracted)_

### `Source/Editor/MovieSceneTools/Public/Conditions/MovieSceneConditionCustomization.h` (Public)


#### class `UMovieSceneTrackRowMetadataHelper`  
`class UMovieSceneTrackRowMetadataHelper : public UObject`  
_L27-38_
- reflection: `UCLASS(MinimalAPI, CollapseCategories)`
- inherits: `UObject`
- desc: Helper UObject for editing optional track row metadata not in-place. A UObject instead of a UStruct because we need to support instanced sub objects (conditions)
- L34 _public member_ `FMovieSceneTrackRowMetadata TrackRowMetadata;` — `UPROPERTY(EditAnywhere, Category = "General", meta=(ShowOnlyInnerProperties))`
- L37 _public member_ `TWeakObjectPtr<UMovieSceneTrack> OwnerTrack;` — `UPROPERTY()`

#### class `FMovieSceneConditionCustomization`  
`class FMovieSceneConditionCustomization : public IPropertyTypeCustomization`  
_L40-143_
- inherits: `IPropertyTypeCustomization`
- L44 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L45 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance(TWeakObjectPtr<UMovieSceneSequence> Sequence, const TWeakPtr<ISequencer> Sequencer);`
- L48 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;` — IPropertyTypeCustomization interface
- L49 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L56 _private prototype_ `FText GetDisplayValueAsString() const;` — @return The current display value for the combo box as a string
- L61 _private prototype_ `const FSlateBrush* GetDisplayValueIcon() const;` — @return The current display value's icon, if any. Returns nullptr if we have no valid value.
- L72 _private prototype_ `bool IsClassAllowed(UClass* CheckClass, bool bAllowAbstract) const;` — Wrapper method for determining whether a class is valid for use by this property item input proxy. @param	InItem			the property window item that contains this proxy. @param	CheckClass		the class to verify @param	bAllowAbstract	true if abstract classes are allowed @return	true if CheckClass is valid to be used by this input proxy
- L79 _private prototype_ `TSharedRef<SWidget> GenerateConditionPicker();` — Generates a condition picker allowing choice of condition class, creation of new class, or director blueprint condition. @return The Condition Picker widget.
- L86 _private prototype_ `void OnClassPicked(UClass* InClass);` — Callback function from the Class Picker for when a Class is picked. @param InClass			The class picked in the Class Picker
- L89 _private prototype_ `void FillConditionClassSubMenu(FMenuBuilder& MenuBuilder);` — Fills a sub menu to create a new or pick an existing condition class
- L92 _private prototype_ `void FillDirectorBlueprintConditionSubMenu(FMenuBuilder& MenuBuilder);` — Fills a sub menu to create a new director blueprint condition endpoint or pick an existing one
- L95 _private prototype_ `UMovieSceneSequence* GetCommonSequence() const;` — Gets the common sequence for this customization
- L98 _private prototype_ `UMovieSceneTrack* GetCommonTrack() const;` — Gets the common track for this customization
- L103 _private prototype_ `void PopulateQuickBindSubMenu(FMenuBuilder& MenuBuilder);` — Generate the content of the quick bind sub-menu dropdown (shown if the endpoint is not already bound)
- L106 _private prototype_ `void OnUseSelected();` — Used by 'Use Selected' button when clicked to change the condition class to the selected condition class in the asset browser
- L109 _private prototype_ `bool CanUseSelectedAsset() const;` — Used to enable/disable the selected asset button based on whether a condition class is currently selected
- L112 _private prototype_ `void OnBrowseTo();` — Used by 'Browse To' button when clicked to browse to the condition class currently in use in the asset browser
- L115 _private prototype_ `bool CanBrowseToAsset() const;` — Used to enable/disable the browse to button based on whether a blueprint condition class is currently in use.
- L120 _private member_ `TSharedPtr<IPropertyHandle> ConditionContainerPropertyHandle;` — The property handle for the condition container
- L123 _private member_ `TSharedPtr<IPropertyHandle> ConditionPropertyHandle;` — The property handle for the instanced condition property itself
- L126 _private member_ `TSharedPtr<IPropertyUtilities> PropertyUtilities;` — Property utilities for the property we're editing
- L129 _private member_ `TSharedPtr<FPropertyEditor> PropertyEditor;` — Property editor for the condition property
- L132 _private member_ `TSharedPtr<class SComboButton> ComboButton;` — The combo button
- L135 _private member_ `TSharedPtr<IDetailsView> DetailsView;` — Hold a shared ptr to the details view to prevent it from getting destroyed before combo button actions have taken place
- L137 _private member_ `TSharedPtr<SWidget> OpenMenuWidget;`
- L139 _private member_ `TWeakObjectPtr<UMovieSceneSequence> Sequence;`
- L140 _private member_ `TWeakObjectPtr<UMovieSceneTrack> Track;`
- L142 _private member_ `TWeakPtr<ISequencer> Sequencer;`

### `Source/Editor/MovieSceneTools/Public/Conditions/MovieSceneDirectorBlueprintConditionCustomization.h` (Public)


#### class `FMovieSceneDirectorBlueprintConditionCustomization`  
`class FMovieSceneDirectorBlueprintConditionCustomization : public FMovieSceneDirectorBlueprintEndpointCustomization`  
_L26-58_
- inherits: `FMovieSceneDirectorBlueprintEndpointCustomization`
- desc: Customization for director blueprint condition endpoint picker
- L30 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L31 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance(UMovieScene* InMovieScene);`
- L32 _public prototype_ `static TSharedRef<FMovieSceneDirectorBlueprintConditionCustomization> MakeInstance(UMovieScene* InMovieScene, TSharedPtr<IPropertyHandle> InPropertyHandle, TSharedPtr<IPropertyUtilities> InPropertyUtilities);`
- L36 _protected prototype_ `virtual void GetPayloadVariables(UObject* EditObject, void* RawData, FPayloadVariableMap& OutPayloadVariables) const override;`
- L37 _protected prototype_ `virtual bool SetPayloadVariable(UObject* EditObject, void* RawData, FName FieldName, const FMovieSceneDirectorBlueprintVariableValue& NewVariableValue) override;`
- L38 _protected prototype_ `virtual UK2Node* FindEndpoint(UMovieSceneSequence* Sequence, UBlueprint* Blueprint, UObject* EditObject, void* RawData) const override;`
- L39 _protected prototype_ `virtual void GetWellKnownParameterPinNames(UObject* EditObject, void* RawData, TArray<FName>& OutWellKnownParameters) const override;`
- L40 _protected prototype_ `virtual void GetWellKnownParameterCandidates(UK2Node* Endpoint, TArray<FWellKnownParameterCandidates>& OutCandidates) const override;`
- L41 _protected prototype_ `virtual bool SetWellKnownParameterPinName(UObject* EditObject, void* RawData, int32 ParameterIndex, FName BoundPinName) override;`
- L42 _protected prototype_ `virtual FMovieSceneDirectorBlueprintEndpointDefinition GenerateEndpointDefinition(UMovieSceneSequence* Sequence) override;`
- L43 _protected prototype_ `virtual void OnCreateEndpoint(UMovieSceneSequence* Sequence, UBlueprint* Blueprint, const TArray<UObject*> EditObjects, const TArray<void*> RawData, const FMovieSceneDirectorBlueprintEndpointDefinition& EndpointDefinition, UK2Node* NewEndpoint) override;`
- L44 _protected prototype_ `virtual void OnSetEndpoint(UMovieSceneSequence* Sequence, UBlueprint* Blueprint, const TArray<UObject*> EditObjects, const TArray<void*> RawData, const FMovieSceneDirectorBlueprintEndpointDefinition& EndpointDefinition, UK2Node* NewEndpoint) override;`
- L45 _protected prototype_ `virtual void GetEditObjects(TArray<UObject*>& OutObjects) const override;`
- L46 _protected prototype_ `virtual void OnCollectQuickBindActions(UBlueprint* Blueprint, FBlueprintActionMenuBuilder& MenuBuilder) override;`
- L47 _protected function_ `virtual bool CreateNewCategoryForPayloadVariables() const override`
- L50 _private prototype_ `void SetEndpointImpl(UMovieScene* MovieScene, FMovieSceneDirectorBlueprintConditionData* DynamicBinding, UBlueprint* Blueprint, UK2Node* NewEndpoint);`
- L51 _private prototype_ `void EnsureBlueprintExtensionCreated(UMovieScene* MovieScene, UBlueprint* Blueprint);`
- L53 _private prototype_ `void CollectConditionBindActions(UBlueprint* Blueprint, FBlueprintActionMenuBuilder& MenuBuilder, bool bIsRebinding);`
- L57 _private member_ `UMovieScene* EditedMovieScene;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MOVIESCENETOOLS_API`

### `Source/Editor/MovieSceneTools/Public/Conditions/MovieSceneDirectorBlueprintConditionUtils.h` (Public)


#### struct `FMovieSceneDirectorBlueprintConditionUtils`  
`struct FMovieSceneDirectorBlueprintConditionUtils`  
_L21-99_
- desc: A utility class for managing director blueprint condition endpoints.
- L23 _public typedef_ `using FSharedPlaybackState = UE::MovieScene::FSharedPlaybackState;`
- L28 _public prototype_ `static void SetEndpoint(UMovieScene* MovieScene, FMovieSceneDirectorBlueprintConditionData* DirectorBlueprintConditionData, UK2Node* NewEndpoint);` — Set an endpoint on the given blueprint condition
- L33 _public prototype_ `static void EnsureBlueprintExtensionCreated(UMovieSceneSequence* MovieSceneSequence, UBlueprint* Blueprint);` — Ensures that the condition blueprint extension has been added to the given sequence's director blueprint.
- L39 _public function_ `template<typename Callback> static void IterateDirectorBlueprintConditions(UMovieScene* InMovieScene, Callback&& InCallback)` — Utility function for iterating all blueprint conditions in a sequence.
- L92 _public function_ `static void GatherDirectorBlueprintConditions(UMovieScene* InMovieScene, TArray<FMovieSceneDirectorBlueprintConditionData*>& OutDirectorBlueprintConditionData)` — Utility function for gathering all blueprint conditions in a sequence into a container.

#### class `UMovieSceneDirectorBlueprintConditionEndpointUtil`  
`class UMovieSceneDirectorBlueprintConditionEndpointUtil : public UObject`  
_L105-111_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: Dummy class, used for easily getting a valid UFunction that helps prepare blueprint function graphs.
- L110 _private function_ `bool SampleDirectorBlueprintCondition(const FMovieSceneConditionContext& ConditionContext) const` — `UFUNCTION()`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API MOVIESCENETOOLS_API`
- L42 _function_ `` (scope `FMovieSceneDirectorBlueprintConditionUtils::IterateDirectorBlueprintConditions`)
- L45 _function_ `` (scope `FMovieSceneDirectorBlueprintConditionUtils::IterateDirectorBlueprintConditions::__anon2764e69e0102`)
- L95 _function_ `` (scope `FMovieSceneDirectorBlueprintConditionUtils::GatherDirectorBlueprintConditions`)

### `Source/Editor/MovieSceneTools/Public/Conditions/MovieScenePlatformConditionCustomization.h` (Public)


#### class `FMovieScenePlatformConditionCustomization`  
`class FMovieScenePlatformConditionCustomization : public IDetailCustomization`  
_L14-27_
- inherits: `IDetailCustomization`
- L17 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L18 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L22 _private prototype_ `void OnPlatformCheckChanged(int32 Index);`
- L23 _private prototype_ `TArray<FName> GetCurrentValidPlatformNames();`
- L25 _private member_ `TSharedPtr<IPropertyHandle> ValidPlatformsPropertyHandle;`
- L26 _private member_ `TSharedPtr<SCheckBoxList> CheckBoxList;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MOVIESCENETOOLS_API`

### `Source/Editor/MovieSceneTools/Public/Constraints/MovieSceneConstraintChannelHelper.h` (Public)


#### enum `ECreationTime`  
`enum class ECreationTime : uint8`  
_L28-34_
- reflection: `UENUM()`
- L30 _public enumerator_ `CurrentFrame`
- L31 _public enumerator_ `FromStart`
- L32 _public enumerator_ `Infinite`

#### struct `FSequencerCreationOptions`  
`struct FSequencerCreationOptions`  
_L37-44_
- reflection: `USTRUCT()`
- L43 _public member_ `ECreationTime CreationTime = ECreationTime::CurrentFrame;` — `UPROPERTY(EditAnywhere, Category=Options)` — Whether to create the constraint at the current frame, at the beginning of the sequence, or infinitely.

#### struct `FCompensationEvaluator`  
`struct FCompensationEvaluator`  
_L46-89_
- L49 _public member_ `TArray<FTransform> ChildLocals;`
- L50 _public member_ `TArray<FTransform> ChildGlobals;`
- L51 _public member_ `TArray<FTransform> SpaceGlobals;`
- L53 _public prototype_ `FCompensationEvaluator(UTickableTransformConstraint* InConstraint);`
- L76 _public prototype_ `void ComputeLocalTransforms(UWorld* InWorld, const FEvalParameters& InEvalParams);`
- L77 _public prototype_ `void ComputeLocalTransformsBeforeDeletion(UWorld* InWorld, const FEvalParameters& InEvalParams);`
- L78 _public prototype_ `void ComputeCompensation(UWorld* InWorld, const TSharedPtr<ISequencer>& InSequencer, const FFrameNumber& InTime);`
- L79 _public prototype_ `void ComputeLocalTransformsForBaking(UWorld* InWorld, const FEvalParameters& InEvalParams);`
- L80 _public prototype_ `void CacheTransforms(UWorld* InWorld, const FEvalParameters& InEvalParams);`
- L81 _public prototype_ `void ComputeCurrentTransforms(UWorld* InWorld);`
- L85 _private prototype_ `const TArray< TWeakObjectPtr<UTickableConstraint> > GetHandleTransformConstraints(UWorld* InWorld) const;`
- L87 _private member_ `UTickableTransformConstraint* Constraint = nullptr;`
- L88 _private member_ `UTransformableHandle* Handle = nullptr;`

#### struct `FCompensationEvaluator::FEvalParameters`  
`struct FEvalParameters`  
_L55-74_
- L57 _public function_ `FEvalParameters(const TSharedPtr<ISequencer>& InSequencer, const TArray<FFrameNumber>& InFrames) : Sequencer(InSequencer.Get()) , Frames(InFrames)`
- L62 _public function_ `bool IsValid() const`
- L67 _public member_ `ISequencer* Sequencer = nullptr;`
- L68 _public member_ `const TConstArrayView<const FFrameNumber> Frames;`
- L69 _public member_ `bool bToActive = false;`
- L70 _public member_ `bool bKeepCurrent = false;`
- L71 _public member_ `bool bInfiniteAtLeft = false;`
- L72 _public member_ `TOptional<FFrameNumber> OptCurrentFrame;`
- L73 _public member_ `bool bPropagateRelative = true;`

#### struct `FConstraintSections`  
`struct FConstraintSections`  
_L91-98_
- L93 _public member_ `UMovieSceneSection* ConstraintSection = nullptr;`
- L94 _public member_ `UMovieSceneSection* ChildTransformSection = nullptr;`
- L95 _public member_ `UMovieSceneSection* ParentTransformSection = nullptr;`
- L96 _public member_ `FConstraintAndActiveChannel* ActiveChannel = nullptr;`
- L97 _public member_ `ITransformConstraintChannelInterface* Interface = nullptr;`

#### struct `FMovieSceneConstraintChannelHelper`  
`struct FMovieSceneConstraintChannelHelper`  
_L99-266_
- L103 _public prototype_ `static bool AddConstraintToSequencer( const TSharedPtr<ISequencer>& InSequencer, UTickableTransformConstraint* InConstraint, const FSequencerCreationOptions& InOptions = FSequencerCreationOptions());`
- L110 _public prototype_ `static bool SmartConstraintKey( const TSharedPtr<ISequencer>& InSequencer, UTickableTransformConstraint* InConstraint, const TOptional<bool>& InOptActive, const TOptional<FFrameNumber>& InOptFrameTime);` — Adds an active key if needed and does the compensation when switching. Will use the optional active and time if set. Will return true if key is actually set, may not be if the value is the same.
- L117 _public prototype_ `static void Compensate( const TSharedPtr<ISequencer>& InSequencer, const UTickableTransformConstraint* InConstraint, const TOptional<FFrameNumber>& InOptTime, const bool bCompPreviousTick);` — Compensate transform on handles when a constraint switches state.
- L123 _public prototype_ `static void CompensateIfNeeded( const TSharedPtr<ISequencer>& InSequencer, IMovieSceneConstrainedSection* Section, const TOptional<FFrameNumber>& OptionalTime, const bool bCompPreviousTick, const int32 InChildHash = INDEX_NONE);`
- L130 _public prototype_ `static void HandleConstraintRemoved( UTickableConstraint* InConstraint, const FMovieSceneConstraintChannel* InChannel, const TSharedPtr<ISequencer>& InSequencer, UMovieSceneSection* InSection);`
- L136 _public prototype_ `static void HandleConstraintKeyDeleted( UTickableTransformConstraint* InConstraint, const FMovieSceneConstraintChannel* InConstraintChannel, const TSharedPtr<ISequencer>& InSequencer, UMovieSceneSection* InSection, const FFrameNumber& InTime);`
- L143 _public prototype_ `static void HandleConstraintKeyMoved( const UTickableTransformConstraint* InConstraint, const FMovieSceneConstraintChannel* InConstraintChannel, UMovieSceneSection* InSection, const FFrameNumber& InCurrentFrame, const FFrameNumber& InNextFrame);`
- L150 _public prototype_ `static FConstraintSections GetConstraintSectionAndChannel( const UTickableTransformConstraint* InConstraint, const TSharedPtr<ISequencer>& InSequencer);` — Get the section and the channel for the given constraint, will be nullptr's if it doesn't exist in Sequencer
- L155 _public prototype_ `static void GetTransformFramesForConstraintHandles( const UTickableTransformConstraint* InConstraint, const TSharedPtr<ISequencer>& InSequencer, const FFrameNumber& StartFrame, const FFrameNumber& EndFrame, TArray<FFrameNumber>& OutFramesToBake);` — For the given constraint get all of the transform keys for it's child and parent handles
- L165 _public prototype_ `template<typename ChannelType> static void GetFramesToCompensate( const FMovieSceneConstraintChannel& InActiveChannel, const bool InActiveValueToBeSet, const TOptional<FFrameNumber>& InTime, const TArrayView<ChannelType*>& InChannels, TArray<FFrameNumber>& OutFrames);` — @todo documentation.
- L174 _public prototype_ `template< typename ChannelType > static void GetFramesAfter( const FMovieSceneConstraintChannel& InActiveChannel, const FFrameNumber& InTime, const TArrayView<ChannelType*>& InChannels, TArray<FFrameNumber>& OutFrames);` — @todo documentation.
- L182 _public prototype_ `template< typename ChannelType > static void GetFramesWithinActiveState( const FMovieSceneConstraintChannel& InActiveChannel, const TArrayView<ChannelType*>& InChannels, TArray<FFrameNumber>& OutFrames);` — @todo documentation.
- L189 _public prototype_ `template< typename ChannelType > static void MoveTransformKeys( const TArrayView<ChannelType*>& InChannels, const FFrameNumber& InCurrentTime, const FFrameNumber& InNextTime);` — @todo documentation.
- L196 _public prototype_ `template< typename ChannelType > static void DeleteTransformKeys( const TArrayView<ChannelType*>& InChannels, const FFrameNumber& InTime);` — delete transform keys at that time
- L202 _public prototype_ `template< typename ChannelType > static void ChangeKeyInterpolation( const TArrayView<ChannelType*>& InChannels, const FFrameNumber& InTime, EMovieSceneKeyInterpolation KeyInterpolation);` — Change key interpolation at the specified time
- L207 _public prototype_ `static void HandleConstraintPropertyChanged( UTickableTransformConstraint* InConstraint, const FMovieSceneConstraintChannel& InActiveChannel, const FPropertyChangedEvent& InPropertyChangedEvent, const TSharedPtr<ISequencer>& InSequencer, UMovieSceneSection* InSection);`
- L215 _public prototype_ `template< typename ChannelType > static TArray<FFrameNumber> GetTransformTimes( const TArrayView<ChannelType*>& InChannels, const FFrameNumber& StartTime, const FFrameNumber& EndTime);`
- L221 _public prototype_ `template< typename ChannelType > static void DeleteTransformTimes( const TArrayView<ChannelType*>& InChannels, const FFrameNumber& StartTime, const FFrameNumber& EndTime, EMovieSceneTransformChannel Channels = EMovieSceneTransformChannel::AllTransform);`
- L229 _public prototype_ `template< typename ChannelType > static void SetTransformTimes( const TArrayView<ChannelType*>& InChannels, const TArray<FFrameNumber>& Frames, const TArray<FTransform>& Transforms);` — this will only set the value son channels with keys at the specified time, reusing tangent time etc.
- L236 _public prototype_ `template<typename ChannelType> static TPair<TOptional<FFrameNumber>, bool> IsActiveKeyAddedBeforeCurrentTime( const FFrameNumber& InCurrentTime, const FFrameNumber& InTime, const TArrayView<ChannelType*>& InChannels, TArray<FFrameNumber>& InOutFramesToCompensate);` — Checks whether the key to be added is prior to the current frame and updates the frames to be compensated accordingly.
- L242 _public member_ `static bool bDoNotCompensate;`
- L246 _private prototype_ `static ITransformConstraintChannelInterface* GetHandleInterface(const UTransformableHandle* InHandle);` — Get the animatable interface for that handle if registered.
- L249 _private prototype_ `static void CreateBindingIDForHandle(const TSharedPtr<ISequencer>& InSequencer, UTransformableHandle* InHandle);` — For the given handle create any movie scene binding for it based upon the current sequencer that's open
- L252 _private prototype_ `static bool IsHandleSpawnable(const TSharedPtr<ISequencer>& InSequencer, const UTransformableHandle* InHandle);` — For the given handle, return true if a binding exists and if that binding represents a spawnable.
- L255 _private prototype_ `static void CompensateScale( UTickableParentConstraint* InParentConstraint, const FMovieSceneConstraintChannel& InActiveChannel, const TSharedPtr<ISequencer>& InSequencer, UMovieSceneSection* InSection);` — Compensate scale keys when enabling/disabling scaling for parent constraints.
- L262 _private prototype_ `static void HandleOffsetChanged( UTickableTransformConstraint* InConstraint, const FMovieSceneConstraintChannel& InActiveChannel, const TSharedPtr<ISequencer>& InSequencer);` — Handle offset modifications so that the child's transform channels are synced.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MOVIESCENETOOLS_API`

### `Source/Editor/MovieSceneTools/Public/Constraints/MovieSceneConstraintChannelHelper.inl` (Public)


#### Free symbols / members of external scopes

- L16 _function_ `template<typename ChannelType> void FMovieSceneConstraintChannelHelper::GetFramesToCompensate( const FMovieSceneConstraintChannel& InActiveChannel, const bool InActiveValueToBeSet, const TOptional<FFrameNumber>& InTime, const TArrayView<ChannelType*>& InChannels, TArray<FFrameNumber>& OutFrames)` (scope `FMovieSceneConstraintChannelHelper`)
- L23 _typedef_ `using ChannelValueType = typename ChannelType::ChannelValueType;` (scope `FMovieSceneConstraintChannelHelper::GetFramesToCompensate`)
- L141 _function_ `template< typename ChannelType > void FMovieSceneConstraintChannelHelper::GetFramesAfter( const FMovieSceneConstraintChannel& InActiveChannel, const FFrameNumber& InTime, const TArrayView<ChannelType*>& InChannels, TArray<FFrameNumber>& OutFrames)` (scope `FMovieSceneConstraintChannelHelper`)
- L147 _typedef_ `using ChannelValueType = typename ChannelType::ChannelValueType;` (scope `FMovieSceneConstraintChannelHelper::GetFramesAfter`)
- L162 _function_ `` (scope `FMovieSceneConstraintChannelHelper::GetFramesAfter`)
- L212 _function_ `template< typename ChannelType > void FMovieSceneConstraintChannelHelper::GetFramesWithinActiveState( const FMovieSceneConstraintChannel& InActiveChannel, const TArrayView<ChannelType*>& InChannels, TArray<FFrameNumber>& OutFrames)` (scope `FMovieSceneConstraintChannelHelper`)
- L217 _typedef_ `using ChannelValueType = typename ChannelType::ChannelValueType;` (scope `FMovieSceneConstraintChannelHelper::GetFramesWithinActiveState`)
- L287 _function_ `template< typename ChannelType > void FMovieSceneConstraintChannelHelper::MoveTransformKeys( const TArrayView<ChannelType*>& InChannels, const FFrameNumber& InCurrentTime, const FFrameNumber& InNextTime)` (scope `FMovieSceneConstraintChannelHelper`)
- L332 _function_ `template< typename ChannelType > void FMovieSceneConstraintChannelHelper::DeleteTransformKeys( const TArrayView<ChannelType*>& InChannels, const FFrameNumber& InTime)` (scope `FMovieSceneConstraintChannelHelper`)
- L351 _function_ `template< typename ChannelType > void FMovieSceneConstraintChannelHelper::ChangeKeyInterpolation( const TArrayView<ChannelType*>& InChannels, const FFrameNumber& InTime, EMovieSceneKeyInterpolation KeyInterpolation)` (scope `FMovieSceneConstraintChannelHelper`)
- L356 _typedef_ `using ChannelValueType = typename ChannelType::ChannelValueType;` (scope `FMovieSceneConstraintChannelHelper::ChangeKeyInterpolation`)
- L412 _function_ `template< typename ChannelType > TArray<FFrameNumber> FMovieSceneConstraintChannelHelper::GetTransformTimes( const TArrayView<ChannelType*>& InChannels, const FFrameNumber& StartTime, const FFrameNumber& EndTime)` (scope `FMovieSceneConstraintChannelHelper`)
- L440 _function_ `template< typename ChannelType > void FMovieSceneConstraintChannelHelper::DeleteTransformTimes( const TArrayView<ChannelType*>& InChannels, const FFrameNumber& StartTime, const FFrameNumber& EndTime, EMovieSceneTransformChannel InChannelsToKey)` (scope `FMovieSceneConstraintChannelHelper`)
- L458 _function_ `` (scope `FMovieSceneConstraintChannelHelper::DeleteTransformTimes`)
- L531 _function_ `template<typename ChannelType> void EvaluateTangentAtThisTime(int32 ChannelIndex, int32 NumChannels, UMovieSceneSection* Section, FFrameNumber Time, TArray<FMovieSceneTangentData>& OutTangents)`
- L536 _typedef_ `using ChannelValueType = typename ChannelType::ChannelValueType;` (scope `EvaluateTangentAtThisTime`)
- L540 _function_ `` (scope `EvaluateTangentAtThisTime`)
- L612 _function_ `template<typename ChannelType> void SetTangentsAtThisTime(int32 ChannelIndex, int32 NumChannels, UMovieSceneSection* Section, FFrameNumber Time, const TArray<FMovieSceneTangentData>& InTangents)` — NOTE we may pass an enum to tell which tangent we wanna set (arrive, leave, both)
- L618 _typedef_ `using ChannelValueType = typename ChannelType::ChannelValueType;` (scope `SetTangentsAtThisTime`)
- L652 _function_ `template<typename ChannelType> TPair<TOptional<FFrameNumber>, bool> IsActiveKeyAddedBeforeCurrentTime( const FFrameNumber& InCurrentTime, const FFrameNumber& InTime, const TArrayView<ChannelType*>& InChannels, TArray<FFrameNumber>& InOutFramesToCompensate)`
- L675 _function_ `` (scope `IsActiveKeyAddedBeforeCurrentTime`)

### `Source/Editor/MovieSceneTools/Public/Constraints/TransformConstraintChannelInterface.h` (Public)


#### struct `ITransformConstraintChannelInterface`  
`struct ITransformConstraintChannelInterface`  
_L28-71_
- L30 _public prototype_ `virtual ~ITransformConstraintChannelInterface();`
- L33 _public prototype_ `virtual UMovieSceneSection* GetHandleSection(const UTransformableHandle* InHandle, const TSharedPtr<ISequencer>& InSequencer) = 0;` — Get the section where the channels live from the object that the handle wraps.
- L34 _public prototype_ `virtual UMovieSceneSection* GetHandleConstraintSection(const UTransformableHandle* InHandle, const TSharedPtr<ISequencer>& InSequencer) = 0;`
- L37 _public prototype_ `virtual UWorld* GetHandleWorld(UTransformableHandle* InHandle) = 0;` — Get the world from the object that the handle wraps.
- L40 _public prototype_ `virtual bool SmartConstraintKey( UTickableTransformConstraint* InConstraint, const TOptional<bool>& InOptActive, const TRange<FFrameNumber>& InTimeRange, const TSharedPtr<ISequencer>& InSequencer) = 0;` — Add an active/inactive key to the constraint channel if needed and does the transform compensation on the transform channels.
- L45 _public prototype_ `virtual void AddHandleTransformKeys( const TSharedPtr<ISequencer>& InSequencer, const UTransformableHandle* InHandle, const TArray<FFrameNumber>& InFrames, const TArray<FTransform>& InLocalTransforms, const EMovieSceneTransformChannel& InChannels) = 0;` — Add keys on the transform channels of the object that the handle wraps.
- L54 _protected prototype_ `ITransformConstraintChannelInterface();`
- L56 _protected prototype_ `static bool CanAddKey(const FMovieSceneConstraintChannel& InActiveChannel, const FFrameNumber& InTime, bool& ActiveValue);`
- L57 _protected prototype_ `static void CleanDuplicates(FMovieSceneConstraintChannel& InOutActiveChannel, TArray<FFrameNumber>& OutTimesRemoved);`
- L59 _protected prototype_ `void Initialize();`
- L60 _protected prototype_ `void Shutdown();`
- L62 _protected prototype_ `void OnSequencerCreated(TSharedRef<ISequencer> InSequencer);`
- L63 _protected prototype_ `void OnSequencerClosed(TSharedRef<ISequencer> InSequencer);`
- L65 _protected prototype_ `virtual void UnregisterTrack(UMovieSceneTrack* InTrack, UWorld* InWorld);`
- L66 _protected prototype_ `static void UnregisterConstraints(IMovieSceneConstrainedSection* InSection, UWorld* InWorld);`
- L67 _protected prototype_ `void UnregisterMovieScene(const UMovieScene* InMovieScene, UWorld* InWorld);`
- L69 _protected member_ `FDelegateHandle SequencerCreatedHandle;`
- L70 _protected member_ `TArray<TWeakPtr<ISequencer>> Sequencers;`

#### class `FConstraintChannelInterfaceRegistry`  
`class FConstraintChannelInterfaceRegistry`  
_L77-101_
- L80 _public prototype_ `~FConstraintChannelInterfaceRegistry() = default;`
- L83 _public prototype_ `static FConstraintChannelInterfaceRegistry& Get();` — Get the singleton registry object
- L87 _public function_ `template<typename HandleType> void RegisterConstraintChannelInterface(TUniquePtr<ITransformConstraintChannelInterface>&& InInterface)` — Register an interface for the HandleType static class
- L95 _public prototype_ `ITransformConstraintChannelInterface* FindConstraintChannelInterface(const UClass* InClass) const;` — Find the registered interface from the given class. Returns a nullptr if noting registered for that class.
- L98 _private prototype_ `FConstraintChannelInterfaceRegistry() = default;`
- L100 _private member_ `TMap<UClass*, TUniquePtr<ITransformConstraintChannelInterface>> HandleToInterfaceMap;`

### `Source/Editor/MovieSceneTools/Public/Decorations/IMovieSceneDecorationMenuProvider.h` (Public)


#### class `IMovieSceneDecorationMenuProvider`  
`class IMovieSceneDecorationMenuProvider : public IModularFeature`  
_L14-44_
- inherits: `IModularFeature`
- L18 _public prototype_ `static FName GetModularFeatureName();`
- L20 _public prototype_ `virtual ~IMovieSceneDecorationMenuProvider();`
- L26 _public prototype_ `virtual const UClass* GetHandledDecorationClass() const = 0;` — Allows providers to specify the decoration classes they handle. @return The decoration UClass this menu provider handles.
- L36 _public prototype_ `virtual void PopulateAddDecorationMenu(FMenuBuilder& MenuBuilder, TObjectPtr<UObject> BoundObject, UMovieSceneDecorationContainerObject* DecorationContainer, TWeakPtr<ISequencer> InSequencer) = 0;` — Populate the custom menu entry for the decoration class handled by this provider. @param MenuBuilder The menu builder to extend, and add a custom entry to. @param BoundObject The object associated with the decoration container, if it exists. @param DecorationContainer The decoration container owning the decoration this provider is associated with. @param InSequencer The sequence editor.
- L43 _public function_ `virtual int32 GetDecorationMenuPriority() const` — Allows providers to define their priority in their menu entries. @return Menu priority for this decoration provider. Lower values appear first in the menu. Default is 100 (middle priority). Use 0-50 for high priority items, 100+ for normal items.

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MOVIESCENETOOLS_API`

### `Source/Editor/MovieSceneTools/Public/Decorations/MovieSceneDecorationContainerCustomization.h` (Public)


#### class `FMovieSceneDecorationContainerCustomization`  
`class FMovieSceneDecorationContainerCustomization : public IPropertyTypeCustomization`  
_L17-37_
- inherits: `IPropertyTypeCustomization`
- desc: Detail customization for UMovieSceneDecorationContainerObject
- L20 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L23 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;` — IPropertyTypeCustomization interface
- L24 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L28 _private prototype_ `void AddCompatibleDecorationsUI(UMovieSceneDecorationContainerObject* Container, IDetailLayoutBuilder& LayoutBuilder);`
- L30 _private prototype_ `TSharedRef<SWidget> OnGetAddDecorationMenuContent(UMovieSceneDecorationContainerObject* Container, TSet<UClass*> CompatibleClasses);`
- L32 _private prototype_ `void OnAddDecoration(UMovieSceneDecorationContainerObject* Container, UClass* DecorationClass);`
- L34 _private prototype_ `void OnRemoveDecoration(UMovieSceneDecorationContainerObject* Container, UClass* DecorationClass);`
- L36 _private member_ `TWeakPtr<IPropertyUtilities> PropertyUtils;`

### `Source/Editor/MovieSceneTools/Public/FCPXML/FCPXMLMovieSceneTranslator.h` (Public)


#### class `FFCPXMLImporter`  
`class FFCPXMLImporter : public FMovieSceneImporter`  
_L18-47_
- inherits: `FMovieSceneImporter`
- desc: The FFCPXMLImporter class is the entry point for launching an import of data from an XML file into Sequencer.
- L21 _public prototype_ `FFCPXMLImporter();`
- L23 _public prototype_ `virtual ~FFCPXMLImporter();`
- L26 _public prototype_ `virtual FText GetFileTypeDescription() const;` — Format description.
- L28 _public prototype_ `virtual FText GetDialogTitle() const;` — Import window title.
- L30 _public prototype_ `virtual FText GetTransactionDescription() const;` — Scoped transaction description.
- L32 _public prototype_ `virtual FName GetMessageLogWindowTitle() const;` — Message log window title.
- L34 _public prototype_ `virtual FText GetMessageLogLabel() const;` — Message log list label.
- L46 _public prototype_ `bool Import(UMovieScene* InMovieScene, FFrameRate InFrameRate, FString InFilename, TSharedRef<FMovieSceneTranslatorContext> InContext);` — Import FCP 7 XML @param InMovieScene The movie scene to import the XML file into @param InFrameRate The frame rate to import the XML at @param InFilename The filename to import @param OutError The return error message @return Whether the import was successful

#### class `FFCPXMLExporter`  
`class FFCPXMLExporter : public FMovieSceneExporter`  
_L52-93_
- inherits: `FMovieSceneExporter`
- desc: The FFCPXMLExporter class is the entry point for launching an export of data from Sequencer into an XML file.
- L56 _public prototype_ `FFCPXMLExporter();` — Constructor
- L58 _public prototype_ `virtual ~FFCPXMLExporter();` — Destructor
- L61 _public prototype_ `virtual FText GetFileTypeDescription() const;` — Format description.
- L63 _public prototype_ `virtual FText GetDialogTitle() const;` — Export dialog window title.
- L65 _public prototype_ `virtual FText GetDefaultFileExtension() const;` — Default format file extension.
- L67 _public prototype_ `virtual FText GetNotificationExportFinished() const;` — Notification when export completes.
- L69 _public prototype_ `virtual FText GetNotificationHyperlinkText() const;` — Notification hyperlink to exported file path.
- L71 _public prototype_ `virtual FName GetMessageLogWindowTitle() const;` — Message log window title.
- L73 _public prototype_ `virtual FText GetMessageLogLabel() const;` — Message log list label.
- L92 _public prototype_ `virtual bool Export(const UMovieScene* InMovieScene, FString InFilenameFormat, FFrameRate InFrameRate, uint32 InResX, uint32 InResY, int32 InHandleFrames, FString InSaveFilename, TSharedRef<FMovieSceneTranslatorContext> InContext, FString InMovieExtension, const FMovieSceneExportMetadata* InMetadata=nullptr);`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MOVIESCENETOOLS_API`

### `Source/Editor/MovieSceneTools/Public/FrameNumberDetailsCustomization.h` (Public)


#### class `FFrameNumberDetailsCustomization`  
`class FFrameNumberDetailsCustomization : public IPropertyTypeCustomization`  
_L17-60_
- inherits: `IPropertyTypeCustomization`
- desc: Customize the FFrameNumber to support conversion from seconds/frames/timecode formats.
- L21 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance(TSharedPtr<INumericTypeInterface<double>> InNumericTypeInterface)`
- L26 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance(TWeakPtr<ISequencer> Sequencer)`
- L31 _public function_ `FFrameNumberDetailsCustomization(TWeakPtr<ISequencer> Sequencer)`
- L35 _public function_ `FFrameNumberDetailsCustomization(TSharedPtr<INumericTypeInterface<double>> InNumericTypeInterface)`
- L41 _public function_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override` — IPropertyTypeCustomization interface
- L42 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L45 _private prototype_ `FText OnGetTimeText() const;`
- L46 _private prototype_ `FText OnGetTimeToolTipText() const;`
- L47 _private prototype_ `void OnTimeTextCommitted(const FText& InText, ETextCommit::Type CommitInfo);`
- L49 _private member_ `TWeakPtr<ISequencer> WeakSequencer;`
- L51 _private member_ `TSharedPtr<INumericTypeInterface<double>> NumericTypeInterface;`
- L54 _private member_ `TSharedPtr<IPropertyHandle> FrameNumberProperty;` — Store the property handle to the FrameNumber field so we can get/set the value on the object via text box callbacks.
- L57 _private member_ `int32 UIClampMin;` — If they've used the UIMin metadata on the FFrameNumber property, we store that for use via text box callbacks.
- L59 _private member_ `int32 UIClampMax;` — If they've used the UIMax metadata on the FFrameNumber property, we store that for use via text box callbacks.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MOVIESCENETOOLS_API`

### `Source/Editor/MovieSceneTools/Public/IMovieSceneAnimMixerBakeProvider.h` (Public)


#### struct `FAnimMixerBakeMenuParams`  
`struct FAnimMixerBakeMenuParams`  
_L23-71_
- desc: Parameters for building a "Bake To Control Rig" menu section. All fields are Control Rig-agnostic so that the AnimMixer editor has no CR dependency.
- L26 _public member_ `TSharedPtr<ISequencer> Sequencer;` — Sequencer instance
- L29 _public member_ `USkeletalMeshComponent* SkelMeshComp = nullptr;` — Skeletal mesh component for the bound object
- L32 _public member_ `USkeleton* Skeleton = nullptr;` — Skeleton for filtering control rig assets
- L35 _public member_ `FGuid ObjectBinding;` — Object binding GUID
- L38 _public member_ `UObject* BoundObject = nullptr;` — The bound actor/object
- L41 _public member_ `bool* bFilterAssetBySkeleton = nullptr;` — Mutable filter-by-skeleton toggle state (caller-owned, persists across menu opens)
- L48 _public member_ `FText EntryLabelVerb;` — Verb used in the "{Verb} to Control Rig" submenu label. Examples: "Bake", "Bake Layer", "Bake Selected Layers". If empty, the provider defaults to "Bake".
- L55 _public member_ `TDelegate<bool(UAnimSequence*, UAnimSeqExportOption*, USkeletalMeshComponent*)> PopulateAnimSequence;` — Delegate the provider calls to populate a temporary UAnimSequence with animation data. The caller captures mixer-specific context (track, filter, etc.) in this delegate. Return true on success, false to abort the bake.
- L62 _public member_ `TFunction<UMovieSceneTrack*(UMovieScene*, TSubclassOf<UMovieSceneTrack>)> ChildTrackFactory;` — Creates a child track inside the mixer at the desired location. The provider calls this with the UClass of the track to create (e.g. UMovieSceneControlRigParameterTrack). Returns the created track, or nullptr on failure.
- L70 _public member_ `TFunction<void(UMovieSceneTrack* , UObject* , bool )> OnComplete;` — Called by the provider after a successful bake. @param BakeTrack      The created track (same pointer returned by ChildTrackFactory) @param ControlRigObj  The control rig object (as UObject* to avoid CR type dependency) @param bSuccess       Whether the bake succeeded

#### class `IMovieSceneAnimMixerBakeProvider`  
`class IMovieSceneAnimMixerBakeProvider : public IModularFeature`  
_L81-104_
- inherits: `IModularFeature`
- desc: Modular feature interface for providing "Bake To Control Rig" menu entries inside Animation Mixer track and layer context menus. When no provider is registered, the bake submenu is simply omitted. The MovieSceneMixedControlRigEditor module registers a concrete provider that delegates to the ControlRigEditor bake helpers.
- L85 _public prototype_ `static FName GetModularFeatureName();`
- L87 _public function_ `virtual ~IMovieSceneAnimMixerBakeProvider()`
- L101 _public prototype_ `virtual void BuildBakeToControlRigMenuSection( FMenuBuilder& MenuBuilder, const FAnimMixerBakeMenuParams& Params) = 0;` — Build the "Bake To Control Rig" submenu section into the provided MenuBuilder. This includes the "Filter Asset By Skeleton" toggle and the rig picker submenu. The provider is responsible for the entire bake flow: 1. Building the menu UI (rig picker, filter toggle) 2. On user selection: calling PopulateAnimSequence to fill a temp anim sequence 3. Calling ChildTrackFactory to create the destination track 4. Running the bake (e.g. InitControlRigFromAnimSequence) 5. Activating any required editor modes 6. Calling OnComplete with the results

### `Source/Editor/MovieSceneTools/Public/IMovieSceneAnimMixerItemMenuProvider.h` (Public)


#### class `IMovieSceneAnimMixerItemMenuProvider`  
`class IMovieSceneAnimMixerItemMenuProvider : public IModularFeature`  
_L20-69_
- inherits: `IModularFeature`
- desc: Modular feature interface for providing custom UI when adding items to Animation Mixer tracks. Implement this interface to provide custom menu entries with specialized UI (e.g., asset pickers, class selectors). If no provider is registered for a class implementing IMovieSceneAnimationSectionInterface or IMovieSceneAnimationTrackInterface, the AnimMixer editor will auto-generate a basic menu entry.
- L24 _public prototype_ `static FName GetModularFeatureName();`
- L26 _public prototype_ `IMovieSceneAnimMixerItemMenuProvider();`
- L28 _public prototype_ `virtual ~IMovieSceneAnimMixerItemMenuProvider();`
- L33 _public prototype_ `virtual const UClass* GetHandledMixerItemClass() const = 0;` — Returns the UClass this provider handles.
- L44 _public prototype_ `virtual void PopulateAddMixerItemMenu(FMenuBuilder& MenuBuilder, TArray<FGuid> ObjectBindings, UMovieSceneTrack* Track, TSharedPtr<ISequencer> Sequencer, int32 RowIndex) = 0;` — Populate the menu with custom UI for adding this item type. Called when building the "Add Section" menu for an Animation Mixer track. @param MenuBuilder The menu builder to populate @param ObjectBindings The object bindings for the track @param Track The track to add items to @param Sequencer The sequencer instance @param RowIndex The target row index to add items to (INDEX_NONE for auto-row assignment)
- L50 _public function_ `virtual int32 GetMixerItemMenuPriority() const` — Returns the menu priority for this provider. Lower values appear first in the menu. Default is 100 (middle priority). Use 0-50 for high priority items, 100+ for normal items.
- L61 _public function_ `virtual void PopulateObjectBindingAnimationMenu(FMenuBuilder& MenuBuilder, const TArray<FGuid>& ObjectBindings, const UClass* ObjectClass, bool bIsInsideSubmenu)` — Populate the Object Binding Animation menu with entries for adding standalone tracks. Called when building the "Animation" menu/submenu in the Object Binding +Track menu. Default implementation does nothing - override to add custom menu entries. @param MenuBuilder The menu builder to populate @param ObjectBindings The object bindings for the track @param ObjectClass The class of the bound object @param bIsInsideSubmenu True if called inside an Animation submenu (can use BeginSection), false if at top-level menu (should use AddSubMenu)
- L68 _public function_ `virtual int32 GetObjectBindingAnimationMenuPriority() const` — Returns the menu priority for the Object Binding Animation menu. Lower values appear first. Default delegates to GetMixerItemMenuPriority(). Animation Mixer should use 0 to appear first.

### `Source/Editor/MovieSceneTools/Public/IMovieSceneAnimMixerTargetMenuProvider.h` (Public)


#### class `IMovieSceneAnimMixerTargetMenuProvider`  
`class IMovieSceneAnimMixerTargetMenuProvider : public IModularFeature`  
_L22-66_
- inherits: `IModularFeature`
- desc: Modular feature interface for providing custom UI when selecting animation mixer targets. Implement this interface to provide custom menu entries for target selection when creating Animation Mixer tracks or changing the target on an existing track. Each target type (e.g. Automatic, Custom Anim Instance, Anim Blueprint Target, UAF Module Injection) should have a corresponding provider that handles its menu population.
- L25 _public prototype_ `static FName GetModularFeatureName();`
- L27 _public function_ `virtual ~IMovieSceneAnimMixerTargetMenuProvider()`
- L30 _public prototype_ `virtual UScriptStruct* GetHandledTargetStructType() const = 0;` — Returns the target struct type this provider handles (e.g., FMovieSceneMixedAnimationTarget::StaticStruct())
- L42 _public function_ `virtual void PopulateTargetMenu( FMenuBuilder& MenuBuilder, TObjectPtr<UObject> BoundObject, TFunction<void(TInstancedStruct<FMovieSceneMixedAnimationTarget>)> OnTargetSelected, TSharedPtr<ISequencer> Sequencer, UMovieSceneAnimationMixerTrack* Track)` — Populate the menu with entries for this target type. Called when building the target selection menu (both for new track creation and target change). For simple targets (like Automatic or Custom Anim Instance), this may add a single menu entry. For complex targets (like Anim Blueprint Target), this may add a submenu with dynamically discovered options based on the bound object. OnTargetSelected should be invoked by the menu provider with a constructed target once a target is selected.
- L52 _public prototype_ `virtual void PopulateTargetMenu( FMenuBuilder& MenuBuilder, TObjectPtr<UObject> BoundObject, TFunction<void(TInstancedStruct<FMovieSceneMixedAnimationTarget>)> OnTargetSelected) = 0;`
- L65 _public function_ `virtual int32 GetTargetMenuPriority() const` — Returns the menu priority for this provider. Lower values appear first in the menu. 0 - Automatic (default target) 10 - Custom Anim Instance 20 - Anim Blueprint Target 30 - UAF Module Injection 100+ - Custom/plugin targets

### `Source/Editor/MovieSceneTools/Public/IMovieSceneAnimSequenceBakeScope.h` (Public)


#### class `IMovieSceneAnimSequenceBakeScope`  
`class IMovieSceneAnimSequenceBakeScope : public IModularFeature`  
_L18-31_
- inherits: `IModularFeature`
- desc: Modular feature interface for plugins that need to wrap the binding-level "Bake Animation Sequence" / "Bake to Control Rig" recording window with custom scope state. Implementations receive a Begin/End pair bracketing the sequencer playback that the recorder runs internally. Current consumer: MovieSceneAnimMixerEditor registers an implementation that pushes UMovieSceneAnimMixerSystem's force-root-bone scope, so mixer root motion lands on the root bone rather than the actor during bake recording.
- L22 _public prototype_ `static FName GetModularFeatureName();`
- L24 _public function_ `virtual ~IMovieSceneAnimSequenceBakeScope()`
- L27 _public prototype_ `virtual void BeginBakeScope() = 0;` — Called once before the recorder begins playback.
- L30 _public prototype_ `virtual void EndBakeScope() = 0;` — Called once after the recorder finishes playback (always paired with BeginBakeScope).

### `Source/Editor/MovieSceneTools/Public/IMovieSceneEditingContextLayerResolver.h` (Public)


#### class `IMovieSceneEditingContextLayerResolver`  
`class IMovieSceneEditingContextLayerResolver : public IModularFeature`  
_L17-29_
- inherits: `IModularFeature`
- desc: Modular feature for resolving an editing context (e.g. a UControlRig) to the animation mixer layer it belongs to. This allows systems like the root motion offset provider to compute per-layer offsets without hard dependencies on mixer or control rig types. The resolved layer is returned as UObject* to avoid a dependency from MovieSceneTools on MovieSceneAnimMixer. Consumers cast to the concrete type.
- L20 _public prototype_ `virtual ~IMovieSceneEditingContextLayerResolver() = default;`
- L24 _public prototype_ `virtual UObject* ResolveEditingContextToMixerLayer( const UMovieSceneEntitySystemLinker* Linker, const UObject* EditingContext) const = 0;` — Resolve an editing context to the mixer layer it belongs to. Returns nullptr if this resolver doesn't handle the context.
- L28 _public prototype_ `static FName GetModularFeatureName();`

### `Source/Editor/MovieSceneTools/Public/IMovieSceneLinkedAnimTrackProvider.h` (Public)


#### class `IMovieSceneLinkedAnimTrackProvider`  
`class IMovieSceneLinkedAnimTrackProvider : public IModularFeature`  
_L27-94_
- inherits: `IModularFeature`
- desc: Modular feature interface for providing linked animation track or section operations. Implementations handle finding, creating, isolating, and updating linked animation tracks that contain auto-baked animation sequences. Different providers handle different track configurations (e.g., standalone skeletal animation tracks vs. animation mixer sections/tracks). Providers are queried by priority (lower = higher priority). The first provider whose CanHandleBinding() returns true is used for that binding.
- L31 _public prototype_ `static FName GetModularFeatureName();`
- L33 _public function_ `virtual ~IMovieSceneLinkedAnimTrackProvider()`
- L36 _public prototype_ `virtual int32 GetLinkedAnimTrackPriority() const = 0;` — Priority for provider selection. Lower value = higher priority (checked first). Default provider uses 100.
- L39 _public prototype_ `virtual bool CanHandleBinding(const TWeakPtr<ISequencer>& InSequencer, FGuid BindingID) const = 0;` — Returns true if this provider should handle linked anim track operations for this binding.
- L46 _public prototype_ `virtual UMovieSceneTrack* GetLinkedAnimTrack(const TWeakPtr<ISequencer>& InSequencer, FGuid BindingID) const = 0;` — Find the skeletal animation track(section) containing the linked animation sequence. Read-only lookup, does not create anything. @return The UMovieSceneTrack containing the linked anim, or nullptr if not found.
- L55 _public prototype_ `virtual UMovieSceneTrack* GetOrCreateLinkedAnimTrack( const TWeakPtr<ISequencer>& InSequencer, FGuid BindingID, UE::Sequencer::FCommonAnimationTrackEditor& TrackEditor) = 0;` — Find or create the linked animation track setup. If no linked track exists and creation is needed, creates the necessary track structure, linked animation sequence, section, and disables evaluation on the containing track. @param TrackEditor The track editor instance, needed for track creation operations. @return The UMovieSceneTrack containing the linked anim, or nullptr on failure.
- L66 _public prototype_ `virtual bool IsolateLinkedAnimTrack(const TWeakPtr<ISequencer>& InSequencer, FGuid BindingID, bool bIsolate) = 0;` — Isolate or un-isolate the linked animation track. When isolating: enables the linked anim track and disables other animation/control rig tracks. When un-isolating: restores the previous evaluation state. @return true if any track evaluation state was changed.
- L69 _public prototype_ `virtual void UpdateLinkedAnimSectionRange(const TWeakPtr<ISequencer>& InSequencer, FGuid BindingID) = 0;` — Update linked anim section ranges after bake, in case the playback range changed.
- L83 _public function_ `virtual bool TryBakeLinkedAnimSequence( const TWeakPtr<ISequencer>& InSequencer, FGuid BindingID, UAnimSequence* InAnimSequence, const FLevelSequenceAnimSequenceLinkItem& InLinkItem)` — Perform the auto-bake for the linked animation on behalf of the recorder. Providers that own a richer evaluation model than per-frame skeletal mesh component sampling can implement this to write directly into the AnimSequence. The mixer provider, for example, calls its dedicated bake helper which composites the mixer's RootMotionTransform onto the root bone and sets bEnableRootMotion on the asset. Return true if this provider performed the bake. The auto-bake recorder will skip its frame-by-frame fallback when true is returned. The default implementation returns false, leaving the recorder to use UAnimSequenceRecorder.
- L93 _public prototype_ `virtual bool DeleteLinkedAnimTrack(const TWeakPtr<ISequencer>& InSequencer, FGuid BindingID) = 0;` — Delete the linked animation track setup for this binding. @return true if a track was found and removed.

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Sequencer` (scope `UE`)
- L16 _macro_ `#define UE_API MOVIESCENETOOLS_API`

### `Source/Editor/MovieSceneTools/Public/IMovieSceneRootMotionOffsetProvider.h` (Public)


#### class `IMovieSceneRootMotionOffsetProvider`  
`class IMovieSceneRootMotionOffsetProvider : public IModularFeature`  
_L13-35_
- inherits: `IModularFeature`
- desc: Modular feature for systems that apply root motion to scene components. Allows the transform track editor to subtract root motion when auto-keying, preventing double-application of root motion offsets.
- L16 _public prototype_ `virtual ~IMovieSceneRootMotionOffsetProvider() = default;`
- L20 _public prototype_ `virtual FTransform GetRootMotionOffset(const UMovieSceneEntitySystemLinker* Linker, UObject* AnimatedObject) const = 0;` — Returns the root motion offset currently applied to the given object, or Identity if this provider doesn't handle the object.
- L25 _public function_ `virtual FTransform GetRootMotionOffset(const UMovieSceneEntitySystemLinker* Linker, UObject* AnimatedObject, const UObject* EditingContext) const` — Returns the root motion offset for a specific editing context (e.g. a UControlRig on a particular mixer layer). When EditingContext is non-null, the provider may return a per-layer offset rather than the total. Default delegates to the 2-arg version.
- L32 _public function_ `virtual void UpdateRootMotionOffset(UMovieSceneEntitySystemLinker* Linker, UObject* AnimatedObject)` — Recalculates the initial actor transform baseline after the user manually changes the transform.
- L34 _public prototype_ `static FName GetModularFeatureName();`

### `Source/Editor/MovieSceneTools/Public/IMovieSceneTools.h` (Public)


#### class `IMovieSceneTools`  
`class IMovieSceneTools : public IModuleInterface`  
_L11-16_
- inherits: `IModuleInterface`
- desc: The public interface of the MovieSceneTools module

### `Source/Editor/MovieSceneTools/Public/IMovieSceneToolsTrackImporter.h` (Public)


#### class `IMovieSceneToolsTrackImporter`  
`class IMovieSceneToolsTrackImporter`  
_L12-37_
- L25 _public prototype_ `virtual bool ImportAnimatedProperty(const FString& InPropertyName, const FRichCurve& InCurve, FGuid InBinding, UMovieScene* InMovieScene) = 0;` — ImportAnimatedProperty @param InPropertyName The name of the property to import @param InCurve The curve with the keys to import @param InBinding The binding to import the property onto @param InMovieScene The movie scene that contains the binding to import onto @return Whether the property was imported successfully
- L36 _public prototype_ `virtual bool ImportStringProperty(const FString& InPropertyName, const FString& InStringValue, FGuid InBinding, UMovieScene* InMovieScene) = 0;` — ImportStringProperty @param InPropertyName The name of the property to import @param InStringValue The value of the string to import @param InBinding The binding to import the property onto @param InMovieScene The movie scene that contains the binding to import onto @return Whether the property was imported successfully

### `Source/Editor/MovieSceneTools/Public/K2Node_GetSequenceBinding.h` (Public)


#### class `UK2Node_GetSequenceBinding`  
`class UK2Node_GetSequenceBinding : public UK2Node`  
_L20-71_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node`
- L27 _public member_ `FSoftObjectPath SourceSequence_DEPRECATED;` — `UPROPERTY()`
- L31 _public member_ `FMovieSceneObjectBindingID Binding;` — `UPROPERTY()` — The user-selected literal binding identifier from the sequence to use
- L33 _public prototype_ `void SetSequence(UMovieSceneSequence* InSequence);`
- L37 _public prototype_ `virtual void Serialize(FArchive& Ar) override;` — UObject interface
- L41 _public prototype_ `virtual void ValidateNodeDuringCompilation(FCompilerResultsLog& MessageLog) const override;` — UK2Node interface
- L42 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;`
- L43 _public prototype_ `virtual FText GetTooltipText() const override;`
- L44 _public prototype_ `virtual FText GetMenuCategory() const override;`
- L45 _public prototype_ `virtual FSlateIcon GetIconAndTint(FLinearColor& OutColor) const override;`
- L46 _public function_ `virtual bool ShouldShowNodeProperties() const override`
- L47 _public function_ `virtual bool IsNodePure() const override`
- L48 _public prototype_ `virtual void GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;`
- L49 _public function_ `virtual bool IncludeParentNodeContextMenu() const override`
- L50 _public prototype_ `virtual class FNodeHandlingFunctor* CreateNodeHandler(class FKismetCompilerContext& CompilerContext) const override;`
- L51 _public prototype_ `virtual void PreloadRequiredAssets() override;`
- L52 _public prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L53 _public prototype_ `virtual void AllocateDefaultPins() override;`
- L54 _public prototype_ `virtual void PostPlacedNewNode() override;`
- L55 _public prototype_ `virtual TSharedPtr<SGraphNode> CreateVisualWidget() override;`
- L58 _public prototype_ `void SetSequence(const FAssetData& InAssetData);`
- L59 _public prototype_ `FText GetSequenceName() const;`
- L60 _public prototype_ `FText GetBindingName() const;`
- L63 _private prototype_ `UMovieScene* GetObjectMovieScene() const;`
- L67 _private member_ `TObjectPtr<UMovieSceneSequence> SourceMovieSequence;` — `UPROPERTY(EditAnywhere, Category="Sequence", meta=(DisplayName="Source Sequence"))` — The sequence from which to choose a binding identifier
- L69 _private member_ `mutable FMovieSceneSequenceHierarchy SequenceHierarchyCache;`
- L70 _private member_ `mutable TMap<FMovieSceneSequenceID, FGuid> SequenceSignatureCache;`

### `Source/Editor/MovieSceneTools/Public/KeyStructTypes/MovieSceneTextKeyStruct.h` (Public)


#### class `UMovieSceneTextKeyStruct`  
`class UMovieSceneTextKeyStruct : public UMovieSceneKeyStructType`  
_L14-22_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneKeyStructType`
- desc: Derived only to explicitly specify that it's Editor Only to be ignored in Cooked Builds as these KeyStructs are instanced under a non-editor package for text localization @see InstanceGeneratedStruct overload for FMovieSceneTextChannel
- L20 _public function_ `virtual bool IsEditorOnly() const override`

### `Source/Editor/MovieSceneTools/Public/KeyframeTrackEditor.h` (Public)


#### enum `EKeyFrameTrackEditorSetDefault`  
`enum class EKeyFrameTrackEditorSetDefault`  
_L29-37_
- L32 _public enumerator_ `DoNotSetDefault` — Do not set default
- L34 _public enumerator_ `SetDefaultOnAddKeys` — Set default just on keys that have bAddKey set
- L36 _public enumerator_ `SetDefault` — Set default

#### struct `IImpl`  
`struct IImpl`  
_L39-50_
- L41 _public prototype_ `virtual ~IImpl() = default;`
- L44 _public function_ `virtual bool Apply(UMovieSceneSection* Section, FMovieSceneChannelProxy& Proxy, FFrameNumber InTime, EMovieSceneKeyInterpolation InterpolationMode, bool bKeyEvenIfUnchanged, bool bKeyEvenIfEmpty) const` — Returns whether a key was created
- L46 _public function_ `virtual void ApplyDefault(UMovieSceneSection* Section, FMovieSceneChannelProxy& Proxy, EKeyFrameTrackEditorSetDefault SetDefault) const`
- L48 _public function_ `virtual bool ModifyByCurrentAndWeight(FMovieSceneChannelProxy& Proxy, FFrameNumber InTime, void* VCurrentValue, float Weight)`

#### struct `TAddKeyImpl`  
`template<typename ChannelType, typename ValueType> struct TAddKeyImpl : IImpl`  
_L54-111_
- inherits: `IImpl`
- desc: If this implementation changes need to change the specializations below.
- L56 _public member_ `int32 ChannelIndex;`
- L57 _public member_ `bool bAddKey;`
- L58 _public member_ `ValueType ValueToSet;`
- L60 _public function_ `TAddKeyImpl(int32 InChannelIndex, bool bInAddKey, const ValueType& InValue) : ChannelIndex(InChannelIndex), bAddKey(bInAddKey), ValueToSet(InValue)`
- L64 _public function_ `virtual bool Apply(UMovieSceneSection* Section, FMovieSceneChannelProxy& Proxy, FFrameNumber InTime, EMovieSceneKeyInterpolation InterpolationMode, bool bKeyEvenIfUnchanged, bool bKeyEvenIfEmpty) const override`
- L95 _public function_ `virtual void ApplyDefault(UMovieSceneSection* Section, FMovieSceneChannelProxy& Proxy, EKeyFrameTrackEditorSetDefault SetDefault) const override`
- L109 _public function_ `virtual bool ModifyByCurrentAndWeight(FMovieSceneChannelProxy& Proxy, FFrameNumber InTime, void* VCurrentValue, float Weight)`
- L119 _public member_ `bool ValueToSet;`
- L121 _public function_ `TAddKeyImpl(int32 InChannelIndex, bool bInAddKey, const bool& InValue) : ChannelIndex(InChannelIndex), bAddKey(bInAddKey), ValueToSet(InValue)`
- L180 _public member_ `double ValueToSet;`
- L182 _public function_ `TAddKeyImpl(int32 InChannelIndex, bool bInAddKey, const double& InValue) : ChannelIndex(InChannelIndex), bAddKey(bInAddKey), ValueToSet(InValue)`
- L233 _public function_ `virtual bool ModifyByCurrentAndWeight(FMovieSceneChannelProxy& Proxy, FFrameNumber InTime, void* VCurrentValue, float Weight) override`
- L259 _public member_ `float ValueToSet;`
- L261 _public function_ `TAddKeyImpl(int32 InChannelIndex, bool bInAddKey, const float& InValue) : ChannelIndex(InChannelIndex), bAddKey(bInAddKey), ValueToSet(InValue)`
- L338 _public member_ `int32 ValueToSet;`
- L340 _public function_ `TAddKeyImpl(int32 InChannelIndex, bool bInAddKey, const int32& InValue) : ChannelIndex(InChannelIndex),bAddKey(bInAddKey), ValueToSet(InValue)`

#### struct `TAddKeyImpl`  
`template<> struct TAddKeyImpl<FMovieSceneBoolChannel, bool> : IImpl`  
_L115-173_
- inherits: `IImpl`
- desc: bool specialization
- L56 _public member_ `int32 ChannelIndex;`
- L57 _public member_ `bool bAddKey;`
- L58 _public member_ `ValueType ValueToSet;`
- L60 _public function_ `TAddKeyImpl(int32 InChannelIndex, bool bInAddKey, const ValueType& InValue) : ChannelIndex(InChannelIndex), bAddKey(bInAddKey), ValueToSet(InValue)`
- L64 _public function_ `virtual bool Apply(UMovieSceneSection* Section, FMovieSceneChannelProxy& Proxy, FFrameNumber InTime, EMovieSceneKeyInterpolation InterpolationMode, bool bKeyEvenIfUnchanged, bool bKeyEvenIfEmpty) const override`
- L95 _public function_ `virtual void ApplyDefault(UMovieSceneSection* Section, FMovieSceneChannelProxy& Proxy, EKeyFrameTrackEditorSetDefault SetDefault) const override`
- L109 _public function_ `virtual bool ModifyByCurrentAndWeight(FMovieSceneChannelProxy& Proxy, FFrameNumber InTime, void* VCurrentValue, float Weight)`
- L119 _public member_ `bool ValueToSet;`
- L121 _public function_ `TAddKeyImpl(int32 InChannelIndex, bool bInAddKey, const bool& InValue) : ChannelIndex(InChannelIndex), bAddKey(bInAddKey), ValueToSet(InValue)`
- L180 _public member_ `double ValueToSet;`
- L182 _public function_ `TAddKeyImpl(int32 InChannelIndex, bool bInAddKey, const double& InValue) : ChannelIndex(InChannelIndex), bAddKey(bInAddKey), ValueToSet(InValue)`
- L233 _public function_ `virtual bool ModifyByCurrentAndWeight(FMovieSceneChannelProxy& Proxy, FFrameNumber InTime, void* VCurrentValue, float Weight) override`
- L259 _public member_ `float ValueToSet;`
- L261 _public function_ `TAddKeyImpl(int32 InChannelIndex, bool bInAddKey, const float& InValue) : ChannelIndex(InChannelIndex), bAddKey(bInAddKey), ValueToSet(InValue)`
- L338 _public member_ `int32 ValueToSet;`
- L340 _public function_ `TAddKeyImpl(int32 InChannelIndex, bool bInAddKey, const int32& InValue) : ChannelIndex(InChannelIndex),bAddKey(bInAddKey), ValueToSet(InValue)`

#### struct `TAddKeyImpl`  
`template<> struct TAddKeyImpl<FMovieSceneDoubleChannel, double> : IImpl`  
_L176-253_
- inherits: `IImpl`
- desc: Specializations for channels that SUPPORT Blending
- L56 _public member_ `int32 ChannelIndex;`
- L57 _public member_ `bool bAddKey;`
- L58 _public member_ `ValueType ValueToSet;`
- L60 _public function_ `TAddKeyImpl(int32 InChannelIndex, bool bInAddKey, const ValueType& InValue) : ChannelIndex(InChannelIndex), bAddKey(bInAddKey), ValueToSet(InValue)`
- L64 _public function_ `virtual bool Apply(UMovieSceneSection* Section, FMovieSceneChannelProxy& Proxy, FFrameNumber InTime, EMovieSceneKeyInterpolation InterpolationMode, bool bKeyEvenIfUnchanged, bool bKeyEvenIfEmpty) const override`
- L95 _public function_ `virtual void ApplyDefault(UMovieSceneSection* Section, FMovieSceneChannelProxy& Proxy, EKeyFrameTrackEditorSetDefault SetDefault) const override`
- L109 _public function_ `virtual bool ModifyByCurrentAndWeight(FMovieSceneChannelProxy& Proxy, FFrameNumber InTime, void* VCurrentValue, float Weight)`
- L119 _public member_ `bool ValueToSet;`
- L121 _public function_ `TAddKeyImpl(int32 InChannelIndex, bool bInAddKey, const bool& InValue) : ChannelIndex(InChannelIndex), bAddKey(bInAddKey), ValueToSet(InValue)`
- L180 _public member_ `double ValueToSet;`
- L182 _public function_ `TAddKeyImpl(int32 InChannelIndex, bool bInAddKey, const double& InValue) : ChannelIndex(InChannelIndex), bAddKey(bInAddKey), ValueToSet(InValue)`
- L233 _public function_ `virtual bool ModifyByCurrentAndWeight(FMovieSceneChannelProxy& Proxy, FFrameNumber InTime, void* VCurrentValue, float Weight) override`
- L259 _public member_ `float ValueToSet;`
- L261 _public function_ `TAddKeyImpl(int32 InChannelIndex, bool bInAddKey, const float& InValue) : ChannelIndex(InChannelIndex), bAddKey(bInAddKey), ValueToSet(InValue)`
- L338 _public member_ `int32 ValueToSet;`
- L340 _public function_ `TAddKeyImpl(int32 InChannelIndex, bool bInAddKey, const int32& InValue) : ChannelIndex(InChannelIndex),bAddKey(bInAddKey), ValueToSet(InValue)`

#### struct `TAddKeyImpl`  
`template<> struct TAddKeyImpl<FMovieSceneFloatChannel, float> : IImpl`  
_L255-332_
- inherits: `IImpl`
- L56 _public member_ `int32 ChannelIndex;`
- L57 _public member_ `bool bAddKey;`
- L58 _public member_ `ValueType ValueToSet;`
- L60 _public function_ `TAddKeyImpl(int32 InChannelIndex, bool bInAddKey, const ValueType& InValue) : ChannelIndex(InChannelIndex), bAddKey(bInAddKey), ValueToSet(InValue)`
- L64 _public function_ `virtual bool Apply(UMovieSceneSection* Section, FMovieSceneChannelProxy& Proxy, FFrameNumber InTime, EMovieSceneKeyInterpolation InterpolationMode, bool bKeyEvenIfUnchanged, bool bKeyEvenIfEmpty) const override`
- L95 _public function_ `virtual void ApplyDefault(UMovieSceneSection* Section, FMovieSceneChannelProxy& Proxy, EKeyFrameTrackEditorSetDefault SetDefault) const override`
- L109 _public function_ `virtual bool ModifyByCurrentAndWeight(FMovieSceneChannelProxy& Proxy, FFrameNumber InTime, void* VCurrentValue, float Weight)`
- L119 _public member_ `bool ValueToSet;`
- L121 _public function_ `TAddKeyImpl(int32 InChannelIndex, bool bInAddKey, const bool& InValue) : ChannelIndex(InChannelIndex), bAddKey(bInAddKey), ValueToSet(InValue)`
- L180 _public member_ `double ValueToSet;`
- L182 _public function_ `TAddKeyImpl(int32 InChannelIndex, bool bInAddKey, const double& InValue) : ChannelIndex(InChannelIndex), bAddKey(bInAddKey), ValueToSet(InValue)`
- L233 _public function_ `virtual bool ModifyByCurrentAndWeight(FMovieSceneChannelProxy& Proxy, FFrameNumber InTime, void* VCurrentValue, float Weight) override`
- L259 _public member_ `float ValueToSet;`
- L261 _public function_ `TAddKeyImpl(int32 InChannelIndex, bool bInAddKey, const float& InValue) : ChannelIndex(InChannelIndex), bAddKey(bInAddKey), ValueToSet(InValue)`
- L338 _public member_ `int32 ValueToSet;`
- L340 _public function_ `TAddKeyImpl(int32 InChannelIndex, bool bInAddKey, const int32& InValue) : ChannelIndex(InChannelIndex),bAddKey(bInAddKey), ValueToSet(InValue)`

#### struct `TAddKeyImpl`  
`template<> struct TAddKeyImpl<FMovieSceneIntegerChannel, int32> : IImpl`  
_L334-411_
- inherits: `IImpl`
- L56 _public member_ `int32 ChannelIndex;`
- L57 _public member_ `bool bAddKey;`
- L58 _public member_ `ValueType ValueToSet;`
- L60 _public function_ `TAddKeyImpl(int32 InChannelIndex, bool bInAddKey, const ValueType& InValue) : ChannelIndex(InChannelIndex), bAddKey(bInAddKey), ValueToSet(InValue)`
- L64 _public function_ `virtual bool Apply(UMovieSceneSection* Section, FMovieSceneChannelProxy& Proxy, FFrameNumber InTime, EMovieSceneKeyInterpolation InterpolationMode, bool bKeyEvenIfUnchanged, bool bKeyEvenIfEmpty) const override`
- L95 _public function_ `virtual void ApplyDefault(UMovieSceneSection* Section, FMovieSceneChannelProxy& Proxy, EKeyFrameTrackEditorSetDefault SetDefault) const override`
- L109 _public function_ `virtual bool ModifyByCurrentAndWeight(FMovieSceneChannelProxy& Proxy, FFrameNumber InTime, void* VCurrentValue, float Weight)`
- L119 _public member_ `bool ValueToSet;`
- L121 _public function_ `TAddKeyImpl(int32 InChannelIndex, bool bInAddKey, const bool& InValue) : ChannelIndex(InChannelIndex), bAddKey(bInAddKey), ValueToSet(InValue)`
- L180 _public member_ `double ValueToSet;`
- L182 _public function_ `TAddKeyImpl(int32 InChannelIndex, bool bInAddKey, const double& InValue) : ChannelIndex(InChannelIndex), bAddKey(bInAddKey), ValueToSet(InValue)`
- L233 _public function_ `virtual bool ModifyByCurrentAndWeight(FMovieSceneChannelProxy& Proxy, FFrameNumber InTime, void* VCurrentValue, float Weight) override`
- L259 _public member_ `float ValueToSet;`
- L261 _public function_ `TAddKeyImpl(int32 InChannelIndex, bool bInAddKey, const float& InValue) : ChannelIndex(InChannelIndex), bAddKey(bInAddKey), ValueToSet(InValue)`
- L338 _public member_ `int32 ValueToSet;`
- L340 _public function_ `TAddKeyImpl(int32 InChannelIndex, bool bInAddKey, const int32& InValue) : ChannelIndex(InChannelIndex),bAddKey(bInAddKey), ValueToSet(InValue)`

#### struct `FMovieSceneChannelValueSetter`  
`struct FMovieSceneChannelValueSetter`  
_L412-515_
- L414 _public prototype_ `FMovieSceneChannelValueSetter(const FMovieSceneChannelValueSetter&) = delete;`
- L415 _public prototype_ `FMovieSceneChannelValueSetter& operator=(const FMovieSceneChannelValueSetter&) = delete;`
- L417 _public prototype_ `FMovieSceneChannelValueSetter(FMovieSceneChannelValueSetter&&) = default;`
- L418 _public prototype_ `FMovieSceneChannelValueSetter& operator=(FMovieSceneChannelValueSetter&&) = default;`
- L422 _public function_ `template<typename ChannelType, typename ValueType> static FMovieSceneChannelValueSetter Create(int32 ChannelIndex, ValueType&& InNewValue, bool bAddKey)` — Templated construction function that can add a key (and potentially also set a default) for the specified channel and value
- L431 _public function_ `static FMovieSceneChannelValueSetter Create(UE::MovieScene::FUnpackedChannelValue&& InValue, bool bAddKey)` — Templated construction function that can add a key (and potentially also set a default) for the specified channel and value
- L438 _public function_ `IImpl* operator->()`
- L443 _public function_ `const IImpl* operator->() const`
- L450 _private function_ `FMovieSceneChannelValueSetter()`
- L514 _private member_ `TInlineValue<IImpl> Impl;`

#### struct `FMovieSceneChannelValueSetter::FUnpackedChannelValueSetter`  
`struct FUnpackedChannelValueSetter : IImpl`  
_L453-512_
- inherits: `IImpl`
- L455 _public member_ `UE::MovieScene::FUnpackedChannelValue ChannelValue;`
- L456 _public member_ `bool bAddKey;`
- L458 _public function_ `FUnpackedChannelValueSetter(UE::MovieScene::FUnpackedChannelValue&& InValue, bool bInAddKey) : ChannelValue(MoveTemp(InValue)), bAddKey(bInAddKey)`
- L462 _public function_ `virtual bool Apply(UMovieSceneSection* Section, FMovieSceneChannelProxy& Proxy, FFrameNumber InTime, EMovieSceneKeyInterpolation InterpolationMode, bool bKeyEvenIfUnchanged, bool bKeyEvenIfEmpty) const override`
- L492 _public function_ `virtual void ApplyDefault(UMovieSceneSection* Section, FMovieSceneChannelProxy& Proxy, EKeyFrameTrackEditorSetDefault SetDefault) const override`
- L507 _public function_ `virtual bool ModifyByCurrentAndWeight(FMovieSceneChannelProxy& Proxy, FFrameNumber InTime, void* VCurrentValue, float Weight) override`

#### class `FKeyframeTrackEditor`  
`template<typename TrackType> class FKeyframeTrackEditor : public FMovieSceneTrackEditor`  
_L523-790_
- inherits: `FMovieSceneTrackEditor`
- desc: A base class for track editors that edit tracks which contain sections implementing GetKeyDataInterface.
- L527 _public typedef_ `using GenerateKeysCallback = TFunction<void(UMovieSceneSection*, FGeneratedTrackKeys&)>;`
- L534 _public function_ `FKeyframeTrackEditor( TSharedRef<ISequencer> InSequencer ) : FMovieSceneTrackEditor( InSequencer )` — Constructor @param InSequencer The sequencer instance to be used by this tool
- L539 _public prototype_ `~FKeyframeTrackEditor() = default;` — Virtual destructor.
- L545 _public function_ `virtual FText GetDisplayName() const override`
- L550 _public function_ `virtual bool SupportsType( TSubclassOf<UMovieSceneTrack> Type ) const override`
- L556 _public function_ `virtual void BuildTrackContextMenu(FMenuBuilder& MenuBuilder, UMovieSceneTrack* Track) override`
- L580 _protected function_ `FKeyPropertyResult AddKeysToObjects( TArrayView<UObject* const> ObjectsToKey, FFrameNumber KeyTime, ESequencerKeyMode KeyMode, TSubclassOf<UMovieSceneTrack> TrackClass, FName PropertyName, TFunction<void(TrackType*)> OnInitializeNewTrack, const GenerateKeysCallback& OnGenerateKeys)` — Adds keys to the specified object.  This may also add tracks and sections depending on the options specified. @param ObjectsToKey An array of objects to add keyframes to. @param KeyTime The time to add keys. @param KeyedChannels Aggregate of optionally enabled channel values for which to create new keys @param ChannelDefaults Aggregate of optionally enabled channel default values that should be applied to the section @param KeyParams The parameters to control keyframing behavior. @param TrackClass The class of track which should be created if specified in the parameters. @param PropertyName The name of the property to add keys for. @param OnInitializeNewTrack A delegate which allows for custom initialization for new tracks.  This is called after the track is created, but before any sections or keys have been added. @return Whether or not a handle guid or track was created. Note this does not return true if keys were added or modified.
- L616 _private function_ `void ClearDefaults( UMovieSceneTrack* Track )`
- L635 _private function_ `void AddTrackDefaultsItems( FMenuBuilder& MenuBuilder, UMovieSceneTrack* Track )`
- L660 _private function_ `FKeyPropertyResult AddKeysToHandle(UObject *Object, FGuid ObjectHandle, FFrameNumber KeyTime, ESequencerKeyMode KeyMode, TSubclassOf<UMovieSceneTrack> TrackClass, FName PropertyName, TFunction<void(TrackType*)> OnInitializeNewTrack, const GenerateKeysCallback& OnGenerateKeys)` — Adds keys to the specified guid.  This may also add tracks and sections depending on the options specified. @param Object Object to add keyframes to. @param ObjectHandle Object Handle to add keyframes to. @param KeyTime The time to add keys. @param GeneratedKeys Array of keys to set @param KeyParams The parameters to control keyframing behavior. @param TrackClass The class of track which should be created if specified in the parameters. @param PropertyName The name of the property to add keys for. @param OnInitializeNewTrack A delegate which allows for custom initialization for new tracks.  This is called after the track is created, but before any sections or keys have been added. @return Whether or not a track was created. Note this does not return true if keys were added or modified.
- L730 _protected function_ `FKeyPropertyResult AddKeysToSection(UMovieSceneSection* Section, FFrameNumber KeyTime, const FGeneratedTrackKeys& Keys, ESequencerKeyMode KeyMode, EKeyFrameTrackEditorSetDefault SetDefault = EKeyFrameTrackEditorSetDefault::SetDefault)` — Returns whether a section was added
- L779 _protected function_ `virtual bool ModifyGeneratedKeysByCurrentAndWeight(UObject *Object, UMovieSceneTrack *Track, UMovieSceneSection* SectionToKey, FFrameNumber Time, FGeneratedTrackKeys& GeneratedTotalKeys, float Weight) const` — `UE_DEPRECATED(5.7, "This function is no longer called. Please ensure that generated keys populated through GenerateKeysCallback have already been compensated.")`
- L785 _protected function_ `static bool CanAutoKeySection(UMovieSceneSection* Section, FFrameNumber Time)` — Check whether we can autokey the specified section at the specified time

#### Free symbols / members of external scopes

- L517 _typedef_ `typedef TArray<FMovieSceneChannelValueSetter, TInlineAllocator<1>> FGeneratedTrackKeys;`

### `Source/Editor/MovieSceneTools/Public/LevelSequenceFBXInterop.h` (Public)


#### class `FLevelSequenceFBXInterop`  
`class FLevelSequenceFBXInterop`  
_L9-30_
- L13 _public prototype_ `FLevelSequenceFBXInterop(TSharedRef<ISequencer> InSequencer);`
- L16 _public prototype_ `void ImportFBX();` — Imports the animation from an fbx file.
- L17 _public prototype_ `void ImportFBXOntoSelectedNodes();`
- L20 _public prototype_ `void ExportFBX();` — Exports the animation to an fbx file.
- L25 _private prototype_ `void ExportFBXInternal(const FString& ExportFilename, const TArray<FGuid>& Bindings, const TArray<UMovieSceneTrack*>& Tracks);` — Exports sequence to a FBX file
- L29 _private member_ `TWeakPtr<ISequencer> WeakSequencer;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API MOVIESCENETOOLS_API`

### `Source/Editor/MovieSceneTools/Public/MVVM/ViewModels/BindingLifetimeTrackModel.h` (Public)


#### class `UE::Sequencer::FBindingLifetimeTrackModel`  
`class FBindingLifetimeTrackModel : public FTrackModel , public IBindingLifetimeExtension`  
_L22-51_
- inherits: `FTrackModel,IBindingLifetimeExtension`
- L30 _public prototype_ `static TSharedPtr<FTrackModel> CreateTrackModel(UMovieSceneTrack* Track);`
- L32 _public prototype_ `explicit FBindingLifetimeTrackModel(UMovieSceneBindingLifetimeTrack* Track);`
- L34 _public prototype_ `FSortingKey GetSortingKey() const override;`
- L36 _public prototype_ `void OnDeferredModifyFlush() override;`
- L39 _public function_ `const TArray<FFrameNumberRange>& GetInverseLifetimeRange() const override` — IBindingLifetimeExtension
- L42 _protected prototype_ `virtual void OnConstruct() override;`
- L45 _private prototype_ `void RecalculateInverseLifetimeRange();`
- L49 _private member_ `TArray<FFrameNumberRange> InverseLifetimeRange;` — The inverse of the range created by all of our binding lifetime sections In other words, the ranges where the object binding should be deactivated.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MOVIESCENETOOLS_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Sequencer` (scope `UE`)
- L17 _namespace_ `namespace UE`
- L19 _namespace_ `namespace Sequencer` (scope `UE`)

### `Source/Editor/MovieSceneTools/Public/MovieSceneDirectorBlueprintEndpointCustomization.h` (Public)


#### enum `EAutoCreatePayload`  
`enum class EAutoCreatePayload : uint8`  
_L34-39_
- L36 _public enumerator_ `None = 0`
- L37 _public enumerator_ `Pins = 1 << 0`
- L38 _public enumerator_ `Variables = 1 << 1`

#### class `FMovieSceneDirectorBlueprintEndpointCustomization`  
`class FMovieSceneDirectorBlueprintEndpointCustomization : public IPropertyTypeCustomization`  
_L48-328_
- inherits: `IPropertyTypeCustomization`
- desc: Base class for details view customizations that operate on sequence director blueprint endpoints.
- L53 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;` — IPropertyTypeCustomization interface
- L54 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L62 _public prototype_ `void CreateEndpoint();` — Creates a single new endpoint represented by this property handle.
- L67 _public prototype_ `void PopulateQuickBindSubMenu(FMenuBuilder& MenuBuilder, UMovieSceneSequence* Sequence, FOnQuickBindActionSelected InOnQuickBindActionSelected);` — Generate the content of the quick bind sub-menu dropdown (shown if the endpoint is not already bound)
- L72 _public prototype_ `void HandleQuickBindActionSelected(const TArray<TSharedPtr<FEdGraphSchemaAction>>& SelectedAction, ESelectInfo::Type InSelectionType, UBlueprint* Blueprint, FMovieSceneDirectorBlueprintEndpointDefinition EndpointDefinition);` — Called when a quick bind action has been selected
- L75 _public prototype_ `void SetPropertyHandle(TSharedPtr<IPropertyHandle> InPropertyHandle);` — Set the property handle to use for customization. Used when using the customization class as a helper.
- L78 _public function_ `void SetRawData(const TArray<void*>& InRawData)` — Set the raw data to use for customization. Used when the customization class is used as a helper without a details view.
- L82 _protected typedef_ `using FPayloadVariableMap = TMap<FName, FMovieSceneDirectorBlueprintVariableValue, TInlineSetAllocator<8>>;`
- L115 _protected prototype_ `virtual void GetPayloadVariables(UObject* EditObject, void* RawData, FPayloadVariableMap& OutPayloadVariables) const = 0;` — Gets the payload values to pass to the endpoint. @param EditObject		The edited object for which to get the endpoint call payload variables @param RawData			The raw data for which to get the endpoint call payload variables @param OutPayloadVariables	The string values of the payload variables to pass to the endpoint
- L127 _protected prototype_ `virtual bool SetPayloadVariable(UObject* EditObject, void* RawData, FName FieldName, const FMovieSceneDirectorBlueprintVariableValue& NewVariableValue) = 0;` — Sets a payload value to pass to the endpoint. @param EditObject		The edited object for which to set the endpoint call payload variable @param RawData			The raw data for which to set the endpoint call payload variable @param FieldName			The name of the payload variable to set @param NewVariableValue	The string value of the payload variable to set @param NewVariableObject	In the case the payload is a UObject, a reference to the UObject @return					Whether the payload variable was set
- L139 _protected function_ `virtual void GetWellKnownParameterPinNames(UObject* EditObject, void* RawData, TArray<FName>& OutParameters) const` — Get the pin names setup with "well-known parameters" for the currently edited objects. The output array of pin names should be of the same size as GetWellKnownParameterCandidates, with NAME_None for those parameters that aren't hooked up to any pin. @param EditObject		The edited object on which to get the connected pin names @param RawData			The raw data on which to get the connected pin names @param OutParameters		The list of pin names connected to "well-known parameters"
- L150 _protected function_ `virtual void GetWellKnownParameterCandidates(UK2Node* Endpoint, TArray<FWellKnownParameterCandidates>& OutCandidates) const` — Get the pins that are candidates for any "well-known parameter". The output array of pin candidates should be of the same size as GetWellKnownParameterPinNames, with an empty array of candidates for those parameters that currently have no compatible pins. @param EditObject		The edited object on which to set the connected pin name @param RawData			The raw data on which to set the connected pin name
- L160 _protected function_ `virtual bool SetWellKnownParameterPinName(UObject* EditObject, void* RawData, int32 ParameterIndex, FName BoundPinName)` — Set the pin name for the given "well-known parameter". @param EditObject		The edited object on which to set the connected pin name @param RawData			The raw data on which to set the connected pin name @param ParameterIndex	The index of the "well-known parameter", as reported by GetWellKnownParameterCandidates @return					Whether the pin name was successfully set
- L165 _protected prototype_ `virtual FMovieSceneDirectorBlueprintEndpointDefinition GenerateEndpointDefinition(UMovieSceneSequence* Sequence) = 0;` — Generate endpoint definition for the sequence.
- L170 _protected prototype_ `virtual UK2Node* FindEndpoint(UMovieSceneSequence* Sequence, UBlueprint* Blueprint, UObject* EditObject, void* RawData) const = 0;` — Called to find the endpoint node in the director blueprint.
- L175 _protected prototype_ `virtual void OnCreateEndpoint(UMovieSceneSequence* Sequence, UBlueprint* Blueprint, const TArray<UObject*> EditObjects, const TArray<void*> RawData, const FMovieSceneDirectorBlueprintEndpointDefinition& EndpointDefinition, UK2Node* NewEndpoint) = 0;` — Called when an endpoint has been created.
- L180 _protected prototype_ `virtual void OnSetEndpoint(UMovieSceneSequence* Sequence, UBlueprint* Blueprint, const TArray<UObject*> EditObjects, const TArray<void*> RawData, const FMovieSceneDirectorBlueprintEndpointDefinition& EndpointDefinition, UK2Node* NewEndpoint) = 0;` — Called when an endpoint has been set.
- L185 _protected function_ `virtual bool OnRebindEndpoint(UMovieSceneSequence* Sequence, UBlueprint* Blueprint, const TArray<UObject*> EditObjects, const TArray<void*> RawData, const FMovieSceneDirectorBlueprintEndpointDefinition& EndpointDefinition, TSharedPtr<FEdGraphSchemaAction> Action)` — Called when an endpoint was set and has been changed to another endpoint.
- L191 _protected prototype_ `virtual void GetEditObjects(TArray<UObject*>& OutObjects) const;` — Get all the objects that the endpoints reside within. By default, this gets the outer objects of the property handle.
- L196 _protected function_ `virtual void OnCollectQuickBindActions(UBlueprint* Blueprint, FBlueprintActionMenuBuilder& MenuBuilder)` — Collect blueprint actions for quick-binding a non-connected endpoint.
- L201 _protected function_ `virtual void OnCollectAllRebindActions(UBlueprint* Blueprint, FBlueprintActionMenuBuilder& MenuBuilder)` — Collect blueprint actions for rebinding an already connected endpoint.
- L203 _protected function_ `virtual bool CreateNewCategoryForPayloadVariables() const`
- L211 _protected prototype_ `void ClearEndpoint();` — Clear the endpoint represented by this property handle. @note: Does not delete the endpoint in the blueprint itself.
- L217 _protected prototype_ `UK2Node* FindEndpoint(UObject* EditObject, void* RawData) const;` — Find the endpoint node in the director blueprint.
- L222 _protected prototype_ `void SetEndpoint(const FMovieSceneDirectorBlueprintEndpointDefinition& EndpointDefinition, UK2Node* NewEndpoint, UK2Node* PayloadTemplate, EAutoCreatePayload AutoCreatePayload);` — Assigns the specified function entry to this property handle.
- L227 _protected prototype_ `void NavigateToDefinition();` — Navigate to the definition of the endpoint represented by this property handle.
- L232 _protected prototype_ `TSharedRef<SWidget> GetMenuContent();` — Generate the content of the main combo button menu dropdown
- L237 _protected prototype_ `void PopulateRebindSubMenu(FMenuBuilder& MenuBuilder, UMovieSceneSequence* Sequence);` — Generate the content of the rebind sub-menu dropdown (shown if the endpoint is already bound)
- L242 _protected prototype_ `void OnPayloadVariableChanged(TSharedRef<FStructOnScope> InStructData, TSharedPtr<IPropertyHandle> LocalVariableProperty);` — Called when a payload variable property value is changed on the details panel
- L252 _protected typedef_ `using FSequenceDataMap = TMap<UMovieSceneSequence*, FSequenceData>;`
- L257 _protected prototype_ `void GatherSequenceData(FSequenceDataMap& AllSequenceData);` — Gather data for the sequences being edited.
- L262 _protected function_ `TSharedPtr<IPropertyHandle> GetPropertyHandle() const` — Get the property handle for this customization.
- L267 _protected function_ `TSharedPtr<IPropertyUtilities> GetPropertyUtilities() const` — Get the property utilities for this customization.
- L272 _protected prototype_ `UMovieSceneSequence* GetCommonSequence() const;` — Get the sequence that is common to all the values in our property handle, or nullptr if they are not all the same.
- L277 _protected prototype_ `UK2Node* GetCommonEndpoint() const;` — Get the endpoint that is common to all the values in our property handle, or nullptr if they are not all the same.
- L282 _protected prototype_ `TArray<UK2Node*> GetAllValidEndpoints() const;` — Get all the endpoints of all the values in our property handle.
- L287 _protected prototype_ `void IterateEndpoints(TFunctionRef<bool(UK2Node*)> Callback) const;` — Invoke a callback on all the endpoints.
- L291 _protected member_ `TSharedPtr<IPropertyHandle> PropertyHandle;` — The property handle we're reflecting
- L294 _protected member_ `TSharedPtr<IPropertyUtilities> PropertyUtilities;` — Property utilities for the property we're editing
- L297 _protected member_ `TArray<void*> PropertyRawData;` — RawData taken either from the PropertyHandle, or manually passed into the customization for cases this is used as a helper
- L301 _private prototype_ `void CollectQuickBindActions(FGraphActionListBuilderBase& OutAllActions, UBlueprint* Blueprint, FMovieSceneDirectorBlueprintEndpointDefinition EndpointDefinition);`
- L302 _private prototype_ `void CollectAllRebindActions(FGraphActionListBuilderBase& OutAllActions, UBlueprint* Blueprint, FMovieSceneDirectorBlueprintEndpointDefinition EndpointDefinition);`
- L307 _private prototype_ `FText GetEndpointName() const;` — Get the name of the endpoint to display on the main combo button
- L309 _private prototype_ `const FSlateBrush* GetEndpointIcon() const;` — Get the icon of the endpoint to display on the main combo button
- L311 _private prototype_ `void HandleRebindActionSelected(const TArray<TSharedPtr<FEdGraphSchemaAction>>& SelectedAction, ESelectInfo::Type InSelectionType, UBlueprint* Blueprint, FMovieSceneDirectorBlueprintEndpointDefinition EndpointDefinition);`
- L313 _private prototype_ `void OnBlueprintCompiled(UBlueprint*);`
- L315 _private prototype_ `ECheckBoxState GetCallInEditorCheckState() const;`
- L316 _private prototype_ `void OnSetCallInEditorCheckState(ECheckBoxState NewCheckBoxState);`
- L318 _private prototype_ `TSharedRef<SWidget> GetWellKnownParameterPinMenuContent(int32 ParameterIndex);`
- L319 _private prototype_ `const FSlateBrush* GetWellKnownParameterPinIcon(int32 ParameterIndex) const;`
- L320 _private prototype_ `FText GetWellKnownParameterPinText(int32 ParameterIndex) const;`
- L321 _private prototype_ `bool CompareWellKnownParameterPinName(int32 ParameterIndex, FName InPinName) const;`
- L322 _private prototype_ `void SetWellKnownParameterPinName(int32 ParameterIndex, FName InNewWellKnownParameterPinName);`
- L327 _private member_ `TWeakObjectPtr<UK2Node_FunctionEntry> CachedCommonEndpoint;` — A cache of the common endpoint that is only used when the menu is open to avoid re-computing it every frame.

#### struct `FMovieSceneDirectorBlueprintEndpointCustomization::FWellKnownParameterMetadata`  
`struct FWellKnownParameterMetadata`  
_L88-93_
- desc: User-interface information for "well-known parameters", i.e. parameters that can be bound to values provided by the underlying system, as opposed to values entered by the user.
- L90 _public member_ `FText PickerLabel;`
- L91 _public member_ `FText PickerTooltip;`
- L92 _public member_ `FText CandidateTooltip;`

#### struct `FMovieSceneDirectorBlueprintEndpointCustomization::FWellKnownParameterCandidates`  
`struct FWellKnownParameterCandidates`  
_L98-106_
- desc: Structure specifying candidate pins for a given "well-known parameter".
- L101 _public member_ `TArray<FName> CandidatePinNames;` — Names of the pins that can be bound to the "well-known parameter" described in the metadata
- L103 _public member_ `FWellKnownParameterMetadata Metadata;` — User-interface information for the "well-known parameter"
- L105 _public member_ `bool bShowUnmatchedParameters = false;` — Whether to show this "well-known" parameter when no candidate pins have been found

#### struct `FMovieSceneDirectorBlueprintEndpointCustomization::FSequenceData`  
`struct FSequenceData`  
_L246-251_
- L248 _public member_ `UBlueprint* Blueprint;`
- L249 _public member_ `TArray<UObject*> EditObjects;`
- L250 _public member_ `TArray<void*> RawData;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MOVIESCENETOOLS_API`
- L42 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnActionSelected, const TArray< TSharedPtr<FEdGraphSchemaAction> >&, ESelectInfo::Type);`
- L42 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnActionSelected, const TArray< TSharedPtr<FEdGraphSchemaAction> >&, ESelectInfo::Type);`
- L43 _delegate_ `DECLARE_DELEGATE_FourParams(FOnQuickBindActionSelected, const TArray<TSharedPtr<FEdGraphSchemaAction>>&, ESelectInfo::Type, UBlueprint*, FMovieSceneDirectorBlueprintEndpointDefinition);`
- L43 _prototype_ `DECLARE_DELEGATE_FourParams(FOnQuickBindActionSelected, const TArray<TSharedPtr<FEdGraphSchemaAction>>&, ESelectInfo::Type, UBlueprint*, FMovieSceneDirectorBlueprintEndpointDefinition);`

### `Source/Editor/MovieSceneTools/Public/MovieSceneDirectorBlueprintUtils.h` (Public)


#### enum `EMovieSceneDirectorBlueprintEndpointType`  
`enum class EMovieSceneDirectorBlueprintEndpointType`  
_L36-41_
- desc: Sequence Director Blueprint endpoint type
- L38 _public enumerator_ `None = 0`
- L39 _public enumerator_ `Event`
- L40 _public enumerator_ `Function`

#### struct `FMovieSceneDirectorBlueprintEndpointParameter`  
`struct FMovieSceneDirectorBlueprintEndpointParameter`  
_L46-54_
- desc: Structure for creating extra parameter pins on an enpdoint
- L48 _public member_ `FString PinName;`
- L49 _public member_ `EEdGraphPinDirection PinDirection;`
- L50 _public member_ `FName PinTypeCategory;`
- L51 _public member_ `TWeakObjectPtr<UObject> PinTypeClass;`
- L53 _public prototype_ `static FString SanitizePinName(const FString& InPinName);`

#### struct `FMovieSceneDirectorBlueprintVariableValue`  
`struct FMovieSceneDirectorBlueprintVariableValue`  
_L59-66_
- desc: Structure for holding value of a blueprint variable
- L62 _public member_ `FSoftObjectPath ObjectValue;` — In the case the variable is a UObject, reference to the UObject
- L65 _public member_ `FString Value;` — String value of the variable

#### struct `FMovieSceneDirectorBlueprintEndpointDefinition`  
`struct FMovieSceneDirectorBlueprintEndpointDefinition`  
_L71-114_
- desc: Parameters for creating a blueprint endpoint
- L74 _public member_ `EMovieSceneDirectorBlueprintEndpointType EndpointType;` — Type of endpoint
- L77 _public member_ `FString GraphName;` — Name of the event or function graph
- L80 _public member_ `FString EndpointName;` — Name of the event or function
- L83 _public member_ `UFunction* EndpointSignature = nullptr;` — Function signature, for function endpoint types
- L86 _public member_ `UClass* PossibleCallTargetClass = nullptr;` — Optional class on which the endpoint can call functions
- L89 _public member_ `TArray<FMovieSceneDirectorBlueprintEndpointParameter> ExtraPins;` — Extra pins to create on the endpoint
- L91 _public function_ `FMovieSceneDirectorBlueprintEndpointDefinition() : EndpointType(EMovieSceneDirectorBlueprintEndpointType::None)`
- L95 _public function_ `void AddExtraInputPin(const FString& InName, FName InPinCategory, TWeakObjectPtr<UObject> InPinTypeClass = nullptr)`
- L105 _public function_ `void AddExtraOutputPin(const FString& InName, FName InPinCategory, TWeakObjectPtr<UObject> InPinTypeClass = nullptr)`

#### struct `FMovieSceneCustomizeDirectorBlueprintEndpointCallParams`  
`struct FMovieSceneCustomizeDirectorBlueprintEndpointCallParams`  
_L117-123_
- desc: Parameters for endpoint call customization callback
- L119 _public member_ `UEdGraph* FunctionGraph = nullptr;`
- L120 _public member_ `UK2Node_FunctionEntry* FunctionEntryNode = nullptr;`
- L121 _public member_ `UK2Node_CallFunction* CallFunctionNode = nullptr;`
- L122 _public member_ `UK2Node_FunctionResult* FunctionResultNode = nullptr;`

#### struct `FMovieSceneDirectorBlueprintEndpointCall`  
`struct FMovieSceneDirectorBlueprintEndpointCall`  
_L130-143_
- desc: Parameters for creating an entry point, i.e. a call to an endpoint
- L133 _public member_ `UEdGraphNode* Endpoint = nullptr;` — The endpoint node to call
- L136 _public member_ `TArray<FName> ExposedPinNames;` — List of endpoint node pins that should be exposed to the call, for receiving special values at runtime
- L139 _public member_ `TMap<FName, FMovieSceneDirectorBlueprintVariableValue> PayloadVariables;` — The values to pass to the endpoint node's parameters
- L142 _public member_ `FMovieSceneCustomizeDirectorBlueprintEndpointCallDelegate CustomizeEndpointCall;` — Callback for customizing the endpoint call

#### struct `FMovieSceneDirectorBlueprintEntrypointResult`  
`struct FMovieSceneDirectorBlueprintEntrypointResult`  
_L148-166_
- desc: Result structure for a created blueprint entry point, i.e. a call to an endpoint
- L151 _public member_ `FName CompiledFunctionName;` — The name of the function that calls the endpoint
- L153 _public member_ `UK2Node_FunctionEntry* Entrypoint = nullptr;` — The entry point node
- L155 _public member_ `TArray<FName> StalePayloadVariables;` — A list of payload variables that aren't valid anymore
- L159 _public function_ `template<typename Container> void CleanUpStalePayloadVariables(Container& InPayloadVariables) const` — A utility method for cleaning up stale payload variables

#### struct `FMovieSceneDirectorBlueprintUtils`  
`struct FMovieSceneDirectorBlueprintUtils`  
_L171-228_
- desc: Static utility library for dealing with movie-scene blueprint endpoints at edit/cook-time
- L180 _public prototype_ `static UK2Node* CreateEndpoint(UBlueprint* Blueprint, const FMovieSceneDirectorBlueprintEndpointDefinition& EndpointDefinition);` — Create a new endpoint for the specified sequence. @param Blueprint       (Required, non-null) The blueprint within which to create the new custom event @param EndpointDefinition  The end point definition @return A valid pointer to the blueprint node for the endpoint
- L191 _public prototype_ `static UK2Node_CustomEvent* CreateEventEndpoint(UBlueprint* Blueprint, const FMovieSceneDirectorBlueprintEndpointDefinition& EndpointDefinition);` — Create a new event endpoint for the specified sequence. By default, event endpoints are presented as a UK2Node_CustomEvent in an event graph called "Sequencer Events" with a pin for the bound object. @param Blueprint       (Required, non-null) The blueprint within which to create the new custom event @param EndpointDefinition  The end point definition @return A valid pointer to the blueprint node for the endpoint
- L200 _public prototype_ `static UK2Node_FunctionEntry* CreateFunctionEndpoint(UBlueprint* Blueprint, const FMovieSceneDirectorBlueprintEndpointDefinition& EndpointDefinition);` — Create a new function endpoint for the specified sequence. @param Blueprint       (Required, non-null) The blueprint within which to create the new custom event @param EndpointDefinition  The end point definition @return A valid pointer to the blueprint node for the endpoint
- L210 _public prototype_ `static FMovieSceneDirectorBlueprintEntrypointResult GenerateEntryPoint(const FMovieSceneDirectorBlueprintEndpointCall& EndpointCall, FKismetCompilerContext* Compiler);` — Main generation function for creating the necessary function graph for calling an event endpoint with the parameters specified in the entry point payload @param EntryPoint             (Required, non-null) The event entry point definition to generate a function graph for @param Compiler               (Required, non-null) The kismet compiler context for generation @param Endpoint               (Required, non-null) The endpoint node that the event is bound to
- L219 _public prototype_ `static UEdGraphPin* FindCallTargetPin(UK2Node* InEndpoint, UClass* CallTargetClass);` — Attempt to locate an output pin on the specified endpoint node that matches the specified pin class @param InEndpoint             (Required, non-null) The endpoint node to search on @param BoundObjectPinClass    (Required, non-null) The class of the object pin to locate @return An output pin that is of type PC_Object with the specified class as its PinSubCategoryObject, or nullptr if one was not found
- L223 _private prototype_ `static UEdGraph* FindOrCreateEventGraph(UBlueprint* Blueprint, const FString& GraphName);`
- L225 _private prototype_ `static bool GenerateEntryPointRawActorParameter( FKismetCompilerContext* Compiler, UEdGraph* Graph, UEdGraphNode* Endpoint, UK2Node* OriginNode, UEdGraphPin* DestPin, const FMovieSceneDirectorBlueprintVariableValue& PayloadValue);`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API MOVIESCENETOOLS_API`
- L125 _delegate_ `DECLARE_DELEGATE_OneParam(FMovieSceneCustomizeDirectorBlueprintEndpointCallDelegate, const FMovieSceneCustomizeDirectorBlueprintEndpointCallParams&);`
- L125 _prototype_ `DECLARE_DELEGATE_OneParam(FMovieSceneCustomizeDirectorBlueprintEndpointCallDelegate, const FMovieSceneCustomizeDirectorBlueprintEndpointCallParams&);`

### `Source/Editor/MovieSceneTools/Public/MovieSceneDynamicBindingCustomization.h` (Public)


#### class `FMovieSceneDynamicBindingCustomization`  
`class FMovieSceneDynamicBindingCustomization : public FMovieSceneDirectorBlueprintEndpointCustomization`  
_L26-61_
- inherits: `FMovieSceneDirectorBlueprintEndpointCustomization`
- desc: Customization for dynamic spawn/possession endpoint picker.
- L30 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L31 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance(UMovieScene* InMovieScene, FGuid InObjectBinding, int32 InBindingIndex=0);`
- L33 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L37 _protected prototype_ `virtual void GetPayloadVariables(UObject* EditObject, void* RawData, FPayloadVariableMap& OutPayloadVariables) const override;`
- L38 _protected prototype_ `virtual bool SetPayloadVariable(UObject* EditObject, void* RawData, FName FieldName, const FMovieSceneDirectorBlueprintVariableValue& NewVariableValue) override;`
- L39 _protected prototype_ `virtual UK2Node* FindEndpoint(UMovieSceneSequence* Sequence, UBlueprint* Blueprint, UObject* EditObject, void* RawData) const override;`
- L40 _protected prototype_ `virtual void GetWellKnownParameterPinNames(UObject* EditObject, void* RawData, TArray<FName>& OutWellKnownParameters) const override;`
- L41 _protected prototype_ `virtual void GetWellKnownParameterCandidates(UK2Node* Endpoint, TArray<FWellKnownParameterCandidates>& OutCandidates) const override;`
- L42 _protected prototype_ `virtual bool SetWellKnownParameterPinName(UObject* EditObject, void* RawData, int32 ParameterIndex, FName BoundPinName) override;`
- L43 _protected prototype_ `virtual FMovieSceneDirectorBlueprintEndpointDefinition GenerateEndpointDefinition(UMovieSceneSequence* Sequence) override;`
- L44 _protected prototype_ `virtual void OnCreateEndpoint(UMovieSceneSequence* Sequence, UBlueprint* Blueprint, const TArray<UObject*> EditObjects, const TArray<void*> RawData, const FMovieSceneDirectorBlueprintEndpointDefinition& EndpointDefinition, UK2Node* NewEndpoint) override;`
- L45 _protected prototype_ `virtual void OnSetEndpoint(UMovieSceneSequence* Sequence, UBlueprint* Blueprint, const TArray<UObject*> EditObjects, const TArray<void*> RawData, const FMovieSceneDirectorBlueprintEndpointDefinition& EndpointDefinition, UK2Node* NewEndpoint) override;`
- L46 _protected prototype_ `virtual void GetEditObjects(TArray<UObject*>& OutObjects) const override;`
- L47 _protected prototype_ `virtual void OnCollectQuickBindActions(UBlueprint* Blueprint, FBlueprintActionMenuBuilder& MenuBuilder) override;`
- L51 _private prototype_ `void SetEndpointImpl(UMovieScene* MovieScene, FMovieSceneDynamicBinding* DynamicBinding, UBlueprint* Blueprint, UK2Node* NewEndpoint);`
- L52 _private prototype_ `void EnsureBlueprintExtensionCreated(UMovieScene* MovieScene, UBlueprint* Blueprint);`
- L54 _private prototype_ `void CollectResolverLibraryBindActions(UBlueprint* Blueprint, FBlueprintActionMenuBuilder& MenuBuilder, bool bIsRebinding);`
- L58 _private member_ `UMovieScene* EditedMovieScene;`
- L59 _private member_ `FGuid ObjectBinding;`
- L60 _private member_ `int32 BindingIndex = 0;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MOVIESCENETOOLS_API`

### `Source/Editor/MovieSceneTools/Public/MovieSceneDynamicBindingUtils.h` (Public)


#### struct `FMovieSceneDynamicBindingUtils`  
`struct FMovieSceneDynamicBindingUtils`  
_L23-58_
- desc: A utility class for managing dynamic binding endpoints.
- L25 _public typedef_ `using FSharedPlaybackState = UE::MovieScene::FSharedPlaybackState;`
- L30 _public prototype_ `static void SetEndpoint(UMovieScene* MovieScene, FMovieSceneDynamicBinding* DynamicBinding, UK2Node* NewEndpoint);` — Set an endpoint on the given dynamic binding.
- L35 _public prototype_ `static void EnsureBlueprintExtensionCreated(UMovieSceneSequence* MovieSceneSequence, UBlueprint* Blueprint);` — Ensures that the dynamic binding blueprint extension has been added to the given sequence's director blueprint.
- L41 _public function_ `template<typename Callback> static void IterateDynamicBindings(UMovieScene* InMovieScene, Callback&& InCallback)` — Utility function for iterating all dynamic bindings in a sequence.
- L51 _public function_ `static void GatherDynamicBindings(UMovieScene* InMovieScene, TArray<FMovieSceneDynamicBinding*>& OutDynamicBindings)` — Utility function for gathering all dynamic bindings in a sequence into a container.

#### class `UMovieSceneDynamicBindingEndpointUtil`  
`class UMovieSceneDynamicBindingEndpointUtil : public UObject`  
_L64-70_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: Dummy class, used for easily getting a valid UFunction that helps prepare blueprint function graphs.
- L69 _private function_ `FMovieSceneDynamicBindingResolveResult SampleResolveBinding()` — `UFUNCTION()`

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API MOVIESCENETOOLS_API`
- L54 _function_ `` (scope `FMovieSceneDynamicBindingUtils::GatherDynamicBindings`)

### `Source/Editor/MovieSceneTools/Public/MovieSceneEventCustomization.h` (Public)


#### class `FMovieSceneEventCustomization`  
`class FMovieSceneEventCustomization : public FMovieSceneDirectorBlueprintEndpointCustomization`  
_L16-39_
- inherits: `FMovieSceneDirectorBlueprintEndpointCustomization`
- desc: Customization for FMovieSceneEvent structs. Will deduce the event's section either from the outer objects on the details customization, or use the one provided on construction (for instanced property type customizations)
- L19 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L20 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance(UMovieSceneSection* InSection);`
- L24 _protected prototype_ `virtual void GetPayloadVariables(UObject* EditObject, void* RawData, FPayloadVariableMap& OutPayloadVariables) const override;`
- L25 _protected prototype_ `virtual bool SetPayloadVariable(UObject* EditObject, void* RawData, FName FieldName, const FMovieSceneDirectorBlueprintVariableValue& NewValue) override;`
- L26 _protected prototype_ `virtual UK2Node* FindEndpoint(UMovieSceneSequence* Sequence, UBlueprint* Blueprint, UObject* EditObject, void* RawData) const override;`
- L27 _protected prototype_ `virtual void GetWellKnownParameterPinNames(UObject* EditObject, void* RawData, TArray<FName>& OutWellKnownParameters) const override;`
- L28 _protected prototype_ `virtual void GetWellKnownParameterCandidates(UK2Node* Endpoint, TArray<FWellKnownParameterCandidates>& OutCandidates) const override;`
- L29 _protected prototype_ `virtual bool SetWellKnownParameterPinName(UObject* EditObject, void* RawData, int32 ParameterIndex, FName BoundPinName) override;`
- L30 _protected prototype_ `virtual FMovieSceneDirectorBlueprintEndpointDefinition GenerateEndpointDefinition(UMovieSceneSequence* Sequence) override;`
- L31 _protected prototype_ `virtual void OnCreateEndpoint(UMovieSceneSequence* Sequence, UBlueprint* Blueprint, const TArray<UObject*> EditObjects, const TArray<void*> RawData, const FMovieSceneDirectorBlueprintEndpointDefinition& EndpointDefinition, UK2Node* NewEndpoint) override;`
- L32 _protected prototype_ `virtual void OnSetEndpoint(UMovieSceneSequence* Sequence, UBlueprint* Blueprint, const TArray<UObject*> EditObjects, const TArray<void*> RawData, const FMovieSceneDirectorBlueprintEndpointDefinition& EndpointDefinition, UK2Node* NewEndpoint) override;`
- L33 _protected prototype_ `virtual void GetEditObjects(TArray<UObject*>& OutObjects) const override;`
- L38 _private member_ `TWeakObjectPtr<UMovieSceneSection> WeakExternalSection;` — Externally supplied section that the event(s) we're reflecting reside within

### `Source/Editor/MovieSceneTools/Public/MovieSceneEventUtils.h` (Public)


#### struct `FMovieSceneEventUtils`  
`struct FMovieSceneEventUtils`  
_L33-116_
- desc: Static utility library for dealing with movie-scene events at edit/cook-time
- L38 _public prototype_ `static FMovieSceneDirectorBlueprintEndpointDefinition GenerateEventDefinition(UMovieSceneTrack* Track);` — Generate event endpoint definition for the given track
- L43 _public prototype_ `static FMovieSceneDirectorBlueprintEndpointDefinition GenerateEventDefinition(UMovieScene* MovieScene, const FGuid& ObjectBindingID);` — Generate event endpoint definition for the given object binding
- L54 _public prototype_ `static UK2Node_CustomEvent* BindNewUserFacingEvent(FMovieSceneEvent* EntryPoint, UMovieSceneEventSectionBase* EventSection, UBlueprint* Blueprint);` — As with CreateUserFacingEvent, but also binds the section to a UBlueprintExtension which ensures that it will hook into the compilation process to generate its entry point function graph @param EntryPoint      (Required, non-null) The event entry point definition @param EventSection    (Required, non-null) The event section that owns the specified entry point @param Blueprint       (Required, non-null) The blueprint within which to create the new custom event @return A valid pointer to the blueprint node for the event endpoint
- L64 _public prototype_ `static UK2Node_FunctionEntry* GenerateEntryPoint(FMovieSceneEvent* EntryPoint, FKismetCompilerContext* Compiler, UEdGraphNode* Endpoint);` — Main generation function for creating the necessary function graph for calling an event endpoint with the parameters specified in the entry point payload @param EventSection           (Required, non-null) The event section that owns the event @param EntryPoint             (Required, non-null) The event entry point definition to generate a function graph for @param Compiler               (Required, non-null) The kismet compiler context for generation @param Endpoint               (Required, non-null) The endpoint node that the event is bound to
- L72 _public prototype_ `static void BindEventSectionToBlueprint(UMovieSceneEventSectionBase* EventSection, UBlueprint* DirectorBP);` — Create the necessary mapping between a director Blueprint and and event section in order for the event section to be compiled correctly. @param EventSection           (Required, non-null) The event section to bind to the director BP @param DirectorBP             (Required, non-null) The owning blueprint that will compile the event section's entry points
- L80 _public prototype_ `static void RemoveEndpointsForEventSection(UMovieSceneEventSectionBase* EventSection, UBlueprint* DirectorBP);` — Remove all event end points for the given event section @param EventSection           (Required, non-null) The event section to remove event endpoints from @param DirectorBP             (Required, non-null) The owning blueprint from which to remove the event section's entry points
- L87 _public prototype_ `static void ClearInvalidEndpointsForEventSection(UMovieSceneEventSectionBase* EventSection);` — Clear invalid endpoints (end points to that point to a blueprint in a different movie scene, possibly from copy/paste) @param EventSection           (Required, non-null) The event section to search for invalid event endpoints from
- L95 _public prototype_ `static void RemoveUnusedCustomEvents(const TArray<TWeakObjectPtr<UMovieSceneEventSectionBase>>& EventSections, UBlueprint* DirectorBP);` — Remove unused custom events (that don't have corresponding event end points in the given event sections) @param EventSections          (Required, non-null) The event sections to search for event endpoints from @param DirectorBP             (Required, non-null) The owning blueprint from which to remove the event section's entry points
- L105 _public prototype_ `static UK2Node* FindEndpoint(FMovieSceneEvent* EntryPoint, UMovieSceneEventSectionBase* EventSection, UBlueprint* OwnerBlueprint);` — Attempt to locate the blueprint node that relates to an event's end-point. @param EntryPoint             (Required, non-null) The event entry point definition to look up @param EventSection           (Required, non-null) The event section that owns the event @param OwnerBlueprint         (Required, non-null) The blueprint to search within @return The K2Node that relates to the specified event's end point, or nullptr if one was not found
- L115 _public prototype_ `static void SetEndpoint(FMovieSceneEvent* EntryPoint, UMovieSceneEventSectionBase* EventSection, UK2Node* InNewEndpoint, UEdGraphPin* BoundObjectPin);` — Set the specified EntryPoint to be bound to a new K2 node @param EntryPoint             (Required, non-null) The event entry point definition to assign to @param EventSection           (Required, non-null) The event section that owns the event entry point definition @param InNewEndpoint          (Optional) The new endpoint node to call from the event @param BoundObjectPin         (Optional) The pin that should receive the bound object when invoking the event

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MOVIESCENETOOLS_API`

### `Source/Editor/MovieSceneTools/Public/MovieSceneExportMetadata.h` (Public)


#### struct `FMovieSceneExportMetadataClip`  
`struct FMovieSceneExportMetadataClip`  
_L8-24_
- L10 _public function_ `FMovieSceneExportMetadataClip() : StartFrame(INT32_MAX) , EndFrame(INT32_MIN) , bHasAlpha(false)`
- L16 _public function_ `bool IsValid() const`
- L17 _public function_ `int32 GetDuration() const`
- L19 _public member_ `int32 StartFrame;`
- L20 _public member_ `int32 EndFrame;`
- L21 _public member_ `bool bHasAlpha;`
- L23 _public member_ `FString FileName;`

#### struct `FMovieSceneExportMetadataShot`  
`struct FMovieSceneExportMetadataShot`  
_L26-34_
- L28 _public member_ `TWeakObjectPtr<UMovieSceneCinematicShotSection> MovieSceneShotSection;`
- L29 _public member_ `int32 HandleFrames;`
- L33 _public member_ `TMap< FString, TMap<FString, FMovieSceneExportMetadataClip> > Clips;` — All of the clips for this shot, stored by ClipName Multiple formats may be exported, so each ClipName has a list metadata stored by extension

#### struct `FMovieSceneExportMetadata`  
`struct FMovieSceneExportMetadata`  
_L36-39_
- L38 _public member_ `TArray<FMovieSceneExportMetadataShot> Shots;`

### `Source/Editor/MovieSceneTools/Public/MovieSceneObjectBindingIDCustomization.h` (Public)


#### class `FMovieSceneObjectBindingIDCustomization`  
`class FMovieSceneObjectBindingIDCustomization : public IPropertyTypeCustomization , FMovieSceneObjectBindingIDPicker`  
_L32-65_
- inherits: `IPropertyTypeCustomization,FMovieSceneObjectBindingIDPicker`
- L38 _public function_ `FMovieSceneObjectBindingIDCustomization()`
- L41 _public function_ `FMovieSceneObjectBindingIDCustomization(FMovieSceneSequenceID InLocalSequenceID, TWeakPtr<ISequencer> InSequencer) : FMovieSceneObjectBindingIDPicker(InLocalSequenceID, InSequencer)`
- L45 _public prototype_ `static void BindTo(TSharedRef<ISequencer> InSequencer);`
- L47 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L48 _public function_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override`
- L52 _private prototype_ `virtual UMovieSceneSequence* GetSequence() const override;`
- L54 _private prototype_ `virtual void SetCurrentValue(const FMovieSceneObjectBindingID& InBindingId) override;`
- L56 _private prototype_ `virtual FMovieSceneObjectBindingID GetCurrentValue() const override;`
- L58 _private prototype_ `virtual bool HasMultipleValues() const override;`
- L60 _private prototype_ `FReply OnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent);`
- L62 _private prototype_ `void OnResetToDefault();`
- L64 _private member_ `TSharedPtr<IPropertyHandle> StructProperty;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MOVIESCENETOOLS_API`
- L22 _namespace_ `namespace UE`
- L24 _namespace_ `namespace MovieScene` (scope `UE`)

### `Source/Editor/MovieSceneTools/Public/MovieSceneObjectBindingIDPicker.h` (Public)


#### class `FMovieSceneObjectBindingIDPicker`  
`class FMovieSceneObjectBindingIDPicker`  
_L39-171_
- desc: Helper class that is used to pick object bindings for movie scene data
- L44 _public function_ `FMovieSceneObjectBindingIDPicker() : bIsCurrentItemSpawnable(false)` — Default constructor used in contexts external to the sequencer interface. Always generates FMovieSceneObjectBindingIDs from the root of the sequence
- L52 _public function_ `FMovieSceneObjectBindingIDPicker(FMovieSceneSequenceID InLocalSequenceID, TWeakPtr<ISequencer> InSequencer) : WeakSequencer(InSequencer) , LocalSequenceID(InLocalSequenceID) , bIsCurrentItemSpawnable(false)` — Constructor used from within the sequencer interface to generate IDs from the currently focused sequence if possible (else from the root sequence). This ensures that the bindings will resolve correctly in isolation only the the focused sequence is being used, or from the root sequence.
- L62 _public prototype_ `bool IsEmpty() const;` — Check whether this picker actually has anything to pick
- L65 _protected prototype_ `virtual ~FMovieSceneObjectBindingIDPicker() = default;`
- L68 _protected prototype_ `virtual UMovieSceneSequence* GetSequence() const = 0;` — Get the sequence to look up object bindings within. Only used when no sequencer is available.
- L71 _protected prototype_ `virtual void SetCurrentValue(const FMovieSceneObjectBindingID& InBindingId) = 0;` — Set the current binding ID
- L74 _protected prototype_ `virtual FMovieSceneObjectBindingID GetCurrentValue() const = 0;` — Get the current binding ID
- L77 _protected function_ `virtual bool HasMultipleValues() const` — Whether there are multiple values
- L80 _protected prototype_ `virtual bool IsNodeAllowed(const TSharedPtr<FSequenceBindingNode>& Node) const;` — Checks if node is allowed by this binding
- L85 _protected prototype_ `void Initialize();` — Initialize this class - rebuilds sequence hierarchy data and available IDs from the source sequence
- L88 _protected prototype_ `FText GetCurrentText() const;` — Access the text that relates to the currently selected binding ID
- L91 _protected prototype_ `FText GetToolTipText() const;` — Access the tooltip text that relates to the currently selected binding ID
- L94 _protected prototype_ `FSlateIcon GetCurrentIcon() const;` — Get the icon that represents the currently assigned binding
- L95 _protected prototype_ `const FSlateBrush* GetCurrentIconBrush() const;`
- L98 _protected prototype_ `EVisibility GetSpawnableIconOverlayVisibility() const;` — Get the visibility for the spawnable icon overlap
- L101 _protected prototype_ `void SetBindingId(UE::MovieScene::FFixedObjectBindingID InBindingId);` — Assign a new binding ID in response to user-input
- L104 _protected prototype_ `TSharedRef<SWidget> GetPickerMenu();` — Build menu content that allows the user to choose a binding from inside the source sequence
- L107 _protected prototype_ `void GetPickerMenu(FMenuBuilder& MenuBuilder);` — Build menu content that allows the user to choose a binding from inside the source sequence
- L110 _protected prototype_ `TSharedRef<SWidget> GetCurrentItemWidget(TSharedRef<STextBlock> TextContent);` — Get a widget that represents the currently chosen item
- L113 _protected prototype_ `TSharedRef<SWidget> GetWarningWidget();` — Get a widget that represents a warning/fixup button for this binding
- L116 _protected member_ `TWeakPtr<ISequencer> WeakSequencer;` — Optional sequencer ptr
- L119 _protected member_ `FMovieSceneSequenceID LocalSequenceID;` — The ID of the sequence to generate IDs relative to
- L122 _protected prototype_ `void UpdateCachedData();` — Update the cached text, tooltip and icon
- L127 _private prototype_ `UE::MovieScene::FFixedObjectBindingID GetCurrentValueAsFixed() const;` — Get the currently set binding ID as a fixed binding ID from the root sequence
- L130 _private prototype_ `void SetCurrentValueFromFixed(UE::MovieScene::FFixedObjectBindingID InValue);` — Set the binding ID
- L133 _private prototype_ `void OnGetMenuContent(FMenuBuilder& MenuBuilder, TSharedPtr<FSequenceBindingNode> Node);` — Called when the combo box has been clicked to populate its menu content
- L136 _private prototype_ `EVisibility GetFixedWarningVisibility() const;` — Get the visibility for the warning/fixup button
- L139 _private prototype_ `FReply AttemptBindingFixup();` — Get the visibility for the warning/fixup button
- L142 _private prototype_ `bool IsClassAllowed(const TSharedPtr<FSequenceBindingNode>& Node) const;` — Checks if a class is allowed by this binding
- L145 _private member_ `FText CurrentText, ToolTipText;` — Cached current text and tooltips
- L145 _private member_ `FText CurrentText, ToolTipText;` — Cached current text and tooltips
- L148 _private member_ `FSlateIcon CurrentIcon;` — Cached current icon
- L151 _private member_ `bool bIsCurrentItemSpawnable;` — Cached value indicating whether the current item is a spawnable
- L154 _private member_ `TSharedPtr<FSequenceBindingTree> DataTree;` — Data tree that stores all the available bindings for the current sequence, and their identifiers
- L157 _private member_ `TWeakPtr<SWidget> DismissWidget;` — Weak ptr to a widget used to dismiss menus to
- L161 _protected member_ `const UClass* ClassPropertyMetaClass = UObject::StaticClass();` — The meta class for the property that classes must be a child-of.
- L164 _protected member_ `const UClass* InterfaceThatMustBeImplemented = nullptr;` — The interface that must be implemented.
- L167 _protected member_ `TArray<const UClass*> AllowedClassFilters;` — Classes that can be picked
- L170 _protected member_ `TArray<const UClass*> DisallowedClassFilters;` — Classes that can't be picked

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MOVIESCENETOOLS_API`
- L25 _namespace_ `namespace UE`
- L27 _namespace_ `namespace MovieScene` (scope `UE`)

### `Source/Editor/MovieSceneTools/Public/MovieSceneSectionDetailsCustomization.h` (Public)


#### class `FMovieSceneSectionDetailsCustomization`  
`class FMovieSceneSectionDetailsCustomization : public IDetailCustomization`  
_L19-101_
- inherits: `IDetailCustomization`
- desc: Customizes FMovieSceneSection to expose the section bounds to the UI and allow changing their bounded states.
- L22 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance(TSharedPtr<INumericTypeInterface<double>> InNumericTypeInterface, TWeakObjectPtr<UMovieScene> InParentMovieScene)`
- L27 _public function_ `FMovieSceneSectionDetailsCustomization(TSharedPtr<INumericTypeInterface<double>> InNumericTypeInterface, TWeakObjectPtr<UMovieScene> InParentMovieScene)`
- L34 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder);` — IDetailCustomization interface
- L46 _private prototype_ `ERangeBoundValueType GetRangeStartValue(FFrameNumber& OutValue) const;` — Get the range start value
- L49 _private prototype_ `FText OnGetRangeStartText() const;` — Convert the range start into an FText for display
- L51 _private prototype_ `FText OnGetRangeStartToolTipText() const;` — Convert the range start into an FText for tooltip display
- L53 _private prototype_ `void OnRangeStartTextCommitted(const FText& InText, ETextCommit::Type CommitInfo);` — Convert the text into a new range start
- L55 _private prototype_ `bool IsRangeStartTextboxEnabled() const;` — Should the textbox be editable? False if we have an infinite range.
- L58 _private prototype_ `ECheckBoxState GetRangeStartBoundedState() const;` — Determines if the range is Open, Closed, or Undetermined which can happen in the case of multi-select.
- L60 _private prototype_ `void SetRangeStartBounded(bool InbIsBounded);` — Sets the range to have a fixed bound or convert to an open bound.
- L64 _private prototype_ `FText GetRangeStartButtonIcon() const;` — Get the FText representing the appropriate Unicode icon for the toggle button.
- L66 _private prototype_ `FReply ToggleRangeStartBounded();` — Called by the UI when the button is pressed to toggle the current state.
- L70 _private prototype_ `ERangeBoundValueType GetRangeEndValue(FFrameNumber& OutValue) const;` — Get the range end value
- L73 _private prototype_ `FText OnGetRangeEndText() const;` — Convert the range end into an FText for display
- L75 _private prototype_ `FText OnGetRangeEndToolTipText() const;` — Convert the range end into an FText for tooltip display
- L77 _private prototype_ `void OnRangeEndTextCommitted(const FText& InText, ETextCommit::Type CommitInfo);` — Convert the text into a new range start
- L79 _private prototype_ `bool IsRangeEndTextboxEnabled() const;` — Should the textbox be editable? False if we have an infinite range.
- L82 _private prototype_ `ECheckBoxState GetRangeEndBoundedState() const;` — Determines if the range is Open, Closed, or Undetermined which can happen in the case of multi-select.
- L84 _private prototype_ `void SetRangeEndBounded(bool InbIsBounded);` — Sets the range to have a fixed bound or convert to an open bound.
- L88 _private prototype_ `FText GetRangeEndButtonIcon() const;` — Get the FText representing the appropriate Unicode icon for the toggle button.
- L90 _private prototype_ `FReply ToggleRangeEndBounded();` — Called by the UI when the button is pressed to toggle the current state.
- L94 _private member_ `TSharedPtr<INumericTypeInterface<double>> NumericTypeInterface;` — The Numeric Type interface used to convert between display formats and internal tick resolution.
- L97 _private member_ `TSharedPtr<IPropertyHandle> MovieSceneSectionPropertyHandle;` — Store the property handle to the FrameNumber field so we can get/set the value on the object via text box callbacks.
- L100 _private member_ `TWeakObjectPtr<UMovieScene> ParentMovieScene;` — The movie scene that owns the section we're customizing. Used to find out the overall bounds for changing a section bounds from infinite -> closed.

#### enum `FMovieSceneSectionDetailsCustomization::ERangeBoundValueType`  
`enum class ERangeBoundValueType`  
_L37-42_
- L39 _public enumerator_ `Finite`
- L40 _public enumerator_ `Infinite`
- L41 _public enumerator_ `MultipleValues`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MOVIESCENETOOLS_API`

### `Source/Editor/MovieSceneTools/Public/MovieSceneToolHelpers.h` (Public)


#### struct `FFBXInOutParameters`  
`struct FFBXInOutParameters`  
_L63-69_
- L65 _public member_ `bool bConvertSceneBackup;`
- L66 _public member_ `bool bConvertSceneUnitBackup;`
- L67 _public member_ `bool bForceFrontXAxisBackup;`
- L68 _public member_ `float ImportUniformScaleBackup;`

#### struct `FAnimExportSequenceParameters`  
`struct FAnimExportSequenceParameters`  
_L71-79_
- L73 _public prototype_ `FAnimExportSequenceParameters() = default;`
- L74 _public member_ `UMovieSceneSequence* MovieSceneSequence;`
- L75 _public member_ `UMovieSceneSequence* RootMovieSceneSequence;`
- L76 _public member_ `IMovieScenePlayer* Player;`
- L77 _public member_ `FMovieSceneSequenceTransform RootToLocalTransform;`
- L78 _public member_ `bool bForceUseOfMovieScenePlaybackRange = false;`

#### struct `FSkelMeshRecorderState`  
`struct FSkelMeshRecorderState`  
_L89-110_
- desc: Skel Mesh Recorder to set up and restore various parameters on the skelmesh
- L92 _public function_ `FSkelMeshRecorderState()`
- L93 _public prototype_ `~FSkelMeshRecorderState() = default;`
- L95 _public prototype_ `void Init(USkeletalMeshComponent* InComponent);`
- L96 _public prototype_ `void FinishRecording();`
- L100 _public member_ `TWeakObjectPtr<USkeletalMeshComponent> SkelComp;`
- L103 _public member_ `int CachedSkelCompForcedLodModel;` — Original ForcedLodModel setting on the SkelComp, so we can modify it and restore it when we are done.
- L106 _public member_ `EVisibilityBasedAnimTickOption CachedVisibilityBasedAnimTickOption;` — Used to store/restore update flag when recording
- L109 _public member_ `bool bCachedEnableUpdateRateOptimizations;` — Used to store/restore URO when recording

#### enum `FChannelMergeAlgorithm`  
`enum class FChannelMergeAlgorithm : uint8`  
_L112-120_
- L115 _public enumerator_ `Average` — Average values together
- L117 _public enumerator_ `Add` — Add values together
- L119 _public enumerator_ `Override` — Override values together

#### class `MovieSceneToolHelpers`  
`class MovieSceneToolHelpers`  
_L122-1283_
- L133 _public prototype_ `static void TrimSection(const TSet<UMovieSceneSection*>& Sections, FQualifiedFrameTime Time, bool bTrimLeft, bool bDeleteKeys);` — Trim section at the given time @param Sections The sections to trim @param Time	The time at which to trim @param bTrimLeft Trim left or trim right @param bDeleteKeys Delete keys outside the split ranges
- L134 _public prototype_ `static bool CanTrimSectionLeft(const TSet<UMovieSceneSection*>& Sections, FQualifiedFrameTime Time);`
- L135 _public prototype_ `static bool CanTrimSectionRight(const TSet<UMovieSceneSection*>& Sections, FQualifiedFrameTime Time);`
- L146 _public prototype_ `static void TrimOrExtendSection(UMovieSceneTrack* Track, TOptional<int32> RowIndex, FQualifiedFrameTime Time, bool bTrimOrExtendLeft, bool bDeleteKeys);` — Trim or extend section at the given time @param Track The track that contains the sections to trim @param RowIndex Optional row index to trim, otherwise trims sections with all row indices @param Time	The time at which to trim @param bTrimOrExtendleft Trim or extend left or right @param bDeleteKeys Delete keys outside the split ranges
- L155 _public prototype_ `static void SplitSection(const TSet<UMovieSceneSection*>& Sections, FQualifiedFrameTime Time, bool bDeleteKeys);` — Splits sections at the given time @param Sections The sections to split @param Time	The time at which to split @param bDeleteKeys Delete keys outside the split ranges
- L156 _public prototype_ `static bool CanSplitSection(const TSet<UMovieSceneSection*>& Sections, FQualifiedFrameTime Time);`
- L158 _public prototype_ `static FTransform GetTransformOriginForFocusedSequence(TSharedPtr<ISequencer> InSequencer);`
- L171 _public prototype_ `static bool ParseShotName(const FString& ShotName, FString& ShotPrefix, uint32& ShotNumber, uint32& TakeNumber, uint32& ShotNumberDigits, uint32& TakeNumberDigits);` — Parse a shot name into its components. @param ShotName The shot name to parse @param ShotPrefix The parsed shot prefix @param ShotNumber The parsed shot number @param TakeNumber The parsed take number @param ShotNumberDigits The number of digits to pad for the shot number @param TakeNumberDigits The number of digits to pad for the take number @return Whether the shot name was parsed successfully
- L183 _public prototype_ `static FString ComposeShotName(const FString& ShotPrefix, uint32 ShotNumber, uint32 TakeNumber, uint32 ShotNumberDigits, uint32 TakeNumberDigits);` — Compose a shot name given its components. @param ShotPrefix The shot prefix to use @param ShotNumber The shot number to use @param TakeNumber The take number to use @param ShotNumberDigits The number of digits to pad for the shot number @param TakeNumberDigits The number of digits to pad for the take number @return The composed shot name
- L193 _public prototype_ `static FString GenerateNewSubsequencePath(UMovieScene* SequenceMovieScene, const FString& SubsequenceDirectory, FString& NewShotName);` — Generate a new subsequence package @param SequenceMovieScene The sequence movie scene for the new subsequence @param SubsequenceDirectory The directory for the new subsequence @param NewShotName The new shot name @return The new subsequence path
- L196 _public prototype_ `static FString GenerateNewShotPath(UMovieScene* SequenceMovieScene, FString& NewShotName);` — `UE_DEPRECATED(5.3, "GenerateNewShotPath has been deprecated in favor of GenerateNewSubsequencePath that takes a given directory")`
- L206 _public prototype_ `static FString GenerateNewSubsequenceName(const TArray<UMovieSceneSection*>& AllSections, const FString& SubsequencePrefix, FFrameNumber Time);` — Generate a new shot name @param AllSections All the sections in the given shot track @param Time The time to generate the new shot name at @return The new shot name
- L209 _public prototype_ `static FString GenerateNewShotName(const TArray<UMovieSceneSection*>& AllSections, FFrameNumber Time);` — `UE_DEPRECATED(5.3, "GenerateNewShotName has been deprecated in favor of GenerateNewSubsequenceName that takes a given prefix")`
- L220 _public prototype_ `static UMovieSceneSequence* CreateSequence(FString& NewSequenceName, FString& NewSequencePath, UMovieSceneSubSection* SectionToDuplicate = nullptr, TSubclassOf<UMovieSceneSequence> SequenceClass = nullptr);` — Create sequence @param NewSequenceName The new sequence name. @param NewSequencePath The new sequence path. @param SectionToDuplicate The section to duplicate. @param SequenceClass The class of sequence. Used only if SectionToDuplicate is not provided. @return The new subsequence.
- L229 _public prototype_ `static void GatherTakes(const UMovieSceneSection* Section, TArray<FAssetData>& AssetData, uint32& OutCurrentTakeNumber);` — Gather takes - level sequence assets that have the same shot prefix and shot number in the same asset path (directory) @param Section The section to gather takes from @param AssetData The gathered asset take data @param OutCurrentTakeNumber The current take number of the section
- L239 _public prototype_ `static bool GetTakeNumber(const UMovieSceneSection* Section, FAssetData AssetData, uint32& OutTakeNumber);` — Get the take number for the given asset @param Section The section to gather the take number from @param AssetData The take asset to search for @param OutTakeNumber The take number for the given asset @return Whether the take number was found
- L248 _public prototype_ `static bool SetTakeNumber(const UMovieSceneSection* Section, uint32 InTakeNumber);` — Set the take number for the given asset @param Section The section to set the take number on @param InTakeNumber The take number for the given asset @return Whether the take number could be set
- L258 _public prototype_ `static int32 FindAvailableRowIndex(UMovieSceneTrack* InTrack, UMovieSceneSection* InSection, const TArray<UMovieSceneSection*>& SectionsToDisregard = TArray<UMovieSceneSection*>());` — Get the next available row index for the section so that it doesn't overlap any other sections in time. @param InTrack The track to find the next available row on @param InSection The section @param SectionsToDisregard Disregard checking these sections @return The next available row index
- L268 _public prototype_ `static bool OverlapsSection(UMovieSceneTrack* InTrack, UMovieSceneSection* InSection, const TArray<UMovieSceneSection*>& SectionsToDisregard = TArray<UMovieSceneSection*>());` — Does this section overlap any other track section? @param InTrack The track to find sections on @param InSection The section @param SectionsToDisregard Disregard checking these sections @return Whether this section overlaps any other track section
- L278 _public prototype_ `static TSharedRef<SWidget> MakeEnumComboBox(const UEnum* Enum, TAttribute<int32> CurrentValue, SEnumComboBox::FOnEnumSelectionChanged OnSelectionChanged);` — Generate a combobox for editing enum values @param Enum The enum to make the combobox from @param CurrentValue The current value to display @param OnSelectionChanged Delegate fired when selection is changed @return The new widget
- L289 _public prototype_ `static bool ShowImportEDLDialog(UMovieScene* InMovieScene, FFrameRate InFrameRate, FString InOpenDirectory = TEXT(""));` — Show Import EDL Dialog @param InMovieScene The movie scene to import the edl into @param InFrameRate The frame rate to import the EDL at @param InOpenDirectory Optional directory path to open from. If none given, a dialog will pop up to prompt the user @return Whether the import was successful
- L301 _public prototype_ `static bool ShowExportEDLDialog(const UMovieScene* InMovieScene, FFrameRate InFrameRate, FString InSaveDirectory = TEXT(""), int32 InHandleFrames = 8, FString InMovieExtension = TEXT(".avi` — Show Export EDL Dialog @param InMovieScene The movie scene with the cinematic shot track and audio tracks to export @param InFrameRate The frame rate to export the EDL at @param InSaveDirectory Optional directory path to save to. If none given, a dialog will pop up to prompt the user @param InHandleFrames The number of handle frames to include for each shot. @param MovieExtension The movie extension for the shot filenames (ie. .avi, .mov, .mp4) @return Whether the export was successful
- L312 _public prototype_ `static bool MovieSceneTranslatorImport(FMovieSceneImporter* InImporter, UMovieScene* InMovieScene, FFrameRate InFrameRate, FString InOpenDirectory = TEXT(""));` — Import movie scene formats @param InImporter The movie scene importer. @param InMovieScene The movie scene to import the format into @param InFrameRate The frame rate to import the format at @param InOpenDirectory Optional directory path to open from. If none given, a dialog will pop up to prompt the user @return Whether the import was successful
- L324 _public prototype_ `static bool MovieSceneTranslatorExport(FMovieSceneExporter* InExporter, const UMovieScene* InMovieScene, const FMovieSceneCaptureSettings& Settings);` — Export movie scene formats @param InExporter The movie scene exporter. @param InMovieScene The movie scene with the cinematic shot track and audio tracks to export @param InFrameRate The frame rate to export the AAF at @param InSaveDirectory Optional directory path to save to. If none given, a dialog will pop up to prompt the user @param InHandleFrames The number of handle frames to include for each shot. @return Whether the export was successful
- L333 _public prototype_ `static void MovieSceneTranslatorLogMessages(FMovieSceneTranslator* InTranslator, TSharedRef<FMovieSceneTranslatorContext> InContext, bool bDisplayMessages);` — Log messages and display error message window for MovieScene translators @param InTranslator The movie scene importer or exporter. @param InContext The context used to gather error, warning or info messages during import or export. @param bDisplayMessages Whether to open the message log window after adding the message.
- L341 _public prototype_ `static void MovieSceneTranslatorLogOutput(FMovieSceneTranslator* InTranslator, TSharedRef<FMovieSceneTranslatorContext> InContext);` — Log error output for MovieScene translators @param InTranslator The movie scene importer or exporter. @param InContext The context used to gather error, warning or info messages during import or export.
- L355 _public prototype_ `static bool ExportFBX(UWorld* World, const FAnimExportSequenceParameters& AnimExportSequenceParameters, const TArray<FGuid>& Bindings, const TArray<UMovieSceneTrack*>& Tracks, INodeNameAdapter& NodeNameAdapter, FMovieSceneSequenceIDRef& Template, const FString& InFBXFileName);` — Export FBX @param World The world to export from @param AnimExportSequenceParameters The sequence parameters used for evaluation @param Bindings The sequencer binding map @param Tracks The tracks to export @param NodeNameAdaptor Adaptor to look up actor names. @param Template Movie scene sequence id. @param InFBXFileName the fbx file name. @return Whether the export was successful
- L358 _public prototype_ `static bool ExportFBX(UWorld* World, UMovieScene* MovieScene, IMovieScenePlayer* Player, const TArray<FGuid>& Bindings, const TArray<UMovieSceneTrack*>& Tracks, INodeNameAdapter& NodeNameAdapter, FMovieSceneSequenceIDRef& Template, const FString& InFBXFileName, FMovieSceneSequenceTransform& RootToLocalTransform);` — `UE_DEPRECATED(5.5, "ExportFBX taking movie scene has been deprecated in favor of a new function that takes current and root movie scene sequences")`
- L368 _public prototype_ `static bool ImportFBXWithDialog(UMovieSceneSequence* InSequence, ISequencer& InSequencer, const TMap<FGuid, FString>& InObjectBindingNameMap, TOptional<bool> bCreateCameras);` — Import FBX with dialog @param InMovieScene The movie scene to import the fbx into @param InObjectBindingNameMap The object binding to name map to map import fbx animation onto @param bCreateCameras Whether to allow creation of cameras if found in the fbx file. @return Whether the import was successful
- L378 _public prototype_ `static bool ReadyFBXForImport(const FString& ImportFilename, UMovieSceneUserImportFBXSettings* ImportFBXSettings, FFBXInOutParameters& OutFBXParams);` — Get FBX Ready for Import. This make sure the passed in file make be imported. After calling this call ImportReadiedFbx. It returns out some parameters that we forcably change so we reset them later. @param ImportFileName The filename to import into @param ImportFBXSettings FBX Import Settings to enforce. @param OutFBXParams Paremter to pass back to ImportReadiedFbx @return Whether the fbx file was ready and is ready to be import.
- L393 _public prototype_ `static bool ImportFBXIfReady(UWorld* World, UMovieSceneSequence* InSequence, IMovieScenePlayer* Player, FMovieSceneSequenceIDRef TemplateID, TMap<FGuid, FString>& ObjectBindingMap, UMovieSceneUserImportFBXSettings* ImportFBXSettings, const FFBXInOutParameters& InFBXParams, ISequencer* Sequencer = nullptr);`
- L409 _public prototype_ `static void ImportFBXCameraToExisting(UnFbx::FFbxImporter* FbxImporter, UMovieSceneSequence* InSequence, IMovieScenePlayer* Player, FMovieSceneSequenceIDRef TemplateID, TMap<FGuid, FString>& InObjectBindingMap, bool bMatchByNameOnly, bool bNotifySlate);`
- L422 _public prototype_ `static bool ImportFBXNode(FString NodeName, UnFbx::FFbxCurvesAPI& CurveAPI, UMovieSceneSequence* InSequence, IMovieScenePlayer* Player, FMovieSceneSequenceIDRef TemplateID, FGuid ObjectBinding, ISequencer* Sequencer = nullptr);` — Import FBX Node to existing actor/node @param NodeName Name of fbx node/actor @param CurvesApi Existing FBX curves coming in @param InMovieScene The movie scene to import the fbx into @param Player The player we are getting objects from. @param TemplateID Id of the sequence template ID. @param ObjectBinding Guid of the object we are importing onto. @return Whether the import was successful
- L430 _public prototype_ `static void LockCameraActorToViewport(const TSharedPtr<ISequencer>& Sequencer, ACameraActor* CameraActor);` — Lock the given camera actor to the viewport @param Sequencer The Sequencer to set the camera cut enabled for @param CameraActor The camera actor to lock
- L439 _public prototype_ `static void CreateCameraCutSectionForCamera(UMovieScene* MovieScene, FGuid CameraGuid, FFrameNumber FrameNumber);` — Create a new camera cut section for the given camera @param MovieScene MovieScene to add Camera. @param CameraGuid CameraGuid  Guid of the camera that was added. @param FrameNumber FrameNumber it's added at.
- L447 _public prototype_ `static void CopyCameraProperties(fbxsdk::FbxCamera* CameraNode, AActor* InCameraActor);` — Import FBX Camera to existing camera's @param CameraNode The Fbx camera @param InCameraActor UE actor
- L460 _public prototype_ `static bool ExportToAnimSequence(UAnimSequence* AnimSequence, UAnimSeqExportOption* ExportOptions, const FAnimExportSequenceParameters& AnimExportSequenceParameters, USkeletalMeshComponent* SkelMesh);` — Export the SkelMesh to an Anim Sequence for specified MovieScene and Player @param AnimSequence The sequence to save to. @param ExportOptions The options to use when saving. @param AnimExportSequenceParameters The Sequence parameters like the movie scene sequences, the player, template id, used for evaluation @param SkelMesh The Player to evaluatee. @return Whether or not it succeeds
- L464 _public prototype_ `static bool ExportToAnimSequence(UAnimSequence* AnimSequence, UAnimSeqExportOption* ExportOptions, UMovieScene* MovieScene, IMovieScenePlayer* Player, USkeletalMeshComponent* SkelMesh, FMovieSceneSequenceIDRef& Template, FMovieSceneSequenceTransform& RootToLocalTransform);` — `UE_DEPRECATED(5.5, "ExportToAnimSequence taking movie scene has been deprecated in favor of a new function that takes current and root movie scene sequences")`
- L485 _public prototype_ `static bool BakeToSkelMeshToCallbacks(const FAnimExportSequenceParameters& AnimExportSequenceParameters, USkeletalMeshComponent* SkelMesh, UAnimSeqExportOption* ExportOptions, FInitAnimationCB InitCallback, FStartAnimationCB StartCallback, FTickAnimationCB TickCallback, FEndAnimationCB EndCallback);`
- L489 _public prototype_ `static bool BakeToSkelMeshToCallbacks(UMovieScene* MovieScene, IMovieScenePlayer* Player, USkeletalMeshComponent* SkelMesh, FMovieSceneSequenceIDRef& Template, FMovieSceneSequenceTransform& RootToLocalTransform, UAnimSeqExportOption* ExportOptions, FInitAnimationCB InitCallback, FStartAnimationCB StartCallback, FTickAnimationCB TickCallback, FEndAnimationCB EndCallback);` — `UE_DEPRECATED(5.5, "BakeToSkelMeshToCallbacks taking movie scene has been deprecated in favor of a new function that takes current and root movie scene sequences")`
- L497 _public prototype_ `static bool HasHiddenMobility(const UClass* ObjectClass);` — @return Whether this object class has hidden mobility and can't be animated
- L505 _public prototype_ `static const FMovieSceneEvaluationTrack* GetEvaluationTrack(ISequencer *Sequencer, const FGuid& TrackSignature);` — Get the Active EvaluationTrack for a given track. Will do a recompile if the track isn't valid @param Sequencer The sequencer we are evaluating @aram Track The movie scene track whose evaluation counterpart we want @return Returns the evaluation track for the given movie scene track. May do a re-compile if needed.
- L517 _public prototype_ `static void GetLocationAtTime(const FMovieSceneEvaluationTrack* Track, UObject* Object, FFrameTime KeyTime, FVector& KeyPos, FRotator& KeyRot, const TSharedPtr<ISequencer>& Sequencer);` — Get the location at time for the specified transform evaluation track @param Track The sequencer we are evaluating @param Object The object that owns this track @param KeyTime the time to evaluate @param KeyPos The position at this time @param KeyRot The rotation at this time @param Sequencer The Sequence that owns this track
- L523 _public prototype_ `static void GetParents(TArray<const UObject*>& Parents, const UObject* InObject);` — Get the Parents (Scene/Actors) of this object. @param Parents Returned Parents @param InObject Object to find parents for
- L531 _public prototype_ `static FTransform GetRefFrameFromParents(const TSharedPtr<ISequencer>& Sequencer, const TArray<const UObject*>& Parents, FFrameTime KeyTime);` — Return Reference Frame from the passed in paretns @param Sequencer The Sequence that's driving these parents. @param Parents Parents in sequencer to evaluate to find reference transforms @param KeyTime Time to Evaluate At @return Returns Reference Transform.
- L540 _public prototype_ `static bool GetParentTM(FTransform& CurrentRefTM, const TSharedPtr<ISequencer>& Sequencer, UObject* ParentObject, FFrameTime KeyTime);` — Return Return ParentTm for current Parent Object @param CurrentRefTM Current Referemnce TM @param Sequencer The Sequence that's driving these parents. @param ParentObject The Parent @param KeyTime Time to Evaluate At @return Returns true if succesful in evaluating the parent in the sequencer and getting a transform.
- L545 _public prototype_ `static void GetCameras(fbxsdk::FbxNode* Parent, TArray<fbxsdk::FbxCamera*>& Cameras);` — Get the fbx cameras from the requested parent node
- L550 _public prototype_ `static FString GetCameraName(fbxsdk::FbxCamera* InCamera);` — Get the fbx camera name
- L555 _public prototype_ `static bool ImportFBXIntoControlRigChannelsWithDialog(const TSharedRef<ISequencer>& InSequencer, TArray<FRigControlFBXNodeAndChannels>* NodeAndChannels);` — Import FBX into Control Rig Channels With Dialog
- L560 _public prototype_ `static bool ExportFBXFromControlRigChannelsWithDialog(const TSharedRef<ISequencer>& InSequencer, UMovieSceneTrack* Track);` — Export FBX from Control Rig Channels With Dialog
- L565 _public prototype_ `static bool ImportFBXIntoControlRigChannels(UMovieScene* MovieScene, const FString& ImportFilename, UMovieSceneUserImportFBXControlRigSettings *ControlRigSettings, TArray<FRigControlFBXNodeAndChannels>* NodeAndChannels, const TArray<FName>& SelectedControlNames, FFrameRate FrameRate);` — Import FBX into Control Rig Channels
- L571 _public prototype_ `static bool ExportFBXFromControlRigChannels(const UMovieSceneSection* Section, const UMovieSceneUserExportFBXControlRigSettings* ExportFBXControlRigSettings, const TArray<FName>& SelectedControlNames, const FMovieSceneSequenceTransform& RootToLocalTransform);` — Export FBX from Control Rig Channels
- L579 _public prototype_ `static USkeletalMeshComponent* AcquireSkeletalMeshFromObject(UObject* BoundObject);` — Acquire first SkeletalMeshComponent from the Object @param BoundObject Object to get SkeletalMeshComponent from.If actor checks it's components, if component checks itself then child components. @return Returns the USkeletalMeshComponent if one is found
- L586 _public prototype_ `static void GetActorParents(const FActorForWorldTransforms& Actor, TArray<FActorForWorldTransforms>& OutParentActors);` — Get an actors and possible component parents. @param InActorAndComponent Actor and possible component to find parents for @param OutParentActors Returns an array of parents
- L595 _public prototype_ `static void GetActorParentsWithAttachments(ISequencer* Sequencer, const FActorForWorldTransforms& Actor, TArray<FActorForWorldTransforms>& OutParentActors);` — Get an actors and possible component parents using sequencer to test for attachments. @param Sequencer Sequencer to evaluate @param InActorAndComponent Actor and possible component to find parents for @param OutParentActors Returns an array of parents
- L605 _public prototype_ `static void GetActorsAndParentsKeyFrames(ISequencer* Sequencer, const FActorForWorldTransforms& Actor, const FFrameNumber& StartFrame, const FFrameNumber& EndFrame, TSortedMap<FFrameNumber, FFrameNumber>& OutFrameMap);` — Get an actors and it's parent key frames @param Sequencer Sequencer to evaluate @param Actor The actor and possible component and socket that we want to get the frame for @param StartFrame The first frame to start looking for keys @param EndFrame The last frame to stop looking for keys @param OutFrameMap Sorted map of the frame times found
- L615 _public prototype_ `static void GetActorWorldTransforms(ISequencer* Sequencer, const FActorForWorldTransforms& Actors, const TArray<FFrameNumber>& Frames, TArray<FTransform>& OutWorldTransforms);` — Get an actors word transforms at the specified times @param Sequencer Sequencer to evaluate @param Actors The actor and possible component and socket that we want to get the world transforms for. @param Frames The times we want to get the world transforms @param OutWorldTransforms The calculated world transforms, one for each specified frame.
- L623 _public prototype_ `static void SetOrAddKey(TMovieSceneChannelData<FMovieSceneFloatValue>& ChannelData, FFrameNumber Time, float Value, const EMovieSceneKeyInterpolation Interpolation = EMovieSceneKeyInterpolation::Auto);` — Set or add a key onto a float channel. @param ChannelData Channel to set or add @param Time Frame to add or set the value @param Value  Value to Set @param Interpolation Key type to set if added
- L631 _public prototype_ `static void SetOrAddKey(TMovieSceneChannelData<FMovieSceneDoubleValue>& ChannelData, FFrameNumber Time, double Value, const EMovieSceneKeyInterpolation Interpolation = EMovieSceneKeyInterpolation::Auto);` — Set or add a key onto a double channel. @param ChannelData Channel to set or add @param Time Frame to add or set the value @param Value  Value to Set @param Interpolation Key type to set if added
- L637 _public prototype_ `static void SetOrAddKey(TMovieSceneChannelData<FMovieSceneFloatValue>& Curve, FFrameNumber Time, const FMovieSceneFloatValue& Value);` — Set or add a key onto a float channel based on key value.
- L643 _public prototype_ `static void SetOrAddKey(TMovieSceneChannelData<FMovieSceneDoubleValue>& ChannelData, FFrameNumber Time, FMovieSceneDoubleValue Value);` — Set or add a key onto a double channel based on key value.
- L649 _public prototype_ `static void SetOrAddKey(TMovieSceneChannelData<FMovieSceneFloatValue>& Curve, FFrameNumber Time, float Value, float ArriveTangent, float LeaveTangent, ERichCurveInterpMode InterpMode, ERichCurveTangentMode TangentMode, FFrameRate FrameRate, ERichCurveTangentWeightMode WeightedMode = RCTWM_WeightedNone, float ArriveTangentWeight = 0.0f, float LeaveTangentWeight = 0.0f);` — Set or add a key onto a float channel based on rich curve data.
- L657 _public prototype_ `static void SetOrAddKey(TMovieSceneChannelData<FMovieSceneDoubleValue>& Curve, FFrameNumber Time, double Value, float ArriveTangent, float LeaveTangent, ERichCurveInterpMode InterpMode, ERichCurveTangentMode TangentMode, FFrameRate FrameRate, ERichCurveTangentWeightMode WeightedMode = RCTWM_WeightedNone, float ArriveTangentWeight = 0.0f, float LeaveTangentWeight = 0.0f);` — Set or add a key onto a double channel based on rich curve data.
- L671 _public prototype_ `static void GetActorWorldTransforms(IMovieScenePlayer* Player, UMovieSceneSequence* InSequence, FMovieSceneSequenceIDRef Template,const FActorForWorldTransforms& Actors, const TArray<FFrameNumber>& Frames, TArray<FTransform>& OutWorldTransforms);` — Get an actors world transforms at the specified times using a player @param Player Player to evaluate @param InSequence  Sequence to evaluate @param Template  Sequence ID of the template to play @param ActorForWorldTransforms The actor and possible component and socket that we want to get the world transforms for. @param Frames The times we want to get the world transforms @param OutWorldTransforms The calculated world transforms, one for each specified frame.
- L676 _public prototype_ `static bool IsValidAsset(UMovieSceneSequence* Sequence, const FAssetData& InAssetData);` — Return whether this asset is valid for the given sequence
- L686 _public prototype_ `static bool CollapseSection(TSharedPtr<ISequencer>& InSequencer, UMovieSceneTrack* InOwnerTrack, TArray<UMovieSceneSection*> InSections, const FBakingAnimationKeySettings& InSettings);` — Collapse all of the sections specified onto the first one @param InSequencer  Sequencer we are collpasing at @param InOwnerTrack  The track that should be owning the sections we are collapsing @param InSections The sections we are collapsing. Sections[0] will remain, te otheer ones will be deleted @param InSettings Baking settings ussed @return Return true if succeeds false if it doesn't
- L695 _public prototype_ `static void SplitSectionsByBlendType(EMovieSceneBlendType BlendType, const TArray<UMovieSceneSection*>& InSections, TArray<UMovieSceneSection*>& OutSections, TArray<UMovieSceneSection*>& OutBlendTypeSections);` — Split set of sections to one containing the BlendType the other not @param InSections The sections we are searching @param OutSections All non-BlendType sections @param OutAbsoluteSections All BlendType sections
- L709 _public function_ `template<typename ChannelType, typename CurveValueType> static TArray<CurveValueType> GetChannelValues(const int32 StartIndex, const int32 EndIndex, const TArray<UMovieSceneSection*>& Sections, const TArray<UMovieSceneSection*>& AbsoluteSections, const FFrameNumber& FrameTime)` — Get the channel values at the specified time with the specified sections, will get the channels from within the specified start and end indices @param StartIndex Start Index to get values from @param EndIndex End Index to get values from, should be no greater than the number of channels -1 @param Sections List of non-absolute(additive and override) sections to evaluate. Note this may not be all of the sections in the track, but just a subset, which allows us to evaluate up to a certain point in the track. @param AbsoluteSections List of absolute channels to evaluate @param FrameTime Frame to evaluate @return Returns the total channel value of those sections for each channel. Remember if OverrideChannelIndex is set this will just be one channel.
- L792 _public function_ `template<typename ChannelType, typename CurveValueType> static bool MergeValue(CurveValueType& InOutValue, TArray<ChannelType*>& Channels, const FFrameNumber& Frame, int32 SectionChannelIndex, const TArray<UMovieSceneSection*>& Sections, const TArray<UMovieSceneSection*>& AbsoluteSections, const TArray<UMovieSceneSection*>& OtherSections, int32 OverrideChannelIndex, FChannelMergeAlgorithm MergeAlgorithm)` — Merge the value based upon the specified merge algorithm using cached parameters For the algorithm to be relaible it should be done per section blending type. @param InOutValue  Current Value you want to merge with the other sections. @param Channels  Set of channels of this type that we will merge together onto the first specified one. @param Frame  Current Frame to merge @param SectionChannelIndex  The index of the channel of this type in the sections. @param Sections Set of corresponding sections for each channel specified. @param AbsoluteSections Set of absoluate sections for each channel specified. @param OtherSections Set of non-absolute sections for each channel specified. @param OverrideChanneIndex ChannelIndex for an override merge. @param MergeAlgorithm The algorithm to use to blend the channels together. @return Returns true if successful.
- L870 _public function_ `template<typename ChannelType> static bool MergeChannels(int32 SectionChannelIndex, TArray<ChannelType*>& Channels, const TArray<UMovieSceneSection*>& Sections, const TRange<FFrameNumber>& Range, FChannelMergeAlgorithm MergeAlgorithm, const TArray<UMovieSceneSection*>& TrackSections, const int32* Increment = nullptr)` — Merge the set of passed in channels from each section at the specified section channel index. For the algorithm to be relaible it should be done per section blending type. @param SectionChannelIndex  The index of the channel of this type in the sections. @param Channels  Set of channels of this type that we will merge together onto the first specified one. @param Sections Set of corresponding sections for each channel specified. @param Range Minimal range of time over which we will merge, we will always extend to key extents if possible @param MergeAlgorithm The algorithm to use to blend the channels together @param TrackSections Sections in this track @param Increment Optional increment index, if specfied we bake over the range using the increment value, otherwise by default we just merge onto the existing keys @return Returns true if successful
- L1038 _public function_ `template<typename ChannelType> static bool MergeTwoSections(const FBaseTopSections& BT, const TRange<FFrameNumber>& Range, const TArray<UMovieSceneSection*>& TrackSections, const int32* Increment = nullptr)` — Merge the TopSection onto the BaseSection. This function should be used when merging a mix of Override/Additive and Absolute section Blend Types. @param BaseAndTopSections The sections we are merging with index information @param Range Range of time over which we will merge  Control Rig sections and don't want to merge the last weight float channel @param TrackSections Sections in this track @param Increment Optional increment index, if specfied we bake over the range using the increment value, otherwise by default we just merge onto the existing keys @return Returns true if successful
- L1107 _public function_ `template<typename ChannelType> static bool MergeSections(UMovieSceneSection* BaseSection, UMovieSceneSection* TopSection, int32 StartIndex, int32 EndIndex, const TRange<FFrameNumber>& Range, const TArray<UMovieSceneSection*>& TrackSections, const int32* Increment = nullptr)`
- L1128 _public function_ `template<typename ChannelType> static bool MergeSections(UMovieSceneSection* BaseSection, TArray<UMovieSceneSection*>& AbsoluteSections, TArray<UMovieSceneSection*>& AdditiveSections, int32 StartIndex, int32 EndIndex, const TRange<FFrameNumber>& Range, const int32* Increment = nullptr)` — Merge the following set of sections. Should be used when blending just Absolute with additive sections. If Merging with overrides, use the above MergeSections function @param BaseSection  The section to merge onto @param AbsoluteSections  Set of absolute functions to merge @param AddditveSections  Set of Additive functions to merge @param StartIndex Start Index of the channels we are merging @param EndIndex End Index of the channels we are merging, should be no greater than the number of channels -1 @param Range Range of time over which we will merge Control Rig sections and don't want to merge the last weight float channel @param Increment Optional increment index, if specfied we bake over the range using the increment value, otherwise by default we just merge onto the existing keys @return Returns true if successful
- L1223 _public prototype_ `static bool OptimizeSection(const FKeyDataOptimizationParams& InParams, UMovieSceneSection* InSection);`
- L1226 _public prototype_ `static void CalculateFramesBetween( const UMovieScene* MovieScene, FFrameNumber StartFrame, FFrameNumber EndFrame, int FrameIncrement, TArray<FFrameNumber>& OutFrames);` — Returns the frame numbers between start and end.
- L1234 _public prototype_ `static UMovieScene3DTransformSection* GetTransformSection( const ISequencer* InSequencer, const FGuid& InGuid, const FTransform& InDefaultTransform = FTransform::Identity);` — Returns the transform section for that guid.
- L1240 _public prototype_ `static bool AddTransformKeys( const UMovieScene3DTransformSection* InTransformSection, const TArray<FFrameNumber>& Frames, const TArray<FTransform>& InLocalTransforms, const EMovieSceneTransformChannel& InChannels);` — Adds transform keys to the section based on the channels filters.
- L1252 _public prototype_ `static void AddTransformKeysForObject(UObject* Object, EMovieSceneTransformChannel ChannelToKey);` — Adds transform keys to a specific object, using it's current transform @param Object The object to add keys to. @param ChannelToKey The channels to add keys to.
- L1255 _public prototype_ `static void ImportAnimSequenceTransforms(const TSharedRef<ISequencer>& Sequencer, const FAssetData& Asset, UMovieScene3DTransformTrack* TransformTrack);` — Import an animation sequence's root transforms into a transform section
- L1258 _public prototype_ `static void ImportAnimSequenceTransformsEnterPressed(const TSharedRef<ISequencer>& Sequencer, const TArray<FAssetData>& Asset, UMovieScene3DTransformTrack* TransformTrack);` — Import an animation sequence's root transforms into a transform section
- L1266 _public prototype_ `static void RunSequencerTasks( ISequencer* Sequencer, UWorld* World, const TArray<FFrameNumber>& Frames, const TArrayView<TFunction<void(int32)>>& Tasks);` — Executes tasks at specified times. @param Sequencer the sequencer to evaluate. @param World the world context (used to retrieve constraints, can be null). @param Frames the times at which the sequencer should be evaluated. @param Tasks the tasks executed at each frame.
- L1278 _public prototype_ `static void RunSequencerTask( ISequencer* Sequencer, UWorld* World, const TArray<FFrameNumber>& Frames, const TFunctionRef<void(int32)>& Task);` — Executes a task at specified times. @param Sequencer the sequencer to evaluate. @param World the world context (used to retrieve constraints, can be null). @param Frames the times at which the sequencer should be evaluated. @param Task the task executed at each frame.

#### struct `MovieSceneToolHelpers::FBaseTopSections`  
`struct FBaseTopSections`  
_L1006-1027_
- L1008 _public function_ `FBaseTopSections(UMovieSceneSection* InBaseSection, UMovieSceneSection* InTopSection, int32 InBaseStartIndex, int32 InBaseEndIndex, int32 InTopStartIndex, int32 InTopEndIndex) : BaseSection(InBaseSection), TopSection(InTopSection), BaseStartIndex(InBaseStartIndex), BaseEndIndex(InBaseEndIndex), TopStartIndex(InTopStartIndex), TopEndIndex(InTopEndIndex)`
- L1021 _public member_ `UMovieSceneSection* BaseSection;`
- L1022 _public member_ `UMovieSceneSection* TopSection;`
- L1023 _public member_ `int32 BaseStartIndex;`
- L1024 _public member_ `int32 BaseEndIndex;`
- L1025 _public member_ `int32 TopStartIndex;`
- L1026 _public member_ `int32 TopEndIndex;`

#### struct `FSpawnableRestoreState`  
`struct FSpawnableRestoreState`  
_L1285-1300_
- L1288 _public prototype_ `FSpawnableRestoreState(UMovieScene* MovieScene);` — `UE_DEPRECATED(5.5, "This constructor is deprecated in favor of passing in shared playback state")`
- L1291 _public prototype_ `FSpawnableRestoreState(UMovieScene* MovieScene, TSharedPtr<UE::MovieScene::FSharedPlaybackState> InSharedPlaybackState);` — `UE_DEPRECATED(5.7, "FSpawnableRestoreState has been deprecated in favor of FAllSpawnableRestoreState that turns off and restores spawnables for the whole sequence")`
- L1293 _public prototype_ `~FSpawnableRestoreState();` — `UE_DEPRECATED(5.7, "FSpawnableRestoreState has been deprecated in favor of FAllSpawnableRestoreState that turns off and restores spawnables for the whole sequence")`
- L1295 _public member_ `bool bWasChanged;`
- L1296 _public member_ `TMap<FGuid, ESpawnOwnership> SpawnOwnershipMap;`
- L1297 _public member_ `TWeakObjectPtr<UMovieScene> WeakMovieScene;`
- L1298 _public member_ `TSharedPtr<UE::MovieScene::FSharedPlaybackState> SharedPlaybackState;`

#### struct `FAllSpawnableRestoreState`  
`struct FAllSpawnableRestoreState`  
_L1305-1323_
- desc: Helper to make all spawnables in all nested sub sequences persist throughout the export process and then restore properly afterwards You should use this when you may have multiple nested sequences, in particularly when using sequencer as the player If you create a player you need to pass in a MovieScene to use
- L1307 _public prototype_ `FAllSpawnableRestoreState(TSharedPtr<UE::MovieScene::FSharedPlaybackState> InSharedPlaybackState, UMovieScene* OptionalMovieScene = nullptr);`
- L1308 _public prototype_ `~FAllSpawnableRestoreState();`
- L1309 _public member_ `bool bWasChanged = false;`
- L1312 _public prototype_ `static void SaveStateForSpawnable(bool& bInOutWasChanged, TMap<FGuid, ESpawnOwnership>& InOutSpawnOwnershipMap, TWeakObjectPtr<UMovieScene>& WeakMovieScene, FGuid BindingGuid, ESpawnOwnership PreviousSpawnOwnership, TFunction<void(ESpawnOwnership)> SpawnOwnershipSetter);` — helper function to set up the SpawnOwnershipMap given the binding, will update if the spawn track was updated
- L1321 _private member_ `TMap <TWeakObjectPtr<UMovieScene>, FPerMovieScene> OwnershipMaps;`
- L1322 _private member_ `TSharedPtr<UE::MovieScene::FSharedPlaybackState> SharedPlaybackState;`

#### struct `FAllSpawnableRestoreState::FPerMovieScene`  
`struct FPerMovieScene`  
_L1315-1320_
- L1317 _public member_ `TMap<FGuid, ESpawnOwnership> SpawnOwnershipMap;`
- L1318 _public member_ `TWeakObjectPtr<UMovieScene> WeakMovieScene;`
- L1319 _public member_ `FMovieSceneSequenceID SequenceID;`

#### class `FTrackEditorBindingIDPicker`  
`class FTrackEditorBindingIDPicker : public FMovieSceneObjectBindingIDPicker`  
_L1325-1349_
- inherits: `FMovieSceneObjectBindingIDPicker`
- L1328 _public function_ `FTrackEditorBindingIDPicker(FMovieSceneSequenceID InLocalSequenceID, TWeakPtr<ISequencer> InSequencer) : FMovieSceneObjectBindingIDPicker(InLocalSequenceID, InSequencer)`
- L1334 _public function_ `DECLARE_EVENT_OneParam(FTrackEditorBindingIDPicker, FOnBindingPicked, FMovieSceneObjectBindingID) FOnBindingPicked& OnBindingPicked()`
- L1344 _private function_ `virtual UMovieSceneSequence* GetSequence() const override`
- L1345 _private function_ `virtual void SetCurrentValue(const FMovieSceneObjectBindingID& InBindingId) override`
- L1346 _private function_ `virtual FMovieSceneObjectBindingID GetCurrentValue() const override`
- L1348 _private member_ `FOnBindingPicked OnBindingPickedEvent;`

#### Free symbols / members of external scopes

- L25 _macro_ `#define UE_API MOVIESCENETOOLS_API`
- L52 _namespace_ `namespace fbxsdk`
- L57 _namespace_ `namespace UnFbx`
- L83 _delegate_ `DECLARE_DELEGATE(FInitAnimationCB);`
- L83 _prototype_ `DECLARE_DELEGATE(FInitAnimationCB);`
- L84 _delegate_ `DECLARE_DELEGATE_OneParam(FStartAnimationCB, FFrameNumber);`
- L84 _prototype_ `DECLARE_DELEGATE_OneParam(FStartAnimationCB, FFrameNumber);`
- L85 _delegate_ `DECLARE_DELEGATE_TwoParams(FTickAnimationCB, float, FFrameNumber);`
- L85 _prototype_ `DECLARE_DELEGATE_TwoParams(FTickAnimationCB, float, FFrameNumber);`
- L86 _delegate_ `DECLARE_DELEGATE(FEndAnimationCB);`
- L86 _prototype_ `DECLARE_DELEGATE(FEndAnimationCB);`
- L884 _typedef_ `using ChannelValueType = typename ChannelType::ChannelValueType;` (scope `MovieSceneToolHelpers::MergeChannels`)
- L885 _typedef_ `using CurveValueType = typename ChannelType::CurveValueType;` (scope `MovieSceneToolHelpers::MergeChannels`)
- L1334 _delegate_ `DECLARE_EVENT_OneParam(FTrackEditorBindingIDPicker, FOnBindingPicked, FMovieSceneObjectBindingID) FOnBindingPicked& OnBindingPicked() { return OnBindingPickedEvent; } using FMovieSceneObjectBindingIDPicker::GetPickerMenu;`

### `Source/Editor/MovieSceneTools/Public/MovieSceneToolsModule.h` (Public)


#### class `IMovieSceneToolsTakeData`  
`class IMovieSceneToolsTakeData`  
_L27-33_
- L30 _public prototype_ `virtual bool GatherTakes(const UMovieSceneSection* Section, TArray<FAssetData>& AssetData, uint32& OutCurrentTakeNumber) = 0;`
- L31 _public prototype_ `virtual bool GetTakeNumber(const UMovieSceneSection* Section, FAssetData AssetData, uint32& OutTakeNumber) = 0;`
- L32 _public prototype_ `virtual bool SetTakeNumber(const UMovieSceneSection*, uint32 InTakeNumber) = 0;`

#### class `IMovieSceneToolsAnimationBakeHelper`  
`class IMovieSceneToolsAnimationBakeHelper`  
_L36-43_
- desc: Interface to get notifications when an animation bake happens in case in needs to run custom code
- L39 _public function_ `virtual void StartBaking(UMovieScene* MovieScene)`
- L40 _public function_ `virtual void PreEvaluation(UMovieScene* MovieScene, FFrameNumber Frame)`
- L41 _public function_ `virtual void PostEvaluation(UMovieScene* MovieScene, FFrameNumber Frame)`
- L42 _public function_ `virtual void StopBaking(UMovieScene* MovieScene)`

#### struct `FMovieSceneToolsAnimationBakingWrapper`  
`struct FMovieSceneToolsAnimationBakingWrapper`  
_L45-57_
- L47 _public prototype_ `FMovieSceneToolsAnimationBakingWrapper(UMovieScene* InMovieScene);`
- L49 _public prototype_ `void Start() const;`
- L50 _public prototype_ `void PreEvaluate(const FFrameNumber& Frame) const;`
- L51 _public prototype_ `void PostEvaluate(const FFrameNumber& Frame) const;`
- L52 _public prototype_ `void Stop() const;`
- L55 _private member_ `UMovieScene* MovieScene = nullptr;`
- L56 _private member_ `const TArray<IMovieSceneToolsAnimationBakeHelper*>& BakeHelpers;`

#### class `IMovieSceneToolsKeyStructInstancedPropertyTypeCustomizer`  
`class IMovieSceneToolsKeyStructInstancedPropertyTypeCustomizer`  
_L60-64_
- desc: Interface to allow external modules to register additional key struct instanced property type customizations
- L63 _public function_ `virtual void RegisterKeyStructInstancedPropertyTypeCustomization(TSharedRef<IStructureDetailsView> StructureDetailsView, TWeakObjectPtr<UMovieSceneSection> WeakOwningSection)`

#### class `FSkeletalAnimationRootMotionOffsetProvider`  
`class FSkeletalAnimationRootMotionOffsetProvider : public IMovieSceneRootMotionOffsetProvider`  
_L68-73_
- inherits: `IMovieSceneRootMotionOffsetProvider`
- desc: Wraps UMovieSceneSkeletalAnimationSystem as an IMovieSceneRootMotionOffsetProvider so the transform track editor can subtract root motion during auto-key.
- L71 _public prototype_ `virtual FTransform GetRootMotionOffset(const UMovieSceneEntitySystemLinker* Linker, UObject* AnimatedObject) const override;`
- L72 _public prototype_ `virtual void UpdateRootMotionOffset(UMovieSceneEntitySystemLinker* Linker, UObject* AnimatedObject) override;`

#### class `FMovieSceneToolsModule`  
`class FMovieSceneToolsModule : public IMovieSceneTools`  
_L78-189_
- inherits: `IMovieSceneTools`
- desc: Implements the MovieSceneTools module.
- L83 _public function_ `static inline FMovieSceneToolsModule& Get()`
- L89 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface interface
- L90 _public prototype_ `virtual void ShutdownModule() override;`
- L92 _public prototype_ `void RegisterAnimationBakeHelper(IMovieSceneToolsAnimationBakeHelper* BakeHelper);`
- L93 _public prototype_ `void UnregisterAnimationBakeHelper(IMovieSceneToolsAnimationBakeHelper* BakeHelper);`
- L94 _public function_ `const TArray<IMovieSceneToolsAnimationBakeHelper*>& GetAnimationBakeHelpers()`
- L95 _public prototype_ `void RegisterTakeData(IMovieSceneToolsTakeData*);`
- L96 _public prototype_ `void UnregisterTakeData(IMovieSceneToolsTakeData*);`
- L98 _public prototype_ `bool GatherTakes(const UMovieSceneSection* Section, TArray<FAssetData>& AssetData, uint32& OutCurrentTakeNumber);`
- L99 _public prototype_ `bool GetTakeNumber(const UMovieSceneSection* Section, FAssetData AssetData, uint32& OutTakeNumber);`
- L100 _public prototype_ `bool SetTakeNumber(const UMovieSceneSection* Section, uint32 InTakeNumber);`
- L102 _public prototype_ `void RegisterTrackImporter(IMovieSceneToolsTrackImporter*);`
- L103 _public prototype_ `void UnregisterTrackImporter(IMovieSceneToolsTrackImporter*);`
- L105 _public prototype_ `bool ImportAnimatedProperty(const FString& InPropertyName, const FRichCurve& InCurve, FGuid InBinding, UMovieScene* InMovieScene);`
- L106 _public prototype_ `bool ImportStringProperty(const FString& InPropertyName, const FString& InPropertyValue, FGuid InBinding, UMovieScene* InMovieScene);`
- L108 _public prototype_ `void RegisterKeyStructInstancedPropertyTypeCustomizer(IMovieSceneToolsKeyStructInstancedPropertyTypeCustomizer*);`
- L109 _public prototype_ `void UnregisterKeyStructInstancedPropertyTypeCustomizer(IMovieSceneToolsKeyStructInstancedPropertyTypeCustomizer*);`
- L112 _public prototype_ `void CustomizeKeyStructInstancedPropertyTypes(TSharedRef<IStructureDetailsView> StructureDetailsView, TWeakObjectPtr<UMovieSceneSection> Section);` — Called By SKeyEditInterface to allow external modules to add key struct instanced property type customizations
- L116 _private prototype_ `void RegisterClipboardConversions();`
- L118 _private prototype_ `static void FixupPayloadParameterNameForSection(UMovieSceneEventSectionBase* Section, UK2Node* InNode, FName OldPinName, FName NewPinName);`
- L119 _private prototype_ `static void FixupPayloadParameterNameForDynamicBinding(UMovieScene* MovieScene, UK2Node* InNode, FName OldPinName, FName NewPinName);`
- L120 _private prototype_ `static bool UpgradeLegacyEventEndpointForSection(UMovieSceneEventSectionBase* Section);`
- L121 _private prototype_ `static void PostDuplicateEventSection(UMovieSceneEventSectionBase* Section);`
- L122 _private prototype_ `static void RemoveForCookEventSection(UMovieSceneEventSectionBase* Section);`
- L123 _private prototype_ `static bool IsTrackClassAllowed(UClass* InClass);`
- L124 _private prototype_ `static bool IsCustomBindingClassAllowed(UClass* InClass);`
- L125 _private prototype_ `static bool IsConditionClassAllowed(const UClass* InClass);`
- L126 _private prototype_ `static void PostDuplicateEvent(ULevelSequence* LevelSequence);`
- L127 _private prototype_ `static void FixupDynamicBindingsEvent(ULevelSequence* LevelSequence);`
- L128 _private prototype_ `static void FixupPayloadParameterNameForDirectorBlueprintCondition(UMovieScene* MovieScene, UK2Node* InNode, FName OldPinName, FName NewPinName);`
- L133 _private member_ `FDelegateHandle BytePropertyTrackCreateEditorHandle;` — Registered delegate handles
- L134 _private member_ `FDelegateHandle RotatorPropertyTrackCreateEditorHandle;`
- L135 _private member_ `FDelegateHandle VisibilityPropertyTrackCreateEditorHandle;`
- L136 _private member_ `FDelegateHandle ActorReferencePropertyTrackCreateEditorHandle;`
- L137 _private member_ `FDelegateHandle StringPropertyTrackCreateEditorHandle;`
- L138 _private member_ `FDelegateHandle TextPropertyTrackCreateEditorHandle;`
- L139 _private member_ `FDelegateHandle ObjectTrackCreateEditorHandle;`
- L141 _private member_ `FDelegateHandle AnimationTrackCreateEditorHandle;`
- L142 _private member_ `FDelegateHandle AttachTrackCreateEditorHandle;`
- L143 _private member_ `FDelegateHandle AudioTrackCreateEditorHandle;`
- L144 _private member_ `FDelegateHandle EventTrackCreateEditorHandle;`
- L145 _private member_ `FDelegateHandle ParticleTrackCreateEditorHandle;`
- L146 _private member_ `FDelegateHandle ParticleParameterTrackCreateEditorHandle;`
- L147 _private member_ `FDelegateHandle PathTrackCreateEditorHandle;`
- L148 _private member_ `FDelegateHandle CameraCutTrackCreateEditorHandle;`
- L149 _private member_ `FDelegateHandle CinematicShotTrackCreateEditorHandle;`
- L150 _private member_ `FDelegateHandle SlomoTrackCreateEditorHandle;`
- L151 _private member_ `FDelegateHandle SubTrackCreateEditorHandle;`
- L152 _private member_ `FDelegateHandle TransformTrackCreateEditorHandle;`
- L153 _private member_ `FDelegateHandle ComponentMaterialTrackCreateEditorHandle;`
- L154 _private member_ `FDelegateHandle FadeTrackCreateEditorHandle;`
- L155 _private member_ `FDelegateHandle SpawnTrackCreateEditorHandle;`
- L156 _private member_ `FDelegateHandle LevelVisibilityTrackCreateEditorHandle;`
- L157 _private member_ `FDelegateHandle DataLayerTrackCreateEditorHandle;`
- L158 _private member_ `FDelegateHandle CameraShakeTrackCreateEditorHandle;`
- L159 _private member_ `FDelegateHandle MPCTrackCreateEditorHandle;`
- L160 _private member_ `FDelegateHandle PrimitiveMaterialCreateEditorHandle;`
- L161 _private member_ `FDelegateHandle CameraShakeSourceShakeCreateEditorHandle;`
- L162 _private member_ `FDelegateHandle CVarTrackCreateEditorHandle;`
- L163 _private member_ `FDelegateHandle CustomPrimitiveDataTrackCreateEditorHandle;`
- L164 _private member_ `FDelegateHandle BindingLifetimeTrackCreateEditorHandle;`
- L165 _private member_ `FDelegateHandle TimeWarpTrackCreateEditorHandle;`
- L166 _private member_ `FDelegateHandle RegisteredPropertyTrackCreateEditorHandle;`
- L168 _private member_ `FDelegateHandle CameraCutTrackModelHandle;`
- L169 _private member_ `FDelegateHandle CinematicShotTrackModelHandle;`
- L170 _private member_ `FDelegateHandle BindingLifetimeTrackModelHandle;`
- L171 _private member_ `FDelegateHandle TimeWarpTrackModelHandle;`
- L173 _private member_ `FDelegateHandle GenerateEventEntryPointsHandle;`
- L174 _private member_ `FDelegateHandle FixupDynamicBindingPayloadParameterNameHandle;`
- L175 _private member_ `FDelegateHandle FixupEventSectionPayloadParameterNameHandle;`
- L176 _private member_ `FDelegateHandle UpgradeLegacyEventEndpointHandle;`
- L177 _private member_ `FDelegateHandle FixupDynamicBindingsHandle;`
- L178 _private member_ `FDelegateHandle FixupDirectorBlueprintConditionPayloadParameterNameHandle;`
- L180 _private member_ `FDelegateHandle OnObjectsReplacedHandle;`
- L182 _private member_ `TArray<IMovieSceneToolsTakeData*> TakeDatas;`
- L183 _private member_ `TArray<IMovieSceneToolsTrackImporter*> TrackImporters;`
- L185 _private member_ `TArray<IMovieSceneToolsAnimationBakeHelper*> BakeHelpers;`
- L186 _private member_ `TArray<IMovieSceneToolsKeyStructInstancedPropertyTypeCustomizer*> KeyStructInstancedPropertyTypeCustomizers;`
- L188 _private member_ `FSkeletalAnimationRootMotionOffsetProvider SkeletalAnimRootMotionProvider;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API MOVIESCENETOOLS_API`

### `Source/Editor/MovieSceneTools/Public/MovieSceneToolsProjectSettings.h` (Public)


#### enum `EMovieSceneToolsPropertyTrackType`  
`enum class EMovieSceneToolsPropertyTrackType`  
_L18-22_
- reflection: `UENUM()`
- L20 _public enumerator_ `FloatTrack`
- L21 _public enumerator_ `DoubleTrack`

#### struct `FMovieSceneToolsPropertyTrackSettings`  
`struct FMovieSceneToolsPropertyTrackSettings`  
_L25-36_
- reflection: `USTRUCT()`
- L31 _public member_ `FString ComponentName;` — `UPROPERTY(config, EditAnywhere, Category=PropertyTrack)` — Optional ActorComponent tag (when keying a component property).
- L35 _public member_ `FString PropertyName;` — `UPROPERTY(config, EditAnywhere, Category=PropertyTrack)` — Name to the keyed property within the Actor or ActorComponent.

#### struct `FMovieSceneToolsFbxSettings`  
`struct FMovieSceneToolsFbxSettings`  
_L39-54_
- reflection: `USTRUCT()`
- L45 _public member_ `FString FbxPropertyName;` — `UPROPERTY(config, EditAnywhere, Category=TrackSettings)` — The name of the fbx property
- L49 _public member_ `FMovieSceneToolsPropertyTrackSettings PropertyPath;` — `UPROPERTY(config, EditAnywhere, Category=TrackSettings)` — The property track setting to map to
- L53 _public member_ `EMovieSceneToolsPropertyTrackType PropertyType = EMovieSceneToolsPropertyTrackType::FloatTrack;` — `UPROPERTY(config, EditAnywhere, Category=TrackSettings)` — Type of property track to map to

#### class `UMovieSceneToolsProjectSettings`  
`class UMovieSceneToolsProjectSettings : public UObject`  
_L58-116_
- reflection: `UCLASS(MinimalAPI, config=EditorPerProjectUserSettings)`
- inherits: `UObject`
- desc: Settings for the level sequences
- L63 _public prototype_ `UMovieSceneToolsProjectSettings();`
- L67 _public member_ `float DefaultStartTime;` — `UPROPERTY(config, EditAnywhere, Category=Timeline, meta=(Units=s))` — The default start time for new level sequences, in seconds.
- L71 _public member_ `float DefaultDuration;` — `UPROPERTY(config, EditAnywhere, Category=Timeline, meta=(ClampMin=0.00001f, Units=s))` — The default duration for new level sequences in seconds.
- L75 _public member_ `FString SubsequenceDirectory;` — `UPROPERTY(config, EditAnywhere, Category=Shots)` — The default directory for the subsequences.
- L79 _public member_ `FString ShotDirectory;` — `UPROPERTY(config, EditAnywhere, Category=Shots)` — The default directory for the shots.
- L83 _public member_ `FString SubsequencePrefix;` — `UPROPERTY(config, EditAnywhere, Category=Shots)` — The default prefix for subsequence names.
- L87 _public member_ `FString ShotPrefix;` — `UPROPERTY(config, EditAnywhere, Category=Shots)` — The default prefix for shot names.
- L91 _public member_ `uint32 FirstShotNumber;` — `UPROPERTY(config, EditAnywhere, Category=Shots, meta = (UIMin = "1", UIMax = "100"))` — The first shot number.
- L95 _public member_ `uint32 ShotIncrement;` — `UPROPERTY(config, EditAnywhere, Category=Shots, meta = (UIMin = "1", UIMax = "100"))` — The default shot increment.
- L99 _public member_ `uint32 ShotNumDigits;` — `UPROPERTY(config, EditAnywhere, Category=Shots, meta = (UIMin = "1", UIMax = "10"))` — The number of digits for the shot number.
- L103 _public member_ `uint32 TakeNumDigits;` — `UPROPERTY(config, EditAnywhere, Category=Shots, meta = (UIMin = "1", UIMax = "10"))` — The number of digits for the take number.
- L107 _public member_ `uint32 FirstTakeNumber;` — `UPROPERTY(config, EditAnywhere, Category=Shots, meta = (UIMin = "1", UIMax = "10"))` — The first take number.
- L111 _public member_ `FString TakeSeparator;` — `UPROPERTY(config, EditAnywhere, Category=Shots)` — Character separator between the shot number and the take number.
- L115 _public member_ `TArray<FMovieSceneToolsFbxSettings> FbxSettings;` — `UPROPERTY(config, EditAnywhere, Category=TrackSettings)` — Mapping between fbx property name and property track path

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API MOVIESCENETOOLS_API`

### `Source/Editor/MovieSceneTools/Public/MovieSceneToolsUserSettings.h` (Public)


#### enum `EThumbnailQuality`  
`enum class EThumbnailQuality : uint8`  
_L18-23_
- reflection: `UENUM()`
- L20 _public enumerator_ `Draft`
- L21 _public enumerator_ `Normal`
- L22 _public enumerator_ `Best`

#### class `UMovieSceneUserThumbnailSettings`  
`class UMovieSceneUserThumbnailSettings : public UObject`  
_L26-62_
- reflection: `UCLASS(MinimalAPI, config=EditorSettings)`
- inherits: `UObject`
- L29 _public prototype_ `UMovieSceneUserThumbnailSettings(const FObjectInitializer& Initializer);`
- L35 _public member_ `bool bDrawThumbnails;` — `UPROPERTY(EditAnywhere, config, Category=General)` — Whether to draw thumbnails or not
- L39 _public member_ `bool bDrawSingleThumbnails;` — `UPROPERTY(EditAnywhere, config, Category=General, meta=(EditCondition=bDrawThumbnails))` — Whether to draw a single thumbnail for this section or as many as can fit
- L43 _public member_ `FIntPoint ThumbnailSize;` — `UPROPERTY(EditAnywhere, config, Category=General, meta=(ClampMin=1, ClampMax=1024, EditCondition=bDrawThumbnails))` — Size at which to draw thumbnails on thumbnail sections
- L47 _public member_ `EThumbnailQuality Quality;` — `UPROPERTY(EditAnywhere, config, Category=General, meta=(EditCondition=bDrawThumbnails))` — Quality to render the thumbnails with
- L50 _public member_ `FSceneViewStateReference ViewState;` — Temporal history for the view required for advanced features(e.g., eye adaptation) on all thumbnails
- L52 _public function_ `DECLARE_EVENT(UMovieSceneUserThumbnailSettings, FOnForceRedraw) FOnForceRedraw& OnForceRedraw()`
- L54 _public function_ `void BroadcastRedrawThumbnails() const`
- L56 _public prototype_ `virtual void PostEditChangeProperty( struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L58 _public prototype_ `static void AddReferencedObjects(UObject* InThis, FReferenceCollector& InCollector);`
- L61 _private member_ `FOnForceRedraw OnForceRedrawEvent;`

#### class `UMovieSceneUserImportFBXSettings`  
`class UMovieSceneUserImportFBXSettings : public UObject`  
_L65-109_
- reflection: `UCLASS(MinimalAPI, config=EditorSettings, BlueprintType)`
- inherits: `UObject`
- L68 _public prototype_ `UMovieSceneUserImportFBXSettings(const FObjectInitializer& Initializer);`
- L74 _public member_ `bool bMatchByNameOnly;` — `UPROPERTY(EditAnywhere, config, Category=Import, meta= (ToolTip = "Match fbx node names to sequencer node names"))` — Whether to match fbx node names to sequencer node names.
- L78 _public member_ `bool bForceFrontXAxis;` — `UPROPERTY(EditAnywhere, config, Category=Import, meta= (ToolTip = "Convert the scene from FBX coordinate system to UE coordinate system with front X axis instead of -Y"))` — Whether to force the front axis to be align with X instead of -Y.
- L82 _public member_ `bool bConvertSceneUnit;` — `UPROPERTY(EditAnywhere, config, Category = Import, meta = (ToolTip = "Convert the scene from FBX unit to UE unit(centimeter)"))` — Convert the scene from FBX unit to UE unit(centimeter)
- L86 _public member_ `float ImportUniformScale;` — `UPROPERTY(EditAnywhere, config, Category = Import, meta = (ToolTip = "Import Uniform Scale"))` — Import Uniform Scale
- L90 _public member_ `bool bCreateCameras;` — `UPROPERTY(EditAnywhere, config, Category=Import)` — Whether to create cameras if they don't already exist in the level.
- L94 _public member_ `bool bReplaceTransformTrack;` — `UPROPERTY(EditAnywhere, config, Category=Import)` — Whether to replace the existing transform track or create a new track/section
- L100 _public member_ `bool bCorrectForTransformOrigin;` — `UPROPERTY(EditAnywhere, config, Category=Import)` — When enabled, the current transform origin of the focused sequence will be removed from any imported transforms. If the FBX was exported with a transform origin, this will prevent it from being applied twice.
- L104 _public member_ `bool bReduceKeys;` — `UPROPERTY(EditAnywhere, config, Category=Import)` — Whether to remove keyframes within a tolerance from the imported tracks
- L108 _public member_ `float ReduceKeysTolerance;` — `UPROPERTY(EditAnywhere, config, Category=Import, meta=(EditCondition=bReduceKeys))` — The tolerance for reduce keys

#### enum `FControlRigChannelEnum`  
`enum class FControlRigChannelEnum : uint8`  
_L114-146_
- reflection: `UENUM(BlueprintType)`
- desc: Enumeration specifying the control type and channel
- L117 _public enumerator_ `Bool` — Bool
- L119 _public enumerator_ `Enum` — Enum
- L121 _public enumerator_ `Integer` — Integer
- L123 _public enumerator_ `Float` — Float
- L125 _public enumerator_ `Vector2DX` — Vector2D.X
- L127 _public enumerator_ `Vector2DY` — Vector2D.Y
- L129 _public enumerator_ `PositionX` — Position.X
- L131 _public enumerator_ `PositionY` — Position.Y
- L133 _public enumerator_ `PositionZ` — Position.Z
- L135 _public enumerator_ `RotatorX` — Rotator.X
- L137 _public enumerator_ `RotatorY` — Rotator.Y
- L139 _public enumerator_ `RotatorZ` — Rotator.Z
- L141 _public enumerator_ `ScaleX` — Scale.X
- L143 _public enumerator_ `ScaleY` — Scale.Y
- L145 _public enumerator_ `ScaleZ` — Scale.Z

#### enum `FTransformChannelEnum`  
`enum class FTransformChannelEnum : uint8`  
_L150-161_
- reflection: `UENUM(BlueprintType)`
- desc: Enumeration specifying the transfrom channel
- L152 _public enumerator_ `TranslateX`
- L153 _public enumerator_ `TranslateY`
- L154 _public enumerator_ `TranslateZ`
- L155 _public enumerator_ `RotateX`
- L156 _public enumerator_ `RotateY`
- L157 _public enumerator_ `RotateZ`
- L158 _public enumerator_ `ScaleX`
- L159 _public enumerator_ `ScaleY`
- L160 _public enumerator_ `ScaleZ`

#### struct `FControlToTransformMappings`  
`struct FControlToTransformMappings`  
_L164-182_
- reflection: `USTRUCT(BlueprintType)`
- L168 _public function_ `FControlToTransformMappings() : ControlChannel(FControlRigChannelEnum::Float), FBXChannel(FTransformChannelEnum::TranslateX), bNegate(false)`
- L173 _public member_ `FControlRigChannelEnum ControlChannel;` — `UPROPERTY(Config, EditAnywhere, AdvancedDisplay, Category = "Control To Transform Mappings")` — The channel of the control to map
- L177 _public member_ `FTransformChannelEnum FBXChannel;` — `UPROPERTY(Config, EditAnywhere, AdvancedDisplay, Category = "Controle To Transform Mappings")` — The channel of the fbx transofrm node to map
- L181 _public member_ `bool bNegate;` — `UPROPERTY(Config, EditAnywhere, AdvancedDisplay, Category = "Control To Transform Mappings")` — Whether to negate the value

#### struct `FControlFindReplaceString`  
`struct FControlFindReplaceString`  
_L185-199_
- reflection: `USTRUCT(BlueprintType)`
- L189 _public function_ `FControlFindReplaceString()`
- L194 _public member_ `FString Find;` — `UPROPERTY(Config, EditAnywhere, AdvancedDisplay, Category = "Imported File Information")` — The string to find in the imported data
- L198 _public member_ `FString Replace;` — `UPROPERTY(Config, EditAnywhere, AdvancedDisplay, Category = "Imported File Information")` — The string to replace in the imported data

#### class `UMovieSceneUserImportFBXControlRigSettings`  
`class UMovieSceneUserImportFBXControlRigSettings : public UObject`  
_L202-280_
- reflection: `UCLASS(MinimalAPI, BlueprintType,config = EditorSettings)`
- inherits: `UObject`
- L205 _public prototype_ `UMovieSceneUserImportFBXControlRigSettings(const FObjectInitializer& Initializer);`
- L210 _public member_ `FString ImportedFileName;` — `UPROPERTY(VisibleAnywhere, Category = "Imported File Information")` — Imported File Name
- L214 _public member_ `FFrameNumber ImportedStartTime;` — `UPROPERTY(VisibleAnywhere, Category = "Imported File Information")` — Imported File Duration in Seconds
- L218 _public member_ `FFrameNumber ImportedEndTime;` — `UPROPERTY(VisibleAnywhere, Category = "Imported File Information")` — Imported File
- L222 _public member_ `TArray<FString> ImportedNodeNames;` — `UPROPERTY(VisibleAnywhere,Category = "Imported File Information")` — List Of Imported Names in FBX File
- L226 _public member_ `FString ImportedFrameRate;` — `UPROPERTY(VisibleAnywhere, Category = "Imported File Information")` — Incoming File Frame Rate
- L230 _public member_ `TArray< FControlFindReplaceString> FindAndReplaceStrings;` — `UPROPERTY(EditAnywhere, config, Category = "String Matching Options", meta = (ToolTip = "Strings In Imported Node To Find And Replace"))` — Strings To Find in the Import and Replace With
- L234 _public member_ `bool bStripNamespace = true;` — `UPROPERTY(EditAnywhere, config, Category = "Import Options", meta = (ToolTip = "Will strip any namespace from the FBX node names"))` — Strip namespaces from FBX node names
- L238 _public member_ `bool bForceFrontXAxis;` — `UPROPERTY(EditAnywhere, config, Category = "Import Options", meta = (ToolTip = "Convert the scene from FBX coordinate system to UE coordinate system with front X axis instead of -Y"))` — Whether to force the front axis to be align with X instead of -Y.
- L242 _public member_ `bool bConvertSceneUnit;` — `UPROPERTY(EditAnywhere, config, Category = Import, meta = (ToolTip = "Convert the scene from FBX unit to UE unit(centimeter)"))` — Convert the scene from FBX unit to UE unit(centimeter)
- L246 _public member_ `float ImportUniformScale;` — `UPROPERTY(EditAnywhere, config, Category = Import, meta = (ToolTip = "Import Uniform Scale"))` — Import Uniform Scale
- L250 _public member_ `bool bImportOntoSelectedControls;` — `UPROPERTY(EditAnywhere, config, Category = "Import Options")` — Whether or not import onto selected controls or all controls
- L254 _public member_ `FFrameNumber TimeToInsertOrReplaceAnimation;` — `UPROPERTY(EditAnywhere, config, Category = "Import Options")` — Time that we insert or replace the imported animation
- L258 _public member_ `bool bInsertAnimation;` — `UPROPERTY(EditAnywhere, config, Category = "Import Options")` — Whether or not we insert or replace, by default we insert
- L262 _public member_ `bool bSpecifyTimeRange;` — `UPROPERTY(EditAnywhere, config, Category = "Import Options")` — Whether to import over specific Time Range
- L266 _public member_ `FFrameNumber StartTimeRange;` — `UPROPERTY(EditAnywhere, config, Category = "Import Options", meta = (EditCondition = bSpecifyTimeRange))` — Start Time Range To Import
- L270 _public member_ `FFrameNumber EndTimeRange;` — `UPROPERTY(EditAnywhere, config, Category = "Import Options", meta = (EditCondition = bSpecifyTimeRange))` — End Time Range To Import
- L274 _public member_ `TArray<FControlToTransformMappings> ControlChannelMappings;` — `UPROPERTY(Config, EditAnywhere, Category = "Control Attribute Mappings")` — Mappings for how Control Rig Control Attributes Map to the incoming Transforms
- L279 _public prototype_ `void LoadControlMappingsFromPreset(bool bMetaHumanPreset);` — `UFUNCTION(BlueprintCallable, Category = "Control Rig")` — Load the default or metahuman preset into the current mappings

#### class `UMovieSceneUserExportFBXControlRigSettings`  
`class UMovieSceneUserExportFBXControlRigSettings : public UObject`  
_L283-321_
- reflection: `UCLASS(MinimalAPI, BlueprintType, config = EditorSettings)`
- inherits: `UObject`
- L286 _public prototype_ `UMovieSceneUserExportFBXControlRigSettings(const FObjectInitializer& Initializer);`
- L291 _public member_ `FString ExportFileName;` — `UPROPERTY(EditAnywhere, Category = "Imported File Information")` — Imported File Name
- L295 _public member_ `EFbxExportCompatibility FbxExportCompatibility = EFbxExportCompatibility::FBX_2018;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, config, Category = Exporter)` — This will set the fbx sdk compatibility when exporting to fbx file. The default value is 2013
- L299 _public member_ `uint32 bASCII : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, config, Category = Exporter)` — If enabled, save as ascii instead of binary
- L303 _public member_ `bool bForceFrontXAxis = false;` — `UPROPERTY(EditAnywhere, config, Category = Exporter, meta = (ToolTip = "Convert the scene from FBX coordinate system to UE coordinate system with front X axis instead of -Y"))` — Whether to force the front axis to be align with X instead of -Y.
- L307 _public member_ `bool bExportOnlySelectedControls = false;` — `UPROPERTY(EditAnywhere, config, Category = "Control Rig")` — Whether or not import onto selected controls or all controls
- L311 _public member_ `TArray<FControlToTransformMappings> ControlChannelMappings;` — `UPROPERTY(Config, EditAnywhere, Category = "Control Rig")` — Mappings for how Control Rig Control Attributes Map to the incoming Transforms
- L315 _public member_ `uint32 bExportLocalTime : 1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, config, category = Animation)` — If enabled, export sequencer animation in its local time, relative to its sequence.
- L320 _public prototype_ `void LoadControlMappingsFromPreset(bool bMetaHumanPreset);` — `UFUNCTION(BlueprintCallable, Category = "Control Rig")` — Load the default or metahuman preset into the current mappings

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API MOVIESCENETOOLS_API`
- L52 _delegate_ `DECLARE_EVENT(UMovieSceneUserThumbnailSettings, FOnForceRedraw) FOnForceRedraw& OnForceRedraw() { return OnForceRedrawEvent; } void BroadcastRedrawThumbnails() const { OnForceRedrawEvent.Broadcast(); } virtual void PostEditChangeProperty( struct FPropertyChangedEvent& PropertyChangedEvent) override;`

### `Source/Editor/MovieSceneTools/Public/MovieSceneTranslator.h` (Public)


#### class `FMovieSceneTranslatorContext`  
`class FMovieSceneTranslatorContext : public TSharedFromThis<FMovieSceneTranslatorContext>`  
_L23-50_
- inherits: `TSharedFromThis<FMovieSceneTranslatorContext>`
- desc: MovieSceneTranslator context class.
- L27 _public function_ `FMovieSceneTranslatorContext()` — Constructor
- L29 _public prototype_ `virtual ~FMovieSceneTranslatorContext() = default;` — Destructor
- L32 _public prototype_ `void Init();` — Initialize the context
- L35 _public prototype_ `void AddMessage(EMessageSeverity::Type MessageSeverity, FText ErrorMessage);` — Add message.
- L38 _public prototype_ `void ClearMessages();` — Reset all messages.
- L41 _public prototype_ `bool ContainsMessageType(EMessageSeverity::Type InSeverity) const;` — Returns true if specified type of message
- L44 _public prototype_ `const TArray<TSharedRef<FTokenizedMessage>>& GetMessages() const;` — Get error messages.
- L49 _private member_ `TArray<TSharedRef<FTokenizedMessage>> Messages;` — Error messages

#### struct `FMovieSceneExportSectionData`  
`struct FMovieSceneExportSectionData`  
_L52-65_
- L54 _public member_ `const UMovieSceneSection* MovieSceneSection;`
- L55 _public member_ `int32 RowIndex;`
- L57 _public member_ `FString DisplayName;`
- L58 _public member_ `FString SourceFilename;`
- L59 _public member_ `FString SourceFilePath;`
- L61 _public member_ `FFrameNumber StartFrame;`
- L62 _public member_ `FFrameNumber EndFrame;`
- L63 _public member_ `bool bWithinPlaybackRange;`
- L64 _public member_ `bool bEnabled;`

#### struct `FMovieSceneExportCinematicSectionData`  
`struct FMovieSceneExportCinematicSectionData : public FMovieSceneExportSectionData`  
_L67-69_
- inherits: `FMovieSceneExportSectionData`

#### struct `FMovieSceneExportAudioSectionData`  
`struct FMovieSceneExportAudioSectionData : public FMovieSceneExportSectionData`  
_L71-76_
- inherits: `FMovieSceneExportSectionData`
- L73 _public member_ `int32 NumChannels;`
- L74 _public member_ `int32 Depth;`
- L75 _public member_ `int32 SampleRate;`

#### struct `FMovieSceneExportCinematicTrackData`  
`struct FMovieSceneExportCinematicTrackData`  
_L78-83_
- L81 _public member_ `int32 RowIndex;` — This indicates the sub-track's row index in the track
- L82 _public member_ `TArray< TSharedPtr<FMovieSceneExportCinematicSectionData> > CinematicSections;`

#### struct `FMovieSceneExportAudioTrackData`  
`struct FMovieSceneExportAudioTrackData`  
_L85-92_
- L87 _public member_ `int32 SampleRate;`
- L90 _public member_ `int32 RowIndex;` — This indicates the sub-track's row index in the track
- L91 _public member_ `TArray< TSharedPtr<FMovieSceneExportAudioSectionData> > AudioSections;`

#### struct `FMovieSceneExportTrackData`  
`struct FMovieSceneExportTrackData`  
_L94-97_
- L96 _public member_ `const UMovieSceneTrack* MovieSceneTrack;`

#### struct `FMovieSceneExportAudioData`  
`struct FMovieSceneExportAudioData : public FMovieSceneExportTrackData`  
_L99-109_
- inherits: `FMovieSceneExportTrackData`
- L101 _public member_ `int32 SampleRate;`
- L104 _public member_ `TArray< TSharedPtr<FMovieSceneExportAudioSectionData> > AudioSections;` — Array of all sections in order they appear in UMovieSceneAudioTrack
- L107 _public member_ `TArray< TSharedPtr<FMovieSceneExportAudioTrackData> > AudioTracks;` — Array of sorted audio sub tracks, containing pointers to sections within the sub track row

#### struct `FMovieSceneExportCinematicData`  
`struct FMovieSceneExportCinematicData : public FMovieSceneExportTrackData`  
_L111-118_
- inherits: `FMovieSceneExportTrackData`
- L114 _public member_ `TArray< TSharedPtr<FMovieSceneExportCinematicSectionData> > CinematicSections;` — Array of all sections in order they appear in UMovieSceneCinematicTrack
- L117 _public member_ `TArray< TSharedPtr<FMovieSceneExportCinematicTrackData> > CinematicTracks;` — Array of sorted movie sub tracks, containing pointers to sections within the sub track row

#### struct `FMovieSceneExportMovieSceneData`  
`struct FMovieSceneExportMovieSceneData`  
_L120-131_
- L122 _public member_ `FString Name;`
- L123 _public member_ `FString Path;`
- L124 _public member_ `FFrameRate TickResolution;`
- L125 _public member_ `int32 Duration;`
- L126 _public member_ `FFrameNumber PlaybackRangeStartFrame;`
- L127 _public member_ `FFrameNumber PlaybackRangeEndFrame;`
- L128 _public member_ `TSharedPtr<FMovieSceneExportCinematicData> CinematicData;`
- L129 _public member_ `TArray< TSharedPtr<FMovieSceneExportAudioData> > AudioData;`
- L130 _public member_ `FString MovieExtension;`

#### enum `EMovieSceneTranslatorSectionType`  
`enum class EMovieSceneTranslatorSectionType : int32`  
_L133-137_
- L135 _public enumerator_ `Cinematic = 0`
- L136 _public enumerator_ `Audio = 1`

#### class `FMovieSceneExportData`  
`class FMovieSceneExportData : public TSharedFromThis<FMovieSceneExportData>`  
_L142-226_
- inherits: `TSharedFromThis<FMovieSceneExportData>`
- desc: The FMovieSceneExportData class aggregates intermediate data from Sequencer classes to be used for timeline exports
- L146 _public prototype_ `FMovieSceneExportData(const UMovieScene* InMovieScene, FFrameRate InFrameRate, uint32 InResX, uint32 InResY, int32 InHandleFrames, FString InSaveFilename, TSharedPtr<FMovieSceneTranslatorContext> InContext, FString InMovieExtension);` — Constructor
- L148 _public prototype_ `FMovieSceneExportData();` — Default constructor, necessary for shared ref - should not be used
- L150 _public prototype_ `~FMovieSceneExportData();` — Destructor
- L153 _public prototype_ `FString GetFilename() const;` — Gets export filename
- L155 _public prototype_ `FString GetFilenamePath() const;` — Gets export filename with full path
- L157 _public prototype_ `FString GetMovieExtension() const;` — Gets the shot movie extension
- L160 _public prototype_ `FFrameRate GetFrameRate() const;` — Gets export frame rate
- L162 _public prototype_ `uint32 GetResX() const;` — Gets x resolution
- L164 _public prototype_ `uint32 GetResY() const;` — Gets y resolution
- L166 _public prototype_ `bool GetFrameRateIsNTSC() const;` — Returns true if frame rate is a non-integral frame rate
- L168 _public prototype_ `uint32 GetNearestWholeFrameRate() const;` — Returns the nearest integral frame rate
- L171 _public prototype_ `int32 GetHandleFrames() const;` — Gets the frame handle
- L173 _public prototype_ `int32 GetDefaultAudioSampleRate() const;` — Gets default audio sample rate
- L175 _public prototype_ `int32 GetDefaultAudioDepth() const;` — Gets default audio depth
- L178 _public prototype_ `bool IsExportDataValid() const;` — True when the export data was successfully constructed.
- L181 _public prototype_ `bool FindAudioSections(const FString& InSoundPathName, TArray<TSharedPtr<FMovieSceneExportAudioSectionData>>& OutFoundSections) const;` — Find audio sections
- L186 _private prototype_ `bool ConstructData(const UMovieScene* InMovieScene);` — Entry point for creating the intermediate data to use when exporting.
- L188 _private prototype_ `bool ConstructMovieSceneData(const UMovieScene* InMovieScene);` — Loads intermediate movie scene data from Sequencer.
- L190 _private prototype_ `bool ConstructCinematicData(const UMovieScene* InMovieScene, const UMovieSceneCinematicShotTrack* InCinematicTrack);` — Loads intermediate cinematic data from Sequencer.
- L192 _private prototype_ `bool ConstructCinematicTrackData(const UMovieScene* InMovieScene, TSharedPtr<FMovieSceneExportCinematicData> InCinematicData, int32 InRowIndex);` — Loads intermediate cinematic data from Sequencer.
- L194 _private prototype_ `bool ConstructAudioData(const UMovieScene* InMovieScene, const UMovieSceneAudioTrack* InAudioTrack, TMap<int32, TSharedPtr<FMovieSceneExportAudioData>>& InAudioDataMap);` — Loads intermediate audio data from Sequencer.
- L196 _private prototype_ `bool ConstructAudioData(const UMovieScene* InMovieScene, TSharedPtr<FMovieSceneExportAudioData> InAudioData, int32 InRowIndex);` — Loads intermediate audio data from Sequencer.
- L198 _private prototype_ `bool ConstructCinematicSectionData(const UMovieScene* InMovieScene, TSharedPtr<FMovieSceneExportCinematicData> InCinematicData, const UMovieSceneCinematicShotSection* InCinematicSection);` — Loads intermediate cinematic section data from Sequencer.
- L200 _private prototype_ `bool ConstructAudioSectionData(const UMovieScene* InMovieScene, TSharedPtr<FMovieSceneExportAudioData> InAudioData, const UMovieSceneAudioSection* InAudioSection);` — Loads intermediate audio section data from Sequencer.
- L202 _private prototype_ `bool ConstructSectionData(const UMovieScene* InMovieScene, TSharedPtr<FMovieSceneExportSectionData> InSectionData, const UMovieSceneSection* InSection, EMovieSceneTranslatorSectionType InSectionType, const FString& InSectionDisplayName);` — Loads intermediate common section data from Sequencer.
- L205 _private member_ `TSharedPtr<FMovieSceneTranslatorContext> ExportContext;` — Context for messages
- L210 _public member_ `TSharedPtr<FMovieSceneExportMovieSceneData> MovieSceneData;` — Intermediate data loaded from Sequencer to be used for export
- L214 _private member_ `FFrameRate FrameRate;`
- L215 _private member_ `uint32 ResX;`
- L216 _private member_ `uint32 ResY;`
- L217 _private member_ `int32 HandleFrames;`
- L218 _private member_ `FString SaveFilename;`
- L219 _private member_ `FString SaveFilenamePath;`
- L220 _private member_ `bool bExportDataIsValid;`
- L221 _private member_ `int32 DefaultAudioSampleRate;`
- L222 _private member_ `int32 DefaultAudioDepth;`
- L223 _private member_ `FString MovieExtension;`
- L225 _private member_ `TMap<FString, int32> DuplicateShotNameCounts;`

#### struct `FMovieSceneImportCinematicSectionData`  
`struct FMovieSceneImportCinematicSectionData`  
_L228-231_
- L230 _public member_ `UMovieSceneCinematicShotSection* CinematicSection;`

#### struct `FMovieSceneImportAudioSectionData`  
`struct FMovieSceneImportAudioSectionData`  
_L233-238_
- L235 _public member_ `UMovieSceneAudioSection* AudioSection;`
- L236 _public member_ `FString SourceFilename;`
- L237 _public member_ `FString SourceFilePath;`

#### struct `FMovieSceneImportCinematicTrackData`  
`struct FMovieSceneImportCinematicTrackData`  
_L240-244_
- L242 _public member_ `int32 RowIndex;`
- L243 _public member_ `TArray< TSharedPtr<FMovieSceneImportCinematicSectionData> > CinematicSections;`

#### struct `FMovieSceneImportAudioTrackData`  
`struct FMovieSceneImportAudioTrackData`  
_L246-250_
- L248 _public member_ `int32 RowIndex;`
- L249 _public member_ `TArray< TSharedPtr<FMovieSceneImportAudioSectionData> > AudioSections;`

#### struct `FMovieSceneImportTrackData`  
`struct FMovieSceneImportTrackData`  
_L252-255_
- L254 _public member_ `UMovieSceneTrack* MovieSceneTrack;`

#### struct `FMovieSceneImportAudioData`  
`struct FMovieSceneImportAudioData : public FMovieSceneImportTrackData`  
_L257-267_
- inherits: `FMovieSceneImportTrackData`
- L260 _public member_ `TArray< TSharedPtr<FMovieSceneImportAudioSectionData> > AudioSections;` — Array of all sections in order they appear in UMovieSceneAudioTrack
- L263 _public member_ `TArray< TSharedPtr<FMovieSceneImportAudioTrackData> > AudioTracks;` — Array of sorted audio sub tracks, containing pointers to sections within the sub track row
- L266 _public member_ `int32 MaxRowIndex;` — Max row index existing in this track

#### struct `FMovieSceneImportCinematicData`  
`struct FMovieSceneImportCinematicData : public FMovieSceneImportTrackData`  
_L269-276_
- inherits: `FMovieSceneImportTrackData`
- L272 _public member_ `TArray< TSharedPtr<FMovieSceneImportCinematicSectionData> > CinematicSections;` — Array of all sections in order they appear in UMovieSceneCinematicTrack
- L275 _public member_ `TArray< TSharedPtr<FMovieSceneImportCinematicTrackData> > CinematicTracks;` — Array of sorted movie sub tracks, containing pointers to sections within the sub track row

#### struct `FMovieSceneImportMovieSceneData`  
`struct FMovieSceneImportMovieSceneData`  
_L278-283_
- L280 _public member_ `UMovieScene* MovieScene;`
- L281 _public member_ `TSharedPtr<FMovieSceneImportCinematicData> CinematicData;`
- L282 _public member_ `TArray< TSharedPtr<FMovieSceneImportAudioData> > AudioData;`

#### class `FMovieSceneImportData`  
`class FMovieSceneImportData : public TSharedFromThis<FMovieSceneImportData>`  
_L288-345_
- inherits: `TSharedFromThis<FMovieSceneImportData>`
- desc: The FMovieSceneImportData class aggregates intermediate data from Sequencer classes to be used for timeline imports
- L292 _public prototype_ `FMovieSceneImportData(UMovieScene* InMovieScene, TSharedPtr<FMovieSceneTranslatorContext> InContext);` — Constructor
- L294 _public prototype_ `FMovieSceneImportData();` — Default constructor, necessary for shared ref - should not be used
- L296 _public prototype_ `~FMovieSceneImportData();` — Destructor
- L299 _public prototype_ `bool IsImportDataValid() const;` — True when the export data was successfully constructed.
- L302 _public prototype_ `TSharedPtr<FMovieSceneImportCinematicData> GetCinematicData(bool CreateTrackIfNull);` — Returns the cinematic data pointer or nullptr if one does not exist
- L304 _public prototype_ `TSharedPtr<FMovieSceneImportCinematicSectionData> FindCinematicSection(const FString& InSectionPathName);` — Find cinematic section
- L306 _public prototype_ `TSharedPtr<FMovieSceneImportCinematicSectionData> CreateCinematicSection(FString InName, int32 InRow, FFrameRate InFrameRate, FFrameNumber InStartFrame, FFrameNumber InEndFrame, FFrameNumber InStartOffsetFrame);` — Create cinematic section
- L308 _public prototype_ `bool SetCinematicSection(TSharedPtr<FMovieSceneImportCinematicSectionData> InSection, int32 InRow, FFrameRate InFrameRate, FFrameNumber InStartFrame, FFrameNumber InEndFrame, TOptional<FFrameNumber> InStartOffsetFrame);` — Set cinematic section
- L311 _public prototype_ `TSharedPtr<FMovieSceneImportAudioData> GetAudioData();` — Returns the audio data pointer or nullptr if one does not exist
- L313 _public prototype_ `TSharedPtr<FMovieSceneImportAudioSectionData> FindAudioSection(const FString& InSectionPathName, TSharedPtr<FMovieSceneImportAudioData>& OutAudioData);` — Find audio sections
- L315 _public prototype_ `TSharedPtr<FMovieSceneImportAudioSectionData> CreateAudioSection(FString InFilenameOrAssetPathName, bool bIsPathName, TSharedPtr<FMovieSceneImportAudioData> InAudioData, int32 InRow, FFrameRate InFrameRate, FFrameNumber InStartFrame, FFrameNumber InEndFrame, FFrameNumber InStartOffsetFrame);` — Create audio section
- L317 _public prototype_ `bool SetAudioSection(TSharedPtr<FMovieSceneImportAudioSectionData> InSection, int32 InRow, FFrameRate InFrameRate, FFrameNumber InStartFrame, FFrameNumber InEndFrame, FFrameNumber InStartOffsetFrame);` — Set audio section
- L319 _public prototype_ `bool MoveAudioSection(TSharedPtr<FMovieSceneImportAudioSectionData> InAudioSectionData, TSharedPtr<FMovieSceneImportAudioData> InFromAudioData, TSharedPtr<FMovieSceneImportAudioData> InToAudioData, int32 InToRowIndex);` — Move audio section
- L324 _private prototype_ `TSharedPtr<FMovieSceneImportMovieSceneData> ConstructMovieSceneData(UMovieScene* InMovieScene);` — Entry point for setting up intermediate data for use when importing.
- L326 _private prototype_ `TSharedPtr<FMovieSceneImportCinematicData> ConstructCinematicData(UMovieSceneCinematicShotTrack* InCinematicTrack);` — Gets cinematic data from Sequencer.
- L328 _private prototype_ `TSharedPtr<FMovieSceneImportCinematicTrackData> ConstructCinematicTrackData(UMovieSceneCinematicShotTrack* InCinematicTrack, int32 InRowIndex);` — Gets cinematic track data from Sequencer.
- L330 _private prototype_ `TSharedPtr<FMovieSceneImportAudioData> ConstructAudioData(UMovieSceneAudioTrack* InAudioTrack);` — Gets audio data from Sequencer.
- L332 _private prototype_ `TSharedPtr<FMovieSceneImportAudioTrackData> ConstructAudioTrackData(UMovieSceneAudioTrack* InAudioTrack, int32 InRowIndex);` — Gets audio track data from Sequencer.
- L334 _private prototype_ `TSharedPtr<FMovieSceneImportCinematicSectionData> ConstructCinematicSectionData(UMovieSceneCinematicShotSection* InCinematicSection);` — Gets cinematic section data from Sequencer.
- L336 _private prototype_ `TSharedPtr<FMovieSceneImportAudioSectionData> ConstructAudioSectionData(UMovieSceneAudioSection* InAudioSection);` — Gets audio section data from Sequencer.
- L339 _private member_ `TSharedPtr<FMovieSceneTranslatorContext> ImportContext;` — Context for messages
- L344 _public member_ `TSharedPtr<FMovieSceneImportMovieSceneData> MovieSceneData;` — Intermediate data loaded from Sequencer to be used for export

#### class `FMovieSceneTranslator`  
`class FMovieSceneTranslator`  
_L348-358_
- desc: Abstract base class for importer/exporter
- L351 _public function_ `FMovieSceneTranslator()`
- L352 _public prototype_ `virtual ~FMovieSceneTranslator() = default;`
- L355 _public prototype_ `virtual FName GetMessageLogWindowTitle() const = 0;` — Error log window title.
- L357 _public prototype_ `virtual FText GetMessageLogLabel() const = 0;` — Error log list label.

#### class `FMovieSceneImporter`  
`class FMovieSceneImporter : public FMovieSceneTranslator`  
_L361-386_
- inherits: `FMovieSceneTranslator`
- desc: Abstract base class for movie scene importers
- L364 _public function_ `FMovieSceneImporter() : FMovieSceneTranslator()`
- L366 _public prototype_ `virtual ~FMovieSceneImporter() = default;`
- L369 _public prototype_ `virtual FText GetFileTypeDescription() const = 0;` — Format description.
- L371 _public prototype_ `virtual FText GetDialogTitle() const = 0;` — Import window title.
- L373 _public prototype_ `virtual FText GetTransactionDescription() const = 0;` — Scoped transaction description.
- L385 _public prototype_ `virtual bool Import(UMovieScene* InMovieScene, FFrameRate InFrameRate, FString InFilename, TSharedRef<FMovieSceneTranslatorContext> InContext) = 0;` — Import movie scene @param InMovieScene The movie scene to import the XML file into @param InFrameRate The frame rate to import the XML at @param InFilename The filename to import @param OutError The return error message @return Whether the import was successful

#### class `FMovieSceneExporter`  
`class FMovieSceneExporter : public FMovieSceneTranslator`  
_L389-425_
- inherits: `FMovieSceneTranslator`
- desc: Abstract base class for movie scene exporters
- L392 _public function_ `FMovieSceneExporter() : FMovieSceneTranslator()`
- L394 _public prototype_ `virtual ~FMovieSceneExporter() = default;`
- L397 _public prototype_ `virtual FText GetFileTypeDescription() const = 0;` — Format description.
- L399 _public prototype_ `virtual FText GetDialogTitle() const = 0;` — Export dialog window title.
- L401 _public prototype_ `virtual FText GetDefaultFileExtension() const = 0;` — Default format file extension.
- L403 _public prototype_ `virtual FText GetNotificationExportFinished() const = 0;` — Notification when export completes.
- L405 _public prototype_ `virtual FText GetNotificationHyperlinkText() const = 0;` — Notification hyperlink to exported file path.
- L424 _public prototype_ `virtual bool Export(const UMovieScene* InMovieScene, FString InFilenameFormat, FFrameRate InFrameRate, uint32 InResX, uint32 InResY, int32 InHandleFrames, FString InSaveFilename, TSharedRef<FMovieSceneTranslatorContext> InContext, FString InMovieExtension, const FMovieSceneExportMetadata* InMetadata=nullptr) = 0;` — Export movie scene @param InMovieScene The movie scene with the cinematic shot track and audio tracks to export @param InFilenameFormat The specified filename format. @param InFrameRate The frame rate for export. @param InResX Sequence resolution x. @param InResY Sequence resolution y. @param InHandleFrames The number of handle frames to include for each shot. @param InSaveFilename The file path to save to. @param OutError The return error message @param MovieExtension The movie extension for the shot filenames (ie. .avi, .mov, .mp4) @param InMetadata (optional) Metadata from export to override movie output file list @return Whether the export was successful

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API MOVIESCENETOOLS_API`

### `Source/Editor/MovieSceneTools/Public/MovieSceneTranslatorEDL.h` (Public)


#### class `MovieSceneTranslatorEDL`  
`class MovieSceneTranslatorEDL`  
_L13-38_
- L25 _public prototype_ `static bool ImportEDL(UMovieScene* InMovieScene, FFrameRate InFrameRate, FString InFilename);` — Import EDL @param InMovieScene The movie scene to import the edl into @param InFrameRate The frame rate to import the EDL at @param InFilename The filename to import @return Whether the import was successful
- L37 _public prototype_ `static bool ExportEDL(const UMovieScene* InMovieScene, FFrameRate InFrameRate, FString InSaveFilename, int32 InHandleFrames, FString InMovieExtension);` — Export EDL @param InMovieScene The movie scene with the cinematic shot track and audio tracks to export @param InFrameRate The frame rate to export the EDL at @param InSaveFilename The file path to save to. @param InHandleFrames The number of handle frames to include for each shot. @param MovieExtension The movie extension for the shot filenames (ie. .avi, .mov, .mp4) @return Whether the export was successful

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API MOVIESCENETOOLS_API`

### `Source/Editor/MovieSceneTools/Public/ObjectBindingTagCache.h` (Public)


#### class `FObjectBindingTagCache`  
`class FObjectBindingTagCache`  
_L22-76_
- desc: Owned by an FSequencer instance, this class tracks tags for object bindings, and maintains a reverse lookup map from binding to tag(s) along with other information for the tags such as color tints.
- L26 _public typedef_ `using TagIterator = TMultiMap<UE::MovieScene::FFixedObjectBindingID, FName>::TConstKeyIterator;`
- L28 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnUpdated, const FObjectBindingTagCache*);`
- L31 _public member_ `FOnUpdated OnUpdatedEvent;` — Public event that is broadcast when this cache changes in some way
- L36 _public prototype_ `void ConditionalUpdate(UMovieSceneSequence* RootSequence);` — Conditionally update this cache based on the state of the specified root sequence
- L42 _public function_ `FLinearColor GetTagColor(const FName& TagName) const` — Retrieve a color for the specified tag name
- L52 _public function_ `bool HasTag(const UE::MovieScene::FFixedObjectBindingID& BindingID, const FName& TagName) const` — Check whether the specified binding ID has the specified tag
- L61 _public function_ `TagIterator IterateTags(const UE::MovieScene::FFixedObjectBindingID& BindingID) const` — Iterate all the tags for the specified binding ID
- L69 _private member_ `TSortedMap<FName, FLinearColor, FDefaultAllocator, FNameFastLess> ExposedNameColors;` — Sorted map of colors by tag name
- L72 _private member_ `FGuid RootSequenceSignature;` — The signature of the root sequence last time we were updated
- L75 _private member_ `TMultiMap<UE::MovieScene::FFixedObjectBindingID, FName> ExposedNameReverseLUT;` — Multi map (1->many) of a binding ID to any tags that are associated with it

#### Free symbols / members of external scopes

- L28 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnUpdated, const FObjectBindingTagCache*);`

### `Source/Editor/MovieSceneTools/Public/PropertyTrackEditor.h` (Public)


#### class `FPropertyTrackEditor`  
`template<typename TrackType> class FPropertyTrackEditor : public FKeyframeTrackEditor<TrackType>`  
_L25-288_
- inherits: `FKeyframeTrackEditor<TrackType>`
- desc: Tools for animatable property types such as floats ands vectors
- L34 _public function_ `FPropertyTrackEditor( TSharedRef<ISequencer> InSequencer ) : FKeyframeTrackEditor<TrackType>( InSequencer )` — Constructor @param InSequencer The sequencer instance to be used by this tool
- L44 _public function_ `FPropertyTrackEditor( TSharedRef<ISequencer> InSequencer, TArrayView<const FAnimatedPropertyKey> InWatchedPropertyTypes ) : FKeyframeTrackEditor<TrackType>( InSequencer )` — Constructor @param InSequencer The sequencer instance to be used by this tool @param InWatchedPropertyTypes A list of property types that this editor can animate
- L53 _public function_ `~FPropertyTrackEditor()`
- L70 _public function_ `virtual FText GetDisplayName() const override`
- L75 _public function_ `virtual bool SupportsSequence(UMovieSceneSequence* InSequence) const override`
- L80 _public function_ `virtual bool SupportsType( TSubclassOf<UMovieSceneTrack> Type ) const override`
- L93 _protected prototype_ `virtual void GenerateKeysFromPropertyChanged( const FPropertyChangedParams& PropertyChangedParams, UMovieSceneSection* SectionToKey, FGeneratedTrackKeys& OutGeneratedKeys ) = 0;` — Generates keys based on the new value from the property property change parameters. @param PropertyChangedParams Parameters associated with the property change. @param OutGeneratedKeys Array of keys that are generated from the changed property
- L97 _protected function_ `virtual bool ForCustomizedUseOnly()` — When true, this track editor will only be used on properties which have specified it as a custom track class. This is necessary to prevent duplicate property change handling in cases where a custom track editor handles the same type of data as one of the standard track editors.
- L104 _protected function_ `virtual void InitializeNewTrack( TrackType* NewTrack, FPropertyChangedParams PropertyChangedParams )` — Initialized values on a track after it's been created, but before any sections or keys have been added. @param NewTrack The newly created track. @param PropertyChangedParams The property change parameters which caused this track to be created.
- L161 _protected function_ `virtual UMovieSceneTrack* AddTrack(UMovieScene* FocusedMovieScene, const FGuid& ObjectHandle, TSubclassOf<class UMovieSceneTrack> TrackClass, FName UniqueTypeName) override`
- L170 _protected function_ `void AddWatchedProperty( FAnimatedPropertyKey PropertyKey )` — Adds a callback for property changes for the supplied property type name.
- L182 _protected function_ `virtual void OnAnimatedPropertyChanged( const FPropertyChangedParams& PropertyChangedParams )` — Called by the details panel when an animatable property changes @param InObjectsThatChanged	List of objects that changed @param KeyPropertyParams		Parameters for the property change.
- L190 _private function_ `void AddWatchedPropertyType( FName WatchedPropertyTypeName )` — Adds a callback for property changes for the supplied property type name.
- L199 _private function_ `FPropertyPath BuildNamingPropertyPath(const FPropertyPath& InPropertyPath)` — Builds a property path that omits properties that are "insignificant" for computing track names. IMPORTANT: the result path is only for looking up names, and is non functional!
- L218 _private function_ `TSubclassOf<UMovieSceneTrack> GetCustomizedTrackClass( const FProperty* Property )` — Get a customized track class from the property if there is one, otherwise return nullptr.
- L235 _private function_ `FKeyPropertyResult OnKeyProperty( FFrameNumber KeyTime, FPropertyChangedParams PropertyChangedParams )` — Adds a key based on a property change.
- L287 _private member_ `TArray<FAnimatedPropertyKey> WatchedProperties;` — An array of property type names which are being watched for changes.

#### Free symbols / members of external scopes

- L19 _macro_ `#define LOCTEXT_NAMESPACE "PropertyTrackEditor"`
- L264 _function_ `` (scope `FPropertyTrackEditor::OnKeyProperty`)
- L274 _function_ `PropertyChangedParams.KeyMode, TrackClass, UniqueName, [&](TrackType* NewTrack)` (scope `FPropertyTrackEditor::OnKeyProperty`)

### `Source/Editor/MovieSceneTools/Public/SKeyEditInterface.h` (Public)


#### struct `FKeyEditData`  
`struct FKeyEditData`  
_L21-27_
- L23 _public member_ `TSharedPtr<FStructOnScope> KeyStruct;`
- L24 _public member_ `TWeakObjectPtr<UMovieSceneSection> OwningSection;`
- L26 _public member_ `TWeakObjectPtr<UObject> OwningObject;` — Channel's actual owning UObject (e.g. a decoration). Falls back to OwningSection for section-owned channels.

#### class `SKeyEditInterface`  
`class SKeyEditInterface : public SCompoundWidget, public FEditorUndoClient, public FNotifyHook`  
_L32-78_
- inherits: `SCompoundWidget,FEditorUndoClient,FNotifyHook`
- desc: Widget that represents a details panel that refreshes on undo, and handles modification of the section on edit
- L35 _public function_ `SLATE_BEGIN_ARGS(SKeyEditInterface)`
- L36 _public prototype_ `SLATE_ATTRIBUTE(FKeyEditData, EditData) SLATE_END_ARGS() ~SKeyEditInterface();`
- L41 _public prototype_ `void Construct(const FArguments& InArgs, TSharedRef<ISequencer> InSequencer);`
- L46 _public prototype_ `void Initialize();` — (Re)Initialize this widget's details panel
- L53 _private prototype_ `TSharedRef<IPropertyTypeCustomization> CreateBindingIDCustomization();` — Create a binding ID customization for the details panel
- L54 _private prototype_ `TSharedRef<IPropertyTypeCustomization> CreateEventCustomization();`
- L59 _private prototype_ `void OnFinishedChangingProperties(const FPropertyChangedEvent& ChangeEvent, TSharedPtr<FStructOnScope> KeyStruct);` — Called when a property has been changed on the UI
- L63 _private prototype_ `virtual FVector2D ComputeDesiredSize(float LayoutScaleMultiplier) const override;`
- L65 _private prototype_ `void ModifySectionAndOwner();`
- L67 _private prototype_ `virtual void NotifyPreChange(FProperty* PropertyAboutToChange) override;`
- L68 _private prototype_ `virtual void NotifyPostChange(const FPropertyChangedEvent& PropertyChangedEvent, class FEditPropertyChain* PropertyThatChanged) override;`
- L69 _private prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L70 _private prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L73 _private member_ `TAttribute<FKeyEditData> EditDataAttribute;`
- L74 _private member_ `TWeakObjectPtr<UMovieSceneSection> WeakSection;`
- L75 _private member_ `TWeakObjectPtr<UObject> WeakOwningObject;`
- L76 _private member_ `TWeakPtr<ISequencer> WeakSequencer;`
- L77 _private member_ `TSharedPtr<IStructureDetailsView> StructureDetailsView;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MOVIESCENETOOLS_API`

### `Source/Editor/MovieSceneTools/Public/SObjectBindingTag.h` (Public)


#### class `SObjectBindingTags`  
`class SObjectBindingTags : public SCompoundWidget`  
_L24-53_
- inherits: `SCompoundWidget`
- desc: A horizontally grouped collection of tags that apply to a single object binding. This widget automatically updates when the tags for a binding change.
- L29 _public function_ `DECLARE_DELEGATE_OneParam(FTagEvent, FName) SLATE_BEGIN_ARGS(SObjectBindingTags)` — A simple delegate that is passed the tag name applicable to the operation
- L34 _public prototype_ `SLATE_EVENT(FTagEvent, OnTagDeleted) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const UE::MovieScene::FFixedObjectBindingID& InBindingID, FObjectBindingTagCache* BindingCache);` — (Optional) When bound, will show a delete button on the tags, and call this delegate when clicked
- L44 _private prototype_ `void OnBindingCacheUpdated(const FObjectBindingTagCache* BindingCache);` — Called when the binding tag cache that holds information about the binding's tags changes
- L47 _private prototype_ `void OnTagDeleted(FName TagName);` — Called when a tag is to be deleted
- L51 _private member_ `FTagEvent OnTagDeletedEvent;`
- L52 _private member_ `UE::MovieScene::FFixedObjectBindingID BindingID;`

#### class `SObjectBindingTag`  
`class SObjectBindingTag : public SCompoundWidget`  
_L56-111_
- inherits: `SCompoundWidget`
- desc: A single named tag widget for an object binding within a sequence, represented as a rounded 'pill'
- L60 _public function_ `DECLARE_DELEGATE_OneParam(FOnCreateNew, FName) SLATE_BEGIN_ARGS(SObjectBindingTag) : _ColorTint(FLinearColor::White)`
- L65 _public prototype_ `SLATE_EVENT(FSimpleDelegate, OnDeleted) SLATE_EVENT(FOnCreateNew, OnCreateNew) SLATE_EVENT(FSimpleDelegate, OnClicked) SLATE_ATTRIBUTE(FText, Text) SLATE_ATTRIBUTE(FText, ToolTipText) SLATE_ATTRIBUTE(FSlateColor, ColorTint) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — (Optional) When bound, shows a small delete button on the tag that invokes this delegate when clicked
- L91 _private prototype_ `void OnNewTextCommitted(const FText& InNewText, ETextCommit::Type CommitType);`
- L93 _private prototype_ `FReply HandleCreateButtonClicked();`
- L95 _private prototype_ `FReply HandleDeleteButtonClicked();`
- L97 _private prototype_ `FReply HandlePillClicked();`
- L99 _private function_ `virtual FVector2D ComputeDesiredSize(float LayoutScaleMultiplier) const override`
- L106 _private member_ `FOnCreateNew OnCreateNew;`
- L107 _private member_ `FSimpleDelegate OnDeleted;`
- L108 _private member_ `FSimpleDelegate OnClicked;`
- L110 _private member_ `TSharedPtr<SEditableTextBox> EditableText;`

#### Free symbols / members of external scopes

- L29 _delegate_ `DECLARE_DELEGATE_OneParam(FTagEvent, FName) SLATE_BEGIN_ARGS(SObjectBindingTags){} SLATE_EVENT(FTagEvent, OnTagDeleted) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const UE::MovieScene::FFixedObjectBindingID& InBindingID, FObjectBindingTagCache* BindingCache);` — A simple delegate that is passed the tag name applicable to the operation
- L60 _delegate_ `DECLARE_DELEGATE_OneParam(FOnCreateNew, FName) SLATE_BEGIN_ARGS(SObjectBindingTag) : _ColorTint(FLinearColor::White) {} SLATE_EVENT(FSimpleDelegate, OnDeleted) SLATE_EVENT(FOnCreateNew, OnCreateNew) SLATE_EVENT(FSimpleDelegate, OnClicked) SLATE_ATTRIBUTE(FText, Text) SLATE_ATTRIBUTE(FText, ToolTipText) SLATE_ATTRIBUTE(FSlateColor, ColorTint) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`

### `Source/Editor/MovieSceneTools/Public/Sections/BoolPropertySection.h` (Public)


#### class `FBoolPropertySection`  
`class FBoolPropertySection : public FSequencerSection`  
_L14-32_
- inherits: `FSequencerSection`
- desc: An implementation of bool sections.
- L25 _public function_ `FBoolPropertySection(UMovieSceneSection& InSectionObject) : FSequencerSection(InSectionObject)` — Creates a new bool section for editing bool sections. @param InSectionObject The section object which is being displayed and edited. @param InDisplayName A display name for the section being displayed and edited.
- L31 _public prototype_ `virtual int32 OnPaintSection(FSequencerSectionPainter& Painter) const override;`

### `Source/Editor/MovieSceneTools/Public/Sections/ColorPropertySection.h` (Public)


#### class `FColorPropertySection`  
`class FColorPropertySection : public FSequencerSection`  
_L23-55_
- inherits: `FSequencerSection`
- desc: A color section implementation
- L35 _public prototype_ `FColorPropertySection(UMovieSceneSection& InSectionObject, const FGuid& InObjectBindingID, TWeakPtr<ISequencer> InSequencer);` — Creates a new color property section. @param InSectionObject The section object which is being displayed and edited. @param InObjectBindingID The ID of the object this section is bound to @param InSequencer The sequencer this section is for
- L39 _private prototype_ `virtual FReply OnKeyDoubleClicked(const TArray<FKeyHandle>& KeyHandles ) override;`
- L40 _private prototype_ `virtual int32 OnPaintSection(FSequencerSectionPainter& Painter) const override;`
- L43 _private prototype_ `FLinearColor GetPropertyValueAsLinearColor() const;` — Get the current value of the object's property as a linear color
- L48 _private member_ `FGuid ObjectBindingID;` — The bound objects ID
- L51 _private member_ `TWeakPtr<ISequencer> WeakSequencer;` — Weak pointer to the sequencer this section is for
- L54 _private member_ `mutable TOptional<FTrackInstancePropertyBindings> PropertyBindings;` — Property bindings used for retrieving object properties

### `Source/Editor/MovieSceneTools/Public/Sections/EventSectionHelper.h` (Public)


#### class `FEventSectionHelper`  
`class FEventSectionHelper`  
_L16-30_
- desc: Helper class for event section interfaces.
- L21 _public prototype_ `static void PaintEventName( FSequencerSectionPainter& Painter, int32 LayerId, const FString& EventString, float PixelPosition, bool bIsEventValid = true);` — Paints an event name.
- L29 _public prototype_ `static bool IsSectionSelected(TSharedRef<ISequencer> Sequencer, UMovieSceneSection* InSection);` — Returns whether the given section is selected.

### `Source/Editor/MovieSceneTools/Public/Sections/ThumbnailSection.h` (Public)


#### struct `FThumbnailCameraSettings`  
`struct FThumbnailCameraSettings`  
_L22-25_
- L24 _public member_ `float AspectRatio;`

#### class `FThumbnailSection`  
`class FThumbnailSection : public ISequencerSection , public TSharedFromThis<FThumbnailSection>`  
_L31-138_
- inherits: `ISequencerSection,TSharedFromThis<FThumbnailSection>`
- desc: Thumbnail section, which paints and ticks the appropriate section.
- L38 _public prototype_ `FThumbnailSection(TSharedPtr<ISequencer> InSequencer, TSharedPtr<FTrackEditorThumbnailPool> InThumbnailPool, IViewportThumbnailClient* InViewportThumbanilClient, UMovieSceneSection& InSection);` — Create and initialize a new instance.
- L39 _public prototype_ `FThumbnailSection(TSharedPtr<ISequencer> InSequencer, TSharedPtr<FTrackEditorThumbnailPool> InThumbnailPool, ICustomThumbnailClient* InCustomThumbnailClient, UMovieSceneSection& InSection);`
- L42 _public prototype_ `~FThumbnailSection();` — Destructor.
- L47 _public function_ `TSharedRef<SWidget> GetSequencerWidget()` — @return The sequencer widget owning the MovieScene section.
- L53 _public prototype_ `void EnterRename();` — Enter rename mode for the section
- L56 _public function_ `virtual bool CanRename() const` — Get whether the text is renameable
- L59 _public function_ `virtual FText HandleThumbnailTextBlockText() const` — Callback for getting the text of the track name text block.
- L62 _public function_ `virtual void HandleThumbnailTextBlockTextCommitted(const FText& NewThumbnailName, ETextCommit::Type CommitType)` — Callback for when the text of the track name text block has changed.
- L67 _public prototype_ `virtual void SetSingleTime(double GlobalTime) = 0;` — Set this thumbnail section to draw a single thumbnail at the specified time
- L73 _public prototype_ `virtual void BuildSectionContextMenu(FMenuBuilder& MenuBuilder, const FGuid& ObjectBinding) override;`
- L74 _public prototype_ `virtual void BuildSectionSidebarMenu(FMenuBuilder& MenuBuilder, const FGuid& ObjectBinding) override;`
- L75 _public prototype_ `virtual TSharedRef<SWidget> GenerateSectionWidget() override;`
- L76 _public prototype_ `virtual float GetSectionGripSize() const override;`
- L77 _public prototype_ `virtual float GetSectionHeight(const UE::Sequencer::FViewDensityInfo& ViewDensity) const override;`
- L78 _public prototype_ `virtual UMovieSceneSection* GetSectionObject() override;`
- L79 _public prototype_ `virtual FText GetSectionTitle() const override;`
- L80 _public prototype_ `virtual int32 OnPaintSection( FSequencerSectionPainter& InPainter ) const override;`
- L81 _public prototype_ `virtual void Tick( const FGeometry& AllottedGeometry, const FGeometry& ParentGeometry, const double InCurrentTime, const float InDeltaTime ) override;`
- L86 _protected prototype_ `void RedrawThumbnails();` — Called to force a redraw of this section's thumbnails
- L89 _protected prototype_ `TRange<double> GetVisibleRange() const;` — Get the range that is currently visible in the section's time space
- L92 _protected prototype_ `TRange<double> GetTotalRange() const;` — Get the total range that thumbnails are to be generated for in the section's time space
- L95 _protected prototype_ `EVisibility GetRenameVisibility() const;` — Get rename visibility
- L98 _protected prototype_ `void OnEnterEditingMode();` — When renaming is started, show the rename widget
- L101 _protected prototype_ `void OnExitEditingMode();` — When renaming is completed, hide the rename widget
- L103 _protected prototype_ `void BuildThumbnailsMenu(FMenuBuilder& InMenuBuilder);`
- L108 _protected member_ `UMovieSceneSection* Section;` — The section we are visualizing.
- L111 _protected member_ `TWeakPtr<ISequencer> SequencerPtr;` — The parent sequencer we are a part of.
- L114 _protected member_ `FTrackEditorThumbnailCache ThumbnailCache;` — A list of all thumbnails this section has.
- L117 _protected member_ `EMovieScenePlayerStatus::Type SavedPlaybackStatus;` — Saved playback status. Used for restoring state when rendering thumbnails
- L120 _protected member_ `TSharedPtr<SInlineEditableTextBlock> NameWidget;` — Rename widget
- L123 _protected member_ `const FSlateBrush* WhiteBrush;` — Fade brush.
- L126 _protected member_ `ESlateDrawEffect AdditionalDrawEffect;` — Additional draw effects
- L135 _protected member_ `ETimeSpace TimeSpace;` — Enumeration value specifyin in which time-space to generate thumbnails
- L137 _protected member_ `FDelegateHandle RedrawThumbnailDelegateHandle;`

#### enum `FThumbnailSection::ETimeSpace`  
`enum class ETimeSpace`  
_L128-132_
- L130 _public enumerator_ `Global`
- L131 _public enumerator_ `Local`

#### class `FViewportThumbnailSection`  
`class FViewportThumbnailSection : public FThumbnailSection , public IViewportThumbnailClient`  
_L143-155_
- inherits: `FThumbnailSection,IViewportThumbnailClient`
- desc: Thumbnail section, which paints and ticks the appropriate section.
- L150 _public prototype_ `FViewportThumbnailSection(TSharedPtr<ISequencer> InSequencer, TSharedPtr<FTrackEditorThumbnailPool> InThumbnailPool, UMovieSceneSection& InSection);` — Create and initialize a new instance.
- L153 _public prototype_ `virtual void PreDraw(FTrackEditorThumbnail& Thumbnail) override;`
- L154 _public prototype_ `virtual void PostDraw(FTrackEditorThumbnail& Thumbnail) override;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MOVIESCENETOOLS_API`

### `Source/Editor/MovieSceneTools/Public/SequenceBindingTree.h` (Public)


#### struct `FSequenceBindingNode`  
`struct FSequenceBindingNode`  
_L23-50_
- desc: Node that represents an object binding, or a sub sequence (where the guid is zero)
- L25 _public function_ `FSequenceBindingNode(FText InDisplayString, const UE::MovieScene::FFixedObjectBindingID& InBindingID, FSlateIcon InIcon) : BindingID(InBindingID) , ParentID(FGuid(), MovieSceneSequenceID::Invalid) , DisplayString(InDisplayString) , Icon(InIcon) , bIsSpawnable(false)`
- L34 _public function_ `void AddChild(TSharedRef<FSequenceBindingNode> Child)` — Add a child
- L41 _public member_ `UE::MovieScene::FFixedObjectBindingID BindingID, ParentID;` — This object's ID, and its parent's
- L41 _public member_ `UE::MovieScene::FFixedObjectBindingID BindingID, ParentID;` — This object's ID, and its parent's
- L43 _public member_ `FText DisplayString;` — The display string that represents this node
- L45 _public member_ `FSlateIcon Icon;` — A representative icon for the node
- L47 _public member_ `bool bIsSpawnable;` — Whether this is a spawnable or not
- L49 _public member_ `TArray<TSharedRef<FSequenceBindingNode>> Children;` — Array holding this node's children

#### struct `FSequenceBindingTree`  
`struct FSequenceBindingTree`  
_L53-120_
- desc: Data structure used internally to represent the bindings of a sequence recursively
- L63 _public prototype_ `bool ConditionalRebuild(UMovieSceneSequence* InSequence, FObjectKey InActiveSequence, FMovieSceneSequenceID InActiveSequenceID);` — Conditionally reconstruct the tree structure from the specified sequence if any of the sequences have changed since the last population @param InSequence			The sequence to generate the tree for @param InActiveSequence		A sequence at which point we can start to generate localally resolving IDs @param InActiveSequenceID	The sequence ID for the above sequence within the root context @retrun True if this tree was rebuilt, false otherwise
- L72 _public prototype_ `void ForceRebuild(UMovieSceneSequence* InSequence, FObjectKey InActiveSequence, FMovieSceneSequenceID InActiveSequenceID);` — Construct the tree structure from the specified sequence. @param InSequence			The sequence to generate the tree for @param InActiveSequence		A sequence at which point we can start to generate localally resolving IDs @param InActiveSequenceID	The sequence ID for the above sequence within the root context
- L75 _public function_ `TSharedRef<FSequenceBindingNode> GetRootNode() const` — Get the root of the tree
- L81 _public function_ `TSharedPtr<FSequenceBindingNode> FindNode(UE::MovieScene::FFixedObjectBindingID BindingID) const` — Find a node in the tree
- L86 _public function_ `bool IsEmpty() const`
- L96 _private prototype_ `static void Sort(TSharedRef<FSequenceBindingNode> Node);` — Recursive sort helper for a sequence binding node
- L99 _private prototype_ `void Build(UMovieSceneSequence* InSequence, FSequenceIDStack& SequenceIDStack);` — Recursive builder function that iterates into sub sequences
- L102 _private prototype_ `TSharedRef<FSequenceBindingNode> EnsureParent(const FGuid& InParentGuid, UMovieScene* InMovieScene, FMovieSceneSequenceID SequenceID);` — Ensure that a parent node exists for the specified object
- L107 _private member_ `FMovieSceneSequenceID ActiveSequenceID;` — The ID of the currently 'active' sequence from which to generate relative IDs
- L109 _private member_ `FObjectKey ActiveSequence;` — The currently 'active' sequence from which to generate relative IDs
- L111 _private member_ `TSharedPtr<FSequenceBindingNode> ActiveSequenceNode;` — The node relating to the currently active sequence ID (if any)
- L113 _private member_ `TSharedPtr<FSequenceBindingNode> TopLevelNode;` — The top level (root) node in the tree
- L115 _private member_ `TMap<UE::MovieScene::FFixedObjectBindingID, TSharedPtr<FSequenceBindingNode>> Hierarchy;` — Map of hierarchical information
- L117 _private member_ `TMap<FObjectKey, FGuid> CachedSequenceSignatures;` — Map of sequence to its signature the last time we were built
- L119 _private member_ `bool bIsEmpty;` — Whether the tree is considered empty

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API MOVIESCENETOOLS_API`

### `Source/Editor/MovieSceneTools/Public/SequencerExportTask.h` (Public)


#### class `USequencerExportTask`  
`class USequencerExportTask : public UAssetExportTask`  
_L15-24_
- reflection: `UCLASS(Transient, BlueprintType)`
- inherits: `UAssetExportTask`
- desc: Contains data for a group of assets to import
- L23 _public member_ `TObjectPtr<UObject> SequencerContext;` — `UPROPERTY(BlueprintReadWrite, Category = Miscellaneous)` — A UWorld for LevelSequences, UUserWidget for WidgetAnimations, or AActor for Actor Sequences, etc...

### `Source/Editor/MovieSceneTools/Public/TrackEditorThumbnail/TrackEditorThumbnail.h` (Public)


#### class `FTrackEditorThumbnail`  
`class FTrackEditorThumbnail : public ISlateViewport , public TSharedFromThis<FTrackEditorThumbnail>`  
_L35-134_
- inherits: `ISlateViewport,TSharedFromThis<FTrackEditorThumbnail>`
- desc: Track Editor Thumbnail, which keeps a Texture to be displayed by a viewport.
- L42 _public prototype_ `FTrackEditorThumbnail(const FOnThumbnailDraw& InOnDraw, const FIntPoint& InDesiredSize, TRange<double> InTimeRange, double InPosition);` — Create and initialize a new instance.
- L45 _public prototype_ `virtual ~FTrackEditorThumbnail();` — Virtual destructor.
- L52 _public prototype_ `void AssignFrom(TSharedRef<FSlateTextureData, ESPMode::ThreadSafe> InTextureData);` — Assign this thumbnail from a slate texture.
- L57 _public prototype_ `void ResizeRenderTarget(const FIntPoint& InSize);` — Ensure that this thumbnail has a render target of the specified size
- L62 _public function_ `FSlateTextureRenderTarget2DResource* GetRenderTarget() const` — Access the (potentially null) render target to be used for rendering onto this thumbnail
- L70 _public function_ `FIntPoint GetDesiredSize() const` — Get the desired size for this thumbnail on the UI
- L76 _public prototype_ `void DrawThumbnail();` — Renders the thumbnail to the texture.
- L79 _public prototype_ `void SetupFade(const TSharedRef<SWidget>& InWidget);` — Prompt this thumbnail to fade in
- L80 _public prototype_ `void PlayFade();`
- L83 _public prototype_ `float GetFadeInCurve() const;` — Gets the curve for fading in the thumbnail.
- L86 _public function_ `const TRange<double> GetTimeRange() const` — Get the full time-range that this thumbnail occupies
- L89 _public function_ `double GetEvalPosition() const` — Get the time at which this thumbnail should be drawn
- L95 _public prototype_ `virtual FIntPoint GetSize() const override;`
- L96 _public prototype_ `virtual FSlateShaderResource* GetViewportRenderTargetTexture() const override;`
- L97 _public prototype_ `virtual bool RequiresVsync() const override;`
- L100 _public prototype_ `void DestroyTexture();` — Destroy the texture on the next tick
- L105 _public member_ `int32 SortOrder;` — Sort order for this thumbnail
- L108 _public member_ `FThreadSafeBool bHasFinishedDrawing;` — True when this thumbnail has been drawn, false otherwise
- L111 _public member_ `bool bIgnoreAlpha;` — True to ignore alpha on this thumbnail
- L116 _private member_ `FOnThumbnailDraw OnDraw;` — Delegate to use to draw the thumbnail.
- L119 _private member_ `FIntPoint DesiredSize;` — The desired size of the thumbnail on the actual UI (Not necessarily the same size as the texture)
- L122 _private member_ `FSlateTexture2DRHIRef* ThumbnailTexture;` — The Texture RHI that holds the thumbnail.
- L124 _private member_ `FSlateTextureRenderTarget2DResource* ThumbnailRenderTarget;` — The texture render target used for 3D rendering on to the texture. May be null.
- L127 _private member_ `TRange<double> TimeRange;` — Where in time this thumbnail is a rendering of.
- L130 _private member_ `double Position;` — The position we should actually render (within the above time range).
- L133 _private member_ `FCurveSequence FadeInCurve;` — Fade curve to display while the thumbnail is redrawing.

#### struct `IViewportThumbnailClient`  
`struct IViewportThumbnailClient`  
_L137-142_
- desc: Client interface for thumbanils that render the current world from a viewport
- L139 _public function_ `virtual UCameraComponent* GetViewCamera()`
- L140 _public function_ `virtual void PreDraw(FTrackEditorThumbnail& TrackEditorThumbnail)`
- L141 _public function_ `virtual void PostDraw(FTrackEditorThumbnail& TrackEditorThumbnail)`

#### struct `ICustomThumbnailClient`  
`struct ICustomThumbnailClient`  
_L145-149_
- desc: Custom thumbnail drawing client interface
- L147 _public function_ `virtual void Setup()`
- L148 _public function_ `virtual void Draw(FTrackEditorThumbnail& TrackEditorThumbnail)`

#### struct `FThumbnailCacheData`  
`struct FThumbnailCacheData`  
_L152-190_
- desc: Cache data
- L154 _public function_ `FThumbnailCacheData() : VisibleRange(0), TimeRange(0), AllottedSize(0,0), DesiredSize(0, 0), Quality(EThumbnailQuality::Normal)`
- L156 _public function_ `bool operator==(const FThumbnailCacheData& RHS) const`
- L167 _public function_ `bool operator!=(const FThumbnailCacheData& RHS) const`
- L179 _public member_ `TRange<double> VisibleRange;` — The visible range of our thumbnails we can see on the UI
- L181 _public member_ `TRange<double> TimeRange;` — The total range to generate thumbnails for
- L183 _public member_ `FIntPoint AllottedSize;` — Physical size of the thumbnail area
- L185 _public member_ `FIntPoint DesiredSize;` — Desired frame size constraint
- L187 _public member_ `EThumbnailQuality Quality;` — Thumbnail quality
- L189 _public member_ `TOptional<double> SingleReferenceFrame;` — Set when we want to render a single reference frame

#### class `FTrackEditorThumbnailCache`  
`class FTrackEditorThumbnailCache`  
_L192-259_
- L195 _public prototype_ `FTrackEditorThumbnailCache(const TSharedPtr<FTrackEditorThumbnailPool>& ThumbnailPool, IViewportThumbnailClient* InViewportThumbnailClient);`
- L196 _public prototype_ `FTrackEditorThumbnailCache(const TSharedPtr<FTrackEditorThumbnailPool>& ThumbnailPool, ICustomThumbnailClient* InCustomThumbnailClient);`
- L198 _public prototype_ `~FTrackEditorThumbnailCache();`
- L200 _public function_ `void ForceRedraw()`
- L202 _public prototype_ `void SetSingleReferenceFrame(TOptional<double> InReferenceFrame);`
- L203 _public function_ `TOptional<double> GetSingleReferenceFrame() const`
- L205 _public prototype_ `void Update(const TRange<double>& NewRange, const TRange<double>& VisibleRange, const FIntPoint& AllottedSize, const FIntPoint& InDesiredSize, EThumbnailQuality InQuality, double InCurrentTime);`
- L207 _public prototype_ `void Revalidate(double InCurrentTime);`
- L209 _public function_ `const TArray<TSharedPtr<FTrackEditorThumbnail>>& GetThumbnails() const`
- L216 _protected prototype_ `void DrawThumbnail(FTrackEditorThumbnail& TrackEditorThumbnail);`
- L218 _protected prototype_ `void DrawViewportThumbnail(FTrackEditorThumbnail& TrackEditorThumbnail) const;`
- L220 _protected prototype_ `void ComputeNewThumbnails();`
- L222 _protected prototype_ `void Setup();`
- L224 _protected prototype_ `bool ShouldRegenerateEverything() const;`
- L226 _protected prototype_ `FIntPoint CalculateTextureSize(const FMinimalViewInfo& ViewInfo) const;`
- L228 _protected prototype_ `void UpdateSingleThumbnail();`
- L230 _protected prototype_ `void UpdateFilledThumbnails();`
- L232 _protected prototype_ `void GenerateFront(const TRange<double>& Boundary);`
- L234 _protected prototype_ `void GenerateBack(const TRange<double>& Boundary);`
- L236 _protected prototype_ `void SetupViewportEngineFlags();`
- L241 _protected member_ `IViewportThumbnailClient* ViewportThumbnailClient;` — Thumbnail client used for paint notifications
- L242 _protected member_ `ICustomThumbnailClient* CustomThumbnailClient;`
- L245 _protected member_ `TWeakPtr<FTrackEditorThumbnailPool> ThumbnailPool;` — The thumbnail pool that we are sending all of our thumbnails to.
- L247 _protected member_ `FThumbnailCacheData CurrentCache;`
- L249 _protected member_ `FThumbnailCacheData PreviousCache;`
- L251 _protected member_ `TArray<TSharedPtr<FTrackEditorThumbnail>> Thumbnails;`
- L252 _protected member_ `TArray<TSharedPtr<FTrackEditorThumbnail>> ThumbnailsNeedingRedraw;`
- L254 _protected member_ `double LastComputationTime;`
- L255 _protected member_ `bool bNeedsNewThumbnails;`
- L258 _protected member_ `bool bForceRedraw;` — Whether to force a redraw or not

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API MOVIESCENETOOLS_API`
- L29 _delegate_ `DECLARE_DELEGATE_OneParam(FOnThumbnailDraw, FTrackEditorThumbnail&);`
- L29 _prototype_ `DECLARE_DELEGATE_OneParam(FOnThumbnailDraw, FTrackEditorThumbnail&);`

### `Source/Editor/MovieSceneTools/Public/TrackEditorThumbnail/TrackEditorThumbnailPool.h` (Public)


#### class `FTrackEditorThumbnailPool`  
`class FTrackEditorThumbnailPool`  
_L16-50_
- desc: Track Editor Thumbnail pool, which keeps a list of thumbnails that need to be drawn and draws them incrementally.
- L20 _public prototype_ `FTrackEditorThumbnailPool(TSharedPtr<ISequencer> InSequencer);`
- L25 _public prototype_ `void AddThumbnailsNeedingRedraw(const TArray<TSharedPtr<FTrackEditorThumbnail>>& InThumbnails);` — Requests that the passed in thumbnails need to be drawn
- L29 _public prototype_ `bool DrawThumbnails();` — @return Whether thumbnails were drawn
- L32 _public prototype_ `void RemoveThumbnailsNeedingRedraw(const TArray< TSharedPtr<FTrackEditorThumbnail>>& InThumbnails);` — Informs the pool that the thumbnails passed in no longer need to be drawn
- L37 _private member_ `TWeakPtr<ISequencer> Sequencer;` — Parent sequencer we're drawing thumbnails for
- L40 _private member_ `TArray< TSharedPtr<FTrackEditorThumbnail> > ThumbnailsNeedingDraw;` — Thumbnails enqueued for drawing
- L43 _private member_ `TArray< TSharedPtr<FTrackEditorThumbnail> > ThumbnailsBeingDrawn;` — Thumbnails that are currently being drawn
- L45 _private member_ `double TimeOfLastDraw;`
- L46 _private member_ `double TimeOfLastUpdate;`
- L49 _private member_ `bool bNeedsSort;` — Whether we need to sort

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API MOVIESCENETOOLS_API`

### `Source/Editor/MovieSceneTools/Public/TrackEditorThumbnail/TrackThumbnailUtils.h` (Public)


#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace MoveSceneTools` (scope `UE`)
- L18 _prototype_ `void PreDrawThumbnailSetupSequencer(ISequencer& Sequencer, FFrameTime CaptureFrame);` (scope `UE::MoveSceneTools`) — Prepares the sequencer so a thumbnail can be captured from it.
- L19 _function_ `inline void PreDrawThumbnailSetupSequencer(ISequencer& Sequencer, double ThumbnailEvalPosition)` (scope `UE::MoveSceneTools`)
- L25 _prototype_ `void PostDrawThumbnailCleanupSequencer(ISequencer& Sequencer);` (scope `UE::MoveSceneTools`) — Cleans up the sequencer from the consequences of PreDrawThumbnailSetupSequencer.
- L28 _prototype_ `void DrawViewportThumbnail( FRenderTarget& ThumbnailRenderTarget, const FIntPoint& RenderTargetSize, FSceneInterface& Scene, const FMinimalViewInfo& ViewInfo, EThumbnailQuality Quality, const FPostProcessSettings* OverridePostProcessSettings = nullptr );` (scope `UE::MoveSceneTools`) — Renders the thumbnail's render target in the current Scene.

### `Source/Editor/MovieSceneTools/Public/TrackEditors/AudioTrackEditor.h` (Public)


#### class `FAudioTrackEditor`  
`class FAudioTrackEditor : public FMovieSceneTrackEditor`  
_L32-127_
- inherits: `FMovieSceneTrackEditor`
- desc: Tools for audio tracks
- L42 _public prototype_ `FAudioTrackEditor(TSharedRef<ISequencer> InSequencer);` — Constructor @param InSequencer The sequencer instance to be used by this tool
- L45 _public prototype_ `virtual ~FAudioTrackEditor();` — Virtual destructor.
- L53 _public prototype_ `static TSharedRef<ISequencerTrackEditor> CreateTrackEditor(TSharedRef<ISequencer> OwningSequencer);` — Creates an instance of this class.  Called by a sequencer @param OwningSequencer The sequencer instance to be used by this tool @return The new instance of this class
- L59 _public prototype_ `virtual FText GetDisplayName() const override;`
- L60 _public prototype_ `virtual void OnInitialize() override;`
- L61 _public prototype_ `virtual void OnRelease() override;`
- L62 _public prototype_ `virtual void BuildAddTrackMenu(FMenuBuilder& MenuBuilder) override;`
- L63 _public prototype_ `virtual void BuildObjectBindingTrackMenu(FMenuBuilder& MenuBuilder, const TArray<FGuid>& ObjectBindings, const UClass* ObjectClass) override;`
- L64 _public prototype_ `virtual TSharedPtr<SWidget> BuildOutlinerColumnWidget(const FBuildColumnWidgetParams& Params, const FName& ColumnName) override;`
- L65 _public prototype_ `virtual bool HandleAssetAdded(UObject* Asset, const FGuid& TargetObjectGuid) override;`
- L66 _public prototype_ `virtual TSharedRef<ISequencerSection> MakeSectionInterface(UMovieSceneSection& SectionObject, UMovieSceneTrack& Track, FGuid ObjectBinding) override;`
- L67 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneTrack> Type) const override;`
- L68 _public prototype_ `virtual bool SupportsSequence(UMovieSceneSequence* InSequence) const override;`
- L69 _public prototype_ `virtual const FSlateBrush* GetIconBrush() const override;`
- L70 _public prototype_ `virtual bool IsResizable(UMovieSceneTrack* InTrack) const override;`
- L71 _public prototype_ `virtual void Resize(float NewSize, UMovieSceneTrack* InTrack) override;`
- L72 _public prototype_ `virtual bool OnAllowDrop(const FDragDropEvent& DragDropEvent, FSequencerDragDropParams& DragDropParams) override;`
- L73 _public prototype_ `virtual FReply OnDrop(const FDragDropEvent& DragDropEvent, const FSequencerDragDropParams& DragDropParams) override;`
- L78 _protected prototype_ `FKeyPropertyResult AddNewSound(FFrameNumber KeyTime, class USoundBase* Sound, UMovieSceneAudioTrack* Track, int32 RowIndex);` — Delegate for AnimatablePropertyChanged in HandleAssetAdded for sounds
- L81 _protected prototype_ `FKeyPropertyResult AddNewAttachedSound(FFrameNumber KeyTime, class USoundBase* Sound, UMovieSceneAudioTrack* Track, TArray<TWeakObjectPtr<UObject>> ObjectsToAttachTo);` — Delegate for AnimatablePropertyChanged in HandleAssetAdded for attached sounds
- L86 _private prototype_ `void HandleAddAudioTrackMenuEntryExecute();` — Callback for executing the "Add Audio Track" menu entry.
- L89 _private prototype_ `void HandleAddAttachedAudioTrackMenuEntryExecute(FMenuBuilder& MenuBuilder, TArray<FGuid> ObjectBindings);` — Callback for executing the "Add Audio Track" menu entry on an actor
- L92 _private prototype_ `TSharedRef<SWidget> BuildAudioSubMenu(FOnAssetSelected OnAssetSelected, FOnAssetEnterPressed OnAssetEnterPressed);` — Audio sub menu
- L95 _private prototype_ `void OnAudioAssetSelected(const FAssetData& AssetData, UMovieSceneTrack* Track);` — Audio asset selected
- L98 _private prototype_ `void OnAudioAssetEnterPressed(const TArray<FAssetData>& AssetData, UMovieSceneTrack* Track);` — Audio asset enter pressed
- L101 _private prototype_ `void OnAttachedAudioAssetSelected(const FAssetData& AssetData, TArray<FGuid> ObjectBindings);` — Attached audio asset selected
- L104 _private prototype_ `void OnAttachedAudioEnterPressed(const TArray<FAssetData>& AssetData, TArray<FGuid> ObjectBindings);` — Attached audio asset enter pressed
- L107 _private prototype_ `void RegisterMovieSceneChangedDelegate();` — Registers a delegate with the sequencer for monitoring edits
- L110 _private prototype_ `void OnMovieSceneDataChanged(EMovieSceneDataChangeType InChangeType);` — Movie Scene Data Changed Delegate
- L113 _private prototype_ `bool SequenceContainsAudioTrack(const UMovieSceneSequence* InSequence);` — Returns true if the given Sequence or any subsequence contains an audio track
- L116 _private prototype_ `bool CheckSequenceClockSource();` — Will return true if a sequence contains an audio track and the user was notified about the potential clock source issue
- L119 _private prototype_ `void PromptUserForClockSource();` — Prompts user and potentially modifies settings pref USequencerSettings::bAutoSelectAudioClockSource
- L122 _private prototype_ `void SetClockSoureToAudioClock();` — Sets the clock source for the given sequence to use the audio clock
- L126 _private member_ `FDelegateHandle MovieSceneChangedDelegate;`

#### class `FAudioSection`  
`class FAudioSection : public ISequencerSection , public TSharedFromThis<FAudioSection>`  
_L133-196_
- inherits: `ISequencerSection,TSharedFromThis<FAudioSection>`
- desc: Class for audio sections, handles drawing of all waveform previews.
- L140 _public prototype_ `FAudioSection(UMovieSceneSection& InSection, TWeakPtr<ISequencer> InSequencer);` — Constructor.
- L143 _public prototype_ `virtual ~FAudioSection();` — Virtual destructor.
- L149 _public prototype_ `virtual UMovieSceneSection* GetSectionObject() override;`
- L150 _public prototype_ `virtual FText GetSectionTitle() const override;`
- L151 _public prototype_ `virtual FText GetSectionToolTip() const override;`
- L152 _public prototype_ `virtual float GetSectionHeight(const UE::Sequencer::FViewDensityInfo& ViewDensity) const override;`
- L153 _public prototype_ `virtual int32 OnPaintSection(FSequencerSectionPainter& Painter) const override;`
- L154 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const FGeometry& ParentGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L155 _public prototype_ `virtual void BeginResizeSection() override;`
- L156 _public prototype_ `virtual void ResizeSection(ESequencerSectionResizeMode ResizeMode, FFrameNumber ResizeTime) override;`
- L157 _public prototype_ `virtual void BeginSlipSection() override;`
- L158 _public prototype_ `virtual void SlipSection(FFrameNumber SlipTime) override;`
- L159 _public prototype_ `virtual TOptional<FFrameTime> GetSectionTime(FSequencerSectionPainter& InPainter) const override;`
- L160 _public prototype_ `virtual void CustomizePropertiesDetailsView(TSharedRef<IDetailsView> DetailsView, const FSequencerSectionPropertyDetailsViewCustomizationParams& InParams) const override;`
- L165 _private prototype_ `void RegenerateWaveforms(TRange<float> DrawRange, int32 XOffset, int32 XSize, const FColor& ColorTint, float DisplayScale);` — Re-creates the texture used to preview the waveform.
- L170 _private member_ `UMovieSceneSection& Section;` — The section we are visualizing.
- L172 _private member_ `mutable TOptional<FTimeToPixel> TimeToPixel;`
- L175 _private member_ `TSharedPtr<class FAudioThumbnail> WaveformThumbnail;` — The waveform thumbnail render object.
- L178 _private member_ `TRange<float> StoredDrawRange;` — Stored data about the waveform to determine when it is invalidated.
- L179 _private member_ `FFrameNumber StoredStartOffset;`
- L180 _private member_ `int32 StoredXOffset;`
- L181 _private member_ `int32 StoredXSize;`
- L182 _private member_ `FColor StoredColor;`
- L183 _private member_ `float StoredSectionHeight;`
- L184 _private member_ `bool bStoredRepeating;`
- L187 _private member_ `TWeakObjectPtr<USoundWave> StoredSoundWave;` — Stored sound wave to determine when it is invalidated.
- L189 _private member_ `TWeakPtr<ISequencer> Sequencer;`
- L192 _private member_ `FFrameNumber InitialStartOffsetDuringResize;` — Cached start offset value valid only during resize
- L195 _private member_ `FFrameNumber InitialStartTimeDuringResize;` — Cached start time valid only during resize

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API MOVIESCENETOOLS_API`

### `Source/Editor/MovieSceneTools/Public/TrackEditors/BindingLifetimeTrackEditor.h` (Public)


#### class `FBindingLifetimeTrackEditor`  
`class FBindingLifetimeTrackEditor : public FMovieSceneTrackEditor`  
_L32-78_
- inherits: `FMovieSceneTrackEditor`
- desc: A track editor for controlling the lifetime of an object binding
- L43 _public prototype_ `static TSharedRef<ISequencerTrackEditor> CreateTrackEditor(TSharedRef<ISequencer> InSequencer);` — Factory function to create an instance of this class (called by a sequencer). @param InSequencer The sequencer instance to be used by this tool. @return The new instance of this class.
- L52 _public prototype_ `FBindingLifetimeTrackEditor(TSharedRef<ISequencer> InSequencer);` — Creates and initializes a new instance. @param InSequencer The sequencer instance to be used by this tool.
- L54 _public prototype_ `void CreateNewSection(UMovieSceneTrack* Track, bool bSelect);`
- L60 _public prototype_ `virtual FText GetDisplayName() const override;`
- L62 _public prototype_ `virtual UMovieSceneTrack* AddTrack(UMovieScene* FocusedMovieScene, const FGuid& ObjectHandle, TSubclassOf<class UMovieSceneTrack> TrackClass, FName UniqueTypeName) override;`
- L63 _public prototype_ `virtual void BuildObjectBindingTrackMenu(FMenuBuilder& MenuBuilder, const TArray<FGuid>& ObjectBindings, const UClass* ObjectClass) override;`
- L65 _public prototype_ `virtual TSharedPtr<SWidget> BuildOutlinerEditWidget(const FGuid& ObjectBinding, UMovieSceneTrack* Track, const FBuildEditWidgetParams& Params) override;`
- L67 _public function_ `virtual bool HandleAssetAdded(UObject* Asset, const FGuid& TargetObjectGuid) override`
- L68 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneTrack> Type) const override;`
- L69 _public prototype_ `virtual bool SupportsSequence(UMovieSceneSequence* InSequence) const override;`
- L71 _public prototype_ `virtual TSharedRef<ISequencerSection> MakeSectionInterface(UMovieSceneSection& SectionObject, UMovieSceneTrack& Track, FGuid ObjectBinding) override;`
- L76 _private prototype_ `void HandleAddBindingLifetimeTrackMenuEntryExecute(TArray<FGuid> ObjectBindings);` — Callback for executing the "Add Binding Lifetime Track" menu entry.
- L77 _private prototype_ `bool CanAddBindingLifetimeTrack(FGuid ObjectBinding) const;`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API MOVIESCENETOOLS_API`

### `Source/Editor/MovieSceneTools/Public/TrackEditors/CinematicShotTrackEditor.h` (Public)


#### class `FCinematicShotTrackEditor`  
`class FCinematicShotTrackEditor : public FSubTrackEditor`  
_L27-112_
- inherits: `FSubTrackEditor`
- desc: Tools for cinematic shots.
- L36 _public prototype_ `FCinematicShotTrackEditor(TSharedRef<ISequencer> InSequencer);` — Constructor @param InSequencer The sequencer instance to be used by this tool.
- L39 _public prototype_ `virtual ~FCinematicShotTrackEditor() = default;` — Virtual destructor.
- L47 _public prototype_ `static TSharedRef<ISequencerTrackEditor> CreateTrackEditor(TSharedRef<ISequencer> OwningSequencer);` — Creates an instance of this class.  Called by a sequencer . @param OwningSequencer The sequencer instance to be used by this tool. @return The new instance of this class.
- L50 _public prototype_ `TWeakObjectPtr<AActor> GetCinematicShotCamera() const;` — `UE_DEPRECATED(5.5, "Use FCameraCutPlaybackCapability::LastViewTargetCamera instead.")`
- L55 _public prototype_ `virtual FText GetDisplayName() const override;` — ISequencerTrackEditor interface
- L56 _public prototype_ `virtual TSharedPtr<SWidget> BuildOutlinerColumnWidget(const FBuildColumnWidgetParams& Params, const FName& ColumnName) override;`
- L57 _public prototype_ `virtual TSharedRef<ISequencerSection> MakeSectionInterface(UMovieSceneSection& SectionObject, UMovieSceneTrack& Track, FGuid ObjectBinding) override;`
- L58 _public prototype_ `virtual bool SupportsSequence(UMovieSceneSequence* InSequence) const override;`
- L59 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L60 _public prototype_ `virtual void BuildTrackContextMenu(FMenuBuilder& MenuBuilder, UMovieSceneTrack* Track) override;`
- L67 _public prototype_ `void RenderShots(const TArray<UMovieSceneCinematicShotSection*>& Sections);` — Render shots. @param Sections The sections to render
- L72 _public prototype_ `virtual FText GetSubTrackName() const override;` — FSubTrackEditor interface
- L73 _public prototype_ `virtual FText GetSubTrackToolTip() const override;`
- L74 _public prototype_ `virtual FName GetSubTrackBrushName() const override;`
- L75 _public prototype_ `virtual FString GetSubSectionDisplayName(const UMovieSceneSubSection* Section) const override;`
- L76 _public prototype_ `virtual FString GetDefaultSubsequenceName() const override;`
- L77 _public prototype_ `virtual FString GetDefaultSubsequenceDirectory() const override;`
- L78 _public prototype_ `virtual TSubclassOf<UMovieSceneSubTrack> GetSubTrackClass() const;`
- L82 _protected prototype_ `virtual bool HandleAddSubTrackMenuEntryCanExecute() const override;`
- L83 _protected prototype_ `virtual bool CanHandleAssetAdded(UMovieSceneSequence* Sequence) const override;`
- L88 _private prototype_ `ECheckBoxState AreShotsLocked() const;` — Delegate for shots button lock state
- L91 _private prototype_ `void OnLockShotsClicked(ECheckBoxState CheckBoxState);` — Delegate for locked shots button
- L94 _private prototype_ `FText GetLockShotsToolTip() const;` — Delegate for shots button lock tooltip
- L97 _private prototype_ `void ImportEDL();` — Callback for ImportEDL.
- L100 _private prototype_ `void ExportEDL();` — Callback for ExportEDL.
- L103 _private prototype_ `void ImportFCPXML();` — Callback for ImportFCPXML.
- L106 _private prototype_ `void ExportFCPXML();` — Callback for ExportFCPXML.
- L111 _private member_ `TSharedPtr<FTrackEditorThumbnailPool> ThumbnailPool;` — The Thumbnail pool which draws all the viewport thumbnails for the shot track.

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API MOVIESCENETOOLS_API`

### `Source/Editor/MovieSceneTools/Public/TrackEditors/CommonAnimationTrackEditor.h` (Public)


#### class `UE::Sequencer::FCommonAnimationTrackEditor`  
`class FCommonAnimationTrackEditor : public FMovieSceneTrackEditor , public FGCObject`  
_L45-223_
- inherits: `FMovieSceneTrackEditor,FGCObject`
- desc: Tools for animation tracks
- L55 _public prototype_ `FCommonAnimationTrackEditor( TSharedRef<ISequencer> InSequencer );` — Constructor @param InSequencer The sequencer instance to be used by this tool
- L58 _public prototype_ `virtual ~FCommonAnimationTrackEditor() = default;` — Virtual destructor.
- L61 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L62 _public function_ `virtual FString GetReferencerName() const override`
- L70 _public member_ `static int32 NumberActive;` — Keeps track of how many skeletal animation track editors we have*
- L72 _public prototype_ `static USkeletalMeshComponent* AcquireSkeletalMeshFromObjectGuid(const FGuid& Guid, TSharedPtr<ISequencer> SequencerPtr);`
- L73 _public prototype_ `static USkeleton* AcquireSkeletonFromObjectGuid(const FGuid& Guid, TSharedPtr<ISequencer> SequencerPtr);`
- L74 _public prototype_ `static bool AcquireAllBoundSkeletalMeshObjectsFromObjectGuid(const FGuid& Guid, TSharedPtr<ISequencer> SequencerPtr, TArray<USkeletalMeshComponent*>& OutSkelMeshComponents, TArray<FGuid>& OutBindingIds);`
- L80 _public prototype_ `virtual FText GetDisplayName() const override;`
- L81 _public prototype_ `virtual void BuildObjectBindingContextMenu(FMenuBuilder& MenuBuilder, const TArray<FGuid>& ObjectBindings, const UClass* ObjectClass) override;`
- L82 _public prototype_ `virtual void BuildObjectBindingTrackMenu(FMenuBuilder& MenuBuilder, const TArray<FGuid>& ObjectBindings, const UClass* ObjectClass) override;`
- L83 _public prototype_ `virtual void BuildObjectBindingColumnWidgets( TFunctionRef<TSharedRef<SHorizontalBox>()> GetEditBox, const UE::Sequencer::TViewModelPtr<UE::Sequencer::FObjectBindingModel>& ObjectBinding, const UE::Sequencer::FCreateOutlinerViewParams& InParams, const FName& InColumnName) override;`
- L88 _public prototype_ `virtual bool HandleAssetAdded(UObject* Asset, const FGuid& TargetObjectGuid) override;`
- L89 _public prototype_ `virtual TSharedRef<ISequencerSection> MakeSectionInterface( UMovieSceneSection& SectionObject, UMovieSceneTrack& Track, FGuid ObjectBinding ) override;`
- L90 _public prototype_ `virtual TSharedPtr<SWidget> BuildOutlinerEditWidget(const FGuid& ObjectBinding, UMovieSceneTrack* Track, const FBuildEditWidgetParams& Params) override;`
- L91 _public prototype_ `virtual bool OnAllowDrop(const FDragDropEvent& DragDropEvent, FSequencerDragDropParams& DragDropParams) override;`
- L92 _public prototype_ `virtual FReply OnDrop(const FDragDropEvent& DragDropEvent, const FSequencerDragDropParams& DragDropParams) override;`
- L93 _public prototype_ `virtual void OnInitialize() override;`
- L94 _public prototype_ `virtual void OnRelease() override;`
- L100 _protected function_ `virtual bool ShouldActivateSkeletalAnimEditMode() const` — Whether to activate FSkeletalAnimationTrackEditMode for skeleton/trail visualization. Override and return false if the subclass provides its own edit mode.
- L102 _protected prototype_ `virtual TSubclassOf<UMovieSceneCommonAnimationTrack> GetTrackClass() const = 0;`
- L105 _protected prototype_ `TSharedRef<SWidget> BuildAddAnimationSubMenu(FGuid ObjectBinding, USkeleton* Skeleton, UE::Sequencer::TWeakViewModelPtr<UE::Sequencer::FViewModel> WeakViewModel);` — Animation sub menu
- L106 _protected prototype_ `TSharedRef<SWidget> BuildAnimationSubMenu(FGuid ObjectBinding, USkeleton* Skeleton, UMovieSceneTrack* Track);`
- L107 _protected prototype_ `void AddAnimationSubMenu(FMenuBuilder& MenuBuilder, TArray<FGuid> ObjectBindings, USkeleton* Skeleton, UMovieSceneTrack* Track, int32 RowIndex = INDEX_NONE);`
- L110 _protected prototype_ `bool FilterAnimSequences(const FAssetData& AssetData, USkeleton* Skeleton);` — Filter only compatible skeletons
- L113 _protected prototype_ `bool ShouldFilterAsset(const FAssetData& AssetData);` — Animation sub menu filter function
- L116 _protected prototype_ `void OnAnimationAssetSelected(const FAssetData& AssetData, TArray<FGuid> ObjectBindings, UMovieSceneTrack* Track, int32 RowIndex = INDEX_NONE);` — Animation asset selected
- L119 _protected prototype_ `void OnAnimationAssetEnterPressed(const TArray<FAssetData>& AssetData, TArray<FGuid> ObjectBindings, UMovieSceneTrack* Track, int32 RowIndex = INDEX_NONE);` — Animation asset enter pressed
- L122 _protected prototype_ `FKeyPropertyResult AddKeyInternal(FFrameNumber KeyTime, UObject* Object, UAnimSequenceBase* AnimSequence, UMovieSceneTrack* Track, int32 RowIndex);` — Delegate for AnimatablePropertyChanged in AddKey
- L125 _protected prototype_ `void ConstructObjectBindingTrackMenu(FMenuBuilder& MenuBuilder, TArray<FGuid> ObjectBindings);` — Construct the binding menu
- L128 _protected prototype_ `void HandleCreateAnimationSequence(USkeletalMeshComponent* SkelMeshComp, USkeleton* Skeleton, FGuid Binding, bool bCeateSoftLink);` — Callback to Create the Animation Asset, pop open the dialog
- L131 _protected prototype_ `bool CreateAnimationSequence(const TArray<UObject*> NewAssets,USkeletalMeshComponent* SkelMeshComp, FGuid Binding, bool bCreateSoftLink);` — Callback to Creae the Animation Asset after getting the name
- L134 _protected prototype_ `void OpenLinkedAnimSequence(FGuid Binding);` — Open the linked Anim Sequence
- L137 _protected prototype_ `bool CanOpenLinkedAnimSequence(FGuid Binding);` — Can Open the linked Anim Sequence
- L140 _protected prototype_ `void HandleDeleteLinkedAnimSequence(FGuid Binding);` — Resolve the linked AnimSequence for the given binding and unlink it from the LevelSequence
- L143 _protected prototype_ `bool CanDeleteLinkedAnimSequence(FGuid Binding);` — Whether a linked AnimSequence exists for the given binding
- L146 _protected prototype_ `bool CanOpenLinkedAnimSequences(TArray<FGuid> Bindings);` — If we can open a linked anim sequence on any binding
- L149 _protected prototype_ `bool HasNoLinkedTracks(TArray<FGuid> Bindings);` — If we can isolate baked anim tracks since they exists
- L152 _protected prototype_ `bool HasAutoBakedLinkedTracks(TArray<FGuid> Bindings);` — Whether any binding has a linked track with bAutoBake == true
- L155 _protected prototype_ `void HandleRemoveAutoBake(TArray<FGuid> Bindings);` — Remove all auto-baked linked sequences and the linked anim track for each binding
- L162 _public prototype_ `void CreateLinkedAnimationSequence(USkeletalMeshComponent* SkelMeshComp, USkeleton* Skeleton, FGuid Binding, bool bCreateSoftLink);` — Create a linked animation sequence for the binding. Used by linked anim track providers.
- L165 _public prototype_ `static bool UnlinkLinkedAnimSequence(UAnimSequence* AnimSequence);` — Remove the bidirectional link between an AnimSequence and its owning LevelSequence.
- L169 _public prototype_ `static bool DeleteLinkedAnimTrackForBinding(const TWeakPtr<ISequencer>& InSequencer, FGuid BindingID, bool bOnlyAutoBaked);` — Remove linked AnimSequence link(s) and the LinkedAnimTrack for the given binding. If bOnlyAutoBaked is true, only removes items where bAutoBake == true.
- L171 _public prototype_ `static TArray<FLevelSequenceAnimSequenceLinkItem*> GetLinkedAnimSequences(const TWeakPtr<ISequencer>& InSequencer, FGuid Binding);`
- L174 _public prototype_ `static bool IsolateLinkedAnimTrack(const TWeakPtr<ISequencer>& InSequencer, FGuid BindingID, bool bIsolate);` — isolate the linked anim track by muting other tracks here, return true if items were changed
- L177 _public prototype_ `static void UpdateLinkedAnimSectionRange(const TWeakPtr<ISequencer>& InSequencer, FGuid BindingID);` — update linked anim sections ranges after bake in case playback range changed
- L181 _public prototype_ `static UMovieSceneTrack* GetOrCreateLinkedAnimTrack( const TWeakPtr<ISequencer>& InSequencer, FGuid BindingID);` — Find or create the linked animation track for the given binding. If none exists, creates the necessary track structure, linked anim sequence, section, and disables evaluation on the track.
- L185 _public prototype_ `static IMovieSceneLinkedAnimTrackProvider* FindProviderForBinding(const TWeakPtr<ISequencer>& InSequencer, FGuid BindingID);` — Find the first linked anim track provider that can handle this binding.
- L188 _public prototype_ `static bool IsolateLinkedAnimTracks(const TWeakPtr<ISequencer>& InSequencer, TArray<FGuid> Bindings, bool bIsolate);` — If bIsolate is true it will activate any linked and autobaked anim tracks, and deactivate control rig or non linked anim tracks, if false does opposite
- L191 _public prototype_ `static void ConfigureAutoBake(const TWeakPtr<ISequencer>& InSequencer, TArray<FGuid> Bindings);` — Set up auto-bake recorders for any linked anim sequences on the given bindings.
- L194 _public prototype_ `UMovieSceneSkeletalAnimationTrack* FindEmptyAnimationTrack(FGuid BindingID);` — Find an empty skeletal animation track on the binding. Used by linked anim track providers.
- L199 _private prototype_ `void SaveAnimSequenceLink(FLevelSequenceAnimSequenceLinkItem& Item);` — save link
- L200 _private prototype_ `UMovieSceneTrack* GetLinkedAnimTrack(FGuid Binding, bool bCreateIfMissing);`
- L202 _private prototype_ `ECheckBoxState IsLinkedAnimTrackIsolated(FGuid ObjectGuid) const;`
- L203 _private prototype_ `void OnIsolateAnimTrackClicked(ECheckBoxState NewState, FGuid ObjectGuid);`
- L208 _protected prototype_ `bool CreatePoseAsset(const TArray<UObject*> NewAssets, FGuid InObjectBinding);` — Was part of the thesection but should be at the track level since it takes the final blended result at the current time, not the section instance value
- L209 _protected prototype_ `void HandleCreatePoseAsset(FGuid InObjectBinding);`
- L210 _protected prototype_ `bool CanCreatePoseAsset(FGuid InObjectBinding) const;`
- L214 _protected member_ `TObjectPtr<UAnimSeqExportOption> AnimSeqExportOption;` — For Anim Sequence UI Option with be gc'd
- L219 _protected member_ `FDelegateHandle SequencerSavedHandle;` — Delegate to handle sequencer changes for auto baking of anim sequences
- L220 _protected prototype_ `void OnSequencerSaved(ISequencer& InSequence);`
- L221 _protected member_ `FDelegateHandle SequencerChangedHandle;`
- L222 _protected prototype_ `void OnSequencerDataChanged(EMovieSceneDataChangeType DataChangeType);`

#### class `UE::Sequencer::FCommonAnimationSection`  
`class FCommonAnimationSection : public ISequencerSection , public TSharedFromThis<FCommonAnimationSection>`  
_L227-277_
- inherits: `ISequencerSection,TSharedFromThis<FCommonAnimationSection>`
- desc: Class for animation sections
- L234 _public prototype_ `FCommonAnimationSection( UMovieSceneSection& InSection, TWeakPtr<ISequencer> InSequencer);` — Constructor.
- L237 _public prototype_ `virtual ~FCommonAnimationSection();` — Virtual destructor.
- L243 _public prototype_ `virtual UMovieSceneSection* GetSectionObject() override;`
- L244 _public prototype_ `virtual FText GetSectionTitle() const override;`
- L245 _public prototype_ `virtual FText GetSectionToolTip() const override;`
- L246 _public prototype_ `virtual TOptional<FFrameTime> GetSectionTime(FSequencerSectionPainter& InPainter) const override;`
- L247 _public prototype_ `virtual float GetSectionHeight(const UE::Sequencer::FViewDensityInfo& ViewDensity) const override;`
- L248 _public prototype_ `virtual FMargin GetContentPadding() const override;`
- L249 _public prototype_ `virtual int32 OnPaintSection( FSequencerSectionPainter& Painter ) const override;`
- L250 _public prototype_ `virtual void BeginResizeSection() override;`
- L251 _public prototype_ `virtual void ResizeSection(ESequencerSectionResizeMode ResizeMode, FFrameNumber ResizeTime) override;`
- L252 _public prototype_ `virtual void BeginSlipSection() override;`
- L253 _public prototype_ `virtual void SlipSection(FFrameNumber SlipTime) override;`
- L254 _public prototype_ `virtual void CustomizePropertiesDetailsView(TSharedRef<IDetailsView> DetailsView, const FSequencerSectionPropertyDetailsViewCustomizationParams& InParams) const override;`
- L255 _public prototype_ `virtual void BeginDilateSection() override;`
- L256 _public prototype_ `virtual void DilateSection(const TRange<FFrameNumber>& NewRange, float DilationFactor) override;`
- L257 _public prototype_ `virtual bool RequestDeleteKeyArea(const TArray<FName>& KeyAreaNamePath) override;`
- L258 _public prototype_ `virtual void BuildSectionContextMenu(FMenuBuilder& MenuBuilder, const FGuid& InObjectBinding) override;`
- L262 _public function_ `virtual bool ShouldShowLegacyBoneMatching() const` — Whether to show the legacy bone matching UI from MovieSceneCommonAnimationTrack. Override to return false when using a different bone matching system (e.g. AnimMixer).
- L265 _protected prototype_ `void FindBestBlendSection(FGuid InObjectBinding);`
- L269 _protected member_ `TWeakObjectPtr<UMovieSceneSkeletalAnimationSection> WeakSection;` — The section we are visualizing
- L272 _protected member_ `TWeakPtr<ISequencer> Sequencer;` — Used to draw animation frame, need selection state and local time
- L274 _protected member_ `TUniquePtr<FMovieSceneSequenceTransform> InitialDragTransform;`
- L275 _protected member_ `TUniquePtr<FMovieSceneTimeWarpChannel> PreDilateChannel;`
- L276 _protected member_ `double PreDilatePlayRate;`

#### Free symbols / members of external scopes

- L20 _macro_ `#define UE_API MOVIESCENETOOLS_API`
- L37 _namespace_ `namespace UE`
- L37 _namespace_ `namespace Sequencer` (scope `UE`)

### `Source/Editor/MovieSceneTools/Public/TrackEditors/CustomPrimitiveDataTrackEditor.h` (Public)


#### class `FCustomPrimitiveDataTrackEditor`  
`class FCustomPrimitiveDataTrackEditor : public FMovieSceneTrackEditor`  
_L25-101_
- inherits: `FMovieSceneTrackEditor`
- desc: Track editor for custom primitive data tracks
- L31 _public prototype_ `FCustomPrimitiveDataTrackEditor(TSharedRef<ISequencer> InSequencer);` — Constructor.
- L34 _public prototype_ `virtual ~FCustomPrimitiveDataTrackEditor() = default;` — Virtual destructor.
- L36 _public prototype_ `static TSharedRef<ISequencerTrackEditor> CreateTrackEditor(TSharedRef<ISequencer> OwningSequencer);`
- L42 _public prototype_ `virtual FText GetDisplayName() const override;`
- L43 _public prototype_ `virtual TSharedPtr<SWidget> BuildOutlinerEditWidget(const FGuid& ObjectBinding, UMovieSceneTrack* Track, const FBuildEditWidgetParams& Params) override;`
- L44 _public prototype_ `virtual TSharedRef<ISequencerSection> MakeSectionInterface(UMovieSceneSection& SectionObject, UMovieSceneTrack& Track, FGuid ObjectBinding) override;`
- L45 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneTrack> Type) const override;`
- L46 _public prototype_ `virtual bool GetDefaultExpansionState(UMovieSceneTrack* InTrack) const override;`
- L47 _public prototype_ `virtual void ExtendObjectBindingTrackMenu(TSharedRef<FExtender> Extender, const TArray<FGuid>& ObjectBindings, const UClass* ObjectClass) override;`
- L55 _private prototype_ `TSharedRef<SWidget> OnGetAddMenuContent(FGuid ObjectBinding, UMovieSceneCustomPrimitiveDataTrack* CPDTrack, int32 TrackInsertRowIndex);` — Provides the contents of the outliner edit widget
- L58 _private prototype_ `TSharedRef<SWidget> OnGetAddParameterMenuContent(FGuid ObjectBinding, UMovieSceneCustomPrimitiveDataTrack* CPDTrack);` — Provides the contents of the add parameter menu.
- L61 _private prototype_ `void OnBuildAddParameterMenu(FMenuBuilder& MenuBuilder, FGuid ObjectBinding, UMovieSceneCustomPrimitiveDataTrack* CPDTrack);` — Provides the contents of the add parameter menu.
- L68 _private prototype_ `void AddScalarParameter(UPrimitiveComponent* Component, UMovieSceneCustomPrimitiveDataTrack* CPDTrack, FGetStartIndexDelegate GetStartIndexDelegate);` — Adds a scalar parameter and initial key to a custom primitive data track. @param ObjectBinding The object binding which owns the custom primitive data track. @param CPDTrack The track in which to look for sections to add the parameter to. @param PrimitiveDataIndex The index for the primitive data to animate
- L75 _private prototype_ `void AddVector2DParameter(UPrimitiveComponent* Component, UMovieSceneCustomPrimitiveDataTrack* CPDTrack, FGetStartIndexDelegate GetStartIndexDelegate);` — Adds a Vector2D parameter and initial key to a custom primitive data track. @param ObjectBinding The object binding which owns the custom primitive data track. @param CPDTrack The track in which to look for sections to add the parameter to. @param PrimitiveDataStartIndex The start index in primitive data where we are animating a Vector2D
- L82 _private prototype_ `void AddVectorParameter(UPrimitiveComponent* Component, UMovieSceneCustomPrimitiveDataTrack* CPDTrack, FGetStartIndexDelegate GetStartIndexDelegate);` — Adds a Vector parameter and initial key to a custom primitive data track. @param ObjectBinding The object binding which owns the custom primitive data track. @param CPDTrack The track in which to look for sections to add the parameter to. @param PrimitiveDataStartIndex The start index in primitive data where we are animating a Vector
- L89 _private prototype_ `void AddColorParameter(UPrimitiveComponent* Component, UMovieSceneCustomPrimitiveDataTrack* CPDTrack, FGetStartIndexDelegate GetStartIndexDelegate);` — Adds a color parameter and initial key to a custom primitive data track. @param ObjectBinding The object binding which owns the custom primitive data track. @param CPDTrack The track in which to look for sections to add the parameter to. @param PrimitiveDataStartIndex The start index in primitive data where we are animating a Color
- L94 _private prototype_ `bool CanAddParameter(UMovieSceneCustomPrimitiveDataTrack* CPDTrack, FGetStartIndexDelegate GetStartIndexDelegate, int ParameterSize);` — Returns whether we can add a parameter starting at this index of size ParameterSize. Will return false if another parameter added overlaps that index.
- L96 _private prototype_ `void ConstructObjectBindingTrackMenu(FMenuBuilder& MenuBuilder, TArray<FGuid> ObjectBindings);`
- L98 _private prototype_ `void HandleAddCustomPrimitiveDataTrackExecute(UPrimitiveComponent* Component);`
- L100 _private member_ `uint8 StartIndex = 0;`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API MOVIESCENETOOLS_API`
- L20 _typedef_ `using FGetStartIndexDelegate = TFunction<uint8()>;`

### `Source/Editor/MovieSceneTools/Public/TrackEditors/MaterialTrackEditor.h` (Public)


#### class `FMaterialTrackEditor`  
`class FMaterialTrackEditor : public FMovieSceneTrackEditor`  
_L27-78_
- inherits: `FMovieSceneTrackEditor`
- desc: Track editor for material parameters.
- L33 _public prototype_ `FMaterialTrackEditor( TSharedRef<ISequencer> InSequencer );` — Constructor.
- L36 _public prototype_ `virtual ~FMaterialTrackEditor() = default;` — Virtual destructor.
- L42 _public prototype_ `virtual FText GetDisplayName() const override;`
- L43 _public prototype_ `virtual TSharedPtr<SWidget> BuildOutlinerEditWidget( const FGuid& ObjectBinding, UMovieSceneTrack* Track, const FBuildEditWidgetParams& Params ) override;`
- L44 _public prototype_ `virtual TSharedRef<ISequencerSection> MakeSectionInterface( UMovieSceneSection& SectionObject, UMovieSceneTrack& Track, FGuid ObjectBinding ) override;`
- L49 _protected prototype_ `virtual UMaterialInterface* GetMaterialInterfaceForTrack( FGuid ObjectBinding, UMovieSceneMaterialTrack* MaterialTrack ) = 0;` — Gets a material interface for a specific object binding and material track.
- L54 _private prototype_ `TSharedRef<SWidget> OnGetAddMenuContent( FGuid ObjectBinding, UMovieSceneMaterialTrack* MaterialTrack, int32 TrackInsertRowIndex );` — Provides the contents of the outliner edit widget
- L57 _private prototype_ `TSharedRef<SWidget> OnGetAddParameterMenuContent( FGuid ObjectBinding, UMovieSceneMaterialTrack* MaterialTrack );` — Provides the contents of the add parameter menu.
- L60 _private prototype_ `void OnBuildAddParameterMenu( FMenuBuilder& MenuBuilder, FGuid ObjectBinding, UMovieSceneMaterialTrack* MaterialTrack );` — Provides the contents of the add parameter menu.
- L63 _private prototype_ `UMaterial* GetMaterialForTrack( FGuid ObjectBinding, UMovieSceneMaterialTrack* MaterialTrack );` — Gets a material for a specific object binding and track
- L70 _private prototype_ `void AddScalarParameter( FGuid ObjectBinding, UMovieSceneMaterialTrack* MaterialTrack, FMaterialParameterInfo ParameterInfo, FString InLayerName, FString InAssetName );` — Adds a scalar parameter and initial key to a material track. @param ObjectBinding The object binding which owns the material track. @param MaterialTrack The track in which to look for sections to add the parameter to. @param ParameterName The name of the parameter to add an initial key for.
- L77 _private prototype_ `void AddColorParameter( FGuid ObjectBinding, UMovieSceneMaterialTrack* MaterialTrack, FMaterialParameterInfo ParameterInfo, FString InLayerName, FString InAssetName);` — Adds a color parameter and initial key to a material track. @param ObjectBinding The object binding which owns the material track. @param MaterialTrack The track in which to look for sections to add the parameter to. @param ParameterName The name of the parameter to add an initial key for.

#### class `FComponentMaterialTrackEditor`  
`class FComponentMaterialTrackEditor : public FMaterialTrackEditor`  
_L84-115_
- inherits: `FMaterialTrackEditor`
- desc: A specialized material track editor for component materials
- L89 _public prototype_ `FComponentMaterialTrackEditor( TSharedRef<ISequencer> InSequencer );`
- L91 _public prototype_ `static TSharedRef<ISequencerTrackEditor> CreateTrackEditor( TSharedRef<ISequencer> OwningSequencer );`
- L96 _public prototype_ `virtual void ExtendObjectBindingTrackMenu(TSharedRef<FExtender> Extender, const TArray<FGuid>& ObjectBindings, const UClass* ObjectClass) override;` — ISequencerTrackEditor interface
- L97 _public prototype_ `virtual bool SupportsType( TSubclassOf<UMovieSceneTrack> Type ) const override;`
- L98 _public prototype_ `virtual bool GetDefaultExpansionState(UMovieSceneTrack* InTrack) const override;`
- L99 _public prototype_ `virtual void BuildTrackContextMenu(FMenuBuilder& MenuBuilder, UMovieSceneTrack* Track) override;`
- L105 _protected prototype_ `virtual UMaterialInterface* GetMaterialInterfaceForTrack( FGuid ObjectBinding, UMovieSceneMaterialTrack* MaterialTrack ) override;`
- L109 _private prototype_ `void ConstructObjectBindingTrackMenu(FMenuBuilder& MenuBuilder, TArray<FGuid> ObjectBindings);`
- L111 _private prototype_ `void HandleAddComponentMaterialActionExecute(USceneComponent* Component, FComponentMaterialInfo MaterialInfo);` — Callback for executing the add component material track.
- L113 _private prototype_ `void FillRebindMaterialTrackMenu(FMenuBuilder& MenuBuilder, class UMovieSceneComponentMaterialTrack* MaterialTrack, class UPrimitiveComponent* Component, FGuid ObjectBinding);` — Callback for rebinding a component material track to a different material slot

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API MOVIESCENETOOLS_API`

### `Source/Editor/MovieSceneTools/Public/TrackEditors/PropertyTrackEditors/BoolPropertyTrackEditor.h` (Public)


#### class `FBoolPropertyTrackEditor`  
`class UE_DEPRECATED(5.7, "This class is no longer in use") FBoolPropertyTrackEditor : public FPropertyTrackEditor<UMovieSceneBoolTrack>`  
_L15-36_
- inherits: `FPropertyTrackEditor<UMovieSceneBoolTrack>`
- desc: A property track editor for Booleans.
- L25 _public function_ `FBoolPropertyTrackEditor( TSharedRef<ISequencer> InSequencer ) : FPropertyTrackEditor( InSequencer, GetAnimatedPropertyTypes() )` — Constructor. @param InSequencer The sequencer instance to be used by this tool.
- L32 _public function_ `static TArray<FAnimatedPropertyKey, TInlineAllocator<1>> GetAnimatedPropertyTypes()` — Retrieve a list of all property types that this track editor animates

### `Source/Editor/MovieSceneTools/Public/TrackEditors/PropertyTrackEditors/RegisteredPropertyTrackEditor.h` (Public)


#### struct `UE::Sequencer::IRegisteredProperty`  
`struct IRegisteredProperty`  
_L11-17_
- L13 _public prototype_ `virtual bool AppliesToTrack(UMovieSceneTrack* Track) const = 0;`
- L14 _public prototype_ `virtual bool AppliesToSection(UMovieSceneSection* Section) const = 0;`
- L16 _public function_ `virtual TSharedPtr<ISequencerSection> TryMakeSectionInterface(UMovieSceneSection* SectionObject, UMovieSceneTrack* Track, const FGuid& ObjectBinding, TWeakPtr<ISequencer> WeakSequencer)`

#### struct `UE::Sequencer::TRegisteredProperty`  
`template<typename TrackType, typename SectionType> struct TRegisteredProperty : IRegisteredProperty`  
_L20-46_
- inherits: `IRegisteredProperty`
- L22 _public typedef_ `using MakeSectionInterfacePtr = TSharedPtr<ISequencerSection> (*)(UMovieSceneSection*, UMovieSceneTrack*, const FGuid&, TWeakPtr<ISequencer>) ;`
- L23 _public function_ `TRegisteredProperty(MakeSectionInterfacePtr InMakeSectionInterface = nullptr) : MakeSectionInterface(InMakeSectionInterface)`
- L28 _public function_ `bool AppliesToTrack(UMovieSceneTrack* Track) const override`
- L32 _public function_ `bool AppliesToSection(UMovieSceneSection* Section) const override`
- L36 _public function_ `TSharedPtr<ISequencerSection> TryMakeSectionInterface(UMovieSceneSection* SectionObject, UMovieSceneTrack* Track, const FGuid& ObjectBinding, TWeakPtr<ISequencer> WeakSequencer) override`
- L45 _public member_ `MakeSectionInterfacePtr MakeSectionInterface;`

#### class `UE::Sequencer::FRegisteredPropertyTrackEditor`  
`class FRegisteredPropertyTrackEditor : public FPropertyTrackEditor<UMovieScenePropertyTrack>`  
_L50-81_
- inherits: `FPropertyTrackEditor<UMovieScenePropertyTrack>`
- L55 _public prototype_ `static TSharedRef<ISequencerTrackEditor> CreateTrackEditor(TSharedRef<ISequencer> OwningSequencer);`
- L57 _public prototype_ `FRegisteredPropertyTrackEditor(TSharedRef<ISequencer> InSequencer);`
- L59 _public prototype_ `static void GenerateKeysFromPropertyChanged(const UE::MovieScene::FPropertyDefinition& PropertyDefinition, ISequencer& Sequencer, const FPropertyChangedParams& PropertyChangedParams, UMovieSceneSection* SectionToKey, FGeneratedTrackKeys& OutGeneratedKeys);`
- L61 _public prototype_ `static UE::MovieScene::FIntermediatePropertyValue RecomposeValue(const UE::MovieScene::FPropertyDefinition& PropertyDefinition, ISequencer& Sequencer, const UE::MovieScene::FIntermediatePropertyValue& InCurrentValue, UObject* AnimatedObject, UMovieSceneSection* Section);`
- L63 _public prototype_ `static const UE::MovieScene::FPropertyDefinition* FindMatchingPropertyDefinition(const FProperty* InProperty);`
- L67 _private prototype_ `void InitializeNewTrack(UMovieScenePropertyTrack* NewTrack, FPropertyChangedParams PropertyChangedParams, const UE::MovieScene::FPropertyDefinition* PropertyDefinition);`
- L68 _private prototype_ `void InitializeNewTrack(UMovieScenePropertyTrack* NewTrack, FPropertyChangedParams PropertyChangedParams) override;`
- L69 _private prototype_ `void GenerateKeysFromPropertyChanged(const FPropertyChangedParams& PropertyChangedParams, UMovieSceneSection* SectionToKey, FGeneratedTrackKeys& OutGeneratedKeys) override;`
- L70 _private prototype_ `TSharedRef<ISequencerSection> MakeSectionInterface(UMovieSceneSection& SectionObject, UMovieSceneTrack& Track, FGuid ObjectBinding) override;`
- L71 _private prototype_ `void ProcessKeyOperation(FFrameNumber InKeyTime, const UE::Sequencer::FKeyOperation& Operation, ISequencer& InSequencer, TArray<UE::Sequencer::FAddKeyResult>* OutResults) override;`
- L72 _private prototype_ `bool SupportsType(TSubclassOf<UMovieSceneTrack> TrackClass) const override;`
- L76 _private prototype_ `void HandlePropertyChanged(const FPropertyChangedParams& PropertyChangedParams, const UE::MovieScene::FPropertyDefinition* Property);`
- L77 _private prototype_ `TSubclassOf<UMovieSceneTrack> GetCustomizedTrackClass(const FProperty* Property) const;`
- L78 _private prototype_ `FKeyPropertyResult KeyProperty(FFrameNumber KeyTime, FPropertyChangedParams PropertyChangedParams, const UE::MovieScene::FPropertyDefinition* Property);`
- L79 _private prototype_ `FOnAnimatablePropertyChanged FindPropertyChangedHandler(const FProperty*) const;`
- L80 _private prototype_ `void ProcessKeyOperation(UObject* ObjectToKey, TArrayView<const UE::Sequencer::FKeySectionOperation> SectionsToKey, ISequencer& InSequencer, FFrameNumber KeyTime, TArray<UE::Sequencer::FAddKeyResult>* OutResults);`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Sequencer` (scope `UE`)
- L48 _prototype_ `void RegisterPropertyType(TSharedPtr<IRegisteredProperty> RegisteredProperty);` (scope `UE::Sequencer`)

### `Source/Editor/MovieSceneTools/Public/TrackEditors/SpawnTrackEditor.h` (Public)


#### class `FSpawnTrackEditor`  
`class FSpawnTrackEditor : public FKeyframeTrackEditor<UMovieSceneSpawnTrack>`  
_L35-74_
- inherits: `FKeyframeTrackEditor<UMovieSceneSpawnTrack>`
- desc: A property track editor for controlling the lifetime of a sapwnable object
- L46 _public prototype_ `static TSharedRef<ISequencerTrackEditor> CreateTrackEditor(TSharedRef<ISequencer> InSequencer);` — Factory function to create an instance of this class (called by a sequencer). @param InSequencer The sequencer instance to be used by this tool. @return The new instance of this class.
- L55 _public prototype_ `FSpawnTrackEditor(TSharedRef<ISequencer> InSequencer);` — Creates and initializes a new instance. @param InSequencer The sequencer instance to be used by this tool.
- L61 _public prototype_ `virtual UMovieSceneTrack* AddTrack(UMovieScene* FocusedMovieScene, const FGuid& ObjectHandle, TSubclassOf<class UMovieSceneTrack> TrackClass, FName UniqueTypeName) override;`
- L62 _public prototype_ `virtual void BuildObjectBindingTrackMenu(FMenuBuilder& MenuBuilder, const TArray<FGuid>& ObjectBindings, const UClass* ObjectClass) override;`
- L63 _public function_ `virtual TSharedPtr<SWidget> BuildOutlinerEditWidget(const FGuid& ObjectBinding, UMovieSceneTrack* Track, const FBuildEditWidgetParams& Params) override`
- L64 _public function_ `virtual bool HandleAssetAdded(UObject* Asset, const FGuid& TargetObjectGuid) override`
- L65 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneTrack> Type) const override;`
- L66 _public prototype_ `virtual bool SupportsSequence(UMovieSceneSequence* InSequence) const override;`
- L67 _public prototype_ `virtual TSharedRef<ISequencerSection> MakeSectionInterface(UMovieSceneSection& SectionObject, UMovieSceneTrack& Track, FGuid ObjectBinding) override;`
- L72 _private prototype_ `void HandleAddSpawnTrackMenuEntryExecute(TArray<FGuid> ObjectBindings);` — Callback for executing the "Add Spawn Track" menu entry.
- L73 _private prototype_ `bool CanAddSpawnTrack(FGuid ObjectBinding) const;`

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API MOVIESCENETOOLS_API`

### `Source/Editor/MovieSceneTools/Public/TrackEditors/SubTrackEditor.h` (Public)


#### class `FSubTrackEditor`  
`class FSubTrackEditor : public FKeyframeTrackEditor<UMovieSceneSubTrack>`  
_L29-201_
- inherits: `FKeyframeTrackEditor<UMovieSceneSubTrack>`
- desc: Tools for subsequences
- L39 _public prototype_ `FSubTrackEditor(TSharedRef<ISequencer> InSequencer);` — Constructor @param InSequencer The sequencer instance to be used by this tool
- L42 _public prototype_ `virtual ~FSubTrackEditor() = default;` — Virtual destructor.
- L50 _public prototype_ `static TSharedRef<ISequencerTrackEditor> CreateTrackEditor(TSharedRef<ISequencer> OwningSequencer);` — Creates an instance of this class.  Called by a sequencer @param OwningSequencer The sequencer instance to be used by this tool @return The new instance of this class
- L55 _public prototype_ `virtual FText GetDisplayName() const override;` — ISequencerTrackEditor interface
- L56 _public prototype_ `virtual void ProcessKeyOperation(FFrameNumber InKeyTime, const UE::Sequencer::FKeyOperation& Operation, ISequencer& InSequencer, TArray<UE::Sequencer::FAddKeyResult>* OutResults = nullptr) override;`
- L57 _public prototype_ `virtual void BuildAddTrackMenu(FMenuBuilder& MenuBuilder) override;`
- L58 _public prototype_ `virtual TSharedPtr<SWidget> BuildOutlinerEditWidget(const FGuid& ObjectBinding, UMovieSceneTrack* Track, const FBuildEditWidgetParams& Params) override;`
- L59 _public prototype_ `virtual TSharedRef<ISequencerSection> MakeSectionInterface(UMovieSceneSection& SectionObject, UMovieSceneTrack& Track, FGuid ObjectBinding) override;`
- L60 _public prototype_ `virtual bool HandleAssetAdded(UObject* Asset, const FGuid& TargetObjectGuid) override;`
- L61 _public prototype_ `virtual bool SupportsSequence(UMovieSceneSequence* InSequence) const override;`
- L62 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneTrack> Type) const override;`
- L63 _public prototype_ `virtual const FSlateBrush* GetIconBrush() const override;`
- L64 _public prototype_ `virtual bool OnAllowDrop(const FDragDropEvent& DragDropEvent, FSequencerDragDropParams& DragDropParams) override;`
- L65 _public prototype_ `virtual FReply OnDrop(const FDragDropEvent& DragDropEvent, const FSequencerDragDropParams& DragDropParams) override;`
- L66 _public prototype_ `virtual bool IsResizable(UMovieSceneTrack* InTrack) const override;`
- L67 _public prototype_ `virtual void OnInitialize() override;`
- L68 _public prototype_ `virtual void OnRelease() override;`
- L69 _public prototype_ `virtual void Resize(float NewSize, UMovieSceneTrack* InTrack) override;`
- L70 _public prototype_ `virtual bool GetDefaultExpansionState(UMovieSceneTrack* InTrack) const override;`
- L71 _public function_ `virtual bool HasTransformKeyBindings() const override`
- L72 _public prototype_ `virtual bool CanAddTransformKeysForSelectedObjects() const override;`
- L73 _public prototype_ `virtual void OnAddTransformKeysForSelectedObjects(EMovieSceneTransformChannel Channel) override;`
- L74 _public prototype_ `virtual void OnDeleteTransformKeysForSelectedObjects(EMovieSceneTransformChannel Channel) override;`
- L79 _public prototype_ `virtual void InsertSection(UMovieSceneTrack* Track);` — Insert sequence into this track
- L82 _public prototype_ `virtual void DuplicateSection(UMovieSceneSubSection* Section);` — Duplicate the section into this track
- L85 _public prototype_ `virtual void CreateNewTake(UMovieSceneSubSection* Section);` — Create a new take of the given section
- L88 _public prototype_ `virtual void ChangeTake(UMovieSceneSequence* Sequence);` — Switch the selected section's take sequence
- L91 _public prototype_ `virtual void AddTakesMenu(UMovieSceneSubSection* Section, FMenuBuilder& MenuBuilder);` — Generate a menu for takes for this section
- L94 _public prototype_ `virtual void EditMetaData(UMovieSceneSubSection* Section);` — Edit the section's metadata
- L97 _public prototype_ `void UpdateActiveMode();` — Update the current active edit mode when a subtrack or section is selected.
- L108 _public prototype_ `bool CanAddSubSequence(const UMovieSceneSequence& Sequence) const;` — Check whether the given sequence can be added as a sub-sequence. The purpose of this method is to disallow circular references between sub-sequences in the focused movie scene. @param Sequence The sequence to check. @return true if the sequence can be added as a sub-sequence, false otherwise.
- L113 _public prototype_ `virtual FText GetSubTrackName() const;` — Get the name of the sub track
- L116 _public prototype_ `virtual FText GetSubTrackToolTip() const;` — Get the tooltip for this sub track editor
- L119 _public prototype_ `virtual FName GetSubTrackBrushName() const;` — Get the brush used for the sub track editor
- L122 _public prototype_ `virtual FString GetSubSectionDisplayName(const UMovieSceneSubSection* Section) const;` — Get the display name for the sub section
- L125 _public prototype_ `virtual FString GetDefaultSubsequenceName() const;` — Get the default sub sequence name
- L128 _public prototype_ `virtual FString GetDefaultSubsequenceDirectory() const;` — Get the sub sequence directory
- L131 _public prototype_ `virtual TSubclassOf<UMovieSceneSubTrack> GetSubTrackClass() const;` — Get the UMovieSceneSubTrack class
- L134 _public prototype_ `void UpdateOrigin(FVector InPosition, FRotator InRotation);` — Called when the editor mode has made external changes to the origin data.
- L137 _public prototype_ `void ResetSectionPreviews();` — Called when sequence playback updates to revert preview data on modified secitons
- L138 _public function_ `void ResetSectionPreviews(FMovieSceneSequenceIDRef IDRef)`
- L139 _public function_ `void ResetSectionPreviews(const TArray<FFrameNumber>& Frames, const FMovieSceneChannelMetaData* MetaData, UMovieSceneSection* InSection)`
- L142 _public prototype_ `FTransform GetTransformOriginDataForSubSection(const UMovieSceneSubSection* SubSection) const;` — Query's the channel data directly (does not take parent transforms into account). Used for setting keyframes.
- L145 _public prototype_ `int32 GetPreviousKey(FMovieSceneDoubleChannel& Channel, FFrameNumber Time);` — Helper function that finds the previous key. Used to "unwind" rotators
- L148 _public prototype_ `double UnwindChannel(const double& OldValue, double NewValue);` — Helper function to fix-up Euler rotations if they would go over 180 degrees due to interpolation.
- L153 _protected prototype_ `virtual void GetSupportedSequenceClassPaths(TArray<FTopLevelAssetPath>& OutClassPaths) const;` — Get the list of supported sequence class paths
- L156 _protected prototype_ `virtual void HandleAddSubTrackMenuEntryExecute();` — Callback for executing the "Add Subsequence" menu entry.
- L159 _protected function_ `virtual bool HandleAddSubTrackMenuEntryCanExecute() const` — Callback for determining whether the "Add Subsequence" menu entry can execute.
- L162 _protected prototype_ `virtual bool CanHandleAssetAdded(UMovieSceneSequence* Sequence) const;` — Whether to handle this asset being dropped onto the sequence as opposed to a specific track.
- L165 _protected prototype_ `virtual UMovieSceneSubTrack* CreateNewTrack(UMovieScene* MovieScene) const;` — `UE_DEPRECATED(5.3, "CreateNewTrack has been deprecated, please implement GetSubTrackClass")`
- L168 _protected prototype_ `UMovieSceneSubTrack* FindOrCreateSubTrack(UMovieScene* MovieScene, UMovieSceneTrack* Track) const;` — Find or create a sub track. If the given track is a subtrack, it will be returned.
- L171 _protected prototype_ `TSharedRef<SWidget> HandleAddSubSequenceComboButtonGetMenuContent(UE::Sequencer::TWeakViewModelPtr<UE::Sequencer::FViewModel> ViewModel);` — Callback for generating the menu of the "Add Sequence" combo button.
- L174 _protected prototype_ `void AddSequenceToTrack(UMovieSceneSequence* InMovieSceneSequence, UMovieSceneTrack* InTrack);` — Add the input UMovieSceneSequence to the input UMovieSceneTrack
- L179 _private prototype_ `void HandleAddSubSequenceComboButtonMenuEntryExecute(const FAssetData& AssetData, UMovieSceneTrack* InTrack);` — Callback for executing a menu entry in the "Add Sequence" combo button.
- L182 _private prototype_ `void HandleAddSubSequenceComboButtonMenuEntryEnterPressed(const TArray<FAssetData>& AssetData, UMovieSceneTrack* InTrack);` — Callback for executing a menu entry in the "Add Sequence" combo button when enter pressed.
- L185 _private prototype_ `FKeyPropertyResult AddKeyInternal(FFrameNumber KeyTime, UMovieSceneSequence* InMovieSceneSequence, UMovieSceneTrack* InTrack, int32 RowIndex);` — Delegate for AnimatablePropertyChanged in AddKey
- L188 _private prototype_ `FKeyPropertyResult HandleSequenceAdded(FFrameNumber KeyTime, UMovieSceneSequence* Sequence, UMovieSceneTrack* Track, int32 RowIndex);` — Callback for AnimatablePropertyChanged in HandleAssetAdded.
- L191 _private prototype_ `void ProcessKeyOperationInternal(TArrayView<const UE::Sequencer::FKeySectionOperation> SectionsToKey, ISequencer& Sequencer, FFrameNumber KeyTime, TArray<UE::Sequencer::FAddKeyResult>* OutResults = nullptr);` — Handles adding keys to section.
- L194 _private prototype_ `void GetOriginKeys(const FVector& CurrentPosition, const FRotator& CurrentRotation, EMovieSceneTransformChannel ChannelsToKey, UMovieSceneSection* Section, FGeneratedTrackKeys& OutGeneratedKeys);` — Helper for creating new keys.
- L197 _private prototype_ `void GetSectionsToKey(TArray<UMovieSceneSubSection*>& OutSectionsToKey) const;` — Helper for getting the sections that should be keyed.
- L200 _private member_ `TArray<UMovieSceneSubSection*> SectionsWithPreviews;` — Sections this editor has added preview data to for keyframing. Used to revert data when other edits are made, before adding a key

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API MOVIESCENETOOLS_API`
- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace Sequencer` (scope `UE`)

### `Source/Editor/MovieSceneTools/Public/TrackEditors/SubTrackEditorBase.h` (Public)


#### struct `FSubSectionPainterParams`  
`struct FSubSectionPainterParams`  
_L34-44_
- desc: Parameters for painting a sub-section.
- L36 _public function_ `FSubSectionPainterParams() : bShowTrackNum(true)`
- L38 _public function_ `FSubSectionPainterParams(FMargin InContentPadding) : ContentPadding(InContentPadding), bShowTrackNum(true)`
- L42 _public member_ `FMargin ContentPadding;`
- L43 _public member_ `bool bShowTrackNum;`

#### enum `FSubSectionPainterResult`  
`enum FSubSectionPainterResult`  
_L49-54_
- desc: Enum indicating the result of painting the sub-section.
- L51 _public enumerator_ `FSSPR_Success`
- L52 _public enumerator_ `FSSPR_InvalidSection`
- L53 _public enumerator_ `FSSPR_NoInnerSequence`

#### class `FSubSectionPainterUtil`  
`class FSubSectionPainterUtil`  
_L59-67_
- desc: Utility class for drawing sub-sequence sections.
- L63 _public prototype_ `static FSubSectionPainterResult PaintSection(TSharedPtr<const ISequencer> Sequencer, const UMovieSceneSubSection& SectionObject, FSequencerSectionPainter& InPainter, FSubSectionPainterParams Params);` — Paints the sub-section, mostly by painting loop boundaries, if appropriate
- L66 _private prototype_ `static void PaintSectionBounds(TSharedPtr<const ISequencer> Sequencer, const UMovieSceneSubSection& SectionObject, const UMovieSceneSequence& InnerSequence, FSequencerSectionPainter& InPainter, ESlateDrawEffect DrawEffects);`

#### class `FSubSectionEditorUtil`  
`class FSubSectionEditorUtil`  
_L72-103_
- desc: Utility class for editing (resize/slip) sub-sequence sections.
- L75 _public prototype_ `FSubSectionEditorUtil(UMovieSceneSubSection& InSection);`
- L76 _public prototype_ `~FSubSectionEditorUtil();`
- L79 _public prototype_ `void BeginResizeSection();` — Starts a resize operation
- L81 _public prototype_ `FFrameNumber ResizeSection(ESequencerSectionResizeMode ResizeMode, FFrameNumber ResizeTime);` — Resizes the section, returns the new resize time
- L84 _public prototype_ `void BeginSlipSection();` — Starts a new slip operation
- L86 _public prototype_ `FFrameNumber SlipSection(FFrameNumber SlipTime);` — Slips the section, returns the new slip time
- L89 _public prototype_ `void BeginDilateSection();` — Starts a new dilate operation
- L91 _public prototype_ `void DilateSection(const TRange<FFrameNumber>& NewRange, float DilationFactor);` — Dilates the section
- L95 _private member_ `UMovieSceneSubSection& SectionObject;` — The section object this utility class is editing
- L97 _private member_ `TUniquePtr<FMovieSceneSequenceTransform> InitialDragTransform;`
- L99 _private member_ `TUniquePtr<FMovieSceneTimeWarpChannel> PreDilateChannel;`
- L102 _private member_ `double PreDilateTimeScale;` — Cached time scale valid only during dilate

#### class `FSubTrackEditorUtil`  
`class FSubTrackEditorUtil`  
_L105-122_
- L117 _public prototype_ `static bool CanAddSubSequence(const UMovieSceneSequence* CurrentSequence, const UMovieSceneSequence& SubSequence);` — Check whether the given sequence can be added as a sub-sequence. The purpose of this method is to disallow circular references between sub-sequences in the focused movie scene. @param Sequence The sequence to check. @return true if the sequence can be added as a sub-sequence, false otherwise.
- L119 _public prototype_ `static UMovieSceneMetaData* FindOrAddMetaData(UMovieSceneSequence* Sequence);`
- L121 _public prototype_ `static FText GetMetaDataText(const UMovieSceneSequence* Sequence);`

#### class `TSubSectionMixin`  
`template<typename ParentSectionClass=ISequencerSection> class TSubSectionMixin : public ParentSectionClass`  
_L132-177_
- inherits: `ParentSectionClass`
- desc: Mixin class for sub-sequence section interfaces. This mixin effectively wraps the 2 utility classes above, hooks them up to the ISequencerSection interface, and implements a few other ISequencerSection interface methods. As such, it's mostly handy boilerplate code, which you can avoid (if it doesn't fit your use-case) in favour of using the uility classes above directly.
- L137 _public prototype_ `template<typename... ParentCtorParams> TSubSectionMixin(TSharedPtr<ISequencer> InSequencer, UMovieSceneSubSection& InSection, ParentCtorParams&&... Params);`
- L140 _public prototype_ `virtual UMovieSceneSection* GetSectionObject() override;` — ISequencerSection interface
- L141 _public prototype_ `virtual FText GetSectionTitle() const override;`
- L142 _public prototype_ `virtual FText GetSectionToolTip() const override;`
- L143 _public prototype_ `virtual TOptional<FFrameTime> GetSectionTime(FSequencerSectionPainter& InPainter) const override;`
- L144 _public prototype_ `virtual float GetSectionHeight(const UE::Sequencer::FViewDensityInfo& ViewDensity) const override;`
- L145 _public prototype_ `virtual bool IsReadOnly() const override;`
- L146 _public prototype_ `virtual int32 OnPaintSection( FSequencerSectionPainter& InPainter ) const override;`
- L147 _public prototype_ `virtual FReply OnSectionDoubleClicked(const FGeometry& SectionGeometry, const FPointerEvent& MouseEvent) override;`
- L148 _public prototype_ `virtual void BeginResizeSection() override;`
- L149 _public prototype_ `virtual void ResizeSection(ESequencerSectionResizeMode ResizeMode, FFrameNumber ResizeTime) override;`
- L150 _public prototype_ `virtual void BeginSlipSection() override;`
- L151 _public prototype_ `virtual void SlipSection(FFrameNumber SlipTime) override;`
- L152 _public prototype_ `virtual void BeginDilateSection() override;`
- L153 _public prototype_ `virtual void DilateSection(const TRange<FFrameNumber>& NewRange, float DilationFactor) override;`
- L154 _public prototype_ `virtual bool RequestDeleteKeyArea( const TArray<FName>& KeyAreaNamePath ) override;`
- L157 _protected member_ `static const float TrackHeight;`
- L158 _protected function_ `TSharedPtr<ISequencer> GetSequencer() const`
- L159 _protected function_ `UMovieSceneSubSection& GetSubSectionObject()`
- L160 _protected function_ `const UMovieSceneSubSection& GetSubSectionObject() const`
- L161 _protected function_ `FSubSectionEditorUtil& GetEditorUtil()`
- L164 _protected function_ `template<typename SectionType> SectionType& GetSectionObjectAs()`
- L166 _protected function_ `template<typename SectionType> const SectionType& GetSectionObjectAs() const`
- L170 _private member_ `TWeakPtr<ISequencer> SequencerPtr;` — The Sequencer this section belongs to
- L173 _private member_ `UMovieSceneSubSection& SubSectionObject;` — The section object this interface represents
- L176 _private member_ `FSubSectionEditorUtil EditorUtil;` — Utility class for resizing/slipping sub-sequence sections
- L184 _function_ `template<typename ParentSectionClass> template<typename... ParentCtorParams> TSubSectionMixin<ParentSectionClass>::TSubSectionMixin(TSharedPtr<ISequencer> InSequencer, UMovieSceneSubSection& InSection, ParentCtorParams&&... Params) : ParentSectionClass(std::forward<ParentCtorParams>(Params)...) , SequencerPtr(InSequencer) , SubSectionObject(InSection) , EditorUtil(InSection)`
- L192 _function_ `template<typename ParentSectionClass> UMovieSceneSection* TSubSectionMixin<ParentSectionClass>::GetSectionObject()`
- L199 _function_ `template<typename ParentSectionClass> FText TSubSectionMixin<ParentSectionClass>::GetSectionTitle() const`
- L212 _function_ `template<typename ParentSectionClass> FText TSubSectionMixin<ParentSectionClass>::GetSectionToolTip() const`
- L263 _function_ `template<typename ParentSectionClass> TOptional<FFrameTime> TSubSectionMixin<ParentSectionClass>::GetSectionTime(FSequencerSectionPainter& InPainter) const`
- L296 _function_ `template<typename ParentSectionClass> float TSubSectionMixin<ParentSectionClass>::GetSectionHeight(const UE::Sequencer::FViewDensityInfo& ViewDensity) const`
- L306 _function_ `template<typename ParentSectionClass> bool TSubSectionMixin<ParentSectionClass>::IsReadOnly() const`
- L312 _function_ `template<typename ParentSectionClass> int32 TSubSectionMixin<ParentSectionClass>::OnPaintSection(FSequencerSectionPainter& InPainter) const`
- L322 _function_ `template<typename ParentSectionClass> FReply TSubSectionMixin<ParentSectionClass>::OnSectionDoubleClicked(const FGeometry& SectionGeometry, const FPointerEvent& MouseEvent)`
- L347 _function_ `template<typename ParentSectionClass> void TSubSectionMixin<ParentSectionClass>::BeginResizeSection()`
- L354 _function_ `template<typename ParentSectionClass> void TSubSectionMixin<ParentSectionClass>::ResizeSection(ESequencerSectionResizeMode ResizeMode, FFrameNumber ResizeTime)`
- L361 _function_ `template<typename ParentSectionClass> void TSubSectionMixin<ParentSectionClass>::BeginSlipSection()`
- L368 _function_ `template<typename ParentSectionClass> void TSubSectionMixin<ParentSectionClass>::SlipSection(FFrameNumber SlipTime)`
- L375 _function_ `template<typename ParentSectionClass> void TSubSectionMixin<ParentSectionClass>::BeginDilateSection()`
- L382 _function_ `template<typename ParentSectionClass> void TSubSectionMixin<ParentSectionClass>::DilateSection(const TRange<FFrameNumber>& NewRange, float DilationFactor)`
- L389 _function_ `template<typename ParentSectionClass> bool TSubSectionMixin<ParentSectionClass>::RequestDeleteKeyArea( const TArray<FName>& KeyAreaNamePath )`

#### Free symbols / members of external scopes

- L25 _macro_ `#define UE_API MOVIESCENETOOLS_API`
- L180 _member_ `template<typename ParentSectionClass> const float TSubSectionMixin<ParentSectionClass>::TrackHeight = 50.f;` (scope `TSubSectionMixin<ParentSectionClass>`)
- L197 _macro_ `#define LOCTEXT_NAMESPACE "FSubTrackEditorBase"`
- L332 _function_ `` (scope `TSubSectionMixin::OnSectionDoubleClicked`)

### `Source/Editor/MovieSceneTools/Public/TrackEditors/TimeWarpTrackEditor.h` (Public)


#### struct `UE::Sequencer::FTimeWarpTrackModel`  
`struct FTimeWarpTrackModel : FTrackModel, ITimeDomainExtension`  
_L17-38_
- inherits: `FTrackModel,ITimeDomainExtension`
- L21 _public function_ `FTimeWarpTrackModel(UMovieSceneTimeWarpTrack* TimeWarpTrack) : FTrackModel(TimeWarpTrack)`
- L25 _public function_ `bool ShouldAnchorToTop() const override`
- L30 _public prototype_ `bool IsActiveTimeWarp() const;`
- L32 _public function_ `ETimeDomain GetDomain() const override`
- L37 _public prototype_ `void OnConstruct() override;`

#### class `UE::Sequencer::FTimeWarpTrackExtension`  
`class FTimeWarpTrackExtension : public IDynamicExtension`  
_L41-50_
- inherits: `IDynamicExtension`
- L49 _public member_ `TArray<TWeakViewModelPtr<FTimeWarpTrackModel>> WeakTimeWarpModels;`

#### class `FTimeWarpTrackEditor`  
`class FTimeWarpTrackEditor : public FKeyframeTrackEditor<UMovieSceneTimeWarpTrack>`  
_L59-83_
- inherits: `FKeyframeTrackEditor<UMovieSceneTimeWarpTrack>`
- L64 _public function_ `FTimeWarpTrackEditor(TSharedRef<ISequencer> InSequencer) : FKeyframeTrackEditor<UMovieSceneTimeWarpTrack>(InSequencer)`
- L68 _public function_ `static TSharedRef<ISequencerTrackEditor> CreateTrackEditor(TSharedRef<ISequencer> InSequencer)`
- L73 _public prototype_ `static TSharedPtr<UE::Sequencer::FTrackModel> CreateTrackModel(UMovieSceneTrack* Track);`
- L75 _public prototype_ `void HandleAddTimeWarpTrack(TSubclassOf<UMovieSceneTimeWarpGetter> ClassType);`
- L78 _private prototype_ `virtual FText GetDisplayName() const override;`
- L79 _private prototype_ `virtual void BuildPinnedAddTrackMenu(FMenuBuilder& MenuBuilder) override;`
- L80 _private prototype_ `virtual void ProcessKeyOperation(FFrameNumber InKeyTime, const UE::Sequencer::FKeyOperation& Operation, ISequencer& InSequencer, TArray<UE::Sequencer::FAddKeyResult>* OutResults = nullptr) override;`
- L81 _private prototype_ `virtual TSharedRef<ISequencerSection> MakeSectionInterface(UMovieSceneSection& SectionObject, UMovieSceneTrack& Track, FGuid ObjectBinding) override;`
- L82 _private prototype_ `virtual bool SupportsSequence(UMovieSceneSequence* InSequence) const override;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Sequencer` (scope `UE`)
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Sequencer` (scope `UE`)
