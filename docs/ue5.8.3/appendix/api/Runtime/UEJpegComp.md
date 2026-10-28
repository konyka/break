# Runtime / UEJpegComp

- module root: `Source/Runtime/UEJpegComp`
- headers: 1; symbols: 139
- symbol kinds: enum=3, enumerator=14, externvar=1, member=75, prototype=20, struct=12, typedef=14

### `Source/Runtime/UEJpegComp/Source/uejpeg.h` (Other)


#### enum `(anonymous)`  
`typedef enum`  
_L79-90_
- desc: Error codes

#### enum `(anonymous)`  
`typedef enum`  
_L93-97_
- desc: Flags to be used in compression or decompression

#### enum `(anonymous)`  
`enum`  
_L99-101_

#### struct `(anonymous)`  
`typedef struct`  
_L105-109_
- desc: IO callbacks For use with uejpeg_*() to specify any input or output method. All methods internally use this!

#### struct `(anonymous)`  
`typedef struct`  
_L112-116_
- desc: For using memory buffers as input or output.

#### struct `(anonymous)`  
`typedef struct`  
_L121-125_
- desc: For setting custom memory allocators.

#### struct `(anonymous)`  
`typedef struct`  
_L127-130_

#### struct `(anonymous)`  
`typedef struct`  
_L133-136_
- desc: compression callbacks, for using custom compression methods, such as zlib

#### struct `uejpeg_ihdr_t`  
`typedef struct uejpeg_ihdr_t`  
_L144-152_
- desc: An internal structure used to store the header of a uejpeg file.
- L145 _public member_ `unsigned version;`
- L146 _public member_ `unsigned width;`
- L147 _public member_ `unsigned height;`
- L148 _public member_ `unsigned char bit_depth;`
- L149 _public member_ `unsigned char comp;`
- L150 _public member_ `unsigned char method;`
- L151 _public member_ `unsigned char num_splits;`

#### struct `uejpeg_lossy_hdr_t`  
`typedef struct uejpeg_lossy_hdr_t`  
_L155-162_
- desc: An internal structure used to store the header of a uejpeg file.
- L156 _public member_ `unsigned short coef_dims[4][2];`
- L158 _public member_ `unsigned short dequant[4][64];` — Quantization tables
- L159 _public member_ `char app14_color_transform;` — valid values are 0(CMYK),1(YCCK),2(YCbCrA)
- L160 _public member_ `char jfif;`
- L161 _public member_ `char comp_id[4];`

#### struct `(anonymous)`  
`typedef struct`  
_L164-175_

#### struct `(anonymous)`  
`typedef struct`  
_L177-184_

#### struct `(anonymous)`  
`typedef struct`  
_L186-201_

#### struct `(anonymous)`  
`typedef struct`  
_L203-217_

#### struct `(anonymous)`  
`typedef struct`  
_L219-236_

#### Free symbols / members of external scopes

