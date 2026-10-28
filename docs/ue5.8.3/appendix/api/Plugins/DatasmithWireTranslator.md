# Plugins / DatasmithWireTranslator

- module root: `Plugins/Enterprise/DatasmithCADImporter/Source/DatasmithWireTranslator`
- headers: 2; symbols: 32
- symbol kinds: class=3, function=4, member=7, prototype=16, struct=1, typedef=1
- PrivateDependencyModuleNames: DatasmithContent, DatasmithTranslator, MessageLog, ParametricSurface, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject

### `Plugins/Enterprise/DatasmithCADImporter/Source/DatasmithWireTranslator/Private/DatasmithWireTranslator.h` (Private)


#### class `UDatasmithWireOptions`  
`class UDatasmithWireOptions : public UDatasmithOptionsBase`  
_L15-22_
- reflection: `UCLASS(BlueprintType, config = EditorPerProjectUserSettings)`
- inherits: `UDatasmithOptionsBase`
- L21 _public member_ `FWireSettings Settings;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Wire Translation Options", meta = (ShowOnlyInnerProperties))`

#### class `FDatasmithWireTranslator`  
`class FDatasmithWireTranslator : public FParametricSurfaceTranslator`  
_L24-59_
- inherits: `FParametricSurfaceTranslator`
- L27 _public prototype_ `FDatasmithWireTranslator();`
- L30 _public function_ `virtual FName GetFName() const override`
- L32 _public prototype_ `virtual void Initialize(FDatasmithTranslatorCapabilities& OutCapabilities) override;`
- L34 _public prototype_ `virtual bool IsSourceSupported(const FDatasmithSceneSource& Source) override;`
- L36 _public prototype_ `virtual bool LoadScene(TSharedRef<IDatasmithScene> OutScene) override;`
- L37 _public prototype_ `virtual void UnloadScene() override;`
- L39 _public prototype_ `virtual bool LoadStaticMesh(const TSharedRef<IDatasmithMeshElement> MeshElement, FDatasmithMeshElementPayload& OutMeshPayload) override;`
- L43 _public prototype_ `virtual void GetSceneImportOptions(TArray<TObjectPtr<UDatasmithOptionsBase>>& Options) override;`
- L44 _public prototype_ `virtual void SetSceneImportOptions(const TArray<TObjectPtr<UDatasmithOptionsBase>>& Options) override;`
- L47 _protected function_ `virtual void InitCommonTessellationOptions(FDatasmithTessellationOptions& TessellationOptions) override`
- L54 _private prototype_ `bool CanTranslate();`
- L57 _private member_ `TSharedPtr<IWireInterface> WireInterface;`
- L58 _private member_ `TObjectPtr<UDatasmithWireOptions> WireImportOptions;`

### `Plugins/Enterprise/DatasmithCADImporter/Source/DatasmithWireTranslator/Public/IWireInterface.h` (Public)


#### struct `FWireSettings`  
`struct FWireSettings : public FDatasmithTessellationOptions`  
_L22-38_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FDatasmithTessellationOptions`
- L27 _public member_ `bool bUseLayerAsActor = true;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Wire Translation Options", meta = (ToolTip = "If set to true, the first level's actors in the outliner are the layers. Default is true"))`
- L30 _public member_ `bool bMergeGeometryByGroup = true;` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Wire Translation Options", meta = (ToolTip = "If set to true, all geometry nodes under a group are merged. Default is true."))`
- L32 _public function_ `uint32 GetHash() const`
- L37 _public member_ `bool bAliasUseNative = false;`

#### class `IWireInterface`  
`class IWireInterface`  
_L40-57_
- L43 _public function_ `virtual ~IWireInterface()`
- L45 _public prototype_ `virtual bool Initialize(const TCHAR* Filename = nullptr) = 0;`
- L47 _public prototype_ `virtual bool Load(TSharedPtr<IDatasmithScene> Scene) = 0;`
- L49 _public prototype_ `virtual void SetImportSettings(const FWireSettings& Settings) = 0;`
- L50 _public prototype_ `virtual void SetOutputPath(const FString& Path) = 0;`
- L51 _public prototype_ `virtual bool LoadStaticMesh(const TSharedPtr<IDatasmithMeshElement> MeshElement, FDatasmithMeshElementPayload& OutMeshPayload, const FDatasmithTessellationOptions& InTessellationOptions) = 0;`
- L53 _public member_ `static uint64 AliasVersion;`
- L55 _public prototype_ `static uint64 GetRequiredAliasVersion(uint64 AliasMaxVersion = 0xffffffffffffffffull);`
- L56 _public prototype_ `static void RegisterInterface(int16 MajorVersion, int16 MinorVersion, FInterfaceMaker&& MakeInterface);`

#### Free symbols / members of external scopes

- L19 _typedef_ `typedef TFunction<TSharedPtr<class IWireInterface>()> FInterfaceMaker;`
