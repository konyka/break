#include <core/trace_core_app.h>

#include <core/trace_schema.h>

#include <stdatomic.h>
#include <stdlib.h>
#include <string.h>

#define TRACE_PREFIX "COREAPPTRACE "
#define TRACE_PREFIX_LENGTH (sizeof(TRACE_PREFIX) - 1u)
#define TRACE_MAX_NUMBER_DIGITS 18u

typedef struct TraceWriter {
    char *out;
    u64 pos;
} TraceWriter;

typedef struct TraceField {
    const char *key;
    usize key_length;
    const char *value;
    usize value_length;
} TraceField;

static void trace_put(TraceWriter *w, const char *bytes, usize length)
{
    if (w->out) memcpy(w->out + w->pos, bytes, length);
    w->pos += length;
}

static void trace_puts(TraceWriter *w, const char *s)
{
    trace_put(w, s, strlen(s));
}

static void trace_put_u32(TraceWriter *w, u32 value)
{
    char digits[10];
    usize n = 0u;
    do {
        digits[n++] = (char)('0' + value % 10u);
        value /= 10u;
    } while (value != 0u);
    while (n > 0u) trace_put(w, &digits[--n], 1u);
}

static void trace_put_string(TraceWriter *w, const char *s, usize length)
{
    static const char hex[] = "0123456789abcdef";
    trace_put(w, "\"", 1u);
    for (usize i = 0u; i < length; ++i) {
        u8 byte = (u8)s[i];
        if (byte == '"' || byte == '\\') {
            char escaped[2] = {'\\', (char)byte};
            trace_put(w, escaped, 2u);
        } else if (byte < 0x20u) {
            char escaped[6] = {'\\', 'u', '0', '0', hex[byte >> 4], hex[byte & 0xfu]};
            trace_put(w, escaped, 6u);
        } else {
            trace_put(w, &s[i], 1u);
        }
    }
    trace_put(w, "\"", 1u);
}

static bool trace_is_number(const char *s, usize length)
{
    if (length == 0u || length > TRACE_MAX_NUMBER_DIGITS) return false;
    if (length > 1u && s[0] == '0') return false;
    for (usize i = 0u; i < length; ++i) {
        if (s[i] < '0' || s[i] > '9') return false;
    }
    return true;
}

static bool trace_same(const char *a, usize a_length, const char *b, usize b_length)
{
    return a_length == b_length && memcmp(a, b, a_length) == 0;
}

/* Splits one line (without '\n'/'\r') into fields. Returns false when the
 * line is malformed; *event receives the index of the event= field and *ts
 * the index of ts_us= (BREAK_TRACE_CORE_APP_MAX_FIELDS when absent). */
static bool trace_parse_line(const char *p, const char *end, TraceField *fields, u32 *count,
                             u32 *event, u32 *ts)
{
    *count = 0u;
    *event = BREAK_TRACE_CORE_APP_MAX_FIELDS;
    *ts = BREAK_TRACE_CORE_APP_MAX_FIELDS;
    if ((usize)(end - p) < TRACE_PREFIX_LENGTH ||
        memcmp(p, TRACE_PREFIX, TRACE_PREFIX_LENGTH) != 0) {
        return false;
    }
    p += TRACE_PREFIX_LENGTH;
    while (p < end) {
        if (*p == ' ' || *p == '\t') {
            p++;
            continue;
        }
        const char *field_end = p;
        while (field_end < end && *field_end != ' ' && *field_end != '\t') field_end++;
        const char *equals = memchr(p, '=', (usize)(field_end - p));
        if (!equals || equals == p || *count == BREAK_TRACE_CORE_APP_MAX_FIELDS) return false;
        TraceField field = {p, (usize)(equals - p), equals + 1, (usize)(field_end - equals - 1)};
        for (u32 i = 0u; i < *count; ++i) {
            if (trace_same(fields[i].key, fields[i].key_length, field.key, field.key_length)) {
                return false;
            }
        }
        if (trace_same(field.key, field.key_length, "event", 5u)) *event = *count;
        if (trace_same(field.key, field.key_length, "ts_us", 5u)) {
            if (!trace_is_number(field.value, field.value_length)) return false;
            *ts = *count;
        }
        fields[(*count)++] = field;
        p = field_end;
    }
    if (*count == 0u || !trace_same(fields[0].key, fields[0].key_length, "version", 7u) ||
        !trace_same(fields[0].value, fields[0].value_length, "1", 1u)) {
        return false;
    }
    return *event < *count && fields[*event].value_length > 0u;
}

