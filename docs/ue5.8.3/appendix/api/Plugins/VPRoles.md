# Plugins / VPRoles

- module root: `Plugins/Experimental/VirtualProduction/VPRoles/Source/VPRoles`
- headers: 3; symbols: 43
- symbol kinds: class=2, delegate=3, enum=1, enumerator=2, function=1, member=8, prototype=26
- PrivateDependencyModuleNames: GameplayTagsEditor, UnrealEd, VPSettings
- PublicDependencyModuleNames: Core, CoreUObject, Engine, GameplayTags

### `Plugins/Experimental/VirtualProduction/VPRoles/Source/VPRoles/Private/VPRolesModule.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogVPRoles, Log, Log);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogVPRoles, Log, Log);`

### `Plugins/Experimental/VirtualProduction/VPRoles/Source/VPRoles/Private/VPRolesSettings.h` (Private)


#### class `UVPRolesUserSettings`  
`class UVPRolesUserSettings : public UObject`  
_L10-32_
- reflection: `UCLASS(config=UserVPRoles)`
- inherits: `UObject`
- L21 _private member_ `FGameplayTagContainer Roles;` — `UPROPERTY(config)` — The machine role(s) in a virtual production context. @note The role may be override via the command line, "-VPRole=[Role.SubRole1|Role.SubRole2]"
- L25 _private member_ `TSet<FName> RoleSources;` — `UPROPERTY(config)` — The files that contain the available VP Roles.
- L29 _private member_ `TArray<FString> CachedRoles;` — `UPROPERTY(config)` — Cached available roles since the list isn't available outside of editor.

### `Plugins/Experimental/VirtualProduction/VPRoles/Source/VPRoles/Public/VPRolesSubsystem.h` (Public)


