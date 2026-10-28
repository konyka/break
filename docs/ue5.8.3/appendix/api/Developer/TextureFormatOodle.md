# Developer / TextureFormatOodle

- module root: `Source/Developer/TextureFormatOodle/Source`
- headers: 4; symbols: 107
- symbol kinds: class=3, externvar=3, function=23, macro=46, member=24, prototype=2, struct=2, typedef=3, variable=1
- PrivateDependencyModuleNames: Core, DerivedDataCache, ImageCore, TextureBuild
- PrivateIncludePathModuleNames: CoreUObject, Engine, TargetPlatform, TextureCompressor

### `Source/Developer/TextureFormatOodle/Source/Private/Jobify/example_jobify.h` (Private)


#### Free symbols / members of external scopes

- L9 _prototype_ `void * example_jobify_init();` — returns void * jobifyUserPtr you must pass back
- L11 _typedef_ `OODEFFUNC typedef void (OODLE_CALLBACK t_fp_example_jobify_Job)( void * job_data );`
- L12 _typedef_ `OODEFFUNC typedef OO_U64 (OODLE_CALLBACK t_fp_example_jobify_RunJob)( t_fp_example_jobify_Job * fp_job, void * job_data , OO_U64 * dependencies, int num_dependencies, void * user_ptr );`
- L13 _typedef_ `OODEFFUNC typedef void (OODLE_CALLBACK t_fp_example_jobify_WaitJob)( OO_U64 job_handle, void * user_ptr );`
- L16 _externvar_ `extern t_fp_example_jobify_RunJob * example_jobify_run_job_fptr;`
- L17 _externvar_ `extern t_fp_example_jobify_WaitJob *example_jobify_wait_job_fptr;`
- L18 _externvar_ `extern int example_jobify_target_parallelism;`

### `Source/Developer/TextureFormatOodle/Source/Private/Jobify/example_jobify_linuxtbb.inl` (Private)


#### class `JobContext`  
`class JobContext`  
_L33-201_
- L60 _private member_ `tbb::task * root_task;` — Root task for WaitJob (this is the parent of the actual work task)
- L62 _private member_ `tbb::task * child_task;` — The actual child task we spawn
- L66 _private member_ `DepLink dep_slot[OODLE_JOB_MAX_DEPENDENCIES];` — Dependency slots. Not actually our data, it belongs to the jobs we depend on, which use it to store a linked list of their dependents.
- L69 _private member_ `tbb::spin_mutex dependents_lock;` — Dependency tracking information
- L70 _private member_ `bool job_completed;`
- L71 _private member_ `DepLink * dependents_head;`
- L72 _private member_ `DepLink * * dependents_tail_next;`
- L79 _private function_ `tbb::task * notify_dep_satisfied(tbb::task * continue_with, int num_deps=1)` — continue_with is the next task to run after this one, or NULL if we don't have a viable candidate yet. Returns the new continue_with.
- L95 _private function_ `tbb::task * notify_completion()` — Returns next task to run
- L124 _private function_ `int add_dependent(JobContext * which, int slot)` — Returns 1 if the job was already completed before we set up the dependency edge.
- L145 _public function_ `JobContext(t_fp_Oodle_Job * fp_job, void * job_data, U64 * dependencies, int num_dependencies, tbb::task_group_context *group_ctx)`
- L188 _public function_ `void wait()` — This has the same semantics as WaitJob(), i.e. you only get to do this once.

#### struct `JobContext::DepLink`  
`struct DepLink`  
_L35-39_
- L37 _public member_ `JobContext * job;`
- L38 _public member_ `DepLink * next;` — singly-linked list

#### class `JobContext::Task`  
`class Task : public tbb::task`  
_L41-57_
- inherits: `tbb::task`
- L44 _private member_ `JobContext * job;` — The job that owns this task.
- L47 _private member_ `t_fp_Oodle_Job * fp_job;` — The job callback and its (opaque) data pointer
- L48 _private member_ `void * job_data;`
- L51 _public function_ `Task(JobContext * job, t_fp_Oodle_Job * fp_job, void * job_data) : job(job), fp_job(fp_job), job_data(job_data)`
- L56 _public prototype_ `virtual tbb::task * execute();`
- L203 _function_ `tbb::task * JobContext::Task::execute()`

