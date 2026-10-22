# Developer / Settings

- module root: `Source/Developer/Settings`
- headers: 8; symbols: 179
- symbol kinds: class=8, delegate=12, function=20, member=28, prototype=105, typedef=6
- PrivateDependencyModuleNames: CoreUObject
- PublicDependencyModuleNames: Core

### `Source/Developer/Settings/Private/SettingsCategory.h` (Private)


#### class `FSettingsCategory`  
`class FSettingsCategory : public TSharedFromThis<FSettingsCategory> , public ISettingsCategory`  
_L17-130_
- inherits: `TSharedFromThis<FSettingsCategory>,ISettingsCategory`
- desc: Implements a settings category.
- L28 _public prototype_ `FSettingsCategory( const FName& InName );` — Creates and initializes a new instance. @param InName The category's name.
- L43 _public prototype_ `ISettingsSectionRef AddSection( const FName& SectionName, const FText& InDisplayName, const FText& InDescription, const TWeakObjectPtr<UObject>& SettingsObject );` — Adds a settings section to this settings category. If a section with the specified settings objects already exists, the existing section will be returned. @param SectionName The name of the settings section to add. @param DisplayName The section's localized display name. @param Description The section's localized description text. @param SettingsObject The object that holds the section's settings. @return The added settings section.
- L56 _public prototype_ `ISettingsSectionRef AddSection( const FName& SectionName, const FText& InDisplayName, const FText& InDescription, const TSharedRef<SWidget>& CustomWidget );` — Adds a settings section to this settings category. If a section with the specified settings objects already exists, the existing section will be returned. @param SectionName The name of the settings section to add. @param DisplayName The section's localized display name. @param Description The section's localized description text. @param CustomWidget A custom settings widget. @return The added settings section.
- L66 _public prototype_ `void Describe( const FText& InDisplayName, const FText& InDescription );` — Updates the details of this settings category. @param InDisplayName The category's localized display name. @param InDescription The category's localized description text. @param InIconName The name of the category's icon. @return The category.
- L73 _public prototype_ `void RemoveSection( const FName& SectionName );` — Removes a settings section. @param SectionName The name of the section to remove.
- L81 _public prototype_ `void ReinstancingComplete( IReload* Reload );` — Invoked when reinstancing is complete.  Allows for settings objects to update their settings object pointers. @param Reload The active reload
- L88 _public function_ `virtual const FText& GetDescription() const override`
- L93 _public function_ `virtual const FText& GetDisplayName() const override`
- L98 _public function_ `virtual const FName& GetName() const override`
- L104 _public prototype_ `virtual ISettingsSectionPtr GetSection( const FName& SectionName, bool bIgnoreVisibility = false ) const override;` — Gets a section if it's visible according to IsSectionVisiblePermissionList. bIgnoreVisibility=true will return the section even if it's filtered
- L107 _public prototype_ `virtual int32 GetSections( TArray<ISettingsSectionPtr>& OutSections, bool bIgnoreVisibility = false ) const override;` — Gets all visible sections according to IsSectionVisiblePermissionList. bIgnoreVisibility=true will return sections even if they're filtered
- L109 _public function_ `virtual FNamePermissionList* GetSectionVisibilityPermissionList() override`
- L117 _private member_ `FText Description;` — Holds the category's description text.
- L120 _private member_ `FText DisplayName;` — Holds the category's localized display name.
- L123 _private member_ `TMap<FName, TSharedPtr<FSettingsSection>> Sections;` — Holds the collection of setting sections.
- L126 _private member_ `FName Name;` — Holds the category's name.
- L129 _private member_ `FNamePermissionList SectionVisibilityPermissionList;` — Determines which sections are returned with GetSection and GetSections

### `Source/Developer/Settings/Private/SettingsContainer.h` (Private)


