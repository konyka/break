#include <core/trace_merge.h>

#include <core/trace_schema.h>

#include <stdint.h>
#include <string.h>

#define MERGE_HEADER "{\"traceEvents\":["
#define MERGE_TRAILER "]," BREAK_TRACE_OTHER_DATA "}"
#define MERGE_KEY_ARGS ",\"args\":"
#define MERGE_KEY_PID ",\"pid\":"
#define MERGE_KEY_TS ",\"ts\":"

typedef struct MergeWriter {
    char *out;
    u64 pos;
    bool first;
} MergeWriter;

typedef struct MergeSpan {
    const char *start;
    const char *end;
} MergeSpan;

typedef struct MergeEdit {
    const char *digits;
    usize length;
    u64 value;
} MergeEdit;

static void merge_put(MergeWriter *w, const char *bytes, usize length)
{
    if (w->out) memcpy(w->out + w->pos, bytes, length);
    w->pos += length;
}

static void merge_puts(MergeWriter *w, const char *s)
{
    merge_put(w, s, strlen(s));
}

static void merge_put_u64(MergeWriter *w, u64 value)
{
    char digits[20];
    usize n = 0u;
    do {
        digits[n++] = (char)('0' + value % 10u);
        value /= 10u;
    } while (value != 0u);
    while (n > 0u) merge_put(w, &digits[--n], 1u);
}

static void merge_put_string(MergeWriter *w, const char *s)
{
    static const char hex[] = "0123456789abcdef";
    merge_put(w, "\"", 1u);
    for (; *s != '\0'; ++s) {
        u8 byte = (u8)*s;
        if (byte == '"' || byte == '\\') {
            char escaped[2] = {'\\', (char)byte};
            merge_put(w, escaped, 2u);
        } else if (byte < 0x20u) {
            char escaped[6] = {'\\', 'u', '0', '0', hex[byte >> 4], hex[byte & 0xfu]};
            merge_put(w, escaped, 6u);
        } else {
            merge_put(w, s, 1u);
        }
    }
    merge_put(w, "\"", 1u);
}

static void merge_begin_item(MergeWriter *w)
{
    if (!w->first) merge_puts(w, ",\n");
    w->first = false;
}

static const char *merge_find(const char *start, const char *end, const char *key)
{
    usize length = strlen(key);
    for (const char *p = start; (usize)(end - p) >= length; ++p) {
        if (memcmp(p, key, length) == 0) return p;
    }
    return NULL;
}

static bool merge_span_is(MergeSpan span, const char *s)
{
    usize length = strlen(s);
    return (usize)(span.end - span.start) == length && memcmp(span.start, s, length) == 0;
}

/* Reads the line at *p; returns false at the end of the text. */
static bool merge_next_line(const char **p, const char *end, MergeSpan *line)
{
    if (*p >= end) return false;
    const char *line_end = memchr(*p, '\n', (usize)(end - *p));
    const char *next = line_end ? line_end + 1 : end;
    if (!line_end) line_end = end;
    if (line_end > *p && line_end[-1] == '\r') line_end--;
    line->start = *p;
    line->end = line_end;
    *p = next;
    return true;
}

/* Locates the digit run after key in [start, end). */
static bool merge_digits(const char *start, const char *end, const char *key, MergeEdit *edit)
{
    const char *found = merge_find(start, end, key);
    if (!found) return false;
    edit->digits = found + strlen(key);
    edit->length = 0u;
    while (edit->digits + edit->length < end && edit->digits[edit->length] >= '0' &&
           edit->digits[edit->length] <= '9') {
        edit->length++;
    }
    return edit->length > 0u;
}

static bool merge_shift_ts(MergeEdit *edit, u64 offset)
{
    u64 value = 0u;
    for (usize i = 0u; i < edit->length; ++i) {
        u64 digit = (u64)(edit->digits[i] - '0');
        if (value > ((u64)INT64_MAX - digit) / 10u) return false;
        value = value * 10u + digit;
    }
    if (offset > (u64)INT64_MAX - value) return false;
    edit->value = value + offset;
    return true;
}