#### Free symbols / members of external scopes

- L23 _macro_ `#define _POSIX_C_SOURCE 200809L`
- L211 _variable_ `void * g_example_jobify_jobifyUserPtr = NULL;`
- L213 _function_ `static U64 OODLE_CALLBACK tbb_run_job(t_fp_Oodle_Job * fp_job, void * job_data, U64 * dependencies, int num_dependencies, void * user_ptr)`
- L246 _function_ `static void OODLE_CALLBACK tbb_wait_job(U64 job_handle, void * )`
- L253 _function_ `void * example_jobify_init()`

### `Source/Developer/TextureFormatOodle/Source/Private/Jobify/example_jobify_win32tp.inl` (Private)


#### class `JobContext`  
`class JobContext`  
_L49-232_
- L58 _private member_ `t_fp_Oodle_Job * fp_job;` — The job callback and its (opaque) data pointer
- L59 _private member_ `void * job_data;`
- L62 _private member_ `PTP_WORK work_handle;` — The thread pool work handle
- L65 _private member_ `SRWLOCK busy_lock;` — "Inverted" lock; held from creation until we've finished executing the job.
- L70 _private member_ `DepLink dep_slot[OODLE_JOB_MAX_DEPENDENCIES];` — Dependency slots. Not actually our data, it belongs to the jobs we depend on, which use it to store a linked list of their dependents.
- L73 _private member_ `LONG volatile num_unsatisfied_deps;` — Dependency tracking information (manipulated via Interlocked ops, don't touch directly outside init!)
- L75 _private member_ `SRWLOCK dependents_lock;` — Just used as a non-recursive mutex; protects the following fields:
- L76 _private member_ `bool job_completed;`
- L77 _private member_ `DepLink * dependents_head;`
- L78 _private member_ `DepLink * * dependents_tail_next;`
- L81 _private function_ `static VOID CALLBACK work_callback(PTP_CALLBACK_INSTANCE , PVOID context, PTP_WORK )`
- L92 _private function_ `void notify_dep_satisfied(LONG num_deps = 1)`
- L103 _private function_ `void notify_completion()`
- L134 _private function_ `LONG add_dependent(JobContext *which, int slot)` — Returns 1 if the job was already completed before we set up the dependency edge.
- L162 _public function_ `JobContext(t_fp_Oodle_Job * _fp_job, void * _job_data, OO_U64 * dependencies, int num_dependencies, void * user_ptr)`
- L208 _public function_ `~JobContext()`
- L215 _public function_ `bool valid() const`
- L220 _public function_ `void wait()`

#### struct `JobContext::DepLink`  
`struct DepLink`  
_L51-55_
- L53 _public member_ `JobContext * job;`
- L54 _public member_ `DepLink * next;` — singly-linked list

#### Free symbols / members of external scopes

- L30 _macro_ `#define InterlockedExchangeAdd(ptr,v) FPlatformAtomics::InterlockedAdd((int32 *)ptr,v)`
- L35 _macro_ `#define _WIN32_WINNT 0x0600` — For the Windows Vista-level thread pool APIs
- L47 _macro_ `#define DEBUG(...)` — #define DEBUG printf
- L234 _function_ `OO_U64 OODLE_CALLBACK example_jobify_win32tp_run_job(t_fp_Oodle_Job * fp_job, void * job_data, OO_U64 * dependencies, int num_dependencies, void * user_ptr)`
- L261 _function_ `void OODLE_CALLBACK example_jobify_win32tp_wait_job(OO_U64 job_handle, void * )`
- L272 _function_ `void * example_jobify_init()`

### `Source/Developer/TextureFormatOodle/Source/Private/Jobify/ooex.h` (Private)


#### Free symbols / members of external scopes

- L5 _macro_ `#define __OOEX_H__`
- L21 _macro_ `#define OodleX_DisplayAssertion(file,line,func,str) ( fprintf(stderr,"ASSERT: %s (%d) : %s\n",file,line,str) , 1 )`
- L22 _macro_ `#define OodleXLog_Printf_v1 printf`
- L23 _macro_ `#define OodleXLog_Printf_v0 printf`
- L30 _macro_ `#define OOEX_BREAK() __debugbreak()`
- L32 _macro_ `#define OOEX_BREAK() __builtin_trap()`
- L36 _macro_ `#define OOEX_BREAK() assert(0)`
- L45 _macro_ `#define OOEX_PLATFORM_ANDROID`
- L49 _macro_ `#define OOEX_PLATFORM_LINUX`
- L60 _macro_ `#define OOEX_PLATFORM_NT`
- L71 _macro_ `#define OOEX_PLATFORM_IOS`
- L72 _macro_ `#define OOEX_PLATFORM_IOS_SIM`
- L76 _macro_ `#define OOEX_PLATFORM_MAC`
- L88 _macro_ `#define OOEX_DO_ASSERTS 1`
- L90 _macro_ `#define OOEX_DO_ASSERTS 0`
- L98 _macro_ `#define OOEX_FUNCTION_NAME __FUNCTION__`
- L100 _macro_ `#define OOEX_FUNCTION_NAME 0`
- L107 _macro_ `#define OOEX_ASSERT_BREAK() OOEX_BREAK()`
- L109 _macro_ `#define OOEX_ASSERT_FAILURE_ALWAYS(str) do { if ( OodleX_DisplayAssertion(__FILE__,__LINE__,OOEX_FUNCTION_NAME,str) ) OOEX_ASSERT_BREAK(); } while(0)`
- L111 _macro_ `#define OOEX_ASSERT_ALWAYS(exp) do { if ( ! (exp) ) { OOEX_ASSERT_FAILURE_ALWAYS(#exp); } } while(0)`
- L116 _macro_ `#define OOEX_ASSERT(exp) OOEX_ASSERT_ALWAYS(exp)`
- L118 _macro_ `#define OOEX_DURING_ASSERT(exp) exp` — OOEX_DURING_ASSERT is to set up expressions or declare variables that are only used in asserts
- L120 _macro_ `#define OOEX_ASSERT_FAILURE(str) OOEX_ASSERT_FAILURE_ALWAYS(str)`
- L124 _macro_ `#define OOEX_ASSERT(exp) (void)0`
- L126 _macro_ `#define OOEX_DURING_ASSERT(exp) (void)0`
- L128 _macro_ `#define OOEX_ASSERT_FAILURE(str) (void)0`
- L136 _macro_ `# define OOEX_UNUSED_VARIABLE(x) x`
- L138 _macro_ `# define OOEX_UNUSED_VARIABLE(x) (void)(sizeof(x))`
- L144 _macro_ `#define OOEX_MIN(a,b) ( (a) < (b) ? (a) : (b) )`
- L148 _macro_ `#define OOEX_MAX(a,b) ( (a) > (b) ? (a) : (b) )`
- L152 _macro_ `#define OOEX_ABS(a) ( ((a) < 0) ? -(a) : (a) )`
- L156 _macro_ `#define OOEX_CLAMP(val,lo,hi) OOEX_MAX( OOEX_MIN(val,hi), lo )`
- L161 _macro_ `#define OOEX_STRINGIZE( L ) #L`
- L163 _macro_ `#define OOEX_STRING_JOIN OO_STRING_JOIN`
- L170 _function_ `static inline OO_U32 ooex_get32_le(const OO_U8 * ptr)` — Little-Endian 32-bit integer read/write
- L179 _function_ `static inline void ooex_put32_le(OO_U8 * ptr, OO_U32 val)`
- L187 _macro_ `#define OOEX_GET32_LE(ptr) ooex_get32_le((const OO_U8 *)(ptr))`
- L188 _macro_ `#define OOEX_PUT32_LE(ptr,val) ooex_put32_le((OO_U8 *)(ptr), (val))`
- L195 _macro_ `#define OOEX_64_FMT "%I64"`
- L196 _macro_ `#define OOEX_64_FMT_SIZE "I64"`
- L198 _macro_ `#define OOEX_64_FMT "%ll"`
- L199 _macro_ `#define OOEX_64_FMT_SIZE "ll"`
- L202 _macro_ `#define OOEX_S64_FMT OOEX_64_FMT "d"`
- L203 _macro_ `#define OOEX_U64_FMT OOEX_64_FMT "u"`
