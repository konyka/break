# Runtime / SessionMessages

- module root: `Source/Runtime/SessionMessages`
- headers: 1; symbols: 25
- symbol kinds: function=4, member=16, struct=5
- PrivateDependencyModuleNames: Core
- PublicDependencyModuleNames: CoreUObject

### `Source/Runtime/SessionMessages/Public/SessionServiceMessages.h` (Public)


#### struct `FSessionServicePing`  
`struct FSessionServicePing`  
_L18-33_
- reflection: `USTRUCT()`
- desc: Implements a message that is published to discover existing application sessions.
- L24 _public member_ `FString UserName;` — `UPROPERTY(EditAnywhere, Category="Message")` — The name of the user who sent this ping.
- L27 _public function_ `FSessionServicePing()` — Default constructor.
- L30 _public function_ `FSessionServicePing(const FString& InUserName) : UserName(InUserName)` — Creates and initializes a new instance.

#### struct `FSessionServicePong`  
`struct FSessionServicePong`  
_L40-83_
- reflection: `USTRUCT()`
- desc: Implements a message that is published in response to FSessionServicePing.
- L46 _public member_ `bool Authorized = true;` — `UPROPERTY(EditAnywhere, Category="Message")` — Indicates whether the pinging user is authorized to interact with this session.
- L50 _public member_ `FString BuildDate;` — `UPROPERTY(EditAnywhere, Category="Message")` — Holds the application's build date.
- L54 _public member_ `FString DeviceName;` — `UPROPERTY(EditAnywhere, Category="Message")` — Holds the name of the device that the application is running on.
- L58 _public member_ `FGuid InstanceId;` — `UPROPERTY(EditAnywhere, Category="Message")` — Holds the application's instance identifier.
- L62 _public member_ `FString InstanceName;` — `UPROPERTY(EditAnywhere, Category="Message")` — Holds the application's instance name.
- L66 _public member_ `FString PlatformName;` — `UPROPERTY(EditAnywhere, Category="Message")` — Holds the name of the platform that the application is running on.
- L70 _public member_ `FGuid SessionId;` — `UPROPERTY(EditAnywhere, Category="Message")` — Holds the identifier of the session that the application belongs to.
- L74 _public member_ `FString SessionName;` — `UPROPERTY(EditAnywhere, Category="Message")` — Holds the user defined name of the session.
- L78 _public member_ `FString SessionOwner;` — `UPROPERTY(EditAnywhere, Category="Message")` — Holds the name of the user that started the session.
- L82 _public member_ `bool Standalone = true;` — `UPROPERTY(EditAnywhere, Category="Message")` — Indicates whether the application is the only one in that session.

#### struct `FSessionServiceLog`  
`struct FSessionServiceLog`  
_L93-132_
- reflection: `USTRUCT()`
- desc: Implements a message that contains a console log entry.
- L99 _public member_ `FName Category;` — `UPROPERTY(EditAnywhere, Category="Message")` — Holds the log message category.
- L103 _public member_ `FString Data;` — `UPROPERTY(EditAnywhere, Category="Message")` — Holds the log message data.
- L107 _public member_ `FGuid InstanceId;` — `UPROPERTY(EditAnywhere, Category="Message")` — Holds the application instance identifier.
- L111 _public member_ `double TimeSeconds = 0.0;` — `UPROPERTY(EditAnywhere, Category="Message")` — Holds the time in seconds since the application was started.
- L115 _public member_ `uint8 Verbosity;` — `UPROPERTY(EditAnywhere, Category="Message")` — Holds the log message's verbosity level.
- L120 _public function_ `FSessionServiceLog() : TimeSeconds(0.0), Verbosity(0)` — Default constructor.
- L125 _public function_ `FSessionServiceLog(const FName& InCategory, const FString& InData, const FGuid& InInstanceId, double InTimeSeconds, uint8 InVerbosity) : Category(InCategory) , Data(InData) , InstanceId(InInstanceId) , TimeSeconds(InTimeSeconds) , Verbosity(InVerbosity)` — Creates and initializes a new instance.

#### struct `FSessionServiceLogSubscribe`  
`struct FSessionServiceLogSubscribe`  
_L139-142_
- reflection: `USTRUCT()`
- desc: Implements a message to subscribe to an application's console log.

#### struct `FSessionServiceLogUnsubscribe`  
`struct FSessionServiceLogUnsubscribe`  
_L149-152_
- reflection: `USTRUCT()`
- desc: Implements a message to unsubscribe from an application's console log.
