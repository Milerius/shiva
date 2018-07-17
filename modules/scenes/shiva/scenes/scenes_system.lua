--
-- Created by IntelliJ IDEA.
-- User: romansztergbaum
-- Date: 23/06/2018
-- Time: 13:31
-- To change this template use File | Settings | File Templates.
--

local lfs = require "lfs"
local scenes_table = {}

function get_file_name(file)
    return file:match("^.+/(.+)$")
end

function get_file_extension(url)
    return url:match("^.+(%..+)$")
end

function attrdir(path, original_path)
    for file in lfs.dir(path) do
        if file ~= "." and file ~= ".." then
            local f = path .. '/' .. file
            local attr = lfs.attributes(f)
            if attr.mode == "directory" then
                attrdir(f, original_path)
            else
                if (get_file_extension(f) == ".lua") then
                    local res = load_script(get_file_name(f), original_path)
                    assert(res, "should be true")
                end
            end
        end
    end
end


function __constructor__()
    print("scene manager constructor")
    local dir = lfs.currentdir() .. "/assets/scripts/scenes/lua"
    attrdir(dir, dir)
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