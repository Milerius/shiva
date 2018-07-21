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

function leave()
    print("leave game scene")
end

function on_after_load_resources(evt)
    local id, sprite = shiva.entity_registry:create_game_object_with_sprite()
    sprite:set_texture(shiva.resource_registry:get_texture("game_scene/toto"), false)
    shiva.entity_registry:add_layer_1_component(id)
end

function enter()
    print("enter game scene")
    shiva.resource_registry:load_all_resources("game_scene")
    print("should be here")
end

return {
    on_key_released = on_key_released,
    on_key_pressed = on_key_pressed,
    on_after_load_resources = on_after_load_resources,
    leave = leave,
    enter = enter,
    update = update,
    scene_active = true
}