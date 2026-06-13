-- init.lua — Break demo script (real Lua 5.4, hot-reloadable)
--
-- The host binds three systems before running this file:
--   engine.entity_count()         -> number of live ECS entities
--   engine.body_count()           -> number of physics bodies
--   engine.get_pos(id)            -> x, y, z
--   engine.set_pos(id, x, y, z)
--   engine.get_vel(id)            -> x, y, z
--   engine.set_vel(id, x, y, z)
--   engine.apply_impulse(id, x, y, z)
--   engine.spawn(x, y, z [,mass]) -> new body id
--   engine.body_set_ccd(id, on)
--   engine.key_down(keycode)      -> bool
--   engine.log(msg)
--
-- Tunables (also readable/writable from the host as plain globals):
gravity = -9.81
move_speed = 6.0
jump_force = 8.0

local elapsed = 0.0
local next_log = 1.0

function on_start()
  engine.log(string.format(
    "init.lua: %d entities, %d bodies (gravity=%.2f)",
    engine.entity_count(), engine.body_count(), gravity))
end

function on_update(dt)
  elapsed = elapsed + dt
  -- Heartbeat so hot-reloading the file is observable in the log without
  -- perturbing the simulation.
  if elapsed >= next_log then
    next_log = next_log + 5.0
    engine.log(string.format("init.lua alive: t=%.1fs, bodies=%d",
                             elapsed, engine.body_count()))
  end
end

-- Invoked on demand by the host (e.g. a spawn key); drops a dynamic box.
function on_spawn()
  local id = engine.spawn(0.0, 6.0, 0.0, 1.0)
  engine.log("init.lua spawned body " .. tostring(id))
end
