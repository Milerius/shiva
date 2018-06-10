//
// Created by roman Sztergbaum on 10/06/2018.
//

#pragma once

#include <EASTL/unordered_map.h>
#include <EASTL/string.h>
#include <EASTL/allocator_malloc.h>
#include <boost/function.hpp>
#include <boost/dll.hpp>
#include <shiva/filesystem/filesystem.hpp>

namespace shiva::helpers
{
    static inline bool is_shared_library(const fs::path &p)
    {
        const std::string &s = p.string();
        return (s.find(".dll") != std::string::npos || s.find(".so") != std::string::npos ||
                s.find(".dylib") != std::string::npos)
               && s.find(".lib") == std::string::npos
               && s.find(".exp") == std::string::npos
               && s.find(".pdb") == std::string::npos
               && s.find(".manifest") == std::string::npos
               && s.find(".rsp") == std::string::npos
               && s.find(".obj") == std::string::npos
               && s.find(".a") == std::string::npos;
    }

    namespace dll = boost::dll;

    template <typename TPlugin, typename CreatorSignature>
    class plugins_registry
    {
    public:
        using plugin_t = std::unordered_map<std::string, dll::shared_library>;
        using symbols_container = std::vector<boost::function<CreatorSignature>>;

    private:
        plugin_t plugins_{};
        symbols_container symbols;
        shiva::fs::path plugins_directory_;

        void load_all_plugins()
        {
            if (!fs::exists(plugins_directory_))
                return;
            fs::recursive_directory_iterator endit;
            for (fs::recursive_directory_iterator it(plugins_directory_); it != endit; ++it) {
                if (!fs::is_regular_file(*it)) {
                    continue;
                }
                if (!is_shared_library((*it).path())) {
                    continue;
                }

                boost::system::error_code error;
                dll::shared_library plugin(it->path(), error);
                if (error) {
                    std::cerr << error.message() << std::endl;
                    continue;
                }
                std::cout << "Loaded (" << plugin.native() << "):" << it->path() << std::endl;

                if (plugin.has("create_plugin")) {
                    auto plugin_name = plugin.get_alias<TPlugin()>("create_plugin")()->get_name();

                    if (shiva::ranges::none_of(plugins_, [&plugin_name](auto &&pair) {
                        return pair.first == plugin_name.c_str();
                    })) {
                        symbols.emplace_back(dll::import_alias<CreatorSignature>(plugin, "create_plugin"));
                        plugins_.emplace(std::move(plugin_name), std::move(plugin));
                    } else {
                        std::cerr << "plugins already register" << std::endl;
                    }
                } else {
                    std::cout << "no creator func : create_plugin()" << std::endl;
                }
            }
        }

    public:
        explicit plugins_registry(shiva::fs::path &&plugins_directory) noexcept :
            plugins_directory_{plugins_directory}
        {
            load_all_plugins();
        }

        size_t nb_plugins() const noexcept
        {
            return plugins_directory_.size();
        }

        template <typename Functor>
        void apply_symbols(Functor &&functor)
        {
            shiva::ranges::for_each(symbols, functor);
        }
    };
}