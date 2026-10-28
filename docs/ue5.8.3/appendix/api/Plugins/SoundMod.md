# Plugins / SoundMod

- module root: `Plugins/Runtime/SoundMod/Source/SoundMod`
- headers: 4; symbols: 30
- symbol kinds: class=4, function=3, member=9, prototype=14
- PublicDependencyModuleNames: AudioExtensions, Core, CoreUObject, Engine

### `Plugins/Runtime/SoundMod/Source/SoundMod/Classes/SoundMod.h` (Public)


#### class `USoundMod`  
`class USoundMod : public USoundBase`  
_L19-44_
- reflection: `UCLASS(hidecategories=Object, MinimalAPI, BlueprintType)`
- inherits: `USoundBase`
- L25 _private member_ `uint32 bLooping:1;` — `UPROPERTY(EditAnywhere, Category=SoundMod)` — If set, when played directly (not through a sound cue) the nid will be played looping.
- L28 _private member_ `FByteBulkData RawData;` — The mod file data
- L33 _private member_ `uint8* ResourceData;` — Memory containing the data copied from the compressed bulk data
- L37 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L41 _public prototype_ `virtual bool IsPlayable() const override;`
- L42 _public prototype_ `virtual void Parse(class FAudioDevice* AudioDevice, const UPTRINT NodeWaveInstanceHash, FActiveSound& ActiveSound, const FSoundParseParameters& ParseParams, TArray<FWaveInstance*>& WaveInstances) override;`

### `Plugins/Runtime/SoundMod/Source/SoundMod/Classes/SoundModWave.h` (Public)


#### class `USoundModWave`  
`class USoundModWave : public USoundWaveProcedural`  
_L16-29_
- reflection: `UCLASS()`
- inherits: `USoundWaveProcedural`
- L21 _private member_ `TObjectPtr<class USoundMod> SoundMod;` — `UPROPERTY()`
- L23 _private member_ `xmp_context xmpContext;`
- L26 _private prototype_ `virtual int32 GeneratePCMData(uint8* PCMData, const int32 SamplesNeeded) override;`

### `Plugins/Runtime/SoundMod/Source/SoundMod/Public/SoundModPlugin.h` (Public)


#### class `ISoundModPlugin`  
`class ISoundModPlugin : public IModuleInterface`  
_L13-38_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L24 _public function_ `static inline ISoundModPlugin& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L34 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use

### `Plugins/Runtime/SoundMod/Source/SoundMod/Public/SoundNodeModPlayer.h` (Public)


#### class `USoundNodeModPlayer`  
`class USoundNodeModPlayer : public USoundNodeAssetReferencer`  
_L23-67_
- reflection: `UCLASS(hidecategories=Object, editinlinenew, MinimalAPI, meta=( DisplayName="Mod Player" ))`
- inherits: `USoundNodeAssetReferencer`
- desc: Sound node that contains a reference to the mod file to be played
- L29 _private member_ `TSoftObjectPtr<USoundMod> SoundModAssetPtr;` — `UPROPERTY(EditAnywhere, Category=ModPlayer, meta=(DisplayName="Sound Mod"))`
- L32 _private member_ `TObjectPtr<USoundMod> SoundMod;` — `UPROPERTY(transient)`
- L35 _private member_ `uint32 bLooping:1;` — `UPROPERTY(EditAnywhere, Category=ModPlayer)`
- L37 _private member_ `uint32 bAsyncLoading:1;`
- L39 _private prototype_ `void OnSoundModLoaded(const FName& PackageName, UPackage * Package, EAsyncLoadingResult::Type Result, bool bAddToRoot);`
- L43 _public function_ `USoundMod* GetSoundMod() const`
- L44 _public prototype_ `void SetSoundMod(USoundMod* SoundMod);`
- L47 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L49 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L54 _public prototype_ `virtual int32 GetMaxChildNodes() const override;`
- L55 _public prototype_ `virtual float GetDuration() override;`
- L56 _public prototype_ `virtual void ParseNodes(FAudioDevice* AudioDevice, const UPTRINT NodeWaveInstanceHash, FActiveSound& ActiveSound, const FSoundParseParameters& ParseParams, TArray<FWaveInstance*>& WaveInstances) override;`
- L58 _public prototype_ `virtual FText GetTitle() const override;`
- L63 _public prototype_ `virtual void LoadAsset(bool bAddToRoot = false) override;`
- L64 _public prototype_ `virtual void ClearAssetReferences() override;`
