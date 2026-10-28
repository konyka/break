#include "test_framework.h"
#include <runtime/runtime_coordinator.h>
#include <string.h>

/* Focused contract tests for the Runtime Core lifecycle coordinator.
 *
 * Event log convention: each fake subsystem callback records
 * `subsystem_id * 10 + phase_code` and the coordinator state observed from
 * inside the callback (state-only queries are the one re-entrant call the
 * contract allows).
 */
enum {
    EV_ADMISSION = 1,
    EV_PRODUCERS = 2,
    EV_CLOSE = 3,
    EV_DRAIN = 4,
    EV_JOIN = 5,
    EV_DESTROY = 6
};

typedef struct FakeSub {
    int id;
    int fail_event;
    BreakRuntimeError fail_error;
    int timeout_event;
    bool timeout_armed;
    int destroy_calls;
} FakeSub;

static int g_events[512];
static BreakRuntimeState g_states[512];
static int g_event_count;
static const BreakRuntimeCoordinator *g_observed;

static void log_reset(const BreakRuntimeCoordinator *rt)
{
    g_event_count = 0;
    g_observed = rt;
}

static BreakRuntimeError fake_event(FakeSub *sub, int event)
{
    g_events[g_event_count] = sub->id * 10 + event;
    g_states[g_event_count] = break_runtime_coordinator_state(g_observed);
    g_event_count++;
    if (sub->fail_event == event) {
        return sub->fail_error;
    }
    if (sub->timeout_event == event && sub->timeout_armed) {
        return BREAK_RUNTIME_TIMEOUT;
    }
    if (event == EV_DESTROY) {
        sub->destroy_calls++;
    }
    return BREAK_RUNTIME_OK;
}

static BreakRuntimeError fake_stop_admission(void *user) { return fake_event(user, EV_ADMISSION); }
static BreakRuntimeError fake_stop_producers(void *user) { return fake_event(user, EV_PRODUCERS); }
static BreakRuntimeError fake_close_queues(void *user) { return fake_event(user, EV_CLOSE); }
static BreakRuntimeError fake_drain(void *user) { return fake_event(user, EV_DRAIN); }
static BreakRuntimeError fake_join(void *user) { return fake_event(user, EV_JOIN); }
static BreakRuntimeError fake_destroy(void *user) { return fake_event(user, EV_DESTROY); }

static BreakRuntimeSubsystem fake_desc(FakeSub *sub)
{
    BreakRuntimeSubsystem desc;
    memset(&desc, 0, sizeof(desc));
    desc.name = "fake";
    desc.user_data = sub;
    desc.stop_admission = fake_stop_admission;
    desc.stop_producers = fake_stop_producers;
    desc.close_queues = fake_close_queues;
    desc.drain = fake_drain;
    desc.join = fake_join;
    desc.destroy = fake_destroy;
    return desc;
}

static bool events_match(const int *expected, int count)
{
    int i;
    if (g_event_count != count) {
        return false;
    }
    for (i = 0; i < count; i++) {
        if (g_events[i] != expected[i]) {
            return false;
        }
    }
    return true;
}

static int event_occurrences(int code)
{
    int i;
    int n = 0;
    for (i = 0; i < g_event_count; i++) {
        if (g_events[i] == code) {
            n++;
        }
    }
    return n;
}

