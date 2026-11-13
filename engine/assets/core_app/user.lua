function on_spawn()
    return true
end
function on_actor_tick(actor, dt)
    state.ticks = (state.ticks or 0) + 1
end
