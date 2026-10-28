# Developer / SlackIntegrations

- module root: `Source/Developer/SlackIntegrations`
- headers: 4; symbols: 20
- symbol kinds: class=3, function=3, member=5, prototype=7, struct=2
- PrivateDependencyModuleNames: HTTP
- PublicDependencyModuleNames: Core

### `Source/Developer/SlackIntegrations/Private/SlackIncomingWebhookInterface.h` (Private)


#### class `FSlackIncomingWebhookInterface`  
`class FSlackIncomingWebhookInterface : public ISlackIncomingWebhookInterface`  
_L18-49_
- inherits: `ISlackIncomingWebhookInterface`
- desc: Concrete implementation of ISlackIncomingWebhookInterface in module's private code. Sends Incoming Webhook messages to Slack.
- L22 _public function_ `virtual ~FSlackIncomingWebhookInterface()` — Empty virtual destructor because class has virtual methods
- L30 _public prototype_ `virtual bool SendMessage(const FSlackIncomingWebhook& InWebhook, const FSlackMessage& InMessage) const override;` — Send an incoming webhook message to Slack @param InWebhook		Webhook parameters sets where and how to send the message @param InMessage		The message to send to Slack @return				True if the http request was send successfully, otherwise false.
- L34 _private prototype_ `TSharedRef<IHttpRequest, ESPMode::ThreadSafe> CreateHttpRequest() const;` — Helper used to make http requests by SendMessage()
- L42 _private prototype_ `void OnProcessRequestComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded) const;` — Callback from HTTP library when a request has completed @param HttpRequest The request object @param HttpResponse The response from the server @param bSucceeded Whether a response was successfully received
- L45 _private prototype_ `static void GetPayload(const FSlackIncomingWebhook& InWebhook, const FSlackMessage& InMessage, TArray<uint8>& OutPayload);` — Builds the json payload bytes to send in the http request to Slack
- L48 _private prototype_ `static FString JsonEncode(const FString& InString);` — Helper that escapes characters in the payload to make valid json

### `Source/Developer/SlackIntegrations/Public/ISlackIncomingWebhookInterface.h` (Public)


#### class `ISlackIncomingWebhookInterface`  
`class ISlackIncomingWebhookInterface`  
_L13-17_
- desc: Public interface for accessing Slack incoming webhook methods
- L16 _public prototype_ `virtual bool SendMessage(const FSlackIncomingWebhook& InWebhook, const FSlackMessage& InMessage) const = 0;`

### `Source/Developer/SlackIntegrations/Public/SlackIntegrations.h` (Public)


#### struct `FSlackIncomingWebhook`  
`struct FSlackIncomingWebhook`  
_L11-24_
- desc: Simple struct represents the parameters used for incoming webhook requests
- L14 _public member_ `FString WebhookUrl;` — Full URL from your Incoming Webhook Integrations on the Slack website
- L17 _public member_ `FString Channel;` — Overrides the channel to which the message is posted. The Incoming Webhook Integrations created on the Slack website will have a default channel.
- L20 _public member_ `FString Username;` — Overrides the username with which the message is posted. The Incoming Webhook Integrations created on the Slack website will have a default username.
- L23 _public member_ `FString IconEmoji;` — Overrides the emoji for the username with which the message is posted. The Incoming Webhook Integrations created on the Slack website will have a default emoji.

#### struct `FSlackMessage`  
`struct FSlackMessage`  
_L29-33_
- desc: Simple struct represents the parameters of a Slack message
- L32 _public member_ `FString MessageText;` — Message content

### `Source/Developer/SlackIntegrations/Public/SlackIntegrationsModule.h` (Public)


#### class `ISlackIntegrationsModule`  
`class ISlackIntegrationsModule : public IModuleInterface`  
_L14-40_
- inherits: `IModuleInterface`
- desc: ISlackIntegrationsModule interface for public access to this module
- L23 _public function_ `static inline ISlackIntegrationsModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L33 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L39 _public prototype_ `virtual ISlackIncomingWebhookInterface& GetIncomingWebhookInterface() = 0;` — Get the incoming webhook interface for sending messages to Slack
