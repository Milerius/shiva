--
-- Created by IntelliJ IDEA.
-- User: romansztergbaum
-- Date: 17/07/2018
-- Time: 16:47
-- To change this template use File | Settings | File Templates.
--

print("hello guys")

function update()
    print("nb entities" .. shiva.entity_registry:nb_entities())
end

function on_key_pressed(keycode)
end

function on_key_released(keycode)
end

return {
    on_key_released = on_key_released,
    on_key_pressed = on_key_pressed,
    update = update,
    scene_active = true
}