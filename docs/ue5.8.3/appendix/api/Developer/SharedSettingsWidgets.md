# Developer / SharedSettingsWidgets

- module root: `Source/Developer/SharedSettingsWidgets`
- headers: 7; symbols: 111
- symbol kinds: class=6, delegate=2, enum=2, enumerator=7, function=8, macro=6, member=31, namespace=1, prototype=44, struct=1, typedef=3
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, InputCore, RHI, Slate, SlateCore, SourceControl, TargetPlatform
- PublicDependencyModuleNames: ExternalImagePicker

### `Source/Developer/SharedSettingsWidgets/Public/ManifestUpdateHelper.h` (Public)


#### class `FManifestUpdateHelper`  
`class FManifestUpdateHelper`  
_L16-42_
- desc: This is a utility class used to update individual sections of an XML manifest or .plist in raw string form. It is formatting sensitive and will fail if things are formatted in an unexpected manner. This is a stopgap measure, and will be replaced using a proper XML parser when it is ready for use.
- L19 _public prototype_ `FManifestUpdateHelper(const FString& InFilename);`
- L22 _public prototype_ `static bool ReplaceStringPortion(FString& InOutString, const FString& MatchPrefix, const FString& MatchSuffix, const FString& NewInfix);` — Replaces the text in InOutString between MatchPrefix and MatchSuffix with NewInfix, returning true if it was found
- L25 _public prototype_ `bool HasKey(const FString& MatchPrefix);` — Checks if a key exists matching MatchPrefix
- L28 _public prototype_ `void ReplaceKey(const FString& MatchPrefix, const FString& MatchSuffix, const FString& NewInfix);` — Replace a key in the manifest (between MatchPrefix and MatchSuffix) with NewInfix
- L31 _public prototype_ `bool Finalize(const FString& TargetFilename, bool bShowNotifyOnFailure = true, FFileHelper::EEncodingOptions EncodingOption = FFileHelper::EEncodingOptions::AutoDetect);` — Finalizes the updater, and writes it back to the file, returning true if successful, and false if there were any errors
- L34 _public function_ `FText GetFirstErrorMessage() const` — Returns the first error message
- L37 _private prototype_ `void WriteError(FText NewError);`
- L39 _private member_ `FText FirstErrorMessage;`
- L40 _private member_ `FString ManifestString;`
- L41 _private member_ `bool bManifestDirty;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API SHAREDSETTINGSWIDGETS_API`

### `Source/Developer/SharedSettingsWidgets/Public/PlatformIconInfo.h` (Public)


#### struct `FPlatformIconInfo`  
`struct FPlatformIconInfo`  
_L10-33_
- L18 _public member_ `FString IconPath;`
- L19 _public member_ `FText IconName;`
- L20 _public member_ `FText IconDescription;`
- L21 _public member_ `FIntPoint IconRequiredSize;`
- L22 _public member_ `ERequiredState RequiredState;`
- L24 _public function_ `FPlatformIconInfo(const FString& InIconPath, FText InIconName, FText InIconDescription, int32 RequiredWidth = -1, int32 RequiredHeight = -1, ERequiredState IsRequired = Optional) : IconPath(InIconPath) , IconName(InIconName) , IconDescription(InIconDescription) , IconRequiredSize(RequiredWidth, RequiredHeight) , RequiredState(IsRequired)`

#### enum `FPlatformIconInfo::ERequiredState`  
`enum ERequiredState`  
_L12-16_
- L14 _public enumerator_ `Required`
- L15 _public enumerator_ `Optional`

### `Source/Developer/SharedSettingsWidgets/Public/SExternalImageReference.h` (Public)


