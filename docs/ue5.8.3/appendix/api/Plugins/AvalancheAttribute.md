# Plugins / AvalancheAttribute

- module root: `Plugins/VirtualProduction/Avalanche/Source/AvalancheAttribute`
- headers: 5; symbols: 27
- symbol kinds: class=5, function=6, member=3, prototype=13
- PrivateDependencyModuleNames: Engine, Slate, SlateCore
- PublicDependencyModuleNames: AvalancheTag, Core, CoreUObject

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheAttribute/Public/AvaAttribute.h` (Public)


#### class `UAvaAttribute`  
`class UAvaAttribute : public UObject`  
_L10-20_
- reflection: `UCLASS(MinimalAPI, Abstract, EditInlineNew)`
- inherits: `UObject`
- desc: Attributes are objects that are added to other objects to describe said object
- L16 _public function_ `virtual FText GetDisplayName() const` — Gets the display name to use for the attribute

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheAttribute/Public/AvaNameAttribute.h` (Public)


#### class `UAvaNameAttribute`  
`class UAvaNameAttribute : public UAvaAttribute`  
_L10-24_
- reflection: `UCLASS(MinimalAPI, DisplayName="Name Attribute")`
- inherits: `UAvaAttribute`
- desc: Attribute that holds a name
- L16 _public prototype_ `virtual FText GetDisplayName() const override;`
- L20 _public prototype_ `void SetName(FName InName);` — `UFUNCTION()`
- L23 _public member_ `FName Name;` — `UPROPERTY(EditAnywhere, Setter, Category="Attributes")`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheAttribute/Public/Tags/AvaTagAttribute.h` (Public)


#### class `UAvaTagAttribute`  
`class UAvaTagAttribute : public UAvaTagAttributeBase`  
_L11-35_
- reflection: `UCLASS(MinimalAPI, DisplayName="Tag Attribute")`
- inherits: `UAvaTagAttributeBase`
- desc: Attribute that holds a tag handle, for single tag referencing
- L17 _public prototype_ `virtual FText GetDisplayName() const override;`
- L21 _public prototype_ `virtual bool SetTagHandle(const FAvaTagHandle& InTagHandle) override;`
- L22 _public prototype_ `virtual bool ClearTagHandle(const FAvaTagHandle& InTagHandle) override;`
- L23 _public prototype_ `virtual bool ContainsTag(const FAvaTagHandle& InTagHandle) const override;`
- L24 _public prototype_ `virtual bool HasValidTagHandle() const override;`
- L28 _public function_ `void SetTag(const FAvaTagHandle& InTag)` — `UFUNCTION()`
- L34 _public member_ `FAvaTagHandle Tag;` — `UPROPERTY(EditAnywhere, Setter, Category="Attributes")`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheAttribute/Public/Tags/AvaTagAttributeBase.h` (Public)


#### class `UAvaTagAttributeBase`  
`class UAvaTagAttributeBase : public UAvaAttribute`  
_L12-55_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UAvaAttribute`
- desc: Base implementation of an attribute that represent one or more tags in some form
- L22 _public function_ `virtual bool SetTagHandle(const FAvaTagHandle& InTagHandle)` — Sets/Adds the given tag handle to the tag attribute @param InTagHandle the tag handle to add @return true if the tag handle was added, false if this tag handle already existed in the tag attribute
- L32 _public function_ `virtual bool ClearTagHandle(const FAvaTagHandle& InTagHandle)` — Clears/Removes the given tag handle from the tag attribute @param InTagHandle the tag handle to remove @return true if the tag handle was removed, false if this tag handle was not present in the tag attribute and nothing was removed
- L42 _public function_ `virtual bool ContainsTag(const FAvaTagHandle& InTagHandle) const` — Checks whether the resolved tag from the given tag handle exists in the tag attribute @param InTagHandle the tag handle to resolve into a tag and check if the tag attribute contains it @return true if the resolved tag exists in the tag attribute, false otherwise.
- L51 _public function_ `virtual bool HasValidTagHandle() const` — Checks whether the tag attribute has any tag handle that could resolve to a valid tag @return true if the tag attribute has a valid tag handle that could resolve to a tag

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheAttribute/Public/Tags/AvaTagContainerAttribute.h` (Public)


#### class `UAvaTagContainerAttribute`  
`class UAvaTagContainerAttribute : public UAvaTagAttributeBase`  
_L11-32_
- reflection: `UCLASS(MinimalAPI, DisplayName="Tag Container Attribute")`
- inherits: `UAvaTagAttributeBase`
- desc: Attribute that holds a tag container handle, for multi-tag referencing
- L17 _public prototype_ `virtual FText GetDisplayName() const override;`
- L21 _public prototype_ `virtual bool SetTagHandle(const FAvaTagHandle& InTagHandle) override;`
- L22 _public prototype_ `virtual bool ClearTagHandle(const FAvaTagHandle& InTagHandle) override;`
- L23 _public prototype_ `virtual bool ContainsTag(const FAvaTagHandle& InTagHandle) const override;`
- L24 _public prototype_ `virtual bool HasValidTagHandle() const;`
- L28 _public prototype_ `void SetTagContainer(const FAvaTagHandleContainer& InTagContainer);` — `UFUNCTION()`
- L31 _public member_ `FAvaTagHandleContainer TagContainer;` — `UPROPERTY(EditAnywhere, Setter, Category="Attributes")`
