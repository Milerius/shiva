--
-- Created by IntelliJ IDEA.
-- User: romansztergbaum
-- Date: 17/07/2018
-- Time: 16:47
-- To change this template use File | Settings | File Templates.
--

local entities = {}

function update()
    --print("nb entities" .. shiva.entity_registry:nb_entities())
    if (shiva.is_key_pressed(Keyboard.Z) == true) then
        print("Z pressed")
    end
end

function on_key_pressed(evt)
    if (evt.keycode == Keyboard.Escape) then
        print("should quit_game")
        shiva.dispatcher.trigger_quit_game_event(shiva.dispatcher, 1)
    end
end

function on_key_released(evt)
end

function leave()
    print("leave game scene")
    for key, value in pairs(entities) do
        shiva.entity_registry:destroy(value)
    end
    shiva.resource_registry:unload_all_resources("game_scene")
end

function on_after_load_resources(evt)
    --local id, sprite = shiva.entity_registry:create_game_object_with_sprite()
    --sprite:set_texture(shiva.resource_registry:get_texture("game_scene/toto"), false)
    --entities[#entities + 1] = id
    --shiva.entity_registry:add_layer_1_component(id)

    --local id = shiva.anim:create_game_object_with_animated_sprite(anim_status.playing,
    --    0.12, true, 1, 1, 1, 9, "game_scene/mage_idle_dir_1")

    local id = shiva.anim:create_game_object_with_animated_sprite(anim_status.playing,
        0.09, true, 1, 12, 7, 80, "game_scene/bheet_arrival")
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