--
-- Created by IntelliJ IDEA.
-- User: romansztergbaum
-- Date: 16/08/2018
-- Time: 16:04
-- To change this template use File | Settings | File Templates.
--

function update(entity_id)
end

function init(entity_id)
    print("INIT: " .. entity_id)
    shiva.anim:add_animated_game_object_from_json("game_scene/bheet_arrival", entity_id);
    shiva.entity_registry:add_layer_1_component(entity_id)
end

player_table = {
    on_update = update,
    on_init = init
}