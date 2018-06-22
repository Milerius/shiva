--
-- Created by IntelliJ IDEA.
-- User: romansztergbaum
-- Date: 22/06/2018
-- Time: 16:23
-- To change this template use File | Settings | File Templates.
--

function test_create_entity()
    local id = shiva.entity_registry:create()
    assert(id == 0, "id should be 0 here")
    return id
end

function test_destroy_entity()
    local id = shiva.entity_registry:create()
    shiva.entity_registry:destroy(id)
    return true
end

function test_component()
    local entity_id = shiva.entity_registry:create()
    local component = shiva.entity_registry:add_layer_1_component(entity_id)
    local same_component = shiva.entity_registry:get_layer_1_component(entity_id)
    assert(shiva.entity_registry:has_layer_1_component(entity_id) == true, "should be true")
    shiva.entity_registry:remove_layer_1_component(entity_id)
    assert(shiva.entity_registry:has_layer_1_component(entity_id) == false, "should be false")
    return true
end

