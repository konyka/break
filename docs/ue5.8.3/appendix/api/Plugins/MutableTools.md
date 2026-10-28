# Plugins / MutableTools

- module root: `Plugins/Mutable/Source/MutableTools`
- headers: 260; symbols: 5174
- symbol kinds: class=283, enum=16, enumerator=208, externvar=2, function=514, macro=145, member=1458, namespace=778, prototype=1590, struct=126, typedef=54
- PublicDependencyModuleNames: Core, CoreUObject, Engine, GeometryCore, ImageCore, MutableRuntime, TextureBuildUtilities, TextureCompressor

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/AST.h` (Internal)


#### struct `std::hash`  
`template<typename T> struct hash<UE::Mutable::Private::Ptr<T>>`  
_L34-40_
- L36 _public function_ `uint64 operator()(const UE::Mutable::Private::Ptr<T>& k) const`

#### class `UE::Mutable::Private::ImageSizeExpression`  
`class ImageSizeExpression : public RefCounted`  
_L73-177_
- inherits: `RefCounted`
- L83 _public member_ `} type;`
- L86 _public member_ `FImageSize size = FImageSize(0, 0);` — For constant sizes
- L89 _public member_ `Ptr<class ASTOp> layout;` — For layout factor sizes
- L90 _public member_ `uint16 factor[2];`
- L93 _public member_ `Ptr<class ASTOp> condition;` — For conditionals
- L94 _public member_ `Ptr<ImageSizeExpression> yes;`
- L95 _public member_ `Ptr<ImageSizeExpression> no;`
- L98 _public function_ `ImageSizeExpression()`
- L110 _public function_ `void CopyFrom(const ImageSizeExpression& o)`
- L123 _public function_ `bool operator==( const ImageSizeExpression& other ) const`
- L151 _public function_ `void Optimise()`

#### enum `UE::Mutable::Private::ImageSizeExpression::(anonymous)`  
``  
_L78-83_

#### struct `UE::Mutable::Private::FModelOptimizationOptions`  
`struct FModelOptimizationOptions`  
_L185-218_
- desc: Detailed optimization flags
- L187 _public member_ `bool bEnabled = true;`
- L188 _public member_ `bool bOptimiseOverlappedMasks = false;`
- L189 _public member_ `bool bConstReduction = true;`
- L193 _public member_ `bool bUniformizeSkeleton = true;` — Preprocess all mesh fragments so that they use the same skeleton, even if not all bones are relevant for all fragments.
- L196 _public member_ `int32 MaxOptimisationLoopCount = 8;` — Maximum number of iterations when optimising models. If 0 as many as necessary will be performed.
- L199 _public member_ `bool bEnableProgressiveImages = false;` — Compile optimizing for the generation of smaller mipmaps of every image.
- L205 _public member_ `float AcceptableCropRatio = 0.5f;` — Ratio used to decide if it is worth to generate a crop operation
- L208 _public member_ `float MinRLECompressionGain = 1.2f;` — Ratio used to decide if it is worth to generate a crop operation
- L214 _public member_ `FReferencedImageResourceFunc ReferencedImageResourceProvider;` — Function used to request an engine resource from the compiler.
- L215 _public member_ `FReferencedMeshResourceFunc ReferencedMeshResourceProvider;`
- L217 _public member_ `bool bDisableMaterialGeneration = false;`

#### struct `UE::Mutable::Private::FLinkerOptions`  
`struct FLinkerOptions`  
_L221-299_
- L223 _public function_ `FLinkerOptions(FImageOperator& InImOp) : ImageOperator(InImOp)`
- L229 _public member_ `int32 MinTextureResidentMipCount = 0;` — TODO: Unused?
- L234 _public member_ `bool bSeparateImageMips = true;` — This flag controls the splitting of image data into mips to store separately. It is usually necessary to be able to generate progressive textures (for texture streaming).
- L254 _public member_ `TMap<TManagedPtr<const FMesh>, int32, FDefaultSetAllocator, FDeduplicationMeshFuncs> MeshConstantMap;`
- L277 _public member_ `TMap<TManagedPtr<const FImage>, int32, FDefaultSetAllocator, FDeduplicationImageFuncs> ImageConstantMipMap;`
- L280 _public member_ `FImageOperator& ImageOperator;` — Image operation functions, so that they can be overriden.
- L296 _public member_ `FAdditionalData AdditionalData;`
- L298 _public member_ `TMap<FOperation::ADDRESS, FInstancedStruct>* ExternalOperations = nullptr;`

#### struct `UE::Mutable::Private::FLinkerOptions::FDeduplicationMeshFuncs`  
`struct FDeduplicationMeshFuncs : TDefaultMapHashableKeyFuncs<TManagedPtr<const FMesh>, int32, false>`  
_L237-252_
- inherits: `TDefaultMapHashableKeyFuncs<TManagedPtr<constFMesh>,int32,false>`
- desc: Structure used to speedup mesh constant comparison.
- L239 _public function_ `static FORCEINLINE bool Matches(KeyInitType A, KeyInitType B)`
- L244 _public function_ `static FORCEINLINE uint32 GetKeyHash(KeyInitType Key)`

#### struct `UE::Mutable::Private::FLinkerOptions::FDeduplicationImageFuncs`  
`struct FDeduplicationImageFuncs : TDefaultMapHashableKeyFuncs<TManagedPtr<const FImage>, int32, false>`  
_L257-275_
- inherits: `TDefaultMapHashableKeyFuncs<TManagedPtr<constFImage>,int32,false>`
- desc: Structure used to speedup image mip comparison.
- L259 _public function_ `static FORCEINLINE bool Matches(KeyInitType A, KeyInitType B)`
- L264 _public function_ `static FORCEINLINE uint32 GetKeyHash(KeyInitType Key)`

#### struct `UE::Mutable::Private::FLinkerOptions::FAdditionalData`  
`struct FAdditionalData`  
_L283-294_
- desc: Store for additional data generated during compilation, but not necessary for the runtime.
- L288 _public member_ `TArray<FSourceDataDescriptor> SourceImagePerConstant;` — Source data descriptor for every image constant that has been generated. It must have the same size than the Program::ConstantImages array.
- L293 _public member_ `TArray<FSourceDataDescriptor> SourceMeshPerConstant;` — Source data descriptor for every mesh constant that has been generated. It must have the same size than the Program::ConstantMeshes array.

#### struct `UE::Mutable::Private::FSinkerOldToNewKey`  
`struct FSinkerOldToNewKey`  
_L303-317_
- desc: For each operation we sink, the map from old instructions to new instructions.
- L305 _public member_ `Ptr<const ASTOp> Op;`
- L306 _public member_ `Ptr<const ASTOp> SinkingOp;`

#### class `UE::Mutable::Private::Sink_ImageCropAST`  
`class Sink_ImageCropAST`  
_L321-335_
- L325 _public prototype_ `Ptr<ASTOp> Apply(const ASTOpImageCrop* root);`
- L329 _protected member_ `const ASTOpImageCrop* Root = nullptr;`
- L330 _protected member_ `Ptr<ASTOp> InitialSource;`
- L332 _protected member_ `TMap<FSinkerOldToNewKey, Ptr<ASTOp>> OldToNew;` — For each operation we sink, the map from old instructions to new instructions.
- L334 _protected prototype_ `Ptr<ASTOp> Visit(Ptr<ASTOp> at, const ASTOpImageCrop* currentCropOp);`

#### class `UE::Mutable::Private::Sink_ImagePixelFormatAST`  
`class Sink_ImagePixelFormatAST`  
_L339-352_
- L343 _public prototype_ `Ptr<ASTOp> Apply(const ASTOpImagePixelFormat* root);`
- L347 _protected member_ `const ASTOpImagePixelFormat* Root = nullptr;`
- L348 _protected member_ `Ptr<ASTOp> InitialSource;`
- L349 _protected member_ `TMap<FSinkerOldToNewKey, Ptr<ASTOp>> OldToNew;`
- L351 _protected prototype_ `Ptr<ASTOp> Visit(Ptr<ASTOp> at, const ASTOpImagePixelFormat* currentFormatOp);`

#### class `UE::Mutable::Private::Sink_ImageSwizzleAST`  
`class Sink_ImageSwizzleAST`  
_L356-369_
- L360 _public prototype_ `Ptr<ASTOp> Apply(const ASTOpImageSwizzle* Root);`
- L364 _protected member_ `const ASTOpImageSwizzle* Root = nullptr;`
- L365 _protected member_ `Ptr<ASTOp> InitialSource;`
- L366 _protected member_ `TMap<FSinkerOldToNewKey, Ptr<ASTOp>> OldToNew;`
- L368 _protected prototype_ `Ptr<ASTOp> Visit(Ptr<ASTOp> at, const ASTOpImageSwizzle* CurrentSwizzleOp);`

#### class `UE::Mutable::Private::Sink_MeshFormatAST`  
`class Sink_MeshFormatAST`  
_L373-386_
- L377 _public prototype_ `Ptr<ASTOp> Apply(const ASTOpMeshFormat* Root);`
- L381 _protected member_ `const ASTOpMeshFormat* Root = nullptr;`
- L382 _protected member_ `Ptr<ASTOp> InitialSource;`
- L383 _protected member_ `TMap<FSinkerOldToNewKey, Ptr<ASTOp>> OldToNew;`
- L385 _protected prototype_ `Ptr<ASTOp> Visit(const Ptr<ASTOp>& Op, const ASTOpMeshFormat* CurrentSinkOp);`

#### class `UE::Mutable::Private::Sink_MeshExtractLayoutBlocksAST`  
`class Sink_MeshExtractLayoutBlocksAST`  
_L390-403_
- L394 _public prototype_ `Ptr<ASTOp> Apply(const ASTOpMeshExtractLayoutBlocks* Root);`
- L398 _protected member_ `const ASTOpMeshExtractLayoutBlocks* Root = nullptr;`
- L399 _protected member_ `Ptr<ASTOp> InitialSource;`
- L400 _protected member_ `TMap<FSinkerOldToNewKey, Ptr<ASTOp>> OldToNew;`
- L402 _protected prototype_ `Ptr<ASTOp> Visit(const Ptr<ASTOp>& at, const ASTOpMeshExtractLayoutBlocks* currentFormatOp);`

#### class `UE::Mutable::Private::Sink_ImageMipmapAST`  
`class Sink_ImageMipmapAST`  
_L407-423_
- L411 _public prototype_ `Ptr<ASTOp> Apply(const ASTOpImageMipmap* Root);`
- L415 _protected member_ `const ASTOpImageMipmap* Root = nullptr;`
- L416 _protected member_ `Ptr<ASTOp> InitialSource;`
- L419 _protected member_ `TMap<FSinkerOldToNewKey, Ptr<ASTOp>> OldToNew;` — For each operation we sink, the map from old instructions to new instructions.
- L421 _protected prototype_ `Ptr<ASTOp> Visit(Ptr<ASTOp> at, const ASTOpImageMipmap* currentMipmapOp);`

#### struct `UE::Mutable::Private::FOptimizeSinkContext`  
`struct FOptimizeSinkContext`  
_L425-433_
- L427 _public member_ `Sink_ImageCropAST ImageCropSinker;`
- L428 _public member_ `Sink_ImagePixelFormatAST ImagePixelFormatSinker;`
- L429 _public member_ `Sink_ImageSwizzleAST ImageSwizzleSinker;`
- L430 _public member_ `Sink_ImageMipmapAST ImageMipmapSinker;`
- L431 _public member_ `Sink_MeshFormatAST MeshFormatSinker;`
- L432 _public member_ `Sink_MeshExtractLayoutBlocksAST MeshExtractLayoutBlocksSinker;`

#### class `UE::Mutable::Private::ASTChild`  
`class ASTChild`  
_L437-500_
- L442 _public prototype_ `explicit ASTChild(ASTOp* parent, const Ptr<ASTOp>& child=Ptr<ASTOp>());`
- L443 _public prototype_ `ASTChild(const Ptr<ASTOp>& parent, const Ptr<ASTOp>& child);`
- L444 _public prototype_ `~ASTChild();`
- L446 _public prototype_ `ASTChild(const ASTChild&) = delete;`
- L447 _public prototype_ `ASTChild& operator=(const ASTChild&) = delete;`
- L449 _public function_ `explicit ASTChild(FInvalidTag)`
- L452 _public function_ `ASTChild(ASTChild&& rhs) : Parent(rhs.Parent) , Child(rhs.Child) , ParentIndexInChild(rhs.ParentIndexInChild)` — move constructor
- L462 _public prototype_ `ASTChild& operator=( ASTChild&& );` — Move assignment
- L464 _public prototype_ `ASTChild& operator=( const Ptr<ASTOp>& );`
- L466 _public function_ `inline explicit operator bool() const`
- L471 _public function_ `inline Ptr<class ASTOp>& child()`
- L476 _public function_ `inline const Ptr<class ASTOp>& child() const`
- L481 _public function_ `inline const Ptr<class ASTOp>& operator->() const`
- L486 _public function_ `inline bool operator==(const ASTChild& o) const`
- L491 _public member_ `class ASTOp* Parent;`
- L492 _public member_ `Ptr<class ASTOp> Child;`
- L493 _public member_ `int32 ParentIndexInChild = 0;`
- L497 _private prototype_ `inline void AddParent();`
- L499 _private prototype_ `inline void ClearParent();`
- L1131 _function_ `inline void ASTChild::AddParent()`
- L1139 _function_ `inline void ASTChild::ClearParent()`

#### struct `UE::Mutable::Private::ASTChild::FInvalidTag`  
`struct FInvalidTag`  
_L440-440_

#### class `UE::Mutable::Private::ASTOp`  
`class ASTOp : public RefCounted`  
_L514-903_
- inherits: `RefCounted`
- L520 _private member_ `TArray<ASTOp*, TInlineAllocator<4> > Parents;` — Operations referring to this one. They may be null: elements are never removed from this TArray.
- L522 _private member_ `UE::FMutex ParentsMutex;`
- L526 _public function_ `inline ASTOp()`
- L532 _public prototype_ `virtual ~ASTOp() = default;`
- L535 _public prototype_ `virtual EOpType GetOpType() const = 0;` — Get the operation type
- L538 _public prototype_ `virtual void Assert();` — Validate that everything is fine with this tree
- L541 _public prototype_ `virtual void ForEachChild( const TFunctionRef<void(ASTChild&)> ) = 0;` — Run something for each child operation, with a chance to modify it.
- L544 _public prototype_ `void ForEachParent(const TFunctionRef<void(ASTOp*)>) const;` — Run something for each parent operation+.
- L547 _public prototype_ `virtual bool operator==( const ASTOp& other ) const;` — Run something for each child operation, with a chance to modify it.
- L550 _public prototype_ `virtual uint32 Hash() const = 0;` — Hint hash method for op sorting and containers. It's a hash of the actual operation.
- L553 _public typedef_ `using MapChildFunc = TFunction<Ptr<ASTOp>(const Ptr<ASTOp>&)>;` — Shallow clone. New node will have no parents but reference to the same children.
- L554 _public typedef_ `using MapChildFuncRef = TFunctionRef<Ptr<ASTOp>(const Ptr<ASTOp>&)>;`
- L555 _public prototype_ `virtual Ptr<ASTOp> Clone(MapChildFuncRef mapChild) const = 0;`
- L558 _public function_ `virtual bool IsConditional() const`
- L559 _public function_ `virtual bool IsSwitch() const`
- L563 _protected prototype_ `void RemoveChildren();`
- L565 _protected prototype_ `virtual bool IsEqual(const ASTOp& other) const = 0;`
- L570 _public prototype_ `static void FullAssert( const TArray<Ptr<ASTOp>>& roots );`
- L572 _public prototype_ `static int32 CountNodes( const TArray<Ptr<ASTOp>>& roots );`
- L574 _public function_ `inline bool IsConstantOp() const`
- L591 _public prototype_ `static Ptr<ASTOp> DeepClone( const Ptr<ASTOp>& );` — Deep clone. New node will have no parents and reference new children
- L594 _public prototype_ `static void LogHistogram(ASTOpList& roots);`
- L600 _public function_ `virtual Ptr<ASTOp> OptimiseSize() const`
- L601 _public function_ `virtual Ptr<ASTOp> OptimiseSemantic(const FModelOptimizationOptions&, int32 Pass) const`
- L602 _public function_ `virtual Ptr<ASTOp> OptimiseSink(const FModelOptimizationOptions&, FOptimizeSinkContext& ) const`
- L603 _public function_ `virtual Ptr<ImageSizeExpression> GetImageSizeExpression() const`
- L616 _public prototype_ `static FOperation::ADDRESS FullLink( Ptr<ASTOp>& Root, FProgram&, FLinkerOptions* );` — Convert the operation graph at Root into code in the given program. Potentially destroys the data in this operation, so it shouldn't be used after calling Link.
- L624 _private prototype_ `virtual void Link( FProgram&, FLinkerOptions* ) = 0;` — Convert this operation into code in the given program. It assumes children have been linked already Potentially destroys the data in this operation, so it shouldn't be used after calling Link.
- L677 _protected prototype_ `static void LinkRange(FProgram& program, const FRangeData& range, FOperation::ADDRESS& rangeSize, uint16& rangeId);`
- L688 _public prototype_ `static void Traverse_TopDown_Unique( const TArray<Ptr<ASTOp>>& roots, TFunctionRef<bool(Ptr<ASTOp>&)> f );`
- L691 _public prototype_ `static void Traverse_TopDown_Unique_Imprecise( const TArray<Ptr<ASTOp>>& roots, TFunctionRef<bool(Ptr<ASTOp>&)> f );` — \todo: it is not strictly top down.
- L696 _public prototype_ `static void Traverse_TopRandom_Unique_NonReentrant ( const TArray<Ptr<ASTOp>>& roots, TFunctionRef<bool(Ptr<ASTOp>&)> f );` — Kind of top-down, but really not. This version is slighlty faster, but doesn't support recursive traversals so use it only in controlled cases.
- L716 _public function_ `template<typename STATE> static inline void Traverse_TopDown_Unique_Imprecise_WithState ( Ptr<ASTOp>& root, const STATE& initialState, TFunctionRef<bool(Ptr<ASTOp>&, STATE&, TArray<TPair<Ptr<ASTOp>,STATE>>&)> f )` — Kind of top-down, but really not. This version is slightly faster, but doesn't support recursive traversals so use it only in controlled cases.
- L767 _public prototype_ `static void Traverse_BottomUp_Unique_NonReentrant( ASTOpList& roots, TFunctionRef<void(Ptr<ASTOp>&)> f );` — This version is slighlty faster, but doesn't support recursive traversals so use it only in controlled cases.
- L771 _public prototype_ `static void Traverse_BottomUp_Unique_NonReentrant ( ASTOpList& roots, TFunctionRef<void(Ptr<ASTOp>&)> f, TFunctionRef<bool(const ASTOp*)> accept );` — This version is slighlty faster, but doesn't support recursive traversals so use it only in controlled cases.
- L779 _public prototype_ `static void Traverse_BottomUp_Unique ( ASTOpList& roots, TFunctionRef<void(Ptr<ASTOp>&)> f, TFunctionRef<bool(const ASTOp*)> accept = [](const ASTOp*){return true;} );`
- L783 _public function_ `ASTOpList& roots, TFunctionRef<void(Ptr<ASTOp>&)> f, TFunctionRef<bool(const ASTOp*)> accept = [](const ASTOp*)`
- L787 _public prototype_ `static void Traverse_BottomUp_Unique ( Ptr<ASTOp>& root, TFunctionRef<void(Ptr<ASTOp>&)> f, TFunctionRef<bool(const ASTOp*)> accept = [](const ASTOp*){return true;} );`
- L791 _public function_ `Ptr<ASTOp>& root, TFunctionRef<void(Ptr<ASTOp>&)> f, TFunctionRef<bool(const ASTOp*)> accept = [](const ASTOp*)`
- L795 _public member_ `FOperation::ADDRESS LinkedAddress = 0;`
- L799 _public member_ `uint32 m_traverseIndex = 0;` — Generic traverse control counter. It should always be left to 0 after any process for all nodes in the hierarchy.
- L800 _public member_ `static std::atomic<uint32> s_lastTraverseIndex;`
- L803 _public member_ `int8 linkedRange = -1;`
- L808 _public member_ `uint8 bIsConstantSubgraph : 1;` — Embedded node data for the constant subtree detection.This flag is only valid if the constant detection process has been executed and no relevant AST transformations have happened.
- L809 _public member_ `uint8 bHasSpecialOpInSubgraph : 1;`
- L820 _public prototype_ `int32 GetParentCount() const;` — Get the number of ASTOps that have this one as child, in any existing AST graph.
- L823 _public prototype_ `static void Replace( const Ptr<ASTOp>& node, const Ptr<ASTOp>& other );` — Make all parents of this node point at the other node instead.
- L839 _public prototype_ `virtual FImageDesc GetImageDesc( bool returnBestOption=false, FGetImageDescContext* context=nullptr ) const;`
- L849 _public prototype_ `virtual FSourceDataDescriptor GetSourceDataDescriptor(FGetSourceDataDescriptorContext* = nullptr) const;`
- L852 _public typedef_ `using FBlockLayoutSizeCache=TMap< const TPair<ASTOp*,uint64>, TPair<int32,int32>>;` — Optional cache struct to use int he method below.
- L855 _public prototype_ `virtual void GetBlockLayoutSize( uint64 BlockId, int32* pBlockX, int32* pBlockY, FBlockLayoutSizeCache* cache );` — Return the size in layout blocks of a particular block given by absolute index
- L856 _public prototype_ `void GetBlockLayoutSizeCached(uint64 BlockId, int32* pBlockX, int32* pBlockY, FBlockLayoutSizeCache* cache );`
- L860 _public prototype_ `virtual void GetLayoutBlockSize( int32* pBlockX, int32* pBlockY );` — Return the size in pixels of the layout grid block for the image operation
- L862 _public prototype_ `virtual bool IsImagePlainConstant(FVector4f& color ) const;`
- L863 _public prototype_ `virtual bool IsColorConstant(FVector4f& color ) const;`
- L866 _public prototype_ `virtual bool GetNonBlackRect( FImageRect& maskUsage ) const;`
- L876 _public prototype_ `virtual EClosedMeshTest IsClosedMesh(TMap<const ASTOp*, EClosedMeshTest>* Cache=nullptr ) const;` — This can be overriden to help detect subgraph mesh properties.
- L885 _public typedef_ `BET_UNKNOWN, BET_TRUE, BET_FALSE, } FBoolEvalResult;`
- L888 _public typedef_ `using FEvaluateBoolCache = std::unordered_map<const ASTOp*,FBoolEvalResult>;`
- L890 _public function_ `virtual FBoolEvalResult EvaluateBool( ASTOpList& , FEvaluateBoolCache* = nullptr ) const`
- L896 _public function_ `virtual int EvaluateInt( ASTOpList& , bool &unknown ) const`

#### struct `UE::Mutable::Private::ASTOp::FRangeData`  
`struct FRangeData`  
_L631-674_
- L634 _public member_ `ASTChild rangeSize;`
- L637 _public member_ `FString rangeName;`
- L640 _public member_ `FString rangeUID;`
- L643 _public function_ `FRangeData( ASTOp* parentOp, Ptr<ASTOp> childOp, const FString& name, const FString& uid ) : rangeSize( parentOp, childOp ) , rangeName(name) , rangeUID(uid)`
- L650 _public prototype_ `FRangeData(const FRangeData&) = delete;`
- L651 _public prototype_ `FRangeData& operator=(const FRangeData&) = delete;`
- L652 _public prototype_ `FRangeData& operator=(FRangeData&&) = delete;`
- L656 _public function_ `FRangeData(FRangeData&& rhs) : rangeSize(MoveTemp(rhs.rangeSize)) , rangeName(MoveTemp(rhs.rangeName)) , rangeUID(MoveTemp(rhs.rangeUID))` — move constructor
- L666 _public function_ `bool operator==(const FRangeData& o) const`

#### struct `UE::Mutable::Private::ASTOp::FKeyFuncs`  
`template<typename STATE> struct FKeyFuncs : BaseKeyFuncs<TPair<Ptr<ASTOp>, STATE>, Ptr<ASTOp>, false>`  
_L704-709_
- inherits: `BaseKeyFuncs<TPair<Ptr<ASTOp>,STATE>,Ptr<ASTOp>,false>`
- L706 _public function_ `static Ptr<ASTOp> GetSetKey(TPair<Ptr<ASTOp>, STATE> Element)`
- L707 _public function_ `static bool Matches(const Ptr<ASTOp>& lhs, const Ptr<ASTOp>& rhs)`
- L708 _public function_ `static uint32 GetKeyHash(const Ptr<ASTOp>& Key)`

#### struct `UE::Mutable::Private::ASTOp::Traverse_TopDown_Unique_Imprecise_WithState::custom_partial_hash`  
`struct custom_partial_hash`  
_L728-734_
- L730 _public function_ `uint64 operator()(const std::pair<Ptr<ASTOp>,STATE>& k) const`

#### class `UE::Mutable::Private::ASTOp::FGetImageDescContext`  
`class FGetImageDescContext`  
_L830-836_
- desc: This class contains the support data to accelerate the GetImageDesc recursive function. If none is provided in the call, one will be created at that level and used from there on.
- L833 _public member_ `TMap<const ASTOp*, FImageDesc> m_results;`
- L834 _public member_ `bool bIsFormatFromImageParameter = false;`
- L835 _public member_ `FParameterKey ParameterKey;`

#### class `UE::Mutable::Private::ASTOp::FGetSourceDataDescriptorContext`  
`class FGetSourceDataDescriptorContext`  
_L842-846_
- L845 _public member_ `TMap<const ASTOp*, FSourceDataDescriptor> Cache;`

#### enum `UE::Mutable::Private::ASTOp::EClosedMeshTest`  
`enum class EClosedMeshTest : uint8`  
_L868-873_
- L870 _public enumerator_ `No`
- L871 _public enumerator_ `Yes`
- L872 _public enumerator_ `Unknown`

#### enum `UE::Mutable::Private::ASTOp::(anonymous)`  
``  
_L881-885_

#### class `UE::Mutable::Private::Visitor_TopDown_Unique_Const`  
`template<typename STATE> class Visitor_TopDown_Unique_Const`  
_L928-1074_
- L933 _private prototype_ `virtual bool Visit( const Ptr<ASTOp>& node ) = 0;` — @return if true, visit children.
- L938 _private member_ `TArray<STATE> States;` — States found so far
- L941 _private member_ `int32 CurrentState;` — Index of the current state, from the States TArray.
- L959 _private member_ `TArray<FPending> Pending;`
- L962 _private member_ `TMultiMap<Ptr<ASTOp>,int32> Traversed;` — List of Traversed nodes with the state in which they were Traversed.
- L967 _protected function_ `const STATE& GetCurrentState() const`
- L973 _protected function_ `STATE GetDefaultState() const`
- L979 _protected function_ `void RecurseWithState(const Ptr<ASTOp>& InAt, const STATE& NewState)` — For manual recursion that changes the state for a specific path.
- L995 _protected function_ `void RecurseWithCurrentState(const Ptr<ASTOp>& InAt)` — For manual recursion that doesn't change the state for a specific path.
- L1004 _protected function_ `void SetCurrentState(const STATE& NewState)` — Can be called from visit to set the state to visit all children ops
- L1017 _public prototype_ `virtual ~Visitor_TopDown_Unique_Const() = default;` — Ensure virtual destruction
- L1020 _public function_ `void Traverse(const ASTOpList& Roots, const STATE& InitialState)`

#### struct `UE::Mutable::Private::Visitor_TopDown_Unique_Const::FPending`  
`struct FPending`  
_L943-957_
- L945 _public function_ `FPending()`
- L949 _public function_ `FPending(Ptr<ASTOp> InAt, int32 InStateIndex)`
- L955 _public member_ `Ptr<ASTOp> At;`
- L956 _public member_ `int32 StateIndex;`

#### class `UE::Mutable::Private::Visitor_TopDown_Unique_Cloning`  
`class Visitor_TopDown_Unique_Cloning`  
_L1082-1128_
- L1087 _public prototype_ `virtual ~Visitor_TopDown_Unique_Cloning() = default;` — Ensure virtual destruction
- L1092 _protected prototype_ `virtual Ptr<ASTOp> Visit( Ptr<ASTOp> at, bool& processChildren ) = 0;` — Do the actual work by overriding this in the derived classes.
- L1095 _protected prototype_ `void Traverse( Ptr<ASTOp>& root );`
- L1100 _private member_ `TArray< TPair<bool,Ptr<ASTOp>> > Pending;` — Operations to be processed
- L1103 _private member_ `TMap<Ptr<ASTOp>,Ptr<ASTOp>> OldToNew;` — Map for visited operations
- L1106 _private function_ `inline Ptr<ASTOp> GetOldToNew( const Ptr<ASTOp>& Old ) const`
- L1126 _private prototype_ `void Process();` — Process all the Pending operations and visit all children if necessary

#### class `UE::Mutable::Private::FUniqueOpPool`  
`class FUniqueOpPool`  
_L1151-1184_
- L1163 _private member_ `TSet<Ptr<ASTOp>, FKeyFuncs> Visited[(int32)EOpType::COUNT];` — Existing ops, per type
- L1167 _public member_ `bool bDisabled = false;`
- L1169 _public function_ `Ptr<ASTOp> Add( const Ptr<ASTOp>& Op )`

#### struct `UE::Mutable::Private::FUniqueOpPool::FKeyFuncs`  
`struct FKeyFuncs : BaseKeyFuncs<Ptr<ASTOp>, Ptr<ASTOp>, false>`  
_L1155-1160_
- inherits: `BaseKeyFuncs<Ptr<ASTOp>,Ptr<ASTOp>,false>`
- L1157 _public function_ `static KeyInitType GetSetKey(ElementInitType Element)`
- L1158 _public function_ `static bool Matches(const Ptr<ASTOp>& lhs, const Ptr<ASTOp>& rhs)`
- L1159 _public function_ `static uint32 GetKeyHash(const Ptr<ASTOp>& Key)`

#### Free symbols / members of external scopes

- L30 _namespace_ `namespace std`
- L45 _namespace_ `namespace UE`
- L45 _namespace_ `namespace Mutable` (scope `UE`)
- L45 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L57 _function_ `template<typename T> inline uint32 GetTypeHash(const Ptr<const T>& p)` (scope `UE::Mutable::Private`)
- L64 _function_ `template<typename T> inline uint32 GetTypeHash(const Ptr<T>& p)` (scope `UE::Mutable::Private`)
- L79 _enumerator_ `ISET_UNKNOWN` (scope `UE::Mutable::Private::ImageSizeExpression::__anon38ff53790103`)
- L80 _enumerator_ `ISET_CONSTANT` (scope `UE::Mutable::Private::ImageSizeExpression::__anon38ff53790103`)
- L81 _enumerator_ `ISET_LAYOUTFACTOR` (scope `UE::Mutable::Private::ImageSizeExpression::__anon38ff53790103`)
- L82 _enumerator_ `ISET_CONDITIONAL` (scope `UE::Mutable::Private::ImageSizeExpression::__anon38ff53790103`)
- L180 _typedef_ `typedef TArray<Ptr<ASTOp>> ASTOpList;` (scope `UE::Mutable::Private`)
- L181 _typedef_ `typedef TSet<Ptr<ASTOp>> ASTOpSet;` (scope `UE::Mutable::Private`)
- L308 _function_ `friend inline uint32 GetTypeHash(const FSinkerOldToNewKey& Key)` (scope `UE::Mutable::Private`)
- L313 _function_ `friend inline bool operator==(const FSinkerOldToNewKey& A, const FSinkerOldToNewKey& B)` (scope `UE::Mutable::Private`)
- L503 _function_ `inline uint32 GetTypeHash(const ASTChild& Child)` (scope `UE::Mutable::Private`)
- L753 _function_ `` (scope `UE::Mutable::Private::ASTOp::Traverse_TopDown_Unique_Imprecise_WithState`)
- L882 _enumerator_ `BET_UNKNOWN` (scope `UE::Mutable::Private::ASTOp::__anon38ff53790503`)
- L883 _enumerator_ `BET_TRUE` (scope `UE::Mutable::Private::ASTOp::__anon38ff53790503`)
- L884 _enumerator_ `BET_FALSE` (scope `UE::Mutable::Private::ASTOp::__anon38ff53790503`)
- L906 _function_ `template<class DERIVED> inline Ptr<DERIVED> Clone( const ASTOp* s )` (scope `UE::Mutable::Private`)
- L908 _function_ `ASTOp::MapChildFunc Identity = [](const Ptr<ASTOp>& o)` (scope `UE::Mutable::Private::Clone`)
- L915 _function_ `template<class DERIVED> inline Ptr<DERIVED> Clone( const Ptr<const ASTOp>& s )` (scope `UE::Mutable::Private`)
- L1064 _function_ `` (scope `UE::Mutable::Private::Visitor_TopDown_Unique_Const::Traverse`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/Compiler.h` (Internal)


#### class `UE::Mutable::Private::CompilerOptions`  
`class CompilerOptions : public RefCounted`  
_L42-118_
- inherits: `RefCounted`
- desc: Options used to compile the models with a compiler.
- L47 _public prototype_ `CompilerOptions();` — Create new settings with the default values as explained in each method below.
- L50 _public prototype_ `void SetLogEnabled( bool bEnabled );`
- L53 _public prototype_ `void SetOptimisationEnabled( bool bEnabled );`
- L56 _public prototype_ `void SetConstReductionEnabled( bool bEnabled );`
- L59 _public prototype_ `void SetOptimisationMaxIteration( int32 MaxIterations );`
- L62 _public prototype_ `void SetIgnoreStates( bool bIgnore );`
- L66 _public prototype_ `void SetImageCompressionQuality(int32 Quality);` — Set the quality for the image compression algorithms. The level value is used internally with FSystem::SetImagecompressionQuality
- L69 _public prototype_ `void SetDataPackingStrategy( int32 MinTextureResidentMipCount, uint64 EmbeddedDataBytesLimit);`
- L72 _public prototype_ `void SetEnableProgressiveImages(bool bEnabled);` — If enabled it will make sure that the object is compile to generate smaller mips of the images.
- L75 _public prototype_ `void SetImagePixelFormatOverride(const FImageOperator::FImagePixelFormatFunc&);` — Set an optional pixel conversion function that will be called before any pixel format conversion.
- L78 _public prototype_ `void SetReferencedResourceCallback(const FReferencedImageResourceFunc&, const FReferencedMeshResourceFunc&);`
- L80 _public prototype_ `void SetDisableMaterialGeneration(bool bDisabled);`
- L96 _public prototype_ `static const char* GetTextureLayoutStrategyName( TextureLayoutStrategy s );`
- L102 _public prototype_ `Private* GetPrivate() const;`
- L104 _public prototype_ `CompilerOptions( const CompilerOptions& ) = delete;`
- L105 _public prototype_ `CompilerOptions( CompilerOptions&& ) = delete;`
- L106 _public prototype_ `CompilerOptions& operator=(const CompilerOptions&) = delete;`
- L107 _public prototype_ `CompilerOptions& operator=(CompilerOptions&&) = delete;`
- L116 _private member_ `Private* m_pD;`

#### enum `UE::Mutable::Private::CompilerOptions::TextureLayoutStrategy`  
`enum class TextureLayoutStrategy : uint8`  
_L83-93_
- desc: Different data packing strategies
- L86 _public enumerator_ `Pack` — Pack texture layouts without changing any scale
- L89 _public enumerator_ `None` — Do not touch mesh or image texture layouts
- L92 _public enumerator_ `Count` — Helper value, not really a strategy.

#### struct `UE::Mutable::Private::FStateOptimizationOptions`  
`struct FStateOptimizationOptions`  
_L122-127_
- L124 _public member_ `uint8 NumExtraLODsToBuildAfterFirstLOD = 0;`
- L125 _public member_ `bool bOnlyFirstLOD = false;`
- L126 _public member_ `ETextureCompressionStrategy TextureCompressionStrategy = ETextureCompressionStrategy::None;`

#### struct `UE::Mutable::Private::FObjectState`  
`struct FObjectState`  
_L131-141_
- desc: Information about an object state in the source data
- L134 _public member_ `FString Name;` — Name used to identify the state from the code and user interface.
- L137 _public member_ `FStateOptimizationOptions Optimisation;` — GPU Optimisation options
- L140 _public member_ `TArray<FString> RuntimeParams;` — List of names of the runtime parameters in this state

#### class `UE::Mutable::Private::Compiler`  
`class Compiler : public RefCounted`  
_L145-167_
- inherits: `RefCounted`
- L149 _public prototype_ `Compiler( Ptr<CompilerOptions> Options, TFunction<void()>& InWaitCallback );`
- L152 _public prototype_ `TSharedPtr<FModel> Compile( const Ptr<Node>& pNode, TMap<FOperation::ADDRESS, FInstancedStruct>& ExternalOperations);` — Compile the expression into a run-time model.
- L155 _public prototype_ `TSharedPtr<FErrorLog> GetLog() const;` — Return the log of messages of all the compile operations executed so far.
- L160 _protected prototype_ `~Compiler();` — Forbidden. Manage with the Ptr<> template.
- L165 _private member_ `Private* m_pD;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API MUTABLETOOLS_API`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Mutable` (scope `UE`)
- L17 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L24 _typedef_ `using TransformPtr=Ptr<Transform>;` (scope `UE::Mutable::Private`)
- L25 _typedef_ `using TransformPtrConst=Ptr<const Transform>;` (scope `UE::Mutable::Private`)
- L31 _typedef_ `typedef TFunction<UE::Tasks::FTask(PASSTHROUGH_ID, TSharedPtr<TManagedPtr<FImage>>, bool)> FReferencedImageResourceFunc;` (scope `UE::Mutable::Private`) — Arguments are Texture ID, output generated texture and a "run immediately" flag.
- L39 _typedef_ `typedef TFunction<UE::Tasks::FTask(PASSTHROUGH_ID, const FString&, TSharedPtr<TManagedPtr<FMesh>>, bool)> FReferencedMeshResourceFunc;` (scope `UE::Mutable::Private`) — Arguments are - Mesh ID, - optional morph name, - output generated mesh - "run immediately" flag.

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/ErrorLog.h` (Internal)


#### enum `UE::Mutable::Private::(anonymous)`  
``  
_L19-24_

#### enum `UE::Mutable::Private::(anonymous)`  
``  
_L28-31_

#### struct `UE::Mutable::Private::ErrorLogMessageAttachedDataView`  
`struct ErrorLogMessageAttachedDataView`  
_L33-37_
- L35 _public member_ `const float* UnassignedUVs = nullptr;`
- L36 _public member_ `int32 UnassignedUVsSize = 0;`

#### class `UE::Mutable::Private::FErrorLog`  
`class FErrorLog`  
_L42-110_
- desc: Storage for mutable error, warning and information messages from several processes performed by the tools library, like compilation. It supports concurrent addition of messages, but not retrieval.
- L64 _private member_ `UE::FMutex MessageMutex;` — This mutex is used to control the access to the messages array when adding them.
- L66 _private member_ `TArray<FMessage> Messages;`
- L76 _public prototype_ `int32 GetMessageCount() const;` — Get the number of messages. If a message type is provided, return the number of that type of message only.
- L80 _public prototype_ `const FString& GetMessageText( int32 index ) const;` — Get the text of a message. \param index index of the message from 0 to GetMessageCount()-1
- L84 _public prototype_ `const TArray<const void*, TInlineAllocator<4>>* GetMessageContexts(int32 Index) const;` — Get the opaque contexts of a message. \param Index index of the message from 0 to GetMessageCount()-1
- L87 _public prototype_ `ErrorLogMessageType GetMessageType( int32 index ) const;`
- L90 _public prototype_ `ErrorLogMessageSpamBin GetMessageSpamBin(int32 index) const;`
- L94 _public prototype_ `ErrorLogMessageAttachedDataView GetMessageAttachedData( int32 index ) const;` — Get the attached data of a message. \param index index of message data from 0 to GetMessageCount(ELMT_NONE)-1
- L97 _public prototype_ `void Log() const;`
- L100 _public prototype_ `void Merge( const FErrorLog* Other );`
- L103 _public prototype_ `void Add(const FString& Message, ErrorLogMessageType Type, const void* Context, ErrorLogMessageSpamBin SpamBin = ELMSB_ALL);`
- L104 _public prototype_ `void Add(const FString& Message, ErrorLogMessageType Type, const void* Context, const void* Context2, ErrorLogMessageSpamBin SpamBin = ELMSB_ALL);`
- L105 _public prototype_ `void Add(const FString& Message, ErrorLogMessageType Type, TArray<const void*, TInlineAllocator<4>>& Contexts, ErrorLogMessageSpamBin SpamBin = ELMSB_ALL);`
- L108 _public prototype_ `void Add(const FString& Message, const ErrorLogMessageAttachedDataView& Data, ErrorLogMessageType Type, const void* Context, ErrorLogMessageSpamBin SpamBin = ELMSB_ALL);`

#### struct `UE::Mutable::Private::FErrorLog::FErrorData`  
`struct FErrorData`  
_L46-49_
- L48 _public member_ `TArray< float > UnassignedUVs;`

#### struct `UE::Mutable::Private::FErrorLog::FMessage`  
`struct FMessage`  
_L51-59_
- L53 _public member_ `ErrorLogMessageType Type = ELMT_NONE;`
- L54 _public member_ `ErrorLogMessageSpamBin Spam = ELMSB_ALL;`
- L55 _public member_ `FString Text;`
- L56 _public member_ `TSharedPtr<FErrorData> Data;`
- L58 _public member_ `TArray<const void*, TInlineAllocator<4>> Contexts;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MUTABLETOOLS_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Mutable` (scope `UE`)
- L14 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L20 _enumerator_ `ELMT_NONE=0` (scope `UE::Mutable::Private::__anonea39313d0103`)
- L21 _enumerator_ `ELMT_ERROR` (scope `UE::Mutable::Private::__anonea39313d0103`)
- L22 _enumerator_ `ELMT_WARNING` (scope `UE::Mutable::Private::__anonea39313d0103`)
- L23 _enumerator_ `ELMT_INFO` (scope `UE::Mutable::Private::__anonea39313d0103`)
- L24 _typedef_ `} ErrorLogMessageType;` (scope `UE::Mutable::Private`)
- L29 _enumerator_ `ELMSB_ALL = 0` (scope `UE::Mutable::Private::__anonea39313d0203`)
- L30 _enumerator_ `ELMSB_UNKNOWN_TAG` (scope `UE::Mutable::Private::__anonea39313d0203`)
- L31 _typedef_ `} ErrorLogMessageSpamBin;` (scope `UE::Mutable::Private`)
- L112 _externvar_ `extern const TCHAR* s_opNames[];` (scope `UE::Mutable::Private`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/LODInfo.h` (Internal)


#### struct `UE::Mutable::Private::FLODInfo`  
`struct FLODInfo`  
_L10-21_
- L12 _public member_ `float ScreenSize = 0.0f;`
- L14 _public member_ `float LODHysteresis = 0.0f;`
- L16 _public member_ `bool bSupportUniformlyDistributedSampling = false;`
- L18 _public member_ `bool bAllowCPUAccess = false;`
- L20 _public prototype_ `bool operator==(const FLODInfo& Other) const = default;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Mutable` (scope `UE`)
- L8 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L24 _prototype_ `uint32 GetTypeHash(const FLODInfo& Key);` (scope `UE::Mutable::Private`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/MutableToolsModule.h` (Internal)


#### class `FMutableToolsModule`  
`class FMutableToolsModule : public IModuleInterface`  
_L7-13_
- inherits: `IModuleInterface`
- L11 _public function_ `virtual void StartupModule() override`
- L12 _public function_ `virtual void ShutdownModule() override`

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/Node.h` (Internal)


#### class `UE::Mutable::Private::Node`  
`class Node : public RefCounted`  
_L24-268_
- inherits: `RefCounted`
- desc: %Base class for all graphs used in the source data to define models and transforms.
- L245 _public function_ `virtual const FNodeType* GetType() const` — Node type hierarchy data.
- L246 _public function_ `static const FNodeType* GetStaticType()`
- L249 _public prototype_ `void SetMessageContext(const void* context);` — Set the opaque context returned in messages in the compiler log.
- L250 _public prototype_ `const void* GetMessageContext() const;`
- L259 _protected prototype_ `inline ~Node() = default;`
- L262 _protected member_ `const void* MessageContext = nullptr;` — This is an opaque context used to attach to reported error messages.
- L266 _private member_ `static FNodeType StaticType;`

#### enum `UE::Mutable::Private::Node::EType`  
`enum class EType : uint8`  
_L29-211_
- desc: Non-stable enumeration of all node types.
- L31 _public enumerator_ `None`
- L33 _public enumerator_ `Node`
- L35 _public enumerator_ `Mesh`
- L36 _public enumerator_ `MeshConstant`
- L37 _public enumerator_ `MeshTable`
- L38 _public enumerator_ `MeshFormat`
- L39 _public enumerator_ `MeshTangents`
- L40 _public enumerator_ `MeshMorph`
- L41 _public enumerator_ `MeshMakeMorph`
- L42 _public enumerator_ `MeshSwitch`
- L43 _public enumerator_ `MeshFragment`
- L44 _public enumerator_ `MeshTransform`
- L45 _public enumerator_ `MeshClipMorphPlane`
- L46 _public enumerator_ `MeshClipWithMesh`
- L47 _public enumerator_ `MeshRemoveMesh`
- L48 _public enumerator_ `MeshTransformWithBone`
- L49 _public enumerator_ `MeshTransformInMesh`
- L50 _public enumerator_ `MeshApplyPose`
- L51 _public enumerator_ `MeshVariation`
- L52 _public enumerator_ `MeshReshape`
- L53 _public enumerator_ `MeshClipDeform`
- L54 _public enumerator_ `MeshSkeletalMeshObjectBreak`
- L55 _public enumerator_ `MeshExternal`
- L57 _public enumerator_ `Image`
- L58 _public enumerator_ `ImageConstant`
- L59 _public enumerator_ `ImageInterpolate`
- L60 _public enumerator_ `ImageSaturate`
- L61 _public enumerator_ `ImageTable`
- L62 _public enumerator_ `ImageSwizzle`
- L63 _public enumerator_ `ImageColorMap`
- L64 _public enumerator_ `ImageGradient`
- L65 _public enumerator_ `ImageBinarise`
- L66 _public enumerator_ `ImageLuminance`
- L67 _public enumerator_ `ImageLayer`
- L68 _public enumerator_ `ImageLayerColor`
- L69 _public enumerator_ `ImageResize`
- L70 _public enumerator_ `ImagePlainColor`
- L71 _public enumerator_ `ImageProject`
- L72 _public enumerator_ `ImageMipmap`
- L73 _public enumerator_ `ImageSwitch`
- L74 _public enumerator_ `ImageConditional`
- L75 _public enumerator_ `ImageFormat`
- L76 _public enumerator_ `ImageConform`
- L77 _public enumerator_ `ImageMultiLayer`
- L78 _public enumerator_ `ImageInvert`
- L79 _public enumerator_ `ImageVariation`
- L80 _public enumerator_ `ImageNormalComposite`
- L81 _public enumerator_ `ImageTransform`
- L82 _public enumerator_ `ImageFromMaterialParameter`
- L83 _public enumerator_ `ImageExternal`
- L84 _public enumerator_ `ImageConvert`
- L86 _public enumerator_ `ImageObject`
- L87 _public enumerator_ `ImageObjectParameter`
- L89 _public enumerator_ `Bool`
- L90 _public enumerator_ `BoolConstant`
- L91 _public enumerator_ `BoolParameter`
- L92 _public enumerator_ `BoolNot`
- L93 _public enumerator_ `BoolAnd`
- L95 _public enumerator_ `Color`
- L96 _public enumerator_ `ColorConstant`
- L97 _public enumerator_ `ColorParameter`
- L98 _public enumerator_ `ColorSampleImage`
- L99 _public enumerator_ `ColorTable`
- L100 _public enumerator_ `ColorImageSize`
- L101 _public enumerator_ `ColorFromScalars`
- L102 _public enumerator_ `ColorArithmeticOperation`
- L103 _public enumerator_ `ColorSwitch`
- L104 _public enumerator_ `ColorVariation`
- L105 _public enumerator_ `ColorLinearToSRGB`
- L106 _public enumerator_ `ColorExternal`
- L108 _public enumerator_ `Scalar`
- L109 _public enumerator_ `ScalarConstant`
- L110 _public enumerator_ `ScalarParameter`
- L111 _public enumerator_ `ScalarEnumParameter`
- L112 _public enumerator_ `ScalarCurve`
- L113 _public enumerator_ `ScalarSwitch`
- L114 _public enumerator_ `ScalarArithmeticOperation`
- L115 _public enumerator_ `ScalarVariation`
- L116 _public enumerator_ `ScalarTable`
- L117 _public enumerator_ `ScalarExternal`
- L119 _public enumerator_ `String`
- L120 _public enumerator_ `StringConstant`
- L121 _public enumerator_ `StringParameter`
- L123 _public enumerator_ `Projector`
- L124 _public enumerator_ `ProjectorConstant`
- L125 _public enumerator_ `ProjectorParameter`
- L127 _public enumerator_ `Range`
- L128 _public enumerator_ `RangeFromScalar`
- L130 _public enumerator_ `Layout`
- L132 _public enumerator_ `PatchImage`
- L133 _public enumerator_ `PatchMesh`
- L135 _public enumerator_ `Surface`
- L136 _public enumerator_ `SurfaceNew`
- L137 _public enumerator_ `SurfaceSwitch`
- L138 _public enumerator_ `SurfaceVariation`
- L140 _public enumerator_ `LOD`
- L142 _public enumerator_ `SkeletalMesh`
- L143 _public enumerator_ `SkeletalMeshNew`
- L144 _public enumerator_ `SkeletalMeshMerge`
- L145 _public enumerator_ `SkeletalMeshConvert`
- L146 _public enumerator_ `SkeletalMeshModify`
- L147 _public enumerator_ `SkeletalMeshMorph`
- L148 _public enumerator_ `SkeletalMeshReshape`
- L149 _public enumerator_ `SkeletalMeshSwitch`
- L150 _public enumerator_ `SkeletalMeshVariation`
- L151 _public enumerator_ `SkeletalMeshTransform`
- L152 _public enumerator_ `SkeletalMeshTransformWithBone`
- L153 _public enumerator_ `SkeletalMeshClipWithSkeletalMesh`
- L155 _public enumerator_ `SkeletalMeshObject`
- L156 _public enumerator_ `SkeletalMeshObjectConvert`
- L157 _public enumerator_ `SkeletalMeshObjectParameter`
- L158 _public enumerator_ `SkeletalMeshObjectSwitch`
- L160 _public enumerator_ `Component`
- L161 _public enumerator_ `ComponentNew`
- L162 _public enumerator_ `ComponentSwitch`
- L163 _public enumerator_ `ComponentVariation`
- L165 _public enumerator_ `Object`
- L166 _public enumerator_ `ObjectNew`
- L167 _public enumerator_ `ObjectGroup`
- L169 _public enumerator_ `Modifier`
- L170 _public enumerator_ `ModifierSkeletalMeshMerge`
- L172 _public enumerator_ `SurfaceModifier`
- L173 _public enumerator_ `SurfaceModifierMeshClipMorphPlane`
- L174 _public enumerator_ `SurfaceModifierMeshClipWithMesh`
- L175 _public enumerator_ `SurfaceModifierMeshClipDeform`
- L176 _public enumerator_ `SurfaceModifierMeshClipWithUVMask`
- L177 _public enumerator_ `SurfaceModifierSurfaceEdit`
- L178 _public enumerator_ `SurfaceModifierTransformInMesh`
- L179 _public enumerator_ `SurfaceModifierTransformWithBone`
- L181 _public enumerator_ `External`
- L182 _public enumerator_ `ExternalOperation`
- L183 _public enumerator_ `ExternalParameter`
- L184 _public enumerator_ `ExternalSwitch`
- L186 _public enumerator_ `ExtensionData`
- L187 _public enumerator_ `ExtensionDataConstant`
- L188 _public enumerator_ `ExtensionDataSwitch`
- L189 _public enumerator_ `ExtensionDataVariation`
- L191 _public enumerator_ `Matrix`
- L192 _public enumerator_ `MatrixConstant`
- L193 _public enumerator_ `MatrixParameter`
- L195 _public enumerator_ `Material`
- L196 _public enumerator_ `MaterialConstant`
- L197 _public enumerator_ `MaterialTable`
- L198 _public enumerator_ `MaterialSwitch`
- L199 _public enumerator_ `MaterialVariation`
- L200 _public enumerator_ `MaterialParameter`
- L201 _public enumerator_ `MaterialExternal`
- L202 _public enumerator_ `MaterialSkeletalMeshObjectBreak`
- L203 _public enumerator_ `MaterialSkeletalMeshBreak`
- L204 _public enumerator_ `MaterialModify`
- L206 _public enumerator_ `ImageMaterialBreak`
- L207 _public enumerator_ `ScalarMaterialBreak`
- L208 _public enumerator_ `ColorMaterialBreak`
- L210 _public enumerator_ `Count`

#### struct `UE::Mutable::Private::Node::FNodeType`  
`struct FNodeType`  
_L215-237_
- desc: Information about the type of a node, to provide some means to the tools to deal generically with nodes.
- L217 _public prototype_ `FNodeType();`
- L218 _public prototype_ `FNodeType(Node::EType, const FNodeType* Parent);`
- L220 _public member_ `Node::EType Type;`
- L221 _public member_ `const FNodeType* Parent;`
- L223 _public function_ `inline bool IsA(const FNodeType* CandidateType) const`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MUTABLETOOLS_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Mutable` (scope `UE`)
- L10 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L14 _typedef_ `typedef Ptr<Node> NodePtr;` (scope `UE::Mutable::Private`)
- L15 _typedef_ `typedef Ptr<const Node> NodePtrConst;` (scope `UE::Mutable::Private`)
- L18 _typedef_ `typedef Ptr<NodeMap> NodeMapPtr;` (scope `UE::Mutable::Private`)
- L19 _typedef_ `typedef Ptr<const NodeMap> NodeMapPtrConst;` (scope `UE::Mutable::Private`)
- L271 _typedef_ `using FNodeType = Node::FNodeType;` (scope `UE::Mutable::Private`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeBool.h` (Internal)


#### class `UE::Mutable::Private::NodeBool`  
`class NodeBool : public Node`  
_L18-35_
- inherits: `Node`
- desc: Base class of any node that outputs a Bool value.
- L23 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L24 _public function_ `static const FNodeType* GetStaticType()`
- L29 _protected prototype_ `inline ~NodeBool() = default;` — Forbidden. Manage with the Ptr<> template.
- L33 _private member_ `static FNodeType StaticType;`

#### class `UE::Mutable::Private::NodeBoolConstant`  
`class NodeBoolConstant : public NodeBool`  
_L39-60_
- inherits: `NodeBool`
- desc: Node returning a Bool constant value.
- L43 _public member_ `bool Value = false;`
- L48 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L49 _public function_ `static const FNodeType* GetStaticType()`
- L54 _protected prototype_ `~NodeBoolConstant() = default;` — Forbidden. Manage with the Ptr<> template.
- L58 _private member_ `static FNodeType StaticType;`

#### class `UE::Mutable::Private::NodeBoolParameter`  
`class NodeBoolParameter : public NodeBool`  
_L64-89_
- inherits: `NodeBool`
- desc: Node that defines a Bool model parameter.
- L68 _public member_ `bool DefaultValue;`
- L69 _public member_ `FString Name;`
- L70 _public member_ `FString UID;`
- L72 _public member_ `TArray<Ptr<NodeRange>> Ranges;`
- L77 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L78 _public function_ `static const FNodeType* GetStaticType()`
- L83 _protected prototype_ `~NodeBoolParameter() = default;` — Forbidden. Manage with the Ptr<> template.
- L87 _private member_ `static FNodeType StaticType;`

#### class `UE::Mutable::Private::NodeBoolNot`  
`class NodeBoolNot : public NodeBool`  
_L93-114_
- inherits: `NodeBool`
- desc: Node that returns the oposite of the input value.
- L97 _public member_ `Ptr<NodeBool> Source;`
- L102 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L103 _public function_ `static const FNodeType* GetStaticType()`
- L108 _protected prototype_ `~NodeBoolNot() = default;` — Forbidden. Manage with the Ptr<> template.
- L112 _private member_ `static FNodeType StaticType;`

#### class `UE::Mutable::Private::NodeBoolAnd`  
`class NodeBoolAnd : public NodeBool`  
_L118-140_
- inherits: `NodeBool`
- L122 _public member_ `Ptr<NodeBool> A;`
- L123 _public member_ `Ptr<NodeBool> B;`
- L128 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L129 _public function_ `static const FNodeType* GetStaticType()`
- L134 _protected prototype_ `~NodeBoolAnd() = default;` — Forbidden. Manage with the Ptr<> template.
- L138 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MUTABLETOOLS_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Mutable` (scope `UE`)
- L14 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeColor.h` (Internal)


#### class `UE::Mutable::Private::NodeColor`  
`class NodeColor : public Node`  
_L18-35_
- inherits: `Node`
- desc: Base class of any node that outputs a color.
- L23 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L24 _public function_ `static const FNodeType* GetStaticType()`
- L29 _protected prototype_ `inline ~NodeColor() = default;` — Forbidden. Manage with the Ptr<> template.
- L33 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MUTABLETOOLS_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Mutable` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeColorArithmeticOperation.h` (Internal)


#### class `UE::Mutable::Private::NodeColorArithmeticOperation`  
`class NodeColorArithmeticOperation : public NodeColor`  
_L17-49_
- inherits: `NodeColor`
- desc: Perform a per - component arithmetic operation between two colors.
- L30 _public member_ `EOperation Operation;`
- L31 _public member_ `Ptr<NodeColor> A;`
- L32 _public member_ `Ptr<NodeColor> B;`
- L37 _public function_ `virtual const FNodeType* GetType() const` — Node type hierarchy data.
- L38 _public function_ `static const FNodeType* GetStaticType()`
- L43 _protected prototype_ `~NodeColorArithmeticOperation() = default;` — Forbidden. Manage with the Ptr<> template.
- L47 _private member_ `static FNodeType StaticType;`

#### enum `UE::Mutable::Private::NodeColorArithmeticOperation::EOperation`  
`enum class EOperation`  
_L22-28_
- desc: Possible arithmetic operations.
- L24 _public enumerator_ `Add`
- L25 _public enumerator_ `Subtract`
- L26 _public enumerator_ `Multiply`
- L27 _public enumerator_ `Divide`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MUTABLETOOLS_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Mutable` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeColorConstant.h` (Internal)


#### class `UE::Mutable::Private::NodeColorConstant`  
`class NodeColorConstant : public NodeColor`  
_L19-40_
- inherits: `NodeColor`
- desc: This node outputs a predefined color value.
- L23 _public member_ `FVector4f Value;`
- L28 _public function_ `virtual const FNodeType* GetType() const` — Node interface
- L29 _public function_ `static const FNodeType* GetStaticType()`
- L34 _protected prototype_ `~NodeColorConstant() = default;` — Forbidden. Manage with the Ptr<> template.
- L38 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MUTABLETOOLS_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Mutable` (scope `UE`)
- L14 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeColorExternal.h` (Internal)


#### class `UE::Mutable::Private::NodeColorExternal`  
`class NodeColorExternal : public NodeColor`  
_L14-30_
- inherits: `NodeColor`
- L18 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L19 _public function_ `static const FNodeType* GetStaticType()`
- L23 _protected prototype_ `virtual ~NodeColorExternal() override = default;` — Forbidden. Manage with the Ptr<> template.
- L26 _private member_ `static FNodeType StaticType;`
- L29 _public member_ `Ptr<NodeExternal> Node;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MUTABLETOOLS_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Mutable` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeColorFromScalars.h` (Internal)


#### class `UE::Mutable::Private::NodeColorFromScalars`  
`class NodeColorFromScalars : public NodeColor`  
_L19-43_
- inherits: `NodeColor`
- desc: Obtain a color by sampling an image at specific homogeneous coordinates.
- L23 _public member_ `Ptr<NodeScalar> X;`
- L24 _public member_ `Ptr<NodeScalar> Y;`
- L25 _public member_ `Ptr<NodeScalar> Z;`
- L26 _public member_ `Ptr<NodeScalar> W;`
- L31 _public function_ `virtual const FNodeType* GetType() const` — Node interface
- L32 _public function_ `static const FNodeType* GetStaticType()`
- L37 _protected prototype_ `~NodeColorFromScalars() = default;` — Forbidden. Manage with the Ptr<> template.
- L41 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MUTABLETOOLS_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Mutable` (scope `UE`)
- L14 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeColorMaterialBreak.h` (Internal)


#### class `UE::Mutable::Private::NodeColorMaterialBreak`  
`class NodeColorMaterialBreak : public NodeColor`  
_L16-37_
- inherits: `NodeColor`
- desc: NodeColorMaterialBreak class.
- L20 _public member_ `Ptr<NodeMaterial> MaterialSource;`
- L21 _public member_ `FParameterKey ParameterKey;`
- L26 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L27 _public function_ `static const FNodeType* GetStaticType()`
- L32 _protected prototype_ `~NodeColorMaterialBreak() = default;` — Forbidden. Manage with the Ptr<> template.
- L36 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MUTABLETOOLS_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Mutable` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeColorParameter.h` (Internal)


#### class `UE::Mutable::Private::NodeColorParameter`  
`class NodeColorParameter : public NodeColor`  
_L20-45_
- inherits: `NodeColor`
- desc: Node that defines a color model parameter.
- L24 _public member_ `FVector4f DefaultValue;`
- L25 _public member_ `FString Name;`
- L26 _public member_ `FString Uid;`
- L28 _public member_ `TArray<Ptr<NodeRange>> Ranges;`
- L33 _public function_ `virtual const FNodeType* GetType() const` — Node interface
- L34 _public function_ `static const FNodeType* GetStaticType()`
- L39 _protected prototype_ `~NodeColorParameter() = default;` — Forbidden. Manage with the Ptr<> template.
- L43 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API MUTABLETOOLS_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Mutable` (scope `UE`)
- L15 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeColorSampleImage.h` (Internal)


#### class `UE::Mutable::Private::NodeColorSampleImage`  
`class NodeColorSampleImage : public NodeColor`  
_L20-43_
- inherits: `NodeColor`
- desc: Obtain a color by sampling an image at specific homogeneous coordinates.
- L24 _public member_ `Ptr<NodeImage> Image;`
- L25 _public member_ `Ptr<NodeScalar> X;`
- L26 _public member_ `Ptr<NodeScalar> Y;`
- L31 _public function_ `virtual const FNodeType* GetType() const` — Node interface
- L32 _public function_ `static const FNodeType* GetStaticType()`
- L37 _protected prototype_ `~NodeColorSampleImage() = default;` — Forbidden. Manage with the Ptr<> template.
- L41 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MUTABLETOOLS_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Mutable` (scope `UE`)
- L15 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeColorSwitch.h` (Internal)


#### class `UE::Mutable::Private::NodeColorSwitch`  
`class NodeColorSwitch : public NodeColor`  
_L19-41_
- inherits: `NodeColor`
- desc: This node selects an output Color from a set of input Colors based on a parameter.
- L23 _public member_ `Ptr<NodeScalar> Parameter;`
- L24 _public member_ `TArray<Ptr<NodeColor>> Options;`
- L29 _public function_ `virtual const FNodeType* GetType() const` — Node type hierarchy data.
- L30 _public function_ `static const FNodeType* GetStaticType()`
- L35 _protected prototype_ `~NodeColorSwitch() = default;` — Forbidden. Manage with the Ptr<> template.
- L39 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MUTABLETOOLS_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Mutable` (scope `UE`)
- L14 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeColorTable.h` (Internal)


#### class `UE::Mutable::Private::NodeColorTable`  
`class NodeColorTable : public NodeColor`  
_L19-44_
- inherits: `NodeColor`
- desc: This node provides the meshes stored in the column of a table.
- L23 _public member_ `FString ParameterName;`
- L24 _public member_ `Ptr<FTable> Table;`
- L25 _public member_ `FString ColumnName;`
- L26 _public member_ `bool bNoneOption = false;`
- L27 _public member_ `FString DefaultRowName;`
- L32 _public function_ `virtual const FNodeType* GetType() const override` — Node interface
- L33 _public function_ `static const FNodeType* GetStaticType()`
- L38 _protected prototype_ `~NodeColorTable() = default;` — Forbidden. Manage with the Ptr<> template.
- L42 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MUTABLETOOLS_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Mutable` (scope `UE`)
- L14 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeColorToSRGB.h` (Internal)


#### class `UE::Mutable::Private::NodeColorToSRGB`  
`class NodeColorToSRGB : public NodeColor`  
_L18-39_
- inherits: `NodeColor`
- desc: Convert a linear color to sRGB
- L22 _public member_ `Ptr<NodeColor> Color;`
- L27 _public function_ `virtual const FNodeType* GetType() const` — Node interface
- L28 _public function_ `static const FNodeType* GetStaticType()`
- L33 _protected prototype_ `~NodeColorToSRGB() = default;` — Forbidden. Manage with the Ptr<> template.
- L37 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MUTABLETOOLS_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Mutable` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeColorVariation.h` (Internal)


#### class `UE::Mutable::Private::NodeColorVariation`  
`class NodeColorVariation : public NodeColor`  
_L17-46_
- inherits: `NodeColor`
- desc: Select different color subgraphs based on active tags.
- L21 _public member_ `Ptr<NodeColor> DefaultColor;`
- L29 _public member_ `TArray<FVariation> Variations;`
- L34 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L35 _public function_ `static const FNodeType* GetStaticType()`
- L40 _protected prototype_ `~NodeColorVariation() = default;` — Forbidden. Manage with the Ptr<> template.
- L44 _private member_ `static FNodeType StaticType;`

#### struct `UE::Mutable::Private::NodeColorVariation::FVariation`  
`struct FVariation`  
_L23-27_
- L25 _public member_ `Ptr<NodeColor> Color;`
- L26 _public member_ `FString Tag;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MUTABLETOOLS_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Mutable` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeComponent.h` (Internal)


#### class `UE::Mutable::Private::NodeComponent`  
`class NodeComponent : public Node`  
_L18-40_
- inherits: `Node`
- L22 _public function_ `virtual const FNodeType* GetType() const override` — Node interface
- L23 _public function_ `static const FNodeType* GetStaticType()`
- L29 _public prototype_ `virtual const class NodeComponentNew* GetParentComponentNew() const = 0;`
- L34 _protected prototype_ `inline ~NodeComponent() = default;` — Forbidden. Manage with the Ptr<> template.
- L38 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MUTABLETOOLS_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Mutable` (scope `UE`)
- L14 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeComponentNew.h` (Internal)


#### class `UE::Mutable::Private::NodeComponentNew`  
`class NodeComponentNew : public NodeComponent`  
_L19-61_
- inherits: `NodeComponent`
- L24 _public member_ `FComponentId Id = INDEX_NONE;` — Externally managed id assigned to this component.
- L26 _public member_ `Ptr<NodeMaterial> OverlayMaterial;`
- L28 _public member_ `Ptr<NodeSkeletalMeshObject> SkeletalMeshObject;`
- L31 _public member_ `TMap<const FName, Ptr<NodeMaterial>> OverrideMaterials;` — Map where the key is the target Material slot and the value the replacement material to be used in the target material slot
- L34 _public member_ `TMap<const FName, Ptr<NodeMaterial>> OverlayMaterials;` — Map where the key is the target Material slot and the value the material to be rendered on top in the target material slot
- L40 _public function_ `virtual const FNodeType* GetType() const override`
- L41 _public function_ `static const FNodeType* GetStaticType()`
- L46 _public function_ `virtual const class NodeComponentNew* GetParentComponentNew() const override`
- L55 _protected prototype_ `~NodeComponentNew() = default;` — Forbidden. Manage with the Ptr<> template.
- L59 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API MUTABLETOOLS_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Mutable` (scope `UE`)
- L16 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeComponentSwitch.h` (Internal)


#### class `UE::Mutable::Private::NodeComponentSwitch`  
`class NodeComponentSwitch : public NodeComponent`  
_L19-44_
- inherits: `NodeComponent`
- desc: This node selects an output component from a set of input components based on a parameter.
- L23 _public member_ `Ptr<NodeScalar> Parameter;`
- L24 _public member_ `TArray<Ptr<NodeComponent>> Options;`
- L29 _public function_ `virtual const FNodeType* GetType() const` — Node type hierarchy data.
- L30 _public function_ `static const FNodeType* GetStaticType()`
- L33 _public function_ `virtual const class NodeComponentNew* GetParentComponentNew() const override` — NodeComponent interface
- L38 _protected prototype_ `~NodeComponentSwitch() = default;` — Forbidden. Manage with the Ptr<> template.
- L42 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MUTABLETOOLS_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Mutable` (scope `UE`)
- L14 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeComponentVariation.h` (Internal)


#### class `UE::Mutable::Private::NodeComponentVariation`  
`class NodeComponentVariation : public NodeComponent`  
_L17-49_
- inherits: `NodeComponent`
- desc: Select different component subgraphs based on active tags.
- L21 _public member_ `Ptr<NodeComponent> DefaultComponent;`
- L29 _public member_ `TArray<FVariation> Variations;`
- L34 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L35 _public function_ `static const FNodeType* GetStaticType()`
- L38 _public function_ `virtual const class NodeComponentNew* GetParentComponentNew() const override` — NodeComponent interface
- L43 _protected prototype_ `~NodeComponentVariation() = default;` — Forbidden. Manage with the Ptr<> template.
- L47 _private member_ `static FNodeType StaticType;`

#### struct `UE::Mutable::Private::NodeComponentVariation::FVariation`  
`struct FVariation`  
_L23-27_
- L25 _public member_ `Ptr<NodeComponent> Component;`
- L26 _public member_ `FString Tag;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MUTABLETOOLS_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Mutable` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeExtensionData.h` (Internal)


#### class `UE::Mutable::Private::NodeExtensionData`  
`class NodeExtensionData : public Node`  
_L18-37_
- inherits: `Node`
- desc: Node that evaluates to an ExtensionData
- L25 _public function_ `virtual const FNodeType* GetType() const override`
- L26 _public function_ `static const FNodeType* GetStaticType()`
- L31 _protected prototype_ `inline ~NodeExtensionData() = default;` — Forbidden. Manage with the Ptr<> template.
- L35 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MUTABLETOOLS_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Mutable` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeExtensionDataConstant.h` (Internal)


#### class `UE::Mutable::Private::NodeExtensionDataConstant`  
`class NodeExtensionDataConstant : public NodeExtensionData`  
_L17-37_
- inherits: `NodeExtensionData`
- desc: Node that outputs a constant ExtensionData \ingroup model
- L20 _public member_ `PASSTHROUGH_ID ExtensionDataId = PASSTHROUGH_ID_INVALID;`
- L25 _public function_ `virtual const FNodeType* GetType() const override`
- L26 _public function_ `static const FNodeType* GetStaticType()`
- L31 _protected prototype_ `~NodeExtensionDataConstant() = default;` — Forbidden. Manage with the Ptr<> template.
- L35 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MUTABLETOOLS_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Mutable` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeExtensionDataSwitch.h` (Internal)


#### class `UE::Mutable::Private::NodeExtensionDataSwitch`  
`class NodeExtensionDataSwitch : public NodeExtensionData`  
_L16-52_
- inherits: `NodeExtensionData`
- L20 _public member_ `Ptr<NodeScalar> Parameter;`
- L21 _public member_ `TArray<Ptr<NodeExtensionData>> Options;`
- L28 _public function_ `virtual const FNodeType* GetType() const override`
- L29 _public function_ `static const FNodeType* GetStaticType()`
- L34 _public prototype_ `Ptr<NodeScalar> GetParameter() const;`
- L35 _public prototype_ `void SetParameter(Ptr<NodeScalar> InParameter);`
- L37 _public prototype_ `void SetOptionCount(int);`
- L39 _public prototype_ `Ptr<NodeExtensionData> GetOption(int32 t) const;`
- L40 _public prototype_ `void SetOption(int32 t, Ptr<NodeExtensionData>);`
- L46 _protected prototype_ `~NodeExtensionDataSwitch() = default;` — Forbidden. Manage with the Ptr<> template.
- L50 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MUTABLETOOLS_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Mutable` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeExtensionDataVariation.h` (Internal)


#### class `UE::Mutable::Private::NodeExtensionDataVariation`  
`class NodeExtensionDataVariation : public NodeExtensionData`  
_L15-59_
- inherits: `NodeExtensionData`
- L19 _public member_ `Ptr<NodeExtensionData> DefaultValue;`
- L27 _public member_ `TArray<FVariation> Variations;`
- L34 _public function_ `virtual const FNodeType* GetType() const override`
- L35 _public function_ `static const FNodeType* GetStaticType()`
- L40 _public prototype_ `void SetDefaultValue(Ptr<NodeExtensionData> InValue);`
- L42 _public prototype_ `void SetVariationCount(int32 InCount);`
- L43 _public prototype_ `int GetVariationCount() const;`
- L45 _public prototype_ `void SetVariationTag(int32 InIndex, const FString& InTag);`
- L47 _public prototype_ `void SetVariationValue(int32 InIndex, Ptr<NodeExtensionData> InValue);`
- L53 _protected prototype_ `~NodeExtensionDataVariation() = default;` — Forbidden. Manage with the Ptr<> template.
- L57 _private member_ `static FNodeType StaticType;`

#### struct `UE::Mutable::Private::NodeExtensionDataVariation::FVariation`  
`struct FVariation`  
_L21-25_
- L23 _public member_ `Ptr<NodeExtensionData> Value;`
- L24 _public member_ `FString Tag;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MUTABLETOOLS_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Mutable` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeExternal.h` (Internal)


#### class `UE::Mutable::Private::NodeExternal`  
`class NodeExternal : public Node`  
_L12-25_
- inherits: `Node`
- L16 _public function_ `virtual const FNodeType* GetType() const override` — Node interface
- L17 _public function_ `static const FNodeType* GetStaticType()`
- L21 _protected prototype_ `virtual ~NodeExternal() override = default;` — Forbidden. Manage with the Ptr<> template.
- L24 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API MUTABLETOOLS_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Mutable` (scope `UE`)
- L10 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeExternalOperation.h` (Internal)


#### class `UE::Mutable::Private::NodeExternalOperation`  
`class NodeExternalOperation : public NodeExternal`  
_L15-33_
- inherits: `NodeExternal`
- L19 _public function_ `virtual const FNodeType* GetType() const override` — Node interface
- L20 _public function_ `static const FNodeType* GetStaticType()`
- L24 _protected prototype_ `virtual ~NodeExternalOperation() override = default;` — Forbidden. Manage with the Ptr<> template.
- L27 _private member_ `static FNodeType StaticType;`
- L30 _public member_ `FInstancedStruct OperationInstancedStruct;`
- L32 _public member_ `TArray<Ptr<Node>> Inputs;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MUTABLETOOLS_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Mutable` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeExternalParameter.h` (Internal)


#### class `UE::Mutable::Private::NodeExternalParameter`  
`class NodeExternalParameter : public NodeExternal`  
_L15-35_
- inherits: `NodeExternal`
- L19 _public function_ `virtual const FNodeType* GetType() const override` — Node interface
- L20 _public function_ `static const FNodeType* GetStaticType()`
- L23 _protected prototype_ `virtual ~NodeExternalParameter() override = default;`
- L26 _private member_ `static FNodeType StaticType;`
- L29 _public member_ `TManagedPtr<const FInstancedStruct> DefaultValue;`
- L31 _public member_ `FString Name;`
- L32 _public member_ `FString UID;`
- L34 _public member_ `TArray<Ptr<NodeRange>> Ranges;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MUTABLETOOLS_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Mutable` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeExternalSwitch.h` (Internal)


#### class `UE::Mutable::Private::NodeExternalSwitch`  
`class NodeExternalSwitch : public NodeExternal`  
_L17-32_
- inherits: `NodeExternal`
- L20 _public member_ `Ptr<NodeScalar> Parameter;`
- L21 _public member_ `TArray<Ptr<NodeExternal>> Options;`
- L23 _public function_ `virtual const FNodeType* GetType() const override`
- L24 _public function_ `static const FNodeType* GetStaticType()`
- L28 _protected prototype_ `virtual ~NodeExternalSwitch() override = default;` — Forbidden. Manage with the Ptr<> template.
- L31 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MUTABLETOOLS_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Mutable` (scope `UE`)
- L15 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeImage.h` (Internal)


#### struct `UE::Mutable::Private::FSourceDataDescriptor`  
`struct FSourceDataDescriptor`  
_L23-120_
- desc: Data related to the a source image that is necessary to classify the final image and mesh fragments that are derived from this source.
- L38 _public member_ `int32 OptionalMaxLODSize = ENeutral;` — The size of the first mip to be considered optional. Mips with equal or larger size will be considered optional. If -1 it means the entire descriptor is neutral. If -2 it means the descriptor is invalid (results of an operation that shouldn't happen). If less than equal 0 it means all mips are non optional.
- L44 _public member_ `int32 OptionalLODBias = 0;` — Bias to the final number of optional mips. Any mip will have at least this number of optional lods if not in the NumNonOptionalLODs range.
- L47 _public member_ `int32 NumNonOptionalLODs = 0;` — Number of lods from the tail that will never be considered optional
- L50 _public member_ `bool bNoMipmaps = false;` — Whether or not the source texture had mip generation settings set to NoMipmaps.
- L53 _public member_ `TArray<FString> Tags;` — Source tags that mark this data and prevent it from mixing with other data at compile time.
- L56 _public member_ `uint32 SourceId = MAX_uint32;` — Source Id
- L58 _public function_ `inline bool operator==(const FSourceDataDescriptor& Other) const`
- L68 _public function_ `inline bool IsInvalid() const`
- L73 _public function_ `inline bool IsNeutral() const`
- L78 _public function_ `void CombineWith(const FSourceDataDescriptor& Other)`

#### enum `UE::Mutable::Private::FSourceDataDescriptor::ESpecialValues`  
`enum ESpecialValues`  
_L25-29_
- L27 _public enumerator_ `EInvalid = -2`
- L28 _public enumerator_ `ENeutral = -1`

#### class `UE::Mutable::Private::NodeImage`  
`class NodeImage : public Node`  
_L124-141_
- inherits: `Node`
- desc: Base class of any node that outputs an image.
- L129 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L130 _public function_ `static const FNodeType* GetStaticType()`
- L135 _protected prototype_ `inline ~NodeImage() = default;` — Forbidden. Manage with the Ptr<> template.
- L139 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MUTABLETOOLS_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Mutable` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L17 _typedef_ `typedef Ptr<NodeImage> NodeImagePtr;` (scope `UE::Mutable::Private`)
- L18 _typedef_ `typedef Ptr<const NodeImage> NodeImagePtrConst;` (scope `UE::Mutable::Private`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeImageBinarise.h` (Internal)


#### class `UE::Mutable::Private::NodeImageBinarise`  
`class NodeImageBinarise : public NodeImage`  
_L17-39_
- inherits: `NodeImage`
- desc: Node that multiplies the colors of an image, channel by channel.
- L21 _public member_ `Ptr<NodeImage> Base;`
- L22 _public member_ `Ptr<NodeScalar> Threshold;`
- L27 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L28 _public function_ `static const FNodeType* GetStaticType()`
- L33 _protected prototype_ `~NodeImageBinarise() = default;` — Forbidden. Manage with the Ptr<> template.
- L37 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MUTABLETOOLS_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Mutable` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeImageColorMap.h` (Internal)


#### class `UE::Mutable::Private::NodeImageColorMap`  
`class NodeImageColorMap : public NodeImage`  
_L18-41_
- inherits: `NodeImage`
- desc: This node changes the colors of a selectd part of the image, applying a color map from conteined in another image.
- L22 _public member_ `Ptr<NodeImage> Base;`
- L23 _public member_ `Ptr<NodeImage> Mask;`
- L24 _public member_ `Ptr<NodeImage> Map;`
- L29 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L30 _public function_ `static const FNodeType* GetStaticType()`
- L35 _protected prototype_ `~NodeImageColorMap() = default;` — Forbidden. Manage with the Ptr<> template.
- L39 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MUTABLETOOLS_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Mutable` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeImageConditional.h` (Internal)


#### class `UE::Mutable::Private::NodeImageConditional`  
`class NodeImageConditional : public NodeImage`  
_L17-40_
- inherits: `NodeImage`
- desc: This node selects an output image from a set of input images based on a parameter.
- L21 _public member_ `Ptr<NodeBool> Parameter;`
- L22 _public member_ `Ptr<NodeImage> True;`
- L23 _public member_ `Ptr<NodeImage> False;`
- L28 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L29 _public function_ `static const FNodeType* GetStaticType()`
- L34 _protected prototype_ `~NodeImageConditional() = default;` — Forbidden. Manage with the Ptr<> template.
- L38 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MUTABLETOOLS_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Mutable` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeImageConform.h` (Internal)


#### class `UE::Mutable::Private::NodeImageConform`  
`class NodeImageConform : public NodeImage`  
_L18-40_
- inherits: `NodeImage`
- desc: Node that conforms an image to a given image descriptor.
- L22 _public member_ `FImageDesc ConformDescriptor;`
- L23 _public member_ `Ptr<NodeImage> Source;`
- L28 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L29 _public function_ `static const FNodeType* GetStaticType()`
- L34 _protected prototype_ `~NodeImageConform() = default;` — Forbidden. Manage with the Ptr<> template.
- L38 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MUTABLETOOLS_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Mutable` (scope `UE`)
- L14 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeImageConstant.h` (Internal)


#### class `UE::Mutable::Private::NodeImageConstant`  
`class NodeImageConstant : public NodeImage`  
_L17-42_
- inherits: `NodeImage`
- desc: Node that outputs a constant image.
- L22 _public member_ `TManagedPtr<FImage> Image;`
- L25 _public member_ `FSourceDataDescriptor SourceDataDescriptor;`
- L30 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L31 _public function_ `static const FNodeType* GetStaticType()`
- L36 _protected prototype_ `~NodeImageConstant() = default;` — Forbidden. Manage with the Ptr<> template.
- L40 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MUTABLETOOLS_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Mutable` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeImageConvert.h` (Internal)


#### class `UE::Mutable::Private::NodeImageConvert`  
`class NodeImageConvert : public NodeImage`  
_L15-30_
- inherits: `NodeImage`
- L18 _public member_ `Ptr<NodeImageObject> ImageParameter;`
- L19 _public member_ `FImageDesc ImageDescriptor;`
- L22 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L23 _public function_ `static const FNodeType* GetStaticType()`
- L26 _protected prototype_ `virtual ~NodeImageConvert() override = default;`
- L29 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MUTABLETOOLS_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Mutable` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeImageExternal.h` (Internal)


#### class `UE::Mutable::Private::NodeImageExternal`  
`class NodeImageExternal : public NodeImage`  
_L14-30_
- inherits: `NodeImage`
- L18 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L19 _public function_ `static const FNodeType* GetStaticType()`
- L23 _protected prototype_ `virtual ~NodeImageExternal() override = default;` — Forbidden. Manage with the Ptr<> template.
- L26 _private member_ `static FNodeType StaticType;`
- L29 _public member_ `Ptr<NodeExternal> Node;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MUTABLETOOLS_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Mutable` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeImageFormat.h` (Internal)


#### class `UE::Mutable::Private::NodeImageFormat`  
`class NodeImageFormat : public NodeImage`  
_L18-43_
- inherits: `NodeImage`
- desc: Node that composes a new image by gathering pixel data from channels in other images.
- L22 _public member_ `EImageFormat Format = EImageFormat::None;`
- L23 _public member_ `EImageFormat FormatIfAlpha = EImageFormat::None;`
- L24 _public member_ `bool bNeedsNormalmapLAEncoding = false;`
- L26 _public member_ `Ptr<NodeImage> Source;`
- L31 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L32 _public function_ `static const FNodeType* GetStaticType()`
- L37 _protected prototype_ `~NodeImageFormat() = default;` — Forbidden. Manage with the Ptr<> template.
- L41 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MUTABLETOOLS_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Mutable` (scope `UE`)
- L14 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeImageFromMaterialParameter.h` (Internal)


#### class `UE::Mutable::Private::NodeImageFromMaterialParameter`  
`class NodeImageFromMaterialParameter : public NodeImage`  
_L14-34_
- inherits: `NodeImage`
- L18 _public member_ `FParameterKey ImageParameterKey;`
- L23 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L24 _public function_ `static const FNodeType* GetStaticType()`
- L29 _protected prototype_ `~NodeImageFromMaterialParameter() = default;` — Forbidden. Manage with the Ptr<> template.
- L33 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MUTABLETOOLS_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Mutable` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeImageInterpolate.h` (Internal)


#### class `UE::Mutable::Private::NodeImageInterpolate`  
`class NodeImageInterpolate : public NodeImage`  
_L23-45_
- inherits: `NodeImage`
- desc: Node that interpolates linearly between several images based on a weight. The different input images are uniformly distributed in the 0 to 1 range: - if two images are set, the first one is 0.0 and the second one is 1.0 - if three images are set, the first one is 0.0 the second one is 0.5 and the third one 1.0 regardless of the input slots used: If B and C are set, but not A, B will be at weight 0 and C will be at weight 1
- L27 _public member_ `Ptr<NodeScalar> Factor;`
- L28 _public member_ `TArray<Ptr<NodeImage>> Targets;`
- L33 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L34 _public function_ `static const FNodeType* GetStaticType()`
- L39 _protected prototype_ `~NodeImageInterpolate() = default;` — Forbidden. Manage with the Ptr<> template.
- L43 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MUTABLETOOLS_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Mutable` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeImageInvert.h` (Internal)


#### class `UE::Mutable::Private::NodeImageInvert`  
`class NodeImageInvert : public NodeImage`  
_L16-37_
- inherits: `NodeImage`
- desc: Node that inverts the colors of an image, channel by channel.
- L20 _public member_ `Ptr<NodeImage> Base;`
- L25 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L26 _public function_ `static const FNodeType* GetStaticType()`
- L31 _protected prototype_ `~NodeImageInvert() = default;` — Forbidden. Manage with the Ptr<> template.
- L35 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MUTABLETOOLS_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Mutable` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeImageLayer.h` (Internal)


#### class `UE::Mutable::Private::NodeImageLayer`  
`class NodeImageLayer : public NodeImage`  
_L18-42_
- inherits: `NodeImage`
- desc: This node applies a layer blending effect on a base image using a mask and a blended image.
- L22 _public member_ `Ptr<NodeImage> Base;`
- L23 _public member_ `Ptr<NodeImage> Mask;`
- L24 _public member_ `Ptr<NodeImage> Blended;`
- L25 _public member_ `EBlendType Type;`
- L30 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L31 _public function_ `static const FNodeType* GetStaticType()`
- L36 _protected prototype_ `~NodeImageLayer() = default;` — Forbidden. Manage with the Ptr<> template.
- L40 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MUTABLETOOLS_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Mutable` (scope `UE`)
- L14 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeImageLayerColor.h` (Internal)


#### class `UE::Mutable::Private::NodeImageLayerColor`  
`class NodeImageLayerColor : public NodeImage`  
_L18-42_
- inherits: `NodeImage`
- desc: This node applies a layer blending effect on a base image using a mask and a color.
- L22 _public member_ `Ptr<NodeImage> Base;`
- L23 _public member_ `Ptr<NodeImage> Mask;`
- L24 _public member_ `Ptr<NodeColor> Color;`
- L25 _public member_ `EBlendType Type;`
- L30 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L31 _public function_ `static const FNodeType* GetStaticType()`
- L36 _protected prototype_ `~NodeImageLayerColor() = default;` — Forbidden. Manage with the Ptr<> template.
- L40 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MUTABLETOOLS_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Mutable` (scope `UE`)
- L14 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeImageLuminance.h` (Internal)


#### class `UE::Mutable::Private::NodeImageLuminance`  
`class NodeImageLuminance : public NodeImage`  
_L16-37_
- inherits: `NodeImage`
- desc: Calculate the luminance of an image into a new single - channel image.
- L20 _public member_ `Ptr<NodeImage> Source;`
- L25 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L26 _public function_ `static const FNodeType* GetStaticType()`
- L31 _protected prototype_ `~NodeImageLuminance() = default;` — Forbidden. Manage with the Ptr<> template.
- L35 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MUTABLETOOLS_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Mutable` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeImageMaterialBreak.h` (Internal)


#### class `UE::Mutable::Private::NodeImageMaterialBreak`  
`class NodeImageMaterialBreak : public NodeImage`  
_L16-37_
- inherits: `NodeImage`
- desc: NodeImageMaterialBreak class.
- L20 _public member_ `Ptr<NodeMaterial> MaterialSource;`
- L21 _public member_ `FParameterKey ParameterKey;`
- L26 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L27 _public function_ `static const FNodeType* GetStaticType()`
- L32 _protected prototype_ `~NodeImageMaterialBreak() = default;` — Forbidden. Manage with the Ptr<> template.
- L36 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MUTABLETOOLS_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Mutable` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeImageMipmap.h` (Internal)


#### class `UE::Mutable::Private::NodeImageMipmap`  
`class NodeImageMipmap : public NodeImage`  
_L18-42_
- inherits: `NodeImage`
- desc: Generate mimaps for an image.
- L22 _public member_ `Ptr<NodeImage> Source;`
- L23 _public member_ `Ptr<NodeScalar> Factor;`
- L25 _public member_ `FMipmapGenerationSettings Settings;`
- L30 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L31 _public function_ `static const FNodeType* GetStaticType()`
- L36 _protected prototype_ `~NodeImageMipmap() = default;` — Forbidden. Manage with the Ptr<> template.
- L40 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MUTABLETOOLS_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Mutable` (scope `UE`)
- L14 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeImageMultiLayer.h` (Internal)


#### class `UE::Mutable::Private::NodeImageMultiLayer`  
`class NodeImageMultiLayer : public NodeImage`  
_L20-45_
- inherits: `NodeImage`
- desc: This node applies any numbre of layer blending effect on a base image using a mask and a blended image. The number of layers depends on a scalar input of this node.
- L24 _public member_ `Ptr<NodeImage> Base;`
- L25 _public member_ `Ptr<NodeImage> Mask;`
- L26 _public member_ `Ptr<NodeImage> Blended;`
- L27 _public member_ `Ptr<NodeRange> Range;`
- L28 _public member_ `EBlendType Type;`
- L33 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L34 _public function_ `static const FNodeType* GetStaticType()`
- L39 _protected prototype_ `~NodeImageMultiLayer() = default;` — Forbidden. Manage with the Ptr<> template.
- L43 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MUTABLETOOLS_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Mutable` (scope `UE`)
- L14 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeImageNormalComposite.h` (Internal)


#### class `UE::Mutable::Private::NodeImageNormalComposite`  
`class NodeImageNormalComposite : public NodeImage`  
_L17-41_
- inherits: `NodeImage`
- desc: Node that inverts the colors of an image, channel by channel.
- L21 _public member_ `Ptr<NodeImage> Base;`
- L22 _public member_ `Ptr<NodeImage> Normal;`
- L23 _public member_ `float Power = 1.0f;`
- L24 _public member_ `ECompositeImageMode Mode;`
- L29 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L30 _public function_ `static const FNodeType* GetStaticType()`
- L35 _protected prototype_ `~NodeImageNormalComposite() = default;` — Forbidden. Manage with the Ptr<> template.
- L39 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MUTABLETOOLS_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Mutable` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeImageObject.h` (Internal)


#### class `UE::Mutable::Private::NodeImageObject`  
`class NodeImageObject : public NodeImage`  
_L12-24_
- inherits: `NodeImage`
- desc: TODO GMT It should inherit from Node
- L16 _public function_ `virtual const FNodeType* GetType() const override` — Node interface
- L17 _public function_ `static const FNodeType* GetStaticType()`
- L20 _protected function_ `virtual ~NodeImageObject() override`
- L23 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API MUTABLETOOLS_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Mutable` (scope `UE`)
- L10 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeImageObjectParameter.h` (Internal)


#### class `UE::Mutable::Private::NodeImageObjectParameter`  
`class NodeImageObjectParameter : public NodeImageObject`  
_L17-39_
- inherits: `NodeImageObject`
- L21 _public member_ `FString Name;` — Name of the parameter
- L24 _public member_ `FString UID;` — User provided ID to identify the parameter.
- L27 _public member_ `TArray<Ptr<NodeRange>> Ranges;` — Ranges for the parameter in case it is multidimensional.
- L30 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L31 _public function_ `static const FNodeType* GetStaticType()`
- L35 _protected prototype_ `virtual ~NodeImageObjectParameter() override = default;` — Forbidden. Manage with the Ptr<> template.
- L38 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MUTABLETOOLS_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Mutable` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeImagePlainColor.h` (Internal)


#### class `UE::Mutable::Private::NodeImagePlainColor`  
`class NodeImagePlainColor : public NodeImage`  
_L18-42_
- inherits: `NodeImage`
- desc: Node that multiplies the colors of an image, channel by channel.
- L22 _public member_ `Ptr<NodeColor> Color;`
- L23 _public member_ `int32 SizeX = 4;`
- L24 _public member_ `int32 SizeY = 4;`
- L25 _public member_ `EImageFormat Format = EImageFormat::RGBA_UByte;`
- L30 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L31 _public function_ `static const FNodeType* GetStaticType()`
- L36 _protected prototype_ `~NodeImagePlainColor() = default;` — Forbidden. Manage with the Ptr<> template.
- L40 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MUTABLETOOLS_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Mutable` (scope `UE`)
- L14 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeImageProject.h` (Internal)


#### class `UE::Mutable::Private::NodeImageProject`  
`class NodeImageProject : public NodeImage`  
_L20-53_
- inherits: `NodeImage`
- L24 _public member_ `Ptr<NodeProjector> Projector;`
- L25 _public member_ `Ptr<NodeMesh> Mesh;`
- L26 _public member_ `Ptr<NodeScalar> AngleFadeStart;`
- L27 _public member_ `Ptr<NodeScalar> AngleFadeEnd;`
- L28 _public member_ `Ptr<NodeImage> Image;`
- L29 _public member_ `Ptr<NodeImage> Mask;`
- L30 _public member_ `FUintVector2 ImageSize;`
- L31 _public member_ `uint8 Layout = 0;`
- L32 _public member_ `bool bIsRGBFadingEnabled = true;`
- L33 _public member_ `bool bIsAlphaFadingEnabled = true;`
- L34 _public member_ `bool bEnableTextureSeamCorrection = true;`
- L35 _public member_ `ESamplingMethod SamplingMethod = ESamplingMethod::Point;`
- L36 _public member_ `EMinFilterMethod MinFilterMethod = EMinFilterMethod::None;`
- L41 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L42 _public function_ `static const FNodeType* GetStaticType()`
- L47 _protected prototype_ `~NodeImageProject() = default;` — Forbidden. Manage with the Ptr<> template.
- L51 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API MUTABLETOOLS_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Mutable` (scope `UE`)
- L16 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeImageResize.h` (Internal)


#### class `UE::Mutable::Private::NodeImageResize`  
`class NodeImageResize : public NodeImage`  
_L16-42_
- inherits: `NodeImage`
- desc: Node that multiplies the colors of an image, channel by channel.
- L20 _public member_ `Ptr<NodeImage> Base;`
- L22 _public member_ `bool bRelative = true;`
- L24 _public member_ `float SizeX = 0.5f;`
- L25 _public member_ `float SizeY = 0.5f;`
- L30 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L31 _public function_ `static const FNodeType* GetStaticType()`
- L36 _protected prototype_ `~NodeImageResize() = default;` — Forbidden. Manage with the Ptr<> template.
- L40 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MUTABLETOOLS_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Mutable` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeImageSaturate.h` (Internal)


#### class `UE::Mutable::Private::NodeImageSaturate`  
`class NodeImageSaturate : public NodeImage`  
_L20-43_
- inherits: `NodeImage`
- desc: Change the saturation of an image.This node can be used to increase the saturation with a factor bigger than 1, or to decrease it or desaturate it completely with a factor smaller than 1 or 0.
- L24 _public member_ `Ptr<NodeImage> Source;`
- L26 _public member_ `Ptr<NodeScalar> Factor;`
- L31 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L32 _public function_ `static const FNodeType* GetStaticType()`
- L37 _protected prototype_ `~NodeImageSaturate() = default;` — Forbidden. Manage with the Ptr<> template.
- L41 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MUTABLETOOLS_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Mutable` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeImageSwitch.h` (Internal)


#### class `UE::Mutable::Private::NodeImageSwitch`  
`class NodeImageSwitch : public NodeImage`  
_L17-40_
- inherits: `NodeImage`
- desc: This node selects an output image from a set of input images based on a parameter.
- L21 _public member_ `Ptr<NodeScalar> Parameter;`
- L23 _public member_ `TArray<Ptr<NodeImage>> Options;`
- L28 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L29 _public function_ `static const FNodeType* GetStaticType()`
- L34 _protected prototype_ `~NodeImageSwitch() = default;` — Forbidden. Manage with the Ptr<> template.
- L38 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MUTABLETOOLS_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Mutable` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeImageSwizzle.h` (Internal)


#### class `UE::Mutable::Private::NodeImageSwizzle`  
`class NodeImageSwizzle : public NodeImage`  
_L17-50_
- inherits: `NodeImage`
- desc: Node that composes a new image by gathering pixel data from channels in other images.
- L21 _public member_ `EImageFormat NewFormat;`
- L22 _public member_ `TArray<Ptr<NodeImage>> Sources;`
- L23 _public member_ `TArray<int32> SourceChannels;`
- L28 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L29 _public function_ `static const FNodeType* GetStaticType()`
- L32 _public function_ `inline void SetFormat(EImageFormat InFormat)` — Own interface
- L44 _protected prototype_ `~NodeImageSwizzle() = default;` — Forbidden. Manage with the Ptr<> template.
- L48 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MUTABLETOOLS_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Mutable` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeImageTable.h` (Internal)


#### class `UE::Mutable::Private::NodeImageTable`  
`class NodeImageTable : public NodeImage`  
_L20-57_
- inherits: `NodeImage`
- desc: This node provides the meshes stored in the column of a table.
- L24 _public member_ `FString ParameterName;`
- L26 _public member_ `Ptr<FTable> Table;`
- L28 _public member_ `FString ColumnName;`
- L30 _public member_ `uint16 MaxTextureSize = 0;`
- L32 _public member_ `FImageDesc ReferenceImageDesc;`
- L34 _public member_ `bool bNoneOption = false;`
- L36 _public member_ `FString DefaultRowName;`
- L39 _public member_ `FSourceDataDescriptor SourceDataDescriptor;`
- L44 _public function_ `virtual const FNodeType* GetType() const override` — Node interface
- L45 _public function_ `static const FNodeType* GetStaticType()`
- L50 _protected prototype_ `~NodeImageTable() = default;` — Forbidden. Manage with the Ptr<> template.
- L54 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MUTABLETOOLS_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Mutable` (scope `UE`)
- L15 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeImageTransform.h` (Internal)


#### class `UE::Mutable::Private::NodeImageTransform`  
`class NodeImageTransform : public NodeImage`  
_L17-49_
- inherits: `NodeImage`
- L21 _public member_ `Ptr<NodeImage> Base;`
- L22 _public member_ `Ptr<NodeScalar> OffsetX;`
- L23 _public member_ `Ptr<NodeScalar> OffsetY;`
- L24 _public member_ `Ptr<NodeScalar> ScaleX;`
- L25 _public member_ `Ptr<NodeScalar> ScaleY;`
- L26 _public member_ `Ptr<NodeScalar> Rotation;`
- L28 _public member_ `EAddressMode AddressMode = EAddressMode::Wrap;`
- L29 _public member_ `uint32 SizeX = 0;`
- L30 _public member_ `uint32 SizeY = 0;`
- L32 _public member_ `bool bKeepAspectRatio = false;`
- L37 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L38 _public function_ `static const FNodeType* GetStaticType()`
- L43 _protected prototype_ `~NodeImageTransform() = default;` — Forbidden. Manage with the Ptr<> template.
- L47 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MUTABLETOOLS_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Mutable` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeImageVariation.h` (Internal)


#### class `UE::Mutable::Private::NodeImageVariation`  
`class NodeImageVariation : public NodeImage`  
_L16-45_
- inherits: `NodeImage`
- L20 _public member_ `Ptr<NodeImage> DefaultImage;`
- L28 _public member_ `TArray<FVariation> Variations;`
- L33 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L34 _public function_ `static const FNodeType* GetStaticType()`
- L39 _protected prototype_ `~NodeImageVariation() = default;` — Forbidden. Manage with the Ptr<> template.
- L43 _private member_ `static FNodeType StaticType;`

#### struct `UE::Mutable::Private::NodeImageVariation::FVariation`  
`struct FVariation`  
_L22-26_
- L24 _public member_ `Ptr<NodeImage> Image;`
- L25 _public member_ `FString Tag;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MUTABLETOOLS_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Mutable` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeLOD.h` (Internal)


#### class `UE::Mutable::Private::NodeLOD`  
`class NodeLOD : public Node`  
_L15-41_
- inherits: `Node`
- L23 _public function_ `virtual const FNodeType* GetType() const override`
- L24 _public function_ `static const FNodeType* GetStaticType()`
- L30 _public member_ `TArray<Ptr<NodeSurface>> Surfaces;`
- L35 _protected prototype_ `~NodeLOD() = default;` — Forbidden. Manage with the Ptr<> template.
- L39 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MUTABLETOOLS_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Mutable` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeLayout.h` (Internal)


#### struct `UE::Mutable::Private::FSourceLayoutBlock`  
`struct FSourceLayoutBlock`  
_L20-36_
- desc: Data for a layout block before it is compiled.
- L23 _public member_ `TManagedPtr<FImage> Mask;` — Optional mask image that selects the vertices to include in the block.
- L25 _public member_ `FIntVector2 Min = { 0, 0 };`
- L26 _public member_ `FIntVector2 Size = { 0, 0 };`
- L29 _public member_ `int32 Priority = 0;` — Priority value to control the shrink texture layout strategy
- L32 _public member_ `uint32 bReduceBothAxes : 1 = 0;` — Value to control the method to reduce the block
- L35 _public member_ `uint32 bReduceByTwo : 1 = 0;` — Value to control if a block has to be reduced by two in an unitary reduction strategy

#### class `UE::Mutable::Private::NodeLayout`  
`class NodeLayout : public Node`  
_L40-95_
- inherits: `Node`
- desc: This node is used to define the texture layout for a texture coordinates channel of a mesh.
- L45 _public member_ `FIntVector2 Size = FIntVector2(0, 0);`
- L50 _public member_ `FIntVector2 MaxSize = FIntVector2(0, 0);` — Maximum size in layout blocks that this layout can grow to. From there on, blocks will shrink to fit. If 0,0 then no maximum size applies.
- L53 _public member_ `EAutoBlocksStrategy AutoBlockStrategy = EAutoBlocksStrategy::Rectangles;`
- L54 _public member_ `TArray<FSourceLayoutBlock> Blocks;`
- L57 _public member_ `EPackStrategy Strategy = EPackStrategy::Resizeable;` — Packing strategy
- L58 _public member_ `EReductionMethod ReductionMethod = EReductionMethod::Halve;`
- L63 _public member_ `int32 FirstLODToIgnoreWarnings = 0;` — When compiling, ignore generated warnings from this LOD on. -1 means all warnings are generated.
- L65 _public member_ `int32 TexCoordsIndex = INDEX_NONE;`
- L67 _public member_ `bool bMergeChildBlocks = false;`
- L72 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L73 _public function_ `static const FNodeType* GetStaticType()`
- L78 _public prototype_ `TManagedPtr<FLayout> BuildRuntimeLayout(uint32 BlockIDPrefix) const;`
- L83 _public prototype_ `void GenerateLayoutBlocks(const TManagedPtr<FMesh>&, int32 LayoutIndex );` — Generate the blocks of a layout using the UV of the meshes. A list of existing blocks may be provided to specify starting blocks that shouldn't be modified unless it is mandatory because they contain partial face islands.
- L84 _public prototype_ `void GenerateLayoutBlocksFromUVIslands(const TManagedPtr<FMesh>&, int32 LayoutIndex);`
- L89 _protected prototype_ `~NodeLayout() = default;` — Forbidden. Manage with the Ptr<> template.
- L93 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MUTABLETOOLS_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Mutable` (scope `UE`)
- L15 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeMaterial.h` (Internal)


#### class `UE::Mutable::Private::NodeMaterial`  
`class NodeMaterial : public Node`  
_L16-33_
- inherits: `Node`
- desc: Base class of any node that outputs a Material.
- L21 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L22 _public function_ `static const FNodeType* GetStaticType()`
- L27 _protected prototype_ `inline ~NodeMaterial() = default;` — Forbidden. Manage with the Ptr<> template.
- L31 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MUTABLETOOLS_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Mutable` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeMaterialConstant.h` (Internal)


#### class `UE::Mutable::Private::NodeMaterialConstant`  
`class NodeMaterialConstant : public NodeMaterial`  
_L20-42_
- inherits: `NodeMaterial`
- desc: NodeMaterialConstant class.
- L25 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L26 _public function_ `static const FNodeType* GetStaticType()`
- L28 _public member_ `PASSTHROUGH_ID MaterialId = PASSTHROUGH_ID_INVALID;`
- L30 _public member_ `TMap<FParameterKey, FVector4f> ColorValues;`
- L31 _public member_ `TMap<FParameterKey, float> ScalarValues;`
- L32 _public member_ `TMap<FParameterKey, Ptr<NodeImage>> ImageValues;`
- L37 _protected prototype_ `inline ~NodeMaterialConstant() = default;` — Forbidden. Manage with the Ptr<> template.
- L41 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API MUTABLETOOLS_API`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Mutable` (scope `UE`)
- L17 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeMaterialExternal.h` (Internal)


#### class `UE::Mutable::Private::NodeMaterialExternal`  
`class NodeMaterialExternal : public NodeMaterial`  
_L14-30_
- inherits: `NodeMaterial`
- L18 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L19 _public function_ `static const FNodeType* GetStaticType()`
- L23 _protected prototype_ `virtual ~NodeMaterialExternal() override = default;` — Forbidden. Manage with the Ptr<> template.
- L26 _private member_ `static FNodeType StaticType;`
- L29 _public member_ `Ptr<NodeExternal> Node;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MUTABLETOOLS_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Mutable` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeMaterialParameter.h` (Internal)


#### class `UE::Mutable::Private::NodeMaterialParameter`  
`class NodeMaterialParameter : public NodeMaterial`  
_L21-51_
- inherits: `NodeMaterial`
- desc: NodeMaterialParameter class.
- L26 _public member_ `FString Name;` — Name of the parameter
- L29 _public member_ `FString UID;` — User provided ID to identify the parameter.
- L32 _public member_ `TArray<Ptr<NodeRange>> Ranges;` — Ranges for the parameter in case it is multidimensional.
- L34 _public member_ `TMap<FParameterKey, Ptr<NodeImage>> ImageParametersToCompile;`
- L39 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L40 _public function_ `static const FNodeType* GetStaticType()`
- L45 _protected prototype_ `inline ~NodeMaterialParameter() = default;` — Forbidden. Manage with the Ptr<> template.
- L49 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API MUTABLETOOLS_API`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Mutable` (scope `UE`)
- L17 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeMaterialSkeletalMeshBreak.h` (Internal)


#### class `UE::Mutable::Private::NodeMaterialSkeletalMeshBreak`  
`class NodeMaterialSkeletalMeshBreak : public NodeMaterial`  
_L15-34_
- inherits: `NodeMaterial`
- desc: Provided a mesh get the material whose material slot name does match the "SlotName" set.
- L19 _public member_ `FName SlotName;` — The name of the material slot to get from the given mesh.
- L22 _public member_ `Ptr<NodeSkeletalMesh> SkeletalMesh;` — The mesh to use as source for the material set in the slot with "SlotName" name.
- L25 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L26 _public function_ `static const FNodeType* GetStaticType()`
- L30 _protected function_ `virtual ~NodeMaterialSkeletalMeshBreak() override` — Forbidden. Manage with the Ptr<> template.
- L33 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MUTABLETOOLS_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Mutable` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeMaterialSkeletalMeshObjectBreak.h` (Internal)


#### class `UE::Mutable::Private::NodeMaterialSkeletalMeshObjectBreak`  
`class NodeMaterialSkeletalMeshObjectBreak : public NodeMaterial`  
_L15-34_
- inherits: `NodeMaterial`
- desc: Provided a mesh get the material whose material slot name does match the "SlotName" set.
- L19 _public member_ `FName SlotName;` — The name of the material slot to get from the given mesh.
- L22 _public member_ `Ptr<NodeSkeletalMeshObject> SkeletalMeshObject;` — The mesh to use as source for the material set in the slot with "SlotName" name.
- L25 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L26 _public function_ `static const FNodeType* GetStaticType()`
- L30 _protected function_ `virtual ~NodeMaterialSkeletalMeshObjectBreak() override` — Forbidden. Manage with the Ptr<> template.
- L33 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MUTABLETOOLS_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Mutable` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeMaterialSwitch.h` (Internal)


#### class `UE::Mutable::Private::NodeMaterialSwitch`  
`class NodeMaterialSwitch : public NodeMaterial`  
_L17-40_
- inherits: `NodeMaterial`
- desc: NodeMaterialSwitch class.
- L21 _public member_ `Ptr<NodeScalar> Parameter;`
- L23 _public member_ `TArray<Ptr<NodeMaterial>> Options;`
- L28 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L29 _public function_ `static const FNodeType* GetStaticType()`
- L34 _protected prototype_ `inline ~NodeMaterialSwitch() = default;` — Forbidden. Manage with the Ptr<> template.
- L38 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MUTABLETOOLS_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Mutable` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeMaterialTable.h` (Internal)


#### class `UE::Mutable::Private::NodeMaterialTable`  
`class NodeMaterialTable : public NodeMaterial`  
_L17-43_
- inherits: `NodeMaterial`
- desc: NodeMaterialTable class.
- L20 _public member_ `FString ParameterName;`
- L21 _public member_ `FString ColumnName;`
- L22 _public member_ `FString DefaultRowName;`
- L24 _public member_ `bool bNoneOption = false;`
- L26 _public member_ `Ptr<FTable> Table;`
- L31 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L32 _public function_ `static const FNodeType* GetStaticType()`
- L37 _protected prototype_ `inline ~NodeMaterialTable() = default;` — Forbidden. Manage with the Ptr<> template.
- L41 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MUTABLETOOLS_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Mutable` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeMaterialVariation.h` (Internal)


#### class `UE::Mutable::Private::NodeMaterialVariation`  
`class NodeMaterialVariation : public NodeMaterial`  
_L16-43_
- inherits: `NodeMaterial`
- desc: NodeMaterialVariation class.
- L19 _public member_ `Ptr<NodeMaterial> DefaultMaterial;`
- L27 _public member_ `TArray<FVariation> Variations;`
- L31 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L32 _public function_ `static const FNodeType* GetStaticType()`
- L37 _protected prototype_ `inline ~NodeMaterialVariation() = default;` — Forbidden. Manage with the Ptr<> template.
- L41 _private member_ `static FNodeType StaticType;`

#### struct `UE::Mutable::Private::NodeMaterialVariation::FVariation`  
`struct FVariation`  
_L21-25_
- L23 _public member_ `Ptr<NodeMaterial> Material;`
- L24 _public member_ `FString Tag;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MUTABLETOOLS_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Mutable` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeMatrix.h` (Internal)


#### class `UE::Mutable::Private::NodeMatrix`  
`class NodeMatrix : public Node`  
_L13-30_
- inherits: `Node`
- desc: Base class of any node that outputs a color.
- L18 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L19 _public function_ `static const FNodeType* GetStaticType()`
- L24 _protected prototype_ `virtual ~NodeMatrix() override = default;` — Forbidden. Manage with the Ptr<> template.
- L28 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API MUTABLETOOLS_API`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Mutable` (scope `UE`)
- L9 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeMatrixConstant.h` (Internal)


#### class `UE::Mutable::Private::NodeMatrixConstant`  
`class NodeMatrixConstant : public NodeMatrix`  
_L13-30_
- inherits: `NodeMatrix`
- L16 _public member_ `FMatrix44f Value;`
- L19 _public function_ `const FNodeType* GetType() const override` — Node interface
- L20 _public function_ `static const FNodeType* GetStaticType()`
- L25 _protected prototype_ `virtual ~NodeMatrixConstant() override = default;` — Forbidden. Manage with the Ptr<> template.
- L29 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MUTABLETOOLS_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Mutable` (scope `UE`)
- L10 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeMatrixParameter.h` (Internal)


#### class `UE::Mutable::Private::NodeMatrixParameter`  
`class NodeMatrixParameter : public NodeMatrix`  
_L16-36_
- inherits: `NodeMatrix`
- L19 _public member_ `FMatrix44f DefaultValue;`
- L20 _public member_ `FString Name;`
- L21 _public member_ `FString Uid;`
- L23 _public member_ `TArray<Ptr<NodeRange>> Ranges;`
- L26 _public function_ `const FNodeType* GetType() const override` — Node interface
- L27 _public function_ `static const FNodeType* GetStaticType()`
- L31 _protected prototype_ `virtual ~NodeMatrixParameter() override = default;` — Forbidden. Manage with the Ptr<> template.
- L35 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MUTABLETOOLS_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Mutable` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeMesh.h` (Internal)


#### class `UE::Mutable::Private::NodeMesh`  
`class NodeMesh : public Node`  
_L25-42_
- inherits: `Node`
- desc: Base class of any node that outputs a mesh.
- L30 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L31 _public function_ `static const FNodeType* GetStaticType()`
- L36 _protected prototype_ `inline ~NodeMesh() = default;` — Forbidden. Manage with the Ptr<> template.
- L40 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MUTABLETOOLS_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Mutable` (scope `UE`)
- L14 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L20 _typedef_ `typedef Ptr<NodeMesh> NodeMeshPtr;` (scope `UE::Mutable::Private`)
- L21 _typedef_ `typedef Ptr<const NodeMesh> NodeMeshPtrConst;` (scope `UE::Mutable::Private`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeMeshApplyPose.h` (Internal)


#### class `UE::Mutable::Private::NodeMeshApplyPose`  
`class NodeMeshApplyPose : public NodeMesh`  
_L16-38_
- inherits: `NodeMesh`
- desc: Node that applies a pose to a mesh, baking it into the vertex data.
- L20 _public member_ `Ptr<NodeMesh> Base;`
- L21 _public member_ `Ptr<NodeMesh> Pose;`
- L26 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L27 _public function_ `static const FNodeType* GetStaticType()`
- L32 _protected prototype_ `~NodeMeshApplyPose() = default;` — Forbidden.Manage with the Ptr<> template.
- L36 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MUTABLETOOLS_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Mutable` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeMeshClipDeform.h` (Internal)


#### class `UE::Mutable::Private::NodeMeshClipDeform`  
`class NodeMeshClipDeform : public NodeMesh`  
_L17-40_
- inherits: `NodeMesh`
- L21 _public member_ `Ptr<NodeMesh> BaseMesh;`
- L22 _public member_ `Ptr<NodeMesh> ClipShape;`
- L23 _public member_ `Ptr<NodeImage> ShapeWeights;`
- L28 _public function_ `virtual const FNodeType* GetType() const override` — Node interface
- L29 _public function_ `static const FNodeType* GetStaticType()`
- L34 _protected prototype_ `inline ~NodeMeshClipDeform() = default;` — Forbidden. Manage with the Ptr<> template.
- L38 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MUTABLETOOLS_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Mutable` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeMeshClipMorphPlane.h` (Internal)


#### class `UE::Mutable::Private::NodeMeshClipMorphPlane`  
`class NodeMeshClipMorphPlane : public NodeMesh`  
_L18-63_
- inherits: `NodeMesh`
- desc: This node applies a geometric transform represented by a 4x4 matrix to a mesh
- L22 _public member_ `Ptr<NodeMesh> Source;`
- L24 _public member_ `FClipMorphPlaneParameters Parameters;`
- L29 _public function_ `virtual const FNodeType* GetType() const override` — Node interface
- L30 _public function_ `static const FNodeType* GetStaticType()`
- L37 _public prototype_ `NodeMeshPtr GetSource() const;` — Source mesh to be clipped and morphed
- L38 _public prototype_ `void SetSource( NodeMesh* );`
- L40 _public prototype_ `void SetPlane(FVector3f Center, FVector3f Normal);`
- L41 _public prototype_ `void SetParams(float dist, float factor);`
- L42 _public prototype_ `void SetMorphEllipse(float radius1, float radius2, float rotation);`
- L47 _public prototype_ `void SetVertexSelectionBox(FVector3f Center, FVector3f Radius);` — Define an axis-aligned box that will select the vertices to be morphed. If this is not set, or the size of the box is 0, all vertices will be affected. Only one of Box or Bone Hierarchy can be used (the last one set)
- L51 _public prototype_ `void SetVertexSelectionBone(FName BoneId, float maxEffectRadius);` — Define the root bone of the subhierarchy of the mesh that will be affected. Only one of Box or Bone Hierarchy can be used (the last one set)
- L57 _protected prototype_ `~NodeMeshClipMorphPlane() = default;` — Forbidden. Manage with the Ptr<> template.
- L61 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MUTABLETOOLS_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Mutable` (scope `UE`)
- L14 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeMeshClipWithMesh.h` (Internal)


#### class `UE::Mutable::Private::NodeMeshClipWithMesh`  
`class NodeMeshClipWithMesh : public NodeMesh`  
_L18-41_
- inherits: `NodeMesh`
- desc: This node applies a geometric transform represented by a 4x4 matrix to a mesh \ingroup model
- L22 _public member_ `Ptr<NodeMesh> Source;`
- L24 _public member_ `Ptr<NodeMesh> ClipMesh;`
- L26 _public member_ `EFaceCullStrategy FaceCullStrategy = EFaceCullStrategy::AllVerticesCulled;`
- L29 _public function_ `virtual const FNodeType* GetType() const override` — Node interface
- L30 _public function_ `static const FNodeType* GetStaticType()`
- L35 _protected prototype_ `inline ~NodeMeshClipWithMesh() = default;` — Forbidden. Manage with the Ptr<> template.
- L39 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MUTABLETOOLS_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Mutable` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeMeshConstant.h` (Internal)


#### class `UE::Mutable::Private::NodeMeshConstant`  
`class NodeMeshConstant : public NodeMesh`  
_L20-50_
- inherits: `NodeMesh`
- desc: Node that outputs a constant mesh. It allows to define the layouts for the texture channels of the constant mesh
- L24 _public member_ `FSourceDataDescriptor SourceDataDescriptor;`
- L26 _public member_ `UE::Mutable::Private::TManagedPtr<FMesh> Value;`
- L28 _public member_ `TArray<Ptr<NodeLayout>> Layouts;`
- L30 _public member_ `TArray<FName> RealTimeMorphNames;`
- L32 _public member_ `int8 BonePosePriority = 0;`
- L33 _public member_ `int8 SocketPriority = 0;`
- L38 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L39 _public function_ `static const FNodeType* GetStaticType()`
- L44 _protected prototype_ `~NodeMeshConstant() = default;` — Forbidden. Manage with the Ptr<> template.
- L48 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MUTABLETOOLS_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Mutable` (scope `UE`)
- L14 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeMeshExternal.h` (Internal)


#### class `UE::Mutable::Private::NodeMeshExternal`  
`class NodeMeshExternal : public NodeMesh`  
_L14-30_
- inherits: `NodeMesh`
- L18 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L19 _public function_ `static const FNodeType* GetStaticType()`
- L23 _protected prototype_ `virtual ~NodeMeshExternal() override = default;` — Forbidden. Manage with the Ptr<> template.
- L26 _private member_ `static FNodeType StaticType;`
- L29 _public member_ `Ptr<NodeExternal> Node;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MUTABLETOOLS_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Mutable` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeMeshFormat.h` (Internal)


#### class `UE::Mutable::Private::NodeMeshFormat`  
`class NodeMeshFormat : public NodeMesh`  
_L20-49_
- inherits: `NodeMesh`
- desc: This node can change the buffer formats of a mesh vertices, indices and faces.
- L25 _public member_ `Ptr<NodeMesh> Source;` — Source mesh to transform.
- L28 _public member_ `FMeshBufferSet VertexBuffers;` — New mesh format.The buffers in the sets have no elements, but they define the formats.
- L29 _public member_ `FMeshBufferSet IndexBuffers;`
- L32 _public member_ `bool bOptimizeBuffers = false;`
- L37 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L38 _public function_ `static const FNodeType* GetStaticType()`
- L43 _protected prototype_ `~NodeMeshFormat() = default;` — Forbidden. Manage with the Ptr<> template.
- L47 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MUTABLETOOLS_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Mutable` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeMeshFragment.h` (Internal)


#### class `UE::Mutable::Private::NodeMeshFragment`  
`class NodeMeshFragment : public NodeMesh`  
_L15-45_
- inherits: `NodeMesh`
- desc: This node extracts a fragment of a mesh by some selection on a texture layout space.
- L20 _public member_ `Ptr<NodeMesh> SourceMesh;` — Mesh from which a fragment will be extracted.
- L25 _public member_ `Ptr<NodeLayout> Layout;` — Layout defining the blocks of mesh to extract by texture space. If no layout is specified, all the blocks in the layout in the SourceMesh subgraph will be extracted.
- L28 _public member_ `int32 LayoutIndex = 0;` — Index of the UV channel in the source mesh to apply the Layout to decide what to extract.
- L33 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L34 _public function_ `static const FNodeType* GetStaticType()`
- L39 _protected prototype_ `~NodeMeshFragment() = default;` — Forbidden. Manage with the Ptr<> template.
- L43 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MUTABLETOOLS_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Mutable` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeMeshMakeMorph.h` (Internal)


#### class `UE::Mutable::Private::NodeMeshMakeMorph`  
`class NodeMeshMakeMorph : public NodeMesh`  
_L17-41_
- inherits: `NodeMesh`
- desc: This node removes from a mesh A all the faces that are also part of a mesh B.
- L21 _public member_ `Ptr<NodeMesh> Base;`
- L22 _public member_ `Ptr<NodeMesh> Target;`
- L24 _public member_ `bool bOnlyPositionAndNormal = false;`
- L29 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L30 _public function_ `static const FNodeType* GetStaticType()`
- L35 _protected prototype_ `~NodeMeshMakeMorph() = default;` — Forbidden. Manage with the Ptr<> template.
- L39 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MUTABLETOOLS_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Mutable` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeMeshMorph.h` (Internal)


#### class `UE::Mutable::Private::NodeMeshMorph`  
`class NodeMeshMorph : public NodeMesh`  
_L17-40_
- inherits: `NodeMesh`
- desc: Node that morphs a base mesh with one weighted target.
- L21 _public member_ `FName Name;`
- L22 _public member_ `Ptr<NodeScalar> Factor;`
- L23 _public member_ `Ptr<NodeMesh> Base;`
- L28 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L29 _public function_ `static const FNodeType* GetStaticType()`
- L34 _protected prototype_ `~NodeMeshMorph() = default;` — Forbidden. Manage with the Ptr<> template.
- L38 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MUTABLETOOLS_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Mutable` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeMeshRemoveMesh.h` (Internal)


#### class `UE::Mutable::Private::NodeMeshRemoveMesh`  
`class NodeMeshRemoveMesh : public NodeMesh`  
_L16-39_
- inherits: `NodeMesh`
- L20 _public member_ `Ptr<NodeMesh> Source;`
- L22 _public member_ `Ptr<NodeMesh> RemoveMesh;`
- L24 _public member_ `EFaceCullStrategy FaceCullStrategy = EFaceCullStrategy::AllVerticesCulled;`
- L27 _public function_ `virtual const FNodeType* GetType() const override` — Node interface
- L28 _public function_ `static const FNodeType* GetStaticType()`
- L33 _protected prototype_ `inline ~NodeMeshRemoveMesh() = default;` — Forbidden. Manage with the Ptr<> template.
- L37 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MUTABLETOOLS_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Mutable` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeMeshReshape.h` (Internal)


#### class `UE::Mutable::Private::NodeMeshReshape`  
`class NodeMeshReshape : public NodeMesh`  
_L17-55_
- inherits: `NodeMesh`
- desc: Node that morphs a base mesh with one or two weighted targets from a sequence.
- L21 _public member_ `Ptr<NodeMesh> BaseMesh;`
- L22 _public member_ `Ptr<NodeMesh> BaseShape;`
- L23 _public member_ `Ptr<NodeMesh> TargetShape;`
- L24 _public member_ `bool bReshapeVertices = true;`
- L25 _public member_ `bool bRecomputeNormals = false;`
- L26 _public member_ `bool bApplyLaplacian = false;`
- L27 _public member_ `bool bReshapeSkeleton = false;`
- L28 _public member_ `bool bReshapePhysicsVolumes = false;`
- L29 _public member_ `bool bReshapeSkeletonInvertSelection = false;`
- L30 _public member_ `bool bReshapePhysicsVolumesInvertSelection = false;`
- L32 _public member_ `EVertexColorUsage ColorRChannelUsage = EVertexColorUsage::None;`
- L33 _public member_ `EVertexColorUsage ColorGChannelUsage = EVertexColorUsage::None;`
- L34 _public member_ `EVertexColorUsage ColorBChannelUsage = EVertexColorUsage::None;`
- L35 _public member_ `EVertexColorUsage ColorAChannelUsage = EVertexColorUsage::None;`
- L37 _public member_ `TArray<FName> BonesToDeform;`
- L38 _public member_ `TArray<FName> PhysicsToDeform;`
- L43 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L44 _public function_ `static const FNodeType* GetStaticType()`
- L49 _protected prototype_ `~NodeMeshReshape() = default;` — Forbidden. Manage with the Ptr<> template.
- L53 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MUTABLETOOLS_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Mutable` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeMeshSkeletalMeshObjectBreak.h` (Internal)


#### class `UE::Mutable::Private::NodeMeshSkeletalMeshObjectBreak`  
`class NodeMeshSkeletalMeshObjectBreak : public NodeMesh`  
_L17-49_
- inherits: `NodeMesh`
- L20 _public member_ `TManagedPtr<FMesh> ReferenceMesh;`
- L22 _public member_ `TArray<Ptr<NodeLayout>> Layouts;`
- L24 _public member_ `TArray<FName> RealTimeMorphNames;`
- L26 _public member_ `uint8 BaseLODIndex = 0;`
- L28 _public member_ `uint8 BaseSectionIndex = 0;`
- L30 _public member_ `uint8 LODBias = 0;`
- L32 _public member_ `uint8 ConversionFlags = 0;`
- L34 _public member_ `int8 BonePosePriority = 0;`
- L35 _public member_ `int8 SocketPriority = 0;`
- L37 _public member_ `Ptr<NodeSkeletalMeshObject> SkeletalMeshObject;`
- L40 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L41 _public function_ `static const FNodeType* GetStaticType()`
- L45 _protected function_ `virtual ~NodeMeshSkeletalMeshObjectBreak() override` — Forbidden. Manage with the Ptr<> template.
- L48 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API MUTABLETOOLS_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Mutable` (scope `UE`)
- L15 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeMeshSwitch.h` (Internal)


#### class `UE::Mutable::Private::NodeMeshSwitch`  
`class NodeMeshSwitch : public NodeMesh`  
_L15-38_
- inherits: `NodeMesh`
- desc: This node selects an output Mesh from a set of input Meshs based on a parameter.
- L19 _public member_ `Ptr<NodeScalar> Parameter;`
- L21 _public member_ `TArray<Ptr<NodeMesh>> Options;`
- L26 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L27 _public function_ `static const FNodeType* GetStaticType()`
- L32 _protected prototype_ `~NodeMeshSwitch() = default;` — Forbidden. Manage with the Ptr<> template.
- L36 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MUTABLETOOLS_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Mutable` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeMeshTable.h` (Internal)


#### class `UE::Mutable::Private::NodeMeshTable`  
`class NodeMeshTable : public NodeMesh`  
_L19-50_
- inherits: `NodeMesh`
- desc: This node provides the meshes stored in the column of a table.
- L23 _public member_ `FString ParameterName;`
- L24 _public member_ `Ptr<FTable> Table;`
- L25 _public member_ `FString ColumnName;`
- L26 _public member_ `bool bNoneOption = false;`
- L27 _public member_ `FString DefaultRowName;`
- L29 _public member_ `TArray<Ptr<NodeLayout>> Layouts;`
- L30 _public member_ `TArray<FName> RealTimeMorphNames;`
- L33 _public member_ `FSourceDataDescriptor SourceDataDescriptor;`
- L38 _public function_ `virtual const FNodeType* GetType() const override` — Node interface
- L39 _public function_ `static const FNodeType* GetStaticType()`
- L44 _protected prototype_ `~NodeMeshTable() = default;` — Forbidden. Manage with the Ptr<> template.
- L48 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API MUTABLETOOLS_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Mutable` (scope `UE`)
- L15 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeMeshTransform.h` (Internal)


#### class `UE::Mutable::Private::NodeMeshTransform`  
`class NodeMeshTransform : public NodeMesh`  
_L17-39_
- inherits: `NodeMesh`
- desc: This node applies a geometric transform represented by a 4x4 matrix to a mesh.
- L21 _public member_ `Ptr<NodeMesh> Source;`
- L22 _public member_ `FMatrix44f Transform;`
- L27 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L28 _public function_ `static const FNodeType* GetStaticType()`
- L33 _protected prototype_ `~NodeMeshTransform() = default;` — Forbidden. Manage with the Ptr<> template.
- L37 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MUTABLETOOLS_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Mutable` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeMeshTransformInMesh.h` (Internal)


#### class `UE::Mutable::Private::NodeMeshTransformInMesh`  
`class NodeMeshTransformInMesh : public NodeMesh`  
_L18-46_
- inherits: `NodeMesh`
- L23 _public member_ `Ptr<NodeMesh> SourceMesh;`
- L26 _public member_ `Ptr<NodeMesh> BoundingMesh;`
- L29 _public member_ `Ptr<NodeMatrix> MatrixNode;`
- L34 _public function_ `virtual const FNodeType* GetType() const override` — Node interface
- L35 _public function_ `static const FNodeType* GetStaticType()`
- L40 _protected prototype_ `virtual ~NodeMeshTransformInMesh() override = default;` — Forbidden. Manage with the Ptr<> template.
- L44 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MUTABLETOOLS_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Mutable` (scope `UE`)
- L14 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeMeshTransformWithBone.h` (Internal)


#### class `UE::Mutable::Private::NodeMeshTransformWithBone`  
`class NodeMeshTransformWithBone : public NodeMesh`  
_L15-40_
- inherits: `NodeMesh`
- L19 _public member_ `Ptr<NodeMesh> Source;`
- L21 _public member_ `FName BoneName = NAME_None;`
- L23 _public member_ `float ThresholdFactor = 0.0f;`
- L25 _public member_ `Ptr<NodeMatrix> MatrixNode;`
- L28 _public function_ `virtual const FNodeType* GetType() const override` — Node interface
- L29 _public function_ `static const FNodeType* GetStaticType()`
- L34 _protected prototype_ `virtual ~NodeMeshTransformWithBone() override = default;` — Forbidden. Manage with the Ptr<> template.
- L38 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MUTABLETOOLS_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Mutable` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeMeshVariation.h` (Internal)


#### class `UE::Mutable::Private::NodeMeshVariation`  
`class NodeMeshVariation : public NodeMesh`  
_L16-45_
- inherits: `NodeMesh`
- L20 _public member_ `Ptr<NodeMesh> DefaultMesh;`
- L28 _public member_ `TArray<FVariation> Variations;`
- L33 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L34 _public function_ `static const FNodeType* GetStaticType()`
- L39 _protected prototype_ `~NodeMeshVariation() = default;` — Forbidden. Manage with the Ptr<> template.
- L43 _private member_ `static FNodeType StaticType;`

#### struct `UE::Mutable::Private::NodeMeshVariation::FVariation`  
`struct FVariation`  
_L22-26_
- L24 _public member_ `Ptr<NodeMesh> Mesh;`
- L25 _public member_ `FString Tag;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MUTABLETOOLS_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Mutable` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeModifier.h` (Internal)


#### class `UE::Mutable::Private::NodeModifier`  
`class NodeModifier : public Node`  
_L13-26_
- inherits: `Node`
- desc: Global graph transformation. No tags.
- L17 _public function_ `virtual const FNodeType* GetType() const override` — Node interface
- L18 _public function_ `static const FNodeType* GetStaticType()`
- L22 _protected prototype_ `virtual ~NodeModifier() override = default;` — Forbidden. Manage with the Ptr<> template.
- L25 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API MUTABLETOOLS_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Mutable` (scope `UE`)
- L10 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeModifierSkeletalMeshMerge.h` (Internal)


#### class `UE::Mutable::Private::NodeModifierSkeletalMeshMerge`  
`class NodeModifierSkeletalMeshMerge : public NodeModifier`  
_L16-33_
- inherits: `NodeModifier`
- L19 _public member_ `FName ParentSkeletalMeshName;`
- L21 _public member_ `Ptr<NodeSkeletalMesh> ToAddSkeletalMesh;`
- L24 _public function_ `virtual const FNodeType* GetType() const override` — Node interface
- L25 _public function_ `static const FNodeType* GetStaticType()`
- L29 _protected prototype_ `virtual ~NodeModifierSkeletalMeshMerge() override = default;` — Forbidden. Manage with the Ptr<> template.
- L32 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MUTABLETOOLS_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Mutable` (scope `UE`)
- L14 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeObject.h` (Internal)


#### class `UE::Mutable::Private::NodeObject`  
`class NodeObject : public Node`  
_L16-47_
- inherits: `Node`
- desc: Base class for any node that outputs an object.
- L21 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L22 _public function_ `static const FNodeType* GetStaticType()`
- L27 _public prototype_ `virtual const FString& GetName() const = 0;` — Get the name of the object.
- L30 _public prototype_ `virtual void SetName( const FString& ) = 0;` — Set the name of the object.
- L33 _public prototype_ `virtual const FString& GetUid() const = 0;` — Get the uid of the object.
- L36 _public prototype_ `virtual void SetUid( const FString& ) = 0;` — Set the uid of the object.
- L41 _protected prototype_ `inline ~NodeObject() = default;` — Forbidden. Manage with the Ptr<> template.
- L45 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MUTABLETOOLS_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Mutable` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeObjectGroup.h` (Internal)


#### class `UE::Mutable::Private::NodeObjectGroup`  
`class NodeObjectGroup : public NodeObject`  
_L16-74_
- inherits: `NodeObject`
- desc: Node that creates a group of objects and describes how they are selected.
- L20 _public member_ `FString Name;`
- L21 _public member_ `FString Uid;`
- L41 _public typedef_ `} EChildSelection;`
- L43 _public member_ `EChildSelection Type;`
- L45 _public member_ `TArray<Ptr<NodeObject>> Children;`
- L51 _public member_ `int32 DefaultValue;` — Default value for CS_ONE_OR_NONE or CS_ALWAYS_ONE groups the value is the index of the child option in the group -1 is the value for the None option. 0 is the first child whether or not the NONE option is present.
- L56 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L57 _public function_ `static const FNodeType* GetStaticType()`
- L60 _public prototype_ `virtual const FString& GetName() const override;` — NodeObject Interface
- L61 _public prototype_ `virtual void SetName( const FString&) override;`
- L62 _public prototype_ `virtual const FString& GetUid() const override;`
- L63 _public prototype_ `virtual void SetUid( const FString&) override;`
- L68 _protected prototype_ `~NodeObjectGroup() = default;` — Forbidden. Manage with the Ptr<> template.
- L72 _private member_ `static FNodeType StaticType;`

#### enum `UE::Mutable::Private::NodeObjectGroup::(anonymous)`  
``  
_L25-41_

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MUTABLETOOLS_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Mutable` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L27 _enumerator_ `CS_ALWAYS_ALL` (scope `UE::Mutable::Private::NodeObjectGroup::__anon1075135b0103`) — All objects in the group will always be enabled, and no parameter will be generated.
- L31 _enumerator_ `CS_ONE_OR_NONE` (scope `UE::Mutable::Private::NodeObjectGroup::__anon1075135b0103`) — Only one children may be selected, but it is allowed to have none. An enumeration parameter will be generated but it may have a null value
- L35 _enumerator_ `CS_ALWAYS_ONE` (scope `UE::Mutable::Private::NodeObjectGroup::__anon1075135b0103`) — One and only one children has to be selected at all times An enumeraation parameter will be generated and it cannot be null
- L39 _enumerator_ `CS_TOGGLE_EACH` (scope `UE::Mutable::Private::NodeObjectGroup::__anon1075135b0103`) — Each child in the group can be enabled or disabled individually. A boolean parameter will be generated for every child.

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeObjectNew.h` (Internal)


#### class `UE::Mutable::Private::NodeObjectNew`  
`class NodeObjectNew : public NodeObject`  
_L22-93_
- inherits: `NodeObject`
- desc: Node that creates a new object by setting its levels-of-detail and its children.
- L27 _public member_ `FString Name;` — Name of the object.
- L30 _public member_ `FString Uid;` — Externally provided id for the object.
- L33 _public member_ `TArray<Ptr<NodeComponent>> Components;` — Components defined in the object.
- L36 _public member_ `TArray<Ptr<NodeModifier>> Modifiers;` — Modifiers defined in the object.
- L39 _public member_ `TArray<Ptr<NodeObject>> Children;` — Children objects.
- L42 _public member_ `TArray<Ptr<NodeExtensionData>> ExtensionDataNodes;` — Extension data attached to this object.
- L45 _public member_ `TArray<FObjectState> States;` — States defined in this object.
- L51 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L52 _public function_ `static const FNodeType* GetStaticType()`
- L55 _public prototype_ `virtual const FString& GetName() const override;` — NodeObject Interface
- L56 _public prototype_ `virtual void SetName( const FString& ) override;`
- L57 _public prototype_ `virtual const FString& GetUid() const override;`
- L58 _public prototype_ `virtual void SetUid( const FString& ) override;`
- L63 _public prototype_ `int32 GetStateCount() const;` — Set the number of states that the model can be in.
- L64 _public prototype_ `void SetStateCount( int32 c );`
- L67 _public prototype_ `void SetStateName( int32 s, const FString& n );` — Set the name of a state
- L70 _public prototype_ `bool HasStateParam( int32 s, const FString& param ) const;` — See if a state has a parameter as runtime.
- L73 _public prototype_ `void AddStateParam( int32 s, const FString& param );` — Add a runtime parameter to the state.
- L76 _public prototype_ `void SetStateProperties(int32 StateIndex, ETextureCompressionStrategy TextureCompressionStrategy, bool bOnlyFirstLOD, uint8 NumExtraLODsToBuildAfterFirstLOD);` — Set the optimisation properties of a state
- L82 _public prototype_ `void AddExtensionDataNode(Ptr<NodeExtensionData> Node);` — Connect a node that produces ExtensionData to be added to the final Instance, and provide a name to associate with the data
- L87 _protected prototype_ `~NodeObjectNew() = default;` — Forbidden. Manage with the Ptr<> template.
- L91 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API MUTABLETOOLS_API`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Mutable` (scope `UE`)
- L17 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeProjector.h` (Internal)


#### class `UE::Mutable::Private::NodeProjector`  
`class NodeProjector : public Node`  
_L19-36_
- inherits: `Node`
- desc: Base class of any node that outputs a Projector.
- L24 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L25 _public function_ `static const FNodeType* GetStaticType()`
- L30 _protected prototype_ `inline ~NodeProjector() = default;` — Forbidden. Manage with the Ptr<> template.
- L34 _private member_ `static FNodeType StaticType;`

#### class `UE::Mutable::Private::NodeProjectorConstant`  
`class NodeProjectorConstant : public NodeProjector`  
_L40-79_
- inherits: `NodeProjector`
- desc: This node outputs a predefined Projector value.
- L44 _public member_ `EProjectorType Type = EProjectorType::Planar;`
- L45 _public member_ `FVector3f Position = FVector3f::ZeroVector;`
- L46 _public member_ `FVector3f Direction = FVector3f::ZeroVector;`
- L47 _public member_ `FVector3f Up = FVector3f::ZeroVector;`
- L48 _public member_ `FVector3f Scale = FVector3f::ZeroVector;`
- L49 _public member_ `float ProjectionAngle = 0.0f;`
- L54 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L55 _public function_ `static const FNodeType* GetStaticType()`
- L60 _public prototype_ `void GetValue( EProjectorType* OutType, FVector3f* OutPos, FVector3f* OutDir, FVector3f* OutUp, FVector3f* OutScaleU, float* OutProjectionAngle ) const;` — Get the value that this node returns
- L68 _public prototype_ `void SetValue( EProjectorType type, FVector3f pos, FVector3f dir, FVector3f up, FVector3f scale, float projectionAngle);` — Set the value to be returned by this node
- L73 _protected prototype_ `~NodeProjectorConstant() = default;` — Forbidden. Manage with the Ptr<> template.
- L77 _private member_ `static FNodeType StaticType;`

#### class `UE::Mutable::Private::NodeProjectorParameter`  
`class NodeProjectorParameter : public NodeProjector`  
_L83-136_
- inherits: `NodeProjector`
- desc: Node that defines a Projector model parameter.
- L87 _public member_ `EProjectorType Type = EProjectorType::Planar;`
- L88 _public member_ `FVector3f Position = FVector3f::ZeroVector;`
- L89 _public member_ `FVector3f Direction = FVector3f::ZeroVector;`
- L90 _public member_ `FVector3f Up = FVector3f::ZeroVector;`
- L91 _public member_ `FVector3f Scale = FVector3f::ZeroVector;`
- L92 _public member_ `float ProjectionAngle = 0.0f;`
- L94 _public member_ `FString Name;`
- L95 _public member_ `FString UID;`
- L97 _public member_ `TArray<Ptr<NodeRange>> Ranges;`
- L102 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L103 _public function_ `static const FNodeType* GetStaticType()`
- L108 _public prototype_ `void SetName( const FString& );` — Set the name of the parameter.
- L111 _public prototype_ `const FString& GetUid() const;` — Get the uid of the parameter. It will be exposed in the final compiled data.
- L112 _public prototype_ `void SetUid( const FString& );`
- L115 _public prototype_ `void SetDefaultValue( EProjectorType type, FVector3f pos, FVector3f dir, FVector3f up, FVector3f scale, float projectionAngle );` — Set the default value of the parameter.
- L124 _public prototype_ `void SetRangeCount( int32 i );` — Set the number of ranges (dimensions) for this parameter. By default a parameter has 0 ranges, meaning it only has one value.
- L125 _public prototype_ `void SetRange( int32 i, Ptr<NodeRange> Range );`
- L130 _protected prototype_ `~NodeProjectorParameter() = default;` — Forbidden. Manage with the Ptr<> template.
- L134 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MUTABLETOOLS_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Mutable` (scope `UE`)
- L15 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeRange.h` (Internal)


#### class `UE::Mutable::Private::NodeRange`  
`class NodeRange : public Node`  
_L16-33_
- inherits: `Node`
- desc: Base class of any node that outputs a range.
- L21 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L22 _public function_ `static const FNodeType* GetStaticType()`
- L27 _protected prototype_ `inline ~NodeRange() = default;` — Forbidden. Manage with the Ptr<> template.
- L31 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MUTABLETOOLS_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Mutable` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeRangeFromScalar.h` (Internal)


#### class `UE::Mutable::Private::NodeRangeFromScalar`  
`class NodeRangeFromScalar : public NodeRange`  
_L18-41_
- inherits: `NodeRange`
- L22 _public member_ `Ptr<NodeScalar> Size;`
- L24 _public member_ `FString Name;`
- L29 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L30 _public function_ `static const FNodeType* GetStaticType()`
- L35 _protected prototype_ `~NodeRangeFromScalar() = default;` — Forbidden. Manage with the Ptr<> template.
- L39 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MUTABLETOOLS_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Mutable` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeScalar.h` (Internal)


#### class `UE::Mutable::Private::NodeScalar`  
`class NodeScalar : public Node`  
_L13-30_
- inherits: `Node`
- desc: Base class of any node that outputs a scalar value.
- L18 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L19 _public function_ `static const FNodeType* GetStaticType()`
- L24 _protected prototype_ `inline ~NodeScalar() = default;` — Forbidden. Manage with the Ptr<> template.
- L28 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API MUTABLETOOLS_API`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Mutable` (scope `UE`)
- L9 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeScalarArithmeticOperation.h` (Internal)


#### class `UE::Mutable::Private::NodeScalarArithmeticOperation`  
`class NodeScalarArithmeticOperation : public NodeScalar`  
_L16-49_
- inherits: `NodeScalar`
- desc: Perform an arithmetic operation between two scalars.
- L28 _public typedef_ `} EOperation;`
- L30 _public member_ `EOperation Operation;`
- L31 _public member_ `Ptr<NodeScalar> A;`
- L32 _public member_ `Ptr<NodeScalar> B;`
- L37 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L38 _public function_ `static const FNodeType* GetStaticType()`
- L43 _protected prototype_ `~NodeScalarArithmeticOperation() = default;` — Forbidden. Manage with the Ptr<> template.
- L47 _private member_ `static FNodeType StaticType;`

#### enum `UE::Mutable::Private::NodeScalarArithmeticOperation::(anonymous)`  
``  
_L22-28_

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MUTABLETOOLS_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Mutable` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L23 _enumerator_ `AO_ADD = 0` (scope `UE::Mutable::Private::NodeScalarArithmeticOperation::__anon675e9d480103`)
- L24 _enumerator_ `AO_SUBTRACT` (scope `UE::Mutable::Private::NodeScalarArithmeticOperation::__anon675e9d480103`)
- L25 _enumerator_ `AO_MULTIPLY` (scope `UE::Mutable::Private::NodeScalarArithmeticOperation::__anon675e9d480103`)
- L26 _enumerator_ `AO_DIVIDE` (scope `UE::Mutable::Private::NodeScalarArithmeticOperation::__anon675e9d480103`)
- L27 _enumerator_ `_AO_COUNT` (scope `UE::Mutable::Private::NodeScalarArithmeticOperation::__anon675e9d480103`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeScalarConstant.h` (Internal)


#### class `UE::Mutable::Private::NodeScalarConstant`  
`class NodeScalarConstant : public NodeScalar`  
_L16-37_
- inherits: `NodeScalar`
- desc: Node returning a scalar constant value.
- L20 _public member_ `float Value;`
- L25 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L26 _public function_ `static const FNodeType* GetStaticType()`
- L31 _protected prototype_ `~NodeScalarConstant() = default;` — Forbidden. Manage with the Ptr<> template.
- L35 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MUTABLETOOLS_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Mutable` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeScalarCurve.h` (Internal)


#### class `UE::Mutable::Private::NodeScalarCurve`  
`class NodeScalarCurve : public NodeScalar`  
_L17-39_
- inherits: `NodeScalar`
- desc: This node makes a new scalar value transforming another scalar value with a curve.
- L21 _public member_ `FRichCurve Curve;`
- L22 _public member_ `Ptr<NodeScalar> CurveSampleValue;`
- L27 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L28 _public function_ `static const FNodeType* GetStaticType()`
- L33 _protected prototype_ `~NodeScalarCurve() = default;` — Forbidden. Manage with the Ptr<> template.
- L37 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MUTABLETOOLS_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Mutable` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeScalarEnumParameter.h` (Internal)


#### class `UE::Mutable::Private::NodeScalarEnumParameter`  
`class NodeScalarEnumParameter : public NodeScalar`  
_L17-50_
- inherits: `NodeScalar`
- desc: Node that defines a scalar model parameter to be selected from a set of named values.
- L21 _public member_ `FString Name;`
- L22 _public member_ `FString UID;`
- L23 _public member_ `int32 DefaultValue = 0;`
- L31 _public member_ `TArray<FOption> Options;`
- L33 _public member_ `TArray<Ptr<NodeRange>> Ranges;`
- L38 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L39 _public function_ `static const FNodeType* GetStaticType()`
- L44 _protected prototype_ `~NodeScalarEnumParameter() = default;` — Forbidden. Manage with the Ptr<> template.
- L48 _private member_ `static FNodeType StaticType;`

#### struct `UE::Mutable::Private::NodeScalarEnumParameter::FOption`  
`struct FOption`  
_L25-29_
- L27 _public member_ `FString Name;`
- L28 _public member_ `float Value = 0.0f;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MUTABLETOOLS_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Mutable` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeScalarExternal.h` (Internal)


#### class `UE::Mutable::Private::NodeScalarExternal`  
`class NodeScalarExternal : public NodeScalar`  
_L14-30_
- inherits: `NodeScalar`
- L18 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L19 _public function_ `static const FNodeType* GetStaticType()`
- L23 _protected prototype_ `virtual ~NodeScalarExternal() override = default;` — Forbidden. Manage with the Ptr<> template.
- L26 _private member_ `static FNodeType StaticType;`
- L29 _public member_ `Ptr<NodeExternal> Node;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MUTABLETOOLS_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Mutable` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeScalarMaterialBreak.h` (Internal)


#### class `UE::Mutable::Private::NodeScalarMaterialBreak`  
`class NodeScalarMaterialBreak : public NodeScalar`  
_L16-37_
- inherits: `NodeScalar`
- desc: NodeMaterialTable class.
- L20 _public member_ `Ptr<NodeMaterial> MaterialSource;`
- L21 _public member_ `FParameterKey ParameterKey;`
- L26 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L27 _public function_ `static const FNodeType* GetStaticType()`
- L32 _protected prototype_ `~NodeScalarMaterialBreak() = default;` — Forbidden. Manage with the Ptr<> template.
- L36 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MUTABLETOOLS_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Mutable` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeScalarParameter.h` (Internal)


#### class `UE::Mutable::Private::NodeScalarParameter`  
`class NodeScalarParameter : public NodeScalar`  
_L18-43_
- inherits: `NodeScalar`
- desc: Node that defines a scalar model parameter.
- L22 _public member_ `float DefaultValue = 0.0f;`
- L23 _public member_ `FString Name;`
- L24 _public member_ `FString UID;`
- L26 _public member_ `TArray<Ptr<NodeRange>> Ranges;`
- L31 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L32 _public function_ `static const FNodeType* GetStaticType()`
- L37 _protected prototype_ `~NodeScalarParameter() = default;` — Forbidden. Manage with the Ptr<> template.
- L41 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MUTABLETOOLS_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Mutable` (scope `UE`)
- L14 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeScalarSwitch.h` (Internal)


#### class `UE::Mutable::Private::NodeScalarSwitch`  
`class NodeScalarSwitch : public NodeScalar`  
_L17-39_
- inherits: `NodeScalar`
- desc: This node selects an output Scalar from a set of input Scalars based on a parameter.
- L21 _public member_ `Ptr<NodeScalar> Parameter;`
- L22 _public member_ `TArray<Ptr<NodeScalar>> Options;`
- L27 _public function_ `virtual const FNodeType* GetType() const override` — Node interface
- L28 _public function_ `static const FNodeType* GetStaticType()`
- L33 _protected prototype_ `~NodeScalarSwitch() = default;` — Forbidden. Manage with the Ptr<> template.
- L37 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MUTABLETOOLS_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Mutable` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeScalarTable.h` (Internal)


#### class `UE::Mutable::Private::NodeScalarTable`  
`class NodeScalarTable : public NodeScalar`  
_L17-42_
- inherits: `NodeScalar`
- desc: This node provides the meshes stored in the column of a table.
- L21 _public member_ `FString ParameterName;`
- L22 _public member_ `Ptr<FTable> Table;`
- L23 _public member_ `FString ColumnName;`
- L24 _public member_ `bool bNoneOption = false;`
- L25 _public member_ `FString DefaultRowName;`
- L30 _public function_ `virtual const FNodeType* GetType() const override` — Node interface
- L31 _public function_ `static const FNodeType* GetStaticType()`
- L36 _protected prototype_ `~NodeScalarTable() = default;` — Forbidden. Manage with the Ptr<> template.
- L40 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MUTABLETOOLS_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Mutable` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeScalarVariation.h` (Internal)


#### class `UE::Mutable::Private::NodeScalarVariation`  
`class NodeScalarVariation : public NodeScalar`  
_L16-45_
- inherits: `NodeScalar`
- L20 _public member_ `Ptr<NodeScalar> DefaultScalar;`
- L28 _public member_ `TArray<FVariation> Variations;`
- L33 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L34 _public function_ `static const FNodeType* GetStaticType()`
- L39 _protected prototype_ `~NodeScalarVariation() = default;` — Forbidden. Manage with the Ptr<> template.
- L43 _private member_ `static FNodeType StaticType;`

#### struct `UE::Mutable::Private::NodeScalarVariation::FVariation`  
`struct FVariation`  
_L22-26_
- L24 _public member_ `Ptr<NodeScalar> Scalar;`
- L25 _public member_ `FString Tag;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MUTABLETOOLS_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Mutable` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeSkeletalMesh.h` (Internal)


#### class `UE::Mutable::Private::NodeSkeletalMesh`  
`class NodeSkeletalMesh : public Node`  
_L12-24_
- inherits: `Node`
- L16 _public function_ `virtual const FNodeType* GetType() const override` — Node interface
- L17 _public function_ `static const FNodeType* GetStaticType()`
- L20 _protected function_ `virtual ~NodeSkeletalMesh() override`
- L23 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API MUTABLETOOLS_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Mutable` (scope `UE`)
- L10 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeSkeletalMeshClipWithSkeletalMesh.h` (Internal)


#### class `UE::Mutable::Private::NodeSkeletalMeshClipWithSkeletalMesh`  
`class NodeSkeletalMeshClipWithSkeletalMesh : public NodeSkeletalMesh`  
_L14-37_
- inherits: `NodeSkeletalMesh`
- L18 _public member_ `Ptr<NodeSkeletalMesh> SourceSkeletalMesh;`
- L20 _public member_ `Ptr<NodeSkeletalMesh> ClipSkeletalMesh;`
- L22 _public member_ `EFaceCullStrategy FaceCullStrategy = EFaceCullStrategy::AllVerticesCulled;`
- L25 _public function_ `virtual const FNodeType* GetType() const override` — Node interface
- L26 _public function_ `static const FNodeType* GetStaticType()`
- L31 _protected prototype_ `inline ~NodeSkeletalMeshClipWithSkeletalMesh() = default;` — Forbidden. Manage with the Ptr<> template.
- L35 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MUTABLETOOLS_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Mutable` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeSkeletalMeshConvert.h` (Internal)


#### class `UE::Mutable::Private::NodeSkeletalMeshConvert`  
`class NodeSkeletalMeshConvert : public NodeSkeletalMesh`  
_L15-30_
- inherits: `NodeSkeletalMesh`
- L18 _public member_ `Ptr<NodeSkeletalMeshObject> SkeletalMesh;`
- L19 _public member_ `uint8 ConversionFlags = 0;`
- L22 _public function_ `virtual const FNodeType* GetType() const override` — Node interface
- L23 _public function_ `static const FNodeType* GetStaticType()`
- L26 _protected function_ `virtual ~NodeSkeletalMeshConvert() override`
- L29 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MUTABLETOOLS_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Mutable` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeSkeletalMeshMerge.h` (Internal)


#### class `UE::Mutable::Private::NodeSkeletalMeshMerge`  
`class NodeSkeletalMeshMerge : public NodeSkeletalMesh`  
_L16-35_
- inherits: `NodeSkeletalMesh`
- L21 _public member_ `Ptr<NodeSkeletalMesh> BaseSkeletalMesh;` — Mesh where we want to merge into the sections of the ToAddSkeletalMesh
- L24 _public member_ `Ptr<NodeSkeletalMesh> ToAddSkeletalMesh;` — Skeletal Mesh whose section will be merged with the ones on the BaseSkeletalMesh
- L27 _public function_ `virtual const FNodeType* GetType() const override` — Node interface
- L28 _public function_ `static const FNodeType* GetStaticType()`
- L31 _protected function_ `virtual ~NodeSkeletalMeshMerge() override`
- L34 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MUTABLETOOLS_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Mutable` (scope `UE`)
- L14 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeSkeletalMeshModify.h` (Internal)


#### class `UE::Mutable::Private::NodeSkeletalMeshModify`  
`class NodeSkeletalMeshModify : public NodeSkeletalMesh`  
_L18-37_
- inherits: `NodeSkeletalMesh`
- L23 _public member_ `Ptr<NodeSkeletalMesh> SkeletalMesh;` — Skeletal mesh whose slots we want to override
- L26 _public member_ `TMap<FName, Ptr<NodeMaterial>> SlotMaterials;` — Map of Slots (FName) where each one of them will have a Material assigned to them
- L29 _public function_ `virtual const FNodeType* GetType() const override` — Node interface
- L30 _public function_ `static const FNodeType* GetStaticType()`
- L33 _protected function_ `virtual ~NodeSkeletalMeshModify() override`
- L36 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API MUTABLETOOLS_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Mutable` (scope `UE`)
- L16 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeSkeletalMeshMorph.h` (Internal)


#### class `UE::Mutable::Private::NodeSkeletalMeshMorph`  
`class NodeSkeletalMeshMorph : public NodeSkeletalMesh`  
_L15-38_
- inherits: `NodeSkeletalMesh`
- desc: Node that morphs a base skeletal mesh with one weighted target.
- L19 _public member_ `FName Name;`
- L20 _public member_ `Ptr<NodeScalar> Factor;`
- L21 _public member_ `Ptr<NodeSkeletalMesh> Base;`
- L26 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L27 _public function_ `static const FNodeType* GetStaticType()`
- L32 _protected prototype_ `~NodeSkeletalMeshMorph() = default;` — Forbidden. Manage with the Ptr<> template.
- L36 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MUTABLETOOLS_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Mutable` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeSkeletalMeshNew.h` (Internal)


#### class `UE::Mutable::Private::NodeSkeletalMeshNew`  
`class NodeSkeletalMeshNew : public NodeSkeletalMesh`  
_L15-29_
- inherits: `NodeSkeletalMesh`
- L18 _public member_ `TArray<Ptr<NodeLOD>> LODs;`
- L21 _public function_ `virtual const FNodeType* GetType() const override` — Node interface
- L22 _public function_ `static const FNodeType* GetStaticType()`
- L25 _protected function_ `virtual ~NodeSkeletalMeshNew() override`
- L28 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MUTABLETOOLS_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Mutable` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeSkeletalMeshObject.h` (Internal)


#### class `UE::Mutable::Private::NodeSkeletalMeshObject`  
`class NodeSkeletalMeshObject : public Node`  
_L12-24_
- inherits: `Node`
- L16 _public function_ `virtual const FNodeType* GetType() const override` — Node interface
- L17 _public function_ `static const FNodeType* GetStaticType()`
- L20 _protected function_ `virtual ~NodeSkeletalMeshObject() override`
- L23 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API MUTABLETOOLS_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Mutable` (scope `UE`)
- L10 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeSkeletalMeshObjectConvert.h` (Internal)


#### class `UE::Mutable::Private::NodeSkeletalMeshObjectConvert`  
`class NodeSkeletalMeshObjectConvert : public NodeSkeletalMeshObject`  
_L18-42_
- inherits: `NodeSkeletalMeshObject`
- L21 _public member_ `Ptr<NodeSkeletalMesh> SkeletalMesh;`
- L23 _public member_ `FName Name;`
- L24 _public member_ `int32 NumLODs = 0;`
- L25 _public member_ `int32 FirstLODAvailable = 0;`
- L26 _public member_ `int32 FirstLODResident = 0;`
- L28 _public member_ `FPerPlatformInt MinLODs;`
- L29 _public member_ `FPerQualityLevelInt MinQualityLevelLODs;`
- L31 _public member_ `TArray<FLODInfo> LODInfos;`
- L34 _public function_ `virtual const FNodeType* GetType() const override` — Node interface
- L35 _public function_ `static const FNodeType* GetStaticType()`
- L38 _protected function_ `virtual ~NodeSkeletalMeshObjectConvert() override`
- L41 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API MUTABLETOOLS_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Mutable` (scope `UE`)
- L16 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeSkeletalMeshObjectParameter.h` (Internal)


#### class `UE::Mutable::Private::NodeSkeletalMeshObjectParameter`  
`class NodeSkeletalMeshObjectParameter : public NodeSkeletalMeshObject`  
_L15-32_
- inherits: `NodeSkeletalMeshObject`
- L18 _public member_ `FString Name;`
- L20 _public member_ `FString UID;`
- L22 _public member_ `TArray<Ptr<NodeRange>> Ranges;`
- L25 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L26 _public function_ `static const FNodeType* GetStaticType()`
- L28 _public function_ `virtual ~NodeSkeletalMeshObjectParameter() override`
- L31 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MUTABLETOOLS_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Mutable` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeSkeletalMeshObjectSwitch.h` (Internal)


#### class `UE::Mutable::Private::NodeSkeletalMeshObjectSwitch`  
`class NodeSkeletalMeshObjectSwitch : public NodeSkeletalMeshObject`  
_L15-31_
- inherits: `NodeSkeletalMeshObject`
- L19 _public member_ `Ptr<NodeScalar> Parameter;`
- L21 _public member_ `TArray<Ptr<NodeSkeletalMeshObject>> Options;`
- L24 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L25 _public function_ `static const FNodeType* GetStaticType()`
- L27 _public function_ `virtual ~NodeSkeletalMeshObjectSwitch() override`
- L30 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MUTABLETOOLS_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Mutable` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeSkeletalMeshReshape.h` (Internal)


#### class `UE::Mutable::Private::NodeSkeletalMeshReshape`  
`class NodeSkeletalMeshReshape : public NodeSkeletalMesh`  
_L15-54_
- inherits: `NodeSkeletalMesh`
- desc: Node that reshapes a base skeletal mesh from a base shape towards a target shape.
- L19 _public member_ `Ptr<NodeSkeletalMesh> Base;`
- L20 _public member_ `Ptr<NodeSkeletalMesh> BaseShape;`
- L21 _public member_ `Ptr<NodeSkeletalMesh> TargetShape;`
- L23 _public member_ `bool bReshapeVertices = true;`
- L24 _public member_ `bool bRecomputeNormals = false;`
- L25 _public member_ `bool bApplyLaplacian = false;`
- L26 _public member_ `bool bReshapeSkeleton = false;`
- L27 _public member_ `bool bReshapePhysicsVolumes = false;`
- L28 _public member_ `bool bReshapeSkeletonInvertSelection = false;`
- L29 _public member_ `bool bReshapePhysicsVolumesInvertSelection = false;`
- L31 _public member_ `EVertexColorUsage ColorRChannelUsage = EVertexColorUsage::None;`
- L32 _public member_ `EVertexColorUsage ColorGChannelUsage = EVertexColorUsage::None;`
- L33 _public member_ `EVertexColorUsage ColorBChannelUsage = EVertexColorUsage::None;`
- L34 _public member_ `EVertexColorUsage ColorAChannelUsage = EVertexColorUsage::None;`
- L36 _public member_ `TArray<FName> BonesToDeform;`
- L37 _public member_ `TArray<FName> PhysicsToDeform;`
- L42 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L43 _public function_ `static const FNodeType* GetStaticType()`
- L48 _protected prototype_ `virtual ~NodeSkeletalMeshReshape() = default;` — Forbidden. Manage with the Ptr<> template.
- L52 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MUTABLETOOLS_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Mutable` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeSkeletalMeshSwitch.h` (Internal)


#### class `UE::Mutable::Private::NodeSkeletalMeshSwitch`  
`class NodeSkeletalMeshSwitch : public NodeSkeletalMesh`  
_L14-37_
- inherits: `NodeSkeletalMesh`
- desc: This node selects an output Skeletal Mesh from a set of input Skeletal Meshes based on a parameter.
- L18 _public member_ `Ptr<NodeScalar> Parameter;`
- L20 _public member_ `TArray<Ptr<NodeSkeletalMesh>> Options;`
- L25 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L26 _public function_ `static const FNodeType* GetStaticType()`
- L31 _protected prototype_ `~NodeSkeletalMeshSwitch() = default;` — Forbidden. Manage with the Ptr<> template.
- L35 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MUTABLETOOLS_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Mutable` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeSkeletalMeshTransform.h` (Internal)


#### class `UE::Mutable::Private::NodeSkeletalMeshTransform`  
`class NodeSkeletalMeshTransform : public NodeSkeletalMesh`  
_L18-39_
- inherits: `NodeSkeletalMesh`
- desc: This node applies a geometric transform represented by a 4x4 matrix to a mesh.
- L22 _public member_ `Ptr<NodeSkeletalMesh> Source;`
- L23 _public member_ `FMatrix44f Transform;`
- L28 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L29 _public function_ `static const FNodeType* GetStaticType()`
- L33 _protected prototype_ `virtual ~NodeSkeletalMeshTransform() override = default;` — Forbidden. Manage with the Ptr<> template.
- L37 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MUTABLETOOLS_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Mutable` (scope `UE`)
- L15 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeSkeletalMeshTransformWithBone.h` (Internal)


#### class `UE::Mutable::Private::NodeSkeletalMeshTransformWithBone`  
`class NodeSkeletalMeshTransformWithBone : public NodeSkeletalMesh`  
_L18-38_
- inherits: `NodeSkeletalMesh`
- L21 _public member_ `FName BoneName = NAME_None;`
- L23 _public member_ `float ThresholdFactor = 0.0f;`
- L25 _public member_ `Ptr<NodeSkeletalMesh> Source;`
- L27 _public member_ `Ptr<NodeMatrix> MatrixNode;`
- L30 _public function_ `virtual const FNodeType* GetType() const override` — Node interface
- L31 _public function_ `static const FNodeType* GetStaticType()`
- L34 _protected function_ `virtual ~NodeSkeletalMeshTransformWithBone() override`
- L37 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API MUTABLETOOLS_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Mutable` (scope `UE`)
- L16 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeSkeletalMeshVariation.h` (Internal)


#### class `UE::Mutable::Private::NodeSkeletalMeshVariation`  
`class NodeSkeletalMeshVariation : public NodeSkeletalMesh`  
_L14-42_
- inherits: `NodeSkeletalMesh`
- L18 _public member_ `Ptr<NodeSkeletalMesh> DefaultSkeletalMesh;`
- L26 _public member_ `TArray<FVariation> Variations;`
- L30 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L31 _public function_ `static const FNodeType* GetStaticType()`
- L36 _protected prototype_ `~NodeSkeletalMeshVariation() = default;` — Forbidden. Manage with the Ptr<> template.
- L40 _private member_ `static FNodeType StaticType;`

#### struct `UE::Mutable::Private::NodeSkeletalMeshVariation::FVariation`  
`struct FVariation`  
_L20-24_
- L22 _public member_ `Ptr<NodeSkeletalMesh> SkeletalMesh;`
- L23 _public member_ `FString Tag;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MUTABLETOOLS_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Mutable` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeString.h` (Internal)


#### class `UE::Mutable::Private::NodeString`  
`class NodeString : public Node`  
_L17-34_
- inherits: `Node`
- desc: Base class of any node that outputs a string value.
- L22 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L23 _public function_ `static const FNodeType* GetStaticType()`
- L28 _protected prototype_ `~NodeString() = default;` — Forbidden. Manage with the Ptr<> template.
- L32 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MUTABLETOOLS_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Mutable` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeStringConstant.h` (Internal)


#### class `UE::Mutable::Private::NodeStringConstant`  
`class NodeStringConstant : public NodeString`  
_L17-38_
- inherits: `NodeString`
- desc: Node returning a string constant value.
- L21 _public member_ `FString Value;`
- L26 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L27 _public function_ `static const FNodeType* GetStaticType()`
- L32 _protected prototype_ `~NodeStringConstant() = default;` — Forbidden. Manage with the Ptr<> template.
- L36 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MUTABLETOOLS_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Mutable` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeStringParameter.h` (Internal)


#### class `UE::Mutable::Private::NodeStringParameter`  
`class NodeStringParameter : public NodeString`  
_L18-43_
- inherits: `NodeString`
- desc: Node that defines a string model parameter.
- L22 _public member_ `FString DefaultValue;`
- L23 _public member_ `FString Name;`
- L24 _public member_ `FString UID;`
- L26 _public member_ `TArray<Ptr<NodeRange>> Ranges;`
- L31 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L32 _public function_ `static const FNodeType* GetStaticType()`
- L37 _protected prototype_ `~NodeStringParameter() = default;` — Forbidden. Manage with the Ptr<> template.
- L41 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MUTABLETOOLS_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Mutable` (scope `UE`)
- L14 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeSurface.h` (Internal)


#### class `UE::Mutable::Private::NodeSurface`  
`class NodeSurface : public Node`  
_L23-40_
- inherits: `Node`
- desc: This class is the parent of all nodes that output a Surface.
- L28 _public function_ `virtual const FNodeType* GetType() const override` — Node interface
- L29 _public function_ `static const FNodeType* GetStaticType()`
- L34 _protected prototype_ `inline ~NodeSurface() = default;` — Forbidden. Manage with the Ptr<> template.
- L38 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MUTABLETOOLS_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Mutable` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L18 _typedef_ `typedef Ptr<NodeSurface> NodeSurfacePtr;` (scope `UE::Mutable::Private`)
- L19 _typedef_ `typedef Ptr<const NodeSurface> NodeSurfacePtrConst;` (scope `UE::Mutable::Private`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeSurfaceModifier.h` (Internal)


#### enum `EMutableMultipleTagPolicy`  
`enum class EMutableMultipleTagPolicy : uint8`  
_L21-28_
- reflection: `UENUM()`
- desc: Despite being an UEnum, this is not always version-serialized (in MutableTools). Beware of changing the enum options or order.
- L24 _public enumerator_ `OnlyOneRequired` — All the Mesh Sections that do have at least one of the Target tags will be modified.
- L27 _public enumerator_ `AllRequired` — Only the Mesh Sections that do have all the Target tags will be modified.

#### class `UE::Mutable::Private::NodeSurfaceModifier`  
`class NodeSurfaceModifier : public NodeModifier`  
_L40-75_
- inherits: `NodeModifier`
- desc: Parent of all node classes that apply modifiers to surfaces.
- L45 _public member_ `int32 RequiredComponentId = -1;` — If not negative, this modifier will only be applied to the nodes of the component with matching id. Otherwise it will be applied to all components.
- L48 _public member_ `TArray<FString> RequiredTags;` — Tags that target surface need to have enabled to receive this modifier.
- L51 _public member_ `EMutableMultipleTagPolicy MultipleTagsPolicy = EMutableMultipleTagPolicy::OnlyOneRequired;` — In case of multiple tags in RequiredTags: are they all required, or one is enough?
- L54 _public member_ `bool bApplyBeforeNormalOperations = true;` — Wether the modifier has to be applied before the normal node operations or after.
- L59 _public member_ `TArray<FString> EnableTags;` — Tags enabled by this modifier. Other modifiers activated by these tags will be applied to this modifier's "child data" like meshes added by this modifier. Not to be confused with the RequiredTags.
- L64 _public function_ `virtual const FNodeType* GetType() const override` — Node interface
- L65 _public function_ `static const FNodeType* GetStaticType()`
- L70 _protected prototype_ `inline ~NodeSurfaceModifier() = default;` — Forbidden. Manage with the Ptr<> template.
- L74 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API MUTABLETOOLS_API`
- L31 _namespace_ `namespace UE`
- L31 _namespace_ `namespace Mutable` (scope `UE`)
- L31 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L36 _typedef_ `typedef Ptr<NodeSurfaceModifier> NodeModifierPtr;` (scope `UE::Mutable::Private`)
- L37 _typedef_ `typedef Ptr<const NodeSurfaceModifier> NodeModifierConst;` (scope `UE::Mutable::Private`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeSurfaceModifierMeshClipDeform.h` (Internal)


#### class `UE::Mutable::Private::NodeSurfaceModifierMeshClipDeform`  
`class NodeSurfaceModifierMeshClipDeform : public NodeSurfaceModifier`  
_L19-45_
- inherits: `NodeSurfaceModifier`
- L23 _public member_ `Ptr<NodeMesh> ClipMesh;`
- L25 _public member_ `EShapeBindingMethod BindingMethod = EShapeBindingMethod::ClipDeformClosestProject;`
- L28 _public member_ `EFaceCullStrategy FaceCullStrategy = EFaceCullStrategy::AllVerticesCulled;`
- L33 _public function_ `virtual const FNodeType* GetType() const override` — Node interface
- L34 _public function_ `static const FNodeType* GetStaticType()`
- L39 _protected prototype_ `inline ~NodeSurfaceModifierMeshClipDeform() = default;` — Forbidden. Manage with the Ptr<> template.
- L43 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API MUTABLETOOLS_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Mutable` (scope `UE`)
- L15 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeSurfaceModifierMeshClipMorphPlane.h` (Internal)


#### struct `UE::Mutable::Private::FClipMorphPlaneParameters`  
`struct FClipMorphPlaneParameters`  
_L17-43_
- L22 _public member_ `float DistanceToPlane = 0;` — Distance to the plane of last affected vertex
- L25 _public member_ `float LinearityFactor = 0;` — "Linearity" factor of the influence.
- L28 _public member_ `FVector3f Origin = FVector3f(0, 0, 0);` — Ellipse location
- L29 _public member_ `FVector3f Normal = FVector3f(0, 0, 0);`
- L30 _public member_ `float Radius1 = 0, Radius2 = 0, Rotation = 0;`
- L30 _public member_ `float Radius1 = 0, Radius2 = 0, Rotation = 0;`
- L30 _public member_ `float Radius1 = 0, Radius2 = 0, Rotation = 0;`
- L33 _public member_ `EClipVertexSelectionType VertexSelectionType = EClipVertexSelectionType::None;` — Vertex selection box
- L34 _public member_ `FVector3f SelectionBoxOrigin = FVector3f(0, 0, 0);`
- L35 _public member_ `FVector3f SelectionBoxRadius = FVector3f(0, 0, 0);`
- L36 _public member_ `FName VertexSelectionBone = NAME_None;`
- L40 _public member_ `float MaxEffectRadius = -1.0f;` — Max distance a vertex can have to the bone in order to be affected. A negative value means no limit.
- L42 _public member_ `EFaceCullStrategy FaceCullStrategy = EFaceCullStrategy::AllVerticesCulled;`

#### class `UE::Mutable::Private::NodeSurfaceModifierMeshClipMorphPlane`  
`class NodeSurfaceModifierMeshClipMorphPlane : public NodeSurfaceModifier`  
_L47-84_
- inherits: `NodeSurfaceModifier`
- L51 _public member_ `FClipMorphPlaneParameters Parameters;`
- L56 _public function_ `virtual const FNodeType* GetType() const override` — Node interface
- L57 _public function_ `static const FNodeType* GetStaticType()`
- L63 _public prototype_ `void SetPlane(FVector3f Center, FVector3f Normal);`
- L64 _public prototype_ `void SetParams(float dist, float factor);`
- L65 _public prototype_ `void SetMorphEllipse(float radius1, float radius2, float rotation);`
- L69 _public prototype_ `void SetVertexSelectionBox(float centerX, float centerY, float centerZ, float radiusX, float radiusY, float radiusZ);` — Define an axis-aligned box that will select the vertices to be morphed. Only one of Box or Bone Hierarchy can be used (the last one set)
- L73 _public prototype_ `void SetVertexSelectionBone(FName BoneId, float maxEffectRadius);` — Define the root bone of the subhierarchy of the mesh that will be affected. Only one of Box or Bone Hierarchy can be used (the last one set)
- L78 _protected prototype_ `~NodeSurfaceModifierMeshClipMorphPlane() = default;` — Forbidden. Manage with the Ptr<> template.
- L82 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MUTABLETOOLS_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Mutable` (scope `UE`)
- L14 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeSurfaceModifierMeshClipWithMesh.h` (Internal)


#### class `UE::Mutable::Private::NodeSurfaceModifierMeshClipWithMesh`  
`class NodeSurfaceModifierMeshClipWithMesh : public NodeSurfaceModifier`  
_L18-43_
- inherits: `NodeSurfaceModifier`
- L23 _public member_ `Ptr<NodeMesh> ClipMesh;`
- L26 _public member_ `EFaceCullStrategy FaceCullStrategy = EFaceCullStrategy::AllVerticesCulled;`
- L31 _public function_ `virtual const FNodeType* GetType() const override` — Node interface
- L32 _public function_ `static const FNodeType* GetStaticType()`
- L37 _protected prototype_ `inline ~NodeSurfaceModifierMeshClipWithMesh() = default;` — Forbidden. Manage with the Ptr<> template.
- L41 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MUTABLETOOLS_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Mutable` (scope `UE`)
- L14 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeSurfaceModifierMeshClipWithUVMask.h` (Internal)


#### class `UE::Mutable::Private::NodeSurfaceModifierMeshClipWithUVMask`  
`class NodeSurfaceModifierMeshClipWithUVMask : public NodeSurfaceModifier`  
_L19-50_
- inherits: `NodeSurfaceModifier`
- desc: This node can clip part of a mesh using UV space-data (an image or a list of layout blocks).
- L24 _public member_ `Ptr<NodeImage> ClipMask;` — Image with the regions to remove. It will be interpreted as a bitmap.
- L27 _public member_ `Ptr<NodeLayout> ClipLayout;` — If the image above is null, clipping may hapopen with layout blocks.
- L30 _public member_ `uint8 LayoutIndex = 0;` — Layout index of the UVs to use inthe source mesh to ben clipped with the mask.
- L33 _public member_ `EFaceCullStrategy FaceCullStrategy = EFaceCullStrategy::AllVerticesCulled;`
- L38 _public function_ `virtual const FNodeType* GetType() const override` — Node interface
- L39 _public function_ `static const FNodeType* GetStaticType()`
- L44 _protected prototype_ `inline ~NodeSurfaceModifierMeshClipWithUVMask() = default;` — Forbidden. Manage with the Ptr<> template.
- L48 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MUTABLETOOLS_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Mutable` (scope `UE`)
- L15 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeSurfaceModifierMeshTransformInMesh.h` (Internal)


#### class `UE::Mutable::Private::NodeSurfaceModifierMeshTransformInMesh`  
`class NodeSurfaceModifierMeshTransformInMesh : public NodeSurfaceModifier`  
_L18-42_
- inherits: `NodeSurfaceModifier`
- L23 _public member_ `Ptr<NodeMesh> BoundingMesh;`
- L26 _public member_ `Ptr<NodeMatrix> MatrixNode;`
- L30 _public function_ `virtual const FNodeType* GetType() const override` — Node interface
- L31 _public function_ `static const FNodeType* GetStaticType()`
- L36 _protected prototype_ `virtual ~NodeSurfaceModifierMeshTransformInMesh() override = default;` — Forbidden. Manage with the Ptr<> template.
- L40 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MUTABLETOOLS_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Mutable` (scope `UE`)
- L14 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeSurfaceModifierMeshTransformWithBone.h` (Internal)


#### class `UE::Mutable::Private::NodeSurfaceModifierMeshTransformWithBone`  
`class NodeSurfaceModifierMeshTransformWithBone : public NodeSurfaceModifier`  
_L18-45_
- inherits: `NodeSurfaceModifier`
- L23 _public member_ `FName BoneName = NAME_None;`
- L24 _public member_ `float ThresholdFactor = 0.0f;`
- L27 _public member_ `Ptr<NodeMatrix> MatrixNode;`
- L33 _public function_ `virtual const FNodeType* GetType() const override` — Node interface
- L34 _public function_ `static const FNodeType* GetStaticType()`
- L39 _protected prototype_ `virtual ~NodeSurfaceModifierMeshTransformWithBone() override = default;` — Forbidden. Manage with the Ptr<> template.
- L43 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API MUTABLETOOLS_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Mutable` (scope `UE`)
- L14 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeSurfaceModifierSurfaceEdit.h` (Internal)


#### class `UE::Mutable::Private::NodeSurfaceModifierSurfaceEdit`  
`class NodeSurfaceModifierSurfaceEdit : public NodeSurfaceModifier`  
_L24-102_
- inherits: `NodeSurfaceModifier`
- desc: This node modifies a surface node. It allows to extend, cut and morph the parent Surface's meshes. It also allows to patch the parent Surface's textures.
- L67 _public member_ `TArray<FLOD> LODs;`
- L70 _public member_ `EFaceCullStrategy FaceCullStrategy = EFaceCullStrategy::AllVerticesCulled;` — For remove operations, use this strategy to cull faces.
- L73 _public member_ `FString MeshMorph;` — Name of the morph to apply to the modified surface if it has it.
- L76 _public member_ `Ptr<NodeScalar> MorphFactor;` — Factor of the morph to apply.
- L79 _public member_ `FGuid ModifierGuid;` — Source modifier guid, used to share resources between LODs and generate a deterministic surface guid.
- L83 _public function_ `NodeSurfaceModifierSurfaceEdit()`
- L90 _public function_ `virtual const FNodeType* GetType() const override` — Node interface
- L91 _public function_ `static const FNodeType* GetStaticType()`
- L96 _protected prototype_ `~NodeSurfaceModifierSurfaceEdit() = default;` — Forbidden. Manage with the Ptr<> template.
- L100 _private member_ `static FNodeType StaticType;`

#### struct `UE::Mutable::Private::NodeSurfaceModifierSurfaceEdit::FTexture`  
`struct FTexture`  
_L29-53_
- desc: Data for every modified texture.
- L34 _public member_ `FParameterKey MaterialParameterKey;` — Key used to match the image with the original one being modified. This should match the MaterialParameterKey in a NodeSurfaceNew::FImageData.
- L37 _public member_ `Ptr<NodeImage> Extend;` — Image to add if extgending.
- L40 _public member_ `Ptr<NodeImage> PatchImage;` — Image to blend if patching.
- L43 _public member_ `Ptr<NodeImage> PatchMask;` — Optional mask controlling the blending area.
- L46 _public member_ `TArray<FBox2f> PatchBlocks;` — Rects in the parent layout homogeneous UV space to patch.
- L49 _public member_ `EBlendType PatchBlendType = EBlendType::BT_BLEND;` — Type of patching operation.
- L52 _public member_ `bool bPatchApplyToAlpha = false;` — Patch alpha channel as well?

#### struct `UE::Mutable::Private::NodeSurfaceModifierSurfaceEdit::FLOD`  
`struct FLOD`  
_L55-65_
- L58 _public member_ `Ptr<NodeMesh> MeshRemove;` — Mesh to remove from the modified surface.
- L61 _public member_ `Ptr<NodeMesh> MeshAdd;` — Mesh to add to the modified surface.
- L64 _public member_ `TArray<FTexture> Textures;` — Textures to modify.

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API MUTABLETOOLS_API`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Mutable` (scope `UE`)
- L17 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeSurfaceNew.h` (Internal)


#### class `UE::Mutable::Private::NodeSurfaceNew`  
`class NodeSurfaceNew : public NodeSurface`  
_L24-71_
- inherits: `NodeSurface`
- desc: This node makes a new Surface (Mesh Material Section) from a mesh and several material parameters like images, vectors and scalars.
- L27 _public member_ `FName Name;`
- L32 _public member_ `uint32 ExternalId = 0;` — An optional, opaque id that will be returned in the surfaces of the created instances. Can be useful to identify surfaces on the application side.
- L35 _public member_ `FGuid SurfaceGuid;` — Source surface Guid, used to share layouts between LODs and generate a deterministic SharedSurfaceId.
- L37 _public member_ `Ptr<NodeMesh> Mesh;`
- L39 _public member_ `Ptr<NodeMaterial> Material;`
- L47 _public member_ `TArray<FStringData> Strings;`
- L54 _public member_ `TArray<FString> Tags;` — Tags added to the surface: - the surface will be affected by modifier nodes with the same tag - the tag will be enabled when the surface is added to an object, and it can activate variations for any surface.
- L59 _public function_ `virtual const FNodeType* GetType() const override` — Node interface
- L60 _public function_ `static const FNodeType* GetStaticType()`
- L65 _protected prototype_ `~NodeSurfaceNew() = default;` — Forbidden. Manage with the Ptr<> template.
- L69 _private member_ `static FNodeType StaticType;`

#### struct `UE::Mutable::Private::NodeSurfaceNew::FStringData`  
`struct FStringData`  
_L41-45_
- L43 _public member_ `FString Name;`
- L44 _public member_ `Ptr<NodeString> String;`

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API MUTABLETOOLS_API`
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace Mutable` (scope `UE`)
- L20 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeSurfaceSwitch.h` (Internal)


#### class `UE::Mutable::Private::NodeSurfaceSwitch`  
`class NodeSurfaceSwitch : public NodeSurface`  
_L18-40_
- inherits: `NodeSurface`
- desc: This node selects an output Surface from a set of input Surfaces based on a parameter.
- L22 _public member_ `Ptr<NodeScalar> Parameter;`
- L23 _public member_ `TArray<Ptr<NodeSurface>> Options;`
- L28 _public function_ `virtual const FNodeType* GetType() const override` — Node interface
- L29 _public function_ `static const FNodeType* GetStaticType()`
- L34 _protected prototype_ `~NodeSurfaceSwitch() = default;` — Forbidden. Manage with the Ptr<> template.
- L38 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MUTABLETOOLS_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Mutable` (scope `UE`)
- L14 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/NodeSurfaceVariation.h` (Internal)


#### class `UE::Mutable::Private::NodeSurfaceVariation`  
`class NodeSurfaceVariation : public NodeSurface`  
_L19-63_
- inherits: `NodeSurface`
- desc: This node modifies a node of the parent object of the object that this node belongs to. It allows to extend, cut and morph the parent Surface's meshes. It also allows to patch the parent Surface's textures.
- L23 _public member_ `TArray<Ptr<NodeSurface>> DefaultSurfaces;`
- L24 _public member_ `TArray<Ptr<NodeSurfaceModifier>> DefaultModifiers;`
- L37 _public member_ `NodeSurfaceVariation::VariationType Type = NodeSurfaceVariation::VariationType::Tag;`
- L46 _public member_ `TArray<FVariation> Variations;`
- L51 _public function_ `virtual const FNodeType* GetType() const override` — Node interface
- L52 _public function_ `static const FNodeType* GetStaticType()`
- L57 _protected prototype_ `~NodeSurfaceVariation() = default;` — Forbidden. Manage with the Ptr<> template.
- L61 _private member_ `static FNodeType StaticType;`

#### enum `UE::Mutable::Private::NodeSurfaceVariation::VariationType`  
`enum class VariationType : uint8`  
_L27-35_
- L31 _public enumerator_ `Tag = 0` — The variation selection is controlled by tags defined in other surfaces. Default value.
- L34 _public enumerator_ `State` — The variation selection is controlled by the state the object is in.

#### struct `UE::Mutable::Private::NodeSurfaceVariation::FVariation`  
`struct FVariation`  
_L39-44_
- L41 _public member_ `TArray<Ptr<NodeSurface>> Surfaces;`
- L42 _public member_ `TArray<Ptr<NodeSurfaceModifier>> Modifiers;`
- L43 _public member_ `FString Tag;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API MUTABLETOOLS_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Mutable` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/Table.h` (Internal)


#### enum `UE::Mutable::Private::ETableColumnType`  
`enum class ETableColumnType : uint32`  
_L20-29_
- desc: Types of the values for the table cells.
- L22 _public enumerator_ `None`
- L23 _public enumerator_ `Scalar`
- L24 _public enumerator_ `Color`
- L25 _public enumerator_ `Image`
- L26 _public enumerator_ `Mesh`
- L27 _public enumerator_ `String`
- L28 _public enumerator_ `Material`

#### class `UE::Mutable::Private::FTable`  
`class FTable : public RefCounted`  
_L36-83_
- inherits: `RefCounted`
- desc: A table that contains many rows and defines attributes like meshes, images, colors, etc. for every column. It is useful to define a big number of similarly structured objects, by using the NodeDatabase in a model expression. \ingroup model
- L40 _public prototype_ `FTable();`
- L47 _public prototype_ `void SetName(const FString&);`
- L48 _public prototype_ `const FString& GetName() const;`
- L51 _public prototype_ `int32 AddColumn(const FString&, ETableColumnType );`
- L54 _public prototype_ `int32 FindColumn(const FString&) const;` — Return the column index with the given name. -1 if not found.
- L57 _public prototype_ `void AddRow( uint32 id );`
- L60 _public prototype_ `void SetCell( int32 Column, uint32 RowId, int32 IntValue, const void* ErrorContext = nullptr);`
- L61 _public prototype_ `void SetCell( int32 Column, uint32 RowId, float Value, const void* ErrorContext = nullptr);`
- L62 _public prototype_ `void SetCell( int32 Column, uint32 RowId, const FVector4f& Value, const void* ErrorContext = nullptr);`
- L63 _public prototype_ `void SetCell( int32 Column, uint32 RowId, const UE::Mutable::Private::TManagedPtr<FImage>& Value, const void* ErrorContext = nullptr);`
- L64 _public prototype_ `void SetCell( int32 Column, uint32 RowId, const UE::Mutable::Private::TManagedPtr<FMesh>& Value, const void* ErrorContext = nullptr);`
- L65 _public prototype_ `void SetCell( int32 Column, uint32 RowId, const FString& Value, const void* ErrorContext = nullptr);`
- L72 _public prototype_ `Private* GetPrivate() const;`
- L77 _protected prototype_ `~FTable();` — Forbidden. Manage with the Ptr<> template.
- L81 _private member_ `Private* m_pD;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API MUTABLETOOLS_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Mutable` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/TablePrivate.h` (Internal)


#### struct `UE::Mutable::Private::FTableColumn`  
`struct FTableColumn`  
_L14-19_
- L16 _public member_ `FString Name;`
- L18 _public member_ `ETableColumnType Type;`

#### struct `UE::Mutable::Private::FTableValue`  
`struct FTableValue`  
_L22-33_
- L25 _public member_ `int32 Int;` — TODO: Union
- L26 _public member_ `float Scalar;`
- L27 _public member_ `FVector4f Color;`
- L28 _public member_ `TManagedPtr<FImage> Image;`
- L29 _public member_ `TManagedPtr<FMesh> Mesh;`
- L30 _public member_ `FString String;`
- L32 _public member_ `const void* ErrorContext;`

#### struct `UE::Mutable::Private::FTableRow`  
`struct FTableRow`  
_L36-40_
- L38 _public member_ `uint32 Id;`
- L39 _public member_ `TArray<FTableValue> Values;`

#### class `UE::Mutable::Private::FTable::Private`  
`class FTable::Private`  
_L44-71_
- L48 _public member_ `FString Name;`
- L49 _public member_ `TArray<FTableColumn> Columns;`
- L50 _public member_ `TArray<FTableRow> Rows;`
- L53 _public member_ `bool bNoneOption_DEPRECATED = false;` — Transient value for serialization compatibility
- L56 _public function_ `int32 FindRow( uint32 id ) const` — Find a row in the table by id. Return -1 if not found.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Mutable` (scope `UE`)
- L9 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/TypeInfo.h` (Internal)


#### class `UE::Mutable::Private::TypeInfo`  
`class TypeInfo`  
_L18-32_
- L22 _public member_ `static const char* s_imageFormatName[size_t(EImageFormat::Count)];`
- L24 _public member_ `static const char* s_meshBufferSemanticName[uint32(EMeshBufferSemantic::Count)];`
- L26 _public member_ `static const char* s_meshBufferFormatName[uint32(EMeshBufferFormat::Count) ];`
- L28 _public member_ `static const char* s_blendModeName[uint32(EBlendType::_BT_COUNT) ];`
- L30 _public member_ `static const char* s_projectorTypeName [ static_cast<uint32>(UE::Mutable::Private::EProjectorType::Count) ];`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API MUTABLETOOLS_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Mutable` (scope `UE`)
- L15 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Internal/MuT/UnrealPixelFormatOverride.h` (Internal)


#### Free symbols / members of external scopes

- L14 _prototype_ `extern void PrepareUnrealCompression();` — This function needs to be called from the game thread before any call to UnrealPixelFormatFunc can be done.
- L17 _prototype_ `void FillBuildSettingsFromMutableFormat(FTextureBuildSettings& Settings, bool& bOutHasAlpha, UE::Mutable::Private::EImageFormat Format);`
- L20 _prototype_ `void MutableToImageCore(const UE::Mutable::Private::FImage* InMutable, FImage& CoreImage, int32 LOD, bool bSwizzleRGBHack);`
- L23 _prototype_ `bool ImageCoreToMutable(const FCompressedImage2D& Compressed, UE::Mutable::Private::FImage* Mutable, int32 LOD);`
- L26 _prototype_ `extern UE::Mutable::Private::EImageFormat UnrealToMutablePixelFormat(EPixelFormat PlatformFormat, bool bHasAlpha);` — Convert an Unreal platform pixel format to Mutable.
- L29 _prototype_ `extern UE::Mutable::Private::EImageFormat QualityAndPerformanceFix(UE::Mutable::Private::EImageFormat Format);` — Function that remaps some formats to the ones that provide more acceptable quality in Mutable.
- L35 _prototype_ `extern void UnrealPixelFormatFunc(bool& bOutSuccess, int32 Quality, UE::Mutable::Private::FImage* Target, const UE::Mutable::Private::FImage* Source, int32 OnlyLOD);` — Try to convert an image using unreal's compression. If the format is not supported, it will return false in bOutSuccess. Can be called from any thread. PrepareUnrealCompression needs to be called from the game thread once prior to using this function.
- L38 _prototype_ `void DebugImageDump(const UE::Mutable::Private::FImage*, const FString& FilePath);` — Debug export the given image to a temp file in the saved folder.

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpAddExtensionData.h` (Private)


#### class `UE::Mutable::Private::ASTOpAddExtensionData`  
`class ASTOpAddExtensionData final : public ASTOp`  
_L20-40_
- inherits: `ASTOp`
- L23 _public member_ `static const EOpType Type = EOpType::IN_ADDEXTENSIONDATA;`
- L25 _public member_ `ASTChild Instance;`
- L26 _public member_ `ASTChild ExtensionData;`
- L30 _public prototype_ `ASTOpAddExtensionData();`
- L31 _public prototype_ `ASTOpAddExtensionData(const ASTOpAddExtensionData&) = delete;`
- L34 _public prototype_ `virtual EOpType GetOpType() const override;`
- L35 _public prototype_ `virtual uint32 Hash() const override;`
- L36 _public prototype_ `virtual void ForEachChild(const TFunctionRef<void(ASTChild&)> F) override;`
- L37 _public prototype_ `virtual bool IsEqual(const ASTOp& OtherUntyped) const override;`
- L38 _public prototype_ `virtual Ptr<ASTOp> Clone(MapChildFuncRef MapChild) const override;`
- L39 _public prototype_ `virtual void Link(FProgram& Program, FLinkerOptions* Options) override;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Mutable` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpAddOverlayMaterial.h` (Private)


#### class `UE::Mutable::Private::ASTOpAddOverlayMaterial`  
`class ASTOpAddOverlayMaterial final : public ASTOp`  
_L15-34_
- inherits: `ASTOp`
- L18 _public member_ `ASTChild Instance;`
- L20 _public member_ `ASTChild Material;`
- L22 _public member_ `FName SlotName;`
- L24 _public prototype_ `ASTOpAddOverlayMaterial();`
- L25 _public prototype_ `ASTOpAddOverlayMaterial(const ASTOpAddOverlayMaterial&) = delete;`
- L28 _public prototype_ `virtual EOpType GetOpType() const override;`
- L29 _public prototype_ `virtual uint32 Hash() const override;`
- L30 _public prototype_ `virtual void ForEachChild(const TFunctionRef<void(ASTChild&)> Func) override;`
- L31 _public prototype_ `virtual bool IsEqual(const ASTOp& OtherUntyped) const override;`
- L32 _public prototype_ `virtual Ptr<ASTOp> Clone(MapChildFuncRef MapChild) const override;`
- L33 _public prototype_ `virtual void Link(FProgram& Program, FLinkerOptions* Options) override;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Mutable` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpAddOverrideMaterial.h` (Private)


#### class `UE::Mutable::Private::ASTOpAddOverrideMaterial`  
`class ASTOpAddOverrideMaterial final : public ASTOp`  
_L15-34_
- inherits: `ASTOp`
- L18 _public member_ `ASTChild Instance;`
- L20 _public member_ `ASTChild Material;`
- L22 _public member_ `FName SlotName;`
- L24 _public prototype_ `ASTOpAddOverrideMaterial();`
- L25 _public prototype_ `ASTOpAddOverrideMaterial(const ASTOpAddOverrideMaterial&) = delete;`
- L28 _public prototype_ `virtual EOpType GetOpType() const override;`
- L29 _public prototype_ `virtual uint32 Hash() const override;`
- L30 _public prototype_ `virtual void ForEachChild(const TFunctionRef<void(ASTChild&)> Func) override;`
- L31 _public prototype_ `virtual bool IsEqual(const ASTOp& OtherUntyped) const override;`
- L32 _public prototype_ `virtual Ptr<ASTOp> Clone(MapChildFuncRef MapChild) const override;`
- L33 _public prototype_ `virtual void Link(FProgram& Program, FLinkerOptions* Options) override;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Mutable` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpAddSkeletalMesh.h` (Private)


#### class `UE::Mutable::Private::ASTOpAddSkeletalMesh`  
`class ASTOpAddSkeletalMesh final : public ASTOp`  
_L17-35_
- inherits: `ASTOp`
- L20 _public member_ `static const EOpType Type = EOpType::IN_ADDSKELETALMESH;`
- L22 _public member_ `ASTChild Instance;`
- L23 _public member_ `ASTChild SkeletalMesh;`
- L25 _public prototype_ `ASTOpAddSkeletalMesh();`
- L26 _public prototype_ `ASTOpAddSkeletalMesh(const ASTOpAddSkeletalMesh&) = delete;`
- L29 _public prototype_ `virtual EOpType GetOpType() const override;`
- L30 _public prototype_ `virtual uint32 Hash() const override;`
- L31 _public prototype_ `virtual void ForEachChild(const TFunctionRef<void(ASTChild&)> F) override;`
- L32 _public prototype_ `virtual bool IsEqual(const ASTOp& OtherUntyped) const override;`
- L33 _public prototype_ `virtual Ptr<ASTOp> Clone(MapChildFuncRef MapChild) const override;`
- L34 _public prototype_ `virtual void Link(FProgram& Program, FLinkerOptions* Options) override;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Mutable` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpBoolAnd.h` (Private)


#### class `UE::Mutable::Private::ASTOpBoolAnd`  
`class ASTOpBoolAnd final : public ASTOp`  
_L16-39_
- inherits: `ASTOp`
- L20 _public member_ `ASTChild A;`
- L21 _public member_ `ASTChild B;`
- L25 _public prototype_ `ASTOpBoolAnd();`
- L26 _public prototype_ `ASTOpBoolAnd(const ASTOpBoolAnd&) = delete;`
- L27 _public prototype_ `~ASTOpBoolAnd();`
- L30 _public function_ `virtual EOpType GetOpType() const override` — ASTOp interface
- L31 _public prototype_ `virtual uint32 Hash() const override;`
- L32 _public prototype_ `virtual bool IsEqual(const ASTOp&) const override;`
- L33 _public prototype_ `virtual Ptr<ASTOp> Clone(MapChildFuncRef) const override;`
- L34 _public prototype_ `virtual void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L35 _public prototype_ `virtual void Link(FProgram&, FLinkerOptions*) override;`
- L36 _public prototype_ `virtual FBoolEvalResult EvaluateBool(ASTOpList& Facts, FEvaluateBoolCache*) const override;`
- L37 _public prototype_ `virtual Ptr<ASTOp> OptimiseSemantic(const FModelOptimizationOptions&, int32 Pass) const override;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Mutable` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpBoolEqualIntConst.h` (Private)


#### class `UE::Mutable::Private::ASTOpBoolEqualIntConst`  
`class ASTOpBoolEqualIntConst final : public ASTOp`  
_L16-37_
- inherits: `ASTOp`
- L20 _public member_ `ASTChild Value;`
- L21 _public member_ `int32 Constant=0;`
- L25 _public prototype_ `ASTOpBoolEqualIntConst();`
- L26 _public prototype_ `ASTOpBoolEqualIntConst(const ASTOpBoolEqualIntConst&) = delete;`
- L30 _public function_ `virtual EOpType GetOpType() const override` — ASTOp interface
- L31 _public prototype_ `virtual uint32 Hash() const override;`
- L32 _public prototype_ `virtual void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L33 _public prototype_ `virtual bool IsEqual(const ASTOp& otherUntyped) const override;`
- L34 _public prototype_ `virtual Ptr<ASTOp> Clone(MapChildFuncRef mapChild) const override;`
- L35 _public prototype_ `virtual void Link(FProgram& program, FLinkerOptions*) override;`
- L36 _public prototype_ `virtual FBoolEvalResult EvaluateBool(ASTOpList& Facts, FEvaluateBoolCache*) const override;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Mutable` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpBoolNot.h` (Private)


#### class `UE::Mutable::Private::ASTOpBoolNot`  
`class ASTOpBoolNot final : public ASTOp`  
_L16-38_
- inherits: `ASTOp`
- L20 _public member_ `ASTChild A;`
- L24 _public prototype_ `ASTOpBoolNot();`
- L25 _public prototype_ `ASTOpBoolNot(const ASTOpBoolNot&) = delete;`
- L26 _public prototype_ `~ASTOpBoolNot();`
- L29 _public function_ `virtual EOpType GetOpType() const override` — ASTOp interface
- L30 _public prototype_ `virtual uint32 Hash() const override;`
- L31 _public prototype_ `virtual bool IsEqual(const ASTOp&) const override;`
- L32 _public prototype_ `virtual Ptr<ASTOp> Clone(MapChildFuncRef) const override;`
- L33 _public prototype_ `virtual void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L34 _public prototype_ `virtual void Link(FProgram&, FLinkerOptions*) override;`
- L35 _public prototype_ `virtual FBoolEvalResult EvaluateBool(ASTOpList& Facts, FEvaluateBoolCache*) const override;`
- L36 _public prototype_ `virtual Ptr<ASTOp> OptimiseSemantic(const FModelOptimizationOptions&, int32 Pass) const override;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Mutable` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpBoolOr.h` (Private)


#### class `UE::Mutable::Private::ASTOpBoolOr`  
`class ASTOpBoolOr final : public ASTOp`  
_L16-39_
- inherits: `ASTOp`
- L20 _public member_ `ASTChild A;`
- L21 _public member_ `ASTChild B;`
- L25 _public prototype_ `ASTOpBoolOr();`
- L26 _public prototype_ `ASTOpBoolOr(const ASTOpBoolOr&) = delete;`
- L27 _public prototype_ `~ASTOpBoolOr();`
- L30 _public function_ `virtual EOpType GetOpType() const override` — ASTOp interface
- L31 _public prototype_ `virtual uint32 Hash() const override;`
- L32 _public prototype_ `virtual bool IsEqual(const ASTOp&) const override;`
- L33 _public prototype_ `virtual Ptr<ASTOp> Clone(MapChildFuncRef) const override;`
- L34 _public prototype_ `virtual void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L35 _public prototype_ `virtual void Link(FProgram&, FLinkerOptions*) override;`
- L36 _public prototype_ `virtual FBoolEvalResult EvaluateBool(ASTOpList& Facts, FEvaluateBoolCache*) const override;`
- L37 _public prototype_ `virtual Ptr<ASTOp> OptimiseSemantic(const FModelOptimizationOptions&, int32 Pass) const override;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Mutable` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpColorArithmetic.h` (Private)


#### class `UE::Mutable::Private::ASTOpColorArithmetic`  
`class ASTOpColorArithmetic final : public ASTOp`  
_L16-37_
- inherits: `ASTOp`
- L20 _public member_ `ASTChild A;`
- L21 _public member_ `ASTChild B;`
- L22 _public member_ `uint16 Operation=0;`
- L26 _public prototype_ `ASTOpColorArithmetic();`
- L27 _public prototype_ `ASTOpColorArithmetic(const ASTOpColorArithmetic&) = delete;`
- L28 _public prototype_ `~ASTOpColorArithmetic();`
- L31 _public function_ `virtual EOpType GetOpType() const override` — ASTOp interface
- L32 _public prototype_ `virtual uint32 Hash() const override;`
- L33 _public prototype_ `virtual bool IsEqual(const ASTOp&) const override;`
- L34 _public prototype_ `virtual Ptr<ASTOp> Clone(MapChildFuncRef) const override;`
- L35 _public prototype_ `virtual void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L36 _public prototype_ `virtual void Link(FProgram&, FLinkerOptions*) override;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Mutable` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpColorFromScalars.h` (Private)


#### class `UE::Mutable::Private::ASTOpColorFromScalars`  
`class ASTOpColorFromScalars final : public ASTOp`  
_L16-34_
- inherits: `ASTOp`
- L20 _public member_ `ASTChild V[MUTABLE_OP_MAX_SWIZZLE_CHANNELS];`
- L24 _public prototype_ `ASTOpColorFromScalars();`
- L25 _public prototype_ `ASTOpColorFromScalars(const ASTOpColorFromScalars&) = delete;`
- L26 _public prototype_ `~ASTOpColorFromScalars();`
- L28 _public function_ `virtual EOpType GetOpType() const override`
- L29 _public prototype_ `virtual uint32 Hash() const override;`
- L30 _public prototype_ `virtual bool IsEqual(const ASTOp& otherUntyped) const override;`
- L31 _public prototype_ `virtual Ptr<ASTOp> Clone(MapChildFuncRef mapChild) const override;`
- L32 _public prototype_ `virtual void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L33 _public prototype_ `virtual void Link(FProgram& program, FLinkerOptions* Options) override;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Mutable` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpColorSampleImage.h` (Private)


#### class `UE::Mutable::Private::ASTOpColorSampleImage`  
`class ASTOpColorSampleImage final : public ASTOp`  
_L16-38_
- inherits: `ASTOp`
- L20 _public member_ `ASTChild Image;`
- L21 _public member_ `ASTChild X;`
- L22 _public member_ `ASTChild Y;`
- L23 _public member_ `uint8 Filter = 0;`
- L27 _public prototype_ `ASTOpColorSampleImage();`
- L28 _public prototype_ `ASTOpColorSampleImage(const ASTOpColorSampleImage&) = delete;`
- L29 _public prototype_ `~ASTOpColorSampleImage();`
- L32 _public function_ `virtual EOpType GetOpType() const override` — ASTOp interface
- L33 _public prototype_ `virtual uint32 Hash() const override;`
- L34 _public prototype_ `virtual bool IsEqual(const ASTOp&) const override;`
- L35 _public prototype_ `virtual Ptr<ASTOp> Clone(MapChildFuncRef) const override;`
- L36 _public prototype_ `virtual void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L37 _public prototype_ `virtual void Link(FProgram&, FLinkerOptions*) override;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Mutable` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpColorSwizzle.h` (Private)


#### class `UE::Mutable::Private::ASTOpColorSwizzle`  
`class ASTOpColorSwizzle final : public ASTOp`  
_L16-37_
- inherits: `ASTOp`
- L20 _public member_ `ASTChild Sources[MUTABLE_OP_MAX_SWIZZLE_CHANNELS];`
- L22 _public member_ `uint8 SourceChannels[MUTABLE_OP_MAX_SWIZZLE_CHANNELS] = { 0,0,0,0 };`
- L26 _public prototype_ `ASTOpColorSwizzle();`
- L27 _public prototype_ `ASTOpColorSwizzle(const ASTOpColorSwizzle&) = delete;`
- L28 _public prototype_ `~ASTOpColorSwizzle();`
- L30 _public function_ `virtual EOpType GetOpType() const override`
- L31 _public prototype_ `virtual uint32 Hash() const override;`
- L32 _public prototype_ `virtual bool IsEqual(const ASTOp& otherUntyped) const override;`
- L33 _public prototype_ `virtual Ptr<ASTOp> Clone(MapChildFuncRef mapChild) const override;`
- L34 _public prototype_ `virtual void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L35 _public prototype_ `virtual void Link(FProgram& program, FLinkerOptions* Options) override;`
- L36 _public prototype_ `virtual Ptr<ASTOp> OptimiseSemantic(const FModelOptimizationOptions&, int32 Pass) const override;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Mutable` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpColorToSRGB.h` (Private)


#### class `UE::Mutable::Private::ASTOpColorToSRGB`  
`class ASTOpColorToSRGB final : public ASTOp`  
_L14-32_
- inherits: `ASTOp`
- L18 _public member_ `ASTChild Color;`
- L22 _public prototype_ `ASTOpColorToSRGB();`
- L23 _public prototype_ `ASTOpColorToSRGB(const ASTOpColorToSRGB&) = delete;`
- L24 _public prototype_ `~ASTOpColorToSRGB();`
- L26 _public function_ `virtual EOpType GetOpType() const override`
- L27 _public prototype_ `virtual uint32 Hash() const override;`
- L28 _public prototype_ `virtual bool IsEqual(const ASTOp& OtherUntyped) const override;`
- L29 _public prototype_ `virtual Ptr<ASTOp> Clone(MapChildFuncRef MapChild) const override;`
- L30 _public prototype_ `virtual void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L31 _public prototype_ `virtual void Link(FProgram& Program, FLinkerOptions* Options) override;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Mutable` (scope `UE`)
- L10 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpComponentAdd.h` (Private)


#### class `UE::Mutable::Private::ASTOpComponentAdd`  
`class ASTOpComponentAdd final : public ASTOp`  
_L19-39_
- inherits: `ASTOp`
- L22 _public member_ `static const EOpType Type = EOpType::IN_ADDCOMPONENT;`
- L24 _public member_ `ASTChild Instance;`
- L25 _public member_ `ASTChild Value;`
- L26 _public member_ `FComponentId ExternalId = INDEX_NONE;`
- L28 _public prototype_ `ASTOpComponentAdd();`
- L29 _public prototype_ `ASTOpComponentAdd(const ASTOpComponentAdd&) = delete;`
- L30 _public prototype_ `~ASTOpComponentAdd();`
- L32 _public prototype_ `virtual EOpType GetOpType() const override;`
- L34 _public prototype_ `virtual void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L35 _public prototype_ `virtual bool IsEqual(const ASTOp& OtherUntyped) const override;`
- L36 _public prototype_ `virtual Ptr<ASTOp> Clone(MapChildFuncRef MapChild) const override;`
- L37 _public prototype_ `virtual uint32 Hash() const override;`
- L38 _public prototype_ `virtual void Link(FProgram& Program, FLinkerOptions* Options) override;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Mutable` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpConditional.h` (Private)


#### class `UE::Mutable::Private::ASTOpConditional`  
`class ASTOpConditional final : public ASTOp`  
_L19-54_
- inherits: `ASTOp`
- L24 _public member_ `EOpType type = EOpType::NONE;` — Type of switch
- L27 _public member_ `ASTChild condition;` — Boolean expression
- L30 _public member_ `ASTChild yes;` — Branches
- L31 _public member_ `ASTChild no;`
- L35 _public prototype_ `ASTOpConditional();`
- L36 _public prototype_ `ASTOpConditional(const ASTOpConditional&) = delete;`
- L39 _public function_ `virtual EOpType GetOpType() const override`
- L40 _public prototype_ `virtual bool IsEqual(const ASTOp& otherUntyped) const override;`
- L41 _public prototype_ `virtual Ptr<ASTOp> Clone(MapChildFuncRef mapChild) const override;`
- L42 _public prototype_ `virtual uint32 Hash() const override;`
- L43 _public prototype_ `virtual void Assert() override;`
- L44 _public prototype_ `virtual void ForEachChild(const TFunctionRef<void(ASTChild&)> f) override;`
- L45 _public prototype_ `virtual void Link(FProgram& program, FLinkerOptions* Options) override;`
- L46 _public prototype_ `virtual FImageDesc GetImageDesc(bool returnBestOption, class FGetImageDescContext* context) const override;`
- L47 _public prototype_ `virtual void GetLayoutBlockSize(int32* pBlockX, int32* pBlockY) override;`
- L48 _public prototype_ `virtual void GetBlockLayoutSize(uint64 BlockId, int32* pBlockX, int32* pBlockY, FBlockLayoutSizeCache* cache) override;`
- L49 _public prototype_ `virtual Ptr<ASTOp> OptimiseSemantic(const FModelOptimizationOptions&, int32 Pass) const override;`
- L50 _public prototype_ `virtual bool GetNonBlackRect(FImageRect& maskUsage) const override;`
- L51 _public prototype_ `virtual Ptr<ImageSizeExpression> GetImageSizeExpression() const override;`
- L52 _public function_ `virtual bool IsConditional() const override`
- L53 _public prototype_ `virtual FSourceDataDescriptor GetSourceDataDescriptor(FGetSourceDataDescriptorContext*) const override;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Mutable` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpConstantBool.h` (Private)


#### class `UE::Mutable::Private::ASTOpConstantBool`  
`class ASTOpConstantBool final : public ASTOp`  
_L15-34_
- inherits: `ASTOp`
- L19 _public member_ `bool bValue = true;`
- L23 _public prototype_ `ASTOpConstantBool(bool bValue = true);`
- L25 _public function_ `virtual EOpType GetOpType() const override`
- L26 _public prototype_ `virtual uint32 Hash() const override;`
- L27 _public prototype_ `virtual void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L28 _public prototype_ `virtual bool IsEqual(const ASTOp&) const override;`
- L29 _public prototype_ `virtual Ptr<ASTOp> Clone(MapChildFuncRef) const override;`
- L30 _public prototype_ `virtual void Link(FProgram&, FLinkerOptions*) override;`
- L31 _public prototype_ `virtual FBoolEvalResult EvaluateBool(ASTOpList& Facts, FEvaluateBoolCache*) const override;`
- L33 _public prototype_ `static bool IsConstantBool(const Ptr<ASTOp>& Op, bool& bOutValue);`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Mutable` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpConstantColor.h` (Private)


#### class `UE::Mutable::Private::ASTOpConstantColor`  
`class ASTOpConstantColor final : public ASTOp`  
_L15-30_
- inherits: `ASTOp`
- L19 _public member_ `FVector4f Value = FVector4f(0.0f,0.0f,0.0f,0.0f);`
- L23 _public function_ `virtual EOpType GetOpType() const override`
- L24 _public prototype_ `virtual uint32 Hash() const override;`
- L25 _public prototype_ `virtual void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L26 _public prototype_ `virtual bool IsEqual(const ASTOp&) const override;`
- L27 _public prototype_ `virtual Ptr<ASTOp> Clone(MapChildFuncRef) const override;`
- L28 _public prototype_ `virtual void Link(FProgram&, FLinkerOptions*) override;`
- L29 _public prototype_ `virtual bool IsColorConstant(FVector4f& OutColor) const override;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Mutable` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpConstantExtensionData.h` (Private)


#### class `UE::Mutable::Private::ASTOpConstantExtensionData`  
`class ASTOpConstantExtensionData final : public ASTOp`  
_L18-30_
- inherits: `ASTOp`
- desc: A constant ExtensionData.
- L21 _public member_ `PASSTHROUGH_ID ExtensionDataId = PASSTHROUGH_ID_INVALID;`
- L24 _public function_ `EOpType GetOpType() const override` — ASTOp interface
- L25 _public function_ `void ForEachChild(const TFunctionRef<void(ASTChild&)>) override`
- L26 _public prototype_ `bool IsEqual(const ASTOp& OtherUntyped) const override;`
- L27 _public prototype_ `Ptr<ASTOp> Clone(MapChildFuncRef MapChild) const override;`
- L28 _public prototype_ `uint32 Hash() const override;`
- L29 _public prototype_ `void Link(FProgram& Program, FLinkerOptions*) override;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Mutable` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpConstantInt.h` (Private)


#### class `UE::Mutable::Private::ASTOpConstantInt`  
`class ASTOpConstantInt final : public ASTOp`  
_L15-32_
- inherits: `ASTOp`
- L19 _public member_ `int32 Value = 0;`
- L23 _public prototype_ `ASTOpConstantInt(int Value = 0);`
- L25 _public function_ `virtual EOpType GetOpType() const override`
- L26 _public prototype_ `virtual uint32 Hash() const override;`
- L27 _public prototype_ `virtual void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L28 _public prototype_ `virtual bool IsEqual(const ASTOp&) const override;`
- L29 _public prototype_ `virtual Ptr<ASTOp> Clone(MapChildFuncRef) const override;`
- L30 _public prototype_ `virtual void Link(FProgram&, FLinkerOptions*) override;`
- L31 _public prototype_ `virtual int32 EvaluateInt(ASTOpList& Facts, bool& bOutUnknown) const override;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Mutable` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpConstantMatrix.h` (Private)


#### class `UE::Mutable::Private::ASTOpConstantMatrix`  
`class ASTOpConstantMatrix final : public ASTOp`  
_L19-36_
- inherits: `ASTOp`
- L24 _public member_ `FMatrix44f value;`
- L28 _public prototype_ `ASTOpConstantMatrix(FMatrix44f value = FMatrix44f::Identity);`
- L30 _public function_ `EOpType GetOpType() const override`
- L31 _public prototype_ `uint32 Hash() const override;`
- L32 _public function_ `void ForEachChild(const TFunctionRef<void(ASTChild&)>) override`
- L33 _public prototype_ `bool IsEqual(const ASTOp& otherUntyped) const override;`
- L34 _public prototype_ `Ptr<ASTOp> Clone(MapChildFuncRef mapChild) const override;`
- L35 _public prototype_ `void Link(FProgram& program, FLinkerOptions* Options) override;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Mutable` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpConstantProjector.h` (Private)


#### class `UE::Mutable::Private::ASTOpConstantProjector`  
`class ASTOpConstantProjector final : public ASTOp`  
_L20-35_
- inherits: `ASTOp`
- L25 _public member_ `FProjector value;`
- L29 _public function_ `EOpType GetOpType() const override`
- L30 _public prototype_ `uint32 Hash() const override;`
- L31 _public prototype_ `void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L32 _public prototype_ `bool IsEqual(const ASTOp& otherUntyped) const override;`
- L33 _public prototype_ `Ptr<ASTOp> Clone(MapChildFuncRef mapChild) const override;`
- L34 _public prototype_ `void Link(FProgram& program, FLinkerOptions*) override;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Mutable` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpConstantResource.h` (Private)


#### class `UE::Mutable::Private::ASTOpConstantResource`  
`class ASTOpConstantResource final : public ASTOp`  
_L18-73_
- inherits: `ASTOp`
- desc: A constant mesh, image, volume or layout.
- L23 _private member_ `TManagedPtr<const FResource> Value;`
- L26 _private member_ `uint64 ValueHash = 0;` — Value hash
- L29 _private member_ `bool bLinkedAndNull = false;` — We tried to link already but the result is a null op.
- L34 _public member_ `EOpType Type;` — Type of constant
- L37 _public member_ `FSourceDataDescriptor SourceDataDescriptor;` — Source data descriptor.
- L40 _public member_ `TMap<FParameterKey, ASTChild> ImageOperations;` — Image Parameters are evaluated at runtime.
- L49 _public prototype_ `uint32 GetValueHash() const;` — Get a hash of the stored value.
- L52 _public prototype_ `TManagedPtr<const FResource> GetValue() const;` — Get a pointer to the stored value.
- L55 _public prototype_ `void SetValue(const TManagedPtr<const FResource>& Value);` — Set the value to store in this op.
- L59 _public function_ `virtual EOpType GetOpType() const override` — ASTOp interface
- L60 _public prototype_ `virtual void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L61 _public prototype_ `virtual bool IsEqual(const ASTOp& otherUntyped) const override;`
- L62 _public prototype_ `virtual Ptr<ASTOp> Clone(MapChildFuncRef mapChild) const override;`
- L63 _public prototype_ `virtual uint32 Hash() const override;`
- L64 _public prototype_ `virtual void Link(FProgram& program, FLinkerOptions*) override;`
- L65 _public prototype_ `virtual FImageDesc GetImageDesc(bool, class FGetImageDescContext*) const override;`
- L66 _public prototype_ `virtual void GetBlockLayoutSize(uint64 BlockId, int32* pBlockX, int32* pBlockY, FBlockLayoutSizeCache* cache) override;`
- L67 _public prototype_ `virtual void GetLayoutBlockSize(int32* pBlockX, int32* pBlockY) override;`
- L68 _public prototype_ `virtual bool GetNonBlackRect(FImageRect& maskUsage) const override;`
- L69 _public prototype_ `virtual bool IsImagePlainConstant(FVector4f& color) const override;`
- L70 _public prototype_ `virtual Ptr<ImageSizeExpression> GetImageSizeExpression() const override;`
- L71 _public prototype_ `virtual FSourceDataDescriptor GetSourceDataDescriptor(FGetSourceDataDescriptorContext*) const override;`
- L72 _public prototype_ `virtual EClosedMeshTest IsClosedMesh(TMap<const ASTOp*, EClosedMeshTest>* Cache) const override;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Mutable` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpConstantScalar.h` (Private)


#### class `UE::Mutable::Private::ASTOpConstantScalar`  
`class ASTOpConstantScalar final : public ASTOp`  
_L15-32_
- inherits: `ASTOp`
- L19 _public member_ `float Value = 0.0f;`
- L23 _public prototype_ `ASTOpConstantScalar(float Value = 0.0f);`
- L25 _public function_ `virtual EOpType GetOpType() const override`
- L26 _public prototype_ `virtual uint32 Hash() const override;`
- L27 _public prototype_ `virtual void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L28 _public prototype_ `virtual bool IsEqual(const ASTOp&) const override;`
- L29 _public prototype_ `virtual Ptr<ASTOp> Clone(MapChildFuncRef) const override;`
- L30 _public prototype_ `virtual void Link(FProgram&, FLinkerOptions*) override;`
- L31 _public prototype_ `virtual int32 EvaluateInt(ASTOpList& Facts, bool& bOutUnknown) const override;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Mutable` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpConstantString.h` (Private)


#### class `UE::Mutable::Private::ASTOpConstantString`  
`class ASTOpConstantString final : public ASTOp`  
_L19-32_
- inherits: `ASTOp`
- L23 _public member_ `FString value;`
- L26 _public function_ `EOpType GetOpType() const override`
- L27 _public prototype_ `uint32 Hash() const override;`
- L28 _public prototype_ `void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L29 _public prototype_ `bool IsEqual(const ASTOp& otherUntyped) const override;`
- L30 _public prototype_ `Ptr<ASTOp> Clone(MapChildFuncRef mapChild) const override;`
- L31 _public prototype_ `void Link(FProgram& program, FLinkerOptions* Options) override;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Mutable` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpEntry.h` (Private)


#### class `UE::Mutable::Private::ASTOpEntry`  
`class ASTOpEntry final : public ASTOp`  
_L15-31_
- inherits: `ASTOp`
- L18 _public member_ `ASTChild A;`
- L20 _public prototype_ `ASTOpEntry();`
- L21 _public prototype_ `ASTOpEntry(const ASTOpEntry&) = delete;`
- L22 _public prototype_ `~ASTOpEntry();`
- L25 _public prototype_ `virtual EOpType GetOpType() const override;` — ASTOp interface
- L26 _public prototype_ `virtual uint32 Hash() const override;`
- L27 _public prototype_ `virtual bool IsEqual(const ASTOp&) const override;`
- L28 _public prototype_ `virtual Ptr<ASTOp> Clone(MapChildFuncRef) const override;`
- L29 _public prototype_ `virtual void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L30 _public prototype_ `virtual void Link(FProgram&, FLinkerOptions*) override;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Mutable` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpExternal.h` (Private)


#### class `UE::Mutable::Private::ASTOpExternal`  
`class ASTOpExternal final : public ASTOp`  
_L16-31_
- inherits: `ASTOp`
- L19 _public prototype_ `virtual EOpType GetOpType() const override;`
- L20 _public prototype_ `virtual uint32 Hash() const override;`
- L21 _public prototype_ `virtual void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L22 _public prototype_ `virtual bool IsEqual(const ASTOp&) const override;`
- L23 _public prototype_ `virtual Ptr<ASTOp> Clone(MapChildFuncRef) const override;`
- L24 _public prototype_ `virtual void Link(FProgram&, FLinkerOptions*) override;`
- L26 _public member_ `EOpType Type = EOpType::NONE;`
- L28 _public member_ `FInstancedStruct OperationInstancedStruct;`
- L30 _public member_ `TArray<ASTChild> Inputs;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Mutable` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpImageBinarize.h` (Private)


#### class `UE::Mutable::Private::ASTOpImageBinarize`  
`class ASTOpImageBinarize final : public ASTOp`  
_L17-40_
- inherits: `ASTOp`
- L21 _public member_ `ASTChild Base;`
- L22 _public member_ `ASTChild Threshold;`
- L26 _public prototype_ `ASTOpImageBinarize();`
- L27 _public prototype_ `ASTOpImageBinarize(const ASTOpImageBinarize&) = delete;`
- L28 _public prototype_ `~ASTOpImageBinarize();`
- L30 _public function_ `virtual EOpType GetOpType() const override`
- L31 _public prototype_ `virtual uint32 Hash() const override;`
- L32 _public prototype_ `virtual bool IsEqual(const ASTOp&) const override;`
- L33 _public prototype_ `virtual Ptr<ASTOp> Clone(MapChildFuncRef) const override;`
- L34 _public prototype_ `virtual void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L35 _public prototype_ `virtual void Link(FProgram&, FLinkerOptions*) override;`
- L36 _public prototype_ `virtual FImageDesc GetImageDesc(bool bReturnBestOption, FGetImageDescContext*) const override;`
- L37 _public prototype_ `virtual Ptr<ImageSizeExpression> GetImageSizeExpression() const override;`
- L38 _public prototype_ `virtual FSourceDataDescriptor GetSourceDataDescriptor(FGetSourceDataDescriptorContext*) const override;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Mutable` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpImageBlankLayout.h` (Private)


#### class `UE::Mutable::Private::ASTOpImageBlankLayout`  
`class ASTOpImageBlankLayout final : public ASTOp`  
_L17-51_
- inherits: `ASTOp`
- L21 _public member_ `ASTChild Layout;`
- L24 _public member_ `UE::Math::TIntVector2<uint16> BlockSize;` — Size of a layout block in pixels.
- L26 _public member_ `EImageFormat Format = EImageFormat::None;`
- L29 _public member_ `uint8 GenerateMipmaps = 0;` — If true, generate mipmaps.
- L32 _public member_ `uint8 MipmapCount = 0;` — Mipmaps to generate if mipmaps are to be generated. 0 means all.
- L36 _public prototype_ `ASTOpImageBlankLayout();`
- L37 _public prototype_ `ASTOpImageBlankLayout(const ASTOpImageBlankLayout&) = delete;`
- L38 _public prototype_ `~ASTOpImageBlankLayout();`
- L40 _public function_ `virtual EOpType GetOpType() const override`
- L41 _public prototype_ `virtual uint32 Hash() const override;`
- L42 _public prototype_ `virtual bool IsEqual(const ASTOp&) const override;`
- L43 _public prototype_ `virtual Ptr<ASTOp> Clone(MapChildFuncRef ) const override;`
- L44 _public prototype_ `virtual void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L45 _public prototype_ `virtual void Link(FProgram&, FLinkerOptions*) override;`
- L46 _public prototype_ `virtual FImageDesc GetImageDesc(bool bReturnBestOption, FGetImageDescContext*) const override;`
- L47 _public prototype_ `virtual Ptr<ImageSizeExpression> GetImageSizeExpression() const override;`
- L48 _public prototype_ `virtual void GetLayoutBlockSize(int* OutBlockX, int* OutBlockY) override;`
- L49 _public prototype_ `virtual bool IsImagePlainConstant(FVector4f& color) const override;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Mutable` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpImageColorMap.h` (Private)


#### class `UE::Mutable::Private::ASTOpImageColorMap`  
`class ASTOpImageColorMap final : public ASTOp`  
_L17-42_
- inherits: `ASTOp`
- L21 _public member_ `ASTChild Base;`
- L22 _public member_ `ASTChild Mask;`
- L23 _public member_ `ASTChild Map;`
- L27 _public prototype_ `ASTOpImageColorMap();`
- L28 _public prototype_ `ASTOpImageColorMap(const ASTOpImageColorMap&) = delete;`
- L29 _public prototype_ `~ASTOpImageColorMap();`
- L31 _public function_ `virtual EOpType GetOpType() const override`
- L32 _public prototype_ `virtual uint32 Hash() const override;`
- L33 _public prototype_ `virtual bool IsEqual(const ASTOp&) const override;`
- L34 _public prototype_ `virtual Ptr<ASTOp> Clone(MapChildFuncRef) const override;`
- L35 _public prototype_ `virtual void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L36 _public prototype_ `virtual void Link(FProgram&, FLinkerOptions*) override;`
- L37 _public prototype_ `virtual FImageDesc GetImageDesc(bool bReturnBestOption, FGetImageDescContext*) const override;`
- L38 _public prototype_ `virtual Ptr<ImageSizeExpression> GetImageSizeExpression() const override;`
- L39 _public prototype_ `virtual bool IsImagePlainConstant(FVector4f& color) const override;`
- L40 _public prototype_ `virtual FSourceDataDescriptor GetSourceDataDescriptor(FGetSourceDataDescriptorContext*) const override;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Mutable` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpImageCompose.h` (Private)


#### class `UE::Mutable::Private::ASTOpImageCompose`  
`class ASTOpImageCompose final : public ASTOp`  
_L16-46_
- inherits: `ASTOp`
- L20 _public member_ `ASTChild Layout;`
- L21 _public member_ `ASTChild Base;`
- L22 _public member_ `ASTChild BlockImage;`
- L23 _public member_ `ASTChild Mask;`
- L24 _public member_ `uint64 BlockId=0;`
- L28 _public prototype_ `ASTOpImageCompose();`
- L29 _public prototype_ `ASTOpImageCompose(const ASTOpImageCompose&) = delete;`
- L30 _public prototype_ `~ASTOpImageCompose();`
- L32 _public function_ `virtual EOpType GetOpType() const override`
- L33 _public prototype_ `virtual uint32 Hash() const override;`
- L34 _public prototype_ `virtual bool IsEqual(const ASTOp& otherUntyped) const override;`
- L35 _public prototype_ `virtual Ptr<ASTOp> Clone(MapChildFuncRef mapChild) const override;`
- L36 _public prototype_ `virtual void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L37 _public prototype_ `virtual void Link(FProgram& program, FLinkerOptions* Options) override;`
- L39 _public prototype_ `virtual Ptr<ASTOp> OptimiseSemantic(const FModelOptimizationOptions& options, int32 Pass) const override;` — TODO: virtual Ptr<ASTOp> OptimiseSink(const FModelOptimizationOptions& options, FOptimizeSinkContext& context) const override;
- L40 _public prototype_ `virtual FImageDesc GetImageDesc(bool returnBestOption, FGetImageDescContext* context) const override;`
- L41 _public prototype_ `virtual void GetLayoutBlockSize(int32* OutBlockX, int32* OutBlockY) override;`
- L42 _public prototype_ `virtual bool IsImagePlainConstant(FVector4f& OutColor) const override;`
- L43 _public prototype_ `virtual Ptr<ImageSizeExpression> GetImageSizeExpression() const override;`
- L44 _public prototype_ `virtual FSourceDataDescriptor GetSourceDataDescriptor(FGetSourceDataDescriptorContext*) const override;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Mutable` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpImageConform.h` (Private)


#### class `UE::Mutable::Private::ASTOpImageConform`  
`class ASTOpImageConform final : public ASTOp`  
_L16-43_
- inherits: `ASTOp`
- L20 _public member_ `ASTChild Source;`
- L21 _public member_ `FImageDesc ConformDescriptor;`
- L25 _public prototype_ `ASTOpImageConform();`
- L26 _public prototype_ `ASTOpImageConform(const ASTOpImageConform&) = delete;`
- L27 _public prototype_ `~ASTOpImageConform();`
- L29 _public function_ `virtual EOpType GetOpType() const override`
- L30 _public prototype_ `virtual uint32 Hash() const override;`
- L31 _public prototype_ `virtual bool IsEqual(const ASTOp& otherUntyped) const override;`
- L32 _public prototype_ `virtual Ptr<ASTOp> Clone(MapChildFuncRef mapChild) const override;`
- L33 _public prototype_ `virtual void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L34 _public prototype_ `virtual void Link(FProgram& program, FLinkerOptions* Options) override;`
- L37 _public prototype_ `virtual FImageDesc GetImageDesc(bool returnBestOption, FGetImageDescContext* context) const override;` — virtual Ptr<ASTOp> OptimiseSemantic(const FModelOptimizationOptions& options, int32 Pass) const override; virtual Ptr<ASTOp> OptimiseSink(const FModelOptimizationOptions& options, FOptimizeSinkContext& context) const override;
- L38 _public prototype_ `virtual void GetLayoutBlockSize(int* pBlockX, int* pBlockY) override;`
- L39 _public prototype_ `virtual bool IsImagePlainConstant(FVector4f& color) const override;`
- L40 _public prototype_ `virtual Ptr<ImageSizeExpression> GetImageSizeExpression() const override;`
- L41 _public prototype_ `virtual FSourceDataDescriptor GetSourceDataDescriptor(FGetSourceDataDescriptorContext*) const override;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Mutable` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpImageCrop.h` (Private)


#### class `UE::Mutable::Private::ASTOpImageCrop`  
`class ASTOpImageCrop final : public ASTOp`  
_L17-45_
- inherits: `ASTOp`
- L21 _public member_ `ASTChild Source;`
- L22 _public member_ `UE::Math::TIntVector2<uint16> Min = UE::Math::TIntVector2<uint16>(0, 0);`
- L23 _public member_ `UE::Math::TIntVector2<uint16> Size = UE::Math::TIntVector2<uint16>(0, 0);`
- L27 _public prototype_ `ASTOpImageCrop();`
- L28 _public prototype_ `ASTOpImageCrop(const ASTOpImageCrop&) = delete;`
- L29 _public prototype_ `~ASTOpImageCrop();`
- L31 _public function_ `virtual EOpType GetOpType() const override`
- L32 _public prototype_ `virtual uint32 Hash() const override;`
- L33 _public prototype_ `virtual bool IsEqual(const ASTOp&) const override;`
- L34 _public prototype_ `virtual Ptr<ASTOp> Clone(MapChildFuncRef ) const override;`
- L35 _public prototype_ `virtual void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L36 _public prototype_ `virtual void Link(FProgram&, FLinkerOptions*) override;`
- L37 _public prototype_ `virtual FImageDesc GetImageDesc(bool bReturnBestOption, FGetImageDescContext*) const override;`
- L38 _public prototype_ `virtual Ptr<ImageSizeExpression> GetImageSizeExpression() const override;`
- L39 _public prototype_ `virtual void GetLayoutBlockSize(int* OutBlockX, int* OutBlockY) override;`
- L41 _public prototype_ `virtual Ptr<ASTOp> OptimiseSemantic(const FModelOptimizationOptions&, int32 Pass) const override;` — TODO: virtual bool IsImagePlainConstant(FVector4f& color) const override;
- L42 _public prototype_ `virtual Ptr<ASTOp> OptimiseSink(const FModelOptimizationOptions&, FOptimizeSinkContext&) const override;`
- L43 _public prototype_ `virtual FSourceDataDescriptor GetSourceDataDescriptor(FGetSourceDataDescriptorContext*) const override;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Mutable` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpImageDisplace.h` (Private)


#### class `UE::Mutable::Private::ASTOpImageDisplace`  
`class ASTOpImageDisplace final : public ASTOp`  
_L17-41_
- inherits: `ASTOp`
- L21 _public member_ `ASTChild Source;`
- L22 _public member_ `ASTChild DisplacementMap;`
- L26 _public prototype_ `ASTOpImageDisplace();`
- L27 _public prototype_ `ASTOpImageDisplace(const ASTOpImageDisplace&) = delete;`
- L28 _public prototype_ `~ASTOpImageDisplace();`
- L30 _public function_ `virtual EOpType GetOpType() const override`
- L31 _public prototype_ `virtual uint32 Hash() const override;`
- L32 _public prototype_ `virtual bool IsEqual(const ASTOp&) const override;`
- L33 _public prototype_ `virtual Ptr<ASTOp> Clone(MapChildFuncRef) const override;`
- L34 _public prototype_ `virtual void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L35 _public prototype_ `virtual void Link(FProgram&, FLinkerOptions*) override;`
- L36 _public prototype_ `virtual FImageDesc GetImageDesc(bool bReturnBestOption, FGetImageDescContext*) const override;`
- L37 _public prototype_ `virtual Ptr<ImageSizeExpression> GetImageSizeExpression() const override;`
- L38 _public prototype_ `virtual FSourceDataDescriptor GetSourceDataDescriptor(FGetSourceDataDescriptorContext*) const override;`
- L39 _public prototype_ `virtual Ptr<ASTOp> OptimiseSink(const FModelOptimizationOptions&, FOptimizeSinkContext&) const override;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Mutable` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpImageInterpolate.h` (Private)


#### class `UE::Mutable::Private::ASTOpImageInterpolate`  
`class ASTOpImageInterpolate final : public ASTOp`  
_L16-40_
- inherits: `ASTOp`
- L20 _public member_ `ASTChild Factor;`
- L21 _public member_ `ASTChild Targets[MUTABLE_OP_MAX_INTERPOLATE_COUNT];`
- L25 _public prototype_ `ASTOpImageInterpolate();`
- L26 _public prototype_ `ASTOpImageInterpolate(const ASTOpImageInterpolate&) = delete;`
- L27 _public prototype_ `~ASTOpImageInterpolate();`
- L29 _public function_ `virtual EOpType GetOpType() const override`
- L30 _public prototype_ `virtual uint32 Hash() const override;`
- L31 _public prototype_ `virtual bool IsEqual(const ASTOp&) const override;`
- L32 _public prototype_ `virtual Ptr<ASTOp> Clone(MapChildFuncRef) const override;`
- L33 _public prototype_ `virtual void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L34 _public prototype_ `virtual void Link(FProgram&, FLinkerOptions*) override;`
- L35 _public prototype_ `virtual FImageDesc GetImageDesc(bool bReturnBestOption, FGetImageDescContext*) const override;`
- L36 _public prototype_ `virtual void GetLayoutBlockSize(int32* OutBlockX, int32* OutBlockY) override;`
- L37 _public prototype_ `virtual Ptr<ImageSizeExpression> GetImageSizeExpression() const override;`
- L38 _public prototype_ `virtual FSourceDataDescriptor GetSourceDataDescriptor(FGetSourceDataDescriptorContext*) const override;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Mutable` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpImageInvert.h` (Private)


#### class `UE::Mutable::Private::ASTOpImageInvert`  
`class ASTOpImageInvert final : public ASTOp`  
_L17-40_
- inherits: `ASTOp`
- L21 _public member_ `ASTChild Base;`
- L25 _public prototype_ `ASTOpImageInvert();`
- L26 _public prototype_ `ASTOpImageInvert(const ASTOpImageInvert&) = delete;`
- L27 _public prototype_ `~ASTOpImageInvert();`
- L29 _public function_ `virtual EOpType GetOpType() const override`
- L30 _public prototype_ `virtual uint32 Hash() const override;`
- L31 _public prototype_ `virtual bool IsEqual(const ASTOp&) const override;`
- L32 _public prototype_ `virtual Ptr<ASTOp> Clone(MapChildFuncRef) const override;`
- L33 _public prototype_ `virtual void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L34 _public prototype_ `virtual void Link(FProgram&, FLinkerOptions*) override;`
- L35 _public prototype_ `virtual FImageDesc GetImageDesc(bool bReturnBestOption, FGetImageDescContext*) const override;`
- L36 _public prototype_ `virtual Ptr<ImageSizeExpression> GetImageSizeExpression() const override;`
- L37 _public prototype_ `virtual bool IsImagePlainConstant(FVector4f& color) const override;`
- L38 _public prototype_ `virtual FSourceDataDescriptor GetSourceDataDescriptor(FGetSourceDataDescriptorContext*) const override;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Mutable` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpImageLayer.h` (Private)


#### class `UE::Mutable::Private::ASTOpImageLayer`  
`class ASTOpImageLayer final : public ASTOp`  
_L20-59_
- inherits: `ASTOp`
- L24 _public member_ `ASTChild base;`
- L25 _public member_ `ASTChild blend;`
- L26 _public member_ `ASTChild mask;`
- L29 _public member_ `EBlendType blendType = EBlendType::BT_NONE;` — Blend type used for the color channels.
- L32 _public member_ `EBlendType blendTypeAlpha = EBlendType::BT_NONE;` — Blend type used for the alpha channel if any.
- L35 _public member_ `uint8 BlendAlphaSourceChannel = 0;` — Channel to use from the source color argument to apply blendTypeAlpha, if any.
- L38 _public member_ `uint8 Flags = 0;` — See ImageLayerArgs::Flags .
- L42 _public prototype_ `ASTOpImageLayer();`
- L43 _public prototype_ `ASTOpImageLayer(const ASTOpImageLayer&) = delete;`
- L44 _public prototype_ `~ASTOpImageLayer();`
- L46 _public function_ `virtual EOpType GetOpType() const override`
- L47 _public prototype_ `virtual uint32 Hash() const override;`
- L48 _public prototype_ `virtual bool IsEqual(const ASTOp& otherUntyped) const override;`
- L49 _public prototype_ `virtual Ptr<ASTOp> Clone(MapChildFuncRef mapChild) const override;`
- L50 _public prototype_ `virtual void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L51 _public prototype_ `virtual void Link(FProgram& program, FLinkerOptions*) override;`
- L52 _public prototype_ `virtual FImageDesc GetImageDesc(bool returnBestOption, FGetImageDescContext*) const override;`
- L53 _public prototype_ `virtual void GetLayoutBlockSize(int* pBlockX, int* pBlockY) override;`
- L54 _public prototype_ `virtual Ptr<ImageSizeExpression> GetImageSizeExpression() const override;`
- L55 _public prototype_ `virtual Ptr<ASTOp> OptimiseSemantic(const FModelOptimizationOptions&, int32 Pass) const override;`
- L56 _public prototype_ `virtual Ptr<ASTOp> OptimiseSink(const FModelOptimizationOptions&, FOptimizeSinkContext&) const override;`
- L57 _public prototype_ `virtual FSourceDataDescriptor GetSourceDataDescriptor(FGetSourceDataDescriptorContext*) const override;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Mutable` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpImageLayerColor.h` (Private)


#### class `UE::Mutable::Private::ASTOpImageLayerColor`  
`class ASTOpImageLayerColor final : public ASTOp`  
_L20-59_
- inherits: `ASTOp`
- L24 _public member_ `ASTChild base;`
- L25 _public member_ `ASTChild color;`
- L26 _public member_ `ASTChild mask;`
- L29 _public member_ `EBlendType blendType = EBlendType::BT_NONE;` — Blend type used for the color channels.
- L32 _public member_ `EBlendType blendTypeAlpha = EBlendType::BT_NONE;` — Blend type used for the alpha channel if any. This will be applied to the alpha with the channel BlendAlphaSourceChannel of the color.
- L35 _public member_ `uint8 BlendAlphaSourceChannel = 0;` — Channel to use from the source color argument to apply blendTypeAlpha, if any.
- L38 _public member_ `uint8 Flags = 0;` — See ImageLayerArgs::Flags .
- L42 _public prototype_ `ASTOpImageLayerColor();`
- L43 _public prototype_ `ASTOpImageLayerColor(const ASTOpImageLayerColor&) = delete;`
- L44 _public prototype_ `~ASTOpImageLayerColor();`
- L46 _public function_ `virtual EOpType GetOpType() const override`
- L47 _public prototype_ `virtual uint32 Hash() const override;`
- L48 _public prototype_ `virtual bool IsEqual(const ASTOp& otherUntyped) const override;`
- L49 _public prototype_ `virtual Ptr<ASTOp> Clone(MapChildFuncRef mapChild) const override;`
- L50 _public prototype_ `virtual void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L51 _public prototype_ `virtual void Link(FProgram& program, FLinkerOptions* Options) override;`
- L52 _public prototype_ `virtual FImageDesc GetImageDesc(bool returnBestOption, FGetImageDescContext* context) const override;`
- L53 _public prototype_ `virtual void GetLayoutBlockSize(int* pBlockX, int* pBlockY) override;`
- L54 _public prototype_ `virtual Ptr<ImageSizeExpression> GetImageSizeExpression() const override;`
- L55 _public prototype_ `virtual Ptr<ASTOp> OptimiseSemantic(const FModelOptimizationOptions& options, int32 Pass) const override;`
- L56 _public prototype_ `virtual Ptr<ASTOp> OptimiseSink(const FModelOptimizationOptions&, FOptimizeSinkContext&) const override;`
- L57 _public prototype_ `virtual FSourceDataDescriptor GetSourceDataDescriptor(FGetSourceDataDescriptorContext*) const override;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Mutable` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpImageLuminance.h` (Private)


#### class `UE::Mutable::Private::ASTOpImageLuminance`  
`class ASTOpImageLuminance final : public ASTOp`  
_L17-40_
- inherits: `ASTOp`
- L21 _public member_ `ASTChild Base;`
- L25 _public prototype_ `ASTOpImageLuminance();`
- L26 _public prototype_ `ASTOpImageLuminance(const ASTOpImageLuminance&) = delete;`
- L27 _public prototype_ `~ASTOpImageLuminance();`
- L29 _public function_ `virtual EOpType GetOpType() const override`
- L30 _public prototype_ `virtual uint32 Hash() const override;`
- L31 _public prototype_ `virtual bool IsEqual(const ASTOp&) const override;`
- L32 _public prototype_ `virtual Ptr<ASTOp> Clone(MapChildFuncRef) const override;`
- L33 _public prototype_ `virtual void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L34 _public prototype_ `virtual void Link(FProgram&, FLinkerOptions*) override;`
- L35 _public prototype_ `virtual FImageDesc GetImageDesc(bool bReturnBestOption, FGetImageDescContext*) const override;`
- L36 _public prototype_ `virtual Ptr<ImageSizeExpression> GetImageSizeExpression() const override;`
- L37 _public prototype_ `virtual bool IsImagePlainConstant(FVector4f& color) const override;`
- L38 _public prototype_ `virtual FSourceDataDescriptor GetSourceDataDescriptor(FGetSourceDataDescriptorContext*) const override;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Mutable` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpImageMakeGrowMap.h` (Private)


#### class `UE::Mutable::Private::ASTOpImageMakeGrowMap`  
`class ASTOpImageMakeGrowMap final : public ASTOp`  
_L16-43_
- inherits: `ASTOp`
- L20 _public member_ `ASTChild Mask;`
- L22 _public member_ `uint32 Border = 0;`
- L26 _public prototype_ `ASTOpImageMakeGrowMap();`
- L27 _public prototype_ `ASTOpImageMakeGrowMap(const ASTOpImageMakeGrowMap&) = delete;`
- L28 _public prototype_ `~ASTOpImageMakeGrowMap();`
- L30 _public function_ `virtual EOpType GetOpType() const override`
- L31 _public prototype_ `virtual uint32 Hash() const override;`
- L32 _public prototype_ `virtual bool IsEqual(const ASTOp& otherUntyped) const override;`
- L33 _public prototype_ `virtual Ptr<ASTOp> Clone(MapChildFuncRef mapChild) const override;`
- L34 _public prototype_ `virtual void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L35 _public prototype_ `virtual void Link(FProgram& program, FLinkerOptions* Options) override;`
- L36 _public prototype_ `virtual Ptr<ASTOp> OptimiseSink(const FModelOptimizationOptions& options, FOptimizeSinkContext& context) const override;`
- L37 _public prototype_ `virtual FImageDesc GetImageDesc(bool returnBestOption, FGetImageDescContext* context) const override;`
- L38 _public prototype_ `virtual void GetLayoutBlockSize(int* pBlockX, int* pBlockY) override;`
- L39 _public prototype_ `virtual bool IsImagePlainConstant(FVector4f& color) const override;`
- L40 _public prototype_ `virtual Ptr<ImageSizeExpression> GetImageSizeExpression() const override;`
- L41 _public prototype_ `virtual FSourceDataDescriptor GetSourceDataDescriptor(FGetSourceDataDescriptorContext*) const override;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Mutable` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpImageMipmap.h` (Private)


#### class `UE::Mutable::Private::ASTOpImageMipmap`  
`class ASTOpImageMipmap final : public ASTOp`  
_L16-58_
- inherits: `ASTOp`
- L20 _public member_ `ASTChild Source;`
- L22 _public member_ `uint8 Levels = 0;`
- L25 _public member_ `uint8 BlockLevels = 0;` — Number of mipmaps that can be generated for a single layout block.
- L29 _public member_ `bool bOnlyTail = false;` — This is true if this operation is supposed to build only the tail mipmaps. It is used during the code optimisation phase, and to validate the code.
- L32 _public member_ `bool bPreventSplitTail = false;` — If this is enabled, at optimize time, the mip operation will not be split in top and bottom mip (for compose tails).
- L35 _public member_ `EAddressMode AddressMode = EAddressMode::None;` — Mipmap generation settings.
- L36 _public member_ `EMipmapFilterType FilterType = EMipmapFilterType::SimpleAverage;`
- L40 _public prototype_ `ASTOpImageMipmap();`
- L41 _public prototype_ `ASTOpImageMipmap(const ASTOpImageMipmap&) = delete;`
- L42 _public prototype_ `~ASTOpImageMipmap();`
- L44 _public function_ `virtual EOpType GetOpType() const override`
- L45 _public prototype_ `virtual uint32 Hash() const override;`
- L46 _public prototype_ `virtual bool IsEqual(const ASTOp& otherUntyped) const override;`
- L47 _public prototype_ `virtual Ptr<ASTOp> Clone(MapChildFuncRef mapChild) const override;`
- L48 _public prototype_ `virtual void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L49 _public prototype_ `virtual void Link(FProgram& program, FLinkerOptions* Options) override;`
- L50 _public prototype_ `virtual UE::Mutable::Private::Ptr<ASTOp> OptimiseSemantic(const FModelOptimizationOptions& options, int32 Pass) const override;`
- L51 _public prototype_ `virtual Ptr<ASTOp> OptimiseSink(const FModelOptimizationOptions& options, FOptimizeSinkContext& context) const override;`
- L52 _public prototype_ `virtual FImageDesc GetImageDesc(bool returnBestOption, FGetImageDescContext* context) const override;`
- L53 _public prototype_ `virtual void GetLayoutBlockSize(int* pBlockX, int* pBlockY) override;`
- L54 _public prototype_ `virtual bool IsImagePlainConstant(FVector4f& color) const override;`
- L55 _public prototype_ `virtual Ptr<ImageSizeExpression> GetImageSizeExpression() const override;`
- L56 _public prototype_ `virtual FSourceDataDescriptor GetSourceDataDescriptor(FGetSourceDataDescriptorContext*) const override;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Mutable` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpImageMultiCompose.h` (Private)


#### class `UE::Mutable::Private::ASTOpImageMultiCompose`  
`class ASTOpImageMultiCompose final : public ASTOp`  
_L16-53_
- inherits: `ASTOp`
- L20 _public member_ `ASTChild Layout;`
- L21 _public member_ `ASTChild Base;`
- L22 _public member_ `ASTChild SourceLayout;`
- L23 _public member_ `ASTChild SourceImage;`
- L27 _public member_ `uint16 LayoutBlockSizeInPixelsX = 0;` — Used to find the size of the image to create.
- L28 _public member_ `uint16 LayoutBlockSizeInPixelsY = 0;`
- L30 _public member_ `uint16 SourceSizeX = 0;`
- L31 _public member_ `uint16 SourceSizeY = 0;`
- L35 _public prototype_ `ASTOpImageMultiCompose();`
- L36 _public prototype_ `ASTOpImageMultiCompose(const ASTOpImageMultiCompose&) = delete;`
- L37 _public prototype_ `~ASTOpImageMultiCompose();`
- L39 _public function_ `virtual EOpType GetOpType() const override`
- L40 _public prototype_ `virtual uint32 Hash() const override;`
- L41 _public prototype_ `virtual bool IsEqual(const ASTOp& otherUntyped) const override;`
- L42 _public prototype_ `virtual Ptr<ASTOp> Clone(MapChildFuncRef mapChild) const override;`
- L43 _public prototype_ `virtual void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L44 _public prototype_ `virtual void Link(FProgram& program, FLinkerOptions* Options) override;`
- L47 _public prototype_ `virtual FImageDesc GetImageDesc(bool returnBestOption, FGetImageDescContext* context) const override;` — virtual Ptr<ASTOp> OptimiseSink(const FModelOptimizationOptions& options, FOptimizeSinkContext& context) const override; virtual Ptr<ASTOp> OptimiseSemantic(const FModelOptimizationOptions& options, int32 Pass) const override;
- L48 _public prototype_ `virtual void GetLayoutBlockSize(int32* OutBlockX, int32* OutBlockY) override;`
- L49 _public prototype_ `virtual bool IsImagePlainConstant(FVector4f& OutColor) const override;`
- L50 _public prototype_ `virtual Ptr<ImageSizeExpression> GetImageSizeExpression() const override;`
- L51 _public prototype_ `virtual FSourceDataDescriptor GetSourceDataDescriptor(FGetSourceDataDescriptorContext*) const override;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Mutable` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpImageMultiLayer.h` (Private)


#### class `UE::Mutable::Private::ASTOpImageMultiLayer`  
`class ASTOpImageMultiLayer final : public ASTOp`  
_L20-56_
- inherits: `ASTOp`
- L24 _public member_ `ASTChild base;`
- L25 _public member_ `ASTChild blend;`
- L26 _public member_ `ASTChild mask;`
- L27 _public member_ `FRangeData range;`
- L30 _public member_ `EBlendType blendType = EBlendType::BT_NONE;` — Blend type used for the color channels.
- L33 _public member_ `EBlendType blendTypeAlpha = EBlendType::BT_NONE;` — Blend type used for the alpha channel if any.
- L36 _public member_ `uint8 BlendAlphaSourceChannel = 0;` — Channel to use from the source color argument to apply blendTypeAlpha, if any.
- L39 _public member_ `bool bUseMaskFromBlended = false;` — If true, use the alpha channel of the blended image as mask. Mask should be null.
- L43 _public prototype_ `ASTOpImageMultiLayer();`
- L44 _public prototype_ `ASTOpImageMultiLayer(const ASTOpImageMultiLayer&) = delete;`
- L45 _public prototype_ `~ASTOpImageMultiLayer();`
- L47 _public function_ `EOpType GetOpType() const override`
- L48 _public prototype_ `uint32 Hash() const override;`
- L49 _public prototype_ `bool IsEqual(const ASTOp& otherUntyped) const override;`
- L50 _public prototype_ `Ptr<ASTOp> Clone(MapChildFuncRef mapChild) const override;`
- L51 _public prototype_ `void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L52 _public prototype_ `void Link(FProgram& program, FLinkerOptions* Options) override;`
- L53 _public prototype_ `FImageDesc GetImageDesc(bool returnBestOption, FGetImageDescContext* context) const override;`
- L54 _public prototype_ `void GetLayoutBlockSize(int* pBlockX, int* pBlockY) override;`
- L55 _public prototype_ `Ptr<ImageSizeExpression> GetImageSizeExpression() const override;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Mutable` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpImageNormalComposite.h` (Private)


#### class `UE::Mutable::Private::ASTOpImageNormalComposite`  
`class ASTOpImageNormalComposite final : public ASTOp`  
_L16-40_
- inherits: `ASTOp`
- L19 _public member_ `ASTChild Base;`
- L20 _public member_ `ASTChild Normal;`
- L21 _public member_ `ECompositeImageMode Mode;`
- L22 _public member_ `float Power;`
- L26 _public prototype_ `ASTOpImageNormalComposite();`
- L27 _public prototype_ `ASTOpImageNormalComposite(const ASTOpImageNormalComposite&) = delete;`
- L28 _public prototype_ `~ASTOpImageNormalComposite();`
- L30 _public function_ `EOpType GetOpType() const override`
- L31 _public prototype_ `uint32 Hash() const override;`
- L32 _public prototype_ `bool IsEqual(const ASTOp& otherUntyped) const override;`
- L33 _public prototype_ `Ptr<ASTOp> Clone(MapChildFuncRef mapChild) const override;`
- L34 _public prototype_ `void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L35 _public prototype_ `void Link(FProgram& program, FLinkerOptions* Options) override;`
- L36 _public prototype_ `FImageDesc GetImageDesc(bool returnBestOption, FGetImageDescContext* context) const override;`
- L37 _public prototype_ `void GetLayoutBlockSize(int* pBlockX, int* pBlockY) override;`
- L38 _public prototype_ `Ptr<ImageSizeExpression> GetImageSizeExpression() const override;`
- L39 _public prototype_ `virtual FSourceDataDescriptor GetSourceDataDescriptor(FGetSourceDataDescriptorContext*) const override;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Mutable` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpImageParameterConvert.h` (Private)


#### class `UE::Mutable::Private::ASTOpImageParameterConvert`  
`class ASTOpImageParameterConvert final : public ASTOp`  
_L17-39_
- inherits: `ASTOp`
- L20 _public member_ `EOpType Type = EOpType::IM_PARAMETER_CONVERT;`
- L22 _public member_ `ASTChild ImageParameter;`
- L24 _public member_ `FImageDesc ImageDescriptor;`
- L26 _public member_ `int32 LinkedParameterIndex = -1;`
- L28 _public prototype_ `ASTOpImageParameterConvert();`
- L32 _public prototype_ `virtual EOpType GetOpType() const override;` — ASTOp interface.
- L33 _public prototype_ `virtual uint32 Hash() const override;`
- L34 _public prototype_ `virtual void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L35 _public prototype_ `virtual bool IsEqual(const ASTOp&) const override;`
- L36 _public prototype_ `virtual Ptr<ASTOp> Clone(MapChildFuncRef ) const override;`
- L37 _public prototype_ `virtual void Link(FProgram&, FLinkerOptions*) override;`
- L38 _public prototype_ `virtual FImageDesc GetImageDesc(bool, FGetImageDescContext*) const override;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Mutable` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpImagePatch.h` (Private)


#### class `UE::Mutable::Private::ASTOpImagePatch`  
`class ASTOpImagePatch final : public ASTOp`  
_L17-43_
- inherits: `ASTOp`
- L21 _public member_ `ASTChild base;`
- L22 _public member_ `ASTChild patch;`
- L23 _public member_ `UE::Math::TIntVector2<uint16> location = UE::Math::TIntVector2<uint16>(0, 0);`
- L27 _public prototype_ `ASTOpImagePatch();`
- L28 _public prototype_ `ASTOpImagePatch(const ASTOpImagePatch&) = delete;`
- L29 _public prototype_ `~ASTOpImagePatch();`
- L31 _public function_ `virtual EOpType GetOpType() const override`
- L32 _public prototype_ `virtual uint32 Hash() const override;`
- L33 _public prototype_ `virtual bool IsEqual(const ASTOp&) const override;`
- L34 _public prototype_ `virtual Ptr<ASTOp> Clone(MapChildFuncRef) const override;`
- L35 _public prototype_ `virtual void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L36 _public prototype_ `virtual void Link(FProgram&, FLinkerOptions*) override;`
- L37 _public prototype_ `virtual FImageDesc GetImageDesc(bool bReturnBestOption, FGetImageDescContext*) const override;`
- L38 _public prototype_ `virtual Ptr<ImageSizeExpression> GetImageSizeExpression() const override;`
- L39 _public prototype_ `virtual void GetLayoutBlockSize(int32* OutBlockX, int32* OutBlockY) override;`
- L41 _public prototype_ `virtual FSourceDataDescriptor GetSourceDataDescriptor(FGetSourceDataDescriptorContext*) const override;` — TODO: virtual bool IsImagePlainConstant(FVector4f& color) const override;

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Mutable` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpImagePixelFormat.h` (Private)


#### class `UE::Mutable::Private::ASTOpImagePixelFormat`  
`class ASTOpImagePixelFormat final : public ASTOp`  
_L16-44_
- inherits: `ASTOp`
- L20 _public member_ `ASTChild Source;`
- L21 _public member_ `EImageFormat Format = EImageFormat::None;`
- L22 _public member_ `EImageFormat FormatIfAlpha = EImageFormat::None;`
- L26 _public prototype_ `ASTOpImagePixelFormat();`
- L27 _public prototype_ `ASTOpImagePixelFormat(const ASTOpImagePixelFormat&) = delete;`
- L28 _public prototype_ `~ASTOpImagePixelFormat();`
- L30 _public function_ `virtual EOpType GetOpType() const override`
- L31 _public prototype_ `virtual uint32 Hash() const override;`
- L32 _public prototype_ `virtual bool IsEqual(const ASTOp& otherUntyped) const override;`
- L33 _public prototype_ `virtual Ptr<ASTOp> Clone(MapChildFuncRef mapChild) const override;`
- L34 _public prototype_ `virtual void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L35 _public prototype_ `virtual void Link(FProgram& program, FLinkerOptions* Options) override;`
- L36 _public prototype_ `virtual Ptr<ASTOp> OptimiseSemantic(const FModelOptimizationOptions& options, int32 Pass) const override;`
- L37 _public prototype_ `virtual Ptr<ASTOp> OptimiseSink(const FModelOptimizationOptions& options, FOptimizeSinkContext& context) const override;`
- L38 _public prototype_ `virtual FImageDesc GetImageDesc(bool returnBestOption, FGetImageDescContext* context) const override;`
- L39 _public prototype_ `virtual void GetLayoutBlockSize(int* pBlockX, int* pBlockY) override;`
- L40 _public prototype_ `virtual bool IsImagePlainConstant(FVector4f& color) const override;`
- L41 _public prototype_ `virtual Ptr<ImageSizeExpression> GetImageSizeExpression() const override;`
- L42 _public prototype_ `virtual FSourceDataDescriptor GetSourceDataDescriptor(FGetSourceDataDescriptorContext*) const override;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Mutable` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpImagePlainColor.h` (Private)


#### class `UE::Mutable::Private::ASTOpImagePlainColor`  
`class ASTOpImagePlainColor final : public ASTOp`  
_L17-44_
- inherits: `ASTOp`
- L21 _public member_ `ASTChild Color;`
- L22 _public member_ `EImageFormat Format = EImageFormat::None;`
- L23 _public member_ `UE::Math::TIntVector2<uint16> Size = UE::Math::TIntVector2<uint16>(0, 0);`
- L24 _public member_ `uint8 LODs=1;`
- L28 _public prototype_ `ASTOpImagePlainColor();`
- L29 _public prototype_ `ASTOpImagePlainColor(const ASTOpImagePlainColor&) = delete;`
- L30 _public prototype_ `~ASTOpImagePlainColor();`
- L32 _public function_ `virtual EOpType GetOpType() const override`
- L33 _public prototype_ `virtual uint32 Hash() const override;`
- L34 _public prototype_ `virtual bool IsEqual(const ASTOp&) const override;`
- L35 _public prototype_ `virtual Ptr<ASTOp> Clone(MapChildFuncRef ) const override;`
- L36 _public prototype_ `virtual void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L37 _public prototype_ `virtual void Link(FProgram&, FLinkerOptions*) override;`
- L38 _public prototype_ `virtual FImageDesc GetImageDesc(bool bReturnBestOption, FGetImageDescContext*) const override;`
- L39 _public prototype_ `virtual Ptr<ImageSizeExpression> GetImageSizeExpression() const override;`
- L40 _public prototype_ `virtual void GetLayoutBlockSize(int32* OutBlockX, int32* OutBlockY) override;`
- L41 _public prototype_ `virtual bool IsImagePlainConstant(FVector4f& OutColor) const override;`
- L42 _public prototype_ `virtual FSourceDataDescriptor GetSourceDataDescriptor(FGetSourceDataDescriptorContext*) const override;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Mutable` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpImageRasterMesh.h` (Private)


#### class `UE::Mutable::Private::ASTOpImageRasterMesh`  
`class ASTOpImageRasterMesh final : public ASTOp`  
_L16-65_
- inherits: `ASTOp`
- L20 _public member_ `ASTChild mesh;`
- L21 _public member_ `ASTChild image;`
- L22 _public member_ `ASTChild angleFadeProperties;`
- L23 _public member_ `ASTChild mask;`
- L24 _public member_ `ASTChild projector;`
- L27 _public member_ `uint64 BlockId;` — If layouts are used, this can indicate a single layout block that we want to raster.
- L28 _public member_ `int8 LayoutIndex;`
- L31 _public member_ `uint16 SizeX, SizeY;` — Size of the image to generate by rasterization of the mesh.
- L31 _public member_ `uint16 SizeX, SizeY;` — Size of the image to generate by rasterization of the mesh.
- L34 _public member_ `uint16 SourceSizeX, SourceSizeY;` — Expected size of the image that we want to project.
- L34 _public member_ `uint16 SourceSizeX, SourceSizeY;` — Expected size of the image that we want to project.
- L39 _public member_ `uint16 CropMinX, CropMinY;` — Sub-rect to raster, ignoring all the rest. Only valid if any UncroppedSizeX is greater than 0.
- L39 _public member_ `uint16 CropMinX, CropMinY;` — Sub-rect to raster, ignoring all the rest. Only valid if any UncroppedSizeX is greater than 0.
- L40 _public member_ `uint16 UncroppedSizeX, UncroppedSizeY;`
- L40 _public member_ `uint16 UncroppedSizeX, UncroppedSizeY;`
- L42 _public member_ `uint8 bIsRGBFadingEnabled : 1;`
- L43 _public member_ `uint8 bIsAlphaFadingEnabled : 1;`
- L44 _public member_ `ESamplingMethod SamplingMethod;`
- L45 _public member_ `EMinFilterMethod MinFilterMethod;`
- L49 _public prototype_ `ASTOpImageRasterMesh();`
- L50 _public prototype_ `ASTOpImageRasterMesh(const ASTOpImageRasterMesh&) = delete;`
- L51 _public prototype_ `~ASTOpImageRasterMesh();`
- L53 _public function_ `virtual EOpType GetOpType() const override`
- L54 _public prototype_ `virtual uint32 Hash() const override;`
- L55 _public prototype_ `virtual bool IsEqual(const ASTOp& otherUntyped) const override;`
- L56 _public prototype_ `virtual Ptr<ASTOp> Clone(MapChildFuncRef mapChild) const override;`
- L57 _public prototype_ `virtual void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L58 _public prototype_ `virtual void Link(FProgram& program, FLinkerOptions* Options) override;`
- L59 _public prototype_ `virtual FImageDesc GetImageDesc(bool returnBestOption, FGetImageDescContext* context) const override;`
- L60 _public prototype_ `virtual Ptr<ImageSizeExpression> GetImageSizeExpression() const override;`
- L61 _public prototype_ `virtual Ptr<ASTOp> OptimiseSemantic(const FModelOptimizationOptions& options, int32 Pass) const override;`
- L62 _public prototype_ `virtual Ptr<ASTOp> OptimiseSink(const FModelOptimizationOptions&, FOptimizeSinkContext&) const override;`
- L63 _public prototype_ `virtual FSourceDataDescriptor GetSourceDataDescriptor(FGetSourceDataDescriptorContext*) const override;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Mutable` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpImageResize.h` (Private)


#### class `UE::Mutable::Private::ASTOpImageResize`  
`class ASTOpImageResize final : public ASTOp`  
_L17-44_
- inherits: `ASTOp`
- L21 _public member_ `ASTChild Source;`
- L22 _public member_ `UE::Math::TIntVector2<uint16> Size = UE::Math::TIntVector2<uint16>(0, 0);`
- L26 _public prototype_ `ASTOpImageResize();`
- L27 _public prototype_ `ASTOpImageResize(const ASTOpImageResize&) = delete;`
- L28 _public prototype_ `~ASTOpImageResize();`
- L30 _public function_ `virtual EOpType GetOpType() const override`
- L31 _public prototype_ `virtual uint32 Hash() const override;`
- L32 _public prototype_ `virtual bool IsEqual(const ASTOp&) const override;`
- L33 _public prototype_ `virtual Ptr<ASTOp> Clone(MapChildFuncRef) const override;`
- L34 _public prototype_ `virtual void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L35 _public prototype_ `virtual void Link(FProgram&, FLinkerOptions*) override;`
- L36 _public prototype_ `virtual FImageDesc GetImageDesc(bool bReturnBestOption, FGetImageDescContext*) const override;`
- L37 _public prototype_ `virtual Ptr<ImageSizeExpression> GetImageSizeExpression() const override;`
- L38 _public prototype_ `virtual void GetLayoutBlockSize(int32* OutBlockX, int32* OutBlockY) override;`
- L39 _public prototype_ `virtual bool IsImagePlainConstant(FVector4f& color) const override;`
- L40 _public prototype_ `virtual Ptr<ASTOp> OptimiseSize() const override;`
- L41 _public prototype_ `virtual Ptr<ASTOp> OptimiseSemantic(const FModelOptimizationOptions&, int32 Pass) const override;`
- L42 _public prototype_ `virtual FSourceDataDescriptor GetSourceDataDescriptor(FGetSourceDataDescriptorContext*) const override;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Mutable` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpImageResizeLike.h` (Private)


#### class `UE::Mutable::Private::ASTOpImageResizeLike`  
`class ASTOpImageResizeLike final : public ASTOp`  
_L17-42_
- inherits: `ASTOp`
- L21 _public member_ `ASTChild Source;`
- L22 _public member_ `ASTChild SizeSource;`
- L26 _public prototype_ `ASTOpImageResizeLike();`
- L27 _public prototype_ `ASTOpImageResizeLike(const ASTOpImageResizeLike&) = delete;`
- L28 _public prototype_ `~ASTOpImageResizeLike();`
- L30 _public function_ `virtual EOpType GetOpType() const override`
- L31 _public prototype_ `virtual uint32 Hash() const override;`
- L32 _public prototype_ `virtual bool IsEqual(const ASTOp&) const override;`
- L33 _public prototype_ `virtual Ptr<ASTOp> Clone(MapChildFuncRef) const override;`
- L34 _public prototype_ `virtual void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L35 _public prototype_ `virtual void Link(FProgram&, FLinkerOptions*) override;`
- L36 _public prototype_ `virtual FImageDesc GetImageDesc(bool bReturnBestOption, FGetImageDescContext*) const override;`
- L37 _public prototype_ `virtual Ptr<ImageSizeExpression> GetImageSizeExpression() const override;`
- L38 _public prototype_ `virtual bool IsImagePlainConstant(FVector4f& color) const override;`
- L39 _public prototype_ `virtual Ptr<ASTOp> OptimiseSize() const override;`
- L40 _public prototype_ `virtual FSourceDataDescriptor GetSourceDataDescriptor(FGetSourceDataDescriptorContext*) const override;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Mutable` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpImageResizeRel.h` (Private)


#### class `UE::Mutable::Private::ASTOpImageResizeRel`  
`class ASTOpImageResizeRel final : public ASTOp`  
_L17-44_
- inherits: `ASTOp`
- L21 _public member_ `ASTChild Source;`
- L22 _public member_ `FVector2f Factor = FVector2f(1.0f, 1.0f);`
- L26 _public prototype_ `ASTOpImageResizeRel();`
- L27 _public prototype_ `ASTOpImageResizeRel(const ASTOpImageResizeRel&) = delete;`
- L28 _public prototype_ `~ASTOpImageResizeRel();`
- L30 _public function_ `virtual EOpType GetOpType() const override`
- L31 _public prototype_ `virtual uint32 Hash() const override;`
- L32 _public prototype_ `virtual bool IsEqual(const ASTOp&) const override;`
- L33 _public prototype_ `virtual Ptr<ASTOp> Clone(MapChildFuncRef) const override;`
- L34 _public prototype_ `virtual void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L35 _public prototype_ `virtual void Link(FProgram&, FLinkerOptions*) override;`
- L36 _public prototype_ `virtual FImageDesc GetImageDesc(bool bReturnBestOption, FGetImageDescContext*) const override;`
- L37 _public prototype_ `virtual Ptr<ImageSizeExpression> GetImageSizeExpression() const override;`
- L38 _public prototype_ `virtual void GetLayoutBlockSize(int32* OutBlockX, int32* OutBlockY) override;`
- L39 _public prototype_ `virtual bool IsImagePlainConstant(FVector4f& color) const override;`
- L40 _public prototype_ `virtual Ptr<ASTOp> OptimiseSize() const override;`
- L41 _public prototype_ `virtual Ptr<ASTOp> OptimiseSemantic(const FModelOptimizationOptions&, int32 Pass) const override;`
- L42 _public prototype_ `virtual FSourceDataDescriptor GetSourceDataDescriptor(FGetSourceDataDescriptorContext*) const override;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Mutable` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpImageSaturate.h` (Private)


#### class `UE::Mutable::Private::ASTOpImageSaturate`  
`class ASTOpImageSaturate final : public ASTOp`  
_L17-41_
- inherits: `ASTOp`
- L21 _public member_ `ASTChild Base;`
- L22 _public member_ `ASTChild Factor;`
- L26 _public prototype_ `ASTOpImageSaturate();`
- L27 _public prototype_ `ASTOpImageSaturate(const ASTOpImageSaturate&) = delete;`
- L28 _public prototype_ `~ASTOpImageSaturate();`
- L30 _public function_ `virtual EOpType GetOpType() const override`
- L31 _public prototype_ `virtual uint32 Hash() const override;`
- L32 _public prototype_ `virtual bool IsEqual(const ASTOp&) const override;`
- L33 _public prototype_ `virtual Ptr<ASTOp> Clone(MapChildFuncRef) const override;`
- L34 _public prototype_ `virtual void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L35 _public prototype_ `virtual void Link(FProgram&, FLinkerOptions*) override;`
- L36 _public prototype_ `virtual FImageDesc GetImageDesc(bool bReturnBestOption, FGetImageDescContext*) const override;`
- L37 _public prototype_ `virtual Ptr<ImageSizeExpression> GetImageSizeExpression() const override;`
- L38 _public prototype_ `virtual bool IsImagePlainConstant(FVector4f& color) const override;`
- L39 _public prototype_ `virtual FSourceDataDescriptor GetSourceDataDescriptor(FGetSourceDataDescriptorContext*) const override;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Mutable` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpImageSwizzle.h` (Private)


#### class `UE::Mutable::Private::ASTOpImageSwizzle`  
`class ASTOpImageSwizzle final : public ASTOp`  
_L16-46_
- inherits: `ASTOp`
- L20 _public member_ `ASTChild Sources[MUTABLE_OP_MAX_SWIZZLE_CHANNELS];`
- L22 _public member_ `uint8 SourceChannels[MUTABLE_OP_MAX_SWIZZLE_CHANNELS] = { 0,0,0,0 };`
- L24 _public member_ `EImageFormat Format = EImageFormat::None;`
- L28 _public prototype_ `ASTOpImageSwizzle();`
- L29 _public prototype_ `ASTOpImageSwizzle(const ASTOpImageSwizzle&) = delete;`
- L30 _public prototype_ `~ASTOpImageSwizzle();`
- L32 _public function_ `virtual EOpType GetOpType() const override`
- L33 _public prototype_ `virtual uint32 Hash() const override;`
- L34 _public prototype_ `virtual bool IsEqual(const ASTOp&) const override;`
- L35 _public prototype_ `virtual Ptr<ASTOp> Clone(MapChildFuncRef) const override;`
- L36 _public prototype_ `virtual void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L37 _public prototype_ `virtual void Link(FProgram&, FLinkerOptions*) override;`
- L38 _public prototype_ `virtual Ptr<ASTOp> OptimiseSemantic(const FModelOptimizationOptions&, int32 Pass) const override;`
- L39 _public prototype_ `virtual Ptr<ASTOp> OptimiseSink(const FModelOptimizationOptions&, FOptimizeSinkContext&) const override;`
- L40 _public prototype_ `virtual FImageDesc GetImageDesc(bool bReturnBestOption, FGetImageDescContext*) const override;`
- L41 _public prototype_ `virtual void GetLayoutBlockSize(int32* OutBlockX, int32* OutBlockY) override;`
- L42 _public prototype_ `virtual bool IsImagePlainConstant(FVector4f& OutColor) const override;`
- L43 _public prototype_ `virtual Ptr<ImageSizeExpression> GetImageSizeExpression() const override;`
- L44 _public prototype_ `virtual FSourceDataDescriptor GetSourceDataDescriptor(FGetSourceDataDescriptorContext*) const override;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Mutable` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpImageTransform.h` (Private)


#### class `UE::Mutable::Private::ASTOpImageTransform`  
`class ASTOpImageTransform final : public ASTOp`  
_L20-56_
- inherits: `ASTOp`
- L24 _public member_ `ASTChild Base;`
- L25 _public member_ `ASTChild OffsetX;`
- L26 _public member_ `ASTChild OffsetY;`
- L27 _public member_ `ASTChild ScaleX;`
- L28 _public member_ `ASTChild ScaleY;`
- L29 _public member_ `ASTChild Rotation;`
- L31 _public member_ `uint16 SizeX = 0;`
- L32 _public member_ `uint16 SizeY = 0;`
- L34 _public member_ `uint16 SourceSizeX = 0;`
- L35 _public member_ `uint16 SourceSizeY = 0;`
- L37 _public member_ `EAddressMode AddressMode = EAddressMode::Wrap;`
- L38 _public member_ `bool bKeepAspectRatio = false;`
- L42 _public prototype_ `ASTOpImageTransform();`
- L43 _public prototype_ `ASTOpImageTransform(const ASTOpImageTransform&) = delete;`
- L44 _public prototype_ `~ASTOpImageTransform();`
- L46 _public function_ `virtual EOpType GetOpType() const override`
- L47 _public prototype_ `virtual uint32 Hash() const override;`
- L48 _public prototype_ `virtual bool IsEqual(const ASTOp& OtherUntyped) const override;`
- L49 _public prototype_ `virtual Ptr<ASTOp> Clone(MapChildFuncRef MapChild) const override;`
- L50 _public prototype_ `virtual void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L51 _public prototype_ `virtual void Link(FProgram& Program, FLinkerOptions* Options) override;`
- L52 _public prototype_ `virtual FImageDesc GetImageDesc(bool bReturnBestOption, FGetImageDescContext* Context) const override;`
- L53 _public prototype_ `virtual void GetLayoutBlockSize(int* pBlockX, int* pBlockY) override;`
- L54 _public prototype_ `virtual Ptr<ImageSizeExpression> GetImageSizeExpression() const override;`
- L55 _public prototype_ `virtual FSourceDataDescriptor GetSourceDataDescriptor(FGetSourceDataDescriptorContext*) const override;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Mutable` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpLODNew.h` (Private)


#### class `UE::Mutable::Private::ASTOpLODNew`  
`class ASTOpLODNew final : public ASTOp`  
_L15-35_
- inherits: `ASTOp`
- L18 _public member_ `TArray<ASTChild> Meshes;`
- L20 _public member_ `TArray<FName> MaterialSlotName;`
- L22 _public member_ `TArray<uint32> MeshIds;`
- L23 _public member_ `TArray<uint32> MeshExternalIds;`
- L25 _public prototype_ `ASTOpLODNew();`
- L26 _public prototype_ `ASTOpLODNew(const ASTOpLODNew&) = delete;`
- L29 _public prototype_ `virtual EOpType GetOpType() const override;`
- L30 _public prototype_ `virtual uint32 Hash() const override;`
- L31 _public prototype_ `virtual void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L32 _public prototype_ `virtual bool IsEqual(const ASTOp& OtherUntyped) const override;`
- L33 _public prototype_ `virtual Ptr<ASTOp> Clone(MapChildFuncRef MapChild) const override;`
- L34 _public prototype_ `virtual void Link(FProgram& Program, FLinkerOptions* Options) override;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Mutable` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpLayoutFromMesh.h` (Private)


#### class `UE::Mutable::Private::ASTOpLayoutFromMesh`  
`class ASTOpLayoutFromMesh final : public ASTOp`  
_L15-37_
- inherits: `ASTOp`
- L19 _public member_ `ASTChild Mesh;`
- L20 _public member_ `uint8_t LayoutIndex = 0;`
- L24 _public prototype_ `ASTOpLayoutFromMesh();`
- L25 _public prototype_ `ASTOpLayoutFromMesh(const ASTOpLayoutFromMesh&) = delete;`
- L26 _public prototype_ `~ASTOpLayoutFromMesh();`
- L28 _public function_ `EOpType GetOpType() const override`
- L29 _public prototype_ `uint32 Hash() const override;`
- L30 _public prototype_ `bool IsEqual(const ASTOp& otherUntyped) const override;`
- L31 _public prototype_ `Ptr<ASTOp> Clone(MapChildFuncRef mapChild) const override;`
- L32 _public prototype_ `void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L33 _public prototype_ `void Link(FProgram& program, FLinkerOptions* Options) override;`
- L34 _public prototype_ `Ptr<ASTOp> OptimiseSink(const FModelOptimizationOptions& options, FOptimizeSinkContext& context) const override;`
- L35 _public prototype_ `void GetBlockLayoutSize(uint64 BlockId, int32* pBlockX, int32* pBlockY, FBlockLayoutSizeCache* cache) override;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Mutable` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpLayoutMerge.h` (Private)


#### class `UE::Mutable::Private::ASTOpLayoutMerge`  
`class ASTOpLayoutMerge final : public ASTOp`  
_L15-36_
- inherits: `ASTOp`
- L19 _public member_ `ASTChild Base;`
- L20 _public member_ `ASTChild Added;`
- L24 _public prototype_ `ASTOpLayoutMerge();`
- L25 _public prototype_ `ASTOpLayoutMerge(const ASTOpLayoutMerge&) = delete;`
- L26 _public prototype_ `~ASTOpLayoutMerge();`
- L28 _public function_ `EOpType GetOpType() const override`
- L29 _public prototype_ `uint32 Hash() const override;`
- L30 _public prototype_ `bool IsEqual(const ASTOp& otherUntyped) const override;`
- L31 _public prototype_ `Ptr<ASTOp> Clone(MapChildFuncRef mapChild) const override;`
- L32 _public prototype_ `void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L33 _public prototype_ `void Link(FProgram& program, FLinkerOptions* Options) override;`
- L34 _public prototype_ `void GetBlockLayoutSize(uint64 BlockId, int32* pBlockX, int32* pBlockY, FBlockLayoutSizeCache* cache) override;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Mutable` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpLayoutPack.h` (Private)


#### class `UE::Mutable::Private::ASTOpLayoutPack`  
`class ASTOpLayoutPack final : public ASTOp`  
_L15-35_
- inherits: `ASTOp`
- L19 _public member_ `ASTChild Source;`
- L23 _public prototype_ `ASTOpLayoutPack();`
- L24 _public prototype_ `ASTOpLayoutPack(const ASTOpLayoutPack&) = delete;`
- L25 _public prototype_ `~ASTOpLayoutPack();`
- L27 _public function_ `EOpType GetOpType() const override`
- L28 _public prototype_ `uint32 Hash() const override;`
- L29 _public prototype_ `bool IsEqual(const ASTOp& otherUntyped) const override;`
- L30 _public prototype_ `Ptr<ASTOp> Clone(MapChildFuncRef mapChild) const override;`
- L31 _public prototype_ `void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L32 _public prototype_ `void Link(FProgram& program, FLinkerOptions* Options) override;`
- L33 _public prototype_ `void GetBlockLayoutSize(uint64 BlockId, int32* pBlockX, int32* pBlockY, FBlockLayoutSizeCache* cache) override;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Mutable` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpLayoutRemoveBlocks.h` (Private)


#### class `UE::Mutable::Private::ASTOpLayoutRemoveBlocks`  
`class ASTOpLayoutRemoveBlocks final : public ASTOp`  
_L15-36_
- inherits: `ASTOp`
- L19 _public member_ `ASTChild Source;`
- L20 _public member_ `ASTChild ReferenceLayout;`
- L24 _public prototype_ `ASTOpLayoutRemoveBlocks();`
- L25 _public prototype_ `ASTOpLayoutRemoveBlocks(const ASTOpLayoutRemoveBlocks&) = delete;`
- L26 _public prototype_ `~ASTOpLayoutRemoveBlocks();`
- L28 _public function_ `EOpType GetOpType() const override`
- L29 _public prototype_ `uint32 Hash() const override;`
- L30 _public prototype_ `bool IsEqual(const ASTOp& otherUntyped) const override;`
- L31 _public prototype_ `Ptr<ASTOp> Clone(MapChildFuncRef mapChild) const override;`
- L32 _public prototype_ `void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L33 _public prototype_ `void Link(FProgram& program, FLinkerOptions* Options) override;`
- L34 _public prototype_ `void GetBlockLayoutSize(uint64 BlockId, int32* pBlockX, int32* pBlockY, FBlockLayoutSizeCache* cache) override;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Mutable` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpMaterialBreak.h` (Private)


#### class `UE::Mutable::Private::ASTOpMaterialBreak`  
`class ASTOpMaterialBreak final : public ASTOp`  
_L16-43_
- inherits: `ASTOp`
- desc: Parameter operation.
- L21 _public member_ `EOpType Type = EOpType::NONE;` — Type of parameter
- L23 _public member_ `ASTChild Material;`
- L25 _public member_ `FParameterKey ParameterKey;`
- L29 _public prototype_ `ASTOpMaterialBreak();`
- L30 _public prototype_ `ASTOpMaterialBreak(const ASTOpMaterialBreak&) = delete;`
- L34 _public prototype_ `virtual EOpType GetOpType() const override;` — ASTOp interface.
- L35 _public prototype_ `virtual uint32 Hash() const override;`
- L36 _public prototype_ `virtual void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L37 _public prototype_ `virtual bool IsEqual(const ASTOp&) const override;`
- L38 _public prototype_ `virtual Ptr<ASTOp> Clone(MapChildFuncRef ) const override;`
- L39 _public prototype_ `virtual void Assert() override;`
- L40 _public prototype_ `virtual void Link(FProgram&, FLinkerOptions*) override;`
- L41 _public prototype_ `virtual FImageDesc GetImageDesc(bool, FGetImageDescContext*) const override;`
- L42 _public prototype_ `virtual FSourceDataDescriptor GetSourceDataDescriptor(FGetSourceDataDescriptorContext*) const override;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Mutable` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpMaterialBreakImageParameter.h` (Private)


#### class `UE::Mutable::Private::ASTOpImageFromMaterialParameter`  
`class ASTOpImageFromMaterialParameter final : public ASTOp`  
_L16-39_
- inherits: `ASTOp`
- desc: Parameter operation.
- L20 _public member_ `FParameterDesc MaterialParameter;`
- L21 _public member_ `FParameterKey ParameterKey;`
- L25 _public prototype_ `ASTOpImageFromMaterialParameter();`
- L26 _public prototype_ `ASTOpImageFromMaterialParameter(const ASTOpImageFromMaterialParameter&) = delete;`
- L30 _public prototype_ `virtual EOpType GetOpType() const override;` — ASTOp interface.
- L31 _public prototype_ `virtual uint32 Hash() const override;`
- L32 _public prototype_ `virtual void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L33 _public prototype_ `virtual bool IsEqual(const ASTOp&) const override;`
- L34 _public prototype_ `virtual Ptr<ASTOp> Clone(MapChildFuncRef ) const override;`
- L35 _public prototype_ `virtual void Assert() override;`
- L36 _public prototype_ `virtual void Link(FProgram&, FLinkerOptions*) override;`
- L37 _public prototype_ `virtual FImageDesc GetImageDesc(bool, FGetImageDescContext*) const override;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Mutable` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpMaterialModify.h` (Private)


#### class `UE::Mutable::Private::ASTOpMaterialModify`  
`class ASTOpMaterialModify final : public ASTOp`  
_L9-40_
- inherits: `ASTOp`
- L14 _public member_ `ASTChild Material;` — Parent Material
- L18 _public member_ `TMap<FParameterKey, ASTChild> ParametersToModify;` — Parameters to modify. A nullptr value means that, if this operation is linked to a previous Modify operation, the value set in that operation will be reset to its default value (the value set in the material)
- L21 _public member_ `TMap<FParameterKey, int32> ImagePropertyIndexMap;` — Index to the ImageProperties array of the model resources
- L25 _public prototype_ `ASTOpMaterialModify();`
- L26 _public prototype_ `ASTOpMaterialModify(const ASTOpMaterialModify&) = delete;`
- L30 _public prototype_ `virtual EOpType GetOpType() const override;` — ASTOp interface.
- L31 _public prototype_ `virtual uint32 Hash() const override;`
- L32 _public prototype_ `virtual void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L33 _public prototype_ `virtual bool IsEqual(const ASTOp&) const override;`
- L34 _public prototype_ `virtual Ptr<ASTOp> Clone(MapChildFuncRef ) const override;`
- L35 _public prototype_ `virtual void Assert() override;`
- L36 _public prototype_ `virtual void Link(FProgram&, FLinkerOptions*) override;`
- L37 _public prototype_ `virtual FImageDesc GetImageDesc(bool, FGetImageDescContext*) const override;`
- L38 _public prototype_ `virtual FSourceDataDescriptor GetSourceDataDescriptor(FGetSourceDataDescriptorContext*) const override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Mutable` (scope `UE`)
- L7 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpMaterialSkeletalMeshBreak.h` (Private)


#### class `UE::Mutable::Private::ASTOpMaterialSkeletalMeshBreak`  
`class ASTOpMaterialSkeletalMeshBreak final : public ASTOp`  
_L16-36_
- inherits: `ASTOp`
- L21 _public member_ `FName SlotName;` — The name of the material slot to get from the given mesh.
- L24 _public member_ `ASTChild SkeletalMesh;` — The skeletal mesh to use as source when looking for the material with the target "SlotName"
- L26 _public prototype_ `ASTOpMaterialSkeletalMeshBreak();`
- L30 _public prototype_ `virtual EOpType GetOpType() const override;` — ASTOp interface.
- L31 _public prototype_ `virtual uint32 Hash() const override;`
- L32 _public prototype_ `virtual void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L33 _public prototype_ `virtual bool IsEqual(const ASTOp&) const override;`
- L34 _public prototype_ `virtual Ptr<ASTOp> Clone(MapChildFuncRef ) const override;`
- L35 _public prototype_ `virtual void Link(FProgram&, FLinkerOptions*) override;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Mutable` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpMaterialSkeletalMeshObjectBreak.h` (Private)


#### class `UE::Mutable::Private::ASTOpMaterialSkeletalMeshObjectBreak`  
`class ASTOpMaterialSkeletalMeshObjectBreak final : public ASTOp`  
_L16-36_
- inherits: `ASTOp`
- L21 _public member_ `FName SlotName;` — The name of the material slot to get from the given mesh.
- L24 _public member_ `ASTChild SkeletalMeshObject;` — The skeletal mesh to use as source when looking for the material with the target "SlotName"
- L26 _public prototype_ `ASTOpMaterialSkeletalMeshObjectBreak();`
- L30 _public prototype_ `virtual EOpType GetOpType() const override;` — ASTOp interface.
- L31 _public prototype_ `virtual uint32 Hash() const override;`
- L32 _public prototype_ `virtual void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L33 _public prototype_ `virtual bool IsEqual(const ASTOp&) const override;`
- L34 _public prototype_ `virtual Ptr<ASTOp> Clone(MapChildFuncRef ) const override;`
- L35 _public prototype_ `virtual void Link(FProgram&, FLinkerOptions*) override;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Mutable` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpMeshAddMetadata.h` (Private)


#### class `UE::Mutable::Private::ASTOpMeshAddMetadata`  
`class ASTOpMeshAddMetadata final : public ASTOp`  
_L17-65_
- inherits: `ASTOp`
- desc: Add metadata to a mesh.
- L22 _public member_ `ASTChild Source;` — Source mesh to add tags to.
- L25 _public member_ `TArray<FName> GameplayTags;` — Tags to add.
- L27 _public member_ `TArray<PASSTHROUGH_ID> AssetUserDataIds;`
- L29 _public member_ `TArray<TPair<FName, PASSTHROUGH_ID>> AnimationSlots;`
- L31 _public member_ `PASSTHROUGH_ID AnimInstanceId = PASSTHROUGH_ID_INVALID;`
- L34 _public member_ `PASSTHROUGH_ID SkeletonId = PASSTHROUGH_ID_INVALID;` — SkeletonId to add.
- L36 _public member_ `TArray<FString> RealTimeMorphNames;`
- L39 _public member_ `int8 BonePosePriority = 0;` — Bone Pose priority when merging two meshes.
- L42 _public member_ `int8 SocketPriority = 0;` — Socket priority when merging two meshes.
- L45 _public member_ `TArray<FMeshSocket> Sockets;` — Array of sockets.
- L48 _public member_ `PASSTHROUGH_ID PhysicsAssetId = PASSTHROUGH_ID_INVALID;` — PhysicsAsset to add
- L51 _public member_ `TArray<PASSTHROUGH_ID> AdditionalPhysicsAssetIds;` — Additional PhysicsAssets
- L53 _public prototype_ `ASTOpMeshAddMetadata();`
- L54 _public prototype_ `ASTOpMeshAddMetadata(const ASTOpMeshAddMetadata&) = delete;`
- L58 _public function_ `virtual EOpType GetOpType() const override` — ASTOp interface
- L59 _public prototype_ `virtual uint32 Hash() const override;`
- L60 _public prototype_ `virtual void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L61 _public prototype_ `virtual bool IsEqual(const ASTOp& OtherUntyped) const override;`
- L62 _public prototype_ `virtual Ptr<ASTOp> Clone(MapChildFuncRef MapChild) const override;`
- L63 _public prototype_ `virtual void Link(FProgram& Program, FLinkerOptions*) override;`
- L64 _public prototype_ `virtual FSourceDataDescriptor GetSourceDataDescriptor(FGetSourceDataDescriptorContext*) const override;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Mutable` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpMeshApplyLayout.h` (Private)


#### class `UE::Mutable::Private::ASTOpMeshApplyLayout`  
`class ASTOpMeshApplyLayout final : public ASTOp`  
_L16-39_
- inherits: `ASTOp`
- L20 _public member_ `ASTChild Mesh;`
- L21 _public member_ `ASTChild Layout;`
- L22 _public member_ `uint16 Channel=0;`
- L26 _public prototype_ `ASTOpMeshApplyLayout();`
- L27 _public prototype_ `ASTOpMeshApplyLayout(const ASTOpMeshApplyLayout&) = delete;`
- L28 _public prototype_ `~ASTOpMeshApplyLayout();`
- L31 _public function_ `virtual EOpType GetOpType() const override` — ASTOp interface
- L32 _public prototype_ `virtual uint32 Hash() const override;`
- L33 _public prototype_ `virtual bool IsEqual(const ASTOp&) const override;`
- L34 _public prototype_ `virtual Ptr<ASTOp> Clone(MapChildFuncRef) const override;`
- L35 _public prototype_ `virtual void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L36 _public prototype_ `virtual void Link(FProgram&, FLinkerOptions*) override;`
- L37 _public prototype_ `virtual Ptr<ASTOp> OptimiseSink(const FModelOptimizationOptions&, FOptimizeSinkContext&) const override;`
- L38 _public prototype_ `virtual FSourceDataDescriptor GetSourceDataDescriptor(FGetSourceDataDescriptorContext*) const override;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Mutable` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpMeshApplyPose.h` (Private)


#### class `UE::Mutable::Private::ASTOpMeshApplyPose`  
`class ASTOpMeshApplyPose final : public ASTOp`  
_L16-38_
- inherits: `ASTOp`
- L20 _public member_ `ASTChild Base;`
- L21 _public member_ `ASTChild Pose;`
- L25 _public prototype_ `ASTOpMeshApplyPose();`
- L26 _public prototype_ `ASTOpMeshApplyPose(const ASTOpMeshApplyPose&) = delete;`
- L27 _public prototype_ `~ASTOpMeshApplyPose();`
- L30 _public function_ `virtual EOpType GetOpType() const override` — ASTOp interface
- L31 _public prototype_ `virtual uint32 Hash() const override;`
- L32 _public prototype_ `virtual bool IsEqual(const ASTOp&) const override;`
- L33 _public prototype_ `virtual Ptr<ASTOp> Clone(MapChildFuncRef) const override;`
- L34 _public prototype_ `virtual void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L35 _public prototype_ `virtual void Link(FProgram&, FLinkerOptions*) override;`
- L36 _public prototype_ `virtual Ptr<ASTOp> OptimiseSink(const FModelOptimizationOptions&, FOptimizeSinkContext&) const override;`
- L37 _public prototype_ `virtual FSourceDataDescriptor GetSourceDataDescriptor(FGetSourceDataDescriptorContext*) const override;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Mutable` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpMeshApplyShape.h` (Private)


#### class `UE::Mutable::Private::ASTOpMeshApplyShape`  
`class ASTOpMeshApplyShape final : public ASTOp`  
_L18-43_
- inherits: `ASTOp`
- L22 _public member_ `ASTChild Mesh;`
- L23 _public member_ `ASTChild Shape;`
- L25 _public member_ `uint32 bRecomputeNormals : 1;`
- L26 _public member_ `uint32 bReshapeSkeleton : 1;`
- L27 _public member_ `uint32 bReshapePhysicsVolumes : 1;`
- L28 _public member_ `uint32 bReshapeVertices : 1;`
- L29 _public member_ `uint32 bApplyLaplacian : 1;`
- L32 _public prototype_ `ASTOpMeshApplyShape();`
- L33 _public prototype_ `ASTOpMeshApplyShape(const ASTOpMeshApplyShape&) = delete;`
- L34 _public prototype_ `~ASTOpMeshApplyShape();`
- L36 _public function_ `EOpType GetOpType() const override`
- L37 _public prototype_ `uint32 Hash() const override;`
- L38 _public prototype_ `bool IsEqual(const ASTOp& otherUntyped) const override;`
- L39 _public prototype_ `Ptr<ASTOp> Clone(MapChildFuncRef mapChild) const override;`
- L40 _public prototype_ `void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L41 _public prototype_ `void Link(FProgram& program, FLinkerOptions* Options) override;`
- L42 _public prototype_ `virtual FSourceDataDescriptor GetSourceDataDescriptor(FGetSourceDataDescriptorContext*) const override;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Mutable` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpMeshBindShape.h` (Private)


#### class `UE::Mutable::Private::ASTOpMeshBindShape`  
`class ASTOpMeshBindShape final : public ASTOp`  
_L17-54_
- inherits: `ASTOp`
- L21 _public member_ `ASTChild Mesh;`
- L22 _public member_ `ASTChild Shape;`
- L24 _public member_ `TArray<FName> BonesToDeform;`
- L25 _public member_ `TArray<FName> PhysicsToDeform;`
- L27 _public member_ `uint32 BindingMethod = 0;`
- L29 _public member_ `uint32 bRecomputeNormals : 1;`
- L30 _public member_ `uint32 bReshapeSkeleton : 1;`
- L31 _public member_ `uint32 bReshapePhysicsVolumes : 1;`
- L32 _public member_ `uint32 bReshapeVertices : 1;`
- L33 _public member_ `uint32 bApplyLaplacian : 1;`
- L34 _public member_ `uint32 bReshapeSkeletonInvertSelection : 1;`
- L35 _public member_ `uint32 bReshapePhysicsVolumesInvertSelection : 1;`
- L37 _public member_ `EVertexColorUsage RChannelUsage = EVertexColorUsage::None;`
- L38 _public member_ `EVertexColorUsage GChannelUsage = EVertexColorUsage::None;`
- L39 _public member_ `EVertexColorUsage BChannelUsage = EVertexColorUsage::None;`
- L40 _public member_ `EVertexColorUsage AChannelUsage = EVertexColorUsage::None;`
- L42 _public prototype_ `ASTOpMeshBindShape();`
- L43 _public prototype_ `ASTOpMeshBindShape(const ASTOpMeshBindShape&) = delete;`
- L46 _public function_ `virtual EOpType GetOpType() const override`
- L47 _public prototype_ `virtual uint32 Hash() const override;`
- L48 _public prototype_ `virtual bool IsEqual(const ASTOp& otherUntyped) const override;`
- L49 _public prototype_ `virtual Ptr<ASTOp> Clone(MapChildFuncRef mapChild) const override;`
- L50 _public prototype_ `virtual void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L51 _public prototype_ `virtual void Link(FProgram& program, FLinkerOptions* Options) override;`
- L52 _public prototype_ `virtual Ptr<ASTOp> OptimiseSink(const FModelOptimizationOptions&, FOptimizeSinkContext&) const override;`
- L53 _public prototype_ `virtual FSourceDataDescriptor GetSourceDataDescriptor(FGetSourceDataDescriptorContext*) const override;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Mutable` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpMeshClipDeform.h` (Private)


#### class `UE::Mutable::Private::ASTOpMeshClipDeform`  
`class ASTOpMeshClipDeform final : public ASTOp`  
_L19-42_
- inherits: `ASTOp`
- L23 _public member_ `ASTChild Mesh;`
- L24 _public member_ `ASTChild ClipShape;`
- L27 _public member_ `EFaceCullStrategy FaceCullStrategy = EFaceCullStrategy::AllVerticesCulled;` — Strategy to decide when to cull a face.
- L31 _public prototype_ `ASTOpMeshClipDeform();`
- L32 _public prototype_ `ASTOpMeshClipDeform(const ASTOpMeshClipDeform&) = delete;`
- L33 _public prototype_ `~ASTOpMeshClipDeform();`
- L35 _public function_ `EOpType GetOpType() const override`
- L36 _public prototype_ `uint32 Hash() const override;`
- L37 _public prototype_ `bool IsEqual(const ASTOp& otherUntyped) const override;`
- L38 _public prototype_ `Ptr<ASTOp> Clone(MapChildFuncRef mapChild) const override;`
- L39 _public prototype_ `void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L40 _public prototype_ `void Link(FProgram& program, FLinkerOptions* Options) override;`
- L41 _public prototype_ `virtual FSourceDataDescriptor GetSourceDataDescriptor(FGetSourceDataDescriptorContext*) const override;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Mutable` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpMeshClipMorphPlane.h` (Private)


#### class `UE::Mutable::Private::ASTOpMeshClipMorphPlane`  
`class ASTOpMeshClipMorphPlane final : public ASTOp`  
_L16-45_
- inherits: `ASTOp`
- L20 _public member_ `ASTChild Source;`
- L22 _public member_ `FShape MorphShape;`
- L23 _public member_ `FShape SelectionShape;`
- L24 _public member_ `FName VertexSelectionBone = NAME_None;`
- L26 _public member_ `EClipVertexSelectionType VertexSelectionType = EClipVertexSelectionType::None;`
- L27 _public member_ `EFaceCullStrategy FaceCullStrategy = EFaceCullStrategy::AllVerticesCulled;`
- L29 _public member_ `float Dist = 0.f, Factor = 0.f, VertexSelectionBoneMaxRadius = -1.f;`
- L29 _public member_ `float Dist = 0.f, Factor = 0.f, VertexSelectionBoneMaxRadius = -1.f;`
- L29 _public member_ `float Dist = 0.f, Factor = 0.f, VertexSelectionBoneMaxRadius = -1.f;`
- L33 _public prototype_ `ASTOpMeshClipMorphPlane();`
- L34 _public prototype_ `ASTOpMeshClipMorphPlane(const ASTOpMeshClipMorphPlane&) = delete;`
- L35 _public prototype_ `virtual ~ASTOpMeshClipMorphPlane();`
- L37 _public function_ `virtual EOpType GetOpType() const override`
- L38 _public prototype_ `virtual uint32 Hash() const override;`
- L39 _public prototype_ `virtual bool IsEqual(const ASTOp& otherUntyped) const override;`
- L40 _public prototype_ `virtual Ptr<ASTOp> Clone(MapChildFuncRef mapChild) const override;`
- L41 _public prototype_ `virtual void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L42 _public prototype_ `virtual void Link(FProgram& program, FLinkerOptions* Options) override;`
- L43 _public prototype_ `virtual UE::Mutable::Private::Ptr<ASTOp> OptimiseSink(const FModelOptimizationOptions&, FOptimizeSinkContext&) const override;`
- L44 _public prototype_ `virtual FSourceDataDescriptor GetSourceDataDescriptor(FGetSourceDataDescriptorContext*) const override;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Mutable` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpMeshClipWithMesh.h` (Private)


#### class `UE::Mutable::Private::ASTOpMeshClipWithMesh`  
`class ASTOpMeshClipWithMesh final : public ASTOp`  
_L17-40_
- inherits: `ASTOp`
- L21 _public member_ `ASTChild Source;`
- L22 _public member_ `ASTChild ClipMesh;`
- L23 _public member_ `EFaceCullStrategy FaceCullStrategy = EFaceCullStrategy::AllVerticesCulled;`
- L27 _public prototype_ `ASTOpMeshClipWithMesh();`
- L28 _public prototype_ `ASTOpMeshClipWithMesh(const ASTOpMeshClipWithMesh&) = delete;`
- L29 _public prototype_ `~ASTOpMeshClipWithMesh();`
- L32 _public function_ `virtual EOpType GetOpType() const override` — ASTOp interface
- L33 _public prototype_ `virtual uint32 Hash() const override;`
- L34 _public prototype_ `virtual bool IsEqual(const ASTOp&) const override;`
- L35 _public prototype_ `virtual Ptr<ASTOp> Clone(MapChildFuncRef) const override;`
- L36 _public prototype_ `virtual void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L37 _public prototype_ `virtual void Link(FProgram&, FLinkerOptions*) override;`
- L38 _public prototype_ `virtual Ptr<ASTOp> OptimiseSink(const FModelOptimizationOptions&, FOptimizeSinkContext&) const override;`
- L39 _public prototype_ `virtual FSourceDataDescriptor GetSourceDataDescriptor(FGetSourceDataDescriptorContext*) const override;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Mutable` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpMeshDifference.h` (Private)


#### class `UE::Mutable::Private::ASTOpMeshDifference`  
`class ASTOpMeshDifference final : public ASTOp`  
_L16-58_
- inherits: `ASTOp`
- desc: Calculate the difference between two meshes (usually to calculate a morph delta).
- L21 _public member_ `ASTChild Base;` — Base mesh of the morph.
- L24 _public member_ `ASTChild Target;` — Target mesh of the morph.
- L27 _public member_ `bool bIgnoreTextureCoords;` — If true the texture coordinates will not be morphed.This is only relevant if the list in channelSemantic is empty.
- L40 _public member_ `TArray<FChannel> Channels;`
- L44 _public prototype_ `ASTOpMeshDifference();`
- L45 _public prototype_ `ASTOpMeshDifference(const ASTOpMeshDifference&) = delete;`
- L49 _public function_ `EOpType GetOpType() const override` — ASTOp interface
- L50 _public prototype_ `uint32 Hash() const override;`
- L51 _public prototype_ `void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L52 _public prototype_ `bool IsEqual(const ASTOp& otherUntyped) const override;`
- L53 _public prototype_ `Ptr<ASTOp> Clone(MapChildFuncRef mapChild) const override;`
- L54 _public prototype_ `void Link(FProgram& program, FLinkerOptions*) override;`
- L55 _public prototype_ `Ptr<ASTOp> OptimiseSink(const FModelOptimizationOptions&, FOptimizeSinkContext&) const override;`
- L56 _public prototype_ `virtual FSourceDataDescriptor GetSourceDataDescriptor(FGetSourceDataDescriptorContext*) const override;`

#### struct `UE::Mutable::Private::ASTOpMeshDifference::FChannel`  
`struct FChannel`  
_L30-39_
- desc: Channels to diff.
- L32 _public member_ `uint8 Semantic=0;`
- L33 _public member_ `uint8 SemanticIndex=0;`
- L35 _public function_ `inline bool operator==( const FChannel& Other ) const`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Mutable` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpMeshExtractLayoutBlocks.h` (Private)


#### class `UE::Mutable::Private::ASTOpMeshExtractLayoutBlocks`  
`class ASTOpMeshExtractLayoutBlocks final : public ASTOp`  
_L19-49_
- inherits: `ASTOp`
- L24 _public member_ `ASTChild Source;` — Source mesh to extract block from.
- L27 _public member_ `uint16 LayoutIndex = 0;` — Layout to use to select the blocks.
- L30 _public member_ `TArray<uint64> Blocks;` — Block Ids to include in the resulting mesh. If this is empty all vertices with any valid block assigned will be included.
- L34 _public prototype_ `ASTOpMeshExtractLayoutBlocks();`
- L35 _public prototype_ `ASTOpMeshExtractLayoutBlocks(const ASTOpMeshExtractLayoutBlocks&) = delete;`
- L39 _public function_ `EOpType GetOpType() const override` — ASTOp interface
- L40 _public prototype_ `uint32 Hash() const override;`
- L41 _public prototype_ `void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L42 _public prototype_ `bool IsEqual(const ASTOp& otherUntyped) const override;`
- L43 _public prototype_ `Ptr<ASTOp> Clone(MapChildFuncRef mapChild) const override;`
- L44 _public prototype_ `void Assert() override;`
- L45 _public prototype_ `void Link(FProgram& program, FLinkerOptions* Options) override;`
- L46 _public prototype_ `UE::Mutable::Private::Ptr<ASTOp> OptimiseSink(const FModelOptimizationOptions&, FOptimizeSinkContext&) const;`
- L47 _public prototype_ `virtual FSourceDataDescriptor GetSourceDataDescriptor(FGetSourceDataDescriptorContext*) const override;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Mutable` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpMeshFormat.h` (Private)


#### class `UE::Mutable::Private::ASTOpMeshFormat`  
`class ASTOpMeshFormat final : public ASTOp`  
_L15-39_
- inherits: `ASTOp`
- L19 _public member_ `ASTChild Source;`
- L20 _public member_ `ASTChild Format;`
- L21 _public member_ `uint8 Flags = 0;`
- L22 _public member_ `bool bOptimizeBuffers = false;`
- L26 _public prototype_ `ASTOpMeshFormat();`
- L27 _public prototype_ `ASTOpMeshFormat(const ASTOpMeshFormat&) = delete;`
- L28 _public prototype_ `~ASTOpMeshFormat();`
- L30 _public function_ `EOpType GetOpType() const override`
- L31 _public prototype_ `uint32 Hash() const override;`
- L32 _public prototype_ `bool IsEqual(const ASTOp& otherUntyped) const override;`
- L33 _public prototype_ `Ptr<ASTOp> Clone(MapChildFuncRef mapChild) const override;`
- L34 _public prototype_ `void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L35 _public prototype_ `void Link(FProgram& program, FLinkerOptions* Options) override;`
- L36 _public prototype_ `Ptr<ASTOp> OptimiseSink(const FModelOptimizationOptions& options, FOptimizeSinkContext& context) const override;`
- L37 _public prototype_ `virtual FSourceDataDescriptor GetSourceDataDescriptor(FGetSourceDataDescriptorContext*) const override;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Mutable` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpMeshMaskClipMesh.h` (Private)


#### class `UE::Mutable::Private::ASTOpMeshMaskClipMesh`  
`class ASTOpMeshMaskClipMesh final : public ASTOp`  
_L19-41_
- inherits: `ASTOp`
- L23 _public member_ `ASTChild source;`
- L24 _public member_ `ASTChild clip;`
- L28 _public prototype_ `ASTOpMeshMaskClipMesh();`
- L29 _public prototype_ `ASTOpMeshMaskClipMesh(const ASTOpMeshMaskClipMesh&) = delete;`
- L30 _public prototype_ `~ASTOpMeshMaskClipMesh();`
- L32 _public function_ `EOpType GetOpType() const override`
- L33 _public prototype_ `uint32 Hash() const override;`
- L34 _public prototype_ `bool IsEqual(const ASTOp& otherUntyped) const override;`
- L35 _public prototype_ `Ptr<ASTOp> Clone(MapChildFuncRef mapChild) const override;`
- L36 _public prototype_ `void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L37 _public prototype_ `void Link(FProgram& program, FLinkerOptions* Options) override;`
- L38 _public prototype_ `Ptr<ASTOp> OptimiseSink(const FModelOptimizationOptions&, FOptimizeSinkContext&) const override;`
- L39 _public prototype_ `virtual FSourceDataDescriptor GetSourceDataDescriptor(FGetSourceDataDescriptorContext*) const override;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Mutable` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpMeshMaskClipUVMask.h` (Private)


#### class `UE::Mutable::Private::ASTOpMeshMaskClipUVMask`  
`class ASTOpMeshMaskClipUVMask final : public ASTOp`  
_L16-41_
- inherits: `ASTOp`
- desc: Generate a mesh mask from an image mask or a layout with blocks.
- L20 _public member_ `ASTChild Source;`
- L21 _public member_ `ASTChild UVSource;`
- L22 _public member_ `ASTChild MaskImage;`
- L23 _public member_ `ASTChild MaskLayout;`
- L24 _public member_ `uint8 LayoutIndex = 0;`
- L28 _public prototype_ `ASTOpMeshMaskClipUVMask();`
- L29 _public prototype_ `ASTOpMeshMaskClipUVMask(const ASTOpMeshMaskClipUVMask&) = delete;`
- L30 _public prototype_ `~ASTOpMeshMaskClipUVMask();`
- L32 _public function_ `EOpType GetOpType() const override`
- L33 _public prototype_ `uint32 Hash() const override;`
- L34 _public prototype_ `bool IsEqual(const ASTOp& otherUntyped) const override;`
- L35 _public prototype_ `Ptr<ASTOp> Clone(MapChildFuncRef mapChild) const override;`
- L36 _public prototype_ `void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L37 _public prototype_ `void Link(FProgram& program, FLinkerOptions* Options) override;`
- L38 _public prototype_ `Ptr<ASTOp> OptimiseSink(const FModelOptimizationOptions&, FOptimizeSinkContext&) const override;`
- L39 _public prototype_ `virtual FSourceDataDescriptor GetSourceDataDescriptor(FGetSourceDataDescriptorContext*) const override;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Mutable` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpMeshMaskDiff.h` (Private)


#### class `UE::Mutable::Private::ASTOpMeshMaskDiff`  
`class ASTOpMeshMaskDiff final : public ASTOp`  
_L15-37_
- inherits: `ASTOp`
- L19 _public member_ `ASTChild Source;`
- L20 _public member_ `ASTChild Fragment;`
- L24 _public prototype_ `ASTOpMeshMaskDiff();`
- L25 _public prototype_ `ASTOpMeshMaskDiff(const ASTOpMeshMaskDiff&) = delete;`
- L26 _public prototype_ `~ASTOpMeshMaskDiff();`
- L29 _public function_ `virtual EOpType GetOpType() const override` — ASTOp interface
- L30 _public prototype_ `virtual uint32 Hash() const override;`
- L31 _public prototype_ `virtual bool IsEqual(const ASTOp&) const override;`
- L32 _public prototype_ `virtual Ptr<ASTOp> Clone(MapChildFuncRef) const override;`
- L33 _public prototype_ `virtual void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L34 _public prototype_ `virtual void Link(FProgram&, FLinkerOptions*) override;`
- L35 _public prototype_ `virtual Ptr<ASTOp> OptimiseSemantic(const FModelOptimizationOptions&, int32 Pass) const override;`
- L36 _public prototype_ `virtual FSourceDataDescriptor GetSourceDataDescriptor(FGetSourceDataDescriptorContext*) const override;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Mutable` (scope `UE`)
- L10 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpMeshMerge.h` (Private)


#### class `UE::Mutable::Private::ASTOpMeshMerge`  
`class ASTOpMeshMerge final : public ASTOp`  
_L16-38_
- inherits: `ASTOp`
- L20 _public member_ `ASTChild Base;`
- L21 _public member_ `ASTChild Added;`
- L22 _public member_ `uint32 NewSurfaceID = 0;`
- L26 _public prototype_ `ASTOpMeshMerge();`
- L27 _public prototype_ `ASTOpMeshMerge(const ASTOpMeshMerge&) = delete;`
- L28 _public prototype_ `~ASTOpMeshMerge();`
- L31 _public function_ `virtual EOpType GetOpType() const override` — ASTOp interface
- L32 _public prototype_ `virtual uint32 Hash() const override;`
- L33 _public prototype_ `virtual bool IsEqual(const ASTOp&) const override;`
- L34 _public prototype_ `virtual Ptr<ASTOp> Clone(MapChildFuncRef) const override;`
- L35 _public prototype_ `virtual void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L36 _public prototype_ `virtual void Link(FProgram&, FLinkerOptions*) override;`
- L37 _public prototype_ `virtual FSourceDataDescriptor GetSourceDataDescriptor(FGetSourceDataDescriptorContext*) const override;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Mutable` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpMeshMorph.h` (Private)


#### class `UE::Mutable::Private::ASTOpMeshMorph`  
`class ASTOpMeshMorph final : public ASTOp`  
_L18-45_
- inherits: `ASTOp`
- L21 _public member_ `FName Name;`
- L24 _public member_ `ASTChild Factor;` — Factor selecting what morphs to apply and with what weight.
- L27 _public member_ `ASTChild Base;` — Base mesh to morph.
- L31 _public prototype_ `ASTOpMeshMorph();`
- L32 _public prototype_ `ASTOpMeshMorph(const ASTOpMeshMorph&) = delete;`
- L36 _public function_ `EOpType GetOpType() const override` — ASTOp interface
- L37 _public prototype_ `uint32 Hash() const override;`
- L38 _public prototype_ `void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L39 _public prototype_ `bool IsEqual(const ASTOp& otherUntyped) const override;`
- L40 _public prototype_ `Ptr<ASTOp> Clone(MapChildFuncRef mapChild) const override;`
- L41 _public prototype_ `void Link(FProgram& program, FLinkerOptions*) override;`
- L42 _public prototype_ `Ptr<ASTOp> OptimiseSink(const FModelOptimizationOptions&, FOptimizeSinkContext&) const override;`
- L43 _public prototype_ `virtual FSourceDataDescriptor GetSourceDataDescriptor(FGetSourceDataDescriptorContext*) const override;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Mutable` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpMeshPrepareLayout.h` (Private)


#### class `UE::Mutable::Private::ASTOpMeshPrepareLayout`  
`class ASTOpMeshPrepareLayout final : public ASTOp`  
_L16-42_
- inherits: `ASTOp`
- L20 _public member_ `ASTChild Mesh;`
- L21 _public member_ `ASTChild Layout;`
- L22 _public member_ `uint8 LayoutChannel = 0;`
- L23 _public member_ `bool bUseAbsoluteBlockIds = false;`
- L24 _public member_ `bool bNormalizeUVs = false;`
- L25 _public member_ `bool bClampUVIslands = false;`
- L26 _public member_ `bool bEnsureAllVerticesHaveLayoutBlock = false;`
- L30 _public prototype_ `ASTOpMeshPrepareLayout();`
- L31 _public prototype_ `ASTOpMeshPrepareLayout(const ASTOpMeshPrepareLayout&) = delete;`
- L32 _public prototype_ `~ASTOpMeshPrepareLayout();`
- L35 _public function_ `virtual EOpType GetOpType() const override` — ASTOp interface
- L36 _public prototype_ `virtual uint32 Hash() const override;`
- L37 _public prototype_ `virtual bool IsEqual(const ASTOp&) const override;`
- L38 _public prototype_ `virtual Ptr<ASTOp> Clone(MapChildFuncRef) const override;`
- L39 _public prototype_ `virtual void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L40 _public prototype_ `virtual void Link(FProgram&, FLinkerOptions*) override;`
- L41 _public prototype_ `virtual FSourceDataDescriptor GetSourceDataDescriptor(FGetSourceDataDescriptorContext*) const override;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Mutable` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpMeshProject.h` (Private)


#### class `UE::Mutable::Private::ASTOpMeshProject`  
`class ASTOpMeshProject final : public ASTOp`  
_L16-41_
- inherits: `ASTOp`
- L20 _public member_ `ASTChild Mesh;`
- L21 _public member_ `ASTChild Projector;`
- L24 _public member_ `uint8 LayoutIndex = 0;` — UV layout index to project with.
- L28 _public prototype_ `ASTOpMeshProject();`
- L29 _public prototype_ `ASTOpMeshProject(const ASTOpMeshProject&) = delete;`
- L30 _public prototype_ `~ASTOpMeshProject();`
- L33 _public function_ `virtual EOpType GetOpType() const override` — ASTOp interface
- L34 _public prototype_ `virtual uint32 Hash() const override;`
- L35 _public prototype_ `virtual bool IsEqual(const ASTOp&) const override;`
- L36 _public prototype_ `virtual Ptr<ASTOp> Clone(MapChildFuncRef) const override;`
- L37 _public prototype_ `virtual void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L38 _public prototype_ `virtual void Link(FProgram&, FLinkerOptions*) override;`
- L39 _public prototype_ `virtual Ptr<ASTOp> OptimiseSink(const FModelOptimizationOptions&, FOptimizeSinkContext&) const override;`
- L40 _public prototype_ `virtual FSourceDataDescriptor GetSourceDataDescriptor(FGetSourceDataDescriptorContext*) const override;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Mutable` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpMeshRemoveMask.h` (Private)


#### class `UE::Mutable::Private::ASTOpMeshRemoveMask`  
`class ASTOpMeshRemoveMask final : public ASTOp`  
_L16-47_
- inherits: `ASTOp`
- desc: Remove a list of mesh fragments with a condition from a source mesh.
- L21 _public member_ `ASTChild source;` — Source mesh to remove from.
- L24 _public member_ `TArray< TPair<ASTChild, ASTChild> > removes;` — Pairs of remove candidates: condition + mesh to remove
- L27 _public member_ `EFaceCullStrategy FaceCullStrategy = EFaceCullStrategy::AllVerticesCulled;` — Strategy to decide when to cull a face.
- L31 _public prototype_ `ASTOpMeshRemoveMask();`
- L32 _public prototype_ `ASTOpMeshRemoveMask(const ASTOpMeshRemoveMask&) = delete;`
- L36 _public function_ `EOpType GetOpType() const override` — ASTOp interface
- L37 _public prototype_ `uint32 Hash() const override;`
- L38 _public prototype_ `void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L39 _public prototype_ `bool IsEqual(const ASTOp& otherUntyped) const override;`
- L40 _public prototype_ `Ptr<ASTOp> Clone(MapChildFuncRef mapChild) const override;`
- L41 _public prototype_ `void Link(FProgram& program, FLinkerOptions*) override;`
- L42 _public prototype_ `Ptr<ASTOp> OptimiseSink(const FModelOptimizationOptions&, FOptimizeSinkContext&) const override;`
- L43 _public prototype_ `virtual FSourceDataDescriptor GetSourceDataDescriptor(FGetSourceDataDescriptorContext*) const override;`
- L46 _public prototype_ `void AddRemove(const Ptr<ASTOp>& condition, const Ptr<ASTOp>& mask);` — Own interface

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Mutable` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpMeshSetMaterialSlotId.h` (Private)


#### class `UE::Mutable::Private::ASTOpMeshSetMaterialSlotId`  
`class ASTOpMeshSetMaterialSlotId final : public ASTOp`  
_L18-39_
- inherits: `ASTOp`
- desc: Set a MaterialSlotId to an FMesh.
- L22 _public member_ `ASTChild Mesh;`
- L23 _public member_ `uint32 MaterialSlotId = 0;`
- L27 _public prototype_ `ASTOpMeshSetMaterialSlotId();`
- L28 _public prototype_ `ASTOpMeshSetMaterialSlotId(const ASTOpMeshSetMaterialSlotId&) = delete;`
- L32 _public prototype_ `EOpType GetOpType() const override;` — ASTOp interface
- L33 _public prototype_ `uint32 Hash() const override;`
- L34 _public prototype_ `void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L35 _public prototype_ `bool IsEqual(const ASTOp& OtherUntyped) const override;`
- L36 _public prototype_ `Ptr<ASTOp> Clone(MapChildFuncRef MapChild) const override;`
- L37 _public prototype_ `void Link(FProgram& Program, FLinkerOptions*) override;`
- L38 _public prototype_ `virtual FSourceDataDescriptor GetSourceDataDescriptor(FGetSourceDataDescriptorContext*) const override;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Mutable` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpMeshSkeletalMeshBreak.h` (Private)


#### class `UE::Mutable::Private::ASTOpMeshSkeletalMeshBreak`  
`class ASTOpMeshSkeletalMeshBreak final : public ASTOp`  
_L17-44_
- inherits: `ASTOp`
- L20 _public member_ `EOpType Type = EOpType::ME_SKELETALMESH_BREAK;`
- L23 _public member_ `uint8 BaseLODIndex = 0;` — Used by some parameter types (Mesh) to specify which subdata from the actual parameter value should be used in the operation.
- L24 _public member_ `uint8 BaseSectionIndex = 0;`
- L25 _public member_ `uint8 LODBias = 0;`
- L26 _public member_ `uint8 ConversionFlags = 0;`
- L27 _public member_ `uint32 MeshID = 0;`
- L29 _public member_ `ASTChild SkeletalMeshParameter;`
- L31 _public member_ `int32 LinkedParameterIndex = -1;`
- L33 _public prototype_ `ASTOpMeshSkeletalMeshBreak();`
- L37 _public prototype_ `virtual EOpType GetOpType() const override;` — ASTOp interface
- L38 _public prototype_ `virtual uint32 Hash() const override;`
- L39 _public prototype_ `virtual void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L40 _public prototype_ `virtual bool IsEqual(const ASTOp&) const override;`
- L41 _public prototype_ `virtual Ptr<ASTOp> Clone(MapChildFuncRef ) const override;`
- L42 _public prototype_ `virtual void Assert() override;`
- L43 _public prototype_ `virtual void Link(FProgram&, FLinkerOptions*) override;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Mutable` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpMeshTransform.h` (Private)


#### class `UE::Mutable::Private::ASTOpMeshTransform`  
`class ASTOpMeshTransform final : public ASTOp`  
_L20-44_
- inherits: `ASTOp`
- L24 _public member_ `ASTChild source;`
- L26 _public member_ `FMatrix44f matrix;`
- L30 _public prototype_ `ASTOpMeshTransform();`
- L31 _public prototype_ `ASTOpMeshTransform(const ASTOpMeshTransform&) = delete;`
- L32 _public prototype_ `~ASTOpMeshTransform();`
- L35 _public function_ `EOpType GetOpType() const override` — ASTOp interface
- L36 _public prototype_ `uint32 Hash() const override;`
- L37 _public prototype_ `void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L38 _public prototype_ `bool IsEqual(const ASTOp& otherUntyped) const override;`
- L39 _public prototype_ `Ptr<ASTOp> Clone(MapChildFuncRef mapChild) const override;`
- L40 _public prototype_ `void Link(FProgram& program, FLinkerOptions* Options) override;`
- L41 _public prototype_ `virtual FSourceDataDescriptor GetSourceDataDescriptor(FGetSourceDataDescriptorContext*) const override;`
- L42 _public prototype_ `virtual EClosedMeshTest IsClosedMesh(TMap<const ASTOp*, EClosedMeshTest>* Cache) const override;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Mutable` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpMeshTransformWithBone.h` (Private)


#### class `UE::Mutable::Private::ASTOpMeshTransformWithBone`  
`class ASTOpMeshTransformWithBone final : public ASTOp`  
_L20-41_
- inherits: `ASTOp`
- L23 _public member_ `ASTChild SourceMesh;`
- L24 _public member_ `ASTChild Matrix;`
- L25 _public member_ `FName BoneName = NAME_None;`
- L26 _public member_ `float ThresholdFactor = 0.05f;`
- L29 _public prototype_ `ASTOpMeshTransformWithBone();`
- L30 _public prototype_ `ASTOpMeshTransformWithBone(const ASTOpMeshTransformWithBone&) = delete;`
- L33 _public function_ `EOpType GetOpType() const override`
- L34 _public prototype_ `uint32 Hash() const override;`
- L35 _public prototype_ `bool IsEqual(const ASTOp& otherUntyped) const override;`
- L36 _public prototype_ `Ptr<ASTOp> Clone(MapChildFuncRef mapChild) const override;`
- L37 _public prototype_ `void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L38 _public prototype_ `void Link(FProgram& program, FLinkerOptions* Options) override;`
- L39 _public prototype_ `virtual FSourceDataDescriptor GetSourceDataDescriptor(FGetSourceDataDescriptorContext*) const override;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Mutable` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpMeshTransformWithBoundingMesh.h` (Private)


#### class `UE::Mutable::Private::ASTOpMeshTransformWithBoundingMesh`  
`class ASTOpMeshTransformWithBoundingMesh final : public ASTOp`  
_L19-41_
- inherits: `ASTOp`
- L23 _public member_ `ASTChild source;`
- L24 _public member_ `ASTChild boundingMesh;`
- L26 _public member_ `ASTChild matrix;`
- L29 _public prototype_ `ASTOpMeshTransformWithBoundingMesh();`
- L30 _public prototype_ `ASTOpMeshTransformWithBoundingMesh(const ASTOpMeshTransformWithBoundingMesh&) = delete;`
- L33 _public function_ `EOpType GetOpType() const override`
- L34 _public prototype_ `uint32 Hash() const override;`
- L35 _public prototype_ `bool IsEqual(const ASTOp& otherUntyped) const override;`
- L36 _public prototype_ `Ptr<ASTOp> Clone(MapChildFuncRef mapChild) const override;`
- L37 _public prototype_ `void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L38 _public prototype_ `void Link(FProgram& program, FLinkerOptions* Options) override;`
- L39 _public prototype_ `virtual FSourceDataDescriptor GetSourceDataDescriptor(FGetSourceDataDescriptorContext*) const override;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Mutable` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpParameter.h` (Private)


#### class `UE::Mutable::Private::ASTOpParameter`  
`class ASTOpParameter final : public ASTOp`  
_L19-54_
- inherits: `ASTOp`
- desc: Parameter operation.
- L24 _public member_ `EOpType Type = EOpType::NONE;` — Type of parameter
- L27 _public member_ `FParameterDesc Parameter;`
- L30 _public member_ `TArray<FRangeData> Ranges;` — /  Ranges adding dimensions to this parameter.
- L33 _public member_ `TMap<FParameterKey, ASTChild> ImageOperations;` — Image Parameters which are evaluated at runtime.
- L38 _public member_ `int32 LinkedParameterIndex = -1;` — Index of the parameter in the final program parameter list. This is generated at link time, because the parameters may be reordered.
- L43 _public prototype_ `virtual EOpType GetOpType() const override;` — ASTOp interface.
- L44 _public prototype_ `virtual uint32 Hash() const override;`
- L45 _public prototype_ `virtual void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L46 _public prototype_ `virtual bool IsEqual(const ASTOp&) const override;`
- L47 _public prototype_ `virtual Ptr<ASTOp> Clone(MapChildFuncRef ) const override;`
- L48 _public prototype_ `virtual void Assert() override;`
- L49 _public prototype_ `virtual void Link(FProgram&, FLinkerOptions*) override;`
- L50 _public prototype_ `virtual int EvaluateInt(ASTOpList& Facts, bool& bOutUnknown) const override;`
- L51 _public prototype_ `virtual FBoolEvalResult EvaluateBool(ASTOpList& Facts, FEvaluateBoolCache* = nullptr) const override;`
- L52 _public prototype_ `virtual FImageDesc GetImageDesc(bool, FGetImageDescContext*) const override;`
- L53 _public prototype_ `virtual bool IsColorConstant(FVector4f& OutColor) const override;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Mutable` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpReferenceResource.h` (Private)


#### class `UE::Mutable::Private::ASTOpReferenceResource`  
`class ASTOpReferenceResource final : public ASTOp`  
_L22-58_
- inherits: `ASTOp`
- L27 _public member_ `EOpType Type = EOpType::NONE;` — Type of switch
- L30 _public member_ `bool bForceLoad = false;`
- L33 _public member_ `PASSTHROUGH_ID ID = PASSTHROUGH_ID_INVALID;` — Externally provided ID to identify the resource.
- L36 _public member_ `FImageDesc ImageDesc;`
- L39 _public member_ `FSourceDataDescriptor SourceDataDescriptor;` — Source data descriptor.
- L46 _public function_ `virtual EOpType GetOpType() const override` — ASTOp interface
- L47 _public prototype_ `virtual void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L48 _public prototype_ `virtual bool IsEqual(const ASTOp& otherUntyped) const override;`
- L49 _public prototype_ `virtual Ptr<ASTOp> Clone(MapChildFuncRef mapChild) const override;`
- L50 _public prototype_ `virtual uint32 Hash() const override;`
- L51 _public prototype_ `virtual void Link(FProgram& program, FLinkerOptions*) override;`
- L52 _public prototype_ `virtual FImageDesc GetImageDesc(bool, class FGetImageDescContext*) const override;`
- L53 _public prototype_ `virtual void GetBlockLayoutSize(uint64 BlockId, int32* pBlockX, int32* pBlockY, FBlockLayoutSizeCache* cache) override;`
- L54 _public prototype_ `virtual void GetLayoutBlockSize(int32* pBlockX, int32* pBlockY) override;`
- L55 _public prototype_ `virtual bool GetNonBlackRect(FImageRect& maskUsage) const override;`
- L56 _public prototype_ `virtual Ptr<ImageSizeExpression> GetImageSizeExpression() const override;`
- L57 _public prototype_ `virtual FSourceDataDescriptor GetSourceDataDescriptor(FGetSourceDataDescriptorContext*) const override;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Mutable` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpScalarArithmetic.h` (Private)


#### class `UE::Mutable::Private::ASTOpScalarArithmetic`  
`class ASTOpScalarArithmetic final : public ASTOp`  
_L16-37_
- inherits: `ASTOp`
- L20 _public member_ `ASTChild A;`
- L21 _public member_ `ASTChild B;`
- L22 _public member_ `uint16 Operation=0;`
- L26 _public prototype_ `ASTOpScalarArithmetic();`
- L27 _public prototype_ `ASTOpScalarArithmetic(const ASTOpScalarArithmetic&) = delete;`
- L28 _public prototype_ `~ASTOpScalarArithmetic();`
- L31 _public function_ `virtual EOpType GetOpType() const override` — ASTOp interface
- L32 _public prototype_ `virtual uint32 Hash() const override;`
- L33 _public prototype_ `virtual bool IsEqual(const ASTOp&) const override;`
- L34 _public prototype_ `virtual Ptr<ASTOp> Clone(MapChildFuncRef) const override;`
- L35 _public prototype_ `virtual void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L36 _public prototype_ `virtual void Link(FProgram&, FLinkerOptions*) override;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Mutable` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpScalarCurve.h` (Private)


#### class `UE::Mutable::Private::ASTOpScalarCurve`  
`class ASTOpScalarCurve final : public ASTOp`  
_L21-42_
- inherits: `ASTOp`
- L25 _public member_ `ASTChild time;`
- L28 _public member_ `FRichCurve Curve;`
- L32 _public prototype_ `ASTOpScalarCurve();`
- L33 _public prototype_ `ASTOpScalarCurve(const ASTOpScalarCurve&) = delete;`
- L36 _public function_ `EOpType GetOpType() const override`
- L37 _public prototype_ `uint32 Hash() const override;`
- L38 _public prototype_ `void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L39 _public prototype_ `bool IsEqual(const ASTOp& otherUntyped) const override;`
- L40 _public prototype_ `Ptr<ASTOp> Clone(MapChildFuncRef mapChild) const override;`
- L41 _public prototype_ `void Link(FProgram& program, FLinkerOptions* Options) override;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Mutable` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpSkeletalMeshClipWithMesh.h` (Private)


#### class `UE::Mutable::Private::ASTOpSkeletalMeshClipWithSkeletalMesh`  
`class ASTOpSkeletalMeshClipWithSkeletalMesh final : public ASTOp`  
_L17-40_
- inherits: `ASTOp`
- L21 _public member_ `ASTChild Source;`
- L22 _public member_ `ASTChild Clip;`
- L24 _public member_ `EFaceCullStrategy FaceCullStrategy = EFaceCullStrategy::AllVerticesCulled;`
- L28 _public prototype_ `ASTOpSkeletalMeshClipWithSkeletalMesh();`
- L29 _public prototype_ `ASTOpSkeletalMeshClipWithSkeletalMesh(const ASTOpSkeletalMeshClipWithSkeletalMesh&) = delete;`
- L30 _public prototype_ `~ASTOpSkeletalMeshClipWithSkeletalMesh();`
- L33 _public function_ `virtual EOpType GetOpType() const override` — ASTOp interface
- L34 _public prototype_ `virtual uint32 Hash() const override;`
- L35 _public prototype_ `virtual bool IsEqual(const ASTOp&) const override;`
- L36 _public prototype_ `virtual Ptr<ASTOp> Clone(MapChildFuncRef) const override;`
- L37 _public prototype_ `virtual void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L38 _public prototype_ `virtual void Link(FProgram&, FLinkerOptions*) override;`
- L39 _public prototype_ `virtual FSourceDataDescriptor GetSourceDataDescriptor(FGetSourceDataDescriptorContext*) const override;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Mutable` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpSkeletalMeshConvert.h` (Private)


#### class `UE::Mutable::Private::ASTOpSkeletalMeshConvert`  
`class ASTOpSkeletalMeshConvert final : public ASTOp`  
_L17-38_
- inherits: `ASTOp`
- L22 _public member_ `uint8 ConversionFlags = 0;` — Used by some parameter types (Mesh) to specify which subdata from the actual parameter value should be used in the operation.
- L23 _public member_ `uint32 MeshID = 0;`
- L25 _public member_ `ASTChild SkeletalMeshObject;`
- L27 _public prototype_ `ASTOpSkeletalMeshConvert();`
- L31 _public function_ `virtual EOpType GetOpType() const override` — ASTOp interface
- L32 _public prototype_ `virtual uint32 Hash() const override;`
- L33 _public prototype_ `virtual void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L34 _public prototype_ `virtual bool IsEqual(const ASTOp&) const override;`
- L35 _public prototype_ `virtual Ptr<ASTOp> Clone(MapChildFuncRef ) const override;`
- L36 _public prototype_ `virtual void Assert() override;`
- L37 _public prototype_ `virtual void Link(FProgram&, FLinkerOptions*) override;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Mutable` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpSkeletalMeshMaterialModify.h` (Private)


#### class `UE::Mutable::Private::ASTOpSkeletalMeshMaterialModify`  
`class ASTOpSkeletalMeshMaterialModify final : public ASTOp`  
_L9-38_
- inherits: `ASTOp`
- L13 _public member_ `FName MaterialSlotNameToModify;`
- L16 _public member_ `ASTChild SkeletalMesh;` — SkeletalMesh to Modify
- L19 _public member_ `ASTChild NewMaterial;` — New material to slot in MaterialSlotNameToModify
- L24 _public prototype_ `ASTOpSkeletalMeshMaterialModify();`
- L25 _public prototype_ `ASTOpSkeletalMeshMaterialModify(const ASTOpSkeletalMeshMaterialModify&) = delete;`
- L29 _public prototype_ `virtual EOpType GetOpType() const override;` — ASTOp interface.
- L30 _public prototype_ `virtual uint32 Hash() const override;`
- L31 _public prototype_ `virtual void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L32 _public prototype_ `virtual bool IsEqual(const ASTOp&) const override;`
- L33 _public prototype_ `virtual Ptr<ASTOp> Clone(MapChildFuncRef ) const override;`
- L34 _public prototype_ `virtual void Assert() override;`
- L35 _public prototype_ `virtual void Link(FProgram&, FLinkerOptions*) override;`
- L36 _public prototype_ `virtual FSourceDataDescriptor GetSourceDataDescriptor(FGetSourceDataDescriptorContext*) const override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Mutable` (scope `UE`)
- L7 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpSkeletalMeshMerge.h` (Private)


#### class `UE::Mutable::Private::ASTOpSkeletalMeshMerge`  
`class ASTOpSkeletalMeshMerge final : public ASTOp`  
_L15-32_
- inherits: `ASTOp`
- L18 _public member_ `ASTChild BaseMesh;`
- L19 _public member_ `ASTChild AddedMesh;`
- L21 _public prototype_ `ASTOpSkeletalMeshMerge();`
- L22 _public prototype_ `ASTOpSkeletalMeshMerge(const ASTOpSkeletalMeshMerge&) = delete;`
- L25 _public prototype_ `virtual EOpType GetOpType() const override;`
- L26 _public prototype_ `virtual uint32 Hash() const override;`
- L27 _public prototype_ `virtual void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L28 _public prototype_ `virtual bool IsEqual(const ASTOp& OtherUntyped) const override;`
- L29 _public prototype_ `virtual Ptr<ASTOp> Clone(MapChildFuncRef MapChild) const override;`
- L30 _public prototype_ `virtual void Link(FProgram& Program, FLinkerOptions* Options) override;`
- L31 _public prototype_ `virtual Ptr<ASTOp> OptimiseSemantic(const FModelOptimizationOptions&, int32 Pass) const override;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Mutable` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpSkeletalMeshMorph.h` (Private)


#### class `UE::Mutable::Private::ASTOpSkeletalMeshMorph`  
`class ASTOpSkeletalMeshMorph final : public ASTOp`  
_L18-44_
- inherits: `ASTOp`
- desc: Apply a morph to a SkeletalMesh.
- L22 _public member_ `FName MorphName;` — Morph name to apply.
- L25 _public member_ `ASTChild Factor;` — Factor selecting what morphs to apply and with what weight.
- L28 _public member_ `ASTChild Base;` — Base mesh to morph.
- L32 _public prototype_ `ASTOpSkeletalMeshMorph();`
- L33 _public prototype_ `ASTOpSkeletalMeshMorph(const ASTOpSkeletalMeshMorph&) = delete;`
- L37 _public function_ `EOpType GetOpType() const override` — ASTOp interface
- L38 _public prototype_ `uint32 Hash() const override;`
- L39 _public prototype_ `void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L40 _public prototype_ `bool IsEqual(const ASTOp& OtherUntyped) const override;`
- L41 _public prototype_ `Ptr<ASTOp> Clone(MapChildFuncRef MapChild) const override;`
- L42 _public prototype_ `void Link(FProgram& Program, FLinkerOptions*) override;`
- L43 _public prototype_ `virtual FSourceDataDescriptor GetSourceDataDescriptor(FGetSourceDataDescriptorContext*) const override;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Mutable` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpSkeletalMeshNew.h` (Private)


#### class `UE::Mutable::Private::ASTOpSkeletalMeshNew`  
`class ASTOpSkeletalMeshNew final : public ASTOp`  
_L15-40_
- inherits: `ASTOp`
- L19 _public member_ `TArray<ASTChild> MaterialSlotMaterials;` — Key is the Material Slot.
- L22 _public member_ `TArray<FName> MaterialSlotNames;` — Key is the Material Slot.
- L25 _public member_ `TArray<uint32> MaterialSlotIds;` — Key is the Material Slot.
- L28 _public member_ `TArray<ASTChild> LODs;` — Key is the LOD Index.
- L30 _public prototype_ `ASTOpSkeletalMeshNew();`
- L31 _public prototype_ `ASTOpSkeletalMeshNew(const ASTOpSkeletalMeshNew&) = delete;`
- L34 _public prototype_ `virtual EOpType GetOpType() const override;`
- L35 _public prototype_ `virtual uint32 Hash() const override;`
- L36 _public prototype_ `virtual void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L37 _public prototype_ `virtual bool IsEqual(const ASTOp& OtherUntyped) const override;`
- L38 _public prototype_ `virtual Ptr<ASTOp> Clone(MapChildFuncRef MapChild) const override;`
- L39 _public prototype_ `virtual void Link(FProgram& Program, FLinkerOptions* Options) override;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Mutable` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpSkeletalMeshObjectConvert.h` (Private)


#### class `UE::Mutable::Private::ASTOpSkeletalMeshObjectConvert`  
`class ASTOpSkeletalMeshObjectConvert final : public ASTOp`  
_L17-42_
- inherits: `ASTOp`
- L20 _public member_ `ASTChild SkeletalMesh;`
- L22 _public member_ `FName Name;`
- L23 _public member_ `uint8 NumLODs = 0;`
- L24 _public member_ `uint8 FirstLODAvailable = 0;`
- L25 _public member_ `uint8 FirstLODResident = 0;`
- L27 _public member_ `FPerPlatformInt MinLODs;`
- L28 _public member_ `FPerQualityLevelInt MinQualityLevelLODs;`
- L30 _public member_ `TArray<FLODInfo> LODInfos;`
- L32 _public prototype_ `ASTOpSkeletalMeshObjectConvert();`
- L33 _public prototype_ `ASTOpSkeletalMeshObjectConvert(const ASTOpSkeletalMeshObjectConvert&) = delete;`
- L36 _public prototype_ `virtual EOpType GetOpType() const override;`
- L37 _public prototype_ `virtual uint32 Hash() const override;`
- L38 _public prototype_ `virtual void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L39 _public prototype_ `virtual bool IsEqual(const ASTOp& OtherUntyped) const override;`
- L40 _public prototype_ `virtual Ptr<ASTOp> Clone(MapChildFuncRef MapChild) const override;`
- L41 _public prototype_ `virtual void Link(FProgram& Program, FLinkerOptions* Options) override;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Mutable` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpSkeletalMeshReshape.h` (Private)


#### class `UE::Mutable::Private::ASTOpSkeletalMeshReshape`  
`class ASTOpSkeletalMeshReshape final : public ASTOp`  
_L18-57_
- inherits: `ASTOp`
- desc: Apply a reshape to a SkeletalMesh.
- L21 _public member_ `ASTChild Base;`
- L22 _public member_ `ASTChild BaseShape;`
- L23 _public member_ `ASTChild TargetShape;`
- L25 _public member_ `TArray<FName> BonesToDeform;`
- L26 _public member_ `TArray<FName> PhysicsToDeform;`
- L28 _public member_ `uint32 BindingMethod = 0;`
- L30 _public member_ `uint32 bRecomputeNormals : 1 = false;`
- L31 _public member_ `uint32 bReshapeSkeleton : 1 = false;`
- L32 _public member_ `uint32 bReshapePhysicsVolumes : 1 = false;`
- L33 _public member_ `uint32 bReshapeVertices : 1 = false;`
- L34 _public member_ `uint32 bApplyLaplacian : 1 = false;`
- L35 _public member_ `uint32 bReshapeSkeletonInvertSelection : 1 = false;`
- L36 _public member_ `uint32 bReshapePhysicsVolumesInvertSelection : 1 = false;`
- L38 _public member_ `EVertexColorUsage RChannelUsage = EVertexColorUsage::None;`
- L39 _public member_ `EVertexColorUsage GChannelUsage = EVertexColorUsage::None;`
- L40 _public member_ `EVertexColorUsage BChannelUsage = EVertexColorUsage::None;`
- L41 _public member_ `EVertexColorUsage AChannelUsage = EVertexColorUsage::None;`
- L45 _public prototype_ `ASTOpSkeletalMeshReshape();`
- L46 _public prototype_ `ASTOpSkeletalMeshReshape(const ASTOpSkeletalMeshReshape&) = delete;`
- L50 _public function_ `EOpType GetOpType() const override` — ASTOp interface
- L51 _public prototype_ `uint32 Hash() const override;`
- L52 _public prototype_ `void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L53 _public prototype_ `bool IsEqual(const ASTOp& OtherUntyped) const override;`
- L54 _public prototype_ `Ptr<ASTOp> Clone(MapChildFuncRef MapChild) const override;`
- L55 _public prototype_ `void Link(FProgram& Program, FLinkerOptions*) override;`
- L56 _public prototype_ `virtual FSourceDataDescriptor GetSourceDataDescriptor(FGetSourceDataDescriptorContext*) const override;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Mutable` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpSkeletalMeshTransform.h` (Private)


#### class `UE::Mutable::Private::ASTOpSkeletalMeshTransform`  
`class ASTOpSkeletalMeshTransform final : public ASTOp`  
_L16-36_
- inherits: `ASTOp`
- L19 _public member_ `ASTChild Source;`
- L21 _public member_ `FMatrix44f Matrix;`
- L23 _public prototype_ `ASTOpSkeletalMeshTransform();`
- L24 _public prototype_ `ASTOpSkeletalMeshTransform(const ASTOpSkeletalMeshTransform&) = delete;`
- L28 _public prototype_ `virtual EOpType GetOpType() const override;` — ASTOp interface
- L29 _public prototype_ `virtual uint32 Hash() const override;`
- L30 _public prototype_ `virtual void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L31 _public prototype_ `virtual bool IsEqual(const ASTOp& otherUntyped) const override;`
- L32 _public prototype_ `virtual Ptr<ASTOp> Clone(MapChildFuncRef MapChild) const override;`
- L33 _public prototype_ `virtual void Link(FProgram& program, FLinkerOptions* Options) override;`
- L34 _public prototype_ `virtual FSourceDataDescriptor GetSourceDataDescriptor(FGetSourceDataDescriptorContext*) const override;`
- L35 _public prototype_ `virtual EClosedMeshTest IsClosedMesh(TMap<const ASTOp*, EClosedMeshTest>* Cache) const override;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Mutable` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpSkeletalMeshTransformWithBone.h` (Private)


#### class `UE::Mutable::Private::ASTOpSkeletalMeshTransformWithBone`  
`class ASTOpSkeletalMeshTransformWithBone final : public ASTOp`  
_L19-38_
- inherits: `ASTOp`
- L22 _public member_ `ASTChild SourceSkeletalMesh;`
- L23 _public member_ `ASTChild Matrix;`
- L24 _public member_ `FName BoneName = NAME_None;`
- L25 _public member_ `float ThresholdFactor = 0.05f;`
- L27 _public prototype_ `ASTOpSkeletalMeshTransformWithBone();`
- L28 _public prototype_ `ASTOpSkeletalMeshTransformWithBone(const ASTOpSkeletalMeshTransformWithBone&) = delete;`
- L31 _public prototype_ `virtual EOpType GetOpType() const override;`
- L32 _public prototype_ `virtual uint32 Hash() const override;`
- L33 _public prototype_ `virtual bool IsEqual(const ASTOp& otherUntyped) const override;`
- L34 _public prototype_ `virtual Ptr<ASTOp> Clone(MapChildFuncRef mapChild) const override;`
- L35 _public prototype_ `virtual void ForEachChild(const TFunctionRef<void(ASTChild&)>) override;`
- L36 _public prototype_ `virtual void Link(FProgram& program, FLinkerOptions* Options) override;`
- L37 _public prototype_ `virtual FSourceDataDescriptor GetSourceDataDescriptor(FGetSourceDataDescriptorContext*) const override;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Mutable` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/ASTOpSwitch.h` (Private)


#### class `UE::Mutable::Private::ASTOpSwitch`  
`class ASTOpSwitch final : public ASTOp`  
_L21-91_
- inherits: `ASTOp`
- L26 _public member_ `EOpType Type;` — Type of switch
- L29 _public member_ `ASTChild Variable;` — Variable whose value will be used to choose the switch branch.
- L32 _public member_ `ASTChild Default;` — Default branch in case none matches the value in the variable.
- L52 _public member_ `TArray<FCase> Cases;`
- L56 _public prototype_ `ASTOpSwitch();`
- L57 _public prototype_ `ASTOpSwitch(const ASTOpSwitch&) = delete;`
- L61 _public function_ `virtual EOpType GetOpType() const override` — ASTOp interface
- L62 _public prototype_ `virtual uint32 Hash() const override;`
- L63 _public prototype_ `virtual void ForEachChild(const TFunctionRef<void(ASTChild&)> f) override;`
- L64 _public prototype_ `virtual bool IsEqual(const ASTOp& otherUntyped) const override;`
- L65 _public prototype_ `virtual Ptr<ASTOp> Clone(MapChildFuncRef mapChild) const override;`
- L66 _public prototype_ `virtual void Assert() override;`
- L67 _public prototype_ `virtual void Link(FProgram& program, FLinkerOptions* Options) override;`
- L68 _public prototype_ `virtual FImageDesc GetImageDesc(bool returnBestOption, class FGetImageDescContext* context) const override;`
- L69 _public prototype_ `virtual void GetBlockLayoutSize(uint64 BlockId, int32* pBlockX, int32* pBlockY, FBlockLayoutSizeCache* cache) override;`
- L70 _public prototype_ `virtual void GetLayoutBlockSize(int32* pBlockX, int32* pBlockY) override;`
- L71 _public prototype_ `virtual Ptr<ASTOp> OptimiseSemantic(const FModelOptimizationOptions&, int32 Pass) const override;`
- L72 _public prototype_ `Ptr<ASTOp> OptimiseSink(const FModelOptimizationOptions&, FOptimizeSinkContext&) const override;`
- L73 _public prototype_ `virtual bool GetNonBlackRect(FImageRect& maskUsage) const override;`
- L74 _public prototype_ `virtual bool IsImagePlainConstant(FVector4f& color) const override;`
- L75 _public prototype_ `virtual Ptr<ImageSizeExpression> GetImageSizeExpression() const override;`
- L76 _public function_ `virtual bool IsSwitch() const override`
- L77 _public prototype_ `virtual FSourceDataDescriptor GetSourceDataDescriptor(FGetSourceDataDescriptorContext*) const override;`
- L82 _public prototype_ `Ptr<ASTOp> GetFirstValidValue();`
- L86 _public prototype_ `bool IsCompatibleWith(const ASTOpSwitch* other) const;` — Return true if the two switches have the same condition, amd case value (but not necessarily branches) or operation type.
- L89 _public prototype_ `Ptr<ASTOp> FindBranch(int32 condition) const;`

#### struct `UE::Mutable::Private::ASTOpSwitch::FCase`  
`struct FCase`  
_L34-50_
- L38 _public function_ `explicit FCase(FInvalidTag) : Branch(ASTChild::FInvalidTag())`
- L40 _public function_ `FCase(int32 cond, Ptr<ASTOp> parent, Ptr<ASTOp> b) : Condition(cond) , Branch(parent.get(), b)`
- L46 _public member_ `int32 Condition;`
- L47 _public member_ `ASTChild Branch;`
- L49 _public prototype_ `bool operator==(const FCase& other) const = default;`

#### struct `UE::Mutable::Private::ASTOpSwitch::FCase::FInvalidTag`  
`struct FInvalidTag`  
_L36-36_

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Mutable` (scope `UE`)
- L12 _namespace_ `namespace Private` (scope `UE::Mutable`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/CodeGenerator.h` (Private)


#### class `UE::Mutable::Private::CodeGenerator`  
`class CodeGenerator`  
_L154-1360_
- desc: Converts UE::Mutable::Private::Node graphs into ASTOp graphs.
- L163 _public prototype_ `CodeGenerator( CompilerOptions::Private*, TFunction<void()>& InWaitCallback );`
- L164 _public prototype_ `~CodeGenerator();`
- L167 _public prototype_ `void GenerateRoot( const Ptr<const Node> );` — Data will be stored in States
- L169 _public prototype_ `void WaitTask(Tasks::FTask Task);`
- L174 _public member_ `TFunction<void()> WaitCallback;` — This function will be called repeatedly in case a synchronization between threads is necessary. It can be called from any thread.
- L178 _public function_ `friend FORCEINLINE uint32 GetTypeHash(const FGenericGenerationOptions& InKey)`
- L274 _public function_ `friend FORCEINLINE uint32 GetTypeHash(const FGeneratedCacheKey& InKey)`
- L307 _public function_ `friend FORCEINLINE uint32 GetTypeHash(const FGeneratedSkeletalMeshCacheKey& InKey)`
- L322 _public prototype_ `void GenerateGeneric(const FGenericGenerationOptions& Options, FGenericGenerationResult& OutResult, const Ptr<const Node> InNode);`
- L327 _public prototype_ `FLODTask GenerateLOD(const FLODGenerationOptions&, const NodeLOD*, FLODTask PreviousLODTask);` — Launch the tasks to generate a LOD subgraph. Since LODs need to be generated in order a dependency task representing the previous LOD generation can be specified.
- L331 _public prototype_ `FSurfaceTask GenerateSurface(const FSurfaceGenerationOptions&, Ptr<const NodeSurfaceNew>, FLODTask PreviousLODTask);` — Launch the tasks to generate a Surface subgraph.
- L339 _public function_ `friend FORCEINLINE uint32 GetTypeHash(const FGeneratedObjectCacheKey& InKey)`
- L383 _public typedef_ `typedef TMap<FGeneratedObjectCacheKey, FObjectGenerationResult> FGeneratedObjectsMap;`
- L384 _public member_ `FGeneratedObjectsMap GeneratedObjects;`
- L386 _public prototype_ `void GenerateObject(const FObjectGenerationOptions&, FObjectGenerationResult&, const NodeObject*);`
- L387 _public prototype_ `void GenerateObject_New(const FObjectGenerationOptions&, FObjectGenerationResult&, const NodeObjectNew*);`
- L388 _public prototype_ `void GenerateObject_Group(const FObjectGenerationOptions&, FObjectGenerationResult&, const NodeObjectGroup*);`
- L393 _public member_ `const CompilerOptions::Private* CompilerOptions = nullptr;`
- L396 _public member_ `FirstPassGenerator FirstPass;`
- L399 _public member_ `TSharedPtr<FErrorLog> ErrorLog;` — Used to accumulate all generation error messages.
- L402 _public typedef_ `typedef TArray< TPair<FObjectState, Ptr<ASTOp>> > FStateList;` — After the entire code generation this contains the information about all the states.
- L403 _public member_ `FStateList States;`
- L408 _private member_ `UE::Tasks::FPipe LocalPipe;` — Any task accessing generic CodeGenerator members or "serial" data should run in this pipe.
- L425 _private member_ `FGenerateMeshConstantState GenerateMeshConstantState;`
- L437 _private member_ `FUniqueMeshIds UniqueMeshIds;`
- L440 _private member_ `UE::Tasks::FPipe GenerateMeshConstantPipe;` — Any task accessing GenerateMeshConstantState should run in this pipe.
- L449 _private function_ `friend FORCEINLINE uint32 GetTypeHash(const FTableCacheKey& InKey)`
- L469 _private member_ `FGeneratedTableNodes GeneratedTableNodes;`
- L477 _private member_ `TArray<FConditionalExtensionDataOp> ConditionalExtensionDataOps;`
- L484 _private function_ `friend FORCEINLINE uint32 GetTypeHash(const FGeneratedComponentCacheKey& InKey)`
- L498 _private typedef_ `typedef TMap<FGeneratedComponentCacheKey, FGenericGenerationResult> FGeneratedComponentMap;`
- L499 _private member_ `FGeneratedComponentMap GeneratedComponents;`
- L501 _private prototype_ `void GenerateComponent(const FComponentGenerationOptions&, FGenericGenerationResult&, const NodeComponent*);`
- L502 _private prototype_ `void GenerateComponent_New(const FComponentGenerationOptions&, FGenericGenerationResult&, const NodeComponentNew*);`
- L503 _private prototype_ `void GenerateComponent_Switch(const FComponentGenerationOptions&, FGenericGenerationResult&, const NodeComponentSwitch*);`
- L504 _private prototype_ `void GenerateComponent_Variation(const FComponentGenerationOptions&, FGenericGenerationResult&, const NodeComponentVariation*);`
- L507 _private prototype_ `Ptr<NodeScalar> GenerateTableVariableNode(const Node&, const FTableCacheKey&, bool bAddNoneOption, const FString& DefaultRowName);`
- L510 _private prototype_ `Ptr<ASTOp> GenerateMissingBoolCode(const TCHAR* strWhere, bool value, const void* errorContext );`
- L519 _private prototype_ `Ptr<ASTOpImagePixelFormat> GenerateFormatExpression(const NodeImageFormat* NodeFormat, Ptr<ASTOp> SubExpression, EYesNoQuery CanNormalLAEncode);`
- L523 _private prototype_ `template<class NODE_TABLE, ETableColumnType TYPE, EOpType OPTYPE, typename F> Ptr<ASTOp> GenerateTableSwitch( const NODE_TABLE& node, F&& GenerateOption );`
- L526 _private prototype_ `template<class NODE_TABLE, ETableColumnType TYPE, class NODE_TYPE, class NODE_SWITCH_TYPE, typename F> void GenerateTableSwitchNode(const NODE_TABLE& node, Ptr<NODE_SWITCH_TYPE>& OutResult, F&& GenerateOption);`
- L563 _private function_ `friend FORCEINLINE uint32 GetTypeHash(const FImageGenerationOptions& InKey)`
- L599 _private function_ `friend FORCEINLINE uint32 GetTypeHash(const FGeneratedImageCacheKey& InKey)`
- L610 _private typedef_ `typedef TMap<FGeneratedImageCacheKey, FImageGenerationResult> FGeneratedImagesMap;`
- L616 _private member_ `FGeneratedImages GeneratedImages;`
- L618 _private prototype_ `void GenerateImage(const FImageGenerationOptions&, FImageGenerationResult& result, const NodeImagePtrConst& node);`
- L619 _private prototype_ `void GenerateImage_Constant(const FImageGenerationOptions&, FImageGenerationResult&, const NodeImageConstant*);`
- L620 _private prototype_ `void GenerateImage_Interpolate(const FImageGenerationOptions&, FImageGenerationResult&, const NodeImageInterpolate*);`
- L621 _private prototype_ `void GenerateImage_Saturate(const FImageGenerationOptions&, FImageGenerationResult&, const NodeImageSaturate*);`
- L622 _private prototype_ `void GenerateImage_Table(const FImageGenerationOptions&, FImageGenerationResult&, const NodeImageTable*);`
- L623 _private prototype_ `void GenerateImage_Swizzle(const FImageGenerationOptions&, FImageGenerationResult&, const NodeImageSwizzle*);`
- L624 _private prototype_ `void GenerateImage_ColorMap(const FImageGenerationOptions&, FImageGenerationResult&, const NodeImageColorMap*);`
- L625 _private prototype_ `void GenerateImage_Binarise(const FImageGenerationOptions&, FImageGenerationResult&, const NodeImageBinarise*);`
- L626 _private prototype_ `void GenerateImage_Luminance(const FImageGenerationOptions&, FImageGenerationResult&, const NodeImageLuminance*);`
- L627 _private prototype_ `void GenerateImage_Layer(const FImageGenerationOptions&, FImageGenerationResult&, const NodeImageLayer*);`
- L628 _private prototype_ `void GenerateImage_LayerColor(const FImageGenerationOptions&, FImageGenerationResult&, const NodeImageLayerColor*);`
- L629 _private prototype_ `void GenerateImage_Resize(const FImageGenerationOptions&, FImageGenerationResult&, const NodeImageResize*);`
- L630 _private prototype_ `void GenerateImage_PlainColor(const FImageGenerationOptions&, FImageGenerationResult&, const NodeImagePlainColor*);`
- L631 _private prototype_ `void GenerateImage_Project(const FImageGenerationOptions&, FImageGenerationResult&, const NodeImageProject*);`
- L632 _private prototype_ `void GenerateImage_Mipmap(const FImageGenerationOptions&, FImageGenerationResult&, const NodeImageMipmap*);`
- L633 _private prototype_ `void GenerateImage_Switch(const FImageGenerationOptions&, FImageGenerationResult&, const NodeImageSwitch*);`
- L634 _private prototype_ `void GenerateImage_Conditional(const FImageGenerationOptions&, FImageGenerationResult&, const NodeImageConditional*);`
- L635 _private prototype_ `void GenerateImage_Format(const FImageGenerationOptions&, FImageGenerationResult&, const NodeImageFormat*);`
- L636 _private prototype_ `void GenerateImage_Conform(const FImageGenerationOptions&, FImageGenerationResult&, const NodeImageConform*);`
- L637 _private prototype_ `void GenerateImage_Parameter(const FImageGenerationOptions&, FImageGenerationResult&, const NodeImageObjectParameter*);`
- L638 _private prototype_ `void GenerateImage_MultiLayer(const FImageGenerationOptions&, FImageGenerationResult&, const NodeImageMultiLayer*);`
- L639 _private prototype_ `void GenerateImage_Invert(const FImageGenerationOptions&, FImageGenerationResult&, const NodeImageInvert*);`
- L640 _private prototype_ `void GenerateImage_Variation(const FImageGenerationOptions&, FImageGenerationResult&, const NodeImageVariation*);`
- L641 _private prototype_ `void GenerateImage_NormalComposite(const FImageGenerationOptions&, FImageGenerationResult&, const NodeImageNormalComposite*);`
- L642 _private prototype_ `void GenerateImage_Transform(const FImageGenerationOptions&, FImageGenerationResult&, const NodeImageTransform*);`
- L643 _private prototype_ `void GenerateImage_MaterialBreak(const FImageGenerationOptions&, FImageGenerationResult&, const NodeImageMaterialBreak*);`
- L644 _private prototype_ `void GenerateImage_FromMaterialParameter(const FImageGenerationOptions&, FImageGenerationResult&, const NodeImageFromMaterialParameter*);`
- L645 _private prototype_ `void GenerateImage_External(const FImageGenerationOptions&, FImageGenerationResult&, const NodeImageExternal*);`
- L646 _private prototype_ `void GenerateImage_ParameterConvert(const FImageGenerationOptions&, FImageGenerationResult&, const NodeImageConvert*);`
- L648 _private prototype_ `void GenerateCrop(const FImageGenerationOptions& Options, FImageGenerationResult& Result, const NodeImage&);`
- L651 _private prototype_ `TManagedPtr<FImage> GenerateMissingImage(EImageFormat);`
- L654 _private prototype_ `Ptr<ASTOp> GenerateMissingImageCode(const TCHAR* strWhere, EImageFormat, const void* errorContext, const FImageGenerationOptions& Options);`
- L657 _private prototype_ `Ptr<ASTOp> GeneratePlainImageCode(const FVector4f& Color, const FImageGenerationOptions& Options);`
- L660 _private prototype_ `Ptr<ASTOp> GenerateImageFormat(Ptr<ASTOp>, EImageFormat);`
- L663 _private prototype_ `Ptr<ASTOp> GenerateImageSize(Ptr<ASTOp>, UE::Math::TIntVector2<int32>);`
- L666 _private prototype_ `Ptr<ASTOp> GenerateImageMulticompose(Ptr<ASTOp> BaseOp, Ptr<ASTOp> LayoutOp, const FImageGenerationOptions& Options, const NodeImagePtrConst& NodeImage, TManagedPtr<const FLayout> SourceLayout, const CodeGenerator::FLayoutBlockDesc& InLayoutBlockDesc );`
- L669 _private prototype_ `TManagedPtr<FImage> GenerateImageBlockPatchMask(const NodeSurfaceModifierSurfaceEdit::FTexture&, FIntPoint GridSize, int32 BlockPixelsX, int32 BlockPixelsY, box<FIntVector2> RectInCells);` — Generate a layout block-sized image with a mask including all pixels in the blocks defined in the patch node.
- L672 _private prototype_ `Ptr<ASTOp> GenerateImageBlockPatch(Ptr<ASTOp> BlockOp, const NodeSurfaceModifierSurfaceEdit::FTexture&, TManagedPtr<FImage> PatchMask, Ptr<ASTOp> ConditionOp, const FImageGenerationOptions&);` — Generate all the operations to apply the block patching on top of the BlockOp, and masking with PatchMask.
- L710 _private function_ `friend FORCEINLINE uint32 GetTypeHash(const FMaterialGenerationOptions& Options)`
- L732 _private function_ `friend FORCEINLINE uint32 GetTypeHash(const FGeneratedMaterialCacheKey& InKey)`
- L745 _private typedef_ `typedef TMap<FGeneratedMaterialCacheKey, FMaterialGenerationResult> FGeneratedMaterialsMap;`
- L751 _private member_ `FGeneratedMaterials GeneratedMaterials;`
- L753 _private prototype_ `void GenerateMaterial(const FMaterialGenerationOptions&, FMaterialGenerationResult& result, const Ptr<const NodeMaterial>& node);`
- L754 _private prototype_ `void GenerateMaterial_Constant(const FMaterialGenerationOptions&, FMaterialGenerationResult& result, const NodeMaterialConstant* node);`
- L755 _private prototype_ `void GenerateMaterial_Switch(const FMaterialGenerationOptions&, FMaterialGenerationResult& result, const NodeMaterialSwitch* node);`
- L756 _private prototype_ `void GenerateMaterial_Table(const FMaterialGenerationOptions&, FMaterialGenerationResult& result, const NodeMaterialTable* node);`
- L757 _private prototype_ `void GenerateMaterial_Variation(const FMaterialGenerationOptions&, FMaterialGenerationResult& result, const NodeMaterialVariation* node);`
- L758 _private prototype_ `void GenerateMaterial_Parameter(const FMaterialGenerationOptions&, FMaterialGenerationResult& result, const NodeMaterialParameter* node);`
- L759 _private prototype_ `void GenerateMaterial_External(const FMaterialGenerationOptions&, FMaterialGenerationResult& result, const NodeMaterialExternal* node);`
- L760 _private prototype_ `void GenerateMaterial_BreakSkeletalMeshObject(const FMaterialGenerationOptions&, FMaterialGenerationResult& OutResult, const NodeMaterialSkeletalMeshObjectBreak* InNode);`
- L761 _private prototype_ `void GenerateMaterial_BreakSkeletalMesh(const FMaterialGenerationOptions&, FMaterialGenerationResult& OutResult, const NodeMaterialSkeletalMeshBreak* InNode);`
- L762 _private prototype_ `void GenerateMaterial_Modify(const FMaterialGenerationOptions&, FMaterialGenerationResult& result, const NodeMaterialModify* node);`
- L765 _private prototype_ `Ptr<ASTOp> GenerateMissingMaterialCode(const TCHAR* strWhere, const void* ErrorContext);`
- L825 _private typedef_ `using FMeshOptionsTask = UE::Tasks::TTask<CodeGenerator::FMeshGenerationDynamicOptions>;`
- L840 _private member_ `FBaseMeshResultOptions BaseMeshOptions;`
- L869 _private member_ `FExtraLayoutsResultOptions ExtraLayoutsOptions;`
- L906 _private member_ `FSharedSurfaceResultOptions SharedSurfaceOptions;`
- L932 _private member_ `FGenerateLayoutConstantState GenerateLayoutConstantState;`
- L934 _private prototype_ `FMeshTask GenerateMesh(const FMeshGenerationStaticOptions&, FMeshOptionsTask, const Ptr<const NodeMesh>&);`
- L935 _private prototype_ `FMeshTask GenerateMesh_Constant(const FMeshGenerationStaticOptions&, FMeshOptionsTask, const NodeMeshConstant*);`
- L936 _private prototype_ `FMeshTask GenerateMesh_Format(const FMeshGenerationStaticOptions&, FMeshOptionsTask, const NodeMeshFormat*);`
- L937 _private prototype_ `FMeshTask GenerateMesh_Morph(const FMeshGenerationStaticOptions&, FMeshOptionsTask, const NodeMeshMorph*);`
- L938 _private prototype_ `FMeshTask GenerateMesh_MakeMorph(const FMeshGenerationStaticOptions&, FMeshOptionsTask, const NodeMeshMakeMorph*);`
- L939 _private prototype_ `FMeshTask GenerateMesh_Fragment(const FMeshGenerationStaticOptions&, FMeshOptionsTask, const NodeMeshFragment*);`
- L940 _private prototype_ `FMeshTask GenerateMesh_Switch(const FMeshGenerationStaticOptions&, FMeshOptionsTask, const NodeMeshSwitch*);`
- L941 _private prototype_ `FMeshTask GenerateMesh_Transform(const FMeshGenerationStaticOptions&, FMeshOptionsTask, const NodeMeshTransform*);`
- L942 _private prototype_ `FMeshTask GenerateMesh_ClipMorphPlane(const FMeshGenerationStaticOptions&, FMeshOptionsTask, const NodeMeshClipMorphPlane*);`
- L943 _private prototype_ `FMeshTask GenerateMesh_ClipWithMesh(const FMeshGenerationStaticOptions&, FMeshOptionsTask, const NodeMeshClipWithMesh*);`
- L944 _private prototype_ `FMeshTask GenerateMesh_ApplyPose(const FMeshGenerationStaticOptions&, FMeshOptionsTask, const NodeMeshApplyPose*);`
- L945 _private prototype_ `FMeshTask GenerateMesh_RemoveMesh(const FMeshGenerationStaticOptions&, FMeshOptionsTask, const NodeMeshRemoveMesh*);`
- L946 _private prototype_ `FMeshTask GenerateMesh_TransformWithBone(const FMeshGenerationStaticOptions&, FMeshOptionsTask, const NodeMeshTransformWithBone*);`
- L947 _private prototype_ `FMeshTask GenerateMesh_TransformInMesh(const FMeshGenerationStaticOptions&, const FMeshOptionsTask, const NodeMeshTransformInMesh*);`
- L948 _private prototype_ `FMeshTask GenerateMesh_Variation(const FMeshGenerationStaticOptions&, FMeshOptionsTask, const NodeMeshVariation*);`
- L949 _private prototype_ `FMeshTask GenerateMesh_Table(const FMeshGenerationStaticOptions&, FMeshOptionsTask, const NodeMeshTable*);`
- L950 _private prototype_ `FMeshTask GenerateMesh_Reshape(const FMeshGenerationStaticOptions&, FMeshOptionsTask, const NodeMeshReshape*);`
- L951 _private prototype_ `FMeshTask GenerateMesh_ClipDeform(const FMeshGenerationStaticOptions&, FMeshOptionsTask, const NodeMeshClipDeform*);`
- L952 _private prototype_ `FMeshTask GenerateMesh_SkeletalMeshBreak(const FMeshGenerationStaticOptions&, FMeshOptionsTask, const NodeMeshSkeletalMeshObjectBreak*);`
- L953 _private prototype_ `FMeshTask GenerateMesh_External(const FMeshGenerationStaticOptions&, FMeshOptionsTask, const NodeMeshExternal*);`
- L955 _private prototype_ `Ptr<ASTOp> GenerateLayoutOpsAndResult(const FMeshGenerationDynamicOptions&, Ptr<ASTOp> LastMeshOp, const TArray<Ptr<NodeLayout>>& OriginalLayouts, uint32 MeshId, FMeshGenerationResult& OutResult);`
- L958 _private prototype_ `TManagedPtr<const FLayout> GenerateLayout(Ptr<const NodeLayout> SourceLayout, uint32 MeshIDPrefix);`
- L968 _private typedef_ `typedef TMap<FGeneratedSkeletalMeshCacheKey, FSkeletalMeshGenerationResult> FGeneratedSkeletalMeshesMap;`
- L975 _private member_ `FGeneratedSkeletalMeshes GeneratedSkeletalMeshes;`
- L977 _private prototype_ `void GenerateSkeletalMesh(FSkeletalMeshGenerationResult& OutResult, const FSkeletalMeshGenerationOptions&, const Ptr<const NodeSkeletalMesh>&);`
- L978 _private prototype_ `void GenerateSkeletalMesh_New(FSkeletalMeshGenerationResult& OutResult, const FSkeletalMeshGenerationOptions&, const NodeSkeletalMeshNew*);`
- L979 _private prototype_ `void GenerateSkeletalMesh_Convert(FSkeletalMeshGenerationResult& OutResult, const FSkeletalMeshGenerationOptions&, const NodeSkeletalMeshConvert*);`
- L980 _private prototype_ `void GenerateSkeletalMesh_Merge(FSkeletalMeshGenerationResult& OutResult, const FSkeletalMeshGenerationOptions&, const NodeSkeletalMeshMerge*);`
- L981 _private prototype_ `void GenerateSkeletalMesh_Switch(FSkeletalMeshGenerationResult& OutResult, const FSkeletalMeshGenerationOptions&, const NodeSkeletalMeshSwitch*);`
- L982 _private prototype_ `void GenerateSkeletalMesh_Variation(FSkeletalMeshGenerationResult& OutResult, const FSkeletalMeshGenerationOptions&, const NodeSkeletalMeshVariation*);`
- L983 _private prototype_ `void GenerateSkeletalMesh_Morph(FSkeletalMeshGenerationResult& OutResult, const FSkeletalMeshGenerationOptions&, const NodeSkeletalMeshMorph*);`
- L984 _private prototype_ `void GenerateSkeletalMesh_Reshape(FSkeletalMeshGenerationResult& OutResult, const FSkeletalMeshGenerationOptions&, const NodeSkeletalMeshReshape*);`
- L985 _private prototype_ `void GenerateSkeletalMesh_Modify(FSkeletalMeshGenerationResult& OutResult, const FSkeletalMeshGenerationOptions&, const NodeSkeletalMeshModify*);`
- L986 _private prototype_ `void GenerateSkeletalMesh_Transform(FSkeletalMeshGenerationResult& OutResult, const FSkeletalMeshGenerationOptions&, const NodeSkeletalMeshTransform*);`
- L987 _private prototype_ `void GenerateSkeletalMesh_TransformWithBone(FSkeletalMeshGenerationResult& OutResult, const FSkeletalMeshGenerationOptions&, const NodeSkeletalMeshTransformWithBone*);`
- L988 _private prototype_ `void GenerateSkeletalMesh_ClipWithSkeletalMesh(FSkeletalMeshGenerationResult& OutResult, const FSkeletalMeshGenerationOptions&, const NodeSkeletalMeshClipWithSkeletalMesh*);`
- L998 _private typedef_ `typedef TMap<FGeneratedCacheKey, FSkeletalMeshObjectGenerationResult> FGeneratedSkeletalMeshObjectsMap;`
- L1005 _private member_ `FGeneratedSkeletalMeshObjects GeneratedSkeletalMeshObjects;`
- L1006 _private prototype_ `void GenerateSkeletalMeshObject(FSkeletalMeshObjectGenerationResult& Result, const FSkeletalMeshGenerationOptions&, const Ptr<const NodeSkeletalMeshObject>&);`
- L1007 _private prototype_ `void GenerateSkeletalMeshObject_Convert(FSkeletalMeshObjectGenerationResult& Result, const FSkeletalMeshGenerationOptions&, const NodeSkeletalMeshObjectConvert*);`
- L1008 _private prototype_ `void GenerateSkeletalMeshObject_Parameter(FSkeletalMeshObjectGenerationResult& Result, const FSkeletalMeshGenerationOptions&, const NodeSkeletalMeshObjectParameter*);`
- L1009 _private prototype_ `void GenerateSkeletalMeshObject_Switch(FSkeletalMeshObjectGenerationResult& Result, const FSkeletalMeshGenerationOptions&, const NodeSkeletalMeshObjectSwitch*);`
- L1043 _private function_ `friend uint32 GetTypeHash(const FExternalGenerationOptions& InKey)`
- L1092 _private function_ `friend uint32 GetTypeHash(const FGeneratedExternalCacheKey& InKey)`
- L1105 _private typedef_ `typedef TMap<FGeneratedExternalCacheKey, FExternalTask> FGeneratedExternalMap;`
- L1111 _private member_ `FGeneratedExternal GeneratedExternal;`
- L1113 _private prototype_ `FExternalTask GenerateExternal(const FExternalGenerationOptions& Options, const Ptr<const NodeExternal>& ExternalNode);`
- L1114 _private prototype_ `FExternalTask GenerateExternal_Operation(const FExternalGenerationOptions& Options, const Ptr<const NodeExternalOperation>& ExternalNode);`
- L1115 _private prototype_ `FExternalTask GenerateExternal_Parameter(const FExternalGenerationOptions& Options, const Ptr<const NodeExternalParameter>& ExtensionNode);`
- L1116 _private prototype_ `FExternalTask GenerateExternal_Switch(const FExternalGenerationOptions& Options, const Ptr<const NodeExternalSwitch>& ExtensionNode);`
- L1117 _private prototype_ `Ptr<ASTOp> GenerateMissingExternalCode(const TCHAR* StrWhere, const void* ErrorContext);`
- L1126 _private typedef_ `typedef const NodeExtensionData* FGeneratedExtensionDataCacheKey;`
- L1127 _private typedef_ `typedef TMap<FGeneratedExtensionDataCacheKey, FExtensionDataGenerationResult> FGeneratedExtensionDataMap;`
- L1128 _private member_ `FGeneratedExtensionDataMap GeneratedExtensionData;`
- L1130 _private prototype_ `void GenerateExtensionData(FExtensionDataGenerationResult& OutResult, const FGenericGenerationOptions&, const Ptr<const NodeExtensionData>&);`
- L1131 _private prototype_ `void GenerateExtensionData_Constant(FExtensionDataGenerationResult& OutResult, const FGenericGenerationOptions&, const class NodeExtensionDataConstant*);`
- L1132 _private prototype_ `void GenerateExtensionData_Switch(FExtensionDataGenerationResult& OutResult, const FGenericGenerationOptions&, const class NodeExtensionDataSwitch*);`
- L1133 _private prototype_ `void GenerateExtensionData_Variation(FExtensionDataGenerationResult& OutResult, const FGenericGenerationOptions&, const class NodeExtensionDataVariation*);`
- L1134 _private prototype_ `Ptr<ASTOp> GenerateMissingExtensionDataCode(const TCHAR* StrWhere, const void* ErrorContext);`
- L1144 _private typedef_ `typedef TMap<FGeneratedCacheKey,FProjectorGenerationResult> FGeneratedProjectorsMap;`
- L1150 _private member_ `FGeneratedProjectors GeneratedProjectors;`
- L1152 _private prototype_ `void GenerateProjector( FProjectorGenerationResult&, const FGenericGenerationOptions&, const Ptr<const NodeProjector>& );`
- L1153 _private prototype_ `void GenerateProjector_Constant( FProjectorGenerationResult&, const FGenericGenerationOptions&, const Ptr<const NodeProjectorConstant>& );`
- L1154 _private prototype_ `void GenerateProjector_Parameter( FProjectorGenerationResult&, const FGenericGenerationOptions&, const Ptr<const NodeProjectorParameter>& );`
- L1155 _private prototype_ `void GenerateMissingProjectorCode( FProjectorGenerationResult&, const void* errorContext );`
- L1164 _private typedef_ `typedef TMap<FGeneratedCacheKey, FBoolGenerationResult> FGeneratedBoolsMap;`
- L1170 _private member_ `FGeneratedBools GeneratedBools;`
- L1172 _private prototype_ `void GenerateBool(FBoolGenerationResult&, const FGenericGenerationOptions&, const Ptr<const NodeBool>&);`
- L1173 _private prototype_ `void GenerateBool_Constant(FBoolGenerationResult&, const FGenericGenerationOptions&, const Ptr<const NodeBoolConstant>&);`
- L1174 _private prototype_ `void GenerateBool_Parameter(FBoolGenerationResult&, const FGenericGenerationOptions&, const Ptr<const NodeBoolParameter>&);`
- L1175 _private prototype_ `void GenerateBool_Not(FBoolGenerationResult&, const FGenericGenerationOptions&, const Ptr<const NodeBoolNot>&);`
- L1176 _private prototype_ `void GenerateBool_And(FBoolGenerationResult&, const FGenericGenerationOptions&, const Ptr<const NodeBoolAnd>&);`
- L1185 _private typedef_ `typedef TMap<FGeneratedCacheKey, FScalarGenerationResult> FGeneratedScalarsMap;`
- L1192 _private member_ `FGeneratedScalars GeneratedScalars;`
- L1194 _private prototype_ `void GenerateScalar(FScalarGenerationResult&, const FGenericGenerationOptions&, const Ptr<const NodeScalar>&);`
- L1195 _private prototype_ `void GenerateScalar_Constant(FScalarGenerationResult&, const FGenericGenerationOptions&, const Ptr<const NodeScalarConstant>&);`
- L1196 _private prototype_ `void GenerateScalar_Parameter(FScalarGenerationResult&, const FGenericGenerationOptions&, const Ptr<const NodeScalarParameter>&);`
- L1197 _private prototype_ `void GenerateScalar_Switch(FScalarGenerationResult&, const FGenericGenerationOptions&, const Ptr<const NodeScalarSwitch>&);`
- L1198 _private prototype_ `void GenerateScalar_EnumParameter(FScalarGenerationResult&, const FGenericGenerationOptions&, const Ptr<const NodeScalarEnumParameter>&);`
- L1199 _private prototype_ `void GenerateScalar_Curve(FScalarGenerationResult&, const FGenericGenerationOptions&, const Ptr<const NodeScalarCurve>&);`
- L1200 _private prototype_ `void GenerateScalar_Arithmetic(FScalarGenerationResult&, const FGenericGenerationOptions&, const Ptr<const NodeScalarArithmeticOperation>&);`
- L1201 _private prototype_ `void GenerateScalar_Variation(FScalarGenerationResult&, const FGenericGenerationOptions&, const Ptr<const NodeScalarVariation>&);`
- L1202 _private prototype_ `void GenerateScalar_Table(FScalarGenerationResult&, const FGenericGenerationOptions&, const Ptr<const NodeScalarTable>&);`
- L1203 _private prototype_ `void GenerateScalar_MaterialBreak(FScalarGenerationResult&, const FGenericGenerationOptions&, const Ptr<const NodeScalarMaterialBreak>&);`
- L1204 _private prototype_ `void GenerateScalar_External(FScalarGenerationResult&, const FGenericGenerationOptions&, const Ptr<const NodeScalarExternal>&);`
- L1205 _private prototype_ `Ptr<ASTOp> GenerateMissingScalarCode(const TCHAR* strWhere, float value, const void* errorContext);`
- L1214 _private typedef_ `typedef TMap<FGeneratedCacheKey, FColorGenerationResult> FGeneratedColorsMap;`
- L1220 _private member_ `FGeneratedColors GeneratedColors;`
- L1222 _private prototype_ `void GenerateColor(FColorGenerationResult&, const FGenericGenerationOptions&, const Ptr<const NodeColor>&);`
- L1223 _private prototype_ `void GenerateColor_Constant(FColorGenerationResult&, const FGenericGenerationOptions&, const Ptr<const NodeColorConstant>&);`
- L1224 _private prototype_ `void GenerateColor_Parameter(FColorGenerationResult&, const FGenericGenerationOptions&, const Ptr<const NodeColorParameter>&);`
- L1225 _private prototype_ `void GenerateColor_Switch(FColorGenerationResult&, const FGenericGenerationOptions&, const Ptr<const NodeColorSwitch>&);`
- L1226 _private prototype_ `void GenerateColor_SampleImage(FColorGenerationResult&, const FGenericGenerationOptions&, const Ptr<const NodeColorSampleImage>&);`
- L1227 _private prototype_ `void GenerateColor_FromScalars(FColorGenerationResult&, const FGenericGenerationOptions&, const Ptr<const NodeColorFromScalars>&);`
- L1228 _private prototype_ `void GenerateColor_Arithmetic(FColorGenerationResult&, const FGenericGenerationOptions&, const Ptr<const NodeColorArithmeticOperation>&);`
- L1229 _private prototype_ `void GenerateColor_Variation(FColorGenerationResult&, const FGenericGenerationOptions&, const Ptr<const NodeColorVariation>&);`
- L1230 _private prototype_ `void GenerateColor_ToSRGB(FColorGenerationResult&, const FGenericGenerationOptions&, const Ptr<const NodeColorToSRGB>&);`
- L1231 _private prototype_ `void GenerateColor_Table(FColorGenerationResult&, const FGenericGenerationOptions&, const Ptr<const NodeColorTable>&);`
- L1232 _private prototype_ `void GenerateColor_MaterialBreak(FColorGenerationResult&, const FGenericGenerationOptions&, const Ptr<const NodeColorMaterialBreak>&);`
- L1233 _private prototype_ `void GenerateColor_External(FColorGenerationResult&, const FGenericGenerationOptions&, const Ptr<const NodeColorExternal>&);`
- L1234 _private prototype_ `Ptr<ASTOp> GenerateMissingColorCode(const TCHAR* strWhere, const void* errorContext);`
- L1243 _private typedef_ `typedef TMap<FGeneratedCacheKey, FStringGenerationResult> FGeneratedStringsMap;`
- L1249 _private member_ `FGeneratedStrings GeneratedStrings;`
- L1251 _private prototype_ `void GenerateString(FStringGenerationResult&, const FGenericGenerationOptions&, const Ptr<const NodeString>&);`
- L1252 _private prototype_ `void GenerateString_Constant(FStringGenerationResult&, const FGenericGenerationOptions& Options, const Ptr<const NodeStringConstant>&);`
- L1253 _private prototype_ `void GenerateString_Parameter(FStringGenerationResult&, const FGenericGenerationOptions& Options, const Ptr<const NodeStringParameter>&);`
- L1262 _private typedef_ `typedef TMap<FGeneratedCacheKey, FMatrixGenerationResult> FGeneratedMatrixMap;`
- L1268 _private member_ `FGeneratedMatrices GeneratedMatrices;`
- L1270 _private prototype_ `void GenerateMatrix(FMatrixGenerationResult&, const FGenericGenerationOptions&, const Ptr<const NodeMatrix>&);`
- L1271 _private prototype_ `void GenerateMatrix_Constant(FMatrixGenerationResult&, const FGenericGenerationOptions&, const Ptr<const NodeMatrixConstant>&);`
- L1272 _private prototype_ `void GenerateMatrix_Parameter(FMatrixGenerationResult&, const FGenericGenerationOptions&, const Ptr<const NodeMatrixParameter>&);`
- L1288 _private typedef_ `typedef TMap<FGeneratedCacheKey,FRangeGenerationResult> FGeneratedRangeMap;`
- L1294 _private member_ `FGeneratedRanges GeneratedRanges;`
- L1296 _private prototype_ `void GenerateRange(FRangeGenerationResult&, const FGenericGenerationOptions&, Ptr<const NodeRange>);`
- L1308 _private prototype_ `void UpdateLayoutBlockDesc(FLayoutBlockDesc& Out, FImageDesc BlockDesc, FIntVector2 LayoutCellSize);`
- L1311 _private prototype_ `void GetModifiersFor(int32 ComponentId, const TArray<FString>& SurfaceTags, bool bModifiersForBeforeOperations, TArray<FirstPassGenerator::FModifier>& OutModifiers) const;` — Get the modifiers that have to be applied to elements with a specific tag.
- L1314 _private prototype_ `FMeshTask ApplyMeshModifiers( const TArray<FirstPassGenerator::FModifier>&, const FMeshGenerationStaticOptions&, FMeshOptionsTask DynamicOptionsTask, FMeshTask BaseTask, FGuid SurfaceGuid, const void* ErrorContext, const NodeMesh* OriginalMeshNode);` — Apply the required mesh modifiers to the given operation.
- L1323 _private prototype_ `Ptr<ASTOp> ApplyImageBlockModifiers( const TArray<FirstPassGenerator::FModifier>&, const FImageGenerationOptions&, Ptr<ASTOp> BaseImageOp, const FParameterKey& ImageParameterKey, FIntPoint GridSize, const FLayoutBlockDesc& LayoutBlockDesc, box< FIntVector2 > RectInCells, const void* ErrorContext);`
- L1333 _private prototype_ `Ptr<ASTOp> ApplyImageExtendModifiers( const TArray<FirstPassGenerator::FModifier>&, const FMeshGenerationStaticOptions& Options, const FMeshGenerationResult& BaseMeshResults, Ptr<ASTOp> ImageAd, CompilerOptions::TextureLayoutStrategy ImageLayoutStrategy, int32 LayoutIndex, const FParameterKey& ImageParameterKey, FIntPoint GridSize, CodeGenerator::FLayoutBlockDesc& InOutLayoutBlockDesc, const void* ModifiedNodeErrorContext);`
- L1345 _private prototype_ `void CheckModifiersForSurface(const NodeSurfaceNew&, const TArray<FirstPassGenerator::FModifier>&, int32 LODIndex);`
- L1347 _private prototype_ `bool HasImageBlockModifiers(const FParameterKey& ImageKey, const TArray<FirstPassGenerator::FModifier>&, int32 LODIndex) const;`
- L1349 _private prototype_ `void GenerateMaterialImage( const TPair<FParameterKey, FImageParameterData>& ImageData, FImageGenerationResult& OutImageGenerated, const TArray<FirstPassGenerator::FModifier>& Modifiers, const int32 State, const int32 ComponentId, const int32 LODIndex, const TArray<FString>& Tags, const FMeshGenerationResult& MeshResults, const TBitArray<>& LayoutFromExtension, const void* ErrorContext);`
- L1365 _function_ `template<class NODE_TABLE, ETableColumnType TYPE, EOpType OPTYPE, typename F> Ptr<ASTOp> CodeGenerator::GenerateTableSwitch( const NODE_TABLE& node, F&& GenerateOption )`
- L1442 _function_ `template<class NODE_TABLE, ETableColumnType TYPE, class NODE_TYPE, class NODE_SWITCH_TYPE, typename F> void CodeGenerator::GenerateTableSwitchNode( const NODE_TABLE& node, Ptr<NODE_SWITCH_TYPE>& OutResult, F&& GenerateOption )`

#### struct `UE::Mutable::Private::CodeGenerator::FGenericGenerationOptions`  
`struct FGenericGenerationOptions`  
_L176-194_
- L188 _public member_ `int32 State = -1;`
- L189 _public member_ `TArray<FString> ActiveTags;`
- L192 _public member_ `bool bIsImage = false;` — Variable to identify if an operation will end up generating an image.

#### struct `UE::Mutable::Private::CodeGenerator::FObjectGenerationOptions`  
`struct FObjectGenerationOptions : public FGenericGenerationOptions`  
_L196-202_
- inherits: `FGenericGenerationOptions`
- L198 _public member_ `const NodeObjectNew* ParentObjectNode = nullptr;`
- L201 _public member_ `Ptr<ASTOp> CurrentObjectCondition;` — Condition that enables a specific object.

#### struct `UE::Mutable::Private::CodeGenerator::FComponentGenerationOptions`  
`struct FComponentGenerationOptions : public FGenericGenerationOptions`  
_L204-215_
- inherits: `FGenericGenerationOptions`
- L206 _public function_ `FComponentGenerationOptions(const FGenericGenerationOptions& BaseOptions, const Ptr<ASTOp>& InBaseInstance )`
- L214 _public member_ `Ptr<ASTOp> BaseInstance;` — Instance to which the possibly generated components should be added.

#### struct `UE::Mutable::Private::CodeGenerator::FSkeletalMeshGenerationOptions`  
`struct FSkeletalMeshGenerationOptions`  
_L217-229_
- L219 _public function_ `FSkeletalMeshGenerationOptions(const FGenericGenerationOptions& BaseOptions, const NodeComponentNew* InComponent) : GenericOptions(BaseOptions) , Component(InComponent)`
- L225 _public member_ `uint8 FirstLODAvailable = 0;`
- L226 _public member_ `uint8 NumLODs = 0;`
- L227 _public member_ `FGenericGenerationOptions GenericOptions;`
- L228 _public member_ `const NodeComponentNew* Component = nullptr;`

#### struct `UE::Mutable::Private::CodeGenerator::FLODGenerationOptions`  
`struct FLODGenerationOptions : public FGenericGenerationOptions`  
_L231-245_
- inherits: `FGenericGenerationOptions`
- L233 _public function_ `FLODGenerationOptions(const FGenericGenerationOptions& BaseOptions, int32 InLODIndex, const NodeComponentNew* InComponent, TConstArrayView<int32> InSurfaceIndices)`
- L242 _public member_ `const NodeComponentNew* Component = nullptr;`
- L243 _public member_ `int32 LODIndex;`
- L244 _public member_ `TConstArrayView<int32> SurfaceIndices;`

#### struct `UE::Mutable::Private::CodeGenerator::FSurfaceGenerationOptions`  
`struct FSurfaceGenerationOptions : public FGenericGenerationOptions`  
_L247-267_
- inherits: `FGenericGenerationOptions`
- L249 _public function_ `explicit FSurfaceGenerationOptions(const FGenericGenerationOptions& BaseOptions)`
- L257 _public function_ `explicit FSurfaceGenerationOptions(const FLODGenerationOptions& BaseOptions)`
- L265 _public member_ `const NodeComponentNew* Component = nullptr;`
- L266 _public member_ `int32 LODIndex = -1;`

#### struct `UE::Mutable::Private::CodeGenerator::FGeneratedCacheKey`  
`struct FGeneratedCacheKey`  
_L269-283_
- L271 _public member_ `Ptr<const Node> Node;`
- L272 _public member_ `FGenericGenerationOptions Options;`
- L282 _public prototype_ `FORCEINLINE bool operator==(const FGeneratedCacheKey& Other) const = default;`

#### struct `UE::Mutable::Private::CodeGenerator::FGeneratedSkeletalMeshCacheKey`  
`struct FGeneratedSkeletalMeshCacheKey`  
_L288-319_
- desc: Key of the generated skeletal mesh cache. Includes the LOD range and the component.
- L290 _public member_ `Ptr<const Node> Node;`
- L291 _public member_ `FGenericGenerationOptions Options;`
- L292 _public member_ `const NodeComponentNew* Component = nullptr;`
- L293 _public member_ `uint8 FirstLODAvailable = 0;`
- L294 _public member_ `uint8 NumLODs = 0;`
- L296 _public prototype_ `FGeneratedSkeletalMeshCacheKey() = default;`
- L298 _public function_ `FGeneratedSkeletalMeshCacheKey(const Ptr<const class Node>& InNode, const FSkeletalMeshGenerationOptions& InOptions) : Node(InNode) , Options(InOptions.GenericOptions) , Component(InOptions.Component) , FirstLODAvailable(InOptions.FirstLODAvailable) , NumLODs(InOptions.NumLODs)`
- L318 _public prototype_ `FORCEINLINE bool operator==(const FGeneratedSkeletalMeshCacheKey& Other) const = default;`

#### struct `UE::Mutable::Private::CodeGenerator::FGeneratedObjectCacheKey`  
`struct FGeneratedObjectCacheKey`  
_L334-351_
- L336 _public member_ `Ptr<const Node> Node;`
- L337 _public member_ `FObjectGenerationOptions Options;`
- L347 _public function_ `FORCEINLINE bool operator==(const FGeneratedObjectCacheKey& Other) const`

#### struct `UE::Mutable::Private::CodeGenerator::FObjectGenerationResult`  
`struct FObjectGenerationResult : public FGenericGenerationResult`  
_L353-381_
- inherits: `FGenericGenerationResult`
- L367 _public function_ `friend FORCEINLINE uint32 GetTypeHash(const FAdditionalComponentKey& InKey)`
- L380 _public member_ `TMultiMap< FAdditionalComponentKey, TArray<FAdditionalComponentData> > AdditionalComponents;`

#### struct `UE::Mutable::Private::CodeGenerator::FObjectGenerationResult::FAdditionalComponentKey`  
`struct FAdditionalComponentKey`  
_L358-372_
- desc: List of additional components to add to an object that come from child objects. The index is the object and lod that should receive the components.
- L360 _public member_ `const NodeObjectNew* ObjectNode = nullptr;`
- L362 _public function_ `FORCEINLINE bool operator==(const FAdditionalComponentKey& Other) const`

#### struct `UE::Mutable::Private::CodeGenerator::FObjectGenerationResult::FAdditionalComponentData`  
`struct FAdditionalComponentData`  
_L374-378_
- L376 _public member_ `Ptr<ASTOp> ComponentOp;`
- L377 _public member_ `Ptr<ASTOp> PlaceholderOp;`

#### struct `UE::Mutable::Private::CodeGenerator::FGenerateMeshConstantState`  
`struct FGenerateMeshConstantState`  
_L413-424_
- desc: This struct contains the generation state that can only be accessed when generating NodeMeshConstants. It should only be accessed from tasks running in the specific FPipe below.
- L423 _public member_ `TMap<uint64, TArray<FGeneratedConstantMesh>> GeneratedConstantMeshes;`

#### struct `UE::Mutable::Private::CodeGenerator::FGenerateMeshConstantState::FGeneratedConstantMesh`  
`struct FGeneratedConstantMesh`  
_L418-422_
- desc: Container of meshes generated to be able to reuse them. They are sorted by a cheap hash to speed up searches.
- L420 _public member_ `TManagedPtr<FMesh> Mesh;`
- L421 _public member_ `Ptr<ASTOp> LastMeshOp;`

#### struct `UE::Mutable::Private::CodeGenerator::FUniqueMeshIds`  
`struct FUniqueMeshIds`  
_L429-435_
- desc: List of already used vertex ID for meshes that must be unique.
- L431 _public prototype_ `uint32 EnsureUnique(uint32 Id);`
- L433 _private member_ `UE::FMutex Mutex;`
- L434 _private member_ `TSet<uint32> Map;`

#### struct `UE::Mutable::Private::CodeGenerator::FTableCacheKey`  
`struct FTableCacheKey`  
_L444-462_
- desc: The key for generated tables is made of the source table and a parameter name.
- L446 _public member_ `Ptr<const FTable> Table;`
- L447 _public member_ `FString ParameterName;`
- L456 _public function_ `FORCEINLINE bool operator==(const FTableCacheKey& InKey) const`

#### struct `UE::Mutable::Private::CodeGenerator::FGeneratedTableNodes`  
`struct FGeneratedTableNodes`  
_L464-468_
- L466 _public member_ `UE::FMutex Mutex;`
- L467 _public member_ `TMap< FTableCacheKey, Ptr<NodeScalar> > Map;`

#### struct `UE::Mutable::Private::CodeGenerator::FConditionalExtensionDataOp`  
`struct FConditionalExtensionDataOp`  
_L471-475_
- L473 _public member_ `Ptr<ASTOp> Condition;`
- L474 _public member_ `Ptr<ASTOp> ExtensionDataOp;`

#### struct `UE::Mutable::Private::CodeGenerator::FGeneratedComponentCacheKey`  
`struct FGeneratedComponentCacheKey`  
_L479-496_
- L481 _public member_ `Ptr<const Node> Node;`
- L482 _public member_ `FGenericGenerationOptions Options;`
- L492 _public function_ `FORCEINLINE bool operator==(const FGeneratedComponentCacheKey& Other) const`

#### enum `UE::Mutable::Private::CodeGenerator::EYesNoQuery`  
`enum class EYesNoQuery`  
_L512-517_
- L514 _public enumerator_ `Yes`
- L515 _public enumerator_ `No`
- L516 _public enumerator_ `Mixed`

#### struct `UE::Mutable::Private::CodeGenerator::FImageGenerationOptions`  
`struct FImageGenerationOptions`  
_L533-576_
- desc: Options that affect the generation of images. It is like list of what required data we want while parsing down the image node graph.
- L535 _public function_ `FImageGenerationOptions(int32 InComponentId, int32 InLODIndex) : ComponentId(InComponentId) , LODIndex(InLODIndex)`
- L542 _public member_ `FGenericGenerationOptions GenericOptions;`
- L545 _public member_ `int32 ComponentId = -1;` — The id of the component that we are currently generating.
- L548 _public member_ `int32 LODIndex = -1;` — The LOD being generated.
- L551 _public member_ `CompilerOptions::TextureLayoutStrategy ImageLayoutStrategy = CompilerOptions::TextureLayoutStrategy::None;`
- L554 _public member_ `UE::Math::TIntVector2<int32> RectSize = {0, 0};` — If different than {0,0} this is the mandatory size of the image that needs to be generated.
- L557 _public member_ `uint64 LayoutBlockId = FLayoutBlock::InvalidBlockId;` — Layout block that we are trying to generate if any.
- L558 _public member_ `TManagedPtr<const FLayout> LayoutToApply;`
- L561 _public member_ `FParameterDesc MaterialParameter;` — (Optional) Parameter Descriptor of the material where this image belongs.
- L575 _public prototype_ `FORCEINLINE bool operator==(const FImageGenerationOptions& Other) const = default;`

#### struct `UE::Mutable::Private::CodeGenerator::FImageGenerationResult`  
`struct FImageGenerationResult`  
_L579-585_
- L581 _public member_ `Ptr<ASTOp> op;`
- L582 _public member_ `bool Parameter = false;`
- L583 _public member_ `bool bCanMulticompose = true;`
- L584 _public member_ `EYesNoQuery CanNormalLAEncode = EYesNoQuery::Yes;`

#### struct `UE::Mutable::Private::CodeGenerator::FGeneratedImageCacheKey`  
`struct FGeneratedImageCacheKey`  
_L588-608_
- L590 _public function_ `FGeneratedImageCacheKey(const FImageGenerationOptions& InOptions, const NodeImagePtrConst& InNode) : Node(InNode) , Options(InOptions)`
- L596 _public member_ `Ptr<const Node> Node;`
- L597 _public member_ `FImageGenerationOptions Options;`
- L607 _public prototype_ `FORCEINLINE bool operator==(const FGeneratedImageCacheKey& Other) const = default;`

#### struct `UE::Mutable::Private::CodeGenerator::FGeneratedImages`  
`struct FGeneratedImages`  
_L611-615_
- L613 _public member_ `UE::FMutex Mutex;`
- L614 _public member_ `FGeneratedImagesMap Map;`

#### struct `UE::Mutable::Private::CodeGenerator::FMaterialGenerationOptions`  
`struct FMaterialGenerationOptions`  
_L678-719_
- desc: Options that affect the generation of Materials. It is like list of what required data we want while parsing down the material node graph.
- L680 _public member_ `FGenericGenerationOptions GenericOptions;`
- L683 _public member_ `int32 ComponentId = -1;` — The id of the component that we are currently generating.
- L686 _public member_ `int32 LODIndex = -1;` — The LOD being generated.
- L689 _public member_ `TArray<FString> Tags;` — Array with all the tags for the modifiers.
- L692 _public member_ `TArray<FirstPassGenerator::FModifier> Modifiers;` — Modifiers to apply.
- L694 _public member_ `FMeshGenerationResult MeshResults;`
- L696 _public member_ `TBitArray<> LayoutFromExtension;`
- L699 _public member_ `CompilerOptions::TextureLayoutStrategy ImageLayoutStrategy = CompilerOptions::TextureLayoutStrategy::None;`
- L702 _public member_ `UE::Math::TIntVector2<int32> RectSize = { 0, 0 };` — If different than {0,0} this is the mandatory size of the image that needs to be generated.
- L705 _public member_ `uint64 LayoutBlockId = FLayoutBlock::InvalidBlockId;` — Layout block that we are trying to generate if any.
- L706 _public member_ `TManagedPtr<const FLayout> LayoutToApply;`

#### struct `UE::Mutable::Private::CodeGenerator::FMaterialGenerationResult`  
`struct FMaterialGenerationResult`  
_L722-725_
- L724 _public member_ `Ptr<ASTOp> op;`

#### struct `UE::Mutable::Private::CodeGenerator::FGeneratedMaterialCacheKey`  
`struct FGeneratedMaterialCacheKey`  
_L727-743_
- L729 _public member_ `Ptr<const Node> Node;`
- L730 _public member_ `FMaterialGenerationOptions Options;`

#### struct `UE::Mutable::Private::CodeGenerator::FGeneratedMaterials`  
`struct FGeneratedMaterials`  
_L746-750_
- L748 _public member_ `UE::FMutex Mutex;`
- L749 _public member_ `FGeneratedMaterialsMap Map;`

#### struct `UE::Mutable::Private::CodeGenerator::FMeshGenerationStaticOptions`  
`struct FMeshGenerationStaticOptions : public FGenericGenerationOptions`  
_L773-791_
- inherits: `FGenericGenerationOptions`
- desc: Options that affect the generation of meshes. It is like list of what required data we want while parsing down the mesh node graph.
- L775 _public function_ `FMeshGenerationStaticOptions(int32 InComponentId, int32 InLODIndex) : ComponentId(InComponentId) , LODIndex(InLODIndex)`
- L782 _public member_ `int32 ComponentId = -1;` — The id of the component that we are currently generating.
- L785 _public member_ `int32 LODIndex = -1;` — The LOD being generated.
- L790 _public member_ `TArray<FirstPassGenerator::FModifier> ModifiersToIgnore;` — List of midifiers that shouldn't be applied in the processing of the current subgraph. This is usually because they have been processed already in the generation so far.

#### struct `UE::Mutable::Private::CodeGenerator::FMeshGenerationDynamicOptions`  
`struct FMeshGenerationDynamicOptions`  
_L797-823_
- desc: Options that affect the generation of meshes. It is like list of what required data we want while parsing down the mesh node graph.
- L800 _public member_ `bool bLayouts = false;` — The meshes at the leaves will need their own layout block data.
- L806 _public member_ `bool bClampUVIslands = true;` — If true, Ensure UV Islands are not split between two or more blocks. UVs shared between multiple layout blocks will be clamped to fit the one with more vertices belonging to the UV island. Mainly used to keep consistent layouts when reusing textures between LODs.
- L809 _public member_ `bool bNormalizeUVs = false;` — If true, UVs will be normalized. Normalize UVs should be done in cases where we operate with Images and Layouts
- L812 _public member_ `bool bEnsureAllVerticesHaveLayoutBlock = true;` — If true, assign vertices without layout to the first block.
- L818 _public member_ `TArray<FGeneratedLayout> OverrideLayouts;` — If this has something the layouts in constant meshes will be ignored, because they are supposed to match some other set of layouts. If the array is empty, layouts are generated normally.
- L822 _public member_ `TOptional<const void*> OverrideContext;` — Optional context to use instead of the node error context. Be careful since it is not used everywhere. Check usages before assigning a value to it.

#### struct `UE::Mutable::Private::CodeGenerator::FBaseMeshResultOptions`  
`struct FBaseMeshResultOptions`  
_L827-839_
- L833 _public member_ `UE::FMutex Mutex;` — Use this mutex to control access to the BaseMeshOptions attribute from any thread. The task dependency will make sure that the actual order for data insert and retrieval is correct, but unrelated data can be added while unrelated data is being retrieved so we need the mutex.
- L838 _public member_ `TMap<FGuid, FMeshGenerationResult> Map;` — Store the mesh generation data for edits that we intend to share across LODs. The key is the combination of the SharedSurfaceGuid of the surface.

#### struct `UE::Mutable::Private::CodeGenerator::FExtraLayoutsResultOptions`  
`struct FExtraLayoutsResultOptions`  
_L842-867_
- L848 _public member_ `UE::FMutex Mutex;` — Use this mutex to control access to the ExtraLayoutsOptions attribute from any thread. The task dependency will make sure that the actual order for data insert and retrieval is correct, but unrelated data can be added while unrelated data is being retrieved so we need the mutex.
- L855 _public function_ `friend FORCEINLINE uint32 GetTypeHash(const FExtraLayoutsKey& InKey)`
- L866 _public member_ `TMap<FExtraLayoutsKey, FMeshGenerationResult::FExtraLayouts> Map;` — Store the mesh generation data for edits that we intend to share across LODs. The key is the combination of the BaseSurfaceGuid and the ModifierGuid.

#### struct `UE::Mutable::Private::CodeGenerator::FExtraLayoutsResultOptions::FExtraLayoutsKey`  
`struct FExtraLayoutsKey`  
_L850-861_
- L852 _public member_ `FGuid BaseSurfaceGuid;`
- L853 _public member_ `FGuid EditGuid;`
- L860 _public prototype_ `FORCEINLINE bool operator==(const FExtraLayoutsKey& Other) const = default;`

#### struct `UE::Mutable::Private::CodeGenerator::FSharedSurfaceResultOptions`  
`struct FSharedSurfaceResultOptions`  
_L871-904_
- L877 _public member_ `UE::FMutex Mutex;` — Use this mutex to control access to the SharedSurfaceOptions attribute from any thread. The task dependency will make sure that the actual order for data insert and retrieval is correct, but unrelated data can be added while unrelated data is being retrieved so we need the mutex.
- L891 _public function_ `friend FORCEINLINE uint32 GetTypeHash(const FSharedSurfaceResultKey& InKey)`
- L903 _public member_ `TMap<FSharedSurfaceResultKey, FSharedSurfaceResult> Map;` — Store the generated layout and surface operations that we intend to share across LODs. The key is the combination of the BaseSurfaceGuid and the combination of all ModifierGuids affecting this surface.

#### struct `UE::Mutable::Private::CodeGenerator::FSharedSurfaceResultOptions::FSharedSurfaceResult`  
`struct FSharedSurfaceResult`  
_L879-884_
- L881 _public member_ `TArray<Ptr<ASTOp>> LayoutOps;`
- L882 _public member_ `Ptr<ASTOp> LastMaterialOp;`
- L883 _public member_ `uint32 SurfaceId;`

#### struct `UE::Mutable::Private::CodeGenerator::FSharedSurfaceResultOptions::FSharedSurfaceResultKey`  
`struct FSharedSurfaceResultKey`  
_L886-897_
- L888 _public member_ `FGuid BaseSurfaceGuid;`
- L889 _public member_ `FGuid CombinedGuid;`
- L896 _public prototype_ `FORCEINLINE bool operator==(const FSharedSurfaceResultKey& Other) const = default;`

#### struct `UE::Mutable::Private::CodeGenerator::FGenerateLayoutConstantState`  
`struct FGenerateLayoutConstantState`  
_L911-931_
- desc: This struct contains the generation state that can only be accessed when generating constant layouts. It should only be accessed after locking the included mutex.
- L913 _public member_ `UE::FMutex Mutex;`
- L921 _public function_ `friend FORCEINLINE uint32 GetTypeHash(const FGeneratedLayoutKey& InKey)`
- L930 _public member_ `TMap<FGeneratedLayoutKey, TManagedPtr<const FLayout>> GeneratedLayouts;`

#### struct `UE::Mutable::Private::CodeGenerator::FGenerateLayoutConstantState::FGeneratedLayoutKey`  
`struct FGeneratedLayoutKey`  
_L916-929_
- desc: Map of layouts found in the code already generated.The map is from the source layout node to the generated layout.
- L918 _public member_ `Ptr<const NodeLayout> SourceLayout;`
- L919 _public member_ `uint32 MeshIdPrefix;`
- L928 _public prototype_ `FORCEINLINE bool operator==(const FGeneratedLayoutKey& Other) const = default;`

#### struct `UE::Mutable::Private::CodeGenerator::FSkeletalMeshGenerationResult`  
`struct FSkeletalMeshGenerationResult`  
_L963-966_
- L965 _public member_ `Ptr<ASTOp> SkeletalMeshOp;`

#### struct `UE::Mutable::Private::CodeGenerator::FGeneratedSkeletalMeshes`  
`struct FGeneratedSkeletalMeshes`  
_L970-974_
- L972 _public member_ `UE::FMutex Mutex;`
- L973 _public member_ `FGeneratedSkeletalMeshesMap Map;`

#### struct `UE::Mutable::Private::CodeGenerator::FSkeletalMeshObjectGenerationResult`  
`struct FSkeletalMeshObjectGenerationResult`  
_L993-996_
- L995 _public member_ `Ptr<ASTOp> SkeletalMeshOp;`

#### struct `UE::Mutable::Private::CodeGenerator::FGeneratedSkeletalMeshObjects`  
`struct FGeneratedSkeletalMeshObjects`  
_L1000-1004_
- L1002 _public member_ `UE::FMutex Mutex;`
- L1003 _public member_ `FGeneratedSkeletalMeshObjectsMap Map;`

#### struct `UE::Mutable::Private::CodeGenerator::FExternalGenerationOptions`  
`struct FExternalGenerationOptions`  
_L1012-1085_
- L1017 _public member_ `TOptional<FMeshGenerationStaticOptions> MeshStaticOptions;` — GenerateMesh
- L1018 _public member_ `TOptional<FMeshOptionsTask> MeshDynamicOptions;`
- L1021 _public member_ `TOptional<FImageGenerationOptions> ImageOptions;` — GenerateImage
- L1024 _public member_ `TOptional<FGenericGenerationOptions> ScalarOptions;` — GenerateScalar
- L1027 _public member_ `TOptional<FGenericGenerationOptions> ColorOptions;` — GenerateColor
- L1030 _public member_ `TOptional<FMaterialGenerationOptions> MaterialOptions;` — GenerateMaterial
- L1032 _public function_ `bool operator==(const FExternalGenerationOptions& Other) const`
- L1056 _public function_ `FGenericGenerationOptions GetGenericOptions() const`

#### struct `UE::Mutable::Private::CodeGenerator::FGeneratedExternalCacheKey`  
`struct FGeneratedExternalCacheKey`  
_L1087-1103_
- L1089 _public member_ `Ptr<const NodeExternal> Node;`
- L1090 _public member_ `FExternalGenerationOptions Options;`
- L1102 _public prototype_ `bool operator==(const FGeneratedExternalCacheKey& Other) const = default;`

#### struct `UE::Mutable::Private::CodeGenerator::FGeneratedExternal`  
`struct FGeneratedExternal`  
_L1106-1110_
- L1108 _public member_ `UE::FMutex Mutex;`
- L1109 _public member_ `FGeneratedExternalMap Map;`

#### struct `UE::Mutable::Private::CodeGenerator::FExtensionDataGenerationResult`  
`struct FExtensionDataGenerationResult`  
_L1121-1124_
- L1123 _public member_ `Ptr<ASTOp> Op;`

#### struct `UE::Mutable::Private::CodeGenerator::FProjectorGenerationResult`  
`struct FProjectorGenerationResult`  
_L1138-1142_
- desc: Projectors
- L1140 _public member_ `Ptr<ASTOp> op;`
- L1141 _public member_ `EProjectorType type;`

#### struct `UE::Mutable::Private::CodeGenerator::FGeneratedProjectors`  
`struct FGeneratedProjectors`  
_L1145-1149_
- L1147 _public member_ `UE::FMutex Mutex;`
- L1148 _public member_ `FGeneratedProjectorsMap Map;`

#### struct `UE::Mutable::Private::CodeGenerator::FBoolGenerationResult`  
`struct FBoolGenerationResult`  
_L1159-1162_
- desc: Bools
- L1161 _public member_ `Ptr<ASTOp> op;`

#### struct `UE::Mutable::Private::CodeGenerator::FGeneratedBools`  
`struct FGeneratedBools`  
_L1165-1169_
- L1167 _public member_ `UE::FMutex Mutex;`
- L1168 _public member_ `FGeneratedBoolsMap Map;`

#### struct `UE::Mutable::Private::CodeGenerator::FScalarGenerationResult`  
`struct FScalarGenerationResult`  
_L1180-1183_
- desc: Scalars
- L1182 _public member_ `Ptr<ASTOp> op;`

#### struct `UE::Mutable::Private::CodeGenerator::FGeneratedScalars`  
`struct FGeneratedScalars`  
_L1187-1191_
- L1189 _public member_ `UE::FMutex Mutex;`
- L1190 _public member_ `FGeneratedScalarsMap Map;`

#### struct `UE::Mutable::Private::CodeGenerator::FColorGenerationResult`  
`struct FColorGenerationResult`  
_L1209-1212_
- desc: Colors
- L1211 _public member_ `Ptr<ASTOp> op;`

#### struct `UE::Mutable::Private::CodeGenerator::FGeneratedColors`  
`struct FGeneratedColors`  
_L1215-1219_
- L1217 _public member_ `UE::FMutex Mutex;`
- L1218 _public member_ `FGeneratedColorsMap Map;`

#### struct `UE::Mutable::Private::CodeGenerator::FStringGenerationResult`  
`struct FStringGenerationResult`  
_L1238-1241_
- desc: Strings
- L1240 _public member_ `Ptr<ASTOp> op;`

#### struct `UE::Mutable::Private::CodeGenerator::FGeneratedStrings`  
`struct FGeneratedStrings`  
_L1244-1248_
- L1246 _public member_ `UE::FMutex Mutex;`
- L1247 _public member_ `FGeneratedStringsMap Map;`

#### struct `UE::Mutable::Private::CodeGenerator::FMatrixGenerationResult`  
`struct FMatrixGenerationResult`  
_L1257-1260_
- desc: Transforms
- L1259 _public member_ `Ptr<ASTOp> op;`

#### struct `UE::Mutable::Private::CodeGenerator::FGeneratedMatrices`  
`struct FGeneratedMatrices`  
_L1263-1267_
- L1265 _public member_ `UE::FMutex Mutex;`
- L1266 _public member_ `FGeneratedMatrixMap Map;`

#### struct `UE::Mutable::Private::CodeGenerator::FRangeGenerationResult`  
`struct FRangeGenerationResult`  
_L1276-1286_
- desc: Ranges
- L1279 _public member_ `Ptr<ASTOp> sizeOp;`
- L1282 _public member_ `FString rangeName;`
- L1285 _public member_ `FString rangeUID;`

#### struct `UE::Mutable::Private::CodeGenerator::FGeneratedRanges`  
`struct FGeneratedRanges`  
_L1289-1293_
- L1291 _public member_ `UE::FMutex Mutex;`
- L1292 _public member_ `FGeneratedRangeMap Map;`

#### struct `UE::Mutable::Private::CodeGenerator::FLayoutBlockDesc`  
`struct FLayoutBlockDesc`  
_L1300-1306_
- L1302 _public member_ `EImageFormat FinalFormat = EImageFormat::None;`
- L1303 _public member_ `uint16 BlockPixelsX = 0;`
- L1304 _public member_ `uint16 BlockPixelsY = 0;`
- L1305 _public member_ `bool bBlocksHaveMips = false;`

#### Free symbols / members of external scopes

- L46 _namespace_ `namespace UE`
- L46 _namespace_ `namespace Mutable` (scope `UE`)
- L46 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L55 _externvar_ `extern TAutoConsoleVariable<bool> CVarAllowMulticompose;` (scope `UE::Mutable::Private`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/CodeGenerator_FirstPass.h` (Private)


#### struct `UE::Mutable::Private::FGeneratedLayout`  
`struct FGeneratedLayout`  
_L56-62_
- L58 _public member_ `TManagedPtr<const FLayout> Layout;`
- L59 _public member_ `Ptr<const NodeLayout> Source;`

#### struct `UE::Mutable::Private::FMeshGenerationResult`  
`struct FMeshGenerationResult`  
_L65-93_
- desc: Store the results of the code generation of a mesh.
- L68 _public member_ `Ptr<ASTOp> MeshOp;` — Mesh after all code tree is applied
- L71 _public member_ `Ptr<ASTOp> BaseMeshOp;` — Original base mesh before removes, morphs, etc.
- L74 _public member_ `TArray<FGeneratedLayout> GeneratedLayouts;` — Generated node layouts with their own block ids.
- L77 _public member_ `TArray<Ptr<ASTOp>> LayoutOps;` — TODO: The following members seem related to surface-sharing data and not actual mesh generation result. Maybe they should be moved to a different struct.
- L90 _public member_ `TArray<FExtraLayouts> ExtraMeshLayouts;`

#### struct `UE::Mutable::Private::FMeshGenerationResult::FExtraLayouts`  
`struct FExtraLayouts`  
_L79-89_
- L81 _public member_ `FGuid EditGuid;`
- L84 _public member_ `TArray<FGeneratedLayout> GeneratedLayouts;` — Source node layouts to use with these extra mesh. They don't have block ids.
- L85 _public member_ `Ptr<ASTOp> Condition;`
- L86 _public member_ `Ptr<ASTOp> MeshFragment;`

#### struct `UE::Mutable::Private::FSurfaceGenerationResult`  
`struct FSurfaceGenerationResult`  
_L100-104_
- L102 _public member_ `Ptr<ASTOp> MaterialOp;`
- L103 _public member_ `FGuid SharedSurfaceGuid;`

#### struct `UE::Mutable::Private::FLODGenerationResult`  
`struct FLODGenerationResult`  
_L108-120_
- L110 _public member_ `Ptr<ASTOp> LODOp;`
- L119 _public member_ `TArray<FMaterialSlot> MaterialSlots;`

#### struct `UE::Mutable::Private::FLODGenerationResult::FMaterialSlot`  
`struct FMaterialSlot`  
_L112-118_
- L114 _public member_ `Ptr<ASTOp> Material;`
- L115 _public member_ `FName SlotName;`
- L116 _public member_ `uint32 Id = 0;`
- L117 _public member_ `uint32 ExternalId = 0;`

#### struct `UE::Mutable::Private::FGenericGenerationResult`  
`struct FGenericGenerationResult`  
_L124-127_
- L126 _public member_ `Ptr<ASTOp> Op;`

#### struct `UE::Mutable::Private::FExternalGenerationResult`  
`struct FExternalGenerationResult`  
_L132-138_
- L134 _public member_ `Ptr<ASTOp> Op;`
- L137 _public member_ `TOptional<FMeshGenerationResult> MeshGenerationResult;` — If set, at least one of the external operation inputs is a mesh

#### class `UE::Mutable::Private::FirstPassGenerator`  
`class FirstPassGenerator`  
_L146-384_
- desc: First pass of the code generation process. It collects data about the object hierarchy, the conditions for each object and the global modifiers.
- L150 _public prototype_ `FirstPassGenerator();`
- L152 _public prototype_ `void Generate(TSharedPtr<FErrorLog>, const Node* Root, bool bIgnoreStates, class CodeGenerator*);`
- L156 _private prototype_ `void Generate_Generic(const Node*);`
- L157 _private prototype_ `void Generate_SurfaceModifier(const NodeSurfaceModifier*);`
- L158 _private prototype_ `void Generate_SurfaceNew(const NodeSurfaceNew*);`
- L159 _private prototype_ `void Generate_SurfaceSwitch(const NodeSurfaceSwitch*);`
- L160 _private prototype_ `void Generate_SurfaceVariation(const NodeSurfaceVariation*);`
- L161 _private prototype_ `void Generate_ComponentNew(const NodeComponentNew*);`
- L162 _private prototype_ `void Generate_ModifierSkeletalMeshMerge(const NodeModifierSkeletalMeshMerge*);`
- L163 _private prototype_ `void Generate_ComponentSwitch(const NodeComponentSwitch*);`
- L164 _private prototype_ `void Generate_ComponentVariation(const NodeComponentVariation*);`
- L165 _private prototype_ `void Generate_SkeletalMeshNew(const NodeSkeletalMeshNew*);`
- L166 _private prototype_ `void Generate_SkeletalMeshConvert(const NodeSkeletalMeshConvert*);`
- L167 _private prototype_ `void Generate_SkeletalMeshMerge(const NodeSkeletalMeshMerge*);`
- L168 _private prototype_ `void Generate_SkeletalMeshSwitch(const NodeSkeletalMeshSwitch*);`
- L169 _private prototype_ `void Generate_SkeletalMeshVariation(const NodeSkeletalMeshVariation*);`
- L170 _private prototype_ `void Generate_SkeletalMeshTransform(const NodeSkeletalMeshTransform*);`
- L171 _private prototype_ `void Generate_SkeletalMeshMorph(const NodeSkeletalMeshMorph*);`
- L172 _private prototype_ `void Generate_SkeletalMeshReshape(const NodeSkeletalMeshReshape*);`
- L173 _private prototype_ `void Generate_SkeletalMeshModify(const NodeSkeletalMeshModify*);`
- L174 _private prototype_ `void Generate_SkeletalMeshTransformWithBone(const NodeSkeletalMeshTransformWithBone*);`
- L175 _private prototype_ `void Generate_LOD(const NodeLOD*);`
- L176 _private prototype_ `void Generate_ObjectNew(const NodeObjectNew*);`
- L177 _private prototype_ `void Generate_ObjectGroup(const NodeObjectGroup*);`
- L178 _private prototype_ `void Generate_SkeletalMeshObjectConvert(const NodeSkeletalMeshObjectConvert*);`
- L179 _private prototype_ `void Generate_SkeletalMeshObjectSwitch(const NodeSkeletalMeshObjectSwitch*);`
- L180 _private prototype_ `void Generate_SkeletalMeshClipSkeletalMesh(const NodeSkeletalMeshClipWithSkeletalMesh*);`
- L181 _private prototype_ `void Generate_MaterialModify(const NodeMaterialModify*);`
- L182 _private prototype_ `void Generate_MaterialSwitch(const NodeMaterialSwitch*);`
- L183 _private prototype_ `void Generate_MaterialVariation(const NodeMaterialVariation*);`
- L184 _private prototype_ `void Generate_MaterialSkeletalMeshBreak(const NodeMaterialSkeletalMeshBreak*);`
- L186 _private prototype_ `void AddSkeletalMeshDataForNode(const NodeSkeletalMesh*);`
- L199 _public member_ `TArray<FObject> Objects;`
- L213 _public member_ `TArray<FSkeletalMeshData> SkeletalMeshes;`
- L215 _public member_ `bool bIsSkeletalMeshEntryPoint = true;`
- L221 _public typedef_ `using StateCondition = TArray<uint8>;` — Type used to represent the activation conditions regarding states This is the state mask for the states in which this surface must be added. If it is empty it means the surface is valid for all states. Otherwise it is only valid for the states whose index is true.
- L243 _public member_ `TArray<FComponent> Components;`
- L286 _public member_ `TArray<FSurface> Surfaces;`
- L312 _public member_ `TArray<FModifier> Modifiers;`
- L330 _public member_ `TArray<FTag> Tags;`
- L333 _public typedef_ `typedef TArray< FObjectState > StateList;` — Accumulate the model states found while generating code.
- L334 _public member_ `StateList States;`
- L345 _public member_ `FSafeParameterNodes ParameterNodes;`
- L362 _private member_ `FConditionContext ConditionContext;`
- L365 _private member_ `TArray< StateCondition > CurrentStateCondition;`
- L368 _private member_ `const NodeComponentNew* CurrentComponent = nullptr;` — When processing surfaces, this is the parent component the surfaces may be added to.
- L370 _private member_ `FName CurrentSkeletalMeshName;`
- L373 _private member_ `TArray<FString> CurrentPositiveTags;` — Current relevant tags so far. Used during traversal.
- L374 _private member_ `TArray<FString> CurrentNegativeTags;`
- L377 _private member_ `int32 CurrentLOD = -1;` — /  Index of the LOD we are processing.
- L380 _private member_ `CodeGenerator* Generator = nullptr;` — Non-owned reference to main code generator.
- L383 _private member_ `TSharedPtr<FErrorLog> ErrorLog;`

#### struct `UE::Mutable::Private::FirstPassGenerator::FObject`  
`struct FObject`  
_L194-198_
- desc: Store the conditions that will enable or disable every object
- L196 _public member_ `const NodeObjectNew* Node = nullptr;`
- L197 _public member_ `Ptr<ASTOp> Condition;`

#### struct `UE::Mutable::Private::FirstPassGenerator::FSkeletalMeshData`  
`struct FSkeletalMeshData`  
_L201-212_
- L203 _public member_ `const NodeSkeletalMesh* SkeletalMeshNode = nullptr;`
- L205 _public member_ `FName ParentSkeletalMeshName;`
- L207 _public member_ `bool bIsEntryPoint = true;`
- L209 _public member_ `Ptr<ASTOp> ObjectCondition;`
- L211 _public member_ `TArray<TArray<int32>> SurfacesPerLOD;`

#### struct `UE::Mutable::Private::FirstPassGenerator::FComponent`  
`struct FComponent`  
_L224-242_
- desc: Store information about every component found.
- L227 _public member_ `const NodeComponentNew* Component = nullptr;` — Main component node.
- L230 _public member_ `TArray<FString> PositiveTags;` — List of tags that are required for the presence of this component
- L233 _public member_ `TArray<FString> NegativeTags;` — List of tags that block the presence of this component
- L237 _public member_ `Ptr<ASTOp> ObjectCondition;` — This conditions is the condition of the object defining this surface which may not be the parent object where this surface will be added.
- L241 _public member_ `Ptr<ASTOp> ComponentCondition;` — Condition for this component to be added. This is filled in CodeGenerator_SecondPass.

#### struct `UE::Mutable::Private::FirstPassGenerator::FSurface`  
`struct FSurface`  
_L251-285_
- desc: Store information about every surface including - the component it may be added to - the conditions that will enable or disable it - all edit operators A surface may have different versions depending on the different parents and conditions it is reached with.
- L253 _public member_ `Ptr<const NodeSurfaceNew> Node;`
- L258 _public member_ `const NodeComponentNew* Component = nullptr;` — Parent Component where this surface will be added.It may be different from the Component that defined it (if it was an edit component).
- L260 _public member_ `int32 LOD = 0;`
- L263 _public member_ `TArray<FString> PositiveTags;` — List of tags that are required for the presence of this surface
- L266 _public member_ `TArray<FString> NegativeTags;` — List of tags that block the presence of this surface
- L270 _public member_ `Ptr<ASTOp> ObjectCondition;` — This conditions is the condition of the object defining this surface which may not be the parent object where this surface will be added.
- L271 _public member_ `Ptr<ASTOp> MeshCondition;`
- L274 _public member_ `StateCondition StateCondition;` — This is filled in the first pass.
- L278 _public member_ `Ptr<ASTOp> FinalCondition;` — Combined condition for the surface and the object conditions. This is filled in CodeGenerator_SecondPass.
- L281 _public member_ `FSurfaceTask ResultSurfaceTask;` — This is filled in the final code generation pass
- L282 _public member_ `Ptr<ASTOp> ResultMeshOp;`
- L284 _public prototype_ `bool operator==(const FSurface&) const = default;`

#### struct `UE::Mutable::Private::FirstPassGenerator::FModifier`  
`struct FModifier`  
_L289-311_
- desc: Store the conditions that enable every modifier.
- L291 _public member_ `const NodeSurfaceModifier* Node = nullptr;`
- L294 _public member_ `TArray<FString> PositiveTags;` — List of tags that are required to apply this modifier
- L297 _public member_ `TArray<FString> NegativeTags;` — List of tags that block the activation of this modifier
- L301 _public member_ `Ptr<ASTOp> ObjectCondition;` — This conditions is the condition of the object defining this modifier which may not be the parent object where this surface will be added.
- L305 _public member_ `Ptr<ASTOp> FinalCondition;` — Combined condition for the this modifier and the object conditions. This is filled in CodeGenerator_SecondPass.
- L308 _public member_ `StateCondition StateCondition;` — This is filled in CodeGenerator_SecondPass.
- L310 _public prototype_ `bool operator==(const FModifier&) const = default;`

#### struct `UE::Mutable::Private::FirstPassGenerator::FTag`  
`struct FTag`  
_L315-329_
- desc: Info about all found tags.
- L317 _public member_ `FString Tag;`
- L320 _public member_ `TArray<int32> Surfaces;` — Surfaces that activate the tag.These are indices to the FirstPassGenerator::Surfaces array.
- L323 _public member_ `TArray<int32> Modifiers;` — Modifiers that activate the tag. The index refers to the FirstPassGenerator::Modifiers.
- L328 _public member_ `Ptr<ASTOp> GenericCondition;` — This conditions is the condition for this tag to be enabled considering no other condition. This is filled in CodeGenerator_SecondPass.

#### struct `UE::Mutable::Private::FirstPassGenerator::FSafeParameterNodes`  
`struct FSafeParameterNodes`  
_L337-344_
- desc: FParameters added for every node.
- L340 _public member_ `UE::FMutex Mutex;` — Lock this mutex before accessing any data in the struct.
- L343 _public member_ `TMap< Ptr<const Node>, Ptr<ASTOpParameter> > GenericParametersCache;` — Cache for generic parameters.

#### struct `UE::Mutable::Private::FirstPassGenerator::FConditionContext`  
`struct FConditionContext`  
_L349-361_
- L351 _public prototype_ `void Push(Ptr<ASTOp> InCurrentCondition, bool bStartLocalPath = false);`
- L352 _public prototype_ `void Pop();`
- L354 _public prototype_ `void GetCurrent(Ptr<ASTOp>& OutPathCondition, Ptr<ASTOp>& OutLocalPathCondition);`
- L358 _private member_ `TArray<Ptr<ASTOp>> PathConditions;`
- L359 _private member_ `TArray<Ptr<ASTOp>> LocalPathConditions;`

#### Free symbols / members of external scopes

- L36 _namespace_ `namespace UE`
- L36 _namespace_ `namespace Mutable` (scope `UE`)
- L36 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L98 _typedef_ `using FMeshTask = UE::Tasks::TTask<FMeshGenerationResult>;` (scope `UE::Mutable::Private`)
- L106 _typedef_ `using FSurfaceTask = UE::Tasks::TTask<FSurfaceGenerationResult>;` (scope `UE::Mutable::Private`)
- L122 _typedef_ `using FLODTask = UE::Tasks::TTask<FLODGenerationResult>;` (scope `UE::Mutable::Private`)
- L129 _typedef_ `using FSkeletalMeshTask = UE::Tasks::TTask<FGenericGenerationResult>;` (scope `UE::Mutable::Private`)
- L130 _typedef_ `using FComponentTask = UE::Tasks::TTask<FGenericGenerationResult>;` (scope `UE::Mutable::Private`)
- L140 _typedef_ `using FExternalTask = UE::Tasks::TTask<FExternalGenerationResult>;` (scope `UE::Mutable::Private`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/CodeGenerator_SecondPass.h` (Private)


#### class `UE::Mutable::Private::SecondPassGenerator`  
`class SecondPassGenerator`  
_L26-106_
- desc: Second pass of the code generation process. It solves surface and modifier conditions from tags and variations
- L30 _public prototype_ `SecondPassGenerator( FirstPassGenerator*, const CompilerOptions::Private* );`
- L33 _public prototype_ `bool Generate(TSharedPtr<FErrorLog>, const Node* Root );` — Return true on success.
- L37 _private member_ `FirstPassGenerator* FirstPass = nullptr;`
- L38 _private member_ `const CompilerOptions::Private *CompilerOptions = nullptr;`
- L42 _private member_ `TSharedPtr<FErrorLog> ErrorLog;`
- L53 _private function_ `friend FORCEINLINE uint32 GetTypeHash(const FConditionGenerationKey& InKey)`
- L77 _private member_ `TArray< TSet<int32> > SurfacesPerTag;` — List of surfaces that activate or deactivate every tag, or another surface that activates a tag in this set.
- L78 _private member_ `TArray< TSet<int32> > TagsPerTag;`
- L80 _private member_ `TMap<FConditionGenerationKey,Ptr<ASTOp>> TagConditionGenerationCache;`
- L82 _private member_ `FUniqueOpPool OpPool;`
- L85 _private prototype_ `Ptr<ASTOp> GenerateTagCondition( int32 tagIndex, const TSet<int32>& posSurf, const TSet<int32>& negSurf, const TSet<int32>& posTag, const TSet<int32>& negTag );`
- L99 _private prototype_ `Ptr<ASTOp> GenerateDataCodition(int32 Index, const TArray<FString>& PositiveTags, const TArray<FString>& NegativeTags, const TSet<int32>& posSurf, const TSet<int32>& negSurf, const TSet<int32>& posTag, const TSet<int32>& negTag);` — Generate Surface, Edit or Modifier condition. @param Index Surface, Edit, Component or Modifier index. @param PositiveTags function that given the Surface, Edit or Modifier index, returns its positive tags. @param NegativeTags function that given the Surface, Edit or Modifier, returns its negative tags. @param posSurf already visited Surfaces, Edits, or Modifiers that participate positively in the condition. @param negSurf already visited Surfaces, Edits, or Modifiers that participate negatively in the condition. @param posSurf Tags that already belong to the condition (positively). @param negSurf Tags that already belong to the condition (negatively).

#### struct `UE::Mutable::Private::SecondPassGenerator::FConditionGenerationKey`  
`struct FConditionGenerationKey`  
_L45-74_
- L47 _public member_ `int32 tagOrSurfIndex = 0;`
- L48 _public member_ `TSet<int32> posSurf;`
- L49 _public member_ `TSet<int32> negSurf;`
- L50 _public member_ `TSet<int32> posTag;`
- L51 _public member_ `TSet<int32> negTag;`
- L64 _public function_ `FORCEINLINE bool operator==(const FConditionGenerationKey& Other) const`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Mutable` (scope `UE`)
- L15 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L17 _function_ `inline bool SetsEquals(const TSet<int32>& Left, const TSet<int32>& Right)` (scope `UE::Mutable::Private`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/CodeOptimiser.h` (Private)


#### class `UE::Mutable::Private::CodeOptimiser`  
`class CodeOptimiser`  
_L13-34_
- desc: Code optimiser: Rebuild an ASTOp graph so that it is more efficient.
- L16 _public prototype_ `CodeOptimiser( Ptr<CompilerOptions>, TArray<FStateCompilationData>& States );`
- L18 _public prototype_ `void Optimise();`
- L22 _private member_ `Ptr<CompilerOptions> Options;`
- L23 _private member_ `TArray<FStateCompilationData>& States;`
- L26 _private member_ `int32 OptimizeIterationsLeft=0;` — The max number of optimize iterations is shared across several stages now. This is how many are left.
- L29 _private prototype_ `void FullOptimiseAST( ASTOpList& roots, int32 Pass);` — Full optimisation pass
- L32 _private prototype_ `void OptimiseStatesAST();` — Optimise the code for each specific state, generating new instructions and state information.

#### class `UE::Mutable::Private::LODCountReducerAST`  
`class LODCountReducerAST : public Visitor_TopDown_Unique_Cloning`  
_L61-72_
- inherits: `Visitor_TopDown_Unique_Cloning`
- desc: Discard all LODs beyond the given lod count.
- L65 _public prototype_ `LODCountReducerAST( Ptr<ASTOp>& Root, uint8 NumExtraLODsToBuildAfterFirstLOD );`
- L69 _protected prototype_ `Ptr<ASTOp> Visit( Ptr<ASTOp>, bool& bOutProcessChildren ) override;`
- L71 _protected member_ `uint8 NumExtraLODs = 0;`

#### class `UE::Mutable::Private::RuntimeParameterVisitorAST`  
`class RuntimeParameterVisitorAST`  
_L79-125_
- desc: Scan the code in the given subtree and return true if a state runtime parameters is found. Intermediate data is used betwen calls to apply, so don't remove program code or directly change the instructions. Adding new instructions is ok.
- L83 _public prototype_ `RuntimeParameterVisitorAST(const FStateCompilationData* );`
- L85 _public prototype_ `bool HasAny( const Ptr<ASTOp>& Root );`
- L89 _private member_ `const FStateCompilationData* State;`
- L107 _private member_ `TArray< FPendingItem > Pending;`
- L120 _private member_ `TMap<Ptr<ASTOp>, EOpState> Visited;`
- L123 _private prototype_ `void AddIfNeeded( const FPendingItem& );`

#### struct `UE::Mutable::Private::RuntimeParameterVisitorAST::FPendingItem`  
`struct FPendingItem`  
_L92-104_
- L96 _public member_ `uint8 ItemType;` — 0: indicate subtree pending 1: indicate children finished
- L100 _public member_ `uint8 OnlyLayoutsRelevant;` — 0: everything is relevant 1: only layouts are relevant
- L103 _public member_ `Ptr<ASTOp> Op;` — Operation to visit

#### enum `UE::Mutable::Private::RuntimeParameterVisitorAST::EOpState`  
`enum class EOpState : uint8`  
_L110-118_
- desc: Possible op state
- L112 _public enumerator_ `NotVisited = 0`
- L113 _public enumerator_ `ChildrenPendingFull`
- L114 _public enumerator_ `ChildrenPendingPartial`
- L115 _public enumerator_ `VisitedHasRuntime`
- L116 _public enumerator_ `VisitedFullDoesntHaveRuntime`
- L117 _public enumerator_ `VisitedPartialDoesntHaveRuntime`

#### class `UE::Mutable::Private::RuntimeTextureCompressionRemoverAST`  
`class RuntimeTextureCompressionRemoverAST : public Visitor_TopDown_Unique_Cloning`  
_L129-144_
- inherits: `Visitor_TopDown_Unique_Cloning`
- desc: Remove all texture compression operations that would happen for runtime parameter changes.
- L133 _public prototype_ `RuntimeTextureCompressionRemoverAST(FStateCompilationData*, bool bInAlwaysUncompress );`
- L137 _protected prototype_ `Ptr<ASTOp> Visit( Ptr<ASTOp>, bool& bOutProcessChildren ) override;`
- L141 _private member_ `RuntimeParameterVisitorAST HasRuntimeParamVisitor;`
- L142 _private member_ `bool bAlwaysUncompress = false;`

#### class `UE::Mutable::Private::ParameterOptimiserAST`  
`class ParameterOptimiserAST : public Visitor_TopDown_Unique_Cloning`  
_L147-169_
- inherits: `Visitor_TopDown_Unique_Cloning`
- desc: Restructure the code to move operations involving runtime parameters as high as possible.
- L151 _private member_ `FStateCompilationData& StateProps;`
- L155 _public prototype_ `ParameterOptimiserAST(FStateCompilationData&, const FModelOptimizationOptions& );`
- L157 _public prototype_ `bool Apply();`
- L161 _private prototype_ `Ptr<ASTOp> Visit( Ptr<ASTOp>, bool& bOutProcessChildren ) override;`
- L163 _private member_ `bool bModified;`
- L165 _private member_ `FModelOptimizationOptions OptimisationOptions;`
- L167 _private member_ `RuntimeParameterVisitorAST HasRuntimeParamVisitor;`

#### class `UE::Mutable::Private::SubtreeRelevantParametersVisitorAST`  
`class SubtreeRelevantParametersVisitorAST : public Visitor_TopDown_Unique_Const<bool>`  
_L180-219_
- inherits: `Visitor_TopDown_Unique_Const<bool>`
- desc: Calculate all the parameters found relevant under a particular operation.This may not incldue all the parameters in the subtree (if because of the operations they are not relevant) It has an internal cache, so don't reuse if the program changes.
- L184 _public prototype_ `void Run( Ptr<ASTOp> Root );`
- L186 _public prototype_ `virtual bool Visit(const Ptr<ASTOp>& node) override;`
- L189 _public member_ `TSet< FString > Parameters;` — After Run, list of relevant parameters.
- L206 _private function_ `friend FORCEINLINE uint32 GetTypeHash(const FState& InKey)`
- L218 _private member_ `TMap< FState, TSet<FString> > ResultCache;` — Result cache \todo optimise by storing unique lists separately and an index here.

#### struct `UE::Mutable::Private::SubtreeRelevantParametersVisitorAST::FState`  
`struct FState`  
_L193-213_
- L195 _public member_ `Ptr<ASTOp> Op;`
- L196 _public member_ `bool bOnlyLayoutIsRelevant=false;`
- L198 _public function_ `FState( Ptr<ASTOp> o=nullptr, bool l=false) : Op(o), bOnlyLayoutIsRelevant(l)`
- L200 _public function_ `bool operator==(const FState& o) const`

#### class `UE::Mutable::Private::SubtreeResourceRelevantParametersVisitorAST`  
`class SubtreeResourceRelevantParametersVisitorAST : public SubtreeRelevantParametersVisitorAST`  
_L222-226_
- inherits: `SubtreeRelevantParametersVisitorAST`
- L225 _public prototype_ `virtual bool Visit(const Ptr<ASTOp>& node) override;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Mutable` (scope `UE`)
- L9 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L38 _prototype_ `extern bool ConstantGenerator( const CompilerOptions::Private*, Ptr<ASTOp>& Root, int32 Pass );` (scope `UE::Mutable::Private`) — ConstantGenerator replaces constant subtrees of operations with an equivalent single
- L41 _prototype_ `extern bool DuplicatedDataRemoverAST( ASTOpList& Roots );` (scope `UE::Mutable::Private`) — \TODO: shapes, projectors, others? but not switches (they must be unique)
- L44 _prototype_ `extern bool DuplicatedCodeRemoverAST( ASTOpList& Roots );` (scope `UE::Mutable::Private`) — Mark all the duplicated code instructions to point at the same operation, leaving the copies unreachable.
- L47 _prototype_ `extern bool SemanticOptimiserAST( ASTOpList& Roots, const FModelOptimizationOptions&, int32 Pass);` (scope `UE::Mutable::Private`) — All kinds of optimisations that depend on the meaning of each operation.
- L52 _prototype_ `extern bool SinkOptimiserAST( ASTOpList& Roots, const FModelOptimizationOptions& );` (scope `UE::Mutable::Private`) — Semantic operator that reorders instructions moving expensive ones down to the leaves of the expressions trying to turn them into constants.
- L55 _prototype_ `extern bool SizeOptimiserAST( ASTOpList& Roots );` (scope `UE::Mutable::Private`)
- L58 _prototype_ `extern bool LocalLogicOptimiserAST(ASTOpList& roots);` (scope `UE::Mutable::Private`)
- L173 _prototype_ `extern Ptr<ASTOp> EnsureValidMask( Ptr<ASTOp> mask, Ptr<ASTOp> base );` (scope `UE::Mutable::Private`) — Some masks are optional.If they are null, replace them by a white plain image of the right size.

### `Plugins/Mutable/Source/MutableTools/Private/MuT/CodeOptimiserPrivate.h` (Private)


#### struct `UE::Mutable::Private::FResourceEntry`  
`template<typename T> struct FResourceEntry`  
_L14-28_
- L16 _public member_ `uint32 Hash = 0;`
- L17 _public member_ `TManagedPtr<const T> Value;`
- L19 _public function_ `bool operator==(const FResourceEntry& Entry) const`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Mutable` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L24 _function_ `friend uint32 GetTypeHash(const FResourceEntry& Entry)` (scope `UE::Mutable::Private`)
- L32 _function_ `template<typename T> bool Deduplicate(TMap<FResourceEntry<T>, Ptr<ASTOpConstantResource>>& Ops, const Ptr<ASTOpConstantResource>& OpResource)` (scope `UE::Mutable::Private`)
- L52 _prototype_ `bool DeduplicateFMaterial(TMap<TPassthroughObjectPtr<UMaterialInterface>, Ptr<ASTOpConstantResource>>& Ops, const Ptr<ASTOpConstantResource>& OpResource);` (scope `UE::Mutable::Private`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/CompilerPrivate.h` (Private)


#### struct `UE::Mutable::Private::FOpToolsDesc`  
`struct FOpToolsDesc`  
_L17-24_
- desc: Generic data about a Mutable operation that is needed at compile time.
- L20 _public member_ `bool bCached;` — True if the instruction is worth caching when generating models.
- L23 _public member_ `bool bSupportedBasePixelFormats[uint8(EImageFormat::Count)];` — For image instructions, for every image format, true if it is supported as the base format of the operation.

#### class `UE::Mutable::Private::CompilerOptions::Private`  
`class CompilerOptions::Private`  
_L29-47_
- L34 _public member_ `FModelOptimizationOptions OptimisationOptions;` — Detailed optimization options
- L36 _public member_ `uint64 EmbeddedDataBytesLimit = 1024;`
- L39 _public member_ `int32 MinTextureResidentMipCount = 3;` — \TODO: Unused?
- L41 _public member_ `int32 ImageCompressionQuality = 0;`
- L43 _public member_ `bool bIgnoreStates = false;`
- L44 _public member_ `bool bLog = false;`
- L46 _public member_ `FImageOperator::FImagePixelFormatFunc ImageFormatFunc;`

#### struct `UE::Mutable::Private::FStateCompilationData`  
`struct FStateCompilationData`  
_L51-64_
- L53 _public member_ `FObjectState nodeState;`
- L54 _public member_ `Ptr<ASTOp> root;`
- L55 _public member_ `FProgram::FState state;`
- L59 _public member_ `TArray<Ptr<ASTOp>> m_updateCache;` — List of instructions that need to be cached to efficiently update this state
- L63 _public member_ `TArray< TPair<Ptr<ASTOp>, TArray<FString> > > m_dynamicResources;` — List of root instructions for the dynamic resources that depend on the runtime parameters of this state.

#### class `UE::Mutable::Private::Compiler::Private`  
`class Compiler::Private`  
_L68-87_
- L72 _public function_ `Private()`
- L77 _public member_ `TSharedPtr<FErrorLog> ErrorLog;`
- L80 _public member_ `Ptr<CompilerOptions> Options;`
- L83 _public member_ `TFunction<void()> WaitCallback;`
- L86 _public prototype_ `void GenerateRoms(FModel*, const FLinkerOptions::FAdditionalData&);`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Mutable` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L26 _prototype_ `extern const FOpToolsDesc& GetOpToolsDesc(EOpType type);` (scope `UE::Mutable::Private`)

### `Plugins/Mutable/Source/MutableTools/Private/MuT/DataPacker.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Mutable` (scope `UE`)
- L8 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Mutable` (scope `UE`)
- L10 _namespace_ `namespace Private` (scope `UE::Mutable`)
- L15 _prototype_ `extern void DataOptimise( const CompilerOptions*, ASTOpList& roots );` (scope `UE::Mutable::Private`) — Convert constant data to different formats, based on their usage.

### `Plugins/Mutable/Source/MutableTools/Public/MuT/NodeMaterialModify.h` (Public)


#### struct `UE::Mutable::Private::FImageParameterData`  
`struct FImageParameterData`  
_L17-27_
- L19 _public member_ `Ptr<NodeImage> ImageNode;`
- L20 _public member_ `int32 ImagePropertyIndex = 0;`
- L21 _public member_ `int8 LayoutIndex = 0;`
- L22 _public member_ `bool bIsPassthrough = false;`
- L23 _public member_ `uint16 BlockSizeX = 0;`
- L24 _public member_ `uint16 BlockSizeY = 0;`
- L26 _public prototype_ `bool operator==(const FImageParameterData& Other) const = default;`

#### class `UE::Mutable::Private::NodeMaterialModify`  
`class NodeMaterialModify : public NodeMaterial`  
_L29-53_
- inherits: `NodeMaterial`
- L33 _public member_ `Ptr<NodeMaterial> MaterialSource;`
- L34 _public member_ `TMap<FParameterKey, FImageParameterData> ImageParameters;`
- L35 _public member_ `TMap<FParameterKey, Ptr<NodeColor>> ColorParameters;`
- L36 _public member_ `TMap<FParameterKey, Ptr<NodeScalar>> ScalarParameters;`
- L41 _public function_ `virtual const FNodeType* GetType() const override` — Node Interface
- L42 _public function_ `static const FNodeType* GetStaticType()`
- L47 _protected function_ `~NodeMaterialModify()` — Forbidden. Manage with the Ptr<> template.
- L51 _private member_ `static FNodeType StaticType;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API MUTABLETOOLS_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Mutable` (scope `UE`)
- L15 _namespace_ `namespace Private` (scope `UE::Mutable`)
