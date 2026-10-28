# Runtime / DatasmithCore

- module root: `Source/Runtime/Datasmith/DatasmithCore`
- headers: 25; symbols: 2724
- symbol kinds: class=143, enum=38, enumerator=235, function=645, macro=172, member=355, namespace=4, prototype=1105, struct=15, typedef=8, variable=4
- PrivateDependencyModuleNames: Json, XmlParser
- PublicDependencyModuleNames: Core, CoreUObject, DirectLink, MeshDescription, RawMesh, StaticMeshDescription

### `Source/Runtime/Datasmith/DatasmithCore/Private/DatasmithAnimationElementsImpl.h` (Private)


#### class `FDatasmithLevelSequenceElementImpl`  
`class FDatasmithLevelSequenceElementImpl : public FDatasmithElementImpl< IDatasmithLevelSequenceElement >`  
_L10-40_
- inherits: `FDatasmithElementImpl<IDatasmithLevelSequenceElement>`
- L13 _public prototype_ `explicit FDatasmithLevelSequenceElementImpl(const TCHAR* InName);`
- L15 _public function_ `virtual const TCHAR* GetFile() const override`
- L16 _public function_ `virtual void SetFile(const TCHAR* InFile) override`
- L18 _public function_ `virtual FMD5Hash GetFileHash() const override`
- L19 _public function_ `virtual void SetFileHash(FMD5Hash Hash) override`
- L21 _public function_ `virtual float GetFrameRate() const override`
- L22 _public function_ `virtual void SetFrameRate(float FramePerSecs) override`
- L24 _public function_ `virtual void AddAnimation(const TSharedRef< IDatasmithBaseAnimationElement >& InAnimation) override`
- L25 _public function_ `virtual int32 GetAnimationsCount() const override`
- L27 _public function_ `virtual TSharedPtr< IDatasmithBaseAnimationElement > GetAnimation(int32 InIndex) override`
- L32 _public function_ `virtual void RemoveAnimation(const TSharedRef< IDatasmithBaseAnimationElement >& InAnimation) override`
- L35 _private member_ `TReflected<FString> File;`
- L36 _private member_ `TReflected<FMD5Hash> FileHash;`
- L37 _private member_ `TReflected<float> FrameRate;`
- L39 _private member_ `TArray< TSharedRef< IDatasmithBaseAnimationElement > > Animations;`

#### class `FDatasmithBaseAnimationElementImpl`  
`template< typename InterfaceType > class FDatasmithBaseAnimationElementImpl : public FDatasmithElementImpl< InterfaceType >`  
_L43-62_
- inherits: `FDatasmithElementImpl<InterfaceType>`
- L46 _public prototype_ `explicit FDatasmithBaseAnimationElementImpl(const TCHAR* InName, EDatasmithElementType ChildType, EDatasmithElementAnimationSubType InSubtype = EDatasmithElementAnimationSubType::BaseAnimation);`
- L48 _public function_ `virtual bool IsSubType( const EDatasmithElementAnimationSubType AnimSubType ) const override`
- L50 _public function_ `virtual void SetCompletionMode(EDatasmithCompletionMode InCompletionMode) override`
- L55 _public function_ `virtual EDatasmithCompletionMode GetCompletionMode() const override`
- L61 _private member_ `EDatasmithCompletionMode CompletionMode;`
- L65 _function_ `template< typename T > inline FDatasmithBaseAnimationElementImpl<T>::FDatasmithBaseAnimationElementImpl(const TCHAR* InName, EDatasmithElementType ChildType, EDatasmithElementAnimationSubType InSubtype) : FDatasmithElementImpl<T>(InName, EDatasmithElementType::Animation | ChildType, (uint64)InSubtype) , CompletionMode(EDatasmithCompletionMode::ProjectDefault)`

#### class `FDatasmithTransformAnimationElementImpl`  
`class FDatasmithTransformAnimationElementImpl : public FDatasmithBaseAnimationElementImpl< IDatasmithTransformAnimationElement >`  
_L71-116_
- inherits: `FDatasmithBaseAnimationElementImpl<IDatasmithTransformAnimationElement>`
- L74 _public prototype_ `explicit FDatasmithTransformAnimationElementImpl(const TCHAR* InName);`
- L76 _public function_ `virtual void AddFrame(EDatasmithTransformType TransformType, const FDatasmithTransformFrameInfo& FrameInfo) override`
- L77 _public function_ `virtual int32 GetFramesCount(EDatasmithTransformType TransformType) const override`
- L79 _public function_ `virtual void SetCurveInterpMode(EDatasmithTransformType TransformType, EDatasmithCurveInterpMode CurveInterpMode) override`
- L84 _public function_ `virtual EDatasmithCurveInterpMode GetCurveInterpMode(EDatasmithTransformType TransformType) const override`
- L89 _public function_ `virtual const FDatasmithTransformFrameInfo& GetFrame(EDatasmithTransformType TransformType, int32 Index) const override`
- L94 _public function_ `virtual void RemoveFrame(EDatasmithTransformType TransformType, int32 Index) override`
- L102 _public function_ `virtual EDatasmithTransformChannels GetEnabledTransformChannels() const override`
- L107 _public function_ `virtual void SetEnabledTransformChannels(EDatasmithTransformChannels Channels) override`
- L113 _private member_ `TArray< FDatasmithTransformFrameInfo > Frames[(uint8) EDatasmithTransformType::Count];`
- L114 _private member_ `EDatasmithCurveInterpMode TransformCurveInterpMode[(uint8) EDatasmithTransformType::Count];`
- L115 _private member_ `EDatasmithTransformChannels EnabledChannels;`

#### class `FDatasmithVisibilityAnimationElementImpl`  
`class FDatasmithVisibilityAnimationElementImpl : public FDatasmithBaseAnimationElementImpl< IDatasmithVisibilityAnimationElement >`  
_L118-163_
- inherits: `FDatasmithBaseAnimationElementImpl<IDatasmithVisibilityAnimationElement>`
- L121 _public prototype_ `explicit FDatasmithVisibilityAnimationElementImpl(const TCHAR* InName);`
- L123 _public function_ `virtual void AddFrame(const FDatasmithVisibilityFrameInfo& FrameInfo) override`
- L124 _public function_ `virtual int32 GetFramesCount() const override`
- L126 _public function_ `virtual void SetCurveInterpMode(EDatasmithCurveInterpMode InCurveInterpMode) override`
- L131 _public function_ `virtual EDatasmithCurveInterpMode GetCurveInterpMode() const override`
- L136 _public function_ `virtual const FDatasmithVisibilityFrameInfo& GetFrame(int32 Index) const override`
- L141 _public function_ `virtual void RemoveFrame(int32 Index) override`
- L149 _public function_ `virtual void SetPropagateToChildren(bool bInPropagate) override`
- L154 _public function_ `virtual bool GetPropagateToChildren() const override`
- L160 _private member_ `TArray<FDatasmithVisibilityFrameInfo> Frames;`
- L161 _private member_ `EDatasmithCurveInterpMode CurveInterpMode;`
- L162 _private member_ `bool bPropagate;`

#### class `FDatasmithSubsequenceAnimationElementImpl`  
`class FDatasmithSubsequenceAnimationElementImpl : public FDatasmithBaseAnimationElementImpl< IDatasmithSubsequenceAnimationElement >`  
_L165-215_
- inherits: `FDatasmithBaseAnimationElementImpl<IDatasmithSubsequenceAnimationElement>`
- L168 _public prototype_ `explicit FDatasmithSubsequenceAnimationElementImpl(const TCHAR* InName);`
- L170 _public function_ `virtual FFrameNumber GetStartTime() const override`
- L175 _public function_ `virtual void SetStartTime(FFrameNumber InStartTime) override`
- L180 _public function_ `virtual int32 GetDuration() const override`
- L185 _public function_ `virtual void SetDuration(int32 InDuration) override`
- L190 _public function_ `virtual float GetTimeScale() const override`
- L195 _public function_ `virtual void SetTimeScale(float InTimeScale) override`
- L200 _public function_ `virtual TWeakPtr<IDatasmithLevelSequenceElement> GetSubsequence() const override`
- L205 _public function_ `virtual void SetSubsequence(TWeakPtr<IDatasmithLevelSequenceElement> InSubsequence) override`
- L211 _private member_ `FFrameNumber StartTime;`
- L212 _private member_ `int32 Duration;`
- L213 _private member_ `float TimeScale;`
- L214 _private member_ `TWeakPtr<IDatasmithLevelSequenceElement> Subsequence;`

### `Source/Runtime/Datasmith/DatasmithCore/Private/DatasmithLocaleScope.h` (Private)


#### struct `FDatasmithLocaleScope`  
`struct FDatasmithLocaleScope`  
_L11-22_
- desc: Setup a locale for a given scope, the previous locale is restored on scope end.
- L14 _public prototype_ `FDatasmithLocaleScope(const TCHAR* InScopedLocale = TEXT("C"))` — Set a custom locale within this object scope
- L17 _public prototype_ `~FDatasmithLocaleScope();` — restore the captured Locale
- L20 _private member_ `FString SavedLocale;` — Locale previously used, captured, and to be restored
- L21 _private member_ `FString ScopedLocale;` — Locale in use within the scope

### `Source/Runtime/Datasmith/DatasmithCore/Private/DatasmithMaterialElementsImpl.h` (Private)


#### class `FDatasmithExpressionInputImpl`  
`class FDatasmithExpressionInputImpl : public FDatasmithElementImpl < IDatasmithExpressionInput >`  
_L53-87_
- inherits: `FDatasmithElementImpl<IDatasmithExpressionInput>`
- L56 _public prototype_ `explicit FDatasmithExpressionInputImpl( const TCHAR* InInputName );`
- L57 _public prototype_ `virtual ~FDatasmithExpressionInputImpl() = default;`
- L59 _public function_ `virtual IDatasmithMaterialExpression* GetExpression() override`
- L60 _public function_ `virtual const IDatasmithMaterialExpression* GetExpression() const override`
- L61 _public prototype_ `virtual void SetExpression( IDatasmithMaterialExpression* InExpression ) override;`
- L63 _public function_ `virtual int32 GetOutputIndex() const override`
- L64 _public function_ `virtual void SetOutputIndex( int32 InOutputIndex ) override`
- L66 _public function_ `FMD5Hash CalculateElementHash(bool bForce) override`
- L82 _public prototype_ `virtual void CustomSerialize(class DirectLink::FSnapshotProxy& Ar) override;`
- L85 _protected member_ `TDatasmithReferenceProxy<IDatasmithMaterialExpression> Expression;`
- L86 _protected member_ `TReflected<int32> OutputIndex;`

#### class `FDatasmithExpressionOutputImpl`  
`class FDatasmithExpressionOutputImpl : public FDatasmithElementImpl < IDatasmithExpressionOutput >`  
_L89-110_
- inherits: `FDatasmithElementImpl<IDatasmithExpressionOutput>`
- L92 _public function_ `explicit FDatasmithExpressionOutputImpl( const TCHAR* InOutputName ) : FDatasmithElementImpl< IDatasmithExpressionOutput >( InOutputName, EDatasmithElementType::MaterialExpressionOutput )`
- L96 _public function_ `FMD5Hash CalculateElementHash(bool bForce) override`

#### class `FDatasmithMaterialExpressionImpl`  
`template< typename InterfaceType > class FDatasmithMaterialExpressionImpl : public FDatasmithElementImpl< InterfaceType > , public TSharedFromThis< FDatasmithMaterialExpressionImpl< InterfaceType > >`  
_L113-165_
- inherits: `FDatasmithElementImpl<InterfaceType>,TSharedFromThis<FDatasmithMaterialExpressionImpl<InterfaceType>>`
- L118 _public prototype_ `explicit FDatasmithMaterialExpressionImpl( EDatasmithMaterialExpressionType InSubType );`
- L120 _public prototype_ `virtual ~FDatasmithMaterialExpressionImpl() = default;`
- L122 _public function_ `virtual EDatasmithMaterialExpressionType GetExpressionType() const override`
- L124 _public function_ `virtual bool IsSubType( const EDatasmithMaterialExpressionType ExpressionType ) const override`
- L127 _public function_ `virtual bool IsSubTypeInternal( uint64 InSubType ) const override` — as our subtype is not a bitfield
- L129 _public function_ `virtual void ConnectExpression( IDatasmithExpressionInput& ExpressionInput ) override`
- L134 _public prototype_ `inline virtual void ConnectExpression( IDatasmithExpressionInput& ExpressionInput, int32 OutputIndex ) override;`
- L136 _public function_ `virtual int32 GetInputCount() const override`
- L137 _public function_ `virtual IDatasmithExpressionInput* GetInput( int32 Index ) override`
- L138 _public function_ `virtual const IDatasmithExpressionInput* GetInput( int32 Index ) const override`
- L140 _public function_ `virtual int32 GetDefaultOutputIndex() const override`
- L141 _public function_ `virtual void SetDefaultOutputIndex( int32 InDefaultOutputIndex ) override`
- L143 _public prototype_ `virtual void ResetExpression() override;`
- L145 _public prototype_ `virtual void ResetExpressionImpl() = 0;`
- L148 _protected function_ `FMD5Hash ComputeHash()`
- L162 _protected member_ `TDatasmithReferenceArrayProxy<FDatasmithExpressionOutputImpl> Outputs;`
- L164 _protected member_ `TReflected<int32> DefaultOutputIndex;`
- L752 _function_ `template< typename InterfaceType > FDatasmithMaterialExpressionImpl< InterfaceType >::FDatasmithMaterialExpressionImpl( EDatasmithMaterialExpressionType InSubType ) : FDatasmithElementImpl< InterfaceType >( nullptr, EDatasmithElementType::MaterialExpression, (uint64)InSubType ) , DefaultOutputIndex( 0 )`
- L761 _function_ `template< typename InterfaceType > void FDatasmithMaterialExpressionImpl< InterfaceType >::ConnectExpression( IDatasmithExpressionInput& ExpressionInput, int32 InOutputIndex )`
- L778 _function_ `template< typename InterfaceType > void FDatasmithMaterialExpressionImpl< InterfaceType >::ResetExpression()`

#### class `FDatasmithExpressionParameterImpl`  
`template< typename InterfaceType > class FDatasmithExpressionParameterImpl : public FDatasmithMaterialExpressionImpl< InterfaceType >`  
_L168-200_
- inherits: `FDatasmithMaterialExpressionImpl<InterfaceType>`
- L171 _public typedef_ `typedef FDatasmithMaterialExpressionImpl< InterfaceType > TBaseExpression;`
- L173 _public function_ `FDatasmithExpressionParameterImpl( EDatasmithMaterialExpressionType InSubType ) : FDatasmithMaterialExpressionImpl< InterfaceType >( InSubType )`
- L179 _public function_ `virtual const TCHAR* GetGroupName() const override`
- L180 _public function_ `virtual void SetGroupName( const TCHAR* InGroupName ) override`
- L183 _protected function_ `FMD5Hash ComputeHash()`
- L199 _protected member_ `TReflected<FString> GroupName;`

#### class `FDatasmithMaterialExpressionBoolImpl`  
`class FDatasmithMaterialExpressionBoolImpl : public FDatasmithExpressionParameterImpl< IDatasmithMaterialExpressionBool >`  
_L202-236_
- inherits: `FDatasmithExpressionParameterImpl<IDatasmithMaterialExpressionBool>`
- L205 _public prototype_ `FDatasmithMaterialExpressionBoolImpl();`
- L207 _public function_ `virtual bool& GetBool() override`
- L208 _public function_ `virtual const bool& GetBool() const override`
- L210 _public function_ `virtual void ResetExpressionImpl() override`
- L216 _public function_ `FMD5Hash CalculateElementHash(bool bForce) override`
- L235 _protected member_ `TReflected<bool> bValue;`

#### class `FDatasmithMaterialExpressionColorImpl`  
`class FDatasmithMaterialExpressionColorImpl : public FDatasmithExpressionParameterImpl< IDatasmithMaterialExpressionColor >`  
_L238-272_
- inherits: `FDatasmithExpressionParameterImpl<IDatasmithMaterialExpressionColor>`
- L241 _public prototype_ `FDatasmithMaterialExpressionColorImpl();`
- L243 _public function_ `virtual FLinearColor& GetColor() override`
- L244 _public function_ `virtual const FLinearColor& GetColor() const override`
- L246 _public function_ `virtual void ResetExpressionImpl() override`
- L252 _public function_ `FMD5Hash CalculateElementHash(bool bForce) override`
- L271 _protected member_ `TReflected<FLinearColor> LinearColor;`

#### class `FDatasmithMaterialExpressionScalarImpl`  
`class FDatasmithMaterialExpressionScalarImpl : public FDatasmithExpressionParameterImpl< IDatasmithMaterialExpressionScalar >`  
_L274-308_
- inherits: `FDatasmithExpressionParameterImpl<IDatasmithMaterialExpressionScalar>`
- L277 _public prototype_ `FDatasmithMaterialExpressionScalarImpl();`
- L279 _public function_ `virtual float& GetScalar() override`
- L280 _public function_ `virtual const float& GetScalar() const override`
- L282 _public function_ `virtual void ResetExpressionImpl() override`
- L288 _public function_ `FMD5Hash CalculateElementHash(bool bForce) override`
- L307 _protected member_ `TReflected<float> Scalar;`

#### class `FDatasmithMaterialExpressionTextureImpl`  
`class FDatasmithMaterialExpressionTextureImpl : public FDatasmithExpressionParameterImpl< IDatasmithMaterialExpressionTexture >`  
_L310-367_
- inherits: `FDatasmithExpressionParameterImpl<IDatasmithMaterialExpressionTexture>`
- L313 _public prototype_ `FDatasmithMaterialExpressionTextureImpl();`
- L315 _public function_ `virtual const TCHAR* GetTexturePathName() const override`
- L316 _public function_ `virtual void SetTexturePathName( const TCHAR* InTexturePathName )`
- L321 _public function_ `virtual IDatasmithExpressionInput& GetInputCoordinate() override` — Inputs
- L322 _public function_ `virtual const IDatasmithExpressionInput& GetInputCoordinate() const override`
- L324 _public function_ `virtual int32 GetInputCount() const override`
- L325 _public function_ `virtual IDatasmithExpressionInput* GetInput( int32 Index ) override`
- L326 _public function_ `virtual const IDatasmithExpressionInput* GetInput( int32 Index ) const override`
- L328 _public function_ `virtual void ResetExpressionImpl() override`
- L334 _public function_ `FMD5Hash CalculateElementHash(bool bForce) override`
- L355 _protected member_ `TReflected< FString > TexturePathName;`
- L357 _protected member_ `TDatasmithReferenceProxy< FDatasmithExpressionInputImpl > TextureCoordinate;`

#### class `FDatasmithMaterialExpressionTextureCoordinateImpl`  
`class FDatasmithMaterialExpressionTextureCoordinateImpl : public FDatasmithMaterialExpressionImpl< IDatasmithMaterialExpressionTextureCoordinate >`  
_L369-414_
- inherits: `FDatasmithMaterialExpressionImpl<IDatasmithMaterialExpressionTextureCoordinate>`
- L372 _public prototype_ `FDatasmithMaterialExpressionTextureCoordinateImpl();`
- L374 _public function_ `virtual int32 GetCoordinateIndex() const override`
- L375 _public function_ `virtual void SetCoordinateIndex( int32 InCoordinateIndex ) override`
- L377 _public function_ `virtual float GetUTiling() const override`
- L378 _public function_ `virtual void SetUTiling( float InUTiling ) override`
- L380 _public function_ `virtual float GetVTiling() const override`
- L381 _public function_ `virtual void SetVTiling( float InVTiling ) override`
- L383 _public function_ `virtual void ResetExpressionImpl() override`
- L390 _public function_ `FMD5Hash CalculateElementHash(bool bForce) override`
- L411 _protected member_ `TReflected< int32 > CoordinateIndex;`
- L412 _protected member_ `TReflected< float > UTiling;`
- L413 _protected member_ `TReflected< float > VTiling;`

#### class `FDatasmithMaterialExpressionFlattenNormalImpl`  
`class FDatasmithMaterialExpressionFlattenNormalImpl : public FDatasmithMaterialExpressionImpl< IDatasmithMaterialExpressionFlattenNormal >`  
_L416-455_
- inherits: `FDatasmithMaterialExpressionImpl<IDatasmithMaterialExpressionFlattenNormal>`
- L419 _public prototype_ `FDatasmithMaterialExpressionFlattenNormalImpl();`
- L421 _public function_ `virtual IDatasmithExpressionInput& GetNormal() override`
- L422 _public function_ `virtual const IDatasmithExpressionInput& GetNormal() const override`
- L424 _public function_ `virtual IDatasmithExpressionInput& GetFlatness() override`
- L425 _public function_ `virtual const IDatasmithExpressionInput& GetFlatness() const override`
- L427 _public function_ `virtual int32 GetInputCount() const override`
- L428 _public function_ `virtual IDatasmithExpressionInput* GetInput( int32 Index ) override`
- L429 _public function_ `virtual const IDatasmithExpressionInput* GetInput( int32 Index ) const override`
- L431 _public function_ `virtual void ResetExpressionImpl() override`
- L433 _public function_ `FMD5Hash CalculateElementHash(bool bForce) override`
- L453 _protected member_ `TDatasmithReferenceProxy< FDatasmithExpressionInputImpl > Normal;`
- L454 _protected member_ `TDatasmithReferenceProxy< FDatasmithExpressionInputImpl > Flatness;`

#### class `FDatasmithMaterialExpressionGenericImpl`  
`class FDatasmithMaterialExpressionGenericImpl : public FDatasmithMaterialExpressionImpl< IDatasmithMaterialExpressionGeneric >`  
_L457-529_
- inherits: `FDatasmithMaterialExpressionImpl<IDatasmithMaterialExpressionGeneric>`
- L460 _public member_ `static TSharedPtr< IDatasmithKeyValueProperty > NullPropertyPtr;`
- L462 _public function_ `FDatasmithMaterialExpressionGenericImpl() : FDatasmithMaterialExpressionImpl< IDatasmithMaterialExpressionGeneric >( EDatasmithMaterialExpressionType::Generic )`
- L471 _public function_ `virtual void SetExpressionName( const TCHAR* InExpressionName ) override`
- L472 _public function_ `virtual const TCHAR* GetExpressionName() const override`
- L474 _public function_ `int32 GetPropertiesCount() const override`
- L476 _public prototype_ `const TSharedPtr< IDatasmithKeyValueProperty >& GetProperty( int32 InIndex ) const override;`
- L477 _public prototype_ `TSharedPtr< IDatasmithKeyValueProperty >& GetProperty( int32 InIndex ) override;`
- L479 _public prototype_ `const TSharedPtr< IDatasmithKeyValueProperty >& GetPropertyByName( const TCHAR* InName ) const override;`
- L480 _public prototype_ `TSharedPtr< IDatasmithKeyValueProperty >& GetPropertyByName( const TCHAR* InName ) override;`
- L482 _public prototype_ `void AddProperty( const TSharedPtr< IDatasmithKeyValueProperty >& InProperty ) override;`
- L484 _public function_ `virtual int32 GetInputCount() const override`
- L485 _public function_ `virtual IDatasmithExpressionInput* GetInput( int32 Index ) override`
- L495 _public function_ `virtual const IDatasmithExpressionInput* GetInput( int32 Index ) const override`
- L497 _public function_ `virtual void ResetExpressionImpl() override`
- L504 _public function_ `FMD5Hash CalculateElementHash(bool bForce) override`
- L525 _protected member_ `TDatasmithReferenceArrayProxy< FDatasmithExpressionInputImpl > Inputs;`
- L526 _protected member_ `TReflected<FString> ExpressionName;`
- L528 _protected member_ `TDatasmithReferenceArrayProxy< IDatasmithKeyValueProperty > Properties;`

#### class `FDatasmithMaterialExpressionFunctionCallImpl`  
`class FDatasmithMaterialExpressionFunctionCallImpl : public FDatasmithMaterialExpressionImpl< IDatasmithMaterialExpressionFunctionCall >`  
_L531-585_
- inherits: `FDatasmithMaterialExpressionImpl<IDatasmithMaterialExpressionFunctionCall>`
- L534 _public function_ `FDatasmithMaterialExpressionFunctionCallImpl() : FDatasmithMaterialExpressionImpl< IDatasmithMaterialExpressionFunctionCall >( EDatasmithMaterialExpressionType::FunctionCall )`
- L541 _public function_ `virtual void SetFunctionPathName( const TCHAR* InFunctionPathName ) override`
- L542 _public function_ `virtual const TCHAR* GetFunctionPathName() const override`
- L544 _public function_ `virtual int32 GetInputCount() const override`
- L545 _public function_ `virtual IDatasmithExpressionInput* GetInput( int32 Index ) override`
- L555 _public function_ `virtual const IDatasmithExpressionInput* GetInput( int32 Index ) const override`
- L557 _public function_ `virtual void ResetExpressionImpl() override`
- L563 _public function_ `FMD5Hash CalculateElementHash(bool bForce) override`
- L583 _protected member_ `TDatasmithReferenceArrayProxy< FDatasmithExpressionInputImpl > Inputs;`
- L584 _protected member_ `TReflected<FString> FunctionPathName;`

#### class `FDatasmithMaterialExpressionCustomImpl`  
`class FDatasmithMaterialExpressionCustomImpl : public FDatasmithMaterialExpressionImpl< IDatasmithMaterialExpressionCustom >`  
_L587-660_
- inherits: `FDatasmithMaterialExpressionImpl<IDatasmithMaterialExpressionCustom>`
- L590 _public prototype_ `FDatasmithMaterialExpressionCustomImpl();`
- L592 _public function_ `virtual int32 GetInputCount() const override`
- L593 _public prototype_ `virtual IDatasmithExpressionInput* GetInput( int32 Index ) override;`
- L594 _public function_ `virtual const IDatasmithExpressionInput* GetInput( int32 Index ) const override`
- L596 _public function_ `virtual void SetCode(const TCHAR* InCode) override`
- L597 _public function_ `virtual const TCHAR* GetCode() const override`
- L599 _public function_ `virtual void SetDescription(const TCHAR* InDescription) override`
- L600 _public function_ `virtual const TCHAR* GetDescription() const override`
- L602 _public function_ `virtual void SetOutputType(EDatasmithShaderDataType InOutputType) override`
- L603 _public function_ `virtual EDatasmithShaderDataType GetOutputType() const override`
- L605 _public function_ `virtual int32 GetIncludeFilePathCount() const override`
- L606 _public function_ `virtual void AddIncludeFilePath(const TCHAR* Path) override`
- L607 _public function_ `virtual const TCHAR* GetIncludeFilePath(int32 Index) const override`
- L609 _public function_ `virtual int32 GetAdditionalDefineCount() const override`
- L610 _public function_ `virtual void AddAdditionalDefine(const TCHAR* Define) override`
- L611 _public function_ `virtual const TCHAR* GetAdditionalDefine(int32 Index) const override`
- L613 _public function_ `virtual int32 GetArgumentNameCount() const override`
- L614 _public prototype_ `virtual void SetArgumentName(int32 ArgIndex, const TCHAR* ArgName) override;`
- L615 _public function_ `virtual const TCHAR* GetArgumentName(int32 Index) const override`
- L617 _public function_ `virtual void ResetExpressionImpl() override`
- L628 _public function_ `virtual FMD5Hash CalculateElementHash(bool bForce) override`
- L653 _protected member_ `TReflected<FString> Code;`
- L654 _protected member_ `TReflected<FString> Description;`
- L655 _protected member_ `TReflected<EDatasmithShaderDataType, uint32> OutputType = EDatasmithShaderDataType::Float1;`
- L656 _protected member_ `TReflected<TArray<FString>> IncludeFilePaths;`
- L657 _protected member_ `TReflected<TArray<FString>> Defines;`
- L658 _protected member_ `TReflected<TArray<FString>> ArgNames;`
- L659 _protected member_ `TDatasmithReferenceArrayProxy< FDatasmithExpressionInputImpl > Inputs;`

#### class `FDatasmithUEPbrMaterialElementImpl`  
`class FDatasmithUEPbrMaterialElementImpl : public FDatasmithBaseMaterialElementImpl< IDatasmithUEPbrMaterialElement >`  
_L662-749_
- inherits: `FDatasmithBaseMaterialElementImpl<IDatasmithUEPbrMaterialElement>`
- L665 _public prototype_ `explicit FDatasmithUEPbrMaterialElementImpl( const TCHAR* InName );`
- L666 _public prototype_ `virtual ~FDatasmithUEPbrMaterialElementImpl() = default;`
- L668 _public prototype_ `virtual FMD5Hash CalculateElementHash(bool bForce) override;`
- L670 _public function_ `virtual IDatasmithExpressionInput& GetBaseColor() override`
- L671 _public function_ `virtual IDatasmithExpressionInput& GetMetallic() override`
- L672 _public function_ `virtual IDatasmithExpressionInput& GetSpecular() override`
- L673 _public function_ `virtual IDatasmithExpressionInput& GetRoughness() override`
- L674 _public function_ `virtual IDatasmithExpressionInput& GetEmissiveColor() override`
- L675 _public function_ `virtual IDatasmithExpressionInput& GetOpacity() override`
- L676 _public function_ `virtual IDatasmithExpressionInput& GetNormal() override`
- L677 _public function_ `virtual IDatasmithExpressionInput& GetRefraction() override`
- L678 _public function_ `virtual IDatasmithExpressionInput& GetAmbientOcclusion() override`
- L679 _public function_ `virtual IDatasmithExpressionInput& GetClearCoat() override`
- L680 _public function_ `virtual IDatasmithExpressionInput& GetClearCoatRoughness() override`
- L681 _public function_ `virtual IDatasmithExpressionInput& GetWorldPositionOffset() override`
- L682 _public function_ `virtual IDatasmithExpressionInput& GetMaterialAttributes() override`
- L684 _public function_ `virtual int GetBlendMode() const override`
- L685 _public function_ `virtual void SetBlendMode( int InBlendMode ) override`
- L687 _public function_ `virtual bool GetTwoSided() const override`
- L688 _public function_ `virtual void SetTwoSided( bool bInTwoSided ) override`
- L690 _public function_ `virtual bool GetIsThinSurface() const override`
- L691 _public function_ `virtual void SetIsThinSurface(bool bInIsThinSurface) override`
- L693 _public function_ `virtual bool GetUseMaterialAttributes() const override`
- L694 _public function_ `virtual void SetUseMaterialAttributes( bool bInUseMaterialAttributes ) override`
- L696 _public function_ `virtual bool GetMaterialFunctionOnly() const override`
- L697 _public function_ `virtual void SetMaterialFunctionOnly(bool bInMaterialFunctionOnly) override`
- L699 _public function_ `virtual float GetOpacityMaskClipValue() const override`
- L700 _public function_ `virtual void SetOpacityMaskClipValue(float InClipValue) override`
- L702 _public function_ `virtual int GetTranslucencyLightingMode() const`
- L703 _public function_ `virtual void SetTranslucencyLightingMode(int InMode)`
- L705 _public function_ `virtual int32 GetExpressionsCount() const override`
- L706 _public prototype_ `virtual IDatasmithMaterialExpression* GetExpression( int32 Index ) override;`
- L707 _public prototype_ `virtual int32 GetExpressionIndex( const IDatasmithMaterialExpression* Expression ) const override;`
- L709 _public prototype_ `virtual IDatasmithMaterialExpression* AddMaterialExpression( const EDatasmithMaterialExpressionType ExpressionType ) override;`
- L711 _public prototype_ `virtual void ResetExpressionGraph( bool bRemoveAllExpressions ) override;`
- L713 _public function_ `virtual void SetParentLabel( const TCHAR* InParentLabel ) override`
- L714 _public prototype_ `virtual const TCHAR* GetParentLabel() const override;`
- L716 _public function_ `virtual void SetShadingModel( const EDatasmithShadingModel InShadingModel ) override`
- L717 _public function_ `virtual EDatasmithShadingModel GetShadingModel() const override`
- L719 _public prototype_ `virtual void CustomSerialize(class DirectLink::FSnapshotProxy& Ar) override;`
- L722 _protected member_ `TDatasmithReferenceProxy< FDatasmithExpressionInputImpl > BaseColor;`
- L723 _protected member_ `TDatasmithReferenceProxy< FDatasmithExpressionInputImpl > Metallic;`
- L724 _protected member_ `TDatasmithReferenceProxy< FDatasmithExpressionInputImpl > Specular;`
- L725 _protected member_ `TDatasmithReferenceProxy< FDatasmithExpressionInputImpl > Roughness;`
- L726 _protected member_ `TDatasmithReferenceProxy< FDatasmithExpressionInputImpl > EmissiveColor;`
- L727 _protected member_ `TDatasmithReferenceProxy< FDatasmithExpressionInputImpl > Opacity;`
- L728 _protected member_ `TDatasmithReferenceProxy< FDatasmithExpressionInputImpl > Normal;`
- L729 _protected member_ `TDatasmithReferenceProxy< FDatasmithExpressionInputImpl > WorldDisplacement;`
- L730 _protected member_ `TDatasmithReferenceProxy< FDatasmithExpressionInputImpl > Refraction;`
- L731 _protected member_ `TDatasmithReferenceProxy< FDatasmithExpressionInputImpl > AmbientOcclusion;`
- L732 _protected member_ `TDatasmithReferenceProxy< FDatasmithExpressionInputImpl > ClearCoat;`
- L733 _protected member_ `TDatasmithReferenceProxy< FDatasmithExpressionInputImpl > ClearCoatRoughness;`
- L734 _protected member_ `TDatasmithReferenceProxy< FDatasmithExpressionInputImpl > WorldPositionOffset;`
- L735 _protected member_ `TDatasmithReferenceProxy< FDatasmithExpressionInputImpl > MaterialAttributes;`
- L737 _protected member_ `TDatasmithReferenceArrayProxy< IDatasmithMaterialExpression > Expressions;`
- L739 _protected member_ `TReflected<int32> BlendMode;`
- L740 _protected member_ `TReflected<bool> bTwoSided;`
- L741 _protected member_ `TReflected<bool> bIsThinSurface;`
- L742 _protected member_ `TReflected<bool> bUseMaterialAttributes;`
- L743 _protected member_ `TReflected<bool> bMaterialFunctionOnly;`
- L744 _protected member_ `TReflected<float> OpacityMaskClipValue;`
- L745 _protected member_ `TReflected<int32> TranslucencyLightingMode;`
- L747 _protected member_ `TReflected<FString> ParentLabel;`
- L748 _protected member_ `TReflected<EDatasmithShadingModel, uint8> ShadingModel;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API DATASMITHCORE_API`
- L14 _namespace_ `namespace FDatasmithExpressionUtils`
- L16 _function_ `FORCEINLINE void UpdateHashWithString(FMD5& MD5, const FString& String)` (scope `FDatasmithExpressionUtils`)
- L24 _function_ `FORCEINLINE void UpdateHashWithStrings(FMD5& MD5, const TArray<FString>& Strings)` (scope `FDatasmithExpressionUtils`)
- L33 _function_ `template< typename ReferenceType > void UpdateHashWithReference(FMD5& MD5, TDatasmithReferenceProxy<ReferenceType>& Reference)` (scope `FDatasmithExpressionUtils`)
- L43 _function_ `template< typename ClassType > void UpdateHashWithArray(FMD5& MD5, TDatasmithReferenceArrayProxy<ClassType>& Array)` (scope `FDatasmithExpressionUtils`)

### `Source/Runtime/Datasmith/DatasmithCore/Private/DatasmithSceneElementsImpl.h` (Private)


#### class `FDatasmithElementImpl`  
`template< typename InterfaceType > class FDatasmithElementImpl : public InterfaceType`  
_L24-58_
- inherits: `InterfaceType`
- L27 _public prototype_ `FDatasmithElementImpl(const TCHAR* InName, EDatasmithElementType InType, uint64 InSubType = 0);`
- L28 _public function_ `virtual ~FDatasmithElementImpl()`
- L30 _public function_ `virtual bool IsA( EDatasmithElementType InType ) const override`
- L32 _public function_ `virtual const TCHAR* GetName() const override`
- L33 _public function_ `virtual void SetName(const TCHAR* InName) override`
- L35 _public function_ `virtual const TCHAR* GetLabel() const override`
- L36 _public function_ `virtual void SetLabel(const TCHAR* InLabel) override`
- L38 _public function_ `virtual FMD5Hash CalculateElementHash(bool) override`
- L41 _public function_ `virtual TSharedPtr<DirectLink::FSceneGraphSharedState> MakeSharedState() const override`
- L42 _public function_ `virtual const DirectLink::FParameterStore& GetStore() const override`
- L43 _public function_ `virtual DirectLink::FParameterStore& GetStore() override`
- L46 _protected function_ `virtual bool IsSubTypeInternal( uint64 InSubType ) const`
- L47 _protected function_ `EDatasmithElementType GetElementType() const`
- L48 _protected function_ `uint64 GetSubType() const`
- L51 _protected member_ `FMD5Hash ElementHash;`
- L53 _protected member_ `DirectLink::FParameterStore Store;`
- L54 _protected member_ `TReflected<EDatasmithElementType, uint64> Type;`
- L55 _protected member_ `TReflected<uint64> Subtype;`
- L56 _protected member_ `TReflected<FString> Name;`
- L57 _protected member_ `TReflected<FString> Label;`
- L62 _function_ `template< typename InterfaceType > inline FDatasmithElementImpl< InterfaceType >::FDatasmithElementImpl(const TCHAR* InName, EDatasmithElementType InType, uint64 InSubType) : Type(InType) , Subtype(InSubType)`

#### class `FDatasmithKeyValuePropertyImpl`  
`class FDatasmithKeyValuePropertyImpl : public FDatasmithElementImpl< IDatasmithKeyValueProperty >`  
_L73-93_
- inherits: `FDatasmithElementImpl<IDatasmithKeyValueProperty>`
- L76 _public prototype_ `FDatasmithKeyValuePropertyImpl(const TCHAR* InName);`
- L77 _public function_ `virtual void SetName(const TCHAR* InName) override`
- L79 _public function_ `EDatasmithKeyValuePropertyType GetPropertyType() const override`
- L80 _public prototype_ `void SetPropertyType( EDatasmithKeyValuePropertyType InType ) override;`
- L82 _public function_ `const TCHAR* GetValue() const override`
- L83 _public prototype_ `void SetValue( const TCHAR* InValue ) override;`
- L85 _public member_ `static TSharedPtr< IDatasmithKeyValueProperty > NullPropertyPtr;`
- L88 _protected prototype_ `void FormatValue();`
- L91 _private member_ `TReflected<EDatasmithKeyValuePropertyType, uint8> PropertyType;`
- L92 _private member_ `TReflected<FString> Value;`

#### enum `EActorFlags`  
`enum class EActorFlags : uint8`  
_L96-101_
- L98 _public enumerator_ `IsAComponent = 0x01`
- L99 _public enumerator_ `IsASelector = 0x02` — Deprecated
- L100 _public enumerator_ `IsVisible = 0x04`

#### class `FDatasmithActorElementImpl`  
`template< typename InterfaceType > class FDatasmithActorElementImpl : public FDatasmithElementImpl< InterfaceType >, public TSharedFromThis< FDatasmithActorElementImpl< InterfaceType > >`  
_L107-236_
- inherits: `FDatasmithElementImpl<InterfaceType>,TSharedFromThis<FDatasmithActorElementImpl<InterfaceType>>`
- L111 _public prototype_ `FDatasmithActorElementImpl(const TCHAR* InName, EDatasmithElementType InType);`
- L113 _public function_ `virtual FVector GetTranslation() const override`
- L114 _public function_ `virtual void SetTranslation(double InX, double InY, double InZ, bool bKeepChildrenRelative) override`
- L115 _public function_ `virtual void SetTranslation(const FVector& Value, bool bKeepChildrenRelative) override`
- L128 _public function_ `virtual FVector GetScale() const override`
- L129 _public function_ `virtual void SetScale(double InX, double InY, double InZ, bool bKeepChildrenRelative) override`
- L130 _public function_ `virtual void SetScale(const FVector& Value, bool bKeepChildrenRelative) override`
- L143 _public function_ `virtual FQuat GetRotation() const override`
- L144 _public function_ `virtual void SetRotation(double InX, double InY, double InZ, double InW, bool bKeepChildrenRelative) override`
- L145 _public function_ `virtual void SetRotation(const FQuat& Value, bool bKeepChildrenRelative) override`
- L158 _public prototype_ `virtual FTransform GetRelativeTransform() const override;`
- L160 _public function_ `virtual const TCHAR* GetLayer() const override`
- L161 _public function_ `virtual void SetLayer(const TCHAR* InLayer) override`
- L163 _public function_ `virtual void AddTag(const TCHAR* InTag) override`
- L164 _public function_ `virtual void ResetTags() override`
- L165 _public function_ `virtual int32 GetTagsCount() const`
- L166 _public function_ `virtual const TCHAR* GetTag(int32 TagIndex) const override`
- L168 _public prototype_ `virtual void AddChild(const TSharedPtr< IDatasmithActorElement >& InChild, EDatasmithActorAttachmentRule AttachementRule = EDatasmithActorAttachmentRule::KeepWorldTransform) override;`
- L169 _public function_ `virtual int32 GetChildrenCount() const override`
- L175 _public function_ `virtual TSharedPtr< IDatasmithActorElement > GetChild(int32 InIndex) override` — Get the 'InIndex'th child of the actor
- L180 _public function_ `virtual const TSharedPtr< IDatasmithActorElement >& GetChild(int32 InIndex) const override`
- L185 _public function_ `virtual void RemoveChild(const TSharedPtr< IDatasmithActorElement >& InChild) override`
- L191 _public function_ `virtual const TSharedPtr< IDatasmithActorElement >& GetParentActor() const override`
- L196 _public function_ `virtual void SetIsAComponent(bool Value) override`
- L197 _public function_ `virtual bool IsAComponent() const override`
- L199 _public function_ `virtual void SetVisibility(bool bInVisibility) override`
- L200 _public function_ `virtual bool GetVisibility() const override`
- L202 _public function_ `virtual void SetCastShadow(bool bInCastShadow) override`
- L203 _public function_ `virtual bool GetCastShadow() const override`
- L205 _public function_ `virtual void SetMobility(EDatasmithActorMobilityType InMobility) override`
- L206 _public function_ `virtual EDatasmithActorMobilityType GetMobility() const override`
- L210 _protected prototype_ `void ConvertChildsToRelative();` — Converts all children's transforms to relative
- L213 _protected prototype_ `void ConvertChildsToWorld();` — Converts all children's transforms to world
- L215 _protected function_ `void SetInternalRotation(const FQuat& Value)`
- L216 _protected function_ `void SetInternalScale(const FVector& Value)`
- L217 _protected function_ `void SetInternalTranslation(const FVector& Value)`
- L220 _private member_ `static TSharedPtr<IDatasmithActorElement> NullActorPtr;`
- L222 _private member_ `TReflected<FVector> Translation;`
- L223 _private member_ `TReflected<FVector> Scale;`
- L224 _private member_ `TReflected<FQuat> Rotation;`
- L226 _private member_ `TReflected<FString> Layer;`
- L228 _private member_ `TReflected<TArray<FString>> Tags;`
- L230 _private member_ `TDatasmithReferenceArrayProxy<IDatasmithActorElement> Children;`
- L231 _private member_ `TDatasmithReferenceProxy<IDatasmithActorElement> Parent;`
- L233 _private member_ `TReflected<EActorFlags, uint8> Flags;`
- L234 _private member_ `TReflected<bool> bCastShadow;`
- L235 _private member_ `TReflected<EDatasmithActorMobilityType, uint8> Mobility;`
- L242 _function_ `template< typename T > inline FDatasmithActorElementImpl<T>::FDatasmithActorElementImpl(const TCHAR* InName, EDatasmithElementType ChildType) : FDatasmithElementImpl<T>(InName, EDatasmithElementType::Actor | ChildType) , Translation(FVector::ZeroVector) , Scale(FVector::OneVector) , Rotation(FQuat::Identity) , Flags(EActorFlags::IsVisible) , bCastShadow(true) , Mobility(EDatasmithActorMobilityType::Static)`
- L265 _function_ `template< typename T > inline FTransform FDatasmithActorElementImpl<T>::GetRelativeTransform() const`
- L280 _function_ `template< typename T > inline void FDatasmithActorElementImpl<T>::AddChild(const TSharedPtr< IDatasmithActorElement >& InChild, EDatasmithActorAttachmentRule AttachementRule)`
- L299 _function_ `template< typename T > inline void FDatasmithActorElementImpl<T>::ConvertChildsToRelative()`
- L323 _function_ `template< typename T > inline void FDatasmithActorElementImpl<T>::ConvertChildsToWorld()`

#### class `FDatasmithMeshElementImpl`  
`class FDatasmithMeshElementImpl : public FDatasmithElementImpl< IDatasmithMeshElement >`  
_L347-396_
- inherits: `FDatasmithElementImpl<IDatasmithMeshElement>`
- L350 _public prototype_ `explicit FDatasmithMeshElementImpl(const TCHAR* InName);`
- L352 _public prototype_ `virtual FMD5Hash CalculateElementHash(bool bForce) override;`
- L354 _public function_ `virtual const TCHAR* GetFile() const override`
- L355 _public function_ `virtual void SetFile(const TCHAR* InFile) override`
- L357 _public function_ `virtual FMD5Hash GetFileHash() const override`
- L358 _public function_ `virtual void SetFileHash(FMD5Hash Hash) override`
- L360 _public function_ `virtual void SetDimensions(float InArea, float InWidth, float InHeight, float InDepth) override`
- L361 _public function_ `virtual FVector3f GetDimensions() const override`
- L363 _public function_ `virtual float GetArea() const override`
- L364 _public function_ `virtual float GetWidth() const override`
- L365 _public function_ `virtual float GetHeight() const override`
- L366 _public function_ `virtual float GetDepth() const override`
- L368 _public function_ `virtual int32 GetLightmapCoordinateIndex() const`
- L369 _public function_ `virtual void SetLightmapCoordinateIndex(int32 UVChannel)`
- L371 _public function_ `virtual int32 GetLightmapSourceUV() const override`
- L372 _public function_ `virtual void SetLightmapSourceUV( int32 UVChannel ) override`
- L374 _public prototype_ `virtual void SetMaterial(const TCHAR* MaterialPathName, int32 SlotId) override;`
- L375 _public prototype_ `virtual const TCHAR* GetMaterial(int32 SlotId) const override;`
- L377 _public prototype_ `virtual int32 GetMaterialSlotCount() const override;`
- L378 _public prototype_ `virtual TSharedPtr<const IDatasmithMaterialIDElement> GetMaterialSlotAt(int32 Index) const override;`
- L379 _public prototype_ `virtual TSharedPtr<IDatasmithMaterialIDElement> GetMaterialSlotAt(int32 Index) override;`
- L382 _protected function_ `virtual int32 GetLODCount() const override`
- L383 _protected function_ `virtual void SetLODCount(int32 Count) override`
- L386 _private member_ `TReflected<FString> File;`
- L387 _private member_ `TReflected<FMD5Hash> FileHash;`
- L388 _private member_ `TReflected<float> Area;`
- L389 _private member_ `TReflected<float> Width;`
- L390 _private member_ `TReflected<float> Height;`
- L391 _private member_ `TReflected<float> Depth;`
- L392 _private member_ `TReflected<int32> LODCount;`
- L393 _private member_ `TReflected<int32> LightmapCoordinateIndex;`
- L394 _private member_ `TReflected<int32> LightmapSourceUV;`
- L395 _private member_ `TDatasmithReferenceArrayProxy<IDatasmithMaterialIDElement> MaterialSlots;`

#### class `PRAGMA_DISABLE_DEPRECATION_WARNINGS`  
`PRAGMA_DISABLE_DEPRECATION_WARNINGS : public FDatasmithElementImpl< IDatasmithClothElement > PRAGMA_ENABLE_DEPRECATION_WARNINGS`  
_L402-415_
- reflection: `UE_DEPRECATED(5.5, "The experimental Cloth importer is no longer supported.")`
- inherits: `FDatasmithElementImpl<IDatasmithClothElement>PRAGMA_ENABLE_DEPRECATION_WARNINGS`
- desc: Experimental Element that describes a cloth asset.
- L407 _public prototype_ `explicit FDatasmithClothElementImpl(const TCHAR* InName);`
- L410 _public function_ `virtual const TCHAR* GetFile() const override`
- L411 _public function_ `virtual void SetFile(const TCHAR* InFile) override`
- L414 _private member_ `TReflected<FString> File;`

#### class `FDatasmithMaterialIDElementImpl`  
`class FDatasmithMaterialIDElementImpl : public FDatasmithElementImpl< IDatasmithMaterialIDElement >`  
_L418-432_
- inherits: `FDatasmithElementImpl<IDatasmithMaterialIDElement>`
- L421 _public prototype_ `explicit FDatasmithMaterialIDElementImpl(const TCHAR* InName);`
- L422 _public function_ `virtual void SetName(const TCHAR* InName) override`
- L427 _public function_ `virtual int32 GetId() const override`
- L428 _public function_ `virtual void SetId(int32 InId) override`
- L431 _private member_ `TReflected<int32> Id;`

#### class `FDatasmithMeshActorElementImpl`  
`template< typename InterfaceType = IDatasmithMeshActorElement > class FDatasmithMeshActorElementImpl : public FDatasmithActorElementImpl< InterfaceType >`  
_L435-460_
- inherits: `FDatasmithActorElementImpl<InterfaceType>`
- L440 _public prototype_ `explicit FDatasmithMeshActorElementImpl(const TCHAR* InName);`
- L442 _public prototype_ `virtual void AddMaterialOverride(const TCHAR* InMaterialName, int32 Id) override;`
- L443 _public prototype_ `virtual void AddMaterialOverride(const TSharedPtr< IDatasmithMaterialIDElement >& Material) override;`
- L445 _public prototype_ `virtual int32 GetMaterialOverridesCount() const override;`
- L446 _public prototype_ `virtual TSharedPtr<IDatasmithMaterialIDElement> GetMaterialOverride(int32 i) override;`
- L447 _public prototype_ `virtual TSharedPtr<const IDatasmithMaterialIDElement> GetMaterialOverride(int32 i) const override;`
- L448 _public prototype_ `virtual void RemoveMaterialOverride(const TSharedPtr< IDatasmithMaterialIDElement >& Material) override;`
- L449 _public prototype_ `virtual void ResetMaterialOverrides() override;`
- L451 _public prototype_ `virtual const TCHAR* GetStaticMeshPathName() const override;`
- L452 _public prototype_ `virtual void SetStaticMeshPathName(const TCHAR* InStaticMeshName) override;`
- L455 _protected prototype_ `explicit FDatasmithMeshActorElementImpl(const TCHAR* InName, EDatasmithElementType ElementType);`
- L458 _private member_ `TReflected<FString> StaticMeshPathName;`
- L459 _private member_ `TDatasmithReferenceArrayProxy<IDatasmithMaterialIDElement> Materials;`
- L463 _function_ `template < typename InterfaceType > FDatasmithMeshActorElementImpl< InterfaceType >::FDatasmithMeshActorElementImpl(const TCHAR* InName) : FDatasmithMeshActorElementImpl< InterfaceType >(InName, EDatasmithElementType::None)`
- L468 _function_ `template < typename InterfaceType > FDatasmithMeshActorElementImpl< InterfaceType >::FDatasmithMeshActorElementImpl(const TCHAR* InName, EDatasmithElementType ElementType) : FDatasmithActorElementImpl< InterfaceType >(InName, EDatasmithElementType::StaticMeshActor | ElementType)`
- L476 _function_ `template < typename InterfaceType > void FDatasmithMeshActorElementImpl< InterfaceType >::AddMaterialOverride(const TCHAR* InMaterialName, int32 Id)`
- L494 _function_ `template < typename InterfaceType > void FDatasmithMeshActorElementImpl< InterfaceType >::AddMaterialOverride(const TSharedPtr< IDatasmithMaterialIDElement >& Material)`
- L500 _function_ `template < typename InterfaceType > int32 FDatasmithMeshActorElementImpl< InterfaceType >::GetMaterialOverridesCount() const`
- L506 _function_ `template < typename InterfaceType > TSharedPtr<IDatasmithMaterialIDElement> FDatasmithMeshActorElementImpl< InterfaceType >::GetMaterialOverride(int32 i)`
- L517 _function_ `template < typename InterfaceType > TSharedPtr<const IDatasmithMaterialIDElement> FDatasmithMeshActorElementImpl< InterfaceType >::GetMaterialOverride(int32 i) const`
- L528 _function_ `template < typename InterfaceType > void FDatasmithMeshActorElementImpl< InterfaceType >::RemoveMaterialOverride(const TSharedPtr< IDatasmithMaterialIDElement >& Material)`
- L534 _function_ `template < typename InterfaceType > void FDatasmithMeshActorElementImpl< InterfaceType >::ResetMaterialOverrides()`
- L540 _function_ `template < typename InterfaceType > const TCHAR* FDatasmithMeshActorElementImpl< InterfaceType >::GetStaticMeshPathName() const`
- L546 _function_ `template < typename InterfaceType > void FDatasmithMeshActorElementImpl< InterfaceType >::SetStaticMeshPathName(const TCHAR* InStaticMeshName)`

#### class `FDatasmithHierarchicalInstancedStaticMeshActorElementImpl`  
`class FDatasmithHierarchicalInstancedStaticMeshActorElementImpl : public FDatasmithMeshActorElementImpl< IDatasmithHierarchicalInstancedStaticMeshActorElement >`  
_L551-566_
- inherits: `FDatasmithMeshActorElementImpl<IDatasmithHierarchicalInstancedStaticMeshActorElement>`
- L554 _public prototype_ `explicit FDatasmithHierarchicalInstancedStaticMeshActorElementImpl(const TCHAR* InName);`
- L556 _public prototype_ `virtual ~FDatasmithHierarchicalInstancedStaticMeshActorElementImpl();`
- L558 _public prototype_ `virtual int32 GetInstancesCount() const override;`
- L559 _public prototype_ `virtual void ReserveSpaceForInstances(int32 NumIntances) override;`
- L560 _public prototype_ `virtual int32 AddInstance(const FTransform& Transform) override;`
- L561 _public prototype_ `virtual FTransform GetInstance(int32 InstanceIndex) const override;`
- L562 _public prototype_ `virtual void RemoveInstance(int32 InstanceIndex) override;`
- L565 _private member_ `TReflected<TArray<FTransform>> Instances;`

#### enum `LightActorFlags`  
`enum class LightActorFlags : uint8`  
_L568-575_
- L570 _public enumerator_ `LightNone = 0x00`
- L571 _public enumerator_ `LightEnabled = 0x01`
- L572 _public enumerator_ `LightUseTemperature = 0x02`
- L573 _public enumerator_ `LightUseIes = 0x04`
- L574 _public enumerator_ `LightUseIesBrightness = 0x08`

#### class `FDatasmithLightActorElementImpl`  
`template< typename InterfaceType = IDatasmithLightActorElement > class FDatasmithLightActorElementImpl : public FDatasmithActorElementImpl< InterfaceType >`  
_L579-647_
- inherits: `FDatasmithActorElementImpl<InterfaceType>`
- L583 _public function_ `virtual bool IsEnabled() const override`
- L584 _public function_ `virtual void SetEnabled(bool bInIsEnabled) override`
- L586 _public function_ `virtual double GetIntensity() const override`
- L587 _public function_ `virtual void SetIntensity(double InIntensity) override`
- L589 _public function_ `virtual FLinearColor GetColor() const override`
- L590 _public function_ `virtual void SetColor(FLinearColor InColor) override`
- L592 _public function_ `virtual double GetTemperature() const override`
- L593 _public function_ `virtual void SetTemperature(double InTemperature) override`
- L595 _public function_ `virtual bool GetUseTemperature() const override`
- L596 _public function_ `virtual void SetUseTemperature(bool bInUseTemperature) override`
- L598 _public function_ `virtual const TCHAR* GetIesFile() const override`
- L599 _public function_ `virtual void SetIesFile(const TCHAR* InIesFile) override`
- L601 _public function_ `virtual bool GetUseIes() const override`
- L602 _public function_ `virtual void SetUseIes(bool bInUseIes) override`
- L604 _public function_ `virtual double GetIesBrightnessScale() const override`
- L605 _public function_ `virtual void SetIesBrightnessScale(double InIesBrightnessScale) override`
- L607 _public function_ `virtual bool GetUseIesBrightness() const override`
- L608 _public function_ `virtual void SetUseIesBrightness(bool bInUseIesBrightness) override`
- L610 _public function_ `virtual FQuat GetIesRotation() const override`
- L611 _public function_ `virtual void SetIesRotation(const FQuat& InIesRotation) override`
- L613 _public function_ `TSharedPtr< IDatasmithMaterialIDElement >& GetLightFunctionMaterial() override`
- L615 _public function_ `void SetLightFunctionMaterial(const TSharedPtr< IDatasmithMaterialIDElement >& InMaterial) override`
- L617 _public function_ `void SetLightFunctionMaterial(const TCHAR* InMaterialName) override`
- L623 _public function_ `const TCHAR* GetIesTexturePathName() const override`
- L624 _public function_ `void SetIesTexturePathName(const TCHAR* InTextureName) override`
- L627 _protected prototype_ `explicit FDatasmithLightActorElementImpl(const TCHAR* InName, EDatasmithElementType ChildType);`
- L630 _private member_ `TReflected<double> Intensity;`
- L632 _private member_ `TReflected<FVector> Color;`
- L634 _private member_ `TReflected<double> Temperature;`
- L636 _private member_ `TReflected<FString> IesFile;`
- L638 _private member_ `TReflected<FString> IesTexturePathName;`
- L640 _private member_ `TReflected<double> IesBrightnessScale;`
- L642 _private member_ `TReflected<FQuat> IesRotation;`
- L644 _private member_ `TReflected<LightActorFlags, uint8> LightFLags;`
- L646 _private member_ `TDatasmithReferenceProxy< IDatasmithMaterialIDElement > LightFunctionMaterial;`
- L650 _function_ `template<typename InterfaceType> FDatasmithLightActorElementImpl<InterfaceType>::FDatasmithLightActorElementImpl(const TCHAR* InName, EDatasmithElementType ChildType) : FDatasmithActorElementImpl< InterfaceType >( InName, EDatasmithElementType::Light | ChildType ) , Intensity(1.0) , Color(FVector::OneVector) , Temperature(6500.0) , IesBrightnessScale(1.0) , IesRotation(FQuat::Identity) , LightFLags(LightActorFlags::LightEnabled)`

#### class `FDatasmithPointLightElementImpl`  
`template< typename InterfaceType = IDatasmithPointLightElement > class FDatasmithPointLightElementImpl : public FDatasmithLightActorElementImpl< InterfaceType >`  
_L672-713_
- inherits: `FDatasmithLightActorElementImpl<InterfaceType>`
- L677 _public function_ `explicit FDatasmithPointLightElementImpl(const TCHAR* InName) : FDatasmithPointLightElementImpl( InName, EDatasmithElementType::None )`
- L682 _public function_ `virtual void SetIntensityUnits(EDatasmithLightUnits InUnits)`
- L683 _public function_ `virtual EDatasmithLightUnits GetIntensityUnits() const`
- L685 _public function_ `virtual float GetSourceRadius() const override`
- L686 _public function_ `virtual void SetSourceRadius(float InSourceRadius) override`
- L688 _public function_ `virtual float GetSourceLength() const override`
- L689 _public function_ `virtual void SetSourceLength(float InSourceLength) override`
- L691 _public function_ `virtual float GetAttenuationRadius() const override`
- L692 _public function_ `virtual void SetAttenuationRadius(float InAttenuationRadius) override`
- L695 _protected function_ `explicit FDatasmithPointLightElementImpl(const TCHAR* InName, EDatasmithElementType ChildType) : FDatasmithLightActorElementImpl< InterfaceType >( InName, EDatasmithElementType::PointLight | ChildType ) , Units(EDatasmithLightUnits::Unitless) , SourceRadius(-1) , SourceLength(-1) , AttenuationRadius(-1)`
- L709 _private member_ `TReflected<EDatasmithLightUnits, uint8> Units;`
- L710 _private member_ `TReflected<float> SourceRadius;`
- L711 _private member_ `TReflected<float> SourceLength;`
- L712 _private member_ `TReflected<float> AttenuationRadius;`

#### class `FDatasmithSpotLightElementImpl`  
`template< typename InterfaceType = IDatasmithSpotLightElement > class FDatasmithSpotLightElementImpl : public FDatasmithPointLightElementImpl< InterfaceType >`  
_L716-758_
- inherits: `FDatasmithPointLightElementImpl<InterfaceType>`
- L720 _public function_ `explicit FDatasmithSpotLightElementImpl(const TCHAR* InName) : FDatasmithSpotLightElementImpl( InName, EDatasmithElementType::None )`
- L725 _public function_ `virtual float GetInnerConeAngle() const override`
- L730 _public function_ `virtual void SetInnerConeAngle(float InInnerConeAngle) override`
- L735 _public function_ `virtual float GetOuterConeAngle() const override`
- L740 _public function_ `virtual void SetOuterConeAngle(float InOuterConeAngle) override`
- L746 _protected function_ `explicit FDatasmithSpotLightElementImpl(const TCHAR* InName, EDatasmithElementType ChildType) : FDatasmithPointLightElementImpl< InterfaceType >( InName, EDatasmithElementType::SpotLight | ChildType ) , InnerConeAngle(45.f) , OuterConeAngle(60.f)`
- L756 _private member_ `TReflected<float> InnerConeAngle;`
- L757 _private member_ `TReflected<float> OuterConeAngle;`

#### class `FDatasmithDirectionalLightElementImpl`  
`class FDatasmithDirectionalLightElementImpl : public FDatasmithLightActorElementImpl< IDatasmithDirectionalLightElement >`  
_L760-767_
- inherits: `FDatasmithLightActorElementImpl<IDatasmithDirectionalLightElement>`
- L763 _public function_ `explicit FDatasmithDirectionalLightElementImpl(const TCHAR* InName) : FDatasmithLightActorElementImpl< IDatasmithDirectionalLightElement >( InName, EDatasmithElementType::DirectionalLight )`

#### class `FDatasmithAreaLightElementImpl`  
`class FDatasmithAreaLightElementImpl : public FDatasmithSpotLightElementImpl< IDatasmithAreaLightElement >`  
_L769-802_
- inherits: `FDatasmithSpotLightElementImpl<IDatasmithAreaLightElement>`
- L772 _public function_ `explicit FDatasmithAreaLightElementImpl(const TCHAR* InName) : FDatasmithSpotLightElementImpl< IDatasmithAreaLightElement >( InName, EDatasmithElementType::AreaLight ) , LightShape( EDatasmithLightShape::Rectangle ) , LightType( EDatasmithAreaLightType::Point ) , Width( 0.f ) , Length( 0.f )`
- L785 _public function_ `virtual EDatasmithLightShape GetLightShape() const override`
- L786 _public function_ `virtual void SetLightShape(EDatasmithLightShape InShape) override`
- L788 _public function_ `virtual EDatasmithAreaLightType GetLightType() const override`
- L789 _public function_ `virtual void SetLightType(EDatasmithAreaLightType InLightType) override`
- L791 _public function_ `virtual void SetWidth(float InWidth) override`
- L792 _public function_ `virtual float GetWidth() const override`
- L794 _public function_ `virtual void SetLength(float InLength) override`
- L795 _public function_ `virtual float GetLength() const override`
- L798 _private member_ `TReflected<EDatasmithLightShape, uint8> LightShape;`
- L799 _private member_ `TReflected<EDatasmithAreaLightType, uint8> LightType;`
- L800 _private member_ `TReflected<float> Width;`
- L801 _private member_ `TReflected<float> Length;`

#### class `FDatasmithLightmassPortalElementImpl`  
`class FDatasmithLightmassPortalElementImpl : public FDatasmithPointLightElementImpl< IDatasmithLightmassPortalElement >`  
_L804-811_
- inherits: `FDatasmithPointLightElementImpl<IDatasmithLightmassPortalElement>`
- L807 _public function_ `explicit FDatasmithLightmassPortalElementImpl(const TCHAR* InName) : FDatasmithPointLightElementImpl< IDatasmithLightmassPortalElement >( InName, EDatasmithElementType::LightmassPortal )`

#### class `FDatasmithPostProcessElementImpl`  
`class FDatasmithPostProcessElementImpl : public FDatasmithElementImpl< IDatasmithPostProcessElement >`  
_L813-855_
- inherits: `FDatasmithElementImpl<IDatasmithPostProcessElement>`
- L816 _public prototype_ `FDatasmithPostProcessElementImpl();`
- L818 _public function_ `virtual float GetTemperature() const override`
- L819 _public function_ `virtual void SetTemperature(float InTemperature) override`
- L821 _public function_ `virtual FLinearColor GetColorFilter() const override`
- L822 _public function_ `virtual void SetColorFilter(FLinearColor InColorFilter) override`
- L824 _public function_ `virtual float GetVignette() const override`
- L825 _public function_ `virtual void SetVignette(float InVignette) override`
- L827 _public function_ `virtual float GetDof() const override`
- L828 _public function_ `virtual void SetDof(float InDof) override`
- L830 _public function_ `virtual float GetMotionBlur() const override`
- L831 _public function_ `virtual void SetMotionBlur(float InMotionBlur) override`
- L833 _public function_ `virtual float GetSaturation() const override`
- L834 _public function_ `virtual void SetSaturation(float InSaturation) override`
- L836 _public function_ `virtual float GetCameraISO() const override`
- L837 _public function_ `virtual void SetCameraISO(float InCameraISO) override`
- L839 _public function_ `virtual float GetCameraShutterSpeed() const override`
- L840 _public function_ `virtual void SetCameraShutterSpeed(float InCameraShutterSpeed) override`
- L842 _public function_ `virtual float GetDepthOfFieldFstop() const override`
- L843 _public function_ `virtual void SetDepthOfFieldFstop( float InFstop ) override`
- L846 _private member_ `TReflected<float> Temperature;`
- L847 _private member_ `TReflected<FLinearColor> ColorFilter;`
- L848 _private member_ `TReflected<float> Vignette;`
- L849 _private member_ `TReflected<float> Dof;`
- L850 _private member_ `TReflected<float> MotionBlur;`
- L851 _private member_ `TReflected<float> Saturation;`
- L852 _private member_ `TReflected<float> CameraISO;`
- L853 _private member_ `TReflected<float> CameraShutterSpeed;`
- L854 _private member_ `TReflected<float> Fstop;`

#### class `FDatasmithPostProcessVolumeElementImpl`  
`class FDatasmithPostProcessVolumeElementImpl : public FDatasmithActorElementImpl< IDatasmithPostProcessVolumeElement >`  
_L857-876_
- inherits: `FDatasmithActorElementImpl<IDatasmithPostProcessVolumeElement>`
- L860 _public prototype_ `FDatasmithPostProcessVolumeElementImpl( const TCHAR* InName );`
- L862 _public function_ `virtual TSharedRef< IDatasmithPostProcessElement > GetSettings() const override`
- L863 _public function_ `virtual void SetSettings(const TSharedRef< IDatasmithPostProcessElement >& InSettings) override`
- L865 _public function_ `virtual bool GetEnabled() const`
- L866 _public function_ `virtual void SetEnabled( bool bInEnabled )`
- L868 _public function_ `virtual bool GetUnbound() const override`
- L869 _public function_ `virtual void SetUnbound( bool bInUnbound) override`
- L872 _private member_ `TDatasmithReferenceProxy<IDatasmithPostProcessElement> Settings;`
- L874 _private member_ `TReflected<bool> bEnabled;`
- L875 _private member_ `TReflected<bool> bUnbound;`

#### class `FDatasmithCameraActorElementImpl`  
`class FDatasmithCameraActorElementImpl : public FDatasmithActorElementImpl< IDatasmithCameraActorElement >`  
_L878-922_
- inherits: `FDatasmithActorElementImpl<IDatasmithCameraActorElement>`
- L881 _public prototype_ `explicit FDatasmithCameraActorElementImpl(const TCHAR* InName);`
- L883 _public prototype_ `virtual float GetSensorWidth() const override;`
- L884 _public prototype_ `virtual void SetSensorWidth(float InSensorWidth) override;`
- L886 _public prototype_ `virtual float GetSensorAspectRatio() const override;`
- L887 _public prototype_ `virtual void SetSensorAspectRatio(float InSensorAspectRatio) override;`
- L889 _public function_ `virtual bool GetEnableDepthOfField() const override`
- L890 _public function_ `virtual void SetEnableDepthOfField(bool bInEnableDepthOfField) override`
- L892 _public prototype_ `virtual float GetFocusDistance() const override;`
- L893 _public prototype_ `virtual void SetFocusDistance(float InFocusDistance) override;`
- L895 _public prototype_ `virtual float GetFStop() const override;`
- L896 _public prototype_ `virtual void SetFStop(float InFStop) override;`
- L898 _public prototype_ `virtual float GetFocalLength() const override;`
- L899 _public prototype_ `virtual void SetFocalLength(float InFocalLength) override;`
- L901 _public prototype_ `virtual TSharedPtr< IDatasmithPostProcessElement >& GetPostProcess() override;`
- L902 _public prototype_ `virtual const TSharedPtr< IDatasmithPostProcessElement >& GetPostProcess() const override;`
- L903 _public prototype_ `virtual void SetPostProcess(const TSharedPtr< IDatasmithPostProcessElement >& InPostProcess) override;`
- L905 _public function_ `virtual const TCHAR* GetLookAtActor() const override`
- L906 _public function_ `virtual void SetLookAtActor(const TCHAR* InActorName) override`
- L908 _public function_ `virtual bool GetLookAtAllowRoll() const override`
- L909 _public function_ `virtual void SetLookAtAllowRoll(bool bAllow) override`
- L912 _private member_ `TDatasmithReferenceProxy<IDatasmithPostProcessElement> PostProcess;`
- L914 _private member_ `TReflected<float> SensorWidth;`
- L915 _private member_ `TReflected<float> SensorAspectRatio;`
- L916 _private member_ `TReflected<bool> bEnableDepthOfField;`
- L917 _private member_ `TReflected<float> FocusDistance;`
- L918 _private member_ `TReflected<float> FStop;`
- L919 _private member_ `TReflected<float> FocalLength;`
- L920 _private member_ `TReflected<FString> ActorName;`
- L921 _private member_ `TReflected<bool> bLookAtAllowRoll;`

#### class `FDatasmithCustomActorElementImpl`  
`template< typename InterfaceType = IDatasmithCustomActorElement > class FDatasmithCustomActorElementImpl : public FDatasmithActorElementImpl< InterfaceType >`  
_L925-1005_
- inherits: `FDatasmithActorElementImpl<InterfaceType>`
- L930 _public function_ `explicit FDatasmithCustomActorElementImpl(const TCHAR* InName, EDatasmithElementType InChildType = EDatasmithElementType::None) : FDatasmithActorElementImpl< InterfaceType >(InName, EDatasmithElementType::CustomActor | InChildType)`
- L938 _public function_ `virtual const TCHAR* GetClassOrPathName() const override` — The class name or path to the blueprint to instantiate.
- L939 _public function_ `virtual void SetClassOrPathName( const TCHAR* InClassOrPathName ) override`
- L942 _public function_ `virtual int32 GetPropertiesCount() const override` — Get the total amount of properties in this actor
- L945 _public function_ `virtual const TSharedPtr< IDatasmithKeyValueProperty >& GetProperty(int32 Index) const override` — Get the property i-th of this actor
- L951 _public function_ `virtual const TSharedPtr< IDatasmithKeyValueProperty >& GetPropertyByName(const TCHAR* InName) const override` — Get a property by its name if it exists
- L960 _public function_ `virtual void AddProperty( const TSharedPtr< IDatasmithKeyValueProperty >& InProperty ) override` — Add a property to this actor
- L979 _public function_ `virtual void RemoveProperty( const TSharedPtr< IDatasmithKeyValueProperty >& Property ) override` — Removes a property from this actor, doesn't preserve ordering
- L983 _protected function_ `int32 AddPropertyInternal(const TCHAR* InKey, EDatasmithKeyValuePropertyType InType, const TCHAR* InValue)` — Add a property to this actor
- L1002 _private member_ `TReflected<FString> ClassOrPathName;`
- L1004 _private member_ `TDatasmithReferenceArrayProxy<IDatasmithKeyValueProperty> Properties;`

#### class `FDatasmithLandscapeElementImpl`  
`class FDatasmithLandscapeElementImpl final : public FDatasmithActorElementImpl< IDatasmithLandscapeElement >`  
_L1007-1034_
- inherits: `FDatasmithActorElementImpl<IDatasmithLandscapeElement>`
- L1010 _public function_ `explicit FDatasmithLandscapeElementImpl(const TCHAR* InName) : FDatasmithActorElementImpl(InName, EDatasmithElementType::Landscape)`
- L1022 _public function_ `virtual void SetHeightmap( const TCHAR* InFilePath ) override`
- L1023 _public function_ `virtual const TCHAR* GetHeightmap() const override`
- L1025 _public function_ `virtual void SetMaterial( const TCHAR* InMaterialPathName ) override`
- L1026 _public function_ `virtual const TCHAR* GetMaterial() const override`
- L1029 _private member_ `TDatasmithReferenceProxy<IDatasmithBaseMaterialElement> Material;`
- L1030 _private member_ `TDatasmithReferenceProxy<IDatasmithTextureElement> Heightmap;`
- L1032 _private member_ `TReflected<FString> HeightmapFilePath;`
- L1033 _private member_ `TReflected<FString> MaterialPathName;`

#### class `FDatasmithClothActorElementImpl`  
`class UE_DEPRECATED(5.5, "The experimental Cloth importer is no longer supported.") FDatasmithClothActorElementImpl : public FDatasmithActorElementImpl<IDatasmithClothActorElement>`  
_L1038-1049_
- inherits: `FDatasmithActorElementImpl<IDatasmithClothActorElement>`
- L1042 _public prototype_ `FDatasmithClothActorElementImpl(const TCHAR* InName);`
- L1044 _public function_ `virtual void SetCloth(const TCHAR* InCloth) override`
- L1045 _public function_ `virtual const TCHAR* GetCloth() const override`
- L1048 _private member_ `TReflected<FString> Cloth;`

#### class `FDatasmithEnvironmentElementImpl`  
`class FDatasmithEnvironmentElementImpl : public FDatasmithLightActorElementImpl< IDatasmithEnvironmentElement >`  
_L1053-1068_
- inherits: `FDatasmithLightActorElementImpl<IDatasmithEnvironmentElement>`
- L1056 _public prototype_ `explicit FDatasmithEnvironmentElementImpl(const TCHAR* InName);`
- L1058 _public prototype_ `virtual TSharedPtr<IDatasmithCompositeTexture>& GetEnvironmentComp() override;`
- L1059 _public prototype_ `virtual const TSharedPtr<IDatasmithCompositeTexture>& GetEnvironmentComp() const override;`
- L1061 _public prototype_ `virtual void SetEnvironmentComp(const TSharedPtr<IDatasmithCompositeTexture>& InEnvironmentComp) override;`
- L1062 _public prototype_ `virtual bool GetIsIlluminationMap() const override;`
- L1063 _public prototype_ `virtual void SetIsIlluminationMap(bool bInIsIlluminationMap) override;`
- L1066 _private member_ `TSharedPtr<IDatasmithCompositeTexture> EnvironmentComp;`
- L1067 _private member_ `TReflected<bool> bIsIlluminationMap;`

#### class `FDatasmithTextureElementImpl`  
`class FDatasmithTextureElementImpl : public FDatasmithElementImpl< IDatasmithTextureElement >`  
_L1070-1123_
- inherits: `FDatasmithElementImpl<IDatasmithTextureElement>`
- L1073 _public prototype_ `explicit FDatasmithTextureElementImpl(const TCHAR* InName);`
- L1075 _public prototype_ `virtual FMD5Hash CalculateElementHash(bool bForce) override;`
- L1077 _public prototype_ `virtual const TCHAR* GetFile() const override;`
- L1078 _public prototype_ `virtual void SetFile(const TCHAR* InFile) override;`
- L1080 _public prototype_ `virtual void SetData(const uint8* InData, uint32 InDataSize, EDatasmithTextureFormat InFormat) override;`
- L1081 _public prototype_ `virtual const uint8* GetData(uint32& OutDataSize, EDatasmithTextureFormat& OutFormat) const override;`
- L1083 _public function_ `virtual FMD5Hash GetFileHash() const override`
- L1084 _public function_ `virtual void SetFileHash(FMD5Hash Hash) override`
- L1086 _public prototype_ `virtual EDatasmithTextureMode GetTextureMode() const override;`
- L1087 _public prototype_ `virtual void SetTextureMode(EDatasmithTextureMode InMode) override;`
- L1089 _public prototype_ `virtual EDatasmithTextureFilter GetTextureFilter() const override;`
- L1090 _public prototype_ `virtual void SetTextureFilter(EDatasmithTextureFilter InFilter) override;`
- L1092 _public prototype_ `virtual EDatasmithTextureAddress GetTextureAddressX() const override;`
- L1093 _public prototype_ `virtual void SetTextureAddressX(EDatasmithTextureAddress InMode) override;`
- L1095 _public prototype_ `virtual EDatasmithTextureAddress GetTextureAddressY() const override;`
- L1096 _public prototype_ `virtual void SetTextureAddressY(EDatasmithTextureAddress InMode) override;`
- L1098 _public prototype_ `virtual bool GetAllowResize() const override;`
- L1099 _public prototype_ `virtual void SetAllowResize(bool bInAllowResize) override;`
- L1101 _public prototype_ `virtual float GetRGBCurve() const override;`
- L1102 _public prototype_ `virtual void SetRGBCurve(float InRGBCurve) override;`
- L1104 _public prototype_ `virtual EDatasmithColorSpace GetSRGB() const override;`
- L1105 _public prototype_ `virtual void SetSRGB(EDatasmithColorSpace Option) override;`
- L1108 _private member_ `TReflected<FString> File;`
- L1109 _private member_ `TReflected<FMD5Hash> FileHash;`
- L1110 _private member_ `TReflected<float> RGBCurve;`
- L1111 _private member_ `TReflected<EDatasmithColorSpace, uint8> ColorSpace;`
- L1112 _private member_ `TReflected<EDatasmithTextureMode, uint8> TextureMode;`
- L1113 _private member_ `TReflected<EDatasmithTextureFilter, uint8> TextureFilter;`
- L1114 _private member_ `TReflected<EDatasmithTextureAddress, uint8> TextureAddressX;`
- L1115 _private member_ `TReflected<EDatasmithTextureAddress, uint8> TextureAddressY;`
- L1116 _private member_ `TReflected<bool> bAllowResize;`
- L1119 _private member_ `const uint8* Data;` — #ue_directlink_reflect buffer: should not be separated in 2 properties.
- L1120 _private member_ `uint32 DataSize;`
- L1122 _private member_ `TReflected<EDatasmithTextureFormat, uint8> TextureFormat;`

#### class `FDatasmithShaderElementImpl`  
`class FDatasmithShaderElementImpl : public FDatasmithElementImpl< IDatasmithShaderElement >`  
_L1125-1361_
- inherits: `FDatasmithElementImpl<IDatasmithShaderElement>`
- L1128 _public prototype_ `explicit FDatasmithShaderElementImpl(const TCHAR* InName);`
- L1130 _public function_ `virtual double GetIOR() const override`
- L1131 _public function_ `virtual void SetIOR(double InValue) override`
- L1133 _public function_ `virtual double GetIORk() const override`
- L1134 _public function_ `virtual void SetIORk(double InValue) override`
- L1136 _public function_ `virtual double GetIORRefra() const override`
- L1137 _public function_ `virtual void SetIORRefra(double Value) override`
- L1139 _public function_ `virtual double GetBumpAmount() const override`
- L1140 _public function_ `virtual void SetBumpAmount(double InValue) override`
- L1142 _public function_ `virtual bool GetTwoSided() const override`
- L1143 _public function_ `virtual void SetTwoSided(bool InValue) override`
- L1145 _public function_ `virtual FLinearColor GetDiffuseColor() const override`
- L1146 _public function_ `virtual void SetDiffuseColor(FLinearColor InValue) override`
- L1148 _public function_ `virtual const TCHAR* GetDiffuseTexture() const override`
- L1149 _public function_ `virtual void SetDiffuseTexture(const TCHAR* InValue) override`
- L1151 _public function_ `virtual FDatasmithTextureSampler GetDiffTextureSampler() const override`
- L1152 _public function_ `virtual void SetDiffTextureSampler(FDatasmithTextureSampler InValue) override`
- L1154 _public function_ `virtual TSharedPtr<IDatasmithCompositeTexture>& GetDiffuseComp() override`
- L1155 _public function_ `virtual const TSharedPtr<IDatasmithCompositeTexture>& GetDiffuseComp() const override`
- L1156 _public function_ `virtual void SetDiffuseComp(const TSharedPtr<IDatasmithCompositeTexture>& InValue) override`
- L1158 _public function_ `virtual FLinearColor GetReflectanceColor() const override`
- L1159 _public function_ `virtual void SetReflectanceColor(FLinearColor InValue) override`
- L1161 _public function_ `virtual const TCHAR* GetReflectanceTexture() const override`
- L1162 _public function_ `virtual void SetReflectanceTexture(const TCHAR* InValue) override`
- L1164 _public function_ `virtual FDatasmithTextureSampler GetRefleTextureSampler() const override`
- L1165 _public function_ `virtual void SetRefleTextureSampler(FDatasmithTextureSampler InValue) override`
- L1167 _public function_ `virtual TSharedPtr<IDatasmithCompositeTexture>& GetRefleComp() override`
- L1168 _public function_ `virtual const TSharedPtr<IDatasmithCompositeTexture>& GetRefleComp() const override`
- L1169 _public function_ `virtual void SetRefleComp(const TSharedPtr<IDatasmithCompositeTexture>& InValue) override`
- L1171 _public function_ `virtual double GetRoughness() const override`
- L1172 _public function_ `virtual void SetRoughness(double InValue) override`
- L1174 _public function_ `virtual const TCHAR* GetRoughnessTexture() const override`
- L1175 _public function_ `virtual void SetRoughnessTexture(const TCHAR* InValue) override`
- L1177 _public function_ `virtual TSharedPtr<IDatasmithCompositeTexture>& GetRoughnessComp() override`
- L1178 _public function_ `virtual const TSharedPtr<IDatasmithCompositeTexture>& GetRoughnessComp() const override`
- L1179 _public function_ `virtual void SetRoughnessComp(const TSharedPtr<IDatasmithCompositeTexture>& InValue) override`
- L1181 _public function_ `virtual FDatasmithTextureSampler GetRoughTextureSampler() const override`
- L1182 _public function_ `virtual void SetRoughTextureSampler(FDatasmithTextureSampler InValue) override`
- L1184 _public function_ `virtual const TCHAR* GetNormalTexture() const override`
- L1185 _public function_ `virtual void SetNormalTexture(const TCHAR* InValue) override`
- L1187 _public function_ `virtual FDatasmithTextureSampler GetNormalTextureSampler() const override`
- L1188 _public function_ `virtual void SetNormalTextureSampler(FDatasmithTextureSampler InValue) override`
- L1190 _public function_ `virtual TSharedPtr<IDatasmithCompositeTexture>& GetNormalComp() override`
- L1191 _public function_ `virtual const TSharedPtr<IDatasmithCompositeTexture>& GetNormalComp() const override`
- L1192 _public function_ `virtual void SetNormalComp(const TSharedPtr<IDatasmithCompositeTexture>& InValue) override`
- L1194 _public function_ `virtual const TCHAR* GetBumpTexture() const override`
- L1195 _public function_ `virtual void SetBumpTexture(const TCHAR* Value) override`
- L1197 _public function_ `virtual FDatasmithTextureSampler GetBumpTextureSampler() const override`
- L1198 _public function_ `virtual void SetBumpTextureSampler(FDatasmithTextureSampler InValue) override`
- L1200 _public function_ `virtual TSharedPtr<IDatasmithCompositeTexture>& GetBumpComp() override`
- L1201 _public function_ `virtual const TSharedPtr<IDatasmithCompositeTexture>& GetBumpComp() const override`
- L1202 _public function_ `virtual void SetBumpComp(const TSharedPtr<IDatasmithCompositeTexture>& InValue) override`
- L1204 _public function_ `virtual FLinearColor GetTransparencyColor() const override`
- L1205 _public function_ `virtual void SetTransparencyColor(FLinearColor InValue) override`
- L1207 _public function_ `virtual const TCHAR* GetTransparencyTexture() const override`
- L1208 _public function_ `virtual void SetTransparencyTexture(const TCHAR* InValue) override`
- L1210 _public function_ `virtual FDatasmithTextureSampler GetTransTextureSampler() const override`
- L1211 _public function_ `virtual void SetTransTextureSampler(FDatasmithTextureSampler InValue) override`
- L1213 _public function_ `virtual TSharedPtr<IDatasmithCompositeTexture>& GetTransComp() override`
- L1214 _public function_ `virtual const TSharedPtr<IDatasmithCompositeTexture>& GetTransComp() const override`
- L1215 _public function_ `virtual void SetTransComp(const TSharedPtr<IDatasmithCompositeTexture>& InValue) override`
- L1217 _public function_ `virtual const TCHAR* GetMaskTexture() const override`
- L1218 _public function_ `virtual void SetMaskTexture(const TCHAR* InValue) override`
- L1220 _public function_ `virtual FDatasmithTextureSampler GetMaskTextureSampler() const override`
- L1221 _public function_ `virtual void SetMaskTextureSampler(FDatasmithTextureSampler InValue) override`
- L1223 _public function_ `virtual TSharedPtr<IDatasmithCompositeTexture>& GetMaskComp() override`
- L1224 _public function_ `virtual const TSharedPtr<IDatasmithCompositeTexture>& GetMaskComp() const override`
- L1225 _public function_ `virtual void SetMaskComp(const TSharedPtr<IDatasmithCompositeTexture>& InValue) override`
- L1227 _public function_ `virtual double GetMetal() const override`
- L1228 _public function_ `virtual void SetMetal(double InValue) override`
- L1230 _public function_ `virtual const TCHAR* GetMetalTexture() const override`
- L1231 _public function_ `virtual void SetMetalTexture(const TCHAR* InValue) override`
- L1233 _public function_ `virtual FDatasmithTextureSampler GetMetalTextureSampler() const override`
- L1234 _public function_ `virtual void SetMetalTextureSampler(FDatasmithTextureSampler InValue) override`
- L1236 _public function_ `virtual TSharedPtr<IDatasmithCompositeTexture>& GetMetalComp() override`
- L1237 _public function_ `virtual const TSharedPtr<IDatasmithCompositeTexture>& GetMetalComp() const override`
- L1238 _public function_ `virtual void SetMetalComp(const TSharedPtr<IDatasmithCompositeTexture>& Value) override`
- L1240 _public function_ `virtual const TCHAR* GetEmitTexture() const override`
- L1241 _public function_ `virtual void SetEmitTexture(const TCHAR* InValue) override`
- L1243 _public function_ `virtual FDatasmithTextureSampler GetEmitTextureSampler() const override`
- L1244 _public function_ `virtual void SetEmitTextureSampler(FDatasmithTextureSampler InValue) override`
- L1246 _public function_ `virtual FLinearColor GetEmitColor() const override`
- L1247 _public function_ `virtual void SetEmitColor(FLinearColor InValue) override`
- L1249 _public function_ `virtual double GetEmitTemperature() const override`
- L1250 _public function_ `virtual void SetEmitTemperature(double InValue) override`
- L1252 _public function_ `virtual double GetEmitPower() const override`
- L1253 _public function_ `virtual void SetEmitPower(double InValue) override`
- L1255 _public function_ `virtual TSharedPtr<IDatasmithCompositeTexture>& GetEmitComp() override`
- L1256 _public function_ `virtual const TSharedPtr<IDatasmithCompositeTexture>& GetEmitComp() const override`
- L1257 _public function_ `virtual void SetEmitComp(const TSharedPtr<IDatasmithCompositeTexture>& InValue) override`
- L1259 _public function_ `virtual bool GetLightOnly() const override`
- L1260 _public function_ `virtual void SetLightOnly(bool InValue) override`
- L1262 _public function_ `virtual FLinearColor GetWeightColor() const override`
- L1263 _public function_ `virtual void SetWeightColor(FLinearColor InValue) override`
- L1265 _public function_ `virtual const TCHAR* GetWeightTexture() const override`
- L1266 _public function_ `virtual void SetWeightTexture(const TCHAR* InValue) override`
- L1268 _public function_ `virtual FDatasmithTextureSampler GetWeightTextureSampler() const override`
- L1269 _public function_ `virtual void SetWeightTextureSampler(FDatasmithTextureSampler InValue) override`
- L1271 _public function_ `virtual TSharedPtr<IDatasmithCompositeTexture>& GetWeightComp() override`
- L1272 _public function_ `virtual const TSharedPtr<IDatasmithCompositeTexture>& GetWeightComp() const override`
- L1273 _public function_ `virtual void SetWeightComp(const TSharedPtr<IDatasmithCompositeTexture>& InValue) override`
- L1275 _public function_ `virtual double GetWeightValue() const override`
- L1276 _public function_ `virtual void SetWeightValue(double InValue) override`
- L1278 _public function_ `virtual EDatasmithBlendMode GetBlendMode() const override`
- L1279 _public function_ `virtual void SetBlendMode(EDatasmithBlendMode InValue) override`
- L1281 _public function_ `virtual bool GetIsStackedLayer() const override`
- L1282 _public function_ `virtual void SetIsStackedLayer(bool InValue) override`
- L1284 _public function_ `virtual const EDatasmithShaderUsage GetShaderUsage() const override`
- L1285 _public function_ `virtual void SetShaderUsage(EDatasmithShaderUsage InShaderUsage) override`
- L1287 _public function_ `virtual const bool GetUseEmissiveForDynamicAreaLighting() const override`
- L1288 _public function_ `virtual void SetUseEmissiveForDynamicAreaLighting(bool InUseEmissiveForDynamicAreaLighting) override`
- L1291 _private member_ `double IOR;`
- L1292 _private member_ `double IORk;`
- L1293 _private member_ `double IORRefra;`
- L1295 _private member_ `double BumpAmount;`
- L1296 _private member_ `bool bTwoSided;`
- L1298 _private member_ `FLinearColor DiffuseColor;`
- L1299 _private member_ `FString DiffuseTexture;`
- L1300 _private member_ `FDatasmithTextureSampler DiffSampler;`
- L1301 _private member_ `TSharedPtr<IDatasmithCompositeTexture> DiffuseComp;`
- L1303 _private member_ `FLinearColor ReflectanceColor;`
- L1304 _private member_ `FString ReflectanceTexture;`
- L1305 _private member_ `FDatasmithTextureSampler RefleSampler;`
- L1306 _private member_ `TSharedPtr<IDatasmithCompositeTexture> RefleComp;`
- L1308 _private member_ `double Roughness;`
- L1309 _private member_ `FString RoughnessTexture;`
- L1310 _private member_ `FDatasmithTextureSampler RoughSampler;`
- L1311 _private member_ `TSharedPtr<IDatasmithCompositeTexture> RoughnessComp;`
- L1313 _private member_ `FString NormalTexture;`
- L1314 _private member_ `FDatasmithTextureSampler NormalSampler;`
- L1315 _private member_ `TSharedPtr<IDatasmithCompositeTexture> NormalComp;`
- L1317 _private member_ `FString BumpTexture;`
- L1318 _private member_ `FDatasmithTextureSampler BumpSampler;`
- L1319 _private member_ `TSharedPtr<IDatasmithCompositeTexture> BumpComp;`
- L1321 _private member_ `FLinearColor TransparencyColor;`
- L1322 _private member_ `FString TransparencyTexture;`
- L1323 _private member_ `FDatasmithTextureSampler TransSampler;`
- L1324 _private member_ `TSharedPtr<IDatasmithCompositeTexture> TransComp;`
- L1326 _private member_ `FString MaskTexture;`
- L1327 _private member_ `FDatasmithTextureSampler MaskSampler;`
- L1328 _private member_ `TSharedPtr<IDatasmithCompositeTexture> MaskComp;`
- L1330 _private member_ `FString DisplaceTexture;`
- L1331 _private member_ `FDatasmithTextureSampler DisplaceSampler;`
- L1332 _private member_ `double Displace;`
- L1333 _private member_ `double DisplaceSubDivision;`
- L1334 _private member_ `TSharedPtr<IDatasmithCompositeTexture> DisplaceComp;`
- L1336 _private member_ `double Metal;`
- L1337 _private member_ `FString MetalTexture;`
- L1338 _private member_ `FDatasmithTextureSampler MetalSampler;`
- L1339 _private member_ `TSharedPtr<IDatasmithCompositeTexture> MetalComp;`
- L1341 _private member_ `FString EmitTexture;`
- L1342 _private member_ `FDatasmithTextureSampler EmitSampler;`
- L1343 _private member_ `FLinearColor EmitColor;`
- L1344 _private member_ `double EmitTemperature;`
- L1345 _private member_ `double EmitPower;`
- L1346 _private member_ `TSharedPtr<IDatasmithCompositeTexture> EmitComp;`
- L1348 _private member_ `bool bLightOnly;`
- L1350 _private member_ `FLinearColor WeightColor;`
- L1351 _private member_ `FString WeightTexture;`
- L1352 _private member_ `FDatasmithTextureSampler WeightSampler;`
- L1353 _private member_ `TSharedPtr<IDatasmithCompositeTexture> WeightComp;`
- L1354 _private member_ `double WeightValue;`
- L1356 _private member_ `EDatasmithBlendMode BlendMode;`
- L1357 _private member_ `bool bIsStackedLayer;`
- L1359 _private member_ `EDatasmithShaderUsage ShaderUsage;`
- L1360 _private member_ `bool bUseEmissiveForDynamicAreaLighting;`

#### class `FDatasmithBaseMaterialElementImpl`  
`template< typename InterfaceType > class FDatasmithBaseMaterialElementImpl : public FDatasmithElementImpl< InterfaceType >`  
_L1364-1368_
- inherits: `FDatasmithElementImpl<InterfaceType>`
- L1367 _public prototype_ `explicit FDatasmithBaseMaterialElementImpl(const TCHAR* InName, EDatasmithElementType ChildType);`
- L1371 _function_ `template< typename T > inline FDatasmithBaseMaterialElementImpl<T>::FDatasmithBaseMaterialElementImpl(const TCHAR* InName, EDatasmithElementType ChildType) : FDatasmithElementImpl<T>(InName, EDatasmithElementType::BaseMaterial | ChildType)`

#### class `FDatasmithMaterialElementImpl`  
`class FDatasmithMaterialElementImpl : public FDatasmithBaseMaterialElementImpl< IDatasmithMaterialElement >`  
_L1376-1392_
- inherits: `FDatasmithBaseMaterialElementImpl<IDatasmithMaterialElement>`
- L1379 _public prototype_ `explicit FDatasmithMaterialElementImpl(const TCHAR* InName);`
- L1381 _public prototype_ `virtual bool IsSingleShaderMaterial() const override;`
- L1382 _public prototype_ `virtual bool IsClearCoatMaterial() const override;`
- L1384 _public prototype_ `virtual void AddShader(const TSharedPtr< IDatasmithShaderElement >& InShader) override;`
- L1386 _public prototype_ `virtual int32 GetShadersCount() const override;`
- L1387 _public prototype_ `virtual TSharedPtr< IDatasmithShaderElement >& GetShader(int32 InIndex) override;`
- L1388 _public prototype_ `virtual const TSharedPtr< IDatasmithShaderElement >& GetShader(int32 InIndex) const override;`
- L1391 _private member_ `TArray< TSharedPtr< IDatasmithShaderElement > > Shaders;`

#### class `FDatasmithMaterialIntanceElementImpl`  
`class FDatasmithMaterialIntanceElementImpl : public FDatasmithBaseMaterialElementImpl< IDatasmithMaterialInstanceElement >`  
_L1394-1422_
- inherits: `FDatasmithBaseMaterialElementImpl<IDatasmithMaterialInstanceElement>`
- L1397 _public prototype_ `FDatasmithMaterialIntanceElementImpl(const TCHAR* InName);`
- L1399 _public function_ `virtual EDatasmithReferenceMaterialType GetMaterialType() const override`
- L1400 _public function_ `virtual void SetMaterialType( EDatasmithReferenceMaterialType InType ) override`
- L1402 _public function_ `virtual EDatasmithReferenceMaterialQuality GetQuality() const override`
- L1403 _public function_ `virtual void SetQuality( EDatasmithReferenceMaterialQuality InQuality ) override`
- L1405 _public function_ `virtual const TCHAR* GetCustomMaterialPathName() const override`
- L1406 _public function_ `virtual void SetCustomMaterialPathName( const TCHAR* InPathName ) override`
- L1408 _public function_ `virtual int32 GetPropertiesCount() const override`
- L1409 _public prototype_ `virtual const TSharedPtr< IDatasmithKeyValueProperty >& GetProperty( int32 InIndex ) const override;`
- L1410 _public prototype_ `virtual const TSharedPtr< IDatasmithKeyValueProperty >& GetPropertyByName( const TCHAR* InName ) const override;`
- L1411 _public prototype_ `virtual void AddProperty( const TSharedPtr< IDatasmithKeyValueProperty >& InProperty ) override;`
- L1413 _public prototype_ `virtual FMD5Hash CalculateElementHash(bool bForce) override;`
- L1416 _private member_ `TDatasmithReferenceArrayProxy<IDatasmithKeyValueProperty> Properties;`
- L1418 _private member_ `TReflected<EDatasmithReferenceMaterialType, uint8> MaterialType;`
- L1419 _private member_ `TReflected<EDatasmithReferenceMaterialQuality, uint8> Quality;`
- L1421 _private member_ `TReflected<FString> CustomMaterialPathName;`

#### class `FDatasmithDecalMaterialElementImpl`  
`class FDatasmithDecalMaterialElementImpl : public FDatasmithBaseMaterialElementImpl< IDatasmithDecalMaterialElement >`  
_L1424-1443_
- inherits: `FDatasmithBaseMaterialElementImpl<IDatasmithDecalMaterialElement>`
- L1427 _public function_ `FDatasmithDecalMaterialElementImpl(const TCHAR* InName) : FDatasmithBaseMaterialElementImpl(InName, EDatasmithElementType::DecalMaterial)`
- L1434 _public function_ `virtual const TCHAR* GetDiffuseTexturePathName() const override`
- L1435 _public function_ `virtual void SetDiffuseTexturePathName( const TCHAR* InPathName ) override`
- L1437 _public function_ `virtual const TCHAR* GetNormalTexturePathName() const override`
- L1438 _public function_ `virtual void SetNormalTexturePathName( const TCHAR* InPathName ) override`
- L1441 _private member_ `TReflected<FString> DiffuseTexturePathName;`
- L1442 _private member_ `TReflected<FString> NormalTexturePathName;`

#### class `FDatasmithCompositeSurface`  
`class FDatasmithCompositeSurface`  
_L1445-1468_
- L1448 _public prototype_ `FDatasmithCompositeSurface(const TSharedPtr<IDatasmithCompositeTexture>& SubComp);`
- L1449 _public prototype_ `FDatasmithCompositeSurface(const TCHAR* InTexture, FDatasmithTextureSampler InTexUV);`
- L1450 _public prototype_ `FDatasmithCompositeSurface(const FLinearColor& InColor);`
- L1452 _public prototype_ `bool GetUseTexture() const;`
- L1453 _public prototype_ `bool GetUseColor() const;`
- L1454 _public prototype_ `bool GetUseComposite() const;`
- L1456 _public prototype_ `FDatasmithTextureSampler& GetParamTextureSampler();`
- L1457 _public prototype_ `const TCHAR* GetParamTexture() const;`
- L1458 _public prototype_ `void SetParamTexture(const TCHAR* InTexture);`
- L1459 _public prototype_ `const FLinearColor& GetParamColor() const;`
- L1460 _public prototype_ `TSharedPtr<IDatasmithCompositeTexture>& GetParamSubComposite();`
- L1463 _private member_ `FDatasmithTextureSampler ParamSampler;`
- L1464 _private member_ `FString ParamTextures;`
- L1465 _private member_ `FLinearColor ParamColor;`
- L1466 _private member_ `TSharedPtr<IDatasmithCompositeTexture> ParamSubComposite;`
- L1467 _private member_ `bool bParamUseTexture;`

#### class `FDatasmithCompositeTextureImpl`  
`class FDatasmithCompositeTextureImpl : public IDatasmithCompositeTexture`  
_L1470-1545_
- inherits: `IDatasmithCompositeTexture`
- L1473 _public prototype_ `FDatasmithCompositeTextureImpl();`
- L1475 _public prototype_ `virtual bool IsValid() const override;`
- L1477 _public function_ `virtual EDatasmithCompMode GetMode() const override`
- L1478 _public function_ `virtual void SetMode(EDatasmithCompMode InMode) override`
- L1479 _public function_ `virtual int32 GetParamSurfacesCount() const override`
- L1481 _public prototype_ `virtual bool GetUseTexture(int32 InIndex) override;`
- L1483 _public prototype_ `virtual const TCHAR* GetParamTexture(int32 InIndex) override;`
- L1484 _public prototype_ `virtual void SetParamTexture(int32 InIndex, const TCHAR* InTexture) override;`
- L1486 _public prototype_ `virtual FDatasmithTextureSampler& GetParamTextureSampler(int32 InIndex) override;`
- L1488 _public prototype_ `virtual bool GetUseColor(int32 InIndex) override;`
- L1489 _public prototype_ `virtual const FLinearColor& GetParamColor(int32 InIndex) override;`
- L1491 _public prototype_ `virtual bool GetUseComposite(int32 InIndex) override;`
- L1493 _public function_ `virtual int32 GetParamVal1Count() const override`
- L1494 _public prototype_ `virtual ParamVal GetParamVal1(int32 InIndex) const override;`
- L1495 _public function_ `virtual void AddParamVal1(ParamVal InParamVal) override`
- L1497 _public function_ `virtual int32 GetParamVal2Count() const override`
- L1498 _public prototype_ `virtual ParamVal GetParamVal2(int32 InIndex) const override;`
- L1499 _public function_ `virtual void AddParamVal2(ParamVal InParamVal) override`
- L1501 _public function_ `virtual int32 GetParamMaskSurfacesCount() const override`
- L1502 _public prototype_ `virtual const TCHAR* GetParamMask(int32 InIndex) override;`
- L1503 _public prototype_ `virtual const FLinearColor& GetParamMaskColor(int32 i) const override;`
- L1504 _public prototype_ `virtual bool GetMaskUseComposite(int32 InIndex) const override;`
- L1505 _public function_ `virtual void AddMaskSurface(const TCHAR* InMask, const FDatasmithTextureSampler InMaskSampler) override`
- L1506 _public function_ `virtual void AddMaskSurface(const FLinearColor& InColor) override`
- L1508 _public prototype_ `virtual FDatasmithTextureSampler GetParamMaskTextureSampler(int32 InIndex) override;`
- L1510 _public prototype_ `virtual TSharedPtr<IDatasmithCompositeTexture>& GetParamSubComposite(int32 InIndex) override;`
- L1511 _public function_ `virtual void AddSurface(const TSharedPtr<IDatasmithCompositeTexture>& SubComp) override`
- L1513 _public prototype_ `virtual TSharedPtr<IDatasmithCompositeTexture>& GetParamMaskSubComposite(int32 InIndex) override;`
- L1514 _public function_ `virtual void AddMaskSurface(const TSharedPtr<IDatasmithCompositeTexture>& InMaskSubComp) override`
- L1516 _public function_ `virtual const TCHAR* GetBaseTextureName() const override`
- L1517 _public function_ `virtual const TCHAR* GetBaseColName() const override`
- L1518 _public function_ `virtual const TCHAR* GetBaseValName() const override`
- L1519 _public function_ `virtual const TCHAR* GetBaseCompName() const override`
- L1521 _public prototype_ `virtual void SetBaseNames(const TCHAR* InTextureName, const TCHAR* InColorName, const TCHAR* InValueName, const TCHAR* InCompName) override;`
- L1523 _public function_ `virtual void AddSurface(const TCHAR* InTexture, FDatasmithTextureSampler InTexUV) override`
- L1524 _public function_ `virtual void AddSurface(const FLinearColor& InColor) override`
- L1525 _public function_ `virtual void ClearSurface() override`
- L1531 _private member_ `TArray<FDatasmithCompositeSurface> ParamSurfaces;`
- L1532 _private member_ `TArray<FDatasmithCompositeSurface> ParamMaskSurfaces;`
- L1534 _private typedef_ `typedef TPair<float, FString> ParamValImpl;`
- L1535 _private member_ `TArray<ParamValImpl> ParamVal1;`
- L1536 _private member_ `TArray<ParamValImpl> ParamVal2;`
- L1538 _private member_ `EDatasmithCompMode CompMode;`
- L1541 _private member_ `FString BaseTexName;` — used for single material
- L1542 _private member_ `FString BaseColName;`
- L1543 _private member_ `FString BaseValName;`
- L1544 _private member_ `FString BaseCompName;`

#### class `FDatasmithMetaDataElementImpl`  
`class FDatasmithMetaDataElementImpl : public FDatasmithElementImpl< IDatasmithMetaDataElement >`  
_L1547-1570_
- inherits: `FDatasmithElementImpl<IDatasmithMetaDataElement>`
- L1550 _public prototype_ `explicit FDatasmithMetaDataElementImpl(const TCHAR* InName);`
- L1552 _public function_ `virtual const TSharedPtr< IDatasmithElement >& GetAssociatedElement() const override`
- L1553 _public function_ `virtual void SetAssociatedElement(const TSharedPtr< IDatasmithElement >& Element)`
- L1555 _public function_ `virtual int32 GetPropertiesCount() const override`
- L1557 _public prototype_ `virtual const TSharedPtr< IDatasmithKeyValueProperty >& GetProperty(int32 i) const override;`
- L1559 _public prototype_ `virtual const TSharedPtr< IDatasmithKeyValueProperty >& GetPropertyByName( const TCHAR* InName ) const override;`
- L1561 _public prototype_ `virtual void AddProperty( const TSharedPtr< IDatasmithKeyValueProperty >& Property ) override;`
- L1563 _public prototype_ `virtual void RemoveProperty( const TSharedPtr<IDatasmithKeyValueProperty>& Property ) override;`
- L1565 _public prototype_ `virtual void ResetProperties() override;`
- L1568 _private member_ `TDatasmithReferenceProxy<IDatasmithElement> AssociatedElement;`
- L1569 _private member_ `TDatasmithReferenceArrayProxy<IDatasmithKeyValueProperty> Properties;`

#### class `FDatasmithDecalActorElementImpl`  
`class FDatasmithDecalActorElementImpl : public FDatasmithCustomActorElementImpl< IDatasmithDecalActorElement >`  
_L1572-1590_
- inherits: `FDatasmithCustomActorElementImpl<IDatasmithDecalActorElement>`
- L1575 _public prototype_ `explicit FDatasmithDecalActorElementImpl( const TCHAR* InName );`
- L1577 _public prototype_ `virtual FVector GetDimensions() const;`
- L1578 _public prototype_ `virtual void SetDimensions( const FVector& InDimensions );`
- L1580 _public prototype_ `virtual const TCHAR* GetDecalMaterialPathName() const;`
- L1581 _public prototype_ `virtual void SetDecalMaterialPathName( const TCHAR* InMaterialPathName );`
- L1583 _public prototype_ `virtual int32 GetSortOrder() const;`
- L1584 _public prototype_ `virtual void SetSortOrder( int32 InSortOrder );`
- L1587 _private member_ `int32 SortOrderPropertyIndex;`
- L1588 _private member_ `int32 DimensionsPropertyIndex;`
- L1589 _private member_ `int32 MaterialPropertyIndex;`

#### class `FDatasmithSceneImpl`  
`class FDatasmithSceneImpl : public FDatasmithElementImpl< IDatasmithScene > PRAGMA_ENABLE_DEPRECATION_WARNINGS`  
_L1593-1750_
- reflection: `UE_DEPRECATED(5.5, "The experimental Cloth importer is no longer supported.")`
- inherits: `FDatasmithElementImpl<IDatasmithScene>PRAGMA_ENABLE_DEPRECATION_WARNINGS`
- L1597 _public prototype_ `explicit FDatasmithSceneImpl(const TCHAR* InName);`
- L1599 _public prototype_ `virtual void Reset() override;`
- L1601 _public prototype_ `virtual const TCHAR* GetHost() const override;`
- L1602 _public prototype_ `virtual void SetHost(const TCHAR* InHostname) override;`
- L1604 _public function_ `virtual const TCHAR* GetExporterVersion() const override`
- L1605 _public function_ `virtual void SetExporterVersion(const TCHAR* InVersion) override`
- L1607 _public function_ `virtual const TCHAR* GetExporterSDKVersion() const override`
- L1608 _public function_ `virtual void SetExporterSDKVersion(const TCHAR* InVersion) override`
- L1610 _public function_ `virtual const TCHAR* GetVendor() const override`
- L1611 _public function_ `virtual void SetVendor(const TCHAR* InVendor) override`
- L1613 _public function_ `virtual const TCHAR* GetProductName() const override`
- L1614 _public function_ `virtual void SetProductName(const TCHAR* InProductName) override`
- L1616 _public function_ `virtual const TCHAR* GetProductVersion() const override`
- L1617 _public function_ `virtual void SetProductVersion(const TCHAR* InProductVersion) override`
- L1619 _public function_ `virtual const TCHAR* GetResourcePath() const override`
- L1620 _public function_ `virtual void SetResourcePath(const TCHAR* InResourcePath) override`
- L1622 _public function_ `virtual const TCHAR* GetUserID() const override`
- L1623 _public function_ `virtual void SetUserID(const TCHAR* InUserID) override`
- L1625 _public function_ `virtual const TCHAR* GetUserOS() const override`
- L1626 _public function_ `virtual void SetUserOS(const TCHAR* InUserOS) override`
- L1628 _public function_ `virtual FVector GetGeolocation() const override`
- L1629 _public function_ `virtual void SetGeolocationLatitude(double InLatitude) override`
- L1630 _public function_ `virtual void SetGeolocationLongitude(double InLongitude) override`
- L1631 _public function_ `virtual void SetGeolocationElevation(double InElevation) override`
- L1633 _public function_ `virtual int32 GetExportDuration() const override`
- L1634 _public function_ `virtual void SetExportDuration(int32 InExportDuration) override`
- L1636 _public function_ `virtual void AddMesh(const TSharedPtr< IDatasmithMeshElement >& InMesh) override`
- L1637 _public function_ `virtual int32 GetMeshesCount() const override`
- L1638 _public prototype_ `virtual TSharedPtr< IDatasmithMeshElement > GetMesh(int32 InIndex) override;`
- L1639 _public prototype_ `virtual const TSharedPtr< IDatasmithMeshElement >& GetMesh(int32 InIndex) const override;`
- L1640 _public function_ `virtual void RemoveMesh(const TSharedPtr< IDatasmithMeshElement >& InMesh) override`
- L1641 _public prototype_ `virtual void RemoveMeshAt(int32 InIndex) override;`
- L1642 _public function_ `virtual void EmptyMeshes() override`
- L1646 _public prototype_ `virtual void AddCloth(const TSharedPtr< IDatasmithClothElement >& InElement) override;` — `UE_DEPRECATED(5.5, "The experimental Cloth importer is no longer supported.")`
- L1648 _public prototype_ `virtual int32 GetClothesCount() const override;` — `UE_DEPRECATED(5.5, "The experimental Cloth importer is no longer supported.")`
- L1650 _public prototype_ `virtual TSharedPtr< IDatasmithClothElement > GetCloth(int32 InIndex) override;` — `UE_DEPRECATED(5.5, "The experimental Cloth importer is no longer supported.")`
- L1652 _public prototype_ `virtual const TSharedPtr< IDatasmithClothElement >& GetCloth(int32 InIndex) const override;` — `UE_DEPRECATED(5.5, "The experimental Cloth importer is no longer supported.")`
- L1654 _public prototype_ `virtual void RemoveCloth(const TSharedPtr< IDatasmithClothElement >& InElement) override;` — `UE_DEPRECATED(5.5, "The experimental Cloth importer is no longer supported.")`
- L1656 _public prototype_ `virtual void RemoveClothAt(int32 InIndex) override;` — `UE_DEPRECATED(5.5, "The experimental Cloth importer is no longer supported.")`
- L1658 _public prototype_ `virtual void EmptyClothes() override;` — `UE_DEPRECATED(5.5, "The experimental Cloth importer is no longer supported.")`
- L1661 _public function_ `virtual void AddActor(const TSharedPtr< IDatasmithActorElement >& InActor) override`
- L1662 _public function_ `virtual int32 GetActorsCount() const override`
- L1663 _public prototype_ `virtual TSharedPtr< IDatasmithActorElement > GetActor(int32 InIndex) override;`
- L1664 _public prototype_ `virtual const TSharedPtr< IDatasmithActorElement >& GetActor(int32 InIndex) const override;`
- L1665 _public prototype_ `virtual void RemoveActor(const TSharedPtr< IDatasmithActorElement >& InActor, EDatasmithActorRemovalRule RemoveRule) override;`
- L1666 _public prototype_ `virtual void RemoveActorAt(int32 InIndex, EDatasmithActorRemovalRule RemoveRule) override;`
- L1668 _public function_ `virtual void AddMaterial(const TSharedPtr< IDatasmithBaseMaterialElement >& InMaterial) override`
- L1669 _public function_ `virtual int32 GetMaterialsCount() const override`
- L1670 _public prototype_ `virtual TSharedPtr< IDatasmithBaseMaterialElement > GetMaterial(int32 InIndex) override;`
- L1671 _public prototype_ `virtual const TSharedPtr< IDatasmithBaseMaterialElement >& GetMaterial(int32 InIndex) const override;`
- L1672 _public function_ `virtual void RemoveMaterial(const TSharedPtr< IDatasmithBaseMaterialElement >& InMaterial) override`
- L1673 _public prototype_ `virtual void RemoveMaterialAt(int32 InIndex) override;`
- L1674 _public function_ `virtual void EmptyMaterials() override`
- L1676 _public function_ `virtual void AddTexture(const TSharedPtr< IDatasmithTextureElement >& InTexture) override`
- L1677 _public function_ `virtual int32 GetTexturesCount() const override`
- L1678 _public prototype_ `virtual TSharedPtr< IDatasmithTextureElement > GetTexture(int32 InIndex) override;`
- L1679 _public prototype_ `virtual const TSharedPtr< IDatasmithTextureElement >& GetTexture(int32 InIndex) const override;`
- L1680 _public function_ `virtual void RemoveTexture(const TSharedPtr< IDatasmithTextureElement >& InTexture) override`
- L1681 _public prototype_ `virtual void RemoveTextureAt(int32 InIndex) override;`
- L1682 _public function_ `virtual void EmptyTextures() override`
- L1684 _public function_ `virtual void SetPostProcess(const TSharedPtr< IDatasmithPostProcessElement >& InPostProcess) override`
- L1685 _public function_ `virtual TSharedPtr< IDatasmithPostProcessElement > GetPostProcess() override`
- L1686 _public function_ `virtual const TSharedPtr< IDatasmithPostProcessElement >& GetPostProcess() const override`
- L1688 _public function_ `virtual void SetUsePhysicalSky(bool bInUsePhysicalSky) override`
- L1689 _public function_ `virtual bool GetUsePhysicalSky() const override`
- L1691 _public function_ `virtual void AddMetaData(const TSharedPtr< IDatasmithMetaDataElement >& InMetaData) override`
- L1692 _public function_ `virtual int32 GetMetaDataCount() const override`
- L1693 _public prototype_ `virtual TSharedPtr< IDatasmithMetaDataElement > GetMetaData(int32 InIndex) override;`
- L1694 _public prototype_ `virtual const TSharedPtr< IDatasmithMetaDataElement >& GetMetaData(int32 InIndex) const override;`
- L1695 _public prototype_ `virtual TSharedPtr< IDatasmithMetaDataElement > GetMetaData(const TSharedPtr<IDatasmithElement>& Element) override;`
- L1696 _public prototype_ `virtual const TSharedPtr< IDatasmithMetaDataElement >& GetMetaData(const TSharedPtr<IDatasmithElement>& Element) const override;`
- L1697 _public prototype_ `virtual void RemoveMetaData( const TSharedPtr<IDatasmithMetaDataElement>& Element ) override;`
- L1698 _public prototype_ `virtual void RemoveMetaDataAt(int32 InIndex) override;`
- L1700 _public function_ `virtual void AddLevelSequence(const TSharedRef< IDatasmithLevelSequenceElement >& InSequence) override`
- L1701 _public function_ `virtual int32 GetLevelSequencesCount() const override`
- L1702 _public prototype_ `virtual TSharedPtr< IDatasmithLevelSequenceElement > GetLevelSequence(int32 InIndex) override;`
- L1703 _public prototype_ `virtual const TSharedPtr< IDatasmithLevelSequenceElement >& GetLevelSequence(int32 InIndex) const override;`
- L1704 _public function_ `virtual void RemoveLevelSequence(const TSharedRef< IDatasmithLevelSequenceElement >& InSequence) override`
- L1705 _public prototype_ `virtual void RemoveLevelSequenceAt(int32 InIndex) override;`
- L1707 _public function_ `virtual void AddLevelVariantSets(const TSharedPtr< IDatasmithLevelVariantSetsElement >& InLevelVariantSets) override`
- L1708 _public function_ `virtual int32 GetLevelVariantSetsCount() const override`
- L1709 _public prototype_ `virtual TSharedPtr< IDatasmithLevelVariantSetsElement > GetLevelVariantSets(int32 InIndex) override;`
- L1710 _public prototype_ `virtual const TSharedPtr< IDatasmithLevelVariantSetsElement >& GetLevelVariantSets(int32 InIndex) const override;`
- L1711 _public function_ `virtual void RemoveLevelVariantSets(const TSharedPtr< IDatasmithLevelVariantSetsElement >& InLevelVariantSets) override`
- L1712 _public prototype_ `virtual void RemoveLevelVariantSetsAt(int32 InIndex) override;`
- L1714 _public prototype_ `virtual void AttachActor(const TSharedPtr< IDatasmithActorElement >& NewParent, const TSharedPtr< IDatasmithActorElement >& Child, EDatasmithActorAttachmentRule AttachmentRule) override;`
- L1715 _public prototype_ `virtual void AttachActorToSceneRoot(const TSharedPtr< IDatasmithActorElement >& Child, EDatasmithActorAttachmentRule AttachmentRule) override;`
- L1719 _private member_ `TDatasmithReferenceArrayProxy<IDatasmithActorElement> Actors;`
- L1720 _private member_ `TDatasmithReferenceArrayProxy<IDatasmithMeshElement> Meshes;`
- L1723 _private member_ `TDatasmithReferenceArrayProxy<IDatasmithClothElement> Clothes;` — `UE_DEPRECATED(5.5, "The experimental Cloth importer is no longer supported.")`
- L1725 _private member_ `TDatasmithReferenceArrayProxy<IDatasmithBaseMaterialElement> Materials;`
- L1726 _private member_ `TDatasmithReferenceArrayProxy<IDatasmithTextureElement> Textures;`
- L1727 _private member_ `TDatasmithReferenceArrayProxy<IDatasmithMetaDataElement> MetaData;`
- L1728 _private member_ `TDatasmithReferenceArrayProxy<IDatasmithLevelSequenceElement> LevelSequences;`
- L1729 _private member_ `TDatasmithReferenceArrayProxy<IDatasmithLevelVariantSetsElement> LevelVariantSets;`
- L1730 _private member_ `TDatasmithReferenceProxy<IDatasmithPostProcessElement> PostProcess;`
- L1732 _private member_ `TReflected<FString> Hostname;`
- L1733 _private member_ `TReflected<FString> ExporterVersion;`
- L1734 _private member_ `TReflected<FString> ExporterSDKVersion;`
- L1735 _private member_ `TReflected<FString> Vendor;`
- L1736 _private member_ `TReflected<FString> ProductName;`
- L1737 _private member_ `TReflected<FString> ProductVersion;`
- L1738 _private member_ `TReflected<FString> UserID;`
- L1739 _private member_ `TReflected<FString> UserOS;`
- L1740 _private member_ `TReflected<FVector> Geolocation;`
- L1741 _private member_ `TReflected<FString> ResourcePath;`
- L1743 _private member_ `TReflected<uint32> ExportDuration;`
- L1745 _private member_ `TReflected<bool> bUseSky;`
- L1748 _private member_ `mutable TMap< TSharedPtr< IDatasmithElement >, TSharedPtr< IDatasmithMetaDataElement> > ElementToMetaDataMap;` — Internal cache for faster metadata access per-element, should be accessed via GetMetaDataCache(), do not use directly.
- L1749 _private prototype_ `TMap< TSharedPtr< IDatasmithElement >, TSharedPtr< IDatasmithMetaDataElement> >& GetElementToMetaDataCache() const;`

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API DATASMITHCORE_API`
- L20 _typedef_ `template<typename T, typename S=T> using TReflected = DirectLink::TStoreKey<T, S>;`
- L102 _prototype_ `ENUM_CLASS_FLAGS(EActorFlags);`
- L104 _macro_ `#define UPDATE_BITFLAGS( Flags, bValue, EnumValue) Flags = bValue ? Flags | EnumValue : Flags & ~EnumValue`
- L239 _member_ `template< typename InterfaceType > TSharedPtr<IDatasmithActorElement> FDatasmithActorElementImpl< InterfaceType >::NullActorPtr;` (scope `FDatasmithActorElementImpl< InterfaceType >`)
- L576 _prototype_ `ENUM_CLASS_FLAGS(LightActorFlags);`
- L953 _function_ `const int32 Index = Properties.View().IndexOfByPredicate([InName](const TSharedPtr<IDatasmithKeyValueProperty>& Property){ return Property.IsValid() && FCString::Stricmp(Property->GetName(), InName) == 0; });` (scope `FDatasmithCustomActorElementImpl::GetPropertyByName`)
- L968 _function_ `const int32 Index = Properties.View().IndexOfByPredicate([InName](const TSharedPtr<IDatasmithKeyValueProperty>& Property){ return Property.IsValid() && FCString::Stricmp(Property->GetName(), InName) == 0; });` (scope `FDatasmithCustomActorElementImpl::AddProperty`)
- L985 _function_ `const int32 Index = Properties.View().IndexOfByPredicate([InKey](const TSharedPtr<IDatasmithKeyValueProperty>& Property){ return Property.IsValid() && FCString::Stricmp(Property->GetName(), InKey) == 0; });` (scope `FDatasmithCustomActorElementImpl::AddPropertyInternal`)

### `Source/Runtime/Datasmith/DatasmithCore/Private/DatasmithSceneGraphSharedState.h` (Private)


#### class `FDatasmithSceneGraphSharedState`  
`class FDatasmithSceneGraphSharedState : public DirectLink::FSceneGraphSharedState`  
_L12-21_
- inherits: `DirectLink::FSceneGraphSharedState`
- L15 _public prototype_ `FDatasmithSceneGraphSharedState() = default;`
- L17 _public function_ `FDatasmithSceneGraphSharedState(const DirectLink::FSceneIdentifier& InSceneId)`

#### class `TDatasmithReferenceProxy`  
`template<typename T> class TDatasmithReferenceProxy : public DirectLink::IReferenceProxy`  
_L25-62_
- inherits: `DirectLink::IReferenceProxy`
- L29 _public function_ `TDatasmithReferenceProxy(const TSharedPtr<T>& Reference = nullptr) : Inner(Reference)`
- L33 _public function_ `virtual int32 Num() const override`
- L35 _public function_ `virtual DirectLink::ISceneGraphNode* GetNode(int32 Index) const override`
- L40 _public function_ `virtual void SetNodes(DirectLink::IReferenceResolutionProvider& ResolutionProvider, const TArray<DirectLink::FSceneGraphId>& NodeIds) override`
- L57 _public function_ `const TSharedPtr<T>& View() const`
- L58 _public function_ `TSharedPtr<T>& Edit()`
- L61 _public member_ `TSharedPtr<T> Inner;`

#### class `TDatasmithReferenceArrayProxy`  
`template<typename T> class TDatasmithReferenceArrayProxy : public DirectLink::IReferenceProxy`  
_L66-109_
- inherits: `DirectLink::IReferenceProxy`
- L68 _private typedef_ `using SizeType = typename TArray<TSharedPtr<T>>::SizeType;`
- L71 _public function_ `virtual int32 Num() const override`
- L76 _public function_ `virtual DirectLink::ISceneGraphNode* GetNode(int32 Index) const override`
- L81 _public function_ `virtual void SetNodes(DirectLink::IReferenceResolutionProvider& ResolutionProvider, const TArray<DirectLink::FSceneGraphId>& NodeIds) override`
- L95 _public function_ `const TSharedPtr<T>& operator[](int32 Index) const` — simpler access to the inner array...
- L96 _public function_ `TSharedPtr<T>& operator[](int32 Index)`
- L97 _public function_ `bool IsValidIndex(SizeType Index) const`
- L98 _public function_ `SizeType Add(const TSharedPtr<T>& Element)`
- L99 _public function_ `SizeType Add(TSharedPtr<T>&& Element)`
- L100 _public function_ `SizeType Remove(const TSharedPtr<T>& Item)`
- L101 _public function_ `void RemoveAt(int32 Index)`
- L102 _public function_ `void Empty()`
- L104 _public function_ `const TArray<TSharedPtr<T>>& View() const`
- L105 _public function_ `TArray<TSharedPtr<T>>& Edit()`
- L108 _private member_ `TArray<TSharedPtr<T>> Inner;`

#### Free symbols / members of external scopes

- L85 _function_ `` (scope `TDatasmithReferenceArrayProxy::SetNodes`)

### `Source/Runtime/Datasmith/DatasmithCore/Private/DatasmithVariantElementsImpl.h` (Private)


#### class `FDatasmithBaseVariantElementImpl`  
`template< typename InterfaceType > class FDatasmithBaseVariantElementImpl : public FDatasmithElementImpl< InterfaceType >`  
_L12-21_
- inherits: `FDatasmithElementImpl<InterfaceType>`
- L17 _public function_ `virtual bool IsSubType( const EDatasmithElementVariantSubType VariantSubType ) const override`

#### class `FDatasmithBasePropertyCaptureElementImpl`  
`template< typename InterfaceType > class FDatasmithBasePropertyCaptureElementImpl : public FDatasmithBaseVariantElementImpl< InterfaceType >`  
_L24-56_
- inherits: `FDatasmithBaseVariantElementImpl<InterfaceType>`
- L27 _public function_ `explicit FDatasmithBasePropertyCaptureElementImpl(EDatasmithElementVariantSubType InSubType = EDatasmithElementVariantSubType::PropertyCapture) : FDatasmithBaseVariantElementImpl< InterfaceType >(nullptr, EDatasmithElementType::Variant, (uint64)InSubType) , Category(EDatasmithPropertyCategory::Undefined)`
- L33 _public function_ `virtual void SetPropertyPath(const FString& Path) override`
- L38 _public function_ `virtual const FString& GetPropertyPath() const override`
- L43 _public function_ `virtual void SetCategory(EDatasmithPropertyCategory InCategory) override`
- L48 _public function_ `virtual EDatasmithPropertyCategory GetCategory() const override`
- L54 _private member_ `FString PropertyPath;`
- L55 _private member_ `EDatasmithPropertyCategory Category;`

#### class `FDatasmithPropertyCaptureElementImpl`  
`class FDatasmithPropertyCaptureElementImpl : public FDatasmithBasePropertyCaptureElementImpl< IDatasmithPropertyCaptureElement >`  
_L58-79_
- inherits: `FDatasmithBasePropertyCaptureElementImpl<IDatasmithPropertyCaptureElement>`
- L61 _public function_ `explicit FDatasmithPropertyCaptureElementImpl() : FDatasmithBasePropertyCaptureElementImpl(EDatasmithElementVariantSubType::PropertyCapture)`
- L66 _public function_ `virtual void SetRecordedData(const uint8* InData, int32 InNumBytes)`
- L72 _public function_ `virtual const TArray<uint8>& GetRecordedData() const`
- L78 _protected member_ `TArray<uint8> Data;`

#### class `FDatasmithObjectPropertyCaptureElementImpl`  
`class FDatasmithObjectPropertyCaptureElementImpl : public FDatasmithBasePropertyCaptureElementImpl< IDatasmithObjectPropertyCaptureElement >`  
_L81-101_
- inherits: `FDatasmithBasePropertyCaptureElementImpl<IDatasmithObjectPropertyCaptureElement>`
- L84 _public function_ `explicit FDatasmithObjectPropertyCaptureElementImpl() : FDatasmithBasePropertyCaptureElementImpl(EDatasmithElementVariantSubType::ObjectPropertyCapture)`
- L89 _public function_ `virtual void SetRecordedObject(TWeakPtr<IDatasmithElement> InObject)`
- L94 _public function_ `virtual TWeakPtr<IDatasmithElement> GetRecordedObject() const`
- L100 _private member_ `TWeakPtr<IDatasmithElement> Object;`

#### class `FDatasmithActorBindingElementImpl`  
`class FDatasmithActorBindingElementImpl : public FDatasmithBaseVariantElementImpl< IDatasmithActorBindingElement >`  
_L103-144_
- inherits: `FDatasmithBaseVariantElementImpl<IDatasmithActorBindingElement>`
- L106 _public function_ `explicit FDatasmithActorBindingElementImpl() : FDatasmithBaseVariantElementImpl(nullptr, EDatasmithElementType::Variant, (uint64)EDatasmithElementVariantSubType::ActorBinding)`
- L111 _public function_ `virtual void SetActor(TSharedPtr<IDatasmithActorElement> InActor) override`
- L116 _public function_ `virtual TSharedPtr<IDatasmithActorElement> GetActor() const override`
- L121 _public function_ `virtual void AddPropertyCapture(const TSharedRef< IDatasmithBasePropertyCaptureElement >& Prop) override`
- L126 _public function_ `virtual int32 GetPropertyCapturesCount() const override`
- L131 _public function_ `virtual TSharedPtr< IDatasmithBasePropertyCaptureElement > GetPropertyCapture(int32 InIndex) override`
- L136 _public function_ `virtual void RemovePropertyCapture(const TSharedRef< IDatasmithBasePropertyCaptureElement >& Prop) override`
- L142 _private member_ `TSharedPtr<IDatasmithActorElement> Actor;`
- L143 _private member_ `TArray< TSharedRef< IDatasmithBasePropertyCaptureElement > > PropertyCaptures;`

#### class `FDatasmithVariantElementImpl`  
`class FDatasmithVariantElementImpl : public FDatasmithBaseVariantElementImpl< IDatasmithVariantElement >`  
_L146-176_
- inherits: `FDatasmithBaseVariantElementImpl<IDatasmithVariantElement>`
- L149 _public function_ `explicit FDatasmithVariantElementImpl(const TCHAR* InName) : FDatasmithBaseVariantElementImpl(InName, EDatasmithElementType::Variant, (uint64)EDatasmithElementVariantSubType::Variant)`
- L154 _public function_ `virtual void AddActorBinding(const TSharedRef< IDatasmithActorBindingElement >& Binding) override`
- L159 _public function_ `virtual int32 GetActorBindingsCount() const override`
- L164 _public function_ `virtual TSharedPtr< IDatasmithActorBindingElement > GetActorBinding(int32 InIndex) override`
- L169 _public function_ `virtual void RemoveActorBinding(const TSharedRef< IDatasmithActorBindingElement >& Binding) override`
- L175 _private member_ `TArray< TSharedRef< IDatasmithActorBindingElement > > Bindings;`

#### class `FDatasmithVariantSetElementImpl`  
`class FDatasmithVariantSetElementImpl : public FDatasmithBaseVariantElementImpl< IDatasmithVariantSetElement >`  
_L178-208_
- inherits: `FDatasmithBaseVariantElementImpl<IDatasmithVariantSetElement>`
- L181 _public function_ `explicit FDatasmithVariantSetElementImpl(const TCHAR* InName) : FDatasmithBaseVariantElementImpl(InName, EDatasmithElementType::Variant, (uint64)EDatasmithElementVariantSubType::VariantSet)`
- L186 _public function_ `virtual void AddVariant(const TSharedRef< IDatasmithVariantElement >& Variant) override`
- L191 _public function_ `virtual int32 GetVariantsCount() const override`
- L196 _public function_ `virtual TSharedPtr< IDatasmithVariantElement > GetVariant(int32 InIndex) override`
- L201 _public function_ `virtual void RemoveVariant(const TSharedRef< IDatasmithVariantElement >& Variant) override`
- L207 _private member_ `TArray< TSharedRef< IDatasmithVariantElement > > Variants;`

#### class `FDatasmithLevelVariantSetsElementImpl`  
`class FDatasmithLevelVariantSetsElementImpl : public FDatasmithBaseVariantElementImpl< IDatasmithLevelVariantSetsElement >`  
_L210-240_
- inherits: `FDatasmithBaseVariantElementImpl<IDatasmithLevelVariantSetsElement>`
- L213 _public function_ `explicit FDatasmithLevelVariantSetsElementImpl(const TCHAR* InName) : FDatasmithBaseVariantElementImpl(InName, EDatasmithElementType::Variant, (uint64)EDatasmithElementVariantSubType::LevelVariantSets)`
- L218 _public function_ `virtual void AddVariantSet(const TSharedRef< IDatasmithVariantSetElement >& VariantSet) override`
- L223 _public function_ `virtual int32 GetVariantSetsCount() const override`
- L228 _public function_ `virtual TSharedPtr< IDatasmithVariantSetElement > GetVariantSet(int32 InIndex) override`
- L233 _public function_ `virtual void RemoveVariantSet(const TSharedRef< IDatasmithVariantSetElement >& VariantSet) override`
- L239 _private member_ `TArray< TSharedRef< IDatasmithVariantSetElement > > VariantSets;`

### `Source/Runtime/Datasmith/DatasmithCore/Public/DatasmithAnimationElements.h` (Public)


#### class `IDatasmithBaseAnimationElement`  
`class IDatasmithBaseAnimationElement : public IDatasmithElement`  
_L13-23_
- inherits: `IDatasmithElement`
- L16 _public prototype_ `virtual bool IsSubType( const EDatasmithElementAnimationSubType AnimSubType ) const = 0;`
- L19 _public prototype_ `virtual void SetCompletionMode(EDatasmithCompletionMode CompletionMode) = 0;` — Set how the actor should behave once its animation completes
- L22 _public prototype_ `virtual EDatasmithCompletionMode GetCompletionMode() const = 0;` — Get how the actor behaves once this animation is complete

#### class `IDatasmithTransformAnimationElement`  
`class IDatasmithTransformAnimationElement : public IDatasmithBaseAnimationElement`  
_L26-54_
- inherits: `IDatasmithBaseAnimationElement`
- desc: IDatasmithTransformAnimationElement holds the frames for an actor transform animation
- L29 _public prototype_ `virtual ~IDatasmithTransformAnimationElement() = default;`
- L32 _public prototype_ `virtual void AddFrame(EDatasmithTransformType TransformType, const FDatasmithTransformFrameInfo& FrameInfo) = 0;` — Add a frame of the given transform type to the animation
- L35 _public prototype_ `virtual int32 GetFramesCount(EDatasmithTransformType TransformType) const = 0;` — Return the number of frames of the given transform type in the animation
- L38 _public prototype_ `virtual void SetCurveInterpMode(EDatasmithTransformType TransformType, EDatasmithCurveInterpMode CurveInterpMode) = 0;` — Set the interpolation mode of the given transform type in the animation
- L41 _public prototype_ `virtual EDatasmithCurveInterpMode GetCurveInterpMode(EDatasmithTransformType TransformType) const = 0;` — Get the interpolation mode of the given transform type in the animation
- L44 _public prototype_ `virtual const FDatasmithTransformFrameInfo& GetFrame(EDatasmithTransformType TransformType, int32 Index) const = 0;` — Return the frame of the given transform type at the given index or an invalid frame if the index was out of bounds
- L47 _public prototype_ `virtual void RemoveFrame(EDatasmithTransformType TransformType, int32 Index) = 0;` — Remove the frame of the given transform type at the given index from the animation
- L50 _public prototype_ `virtual EDatasmithTransformChannels GetEnabledTransformChannels() const = 0;` — Gets which channels of this animation will be moved to the animation assets or serialized. All channels are enabled by default
- L53 _public prototype_ `virtual void SetEnabledTransformChannels(EDatasmithTransformChannels Channels) = 0;` — Sets which channels of this animation will be moved to the animation assets or serialized. All channels are enabled by default

#### class `IDatasmithVisibilityAnimationElement`  
`class IDatasmithVisibilityAnimationElement : public IDatasmithBaseAnimationElement`  
_L57-85_
- inherits: `IDatasmithBaseAnimationElement`
- desc: IDatasmithVisibilityAnimationElement holds the frames for an actor's visibility animation
- L60 _public prototype_ `virtual ~IDatasmithVisibilityAnimationElement() = default;`
- L63 _public prototype_ `virtual void AddFrame(const FDatasmithVisibilityFrameInfo& FrameInfo) = 0;` — Add a frame to the animation
- L66 _public prototype_ `virtual int32 GetFramesCount() const = 0;` — Return the number of frames of the animation
- L69 _public prototype_ `virtual void SetCurveInterpMode(EDatasmithCurveInterpMode CurveInterpMode) = 0;` — Set the interpolation mode of the animation
- L72 _public prototype_ `virtual EDatasmithCurveInterpMode GetCurveInterpMode() const = 0;` — Get the interpolation mode of the animation
- L75 _public prototype_ `virtual const FDatasmithVisibilityFrameInfo& GetFrame(int32 Index) const = 0;` — Return the frame of the animation at the given index or an invalid frame if the index was out of bounds
- L78 _public prototype_ `virtual void RemoveFrame(int32 Index) = 0;` — Remove the frame at the given index from the animation
- L81 _public prototype_ `virtual void SetPropagateToChildren(bool bPropagate) = 0;` — Sets whether this animation will be duplicated to all children (recursively) when imported
- L84 _public prototype_ `virtual bool GetPropagateToChildren() const = 0;` — Gets whether this animation will be duplicated to all children (recursively) when imported

#### class `IDatasmithSubsequenceAnimationElement`  
`class IDatasmithSubsequenceAnimationElement : public IDatasmithBaseAnimationElement`  
_L88-116_
- inherits: `IDatasmithBaseAnimationElement`
- desc: IDatasmithSubsequenceAnimationElement holds a reference to a IDatasmithLevelSequenceElement, to be played as a subsequence
- L91 _public prototype_ `virtual ~IDatasmithSubsequenceAnimationElement() = default;`
- L94 _public prototype_ `virtual FFrameNumber GetStartTime() const = 0;` — Get the frame where the subsequence starts
- L97 _public prototype_ `virtual void SetStartTime(FFrameNumber InStartTime) = 0;` — Set the frame where the subsequence starts
- L100 _public prototype_ `virtual int32 GetDuration() const = 0;` — Get the subsequence duration in number of frames
- L103 _public prototype_ `virtual void SetDuration(int32 InDuration) = 0;` — Set the subsequence duration in number of frames
- L106 _public prototype_ `virtual float GetTimeScale() const = 0;` — Get the time scale used for the subsequence
- L109 _public prototype_ `virtual void SetTimeScale(float InTimeScale) = 0;` — Set the time scale used for the subsequence
- L112 _public prototype_ `virtual TWeakPtr<IDatasmithLevelSequenceElement> GetSubsequence() const = 0;` — Get a pointer to the subsequence that this element references
- L115 _public prototype_ `virtual void SetSubsequence(TWeakPtr<IDatasmithLevelSequenceElement> InSubsequence) = 0;` — Set the subsequence that this element references

#### class `IDatasmithLevelSequenceElement`  
`class IDatasmithLevelSequenceElement : public IDatasmithElement`  
_L119-161_
- inherits: `IDatasmithElement`
- desc: IDatasmithLevelSequenceElement holds a set of animations
- L122 _public prototype_ `virtual ~IDatasmithLevelSequenceElement() = default;`
- L125 _public prototype_ `virtual const TCHAR* GetFile() const = 0;` — Get the output filename, it can be absolute or relative to the scene file
- L128 _public prototype_ `virtual void SetFile(const TCHAR* InFile) = 0;` — Set the output filename, it can be absolute or relative to the scene file
- L131 _public prototype_ `virtual FMD5Hash GetFileHash() const = 0;` — Return a MD5 hash of the content of the Level Sequence Element. Used in CalculateElementHash to quickly identify Element with identical content
- L134 _public prototype_ `virtual void SetFileHash(FMD5Hash Hash) = 0;` — Set the MD5 hash of the Level Sequence file. This should be a hash of its content.
- L137 _public prototype_ `virtual float GetFrameRate() const = 0;` — Gets the frame rate for the animations in the level sequence
- L140 _public prototype_ `virtual void SetFrameRate(float FramePerSecs) = 0;` — Sets the frame rate for the animations in the level sequence
- L147 _public prototype_ `virtual void AddAnimation(const TSharedRef< IDatasmithBaseAnimationElement >& InAnimation) = 0;` — Adds an animation to the level sequence. @param InAnimation the animation to add
- L150 _public prototype_ `virtual int32 GetAnimationsCount() const = 0;` — Returns the number of animations in the level sequence
- L153 _public prototype_ `virtual TSharedPtr< IDatasmithBaseAnimationElement > GetAnimation(int32 InIndex) = 0;` — Returns the animation using this index
- L160 _public prototype_ `virtual void RemoveAnimation(const TSharedRef< IDatasmithBaseAnimationElement >& InAnimation) = 0;` — Removes an animation from the level sequence. @param InAnimation the animation to remove

### `Source/Runtime/Datasmith/DatasmithCore/Public/DatasmithAnimationSerializer.h` (Public)


#### class `FDatasmithAnimationSerializer`  
`class FDatasmithAnimationSerializer`  
_L15-20_
- L18 _public prototype_ `bool Serialize(const TSharedRef<IDatasmithLevelSequenceElement>& LevelSequence, const TCHAR* FilePath, bool bDebugFormat = false);`
- L19 _public prototype_ `bool Deserialize(const TSharedRef<IDatasmithLevelSequenceElement>& LevelSequence, const TCHAR* FilePath);`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API DATASMITHCORE_API`
- L13 _macro_ `#define DATASMITH_ANIMATION_EXTENSION TEXT(".udsanim")`

### `Source/Runtime/Datasmith/DatasmithCore/Public/DatasmithCloth.h` (Public)


#### struct `FParameterData`  
`struct UE_DEPRECATED(5.5, "The experimental Cloth importer is no longer supported.") FParameterData`  
_L20-31_
- L22 _public member_ `FString Name;`
- L25 _public member_ `ETarget Target = ETarget::Vertex;` — (also drives the expected number of values)
- L27 _public member_ `TVariant<TArray<float>, TArray<double>> Data;`

#### enum `FParameterData::ETarget`  
`enum class ETarget`  
_L24-24_
- L24 _public enumerator_ `enum class ETarget { Vertex }; ETarget Target = ETarget::Vertex; TVariant<TArray<float>`

#### class `FDatasmithClothPattern`  
`class UE_DEPRECATED(5.5, "The experimental Cloth importer is no longer supported.") FDatasmithClothPattern`  
_L34-48_
- L37 _public member_ `TArray<FVector2f> SimPosition;`
- L38 _public member_ `TArray<FVector3f> SimRestPosition;`
- L39 _public member_ `TArray<uint32> SimTriangleIndices;`
- L42 _public member_ `TArray<FParameterData> Parameters;`
- L46 _public function_ `bool IsValid() const`

#### struct `FDatasmithClothSewingInfo`  
`struct UE_DEPRECATED(5.5, "The experimental Cloth importer is no longer supported.") FDatasmithClothSewingInfo`  
_L51-59_
- L53 _public member_ `uint32 Seam0PanelIndex = 0;`
- L54 _public member_ `uint32 Seam1PanelIndex = 0;`
- L55 _public member_ `TArray<uint32> Seam0MeshIndices;`
- L56 _public member_ `TArray<uint32> Seam1MeshIndices;`

#### class `FDatasmithClothPresetProperty`  
`class UE_DEPRECATED(5.5, "The experimental Cloth importer is no longer supported.") FDatasmithClothPresetProperty`  
_L62-70_
- L65 _public member_ `FName Name;`
- L66 _public member_ `double Value;`

#### class `FDatasmithClothPresetPropertySet`  
`class UE_DEPRECATED(5.5, "The experimental Cloth importer is no longer supported.") FDatasmithClothPresetPropertySet`  
_L73-83_
- L76 _public member_ `FString SetName;`
- L78 _public member_ `TArray<FDatasmithClothPresetProperty> Properties;`

#### class `FDatasmithCloth`  
`class UE_DEPRECATED(5.5, "The experimental Cloth importer is no longer supported.") FDatasmithCloth`  
_L86-97_
- L90 _public member_ `TArray<FDatasmithClothPattern> Patterns;`
- L91 _public member_ `TArray<FDatasmithClothSewingInfo> Sewing;`
- L92 _public member_ `TArray<FDatasmithClothPresetPropertySet> PropertySets;`

#### class `UDatasmithClothAssetFactory`  
`class UDatasmithClothAssetFactory : public UObject`  
_L102-125_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UObject`
- desc: Modular cloth asset factory base class.
- L108 _public prototype_ `UDatasmithClothAssetFactory() = default;` — `UE_DEPRECATED(5.5, "The experimental Cloth importer is no longer supported.")`
- L110 _public prototype_ `virtual ~UDatasmithClothAssetFactory() = default;` — `UE_DEPRECATED(5.5, "The experimental Cloth importer is no longer supported.")`
- L113 _public prototype_ `virtual UObject* CreateClothAsset(UObject* Outer, const FName& Name, EObjectFlags Flags) const PURE_VIRTUAL(UDatasmithClothAssetFactory::CreateClothAsset, return nullptr;);` — `UE_DEPRECATED(5.5, "The experimental Cloth importer is no longer supported.")`
- L117 _public prototype_ `virtual UObject* DuplicateClothAsset(UObject* ClothAsset, UObject* Outer, const FName& Name) const PURE_VIRTUAL(UDatasmithClothAssetFactory::DuplicateClothAsset, return nullptr;);` — `UE_DEPRECATED(5.5, "The experimental Cloth importer is no longer supported.")`
- L122 _public prototype_ `virtual void InitializeClothAsset(UObject* ClothAsset, const FDatasmithCloth& DatasmithCloth) const PURE_VIRTUAL(UDatasmithClothAssetFactory::InitializeClothAsset, );` — `UE_DEPRECATED(5.5, "The experimental Cloth importer is no longer supported.")`

#### class `UDatasmithClothComponentFactory`  
`class UDatasmithClothComponentFactory : public UObject`  
_L130-147_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UObject`
- desc: Modular cloth component factory base class.
- L136 _public prototype_ `UDatasmithClothComponentFactory() = default;` — `UE_DEPRECATED(5.5, "The experimental Cloth importer is no longer supported.")`
- L138 _public prototype_ `virtual ~UDatasmithClothComponentFactory() = default;` — `UE_DEPRECATED(5.5, "The experimental Cloth importer is no longer supported.")`
- L141 _public prototype_ `virtual USceneComponent* CreateClothComponent(UObject* Outer) const PURE_VIRTUAL(UDatasmithClothComponentFactory::CreateClothComponent, return nullptr;);` — `UE_DEPRECATED(5.5, "The experimental Cloth importer is no longer supported.")`
- L145 _public prototype_ `virtual void InitializeClothComponent(USceneComponent* ClothComponent, UObject* ClothAsset, USceneComponent* RootComponent) const PURE_VIRTUAL(UDatasmithClothComponentFactory::InitializeClothComponent, );` — `UE_DEPRECATED(5.5, "The experimental Cloth importer is no longer supported.")`

#### class `IDatasmithClothFactoryClassesProvider`  
`class UE_DEPRECATED(5.5, "The experimental Cloth importer is no longer supported.") IDatasmithClothFactoryClassesProvider : public IModularFeature`  
_L151-163_
- inherits: `IModularFeature`
- desc: A modular interface to provide factory classes to initialize cloth assets and components.
- L154 _public member_ `inline static const FName FeatureName = "ID`
- L156 _public prototype_ `IDatasmithClothFactoryClassesProvider() = default;`
- L157 _public prototype_ `virtual ~IDatasmithClothFactoryClassesProvider() = default;`
- L159 _public prototype_ `virtual FName GetName() const = 0;`
- L161 _public prototype_ `virtual TSubclassOf<UDatasmithClothAssetFactory> GetClothAssetFactoryClass() const = 0;`
- L162 _public prototype_ `virtual TSubclassOf<UDatasmithClothComponentFactory> GetClothComponentFactoryClass() const = 0;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API DATASMITHCORE_API`

### `Source/Runtime/Datasmith/DatasmithCore/Public/DatasmithCore.h` (Public)


#### Free symbols / members of external scopes

- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDatasmith, Log, All);`

### `Source/Runtime/Datasmith/DatasmithCore/Public/DatasmithDefinitions.h` (Public)


#### enum `EDatasmithElementType`  
`enum class EDatasmithElementType : uint64`  
_L19-59_
- desc: Element type is used to identify its class like Mesh, Actor, Light, etc.
- L21 _public enumerator_ `None = 0ull`
- L22 _public enumerator_ `StaticMesh = 1ull << 0`
- L23 _public enumerator_ `Actor = 1ull << 1`
- L24 _public enumerator_ `StaticMeshActor = 1ull << 2`
- L25 _public enumerator_ `Light = 1ull << 3`
- L26 _public enumerator_ `PointLight = 1ull << 4`
- L27 _public enumerator_ `SpotLight = 1ull << 5`
- L28 _public enumerator_ `DirectionalLight = 1ull << 6`
- L29 _public enumerator_ `AreaLight = 1ull << 7`
- L30 _public enumerator_ `LightmassPortal = 1ull << 8`
- L31 _public enumerator_ `EnvironmentLight = 1ull << 9`
- L32 _public enumerator_ `Camera = 1ull << 10`
- L33 _public enumerator_ `Shader = 1ull << 11`
- L34 _public enumerator_ `BaseMaterial = 1ull << 12`
- L35 _public enumerator_ `MasterMaterial UE_DEPRECATED(5.1, "EDatasmithElementType::MasterMaterial will not be supported in 5.2. Please use EDatasmithElementType::MaterialInstance instead.") = 1ull << 13`
- L36 _public enumerator_ `MaterialInstance = 1ull << 13`
- L37 _public enumerator_ `KeyValueProperty = 1ull << 14`
- L38 _public enumerator_ `Texture = 1ull << 15`
- L39 _public enumerator_ `MaterialId = 1ull << 16`
- L40 _public enumerator_ `PostProcess = 1ull << 17`
- L41 _public enumerator_ `Scene = 1ull << 18`
- L42 _public enumerator_ `MetaData = 1ull << 19`
- L43 _public enumerator_ `CustomActor = 1ull << 20`
- L44 _public enumerator_ `Material = 1ull << 21`
- L45 _public enumerator_ `Landscape = 1ull << 22`
- L46 _public enumerator_ `UEPbrMaterial = 1ull << 23`
- L47 _public enumerator_ `PostProcessVolume = 1ull << 24`
- L48 _public enumerator_ `LevelSequence = 1ull << 25`
- L49 _public enumerator_ `Animation = 1ull << 26`
- L50 _public enumerator_ `HierarchicalInstanceStaticMesh = 1ull << 27`
- L51 _public enumerator_ `Variant = 1ull << 28`
- L52 _public enumerator_ `Decal = 1ull << 29`
- L53 _public enumerator_ `DecalMaterial = 1ull << 30`
- L54 _public enumerator_ `MaterialExpression = 1ull << 31`
- L55 _public enumerator_ `MaterialExpressionInput = 1ull << 32`
- L56 _public enumerator_ `MaterialExpressionOutput = 1ull << 33`
- L57 _public enumerator_ `Cloth UE_DEPRECATED(5.5, "The experimental Cloth importer is no longer supported.") = 1ull << 34`
- L58 _public enumerator_ `ClothActor UE_DEPRECATED(5.5, "The experimental Cloth importer is no longer supported.") = 1ull << 35`

#### enum `EDatasmithElementAnimationSubType`  
`enum class EDatasmithElementAnimationSubType : uint64`  
_L64-70_
- desc: Subtype of the Animation EDatasmithElementType, containing base, transform, visibility animations and etc.
- L66 _public enumerator_ `BaseAnimation = 0`
- L67 _public enumerator_ `TransformAnimation = 1 << 0`
- L68 _public enumerator_ `VisibilityAnimation = 1 << 1`
- L69 _public enumerator_ `SubsequenceAnimation = 1 << 2`

#### enum `EDatasmithElementVariantSubType`  
`enum class EDatasmithElementVariantSubType : uint64`  
_L75-84_
- desc: Subtype of the Variant EDatasmithElementType, containing property value, variant, variant set, etc.
- L77 _public enumerator_ `None = 0`
- L78 _public enumerator_ `LevelVariantSets = 1 << 0`
- L79 _public enumerator_ `VariantSet = 1 << 1`
- L80 _public enumerator_ `Variant = 1 << 2`
- L81 _public enumerator_ `ActorBinding = 1 << 3`
- L82 _public enumerator_ `PropertyCapture = 1 << 4`
- L83 _public enumerator_ `ObjectPropertyCapture = 1 << 5`

#### enum `EDatasmithMaterialExpressionType`  
`enum class EDatasmithMaterialExpressionType : uint8`  
_L89-102_
- desc: Subtype of the MaterialExpression EDatasmithElementType, containing property value, variant, variant set, etc.
- L91 _public enumerator_ `ConstantBool`
- L92 _public enumerator_ `ConstantColor`
- L93 _public enumerator_ `ConstantScalar`
- L94 _public enumerator_ `FlattenNormal`
- L95 _public enumerator_ `FunctionCall`
- L96 _public enumerator_ `Generic`
- L97 _public enumerator_ `Texture`
- L98 _public enumerator_ `TextureCoordinate`
- L99 _public enumerator_ `Custom`
- L101 _public enumerator_ `None = 255`

#### enum `EDatasmithTransformChannels`  
`enum class EDatasmithTransformChannels : uint16`  
_L109-129_
- desc: Describes a set of channels from a transform animation. Used to enable/disable those channels on import/export. The values defined in EDatasmithTransformChannels should mirror the analogues in EMovieSceneTransformChannel
- L111 _public enumerator_ `None = 0x000`
- L113 _public enumerator_ `TranslationX = 0x001`
- L114 _public enumerator_ `TranslationY = 0x002`
- L115 _public enumerator_ `TranslationZ = 0x004`
- L116 _public enumerator_ `Translation = TranslationX | TranslationY | TranslationZ`
- L118 _public enumerator_ `RotationX = 0x008`
- L119 _public enumerator_ `RotationY = 0x010`
- L120 _public enumerator_ `RotationZ = 0x020`
- L121 _public enumerator_ `Rotation = RotationX | RotationY | RotationZ`
- L123 _public enumerator_ `ScaleX = 0x040`
- L124 _public enumerator_ `ScaleY = 0x080`
- L125 _public enumerator_ `ScaleZ = 0x100`
- L126 _public enumerator_ `Scale = ScaleX | ScaleY | ScaleZ`
- L128 _public enumerator_ `All = Translation | Rotation | Scale`

#### enum `EDatasmithLightShape`  
`enum class EDatasmithLightShape : uint8`  
_L135-142_
- reflection: `UENUM(BlueprintType)`
- desc: Different supported light shapes
- L137 _public enumerator_ `Rectangle`
- L138 _public enumerator_ `Disc`
- L139 _public enumerator_ `Sphere`
- L140 _public enumerator_ `Cylinder`
- L141 _public enumerator_ `None`

#### enum `EDatasmithAreaLightType`  
`enum class EDatasmithAreaLightType`  
_L146-152_
- L148 _public enumerator_ `Point`
- L149 _public enumerator_ `Spot`
- L150 _public enumerator_ `IES_DEPRECATED`
- L151 _public enumerator_ `Rect`

#### enum `EDatasmithLightUnits`  
`enum class EDatasmithLightUnits`  
_L157-163_
- desc: Light intensity units
- L159 _public enumerator_ `Unitless`
- L160 _public enumerator_ `Candelas`
- L161 _public enumerator_ `Lumens`
- L162 _public enumerator_ `EV`

#### enum `EDatasmithTextureMode`  
`enum class EDatasmithTextureMode : uint8`  
_L167-177_
- reflection: `UENUM()`
- desc: Different usage for textures.  Note: Preserve enum order.
- L169 _public enumerator_ `Diffuse`
- L170 _public enumerator_ `Specular`
- L171 _public enumerator_ `Normal`
- L172 _public enumerator_ `NormalGreenInv`
- L173 _public enumerator_ `UNUSED_Displace`
- L174 _public enumerator_ `Other`
- L175 _public enumerator_ `Bump`
- L176 _public enumerator_ `Ies`

#### enum `EDatasmithTextureFilter`  
`enum class EDatasmithTextureFilter : uint8`  
_L181-188_
- reflection: `UENUM()`
- desc: Texture filtering for textures.
- L183 _public enumerator_ `Nearest`
- L184 _public enumerator_ `Bilinear`
- L185 _public enumerator_ `Trilinear`
- L187 _public enumerator_ `Default` — Use setting from the Texture Group.

#### enum `EDatasmithTextureAddress`  
`enum class EDatasmithTextureAddress : uint8`  
_L192-197_
- reflection: `UENUM()`
- desc: Texture address mode for textures.  Note: Preserve enum order.
- L194 _public enumerator_ `Wrap`
- L195 _public enumerator_ `Clamp`
- L196 _public enumerator_ `Mirror`

#### enum `EDatasmithTextureFormat`  
`enum class EDatasmithTextureFormat : uint8`  
_L201-205_
- reflection: `UENUM()`
- desc: Texture format for raw data importing.
- L203 _public enumerator_ `PNG`
- L204 _public enumerator_ `JPEG`

#### enum `EDatasmithColorSpace`  
`enum class EDatasmithColorSpace : uint8`  
_L214-219_
- reflection: `UENUM()`
- desc: Texture color space. Default: Leave at whatever is default for the texture mode sRGB: Enable the sRGB boolean regardless of texture mode Linear: Disable the sRGB boolean regardless of texture mode
- L216 _public enumerator_ `Default`
- L217 _public enumerator_ `sRGB`
- L218 _public enumerator_ `Linear`

#### enum `EDatasmithMaterialMode`  
`enum class EDatasmithMaterialMode`  
_L227-233_
- desc: Regular: lambertians, glossy materials and almost every type of material but glass, metal or highly reflective. Glass: glass material, it should have appropriate index of refraction and transparency Metal: to be considered a metal material it should have a proper reflective ior MixedMetal: highly reflective non-metallic materials
- L229 _public enumerator_ `Regular`
- L230 _public enumerator_ `Glass`
- L231 _public enumerator_ `Metal`
- L232 _public enumerator_ `MixedMetal`

#### enum `EDatasmithReferenceMaterialType`  
`enum class EDatasmithReferenceMaterialType : uint8`  
_L235-250_
- L238 _public enumerator_ `Auto` — Let Datasmith figure which reference material to use
- L239 _public enumerator_ `Opaque`
- L240 _public enumerator_ `Transparent`
- L241 _public enumerator_ `ClearCoat`
- L243 _public enumerator_ `Custom` — Instantiate a reference material from a specified one
- L245 _public enumerator_ `CutOut` — Material has a transparent cutout map
- L246 _public enumerator_ `Emissive`
- L247 _public enumerator_ `Decal`
- L249 _public enumerator_ `Count` — Dummy element to count the number of types

#### enum `EDatasmithReferenceMaterialQuality`  
`enum class EDatasmithReferenceMaterialQuality : uint8`  
_L252-258_
- L254 _public enumerator_ `High`
- L255 _public enumerator_ `Low`
- L257 _public enumerator_ `Count` — Dummy element to count the number of qualities

#### enum `EDatasmithCompMode`  
`enum class EDatasmithCompMode`  
_L271-281_
- desc: Different methods for mixing textures: Just one texture Mix blended by weight Fresnel using a fresnel weight expression Ior using a fresnel weight expression where its curve is defined by the ior value ColorCorrectGamma color correct over the texture ColorCorrectContrast color correct over the texture Multiply simple multiplication of textures Composite blending used common image editor modes
- L273 _public enumerator_ `Regular`
- L274 _public enumerator_ `Mix`
- L275 _public enumerator_ `Fresnel`
- L276 _public enumerator_ `Ior`
- L277 _public enumerator_ `ColorCorrectGamma`
- L278 _public enumerator_ `ColorCorrectContrast`
- L279 _public enumerator_ `Multiply`
- L280 _public enumerator_ `Composite`

#### enum `EDatasmithCompositeCompMode`  
`enum class EDatasmithCompositeCompMode`  
_L284-309_
- desc: classic blend modes used in image editors
- L286 _public enumerator_ `Alpha`
- L287 _public enumerator_ `Average`
- L288 _public enumerator_ `Add`
- L289 _public enumerator_ `Sub`
- L290 _public enumerator_ `Mult`
- L291 _public enumerator_ `Burn`
- L292 _public enumerator_ `Dodge`
- L293 _public enumerator_ `Darken`
- L294 _public enumerator_ `Difference`
- L295 _public enumerator_ `Exclusion`
- L296 _public enumerator_ `HardLight`
- L297 _public enumerator_ `Lighten`
- L298 _public enumerator_ `Screen`
- L299 _public enumerator_ `LinearBurn`
- L300 _public enumerator_ `LinearDodge`
- L301 _public enumerator_ `LinearLight`
- L302 _public enumerator_ `Overlay`
- L303 _public enumerator_ `PinLight`
- L304 _public enumerator_ `SoftLight`
- L305 _public enumerator_ `Hue`
- L306 _public enumerator_ `Saturation`
- L307 _public enumerator_ `Color`
- L308 _public enumerator_ `Value`

#### enum `EDatasmithBlendMode`  
`enum class EDatasmithBlendMode`  
_L312-318_
- desc: material blend modes
- L314 _public enumerator_ `Alpha`
- L315 _public enumerator_ `ClearCoat`
- L316 _public enumerator_ `Screen`
- L317 _public enumerator_ `Softlight`

#### enum `EDatasmithShaderDataType`  
`enum class EDatasmithShaderDataType`  
_L322-329_
- desc: see ECustomMaterialOutputType
- L324 _public enumerator_ `Float1 = 1`
- L325 _public enumerator_ `Float2 = 2`
- L326 _public enumerator_ `Float3 = 3`
- L327 _public enumerator_ `Float4 = 4`
- L328 _public enumerator_ `MaterialAttribute = 5`

#### enum `EDatasmithKeyValuePropertyType`  
`enum class EDatasmithKeyValuePropertyType : uint8`  
_L333-342_
- reflection: `UENUM(BlueprintType)`
- desc: Key-value property
- L335 _public enumerator_ `String`
- L336 _public enumerator_ `Color`
- L337 _public enumerator_ `Float`
- L338 _public enumerator_ `Bool`
- L339 _public enumerator_ `Texture`
- L340 _public enumerator_ `Vector`
- L341 _public enumerator_ `Integer`

#### enum `EDatasmithShaderUsage`  
`enum class EDatasmithShaderUsage`  
_L348-352_
- desc: Analog to UE material domain, besides UE has some other modes currently we only support Surface and LightFunction. since GUI, postproduction materials and so are out of the scope of Datasmith
- L350 _public enumerator_ `Surface`
- L351 _public enumerator_ `LightFunction`

#### enum `EDatasmithShadingModel`  
`enum class EDatasmithShadingModel : uint8`  
_L356-363_
- L358 _public enumerator_ `DefaultLit`
- L359 _public enumerator_ `ThinTranslucent`
- L360 _public enumerator_ `Subsurface`
- L361 _public enumerator_ `ClearCoat`
- L362 _public enumerator_ `Unlit`

#### enum `EDatasmithActorRemovalRule`  
`enum class EDatasmithActorRemovalRule : uint8`  
_L366-376_
- reflection: `UENUM()`
- L369 _public enumerator_ `RemoveChildren` — Remove also the actors children
- L372 _public enumerator_ `KeepChildrenAndKeepRelativeTransform` — Keeps current relative transform as the relative transform to the new parent.

#### enum `EDatasmithActorAttachmentRule`  
`enum class EDatasmithActorAttachmentRule : uint8`  
_L379-386_
- reflection: `UENUM()`
- L382 _public enumerator_ `KeepRelativeTransform` — Keeps current relative transform as the relative transform to the new parent.
- L385 _public enumerator_ `KeepWorldTransform` — The attached actor or component will maintain the same world transform.

#### enum `EDatasmithTransformType`  
`enum class EDatasmithTransformType : uint8`  
_L389-395_
- desc: Supported transform types for animations
- L391 _public enumerator_ `Translation`
- L392 _public enumerator_ `Rotation`
- L393 _public enumerator_ `Scale`
- L394 _public enumerator_ `Count`

#### enum `EDatasmithCompletionMode`  
`enum class EDatasmithCompletionMode : uint8`  
_L402-407_
- reflection: `UENUM()`
- desc: Describes how an animated node should behave after its animation has completed Mirrors EMovieSceneCompletionMode
- L404 _public enumerator_ `KeepState`
- L405 _public enumerator_ `RestoreState`
- L406 _public enumerator_ `ProjectDefault`

#### enum `EDatasmithPropertyCategory`  
`enum class EDatasmithPropertyCategory : uint8`  
_L415-426_
- reflection: `UENUM()`
- desc: Describes a category of an UPropertyValue asset, indicating types of properties that require special handling for any reason. Mirrors EPropertyValueCategory
- L417 _public enumerator_ `Undefined = 0`
- L418 _public enumerator_ `Generic = 1`
- L419 _public enumerator_ `RelativeLocation = 2`
- L420 _public enumerator_ `RelativeRotation = 4`
- L421 _public enumerator_ `RelativeScale3D = 8`
- L422 _public enumerator_ `Visibility = 16`
- L423 _public enumerator_ `Material = 32`
- L424 _public enumerator_ `Color = 64`
- L425 _public enumerator_ `Option = 128`

#### enum `EDatasmithActorMobilityType`  
`enum class EDatasmithActorMobilityType : uint8`  
_L651-656_
- L653 _public enumerator_ `Static = 0`
- L654 _public enumerator_ `Stationary`
- L655 _public enumerator_ `Movable`

#### Free symbols / members of external scopes

- L9 _macro_ `#define WITH_COREUOBJECT 0`
- L15 _macro_ `#define UENUM(...)`
- L61 _prototype_ `ENUM_CLASS_FLAGS( EDatasmithElementType );` — Define bitwise operators for EDatasmithElementType
- L72 _prototype_ `ENUM_CLASS_FLAGS( EDatasmithElementAnimationSubType );` — Define bitwise operators for EDatasmithElementAnimationSubtype
- L86 _prototype_ `ENUM_CLASS_FLAGS( EDatasmithElementVariantSubType );` — Define bitwise operators for EDatasmithElementVariantSubType
- L131 _prototype_ `ENUM_CLASS_FLAGS( EDatasmithTransformChannels );` — Define bitwise operators for EDatasmithTransformChannels
- L144 _variable_ `static const TCHAR* DatasmithAreaLightShapeStrings[] = { TEXT("Rectangle"), TEXT("Disc"), TEXT("Sphere"), TE`
- L154 _variable_ `static const TCHAR* DatasmithAreaLightTypeStrings[] = { TEXT("Point"), TEXT("Spot"), TEXT("IES"),`
- L354 _variable_ `static const TCHAR* DatasmithShadingModelStrings[] = { TEXT("DefaultLit"), TEXT("ThinTranslucent"), TEXT("`
- L427 _prototype_ `ENUM_CLASS_FLAGS(EDatasmithPropertyCategory) static const TCHAR* KeyValuePropertyTypeStrings[] =`
- L432 _macro_ `#define DATASMITH_HOSTNAME TEXT("Host")` — HOST NAME
- L435 _macro_ `#define DATASMITH_EXPORTERVERSION TEXT("Version")` — DATASMITH EXPORTER VERSION
- L436 _macro_ `#define DATASMITH_EXPORTERSDKVERSION TEXT("SDKVersion")`
- L439 _macro_ `#define DATASMITH_APPLICATION TEXT("Application")` — APPLICATION INFO
- L440 _macro_ `#define DATASMITH_VENDOR TEXT("Vendor")`
- L441 _macro_ `#define DATASMITH_PRODUCTNAME TEXT("ProductName")`
- L442 _macro_ `#define DATASMITH_PRODUCTVERSION TEXT("ProductVersion")`
- L445 _macro_ `#define DATASMITH_USER TEXT("User")` — USER INFO
- L446 _macro_ `#define DATASMITH_USERID TEXT("ID")`
- L447 _macro_ `#define DATASMITH_USEROS TEXT("OS")`
- L450 _macro_ `#define DATASMITH_EXPORT TEXT("Export")` — EXPORT INFO
- L451 _macro_ `#define DATASMITH_EXPORTDURATION TEXT("Duration")`
- L452 _macro_ `#define DATASMITH_RESOURCEPATH TEXT("ResourcePath")`
- L455 _macro_ `#define DATASMITH_GEOLOCATION TEXT("Geolocation")` — SCENE GEOLOCATION
- L456 _macro_ `#define DATASMITH_GEOLOCATION_LATITUDE TEXT("lat")`
- L457 _macro_ `#define DATASMITH_GEOLOCATION_LONGITUDE TEXT("lon")`
- L458 _macro_ `#define DATASMITH_GEOLOCATION_ELEVATION TEXT("ele")`
- L461 _macro_ `#define DATASMITH_HASH TEXT("Hash")` — ELEMENTS
- L462 _macro_ `#define DATASMITH_ENABLED TEXT("Enabled")`
- L465 _macro_ `#define DATASMITH_STATICMESHNAME TEXT("StaticMesh")` — STATIC MESHES
- L466 _macro_ `#define DATASMITH_LIGHTMAPCOORDINATEINDEX TEXT("LightmapCoordinateIndex")`
- L467 _macro_ `#define DATASMITH_LIGHTMAPUVSOURCE TEXT("LightmapUV")`
- L468 _macro_ `#define DATASMITH_MATERIAL TEXT("Material")`
- L470 _macro_ `#define DATASMITH_ACTORNAME TEXT("Actor")`
- L472 _macro_ `#define DATASMITH_CLOTH TEXT("Cloth") // UE_DEPRECATED(5.5, "The experimental Cloth importer is no longer supported.")`
- L473 _macro_ `#define DATASMITH_CLOTHACTORNAME TEXT("ClothActor") // UE_DEPRECATED(5.5, "The experimental Cloth importer is no longer supported.")`
- L476 _macro_ `#define DATASMITH_ACTORMESHNAME TEXT("ActorMesh")` — ACTOR MESHES
- L479 _macro_ `#define DATASMITH_ACTORHIERARCHICALINSTANCEDMESHNAME TEXT("ActorHierarchicalInstancedStaticMesh")` — ACTOR HIERARCHICAL INSTANCED STATIC MESH
- L482 _macro_ `#define DATASMITH_LEVELSEQUENCENAME TEXT("LevelSequence")` — LEVEL SEQUENCES
- L485 _macro_ `#define DATASMITH_LEVELVARIANTSETSNAME TEXT("LevelVariantSets")` — VARIANTS
- L486 _macro_ `#define DATASMITH_VARIANTSETNAME TEXT("VariantSet")`
- L487 _macro_ `#define DATASMITH_VARIANTNAME TEXT("Variant")`
- L488 _macro_ `#define DATASMITH_ACTORBINDINGNAME TEXT("ActorBinding")`
- L489 _macro_ `#define DATASMITH_PROPERTYCAPTURENAME TEXT("PropertyCapture")`
- L490 _macro_ `#define DATASMITH_OBJECTPROPERTYCAPTURENAME TEXT("ObjectPropertyCapture")`
- L493 _macro_ `#define DATASMITH_LIGHTNAME TEXT("Light")` — LIGHTS
- L494 _macro_ `#define DATASMITH_POINTLIGHTNAME TEXT("PointLight")`
- L495 _macro_ `#define DATASMITH_SPOTLIGHTNAME TEXT("SpotLight")`
- L496 _macro_ `#define DATASMITH_AREALIGHTNAME TEXT("AreaLight")`
- L497 _macro_ `#define DATASMITH_PORTALLIGHTNAME TEXT("SkyPortalLight")`
- L498 _macro_ `#define DATASMITH_DIRECTLIGHTNAME TEXT("DirectionalLight")`
- L499 _macro_ `#define DATASMITH_PHYSICALSKYNAME TEXT("PhysicalSky")`
- L501 _macro_ `#define DATASMITH_LIGHTCOLORNAME TEXT("Color")`
- L502 _macro_ `#define DATASMITH_LIGHTUSETEMPNAME TEXT("usetemp")`
- L503 _macro_ `#define DATASMITH_LIGHTTEMPNAME TEXT("temperature")`
- L504 _macro_ `#define DATASMITH_LIGHTIESNAME TEXT("IES")`
- L505 _macro_ `#define DATASMITH_LIGHTIESTEXTURENAME TEXT("IESTexture")`
- L506 _macro_ `#define DATASMITH_LIGHTIESBRIGHTNAME TEXT("IESbrightness")`
- L507 _macro_ `#define DATASMITH_LIGHTIESROTATION TEXT("IESrotation")`
- L508 _macro_ `#define DATASMITH_LIGHTINTENSITYNAME TEXT("Intensity")`
- L509 _macro_ `#define DATASMITH_LIGHTINTENSITYUNITSNAME TEXT("IntensityUnits")`
- L510 _macro_ `#define DATASMITH_LIGHTSOURCESIZENAME TEXT("SourceSize")`
- L511 _macro_ `#define DATASMITH_LIGHTSOURCELENGTHNAME TEXT("SourceLength")`
- L512 _macro_ `#define DATASMITH_LIGHTATTENUATIONRADIUSNAME TEXT("AttenuationRadius")`
- L513 _macro_ `#define DATASMITH_LIGHTINNERRADIUSNAME TEXT("InnerConeAngle")`
- L514 _macro_ `#define DATASMITH_LIGHTOUTERRADIUSNAME TEXT("OuterConeAngle")`
- L515 _macro_ `#define DATASMITH_LIGHTMATERIAL TEXT("Material")`
- L517 _macro_ `#define DATASMITH_AREALIGHTSHAPE TEXT("Shape")`
- L518 _macro_ `#define DATASMITH_AREALIGHTDISTRIBUTION TEXT("Distribution") // Deprecated`
- L519 _macro_ `#define DATASMITH_AREALIGHTTYPE TEXT("LightType")`
- L522 _macro_ `#define DATASMITH_POSTPRODUCTIONNAME TEXT("Post")` — POSTPRODUCTION
- L523 _macro_ `#define DATASMITH_POSTPRODUCTIONTEMP TEXT("Temperature")`
- L524 _macro_ `#define DATASMITH_POSTPRODUCTIONCOLOR TEXT("Color")`
- L525 _macro_ `#define DATASMITH_POSTPRODUCTIONDISTANCE TEXT("Distance")`
- L526 _macro_ `#define DATASMITH_POSTPRODUCTIONVIGNETTE TEXT("Vignette")`
- L527 _macro_ `#define DATASMITH_POSTPRODUCTIONSATURATION TEXT("Saturation")`
- L528 _macro_ `#define DATASMITH_POSTPRODUCTIONCAMERAISO TEXT("CameraISO")`
- L529 _macro_ `#define DATASMITH_POSTPRODUCTIONSHUTTERSPEED TEXT("ShutterSpeed")`
- L532 _macro_ `#define DATASMITH_CAMERANAME TEXT("Camera")` — CAMERAS
- L533 _macro_ `#define DATASMITH_SENSORWIDTH TEXT("SensorWidth")`
- L534 _macro_ `#define DATASMITH_SENSORASPECT TEXT("SensorAspectRatio")`
- L535 _macro_ `#define DATASMITH_DEPTHOFFIELD TEXT("DepthOfField")`
- L536 _macro_ `#define DATASMITH_FOCUSDISTANCE TEXT("FocusDistance")`
- L537 _macro_ `#define DATASMITH_FSTOP TEXT("FStop")`
- L538 _macro_ `#define DATASMITH_FOCALLENGTH TEXT("FocalLength")`
- L539 _macro_ `#define DATASMITH_LOOKAT TEXT("LookAt")`
- L540 _macro_ `#define DATASMITH_LOOKATROLL TEXT("LookAtRollAllowed")`
- L543 _macro_ `#define DATASMITH_CUSTOMACTORNAME TEXT("CustomActor")` — CUSTOM ACTOR
- L544 _macro_ `#define DATASMITH_CUSTOMACTORPATHNAME TEXT("PathName")`
- L547 _macro_ `#define DATASMITH_DECALACTORNAME TEXT("DecalActor")` — DECAL ACTOR
- L550 _macro_ `#define DATASMITH_LANDSCAPENAME TEXT("Landscape")` — LANDSCAPE
- L551 _macro_ `#define DATASMITH_HEIGHTMAPNAME TEXT("Heightmap")`
- L552 _macro_ `#define DATASMITH_PATHNAME TEXT("PathName")`
- L555 _macro_ `#define DATASMITH_POSTPROCESSVOLUME TEXT("PostProcessVolume")` — POST PROCESS VOLUME
- L556 _macro_ `#define DATASMITH_POSTPROCESSVOLUME_UNBOUND TEXT("Unbound")`
- L559 _macro_ `#define DATASMITH_METADATANAME TEXT("MetaData")` — METADATA
- L560 _macro_ `#define DATASMITH_REFERENCENAME TEXT("reference")`
- L563 _macro_ `#define DATASMITH_KEYVALUEPROPERTYNAME TEXT("KeyValueProperty")` — KEY-VALUE
- L566 _macro_ `#define DATASMITH_TEXTUREMODE TEXT("TextureMode")` — TEXTURES
- L567 _macro_ `#define DATASMITH_TEXTURERESIZE TEXT("AllowResize")`
- L570 _macro_ `#define DATASMITH_SHADERNAME TEXT("Shader")` — MATERIALS
- L571 _macro_ `#define DATASMITH_MATERIALNAME TEXT("Material")`
- L572 _macro_ `#define DATASMITH_PARENTMATERIALLABEL TEXT("ParentLabel")`
- L573 _macro_ `#define DATASMITH_UEPBRMATERIALNAME TEXT("UEPbrMaterial")`
- L575 _macro_ `#define DATASMITH_MATERIALINSTANCENAME TEXT("MaterialInstance")`
- L576 _macro_ `#define DATASMITH_MATERIALINSTANCETYPE TEXT("Type")`
- L577 _macro_ `#define DATASMITH_MATERIALINSTANCEQUALITY TEXT("Quality")`
- L578 _macro_ `#define DATASMITH_MATERIALINSTANCEPATHNAME TEXT("PathName")`
- L580 _macro_ `#define DATASMITH_TEXTURENAME TEXT("Texture")`
- L581 _macro_ `#define DATASMITH_TEXTURECOMPNAME TEXT("Texturecomp")`
- L582 _macro_ `#define DATASMITH_COLORNAME TEXT("Color")`
- L583 _macro_ `#define DATASMITH_MASKNAME TEXT("Mask")`
- L584 _macro_ `#define DATASMITH_MASKCOLOR TEXT("MaskColor")`
- L585 _macro_ `#define DATASMITH_MASKCOMPNAME TEXT("Maskcomp")`
- L586 _macro_ `#define DATASMITH_VALUE1NAME TEXT("Value1")`
- L587 _macro_ `#define DATASMITH_VALUE2NAME TEXT("Value2")`
- L588 _macro_ `#define DATASMITH_ENVIRONMENTNAME TEXT("Environment")`
- L590 _macro_ `#define DATASMITH_DIFFUSETEXNAME TEXT("Diffuse")`
- L591 _macro_ `#define DATASMITH_DIFFUSECOLNAME TEXT("Diffusecolor")`
- L592 _macro_ `#define DATASMITH_DIFFUSECOMPNAME TEXT("Diffusecomp")`
- L594 _macro_ `#define DATASMITH_REFLETEXNAME TEXT("Reflectance")`
- L595 _macro_ `#define DATASMITH_REFLECOLNAME TEXT("Reflectancecolor")`
- L596 _macro_ `#define DATASMITH_REFLECOMPNAME TEXT("Reflectancecomp")`
- L598 _macro_ `#define DATASMITH_ROUGHNESSTEXNAME TEXT("Roughness")`
- L599 _macro_ `#define DATASMITH_ROUGHNESSVALUENAME TEXT("Roughnessval")`
- L600 _macro_ `#define DATASMITH_ROUGHNESSCOMPNAME TEXT("Roughnesscomp")`
- L602 _macro_ `#define DATASMITH_CLIPTEXNAME TEXT("Clip")`
- L603 _macro_ `#define DATASMITH_CLIPCOMPNAME TEXT("Clipcomp")`
- L605 _macro_ `#define DATASMITH_TRANSPTEXNAME TEXT("RefractionTransparency")`
- L606 _macro_ `#define DATASMITH_TRANSPCOLNAME TEXT("RefractionTransparencycolor")`
- L607 _macro_ `#define DATASMITH_TRANSPCOMPNAME TEXT("RefractionTransparencycomp")`
- L609 _macro_ `#define DATASMITH_NORMALTEXNAME TEXT("Normal")`
- L610 _macro_ `#define DATASMITH_NORMALCOMPNAME TEXT("Normalcomp")`
- L611 _macro_ `#define DATASMITH_BUMPTEXNAME TEXT("Bump")`
- L612 _macro_ `#define DATASMITH_BUMPCOMPNAME TEXT("Bumpcomp")`
- L614 _macro_ `#define DATASMITH_USEMATERIALATTRIBUTESNAME TEXT("UseMaterialAttributes")`
- L615 _macro_ `#define DATASMITH_FUNCTIONLYVALUENAME TEXT("FunctionOnly")`
- L616 _macro_ `#define DATASMITH_TWOSIDEDVALUENAME TEXT("TwoSided")`
- L617 _macro_ `#define DATASMITH_BUMPVALUENAME TEXT("Bumpval")`
- L618 _macro_ `#define DATASMITH_IORVALUENAME TEXT("IOR")`
- L619 _macro_ `#define DATASMITH_IORKVALUENAME TEXT("IORk")`
- L620 _macro_ `#define DATASMITH_REFRAIORVALUENAME TEXT("IORRefraction")`
- L622 _macro_ `#define DATASMITH_METALTEXNAME TEXT("Metal")`
- L623 _macro_ `#define DATASMITH_METALVALUENAME TEXT("Metalval")`
- L624 _macro_ `#define DATASMITH_METALCOMPNAME TEXT("Metalcomp")`
- L626 _macro_ `#define DATASMITH_EMITTEXNAME TEXT("Emittance")`
- L627 _macro_ `#define DATASMITH_EMITCOLNAME TEXT("Emittancecolor")`
- L628 _macro_ `#define DATASMITH_EMITCOMPNAME TEXT("Emittancecomp")`
- L629 _macro_ `#define DATASMITH_EMITTEMPNAME TEXT("Emittancetemp")`
- L630 _macro_ `#define DATASMITH_EMITVALUENAME TEXT("Emittanceval")`
- L631 _macro_ `#define DATASMITH_EMITONLYVALUENAME TEXT("EmitOnly")`
- L632 _macro_ `#define DATASMITH_DYNAMICEMISSIVE TEXT("DynamicEmissive")`
- L633 _macro_ `#define DATASMITH_SHADERUSAGE TEXT("ShaderUsage")`
- L635 _macro_ `#define DATASMITH_WEIGHTTEXNAME TEXT("Weight")`
- L636 _macro_ `#define DATASMITH_WEIGHTCOLNAME TEXT("Weightcolor")`
- L637 _macro_ `#define DATASMITH_WEIGHTCOMPNAME TEXT("Weightcomp")`
- L638 _macro_ `#define DATASMITH_WEIGHTVALUENAME TEXT("Weightval")`
- L640 _macro_ `#define DATASMITH_STACKLAYER TEXT("Stacked")`
- L641 _macro_ `#define DATASMITH_BLENDMODE TEXT("Blendmode")`
- L642 _macro_ `#define DATASMITH_OPACITYMASKCLIPVALUE TEXT("OpacityMaskClipValue")`
- L643 _macro_ `#define DATASMITH_SHADINGMODEL TEXT("ShadingModel")`
- L644 _macro_ `#define DATASMITH_TRANSLUCENCYLIGHTINGMODE TEXT("TranslucencyLightingMode")`
- L646 _macro_ `#define DATASMITH_ENVILLUMINATIONMAP TEXT("Illuminate")`
- L648 _macro_ `#define DATASMITH_DECALMATERIALNAME TEXT("DecalMaterial")`
- L658 _variable_ `static const TCHAR* DatasmithActorMobilityTypeStrings[] = { TEXT("Static"), TEXT("Stationar`

### `Source/Runtime/Datasmith/DatasmithCore/Public/DatasmithMaterialElements.h` (Public)


#### class `IDatasmithExpressionInput`  
`class IDatasmithExpressionInput : public IDatasmithElement`  
_L8-20_
- inherits: `IDatasmithElement`
- L12 _public function_ `const TCHAR* GetInputName() const` — `UE_DEPRECATED(4.27, "IDatasmithExpressionInput now derive from IDatasmithElement, please use GetName() instead")`
- L14 _public prototype_ `virtual IDatasmithMaterialExpression* GetExpression() = 0;`
- L15 _public prototype_ `virtual const IDatasmithMaterialExpression* GetExpression() const = 0;`
- L16 _public prototype_ `virtual void SetExpression( IDatasmithMaterialExpression* InExpression ) = 0;`
- L18 _public prototype_ `virtual int32 GetOutputIndex() const = 0;`
- L19 _public prototype_ `virtual void SetOutputIndex( int32 InOutputIndex ) = 0;`

#### class `IDatasmithExpressionOutput`  
`class IDatasmithExpressionOutput : public IDatasmithElement`  
_L22-31_
- inherits: `IDatasmithElement`
- L25 _public prototype_ `virtual ~IDatasmithExpressionOutput() = default;`
- L28 _public function_ `const TCHAR* GetOutputName() const` — `UE_DEPRECATED(4.27, "IDatasmithExpressionOutput now derive from IDatasmithElement, please use GetName() instead")`
- L30 _public function_ `void SetOutputName( const TCHAR* InOutputName )` — `UE_DEPRECATED(4.27, "IDatasmithExpressionOutput now derive from IDatasmithElement, please use SetName() instead")`

#### class `IDatasmithMaterialExpression`  
`class IDatasmithMaterialExpression : public IDatasmithElement`  
_L37-69_
- inherits: `IDatasmithElement`
- desc: Base class for representing an expression in the material graph of a IDatasmithUEPbrMaterial. Setting a name to the expression is optional but allows to automatically create material instances during the import, which is faster and more optimal.
- L40 _public prototype_ `virtual ~IDatasmithMaterialExpression() = default;`
- L46 _public function_ `EDatasmithMaterialExpressionType GetType() const` — `UE_DEPRECATED(4.27, "Deprecated, please use GetExpressionType() instead")`
- L47 _public prototype_ `virtual EDatasmithMaterialExpressionType GetExpressionType() const = 0;`
- L49 _public function_ `bool IsA( const EDatasmithMaterialExpressionType ExpressionType ) const` — `UE_DEPRECATED(4.27, "IDatasmithMaterialExpression now derive from IDatasmithElement, please use IsSubType() or GetExpressionType() instead")`
- L51 _public prototype_ `virtual bool IsSubType( const EDatasmithMaterialExpressionType ExpressionType ) const = 0;`
- L54 _public prototype_ `virtual void ConnectExpression( IDatasmithExpressionInput& ExpressionInput ) = 0;` — Connects the default output to an expression input
- L57 _public prototype_ `virtual void ConnectExpression( IDatasmithExpressionInput& ExpressionInput, int32 OutputIndex ) = 0;` — Connects a specific output to an expression input
- L59 _public prototype_ `virtual int32 GetInputCount() const = 0;`
- L60 _public prototype_ `virtual IDatasmithExpressionInput* GetInput( int32 Index ) = 0;`
- L61 _public prototype_ `virtual const IDatasmithExpressionInput* GetInput( int32 Index ) const = 0;`
- L64 _public prototype_ `virtual int32 GetDefaultOutputIndex() const = 0;` — The output index to use by default for this expression when connecting it to other inputs.
- L65 _public prototype_ `virtual void SetDefaultOutputIndex( int32 OutputIndex ) = 0;`
- L68 _public prototype_ `virtual void ResetExpression() = 0;` — Reset the expression to its default values, and disconnect input expressions

#### class `IDatasmithExpressionParameter`  
`class IDatasmithExpressionParameter : public IDatasmithMaterialExpression`  
_L71-78_
- inherits: `IDatasmithMaterialExpression`
- L74 _public prototype_ `virtual ~IDatasmithExpressionParameter() = default;`
- L76 _public prototype_ `virtual const TCHAR* GetGroupName() const = 0;`
- L77 _public prototype_ `virtual void SetGroupName( const TCHAR* InGroupName ) = 0;`

#### class `IDatasmithMaterialExpressionBool`  
`class IDatasmithMaterialExpressionBool : public IDatasmithExpressionParameter`  
_L83-88_
- inherits: `IDatasmithExpressionParameter`
- desc: Represents a UMaterialExpressionStaticBoolParameter
- L86 _public prototype_ `virtual bool& GetBool() = 0;`
- L87 _public prototype_ `virtual const bool& GetBool() const = 0;`

#### class `IDatasmithMaterialExpressionColor`  
`class IDatasmithMaterialExpressionColor : public IDatasmithExpressionParameter`  
_L90-95_
- inherits: `IDatasmithExpressionParameter`
- L93 _public prototype_ `virtual FLinearColor& GetColor() = 0;`
- L94 _public prototype_ `virtual const FLinearColor& GetColor() const = 0;`

#### class `IDatasmithMaterialExpressionScalar`  
`class IDatasmithMaterialExpressionScalar : public IDatasmithExpressionParameter`  
_L97-102_
- inherits: `IDatasmithExpressionParameter`
- L100 _public prototype_ `virtual float& GetScalar() = 0;`
- L101 _public prototype_ `virtual const float& GetScalar() const = 0;`

#### class `IDatasmithMaterialExpressionTexture`  
`class IDatasmithMaterialExpressionTexture : public IDatasmithExpressionParameter`  
_L104-124_
- inherits: `IDatasmithExpressionParameter`
- L107 _public prototype_ `virtual const TCHAR* GetTexturePathName() const = 0;`
- L108 _public prototype_ `virtual void SetTexturePathName( const TCHAR* InTexturePathName ) = 0;`
- L113 _public prototype_ `virtual IDatasmithExpressionInput& GetInputCoordinate() = 0;` — Inputs
- L114 _public prototype_ `virtual const IDatasmithExpressionInput& GetInputCoordinate() const = 0;`

#### class `IDatasmithMaterialExpressionTextureCoordinate`  
`class IDatasmithMaterialExpressionTextureCoordinate : public IDatasmithMaterialExpression`  
_L126-137_
- inherits: `IDatasmithMaterialExpression`
- L129 _public prototype_ `virtual int32 GetCoordinateIndex() const = 0;`
- L130 _public prototype_ `virtual void SetCoordinateIndex( int32 InCoordinateIndex ) = 0;`
- L132 _public prototype_ `virtual float GetUTiling() const = 0;`
- L133 _public prototype_ `virtual void SetUTiling( float InUTiling ) = 0;`
- L135 _public prototype_ `virtual float GetVTiling() const = 0;`
- L136 _public prototype_ `virtual void SetVTiling( float InVTiling ) = 0;`

#### class `IDatasmithMaterialExpressionFlattenNormal`  
`class IDatasmithMaterialExpressionFlattenNormal : public IDatasmithMaterialExpression`  
_L139-155_
- inherits: `IDatasmithMaterialExpression`
- L145 _public prototype_ `virtual IDatasmithExpressionInput& GetNormal() = 0;` — Inputs
- L146 _public prototype_ `virtual const IDatasmithExpressionInput& GetNormal() const = 0;`
- L148 _public prototype_ `virtual IDatasmithExpressionInput& GetFlatness() = 0;`
- L149 _public prototype_ `virtual const IDatasmithExpressionInput& GetFlatness() const = 0;`

#### class `IDatasmithMaterialExpressionCustom`  
`class IDatasmithMaterialExpressionCustom : public IDatasmithMaterialExpression`  
_L158-181_
- inherits: `IDatasmithMaterialExpression`
- desc: see UMaterialExpressionCustom
- L161 _public prototype_ `virtual void SetCode(const TCHAR* InCode) = 0;`
- L162 _public prototype_ `virtual const TCHAR* GetCode() const = 0;`
- L164 _public prototype_ `virtual void SetOutputType(EDatasmithShaderDataType InOutputType) = 0;`
- L165 _public prototype_ `virtual EDatasmithShaderDataType GetOutputType() const = 0;`
- L167 _public prototype_ `virtual void SetDescription(const TCHAR* InDescription) = 0;`
- L168 _public prototype_ `virtual const TCHAR* GetDescription() const = 0;`
- L170 _public prototype_ `virtual int32 GetIncludeFilePathCount() const = 0;`
- L171 _public prototype_ `virtual void AddIncludeFilePath(const TCHAR* Path) = 0;`
- L172 _public prototype_ `virtual const TCHAR* GetIncludeFilePath(int32 Index) const = 0;`
- L174 _public prototype_ `virtual int32 GetAdditionalDefineCount() const = 0;`
- L175 _public prototype_ `virtual void AddAdditionalDefine(const TCHAR* Define) = 0;`
- L176 _public prototype_ `virtual const TCHAR* GetAdditionalDefine(int32 Index) const = 0;`
- L178 _public prototype_ `virtual int32 GetArgumentNameCount() const = 0;`
- L179 _public prototype_ `virtual void SetArgumentName(int32 ArgIndex, const TCHAR* ArgName) = 0;`
- L180 _public prototype_ `virtual const TCHAR* GetArgumentName(int32 ArgIndex) const = 0;`

#### class `IDatasmithMaterialExpressionGeneric`  
`class IDatasmithMaterialExpressionGeneric : public IDatasmithMaterialExpression`  
_L183-202_
- inherits: `IDatasmithMaterialExpression`
- L186 _public prototype_ `virtual void SetExpressionName( const TCHAR* InExpressionName ) = 0;`
- L187 _public prototype_ `virtual const TCHAR* GetExpressionName() const = 0;`
- L190 _public prototype_ `virtual int32 GetPropertiesCount() const = 0;` — Get the total amount of properties in this expression
- L193 _public prototype_ `virtual const TSharedPtr< IDatasmithKeyValueProperty >& GetProperty(int32 i) const = 0;` — Get the property i-th of this expression
- L194 _public prototype_ `virtual TSharedPtr< IDatasmithKeyValueProperty >& GetProperty(int32 i) = 0;`
- L197 _public prototype_ `virtual const TSharedPtr< IDatasmithKeyValueProperty >& GetPropertyByName(const TCHAR* Name) const = 0;` — Get a property by its name if it exists
- L198 _public prototype_ `virtual TSharedPtr< IDatasmithKeyValueProperty >& GetPropertyByName(const TCHAR* Name) = 0;`
- L201 _public prototype_ `virtual void AddProperty( const TSharedPtr< IDatasmithKeyValueProperty >& Property ) = 0;` — Add a property to this expression

#### class `IDatasmithMaterialExpressionFunctionCall`  
`class IDatasmithMaterialExpressionFunctionCall : public IDatasmithMaterialExpression`  
_L204-210_
- inherits: `IDatasmithMaterialExpression`
- L207 _public prototype_ `virtual void SetFunctionPathName( const TCHAR* InFunctionPathName ) = 0;`
- L208 _public prototype_ `virtual const TCHAR* GetFunctionPathName() const = 0;`

#### class `IDatasmithUEPbrMaterialElement`  
`class IDatasmithUEPbrMaterialElement : public IDatasmithBaseMaterialElement`  
_L212-274_
- inherits: `IDatasmithBaseMaterialElement`
- L215 _public prototype_ `virtual IDatasmithExpressionInput& GetBaseColor() = 0;`
- L216 _public prototype_ `virtual IDatasmithExpressionInput& GetMetallic() = 0;`
- L217 _public prototype_ `virtual IDatasmithExpressionInput& GetSpecular() = 0;`
- L218 _public prototype_ `virtual IDatasmithExpressionInput& GetRoughness() = 0;`
- L219 _public prototype_ `virtual IDatasmithExpressionInput& GetEmissiveColor() = 0;`
- L220 _public prototype_ `virtual IDatasmithExpressionInput& GetOpacity() = 0;`
- L221 _public prototype_ `virtual IDatasmithExpressionInput& GetNormal() = 0;`
- L222 _public prototype_ `virtual IDatasmithExpressionInput& GetRefraction() = 0;`
- L223 _public prototype_ `virtual IDatasmithExpressionInput& GetAmbientOcclusion() = 0;`
- L224 _public prototype_ `virtual IDatasmithExpressionInput& GetClearCoat() = 0;`
- L225 _public prototype_ `virtual IDatasmithExpressionInput& GetClearCoatRoughness() = 0;`
- L226 _public prototype_ `virtual IDatasmithExpressionInput& GetWorldPositionOffset() = 0;`
- L227 _public prototype_ `virtual IDatasmithExpressionInput& GetMaterialAttributes() = 0;`
- L230 _public prototype_ `virtual int GetBlendMode() const = 0;` — InBlendMode must match the values of EBlendMode from EngineTypes.h
- L231 _public prototype_ `virtual void SetBlendMode( int InBlendMode ) = 0;`
- L233 _public prototype_ `virtual bool GetTwoSided() const = 0;`
- L234 _public prototype_ `virtual void SetTwoSided( bool bTwoSided ) = 0;`
- L236 _public prototype_ `virtual bool GetIsThinSurface() const = 0;`
- L237 _public prototype_ `virtual void SetIsThinSurface(bool bIsThinSurface) = 0;`
- L239 _public prototype_ `virtual bool GetUseMaterialAttributes() const = 0;`
- L240 _public prototype_ `virtual void SetUseMaterialAttributes( bool bInUseMaterialAttributes ) = 0;`
- L243 _public prototype_ `virtual bool GetMaterialFunctionOnly() const = 0;` — If a material is only referenced by other materials then it is only used as a material function and there is no need to instantiate it.
- L244 _public prototype_ `virtual void SetMaterialFunctionOnly(bool bInMaterialFunctionOnly) = 0;`
- L246 _public prototype_ `virtual float GetOpacityMaskClipValue() const = 0;`
- L247 _public prototype_ `virtual void SetOpacityMaskClipValue(float InClipValue) = 0;`
- L249 _public prototype_ `virtual int GetTranslucencyLightingMode() const = 0;`
- L251 _public prototype_ `virtual void SetTranslucencyLightingMode(int InMode) = 0;` — InMode must match the values of ETranslucencyLightingMode from EngineTypes.h
- L253 _public prototype_ `virtual int32 GetExpressionsCount() const = 0;`
- L254 _public prototype_ `virtual IDatasmithMaterialExpression* GetExpression( int32 Index ) = 0;`
- L255 _public prototype_ `virtual int32 GetExpressionIndex( const IDatasmithMaterialExpression* Expression ) const = 0;`
- L257 _public prototype_ `virtual IDatasmithMaterialExpression* AddMaterialExpression( const EDatasmithMaterialExpressionType ExpressionType ) = 0;`
- L260 _public function_ `template< typename T > T* AddMaterialExpression()`
- L266 _public prototype_ `virtual void ResetExpressionGraph( bool bRemoveAllExpressions ) = 0;` — Reset all expression to their default values and remove all connections
- L269 _public prototype_ `virtual void SetParentLabel( const TCHAR* InParentLabel ) = 0;` — If a parent material is generated from this material, this will be its label. If none, the instance and the parent will have the same label.
- L270 _public prototype_ `virtual const TCHAR* GetParentLabel() const = 0;`
- L272 _public prototype_ `virtual void SetShadingModel( const EDatasmithShadingModel InShadingModel ) = 0;`
- L273 _public prototype_ `virtual EDatasmithShadingModel GetShadingModel() const = 0;`
- L277 _function_ `template<> inline IDatasmithMaterialExpressionBool* IDatasmithUEPbrMaterialElement::AddMaterialExpression< IDatasmithMaterialExpressionBool >()`
- L283 _function_ `template<> inline IDatasmithMaterialExpressionColor* IDatasmithUEPbrMaterialElement::AddMaterialExpression< IDatasmithMaterialExpressionColor >()`
- L289 _function_ `template<> inline IDatasmithMaterialExpressionFlattenNormal* IDatasmithUEPbrMaterialElement::AddMaterialExpression< IDatasmithMaterialExpressionFlattenNormal >()`
- L295 _function_ `template<> inline IDatasmithMaterialExpressionFunctionCall* IDatasmithUEPbrMaterialElement::AddMaterialExpression< IDatasmithMaterialExpressionFunctionCall >()`
- L301 _function_ `template<> inline IDatasmithMaterialExpressionGeneric* IDatasmithUEPbrMaterialElement::AddMaterialExpression< IDatasmithMaterialExpressionGeneric >()`
- L307 _function_ `template<> inline IDatasmithMaterialExpressionScalar* IDatasmithUEPbrMaterialElement::AddMaterialExpression< IDatasmithMaterialExpressionScalar >()`
- L313 _function_ `template<> inline IDatasmithMaterialExpressionTexture* IDatasmithUEPbrMaterialElement::AddMaterialExpression< IDatasmithMaterialExpressionTexture >()`
- L319 _function_ `template<> inline IDatasmithMaterialExpressionTextureCoordinate* IDatasmithUEPbrMaterialElement::AddMaterialExpression< IDatasmithMaterialExpressionTextureCoordinate >()`
- L325 _function_ `template<> inline IDatasmithMaterialExpressionCustom* IDatasmithUEPbrMaterialElement::AddMaterialExpression< IDatasmithMaterialExpressionCustom >()`

### `Source/Runtime/Datasmith/DatasmithCore/Public/DatasmithMaterialsUtils.h` (Public)


#### struct `DatasmithMaterialsUtils::FUVEditParameters`  
`struct FUVEditParameters`  
_L20-53_
- L22 _public function_ `FUVEditParameters() : UVOffset( FVector2D::ZeroVector ) , UVTiling( FVector2D::UnitVector ) , RotationPivot( 0.f, 1.f, 0.f ) , RotationAngle( 0.f ) , ChannelIndex( 0 ) , bIsUsingRealWorldScale( false ) , bMirrorU( false ) , bMirrorV( false )`
- L35 _public member_ `FVector2D UVOffset;` — UV space has its origin at top-left, with U going left-to-right, V top-to-bottom
- L36 _public member_ `FVector2D UVTiling;`
- L39 _public member_ `FVector RotationPivot;` — W rotation center
- L42 _public member_ `float RotationAngle;` — W rotation in degrees (rotation is counterclockwise)
- L45 _public member_ `uint8 ChannelIndex;` — UV channel to use
- L48 _public member_ `bool bIsUsingRealWorldScale;` — Enable "Real-World Scale" behavior as in 3ds max
- L51 _public member_ `bool bMirrorU;` — Enable mirroring of texture in U and V
- L52 _public member_ `bool bMirrorV;`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace DatasmithMaterialsUtils`
- L63 _prototype_ `IDatasmithMaterialExpressionTexture* CreateTextureExpression( const TSharedRef< IDatasmithUEPbrMaterialElement >& MaterialElement, const TCHAR* ParameterName, const TCHAR* TextureMapPath, const FUVEditParameters& UVParameters );` (scope `DatasmithMaterialsUtils`) — Generate material expressions on a given DatasmithUEPbrMaterialElement to output a texture with UV settings applied to it @param MaterialElement		The UEPbrMaterialElement on which to create the material expressions @param ParameterName			The display name for the Texture expression @param TextureMapPath		The texture to use for the Texture expression @param UVParameters			The UVEditParameters to apply @return						Texture expression with UVEdit applied to it; nullptr if no TextureMapPath is specified
- L76 _prototype_ `IDatasmithMaterialExpression* CreateWeightedMaterialExpression( const TSharedRef< IDatasmithUEPbrMaterialElement >& MaterialElement, const TCHAR* ParameterName, TOptional< FLinearColor > Color, TOptional< float > Scalar, IDatasmithMaterialExpression* Expression, float Weight, EDatasmithTextureMode TextureMode = EDatasmithTextureMode::Diffuse );` (scope `DatasmithMaterialsUtils`) — Generate material expressions on a given DatasmithUEPbrMaterialElement that output a color or scalar interpolated with a MaterialExpression @param MaterialElement		The UEPbrMaterialElement on which to create the material expressions @param ParameterName			The display name for the Color or Scalar input @param Color					The color to interpolate the Expression with. If no color is given, use the scalar @param Scalar				The scalar to interpolate the Expression with. If no color or scalar are given, use the Expression only @param Expression			The MaterialExpression to interpolate the Color or Scalar with @param Weight				The weight of the Expression in the interpolation @param TextureMode			The TextureMode of the Expression to determine if it requires normal flattening (bump and normal mode) or interpolation @return						Material expression that outputs a Color or Scalar interpolated with Expression; nullptr if no Color, Scalar or Expression are given
- L78 _prototype_ `FLinearColor TemperatureToColor(float Kelvin);` (scope `DatasmithMaterialsUtils`)

### `Source/Runtime/Datasmith/DatasmithCore/Public/DatasmithMesh.h` (Public)


#### class `FDatasmithMesh`  
`class FDatasmithMesh`  
_L13-234_
- L16 _public prototype_ `FDatasmithMesh();`
- L17 _public prototype_ `~FDatasmithMesh();`
- L19 _public prototype_ `FDatasmithMesh( const FDatasmithMesh& Other );`
- L20 _public prototype_ `FDatasmithMesh( FDatasmithMesh&& Other );`
- L22 _public prototype_ `FDatasmithMesh& operator=( const FDatasmithMesh& Other );`
- L23 _public prototype_ `FDatasmithMesh& operator=( FDatasmithMesh&& Other );`
- L26 _public prototype_ `FMD5Hash CalculateHash() const;` — Calculate mesh data hash(doesn't include name)
- L28 _public prototype_ `void SetName(const TCHAR* InName);`
- L29 _public prototype_ `const TCHAR* GetName() const;`
- L35 _public prototype_ `void SetFacesCount(int32 NumFaces);` — Setting the amount of faces is mandatory before filling the array
- L38 _public prototype_ `int32 GetFacesCount() const;` — Retrieves the amount of faces
- L48 _public prototype_ `void SetFace(int32 Index, int32 Vertex1, int32 Vertex2, int32 Vertex3, int32 MaterialId = 0);` — Sets the geometry of the face @param Index		value to choose the face that will be affected @param Vertex1	Index of the first geometric vertex that defines this face @param Vertex2	Index of the second geometric vertex that defines this face @param Vertex3	Index of the third geometric vertex that defines this face
- L49 _public prototype_ `void GetFace(int32 Index, int32& Vertex1, int32& Vertex2, int32& Vertex3, int32& MaterialId) const;`
- L57 _public prototype_ `void SetFaceSmoothingMask(int32 Index, uint32 SmoothingMask);` — Sets the smoothing mask of the face @param Index			Index of the face that will be affected @param SmoothingMask	32 bits mask, 0 means no smoothing
- L64 _public prototype_ `uint32 GetFaceSmoothingMask(int32 Index) const;` — Gets the smoothing mask of a face @param Index		Index of the face to retrieve the smoothing mask from
- L66 _public prototype_ `int32 GetMaterialsCount() const;`
- L67 _public prototype_ `bool IsMaterialIdUsed(int32 MaterialId) const;`
- L73 _public prototype_ `void SetVerticesCount(int32 NumVerts);` — Setting the amount of geometric vertices is mandatory before filling the array
- L76 _public prototype_ `int32 GetVerticesCount() const;` — Retrieves the amount of geometric vertices. The validity of the vertex data is not guaranteed
- L86 _public prototype_ `void SetVertex(int32 Index, float X, float Y, float Z);` — Sets the 3d position of the vertex @param Index value to choose the vertex that will be affected @x position on the x axis @y position on the y axis @z position on the z axis
- L87 _public prototype_ `FVector3f GetVertex(int32 Index) const;`
- L100 _public prototype_ `void SetNormal(int32 Index, float X, float Y, float Z);` — Sets the 3d normal @param Index value to choose the normal that will be affected @x direction on the x axis @y direction on the y axis @z direction on the z axis
- L101 _public prototype_ `FVector3f GetNormal(int32 Index) const;`
- L111 _public prototype_ `void SetUVChannelsCount(int32 ChannelCount);` — Sets the amount of UV channels on this mesh @param ChannelCount	The number of UV channels
- L116 _public prototype_ `void AddUVChannel();` — Add a UV channel at the end
- L121 _public prototype_ `void RemoveUVChannel();` — Remove the last UV channel
- L124 _public prototype_ `int32 GetUVChannelsCount() const;` — Gets the amount of UV channels on this mesh
- L132 _public prototype_ `void SetUVCount(int32 Channel, int32 NumVerts);` — Setting the amount of UV coordinates on the channel is mandatory before filling the array @param Channel	The channel to set the numbers of UVs @param NumVerts	The number of UVs in the channel
- L135 _public prototype_ `int32 GetUVCount(int32 Channel) const;` — Retrieves the amount of UV coordinates on the channel. The validity of the vertex data is not guaranteed
- L144 _public prototype_ `void SetUV(int32 Channel, int32 Index, double U, double V);` — Sets the 2d position of the UV vertex for the first uv mapping @param Index	Value to choose the vertex that will be affected @param U		Horizontal coordinate @param V		Vertical coordinate
- L149 _public prototype_ `uint32 GetHashForUVChannel(int32 Channel) const;` — Get the hash for a uv channel
- L157 _public prototype_ `FVector2D GetUV(int32 Channel, int32 Index) const;` — Gets the UV coordinates for a channel @param Channel	The channel we want to retrieve the UVs from @param Index		The UV coordinates to retrieve
- L168 _public prototype_ `void SetFaceUV(int32 Index, int32 Channel, int32 Vertex1, int32 Vertex2, int32 Vertex3);` — Sets the channel UV coordinates of the face @param Index		Index of the face that will be affected @param Channel	UV channel, starting at 0 @param Vertex1	Index of the first uv vertex that defines this face @param Vertex2	Index of the second uv vertex that defines this face @param Vertex3	Index of the third uv vertex that defines this face
- L179 _public prototype_ `void GetFaceUV(int32 Index, int32 Channel, int32& Vertex1, int32& Vertex2, int32& Vertex3) const;` — Gets the UV coordinates of the vertices of a face @param Index		Index of the face to retrieve the UVs from @param Channel	UV channel, starting at 0 @param Vertex1	Index of the first uv vertex that defines this face @param Vertex2	Index of the second uv vertex that defines this face @param Vertex3	Index of the third uv vertex that defines this face
- L182 _public prototype_ `int32 GetVertexColorCount() const;` — Get the number of vertex color
- L190 _public prototype_ `void SetVertexColor(int32 Index, const FColor& Color);` — Set a vertex color @param Index		Index of the vertex color that will be affected @param Color		The color for the vertex
- L197 _public prototype_ `FColor GetVertexColor(int32 Index) const;` — Get the color for a vertex @param Index		Index of the vertex color to retrieve
- L203 _public prototype_ `void SetLightmapSourceUVChannel(int32 Channel);` — Sets the UV channel that will be used as the source UVs for lightmap UVs generation at import, defaults to channel 0. Will be overwritten during Mesh export if we choose to generate the lightmap source UVs.
- L206 _public prototype_ `int32 GetLightmapSourceUVChannel() const;` — Gets the UV channel that will be used for lightmap UVs generation at import
- L213 _public prototype_ `void AddLOD( const FDatasmithMesh& InLODMesh );` — Adds a LOD mesh to this base LOD mesh
- L214 _public prototype_ `void AddLOD( FDatasmithMesh&& InLODMesh );`
- L215 _public prototype_ `int32 GetLODsCount() const;`
- L218 _public prototype_ `FDatasmithMesh* GetLOD( int32 Index );` — Gets the FDatasmithMesh LOD at the given index, if the index is invalid returns nullptr
- L219 _public prototype_ `const FDatasmithMesh* GetLOD( int32 Index ) const;`
- L225 _public prototype_ `float ComputeArea() const;` — Returns the total surface area
- L228 _public prototype_ `FBox3f GetExtents() const;` — Returns the bounding box containing all vertices of this mesh
- L233 _private member_ `FDatasmithMeshImpl* Impl;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API DATASMITHCORE_API`

### `Source/Runtime/Datasmith/DatasmithCore/Public/DatasmithMeshSerialization.h` (Public)


#### struct `FDatasmithMeshModels`  
`struct FDatasmithMeshModels`  
_L18-25_
- L20 _public member_ `FString MeshName;`
- L21 _public member_ `bool bIsCollisionMesh = false;`
- L22 _public member_ `TArray<FMeshDescription> SourceModels;`

#### struct `FDatasmithPackedMeshes`  
`struct FDatasmithPackedMeshes`  
_L27-32_
- L29 _public member_ `TArray<FDatasmithMeshModels> Meshes;`
- L31 _public prototype_ `FMD5Hash Serialize(FArchive& Ar, bool bSaveCompressed=true);`

#### struct `FDatasmithClothInfo`  
`struct UE_DEPRECATED(5.5, "The experimental Cloth importer is no longer supported.") FDatasmithClothInfo`  
_L39-43_
- L41 _public member_ `FDatasmithCloth Cloth;`

#### struct `FDatasmithPackedCloths`  
`struct UE_DEPRECATED(5.5, "The experimental Cloth importer is no longer supported.") FDatasmithPackedCloths`  
_L45-50_
- L47 _public member_ `TArray<FDatasmithClothInfo> ClothInfos;`
- L49 _public prototype_ `FMD5Hash Serialize(FArchive& Ar, bool bSaveCompressed=true);`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API DATASMITHCORE_API`
- L34 _prototype_ `FDatasmithPackedMeshes GetDatasmithMeshFromFile(const FString& MeshPath);`
- L53 _prototype_ `FDatasmithPackedCloths GetDatasmithClothFromFile(const FString& Path);` — `UE_DEPRECATED(5.5, "The experimental Cloth importer is no longer supported.")`

### `Source/Runtime/Datasmith/DatasmithCore/Public/DatasmithMeshUObject.h` (Public)


#### struct `FDatasmithMeshSourceModel`  
`struct FDatasmithMeshSourceModel`  
_L22-30_
- reflection: `USTRUCT()`
- L27 _public prototype_ `void SerializeBulkData(FArchive& Ar, UObject* Owner);`
- L29 _public member_ `FRawMeshBulkData RawMeshBulkData;`

#### class `UDatasmithMesh`  
`class UDatasmithMesh : public UObject`  
_L33-50_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L38 _public function_ `static const TCHAR* GetFileExtension()`
- L40 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L43 _public member_ `FString MeshName;` — `UPROPERTY()`
- L46 _public member_ `bool bIsCollisionMesh;` — `UPROPERTY()`
- L49 _public member_ `TArray< FDatasmithMeshSourceModel > SourceModels;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API DATASMITHCORE_API`

### `Source/Runtime/Datasmith/DatasmithCore/Public/DatasmithSceneFactory.h` (Public)


#### class `FDatasmithSceneFactory`  
`class FDatasmithSceneFactory`  
_L20-123_
- desc: Factory to create the scene elements used for the export and import process. The shared pointer returned is the only one existing at that time. Make sure to hang onto it until the scene element isn't needed anymore.
- L23 _public prototype_ `static TSharedPtr< IDatasmithElement > CreateElement( EDatasmithElementType InType, const TCHAR* InName );`
- L25 _public prototype_ `static TSharedPtr< IDatasmithElement > CreateElement( EDatasmithElementType InType, uint64 InSubType, const TCHAR* InName );`
- L27 _public prototype_ `static TSharedRef< IDatasmithActorElement > CreateActor( const TCHAR* InName );`
- L29 _public prototype_ `static TSharedRef< IDatasmithCameraActorElement > CreateCameraActor( const TCHAR* InName );`
- L31 _public prototype_ `static TSharedRef< IDatasmithCompositeTexture > CreateCompositeTexture();`
- L33 _public prototype_ `static TSharedRef< IDatasmithCustomActorElement > CreateCustomActor( const TCHAR* InName );`
- L35 _public prototype_ `static TSharedRef< IDatasmithLandscapeElement > CreateLandscape( const TCHAR* InName );`
- L37 _public prototype_ `static TSharedRef< IDatasmithPostProcessVolumeElement > CreatePostProcessVolume( const TCHAR* InName );`
- L39 _public prototype_ `static TSharedRef< IDatasmithEnvironmentElement > CreateEnvironment( const TCHAR* InName );`
- L41 _public prototype_ `static TSharedRef< IDatasmithPointLightElement > CreatePointLight( const TCHAR* InName );`
- L42 _public prototype_ `static TSharedRef< IDatasmithSpotLightElement > CreateSpotLight( const TCHAR* InName );`
- L43 _public prototype_ `static TSharedRef< IDatasmithDirectionalLightElement > CreateDirectionalLight( const TCHAR* InName );`
- L44 _public prototype_ `static TSharedRef< IDatasmithAreaLightElement > CreateAreaLight( const TCHAR* InName );`
- L45 _public prototype_ `static TSharedRef< IDatasmithLightmassPortalElement > CreateLightmassPortal( const TCHAR* InName );`
- L47 _public prototype_ `static TSharedRef< IDatasmithKeyValueProperty > CreateKeyValueProperty( const TCHAR* InName );`
- L49 _public prototype_ `static TSharedRef< IDatasmithMeshElement > CreateMesh( const TCHAR* InName );`
- L51 _public prototype_ `static TSharedRef< IDatasmithMeshActorElement > CreateMeshActor(const TCHAR* InName);`
- L55 _public prototype_ `static TSharedRef< IDatasmithClothElement > CreateCloth( const TCHAR* InName );` — `UE_DEPRECATED(5.5, "The experimental Cloth importer is no longer supported.")`
- L58 _public prototype_ `static TSharedRef< IDatasmithClothActorElement > CreateClothActor(const TCHAR* InName);` — `UE_DEPRECATED(5.5, "The experimental Cloth importer is no longer supported.")`
- L61 _public prototype_ `static TSharedRef< IDatasmithHierarchicalInstancedStaticMeshActorElement > CreateHierarchicalInstanceStaticMeshActor( const TCHAR* InName );`
- L63 _public prototype_ `static TSharedRef< IDatasmithMaterialElement > CreateMaterial( const TCHAR* InName );`
- L67 _public function_ `static TSharedRef< IDatasmithMasterMaterialElement > CreateMasterMaterial(const TCHAR* InName)` — `UE_DEPRECATED(5.1, "FDatasmithSceneFactory::CreateMasterMaterial will not be supported in 5.2. Please use FDatasmithSceneFactory::CreateMaterialInstance instead.")`
- L73 _public prototype_ `static TSharedRef< IDatasmithMaterialInstanceElement > CreateMaterialInstance(const TCHAR* InName);`
- L75 _public prototype_ `static TSharedRef< IDatasmithUEPbrMaterialElement > CreateUEPbrMaterial( const TCHAR* InName );`
- L82 _public prototype_ `static TSharedPtr< IDatasmithMaterialExpression > CreateMaterialExpression( EDatasmithMaterialExpressionType MaterialExpression );` — Creates a MaterialExpression from the given type. Warning: This function's main purpose is to allow the creation of serialized material expressions. Creating and adding new expressions to a UEPbrMaterial should be done with the IDatasmithUEPbrMaterialElement::AddMaterialExpression() function.
- L88 _public prototype_ `static TSharedRef< IDatasmithExpressionInput > CreateExpressionInput( const TCHAR* InName );` — Creates an ExpressionInput from the given type. Warning: This function's main purpose is to allow the creation of serialized expression inputs. It should not be used to add inputs to a material expression.
- L94 _public prototype_ `static TSharedRef< IDatasmithExpressionOutput > CreateExpressionOutput( const TCHAR* InName );` — Creates an ExpressionOutput from the given type. Warning: This function's main purpose is to allow the creation of serialized expression outputs. It should not be used to add outputs to a material expression.
- L96 _public prototype_ `static TSharedRef< IDatasmithMetaDataElement > CreateMetaData( const TCHAR* InName );`
- L98 _public prototype_ `static TSharedRef< IDatasmithMaterialIDElement > CreateMaterialId( const TCHAR* InName );`
- L100 _public prototype_ `static TSharedRef< IDatasmithPostProcessElement > CreatePostProcess();`
- L102 _public prototype_ `static TSharedRef< IDatasmithShaderElement > CreateShader( const TCHAR* InName );`
- L104 _public prototype_ `static TSharedRef< IDatasmithTextureElement > CreateTexture( const TCHAR* InName );`
- L106 _public prototype_ `static TSharedRef< IDatasmithLevelSequenceElement > CreateLevelSequence( const TCHAR* InName );`
- L107 _public prototype_ `static TSharedRef< IDatasmithTransformAnimationElement > CreateTransformAnimation( const TCHAR* InName );`
- L108 _public prototype_ `static TSharedRef< IDatasmithVisibilityAnimationElement > CreateVisibilityAnimation( const TCHAR* InName );`
- L109 _public prototype_ `static TSharedRef< IDatasmithSubsequenceAnimationElement > CreateSubsequenceAnimation( const TCHAR* InName );`
- L111 _public prototype_ `static TSharedRef< IDatasmithLevelVariantSetsElement > CreateLevelVariantSets( const TCHAR* InName );`
- L112 _public prototype_ `static TSharedRef< IDatasmithVariantSetElement > CreateVariantSet( const TCHAR* InName );`
- L113 _public prototype_ `static TSharedRef< IDatasmithVariantElement > CreateVariant( const TCHAR* InName );`
- L114 _public prototype_ `static TSharedRef< IDatasmithActorBindingElement > CreateActorBinding();`
- L115 _public prototype_ `static TSharedRef< IDatasmithPropertyCaptureElement > CreatePropertyCapture();`
- L116 _public prototype_ `static TSharedRef< IDatasmithObjectPropertyCaptureElement > CreateObjectPropertyCapture();`
- L118 _public prototype_ `static TSharedRef< IDatasmithDecalActorElement > CreateDecalActor( const TCHAR* InName );`
- L119 _public prototype_ `static TSharedRef< IDatasmithDecalMaterialElement > CreateDecalMaterial( const TCHAR* InName );`
- L121 _public prototype_ `static TSharedRef< IDatasmithScene > CreateScene( const TCHAR* InName );`
- L122 _public prototype_ `static TSharedRef< IDatasmithScene > DuplicateScene( const TSharedRef< IDatasmithScene >& InScene );`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API DATASMITHCORE_API`

### `Source/Runtime/Datasmith/DatasmithCore/Public/DatasmithSceneXmlReader.h` (Public)


#### class `FDatasmithSceneXmlReader`  
`class FDatasmithSceneXmlReader`  
_L24-94_
- L28 _public prototype_ `FDatasmithSceneXmlReader();` — Force non-inline constructor and destructor to prevent instantiating TUniquePtr< FXmlFile > with an incomplete FXmlFile type (forward declared)
- L29 _public prototype_ `~FDatasmithSceneXmlReader();`
- L31 _public prototype_ `bool ParseFile(const FString& InFilename, TSharedRef< IDatasmithScene >& OutScene, bool bInAppend = false);`
- L32 _public prototype_ `bool ParseBuffer(const FString& XmlBuffer, TSharedRef< IDatasmithScene >& OutScene, bool bInAppend = false);`
- L35 _private prototype_ `bool ParseXmlFile(TSharedRef< IDatasmithScene >& OutScene, bool bInAppend = false);`
- L36 _private prototype_ `void PatchUpVersion(TSharedRef< IDatasmithScene >& OutScene) const;`
- L38 _private prototype_ `[[nodiscard]] FString UnsanitizeXMLText(const FString& InString) const;`
- L40 _private prototype_ `template<typename T> T ValueFromString(const FString& InString) const = delete;`
- L41 _private prototype_ `template<typename T> T ValueFromString(const FString& InString) const = delete;`
- L42 _private prototype_ `FQuat QuatFromHexString(const FString& HexString) const;`
- L43 _private prototype_ `FQuat QuatFromNode(FXmlNode* InNode) const;`
- L44 _private prototype_ `FTransform ParseTransform(FXmlNode* InNode) const;`
- L45 _private prototype_ `void ParseTransform(FXmlNode* InNode, TSharedPtr< IDatasmithActorElement >& OutElement) const;`
- L47 _private prototype_ `void ParseElement(FXmlNode* InNode, TSharedRef<IDatasmithElement> OutElement) const;`
- L48 _private prototype_ `void ParseLevelSequence(FXmlNode* InNode, const TSharedRef<IDatasmithLevelSequenceElement>& OutElement) const;`
- L49 _private prototype_ `void ParseLevelVariantSets( FXmlNode* InNode, const TSharedRef<IDatasmithLevelVariantSetsElement>& OutElement, const TMap< FString, TSharedPtr<IDatasmithActorElement> >& Actors, const TMap< FString, TSharedPtr<IDatasmithElement> >& Objects ) const;`
- L50 _private prototype_ `void ParseVariantSet( FXmlNode* InNode, const TSharedRef<IDatasmithVariantSetElement>& OutElement, const TMap< FString, TSharedPtr<IDatasmithActorElement> >& Actors, const TMap< FString, TSharedPtr<IDatasmithElement> >& Objects ) const;`
- L51 _private prototype_ `void ParseVariant( FXmlNode* InNode, const TSharedRef<IDatasmithVariantElement>& OutElement, const TMap< FString, TSharedPtr<IDatasmithActorElement> >& Actors, const TMap< FString, TSharedPtr<IDatasmithElement> >& Objects ) const;`
- L52 _private prototype_ `void ParseActorBinding( FXmlNode* InNode, const TSharedRef<IDatasmithActorBindingElement>& OutElement, const TMap< FString, TSharedPtr<IDatasmithElement> >& Objects ) const;`
- L53 _private prototype_ `void ParsePropertyCapture( FXmlNode* InNode, const TSharedRef<IDatasmithPropertyCaptureElement>& OutElement ) const;`
- L54 _private prototype_ `void ParseObjectPropertyCapture( FXmlNode* InNode, const TSharedRef<IDatasmithObjectPropertyCaptureElement>& OutElement, const TMap< FString, TSharedPtr<IDatasmithElement> >& Objects ) const;`
- L55 _private prototype_ `void ParseMesh(FXmlNode* InNode, TSharedPtr<IDatasmithMeshElement>& OutElement) const;`
- L58 _private prototype_ `void ParseCloth(FXmlNode* InNode, TSharedPtr<IDatasmithClothElement>& OutElement) const;` — `UE_DEPRECATED(5.5, "The experimental Cloth importer is no longer supported.")`
- L60 _private prototype_ `void ParseTextureElement(FXmlNode* InNode, TSharedPtr<IDatasmithTextureElement>& OutElement) const;`
- L61 _private prototype_ `void ParseTexture(FXmlNode* InNode, FString& OutTextureFilename, FDatasmithTextureSampler& OutTextureUV) const;`
- L62 _private prototype_ `void ParseActor(FXmlNode* InNode, TSharedPtr<IDatasmithActorElement>& InOutElement, TSharedRef< IDatasmithScene > Scene, TMap< FString, TSharedPtr<IDatasmithActorElement> >& Actors) const;`
- L63 _private prototype_ `void ParseMeshActor(FXmlNode* InNode, TSharedPtr<IDatasmithMeshActorElement>& OutElement, TSharedRef< IDatasmithScene > Scene) const;`
- L66 _private prototype_ `void ParseClothActor(FXmlNode* InNode, TSharedPtr<IDatasmithClothActorElement>& OutElement, TSharedRef< IDatasmithScene > Scene) const;` — `UE_DEPRECATED(5.5, "The experimental Cloth importer is no longer supported.")`
- L68 _private prototype_ `void ParseHierarchicalInstancedStaticMeshActor(FXmlNode* InNode, TSharedPtr<IDatasmithHierarchicalInstancedStaticMeshActorElement>& OutElement, TSharedRef< IDatasmithScene > Scene) const;`
- L69 _private prototype_ `void ParseLight(FXmlNode* InNode, TSharedPtr<IDatasmithLightActorElement>& OutElement) const;`
- L70 _private prototype_ `void ParseCamera(FXmlNode* InNode, TSharedPtr<IDatasmithCameraActorElement>& OutElement) const;`
- L71 _private prototype_ `void ParsePostProcess(FXmlNode* InNode, const TSharedPtr< IDatasmithPostProcessElement >& Element) const;`
- L72 _private prototype_ `void ParsePostProcessVolume(FXmlNode* InNode, const TSharedRef< IDatasmithPostProcessVolumeElement >& Element) const;`
- L73 _private prototype_ `void ParseColor(FXmlNode* InNode, FLinearColor& OutColor) const;`
- L74 _private prototype_ `void ParseComp(FXmlNode* InNode, TSharedPtr< IDatasmithCompositeTexture >& OutCompTexture, bool bInIsNormal = false) const;`
- L75 _private prototype_ `void ParseMaterial(FXmlNode* InNode, TSharedPtr< IDatasmithMaterialElement >& OutElement) const;`
- L76 _private prototype_ `void ParseMaterialInstance(FXmlNode* InNode, TSharedPtr< IDatasmithMaterialInstanceElement >& OutElement) const;`
- L77 _private prototype_ `void ParseDecalMaterial(FXmlNode* InNode, TSharedPtr< IDatasmithDecalMaterialElement >& OutElement) const;`
- L78 _private prototype_ `void ParseUEPbrMaterial(FXmlNode* InNode, TSharedPtr< IDatasmithUEPbrMaterialElement >& OutElement) const;`
- L79 _private prototype_ `void ParseCustomActor(FXmlNode* InNode, TSharedPtr< IDatasmithCustomActorElement >& OutElement) const;`
- L80 _private prototype_ `void ParseMetaData(FXmlNode* InNode, TSharedPtr< IDatasmithMetaDataElement >& OutElement, const TSharedRef< IDatasmithScene >& InScene, TMap< FString, TSharedPtr<IDatasmithActorElement> >& Actors) const;`
- L81 _private prototype_ `void ParseLandscape(FXmlNode* InNode, TSharedRef< IDatasmithLandscapeElement >& OutElement) const;`
- L84 _private prototype_ `template< typename ElementType > void ParseKeyValueProperties(const FXmlNode* InNode, ElementType& OutElement) const;`
- L86 _private prototype_ `bool LoadFromFile(const FString& InFilename);`
- L87 _private prototype_ `bool LoadFromBuffer(const FString& XmlBuffer);`
- L90 _private prototype_ `template< typename ExpressionInputType > void ParseExpressionInput(const FXmlNode* InNode, TSharedPtr< IDatasmithUEPbrMaterialElement >& OutElement, ExpressionInputType& ExpressionInput) const;`
- L92 _private member_ `TUniquePtr< FXmlFile > XmlFile;`
- L93 _private member_ `FString ProjectPath;`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API DATASMITHCORE_API`

### `Source/Runtime/Datasmith/DatasmithCore/Public/DatasmithSceneXmlWriter.h` (Public)


#### class `FDatasmithSceneXmlWriter`  
`class FDatasmithSceneXmlWriter`  
_L12-16_
- L15 _public prototype_ `void Serialize( TSharedRef< IDatasmithScene > DatasmithScene, FArchive& Archive );`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API DATASMITHCORE_API`

### `Source/Runtime/Datasmith/DatasmithCore/Public/DatasmithTypes.h` (Public)


#### enum `EDatasmithCurveInterpMode`  
`enum class EDatasmithCurveInterpMode`  
_L12-17_
- L14 _public enumerator_ `Linear`
- L15 _public enumerator_ `Constant`
- L16 _public enumerator_ `Cubic`

#### class `FDatasmithTextureSampler`  
`class FDatasmithTextureSampler`  
_L19-86_
- L22 _public function_ `FDatasmithTextureSampler()`
- L38 _public function_ `FDatasmithTextureSampler(int InCoordinateIndex, float InSx, float InSy, float InOx, float InOy, float InRotation, float InMultiplier, bool bInInvert, int InOutputChannel, bool InCroppedTexture, int InMirrorX, int InMirrorY)`
- L55 _public member_ `int CoordinateIndex;` — UV coordinate index
- L58 _public member_ `float ScaleX;` — UV horizontal scale
- L60 _public member_ `float ScaleY;` — UV vertical scale
- L63 _public member_ `float OffsetX;` — UV horizontal offset [0,1] range
- L65 _public member_ `float OffsetY;` — UV vertical offset [0,1] range
- L68 _public member_ `float Rotation;` — UV rotation [0,1] range
- L71 _public member_ `float Multiplier;` — texture multiplier
- L74 _public member_ `bool bInvert;` — force texture invert
- L77 _public member_ `int OutputChannel;` — color channel to be connected
- L80 _public member_ `bool bCroppedTexture;` — flag to enable UV cropping
- L83 _public member_ `int MirrorX;` — UV Mirror 0 No mirror, X mirror tilling otherwise
- L85 _public member_ `int MirrorY;` — UV Mirror 0 No mirror, X mirror tilling otherwise

#### struct `FDatasmithTransformFrameInfo`  
`struct FDatasmithTransformFrameInfo`  
_L93-130_
- desc: FDatasmithTransformFrameInfo holds the data for the transform values of a frame The transform values must be relative to the parent The rotation is represented as Euler angles in degrees
- L95 _public function_ `FDatasmithTransformFrameInfo(int32 InFrameNumber, const FVector& InVec) : FrameNumber(InFrameNumber) , X(InVec.X) , Y(InVec.Y) , Z(InVec.Z)`
- L102 _public function_ `FDatasmithTransformFrameInfo(int32 InFrameNumber, const FQuat& InQuat) : FrameNumber(InFrameNumber)`
- L111 _public function_ `FDatasmithTransformFrameInfo(int32 InFrameNumber, double InX, double InY, double InZ) : FrameNumber(InFrameNumber) , X(InX) , Y(InY) , Z(InZ)`
- L118 _public prototype_ `bool operator==(const FDatasmithTransformFrameInfo& Other) const;`
- L119 _public prototype_ `bool IsValid() const;`
- L121 _public member_ `int32 FrameNumber;`
- L125 _public member_ `double X;` — For translation and scale, X, Y, Z are the transform values of the respective components For rotation, they represent rotation around the X, Y, Z axis (roll, pitch, yaw respectively) in degrees
- L126 _public member_ `double Y;`
- L127 _public member_ `double Z;`
- L129 _public member_ `static FDatasmithTransformFrameInfo InvalidFrameInfo;`

#### struct `FDatasmithVisibilityFrameInfo`  
`struct FDatasmithVisibilityFrameInfo`  
_L135-149_
- desc: FDatasmithVisibilityFrameInfo holds the visibility value for a frame
- L137 _public function_ `FDatasmithVisibilityFrameInfo(int32 InFrameNumber, bool bInVisible) : FrameNumber(InFrameNumber) , bVisible(bInVisible)`
- L142 _public prototype_ `bool operator==(const FDatasmithVisibilityFrameInfo& Other) const;`
- L143 _public prototype_ `bool IsValid() const;`
- L145 _public member_ `int32 FrameNumber;`
- L146 _public member_ `bool bVisible;`
- L148 _public member_ `static FDatasmithVisibilityFrameInfo InvalidFrameInfo;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API DATASMITHCORE_API`

### `Source/Runtime/Datasmith/DatasmithCore/Public/DatasmithUtils.h` (Public)


#### class `FDatasmithUtils`  
`class FDatasmithUtils`  
_L29-185_
- L32 _public prototype_ `static void SanitizeNameInplace(FString& InString);`
- L33 _public prototype_ `static FString SanitizeName(FString InString);`
- L34 _public prototype_ `static FString SanitizeObjectName(FString InString);`
- L35 _public prototype_ `static FString SanitizeFileName(FString InString);`
- L38 _public prototype_ `static void SanitizeStringInplace(FString& InString);` — Remove all non-printable characters from the string
- L40 _public prototype_ `static int32 GetEnterpriseVersionAsInt();`
- L41 _public prototype_ `static FString GetEnterpriseVersionAsString(bool bWithChangelist=false);`
- L44 _public prototype_ `static float GetDatasmithFormatVersionAsFloat();` — Returns the Datasmith data format version
- L45 _public prototype_ `static int32 GetDatasmithFormatVersionAsInt();`
- L46 _public prototype_ `static FString GetDatasmithFormatVersionAsString();`
- L49 _public prototype_ `static const TCHAR* GetFileExtension();` — Returns the file extension without the dot, of the DatasmithScene. Currently udatasmith
- L60 _public prototype_ `static void GetCleanFilenameAndExtension(const FString& InFilePath, FString& OutFilename, FString& OutExtension);` — Gets the file name and its extension. In case of extension like asm.1, the return name is the part before the full extension (asm.1) The right part of extension must to be a numeric value @param	InFilePath the path of the file @param	OutFilename the filename (without extension), minus any path information. @param	OutExtension the extension
- L63 _public prototype_ `static const TCHAR* GetLongAppName();` — Returns the long name of Datasmith
- L65 _public prototype_ `static const TCHAR* GetShortAppName();` — Returns the abbreviated name of Datasmith
- L68 _public prototype_ `static float AreaTriangle3D(const FVector3f& v0, const FVector3f& v1, const FVector3f& v2);` — Computes the area of a triangle
- L80 _public function_ `template<typename VecType> static void ConvertVectorArray(EModelCoordSystem ModelCoordSys, TArray<VecType>& Array)`
- L119 _public function_ `template<typename VecType> static VecType ConvertVector(EModelCoordSystem ModelCoordSys, const VecType& V)`
- L141 _public prototype_ `FTransform static ConvertTransform(EModelCoordSystem SourceCoordSystem, const FTransform& LocalTransform);`
- L144 _public function_ `template<typename Type> static UE::Math::TMatrix<Type> GetSymmetricMatrix(const UE::Math::TVector<Type>& Origin, const UE::Math::TVector<Type>& Normal)`

#### enum `FDatasmithUtils::EModelCoordSystem`  
`enum class EModelCoordSystem : uint8`  
_L70-77_
- L72 _public enumerator_ `ZUp_LeftHanded`
- L73 _public enumerator_ `ZUp_RightHanded`
- L74 _public enumerator_ `YUp_LeftHanded`
- L75 _public enumerator_ `YUp_RightHanded`
- L76 _public enumerator_ `ZUp_RightHanded_FBXLegacy`

#### class `FDatasmithMeshUtils`  
`class FDatasmithMeshUtils`  
_L187-222_
- L193 _private prototype_ `static bool ToRawMesh(const FDatasmithMesh& Mesh, FRawMesh& RawMesh, bool bValidateRawMesh = true);` — @param bValidateRawMesh this boolean indicate if the raw must be valid. For example a collision mesh don't need to have a valid raw mesh
- L201 _public prototype_ `static bool ToMeshDescription(FDatasmithMesh& DsMesh, FMeshDescription& MeshDescription, EUvGenerationPolicy UvGen=EUvGenerationPolicy::Ignore);`
- L209 _public prototype_ `static bool IsUVChannelValid(const FDatasmithMesh& DsMesh, const int32 Channel);` — Validates that the given UV Channel does not contain a degenerated triangle. @param DsMesh	The DatasmithMesh to validate. @param Channel	The UV channel to validate, starting at 0
- L216 _public prototype_ `static void CreateDefaultUVsWithLOD(FDatasmithMesh& Mesh);` — Generate simple UV data at channel 0 for the base mesh and it's various LOD variants. @param Mesh    The DatasmithMesh in which the UV data will be created.
- L221 _public prototype_ `static void ExtractVertexPositions(const FMeshDescription& Mesh, TArray<FVector3f>& OutPositions);` — Build an array of point from a MeshDescription

#### enum `FDatasmithMeshUtils::EUvGenerationPolicy`  
`enum EUvGenerationPolicy`  
_L196-200_
- L198 _public enumerator_ `Ignore` — do not generate a default UV. Conversion fails when no UV is available
- L199 _public enumerator_ `GenerateBox` — generate a Box UV mapping on the resulting MeshDescription (see also FStaticMeshOperations::GenerateBoxUV)

#### enum `EDSTextureUtilsError`  
`enum class EDSTextureUtilsError : int32`  
_L224-234_
- L226 _public enumerator_ `NoError = 0`
- L227 _public enumerator_ `FileNotFound = -1`
- L228 _public enumerator_ `InvalidFileType = -2`
- L229 _public enumerator_ `FileReadIssue = -3`
- L230 _public enumerator_ `InvalidData = -4`
- L231 _public enumerator_ `FreeImageNotFound = -5`
- L232 _public enumerator_ `FileNotSaved = -6`
- L233 _public enumerator_ `ResizeFailed = -7`

#### enum `EDSResizeTextureMode`  
`enum class EDSResizeTextureMode`  
_L242-248_
- desc: NoResize: Keep original size NearestPowerOfTwo: resizes to the nearest power of two value (recommended) PreviousPowerOfTwo: it decreases the value to the previous power of two NextPowerOfTwo: it increases the value to the next power of two
- L244 _public enumerator_ `NoResize`
- L245 _public enumerator_ `NearestPowerOfTwo`
- L246 _public enumerator_ `PreviousPowerOfTwo`
- L247 _public enumerator_ `NextPowerOfTwo`

#### class `FDatasmithTextureUtils`  
`class FDatasmithTextureUtils`  
_L250-255_
- L253 _public prototype_ `static bool CalculateTextureHash(const TSharedPtr<class IDatasmithTextureElement>& TextureElement);`
- L254 _public prototype_ `static void CalculateTextureHashes(const TSharedPtr<class IDatasmithScene>& Scene);`

#### enum `ETransformChannelComponents`  
`enum class ETransformChannelComponents : uint8`  
_L261-268_
- desc: Enum mainly used to describe which components of a transform animation are enabled. Should mostly be used with FDatasmithAnimationUtils::GetChannelTypeComponents
- L263 _public enumerator_ `None = 0x00`
- L264 _public enumerator_ `X = 0x01`
- L265 _public enumerator_ `Y = 0x02`
- L266 _public enumerator_ `Z = 0x04`
- L267 _public enumerator_ `All = X | Y | Z`

#### class `FDatasmithAnimationUtils`  
`class FDatasmithAnimationUtils`  
_L271-279_
- L275 _public prototype_ `static ETransformChannelComponents GetChannelTypeComponents(EDatasmithTransformChannels Channels, EDatasmithTransformType TransformType);` — Utility to help handling the components of a channel independently of the transform type
- L278 _public prototype_ `static EDatasmithTransformChannels SetChannelTypeComponents(ETransformChannelComponents Components, EDatasmithTransformType TransformType);` — Utility to help assembling a transform type's components into a EDatasmithTransformChannels enum

#### class `FDatasmithSceneUtils`  
`class FDatasmithSceneUtils`  
_L281-301_
- L284 _public prototype_ `static TArray<TSharedPtr<class IDatasmithCameraActorElement>> GetAllCameraActorsFromScene(const TSharedPtr<class IDatasmithScene>& Scene);`
- L285 _public prototype_ `static TArray<TSharedPtr<class IDatasmithLightActorElement>> GetAllLightActorsFromScene(const TSharedPtr<class IDatasmithScene>& Scene);`
- L286 _public prototype_ `static TArray<TSharedPtr<class IDatasmithMeshActorElement>> GetAllMeshActorsFromScene(const TSharedPtr<class IDatasmithScene>& Scene);`
- L287 _public prototype_ `static TArray<TSharedPtr<class IDatasmithCustomActorElement>> GetAllCustomActorsFromScene(const TSharedPtr<class IDatasmithScene>& Scene);`
- L289 _public typedef_ `using TActorHierarchy = TArray<TSharedPtr<class IDatasmithActorElement>, TInlineAllocator<8>>;`
- L290 _public prototype_ `static bool FindActorHierarchy(const IDatasmithScene* Scene, const TSharedPtr<IDatasmithActorElement>& ToFind, TActorHierarchy& OutHierarchy);`
- L292 _public prototype_ `static bool IsMaterialIDUsedInScene(const TSharedPtr<class IDatasmithScene>& Scene, const TSharedPtr<class IDatasmithMaterialIDElement>& MaterialElement);`
- L293 _public prototype_ `static bool IsPostProcessUsedInScene(const TSharedPtr<class IDatasmithScene>& Scene, const TSharedPtr<class IDatasmithPostProcessElement>& PostProcessElement);`
- L300 _public prototype_ `static void CleanUpScene(TSharedRef<class IDatasmithScene> Scene, bool bRemoveUnused = false);` — Fixes all missing references, remove all unused meshes, materials, textures, etc @param Scene Scene to perform the cleanup on @param bRemoveUnused Indicates if the cleanup includes the removal of unused assets

#### class `FDatasmithUniqueNameProviderBase`  
`class FDatasmithUniqueNameProviderBase`  
_L309-359_
- desc: Based on a table of frequently used names, this class generates unique names with a good complexity when the number of name is important. @note: This abstact class allows various implementation of the cache of known name. Implementation could use a simple TSet, or reuse existing specific cache structure
- L312 _public prototype_ `FDatasmithUniqueNameProviderBase() = default;`
- L313 _public prototype_ `FDatasmithUniqueNameProviderBase(const FDatasmithUniqueNameProviderBase& Other);`
- L314 _public prototype_ `FDatasmithUniqueNameProviderBase(FDatasmithUniqueNameProviderBase&& Other);`
- L316 _public prototype_ `virtual ~FDatasmithUniqueNameProviderBase() = default;`
- L318 _public prototype_ `FDatasmithUniqueNameProviderBase* operator=(const FDatasmithUniqueNameProviderBase& Other);`
- L319 _public prototype_ `FDatasmithUniqueNameProviderBase* operator=(FDatasmithUniqueNameProviderBase&& Other);`
- L327 _public prototype_ `FString GenerateUniqueName(const FString& BaseName, int32 CharBudget=INT32_MAX);` — Generates a unique name @param BaseName Name that will be suffixed with an index to be unique @param CharBudget Max character allowed in the name. @return FString unique name. Calling "Contains()" with this name will be false
- L333 _public prototype_ `virtual void AddExistingName(const FString& Name) = 0;` — Register a name as known @param Name name to register
- L339 _public prototype_ `virtual void RemoveExistingName(const FString& Name) = 0;` — Remove a name from the list of existing name @param Name name to unregister
- L344 _public prototype_ `virtual void Clear();` — Flushes all known names
- L354 _protected prototype_ `virtual bool Contains(const FString& Name) = 0;` — Check if the given name is already registered @param Name name to test @return true if the name is in the cache
- L357 _private member_ `TMap<FString, int32> FrequentlyUsedNames;`
- L358 _private member_ `mutable FCriticalSection CriticalSection;`

#### class `FDatasmithUniqueNameProvider`  
`class FDatasmithUniqueNameProvider : public FDatasmithUniqueNameProviderBase`  
_L364-381_
- inherits: `FDatasmithUniqueNameProviderBase`
- desc: Name provider with internal cache implemented with a simple TSet
- L367 _public typedef_ `using Super = FDatasmithUniqueNameProviderBase;`
- L369 _public function_ `void Reserve( int32 NumberOfName )`
- L371 _public function_ `virtual void AddExistingName(const FString& Name) override`
- L372 _public function_ `virtual void RemoveExistingName(const FString& Name) override`
- L374 _public function_ `virtual void Clear() override`
- L377 _protected function_ `virtual bool Contains(const FString& Name) override`
- L380 _private member_ `TSet<FString> KnownNames;`

#### Free symbols / members of external scopes

- L21 _macro_ `#define UE_API DATASMITHCORE_API`
- L269 _prototype_ `ENUM_CLASS_FLAGS(ETransformChannelComponents);`

### `Source/Runtime/Datasmith/DatasmithCore/Public/DatasmithVariantElements.h` (Public)


#### class `IDatasmithBaseVariantElement`  
`class IDatasmithBaseVariantElement : public IDatasmithElement`  
_L10-14_
- inherits: `IDatasmithElement`
- L13 _public prototype_ `virtual bool IsSubType( const EDatasmithElementVariantSubType VariantSubType ) const = 0;`

#### class `IDatasmithBasePropertyCaptureElement`  
`class IDatasmithBasePropertyCaptureElement : public IDatasmithBaseVariantElement`  
_L16-24_
- inherits: `IDatasmithBaseVariantElement`
- L19 _public prototype_ `virtual void SetPropertyPath(const FString& Path) = 0;`
- L20 _public prototype_ `virtual const FString& GetPropertyPath() const = 0;`
- L22 _public prototype_ `virtual void SetCategory(EDatasmithPropertyCategory Category) = 0;`
- L23 _public prototype_ `virtual EDatasmithPropertyCategory GetCategory() const = 0;`

#### class `IDatasmithPropertyCaptureElement`  
`class IDatasmithPropertyCaptureElement : public IDatasmithBasePropertyCaptureElement`  
_L26-31_
- inherits: `IDatasmithBasePropertyCaptureElement`
- L29 _public prototype_ `virtual void SetRecordedData(const uint8* Data, int32 NumBytes) = 0;`
- L30 _public prototype_ `virtual const TArray<uint8>& GetRecordedData() const = 0;`

#### class `IDatasmithObjectPropertyCaptureElement`  
`class IDatasmithObjectPropertyCaptureElement : public IDatasmithBasePropertyCaptureElement`  
_L33-38_
- inherits: `IDatasmithBasePropertyCaptureElement`
- L36 _public prototype_ `virtual void SetRecordedObject(TWeakPtr<IDatasmithElement> Object) = 0;`
- L37 _public prototype_ `virtual TWeakPtr<IDatasmithElement> GetRecordedObject() const = 0;`

#### class `IDatasmithActorBindingElement`  
`class IDatasmithActorBindingElement : public IDatasmithBaseVariantElement`  
_L40-50_
- inherits: `IDatasmithBaseVariantElement`
- L43 _public prototype_ `virtual void SetActor(TSharedPtr<IDatasmithActorElement> Actor) = 0;`
- L44 _public prototype_ `virtual TSharedPtr<IDatasmithActorElement> GetActor() const = 0;`
- L46 _public prototype_ `virtual void AddPropertyCapture(const TSharedRef<IDatasmithBasePropertyCaptureElement>& Prop) = 0;`
- L47 _public prototype_ `virtual int32 GetPropertyCapturesCount() const = 0;`
- L48 _public prototype_ `virtual TSharedPtr<IDatasmithBasePropertyCaptureElement> GetPropertyCapture(int32 Index) = 0;`
- L49 _public prototype_ `virtual void RemovePropertyCapture(const TSharedRef<IDatasmithBasePropertyCaptureElement>& Prop) = 0;`

#### class `IDatasmithVariantElement`  
`class IDatasmithVariantElement : public IDatasmithBaseVariantElement`  
_L52-59_
- inherits: `IDatasmithBaseVariantElement`
- L55 _public prototype_ `virtual void AddActorBinding(const TSharedRef<IDatasmithActorBindingElement>& Binding) = 0;`
- L56 _public prototype_ `virtual int32 GetActorBindingsCount() const = 0;`
- L57 _public prototype_ `virtual TSharedPtr<IDatasmithActorBindingElement> GetActorBinding(int32 Index) = 0;`
- L58 _public prototype_ `virtual void RemoveActorBinding(const TSharedRef<IDatasmithActorBindingElement>& Binding) = 0;`

#### class `IDatasmithVariantSetElement`  
`class IDatasmithVariantSetElement : public IDatasmithBaseVariantElement`  
_L61-68_
- inherits: `IDatasmithBaseVariantElement`
- L64 _public prototype_ `virtual void AddVariant(const TSharedRef<IDatasmithVariantElement>& Variant) = 0;`
- L65 _public prototype_ `virtual int32 GetVariantsCount() const = 0;`
- L66 _public prototype_ `virtual TSharedPtr<IDatasmithVariantElement> GetVariant(int32 Index) = 0;`
- L67 _public prototype_ `virtual void RemoveVariant(const TSharedRef<IDatasmithVariantElement>& Variant) = 0;`

#### class `IDatasmithLevelVariantSetsElement`  
`class IDatasmithLevelVariantSetsElement : public IDatasmithBaseVariantElement`  
_L70-77_
- inherits: `IDatasmithBaseVariantElement`
- L73 _public prototype_ `virtual void AddVariantSet(const TSharedRef<IDatasmithVariantSetElement>& VariantSet) = 0;`
- L74 _public prototype_ `virtual int32 GetVariantSetsCount() const = 0;`
- L75 _public prototype_ `virtual TSharedPtr<IDatasmithVariantSetElement> GetVariantSet(int32 Index) = 0;`
- L76 _public prototype_ `virtual void RemoveVariantSet(const TSharedRef<IDatasmithVariantSetElement>& VariantSet) = 0;`

### `Source/Runtime/Datasmith/DatasmithCore/Public/DirectLink/DatasmithDirectLinkTools.h` (Public)


#### Free symbols / members of external scopes

- L13 _prototype_ `const TCHAR* GetElementTypeName(const IDatasmithElement* Element);`
- L15 _prototype_ `void DumpDatasmithScene(const TSharedRef<IDatasmithScene>& Scene, const TCHAR* BaseName);`

### `Source/Runtime/Datasmith/DatasmithCore/Public/DirectLink/DatasmithSceneReceiver.h` (Public)


#### class `FDatasmithSceneReceiver`  
`class FDatasmithSceneReceiver : public DirectLink::ISceneReceiver`  
_L24-89_
- inherits: `DirectLink::ISceneReceiver`
- desc: This class receives DirectLink scene snapshots, and convert them into a DatasmithScene. A listener can be registered to be notified of a scene modification
- L40 _public prototype_ `FDatasmithSceneReceiver();`
- L43 _public function_ `void SetChangeListener(ISceneChangeListener* Listener)` — Register a listner that will be notified of important scene edition events
- L46 _public prototype_ `TSharedPtr<IDatasmithScene> GetScene() const;` — Get the reconstructed DatasmithScene. Can be null.
- L49 _private prototype_ `virtual void FinalSnapshot(const DirectLink::FSceneSnapshot& SceneSnapshot) override;`
- L53 _private prototype_ `TUniquePtr<FSceneState> ParseSnapshot(const DirectLink::FSceneSnapshot& SceneSnapshot);`
- L72 _private member_ `ISceneChangeListener* ChangeListener = nullptr;`
- L88 _private member_ `TUniquePtr<FSceneState> Current;`

#### class `FDatasmithSceneReceiver::ISceneChangeListener`  
`class ISceneChangeListener`  
_L28-37_
- L31 _public prototype_ `virtual void OnOpenDelta() = 0;`
- L32 _public prototype_ `virtual void OnNewScene(const DirectLink::FSceneIdentifier& SceneId) = 0;`
- L33 _public prototype_ `virtual void OnAddElement(DirectLink::FSceneGraphId, TSharedPtr<IDatasmithElement> Element) = 0;`
- L34 _public prototype_ `virtual void OnChangedElement(DirectLink::FSceneGraphId, TSharedPtr<IDatasmithElement> Element) = 0;`
- L35 _public prototype_ `virtual void OnRemovedElement(DirectLink::FSceneGraphId ElementId) = 0;`
- L36 _public prototype_ `virtual void OnCloseDelta() = 0;`

#### struct `FDatasmithSceneReceiver::FDatasmithElementPointers`  
`struct FDatasmithElementPointers : public DirectLink::IReferenceResolutionProvider`  
_L56-64_
- inherits: `DirectLink::IReferenceResolutionProvider`
- L59 _public prototype_ `virtual TSharedPtr<DirectLink::ISceneGraphNode> AsSharedPtr(DirectLink::FSceneGraphId NodeId) override;` — IReferenceResolutionProvider API
- L60 _public function_ `void Reset()`
- L61 _public function_ `void Remove(DirectLink::FSceneGraphId NodeId)`
- L62 _public function_ `void Add(DirectLink::FSceneGraphId Id, TSharedPtr<IDatasmithElement> Element)`
- L63 _public member_ `TMap<DirectLink::FSceneGraphId, TSharedPtr<IDatasmithElement>> ElementsSharedPtrs;`

#### struct `FDatasmithSceneReceiver::FFinalizableNode`  
`struct FFinalizableNode`  
_L66-70_
- L68 _public member_ `TSharedPtr<IDatasmithElement> Element;`
- L69 _public member_ `const DirectLink::FElementSnapshot* Snapshot;`

#### struct `FDatasmithSceneReceiver::FSceneHashTable`  
`struct FSceneHashTable`  
_L74-78_
- L76 _public member_ `TMap<DirectLink::FSceneGraphId, DirectLink::FElementHash> ElementHashes;`
- L77 _public prototype_ `static FSceneHashTable FromSceneSnapshot(const DirectLink::FSceneSnapshot& SceneSnapshot);`

#### struct `FDatasmithSceneReceiver::FSceneState`  
`struct FSceneState`  
_L80-86_
- L82 _public member_ `DirectLink::FSceneIdentifier SceneId;`
- L83 _public member_ `TSharedPtr<IDatasmithScene> Scene;`
- L84 _public member_ `FDatasmithElementPointers Elements;`
- L85 _public member_ `FSceneHashTable HashTable;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API DATASMITHCORE_API`
- L17 _namespace_ `namespace DirectLink`
- L18 _namespace_ `namespace DirectLink`

### `Source/Runtime/Datasmith/DatasmithCore/Public/IDatasmithSceneElements.h` (Public)


#### class `IDatasmithElement`  
`class IDatasmithElement : public DirectLink::ISceneGraphNode`  
_L27-51_
- inherits: `DirectLink::ISceneGraphNode`
- desc: Root class for every element in a Datasmith scene
- L31 _public prototype_ `virtual bool IsA(EDatasmithElementType Type) const = 0;` — returns if this DatasmithElement is of a specified type
- L34 _public prototype_ `virtual const TCHAR* GetName() const = 0;` — Gets the element name
- L37 _public prototype_ `virtual void SetName(const TCHAR* InName) = 0;` — Sets the element name
- L40 _public prototype_ `virtual const TCHAR* GetLabel() const = 0;` — Gets the element label used in the UI
- L43 _public prototype_ `virtual void SetLabel(const TCHAR* InLabel) = 0;` — Sets the element label used in the UI
- L50 _public prototype_ `virtual FMD5Hash CalculateElementHash(bool bForce) = 0;` — Return a MD5 hash of the content of the Element. Used to quickly identify Element with identical content. @param bForce Force recalculation of the hash if it was already cached @return The MD5 hash of the Element properties

#### class `IDatasmithKeyValueProperty`  
`class IDatasmithKeyValueProperty : public IDatasmithElement`  
_L53-69_
- inherits: `IDatasmithElement`
- L56 _public prototype_ `virtual ~IDatasmithKeyValueProperty() = default;`
- L59 _public prototype_ `virtual EDatasmithKeyValuePropertyType GetPropertyType() const = 0;` — Get the type of this property
- L62 _public prototype_ `virtual void SetPropertyType(EDatasmithKeyValuePropertyType InType) = 0;` — Set the type of this property
- L65 _public prototype_ `virtual const TCHAR* GetValue() const = 0;` — Get the value of this property
- L68 _public prototype_ `virtual void SetValue(const TCHAR* Value) = 0;` — Sets the value of this property

#### class `IDatasmithActorElement`  
`class IDatasmithActorElement : public IDatasmithElement`  
_L72-161_
- inherits: `IDatasmithElement`
- desc: Base definition for Actor Elements like geometry instances, cameras or lights
- L75 _public prototype_ `virtual ~IDatasmithActorElement() = default;`
- L78 _public prototype_ `virtual FVector GetTranslation() const = 0;` — Get absolute translation of this entity
- L81 _public prototype_ `virtual void SetTranslation(double InX, double InY, double InZ, bool bKeepChildrenRelative = true) = 0;` — Set absolute translation of this entity
- L84 _public prototype_ `virtual void SetTranslation(const FVector& Value, bool bKeepChildrenRelative = true) = 0;` — Set absolute translation of this entity
- L87 _public prototype_ `virtual FVector GetScale() const = 0;` — Get absolute scale of this entity
- L90 _public prototype_ `virtual void SetScale(double InX, double InY, double InZ, bool bKeepChildrenRelative = true) = 0;` — Set absolute scale of this entity
- L93 _public prototype_ `virtual void SetScale(const FVector& Value, bool bKeepChildrenRelative = true) = 0;` — Set absolute scale of this entity
- L96 _public prototype_ `virtual FQuat GetRotation() const = 0;` — Get rotation (in quaternion format) of this entity
- L99 _public prototype_ `virtual void SetRotation(double InX, double InY, double InZ, double InW, bool bKeepChildrenRelative = true) = 0;` — Set rotation (in quaternion format) of this entity
- L102 _public prototype_ `virtual void SetRotation(const FQuat& Value, bool bKeepChildrenRelative = true) = 0;` — Set rotation (in quaternion format) of this entity
- L105 _public prototype_ `virtual FTransform GetRelativeTransform() const = 0;` — Returns the relative transform for this element
- L108 _public prototype_ `virtual const TCHAR* GetLayer() const = 0;` — Get the the name of the layer that contains this entity
- L111 _public prototype_ `virtual void SetLayer(const TCHAR* InLayer) = 0;` — Set the the the layer that contains this entity, layer will be auto-created from its name
- L114 _public prototype_ `virtual void AddTag(const TCHAR* InTag) = 0;` — Add a new Tag to an Actor element
- L117 _public prototype_ `virtual void ResetTags() = 0;` — Remove all Tags on the Actor element
- L120 _public prototype_ `virtual int32 GetTagsCount() const = 0;` — Get the number of tags attached to an Actor element
- L123 _public prototype_ `virtual const TCHAR* GetTag(int32 TagIndex) const = 0;` — Get the 'TagIndex'th tag of an Actor element
- L126 _public prototype_ `virtual void AddChild(const TSharedPtr< IDatasmithActorElement >& InChild, EDatasmithActorAttachmentRule AttachementRule = EDatasmithActorAttachmentRule::KeepWorldTransform) = 0;` — Adds a new child to the Actor Element
- L129 _public prototype_ `virtual int32 GetChildrenCount() const = 0;` — Get the number of children on this actor
- L132 _public prototype_ `virtual TSharedPtr< IDatasmithActorElement > GetChild(int32 InIndex) = 0;` — Get the InIndex-th child of the mesh actor
- L133 _public prototype_ `virtual const TSharedPtr< IDatasmithActorElement >& GetChild(int32 InIndex) const = 0;`
- L135 _public prototype_ `virtual void RemoveChild(const TSharedPtr< IDatasmithActorElement >& InChild) = 0;`
- L138 _public prototype_ `virtual const TSharedPtr< IDatasmithActorElement >& GetParentActor() const = 0;` — Get the parent actor of the Actor element, returns invalid TSharedPtr if the Actor is directly under the scene root
- L141 _public prototype_ `virtual void SetIsAComponent(bool Value) = 0;` — Indicates if this actor is a standalone actor or a component, when used in a hierarchy
- L142 _public prototype_ `virtual bool IsAComponent() const = 0;`
- L145 _public prototype_ `virtual void SetVisibility(bool bInVisibility) = 0;` — Set a mesh actor's visibility
- L148 _public prototype_ `virtual bool GetVisibility() const = 0;` — Get a mesh actor's visibility
- L151 _public prototype_ `virtual void SetCastShadow(bool bInCastShadow) = 0;` — Set whether an actor's casts shadow
- L154 _public prototype_ `virtual bool GetCastShadow() const = 0;` — Get whether an actor's casts shadow
- L157 _public prototype_ `virtual void SetMobility(EDatasmithActorMobilityType Mobility) = 0;` — Set a mesh actor's visibility
- L160 _public prototype_ `virtual EDatasmithActorMobilityType GetMobility() const = 0;` — Get a mesh actor's visibility

#### class `IDatasmithMeshElement`  
`class IDatasmithMeshElement : public IDatasmithElement`  
_L168-246_
- inherits: `IDatasmithElement`
- desc: IDatasmithMeshElement defines an actual geometry. It won't add any instance to your scene, you'll need IDatasmithMeshActorElement for this. Notice that several IDatasmithMeshActorElements could use the this geometry.
- L171 _public prototype_ `virtual ~IDatasmithMeshElement() = default;`
- L174 _public prototype_ `virtual const TCHAR* GetFile() const = 0;` — Get the output filename, it can be absolute or relative to the scene file
- L177 _public prototype_ `virtual void SetFile(const TCHAR* InFile) = 0;` — Set the output filename, it can be absolute or relative to the scene file
- L180 _public prototype_ `virtual FMD5Hash GetFileHash() const = 0;` — Return a MD5 hash of the content of the Mesh Element. Used in CalculateElementHash to quickly identify Element with identical content
- L183 _public prototype_ `virtual void SetFileHash(FMD5Hash Hash) = 0;` — Set the MD5 hash of the current mesh file. This should be a hash of its content.
- L193 _public prototype_ `virtual void SetDimensions(float InArea, float InWidth, float InHeight, float InDepth) = 0;` — Set surface area and bounding box dimensions to be used on lightmap size calculation. @param InArea total surface area @param InWidth bounding box width @param InHeight bounding box height @param InDepth bounding box depth
- L196 _public prototype_ `virtual FVector3f GetDimensions() const = 0;` — Get the bounding box dimension of the mesh, in a vector in the form of (Width, Height, Depth )
- L199 _public prototype_ `virtual float GetArea() const = 0;` — Get the total surface area
- L202 _public prototype_ `virtual float GetWidth() const = 0;` — Get the bounding box width
- L205 _public prototype_ `virtual float GetHeight() const = 0;` — Get the bounding box height
- L208 _public prototype_ `virtual float GetDepth() const = 0;` — Get the bounding box depth
- L211 _public prototype_ `virtual int32 GetLightmapCoordinateIndex() const = 0;` — Get the UV channel that will be used for the lightmap
- L217 _public prototype_ `virtual void SetLightmapCoordinateIndex(int32 UVChannel) = 0;` — Set the UV channel that will be used for the lightmap Note: If the lightmap coordinate index is something greater than -1 it will make the importer skip the lightmap generation
- L220 _public prototype_ `virtual int32 GetLightmapSourceUV() const = 0;` — Get the source UV channel that will be used at import to generate the lightmap UVs
- L223 _public prototype_ `virtual void SetLightmapSourceUV(int32 UVChannel) = 0;` — Set the source UV channel that will be used at import to generate the lightmap UVs
- L226 _public prototype_ `virtual void SetMaterial(const TCHAR* MaterialPathName, int32 SlotId) = 0;` — Set the material slot Id to use the material MaterialPathName
- L229 _public prototype_ `virtual const TCHAR* GetMaterial(int32 SlotId) const = 0;` — Get the name of the material mapped to slot Id, return nullptr if slot isn't mapped
- L232 _public prototype_ `virtual int32 GetMaterialSlotCount() const = 0;` — Get the number of material slot set on this mesh
- L235 _public prototype_ `virtual TSharedPtr<const IDatasmithMaterialIDElement> GetMaterialSlotAt(int32 Index) const = 0;` — Get the material mapping for slot Index
- L236 _public prototype_ `virtual TSharedPtr<IDatasmithMaterialIDElement> GetMaterialSlotAt(int32 Index) = 0;`
- L240 _protected prototype_ `virtual int32 GetLODCount() const = 0;` — Get number of LODs
- L243 _protected prototype_ `virtual void SetLODCount(int32 Count) = 0;` — Set number of LODs

#### class `IDatasmithClothElement`  
`class UE_DEPRECATED(5.5, "The experimental Cloth importer is no longer supported.") IDatasmithClothElement : public IDatasmithElement`  
_L251-261_
- inherits: `IDatasmithElement`
- desc: IDatasmithClothElement class: experimental class that describes a cloth asset
- L255 _public prototype_ `virtual const TCHAR* GetFile() const = 0;` — Get the FDatasmithCloth resource filename
- L258 _public prototype_ `virtual void SetFile(const TCHAR* InFile) = 0;` — Set the FDatasmithCloth resource filename, it can be absolute or relative to the scene file

#### class `IDatasmithMeshActorElement`  
`class IDatasmithMeshActorElement : public IDatasmithActorElement`  
_L268-307_
- inherits: `IDatasmithActorElement`
- desc: IDatasmithActorElement used in any geometry instance independently if it could be static or movable. It doesn't define the actual geometry, you'll need IDatasmithMeshElement for this. Notice that several IDatasmithMeshActorElements could use the same geometry.
- L271 _public prototype_ `virtual ~IDatasmithMeshActorElement() = default;`
- L279 _public prototype_ `virtual void AddMaterialOverride(const TCHAR* MaterialName, int32 Id) = 0;` — Adds a new material override to the Actor Element @param MaterialName name of the material, it should be unique @param Id material identifier to be used with mesh sub-material indices. Use -1 to override all material slots.
- L282 _public prototype_ `virtual void AddMaterialOverride(const TSharedPtr<IDatasmithMaterialIDElement>& Material) = 0;` — Adds a new material override to the Actor Element
- L285 _public prototype_ `virtual int32 GetMaterialOverridesCount() const = 0;` — Get the amount of material overrides on this mesh
- L288 _public prototype_ `virtual TSharedPtr<IDatasmithMaterialIDElement> GetMaterialOverride(int32 i) = 0;` — Get the i-th material override of this actor
- L291 _public prototype_ `virtual TSharedPtr<const IDatasmithMaterialIDElement> GetMaterialOverride(int32 i) const = 0;` — Get the i-th material override of this actor
- L294 _public prototype_ `virtual void RemoveMaterialOverride(const TSharedPtr<IDatasmithMaterialIDElement>& Material) = 0;` — Remove material from the Actor Element
- L297 _public prototype_ `virtual void ResetMaterialOverrides() = 0;` — Remove all material overrides from the Actor Element
- L300 _public prototype_ `virtual const TCHAR* GetStaticMeshPathName() const = 0;` — Get the path name of the StaticMesh associated with the actor
- L306 _public prototype_ `virtual void SetStaticMeshPathName(const TCHAR* InStaticMeshPathName) = 0;` — Set the path name of the StaticMesh that the actor is using It can be either a package path to refer to an existing mesh or a mesh name to refer to a MeshElement in the DatasmithScene

#### class `IDatasmithClothActorElement`  
`class UE_DEPRECATED(5.5, "The experimental Cloth importer is no longer supported.") IDatasmithClothActorElement : public IDatasmithActorElement`  
_L309-314_
- inherits: `IDatasmithActorElement`
- L312 _public prototype_ `virtual void SetCloth(const TCHAR* Cloth) = 0;`
- L313 _public prototype_ `virtual const TCHAR* GetCloth() const = 0;`

#### class `IDatasmithHierarchicalInstancedStaticMeshActorElement`  
`class IDatasmithHierarchicalInstancedStaticMeshActorElement : public IDatasmithMeshActorElement`  
_L316-352_
- inherits: `IDatasmithMeshActorElement`
- L323 _public prototype_ `virtual int32 GetInstancesCount() const = 0;` — Get the number of instances @return the number of instances
- L330 _public prototype_ `virtual void ReserveSpaceForInstances(int32 NumIntances) = 0;` — Reserve memory for a number of instance. @param NumInstances The number of instance. This reduce the overall time needed to add a large number of instances.
- L337 _public prototype_ `virtual int32 AddInstance(const FTransform& Transform) = 0;` — Add an instance @param Transform the transform of the instance @return the index of the new instance
- L344 _public prototype_ `virtual FTransform GetInstance(int32 InstanceIndex) const = 0;` — Get the transform of a specified instance @param InstanceIndex The index of the instance @return The transform of the instance
- L351 _public prototype_ `virtual void RemoveInstance(int32 InstanceIndex) = 0;` — Remove an instance @param InstanceIndex The index of the instance to remove Note that this destruct the order of the instances

#### class `IDatasmithLightActorElement`  
`class IDatasmithLightActorElement : public IDatasmithActorElement`  
_L354-437_
- inherits: `IDatasmithActorElement`
- L357 _public prototype_ `virtual ~IDatasmithLightActorElement() = default;`
- L360 _public prototype_ `virtual bool IsEnabled() const = 0;` — Return true on light enabled, false otherwise
- L363 _public prototype_ `virtual void SetEnabled(bool bIsEnabled) = 0;` — Set enable property of the light
- L366 _public prototype_ `virtual double GetIntensity() const = 0;` — Get light intensity
- L369 _public prototype_ `virtual void SetIntensity(double Intensity) = 0;` — Set light intensity
- L372 _public prototype_ `virtual FLinearColor GetColor() const = 0;` — Get light color on linear mode
- L375 _public prototype_ `virtual void SetColor(FLinearColor Color) = 0;` — Set light color on linear mode
- L378 _public prototype_ `virtual double GetTemperature() const = 0;` — Get the light temperature in Kelvin
- L381 _public prototype_ `virtual void SetTemperature(double Temperature) = 0;` — Set the light temperature in Kelvin
- L384 _public prototype_ `virtual bool GetUseTemperature() const = 0;` — Get if the light color is controlled by temperature
- L387 _public prototype_ `virtual void SetUseTemperature(bool bUseTemperature) = 0;` — Set if the light color is controlled by temperature
- L390 _public prototype_ `virtual const TCHAR* GetIesFile() const = 0;` — Get the path of the Ies definition file - DEPRECATED in 4.26: Replaced with GetIesTexturePathName
- L393 _public prototype_ `virtual const TCHAR* GetIesTexturePathName() const = 0;` — Get the IES texture path
- L396 _public prototype_ `virtual void SetIesFile(const TCHAR* IesFile) = 0;` — Set the path of the Ies definition file - DEPRECATED in 4.26: Replaced with SetIesTexturePathName
- L403 _public prototype_ `virtual void SetIesTexturePathName(const TCHAR* TextureName) = 0;` — Set the IES texture path The path is either the name of an element attached to the scene or the path of a UE texture asset, i.e. /Game/.../TextureAssetName.TextureAssetName
- L406 _public prototype_ `virtual bool GetUseIes() const = 0;` — Set if this light is controlled by Ies definition file
- L409 _public prototype_ `virtual void SetUseIes(bool bUseIes) = 0;` — Get if this light is controlled by Ies definition file
- L412 _public prototype_ `virtual double GetIesBrightnessScale() const = 0;` — Get the Ies brightness multiplier
- L415 _public prototype_ `virtual void SetIesBrightnessScale(double IesBrightnessScale) = 0;` — Set the Ies brightness multiplier
- L418 _public prototype_ `virtual bool GetUseIesBrightness() const = 0;` — Get if the emissive amount of the ies is controlled by the brightness scale
- L421 _public prototype_ `virtual void SetUseIesBrightness(bool bUseIesBrightness) = 0;` — Set if the emissive amount of the ies is controlled by the brightness scale
- L424 _public prototype_ `virtual FQuat GetIesRotation() const = 0;` — Get the rotation applied to the IES shape
- L427 _public prototype_ `virtual void SetIesRotation(const FQuat& IesRotation) = 0;` — Set the rotation to apply to the IES shape
- L430 _public prototype_ `virtual TSharedPtr< IDatasmithMaterialIDElement >& GetLightFunctionMaterial() = 0;` — Get emissive material on this light
- L433 _public prototype_ `virtual void SetLightFunctionMaterial(const TSharedPtr< IDatasmithMaterialIDElement >& InMaterial) = 0;` — Set emissive material on this light
- L436 _public prototype_ `virtual void SetLightFunctionMaterial(const TCHAR* InMaterialName) = 0;` — Set emissive material on this light

#### class `IDatasmithPointLightElement`  
`class IDatasmithPointLightElement : public IDatasmithLightActorElement`  
_L439-462_
- inherits: `IDatasmithLightActorElement`
- L442 _public prototype_ `virtual void SetIntensityUnits(EDatasmithLightUnits InUnits) = 0;`
- L443 _public prototype_ `virtual EDatasmithLightUnits GetIntensityUnits() const = 0;`
- L446 _public prototype_ `virtual float GetSourceRadius() const = 0;` — Get light radius, width in case of 2D light sources
- L449 _public prototype_ `virtual void SetSourceRadius(float SourceRadius) = 0;` — Set light radius, width in case of 2D light sources
- L452 _public prototype_ `virtual float GetSourceLength() const = 0;` — Get light length only affects 2D shaped lights
- L455 _public prototype_ `virtual void SetSourceLength(float SourceLength) = 0;` — Set light length only affects 2D shaped lights
- L458 _public prototype_ `virtual float GetAttenuationRadius() const = 0;` — Get attenuation radius in centimeters
- L461 _public prototype_ `virtual void SetAttenuationRadius(float AttenuationRadius) = 0;` — Set attenuation radius in centimeters

#### class `IDatasmithSpotLightElement`  
`class IDatasmithSpotLightElement : public IDatasmithPointLightElement`  
_L464-478_
- inherits: `IDatasmithPointLightElement`
- L468 _public prototype_ `virtual float GetInnerConeAngle() const = 0;` — Get the inner cone angle for spot lights in degrees
- L471 _public prototype_ `virtual void SetInnerConeAngle(float InnerConeAngle) = 0;` — Set the inner cone angle for spot lights in degrees
- L474 _public prototype_ `virtual float GetOuterConeAngle() const = 0;` — Get the outer cone angle for spot lights in degrees
- L477 _public prototype_ `virtual void SetOuterConeAngle(float OuterConeAngle) = 0;` — Set the outer cone angle for spot lights in degrees

#### class `IDatasmithDirectionalLightElement`  
`class IDatasmithDirectionalLightElement : public IDatasmithLightActorElement`  
_L480-482_
- inherits: `IDatasmithLightActorElement`

#### class `IDatasmithAreaLightElement`  
`class IDatasmithAreaLightElement : public IDatasmithSpotLightElement`  
_L487-507_
- inherits: `IDatasmithSpotLightElement`
- desc: An area light is an emissive shape (light shape) with a light component (light type)
- L491 _public prototype_ `virtual EDatasmithLightShape GetLightShape() const = 0;` — Get the light shape Rectangle/Sphere/Disc/Cylinder
- L494 _public prototype_ `virtual void SetLightShape(EDatasmithLightShape Shape) = 0;` — Set the light shape Rectangle/Sphere/Disc/Cylinder
- L497 _public prototype_ `virtual void SetLightType(EDatasmithAreaLightType LightType) = 0;` — Set the type of light for an area light: Point/Spot/Rect
- L498 _public prototype_ `virtual EDatasmithAreaLightType GetLightType() const = 0;`
- L501 _public prototype_ `virtual void SetWidth(float InWidth) = 0;` — Set the area light shape size on the Y axis
- L502 _public prototype_ `virtual float GetWidth() const = 0;`
- L505 _public prototype_ `virtual void SetLength(float InLength) = 0;` — Set the area light shape size on the X axis
- L506 _public prototype_ `virtual float GetLength() const = 0;`

#### class `IDatasmithLightmassPortalElement`  
`class IDatasmithLightmassPortalElement : public IDatasmithPointLightElement`  
_L514-516_
- inherits: `IDatasmithPointLightElement`
- desc: Represents a ALightmassPortal Use the actor scale to drive the portal dimensions

#### class `IDatasmithCameraActorElement`  
`class IDatasmithCameraActorElement : public IDatasmithActorElement`  
_L518-579_
- inherits: `IDatasmithActorElement`
- L521 _public prototype_ `virtual ~IDatasmithCameraActorElement() = default;`
- L524 _public prototype_ `virtual float GetSensorWidth() const = 0;` — Get camera sensor width in millimeters
- L527 _public prototype_ `virtual void SetSensorWidth(float SensorWidth) = 0;` — Set camera sensor width in millimeters
- L530 _public prototype_ `virtual float GetSensorAspectRatio() const = 0;` — Get framebuffer aspect ratio (width/height)
- L533 _public prototype_ `virtual void SetSensorAspectRatio(float SensorAspectRatio) = 0;` — Set framebuffer aspect ratio (width/height)
- L536 _public prototype_ `virtual bool GetEnableDepthOfField() const = 0;` — The focus method of the camera, either None (no DoF) or Manual
- L539 _public prototype_ `virtual void SetEnableDepthOfField(bool bEnableDepthOfField) = 0;` — The focus method of the camera, either None (no DoF) or Manual
- L542 _public prototype_ `virtual float GetFocusDistance() const = 0;` — Get camera focus distance in centimeters
- L545 _public prototype_ `virtual void SetFocusDistance(float FocusDistance) = 0;` — Set camera focus distance in centimeters
- L548 _public prototype_ `virtual float GetFStop() const = 0;` — Get camera FStop also known as FNumber
- L551 _public prototype_ `virtual void SetFStop(float FStop) = 0;` — Set camera FStop also known as FNumber
- L554 _public prototype_ `virtual float GetFocalLength() const = 0;` — Get camera focal length in millimeters
- L557 _public prototype_ `virtual void SetFocalLength(float FocalLength) = 0;` — Set camera focal length in millimeters
- L560 _public prototype_ `virtual TSharedPtr< IDatasmithPostProcessElement >& GetPostProcess() = 0;` — Get camera's postprocess
- L563 _public prototype_ `virtual const TSharedPtr< IDatasmithPostProcessElement >& GetPostProcess() const = 0;` — Get camera's postprocess
- L566 _public prototype_ `virtual void SetPostProcess(const TSharedPtr< IDatasmithPostProcessElement >& PostProcess) = 0;` — Set camera's postprocess
- L569 _public prototype_ `virtual const TCHAR* GetLookAtActor() const = 0;` — Get camera look at actor name
- L572 _public prototype_ `virtual void SetLookAtActor(const TCHAR* ActorName) = 0;` — Set camera look at actor name
- L575 _public prototype_ `virtual bool GetLookAtAllowRoll() const = 0;` — Get camera look at allow roll state
- L578 _public prototype_ `virtual void SetLookAtAllowRoll(bool bAllow) = 0;` — Set camera look at allow roll state

#### class `IDatasmithCustomActorElement`  
`class IDatasmithCustomActorElement : public IDatasmithActorElement`  
_L581-602_
- inherits: `IDatasmithActorElement`
- L585 _public prototype_ `virtual const TCHAR* GetClassOrPathName() const = 0;` — The class name or path to the blueprint to instantiate.
- L586 _public prototype_ `virtual void SetClassOrPathName(const TCHAR* InClassOrPathName) = 0;`
- L589 _public prototype_ `virtual int32 GetPropertiesCount() const = 0;` — Get the total amount of properties in this actor
- L592 _public prototype_ `virtual const TSharedPtr< IDatasmithKeyValueProperty >& GetProperty(int32 i) const = 0;` — Get the property i-th of this actor
- L595 _public prototype_ `virtual const TSharedPtr< IDatasmithKeyValueProperty >& GetPropertyByName(const TCHAR* Name) const = 0;` — Get a property by its name if it exists
- L598 _public prototype_ `virtual void AddProperty(const TSharedPtr< IDatasmithKeyValueProperty >& Property) = 0;` — Add a property to this actor
- L601 _public prototype_ `virtual void RemoveProperty(const TSharedPtr< IDatasmithKeyValueProperty >& Property) = 0;` — Removes a property from this actor, doesn't preserve ordering

#### class `IDatasmithLandscapeElement`  
`class IDatasmithLandscapeElement : public IDatasmithActorElement`  
_L604-614_
- inherits: `IDatasmithActorElement`
- L608 _public prototype_ `virtual void SetHeightmap(const TCHAR* FilePath) = 0;` — The path to the heightmap file
- L609 _public prototype_ `virtual const TCHAR* GetHeightmap() const = 0;`
- L612 _public prototype_ `virtual void SetMaterial(const TCHAR* MaterialPathName) = 0;` — The name or path to the material to assign to this landscape layer
- L613 _public prototype_ `virtual const TCHAR* GetMaterial() const = 0;`

#### class `IDatasmithMaterialIDElement`  
`class IDatasmithMaterialIDElement : public IDatasmithElement`  
_L616-623_
- inherits: `IDatasmithElement`
- L619 _public prototype_ `virtual ~IDatasmithMaterialIDElement() = default;`
- L621 _public prototype_ `virtual int32 GetId() const = 0;`
- L622 _public prototype_ `virtual void SetId(int32 Id) = 0;`

#### class `IDatasmithBaseMaterialElement`  
`class IDatasmithBaseMaterialElement : public IDatasmithElement`  
_L625-627_
- inherits: `IDatasmithElement`

#### class `IDatasmithMaterialElement`  
`class IDatasmithMaterialElement : public IDatasmithBaseMaterialElement`  
_L629-651_
- inherits: `IDatasmithBaseMaterialElement`
- L632 _public prototype_ `virtual ~IDatasmithMaterialElement() = default;`
- L635 _public prototype_ `virtual bool IsSingleShaderMaterial() const = 0;` — Returns true if the material has only one shader, false otherwise
- L638 _public prototype_ `virtual bool IsClearCoatMaterial() const = 0;` — Returns true if the material has a clear coat layer, false otherwise
- L641 _public prototype_ `virtual void AddShader(const TSharedPtr< IDatasmithShaderElement >& Shader) = 0;` — Adds a new shader to the material stack
- L644 _public prototype_ `virtual int32 GetShadersCount() const = 0;` — Get the total amount of shaders in this material
- L647 _public prototype_ `virtual TSharedPtr< IDatasmithShaderElement >& GetShader(int32 InIndex) = 0;` — Get the shader i-th of this material
- L650 _public prototype_ `virtual const TSharedPtr< IDatasmithShaderElement >& GetShader(int32 InIndex) const = 0;` — Get the shader i-th of this material

#### class `IDatasmithMaterialInstanceElement`  
`class IDatasmithMaterialInstanceElement : public IDatasmithBaseMaterialElement`  
_L653-679_
- inherits: `IDatasmithBaseMaterialElement`
- L656 _public prototype_ `virtual ~IDatasmithMaterialInstanceElement() = default;`
- L658 _public prototype_ `virtual EDatasmithReferenceMaterialType GetMaterialType() const = 0;`
- L659 _public prototype_ `virtual void SetMaterialType(EDatasmithReferenceMaterialType InType) = 0;`
- L661 _public prototype_ `virtual EDatasmithReferenceMaterialQuality GetQuality() const = 0;`
- L662 _public prototype_ `virtual void SetQuality(EDatasmithReferenceMaterialQuality InQuality) = 0;`
- L665 _public prototype_ `virtual const TCHAR* GetCustomMaterialPathName() const = 0;` — Only used when the material type is set to Custom. The path name to an existing material to instantiate.
- L666 _public prototype_ `virtual void SetCustomMaterialPathName(const TCHAR* InPathName) = 0;`
- L669 _public prototype_ `virtual int32 GetPropertiesCount() const = 0;` — Get the total amount of properties in this material
- L672 _public prototype_ `virtual const TSharedPtr< IDatasmithKeyValueProperty >& GetProperty(int32 i) const = 0;` — Get the property i-th of this material
- L675 _public prototype_ `virtual const TSharedPtr< IDatasmithKeyValueProperty >& GetPropertyByName(const TCHAR* Name) const = 0;` — Get a property by its name if it exists
- L678 _public prototype_ `virtual void AddProperty(const TSharedPtr< IDatasmithKeyValueProperty >& Property) = 0;` — Add a property to this material

#### class `IDatasmithDecalMaterialElement`  
`class IDatasmithDecalMaterialElement : public IDatasmithBaseMaterialElement`  
_L681-705_
- inherits: `IDatasmithBaseMaterialElement`
- L684 _public prototype_ `virtual ~IDatasmithDecalMaterialElement() = default;`
- L687 _public prototype_ `virtual const TCHAR* GetDiffuseTexturePathName() const = 0;` — Get path name of the diffuse texture associated with the material
- L694 _public prototype_ `virtual void SetDiffuseTexturePathName(const TCHAR* DiffuseTexturePathName) = 0;` — Set path name of the diffuse texture associated with the material The path name can be either a package path referring to an existing texture asset or a texture name referring a TextureElement in the DatasmithScene
- L697 _public prototype_ `virtual const TCHAR* GetNormalTexturePathName() const = 0;` — Get path name of the normal texture associated with the material
- L704 _public prototype_ `virtual void SetNormalTexturePathName(const TCHAR* NormalTexturePathName) = 0;` — Set path name of the normal texture associated with the material The path name can be either the name of a texture added to the Datasmith scene or a path to an Unreal asset

#### class `IDatasmithPostProcessElement`  
`class IDatasmithPostProcessElement : public IDatasmithElement`  
_L707-759_
- inherits: `IDatasmithElement`
- L711 _public prototype_ `virtual float GetTemperature() const = 0;` — Get color filter temperature in Kelvin
- L714 _public prototype_ `virtual void SetTemperature(float Temperature) = 0;` — Set color filter temperature in Kelvin
- L717 _public prototype_ `virtual FLinearColor GetColorFilter() const = 0;` — Set color filter in linear color scale
- L720 _public prototype_ `virtual void SetColorFilter(FLinearColor ColorFilter) = 0;` — Get color filter in linear color scale
- L723 _public prototype_ `virtual float GetVignette() const = 0;` — Get vignette amount
- L726 _public prototype_ `virtual void SetVignette(float Vignette) = 0;` — Set vignette amount
- L729 _public prototype_ `virtual float GetDof() const = 0;` — Get depth of field multiplier
- L732 _public prototype_ `virtual void SetDof(float Dof) = 0;` — Set depth of field multiplier
- L735 _public prototype_ `virtual float GetMotionBlur() const = 0;` — Get motion blur multiplier
- L738 _public prototype_ `virtual void SetMotionBlur(float MotionBlur) = 0;` — Set motion blur multiplier
- L741 _public prototype_ `virtual float GetSaturation() const = 0;` — Get color saturation
- L744 _public prototype_ `virtual void SetSaturation(float Saturation) = 0;` — Set color saturation
- L747 _public prototype_ `virtual float GetCameraISO() const = 0;` — Get camera ISO
- L750 _public prototype_ `virtual void SetCameraISO(float CameraISO) = 0;` — Set camera ISO
- L753 _public prototype_ `virtual float GetCameraShutterSpeed() const = 0;` — The camera shutter speed in 1/seconds (ie: 60 = 1/60s)
- L754 _public prototype_ `virtual void SetCameraShutterSpeed(float CameraShutterSpeed) = 0;`
- L757 _public prototype_ `virtual float GetDepthOfFieldFstop() const = 0;` — Defines the opening of the camera lens, Aperture is 1/fstop, typical lens go down to f/1.2 (large opening), larger numbers reduce the DOF effect
- L758 _public prototype_ `virtual void SetDepthOfFieldFstop(float Fstop) = 0;`

#### class `IDatasmithPostProcessVolumeElement`  
`class IDatasmithPostProcessVolumeElement : public IDatasmithActorElement`  
_L762-776_
- inherits: `IDatasmithActorElement`
- desc: Represents the APostProcessVolume object
- L766 _public prototype_ `virtual TSharedRef< IDatasmithPostProcessElement > GetSettings() const = 0;` — The post process settings to use for this volume.
- L767 _public prototype_ `virtual void SetSettings(const TSharedRef< IDatasmithPostProcessElement >& Settings) = 0;`
- L770 _public prototype_ `virtual bool GetEnabled() const = 0;` — Whether this volume is enabled or not.
- L771 _public prototype_ `virtual void SetEnabled(bool bEnabled) = 0;`
- L774 _public prototype_ `virtual bool GetUnbound() const = 0;` — Whether this volume covers the whole world, or just the area inside its bounds.
- L775 _public prototype_ `virtual void SetUnbound(bool bUnbound) = 0;`

#### class `IDatasmithEnvironmentElement`  
`class IDatasmithEnvironmentElement : public IDatasmithLightActorElement`  
_L778-797_
- inherits: `IDatasmithLightActorElement`
- L781 _public prototype_ `virtual ~IDatasmithEnvironmentElement() = default;`
- L784 _public prototype_ `virtual TSharedPtr<IDatasmithCompositeTexture>& GetEnvironmentComp() = 0;` — Get the environment map
- L787 _public prototype_ `virtual const TSharedPtr<IDatasmithCompositeTexture>& GetEnvironmentComp() const = 0;` — Get the environment map
- L790 _public prototype_ `virtual void SetEnvironmentComp(const TSharedPtr<IDatasmithCompositeTexture>& EnvironmentComp) = 0;` — Set the environment map
- L793 _public prototype_ `virtual bool GetIsIlluminationMap() const = 0;` — Returns true if it is used for illumination, false if it is used as background
- L796 _public prototype_ `virtual void SetIsIlluminationMap(bool bIsIlluminationMap) = 0;` — Set true for being used as illumination, false for being used as background

#### class `IDatasmithTextureElement`  
`class IDatasmithTextureElement : public IDatasmithElement`  
_L799-870_
- inherits: `IDatasmithElement`
- L802 _public prototype_ `virtual ~IDatasmithTextureElement() = default;`
- L805 _public prototype_ `virtual const TCHAR* GetFile() const = 0;` — Get texture filename
- L808 _public prototype_ `virtual void SetFile(const TCHAR* File) = 0;` — Set texture filename
- L818 _public prototype_ `virtual void SetData(const uint8* InData, uint32 InDataSize, EDatasmithTextureFormat InFormat) = 0;` — Set the output data buffer, used only when no output filename is set @param InData data to load the texture from @param InDataSize size in bytes of the buffer @param InFormat texture format(e.g. png or jpeg) @note The given data is not freed by the DatasmithImporter.
- L821 _public prototype_ `virtual const uint8* GetData(uint32& OutDataSize, EDatasmithTextureFormat& OutFormat) const = 0;` — Return the optional data, if loading from memory. Must be callable from any thread.
- L824 _public prototype_ `virtual FMD5Hash GetFileHash() const = 0;` — Return a MD5 hash of the content of the Texture Element. Used in CalculateElementHash to quickly identify Element with identical content
- L827 _public prototype_ `virtual void SetFileHash(FMD5Hash Hash) = 0;` — Set the MD5 hash of the current texture file. This should be a hash of its content.
- L830 _public prototype_ `virtual EDatasmithTextureMode GetTextureMode() const = 0;` — Get texture usage
- L833 _public prototype_ `virtual void SetTextureMode(EDatasmithTextureMode Mode) = 0;` — Set texture usage
- L836 _public prototype_ `virtual EDatasmithTextureFilter GetTextureFilter() const = 0;` — Get texture filter
- L839 _public prototype_ `virtual void SetTextureFilter(EDatasmithTextureFilter Filter) = 0;` — Set texture filter
- L842 _public prototype_ `virtual EDatasmithTextureAddress GetTextureAddressX() const = 0;` — Get texture X axis address mode
- L845 _public prototype_ `virtual void SetTextureAddressX(EDatasmithTextureAddress Mode) = 0;` — Set texture X axis address mode
- L848 _public prototype_ `virtual EDatasmithTextureAddress GetTextureAddressY() const = 0;` — Get texture Y axis address mode
- L851 _public prototype_ `virtual void SetTextureAddressY(EDatasmithTextureAddress Mode) = 0;` — Set texture Y axis address mode
- L854 _public prototype_ `virtual bool GetAllowResize() const = 0;` — Get allow texture resizing
- L857 _public prototype_ `virtual void SetAllowResize(bool bAllowResize) = 0;` — Set allow texture resizing
- L860 _public prototype_ `virtual float GetRGBCurve() const = 0;` — Get texture gamma <= 0 for auto
- L863 _public prototype_ `virtual void SetRGBCurve(const float InRGBCurve) = 0;` — Set texture gamma <= 0 for auto
- L866 _public prototype_ `virtual EDatasmithColorSpace GetSRGB() const = 0;` — Gets the color space of the texture
- L869 _public prototype_ `virtual void SetSRGB(EDatasmithColorSpace Option) = 0;` — Sets the color space of the texture

#### class `IDatasmithShaderElement`  
`class IDatasmithShaderElement : public IDatasmithElement`  
_L872-1269_
- inherits: `IDatasmithElement`
- L881 _public member_ `static bool bUseRealisticFresnel;` — Realistic fresnel creates a pretty more complex node tree based on the actual fresnel equation. If this param is not enabled an approximation will be used. It has no effect if bDisableReflectionFresnel is set to true.
- L884 _public member_ `static bool bDisableReflectionFresnel;` — If it is set to true no fresnel effect is applied on reflection and just a constant effect is assigned to the reflection slot
- L886 _public prototype_ `virtual ~IDatasmithShaderElement() = default;`
- L889 _public prototype_ `virtual double GetIOR() const = 0;` — Get the Ior N value, usually Ior K is set to 0 so this will control the entire reflection fresnel effect
- L892 _public prototype_ `virtual void SetIOR(double Value) = 0;` — Set the Ior N value, usually Ior K is set to 0 so this will control the entire reflection fresnel effect
- L895 _public prototype_ `virtual double GetIORk() const = 0;` — Get the Ior K effect, this is used for more advanced representations of the reflection fresnel effect
- L898 _public prototype_ `virtual void SetIORk(double Value) = 0;` — Set the Ior K effect, this is used for more advanced representations of the reflection fresnel effect
- L901 _public prototype_ `virtual double GetIORRefra() const = 0;` — Get the InIndex of Refraction value
- L904 _public prototype_ `virtual void SetIORRefra(double Value) = 0;` — Set the InIndex of Refraction value
- L907 _public prototype_ `virtual double GetBumpAmount() const = 0;` — Get the bump/normal amount
- L910 _public prototype_ `virtual void SetBumpAmount(double Value) = 0;` — Set the bump/normal amount
- L913 _public prototype_ `virtual bool GetTwoSided() const = 0;` — Get the two sided material attribute
- L916 _public prototype_ `virtual void SetTwoSided(bool Value) = 0;` — Set the two sided material attribute
- L919 _public prototype_ `virtual FLinearColor GetDiffuseColor() const = 0;` — Get the diffuse color in linear space
- L922 _public prototype_ `virtual void SetDiffuseColor(FLinearColor Value) = 0;` — Set the diffuse color in linear space
- L925 _public prototype_ `virtual const TCHAR* GetDiffuseTexture() const = 0;` — Get the diffuse filename
- L928 _public prototype_ `virtual void SetDiffuseTexture(const TCHAR* Value) = 0;` — Set the diffuse filename
- L931 _public prototype_ `virtual FDatasmithTextureSampler GetDiffTextureSampler() const = 0;` — Get the diffuse UV coordinates
- L934 _public prototype_ `virtual void SetDiffTextureSampler(FDatasmithTextureSampler Value) = 0;` — Set the diffuse UV coordinates
- L937 _public prototype_ `virtual TSharedPtr<IDatasmithCompositeTexture>& GetDiffuseComp() = 0;` — Get the diffuse compound map
- L940 _public prototype_ `virtual const TSharedPtr<IDatasmithCompositeTexture>& GetDiffuseComp() const = 0;` — Get the diffuse compound map
- L943 _public prototype_ `virtual void SetDiffuseComp(const TSharedPtr<IDatasmithCompositeTexture>& Value) = 0;` — Set the diffuse compound map
- L946 _public prototype_ `virtual FLinearColor GetReflectanceColor() const = 0;` — Get the reflectance color in linear space
- L949 _public prototype_ `virtual void SetReflectanceColor(FLinearColor Value) = 0;` — Set the reflectance color in linear space
- L952 _public prototype_ `virtual const TCHAR* GetReflectanceTexture() const = 0;` — Get the reflectance filename
- L955 _public prototype_ `virtual void SetReflectanceTexture(const TCHAR* Value) = 0;` — Set the reflectance filename
- L958 _public prototype_ `virtual FDatasmithTextureSampler GetRefleTextureSampler() const = 0;` — Get the reflectance UV coordinates
- L961 _public prototype_ `virtual void SetRefleTextureSampler(FDatasmithTextureSampler Value) = 0;` — Set the reflectance UV coordinates
- L964 _public prototype_ `virtual TSharedPtr<IDatasmithCompositeTexture>& GetRefleComp() = 0;` — Get the reflectance compound map
- L967 _public prototype_ `virtual const TSharedPtr<IDatasmithCompositeTexture>& GetRefleComp() const = 0;` — Get the reflectance compound map
- L970 _public prototype_ `virtual void SetRefleComp(const TSharedPtr<IDatasmithCompositeTexture>& Value) = 0;` — Set the reflectance compound map
- L973 _public prototype_ `virtual double GetRoughness() const = 0;` — Get the roughness color in linear space
- L976 _public prototype_ `virtual void SetRoughness(double Value) = 0;` — Set the roughness color in linear space
- L979 _public prototype_ `virtual const TCHAR* GetRoughnessTexture() const = 0;` — Get the roughness filename
- L982 _public prototype_ `virtual void SetRoughnessTexture(const TCHAR* Value) = 0;` — Set the roughness filename
- L985 _public prototype_ `virtual FDatasmithTextureSampler GetRoughTextureSampler() const = 0;` — Get the roughness UV coordinates
- L988 _public prototype_ `virtual void SetRoughTextureSampler(FDatasmithTextureSampler Value) = 0;` — Set the roughness UV coordinates
- L991 _public prototype_ `virtual TSharedPtr<IDatasmithCompositeTexture>& GetRoughnessComp() = 0;` — Get the roughness compound map
- L994 _public prototype_ `virtual const TSharedPtr<IDatasmithCompositeTexture>& GetRoughnessComp() const = 0;` — Get the roughness compound map
- L997 _public prototype_ `virtual void SetRoughnessComp(const TSharedPtr<IDatasmithCompositeTexture>& Value) = 0;` — Set the roughness compound map
- L1000 _public prototype_ `virtual const TCHAR* GetNormalTexture() const = 0;` — Get the normalmapping filename
- L1003 _public prototype_ `virtual void SetNormalTexture(const TCHAR* Value) = 0;` — Set the normalmapping filename
- L1006 _public prototype_ `virtual FDatasmithTextureSampler GetNormalTextureSampler() const = 0;` — Get the normalmapping UV coordinates
- L1009 _public prototype_ `virtual void SetNormalTextureSampler(FDatasmithTextureSampler Value) = 0;` — Set the normalmapping UV coordinates
- L1012 _public prototype_ `virtual TSharedPtr<IDatasmithCompositeTexture>& GetNormalComp() = 0;` — Get the normalmapping compound map
- L1015 _public prototype_ `virtual const TSharedPtr<IDatasmithCompositeTexture>& GetNormalComp() const = 0;` — Get the normalmapping compound map
- L1018 _public prototype_ `virtual void SetNormalComp(const TSharedPtr<IDatasmithCompositeTexture>& Value) = 0;` — Set the normalmapping compound map
- L1021 _public prototype_ `virtual const TCHAR* GetBumpTexture() const = 0;` — Get the bumpmapping filename
- L1024 _public prototype_ `virtual void SetBumpTexture(const TCHAR* Value) = 0;` — Set the bumpmapping filename
- L1027 _public prototype_ `virtual FDatasmithTextureSampler GetBumpTextureSampler() const = 0;` — Get the bumpmapping UV coordinates
- L1030 _public prototype_ `virtual void SetBumpTextureSampler(FDatasmithTextureSampler Value) = 0;` — Set the bumpmapping UV coordinates
- L1033 _public prototype_ `virtual TSharedPtr<IDatasmithCompositeTexture>& GetBumpComp() = 0;` — Get the bumpmapping compound map
- L1036 _public prototype_ `virtual const TSharedPtr<IDatasmithCompositeTexture>& GetBumpComp() const = 0;` — Get the bumpmapping compound map
- L1039 _public prototype_ `virtual void SetBumpComp(const TSharedPtr<IDatasmithCompositeTexture>& Value) = 0;` — Set the bumpmapping compound map
- L1042 _public prototype_ `virtual FLinearColor GetTransparencyColor() const = 0;` — Get the transparency color in linear space
- L1045 _public prototype_ `virtual void SetTransparencyColor(FLinearColor Value) = 0;` — Set the transparency color in linear space
- L1048 _public prototype_ `virtual const TCHAR* GetTransparencyTexture() const = 0;` — Get the transparency filename
- L1051 _public prototype_ `virtual void SetTransparencyTexture(const TCHAR* Value) = 0;` — Set the transparency filename
- L1054 _public prototype_ `virtual FDatasmithTextureSampler GetTransTextureSampler() const = 0;` — Get the transparency UV coordinates
- L1057 _public prototype_ `virtual void SetTransTextureSampler(FDatasmithTextureSampler Value) = 0;` — Set the transparency UV coordinates
- L1060 _public prototype_ `virtual TSharedPtr<IDatasmithCompositeTexture>& GetTransComp() = 0;` — Get the transparency compound map
- L1063 _public prototype_ `virtual const TSharedPtr<IDatasmithCompositeTexture>& GetTransComp() const = 0;` — Get the transparency compound map
- L1066 _public prototype_ `virtual void SetTransComp(const TSharedPtr<IDatasmithCompositeTexture>& Value) = 0;` — Set the transparency compound map
- L1069 _public prototype_ `virtual const TCHAR* GetMaskTexture() const = 0;` — Get the opacity mask filename
- L1072 _public prototype_ `virtual void SetMaskTexture(const TCHAR* Value) = 0;` — Set the opacity mask filename
- L1075 _public prototype_ `virtual FDatasmithTextureSampler GetMaskTextureSampler() const = 0;` — Get the opacity mask UV coordinates
- L1078 _public prototype_ `virtual void SetMaskTextureSampler(FDatasmithTextureSampler Value) = 0;` — Set the opacity mask UV coordinates
- L1081 _public prototype_ `virtual TSharedPtr<IDatasmithCompositeTexture>& GetMaskComp() = 0;` — Get the opacity mask compound map
- L1084 _public prototype_ `virtual const TSharedPtr<IDatasmithCompositeTexture>& GetMaskComp() const = 0;` — Get the opacity mask compound map
- L1087 _public prototype_ `virtual void SetMaskComp(const TSharedPtr<IDatasmithCompositeTexture>& Value) = 0;` — Set the opacity mask compound map
- L1090 _public prototype_ `virtual double GetMetal() const = 0;` — Get the metalness value
- L1093 _public prototype_ `virtual void SetMetal(double Value) = 0;` — Set the metalness value
- L1096 _public prototype_ `virtual const TCHAR* GetMetalTexture() const = 0;` — Get the metalness filename
- L1099 _public prototype_ `virtual void SetMetalTexture(const TCHAR* Value) = 0;` — Set the metalness filename
- L1102 _public prototype_ `virtual FDatasmithTextureSampler GetMetalTextureSampler() const = 0;` — Get the metalness UV coordinates
- L1105 _public prototype_ `virtual void SetMetalTextureSampler(FDatasmithTextureSampler Value) = 0;` — Set the metalness UV coordinates
- L1108 _public prototype_ `virtual TSharedPtr<IDatasmithCompositeTexture>& GetMetalComp() = 0;` — Get the metalness compound map
- L1111 _public prototype_ `virtual const TSharedPtr<IDatasmithCompositeTexture>& GetMetalComp() const = 0;` — Get the metalness compound map
- L1114 _public prototype_ `virtual void SetMetalComp(const TSharedPtr<IDatasmithCompositeTexture>& Value) = 0;` — Set the metalness compound map
- L1117 _public prototype_ `virtual FLinearColor GetEmitColor() const = 0;` — Get the emittance color in linear space
- L1120 _public prototype_ `virtual void SetEmitColor(FLinearColor Value) = 0;` — Set the emittance color in linear space
- L1123 _public prototype_ `virtual const TCHAR* GetEmitTexture() const = 0;` — Get the emittance filename
- L1126 _public prototype_ `virtual void SetEmitTexture(const TCHAR* Value) = 0;` — Set the emittance filename
- L1129 _public prototype_ `virtual FDatasmithTextureSampler GetEmitTextureSampler() const = 0;` — Get the emittance UV coordinates
- L1132 _public prototype_ `virtual void SetEmitTextureSampler(FDatasmithTextureSampler Value) = 0;` — Set the emittance UV coordinates
- L1135 _public prototype_ `virtual double GetEmitTemperature() const = 0;` — Get the emittance temperature color
- L1138 _public prototype_ `virtual void SetEmitTemperature(double Value) = 0;` — Set the emittance temperature color
- L1141 _public prototype_ `virtual double GetEmitPower() const = 0;` — Get the emittance power in lumens
- L1144 _public prototype_ `virtual void SetEmitPower(double Value) = 0;` — Set the emittance power in lumens
- L1147 _public prototype_ `virtual TSharedPtr<IDatasmithCompositeTexture>& GetEmitComp() = 0;` — Get the emittance compound map
- L1150 _public prototype_ `virtual const TSharedPtr<IDatasmithCompositeTexture>& GetEmitComp() const = 0;` — Get the emittance compound map
- L1153 _public prototype_ `virtual void SetEmitComp(const TSharedPtr<IDatasmithCompositeTexture>& Value) = 0;` — Set the emittance compound map
- L1160 _public prototype_ `virtual bool GetLightOnly() const = 0;` — Gets material is used as lighting only. If true the material sets the lighting mode to Unlit, regular lighting mode otherwise.
- L1166 _public prototype_ `virtual void SetLightOnly(bool Value) = 0;` — Sets material is used as lighting only. If true the material sets the lighting mode to Unlit, regular lighting mode otherwise.
- L1172 _public prototype_ `virtual FLinearColor GetWeightColor() const = 0;` — Get the weight color in linear space. Weight color, texture and value are only used for multilayered materials.
- L1178 _public prototype_ `virtual void SetWeightColor(FLinearColor Value) = 0;` — Set the weight color in linear space. Weight color, texture and value are only used for multilayered materials.
- L1184 _public prototype_ `virtual const TCHAR* GetWeightTexture() const = 0;` — Get the weight filename Weight color, texture and value are only used for multilayered materials.
- L1190 _public prototype_ `virtual void SetWeightTexture(const TCHAR* Value) = 0;` — Set the weight filename Weight color, texture and value are only used for multilayered materials.
- L1196 _public prototype_ `virtual FDatasmithTextureSampler GetWeightTextureSampler() const = 0;` — Get the weight UV coordinates Weight color, texture and value are only used for multilayered materials.
- L1202 _public prototype_ `virtual void SetWeightTextureSampler(FDatasmithTextureSampler Value) = 0;` — Set the weight UV coordinates Weight color, texture and value are only used for multilayered materials.
- L1208 _public prototype_ `virtual TSharedPtr<IDatasmithCompositeTexture>& GetWeightComp() = 0;` — Get the weight compound map Weight color, texture and value are only used for multilayered materials.
- L1214 _public prototype_ `virtual const TSharedPtr<IDatasmithCompositeTexture>& GetWeightComp() const = 0;` — Get the weight compound map Weight color, texture and value are only used for multilayered materials.
- L1220 _public prototype_ `virtual void SetWeightComp(const TSharedPtr<IDatasmithCompositeTexture>& Value) = 0;` — Set the weight compound map Weight color, texture and value are only used for multilayered materials.
- L1226 _public prototype_ `virtual double GetWeightValue() const = 0;` — Get the weight power value Weight color, texture and value are only used for multilayered materials.
- L1232 _public prototype_ `virtual void SetWeightValue(double Value) = 0;` — Set the weight power value Weight color, texture and value are only used for multilayered materials.
- L1238 _public prototype_ `virtual EDatasmithBlendMode GetBlendMode() const = 0;` — Get the blending mode. It only has effect on multilayered materials and all the layers but layer 0.
- L1244 _public prototype_ `virtual void SetBlendMode(EDatasmithBlendMode Value) = 0;` — Set the blending mode. It only has effect on multilayered materials and all the layers but layer 0.
- L1250 _public prototype_ `virtual bool GetIsStackedLayer() const = 0;` — Get the if this layer is weighted as a stack. It only has effect on multilayered materials and all the layers but layer 0.
- L1256 _public prototype_ `virtual void SetIsStackedLayer(bool Value) = 0;` — Set the if this layer is weighted as a stack. It only has effect on multilayered materials and all the layers but layer 0.
- L1259 _public prototype_ `virtual const EDatasmithShaderUsage GetShaderUsage() const = 0;` — Get the domain of this shader
- L1262 _public prototype_ `virtual void SetShaderUsage(EDatasmithShaderUsage InMaterialUsage) = 0;` — Set the domain of this shader
- L1265 _public prototype_ `virtual const bool GetUseEmissiveForDynamicAreaLighting() const = 0;` — Set use Emissive for dynamic area lighting
- L1268 _public prototype_ `virtual void SetUseEmissiveForDynamicAreaLighting(bool InUseEmissiveForDynamicAreaLighting) = 0;` — Get use Emissive for dynamic area lighting

#### class `IDatasmithCompositeTexture`  
`class IDatasmithCompositeTexture`  
_L1271-1407_
- L1274 _public typedef_ `typedef TPair<float, const TCHAR*> ParamVal;`
- L1276 _public prototype_ `virtual ~IDatasmithCompositeTexture() = default;`
- L1282 _public prototype_ `virtual bool IsValid() const = 0;` — Gets the validity of the composite texture. If it returns false probably you should use the regular texture or color.
- L1285 _public prototype_ `virtual EDatasmithCompMode GetMode() const = 0;` — Gets the composition mode like color correction etc
- L1288 _public prototype_ `virtual void SetMode(EDatasmithCompMode Mode) = 0;` — Sets the composition mode like color correction etc
- L1291 _public prototype_ `virtual int32 GetParamSurfacesCount() const = 0;` — Get the number of surfaces.
- L1297 _public prototype_ `virtual bool GetUseTexture(int32 i) = 0;` — Gets texture usage. If it returns false you should use a value or a color checking GetUseColor(i).
- L1300 _public prototype_ `virtual const TCHAR* GetParamTexture(int32 i) = 0;` — Get the filename of the i-th texture
- L1303 _public prototype_ `virtual void SetParamTexture(int32 InIndex, const TCHAR* InTexture) = 0;` — Sets the new texture for the index-th item
- L1306 _public prototype_ `virtual FDatasmithTextureSampler& GetParamTextureSampler(int32 i) = 0;` — Get the i-th uv element
- L1312 _public prototype_ `virtual bool GetUseColor(int32 i) = 0;` — Gets color usage. If true color is used, else a value is used.
- L1315 _public prototype_ `virtual const FLinearColor& GetParamColor(int32 i) = 0;` — Get the i-th color in linear space
- L1318 _public prototype_ `virtual bool GetUseComposite(int32 i) = 0;` — Returns true if composite texture should be used
- L1324 _public prototype_ `virtual int32 GetParamVal1Count() const = 0;` — Get the number of value1 parameters. Some composites will use no values, other types could use only one value, and others could use two values.
- L1327 _public prototype_ `virtual ParamVal GetParamVal1(int32 i) const = 0;` — Get the i-th Value1 parameter
- L1330 _public prototype_ `virtual void AddParamVal1(ParamVal InParamVal) = 0;` — Add a new Value1 parameter
- L1336 _public prototype_ `virtual int32 GetParamVal2Count() const = 0;` — Get the number of value2 parameters. Some composites will use no values, other types could use only one value, and others could use two values.
- L1339 _public prototype_ `virtual ParamVal GetParamVal2(int32 i) const = 0;` — Get the Value2 parameter
- L1342 _public prototype_ `virtual void AddParamVal2(ParamVal InParamVal) = 0;` — Add a new Value2 parameter
- L1345 _public prototype_ `virtual TSharedPtr<IDatasmithCompositeTexture>& GetParamSubComposite(int32 i) = 0;` — Get the i-th nested composite texture
- L1348 _public prototype_ `virtual void AddSurface(const TSharedPtr<IDatasmithCompositeTexture>& SubComp) = 0;` — Adds a new nested composite texture
- L1351 _public prototype_ `virtual int32 GetParamMaskSurfacesCount() const = 0;` — Get the amount of layer masks
- L1354 _public prototype_ `virtual const TCHAR* GetParamMask(int32 i) = 0;` — Get the i-th layer mask's filename
- L1357 _public prototype_ `virtual void AddMaskSurface(const TCHAR* InMask, const FDatasmithTextureSampler InMaskSampler) = 0;` — Adds a new layer mask from its filename
- L1360 _public prototype_ `virtual FDatasmithTextureSampler GetParamMaskTextureSampler(int32 i) = 0;` — Get the ith layer mask's uv element
- L1363 _public prototype_ `virtual TSharedPtr<IDatasmithCompositeTexture>& GetParamMaskSubComposite(int32 i) = 0;` — Get the ith composite texture inside this composite used as layer mask
- L1366 _public prototype_ `virtual const FLinearColor& GetParamMaskColor(int32 i) const = 0;` — Get the i-th color in linear space
- L1369 _public prototype_ `virtual bool GetMaskUseComposite(int32 i) const = 0;` — Returns true if composite texture mask should be used
- L1372 _public prototype_ `virtual void AddMaskSurface(const TSharedPtr<IDatasmithCompositeTexture>& MaskSubComp) = 0;` — Adds a new composite texture inside this composite used as layer mask
- L1375 _public prototype_ `virtual void AddMaskSurface(const FLinearColor& Color) = 0;` — Creates a new surface to be used as mask that will be used as layer inside this composite using a color in linear space.
- L1378 _public prototype_ `virtual const TCHAR* GetBaseTextureName() const = 0;` — Returns the string that identifies the texture element
- L1381 _public prototype_ `virtual const TCHAR* GetBaseColName() const = 0;` — Returns the string that identifies the color element
- L1384 _public prototype_ `virtual const TCHAR* GetBaseValName() const = 0;` — Returns the string that identifies the value element
- L1387 _public prototype_ `virtual const TCHAR* GetBaseCompName() const = 0;` — Returns the string that identifies the composite element
- L1397 _public prototype_ `virtual void SetBaseNames(const TCHAR* InTextureName, const TCHAR* InColorName, const TCHAR* InValueName, const TCHAR* InCompName) = 0;` — Sets the strings that identifies the different elements on this composite @param InTextureName	for plain textures @param InColorName	for color elements @param InValueName	for regular float values @param InCompName	for nested composite elements inside this composite
- L1400 _public prototype_ `virtual void AddSurface(const TCHAR* Texture, FDatasmithTextureSampler TexUV) = 0;` — Creates a new surface that will be used as layer inside this composite using the texture filename and its uv element.
- L1403 _public prototype_ `virtual void AddSurface(const FLinearColor& Color) = 0;` — Creates a new surface that will be used as layer inside this composite using a color in linear space.
- L1406 _public prototype_ `virtual void ClearSurface() = 0;` — Purges all the surfaces that could be used as layers inside this composite.

#### class `IDatasmithMetaDataElement`  
`class IDatasmithMetaDataElement : public IDatasmithElement`  
_L1409-1435_
- inherits: `IDatasmithElement`
- L1413 _public prototype_ `virtual const TSharedPtr< IDatasmithElement >& GetAssociatedElement() const = 0;` — Gets the Datasmith element that is associated with this meta data, if any
- L1416 _public prototype_ `virtual void SetAssociatedElement(const TSharedPtr< IDatasmithElement >& Element) = 0;` — Sets the Datasmith element that is associated with this meta data, if any
- L1419 _public prototype_ `virtual int32 GetPropertiesCount() const = 0;` — Get the total amount of properties in this meta data
- L1422 _public prototype_ `virtual const TSharedPtr< IDatasmithKeyValueProperty >& GetProperty(int32 i) const = 0;` — Get the property i-th of this meta data
- L1425 _public prototype_ `virtual const TSharedPtr< IDatasmithKeyValueProperty >& GetPropertyByName(const TCHAR* Name) const = 0;` — Get a property by its name if it exists
- L1428 _public prototype_ `virtual void AddProperty(const TSharedPtr< IDatasmithKeyValueProperty >& Property) = 0;` — Add a property to this meta data
- L1431 _public prototype_ `virtual void RemoveProperty( const TSharedPtr<IDatasmithKeyValueProperty>& Property ) = 0;` — Remove the property from this meta data
- L1434 _public prototype_ `virtual void ResetProperties() = 0;` — Remove all properties in this meta data

#### class `IDatasmithDecalActorElement`  
`class IDatasmithDecalActorElement : public IDatasmithCustomActorElement`  
_L1437-1463_
- inherits: `IDatasmithCustomActorElement`
- L1441 _public prototype_ `virtual FVector GetDimensions() const = 0;` — Get the Decal element size
- L1444 _public prototype_ `virtual void SetDimensions(const FVector&) = 0;` — Set the Decal element size
- L1447 _public prototype_ `virtual const TCHAR* GetDecalMaterialPathName() const = 0;` — Get the path name of the Material associated with the actor
- L1456 _public prototype_ `virtual void SetDecalMaterialPathName(const TCHAR*) = 0;` — Set the path name of the Material that the Decal actor uses It can be either a package path referring to an existing material asset or a material name referring a DecalMaterialElement in the DatasmithScene If this is not a DecalMaterialElement or a material with its material domain as DeferredDecal The DecalActor generated in Unreal at import will use its default material
- L1459 _public prototype_ `virtual int32 GetSortOrder() const = 0;` — Get the order in which Decal element is rendered.
- L1462 _public prototype_ `virtual void SetSortOrder(int32) = 0;` — Set the order in which decal elements are rendered.  Higher values draw later (on top).

#### class `IDatasmithScene`  
`class IDatasmithScene : public IDatasmithElement`  
_L1465-1813_
- inherits: `IDatasmithElement`
- L1468 _public prototype_ `virtual ~IDatasmithScene() = default;`
- L1471 _public prototype_ `virtual void Reset() = 0;` — Resets all the settings on the scene
- L1474 _public prototype_ `virtual const TCHAR* GetHost() const = 0;` — Returns the name of the host application which created the scene
- L1481 _public prototype_ `virtual void SetHost(const TCHAR*) = 0;` — Sets the name of the host application from which we're exporting from. @param InHost	The host application name
- L1484 _public prototype_ `virtual const TCHAR* GetExporterVersion() const = 0;` — Returns the Datasmith format version used to export the scene
- L1492 _public prototype_ `virtual void SetExporterVersion(const TCHAR*) = 0;` — Sets the Datasmith version used to export the scene. Only needs to be set when parsing the .udatasmith during import @param InVersion	The Datasmith version number as string
- L1495 _public prototype_ `virtual const TCHAR* GetExporterSDKVersion() const = 0;` — Return the enterprise version of the SDK used by the exporter
- L1503 _public prototype_ `virtual void SetExporterSDKVersion(const TCHAR*) = 0;` — Sets the enterprise SDK version used to export the scene. Only needs to be set when parsing the .udatasmith during import @param InVersion	The Datasmith version number as string
- L1506 _public prototype_ `virtual const TCHAR* GetVendor() const = 0;` — Returns the vendor name of the application used to export the scene
- L1513 _public prototype_ `virtual void SetVendor(const TCHAR*) = 0;` — Sets the vendor name of the application used to export the scene. @param InVendor	The application vendor name
- L1516 _public prototype_ `virtual const TCHAR* GetProductName() const = 0;` — Returns the product name of the application used to export the scene
- L1523 _public prototype_ `virtual void SetProductName(const TCHAR*) = 0;` — Sets the product name of the application used to export the scene. @param InProductName	The application name
- L1526 _public prototype_ `virtual const TCHAR* GetProductVersion() const = 0;` — Returns the product version of the application used to export the scene
- L1533 _public prototype_ `virtual void SetProductVersion(const TCHAR*) = 0;` — Sets the product version of the application used to export the scene. @param InProductVersion	The application version
- L1536 _public prototype_ `virtual const TCHAR* GetResourcePath() const = 0;` — Returns the ';' separated list of paths where resources are stored
- L1543 _public prototype_ `virtual void SetResourcePath(const TCHAR*) = 0;` — Similar to how the PATH environment variable works, sets list of paths where resources can be stored. @param InResoucePath	The ';' separated list of paths
- L1546 _public prototype_ `virtual const TCHAR* GetUserID() const = 0;` — Returns the user identifier who exported the scene
- L1553 _public prototype_ `virtual void SetUserID(const TCHAR*) = 0;` — Sets the user identifier who exported the scene. @param InUserID	The user identifier
- L1556 _public prototype_ `virtual const TCHAR* GetUserOS() const = 0;` — Returns the OS name used by user who exported the scene
- L1563 _public prototype_ `virtual void SetUserOS(const TCHAR*) = 0;` — Sets the user's OS name. @param InUserOS	The OS name
- L1568 _public prototype_ `virtual FVector GetGeolocation() const = 0;` — Get Geolocation data of the scene. Where X = Latitude, Y = Longitude, Z = Elevation Components are initialized to TNumericLimits<double>::Max() to indicate they are not "set"
- L1570 _public prototype_ `virtual void SetGeolocationLatitude(double) = 0;`
- L1571 _public prototype_ `virtual void SetGeolocationLongitude(double) = 0;`
- L1572 _public prototype_ `virtual void SetGeolocationElevation(double) = 0;`
- L1575 _public prototype_ `virtual int32 GetExportDuration() const = 0;` — Returns the time taken to export the scene
- L1582 _public prototype_ `virtual void SetExportDuration(int32) = 0;` — Sets the time taken to export the scene. @param InExportDuration	The export duration (in seconds)
- L1589 _public prototype_ `virtual bool GetUsePhysicalSky() const = 0;` — Physical Sky could be generated in a large amount of modes, like material, lights etc that's why it has been added as static, just enable it and it is done. Notice that if a HDRI environment is used this gets disabled.
- L1595 _public prototype_ `virtual void SetUsePhysicalSky(bool bInUsePhysicalSky) = 0;` — Enable or disable the usage of Physical Sky Notice that if a HDRI environment is used this gets disabled.
- L1602 _public prototype_ `virtual void AddMesh(const TSharedPtr< IDatasmithMeshElement >& InMesh) = 0;` — Adds a new Mesh to the scene. @param InMesh	the Mesh that will be added
- L1605 _public prototype_ `virtual int32 GetMeshesCount() const = 0;` — Returns the amount of meshes added to the scene
- L1608 _public prototype_ `virtual TSharedPtr< IDatasmithMeshElement > GetMesh(int32 InIndex) = 0;` — Returns the mesh using this index
- L1611 _public prototype_ `virtual const TSharedPtr< IDatasmithMeshElement >& GetMesh(int32 InIndex) const = 0;` — Returns the mesh using this index
- L1618 _public prototype_ `virtual void RemoveMesh(const TSharedPtr< IDatasmithMeshElement >& InMesh) = 0;` — Remove a Mesh to the scene. @param InMesh	the Mesh that will be removed
- L1623 _public prototype_ `virtual void RemoveMeshAt(int32 InIndex) = 0;` — Removes from the scene the Mesh element at the specified index.
- L1628 _public prototype_ `virtual void EmptyMeshes() = 0;` — Remove all meshes from the scene
- L1632 _public prototype_ `virtual void AddCloth(const TSharedPtr< IDatasmithClothElement >& InElement) = 0;` — `UE_DEPRECATED(5.5, "The experimental Cloth importer is no longer supported.")`
- L1634 _public prototype_ `virtual int32 GetClothesCount() const = 0;` — `UE_DEPRECATED(5.5, "The experimental Cloth importer is no longer supported.")`
- L1636 _public prototype_ `virtual TSharedPtr< IDatasmithClothElement > GetCloth(int32 InIndex) = 0;` — `UE_DEPRECATED(5.5, "The experimental Cloth importer is no longer supported.")`
- L1638 _public prototype_ `virtual const TSharedPtr< IDatasmithClothElement >& GetCloth(int32 InIndex) const = 0;` — `UE_DEPRECATED(5.5, "The experimental Cloth importer is no longer supported.")`
- L1640 _public prototype_ `virtual void RemoveCloth(const TSharedPtr< IDatasmithClothElement >& InElement) = 0;` — `UE_DEPRECATED(5.5, "The experimental Cloth importer is no longer supported.")`
- L1642 _public prototype_ `virtual void RemoveClothAt(int32 InIndex) = 0;` — `UE_DEPRECATED(5.5, "The experimental Cloth importer is no longer supported.")`
- L1644 _public prototype_ `virtual void EmptyClothes() = 0;` — `UE_DEPRECATED(5.5, "The experimental Cloth importer is no longer supported.")`
- L1652 _public prototype_ `virtual void AddActor(const TSharedPtr< IDatasmithActorElement >& InActor) = 0;` — Adds an Actor to the scene. @param InActor the Actor that will be added
- L1655 _public prototype_ `virtual int32 GetActorsCount() const = 0;` — Returns the amount of actors added to the scene
- L1658 _public prototype_ `virtual TSharedPtr< IDatasmithActorElement > GetActor(int32 InIndex) = 0;` — Returns the actor using this index
- L1661 _public prototype_ `virtual const TSharedPtr< IDatasmithActorElement >& GetActor(int32 InIndex) const = 0;` — Returns the actor using this index
- L1668 _public prototype_ `virtual void RemoveActor(const TSharedPtr< IDatasmithActorElement >& InActor, EDatasmithActorRemovalRule RemoveRule) = 0;` — Remove Actor from the scene. @param InActor the Actor that will be removed
- L1673 _public prototype_ `virtual void RemoveActorAt(int32 InIndex, EDatasmithActorRemovalRule RemoveRule) = 0;` — Removes from the scene the Actor at the specified index.
- L1680 _public prototype_ `virtual void AddMaterial(const TSharedPtr< IDatasmithBaseMaterialElement >& InMaterial) = 0;` — Adds a new Material to the scene (it won't be applied to any mesh). @param InMaterial the Material that will be added
- L1683 _public prototype_ `virtual int32 GetMaterialsCount() const = 0;` — Returns the amount of materials added to the scene
- L1684 _public prototype_ `virtual TSharedPtr< IDatasmithBaseMaterialElement > GetMaterial(int32 InIndex) = 0;`
- L1685 _public prototype_ `virtual const TSharedPtr< IDatasmithBaseMaterialElement >& GetMaterial(int32 InIndex) const = 0;`
- L1692 _public prototype_ `virtual void RemoveMaterial(const TSharedPtr< IDatasmithBaseMaterialElement >& InMaterial) = 0;` — Removes a Material Element from the scene. @param InMaterial the Material Element to remove
- L1697 _public prototype_ `virtual void RemoveMaterialAt(int32 InIndex) = 0;` — Removes from the scene the Material Element at the specified index.
- L1702 _public prototype_ `virtual void EmptyMaterials() = 0;` — Remove all materials from the scene
- L1709 _public prototype_ `virtual void AddTexture(const TSharedPtr< IDatasmithTextureElement >& InTexture) = 0;` — Adds a new Texture Element to the scene (it won't be applied to any material). @param InTexture the Texture Element that will be added
- L1712 _public prototype_ `virtual int32 GetTexturesCount() const = 0;` — Returns the amount of textures added to the scene
- L1713 _public prototype_ `virtual TSharedPtr< IDatasmithTextureElement > GetTexture(int32 InIndex) = 0;`
- L1714 _public prototype_ `virtual const TSharedPtr< IDatasmithTextureElement >& GetTexture(int32 InIndex) const = 0;`
- L1721 _public prototype_ `virtual void RemoveTexture(const TSharedPtr< IDatasmithTextureElement >& InTexture) = 0;` — Removes a Texture Element from the scene. @param InTexture the Texture Element that will be removed
- L1726 _public prototype_ `virtual void RemoveTextureAt(int32 InIndex) = 0;` — Removes from the scene the Texture element at the specified index.
- L1731 _public prototype_ `virtual void EmptyTextures() = 0;` — Remove all textures from the scene
- L1739 _public prototype_ `virtual void SetPostProcess(const TSharedPtr< IDatasmithPostProcessElement >& InPostProcess) = 0;` — Set a new Postprocess for the scene @param InPostProcess the Environment that will be added
- L1740 _public prototype_ `virtual TSharedPtr< IDatasmithPostProcessElement > GetPostProcess() = 0;`
- L1741 _public prototype_ `virtual const TSharedPtr< IDatasmithPostProcessElement >& GetPostProcess() const = 0;`
- L1747 _public prototype_ `virtual void AddMetaData(const TSharedPtr< IDatasmithMetaDataElement >& InMetaData) = 0;` — Add a metadata to the scene There should be only one metadata per Datasmith element (the element associated with the metadata)
- L1749 _public prototype_ `virtual int32 GetMetaDataCount() const = 0;`
- L1750 _public prototype_ `virtual TSharedPtr< IDatasmithMetaDataElement > GetMetaData(int32 InIndex) = 0;`
- L1751 _public prototype_ `virtual const TSharedPtr< IDatasmithMetaDataElement >& GetMetaData(int32 InIndex) const = 0;`
- L1752 _public prototype_ `virtual TSharedPtr< IDatasmithMetaDataElement > GetMetaData(const TSharedPtr<IDatasmithElement>& Element) = 0;`
- L1753 _public prototype_ `virtual const TSharedPtr< IDatasmithMetaDataElement >& GetMetaData(const TSharedPtr<IDatasmithElement>& Element) const = 0;`
- L1754 _public prototype_ `virtual void RemoveMetaData( const TSharedPtr<IDatasmithMetaDataElement>& Element ) = 0;`
- L1755 _public prototype_ `virtual void RemoveMetaDataAt(int32 InIndex) = 0;`
- L1762 _public prototype_ `virtual void AddLevelSequence(const TSharedRef< IDatasmithLevelSequenceElement >& InSequence) = 0;` — Adds a level sequence to the scene. @param InSequence the level sequence to add
- L1765 _public prototype_ `virtual int32 GetLevelSequencesCount() const = 0;` — Returns the number of level sequences in the scene
- L1768 _public prototype_ `virtual TSharedPtr< IDatasmithLevelSequenceElement > GetLevelSequence(int32 InIndex) = 0;` — Returns the level sequence using this index
- L1769 _public prototype_ `virtual const TSharedPtr< IDatasmithLevelSequenceElement >& GetLevelSequence(int32 InIndex) const = 0;`
- L1776 _public prototype_ `virtual void RemoveLevelSequence(const TSharedRef< IDatasmithLevelSequenceElement>& InSequence) = 0;` — Removes a level sequence from the scene. @param InSequence the level sequence to remove
- L1781 _public prototype_ `virtual void RemoveLevelSequenceAt(int32 InIndex) = 0;` — Removes from the scene the level sequence at the specified index.
- L1788 _public prototype_ `virtual void AddLevelVariantSets(const TSharedPtr< IDatasmithLevelVariantSetsElement >& InLevelVariantSets) = 0;` — Adds a LevelVariantSets to the scene. @param InLevelVariantSets the LevelVariantSets to add
- L1791 _public prototype_ `virtual int32 GetLevelVariantSetsCount() const = 0;` — Returns the number of LevelVariantSets in the scene
- L1794 _public prototype_ `virtual TSharedPtr< IDatasmithLevelVariantSetsElement > GetLevelVariantSets(int32 InIndex) = 0;` — Returns the LevelVariantSets using this index
- L1795 _public prototype_ `virtual const TSharedPtr< IDatasmithLevelVariantSetsElement >& GetLevelVariantSets(int32 InIndex) const = 0;`
- L1802 _public prototype_ `virtual void RemoveLevelVariantSets(const TSharedPtr< IDatasmithLevelVariantSetsElement>& InLevelVariantSets) = 0;` — Removes a LevelVariantSets from the scene. @param InLevelVariantSets the LevelVariantSets to remove
- L1807 _public prototype_ `virtual void RemoveLevelVariantSetsAt(int32 InIndex) = 0;` — Removes from the scene the LevelVariantSets at the specified index.
- L1810 _public prototype_ `virtual void AttachActor(const TSharedPtr< IDatasmithActorElement >& NewParent, const TSharedPtr< IDatasmithActorElement >& Child, EDatasmithActorAttachmentRule AttachmentRule) = 0;` — Attach the actor to its new parent. Detach the actor if it was already attached.
- L1812 _public prototype_ `virtual void AttachActorToSceneRoot(const TSharedPtr< IDatasmithActorElement >& Child, EDatasmithActorAttachmentRule AttachmentRule) = 0;` — Attach the actor to the scene root. Detach the actor if it was already attached.

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API DATASMITHCORE_API`
- L1816 _typedef_ `using IDatasmithMasterMaterialElement UE_DEPRECATED(5.1, "IDatasmithMasterMaterialElement will no`
