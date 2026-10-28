# Plugins / DirectoryPlaceholder

- module root: `Plugins/Developer/DirectoryPlaceholder/Source/DirectoryPlaceholder`
- headers: 5; symbols: 25
- symbol kinds: class=6, member=5, prototype=14
- PrivateDependencyModuleNames: AssetDefinition, ContentBrowser, ContentBrowserData, Core, CoreUObject, DeveloperSettings, Engine, Projects, Slate, SlateCore, ToolMenus, UnrealEd
- PublicDependencyModuleNames: 

### `Plugins/Developer/DirectoryPlaceholder/Source/DirectoryPlaceholder/Private/AssetDefinition_DirectoryPlaceholder.h` (Private)


#### class `UAssetDefinition_DirectoryPlaceholder`  
`class UAssetDefinition_DirectoryPlaceholder : public UAssetDefinitionDefault`  
_L11-23_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- desc: Asset definition for a UDirectoryPlaceholder asset
- L17 _protected prototype_ `virtual FText GetAssetDisplayName() const override;`
- L18 _protected prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L19 _protected prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L20 _protected prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L21 _protected prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`

### `Plugins/Developer/DirectoryPlaceholder/Source/DirectoryPlaceholder/Private/DirectoryPlaceholderFactory.h` (Private)


#### class `UDirectoryPlaceholderFactory`  
`class UDirectoryPlaceholderFactory : public UFactory`  
_L11-22_
- reflection: `UCLASS(hidecategories=Object)`
- inherits: `UFactory`
- desc: Implements a factory for UDirectoryPlaceholder objects
- L16 _protected prototype_ `UDirectoryPlaceholderFactory();`
- L19 _protected prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L20 _protected prototype_ `virtual bool CanCreateNew() const override;`

### `Plugins/Developer/DirectoryPlaceholder/Source/DirectoryPlaceholder/Private/DirectoryPlaceholderSettings.h` (Private)


#### class `UDirectoryPlaceholderSettings`  
`class UDirectoryPlaceholderSettings : public UDeveloperSettings`  
_L13-42_
- reflection: `UCLASS(config = EditorPerProjectUserSettings)`
- inherits: `UDeveloperSettings`
- desc: Directory Placeholder Settings
- L18 _public prototype_ `UDirectoryPlaceholderSettings() = default;`
- L22 _public member_ `bool bAutomaticallyCreatePlaceholders = true;` — `UPROPERTY(Config, EditAnywhere, Category = "Default")` — If enabled, Directory Placeholder assets will be automatically created in new folders
- L26 _public member_ `bool bAutomaticallyCreatePlaceholdersInProjectContent = true;` — `UPROPERTY(Config, EditAnywhere, Category = "Default", meta=(EditCondition = bAutomaticallyCreatePlaceholders))` — If enabled, Directory Placeholder assets will be automatically created in new folders that are created within the Project Content
- L30 _public member_ `bool bAutomaticallyCreatePlaceholdersInProjectPlugins = true;` — `UPROPERTY(Config, EditAnywhere, Category = "Default", meta = (EditCondition = bAutomaticallyCreatePlaceholders))` — If enabled, Directory Placeholder assets will be automatically created in new folders that are created within the Project Plugins
- L34 _public member_ `bool bAutomaticallyCreatePlaceholdersInAdditionalPlugins = true;` — `UPROPERTY(Config, EditAnywhere, Category = "Default", meta = (EditCondition = bAutomaticallyCreatePlaceholders))` — If enabled, Directory Placeholder assets will be automatically created in new folders that are created within all Additional Plugins
- L41 _public member_ `TArray<FString> ExcludePaths;` — `UPROPERTY(Config, EditAnywhere, Category = "Default", meta = (EditCondition = bAutomaticallyCreatePlaceholders))` — Directory Placeholder assets will not be automatically created in new folders under any of the paths in this list. Use content browser paths, such as "/Game/MyFolder/" or "/MyPlugin/MyFolder/".

### `Plugins/Developer/DirectoryPlaceholder/Source/DirectoryPlaceholder/Public/DirectoryPlaceholder.h` (Public)


#### class `UDirectoryPlaceholder`  
`class UDirectoryPlaceholder : public UObject`  
_L17-23_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: Extremely lightweight object that can be used as a placeholder in an otherwise empty directory. The presence of a placeholder object allows that directory to be submitted to source control.
- L22 _public prototype_ `UDirectoryPlaceholder() = default;`

#### class `UDirectoryPlaceholderSearchFilter`  
`class UDirectoryPlaceholderSearchFilter : public UContentBrowserFrontEndFilterExtension`  
_L27-35_
- reflection: `UCLASS()`
- inherits: `UContentBrowserFrontEndFilterExtension`
- desc: Content Browser filter used to show/hide directory placeholder assets
- L33 _protected prototype_ `virtual void AddFrontEndFilterExtensions(TSharedPtr<FFrontendFilterCategory> DefaultCategory, TArray<TSharedRef<FFrontendFilter>>& InOutFilterList) const override;`

### `Plugins/Developer/DirectoryPlaceholder/Source/DirectoryPlaceholder/Public/DirectoryPlaceholderUtils.h` (Public)


#### class `UDirectoryPlaceholderLibrary`  
`class UDirectoryPlaceholderLibrary : public UBlueprintFunctionLibrary`  
_L13-29_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- desc: Library functions for operations on directory placeholder assets
- L20 _public prototype_ `static void CleanupPlaceholdersInPath(const FString& Path);` — `UFUNCTION(BlueprintCallable, Category = "DirectoryPlaceholder")` — Delete all unnecessary placeholder assets in this folder (and sub-folders)
- L24 _public prototype_ `static void CleanupPlaceholdersInPaths(const TArray<FString>& Paths);` — `UFUNCTION(BlueprintCallable, Category = "DirectoryPlaceholder")` — Delete all unnecessary placeholder assets in these folders (and sub-folders)
- L28 _public prototype_ `static void DeletePlaceholdersInPath(const FString& Path);` — `UFUNCTION(BlueprintCallable, Category = "DirectoryPlaceholder")` — Delete all placeholder assets in this folder (and sub-folders)
