# Plugins / SlateScreenReader

- module root: `Plugins/Experimental/SlateScreenReader/Source/SlateScreenReader`
- headers: 5; symbols: 49
- symbol kinds: class=4, delegate=1, function=4, member=1, prototype=39
- PrivateDependencyModuleNames: ApplicationCore, InputCore, ScreenReader, Slate, SlateCore, TextToSpeech
- PublicDependencyModuleNames: Core, CoreUObject, Engine

### `Plugins/Experimental/SlateScreenReader/Source/SlateScreenReader/Private/SlateScreenReader.h` (Private)


#### class `FSlateScreenReader`  
`class FSlateScreenReader : public FScreenReaderBase`  
_L15-32_
- inherits: `FScreenReaderBase`
- desc: A basic screen reader that can work for desktop and consoles that use Slate. All feedback to users are done through speech.
- L19 _public prototype_ `FSlateScreenReader() = delete;`
- L20 _public prototype_ `FSlateScreenReader(const FSlateScreenReader& Other) = delete;`
- L21 _public prototype_ `explicit FSlateScreenReader(const TSharedRef<GenericApplication>& InPlatformApplication);`
- L22 _public prototype_ `virtual ~FSlateScreenReader();`
- L24 _public prototype_ `FSlateScreenReader& operator=(const FSlateScreenReader& Other) = delete;`
- L28 _protected prototype_ `virtual void OnActivate() override;`
- L29 _protected prototype_ `virtual void OnDeactivate() override;`
- L30 _protected prototype_ `virtual void OnAccessibleEventRaised(const FAccessibleEventArgs& Args) override;`

### `Plugins/Experimental/SlateScreenReader/Source/SlateScreenReader/Private/SlateScreenReaderBuilder.h` (Private)


#### class `FSlateScreenReaderBuilder`  
`class FSlateScreenReaderBuilder : public IScreenReaderBuilder`  
_L7-15_
- inherits: `IScreenReaderBuilder`
- L10 _public function_ `FSlateScreenReaderBuilder()`
- L11 _public function_ `virtual ~FSlateScreenReaderBuilder()`
- L13 _public prototype_ `virtual TSharedRef<FScreenReaderBase> Create(const IScreenReaderBuilder::FArgs& InArgs) override;`

### `Plugins/Experimental/SlateScreenReader/Source/SlateScreenReader/Private/SlateScreenReaderLog.h` (Private)


#### Free symbols / members of external scopes

- L6 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogSlateScreenReader, Log, All);`
- L6 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogSlateScreenReader, Log, All);`

### `Plugins/Experimental/SlateScreenReader/Source/SlateScreenReader/Public/SlateScreenReaderEngineSubsystem.h` (Public)


