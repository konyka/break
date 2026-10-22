# Plugins / MotorSimOutputMotoSynth

- module root: `Plugins/Experimental/MotorSimOutputMotoSynth/Source/MotorSimOutputMotoSynth`
- headers: 2; symbols: 9
- symbol kinds: class=2, macro=1, prototype=6
- PrivateDependencyModuleNames: AudioMixer, AudioMotorSim
- PublicDependencyModuleNames: AudioExtensions, Core, CoreUObject, Engine, MotoSynth

### `Plugins/Experimental/MotorSimOutputMotoSynth/Source/MotorSimOutputMotoSynth/Public/MotorSimOutputMotoSynth.h` (Public)


#### class `UMotorSimOutputMotoSynth`  
`class UMotorSimOutputMotoSynth : public USynthComponentMoto, public IAudioMotorSimOutput`  
_L12-23_
- reflection: `UCLASS(MinimalAPI, ClassGroup = Synth, meta = (BlueprintSpawnableComponent))`
- inherits: `USynthComponentMoto,IAudioMotorSimOutput`
- L16 _private prototype_ `virtual ~UMotorSimOutputMotoSynth() override = default;`
- L19 _public prototype_ `virtual void Update(FAudioMotorSimInputContext& Input, FAudioMotorSimRuntimeContext& RuntimeInfo) override;`
- L21 _public prototype_ `virtual void StartOutput() override;`
- L22 _public prototype_ `virtual void StopOutput() override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MOTORSIMOUTPUTMOTOSYNTH_API`

### `Plugins/Experimental/MotorSimOutputMotoSynth/Source/MotorSimOutputMotoSynth/Public/MotorSimOutputMotoSynthModule.h` (Public)


#### class `FMotorSimOutputMotoSynthModule`  
`class FMotorSimOutputMotoSynthModule : public IModuleInterface`  
_L7-14_
- inherits: `IModuleInterface`
- L12 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface interface
- L13 _public prototype_ `virtual void ShutdownModule() override;`
