# Developer / DatasmithExporter

- module root: `Source/Developer/Datasmith/DatasmithExporter`
- headers: 7; symbols: 85
- symbol kinds: class=7, delegate=1, enum=2, enumerator=5, function=1, member=18, namespace=1, prototype=48, struct=1, typedef=1
- PrivateDependencyModuleNames: ApplicationCore, CoreUObject, DirectLink, FreeImage, InputCore, MeshDescription, MessagingCommon, Projects, RawMesh, Slate, SlateCore, StandaloneRenderer, StaticMeshDescription
- PrivateIncludePathModuleNames: Launch
- PublicDependencyModuleNames: Core, DatasmithCore

### `Source/Developer/Datasmith/DatasmithExporter/Public/DatasmithDirectLink.h` (Public)


#### class `FDatasmithDirectLink`  
`class FDatasmithDirectLink`  
_L21-39_
- L24 _public prototype_ `static int32 ValidateCommunicationSetup();`
- L25 _public prototype_ `static bool Shutdown();`
- L28 _public prototype_ `FDatasmithDirectLink();`
- L30 _public prototype_ `bool InitializeForScene(const TSharedRef<IDatasmithScene>& Scene);`
- L31 _public prototype_ `bool UpdateScene(const TSharedRef<IDatasmithScene>& Scene);`
- L36 _public prototype_ `void CloseCurrentSource();` — Close the initialized DirectLink source if any.
- L38 _public prototype_ `static TSharedRef<DirectLink::FEndpoint, ESPMode::ThreadSafe> GetEnpoint();`

#### Free symbols / members of external scopes

- L11 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDatasmithDirectLinkExporterAPI, Log, All);`
- L11 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDatasmithDirectLinkExporterAPI, Log, All);`
- L16 _namespace_ `namespace DirectLink`

### `Source/Developer/Datasmith/DatasmithExporter/Public/DatasmithExportOptions.h` (Public)


#### enum `EDSExportLightmapUV`  
`enum class EDSExportLightmapUV`  
_L13-18_
- desc: Never: it won't force the creation of a UV channel for lightmap, if one already exists it will be exported IfNotPresent: if a channel already exists it will be used, if not a new automatic UV projection will be created Always: it will create the UV channel overwritting existing data
- L15 _public enumerator_ `Never`
- L16 _public enumerator_ `IfNotPresent`
- L17 _public enumerator_ `Always`

#### enum `EDSResizedTexturesPath`  
`enum class EDSResizedTexturesPath`  
_L24-28_
- desc: OriginalFolder: keeps the textures (and its resized copies if needed) in the original folder ExportFolder: copy the textures to the export path
- L26 _public enumerator_ `OriginalFolder`
- L27 _public enumerator_ `ExportFolder`

#### class `FDatasmithExportOptions`  
`class FDatasmithExportOptions`  
_L30-46_
- L35 _public member_ `static EDSExportLightmapUV LightmapUV;` — Creation of automatic flatten projection of UVs to be used on lightmaps
- L37 _public member_ `static EDSResizeTextureMode ResizeTexturesMode;` — Policy to create GPU friendly texture sizes
- L39 _public member_ `static EDSResizedTexturesPath PathTexturesMode;` — it sets where the resized textures will be stored
- L41 _public member_ `static int32 MaxTextureSize;` — Maximum texture size allowed, this will be used in conjuction with ResizeTexturesMode
- L42 _public member_ `static const int32 MaxUnrealSupportedTextureSize;`
- L45 _public member_ `static float ColorGamma;` — Gamma of colors, usually 2.2 for Linear Workflow or 1.0 for classic workflow

### `Source/Developer/Datasmith/DatasmithExporter/Public/DatasmithExporterManager.h` (Public)


