//
// Created by roman Sztergbaum on 10/06/2018.
//

#pragma once

#include <functional>
#include <boost/dll.hpp>
#include <shiva/filesystem/filesystem.hpp>
#include <shiva/spdlog/spdlog.hpp>

namespace shiva::helpers
{
    namespace dll = boost::dll;

    static inline bool is_shared_library(const fs::path &p)
    {
        const std::string &s = p.string();
        return (s.find(".dll") != std::string::npos || s.find(".so") != std::string::npos ||
                s.find(".dylib") != std::string::npos
                || s.find(".bc") != std::string::npos)
               && s.find(".lib") == std::string::npos
               && s.find(".exp") == std::string::npos
               && s.find(".pdb") == std::string::npos
               && s.find(".manifest") == std::string::npos
               && s.find(".rsp") == std::string::npos
               && s.find(".obj") == std::string::npos
               && s.find(".a") == std::string::npos;
    }

    template <typename CreatorSignature>
    class plugins_registry
    {
    public:
        using symbols_container = std::vector<std::function<CreatorSignature>>;

    private:
        symbols_container symbols;
        shiva::fs::path plugins_directory_;
        shiva::logging::logger log_{shiva::log::stdout_color_mt("plugins_registry")};

    public:
        explicit plugins_registry(shiva::fs::path &&plugins_directory) noexcept :
            plugins_directory_{plugins_directory}
        {
            log_->info("plugins_registry directory: {}", plugins_directory.string());
            log_->info("plugins_registry successfully created.");
        }

        bool load_all_symbols() noexcept
        {
            bool res{true};
            if (!fs::exists(plugins_directory_))
                return false;
            fs::recursive_directory_iterator endit;
            for (fs::recursive_directory_iterator it(plugins_directory_); it != endit; ++it) {
                if (!fs::is_regular_file(*it) ||
                    !is_shared_library((*it).path()) ||
                    (*it).path().filename().stem().string().find("shiva-system") == std::string::npos) {
                    continue;
                }
                try {
                    symbols.emplace_back(
                        boost::dll::import_alias<CreatorSignature>(
                            boost::filesystem::path(it->path().string()),
                            "create_plugin",
                            dll::load_mode::append_decorations
                        ));
                    log_->info("Successfully loaded: {}", it->path().filename().string());
                }
                catch (const boost::system::system_error &error) {
                    log_->error("error loading: {0} -> {1}", it->path().filename().string(), error.what());
                    res = false;
                }
            }
            return res;
        }

        size_t nb_plugins() const noexcept
        {
            return symbols.size();
        }

        template <typename Functor>
        void apply_on_each_symbols(Functor &&functor)
        {
            shiva::ranges::for_each(symbols, functor);
        }
    };
}