# Plugins / Shotgrid

- module root: `Plugins/Experimental/Shotgrid/Source/Shotgrid`
- headers: 5; symbols: 42
- symbol kinds: class=5, function=2, macro=1, member=10, prototype=23, struct=1
- PrivateDependencyModuleNames: AssetRegistry, ContentBrowser, Core, CoreUObject, EditorStyle, Engine, LevelEditor, PythonScriptPlugin, Settings, Slate, SlateCore, ToolMenus, UnrealEd

### `Plugins/Experimental/Shotgrid/Source/Shotgrid/Private/ShotgridEngine.h` (Private)


#### struct `FShotgridMenuItem`  
`struct FShotgridMenuItem`  
_L12-32_
- reflection: `USTRUCT(Blueprintable)`
- L19 _public member_ `FString Name;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Python)` — Command name for internal use
- L23 _public member_ `FString Title;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Python)` — Text to display in the menu
- L27 _public member_ `FString Description;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Python)` — Description text for the tooltip
- L31 _public member_ `FString Type;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Python)` — Menu item type to help interpret the command

#### class `UShotgridEngine`  
`class UShotgridEngine : public UObject`  
_L40-88_
- reflection: `UCLASS(Blueprintable)`
- inherits: `UObject`
- desc: Wrapper for the Python Shotgrid Engine The functions are implemented in Python by a class that derives from this one
- L47 _public prototype_ `static UShotgridEngine* GetInstance();` — `UFUNCTION(BlueprintCallable, Category = Python)` — Get the instance of the Python Shotgrid Engine
- L51 _public prototype_ `void OnEngineInitialized() const;` — `UFUNCTION(BlueprintCallable, Category = Python)` — Callback for when the Python Shotgrid Engine has finished initialization
- L55 _public prototype_ `TArray<FShotgridMenuItem> GetShotgridMenuItems() const;` — `UFUNCTION(BlueprintImplementableEvent, Category = Python)` — Get the available Shotgrid commands from the Python Shotgrid Engine
- L59 _public prototype_ `void ExecuteCommand(const FString& CommandName) const;` — `UFUNCTION(BlueprintImplementableEvent, Category = Python)` — Execute a Shotgrid command by name in the Python Shotgrid Engine
- L63 _public prototype_ `void Shutdown() const;` — `UFUNCTION(BlueprintImplementableEvent, Category = Python)` — Shut down the Python Shotgrid Engine
- L66 _public prototype_ `void SetSelection(const TArray<FAssetData>* InSelectedAssets, const TArray<AActor*>* InSelectedActors);` — Set the selected objects that will be used to determine the Shotgrid Engine context and execute Shotgrid commands
- L70 _public prototype_ `TArray<UObject*> GetReferencedAssets(const AActor* Actor) const;` — `UFUNCTION(BlueprintCallable, Category = Python)` — Get the assets that are referenced by the given Actor
- L74 _public prototype_ `static FString GetShotgridWorkDir();` — `UFUNCTION(BlueprintCallable, Category = Python)` — Get the root path for the Shotgrid work area
- L78 _public member_ `TArray<FAssetData> SelectedAssets;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Python)` — Selected assets to be used for Shotgrid commands
- L81 _public member_ `TArray<TObjectPtr<AActor>> SelectedActors;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Python, meta = (Deprecated, DeprecationMessage = "SelectedActors is deprecated, use GetSelectedActors instead." ))`
- L85 _public prototype_ `TArray<AActor*> GetSelectedActors();` — `UFUNCTION(BlueprintCallable, Category = Python)` — Selected actors to be used for Shotgrid commands
- L87 _public member_ `TArray<FWeakObjectPtr> WeakSelectedActors;`

### `Plugins/Experimental/Shotgrid/Source/Shotgrid/Private/ShotgridSettings.h` (Private)


#### class `UShotgridSettings`  
`class UShotgridSettings : public UObject`  
_L11-29_
- reflection: `UCLASS(config = Game)`
- inherits: `UObject`
- L18 _public member_ `TSet<FName> MetaDataTagsForAssetRegistry;` — `UPROPERTY(config, EditAnywhere, AdvancedDisplay, Category = "Asset Registry", DisplayName = "Metadata Tags For Asset Registry")` — The metadata tags to be transferred to the Asset Registry.
- L21 _public prototype_ `virtual void PostInitProperties() override;`
- L22 _public prototype_ `virtual void PreEditChange(FProperty* PropertyAboutToChange) override;`
- L23 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L26 _private prototype_ `void ApplyMetaDataTagsSettings();`
- L27 _private prototype_ `void ClearMetaDataTagsSettings();`

### `Plugins/Experimental/Shotgrid/Source/Shotgrid/Private/ShotgridStyle.h` (Private)


#### class `FShotgridStyle`  
`class FShotgridStyle`  
_L11-26_
- desc: Manages the style that provides resources for Shotgrid integration
- L14 _public prototype_ `static void Initialize();`
- L15 _public prototype_ `static void Shutdown();`
- L16 _public prototype_ `static const ISlateStyle& Get();`
- L17 _public prototype_ `static FName GetStyleSetName();`
- L18 _public prototype_ `static FName GetContextName();`
- L21 _public prototype_ `static void SetIcon(const FString& StyleName, const FString& ResourcePath);` — Adds an icon (.png in the given ResourcePath) with the given style name to this style set
- L24 _private prototype_ `static TUniquePtr< FSlateStyleSet > Create();`
- L25 _private member_ `static TUniquePtr< FSlateStyleSet > ShotgridStyleInstance;`

### `Plugins/Experimental/Shotgrid/Source/Shotgrid/Private/ShotgridUIManager.h` (Private)


#### class `FShotgridUIManager`  
`class FShotgridUIManager`  
_L9-17_
- L12 _public prototype_ `static void Initialize();`
- L13 _public prototype_ `static void Shutdown();`
- L16 _private member_ `static TUniquePtr<FShotgridUIManagerImpl> Instance;`

### `Plugins/Experimental/Shotgrid/Source/Shotgrid/Public/IShotgridModule.h` (Public)


#### class `IShotgridModule`  
`class IShotgridModule : public IModuleInterface`  
_L13-37_
- inherits: `IModuleInterface`
- desc: The public interface of the Shotgrid module
- L23 _public function_ `static inline IShotgridModule& Get()` — Singleton-like access to IShotgridPlugin @return Returns Shotplugin singleton instance, loading the module on demand if needed
- L33 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use

#### Free symbols / members of external scopes

- L8 _macro_ `#define SHOTGUN_MODULE_NAME TEXT("Shotgrid")`
