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
    assert(shiva.entity_registry:nb_entities() == 1)
    shiva.entity_registry:destroy(id)
    assert(shiva.entity_registry:nb_entities() == 0)
    return true
end

function test_component()
    local entity_id = shiva.entity_registry:create()
    local component = shiva.entity_registry:add_layer_1_component(entity_id)
    local same_component = shiva.entity_registry:get_layer_1_component(entity_id)
    assert(shiva.entity_registry:layer_1_id() == 0, "should be 0")
    assert(shiva.entity_registry:has_layer_1_component(entity_id) == true, "should be true")
    shiva.entity_registry:remove_layer_1_component(entity_id)
    assert(shiva.entity_registry:has_layer_1_component(entity_id) == false, "should be false")
    return true
end

function simple_functor(entity_id)
    shiva.entity_registry:destroy(entity_id)
end

function test_for_each()
    for i = 1, 10
    do
        local id = shiva.entity_registry:create()
        shiva.entity_registry:add_layer_1_component(id)
    end

    assert(shiva.entity_registry:nb_entities() == 10, "should be 10")
    shiva.entity_registry:for_each_entities_which_have_layer_1_component(simple_functor)
    assert(shiva.entity_registry:nb_entities() == 0, "should be 0")
    return true
end

function test_for_each_runtime()
    for i = 1, 10
    do
        local id = shiva.entity_registry:create()
        if i == 4 then
            shiva.entity_registry:add_layer_3_component(id)
        else
            shiva.entity_registry:add_layer_1_component(id)
            shiva.entity_registry:add_layer_2_component(id)
        end
    end

    assert(shiva.entity_registry:nb_entities() == 10, "should be 10")

    local table_type = {
        shiva.entity_registry:layer_1_id(),
        shiva.entity_registry:layer_2_id()
    }
    shiva.entity_registry:for_each_runtime(table_type, simple_functor)
    assert(shiva.entity_registry:nb_entities() == 1, "should be 1")
    return true
end

