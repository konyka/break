# Plugins / WebBrowserWidget

- module root: `Plugins/Runtime/WebBrowserWidget/Source/WebBrowserWidget`
- headers: 3; symbols: 36
- symbol kinds: class=3, delegate=3, function=2, member=10, prototype=18
- PrivateDependencyModuleNames: EditorFramework, UnrealEd, WebBrowserTexture
- PrivateIncludePathModuleNames: UnrealEd, WebBrowserTexture
- PublicDependencyModuleNames: Core, CoreUObject, Engine, Slate, SlateCore, UMG, WebBrowser

### `Plugins/Runtime/WebBrowserWidget/Source/WebBrowserWidget/Public/WebBrowser.h` (Public)


#### class `UWebBrowser`  
`class UWebBrowser : public UWidget`  
_L15-110_
- reflection: `UCLASS()`
- inherits: `UWidget`
- L20 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUrlChanged, const FText&, Text);`
- L21 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnBeforePopup, FString, URL, FString, Frame);`
- L22 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnConsoleMessage, const FString&, Message, const FString&, Source, int32, Line);`
- L30 _public prototype_ `void LoadURL(FString NewURL);` — `UFUNCTION(BlueprintCallable, Category="Web Browser")` — Load the specified URL @param NewURL New URL to load
- L39 _public prototype_ `void LoadString(FString Contents, FString DummyURL);` — `UFUNCTION(BlueprintCallable, Category="Web Browser")` — Load a string as data to create a web page @param Contents String to load @param DummyURL Dummy URL for the page
- L47 _public prototype_ `void ExecuteJavascript(const FString& ScriptText);` — `UFUNCTION(BlueprintCallable, Category = "Web Browser")` — Executes a JavaScript string in the context of the web page @param ScriptText JavaScript string to execute
- L53 _public prototype_ `FText GetTitleText() const;` — `UFUNCTION(BlueprintCallable, Category="Web Browser")` — Get the current title of the web page
- L61 _public prototype_ `FString GetUrl() const;` — `UFUNCTION(BlueprintCallable, Category = "Web Browser")` — Gets the currently loaded URL. @return The URL, or empty string if no document is loaded.
- L65 _public member_ `FOnUrlChanged OnUrlChanged;` — `UPROPERTY(BlueprintAssignable, Category = "Web Browser|Event")` — Called when the Url changes.
- L69 _public member_ `FOnBeforePopup OnBeforePopup;` — `UPROPERTY(BlueprintAssignable, Category = "Web Browser|Event")` — Called when a popup is about to spawn.
- L73 _public member_ `FOnConsoleMessage OnConsoleMessage;` — `UPROPERTY(BlueprintAssignable, Category = "Web Browser|Event")` — Called when the browser has console spew to print
- L78 _public prototype_ `virtual void SynchronizeProperties() override;`
- L81 _public prototype_ `virtual void ReleaseSlateResources(bool bReleaseChildren) override;`
- L84 _public prototype_ `virtual const FText GetPaletteCategory() override;`
- L90 _protected member_ `FString InitialURL;` — `UPROPERTY(EditAnywhere, Category=Appearance)` — URL that the browser will initially navigate to. The URL should include the protocol, eg http://
- L94 _protected member_ `bool bSupportsTransparency;` — `UPROPERTY(EditAnywhere, Category=Appearance)` — Should the browser window support transparency.
- L97 _protected member_ `TSharedPtr<class SWebBrowser> WebBrowserWidget;`
- L99 _protected member_ `UMaterialInterface* DefaultMaterial;`
- L100 _protected member_ `UMaterialInterface* DefaultTranslucentMaterial;`
- L104 _protected prototype_ `virtual TSharedRef<SWidget> RebuildWidget() override;` — UWidget interface
- L107 _protected prototype_ `void HandleOnConsoleMessage(const FString& Message, const FString& Source, int32 Line, EWebBrowserConsoleLogSeverity Severity);`
- L108 _protected prototype_ `void HandleOnUrlChanged(const FText& Text);`
- L109 _protected prototype_ `bool HandleOnBeforePopup(FString URL, FString Frame);`

#### Free symbols / members of external scopes

- L20 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUrlChanged, const FText&, Text);`
- L21 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnBeforePopup, FString, URL, FString, Frame);`
- L22 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnConsoleMessage, const FString&, Message, const FString&, Source, int32, Line);`

### `Plugins/Runtime/WebBrowserWidget/Source/WebBrowserWidget/Public/WebBrowserAssetManager.h` (Public)


#### class `UWebBrowserAssetManager`  
`class UWebBrowserAssetManager : public UObject`  
_L15-32_
- reflection: `UCLASS()`
- inherits: `UObject`
- L21 _public prototype_ `void LoadDefaultMaterials();` — `UE_DEPRECATED(5.8, "UWebBrowserAssetManager is deprecated. LoadDefaultMaterials is no longer necessary for the GetDefaultMaterial functions in IWebBrowserSingleton.")`
- L24 _public prototype_ `UMaterial* GetDefaultMaterial();` — `UE_DEPRECATED(5.8, "UWebBrowserAssetManager is deprecated. Please use the GetDefaultMaterial functions in IWebBrowserSingleton instead.")`
- L26 _public prototype_ `UMaterial* GetDefaultTranslucentMaterial();` — `UE_DEPRECATED(5.8, "UWebBrowserAssetManager is deprecated. Please use the GetDefaultMaterial functions in IWebBrowserSingleton instead.")`
- L30 _protected member_ `TSoftObjectPtr<UMaterial> DefaultMaterial;` — `UPROPERTY()`
- L31 _protected member_ `TSoftObjectPtr<UMaterial> DefaultTranslucentMaterial;`

### `Plugins/Runtime/WebBrowserWidget/Source/WebBrowserWidget/Public/WebBrowserWidgetModule.h` (Public)


#### class `IWebBrowserWidgetModule`  
`class IWebBrowserWidgetModule : public IModuleInterface`  
_L11-36_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L22 _public function_ `static inline IWebBrowserWidgetModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L32 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
