# Developer / ExternalImagePicker

- module root: `Source/Developer/ExternalImagePicker`
- headers: 2; symbols: 58
- symbol kinds: class=2, delegate=2, enum=1, enumerator=3, function=3, member=25, prototype=21, struct=1
- PrivateDependencyModuleNames: Core, DesktopPlatform, ImageCore, ImageWrapper, PropertyEditor, Slate, SlateCore

### `Source/Developer/ExternalImagePicker/Private/SExternalImagePicker.h` (Private)


#### class `SExternalImagePicker`  
`class SExternalImagePicker : public SCompoundWidget`  
_L17-155_
- inherits: `SCompoundWidget`
- desc: Widget for displaying and editing an external image reference (e.g., splash screen, platform icons, etc...)
- L21 _public function_ `SLATE_BEGIN_ARGS( SExternalImagePicker )`
- L24 _public prototype_ `SLATE_ARGUMENT(FString, TargetImagePath) SLATE_ARGUMENT(FString, DefaultImagePath) SLATE_ARGUMENT(FOnExternalImagePicked, OnExternalImagePicked) SLATE_ARGUMENT(FOnGetPickerPath, OnGetPickerPath) SLATE_ARGUMENT(FVector2D, MaxDisplayedImageDimensions) SLATE_ARGUMENT(FIntPoint, RequiredImageDimensions) SLATE_ARGUMENT(bool, RequiresSpecificSize) SLATE_ARGUMENT(TArray<FString>, Extensions) SLATE_ATTRIBUTE(EVisibility, GenerateImageVisibility) SLATE_ARGUMENT(FText, GenerateImageToolTipText);` — The path to the image we will be editing
- L54 _public prototype_ `SLATE_ARGUMENT(FOnClicked, OnGenerateImageClicked) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — Delegate fired when an Generate Image button is pressed
- L62 _private prototype_ `void ApplyImageWithExtenstion(const FString& Extension);` — Applies the target image with the given extension to the preview, or the default if the target is missing
- L65 _private prototype_ `void ApplyFirstValidImage();` — Applies the first valid image that matches one of the supported extensions
- L68 _private prototype_ `void ApplyImage();` — Applies the target image to the preview, or the default if the target is missing
- L71 _private prototype_ `void ApplyImage(const FString& ImagePath);` — Applies the image to the preview
- L74 _private prototype_ `void ApplyPlaceholderImage();` — Applies image used to indicate 'no image'
- L77 _private prototype_ `FReply OnPickFile();` — Delegate invoked when the 'pick file' button is clicked
- L80 _private prototype_ `FReply OnGenerateImageClickedInternal(FOnClicked UserOnGenerateImageClicked);` — Internal delegate invoked when the 'generate image' button is clicked, triggers supplied user delegate
- L83 _private prototype_ `const FSlateBrush* GetImage() const;` — Delegate to retrieve the image to display
- L86 _private prototype_ `FText GetImageTooltip() const;` — Returns a tooltip for the selected image, indicating the size
- L89 _private prototype_ `FVector2D GetConstrainedImageSize() const;` — Helper function to resize the image while retaining aspect ratio
- L92 _private prototype_ `FOptionalSize GetImageWidth() const;` — Delegate used to constrain the width of the displayed image
- L95 _private prototype_ `FOptionalSize GetImageHeight() const;` — Delegate used to constrain the height of the displayed image
- L98 _private prototype_ `TSharedPtr< FSlateDynamicImageBrush > LoadImageAsBrush( const FString& ImagePath );` — Load an image off disk & make a Slate brush out of it
- L101 _private prototype_ `void HandleResetToDefault();` — Delegate handler for resetting the image to default
- L104 _private prototype_ `FText GetResetToDefaultText() const;` — Delegate handler for getting the text to use when resetting to default
- L107 _private prototype_ `bool DiffersFromDefault() const;` — Check to see if we differ from the default
- L110 _private member_ `TSharedPtr<SHorizontalBox> HorizontalBox;`
- L113 _private member_ `TSharedPtr<FSlateDynamicImageBrush> ImageBrush;` — The brush we use to draw the splash
- L116 _private member_ `TSharedPtr<SHorizontalBox> ImageBox;` — The box that contains the image preview
- L119 _private member_ `FString DefaultImagePath;` — The path to the default image to display
- L122 _private member_ `FString TargetImagePath;` — The path to the image we will be editing
- L125 _private member_ `TArray<FString> Extensions;` — The extensions of the file types we want to use
- L128 _private member_ `FOnExternalImagePicked OnExternalImagePicked;` — Delegate fired when an image is picked
- L131 _private member_ `FOnGetPickerPath OnGetPickerPath;` — The path the picker will use to start from
- L142 _private member_ `EFileLocation TypeOfImage;` — Which file are we using?
- L145 _private member_ `FVector2D MaxDisplayedImageDimensions;` — The dimensions the image display should be constrained to
- L148 _private member_ `FIntPoint RequiredImageDimensions;` — The dimensions the image ought to be (if bRequiresSpecificSize is set)
- L151 _private member_ `bool bRequiresSpecificSize;` — Does the image need to be a specific size?
- L154 _private member_ `TSharedPtr<class SErrorText> ErrorHintWidget;` — The error hint widget used to display bad sizes

#### enum `SExternalImagePicker::EFileLocation`  
`enum EFileLocation`  
_L134-139_
- desc: The kind of image being used
- L136 _public enumerator_ `UsingDummyPlaceholderImage`
- L137 _public enumerator_ `UsingDefaultImage`
- L138 _public enumerator_ `UsingTargetImage`

### `Source/Developer/ExternalImagePicker/Public/IExternalImagePickerModule.h` (Public)


#### struct `FExternalImagePickerConfiguration`  
`struct FExternalImagePickerConfiguration`  
_L28-71_
- desc: Used for configuring the external image picker
- L30 _public function_ `FExternalImagePickerConfiguration() : MaxDisplayedImageDimensions(400.0f, 400.0f) , bRequiresSpecificSize(false)`
- L37 _public member_ `FString TargetImagePath;` — The image on disk that the external image is stored as.
- L40 _public member_ `FString DefaultImagePath;` — The image on disk that we will use if the target does not exist.
- L43 _public member_ `FOnGetPickerPath OnGetPickerPath;` — The path the picker will use to start from
- L46 _public member_ `FOnExternalImagePicked OnExternalImagePicked;` — Delegate fired when picking a new image.
- L49 _public member_ `FVector2D MaxDisplayedImageDimensions;` — The dimensions the image display should be constrained to. Aspect ratio is maintained.
- L52 _public member_ `FIntPoint RequiredImageDimensions;` — The size the actual image needs to be (ignored unless bRequiresSpecificSize is set)
- L55 _public member_ `bool bRequiresSpecificSize;` — Does the image need to be a specific size?
- L58 _public member_ `TArray<FString> FileExtensions;` — The image on disk that we will use if the target does not exist.
- L61 _public member_ `TAttribute<EVisibility> GenerateImageVisibility;` — Whether the button to generate a new image should be shown.
- L64 _public member_ `FText GenerateImageToolTipText;` — Tooltip for Generate Image button
- L67 _public member_ `FOnClicked OnGenerateImageClicked;` — Delegate fired when an Generate Image button is pressed
- L70 _public member_ `TSharedPtr<class IPropertyHandle> PropertyHandle;` — A property handle to use if required

#### class `IExternalImagePickerModule`  
`class IExternalImagePickerModule : public IModuleInterface`  
_L76-97_
- inherits: `IModuleInterface`
- desc: Public interface for splash screen editor module
- L85 _public prototype_ `virtual TSharedRef<class SWidget> MakeEditorWidget(const FExternalImagePickerConfiguration& InConfiguration) = 0;` — Make a widget used for displaying & editing splash screens @param @return the image editing widget
- L92 _public function_ `static IExternalImagePickerModule& Get()` — Gets a reference to the ExternalImagePicker module instance. @return A reference to the ExternalImagePicker module.

#### Free symbols / members of external scopes

- L17 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FOnExternalImagePicked, const FString& , const FString& );` — Delegate fired when picking a new image. @param	InChosenImage	The path to the image that has been picked by the user. @param	InTargetImage	The path to the target image that this picker represents. @return true if the image should be refreshed
- L17 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FOnExternalImagePicked, const FString& , const FString& );` — Delegate fired when picking a new image. @param	InChosenImage	The path to the image that has been picked by the user. @param	InTargetImage	The path to the target image that this picker represents. @return true if the image should be refreshed
- L23 _delegate_ `DECLARE_DELEGATE_RetVal(FString, FOnGetPickerPath);` — Delegate fired to get the path to start picking from. @return the path the picker will use to start from
- L23 _prototype_ `DECLARE_DELEGATE_RetVal(FString, FOnGetPickerPath);` — Delegate fired to get the path to start picking from. @return the path the picker will use to start from