static void trace_write_event(TraceWriter *w, const TraceField *fields, u32 count, u32 event,
                              u32 ts, u32 ordinal)
{
    trace_puts(w, "{\"name\":");
    trace_put_string(w, fields[event].value, fields[event].value_length);
    trace_puts(w, ",\"cat\":\"" BREAK_TRACE_CAT_CORE_APP "\",\"ph\":\"i\",\"s\":\"g\",\"ts\":");
    if (ts < count) {
        trace_put(w, fields[ts].value, fields[ts].value_length);
    } else {
        trace_put_u32(w, ordinal);
    }
    trace_puts(w, ",\"pid\":1,\"tid\":1,\"args\":{");
    bool first = true;
    for (u32 i = 1u; i < count; ++i) {
        if (i == event || i == ts) continue;
        if (!first) trace_put(w, ",", 1u);
        first = false;
        trace_put_string(w, fields[i].key, fields[i].key_length);
        trace_put(w, ":", 1u);
        if (trace_is_number(fields[i].value, fields[i].value_length)) {
            trace_put(w, fields[i].value, fields[i].value_length);
        } else {
            trace_put_string(w, fields[i].value, fields[i].value_length);
        }
    }
    trace_puts(w, "}}");
}

static void trace_convert(const char *text, usize size, TraceWriter *w,
                          BreakTraceCoreAppReport *report)
{
    TraceField fields[BREAK_TRACE_CORE_APP_MAX_FIELDS];
    report->events = 0u;
    report->skipped = 0u;
    report->timestamped = 0u;
    trace_puts(w, "{\"traceEvents\":[\n");
    const char *p = text;
    const char *end = text + size;
    while (p < end) {
        const char *line_end = memchr(p, '\n', (usize)(end - p));
        const char *next = line_end ? line_end + 1 : end;
        if (!line_end) line_end = end;
        if (line_end > p && line_end[-1] == '\r') line_end--;
        const char *q = p;
        while (q < line_end && (*q == ' ' || *q == '\t')) q++;
        if (q < line_end) {
            u32 count = 0u;
            u32 event = 0u;
            u32 ts = 0u;
            if (trace_parse_line(p, line_end, fields, &count, &event, &ts)) {
                if (report->events > 0u) trace_puts(w, ",\n");
                trace_write_event(w, fields, count, event, ts, report->events);
                report->events++;
                if (ts < count) report->timestamped++;
            } else {
                report->skipped++;
            }
        }
        p = next;
    }
    if (report->events > 0u) trace_puts(w, "\n");
    trace_puts(w, "]," BREAK_TRACE_OTHER_DATA "}\n");
    report->bytes = w->pos;
}

BreakTraceConvertStatus break_trace_core_app_to_chrome(const char *text, usize size, char *out,
                                                       usize capacity,
                                                       BreakTraceCoreAppReport *report)
{
    if (!report || (!text && size != 0u) || (!out && capacity != 0u)) {
        return BREAK_TRACE_CONVERT_INVALID;
    }
    if (!text) text = "";
    TraceWriter measure = {NULL, 0u};
    trace_convert(text, size, &measure, report);
    if ((u64)capacity <= report->bytes) return BREAK_TRACE_CONVERT_TOO_SMALL;
    TraceWriter writer = {out, 0u};
    trace_convert(text, size, &writer, report);
    out[report->bytes] = '\0';
    return BREAK_TRACE_CONVERT_OK;
}