#### class `USlateScreenReaderEngineSubsystem`  
`class USlateScreenReaderEngineSubsystem : public UEngineSubsystem`  
_L32-235_
- reflection: `UCLASS()`
- inherits: `UEngineSubsystem`
- desc: The engine subsystem for the Slate screen reader. A screen reader is a framework that provides vision accessibility services for screen reader useres. A screen reader user is a single user of the screen reader framework and can be thought of as a user of a hardware device such as keyboard/mouse or a controller. Screen reader users must be registered with the screen reader framework for them to receive feedback from the accessibility services provided by the screen reader framework. This class should be the entryway for C++ programmers and BP useres alike to interact with the screen reader system. The subsystem must be activated before the screen reader services can be used. For C++ users, please retrieve the screen reader and interact with the screen reader users from there. Example: USlateScreenReaderEngineSubsystem ::Get().ActivateScreenReader(); // Registers a screen reader user with Id 0. A screen reader user should correspond to a hardware input device such as a keyboard or controller like FSlateUser USlateScreenReaderEngineSubsystem ::Get().GetScreenReader()->RegisterUser(0); TSharedRef<FScreenReaderUser> User = USlateScreenReaderEngineSubsystem::Get().GetScreenReader()->GetUserChecked(0); // Screen reader users are inactive when they are first registered and need to be explicitly activated. User->Activate(); static const FText HelloWorld = LOCTEXT("HelloWorld", "Hello World"); // Requests "Hello World" to be spoken to the screen reader user User->RequestSpeak(FScreenRe
- L36 _public prototype_ `USlateScreenReaderEngineSubsystem();`
- L37 _public prototype_ `virtual ~USlateScreenReaderEngineSubsystem();`
- L40 _public prototype_ `static USlateScreenReaderEngineSubsystem& Get();` — Convenience method to retrieve the screen reader engine subsystem.
- L50 _public prototype_ `void ActivateScreenReader();` — `UFUNCTION(BlueprintCallable, Category="SlateScreenReader")` — Activates the underlying screen reader. Use this to allow screen reader users to register with the screen reader and receive accessible feedback via text to speech and get access to other screen reader services. A basic workflow with activation would be: ActivateScreenReader() -> RegisterScreenReaderUser() -> ActivateScreenReaderUser() @see RegisterScreenReaderUser(), ActivateScreenReaderUser()
- L59 _public prototype_ `void DeactivateScreenReader();` — `UFUNCTION(BlueprintCallable, Category="SlateScreenReader")` — Deactivates the underlying screen reader and prevents screen reader users from getting any accessible feedback via text to speech or using any other screen reader services. Note: When the screen reader is deactivated, none of the registered screen reader users will be unregistered or cleared. This allows you to deactivate the screen reader to prevent accessible services such as text to speech from triggering and then activate the screen reader again to continue those services.
- L66 _public prototype_ `bool IsScreenReaderActive() const;` — `UFUNCTION(BlueprintCallable, Category = "SlateScreenReader")` — Returns true if the screen reader is currently active and accessibility services such as text to speech can be used by the screen reader users. Otherwise, it returns false.
- L76 _public prototype_ `FScreenReaderReply ActivateUser(UPARAM(DisplayName = "Screen Reader User` — `UFUNCTION(BlueprintCallable, Category = "SlateScreenReader")` — Activates a screen reader user and fulfill requests for accessibility services such as text to speech that clients can make. When screen reader users are first registered with a screen reader, they are deactivated by default. Users must explicitly activate the screen reader user. If the passed in user Id does not correspond to a registered screen reader user, nothing will happen. @param InUserId The user Id of the screen reader user to request activation @return FScreenReaderReply::Handled() if the screen reader user is successfully activated. Else FScreenReaderReply::Unhandled() is returned.
- L86 _public prototype_ `FScreenReaderReply DeactivateUser(UPARAM(DisplayName = "Screen Reader User` — `UFUNCTION(BlueprintCallable, Category = "SlateScreenReader")` — Deactivates the screen reader and disables all announcement and text to speech services making them do nothing. If the passed in user Id does not correspond to a registered screen reader user, nothing will happen. @param InUserId The user Id of the screen reader user to request deactivation. The Id should correspond to the Slate user id of an input device. If unsure, use Id 0. @return FScreenReaderReply::Handled() if the screen reader user is successfully deactivated. Else FScreenReaderReply::Unhandled() is returned.
- L98 _public prototype_ `FScreenReaderReply RegisterUser(UPARAM(DisplayName = "Screen Reader User` — `UFUNCTION(BlueprintCallable, Category = "SlateScreenReader")` — Registers a provided user Id to the screen reader framework and allows the screen reader user to receive and respond to accessible events and accessible input. Does nothing if the passed in Id is already registered. Note: A successfully registered screen reader user is deactivated by default and will not respond to accessible events or accessible input. You need to call ActivateUser() to allow the newly registered screen reader user to respond to the accessible events and accessible input. @param InUserId The user Id of the screen reader user to register. The Id should correspond to a valid Slate user Id for an active hardware input device. If unsure, use Id 0. @return FScreenReaderReply::Handled() if the screen reader user is successfully registered. Else FScreenReaderReply::Unhandled() is returned. @see ActivateUser()
- L107 _public prototype_ `FScreenReaderReply UnregisterUser(UPARAM(DisplayName = "Screen Reader User` — `UFUNCTION(BlueprintCallable, Category = "SlateScreenReader")` — Unregisters a provided user Id from the screen reader framework and deactivates the user. The unregistered user will no longer receive or respond to accessible events and input. Nothing will happen if the provided user Id has not been registered with the screen reader. @param InUserId The user Id to unregister from the screen reader framework. @return FScreenReaderReply::Handled() if the screen reader user is successfully unregistered. Else FScreenReaderReply::Unhandled() is returned.
- L113 _public prototype_ `bool IsUserRegistered(UPARAM(DisplayName = "Screen Reader User Id") i` — `UFUNCTION(BlueprintCallable, Category = "SlateScreenReader")` — Returns true if the passed in screen reader user Id is already registered. Else false is returned. @param InUserId The user Id to check for registration.
- L129 _public prototype_ `FScreenReaderReply RequestSpeak(UPARAM(DisplayName = "Screen Reader User Id") int32 InUserId, UPARAM(DisplayName = "Announcement") FScreenRe` — `UFUNCTION(BlueprintCallable, Category = "SlateScreenReader")` — Requests an announcement to be spoken to the screen reader user. This is the main mechanism to provide text to speech auditory feedback to end users. Calling this function does not guarantee that the announcement will be spoken via text to speech and be heard by a user. All announcements spoken via text to speech will be asynchronous and will not block the game thread. If the screen reader user is active and no announcements are currently spoken, the announcement will be spoken immediately. If another announcement is currently being spoken, the passed in announcement could be queued or interrupt the currently spoken announcement. @param InUserId The user Id of the screen reader user the announcement is intended for @param InAnnouncement - The announcement requested to be spoken to the screen reader user @return FScreenReaderReply::Handled() if the request was successfully processed. Else return FScreenReader::Unhandled() @see FScreenReaderAnnouncement, FScreenReaderAnnouncementInfo
- L140 _public prototype_ `FScreenReaderReply RequestSpeakFocusedWidget(UPARAM(DisplayName = "Screen Reader User` — `UFUNCTION(BlueprintCallable, Category = "SlateScreenReader")` — Requests the information about the accessibility widget a user is focused on to be read out. If nothing is currently being focused on by the screen reader user, nothing will be read out. The same guarantees about the announcement being spoken in RequestSpeak() apply for this function. Nothing will happen if the passed in user Id is not already registered with the screen reader. @param InUserId The user Id to request its accessible focus to be read out @return FScreenReaderReply::Handled() if the user's focused widget's information is successfully spoken. Else FScreenReaderReply::Unhandled() is returned.
- L149 _public prototype_ `FScreenReaderReply StopSpeaking(UPARAM(DisplayName = "Screen Reader User` — `UFUNCTION(BlueprintCallable, Category = "SlateScreenReader")` — Immediately stops speaking any currently spoken announcement for a particular screen reader user. Does nothing if there is no announcement currently being spoken for the user or if the user Id is not registered with the screen reader. @param InUserId The user Id of the screen reader user to request announcements to be stopped. @return FScreenReader::Handled() if the request to stop speaking is successfully processed. Else FScreenReaderReply::Unhandled() is returned.
- L157 _public prototype_ `bool IsSpeaking(UPARAM(DisplayName = "Screen Reader User Id") i` — `UFUNCTION(BlueprintCallable, Category = "SlateScreenReader")` — Returns true if the screen reader is speaking text to a particular user. Returns false if no no announcements are being spoken to the user or if the user Id is not registered. @param InUserId The user Id of the screen reader user to check if any announcements are being spoken to.
- L165 _public prototype_ `float GetSpeechVolume(UPARAM(DisplayName = "Screen Reader User Id") i` — `UFUNCTION(BlueprintCallable, Category = "SlateScreenReader")` — Returns the volume text to speech will be speaking at for a screen reader user.  Value is between 0.0f and 1.0f. If the provided user Id doesn't exist, 0.0f will be returned. @param InUserId The user Id of the screen reader user to retrieve the text to speech volume for
- L175 _public prototype_ `FScreenReaderReply SetSpeechVolume(UPARAM(DisplayName = "Screen Reader User Id") int32 InUserId, UPARAM(DisplayName =` — `UFUNCTION(BlueprintCallable, Category = "SlateScreenReader")` — Sets the volume text to speech will be speaking at for a screen reader user. If the provided user Id doesn't exist, nothing will happen. @param InUserId The user Id of the screen reader user to set the text to speech volume for @param InVolume The volume text to speech will be set at for the provided screen reader user. Value will be clamped between 0.0f and 1.0f. @return FScreenReaderReply::Handled() is returned if the speech volume is successfully set for the screen reader user. Otherwise, FScreenReaderReply::Unhandled() is returned.
- L183 _public prototype_ `float GetSpeechRate(UPARAM(DisplayName = "Screen Reader User Id") i` — `UFUNCTION(BlueprintCallable, Category = "SlateScreenReader")` — Returns the rate text to speech will be speaking at for a screen reader user.  Value is between 0.0f and 1.0f. If the provided user Id doesn't exist, 0.0f will be returned. @param InUserId The user Id of the screen reader user to retrieve the text to speech rate for
- L193 _public prototype_ `FScreenReaderReply SetSpeechRate(UPARAM(DisplayName = "Screen Reader User Id") int32 InUserId, UPARAM(DisplayName` — `UFUNCTION(BlueprintCallable, Category = "SlateScreenReader")` — Sets the rate text to speech will be speaking at for a screen reader user. If the provided user Id doesn't exist, nothing will happen. @param InUserId The user Id of the screen reader user to set the text to speech rate for @param InRate The rate text to speech will be set at for the provided screen reader user. Value will be clamped between 0.0f and 1.0f. @return FScreenReaderReply::Handled() is returned if the speech rate is successfully set for the screen reader user. Otherwise, FScreenReaderReply::Unhandled() is returned.
- L202 _public prototype_ `FScreenReaderReply MuteSpeech(UPARAM(DisplayName = "Screen Reader User` — `UFUNCTION(BlueprintCallable, Category = "SlateScreenReader")` — Mutes the text to speech for a screen reader user. If the provided user Id doesn't exist, nothing will happen. @param InUserId The user Id of the screen reader user to mute text to speech for. @return FScreenReaderReply::Handled() is returned if the screen reader user is successfully muted. Otherwise, FScreenReaderReply::Unhandled() is returned.
- L211 _public prototype_ `FScreenReaderReply UnmuteSpeech(UPARAM(DisplayName = "Screen Reader User` — `UFUNCTION(BlueprintCallable, Category = "SlateScreenReader")` — Unmutes the text to speech for a screen reader user. If the provided user Id doesn't exist, nothing will happen. @param InUserId The user Id of the screen reader user to unmute text to speech for. @return FScreenReaderReply::Handled() is returned if the screen reader user is successfully unmuted. Otherwise, FScreenReaderReply::Unhandled() is returned.
- L219 _public prototype_ `bool IsSpeechMuted(UPARAM(DisplayName = "Screen Reader User Id") i` — `UFUNCTION(BlueprintCallable, Category = "SlateScreenReader")` — Returns true if text to speech for a screen reader user is muted. Otherwise false is returned. If the provided user Id doesn't exist, false will be returned. @param InUserId The screen reader user Id to check if text to speech is muted.
- L222 _public prototype_ `TSharedRef<FScreenReaderBase> GetScreenReader() const;` — Returns the underlying screen reader
- L225 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;` — UEngineSubsystem
- L226 _public prototype_ `virtual void Deinitialize() override;`
- L227 _public prototype_ `virtual bool ShouldCreateSubsystem(UObject* Outer) const override;`
- L234 _private member_ `TSharedPtr<FScreenReaderBase> ScreenReader;` — The underlying screen reader. This should be a TUniquePtr but we make it a TSharedPtr to allow for easy delegate unbinding without needing to manually unbind from delegates.

### `Plugins/Experimental/SlateScreenReader/Source/SlateScreenReader/Public/SlateScreenReaderModule.h` (Public)


#### class `ISlateScreenReaderModule`  
`class ISlateScreenReaderModule: public IModuleInterface`  
_L12-28_
- inherits: `IModuleInterface`
- L15 _public function_ `virtual ~ISlateScreenReaderModule()`
- L17 _public function_ `static ISlateScreenReaderModule& Get()` — Get this module and load it if required.
- L23 _public prototype_ `virtual TSharedRef<IScreenReaderBuilder> GetDefaultScreenReaderBuilder() const = 0;` — Returns the default IScreenReaderBuilder used to construct Slate screen readers. There will always be a valid screen reader builder for Slate screen readers.
- L25 _public prototype_ `virtual TSharedPtr<IScreenReaderBuilder> GetCustomScreenReaderBuilder() const = 0;` — Gets the custom screen reader builder set by the user for building Slate screen readers. If the user did not set a custom screen reader builder, this returns nullptr.
- L27 _public prototype_ `virtual void SetCustomScreenReaderBuilder(const TSharedRef<IScreenReaderBuilder>& InBuilder) = 0;` — Sets a custom screen reader builder to build Slate screen readers.
