# NoModule / _nomodule__Developer__Source__Developer__ZenPluggableTransport__zenbase

- module root: `.`
- headers: 4; symbols: 118
- symbol kinds: class=3, function=35, macro=62, member=3, namespace=2, prototype=13

### `Source/Developer/ZenPluggableTransport/zenbase/include/zenbase/atomic.h` (Other)


#### Free symbols / members of external scopes

- L15 _namespace_ `namespace zen`
- L18 _function_ `AtomicIncrement(volatile uint32_t& value)` (scope `zen`)
- L27 _function_ `AtomicDecrement(volatile uint32_t& value)` (scope `zen`)
- L37 _function_ `AtomicIncrement(volatile uint64_t& value)` (scope `zen`)
- L46 _function_ `AtomicDecrement(volatile uint64_t& value)` (scope `zen`)
- L56 _function_ `AtomicAdd(volatile uint32_t& value, uint32_t amount)` (scope `zen`)
- L65 _function_ `AtomicAdd(volatile uint64_t& value, uint64_t amount)` (scope `zen`)

### `Source/Developer/ZenPluggableTransport/zenbase/include/zenbase/concepts.h` (Other)


#### Free symbols / members of external scopes

- L33 _prototype_ `std::invoke(std::forward<F>(f), std::forward<A>(a)...);` (scope `std`)

### `Source/Developer/ZenPluggableTransport/zenbase/include/zenbase/refcount.h` (Other)


#### class `zen::RefCounted`  
`class RefCounted`  
_L14-43_
- desc: Helper base class for reference counted objects using intrusive reference counting
- L17 _public prototype_ `RefCounted() = default;`
- L18 _public prototype_ `virtual ~RefCounted() = default;`
- L20 _public function_ `inline uint32_t AddRef() const`
- L21 _public function_ `inline uint32_t Release() const`
- L33 _public prototype_ `RefCounted(const RefCounted&) = delete;`
- L34 _public prototype_ `RefCounted(RefCounted&&) = delete;`
- L35 _public prototype_ `RefCounted& operator=(const RefCounted&) = delete;`
- L36 _public prototype_ `RefCounted& operator=(RefCounted&&) = delete;`
- L39 _protected function_ `inline uint32_t RefCount() const`
- L42 _private member_ `uint32_t m_RefCount = 0;`

#### class `zen::RefPtr`  
`template<class T> class RefPtr`  
_L50-114_
- L53 _public prototype_ `inline RefPtr() = default;`
- L54 _public function_ `inline RefPtr(const RefPtr& Rhs) : m_Ref(Rhs.m_Ref)`
- L55 _public function_ `inline RefPtr(T* Ptr) : m_Ref(Ptr)`
- L56 _public function_ `inline ~RefPtr()`
- L58 _public function_ `[[nodiscard]] inline bool IsNull() const`
- L59 _public function_ `inline explicit operator bool() const`
- L60 _public function_ `inline operator T*() const`
- L61 _public function_ `inline T* operator->() const`
- L63 _public prototype_ `inline std::strong_ordering operator<=>(const RefPtr& Rhs) const = default;`
- L65 _public function_ `inline RefPtr& operator=(T* Rhs)`
- L72 _public function_ `inline RefPtr& operator=(const RefPtr& Rhs)`
- L82 _public function_ `inline RefPtr& operator=(RefPtr&& Rhs) noexcept`
- L93 _public function_ `template<typename OtherType> inline RefPtr& operator=(RefPtr<OtherType>&& Rhs) noexcept`
- L103 _public function_ `inline RefPtr(RefPtr&& Rhs) noexcept : m_Ref(Rhs.m_Ref)`
- L105 _public function_ `template<typename OtherType> explicit inline RefPtr(RefPtr<OtherType>&& Rhs) noexcept : m_Ref(Rhs.m_Ref)`
- L111 _private member_ `T* m_Ref = nullptr;`

