# Plugins / GizmoSettings

- module root: `Plugins/Experimental/GizmoFramework/Source/GizmoSettings`
- headers: 1; symbols: 5
- symbol kinds: class=1, function=1, member=2, prototype=1
- PrivateDependencyModuleNames: Core, CoreUObject, DeveloperSettings, EditorInteractiveToolsFramework, Engine

### `Plugins/Experimental/GizmoFramework/Source/GizmoSettings/Public/GizmoSettings.h` (Public)


#### class `UGizmoSettings`  
`class UE_DEPRECATED(5.6, "New Gizmos settings can now be found in UTransformGizmoEditorSettings") UGizmoSettings : public UDeveloperSettings`  
_L11-30_
- reflection: `UCLASS(config=EditorPerProjectUserSettings, meta = (DisplayName = "New TRS Gizmo"))`
- inherits: `UDeveloperSettings`
- L19 _public member_ `bool bEnableNewGizmos_DEPRECATED = false;` — `UE_DEPRECATED(5.6, "UGizmoSettings::bEnableNewGizmos is deprecated. See UTransformGizmoEditorSettings::bUseExperimentalGizmo")` — `UPROPERTY(config)` — Enable/Disable New TRS Gizmos across the editor.
- L24 _public member_ `FGizmosParameters GizmoParameters_DEPRECATED;` — `UE_DEPRECATED(5.6, "UGizmoSettings::GizmoParameters is deprecated. See UTransformGizmoEditorSettings::GizmoParameters")` — `UPROPERTY(config)` — Change the current gizmos parameters.
- L26 _public prototype_ `virtual void PostInitProperties() override;`
- L29 _public function_ `virtual bool SupportsAutoRegistration() const override` — We don't want to show this in the Editor Preferences list