static bool trace_parse_u64(const char *s, usize length, u64 *out)
{
    if (!trace_is_number(s, length)) return false;
    u64 value = 0u;
    for (usize i = 0u; i < length; ++i) value = value * 10u + (u64)(s[i] - '0');
    *out = value;
    return true;
}

static bool trace_find_field(const TraceField *fields, u32 count, const char *key,
                             const TraceField **out)
{
    for (u32 i = 0u; i < count; ++i) {
        if (trace_same(fields[i].key, fields[i].key_length, key, strlen(key))) {
            *out = &fields[i];
            return true;
        }
    }
    return false;
}

static bool trace_parse_offset_fields(const TraceField *fields, u32 count, i64 *offset_us,
                                      u64 *error_us)
{
    const TraceField *offset = NULL;
    const TraceField *error = NULL;
    u64 magnitude = 0u;
    if (!trace_find_field(fields, count, "offset_us", &offset) ||
        !trace_find_field(fields, count, "error_us", &error) ||
        !trace_parse_u64(error->value, error->value_length, error_us)) {
        return false;
    }
    bool negative = offset->value_length > 0u && offset->value[0] == '-';
    usize skip = negative ? 1u : 0u;
    if (!trace_parse_u64(offset->value + skip, offset->value_length - skip, &magnitude) ||
        (negative && magnitude == 0u)) {
        return false;
    }
    *offset_us = negative ? -(i64)magnitude : (i64)magnitude;
    return true;
}

/* a canonical decimal (no sign, no leading zero) of at most 20 digits that
 * fits in u64 */
static bool trace_parse_session(const char *s, usize length, u64 *out)
{
    if (length == 0u || length > 20u || (length > 1u && s[0] == '0')) return false;
    u64 value = 0u;
    for (usize i = 0u; i < length; ++i) {
        if (s[i] < '0' || s[i] > '9') return false;
        u64 digit = (u64)(s[i] - '0');
        if (value > (UINT64_MAX - digit) / 10u) return false;
        value = value * 10u + digit;
    }
    *out = value;
    return true;
}

/* every clock line when `session` is NULL, else those of *session */
static BreakTraceClockOffsetStatus trace_clock_offset(const char *text, usize size,
                                                      const u64 *session, i64 *offset_us,
                                                      u64 *error_us)
{
    if (!offset_us || !error_us || (!text && size != 0u)) return BREAK_TRACE_CLOCK_OFFSET_INVALID;
    TraceField fields[BREAK_TRACE_CORE_APP_MAX_FIELDS];
    const char *p = text ? text : "";
    const char *end = p + size;
    u32 found = 0u;
    i64 offset = 0;
    u64 error = 0u;
    while (p < end) {
        const char *line_end = memchr(p, '\n', (usize)(end - p));
        const char *next = line_end ? line_end + 1 : end;
        if (!line_end) line_end = end;
        if (line_end > p && line_end[-1] == '\r') line_end--;
        u32 count = 0u;
        u32 event = 0u;
        u32 ts = 0u;
        if (trace_parse_line(p, line_end, fields, &count, &event, &ts) &&
            trace_same(fields[event].value, fields[event].value_length,
                       "network_clock_offset", 20u)) {
            if (session) {
                const TraceField *field = NULL;
                u64 id = 0u;
                if (!trace_find_field(fields, count, "session", &field) ||
                    !trace_parse_session(field->value, field->value_length, &id)) {
                    return BREAK_TRACE_CLOCK_OFFSET_MALFORMED;
                }
                if (id != *session) {
                    p = next;
                    continue;
                }
            }
            if (!trace_parse_offset_fields(fields, count, &offset, &error)) {
                return BREAK_TRACE_CLOCK_OFFSET_MALFORMED;
            }
            found++;
        }
        p = next;
    }
    if (found == 0u) return BREAK_TRACE_CLOCK_OFFSET_NOT_FOUND;
    if (found > 1u) return BREAK_TRACE_CLOCK_OFFSET_AMBIGUOUS;
    *offset_us = offset;
    *error_us = error;
    return BREAK_TRACE_CLOCK_OFFSET_OK;
}

