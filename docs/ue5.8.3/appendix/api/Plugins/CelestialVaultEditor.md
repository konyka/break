# Plugins / CelestialVaultEditor

- module root: `Plugins/Runtime/CelestialVault/Source/CelestialVaultEditor`
- headers: 4; symbols: 21
- symbol kinds: class=4, member=4, prototype=12, struct=1
- PrivateDependencyModuleNames: CelestialVault, CoreUObject, Engine, Slate, SlateCore, UnrealEd
- PublicDependencyModuleNames: Core

### `Plugins/Runtime/CelestialVault/Source/CelestialVaultEditor/Public/CelestialVaultEditor.h` (Public)


#### class `FCelestialVaultEditorModule`  
`class FCelestialVaultEditorModule : public IModuleInterface`  
_L10-18_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;`
- L14 _public prototype_ `virtual void ShutdownModule() override;`
- L17 _private member_ `static FEditorViewportCameraProvider EditorProvider;`

### `Plugins/Runtime/CelestialVault/Source/CelestialVaultEditor/Public/CelestialVaultEditorUtilities.h` (Public)


#### class `UCelestialVaultEditorUtilities`  
`class UCelestialVaultEditorUtilities : public UBlueprintFunctionLibrary`  
_L14-31_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- L27 _private prototype_ `static void GetViewportCursorInformation(bool& Focused, FVector2D& ScreenLocation, FVector& WorldLocation, FVector& WorldDirection);` — `UFUNCTION(BlueprintCallable, Category = "Celestial Vault|Editor Utilities")` — Retrieve information about the viewport under the mouse cursor. @param	Focused			If the Level editor not are in focus it will return false. @param	ScreenLocation	Viewport-Space position of cursor. @param	WorldLocation	Location of viewport origin (camera) in world space. @param	WorldDirection	Direction of viewport (camera) in world space.
- L30 _private prototype_ `static bool ComputeTextureMeanLuminance(UTexture2D* Texture, float& OutMean);` — `UFUNCTION(BlueprintCallable, Category = "Celestial Vault|Editor Utilities")`

### `Plugins/Runtime/CelestialVault/Source/CelestialVaultEditor/Public/DaylightSavingsCustomization.h` (Public)


#### struct `FNeededDaylightSavingsValues`  
`struct FNeededDaylightSavingsValues`  
_L12-17_
- L14 _public member_ `int32 Year = 0;`
- L15 _public member_ `EDaylightSavingsMode Mode = EDaylightSavingsMode::None;`
- L16 _public member_ `double Latitude = 0.0;`

#### class `FDaylightSavingsCustomization`  
`class FDaylightSavingsCustomization : public IPropertyTypeCustomization`  
_L20-36_
- inherits: `IPropertyTypeCustomization`
- L24 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;` — Inherited from IPropertyTypeCustomization
- L25 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L29 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Utility function to create an instance of the Property Customization.
- L32 _private prototype_ `static TOptional<FNeededDaylightSavingsValues> TryGetNeededDaylightSavingsValuesFromOuter(const TSharedRef<IPropertyHandle>& PropertyHandle);`
- L33 _private prototype_ `static bool ReadInt32Property(UObject* Object, FName PropertyName, int32& Out);`
- L34 _private prototype_ `static bool ReadDoubleProperty(UObject* Object, FName PropertyName, double& Out);`
- L35 _private prototype_ `static bool ReadDaylightSavingsModeProperty(UObject* Object, FName PropertyName, EDaylightSavingsMode& Out);`

### `Plugins/Runtime/CelestialVault/Source/CelestialVaultEditor/Public/EditorViewportCameraProvider.h` (Public)


#### class `FEditorViewportCameraProvider`  
`class FEditorViewportCameraProvider : public IViewportCameraProvider`  
_L7-11_
- inherits: `IViewportCameraProvider`
- L10 _public prototype_ `virtual bool GetCamera(FVector& OutLocation, FRotator& OutRotation) const override;`
