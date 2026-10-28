# Runtime / GDKPackageManifest

- module root: `Source/Runtime/Microsoft/GDKPackageManifest`
- headers: 1; symbols: 24
- symbol kinds: class=1, function=1, member=6, prototype=13, struct=2, typedef=1
- PrivateDependencyModuleNames: Core, GRDK, Json

### `Source/Runtime/Microsoft/GDKPackageManifest/Public/IGDKPackageManifestModule.h` (Public)


#### struct `FGDKPackageManifestChunk`  
`struct FGDKPackageManifestChunk`  
_L9-15_
- L11 _public member_ `int32 UnrealChunkID = 0;`
- L12 _public member_ `FString Tag;` — raw tag string with ; and # separators
- L13 _public member_ `FString Languages;`
- L14 _public member_ `bool bIsInitial;`

#### struct `FGDKPackageManifestFeature`  
`struct FGDKPackageManifestFeature`  
_L17-21_
- L19 _public member_ `FString Id;`
- L20 _public member_ `FString Tags;` — raw tag string with ; separators

#### class `IGDKPackageManifestModule`  
`class IGDKPackageManifestModule : public IModuleInterface, public IPlatformChunkInstallManifest`  
_L25-76_
- inherits: `IModuleInterface,IPlatformChunkInstallManifest`
- L34 _public function_ `static inline IGDKPackageManifestModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L40 _public prototype_ `virtual bool IsPakFileInstalled(const FString& InFilename) const = 0;` — determine whether the given pak file is installed or just a download placeholder with no file system backing
- L43 _public prototype_ `virtual bool HasManifest() const override = 0;` — determine if the package manifest was loaded successfully
- L46 _public prototype_ `virtual int32 GetChunkIDFromPakchunkIndex(int32 PakchunkIndex) const override = 0;` — determine the Unreal chunk ID that the given pak chunk index is stored in
- L49 _public prototype_ `virtual TArray<FString> GetPakFilesInChunk(int32 ChunkID) const override= 0;` — get the pak files that are stored in the given Unreal chunk
- L53 _public prototype_ `virtual const TArray<FGDKPackageManifestChunk>& GetChunks() const = 0;` — get all chunk data
- L56 _public prototype_ `virtual const FGDKPackageManifestChunk* GetChunk(int32 UnrealChunkID) const = 0;` — get data for a specific unreal chunk
- L59 _public prototype_ `virtual const TArray<FGDKPackageManifestFeature>& GetFeatures() const = 0;` — get all feature data
- L62 _public prototype_ `virtual const TArray<FName>& GetLanguages() const = 0;` — get all languages
- L65 _public prototype_ `virtual const TArray<FName>& GetTags() const = 0;` — get all tags
- L69 _public prototype_ `virtual bool GetUnrealChunkIDsByFeature( const FString& Feature, TArray<int32>& OutUnrealChunkIDs ) const = 0;` — get chunks that are referred to by the given feature
- L72 _public prototype_ `virtual bool LoadManifestFromDLC( XPackageMountHandle MountHandle, const char* PackageIdentifier, const FString& MountPath ) = 0;` — DLC support
- L73 _public prototype_ `virtual void UnloadDLC( XPackageMountHandle MountHandle ) = 0;`
- L74 _public prototype_ `virtual bool IsPakFileInstalled(XPackageMountHandle MountHandle, const FString& InFilename) const = 0;`

#### Free symbols / members of external scopes

- L23 _typedef_ `typedef struct XPackageMountInstance* XPackageMountHandle;`