BreakTraceClockOffsetStatus break_trace_core_app_clock_offset(const char *text, usize size,
                                                              i64 *offset_us, u64 *error_us)
{
    return trace_clock_offset(text, size, NULL, offset_us, error_us);
}

BreakTraceClockOffsetStatus break_trace_core_app_clock_offset_for_session(const char *text,
                                                                          usize size, u64 session,
                                                                          i64 *offset_us,
                                                                          u64 *error_us)
{
    return trace_clock_offset(text, size, &session, offset_us, error_us);
}

/* ---------------- writer ---------------- */

#define TRACE_STAMP_PREFIX "COREAPPTRACE version=1 "
#define TRACE_STAMP_PREFIX_LENGTH (sizeof(TRACE_STAMP_PREFIX) - 1u)
#define TRACE_STACK_LINE 1024u

static _Atomic(BreakTraceClockFn) g_trace_clock;

void break_trace_core_app_set_clock(BreakTraceClockFn now_us)
{
    atomic_store_explicit(&g_trace_clock, now_us, memory_order_release);
}

static int trace_write_n(FILE *out, const char *text, usize length)
{
    BreakTraceClockFn clock = atomic_load_explicit(&g_trace_clock, memory_order_acquire);
    if (length > (usize)INT32_MAX - 64u) return -1;
    if (!clock || length < TRACE_STAMP_PREFIX_LENGTH ||
        memcmp(text, TRACE_STAMP_PREFIX, TRACE_STAMP_PREFIX_LENGTH) != 0) {
        return fwrite(text, 1u, length, out) == length ? (int)length : -1;
    }
    char stamp[32];
    int stamp_length = snprintf(stamp, sizeof stamp, "ts_us=%llu ", (unsigned long long)clock());
    if (stamp_length <= 0 || (usize)stamp_length >= sizeof stamp) return -1;
    usize total = length + (usize)stamp_length;
    char stack[TRACE_STACK_LINE];
    char *line = total <= sizeof stack ? stack : malloc(total);
    if (!line) return -1;
    memcpy(line, text, TRACE_STAMP_PREFIX_LENGTH);
    memcpy(line + TRACE_STAMP_PREFIX_LENGTH, stamp, (usize)stamp_length);
    memcpy(line + TRACE_STAMP_PREFIX_LENGTH + (usize)stamp_length,
           text + TRACE_STAMP_PREFIX_LENGTH, length - TRACE_STAMP_PREFIX_LENGTH);
    int result = fwrite(line, 1u, total, out) == total ? (int)total : -1;
    if (line != stack) free(line);
    return result;
}

int break_trace_core_app_write(FILE *out, const char *text)
{
    if (!out || !text) return -1;
    return trace_write_n(out, text, strlen(text));
}

int break_trace_core_app_vfprintf(FILE *out, const char *format, va_list args)
{
    if (!out || !format) return -1;
    /* without a clock this is exactly vfprintf (same bytes, same libc call) */
    if (!atomic_load_explicit(&g_trace_clock, memory_order_acquire)) {
        int direct = vfprintf(out, format, args);
        return direct < 0 ? -1 : direct;
    }
    char stack[TRACE_STACK_LINE];
    va_list again;
    va_copy(again, args);
    int length = vsnprintf(stack, sizeof stack, format, args);
    if (length < 0) {
        va_end(again);
        return -1;
    }
    if ((usize)length < sizeof stack) {
        va_end(again);
        return trace_write_n(out, stack, (usize)length);
    }
    char *heap = malloc((usize)length + 1u);
    if (!heap) {
        va_end(again);
        return -1;
    }
    int second = vsnprintf(heap, (usize)length + 1u, format, again);
    va_end(again);
    int result = second == length ? trace_write_n(out, heap, (usize)length) : -1;
    free(heap);
    return result;
}

int break_trace_core_app_fprintf(FILE *out, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    int result = break_trace_core_app_vfprintf(out, format, args);
    va_end(args);
    return result;
}
