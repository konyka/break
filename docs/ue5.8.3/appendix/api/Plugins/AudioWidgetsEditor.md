# Plugins / AudioWidgetsEditor

- module root: `Plugins/Runtime/AudioWidgets/Source/AudioWidgetsEditor`
- headers: 2; symbols: 12
- symbol kinds: class=2, member=2, prototype=8
- PublicDependencyModuleNames: AudioExtensions, Core, CoreUObject, Engine, PropertyEditor

### `Plugins/Runtime/AudioWidgets/Source/AudioWidgetsEditor/Private/SoundBaseDetails.h` (Private)


#### class `FSoundBaseDetails`  
`class FSoundBaseDetails : public IDetailCustomization`  
_L11-28_
- inherits: `IDetailCustomization`
- L15 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L17 _public prototype_ `virtual ~FSoundBaseDetails();`
- L19 _public prototype_ `virtual void PendingDelete() override;`
- L23 _private prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface
- L25 _private prototype_ `void InjectPropertySheetView(IDetailLayoutBuilder& DetailBuilder);`
- L27 _private member_ `TSharedPtr<IAudioPropertiesDetailsInjector> AudioPropertiesInjector;`

### `Plugins/Runtime/AudioWidgets/Source/AudioWidgetsEditor/Public/AudioWidgetsEditorModule.h` (Public)


#### class `FAudioWidgetsEditorModule`  
`class FAudioWidgetsEditorModule : public IModuleInterface`  
_L10-23_
- inherits: `IModuleInterface`
- L15 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L16 _public prototype_ `virtual void ShutdownModule() override;`
- L19 _private prototype_ `void RegisterCustomClassLayout(FName ClassName, FOnGetDetailCustomizationInstance DetailLayoutDelegate);`
- L22 _private member_ `TSet<FName> RegisteredClassNames;` — List of registered class that we must unregister when the module shuts down