#### class `FSettingsContainer`  
`class FSettingsContainer : public ISettingsContainer`  
_L15-147_
- inherits: `ISettingsContainer`
- desc: Implements a settings container.
- L25 _public prototype_ `FSettingsContainer( const FName& InName );` — Creates and initializes a new instance. @param InName The container's name.
- L41 _public prototype_ `ISettingsSectionPtr AddSection( const FName& CategoryName, const FName& SectionName, const FText& InDisplayName, const FText& InDescription, const TWeakObjectPtr<UObject>& SettingsObject );` — Adds a settings section to the specified settings category (using a settings object). If a section with the specified settings objects already exists, the existing section will be replaced. @param CategoryName The name of the category to add the section to. @param SectionName The name of the settings section to add. @param DisplayName The section's localized display name. @param Description The section's localized description text. @param SettingsObject The object that holds the section's settings. @return The added settings section, or nullptr if the category does not exist.
- L55 _public prototype_ `ISettingsSectionPtr AddSection( const FName& CategoryName, const FName& SectionName, const FText& InDisplayName, const FText& InDescription, const TSharedRef<SWidget>& CustomWidget );` — Adds a settings section to the specified category (using a custom settings widget). If a section with the specified settings objects already exists, the existing section will be replaced. @param CategoryName The name of the category to add the section to. @param SectionName The name of the settings section to add. @param DisplayName The section's localized display name. @param Description The section's localized description text. @param CustomWidget A custom settings widget. @return The added settings section, or nullptr if the category does not exist.
- L63 _public prototype_ `void RemoveSection( const FName& CategoryName, const FName& SectionName );` — Removes a settings section. @param CategoryName The name of the category that contains the section. @param SectionName The name of the section to remove.
- L71 _public prototype_ `void ReinstancingComplete(IReload* Reload);` — Invoked when reinstancing is complete.  Allows for settings objects to update their settings object pointers. @param Reload The active reload
- L78 _public prototype_ `virtual void Describe( const FText& InDisplayName, const FText& InDescription, const FName& InIconName ) override;`
- L79 _public prototype_ `virtual void DescribeCategory( const FName& CategoryName, const FText& InDisplayName, const FText& InDescription ) override;`
- L80 _public prototype_ `virtual int32 GetCategories( TArray<TSharedPtr<ISettingsCategory>>& OutCategories ) const override;`
- L82 _public function_ `virtual TSharedPtr<ISettingsCategory> GetCategory( const FName& CategoryName ) const override`
- L87 _public function_ `virtual const FText& GetDescription() const override`
- L92 _public function_ `virtual const FText& GetDisplayName() const override`
- L97 _public function_ `virtual const FName& GetIconName() const override`
- L102 _public function_ `virtual const FName& GetName() const override`
- L107 _public function_ `virtual FOnCategoryModified& OnCategoryModified() override`
- L112 _public function_ `virtual FOnSectionRemoved& OnSectionRemoved() override`
- L117 _public prototype_ `virtual void SetCategorySortPriority(FName CategoryName, float Priority) override;`
- L118 _public prototype_ `virtual void ResetCategorySortPriority(FName CategoryName) override;`
- L123 _private member_ `TMap<FName, TSharedPtr<FSettingsCategory>> Categories;` — Holds the collection of setting categories.
- L126 _private member_ `FText Description;` — Holds the container's description text.
- L129 _private member_ `FText DisplayName;` — Holds the container's localized display name.
- L132 _private member_ `FName IconName;` — Holds the name of the container's icon.
- L135 _private member_ `FName Name;` — Holds the container's name.
- L138 _private member_ `TMap<FName, float> CategorySortPriorities;` — Category sort priorities
- L143 _private member_ `FOnCategoryModified CategoryModifiedDelegate;` — Holds a delegate that is executed when a settings category has been added or modified.
- L146 _private member_ `FOnSectionRemoved SectionRemovedDelegate;` — Holds a delegate that is executed when a settings section has been removed.

### `Source/Developer/Settings/Private/SettingsSection.h` (Private)


