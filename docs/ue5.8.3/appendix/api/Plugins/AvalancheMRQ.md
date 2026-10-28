# Plugins / AvalancheMRQ

- module root: `Plugins/VirtualProduction/Avalanche/Source/AvalancheMRQ`
- headers: 1; symbols: 9
- symbol kinds: class=1, function=2, member=3, prototype=2, struct=1
- PrivateDependencyModuleNames: Avalanche, AvalancheRemoteControl, CoreUObject, Engine, Slate, SlateCore
- PublicDependencyModuleNames: AvalancheMedia, Core, MovieRenderPipelineCore, RemoteControl

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMRQ/Public/AvaMRQRundownPageSetting.h` (Public)


#### struct `FAvaMRQRundownPage`  
`struct FAvaMRQRundownPage`  
_L12-21_
- reflection: `USTRUCT(BlueprintType, DisplayName = "Motion Design MRQ Rundown Page")`
- L17 _public member_ `TSoftObjectPtr<UAvaRundown> Rundown;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Design Sequence")`
- L20 _public member_ `int32 PageId = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Design Sequence")`

#### class `UAvaMRQRundownPageSetting`  
`class UAvaMRQRundownPageSetting : public UMoviePipelineSetting`  
_L24-39_
- reflection: `UCLASS(MinimalAPI, DisplayName = "Rundown Page")`
- inherits: `UMoviePipelineSetting`
- L30 _public member_ `FAvaMRQRundownPage RundownPage;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Design Sequence", meta=(ShowOnlyInnerProperties))`
- L34 _protected prototype_ `virtual void SetupForPipelineImpl(UMoviePipeline* InPipeline) override;`
- L35 _protected function_ `virtual bool IsValidOnShots() const override`
- L36 _protected function_ `virtual bool IsValidOnPrimary() const override`
- L37 _protected prototype_ `virtual void UpdateTelemetry(FMoviePipelineShotRenderTelemetry* InTelemetry) const override;`