#### class `FDatasmithExporterManager`  
`class FDatasmithExporterManager`  
_L15-96_
- L45 _public prototype_ `static bool Initialize();` — Initializes the Datasmith Exporter module with the default settings Needs to be called before starting any export or using any other features of the datasmith export. Must be called once @return True if the initialization was successful
- L57 _public prototype_ `static bool Initialize(const FInitOptions& InitOptions);`
- L63 _public prototype_ `static void Shutdown();` — Shuts down the Datasmith Exporter module. Must be called when the process performing exports exits
- L70 _public prototype_ `static bool RunGarbageCollection();` — Run the unreal engine garbage collection on the proper thread Exporter code that want to run garbage collection should use this function instead of the standard engine function @return whether the Garbage Collection ran.
- L76 _public prototype_ `static void PushCommandIntoGameThread(FSimpleDelegate&& Command, bool bWakeUpGameThread = false);` — Enqueue a command into the game thread for execution
- L81 _public prototype_ `static bool WasInitializedWithMessaging();` — Returns if the Exporter Manager was initialized with enabled network capabilities.
- L86 _public prototype_ `static bool WasInitializedWithGameThread();` — Returns if the Exporter Manager is running its own game thread.
- L89 _private member_ `static bool bEngineInitialized;`
- L90 _private member_ `static bool bUseMessaging;`
- L91 _private member_ `static class FRunnableThread* GMainThreadAsRunnable;`
- L94 _private member_ `static TSharedPtr<class FDatasmithGameThread> GDatasmithGameThread;` — SharedPtr because we want to forward declare the type

#### struct `FDatasmithExporterManager::FInitOptions`  
`struct FInitOptions`  
_L18-35_
- L20 _public member_ `bool bSuppressLogs = true;`
- L21 _public member_ `bool bSaveLogToUserDir = true;`
- L22 _public member_ `bool bEnableMessaging = false;`
- L33 _public member_ `bool bUseDatasmithExporterUI = false;` — This setting will enable the datasmith exporter UI Enabling this will require the remote engine dir path to be specified It will set the engine loop in it's own thread so that the ui can run independently from the host program If your are not using the datasmith SDK or the C# SDK (Datasmith Facade) you will also need to add the fellowing line to your target.cs file GlobalDefinitions.Add("UE_EXTERNAL_PROFILING_ENABLED=0"); Otherwise the engine path won't be properly initialized as these profilers require the engine path to be valid when the static variables are initialized
- L34 _public member_ `const TCHAR* RemoteEngineDirPath = nullptr;`

#### Free symbols / members of external scopes

- L12 _typedef_ `typedef TDelegate<void(), FDefaultDelegateUserPolicy> FSimpleDelegate;`

### `Source/Developer/Datasmith/DatasmithExporter/Public/DatasmithLogger.h` (Public)


#### class `FDatasmithLogger`  
`class FDatasmithLogger`  
_L13-37_
- desc: Logger that holds the errors during the export process. The user plugin should display the list of errors at the end of the export.
- L16 _public prototype_ `FDatasmithLogger();`
- L17 _public prototype_ `virtual ~FDatasmithLogger();`
- L19 _public prototype_ `void AddGeneralError(const TCHAR* InError);`
- L20 _public prototype_ `int32 GetGeneralErrorsCount();`
- L21 _public prototype_ `const TCHAR* GetGeneralError(int32 Index) const;`
- L22 _public prototype_ `void ResetGeneralErrors();`
- L24 _public prototype_ `void AddTextureError(const TCHAR* InError);`
- L25 _public prototype_ `int32 GetTextureErrorsCount();`
- L26 _public prototype_ `const TCHAR* GetTextureError(int32 Index) const;`
- L27 _public prototype_ `void ResetTextureErrors();`
- L29 _public prototype_ `void AddMissingAssetError(const TCHAR* InError);`
- L30 _public prototype_ `int32 GetMissingAssetErrorsCount();`
- L31 _public prototype_ `const TCHAR* GetMissingAssetError(int32 Index) const;`
- L32 _public prototype_ `void ResetMissingAssetErrors();`
- L35 _protected member_ `FDatasmithLoggerImpl* Impl;`

### `Source/Developer/Datasmith/DatasmithExporter/Public/DatasmithMeshExporter.h` (Public)