/* Copies one event object, rewriting pid and ts in the part before args. */
static bool merge_event(MergeWriter *w, MergeSpan object, const BreakTraceMergeInput *input)
{
    const char *head_end = merge_find(object.start, object.end, MERGE_KEY_ARGS);
    if (!head_end) head_end = object.end;
    MergeEdit edits[2];
    u32 edit_count = 0u;
    if (!merge_digits(object.start, head_end, MERGE_KEY_PID, &edits[0])) return false;
    edits[0].value = input->pid;
    edit_count = 1u;
    if (merge_find(object.start, head_end, MERGE_KEY_TS)) {
        if (!merge_digits(object.start, head_end, MERGE_KEY_TS, &edits[1]) ||
            !merge_shift_ts(&edits[1], input->ts_offset_us)) {
            return false;
        }
        edit_count = 2u;
        if (edits[1].digits < edits[0].digits) {
            MergeEdit swap = edits[0];
            edits[0] = edits[1];
            edits[1] = swap;
        }
    }
    merge_begin_item(w);
    const char *p = object.start;
    for (u32 i = 0u; i < edit_count; ++i) {
        merge_put(w, p, (usize)(edits[i].digits - p));
        merge_put_u64(w, edits[i].value);
        p = edits[i].digits + edits[i].length;
    }
    merge_put(w, p, (usize)(object.end - p));
    return true;
}

/* Returns 0 on success or the 1-based line of the first problem. */
static u32 merge_input(MergeWriter *w, const BreakTraceMergeInput *input, u32 *events)
{
    const char *p = input->text;
    const char *end = input->text + input->size;
    MergeSpan line;
    u32 line_number = 1u;
    if (!merge_next_line(&p, end, &line) || !merge_span_is(line, MERGE_HEADER)) return 1u;
    if (input->label) {
        merge_begin_item(w);
        merge_puts(w, "{\"name\":\"process_name\",\"ph\":\"M\",\"pid\":");
        merge_put_u64(w, input->pid);
        merge_puts(w, ",\"args\":{\"name\":");
        merge_put_string(w, input->label);
        merge_puts(w, "}}");
    }
    for (;;) {
        line_number++;
        if (!merge_next_line(&p, end, &line)) return line_number;
        if (merge_span_is(line, MERGE_TRAILER)) break;
        MergeSpan object = line;
        if (object.end > object.start && object.end[-1] == ',') object.end--;
        if (object.end - object.start < 2 || object.start[0] != '{' || object.end[-1] != '}') {
            return line_number;
        }
        if (!merge_event(w, object, input)) return line_number;
        (*events)++;
    }
    return p < end ? line_number + 1u : 0u;
}

static bool merge_inputs_valid(const BreakTraceMergeInput *inputs, u32 count)
{
    if (count > 0u && !inputs) return false;
    for (u32 i = 0u; i < count; ++i) {
        if (!inputs[i].text || inputs[i].pid == 0u) return false;
        for (u32 j = 0u; j < i; ++j) {
            if (inputs[j].pid == inputs[i].pid) return false;
        }
    }
    return true;
}

static BreakTraceMergeStatus merge_all(const BreakTraceMergeInput *inputs, u32 count,
                                       MergeWriter *w, BreakTraceMergeReport *report)
{
    report->events = 0u;
    report->error_input = 0u;
    report->error_line = 0u;
    merge_puts(w, MERGE_HEADER "\n");
    for (u32 i = 0u; i < count; ++i) {
        u32 bad_line = merge_input(w, &inputs[i], &report->events);
        if (bad_line != 0u) {
            report->error_input = i;
            report->error_line = bad_line;
            return BREAK_TRACE_MERGE_BAD_DOCUMENT;
        }
    }
    if (!w->first) merge_puts(w, "\n");
    merge_puts(w, MERGE_TRAILER "\n");
    report->bytes = w->pos;
    return BREAK_TRACE_MERGE_OK;
}

BreakTraceMergeStatus break_trace_merge(const BreakTraceMergeInput *inputs, u32 count,
                                        char *out, usize capacity,
                                        BreakTraceMergeReport *report)
{
    if (!report || (!out && capacity != 0u) || !merge_inputs_valid(inputs, count)) {
        return BREAK_TRACE_MERGE_INVALID;
    }
    MergeWriter measure = {NULL, 0u, true};
    BreakTraceMergeStatus status = merge_all(inputs, count, &measure, report);
    if (status != BREAK_TRACE_MERGE_OK) return status;
    if ((u64)capacity <= report->bytes) return BREAK_TRACE_MERGE_TOO_SMALL;
    MergeWriter writer = {out, 0u, true};
    (void)merge_all(inputs, count, &writer, report);
    out[report->bytes] = '\0';
    return BREAK_TRACE_MERGE_OK;
}
