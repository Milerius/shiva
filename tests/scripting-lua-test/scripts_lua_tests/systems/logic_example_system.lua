--
-- Created by IntelliJ IDEA.
-- User: romansztergbaum
-- Date: 23/06/2018
-- Time: 13:31
-- To change this template use File | Settings | File Templates.
--

function __constructor__()
    print("constructor logic_example_system")
end

function __destructor__()
    print("destructor logic_example_system")
end

function internal_update()
    print("logic_example_system")
end

logic_example_system_table = {
    update = internal_update,
    on_construct = __constructor__,
    on_destruct = __destructor__,
    current_system_type = system_type.logic_update
}

