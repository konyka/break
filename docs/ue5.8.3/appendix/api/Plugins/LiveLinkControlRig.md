# Plugins / LiveLinkControlRig

- module root: `Plugins/Experimental/LiveLinkControlRig/Source/LiveLinkControlRig`
- headers: 3; symbols: 42
- symbol kinds: class=1, macro=2, member=22, namespace=1, prototype=9, struct=7
- PrivateDependencyModuleNames: ControlRig, InputCore, Media, Projects, RigVM, Slate, SlateCore
- PublicDependencyModuleNames: Core, CoreUObject, Engine, LiveLinkInterface

### `Plugins/Experimental/LiveLinkControlRig/Source/LiveLinkControlRig/Public/LiveLinkControlRig.h` (Public)


#### class `FLiveLinkControlRigModule`  
`class FLiveLinkControlRigModule : public IModuleInterface`  
_L7-12_
- inherits: `IModuleInterface`
- L10 _private prototype_ `virtual void StartupModule() override;` — IModuleInterface interface
- L11 _private prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Experimental/LiveLinkControlRig/Source/LiveLinkControlRig/Public/LiveLinkInputDeviceRigUnits.h` (Public)


#### struct `FRigUnit_LiveLinkEvaluateInputDeviceValue`  
`struct FRigUnit_LiveLinkEvaluateInputDeviceValue : public FRigUnit`  
_L16-31_
- reflection: `USTRUCT(meta = (DisplayName = "Get Live Link Input Device Data", Category = "Live Link"))`
- inherits: `FRigUnit`
- desc: A node to evaluate a live link input device value
- L21 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;` — Execute logic for this rig unit
- L26 _public member_ `FName SubjectName;` — `UPROPERTY(meta = (Input))` — Name of the subject we would like to get Live Link device data. This should be the subject attached to the gamepad.
- L30 _public member_ `FLiveLinkGamepadInputDeviceFrameData InputDeviceData;` — `UPROPERTY(meta = (Output))` — Gamepad device data for the current frame.

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API LIVELINKCONTROLRIG_API`

### `Plugins/Experimental/LiveLinkControlRig/Source/LiveLinkControlRig/Public/LiveLinkRigUnits.h` (Public)


#### struct `FRigUnit_LiveLinkBase`  
`struct FRigUnit_LiveLinkBase : public FRigUnit`  
_L21-24_
- reflection: `USTRUCT(meta = (Abstract, NodeColor = "0.3 0.1 0.1", DocumentationPolicy = "Strict"))`
- inherits: `FRigUnit`
- desc: The base class for all live link control rig nodes

#### struct `FRigUnit_LiveLinkEvaluteFrameAnimation`  
`struct FRigUnit_LiveLinkEvaluteFrameAnimation : public FRigUnit_LiveLinkBase`  
_L30-57_
- reflection: `USTRUCT(meta = (DisplayName = "Evaluate Live Link Frame (Animation)", Category = "Live Link"))`
- inherits: `FRigUnit_LiveLinkBase`
- desc: Evaluate current Live Link Animation associated with supplied subject
- L35 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;` — Execute logic for this rig unit
- L40 _public member_ `FName SubjectName;` — `UPROPERTY(meta = (Input))` — The name of the subject to evaluate a frame for
- L44 _public member_ `bool bDrawDebug = false;` — `UPROPERTY(meta = (Input))` — If True debug data will be drawn for the subject
- L48 _public member_ `FLinearColor DebugColor = FLinearColor::Red;` — `UPROPERTY(meta = (Input))` — The color to use for the debug drawing
- L52 _public member_ `FTransform DebugDrawOffset;` — `UPROPERTY(meta = (Input))` — The world offset to use when drawing the debug data
- L56 _public member_ `FSubjectFrameHandle SubjectFrame;` — `UPROPERTY(meta = (Output))` — The resulting subject's frame

