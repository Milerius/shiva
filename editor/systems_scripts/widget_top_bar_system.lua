--
-- Created by IntelliJ IDEA.
-- User: milerius
-- Date: 31/08/18
-- Time: 14:10
-- To change this template use File | Settings | File Templates.
--

resource_loaded = false

function __constructor__()
    --shiva.resource_registry:load_all_resources("editor_textures")
end

function after_loading()
    --resource_loaded = true
    --next_button_texture = shiva.resource_registry:get_texture_c("editor_textures/next");
end

function __destructor__()
end

function __update__()
    --imgui.BeginMainMenuBar()
    --if imgui.BeginMenu("File", true) then
    --    imgui.MenuItem("            ", false, false)
    --    if imgui.BeginMenu("New") then
    --        imgui.MenuItem("Project")
    --        imgui.EndMenu()
    --    end
    --    imgui.EndMenu()
    --end

    --if imgui.BeginMenu("Options", true) then
    --    imgui.EndMenu()
    --end

    --if imgui.BeginMenu("Help", true) then
    --    imgui.EndMenu()
    --end

    --if resource_loaded then
    --    if shiva.render:imgui_image_button(next_button_texture) then
    --        if imgui:is_item_hovered() then
    --            imgui.BeginTooltip()
    --            imgui.TextUnformatted("I am a fancy tooltip");
    --            imgui.EndTooltip()
    --        end
    --    end
    --end
    --imgui.EndMainMenuBar()
end

widget_top_bar_system_table = {
    update = __update__,
    on_construct = __constructor__,
    on_destruct = __destructor__,
    on_after_load_resources = after_loading,
    current_system_type = system_type.post_update,
    prioritize_system = "render_system"
}

