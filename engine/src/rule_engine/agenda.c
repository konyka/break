#include "re_internal.h"
#include <string.h>

static void sort_premises(re_fact_id_t *premises, size_t count) {
    size_t i;
    for (i = 1u; i < count; ++i) {
        re_fact_id_t current = premises[i];
        size_t j = i;
        while (j != 0u &&
               (premises[j - 1u].slot > current.slot ||
                (premises[j - 1u].slot == current.slot &&
                 premises[j - 1u].generation > current.generation))) {
            premises[j] = premises[j - 1u];
            --j;
        }
        premises[j] = current;
    }
}

/* Entries store premises sorted by (slot, generation), so a key comparison
 * is a plain memcmp once the probe premises are sorted the same way. */
static int entry_matches(const re_agenda_entry_internal_t *entry, size_t rule_index,
                         const re_fact_id_t *sorted, size_t premise_count) {
    if (entry->rule_index != rule_index || entry->premise_count != premise_count) return 0;
    return premise_count == 0u ||
           memcmp(entry->premises, sorted, premise_count * sizeof(*sorted)) == 0;
}

static re_status_t grow_entries(const re_allocator_impl_t *allocator,
                                re_agenda_entry_internal_t **entries, size_t *capacity) {
    size_t grown_cap;
    re_agenda_entry_internal_t *grown;
    if (*capacity != 0u && *capacity > (size_t)-1 / 2u) return RE_STATUS_LIMIT;
    grown_cap = *capacity == 0u ? 8u : *capacity * 2u;
    if (grown_cap > (size_t)-1 / sizeof(*grown)) return RE_STATUS_LIMIT;
    grown = re_realloc(allocator, *entries, grown_cap * sizeof(*grown));
    if (grown == NULL) return RE_STATUS_OUT_OF_MEMORY;
    *entries = grown;
    *capacity = grown_cap;
    return RE_STATUS_OK;
}

re_status_t re_agenda_create_internal(re_allocator_t *alloc, re_agenda_t **out) {
    re_allocator_impl_t selected;
    re_agenda_t *agenda;
    if (out == NULL) return RE_STATUS_INVALID_ARGUMENT;
    *out = NULL;
    re_allocator_init(&selected, alloc);
    if (selected.api.alloc == NULL || selected.api.realloc == NULL ||
        selected.api.free == NULL) return RE_STATUS_INVALID_ARGUMENT;
    agenda = re_alloc(&selected, sizeof(*agenda));
    if (agenda == NULL) return RE_STATUS_OUT_OF_MEMORY;
    memset(agenda, 0, sizeof(*agenda));
    agenda->allocator = selected;
    *out = agenda;
    return RE_STATUS_OK;
}

void re_agenda_destroy_internal(re_agenda_t *agenda) {
    if (agenda == NULL) return;
    re_free(&agenda->allocator, agenda->pending);
    re_free(&agenda->allocator, agenda->fired);
    re_free(&agenda->allocator, agenda);
}

void re_agenda_clear_pending(re_agenda_t *agenda) {
    if (agenda == NULL) return;
    agenda->pending_count = 0u;
}

void re_agenda_reset(re_agenda_t *agenda) {
    if (agenda == NULL) return;
    agenda->pending_count = 0u;
    agenda->fired_count = 0u;
}

int re_agenda_refracted(const re_agenda_t *agenda, size_t rule_index,
                        const re_fact_id_t *premises, size_t premise_count) {
    re_fact_id_t sorted[RE_AGENDA_MAX_PREMISES];
    size_t i;
    if (agenda == NULL || premise_count > RE_AGENDA_MAX_PREMISES) return 0;
    if (premise_count != 0u && premises == NULL) return 0;
    if (premise_count != 0u) memcpy(sorted, premises, premise_count * sizeof(*sorted));
    sort_premises(sorted, premise_count);
    for (i = 0u; i < agenda->fired_count; ++i)
        if (entry_matches(&agenda->fired[i], rule_index, sorted, premise_count)) return 1;
    return 0;
}

re_status_t re_agenda_push(re_agenda_t *agenda, size_t rule_index, int32_t salience,
                           const re_fact_id_t *premises, size_t premise_count) {
    return re_agenda_push_full(agenda, rule_index, salience, premises, premise_count,
                               premises);
}

re_status_t re_agenda_push_full(re_agenda_t *agenda, size_t rule_index, int32_t salience,
                                const re_fact_id_t *premises, size_t premise_count,
                                const re_fact_id_t *true_premises) {
    re_fact_id_t sorted[RE_AGENDA_MAX_PREMISES];
    re_agenda_entry_internal_t *entry;
    size_t i;
    if (agenda == NULL || premise_count > RE_AGENDA_MAX_PREMISES)
        return RE_STATUS_INVALID_ARGUMENT;
    if (premise_count != 0u && premises == NULL) return RE_STATUS_INVALID_ARGUMENT;
    if (premise_count != 0u) memcpy(sorted, premises, premise_count * sizeof(*sorted));
    sort_premises(sorted, premise_count);
    for (i = 0u; i < agenda->pending_count; ++i)
        if (entry_matches(&agenda->pending[i], rule_index, sorted, premise_count))
            return RE_STATUS_OK;
    for (i = 0u; i < agenda->fired_count; ++i)
        if (entry_matches(&agenda->fired[i], rule_index, sorted, premise_count))
            return RE_STATUS_OK;
    if (agenda->pending_count == agenda->pending_cap) {
        re_status_t status = grow_entries(&agenda->allocator, &agenda->pending,
                                          &agenda->pending_cap);
        if (status != RE_STATUS_OK) return status;
    }
    entry = &agenda->pending[agenda->pending_count++];
    entry->rule_index = rule_index;
    if (premise_count != 0u) {
        memcpy(entry->premises, sorted, premise_count * sizeof(*entry->premises));
        /* Provenance for re_agenda_peek: the unsorted, real-generation ids;
         * standalone callers that only know the key premises keep those. */
        memcpy(entry->true_premises, true_premises != NULL ? true_premises : premises,
               premise_count * sizeof(*entry->true_premises));
    }
    entry->premise_count = premise_count;
    entry->salience = salience;
    entry->sequence = agenda->next_sequence++;
    return RE_STATUS_OK;
}

re_status_t re_agenda_mark_fired(re_agenda_t *agenda, const re_agenda_entry_internal_t *entry) {
    if (agenda == NULL || entry == NULL) return RE_STATUS_INVALID_ARGUMENT;
    if (agenda->fired_count == agenda->fired_cap) {
        re_status_t status = grow_entries(&agenda->allocator, &agenda->fired,
                                          &agenda->fired_cap);
        if (status != RE_STATUS_OK) return status;
    }
    agenda->fired[agenda->fired_count++] = *entry;
    return RE_STATUS_OK;
}

int re_agenda_pop_highest(re_agenda_t *agenda, re_agenda_entry_internal_t *out) {
    size_t i;
    size_t best;
    if (agenda == NULL || out == NULL || agenda->pending_count == 0u) return 0;
    best = 0u;
    for (i = 1u; i < agenda->pending_count; ++i) {
        const re_agenda_entry_internal_t *candidate = &agenda->pending[i];
        const re_agenda_entry_internal_t *current = &agenda->pending[best];
        if (candidate->salience > current->salience ||
            (candidate->salience == current->salience &&
             candidate->sequence < current->sequence)) best = i;
    }
    *out = agenda->pending[best];
    agenda->pending[best] = agenda->pending[agenda->pending_count - 1u];
    --agenda->pending_count;
    return 1;
}
