# Plugins / DatasmithMVRTranslator

- module root: `Plugins/VirtualProduction/DMX/DatasmithMVR/Source/DatasmithMVRTranslator`
- headers: 4; symbols: 16
- symbol kinds: class=4, function=2, member=1, prototype=9
- PrivateDependencyModuleNames: AssetRegistry, Core, CoreUObject, DMXEditor, DMXRuntime, DatasmithContent, DatasmithCore, DatasmithNativeTranslator, DatasmithTranslator, Engine, Slate

### `Plugins/VirtualProduction/DMX/DatasmithMVR/Source/DatasmithMVRTranslator/Private/DatasmithMVRImportOptions.h` (Private)


#### class `UDatasmithMVRImportOptions`  
`class UDatasmithMVRImportOptions : public UDatasmithOptionsBase`  
_L12-21_
- reflection: `UCLASS(Config = EditorPerProjectUserSettings)`
- inherits: `UDatasmithOptionsBase`
- L20 _public member_ `bool bImportMVR = true;` — `UPROPERTY(Config, EditAnywhere, Category = MVR)` — If set to true, datasmith elements that correspond to an entry in the MVR are replaced with GDTF Actors

### `Plugins/VirtualProduction/DMX/DatasmithMVR/Source/DatasmithMVRTranslator/Private/DatasmithMVRNativeTranslator.h` (Private)


#### class `FDatasmithMVRNativeTranslator`  
`class FDatasmithMVRNativeTranslator : public FDatasmithNativeTranslator`  
_L14-33_
- inherits: `FDatasmithNativeTranslator`
- desc: An override of the datasmith native translator that considers MVR assets aside or in the *_Assets folder of a .udatasmith file
- L19 _public function_ `virtual FName GetFName() const override`
- L20 _public prototype_ `virtual bool LoadScene(TSharedRef<IDatasmithScene> InOutScene) override;`
- L21 _public prototype_ `virtual void GetSceneImportOptions(TArray<TObjectPtr<UDatasmithOptionsBase>>& Options) override;`
- L26 _private prototype_ `bool FindMVRFile(FString& OutMVRFilePathAndName) const;` — Tries to find an MVR file next to or inside the datasmith folder
- L29 _private prototype_ `UDMXLibrary* CreateDMXLibraryFromMVR(const FString& MVRFilePathAndName) const;` — Creates a DMX Library from an MVR
- L32 _private prototype_ `void ReplaceMVRActorsWithMVRSceneActor(const TSharedRef<IDatasmithScene>& InOutScene, UDMXLibrary* DMXLibrary) const;` — Replaces actors in the Datasmith Scene that correspond to the MVR with the MVR Scene Actor

### `Plugins/VirtualProduction/DMX/DatasmithMVR/Source/DatasmithMVRTranslator/Private/DatasmithMVRTranslatorModule.h` (Private)


#### class `FDatasmithMVRTranslatorModule`  
`class FDatasmithMVRTranslatorModule : public IDatasmithMVRTranslatorModule`  
_L8-20_
- inherits: `IDatasmithMVRTranslatorModule`
- L13 _public prototype_ `virtual void StartupModule() override;`
- L14 _public prototype_ `virtual void ShutdownModule() override;`
- L18 _public prototype_ `virtual void SetDatasmithMVRNativeTanslatorEnabled(bool bEnabled) override;`

### `Plugins/VirtualProduction/DMX/DatasmithMVR/Source/DatasmithMVRTranslator/Public/IDatasmithMVRTranslatorModule.h` (Public)


#### class `IDatasmithMVRTranslatorModule`  
`class IDatasmithMVRTranslatorModule : public IModuleInterface`  
_L11-22_
- inherits: `IModuleInterface`
- L15 _public function_ `static IDatasmithMVRTranslatorModule& Get()`
- L21 _public prototype_ `virtual void SetDatasmithMVRNativeTanslatorEnabled(bool bEnabled) = 0;` — Enables or disables the native translator (translator for .udatasmith files) implemented in this module. When the module is started, the translator is enabled