#### class `FSettingsSection`  
`class FSettingsSection : public ISettingsSection`  
_L16-173_
- inherits: `ISettingsSection`
- desc: Implements a project settings section.
- L30 _public prototype_ `FSettingsSection( const ISettingsCategoryRef& InCategory, const FName& InName, const FText& InDisplayName, const FText& InDescription, const TWeakObjectPtr<UObject>& InSettingsObject );` — Creates and initializes a new settings section from the given settings object. @param InCategory The settings category that owns this section. @param InName The setting section's name. @param InDisplayName The section's localized display name. @param InDescription The section's localized description text. @param InSettingsObject The object that holds the settings for this section.
- L41 _public prototype_ `FSettingsSection( const ISettingsCategoryRef& InCategory, const FName& InName, const FText& InDisplayName, const FText& InDescription, const TSharedRef<SWidget>& InCustomWidget );` — Creates and initializes a new settings section from the given custom settings widget. @param InCategory The settings category that owns this section. @param InName The setting section's name. @param InDisplayName The section's localized display name. @param InDescription The section's localized description text. @param InCustomWidget A custom settings widget.
- L49 _public prototype_ `void ReinstancingComplete(IReload* Reload);` — Invoked when reinstancing is complete.  Allows for settings objects to update their settings object pointers. @param Reload The active reload
- L56 _public prototype_ `virtual bool CanEdit() const override;`
- L57 _public prototype_ `virtual bool CanExport() const override;`
- L58 _public prototype_ `virtual bool CanImport() const override;`
- L59 _public prototype_ `virtual bool CanResetDefaults() const override;`
- L60 _public prototype_ `virtual bool CanSave() const override;`
- L61 _public prototype_ `virtual bool CanSaveDefaults() const override;`
- L62 _public prototype_ `virtual bool Export( const FString& Filename ) override;`
- L63 _public prototype_ `virtual TWeakPtr<ISettingsCategory> GetCategory() override;`
- L64 _public prototype_ `virtual TWeakPtr<SWidget> GetCustomWidget() const override;`
- L65 _public prototype_ `virtual const FText& GetDescription() const override;`
- L66 _public prototype_ `virtual const FText& GetDisplayName() const override;`
- L67 _public prototype_ `virtual const FName& GetName() const override;`
- L68 _public prototype_ `virtual TWeakObjectPtr<UObject> GetSettingsObject() const override;`
- L69 _public prototype_ `virtual FText GetStatus() const override;`
- L70 _public prototype_ `virtual bool HasDefaultSettingsObject() override;`
- L71 _public prototype_ `virtual bool Import( const FString& Filename ) override;`
- L73 _public function_ `virtual FOnCanEdit& OnCanEdit() override`
- L78 _public function_ `virtual FOnExport& OnExport() override`
- L83 _public function_ `virtual FOnImport& OnImport() override`
- L88 _public function_ `virtual FOnModified& OnModified() override`
- L93 _public function_ `virtual FOnResetDefaults& OnResetDefaults() override`
- L98 _public function_ `virtual FOnSave& OnSave() override`
- L103 _public function_ `virtual FOnSaveDefaults& OnSaveDefaults() override`
- L108 _public function_ `virtual FOnStatus& OnStatus() override`
- L113 _public function_ `virtual FOnSelect& OnSelect() override`
- L118 _public prototype_ `virtual bool ResetDefaults() override;`
- L119 _public prototype_ `virtual bool NotifySectionOnPropertyModified() override;`
- L120 _public prototype_ `virtual bool Save() override;`
- L121 _public prototype_ `virtual bool SaveDefaults() override;`
- L123 _public prototype_ `virtual void Select() override;`
- L128 _private member_ `TWeakPtr<ISettingsCategory> Category;` — Holds a pointer to the settings category that owns this section.
- L131 _private member_ `TWeakPtr<SWidget> CustomWidget;` — Holds the section's custom editor widget.
- L134 _private member_ `FText Description;` — Holds the section's description text.
- L137 _private member_ `FText DisplayName;` — Holds the section's localized display name.
- L140 _private member_ `FName Name;` — Holds the section's name.
- L143 _private member_ `TWeakObjectPtr<UObject> SettingsObject;` — Holds the settings object.
- L148 _private member_ `FOnCanEdit CanEditDelegate;` — Holds a delegate that is executed to check whether a settings section can be edited.
- L151 _private member_ `FOnExport ExportDelegate;` — Holds a delegate that is executed when the settings section should be exported to a file.
- L154 _private member_ `FOnImport ImportDelegate;` — Holds a delegate that is executed when the settings section should be imported from a file.
- L157 _private member_ `FOnModified ModifiedDelegate;` — Holds a delegate that is executed after the settings section has been modified.
- L160 _private member_ `FOnResetDefaults ResetDefaultsDelegate;` — Holds a delegate that is executed when the settings section should have its values reset to default.
- L163 _private member_ `FOnSaveDefaults SaveDefaultsDelegate;` — Holds a delegate that is executed when a settings section should have its values saved as default.
- L166 _private member_ `FOnSave SaveDelegate;` — Holds a delegate that is executed when a settings section should have its values saved.
- L169 _private member_ `FOnStatus StatusDelegate;` — Holds a delegate that is executed to retrieve a status message for a settings section.
- L172 _private member_ `FOnSelect SelectDelegate;` — Holds a delegate that is executed when a settings section has been selected.