#### class `UVirtualProductionRolesSubsystem`  
`class UVirtualProductionRolesSubsystem : public UEngineSubsystem`  
_L20-172_
- reflection: `UCLASS()`
- inherits: `UEngineSubsystem`
- desc: Subsystem for common Virtual Production roles operations. The machine role(s) in a virtual production context read from the command line. ie. "-VPRole=[Role.SubRole1|Role.SubRole2]"
- L25 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRolesChanged, const TArray<FString>&, EnabledRoles);`
- L26 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnRolesChangedNative, const TArray<FString>&);`
- L30 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L31 _public prototype_ `virtual void Deinitialize() override;`
- L39 _public prototype_ `TArray<FString> GetActiveRoles() const;` — `UFUNCTION(BlueprintCallable, Category = "Virtual Production|Roles")` — Get the currently active Virtual Production roles. @return The names of the current virtual production roles.
- L45 _public prototype_ `bool HasActiveRole(const FString& Role) const;` — `UFUNCTION(BlueprintCallable, Category = "Virtual Production|Roles")` — @return Whether a role is currently active.
- L51 _public prototype_ `FString GetActiveRolesString() const;` — `UFUNCTION(BlueprintCallable, Category = "Virtual Production|Roles")` — @return the currently active Virtual Production roles as a comma separated string representation.
- L60 _public prototype_ `void SetActiveRoles(const TArray<FString>& Roles);` — `UFUNCTION(BlueprintCallable, Category = "Virtual Production|Roles")` — Set the current Virtual Production roles. @param Roles the list of roles to set as active. @note The roles must already have been added either through the UI or through AddRole. @note This will clear the previous current roles.
- L67 _public prototype_ `TArray<FString> GetAllRoles() const;` — `UFUNCTION(BlueprintCallable, Category = "Virtual Production|Roles")` — Get all available roles that can be set as current. @return The available roles.
- L77 _public prototype_ `bool AddRole(const FString& RoleName);` — `UFUNCTION(BlueprintCallable, Category = "Virtual Production|Roles")` — Add a new virtual production role. @param RoleName the name of the role to add. @return Whether the operation succeeded. @note This will attempt to modify the underlying VProles.ini file so it must be checked out or made writable or the operation will fail.
- L86 _public prototype_ `bool RemoveRole(const FString& RoleName);` — `UFUNCTION(BlueprintCallable, Category = "Virtual Production|Roles")` — Remove a virtual production role. @param RoleName the name of the role to remove. @return Whether the operation succeeded. @note This will attempt to modify the underlying VProles.ini file so it must be checked out or made writable or the operation will fail.
- L92 _public function_ `FOnRolesChangedNative& OnRolesChanged()` — Delegate called when the roles are modified, ie. role is added, current roles are replaced, etc.
- L100 _public prototype_ `bool IsUsingCommandLineRoles() const;` — @return Whether we are using the roles passed in command line if any.
- L105 _public prototype_ `bool HasCommandLineRoles() const;` — @return Whether roles were passed through the command line.
- L110 _public prototype_ `void UseCommandLineRoles(bool bUseCommandLineRoles);` — Set whether the command line roles should be used if any were specified.
- L115 _public prototype_ `const TSet<FName>& GetRoleSources() const;` — @return The list of sources that provide VP roles.
- L120 _public prototype_ `FName GetDefaultRoleSource() const;` — @return The name of the default VP role ini file.
- L125 _public prototype_ `bool HasActiveRole(const FGameplayTag& Role) const;` — @return Whether a role is currently active.
- L131 _public prototype_ `const FGameplayTagContainer& GetRolesContainer_Private() const;` — Get the roles container, either from the command line or from the VP Roles settings. @note New code should not use this method, it is only provided for backwards compatibility.
- L137 _public member_ `FOnRolesChanged OnRolesChangedBP;` — `UPROPERTY(BlueprintAssignable, Category = "Virtual Production|Roles", meta = (ScriptName ="OnRolesChanged"))` — Delegate called when the roles are modified, ie. role is added, current roles are replaced, etc.
- L141 _private prototype_ `void BroadcastRolesChanged() const;` — Save roles to the VP Role config file and trigger a broadcast on the OnRolesChanged delegates.
- L143 _private prototype_ `void AddRoleSource(FName TagSource);` — Add a role source to the VP Roles settings. Used to keep track of which config files provided VP Roles.
- L145 _private prototype_ `bool ImportCurrentRolesFromCommandLine();` — Parses command line roles.
- L147 _private prototype_ `void ImportCurrentRolesFromDeprecatedSetting();` — Imports VP Roles from the VP Settings.
- L149 _private prototype_ `static const FGameplayTagContainer& GetRolesContainerFallback();` — Fallback handler that returns an empty tag container.
- L156 _private prototype_ `FGameplayTagContainer* GetRolesContainerPtr(EGetRolesPtrSource Source);` — Get a pointer to the roles gameplay tag container
- L158 _private prototype_ `void ImportRoleSourcesFromVPSettings();` — Gather all gameplay tag sources from the tags that were imported from the VP settings.
- L162 _private member_ `FOnRolesChangedNative OnRolesChangedNative;` — Delegate called when the roles are modified, ie. role is added, current roles are replaced, etc.
- L164 _private member_ `TPimplPtr<FGameplayTagContainer> CommandLineRoles;` — Holds the role container populated from the roles specified on the command line.
- L166 _private member_ `bool bUseCommandLineRoles = false;` — Whether command line roles should be used.
- L168 _private member_ `bool bHasCommandLineRoles = false;` — Whether command line roles were specified.

#### enum `UVirtualProductionRolesSubsystem::EGetRolesPtrSource`  
`enum class EGetRolesPtrSource`  
_L150-154_
- L152 _public enumerator_ `Settings`
- L153 _public enumerator_ `CommandLine`

#### Free symbols / members of external scopes

- L25 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRolesChanged, const TArray<FString>&, EnabledRoles);`
- L26 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnRolesChangedNative, const TArray<FString>&);`