#### class `SExternalImageReference`  
`class SExternalImageReference : public SCompoundWidget`  
_L33-121_
- inherits: `SCompoundWidget`
- L35 _private function_ `SLATE_BEGIN_ARGS(SExternalImageReference) : _FileDescription(NSLOCTEXT("SExternalImageReference", "FileDescription", "External Image")) , _MaxDisplaySize(400.0f, 400.0f) , _RequiredSize(-1, -1) , _DeleteTargetWhenDefaultChosen(false) , _GenerateImageVisibility(EVisibility::Hidden) , _GenerateImageToolTipText(NSLOCTEXT("SExternalImageReference", "GenerateImage", "Generate Image"))`
- L45 _private prototype_ `SLATE_ARGUMENT(FText, FileDescription) SLATE_ARGUMENT(FVector2D, MaxDisplaySize) SLATE_ARGUMENT(FIntPoint, RequiredSize) SLATE_ARGUMENT(FOnPreExternalImageCopy, OnPreExternalImageCopy) SLATE_ARGUMENT(FOnPostExternalImageCopy, OnPostExternalImageCopy) SLATE_ARGUMENT(FOnGetPickerPath, OnGetPickerPath) SLATE_ARGUMENT(TSharedPtr<class IPropertyHandle>, PropertyHandle) SLATE_ARGUMENT(bool, DeleteTargetWhenDefaultChosen) SLATE_ARGUMENT(TArray<FString>, FileExtensions) SLATE_ARGUMENT(bool, DeletePreviousTargetWhenExtensionChanges) SLATE_ATTRIBUTE(EVisibility, GenerateImageVisibility) SLATE_ARGUMENT(FText, GenerateImageToolTipText);` — The description of the file, used in error messages/notifications
- L87 _public prototype_ `void Construct(const FArguments& InArgs, const FString& InBaseFilename, const FString& InOverrideFilename);`
- L91 _protected prototype_ `bool HandleExternalImagePicked(const FString& InChosenImage, const FString& InTargetImage);` — Delegate handler for when an image is picked
- L96 _protected member_ `FString BaseFilename;` — The image on disk that we will use if the override does not exist.
- L99 _protected member_ `FString OverrideFilename;` — The image on disk that the override image is stored as.
- L102 _protected member_ `FText FileDescription;` — The description of the file in question, e.g. 'image' or 'icon', used for error reporting
- L105 _protected member_ `FOnPreExternalImageCopy OnPreExternalImageCopy;` — Delegate fired before an image has been copied
- L108 _protected member_ `FOnPostExternalImageCopy OnPostExternalImageCopy;` — Delegate fired after an image has been copied
- L111 _protected member_ `TSharedPtr<class IPropertyHandle> PropertyHandle;` — A property handle to use if required
- L114 _protected member_ `bool bDeleteTargetWhenDefaultChosen;` — If true, the target image will be deleted if the default is chosen
- L117 _protected member_ `TArray<FString> Extensions;` — The extensions supported by this external reference
- L120 _protected member_ `bool bDeletePreviousTargetWhenExtensionChanges;` — If true, the previous target image will be deleted if the file extension changes

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API SHAREDSETTINGSWIDGETS_API`
- L18 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnPreExternalImageCopy, const FString& );` — Delegate fired before an image has been copied @param	InChosenImage	The path to the image that has been picked by the user. @return true if the operation was successful
- L18 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnPreExternalImageCopy, const FString& );` — Delegate fired before an image has been copied @param	InChosenImage	The path to the image that has been picked by the user. @return true if the operation was successful
- L25 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnPostExternalImageCopy, const FString& );` — Delegate fired after an image has been copied @param	InChosenImage	The path to the image that has been picked by the user. @return true if the operation was successful
- L25 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnPostExternalImageCopy, const FString& );` — Delegate fired after an image has been copied @param	InChosenImage	The path to the image that has been picked by the user. @return true if the operation was successful

### `Source/Developer/SharedSettingsWidgets/Public/SHyperlinkLaunchURL.h` (Public)


#### class `SHyperlinkLaunchURL`  
`class SHyperlinkLaunchURL : public SCompoundWidget`  
_L16-34_
- inherits: `SCompoundWidget`
- L18 _private function_ `SLATE_BEGIN_ARGS(SHyperlinkLaunchURL)`
- L27 _public prototype_ `void Construct(const FArguments& InArgs, const FString& InDestinationURL);`
- L30 _protected prototype_ `void OnNavigate();`
- L33 _protected member_ `FString DestinationURL;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API SHAREDSETTINGSWIDGETS_API`

### `Source/Developer/SharedSettingsWidgets/Public/SPlatformSetupMessage.h` (Public)


#### class `SPlatformSetupMessage`  
`class SPlatformSetupMessage : public SCompoundWidget`  
_L22-72_
- inherits: `SCompoundWidget`
- L33 _private function_ `SLATE_BEGIN_ARGS(SPlatformSetupMessage)`
- L45 _public prototype_ `void Construct(const FArguments& InArgs, const FString& InTargetFilename);`
- L47 _public prototype_ `TAttribute<bool> GetReadyToGoAttribute() const;`
- L50 _public prototype_ `virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override;` — SWidget interface
- L53 _private prototype_ `int32 GetSetupStateAsInt() const;`
- L54 _private prototype_ `bool IsReadyToGo() const;`
- L55 _private prototype_ `FSlateColor GetBorderColor() const;`
- L57 _private prototype_ `TSharedRef<SWidget> MakeRow(FName IconName, FText Message, FText ButtonMessage);`
- L59 _private prototype_ `FReply OnButtonPressed();`
- L61 _private prototype_ `void OnSourceControlOperationComplete(const FSourceControlOperationRef& InOperation, ECommandResult::Type InResult);`
- L64 _private prototype_ `ESetupState GetSetupStateBasedOnFile(bool bInitStatus);` — Returns the setup state of a specified file
- L67 _private prototype_ `void UpdateCache(bool bForceUpdate);` — Updates the cache CachedSetupState
- L69 _private member_ `FString TargetFilename;`
- L70 _private member_ `ESetupState CachedSetupState;`
- L71 _private member_ `FSimpleDelegate OnSetupClicked;`

#### enum `SPlatformSetupMessage::ESetupState`  
`enum ESetupState`  
_L24-31_
- L26 _public enumerator_ `MissingFiles`
- L27 _public enumerator_ `NeedsCheckout`
- L28 _public enumerator_ `ReadOnlyFiles`
- L29 _public enumerator_ `ReadyToModify`
- L30 _public enumerator_ `GettingStatus`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API SHAREDSETTINGSWIDGETS_API`

