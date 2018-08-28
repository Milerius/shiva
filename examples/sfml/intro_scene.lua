--
-- Created by IntelliJ IDEA.
-- User: romansztergbaum
-- Date: 19/08/2018
-- Time: 17:43
-- To change this template use File | Settings | File Templates.
--

--
-- Created by IntelliJ IDEA.
-- User: romansztergbaum
-- Date: 06/08/2018
-- Time: 22:07
-- To change this template use File | Settings | File Templates.
--

local entities = {}

function update()
end

function on_key_pressed(evt)
    if (evt.keycode == Keyboard.Escape) then
        shiva.dispatcher:trigger_change_scene_event("game_scene")
    end
end

function on_video_end()
    shiva.dispatcher:trigger_change_scene_event("game_scene")
end

function on_key_released(evt)
end

function leave()
    print("leave intro scene")
    for key, value in pairs(entities) do
        shiva.entity_registry:destroy(value)
        entities[key] = nil
    end
    shiva.resource_registry:unload_all_resources("intro_scene")
    print("leaving sprite scene, nb entities: " .. shiva.entity_registry:nb_entities())
end

function on_after_load_resources(evt)
    local video_id = shiva.video:create_game_object_with_video(video_status.playing, "intro_scene/intro", on_video_end);
    shiva.entity_registry:add_layer_8_component(video_id)
    entities[#entities + 1] = video_id
end

function enter()
    print("enter intro scene")
    shiva.resource_registry:load_all_resources("intro_scene")
    shiva.dispatcher:trigger_disable_system_event("imgui_system", system_type.post_update)
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

