#include "cry_game.h"

BreakRuntimeError cry_game_run(const CryGameConfig *config, int *out_exit_code) {
    if (out_exit_code == NULL) return BREAK_RUNTIME_INVALID;
    *out_exit_code = 2;
    if (config == NULL) return BREAK_RUNTIME_INVALID;
    return BREAK_RUNTIME_FAILED;
}
