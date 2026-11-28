#include "network/break_keyring.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct BreakKeyringSlot {
    u8 used;
    u8 key_id[8];
    u8 psk[32];
} BreakKeyringSlot;

typedef struct BreakKeyringEntry {
    u8 key_id[8];
    u8 psk[32];
} BreakKeyringEntry;

/* Used slots are kept contiguous in insertion order: slots[0..count). */
struct BreakKeyring {
    BreakKeyringSlot *slots;
    u32 capacity;
    u32 count;
};

static void keyring_wipe(void *p, usize n)
{
    volatile u8 *v = (volatile u8 *)p;
    while (n-- != 0u) {
        *v++ = 0u;
    }
}

static bool keyring_equal(const u8 *left, const u8 *right, usize n)
{
    u8 difference = 0u;
    usize i;
    for (i = 0u; i < n; i++) difference |= (u8)(left[i] ^ right[i]);
    return difference == 0u;
}

/* Index of key_id among the used slots, or ring->count when absent. For
 * management calls only; authentication lookups use break_keyring_resolve. */
static u32 keyring_find(const BreakKeyring *ring, const u8 key_id[8])
{
    u32 i;
    for (i = 0u; i < ring->count; i++) {
        if (memcmp(ring->slots[i].key_id, key_id, 8u) == 0) return i;
    }
    return ring->count;
}

static void keyring_remove_at(BreakKeyring *ring, u32 index)
{
    u32 last = ring->count - 1u;
    if (index < last) {
        memmove(&ring->slots[index], &ring->slots[index + 1u],
                (usize)(last - index) * sizeof(*ring->slots));
    }
    keyring_wipe(&ring->slots[last], sizeof(*ring->slots));
    ring->count = last;
}

BreakKeyring *break_keyring_create(u32 capacity)
{
    BreakKeyring *ring;
    if (capacity == 0u || capacity > BREAK_KEYRING_MAX_KEYS) return NULL;
    ring = (BreakKeyring *)calloc(1u, sizeof(*ring));
    if (ring == NULL) return NULL;
    ring->slots = (BreakKeyringSlot *)calloc(capacity, sizeof(*ring->slots));
    if (ring->slots == NULL) {
        free(ring);
        return NULL;
    }
    ring->capacity = capacity;
    return ring;
}

void break_keyring_destroy(BreakKeyring *ring)
{
    if (ring == NULL) return;
    keyring_wipe(ring->slots, (usize)ring->capacity * sizeof(*ring->slots));
    free(ring->slots);
    free(ring);
}

bool break_keyring_add(BreakKeyring *ring, const u8 key_id[8], const u8 psk[32])
{
    BreakKeyringSlot *slot;
    if (ring == NULL || key_id == NULL || psk == NULL) return false;
    if (ring->count >= ring->capacity) return false;
    if (keyring_find(ring, key_id) != ring->count) return false;
    slot = &ring->slots[ring->count];
    slot->used = 1u;
    memcpy(slot->key_id, key_id, 8u);
    memcpy(slot->psk, psk, 32u);
    ring->count++;
    return true;
}

bool break_keyring_remove(BreakKeyring *ring, const u8 key_id[8])
{
    u32 index;
    if (ring == NULL || key_id == NULL) return false;
    index = keyring_find(ring, key_id);
    if (index == ring->count) return false;
    keyring_remove_at(ring, index);
    return true;
}

u32 break_keyring_count(const BreakKeyring *ring)
{
    return ring != NULL ? ring->count : 0u;
}

bool break_keyring_resolve(void *ring, const u8 key_id[8], u8 out_psk[32])
{
    const BreakKeyring *r = (const BreakKeyring *)ring;
    u32 found = 0u;
    u32 selected = 0u;
    u32 i;
    if (r == NULL || key_id == NULL || out_psk == NULL) return false;
    for (i = 0u; i < r->capacity; i++) {
        const BreakKeyringSlot *slot = &r->slots[i];
        u32 diff = 0u;
        u32 match;
        u32 j;
        for (j = 0u; j < 8u; j++) diff |= (u32)(slot->key_id[j] ^ key_id[j]);
        /* diff is 0..255: (diff - 1) >> 8 is 1 exactly when diff == 0 */
        match = ((diff - 1u) >> 8) & (u32)slot->used & 1u;
        selected |= i & (0u - match);
        found |= match;
    }
    if (found == 0u) return false;
    memcpy(out_psk, r->slots[selected].psk, 32u);
    return true;
}

static int keyring_hex_nibble(char c)
{
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    return -1;
}

/* Decodes exactly 2 * out_len hex characters. */
static bool keyring_hex_decode(const char *hex, u8 *out, usize out_len)
{
    usize i;
    for (i = 0u; i < out_len; i++) {
        int hi = keyring_hex_nibble(hex[2u * i]);
        int lo = keyring_hex_nibble(hex[2u * i + 1u]);
        if (hi < 0 || lo < 0) return false;
        out[i] = (u8)((hi << 4) | lo);
    }
    return true;
}

/* Parses every line of text into entries (room for capacity); *out_count is
 * the number of keys parsed. Nothing is applied here. */
