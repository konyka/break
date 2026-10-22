# Plugins / VPSettings

- module root: `Plugins/Experimental/VirtualProduction/VPSettings/Source`
- headers: 1; symbols: 15
- symbol kinds: class=1, delegate=1, member=10, prototype=3
- PublicDependencyModuleNames: Core, CoreUObject, Engine, GameplayTags

### `Plugins/Experimental/VirtualProduction/VPSettings/Source/Public/VPSettings.h` (Public)


#### class `UVPSettings`  
`class UVPSettings : public UObject`  
_L14-78_
- reflection: `UCLASS(config=Game)`
- inherits: `UObject`
- L20 _public prototype_ `const FGameplayTagContainer& GetRoles() const;` — `UE_DEPRECATED(5.1, "Use UVirtualProductionRolesSubsystem::GetCurrentRoles() instead.")`
- L24 _public member_ `TArray<float> FocalLengthPresets = { 18.0,21.0,25.0,32.0,40.0,50.0,65.0,75.0,100.0,135.0 };` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, config, Category = "VirtualCamera|Presets")` — Default Kit of Focal Lengths for Virtual Camera
- L28 _public member_ `TArray<float> AperturePresets = { 1.0f,1.4f,2.0f,2.8f,4.0f,5.6f,8.0f,11.0f,16.0f,22.0f };` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, config, Category = "VirtualCamera|Presets")` — Default Apertures for for Virtual Camera
- L32 _public member_ `TArray<float> DefaultShutterSpeedPresets = { 1.0,4.0,8.0,15.0,30.0,60.0,125.0,250.0,500.0,1000.0 };` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, config, Category = "VirtualCamera|Presets")` — Default Shutter Speeds (1/s) for Virtual Camera
- L36 _public member_ `TArray<float> DefaultISOPresets = { 50,100,200,400,800,1600,3200,6400 };` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, config, Category = "VirtualCamera|Presets")` — Default ISOs for Virtual Camera
- L40 _public member_ `FString DirectorName = "De` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Virtual Production", DisplayName = "Director Name")` — Default Name for Director
- L44 _public member_ `FString ShowName = "De` — `UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = "Virtual Production", DisplayName = "Project Name")` — Default Name for Project
- L47 _public prototype_ `static UVPSettings* GetVPSettings();` — `UFUNCTION(BlueprintPure, Category = "Virtual Production")`
- L53 _public member_ `bool bShowRoleInEditor;` — `UPROPERTY(config, EditAnywhere, Category="Virtual Production")` — When enabled, the virtual production role(s) will be displayed in the main editor UI.
- L57 _public member_ `FSimpleMulticastDelegate OnRolesChanged;` — Notify when the virtual production roles have changed.
- L67 _protected member_ `FGameplayTagContainer Roles;` — `UPROPERTY(config)` — The machine role(s) in a virtual production context. @note The role may be override via the command line, "-VPRole=[Role.SubRole1|Role.SubRole2]"
- L74 _private prototype_ `DECLARE_DELEGATE_RetVal(const FGameplayTagContainer&, FOnGetRoles);` — Roles getter set by the VP Roles module to maintain backwards compatibility. May return the command line roles or roles enabled through the VP Roles subsystem.
- L75 _private member_ `FOnGetRoles RolesGetter;`

#### Free symbols / members of external scopes

- L74 _delegate_ `DECLARE_DELEGATE_RetVal(const FGameplayTagContainer&, FOnGetRoles);` — Roles getter set by the VP Roles module to maintain backwards compatibility. May return the command line roles or roles enabled through the VP Roles subsystem.
