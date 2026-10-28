# Plugins / MovieSceneTextTrack

- module root: `Plugins/MovieScene/MovieSceneTextTrack/Source/MovieSceneTextTrack`
- headers: 6; symbols: 13
- symbol kinds: member=3, namespace=2, prototype=7, struct=1
- PublicDependencyModuleNames: Core, CoreUObject, Engine, MovieScene, MovieSceneTracks

### `Plugins/MovieScene/MovieSceneTextTrack/Source/MovieSceneTextTrack/Public/MovieSceneTextChannel.h` (Public)
_(no declarations extracted)_

### `Plugins/MovieScene/MovieSceneTextTrack/Source/MovieSceneTextTrack/Public/MovieSceneTextPropertySystem.h` (Public)
_(no declarations extracted)_

### `Plugins/MovieScene/MovieSceneTextTrack/Source/MovieSceneTextTrack/Public/MovieSceneTextSection.h` (Public)
_(no declarations extracted)_

### `Plugins/MovieScene/MovieSceneTextTrack/Source/MovieSceneTextTrack/Public/MovieSceneTextTrack.h` (Public)
_(no declarations extracted)_

### `Plugins/MovieScene/MovieSceneTextTrack/Source/MovieSceneTextTrack/Public/TextChannelEvaluatorSystem.h` (Public)
_(no declarations extracted)_

### `Plugins/MovieScene/MovieSceneTextTrack/Source/MovieSceneTextTrack/Public/TextComponentTypes.h` (Public)


#### struct `UE::MovieScene::FTextComponentTypes`  
`struct UE_DEPRECATED(5.7, "FTextComponentTypes deprecated. Use FBuiltInComponentTypes and FMovieSceneTracksComponentTypes instead") FTextComponentTypes`  
_L12-36_
- L15 _public prototype_ `static FTextComponentTypes* Get();`
- L18 _public prototype_ `static void Destroy();`
- L21 _public member_ `TComponentTypeID<FSourceTextChannel> TextChannel;` — An FMovieSceneTextChannel
- L24 _public member_ `TComponentTypeID<FText> TextResult;` — Result of an evaluated FMovieSceneTextChannel
- L26 _public member_ `TPropertyComponents<FTextPropertyTraits> Text;`
- L30 _private prototype_ `FTextComponentTypes() = default;`
- L31 _private prototype_ `FTextComponentTypes(const FTextComponentTypes&) = default;`
- L32 _private prototype_ `FTextComponentTypes(FTextComponentTypes&&) = default;`
- L33 _private prototype_ `FTextComponentTypes& operator=(const FTextComponentTypes&) = default;`
- L34 _private prototype_ `FTextComponentTypes& operator=(FTextComponentTypes&&) = default;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace MovieScene` (scope `UE`)