### `Source/Developer/Settings/Public/ISettingsCategory.h` (Public)


#### class `ISettingsCategory`  
`class ISettingsCategory`  
_L16-63_
- desc: Interface for setting categories. A setting category is a collection of setting sections that logically belong together (i.e. all project settings or all platform settings). Each section then contains the actual settings in the form of UObject properties.
- L25 _public prototype_ `virtual const FText& GetDescription() const = 0;` — Gets the category's localized description text. @return Description text.
- L32 _public prototype_ `virtual const FText& GetDisplayName() const = 0;` — Gets the category's localized display name. @return Display name.
- L40 _public prototype_ `virtual TSharedPtr<ISettingsSection> GetSection( const FName& SectionName, bool bIgnoreVisibility = false ) const = 0;` — Gets the settings section with the specified name. @param SectionName The name of the section to get. @return The settings section, or nullptr if it doesn't exist.
- L48 _public prototype_ `virtual int32 GetSections( TArray<TSharedPtr<ISettingsSection>>& OutSections, bool bIgnoreVisibility = false ) const = 0;` — Gets the setting sections contained in this category. @param OutSections Will hold the collection of sections. @return The number of sections returned.
- L55 _public prototype_ `virtual const FName& GetName() const = 0;` — Gets the category's name. @return Category name.
- L57 _public prototype_ `virtual class FNamePermissionList* GetSectionVisibilityPermissionList() = 0;`
- L62 _public prototype_ `virtual ~ISettingsCategory() = default;` — Virtual destructor.

#### Free symbols / members of external scopes

- L67 _typedef_ `typedef TSharedPtr<ISettingsCategory> ISettingsCategoryPtr;` — Type definition for shared pointers to instances of ISettingsCategory.
- L70 _typedef_ `typedef TSharedRef<ISettingsCategory> ISettingsCategoryRef;` — Type definition for shared references to instances of ISettingsCategory.

### `Source/Developer/Settings/Public/ISettingsContainer.h` (Public)


