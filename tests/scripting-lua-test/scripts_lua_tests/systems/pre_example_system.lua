--
-- Created by IntelliJ IDEA.
-- User: romansztergbaum
-- Date: 23/06/2018
-- Time: 08:20
-- To change this template use File | Settings | File Templates.
--

function __constructor__()
    print("constructor pre_example_system")
    for i = 1, 10
    do
        local id = shiva.entity_registry:create()
        shiva.entity_registry:add_layer_1_component(id)
    end

end

function __destructor__()
    print("destructor pre_example_system")
end

function simple_functor(entity_id)
    print("entity_id: " .. entity_id)
end

function internal_update()
    print("pre_example_system")
    shiva.entity_registry:for_each_entities_which_have_layer_1_component(simple_functor)
end

pre_example_system_table = {
    update = internal_update,
    on_construct = __constructor__,
    on_destruct = __destructor__,
    current_system_type = system_type.pre_update
}

