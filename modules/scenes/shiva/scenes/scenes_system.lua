--
-- Created by IntelliJ IDEA.
-- User: romansztergbaum
-- Date: 23/06/2018
-- Time: 13:31
-- To change this template use File | Settings | File Templates.
--

local scenes_table = {}

function __constructor__()
    print("scene manager constructor")
end

function __destructor__()
    print("scene manager destructor")
end

function internal_update()
    print("scene manager update")
end

scenes_system_table = {
    update = internal_update,
    on_construct = __constructor__,
    on_destruct = __destructor__,
    current_system_type = system_type.logic_update
}