### `Source/Developer/SharedSettingsWidgets/Public/SSettingsEditorCheckoutNotice.h` (Public)


#### class `SSettingsEditorCheckoutNotice`  
`class SSettingsEditorCheckoutNotice : public SCompoundWidget`  
_L26-107_
- inherits: `SCompoundWidget`
- desc: Implements a widget that provides a notice for files that need to be checked out.
- L30 _public function_ `SLATE_BEGIN_ARGS(SSettingsEditorCheckoutNotice)`
- L33 _public prototype_ `SLATE_ATTRIBUTE(FString, ConfigFilePath) SLATE_EVENT(FSimpleDelegate, OnFileProbablyModifiedExternally) SLATE_END_ARGS() void Construct( const FArguments& InArgs );` — Called to get the filename of the config file for display
- L48 _public prototype_ `virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override;` — SWidget interface
- L52 _public prototype_ `bool IsUnlocked() const;` — Return true if the watched file can be modified (as of the last update)
- L55 _public function_ `void Invalidate()` — Force an update on the next tick
- L63 _private prototype_ `FReply HandleCheckOutButtonClicked( );` — Callback for clicking the 'Check Out' button.
- L66 _private prototype_ `FText HandleCheckOutButtonText( ) const;` — Callback for getting the text of the 'Check Out' button.
- L69 _private prototype_ `FText HandleCheckOutButtonToolTip( ) const;` — Callback for getting the tool tip text of the 'Check Out' button.
- L72 _private prototype_ `EVisibility HandleCheckOutButtonVisibility( ) const;` — Callback for determining the visibility of the check-out button.
- L75 _private function_ `int32 HandleNoticeSwitcherWidgetIndex( ) const` — Callback for getting the widget index for the notice switcher.
- L81 _private prototype_ `FText HandleLockedStatusText() const;` — Callback for getting the status text when the config is locked
- L84 _private prototype_ `FText HandleUnlockedStatusText() const;` — Callback for getting the status text when the config is unlocked
- L87 _private prototype_ `EVisibility HandleThrobberVisibility() const;` — Callback for getting the visibility of the source control throbber
- L90 _private prototype_ `FSlateColor GetLockedStatusTextColor() const;` — Callback to get the background color of the checkout wanring
- L94 _private member_ `FSimpleDelegate OnFileProbablyModifiedExternally;` — Called when the file was modified externally
- L97 _private member_ `TAttribute<FString> ConfigFilePath;` — The current file being watched
- L100 _private member_ `bool DefaultConfigCheckOutNeeded;` — Holds a flag indicating whether the section's configuration file needs to be checked out.
- L103 _private member_ `bool DefaultConfigQueryInProgress;` — Holds a flag indicating whether the section's configuration file has a source control status request in progress.
- L106 _private member_ `double LastDefaultConfigCheckOutTime;` — Holds a timer for checking whether the section's configuration file needs to be checked out.

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API SHAREDSETTINGSWIDGETS_API`
- L15 _namespace_ `namespace SettingsHelpers`
- L17 _prototype_ `bool IsSourceControlled(const FString& InFileToCheckOut, bool bForceSourceControlUpdate = false);` (scope `SettingsHelpers`)
- L18 _prototype_ `bool IsCheckedOut(const FString& InFileToCheckOut, bool bForceSourceControlUpdate = false);` (scope `SettingsHelpers`)
- L19 _prototype_ `bool CheckOutOrAddFile(const FString& InFileToCheckOut, bool bForceSourceControlUpdate = false, bool ShowErrorInNotification = true, FText* OutErrorMessage = nullptr);` (scope `SettingsHelpers`)
- L20 _prototype_ `bool MakeWritable(const FString& InFileToMakeWritable, bool ShowErrorInNotification = true, FText* OutErrorMessage = nullptr);` (scope `SettingsHelpers`)

### `Source/Developer/SharedSettingsWidgets/Public/ShaderFormatsPropertyDetails.h` (Public)


#### class `FShaderFormatsPropertyDetails`  
`class FShaderFormatsPropertyDetails : public TSharedFromThis<FShaderFormatsPropertyDetails>`  
_L20-72_
- inherits: `TSharedFromThis<FShaderFormatsPropertyDetails>`
- desc: Helper which implements details panel customizations for a device profiles parent property
- L24 _public typedef_ `typedef FText(Deprecated_GetFriendlyNameFromRHINameFnc)(const FString&);`
- L26 _public typedef_ `typedef FText (GetFriendlyNameFromRHINameFnc)(FName);`
- L27 _public typedef_ `typedef bool (FilterShaderPlatformFnc)(FName);`
- L36 _public prototype_ `FShaderFormatsPropertyDetails(IDetailLayoutBuilder* InDetailBuilder, const TCHAR* InProperty = TEXT("TargetedRHIs"), const TCHAR* InTitle` — Constructor for the parent property details view @param InDetailsBuilder - Where we are adding our property view to @param InProperty - The category name to override @param InTitle - Title for display
- L39 _public prototype_ `void SetOnUpdateShaderWarning(const FSimpleDelegate& Delegate);` — Simple delegate for updating shader version warning
- L42 _public prototype_ `void CreateTargetShaderFormatsPropertyView(ITargetPlatformSettings* TargetPlatform, GetFriendlyNameFromRHINameFnc* FriendlyNameFnc, FilterShaderPlatformFnc* FilterShaderPlatformFunc = nullptr, ECategoryPriority::Type InPriority = ECategoryPriority::Default);` — Create the UI to select which windows shader formats we are targeting
- L48 _public prototype_ `ECheckBoxState IsTargetedRHIChecked(FName InRHIName) const;` — @param InRHIName - The input RHI to check @returns Whether this RHI is currently enabled
- L53 _private prototype_ `void OnTargetedRHIChanged(ECheckBoxState InNewValue, FName InRHIName);` — Supported/Targeted RHI check boxes
- L58 _private member_ `IDetailLayoutBuilder* DetailBuilder;` — A handle to the detail view builder
- L61 _private member_ `TSharedPtr<IPropertyHandle> ShaderFormatsPropertyHandle;` — Access to the Parent Property
- L64 _private member_ `FString Property;` — The category name to override
- L68 _private member_ `FName Title;` — Title for display
- L71 _private member_ `TMap<FName, int> ShaderFormatOrder;` — Preserve shader format order when writing to property

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API SHAREDSETTINGSWIDGETS_API`