#### class `zen::Ref`  
`template<class T> class Ref`  
_L124-178_
- L127 _public prototype_ `inline Ref() = default;`
- L128 _public function_ `inline Ref(const Ref& Rhs) : m_Ref(Rhs.m_Ref)`
- L129 _public function_ `inline explicit Ref(T* Ptr) : m_Ref(Ptr)`
- L130 _public function_ `inline ~Ref()`
- L134 _public function_ `template<typename DerivedType> requires DerivedFrom<DerivedType, T> inline Ref(const Ref<DerivedType>& Rhs) : Ref(Rhs.m_Ref)`
- L136 _public function_ `[[nodiscard]] inline bool IsNull() const`
- L137 _public function_ `inline explicit operator bool() const`
- L138 _public function_ `inline T* operator->() const`
- L139 _public function_ `inline T& operator*() const`
- L140 _public function_ `inline T* Get() const`
- L142 _public prototype_ `inline std::strong_ordering operator<=>(const Ref& Rhs) const = default;`
- L144 _public function_ `inline Ref& operator=(T* Rhs)`
- L151 _public function_ `inline Ref& operator=(const Ref& Rhs)`
- L161 _public function_ `inline Ref& operator=(Ref&& Rhs) noexcept`
- L171 _public function_ `inline Ref(Ref&& Rhs) noexcept : m_Ref(Rhs.m_Ref)`
- L174 _private member_ `T* m_Ref = nullptr;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace zen`

### `Source/Developer/ZenPluggableTransport/zenbase/include/zenbase/zenbase.h` (Other)


#### Free symbols / members of external scopes

