#include "re_internal.h"
#include <string.h>

/* Explicit-support markers model upstream tms.rs JustificationType::Explicit:
 * a justification item with no producer rule and no premises. It is
 * unconditionally valid — premise-driven cleanup (re_tms_remove_premise) only
 * removes items that name the retracted premise, so a premise-less marker is
 * never invalidated by a cascade, and a fact is auto-retracted only when no
 * support item of any kind remains (upstream: a fact survives while ANY
 * justification is valid). Markers are invisible to
 * re_facts_justification_count and re_facts_provenance_get, which report
 * logical rule provenance only. Direct retraction (re_tms_remove_derived)
 * drops markers together with everything else. */
static int id_equal(re_fact_id_t a, re_fact_id_t b) { return a.slot == b.slot && a.generation == b.generation; }
static int same_text(re_string_t a, const char *b, size_t n) { return a.size == n && (n == 0u || memcmp(a.data, b, n) == 0); }
static int is_explicit_marker(const re_tms_justification_t *item) { return item->producer_rule == NULL; }

static re_status_t ensure_tms(re_facts_t *facts) {
    if (facts->tms != NULL) return RE_STATUS_OK;
    facts->tms = re_alloc(&facts->allocator, sizeof(*facts->tms));
    if (facts->tms == NULL) return RE_STATUS_OUT_OF_MEMORY;
    facts->tms->allocator = facts->allocator; facts->tms->items = NULL;
    facts->tms->count = 0u; facts->tms->capacity = 0u;
    return RE_STATUS_OK;
}

static re_status_t reserve_tms_item(re_tms_t *tms) {
    if (tms->count == tms->capacity) {
        size_t capacity = tms->capacity == 0u ? 8u : tms->capacity * 2u;
        re_tms_justification_t *grown;
        if (capacity < tms->capacity || capacity > SIZE_MAX / sizeof(*tms->items)) return RE_STATUS_LIMIT;
        grown = re_realloc(&tms->allocator, tms->items, capacity * sizeof(*grown));
        if (grown == NULL) return RE_STATUS_OUT_OF_MEMORY;
        tms->items = grown; tms->capacity = capacity;
    }
    return RE_STATUS_OK;
}

/* All support items for a fact, explicit markers included. */
static size_t support_count(const re_facts_t *facts, re_fact_id_t derived) {
    size_t i, count = 0u;
    if (facts->tms == NULL) return 0u;
    for (i = 0u; i < facts->tms->count; ++i)
        if (id_equal(facts->tms->items[i].derived, derived)) ++count;
    return count;
}

void re_tms_destroy(re_tms_t *tms) {
    size_t i;
    if (tms == NULL) return;
    for (i = 0u; i < tms->count; ++i) {
        re_free(&tms->allocator, tms->items[i].producer_rule);
        re_free(&tms->allocator, tms->items[i].premises);
    }
    re_free(&tms->allocator, tms->items);
    re_free(&tms->allocator, tms);
}

void re_tms_remove_derived(re_facts_t *facts, re_fact_id_t derived) {
    size_t i = 0u;
    if (facts == NULL || facts->tms == NULL) return;
    while (i < facts->tms->count) {
        re_tms_justification_t *item = &facts->tms->items[i];
        if (!id_equal(item->derived, derived)) {
            ++i;
            continue;
        }
        re_free(&facts->tms->allocator, item->producer_rule);
        re_free(&facts->tms->allocator, item->premises);
        facts->tms->items[i] = facts->tms->items[--facts->tms->count];
    }
    if (derived.slot < facts->count && facts->entries[derived.slot].generation == derived.generation)
        facts->entries[derived.slot].logical = 0;
}

