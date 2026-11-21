#pragma once

/* Shared vocabulary for every Chrome trace-event JSON file the engine
 * writes. Full-document exporters close the document with
 * BREAK_TRACE_OTHER_DATA so a consumer can identify the schema and version;
 * fragment exporters (break_runtime_profiler_export_flows) emit only events
 * and rely on the enclosing document for the marker. */

#define BREAK_TRACE_SCHEMA_NAME "break.trace"
#define BREAK_TRACE_SCHEMA_VERSION 1

#define BREAK_TRACE_OTHER_DATA \
    "\"otherData\":{\"schema\":\"break.trace\",\"schema_version\":1}"

#define BREAK_TRACE_CAT_CORE_APP "core_app"
#define BREAK_TRACE_CAT_CPU "cpu"
#define BREAK_TRACE_CAT_FRAME "frame"
#define BREAK_TRACE_CAT_GPU "gpu"
#define BREAK_TRACE_CAT_META "meta"
#define BREAK_TRACE_CAT_RUNTIME "runtime"
#define BREAK_TRACE_CAT_RUNTIME_FLOW "runtime.flow"
#define BREAK_TRACE_CAT_TASK "task"
#define BREAK_TRACE_CAT_TASK_FLOW "task.flow"