#### class `FDatasmithMeshExporter`  
`class FDatasmithMeshExporter`  
_L13-57_
- L16 _public prototype_ `FDatasmithMeshExporter();`
- L17 _public prototype_ `virtual ~FDatasmithMeshExporter();`
- L30 _public prototype_ `TSharedPtr<IDatasmithMeshElement> ExportToUObject(const TCHAR* Filepath, const TCHAR* Filename, FDatasmithMesh& Mesh, FDatasmithMesh* CollisionMesh, EDSExportLightmapUV LightmapUV);` — Exports the DatasmithMesh as a UObject. @param Filepath		The path where the resulting file will be written @param Filename		The name of the file to export to, without any path or extension @param Mesh	        The mesh to export @param CollisionMesh An optional collision mesh @param LightmapUV	The UV generation export option @return				A IDatasmithMeshElement that refers to the exported file
- L43 _public prototype_ `bool ExportToUObject(TSharedPtr<IDatasmithMeshElement>& MeshElement, const TCHAR* Filepath, FDatasmithMesh& Mesh, FDatasmithMesh* CollisionMesh, EDSExportLightmapUV LightmapUV);` — Exports a FDatasmithMesh as a UObject and link it to the given IDatasmithMeshElementElement. @param MeshElement	The existing MeshElement for which we want to export a FDatasmithMesh, the name of the MeshElement will determine the name of the exported file. @param Filepath		The path where the resulting file will be written @param Mesh	        The mesh to export @param CollisionMesh An optional collision mesh @param LightmapUV	The UV generation export option @return				True if export was successful.
- L47 _public prototype_ `bool ExportCloth(class FDatasmithCloth& Cloth, TSharedPtr<class IDatasmithClothElement>& ClothElement, const TCHAR* FilePath, const TCHAR* AssetsOutputPath) const;` — `UE_DEPRECATED(5.5, "The experimental Cloth importer is no longer supported.")`
- L53 _public prototype_ `FString GetLastError() const;` — @return The error that happened during the last export, if any
- L56 _private member_ `TUniquePtr<class FDatasmithMeshExporterImpl> Impl;`

### `Source/Developer/Datasmith/DatasmithExporter/Public/DatasmithProgressManager.h` (Public)


#### class `IDatasmithProgressManager`  
`class IDatasmithProgressManager`  
_L11-23_
- desc: Interface that is called during export time to update the progression. Implement for your specific DCC.
- L14 _public function_ `virtual ~IDatasmithProgressManager()`
- L22 _public prototype_ `virtual void ProgressEvent(float InProgressRatio, const TCHAR* InProgressString) = 0;` — Method called when progress is made during an export. @param InProgressRatio	The ratio of progress, between 0.f and 1.f @param InProgressString	Text describing the current task being performed

### `Source/Developer/Datasmith/DatasmithExporter/Public/DatasmithSceneExporter.h` (Public)


#### class `FDatasmithSceneExporter`  
`class FDatasmithSceneExporter`  
_L21-69_
- desc: This is the export for a DatasmithScene. Call PreExport, then Export to finish the export process.
- L24 _public prototype_ `FDatasmithSceneExporter();`
- L25 _public prototype_ `~FDatasmithSceneExporter();`
- L30 _public prototype_ `void PreExport();` — Indicates that we're starting the export process. Starts the export metrics.
- L38 _public prototype_ `void Export( TSharedRef< IDatasmithScene > DatasmithScene, bool bCleanupUnusedElements = true );` — Exports the entire scene. It will create the scene file as well as the resized textures (in case of resize is enabled). @param bCleanupUnusedElements Remove unused meshes, textures and materials before exporting
- L42 _public prototype_ `void Reset();` — `UE_DEPRECATED(5.1, "This function was selectively reseting the export state and was preserving the export paths. We should now directly set the fields we want to change instead.")` — Resets all the settings on the scene
- L45 _public prototype_ `void SetProgressManager( const TSharedPtr< IDatasmithProgressManager >& InProgressManager );` — Sets the progress manager for visual feedback on exporting
- L48 _public prototype_ `void SetLogger( const TSharedPtr< FDatasmithLogger >& InLogger );` — Sets the logger to store the summary of the export process
- L51 _public prototype_ `void SetName(const TCHAR* InName);` — Sets the name of the scene to export. The resulting file and folder will use this name.
- L54 _public prototype_ `const TCHAR* GetName() const;` — Gets the name of the scene to export.
- L59 _public prototype_ `void SetOutputPath(const TCHAR* InOutputPath);` — Sets the output path to where this scene will be exported.
- L60 _public prototype_ `const TCHAR* GetOutputPath() const;`
- L65 _public prototype_ `const TCHAR* GetAssetsOutputPath() const;` — Gets the path to the assets output folder. This is where we output the mesh files, textures, etc.
- L68 _private member_ `TUniquePtr< FDatasmithSceneExporterImpl > Impl;`
