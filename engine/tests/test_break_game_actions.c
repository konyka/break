#include "test_framework.h"
#include <game/break_game.h>

TEST(bind_and_eval_keys_axes_and_replace) {
    World *world = world_create();
    BreakGame *game = break_game_create(world, NULL);
    ASSERT_NOT_NULL(game);
    BreakGameBinding key;
    key.source = BREAK_GAME_BIND_KEY;
    key.code = 17;
    key.pad = 0;
    key.scale = 0.5f;
    BreakGameBinding pos;
    pos.source = BREAK_GAME_BIND_PAD_AXIS;
    pos.code = 0;
    pos.pad = 0;
    pos.scale = 1.0f;
    BreakGameBinding neg;
    neg.source = BREAK_GAME_BIND_PAD_AXIS;
    neg.code = 1;
    neg.pad = 0;
    neg.scale = 1.0f;
    BreakGameBinding axes[2] = {pos, neg};
    BreakGameActionDesc desc[2];
    desc[0].name = "use";
    desc[0].bindings = &key;
    desc[0].binding_count = 1;
    desc[1].name = "move";
    desc[1].bindings = axes;
    desc[1].binding_count = 2;
    ASSERT_EQ(break_game_bind_actions(game, desc, 2), BREAK_GAME_OK);

    InputState input;
    memset(&input, 0, sizeof(input));
    input.keys[17] = 3;
    input.gamepads[0].connected = true;
    input.gamepads[0].axes[0] = 1.0f;
    input.gamepads[0].axes[1] = 1.0f;
    BreakGameActionValue values[2];
    memset(values, 0, sizeof(values));
    ASSERT_EQ(break_game_eval_actions(game, &input, values, 2), BREAK_GAME_OK);
    ASSERT_TRUE(values[0].down);
    ASSERT_FLOAT_EQ(values[0].axis, 0.5f, 1e-6);
    ASSERT_FALSE(values[1].down);
    ASSERT_FLOAT_EQ(values[1].axis, 1.0f, 1e-6);

    input.gamepads[0].axes[0] = 1.0f;
    input.gamepads[0].axes[1] = 0.0f;
    BreakGameBinding back;
    back.source = BREAK_GAME_BIND_PAD_AXIS;
    back.code = 0;
    back.pad = 0;
    back.scale = -3.0f;
    desc[1].bindings = &back;
    desc[1].binding_count = 1;
    ASSERT_EQ(break_game_bind_actions(game, desc, 2), BREAK_GAME_OK);
    ASSERT_EQ(break_game_eval_actions(game, &input, values, 2), BREAK_GAME_OK);
    ASSERT_FLOAT_EQ(values[1].axis, -1.0f, 1e-6);

    BreakGameBinding nine[9];
    for (int i = 0; i < 9; i++) nine[i] = key;
    BreakGameActionDesc bad = desc[0];
    bad.bindings = nine;
    bad.binding_count = 9;
    ASSERT_EQ(break_game_bind_actions(game, &bad, 1), BREAK_GAME_INVALID);
    input.keys[17] = 0;
    input.keys[17] = 3;
    ASSERT_EQ(break_game_eval_actions(game, &input, values, 2), BREAK_GAME_OK);
    ASSERT_TRUE(values[0].down);

    BreakGameBinding rebound;
    rebound.source = BREAK_GAME_BIND_KEY;
    rebound.code = 18;
    rebound.pad = 0;
    rebound.scale = 1.0f;
    desc[0].bindings = &rebound;
    desc[0].binding_count = 1;
    ASSERT_EQ(break_game_bind_actions(game, desc, 2), BREAK_GAME_OK);
    input.keys[17] = 3;
    input.keys[18] = 0;
    ASSERT_EQ(break_game_eval_actions(game, &input, values, 2), BREAK_GAME_OK);
    ASSERT_FALSE(values[0].down);
    input.keys[17] = 0;
    input.keys[18] = 3;
    ASSERT_EQ(break_game_eval_actions(game, &input, values, 2), BREAK_GAME_OK);
    ASSERT_TRUE(values[0].down);

    BreakGameActionValue dirty;
    dirty.down = true;
    dirty.axis = 9.0f;
    ASSERT_EQ(break_game_eval_actions(game, &input, &dirty, 1), BREAK_GAME_OVERLOAD);
    ASSERT_TRUE(dirty.down);
    ASSERT_FLOAT_EQ(dirty.axis, 9.0f, 1e-6);

    BreakGameActionDesc too_many[65];
    BreakGameBinding one = key;
    char names[65][8];
    for (int i = 0; i < 65; i++) {
        snprintf(names[i], sizeof(names[i]), "a%d", i);
        too_many[i].name = names[i];
        too_many[i].bindings = &one;
        too_many[i].binding_count = 1;
    }
    ASSERT_EQ(break_game_bind_actions(game, too_many, 65), BREAK_GAME_OVERLOAD);
    ASSERT_EQ(break_game_eval_actions(game, &input, values, 2), BREAK_GAME_OK);
    ASSERT_TRUE(values[0].down);

    break_game_destroy(game);
    world_destroy(world);
}

TEST_MAIN_BEGIN()
    RUN_TEST(bind_and_eval_keys_axes_and_replace);
TEST_MAIN_END()