#### class `ISettingsContainer`  
`class ISettingsContainer`  
_L17-123_
- desc: Interface for setting containers. A settings container is a collection of setting categories. Each category holds a collection of setting sections, which contain the actual settings in the form of UObject properties.
- L28 _public prototype_ `virtual void Describe( const FText& InDisplayName, const FText& InDescription, const FName& InIconName ) = 0;` — Updates the details of this settings container. @param InDisplayName The container's localized display name. @param InDescription The container's localized description text. @param InIconName The name of the container's icon.
- L37 _public prototype_ `virtual void DescribeCategory( const FName& CategoryName, const FText& DisplayName, const FText& Description ) = 0;` — Updates the details of the specified settings category. @param CategoryName The name of the category to update. @param DisplayName The category's localized display name. @param Description The category's localized description text.
- L45 _public prototype_ `virtual int32 GetCategories( TArray<TSharedPtr<ISettingsCategory>>& OutCategories ) const = 0;` — Gets the setting categories. @param OutCategories Will hold the collection of categories. @return The number of categories returned.
- L52 _public prototype_ `virtual TSharedPtr<ISettingsCategory> GetCategory( const FName& CategoryName ) const = 0;` — Gets the category with the specified name. @return The category, or nullptr if it doesn't exist.
- L59 _public prototype_ `virtual const FText& GetDescription() const = 0;` — Gets the container's localized description text. @return Description text.
- L66 _public prototype_ `virtual const FText& GetDisplayName() const = 0;` — Gets the container's localized display name. @return Display name.
- L73 _public prototype_ `virtual const FName& GetIconName() const = 0;` — Gets the name of the container's icon. @return Icon image name.
- L80 _public prototype_ `virtual const FName& GetName() const = 0;` — Gets the container's name. @return Container name.
- L92 _public prototype_ `virtual void SetCategorySortPriority(FName CategoryName, float Priority) = 0;` — Sets the sort priority of a category A lower priority value means the category is listed first The priority value is 0 by default @note A category named after FApp::GetProjectName() has a priority of -1.0 by default @note A category named "Advanced" has a priority of 1.0 by default @param ContainerName Settings container name @param CategoryName Name of category to set the priority on @param Priority Priority value
- L99 _public prototype_ `virtual void ResetCategorySortPriority(FName CategoryName) = 0;` — Resets the sort priority of a category to its default value @note Sort priority @param CategoryName Name of category to set the priority on
- L108 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnCategoryModified, const FName&) virtual FOnCategoryModified& OnCategoryModified() = 0;` — A delegate that is executed when a settings category has been added or modified. @return The delegate.
- L116 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSectionRemoved, const TSharedRef<ISettingsSection>&) virtual FOnSectionRemoved& OnSectionRemoved() = 0;` — A delegate that is executed when a settings section has been removed. @return The delegate.
- L122 _public prototype_ `virtual ~ISettingsContainer() = default;` — Virtual destructor.

#### Free symbols / members of external scopes

- L108 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnCategoryModified, const FName&) virtual FOnCategoryModified& OnCategoryModified() = 0;` — A delegate that is executed when a settings category has been added or modified. @return The delegate.
- L116 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSectionRemoved, const TSharedRef<ISettingsSection>&) virtual FOnSectionRemoved& OnSectionRemoved() = 0;` — A delegate that is executed when a settings section has been removed. @return The delegate.
- L127 _typedef_ `typedef TSharedPtr<ISettingsContainer> ISettingsContainerPtr;` — Type definition for shared pointers to instances of ISettingsContainer.
- L130 _typedef_ `typedef TSharedRef<ISettingsContainer> ISettingsContainerRef;` — Type definition for shared references to instances of ISettingsContainer.

### `Source/Developer/Settings/Public/ISettingsModule.h` (Public)