TEST(create_destroy_and_capacity_validation)
{
    BreakRuntimeCoordinator *rt = NULL;
    BreakRuntimeCoordinatorConfig cfg;

    ASSERT_EQ(break_runtime_coordinator_create(NULL, NULL), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_coordinator_create(NULL, &rt), BREAK_RUNTIME_OK);
    ASSERT_NOT_NULL(rt);
    ASSERT_EQ(break_runtime_coordinator_state(rt), BREAK_RUNTIME_CREATED);
    ASSERT_EQ(break_runtime_coordinator_last_error(rt), BREAK_RUNTIME_OK);
    break_runtime_coordinator_destroy(rt);
    break_runtime_coordinator_destroy(NULL);

    memset(&cfg, 0, sizeof(cfg));
    cfg.max_subsystems = BREAK_RUNTIME_MAX_SUBSYSTEMS + 1u;
    rt = NULL;
    ASSERT_EQ(break_runtime_coordinator_create(&cfg, &rt), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(rt, NULL);

    ASSERT_STR_EQ(break_runtime_error_name(BREAK_RUNTIME_OK), "OK");
    ASSERT_STR_EQ(break_runtime_error_name(BREAK_RUNTIME_TIMEOUT), "TIMEOUT");
    ASSERT_STR_EQ(break_runtime_error_name(BREAK_RUNTIME_REJECTED), "REJECTED");
    ASSERT_STR_EQ(break_runtime_state_name(BREAK_RUNTIME_CREATED), "CREATED");
    ASSERT_STR_EQ(break_runtime_state_name(BREAK_RUNTIME_QUIESCING), "QUIESCING");
    ASSERT_STR_EQ(break_runtime_state_name(BREAK_RUNTIME_STOPPING), "STOPPING");
    ASSERT_STR_EQ(break_runtime_state_name(BREAK_RUNTIME_STATE_FAILED), "FAILED");
}

TEST(legal_lifecycle_transitions)
{
    BreakRuntimeCoordinator *rt = NULL;

    ASSERT_EQ(break_runtime_coordinator_create(NULL, &rt), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_coordinator_state(rt), BREAK_RUNTIME_CREATED);
    ASSERT_EQ(break_runtime_coordinator_admit(rt), BREAK_RUNTIME_REJECTED);

    ASSERT_EQ(break_runtime_coordinator_start(rt), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_coordinator_state(rt), BREAK_RUNTIME_RUNNING);
    ASSERT_EQ(break_runtime_coordinator_admit(rt), BREAK_RUNTIME_OK);

    ASSERT_EQ(break_runtime_coordinator_stop(rt), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_coordinator_state(rt), BREAK_RUNTIME_STOPPED);
    ASSERT_EQ(break_runtime_coordinator_admit(rt), BREAK_RUNTIME_CLOSED);

    /* Stop from STOPPED is an idempotent no-op. */
    ASSERT_EQ(break_runtime_coordinator_stop(rt), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_coordinator_state(rt), BREAK_RUNTIME_STOPPED);
    ASSERT_EQ(break_runtime_coordinator_last_error(rt), BREAK_RUNTIME_OK);

    break_runtime_coordinator_destroy(rt);
}

TEST(invalid_transitions_rejected)
{
    BreakRuntimeCoordinator *rt = NULL;
    FakeSub sub;
    BreakRuntimeSubsystem desc;

    memset(&sub, 0, sizeof(sub));
    sub.id = 1;
    desc = fake_desc(&sub);

    ASSERT_EQ(break_runtime_coordinator_create(NULL, &rt), BREAK_RUNTIME_OK);
    /* CREATED -> STOPPING is not a legal transition. */
    ASSERT_EQ(break_runtime_coordinator_stop(rt), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_coordinator_state(rt), BREAK_RUNTIME_CREATED);

    ASSERT_EQ(break_runtime_coordinator_start(rt), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_coordinator_start(rt), BREAK_RUNTIME_REJECTED);
    ASSERT_EQ(break_runtime_coordinator_register_subsystem(rt, &desc),
              BREAK_RUNTIME_REJECTED);
    ASSERT_EQ(break_runtime_coordinator_fail(rt, BREAK_RUNTIME_OK),
              BREAK_RUNTIME_INVALID);

    ASSERT_EQ(break_runtime_coordinator_stop(rt), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_coordinator_start(rt), BREAK_RUNTIME_REJECTED);
    ASSERT_EQ(break_runtime_coordinator_fail(rt, BREAK_RUNTIME_OOM),
              BREAK_RUNTIME_REJECTED);

    ASSERT_EQ(break_runtime_coordinator_start(NULL), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_coordinator_stop(NULL), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_coordinator_admit(NULL), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_coordinator_register_subsystem(NULL, &desc),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_coordinator_register_subsystem(rt, NULL),
              BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_coordinator_fail(NULL, BREAK_RUNTIME_OOM),
              BREAK_RUNTIME_INVALID);

    break_runtime_coordinator_destroy(rt);
}

TEST(subsystem_callbacks_run_in_documented_order)
{
    BreakRuntimeCoordinator *rt = NULL;
    FakeSub subs[3];
    int i;
    int j;
    static const int expected[] = {
        11, 21, 31, /* stop_admission, registration order */
        12, 22, 32, /* stop_producers */
        13, 23, 33, /* close_queues */
        14, 24, 34, /* drain */
        15, 25, 35, /* join */
        16, 26, 36  /* destroy */
    };

    memset(subs, 0, sizeof(subs));
    ASSERT_EQ(break_runtime_coordinator_create(NULL, &rt), BREAK_RUNTIME_OK);
    for (i = 0; i < 3; i++) {
        BreakRuntimeSubsystem desc;
        subs[i].id = i + 1;
        desc = fake_desc(&subs[i]);
        ASSERT_EQ(break_runtime_coordinator_register_subsystem(rt, &desc),
                  BREAK_RUNTIME_OK);
    }

    ASSERT_EQ(break_runtime_coordinator_start(rt), BREAK_RUNTIME_OK);
    log_reset(rt);
    ASSERT_EQ(break_runtime_coordinator_stop(rt), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_coordinator_state(rt), BREAK_RUNTIME_STOPPED);

    ASSERT_TRUE(events_match(expected, 18));
    for (j = 0; j < 18; j++) {
        int phase = g_events[j] % 10;
        if (phase == EV_ADMISSION || phase == EV_PRODUCERS) {
            ASSERT_EQ(g_states[j], BREAK_RUNTIME_QUIESCING);
        } else if (phase == EV_CLOSE || phase == EV_DRAIN) {
            ASSERT_EQ(g_states[j], BREAK_RUNTIME_DRAINING);
        } else {
            ASSERT_EQ(g_states[j], BREAK_RUNTIME_STOPPING);
        }
    }
    for (i = 0; i < 3; i++) {
        ASSERT_EQ(subs[i].destroy_calls, 1);
    }

    break_runtime_coordinator_destroy(rt);
}

TEST(timeout_retains_ownership_and_retry_from_stopping)
{
    BreakRuntimeCoordinator *rt = NULL;
    FakeSub subs[2];

    memset(subs, 0, sizeof(subs));
    subs[0].id = 1;
    subs[1].id = 2;
    subs[1].timeout_event = EV_JOIN;
    subs[1].timeout_armed = true;

    ASSERT_EQ(break_runtime_coordinator_create(NULL, &rt), BREAK_RUNTIME_OK);
    {
        int i;
        for (i = 0; i < 2; i++) {
            BreakRuntimeSubsystem desc = fake_desc(&subs[i]);
            ASSERT_EQ(break_runtime_coordinator_register_subsystem(rt, &desc),
                      BREAK_RUNTIME_OK);
        }
    }
    ASSERT_EQ(break_runtime_coordinator_start(rt), BREAK_RUNTIME_OK);

    log_reset(rt);
    ASSERT_EQ(break_runtime_coordinator_stop(rt), BREAK_RUNTIME_TIMEOUT);
    /* Timeout retains ownership: still STOPPING, nothing destroyed, the
     * coordinator object stays live and queryable. */
    ASSERT_EQ(break_runtime_coordinator_state(rt), BREAK_RUNTIME_STOPPING);
    ASSERT_EQ(break_runtime_coordinator_last_error(rt), BREAK_RUNTIME_TIMEOUT);
    ASSERT_EQ(subs[0].destroy_calls, 0);
    ASSERT_EQ(subs[1].destroy_calls, 0);
    ASSERT_EQ(break_runtime_coordinator_admit(rt), BREAK_RUNTIME_CLOSED);

    {
        static const int expected[] = {
            11, 21, 12, 22, 13, 23, 14, 24, 15, 25
        };
        ASSERT_TRUE(events_match(expected, 10));
    }

    /* Retry stop from STOPPING is legal and resumes at the timed-out join. */
    subs[1].timeout_armed = false;
    ASSERT_EQ(break_runtime_coordinator_stop(rt), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_coordinator_state(rt), BREAK_RUNTIME_STOPPED);
    ASSERT_EQ(break_runtime_coordinator_last_error(rt), BREAK_RUNTIME_OK);

    /* Resume must not re-run completed callbacks: subsystem 1 joined exactly
     * once; subsystem 2 joined twice total (timeout + successful retry);
     * destroy ran exactly once per subsystem. */
    ASSERT_EQ(event_occurrences(15), 1);
    ASSERT_EQ(event_occurrences(25), 2);
    ASSERT_EQ(event_occurrences(16), 1);
    ASSERT_EQ(event_occurrences(26), 1);
    ASSERT_EQ(subs[0].destroy_calls, 1);
    ASSERT_EQ(subs[1].destroy_calls, 1);

    break_runtime_coordinator_destroy(rt);
}

TEST(timeout_during_drain_resumes_in_place)
{
    BreakRuntimeCoordinator *rt = NULL;
    FakeSub sub;
    BreakRuntimeSubsystem desc;

    memset(&sub, 0, sizeof(sub));
    sub.id = 1;
    sub.timeout_event = EV_DRAIN;
    sub.timeout_armed = true;
    desc = fake_desc(&sub);

    ASSERT_EQ(break_runtime_coordinator_create(NULL, &rt), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_coordinator_register_subsystem(rt, &desc),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_coordinator_start(rt), BREAK_RUNTIME_OK);

    log_reset(rt);
    ASSERT_EQ(break_runtime_coordinator_stop(rt), BREAK_RUNTIME_TIMEOUT);
    ASSERT_EQ(break_runtime_coordinator_state(rt), BREAK_RUNTIME_DRAINING);
    ASSERT_EQ(sub.destroy_calls, 0);

    sub.timeout_armed = false;
    ASSERT_EQ(break_runtime_coordinator_stop(rt), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_coordinator_state(rt), BREAK_RUNTIME_STOPPED);
    ASSERT_EQ(event_occurrences(14), 2);
    ASSERT_EQ(event_occurrences(15), 1);
    ASSERT_EQ(event_occurrences(16), 1);
    ASSERT_EQ(sub.destroy_calls, 1);

    break_runtime_coordinator_destroy(rt);
}

TEST(failed_is_sticky_for_admission)
{
    BreakRuntimeCoordinator *rt = NULL;
    FakeSub sub;
    BreakRuntimeSubsystem desc;

    memset(&sub, 0, sizeof(sub));
    sub.id = 1;
    desc = fake_desc(&sub);

    ASSERT_EQ(break_runtime_coordinator_create(NULL, &rt), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_coordinator_register_subsystem(rt, &desc),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_coordinator_start(rt), BREAK_RUNTIME_OK);

    ASSERT_EQ(break_runtime_coordinator_fail(rt, BREAK_RUNTIME_OOM),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_coordinator_state(rt), BREAK_RUNTIME_STATE_FAILED);
    ASSERT_EQ(break_runtime_coordinator_last_error(rt), BREAK_RUNTIME_OOM);

    /* FAILED never re-opens ordinary admission. */
    ASSERT_EQ(break_runtime_coordinator_admit(rt), BREAK_RUNTIME_FAILED);
    ASSERT_EQ(break_runtime_coordinator_start(rt), BREAK_RUNTIME_REJECTED);

    /* Sticky: stop from FAILED runs no subsystem callbacks. */
    log_reset(rt);
    ASSERT_EQ(break_runtime_coordinator_stop(rt), BREAK_RUNTIME_FAILED);
    ASSERT_EQ(g_event_count, 0);
    ASSERT_EQ(sub.destroy_calls, 0);

    /* Re-failing is idempotent and keeps the first diagnostic reason. */
    ASSERT_EQ(break_runtime_coordinator_fail(rt, BREAK_RUNTIME_INVALID),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_coordinator_last_error(rt), BREAK_RUNTIME_OOM);
    ASSERT_EQ(break_runtime_coordinator_state(rt), BREAK_RUNTIME_STATE_FAILED);

    break_runtime_coordinator_destroy(rt);
}

TEST(callback_error_propagates_and_enters_failed)
{
    BreakRuntimeCoordinator *rt = NULL;
    FakeSub subs[3];
    int i;

    memset(subs, 0, sizeof(subs));
    for (i = 0; i < 3; i++) {
        subs[i].id = i + 1;
    }
    subs[1].fail_event = EV_DRAIN;
    subs[1].fail_error = BREAK_RUNTIME_INVALID;

    ASSERT_EQ(break_runtime_coordinator_create(NULL, &rt), BREAK_RUNTIME_OK);
    for (i = 0; i < 3; i++) {
        BreakRuntimeSubsystem desc = fake_desc(&subs[i]);
        ASSERT_EQ(break_runtime_coordinator_register_subsystem(rt, &desc),
                  BREAK_RUNTIME_OK);
    }
    ASSERT_EQ(break_runtime_coordinator_start(rt), BREAK_RUNTIME_OK);

    log_reset(rt);
    /* The subsystem error propagates verbatim and publishes sticky FAILED. */
    ASSERT_EQ(break_runtime_coordinator_stop(rt), BREAK_RUNTIME_INVALID);
    ASSERT_EQ(break_runtime_coordinator_state(rt), BREAK_RUNTIME_STATE_FAILED);
    ASSERT_EQ(break_runtime_coordinator_last_error(rt), BREAK_RUNTIME_INVALID);

    {
        static const int expected[] = {
            11, 21, 31, 12, 22, 32, 13, 23, 33, 14, 24
        };
        ASSERT_TRUE(events_match(expected, 11));
    }

    /* FAILED is sticky: no resume, no extra callbacks, admission stays shut. */
    ASSERT_EQ(break_runtime_coordinator_stop(rt), BREAK_RUNTIME_FAILED);
    ASSERT_EQ(g_event_count, 11);
    ASSERT_EQ(break_runtime_coordinator_admit(rt), BREAK_RUNTIME_FAILED);
    for (i = 0; i < 3; i++) {
        ASSERT_EQ(subs[i].destroy_calls, 0);
    }

    break_runtime_coordinator_destroy(rt);
}

TEST(subsystem_table_is_bounded)
{
    BreakRuntimeCoordinator *rt = NULL;
    BreakRuntimeCoordinatorConfig cfg;
    FakeSub subs[4];
    FakeSub extra;
    int i;

    memset(subs, 0, sizeof(subs));
    memset(&extra, 0, sizeof(extra));
    extra.id = 99;
    memset(&cfg, 0, sizeof(cfg));
    cfg.max_subsystems = 4u;

    ASSERT_EQ(break_runtime_coordinator_create(&cfg, &rt), BREAK_RUNTIME_OK);
    for (i = 0; i < 4; i++) {
        BreakRuntimeSubsystem desc;
        subs[i].id = i + 1;
        desc = fake_desc(&subs[i]);
        ASSERT_EQ(break_runtime_coordinator_register_subsystem(rt, &desc),
                  BREAK_RUNTIME_OK);
    }
    {
        BreakRuntimeSubsystem desc = fake_desc(&extra);
        ASSERT_EQ(break_runtime_coordinator_register_subsystem(rt, &desc),
                  BREAK_RUNTIME_OVERLOAD);
    }
    ASSERT_EQ(break_runtime_coordinator_state(rt), BREAK_RUNTIME_CREATED);

    ASSERT_EQ(break_runtime_coordinator_start(rt), BREAK_RUNTIME_OK);
    log_reset(rt);
    ASSERT_EQ(break_runtime_coordinator_stop(rt), BREAK_RUNTIME_OK);
    for (i = 0; i < 4; i++) {
        ASSERT_EQ(subs[i].destroy_calls, 1);
    }
    ASSERT_EQ(extra.destroy_calls, 0);
    break_runtime_coordinator_destroy(rt);

    /* The default capacity is BREAK_RUNTIME_MAX_SUBSYSTEMS and it is bounded. */
    rt = NULL;
    ASSERT_EQ(break_runtime_coordinator_create(NULL, &rt), BREAK_RUNTIME_OK);
    for (i = 0; i < (int)BREAK_RUNTIME_MAX_SUBSYSTEMS; i++) {
        BreakRuntimeSubsystem desc = fake_desc(&extra);
        ASSERT_EQ(break_runtime_coordinator_register_subsystem(rt, &desc),
                  BREAK_RUNTIME_OK);
    }
    {
        BreakRuntimeSubsystem desc = fake_desc(&extra);
        ASSERT_EQ(break_runtime_coordinator_register_subsystem(rt, &desc),
                  BREAK_RUNTIME_OVERLOAD);
    }
    break_runtime_coordinator_destroy(rt);
}

TEST_MAIN_BEGIN()
    RUN_TEST(create_destroy_and_capacity_validation);
    RUN_TEST(legal_lifecycle_transitions);
    RUN_TEST(invalid_transitions_rejected);
    RUN_TEST(subsystem_callbacks_run_in_documented_order);
    RUN_TEST(timeout_retains_ownership_and_retry_from_stopping);
    RUN_TEST(timeout_during_drain_resumes_in_place);
    RUN_TEST(failed_is_sticky_for_admission);
    RUN_TEST(callback_error_propagates_and_enters_failed);
    RUN_TEST(subsystem_table_is_bounded);
TEST_MAIN_END()