static BreakKeyringLoadResult keyring_parse(const char *text, usize len,
                                            BreakKeyringEntry *entries, u32 capacity,
                                            u32 *out_count)
{
    BreakKeyringLoadResult result = BREAK_KEYRING_LOAD_OK;
    BreakKeyringEntry entry;
    u32 n = 0u;
    usize pos = 0u;
    while (pos < len) {
        usize end = pos;
        usize line_len;
        const char *line = text + pos;
        u32 k;
        while (end < len && text[end] != '\n') end++;
        line_len = end - pos;
        pos = end + 1u;
        if (line_len > 0u && line[line_len - 1u] == '\r') line_len--;
        if (line_len == 0u || line[0] == '#') continue;
        if (line_len != 16u + 1u + 64u || line[16] != ' ' ||
            !keyring_hex_decode(line, entry.key_id, 8u) ||
            !keyring_hex_decode(line + 17, entry.psk, 32u)) {
            result = BREAK_KEYRING_LOAD_MALFORMED;
            break;
        }
        for (k = 0u; k < n; k++) {
            if (memcmp(entries[k].key_id, entry.key_id, 8u) == 0) break;
        }
        if (k < n) {
            result = BREAK_KEYRING_LOAD_MALFORMED;
            break;
        }
        if (n == capacity) {
            result = BREAK_KEYRING_LOAD_TOO_LARGE;
            break;
        }
        entries[n++] = entry;
    }
    keyring_wipe(&entry, sizeof(entry));
    if (result == BREAK_KEYRING_LOAD_OK && n == 0u) result = BREAK_KEYRING_LOAD_EMPTY;
    *out_count = n;
    return result;
}

static bool keyring_entries_hold(const BreakKeyringEntry *entries, u32 n,
                                 const BreakKeyringSlot *slot)
{
    u32 k;
    for (k = 0u; k < n; k++) {
        if (memcmp(entries[k].key_id, slot->key_id, 8u) == 0) {
            return keyring_equal(entries[k].psk, slot->psk, 32u);
        }
    }
    return false;
}

/* Makes the ring equal to entries (validated, at most capacity, no
 * duplicates), so it cannot fail. */
static void keyring_apply(BreakKeyring *ring, const BreakKeyringEntry *entries, u32 n,
                          BreakKeyringRevokedFn revoked, void *user)
{
    u8 key_id[8];
    u32 i = 0u;
    while (i < ring->count) {
        if (keyring_entries_hold(entries, n, &ring->slots[i])) {
            i++;
            continue;
        }
        memcpy(key_id, ring->slots[i].key_id, 8u);
        keyring_remove_at(ring, i);
        if (revoked != NULL) revoked(user, key_id);
        keyring_wipe(key_id, sizeof(key_id));
    }
    for (i = 0u; i < n; i++) {
        if (keyring_find(ring, entries[i].key_id) == ring->count) {
            (void)break_keyring_add(ring, entries[i].key_id, entries[i].psk);
        }
    }
}

BreakKeyringLoadResult break_keyring_load_text(BreakKeyring *ring, const char *text,
                                               usize len, BreakKeyringRevokedFn revoked,
                                               void *user)
{
    BreakKeyringEntry *entries;
    BreakKeyringLoadResult result;
    u32 n = 0u;
    if (ring == NULL || text == NULL) return BREAK_KEYRING_LOAD_UNREADABLE;
    if (len > BREAK_KEYRING_MAX_FILE_BYTES) return BREAK_KEYRING_LOAD_TOO_LARGE;
    entries = (BreakKeyringEntry *)calloc(ring->capacity, sizeof(*entries));
    if (entries == NULL) return BREAK_KEYRING_LOAD_UNREADABLE;
    result = keyring_parse(text, len, entries, ring->capacity, &n);
    if (result == BREAK_KEYRING_LOAD_OK) keyring_apply(ring, entries, n, revoked, user);
    keyring_wipe(entries, (usize)ring->capacity * sizeof(*entries));
    free(entries);
    return result;
}

BreakKeyringLoadResult break_keyring_load_file(BreakKeyring *ring, const char *path,
                                               BreakKeyringRevokedFn revoked, void *user)
{
    BreakKeyringLoadResult result;
    char *buf;
    usize n;
    bool read_failed;
    FILE *f;
    if (ring == NULL || path == NULL) return BREAK_KEYRING_LOAD_UNREADABLE;
    f = fopen(path, "rb");
    if (f == NULL) return BREAK_KEYRING_LOAD_UNREADABLE;
    /* unbuffered: no stdio heap buffer is left holding the key bytes */
    if (setvbuf(f, NULL, _IONBF, 0) != 0) {
        fclose(f);
        return BREAK_KEYRING_LOAD_UNREADABLE;
    }
    buf = (char *)malloc(BREAK_KEYRING_MAX_FILE_BYTES + 1u);
    if (buf == NULL) {
        fclose(f);
        return BREAK_KEYRING_LOAD_UNREADABLE;
    }
    n = fread(buf, 1u, BREAK_KEYRING_MAX_FILE_BYTES + 1u, f);
    read_failed = ferror(f) != 0;
    fclose(f);
    if (read_failed) {
        result = BREAK_KEYRING_LOAD_UNREADABLE;
    } else if (n > BREAK_KEYRING_MAX_FILE_BYTES) {
        result = BREAK_KEYRING_LOAD_TOO_LARGE;
    } else {
        result = break_keyring_load_text(ring, buf, n, revoked, user);
    }
    keyring_wipe(buf, n);
    free(buf);
    return result;
}

bool break_keyring_key_at(const BreakKeyring *ring, u32 index, u8 key_id[8], u8 psk[32])
{
    if (ring == NULL || key_id == NULL || psk == NULL || index >= ring->count) {
        return false;
    }
    memcpy(key_id, ring->slots[index].key_id, 8u);
    memcpy(psk, ring->slots[index].psk, 32u);
    return true;
}
