--
-- Created by IntelliJ IDEA.
-- User: romansztergbaum
-- Date: 17/07/2018
-- Time: 16:47
-- To change this template use File | Settings | File Templates.
--

local entities = {}

function update()
    local transform = shiva.entity_registry:get_transform_2d_component(kirito_id)

    if (shiva.is_key_pressed(Keyboard.D) == true) then
        transform.x = transform.x + 10
    end

    if (shiva.is_key_pressed(Keyboard.Q) == true) then
        transform.x = transform.x - 10
    end

    if (shiva.is_key_pressed(Keyboard.Z) == true) then
        transform.y = transform.y - 10
    end

    if (shiva.is_key_pressed(Keyboard.S) == true) then
        transform.y = transform.y + 10
    end
end

function on_key_pressed(evt)
    print("shift: " .. (evt.shift and 'true' or 'false'))
    print("system: " .. (evt.system and 'true' or 'false'))
    print("alt: " .. (evt.alt and 'true' or 'false'))
    print("ctrl: " .. (evt.control and 'true' or 'false'))
    if (evt.keycode == Keyboard.Escape) then
        print("should quit_game")
        shiva.dispatcher:trigger_quit_game_event(1)
    elseif (evt.keycode == Keyboard.Right) then
        shiva.dispatcher:trigger_change_scene_event("sprite_scene")
    end
end

function on_key_released(evt)
end

function leave()
    for key, value in pairs(entities) do
        shiva.entity_registry:destroy(value)
        entities[key] = nil
    end
    shiva.resource_registry:unload_all_resources("game_scene")
    print("leaving game scene, nb entities: " .. shiva.entity_registry:nb_entities())
end

function prepare_scripted_entities()
    entities[#entities + 1] = shiva.entity_registry:create_scripted_game_object("player.lua", "player_table")
end

function on_after_load_resources(evt)
    prepare_scripted_entities()

    --local id = shiva.anim:create_game_object_with_animated_sprite(anim_status.playing,
    --    0.12, true, 1, 1, 1, 9, "game_scene/mage_idle_dir_1")

    -- local id = shiva.anim:create_game_object_with_animated_sprite(anim_status.playing,
    --     0.09, true, 1, 12, 7, 80, "game_scene/bheet_arrival")

    other_id = shiva.entity_registry:create_text("Hello from game_scene", "game_scene/kenney_future", 24)
    shiva.entity_registry:add_layer_1_component(other_id)

    entities[#entities + 1] = other_id

    kirito_id = shiva.entity_registry:create_game_object_with_sprite("game_scene/kirito", 450, 150)
    local transform = shiva.entity_registry:get_transform_2d_component(kirito_id)
    transform.scale_x = 0.3
    transform.scale_y = 0.3
    shiva.entity_registry:add_layer_1_component(kirito_id)

    entities[#entities + 1] = kirito_id

    print("after_loading_resources game scene, nb entities: " .. shiva.entity_registry:nb_entities())
end

function enter()
    print("enter game scene")
    shiva.resource_registry:load_all_resources("game_scene")
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