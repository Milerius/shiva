--
-- Created by IntelliJ IDEA.
-- User: romansztergbaum
-- Date: 17/07/2018
-- Time: 16:47
-- To change this template use File | Settings | File Templates.
--

function update()
    --print("nb entities" .. shiva.entity_registry:nb_entities())
end

function on_key_pressed(evt)
    print("game scene keycode: " .. evt.keycode)
end

function on_key_released(evt)
    print("game scene released keycode: " .. evt.keycode)
end

return {
    on_key_released = on_key_released,
    on_key_pressed = on_key_pressed,
    update = update,
    scene_active = true
}