re_status_t re_tms_clone(const re_tms_t *source, const re_allocator_impl_t *allocator, re_tms_t **out) {
    re_tms_t *copy;
    size_t i;
    if (source == NULL || allocator == NULL || out == NULL) return RE_STATUS_INVALID_ARGUMENT;
    *out = NULL;
    copy = re_alloc(allocator, sizeof(*copy));
    if (copy == NULL) return RE_STATUS_OUT_OF_MEMORY;
    copy->allocator = *allocator; copy->items = NULL; copy->count = 0u; copy->capacity = 0u;
    for (i = 0u; i < source->count; ++i) {
        re_tms_justification_t *item;
        size_t bytes;
        if (copy->count == copy->capacity) {
            size_t capacity = copy->capacity == 0u ? 8u : copy->capacity * 2u;
            if (capacity < copy->capacity || capacity > SIZE_MAX / sizeof(*copy->items)) { re_tms_destroy(copy); return RE_STATUS_LIMIT; }
            re_tms_justification_t *grown = re_realloc(allocator, copy->items, capacity * sizeof(*grown));
            if (grown == NULL) { re_tms_destroy(copy); return RE_STATUS_OUT_OF_MEMORY; }
            copy->items = grown; copy->capacity = capacity;
        }
        item = &copy->items[copy->count]; *item = source->items[i]; item->producer_rule = NULL; item->premises = NULL;
        if (item->producer_rule_size != 0u) {
            item->producer_rule = re_alloc(allocator, item->producer_rule_size + 1u);
            if (item->producer_rule == NULL) { re_tms_destroy(copy); return RE_STATUS_OUT_OF_MEMORY; }
            memcpy(item->producer_rule, source->items[i].producer_rule, item->producer_rule_size + 1u);
        }
        if (item->premise_count > SIZE_MAX / sizeof(*item->premises)) { re_tms_destroy(copy); return RE_STATUS_LIMIT; }
        bytes = item->premise_count * sizeof(*item->premises);
        if (bytes != 0u) {
            item->premises = re_alloc(allocator, bytes);
            if (item->premises == NULL) { re_tms_destroy(copy); return RE_STATUS_OUT_OF_MEMORY; }
            memcpy(item->premises, source->items[i].premises, bytes);
        }
        ++copy->count;
    }
    *out = copy;
    return RE_STATUS_OK;
}

static int justification_equal(const re_tms_justification_t *item, re_string_t rule,
                               const re_fact_id_t *premises, size_t count) {
    size_t i;
    if (!same_text(rule, item->producer_rule, item->producer_rule_size) || count != item->premise_count) return 0;
    for (i = 0u; i < count; ++i) if (!id_equal(premises[i], item->premises[i])) return 0;
    return 1;
}

static int valid_id(const re_facts_t *facts, re_fact_id_t id) {
    return id.slot < facts->count && facts->entries[id.slot].active && facts->entries[id.slot].generation == id.generation;
}

static int depends_on(const re_facts_t *facts, re_fact_id_t current,
                      re_fact_id_t target, size_t depth) {
    size_t i, j;
    if (id_equal(current, target)) return 1;
    if (facts->tms == NULL || depth > facts->tms->count) return 0;
    for (i = 0u; i < facts->tms->count; ++i)
        if (id_equal(facts->tms->items[i].derived, current))
            for (j = 0u; j < facts->tms->items[i].premise_count; ++j)
                if (depends_on(facts, facts->tms->items[i].premises[j], target, depth + 1u)) return 1;
    return 0;
}

/* Records that the host explicitly asserted a fact that also carries logical
 * justifications, so premise retraction cannot cascade to it (upstream keeps
 * both justification lists; the explicit one is unconditionally valid).
 * Idempotent. Callers reach this only after any transaction redirect, on the
 * store that actually owns the entry. */
re_status_t re_tms_explicit_support_ensure(re_facts_t *facts, re_fact_id_t derived) {
    size_t i;
    re_status_t status;
    re_tms_justification_t *item;
    if (facts == NULL || !valid_id(facts, derived)) return RE_STATUS_INVALID_ARGUMENT;
    status = ensure_tms(facts);
    if (status != RE_STATUS_OK) return status;
    for (i = 0u; i < facts->tms->count; ++i)
        if (id_equal(facts->tms->items[i].derived, derived) && is_explicit_marker(&facts->tms->items[i]))
            return RE_STATUS_OK;
    status = reserve_tms_item(facts->tms);
    if (status != RE_STATUS_OK) return status;
    item = &facts->tms->items[facts->tms->count++];
    memset(item, 0, sizeof(*item));
    item->derived = derived;
    return RE_STATUS_OK;
}

