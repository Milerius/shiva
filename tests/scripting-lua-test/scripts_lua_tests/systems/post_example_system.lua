--
-- Created by IntelliJ IDEA.
-- User: romansztergbaum
-- Date: 23/06/2018
-- Time: 08:20
-- To change this template use File | Settings | File Templates.
--

function __constructor__()
    print("constructor post_example_system")
    --local id = shiva.entity_registry:create()
end

function __destructor__()
    print("destructor post_example_system")
end

function internal_update()
    print("post_example_system")
end

post_example_system_table = {
    update = internal_update,
    on_construct = __constructor__,
    on_destruct = __destructor__,
    current_system_type = system_type.post_update
}