- L16 _macro_ `#define ZEN_PLATFORM_WINDOWS 0`
- L17 _macro_ `#define ZEN_PLATFORM_LINUX 0`
- L18 _macro_ `#define ZEN_PLATFORM_MAC 0`
- L22 _macro_ `# define ZEN_PLATFORM_WINDOWS 1`
- L23 _macro_ `# define ZEN_PLATFORM_NAME "Windows"`
- L26 _macro_ `# define ZEN_PLATFORM_LINUX 1`
- L27 _macro_ `# define ZEN_PLATFORM_NAME "Linux"`
- L30 _macro_ `# define ZEN_PLATFORM_MAC 1`
- L31 _macro_ `# define ZEN_PLATFORM_NAME "MacOS"`
- L36 _macro_ `# define NOMINMAX // stops Windows.h from defining 'min/max' macros`
- L39 _macro_ `# define NOGDI`
- L42 _macro_ `# define WIN32_LEAN_AND_MEAN // cut-down what Windows.h defines`
- L50 _macro_ `#define ZEN_COMPILER_CLANG 0`
- L51 _macro_ `#define ZEN_COMPILER_MSC 0`
- L52 _macro_ `#define ZEN_COMPILER_GCC 0`
- L57 _macro_ `# define ZEN_COMPILER_CLANG 1`
- L60 _macro_ `# define ZEN_COMPILER_MSC 1`
- L63 _macro_ `# define ZEN_COMPILER_GCC 1`
- L80 _macro_ `# define ZEN_THIRD_PARTY_INCLUDES_START \`
- L100 _macro_ `# define ZEN_THIRD_PARTY_INCLUDES_END __pragma(warning(pop))`
- L102 _macro_ `# define ZEN_THIRD_PARTY_INCLUDES_END _Pragma("clang diagnostic pop")`
- L104 _macro_ `# define ZEN_THIRD_PARTY_INCLUDES_END _Pragma("GCC diagnostic pop")`
- L109 _macro_ `# define ZEN_DEBUG_BREAK() \`
- L151 _macro_ `# define ZEN_ARCH_X64 1`
- L152 _macro_ `# define ZEN_ARCH_ARM64 0`
- L154 _macro_ `# define ZEN_ARCH_X64 0`
- L155 _macro_ `# define ZEN_ARCH_ARM64 1`
- L165 _macro_ `# define ZEN_BUILD_DEBUG 0`
- L166 _macro_ `# define ZEN_BUILD_RELEASE 1`
- L167 _macro_ `# define ZEN_BUILD_NAME "release"`
- L169 _macro_ `# define ZEN_BUILD_DEBUG 1`
- L170 _macro_ `# define ZEN_BUILD_RELEASE 0`
- L171 _macro_ `# define ZEN_BUILD_NAME "debug"`
- L176 _macro_ `#define ZEN_PLATFORM_SUPPORTS_UNALIGNED_LOADS 1`
- L179 _macro_ `# define ZEN_SIZEOF_WCHAR_T 4`
- L182 _macro_ `# define ZEN_SIZEOF_WCHAR_T 2`
- L189 _prototype_ `template<typename T> auto ZenArrayCountHelper(T& t) -> typename std::enable_if<__is_array(T), char (&)[sizeof(t) / sizeof(t[0]) + 1]>::type;`
- L192 _prototype_ `template<typename T, uint32_t N> char (&ZenArrayCountHelper(const T (&)[N]))[N + 1];`
- L195 _macro_ `#define ZEN_ARRAY_COUNT(array) (sizeof(ZenArrayCountHelper(array)) - 1)`
- L200 _macro_ `# define ZEN_NOINLINE __declspec(noinline)`
- L201 _macro_ `# define ZEN_FORCEINLINE [[msvc::forceinline]]`
- L203 _macro_ `# define ZEN_NOINLINE __attribute__((noinline))`
- L204 _macro_ `# define ZEN_FORCEINLINE __attribute__((always_inline))`
- L208 _macro_ `# define ZEN_EXE_SUFFIX_LITERAL ".exe"`
- L210 _macro_ `# define ZEN_EXE_SUFFIX_LITERAL ""`
- L213 _macro_ `#define ZEN_UNUSED(...) ((void)__VA_ARGS__)`
- L218 _macro_ `# define ZEN_DISABLE_OPTIMIZATION_ACTUAL __pragma(optimize("", off))`
- L219 _macro_ `# define ZEN_ENABLE_OPTIMIZATION_ACTUAL __pragma(optimize("", on))`
- L221 _macro_ `# define ZEN_DISABLE_OPTIMIZATION_ACTUAL _Pragma("GCC push_options") _Pragma("GCC optimize (\"O0\")")`
- L222 _macro_ `# define ZEN_ENABLE_OPTIMIZATION_ACTUAL _Pragma("GCC pop_options")`
- L224 _macro_ `# define ZEN_DISABLE_OPTIMIZATION_ACTUAL _Pragma("clang optimize off")`
- L225 _macro_ `# define ZEN_ENABLE_OPTIMIZATION_ACTUAL _Pragma("clang optimize on")`
- L229 _macro_ `#define ZEN_DISABLE_OPTIMIZATION ZEN_DISABLE_OPTIMIZATION_ACTUAL` — Set up optimization control macros, now that we have both the build settings and the platform macros
- L232 _macro_ `# define ZEN_ENABLE_OPTIMIZATION ZEN_DISABLE_OPTIMIZATION_ACTUAL`
- L234 _macro_ `# define ZEN_ENABLE_OPTIMIZATION ZEN_ENABLE_OPTIMIZATION_ACTUAL`
- L237 _macro_ `#define ZEN_ENABLE_OPTIMIZATION_ALWAYS ZEN_ENABLE_OPTIMIZATION_ACTUAL`
- L241 _macro_ `# define ZEN_CODE_SECTION(Name) __declspec(code_seg(Name))` — Tells the compiler to put the decorated function in a certain section (aka. segment) of the executable.
- L242 _macro_ `# define ZEN_DATA_SECTION(Name) __declspec(allocate(Name))`
- L243 _macro_ `# define ZEN_FORCENOINLINE __declspec(noinline) /* Force code to NOT be inline */`
- L244 _macro_ `# define LINE_TERMINATOR_ANSI "\r\n"` — #	define ZEN_FORCENOINLINE	   __declspec(noinline)   Force code to NOT be inline
- L246 _macro_ `# define ZEN_CODE_SECTION(Name)`
- L247 _macro_ `# define ZEN_DATA_SECTION(Name)`
- L248 _macro_ `# define ZEN_FORCENOINLINE`
- L249 _macro_ `# define LINE_TERMINATOR_ANSI "\n"`