#### class `ISettingsModule`  
`class ISettingsModule : public IModuleInterface`  
_L16-113_
- inherits: `IModuleInterface`
- desc: Interface for settings UI modules.
- L26 _public prototype_ `virtual void GetContainerNames( TArray<FName>& OutNames ) const = 0;` — Gets the names of all known setting containers. @param OutNames Will contain the collection of names.
- L34 _public prototype_ `virtual TSharedPtr<ISettingsContainer> GetContainer( const FName& ContainerName ) = 0;` — Gets the global settings container with the specified name. @param ContainerName The name of the container to get. @return The settings container, or nullptr if it doesn't exist.
- L49 _public prototype_ `virtual TSharedPtr<ISettingsSection> RegisterSettings( const FName& ContainerName, const FName& CategoryName, const FName& SectionName, const FText& DisplayName, const FText& Description, const TWeakObjectPtr<UObject>& SettingsObject ) = 0;` — Adds a settings section to the specified settings container (using a settings object). If a section with the specified settings objects already exists, the existing section will be replaced. @param ContainerName The name of the container that will contain the settings. @param CategoryName The name of the category within the container. @param SectionName The name of the section within the category. @param DisplayName The section's localized display name. @param Description The section's localized description text. @param SettingsObject The object that holds the section's settings. @return The added settings section, or nullptr if the category does not exist.
- L64 _public prototype_ `virtual TSharedPtr<ISettingsSection> RegisterSettings( const FName& ContainerName, const FName& CategoryName, const FName& SectionName, const FText& DisplayName, const FText& Description, const TSharedRef<SWidget>& CustomWidget ) = 0;` — Adds a settings section to the specified settings container (using a custom settings widget). If a section with the specified settings objects already exists, the existing section will be replaced. @param ContainerName The name of the container that will contain the settings. @param CategoryName The name of the category within the container. @param SectionName The name of the section within the category. @param DisplayName The section's localized display name. @param Description The section's localized description text. @param CustomWidget A custom settings widget. @return The added settings section, or nullptr if the category does not exist.
- L72 _public prototype_ `virtual void RegisterViewer( const FName& ContainerName, ISettingsViewer& SettingsViewer ) = 0;` — Registers a viewer for the specified settings container. @param ContainerName The name of the settings container to register a viewer for. @param SettingsViewer The viewer to register.
- L81 _public prototype_ `virtual void ShowViewer( const FName& ContainerName, const FName& CategoryName, const FName& SectionName ) = 0;` — Shows the settings viewer for the specified settings container. @param ContainerName The name of the section's container. @param CategoryName The name of the section's category. @param SectionName The name of the section to show.
- L90 _public prototype_ `virtual void UnregisterSettings( const FName& ContainerName, const FName& CategoryName, const FName& SectionName ) = 0;` — Removes a settings section from the specified settings container. @param ContainerName The name of the container that to remove the settings from. @param CategoryName The name of the category within the container. @param SectionName The name of the section within the category.
- L97 _public prototype_ `virtual void UnregisterViewer( const FName& ContainerName ) = 0;` — Unregisters the currently assigned viewer for the specified settings container. @param ContainerName The name of the settings container to unregister the viewer for.
- L106 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnContainerAdded, const FName&) virtual FOnContainerAdded& OnContainerAdded() = 0;` — A delegate that is executed when a settings container has been added. @return The delegate.
- L112 _public prototype_ `virtual ~ISettingsModule() = default;` — Virtual destructor.

#### Free symbols / members of external scopes

- L106 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnContainerAdded, const FName&) virtual FOnContainerAdded& OnContainerAdded() = 0;` — A delegate that is executed when a settings container has been added. @return The delegate.

### `Source/Developer/Settings/Public/ISettingsSection.h` (Public)


