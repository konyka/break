#include <core/trace_core_app.h>

#include <core/trace_schema.h>

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
 * line is malformed; *event receives the index of the event= field. */
static bool trace_parse_line(const char *p, const char *end, TraceField *fields, u32 *count,
                             u32 *event)
{
    *count = 0u;
    *event = BREAK_TRACE_CORE_APP_MAX_FIELDS;
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
                              u32 ordinal)
{
    trace_puts(w, "{\"name\":");
    trace_put_string(w, fields[event].value, fields[event].value_length);
    trace_puts(w, ",\"cat\":\"" BREAK_TRACE_CAT_CORE_APP "\",\"ph\":\"i\",\"s\":\"g\",\"ts\":");
    trace_put_u32(w, ordinal);
    trace_puts(w, ",\"pid\":1,\"tid\":1,\"args\":{");
    bool first = true;
    for (u32 i = 1u; i < count; ++i) {
        if (i == event) continue;
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
            if (trace_parse_line(p, line_end, fields, &count, &event)) {
                if (report->events > 0u) trace_puts(w, ",\n");
                trace_write_event(w, fields, count, event, report->events);
                report->events++;
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
