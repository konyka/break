# Runtime / IOSLocalNotification

- module root: `Source/Runtime/IOS/IOSLocalNotification`
- headers: 1; symbols: 19
- symbol kinds: class=1, delegate=2, function=1, member=3, prototype=12
- PrivateDependencyModuleNames: Core, CoreUObject, Engine

### `Source/Runtime/IOS/IOSLocalNotification/Public/IOSLocalNotification.h` (Public)


#### class `FIOSLocalNotificationService`  
`class FIOSLocalNotificationService : public ILocalNotificationService`  
_L18-40_
- inherits: `ILocalNotificationService`
- desc: IOSLocalNotification implementation of an Unreal local notification service.
- L21 _public prototype_ `FIOSLocalNotificationService();`
- L22 _public function_ `virtual ~FIOSLocalNotificationService()`
- L23 _public prototype_ `virtual void ClearAllLocalNotifications();`
- L24 _public prototype_ `virtual int32 ScheduleLocalNotificationAtTime(const FDateTime& FireDateTime, bool LocalTime, const FText& Title, const FText& Body, const FText& Action, const FString& ActivationEvent);`
- L25 _public prototype_ `virtual int32 ScheduleLocalNotificationAtTimeOverrideId(const FDateTime& FireDateTime, bool LocalTime, const FText& Title, const FText& Body, const FText& Action, const FString& ActivationEvent, int32 IdOverride);`
- L26 _public prototype_ `virtual int32 ScheduleLocalNotificationBadgeAtTime(const FDateTime& FireDateTime, bool LocalTime, const FString& ActivationEvent);`
- L27 _public prototype_ `virtual void GetLaunchNotification(bool& NotificationLaunchedApp, FString& ActivationEvent, int32& FireDate);`
- L28 _public prototype_ `virtual void SetLaunchNotification(FString const& ActivationEvent, int32 FireDate);`
- L29 _public prototype_ `virtual void CancelLocalNotification(const FString& ActivationEvent);`
- L30 _public prototype_ `virtual void CancelLocalNotification(int NotificationId);`
- L33 _public prototype_ `DECLARE_DELEGATE_OneParam(FAllowedNotifications, bool);` — Check if notifications are allowed if min iOS version is > 10
- L34 _public prototype_ `static void CheckAllowedNotifications(const FAllowedNotifications& AllowedNotificationsDelegate);`
- L37 _private member_ `bool AppLaunchedWithNotification;`
- L38 _private member_ `FString LaunchNotificationActivationEvent;`
- L39 _private member_ `int32 LaunchNotificationFireDate;`

#### Free symbols / members of external scopes

- L13 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogIOSLocalNotification, Log, All);`
- L13 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogIOSLocalNotification, Log, All);`
- L33 _delegate_ `DECLARE_DELEGATE_OneParam(FAllowedNotifications, bool);` — Check if notifications are allowed if min iOS version is > 10