- L80 _enumerator_ `UEJPEG_ERR_NONE = 0` (scope `__anoncf35e9dd0103`) — No Error, everything OK! :)
- L81 _enumerator_ `UEJPEG_ERR_NOT_A_JPEG = 1` (scope `__anoncf35e9dd0103`) — Not a JPEG file. Happens if you try to encode from a non-JPEG file.
- L82 _enumerator_ `UEJPEG_ERR_CANNOT_OPEN_FILE = 2` (scope `__anoncf35e9dd0103`) — Cannot open file. Happens if the file routines cannot open the files you specified!
- L83 _enumerator_ `UEJPEG_ERR_NOT_UEJPEG_FILE = 3` (scope `__anoncf35e9dd0103`) — Not a uejpeg file. Happens if you try to decode a non-uejpeg file.
- L84 _enumerator_ `UEJPEG_ERR_CORRUPT_UEJPEG_FILE = 4` (scope `__anoncf35e9dd0103`) — Corrupt uejpeg file. Happens if the uejpeg file is corrupt.
- L85 _enumerator_ `UEJPEG_ERR_WRITE_FAILED = 5` (scope `__anoncf35e9dd0103`) — Write failed. Happens if the file routines cannot write to the files you specified!
- L86 _enumerator_ `UEJPEG_ERR_OUT_OF_MEMORY = 6` (scope `__anoncf35e9dd0103`) — Out of memory. Happens if the uejpeg library cannot allocate enough memory.
- L87 _enumerator_ `UEJPEG_ERR_UNSUPPORTED_COLORSPACE = 7` (scope `__anoncf35e9dd0103`) — Unsupported colorspace. Happens when exporting if the JPEG file is not YCbCr.
- L88 _enumerator_ `UEJPEG_ERR_READ_FAILED = 8` (scope `__anoncf35e9dd0103`) — Read failed. Happens if the file routines cannot read from the files you specified!
- L89 _enumerator_ `UEJPEG_ERR_UNSUPPORTED = 9` (scope `__anoncf35e9dd0103`) — Other Unsupported. Happens usually when you try to decode to jpeg in an uncommon format.
- L90 _typedef_ `} uejpeg_error_t;`
- L94 _enumerator_ `UEJPEG_FLAG_NONE = 0x0` (scope `__anoncf35e9dd0203`) — no flags
- L95 _enumerator_ `UEJPEG_FLAG_NO_COMPRESSION = 0x1` (scope `__anoncf35e9dd0203`) — don't compress the coefficients, just store them
- L96 _enumerator_ `UEJPEG_FLAG_FASTDCT = 0x2` (scope `__anoncf35e9dd0203`) — use a fast dct transform which matches libjpegturbo's fastdct.
- L97 _typedef_ `} uejpeg_flags_t;`
- L100 _enumerator_ `UEJPEG_MAX_SPLITS = 16` (scope `__anoncf35e9dd0303`)
- L106 _member_ `size_t (*write)(void *user, const void *data, size_t size);` (scope `__anoncf35e9dd0408`) — write 'data' with 'size' bytes.  return number of bytes actually written
- L107 _member_ `size_t (*read)(void *user, void *data, size_t size);` (scope `__anoncf35e9dd0408`) — read 'data' with 'size' bytes.  return number of bytes actually read
- L108 _member_ `int (*eof)(void *user);` (scope `__anoncf35e9dd0408`) — return 1 if end-of-file, 0 otherwise
- L109 _typedef_ `} uejpeg_io_callbacks_t;`
- L113 _member_ `char *base;` (scope `__anoncf35e9dd0508`)
- L114 _member_ `char *ptr;` (scope `__anoncf35e9dd0508`)
- L115 _member_ `size_t size;` (scope `__anoncf35e9dd0508`)
- L116 _typedef_ `} uejpeg_io_buffer_t;`
- L118 _externvar_ `extern const uejpeg_io_callbacks_t s_uejpeg_buffer_fns;`
- L122 _member_ `void *(*alloc)(size_t size);` (scope `__anoncf35e9dd0608`) — allocate 'size' bytes.  return pointer to allocated memory
- L123 _member_ `void (*free)(void *ptr);` (scope `__anoncf35e9dd0608`) — free memory at 'ptr'
- L124 _member_ `void *(*realloc)(void *ptr, size_t size);` (scope `__anoncf35e9dd0608`) — reallocate 'ptr' to 'size' bytes.  return pointer to reallocated memory
- L125 _typedef_ `} uejpeg_alloc_t;`
- L128 _member_ `void *data;` (scope `__anoncf35e9dd0708`)
- L129 _member_ `size_t size;` (scope `__anoncf35e9dd0708`)
- L130 _typedef_ `} uejpeg_buffer_t;`
- L134 _member_ `uejpeg_buffer_t (*compress)(const void *data, size_t size);` (scope `__anoncf35e9dd0808`)
- L135 _member_ `int (*decompress)(const void *data, size_t size, void *out_data, size_t out_size);` (scope `__anoncf35e9dd0808`)
- L136 _typedef_ `} uejpeg_compression_t;`
- L139 _prototype_ `void uejpeg_set_alloc(const uejpeg_alloc_t *alloc);` — Set custom allocators.  If not set, malloc/free/realloc will be used.
- L141 _prototype_ `void uejpeg_set_compression(const uejpeg_compression_t *compression);` — Set custom compression methods.  If not set, oodle compression methods will be used.
- L152 _typedef_ `} uejpeg_ihdr_t;`
- L162 _typedef_ `} uejpeg_lossy_hdr_t;`
- L165 _member_ `int y_start[4];` (scope `__anoncf35e9dd0908`)
- L166 _member_ `int y_end[4];` (scope `__anoncf35e9dd0908`)
- L167 _member_ `int width[4];` (scope `__anoncf35e9dd0908`)
- L168 _member_ `int height[4];` (scope `__anoncf35e9dd0908`)
- L169 _member_ `int num_blocks;` (scope `__anoncf35e9dd0908`)
- L170 _member_ `short *xcoefs;` (scope `__anoncf35e9dd0908`)
- L171 _member_ `char *split_xcoefs;` (scope `__anoncf35e9dd0908`)
- L172 _member_ `unsigned char *oodle_buf;` (scope `__anoncf35e9dd0908`)
- L173 _member_ `int oodle_size;` (scope `__anoncf35e9dd0908`)
- L174 _member_ `int coefs_size;` (scope `__anoncf35e9dd0908`)
- L175 _typedef_ `} uejpeg_internal_split_t;`
- L178 _member_ `int error;` (scope `__anoncf35e9dd0a08`)
- L179 _member_ `int split_height_min;` (scope `__anoncf35e9dd0a08`)
- L180 _member_ `int split_height[4];` (scope `__anoncf35e9dd0a08`)
- L181 _member_ `int split_blocks[4];` (scope `__anoncf35e9dd0a08`)
- L182 _member_ `int total_split_blocks;` (scope `__anoncf35e9dd0a08`)
- L183 _member_ `uejpeg_internal_split_t splits[UEJPEG_MAX_SPLITS];` (scope `__anoncf35e9dd0a08`)
- L184 _typedef_ `} uejpeg_internal_splits_t;`
- L187 _member_ `int error;` (scope `__anoncf35e9dd0b08`) — If there was an error, it is stored here.
- L188 _member_ `int jobs_to_run;` (scope `__anoncf35e9dd0b08`) — How many times to run uejpeg_decode_thread_run!
- L191 _member_ `const uejpeg_io_callbacks_t *io;` (scope `__anoncf35e9dd0b08`) — arguments
- L192 _member_ `void *io_user;` (scope `__anoncf35e9dd0b08`)
- L193 _member_ `int flags;` (scope `__anoncf35e9dd0b08`)
- L196 _member_ `int width, height, comp;` (scope `__anoncf35e9dd0b08`) — internal state
- L196 _member_ `int width, height, comp;` (scope `__anoncf35e9dd0b08`) — internal state
- L196 _member_ `int width, height, comp;` (scope `__anoncf35e9dd0b08`) — internal state
- L197 _member_ `int num_splits;` (scope `__anoncf35e9dd0b08`)
- L199 _member_ `uejpeg_lossy_hdr_t lhdr;` (scope `__anoncf35e9dd0b08`)
- L200 _member_ `uejpeg_internal_splits_t s;` (scope `__anoncf35e9dd0b08`)
- L201 _typedef_ `} uejpeg_encode_context_t;`
- L204 _member_ `int error;` (scope `__anoncf35e9dd0c08`) — If there was an error, it is stored here.
- L205 _member_ `int jobs_to_run;` (scope `__anoncf35e9dd0c08`) — How many times to run uejpeg_decode_thread_run!
- L208 _member_ `int flags;` (scope `__anoncf35e9dd0c08`) — arguments
- L211 _member_ `uejpeg_ihdr_t ihdr;` (scope `__anoncf35e9dd0c08`) — internal state
- L212 _member_ `uejpeg_lossy_hdr_t lhdr;` (scope `__anoncf35e9dd0c08`)
- L213 _member_ `uejpeg_internal_splits_t spx;` (scope `__anoncf35e9dd0c08`)
- L214 _member_ `int yuva_stride[4];` (scope `__anoncf35e9dd0c08`)
- L215 _member_ `int yuva_height[4];` (scope `__anoncf35e9dd0c08`)
- L216 _member_ `unsigned char *yuva[4];` (scope `__anoncf35e9dd0c08`)
- L217 _typedef_ `} uejpeg_decode_context_t;`
- L220 _member_ `int error;` (scope `__anoncf35e9dd0d08`) — If there was an error, it is stored here.
- L221 _member_ `int jobs_to_run;` (scope `__anoncf35e9dd0d08`) — How many times to run uejpeg_decode_thread_run!
- L224 _member_ `const uejpeg_io_callbacks_t *io;` (scope `__anoncf35e9dd0d08`) — arguments
- L225 _member_ `void *io_user;` (scope `__anoncf35e9dd0d08`)
- L226 _member_ `int width, height, comp;` (scope `__anoncf35e9dd0d08`)
- L226 _member_ `int width, height, comp;` (scope `__anoncf35e9dd0d08`)
- L226 _member_ `int width, height, comp;` (scope `__anoncf35e9dd0d08`)
- L227 _member_ `const unsigned char *in_data;` (scope `__anoncf35e9dd0d08`)
- L228 _member_ `int flags;` (scope `__anoncf35e9dd0d08`)
- L231 _member_ `int num_splits;` (scope `__anoncf35e9dd0d08`) — internal state
- L232 _member_ `uejpeg_internal_splits_t spx;` (scope `__anoncf35e9dd0d08`)
- L233 _member_ `uejpeg_lossy_hdr_t lhdr;` (scope `__anoncf35e9dd0d08`)
- L234 _member_ `float fdtbl_Y[64];` (scope `__anoncf35e9dd0d08`)
- L235 _member_ `float fdtbl_UV[64];` (scope `__anoncf35e9dd0d08`)
- L236 _typedef_ `} uejpeg_encode_image_context_t;`
- L240 _prototype_ `int uejpeg_encode_jpeg_mem(const unsigned char *jpeg_data, int jpeg_data_size, unsigned char **out_uejpeg_data, int *out_uejpeg_size, int flags);` — Encode a JPEG file to uejpeg format. This second function operates totally in memory.
- L247 _prototype_ `uejpeg_encode_context_t uejpeg_encode_jpeg_mem_threaded_start(const unsigned char *data, int size, int flags);` — Threaded API In this API you first call start, and it does some synchronous work and gives you a state context to pass to the run function. Then inside threads, you call the run function with job_idx == 0 .. context.jobs_to_run Then you wait for all the threads to finish processing all the jobs. Then you call finish to get the output data.
- L248 _prototype_ `int uejpeg_encode_jpeg_thread_run(uejpeg_encode_context_t *context, int job_idx);`
- L249 _prototype_ `int uejpeg_encode_jpeg_mem_threaded_finish(uejpeg_encode_context_t *context, unsigned char **out_data, int *out_size);`
- L252 _prototype_ `int uejpeg_encode_to_mem(unsigned char **out_data, int *out_size, int width, int height, int channels, const unsigned char *rgba, int quality, int flags);` — Encode a raw image to a uejpeg file.
- L254 _prototype_ `uejpeg_encode_image_context_t uejpeg_encode_image_mem_threaded_start(int width, int height, int comp, const unsigned char *in_data, int quality, int flags);`
- L255 _prototype_ `uejpeg_encode_image_context_t uejpeg_encode_image_threaded_start(const uejpeg_io_callbacks_t *io, void *io_user, int width, int height, int comp, const unsigned char *in_data, int quality, int flags);`
- L256 _prototype_ `int uejpeg_encode_image_thread_run(uejpeg_encode_image_context_t *ctx, int job_idx);`
- L257 _prototype_ `int uejpeg_encode_image_threaded_finish(uejpeg_encode_image_context_t *ctx);`
- L258 _prototype_ `int uejpeg_encode_image_mem_threaded_finish(uejpeg_encode_image_context_t *ctx, unsigned char **out_data, int *out_size);`
- L262 _prototype_ `unsigned char *uejpeg_decode_mem(const unsigned char *data, int size, int *width, int *height, int *channels, int flags);` — Decode a UEJPEG file to a raw image. Interface is like stbi_load_from_file, stbi_load_from_memory, stbi_load, etc.
- L263 _prototype_ `unsigned char *uejpeg_decode(const uejpeg_io_callbacks_t *io, void *io_user, int *out_width, int *out_height, int *out_comp, int flags);`
- L271 _prototype_ `uejpeg_decode_context_t uejpeg_decode_mem_threaded_start(const unsigned char *data, int size, int flags);`
- L272 _prototype_ `uejpeg_decode_context_t uejpeg_decode_threaded_start(const uejpeg_io_callbacks_t *io, void *io_user, int flags);`
- L273 _prototype_ `int uejpeg_decode_thread_run(uejpeg_decode_context_t *context, int job_idx);`
- L274 _prototype_ `unsigned char *uejpeg_decode_threaded_finish(uejpeg_decode_context_t *context, int *out_width, int *out_height, int *out_comp);`
- L277 _prototype_ `int uejpeg_decode_to_jpeg(const uejpeg_io_callbacks_t *in_io, void *in_io_user, const uejpeg_io_callbacks_t *out_io, void *out_io_user, int flags);` — Decode a UEJPEG file to a JPEG file.
- L278 _prototype_ `int uejpeg_decode_mem_to_jpeg(const unsigned char *data, int size, unsigned char **out_data, int *out_size, int flags);`
