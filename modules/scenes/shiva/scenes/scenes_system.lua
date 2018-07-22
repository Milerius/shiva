--
-- Created by IntelliJ IDEA.
-- User: romansztergbaum
-- Date: 23/06/2018
-- Time: 13:31
-- To change this template use File | Settings | File Templates.
--

local lfs = require "lfs"
local scenes_table = {}
local current_scene

function get_file_name(file)
    return file:match("^.+/(.+)$")
end

function get_file_extension(url)
    return url:match("^.+(%..+)$")
end

function load_scene(require_path, filename)
    if (get_file_extension(filename) == ".lua") then
        local scene_name = string.gsub(get_file_name(filename), '.lua$', '')
        scenes_table[scene_name] = require(require_path .. "." .. scene_name)
        if scenes_table[scene_name].scene_active == true then
            current_scene = scenes_table[scene_name]
            current_scene.enter()
        end
    end
end

function recursive_directory_crossing(path, require_path)
    for file in lfs.dir(path) do
        if file ~= "." and file ~= ".." then
            local f = path .. '/' .. file
            local attr = lfs.attributes(f)
            if attr.mode == "directory" then
                recursive_directory_crossing(f, require_path)
            else
                load_scene(require_path, f)
            end
        end
    end
end

function __constructor__()
    print("scene manager constructor")
    local dir = lfs.currentdir() .. "/assets/scripts/scenes/lua"
    recursive_directory_crossing(dir, "assets.scripts.scenes.lua")
end

function __destructor__()
    print("scene manager destructor")
    if current_scene.leave ~= nil then
        current_scene.leave()
    else
        print("current scene doesn't have leave callback")
    end
end

function internal_update()
    if (current_scene.update ~= nil) then
        current_scene.update()
    end
end

function internal_key_pressed(evt)
    if current_scene.on_key_pressed ~= nil then
        current_scene.on_key_pressed(evt)
    else
        print("current scene doesn't have on_key_pressed callback")
    end
end

function internal_key_released(evt)
    if current_scene.on_key_released ~= nil then
        current_scene.on_key_released(evt)
    else
        print("current scene doesn't have on_key_released callback")
    end
end

function internal_after_load_resources(evt)
    if current_scene.on_after_load_resources ~= nil then
        current_scene.on_after_load_resources(evt)
    else
        print("current scene doesn't have on_after_load_resources callback")
    end
end

function internal_change_scene(scene_name)
    if scenes_table[scene_name] ~= nil then
        current_scene.leave()
        current_scene = scenes_table[scene_name]
        current_scene.scene_active = true
        current_scene.enter()
    end
end

scenes_system_table = {
    update = internal_update,
    on_key_pressed = internal_key_pressed,
    on_key_released = internal_key_released,
    on_after_load_resources = internal_after_load_resources,
    on_construct = __constructor__,
    on_destruct = __destructor__,
    current_system_type = system_type.logic_update
}