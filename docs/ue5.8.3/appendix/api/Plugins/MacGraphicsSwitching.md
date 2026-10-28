# Plugins / MacGraphicsSwitching

- module root: `Plugins/Editor/MacGraphicsSwitching/Source/MacGraphicsSwitching`
- headers: 6; symbols: 31
- symbol kinds: class=5, function=4, member=8, prototype=13, struct=1
- DynamicallyLoadedModuleNames: MainFrame, Settings, SettingsEditor
- PrivateDependencyModuleNames: EditorFramework, PropertyEditor, SlateCore, UnrealEd
- PrivateIncludePathModuleNames: MainFrame, Settings, SettingsEditor
- PublicDependencyModuleNames: Core, CoreUObject, Engine, InputCore, LevelEditor, Slate

### `Plugins/Editor/MacGraphicsSwitching/Source/MacGraphicsSwitching/Private/MacGraphicsSwitchingModule.h` (Private)
_(no declarations extracted)_

### `Plugins/Editor/MacGraphicsSwitching/Source/MacGraphicsSwitching/Private/MacGraphicsSwitchingSettings.h` (Private)


#### class `UMacGraphicsSwitchingSettings`  
`class UMacGraphicsSwitchingSettings : public UObject`  
_L9-20_
- reflection: `UCLASS(Config=EditorSettings)`
- inherits: `UObject`
- L16 _public member_ `int32 RendererID;` — `UPROPERTY(Config, EditAnywhere, Category=RHI, meta = (ConfigRestartRequired=true))`
- L19 _public member_ `bool bShowGraphicsSwitching;` — `UPROPERTY(Config, EditAnywhere, Category=RHI, meta = (DisplayName = "Show Editor GPU Selector", ToolTip = "Adds a drop-down menu to the main Editor window allowing GPU selection. Requires restarting the Editor.", ConfigRestartRequired=true))`

### `Plugins/Editor/MacGraphicsSwitching/Source/MacGraphicsSwitching/Private/MacGraphicsSwitchingSettingsDetails.h` (Private)


#### class `FMacGraphicsSwitchingSettingsDetails`  
`class FMacGraphicsSwitchingSettingsDetails : public IDetailCustomization`  
_L8-16_
- inherits: `IDetailCustomization`
- L12 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L15 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailLayout ) override;` — IDetailCustomization interface

### `Plugins/Editor/MacGraphicsSwitching/Source/MacGraphicsSwitching/Private/MacGraphicsSwitchingStyle.h` (Private)


#### class `FMacGraphicsSwitchingStyle`  
`class FMacGraphicsSwitchingStyle`  
_L7-18_
- L10 _public prototype_ `static void Initialize();`
- L12 _public prototype_ `static void Shutdown();`
- L14 _public prototype_ `static TSharedPtr< class ISlateStyle > Get();`
- L17 _private member_ `static TSharedPtr< class FSlateStyleSet > StyleSet;`

### `Plugins/Editor/MacGraphicsSwitching/Source/MacGraphicsSwitching/Private/MacGraphicsSwitchingWidget.h` (Private)


#### struct `FRendererItem`  
`struct FRendererItem`  
_L10-27_
- L12 _public function_ `FRendererItem(const FText& InText, int32 const InRendererID, uint64 const InRegistryID) : Text(InText) , RendererID(InRendererID) , RegistryID(InRegistryID)`
- L20 _public member_ `FText Text;` — Text to display
- L23 _public member_ `int32 RendererID;` — ID of the renderer
- L26 _public member_ `uint64 RegistryID;` — IOKit entry of the renderer

#### class `SMacGraphicsSwitchingWidget`  
`class SMacGraphicsSwitchingWidget : public SCompoundWidget`  
_L29-62_
- inherits: `SCompoundWidget`
- L32 _public function_ `SLATE_BEGIN_ARGS(SMacGraphicsSwitchingWidget) : _bLiveSwitching(false)`
- L35 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<IPropertyHandle>, PreferredRendererPropertyHandle) SLATE_ARGUMENT(bool, bLiveSwitching) SLATE_END_ARGS();`
- L39 _public prototype_ `SMacGraphicsSwitchingWidget();`
- L40 _public prototype_ `virtual ~SMacGraphicsSwitchingWidget();`
- L42 _public prototype_ `void Construct(FArguments const& InArgs);`
- L46 _private prototype_ `TSharedRef<SWidget> OnGenerateWidget( TSharedPtr<FRendererItem> InItem );` — Generate a row widget for display in the list view
- L49 _private prototype_ `void OnComboBoxOpening();` — Handle opening the combo box.
- L52 _private prototype_ `void OnSelectionChanged(TSharedPtr<FRendererItem> InItem, ESelectInfo::Type InSeletionInfo, TSharedPtr<IPropertyHandle> PreferredProviderPropertyHandle);` — Set the renderer when we change selection
- L55 _private prototype_ `FText GetRendererText() const;` — Get the text to display on the renderer drop-down
- L59 _private member_ `TArray<TSharedPtr<FRendererItem>> Renderers;` — Accessor names to display in a drop-down list
- L61 _private member_ `bool bLiveSwitching;` — Whether we are modifying the current or default

### `Plugins/Editor/MacGraphicsSwitching/Source/MacGraphicsSwitching/Public/IMacGraphicsSwitchingModule.h` (Public)


#### class `IMacGraphicsSwitchingModule`  
`class IMacGraphicsSwitchingModule : public IModuleInterface`  
_L10-35_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L21 _public function_ `static inline IMacGraphicsSwitchingModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L31 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
