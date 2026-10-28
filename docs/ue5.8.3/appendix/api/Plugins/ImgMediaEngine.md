# Plugins / ImgMediaEngine

- module root: `Plugins/Media/ImgMedia/Source/ImgMediaEngine`
- headers: 2; symbols: 12
- symbol kinds: class=2, member=3, prototype=7
- PrivateDependencyModuleNames: UnrealEd
- PrivateIncludePathModuleNames: 
- PublicDependencyModuleNames: Core, CoreUObject, Engine, MediaAssets

### `Plugins/Media/ImgMedia/Source/ImgMediaEngine/Public/ImgMediaEngineModule.h` (Public)


#### class `FImgMediaEngineModule`  
`class FImgMediaEngineModule : public IModuleInterface`  
_L8-15_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;`
- L14 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Media/ImgMedia/Source/ImgMediaEngine/Public/Unreal/ImgMediaPlaybackComponent.h` (Public)


#### class `UDEPRECATED_ImgMediaPlaybackComponent`  
`class UE_DEPRECATED(5.3, "ImgMediaPlaybackComponent functionality is deprecated. Please update your project to use the features of the MediaPlate instead.") UDEPRECATED_ImgMediaPlaybackComponent : public UActorComponent`  
_L18-48_
- reflection: `UCLASS(Deprecated)`
- inherits: `UActorComponent`
- desc: Component to help with ImgMedia playback. If desired, add this to an object that displays an ImgMedia sequence. Not necessary to do this, but if you do then you can get additional functionality such as selective mipmap loading.
- L22 _public prototype_ `UDEPRECATED_ImgMediaPlaybackComponent(const FObjectInitializer& ObjectInitializer);`
- L26 _public member_ `float LODBias = 0.0f;` — `UPROPERTY(EditAnywhere, Category = MipMaps)` — This will be added to the calculated mipmap level. E.g. if set to 2, and you would normally be at mipmap level 1, then you will actually be at level 3.
- L29 _public prototype_ `virtual void BeginPlay() override;`
- L30 _public prototype_ `virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;`
- L36 _protected prototype_ `void RegisterWithMipMapInfo();` — Registers us with the mipmap info system.
- L41 _protected prototype_ `void UnregisterWithMipMapInfo();` — Unregisters us from the mipmap info system.
- L44 _protected member_ `TArray<TWeakObjectPtr<UMediaTexture>> MediaTextures;` — List of media textures that are used by our object.
- L47 _protected member_ `TSharedPtr<FMediaTextureTrackerObject, ESPMode::ThreadSafe> ObjectInfo;` — Info representing this object.