#### class `ISettingsSection`  
`class ISettingsSection`  
_L18-251_
- desc: Interface for setting sections. A setting section is a collection of settings that logically belong together (i.e. all settings for a console platform). Internally, the individual settings are represented as the properties of an UObject. One or more setting sections can the be hierarchically arranged in a setting category.
- L27 _public prototype_ `virtual bool CanEdit() const = 0;` — Checks whether this section can be edited right now. @return true if the section can be edited, false otherwise.
- L34 _public prototype_ `virtual bool CanExport() const = 0;` — Checks whether this section can export its settings to a file. @return true if file export is supported, false otherwise.
- L41 _public prototype_ `virtual bool CanImport() const = 0;` — Checks whether this section can import its settings from a file. @return true if file import is supported, false otherwise.
- L48 _public prototype_ `virtual bool CanResetDefaults() const = 0;` — Checks whether this section can have its settings reset to default. @return true if resetting to default is supported, false otherwise.
- L58 _public prototype_ `virtual bool CanSave() const = 0;` — Checks whether this section can have its settings saved. This method does not indicate whether saving would actually succeed. For example, saving may be aborted by a ModifiedDelegate handler. @return true if saving is supported, false otherwise.
- L65 _public prototype_ `virtual bool CanSaveDefaults() const = 0;` — Checks whether this section can have its settings saved as default. @return true if saving as default is supported, false otherwise.
- L73 _public prototype_ `virtual bool Export( const FString& Filename ) = 0;` — Exports the settings in this section to the specified file. @param Filename The path to the file. @return true if the settings were exported, false otherwise.
- L80 _public prototype_ `virtual TWeakPtr<ISettingsCategory> GetCategory() = 0;` — Gets the settings category that this section belongs to. @return The owner category.
- L87 _public prototype_ `virtual TWeakPtr<SWidget> GetCustomWidget() const = 0;` — Gets the custom settings widget for this settings section. @return The custom widget.
- L94 _public prototype_ `virtual const FText& GetDescription() const = 0;` — Gets the section's localized description text. @return Description text.
- L101 _public prototype_ `virtual const FText& GetDisplayName() const = 0;` — Gets the section's localized display name. @return Display name.
- L108 _public prototype_ `virtual const FName& GetName() const = 0;` — Gets the section's name. @return Section name.
- L115 _public prototype_ `virtual TWeakObjectPtr<UObject> GetSettingsObject() const = 0;` — Gets the UObject holding the section's settings. @return Settings object.
- L122 _public prototype_ `virtual FText GetStatus() const = 0;` — Gets the section's optional status text. @return Status text.
- L129 _public prototype_ `virtual bool HasDefaultSettingsObject() = 0;` — Checks whether this section holds a settings object that saves directly to default configuration files. @return true if it has a default settings object, false otherwise.
- L137 _public prototype_ `virtual bool Import( const FString& Filename ) = 0;` — Imports the settings in this section from the specified file. @param Filename The path to the file. @return true if the settings were imported, false otherwise.
- L144 _public prototype_ `virtual bool ResetDefaults() = 0;` — Resets the settings in this section to their default value. @return true if the section was reset, false otherwise.
- L151 _public prototype_ `virtual bool NotifySectionOnPropertyModified() = 0;` — Notifies a section that a single property has been modified @return true if settings should be saved, false otherwise.
- L158 _public prototype_ `virtual bool Save() = 0;` — Saves the settings in this section. @return true if settings were saved, false otherwise.
- L165 _public prototype_ `virtual bool SaveDefaults() = 0;` — Saves the settings in this section as defaults. @return true if settings were saved, false otherwise.
- L170 _public prototype_ `virtual void Select() = 0;` — Called when the current section is selected.
- L179 _public prototype_ `DECLARE_DELEGATE_RetVal(bool, FOnCanEdit) virtual FOnCanEdit& OnCanEdit() = 0;` — A delegate that is executed to check whether a settings section can be edited. The return value indicates whether the section can be edited.
- L188 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnExport, const FString&) virtual FOnExport& OnExport() = 0;` — A delegate that is executed when a settings section should export its values to a file. The first parameter is the path to the file to export to. The return value indicates whether exporting succeeded.
- L197 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnImport, const FString&) virtual FOnImport& OnImport() = 0;` — A delegate that is executed when a settings section should import its values from a file. The first parameter is the path to the file to import from. The return value indicates whether importing succeeded.
- L205 _public prototype_ `DECLARE_DELEGATE_RetVal(bool, FOnModified) virtual FOnModified& OnModified() = 0;` — A delegate that is executed when a settings section has been modified. The return value indicates whether the modifications should be saved.
- L213 _public prototype_ `DECLARE_DELEGATE_RetVal(bool, FOnResetDefaults) virtual FOnResetDefaults& OnResetDefaults() = 0;` — A delegate that is executed when a settings section should have its values reset to default. The return value indicates whether resetting to defaults succeeded.
- L221 _public prototype_ `DECLARE_DELEGATE_RetVal(bool, FOnSave) virtual FOnSave& OnSave() = 0;` — A delegate that is executed when a settings section should have its values saved. The return value indicates whether saving succeeded.
- L229 _public prototype_ `DECLARE_DELEGATE_RetVal(bool, FOnSaveDefaults) virtual FOnSaveDefaults& OnSaveDefaults() = 0;` — A delegate that is executed when a settings section should have its values saved as default. The return value indicates whether saving as default succeeded.
- L237 _public prototype_ `DECLARE_DELEGATE_RetVal(FText, FOnStatus) virtual FOnStatus& OnStatus() = 0;` — A delegate that is executed to retrieve a status message for a settings section. The return value is status message.
- L245 _public prototype_ `DECLARE_DELEGATE(FOnSelect) virtual FOnSelect& OnSelect() = 0;` — A delegate that is executed to check whether a settings section can be edited.
- L250 _public prototype_ `virtual ~ISettingsSection() = default;` — Virtual destructor.

