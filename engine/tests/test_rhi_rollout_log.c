#include "rhi/rhi_rollout.h"
#include <stdio.h>
#include <string.h>

static int failures = 0;
static void check(const char *what, int cond) {
    if (!cond) { printf("FAIL: %s\n", what); failures++; }
}

int main(void) {
    char buf[512];
    RHIRolloutEvent ev = {
        .event = "backend_selected",
        .backend = "vulkan",
        .reason = "platform-default",
        .config_version = 3,
        .result = "OK",
    };
    int n = rhi_rollout_format(buf, sizeof(buf), &ev);
    check("format returns length", n > 0);
    check("prefix", strncmp(buf, "RHIEVT {", 8) == 0);
    check("event field", strstr(buf, "\"event\":\"backend_selected\"") != NULL);
    check("backend field", strstr(buf, "\"backend\":\"vulkan\"") != NULL);
    check("reason field", strstr(buf, "\"reason\":\"platform-default\"") != NULL);
    check("config_version field", strstr(buf, "\"config_version\":3") != NULL);
    check("result field", strstr(buf, "\"result\":\"OK\"") != NULL);
    check("single line", strchr(buf, '\n') == NULL);

    /* 截断语义：缓冲不足必须返回 -1，不得写出未终止串。 */
    char tiny[16];
    check("truncation returns -1", rhi_rollout_format(tiny, sizeof(tiny), &ev) == -1);

    /* 事件名白名单：非法事件名拒绝格式化。 */
    RHIRolloutEvent bad = ev;
    bad.event = "made_up_event";
    check("unknown event rejected", rhi_rollout_format(buf, sizeof(buf), &bad) == -1);

    if (failures) { printf("%d failures\n", failures); return 1; }
    printf("OK\n");
    return 0;
}