re_status_t re_facts_justification_add(re_facts_t *facts, re_fact_id_t derived, re_string_t rule,
                                       const re_fact_id_t *premises, size_t count) {
    re_tms_t *tms;
    re_tms_justification_t *item;
    re_status_t status;
    size_t i;
    if (facts == NULL || rule.data == NULL || rule.size == 0u ||
        (count != 0u && premises == NULL)) return RE_STATUS_INVALID_ARGUMENT;
    if (!valid_id(facts, derived)) return RE_STATUS_NOT_FOUND;
    if (facts->transaction != NULL) return re_facts_justification_add(facts->transaction->staged, derived, rule, premises, count);
    status = ensure_tms(facts);
    if (status != RE_STATUS_OK) return status;
    for (i = 0u; i < count; ++i) {
        if (!valid_id(facts, premises[i])) return RE_STATUS_NOT_FOUND;
        if (id_equal(derived, premises[i])) return RE_STATUS_LIMIT;
        if (depends_on(facts, premises[i], derived, 0u)) return RE_STATUS_LIMIT;
    }
    for (i = 0u; i < facts->tms->count; ++i) if (id_equal(facts->tms->items[i].derived, derived) && justification_equal(&facts->tms->items[i], rule, premises, count)) return RE_STATUS_OK;
    tms = facts->tms;
    status = reserve_tms_item(tms);
    if (status != RE_STATUS_OK) return status;
    item = &tms->items[tms->count]; memset(item, 0, sizeof(*item)); item->derived = derived; item->premise_count = count;
    item->producer_rule = re_alloc(&tms->allocator, rule.size + 1u);
    if (item->producer_rule == NULL) return RE_STATUS_OUT_OF_MEMORY;
    memcpy(item->producer_rule, rule.data, rule.size); item->producer_rule[rule.size] = '\0'; item->producer_rule_size = rule.size;
    if (count != 0u) {
        if (count > SIZE_MAX / sizeof(*item->premises)) {
            re_free(&tms->allocator, item->producer_rule); item->producer_rule = NULL;
            return RE_STATUS_LIMIT;
        }
        item->premises = re_alloc(&tms->allocator, count * sizeof(*item->premises));
        if (item->premises == NULL) { re_free(&tms->allocator, item->producer_rule); item->producer_rule = NULL; return RE_STATUS_OUT_OF_MEMORY; }
        memcpy(item->premises, premises, count * sizeof(*item->premises));
    }
    ++tms->count; facts->entries[derived.slot].logical = 1; return RE_STATUS_OK;
}

size_t re_facts_justification_count(const re_facts_t *facts, re_fact_id_t id) {
    size_t i, count = 0u;
    if (facts != NULL && facts->transaction != NULL)
        return re_facts_justification_count(facts->transaction->staged, id);
    if (facts == NULL || facts->tms == NULL || !valid_id(facts, id)) return 0u;
    for (i = 0u; i < facts->tms->count; ++i)
        if (id_equal(facts->tms->items[i].derived, id) && !is_explicit_marker(&facts->tms->items[i])) ++count;
    return count;
}

re_status_t re_facts_justification_remove(re_facts_t *facts, re_fact_id_t derived, re_string_t rule,
                                          const re_fact_id_t *premises, size_t count) {
    size_t i;
    /* Mirrors the add-side validation: an empty rule would otherwise match an
     * explicit-support marker (same_text equates size 0 with the marker's
     * empty rule) and let a public call delete unconditionally-valid support. */
    if (facts == NULL || rule.data == NULL || rule.size == 0u ||
        (count != 0u && premises == NULL)) return RE_STATUS_INVALID_ARGUMENT;
    if (facts->transaction != NULL) return re_facts_justification_remove(facts->transaction->staged, derived, rule, premises, count);
    if (facts->tms == NULL) return RE_STATUS_INVALID_ARGUMENT;
    for (i = 0u; i < facts->tms->count; ++i) if (id_equal(facts->tms->items[i].derived, derived) && justification_equal(&facts->tms->items[i], rule, premises, count)) {
        re_tms_justification_t item = facts->tms->items[i]; facts->tms->items[i] = facts->tms->items[--facts->tms->count];
        re_free(&facts->tms->allocator, item.producer_rule); re_free(&facts->tms->allocator, item.premises);
        if (support_count(facts, derived) == 0u && valid_id(facts, derived)) return re_facts_retract(facts, derived);
        return RE_STATUS_OK;
    }
    return RE_STATUS_NOT_FOUND;
}

void re_tms_remove_premise(re_facts_t *facts, re_fact_id_t premise) {
    size_t i = 0u, j;
    if (facts == NULL || facts->tms == NULL) return;
    while (i < facts->tms->count) {
        re_tms_justification_t *item = &facts->tms->items[i];
        int supported = 0;
        for (j = 0u; j < item->premise_count; ++j) if (id_equal(item->premises[j], premise)) supported = 1;
        if (!supported) { ++i; continue; }
        {
            re_fact_id_t derived = item->derived;
            re_tms_justification_t removed = *item;
            facts->tms->items[i] = facts->tms->items[--facts->tms->count];
            re_free(&facts->tms->allocator, removed.producer_rule);
            re_free(&facts->tms->allocator, removed.premises);
            if (support_count(facts, derived) == 0u && valid_id(facts, derived))
                re_facts_retract(facts, derived);
        }
    }
}
