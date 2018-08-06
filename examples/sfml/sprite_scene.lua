--
-- Created by IntelliJ IDEA.
-- User: romansztergbaum
-- Date: 06/08/2018
-- Time: 22:07
-- To change this template use File | Settings | File Templates.
--

local entities = {}

function update()
    if (shiva.is_key_pressed(Keyboard.Z) == true) then
        print("Z pressed")
    end
end

function on_key_pressed(evt)
    if (evt.keycode == Keyboard.Escape) then
        print("should quit_game")
        shiva.dispatcher.trigger_quit_game_event(shiva.dispatcher, 1)
    elseif (evt.keycode == Keyboard.Left) then
        shiva.dispatcher.trigger_change_scene_event(shiva.dispatcher, "game_scene")
    end
end

function on_key_released(evt)
end

function leave()
    print("leave sprite scene")
    for key, value in pairs(entities) do
        shiva.entity_registry:destroy(value)
        entities[key] = nil
    end
    shiva.resource_registry:unload_all_resources("sprite_scene")
    print("leaving sprite scene, nb entities: " .. shiva.entity_registry:nb_entities())
end

function on_after_load_resources(evt)
    local id, sprite = shiva.entity_registry:create_game_object_with_sprite()
    sprite:set_texture(shiva.resource_registry:get_texture("sprite_scene/toto"), false)
    entities[#entities + 1] = id
    shiva.entity_registry:add_layer_1_component(id)

    local other_id = shiva.entity_registry:create_text("Hello from sprite_scene", "sprite_scene/kenney_future", 24)
    shiva.entity_registry:add_layer_1_component(other_id)
    entities[#entities + 1] = other_id

    print("after_loading_resources sprite scene, nb entities: " .. shiva.entity_registry:nb_entities())
end

function enter()
    print("enter sprite scene")
    shiva.resource_registry:load_all_resources("sprite_scene")
end

return {
    on_key_released = on_key_released,
    on_key_pressed = on_key_pressed,
    on_after_load_resources = on_after_load_resources,
    leave = leave,
    enter = enter,
    update = update,
    scene_active = false
}

