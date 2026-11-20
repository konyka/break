#ifndef QNX_TLS_GENERAL_INTERPOSE_H
#define QNX_TLS_GENERAL_INTERPOSE_H

typedef struct {
    unsigned long setspecific_calls;
    unsigned long key_exit_calls;
    unsigned long enter_count;
    unsigned long leave_count;
    unsigned long failures;
    unsigned long last_event;
    unsigned long main_leave_calls;
    unsigned long dso_fini_calls;
} QnxTlsGeneralStats;

static inline unsigned long qnx_tls_general_load(const unsigned long *value)
{
    return __atomic_load_n(value, __ATOMIC_SEQ_CST);
}

static inline void qnx_tls_general_store(unsigned long *value, unsigned long next)
{
    __atomic_store_n(value, next, __ATOMIC_SEQ_CST);
}

#endif