#### struct `FRigUnit_LiveLinkGetTransformByName`  
`struct FRigUnit_LiveLinkGetTransformByName : public FRigUnit_LiveLinkBase`  
_L63-86_
- reflection: `USTRUCT(meta = (DisplayName = "Get Transform By Name", Category = "Live Link"))`
- inherits: `FRigUnit_LiveLinkBase`
- desc: Get the transform value with supplied subject frame
- L68 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;` — Execute logic for this rig unit
- L73 _public member_ `FSubjectFrameHandle SubjectFrame;` — `UPROPERTY(meta = (Input))` — The frame to receive a transform from
- L77 _public member_ `FName TransformName;` — `UPROPERTY(meta = (Input))` — The name of the transform to retrieve
- L81 _public member_ `ERigVMTransformSpace Space = ERigVMTransformSpace::LocalSpace;` — `UPROPERTY(meta = (Input))` — The space to retrieve the transform in
- L85 _public member_ `FTransform Transform;` — `UPROPERTY(meta = (Output))` — The resulting transform

#### struct `FRigUnit_LiveLinkGetParameterValueByName`  
`struct FRigUnit_LiveLinkGetParameterValueByName : public FRigUnit_LiveLinkBase`  
_L92-111_
- reflection: `USTRUCT(meta = (DisplayName = "Get Parameter Value By Name", Category = "Live Link"))`
- inherits: `FRigUnit_LiveLinkBase`
- desc: Get the parameter value with supplied subject frame
- L97 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;` — Execute logic for this rig unit
- L102 _public member_ `FSubjectFrameHandle SubjectFrame;` — `UPROPERTY(meta = (Input))` — The frame to retrieve the parameter from
- L106 _public member_ `FName ParameterName;` — `UPROPERTY(meta = (Input))` — The name of the parameter to retrieve
- L110 _public member_ `float Value = 0.f;` — `UPROPERTY(meta = (Output))` — The resulting value of the parameter

#### struct `FRigUnit_LiveLinkEvaluteFrameTransform`  
`struct FRigUnit_LiveLinkEvaluteFrameTransform : public FRigUnit_LiveLinkBase`  
_L117-144_
- reflection: `USTRUCT(meta = (DisplayName = "Evaluate Live Link Frame (Transform)", Category = "Live Link"))`
- inherits: `FRigUnit_LiveLinkBase`
- desc: Evaluate current Live Link Transform associated with supplied subject
- L122 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;` — Execute logic for this rig unit
- L127 _public member_ `FName SubjectName;` — `UPROPERTY(meta = (Input))` — The name of the subject to evaluate
- L131 _public member_ `bool bDrawDebug = false;` — `UPROPERTY(meta = (Input))` — If True debug data will be drawn
- L135 _public member_ `FLinearColor DebugColor = FLinearColor::Red;` — `UPROPERTY(meta = (Input))` — The color to use for the debug drawing
- L139 _public member_ `FTransform DebugDrawOffset;` — `UPROPERTY(meta = (Input))` — The world offset to use for the debug drawing
- L143 _public member_ `FTransform Transform;` — `UPROPERTY(meta = (Output))` — The resulting transform of the subject

#### struct `FRigUnit_LiveLinkEvaluateBasicValue`  
`struct FRigUnit_LiveLinkEvaluateBasicValue : public FRigUnit_LiveLinkBase`  
_L149-168_
- reflection: `USTRUCT(meta = (DisplayName = "Get Basic Live Link Data", Category = "Live Link"))`
- inherits: `FRigUnit_LiveLinkBase`
- desc: Evaluate current Live Link Basic float property data associated with supplied subject
- L154 _public prototype_ `RIGVM_METHOD() virtual void Execute() override;` — Execute logic for this rig unit
- L159 _public member_ `FName SubjectName;` — `UPROPERTY(meta = (Input))` — The name of the subject to evaluate
- L163 _public member_ `FName PropertyName;` — `UPROPERTY(meta = (Input))` — The name of the property to evaluate
- L167 _public member_ `float Value = 0.f;` — `UPROPERTY(meta = (Output))` — The resulting value of the evaluated property

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API LIVELINKCONTROLRIG_API`
- L12 _namespace_ `namespace LiveLinkControlRigUtilities`
- L14 _prototype_ `ILiveLinkClient* TryGetLiveLinkClient();` (scope `LiveLinkControlRigUtilities`)
