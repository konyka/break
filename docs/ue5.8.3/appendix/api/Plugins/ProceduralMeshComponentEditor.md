# Plugins / ProceduralMeshComponentEditor

- module root: `Plugins/Runtime/ProceduralMeshComponent/Source/ProceduralMeshComponentEditor`
- headers: 2; symbols: 10
- symbol kinds: class=2, function=2, member=1, prototype=5
- PublicDependencyModuleNames: AssetRegistry, AssetTools, Core, CoreUObject, EditorFramework, Engine, MeshDescription, ProceduralMeshComponent, PropertyEditor, RHI, RenderCore, Slate, SlateCore, StaticMeshDescription, UnrealEd

### `Plugins/Runtime/ProceduralMeshComponent/Source/ProceduralMeshComponentEditor/Private/ProceduralMeshComponentDetails.h` (Private)


#### class `FProceduralMeshComponentDetails`  
`class FProceduralMeshComponentDetails : public IDetailCustomization`  
_L13-33_
- inherits: `IDetailCustomization`
- L17 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L20 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailBuilder ) override;` — IDetailCustomization interface
- L23 _public prototype_ `FReply ClickedOnConvertToStaticMesh();` — Handle clicking the convert button
- L26 _public prototype_ `bool ConvertToStaticMeshEnabled() const;` — Is the convert button enabled
- L29 _public prototype_ `UProceduralMeshComponent* GetFirstSelectedProcMeshComp() const;` — Util to get the ProcMeshComp we want to convert
- L32 _public member_ `TArray< TWeakObjectPtr<UObject> > SelectedObjectsList;` — Cached array of selected objects

### `Plugins/Runtime/ProceduralMeshComponent/Source/ProceduralMeshComponentEditor/Public/IProceduralMeshComponentEditorPlugin.h` (Public)


#### class `IProceduralMeshComponentEditorPlugin`  
`class IProceduralMeshComponentEditorPlugin : public IModuleInterface`  
_L11-36_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L22 _public function_ `static inline IProceduralMeshComponentEditorPlugin& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L32 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