#### Free symbols / members of external scopes

- L179 _delegate_ `DECLARE_DELEGATE_RetVal(bool, FOnCanEdit) virtual FOnCanEdit& OnCanEdit() = 0;` — A delegate that is executed to check whether a settings section can be edited. The return value indicates whether the section can be edited.
- L188 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnExport, const FString&) virtual FOnExport& OnExport() = 0;` — A delegate that is executed when a settings section should export its values to a file. The first parameter is the path to the file to export to. The return value indicates whether exporting succeeded.
- L197 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnImport, const FString&) virtual FOnImport& OnImport() = 0;` — A delegate that is executed when a settings section should import its values from a file. The first parameter is the path to the file to import from. The return value indicates whether importing succeeded.
- L205 _delegate_ `DECLARE_DELEGATE_RetVal(bool, FOnModified) virtual FOnModified& OnModified() = 0;` — A delegate that is executed when a settings section has been modified. The return value indicates whether the modifications should be saved.
- L213 _delegate_ `DECLARE_DELEGATE_RetVal(bool, FOnResetDefaults) virtual FOnResetDefaults& OnResetDefaults() = 0;` — A delegate that is executed when a settings section should have its values reset to default. The return value indicates whether resetting to defaults succeeded.
- L221 _delegate_ `DECLARE_DELEGATE_RetVal(bool, FOnSave) virtual FOnSave& OnSave() = 0;` — A delegate that is executed when a settings section should have its values saved. The return value indicates whether saving succeeded.
- L229 _delegate_ `DECLARE_DELEGATE_RetVal(bool, FOnSaveDefaults) virtual FOnSaveDefaults& OnSaveDefaults() = 0;` — A delegate that is executed when a settings section should have its values saved as default. The return value indicates whether saving as default succeeded.
- L237 _delegate_ `DECLARE_DELEGATE_RetVal(FText, FOnStatus) virtual FOnStatus& OnStatus() = 0;` — A delegate that is executed to retrieve a status message for a settings section. The return value is status message.
- L245 _delegate_ `DECLARE_DELEGATE(FOnSelect) virtual FOnSelect& OnSelect() = 0;` — A delegate that is executed to check whether a settings section can be edited.
- L255 _typedef_ `typedef TSharedPtr<ISettingsSection> ISettingsSectionPtr;` — Type definition for shared pointers to instances of ISettingsSection.
- L258 _typedef_ `typedef TSharedRef<ISettingsSection> ISettingsSectionRef;` — Type definition for shared references to instances of ISettingsSection.

### `Source/Developer/Settings/Public/ISettingsViewer.h` (Public)


#### class `ISettingsViewer`  
`class ISettingsViewer`  
_L10-26_
- desc: Interface for settings tabs.
- L20 _public prototype_ `virtual void ShowSettings( const FName& CategoryName, const FName& SectionName ) = 0;` — Shows the settings tab that belongs to this viewer with the specified settings section pre-selected. @param CategoryName The name of the section's category. @param SectionName The name of the section to select.
- L25 _public prototype_ `virtual ~ISettingsViewer() = default;` — Virtual destructor.
