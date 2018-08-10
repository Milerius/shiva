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

    /**
     * \note check if the path passed in parameter is a shared library
     * \fn bool is_shared_library(const fs::path& p) noexcept
     * \param p the path to be tested
     * \return true if the path is a shared_library, false otherwise.
     */
    static inline bool is_shared_library(const fs::path &p) noexcept;

    /**
     * \note This class allows you to store plugin creation symbols through its template CreatorSignature parameter.
     * \note Through this class you are able to retrieve the number of plugins,
     * apply a functor on each of the symbols (as creates the plugin for example).
     * \class plugins_registry
     * \tparam CreatorSignature Represents the signature of the creator function of a shared library
     */
    template <typename CreatorSignature>
    class plugins_registry
    {
    public:
        //! Public typedefs

        /**
         * \typedef Shortcut representing a collection of shared library creator function.
         */
        using symbols_container = std::vector<std::function<CreatorSignature>>;

        //! Constructors

        /**
         * \note Basic constructor
         * \param plugins_directory represents the path to the directory containing the plugins
         * \param library_pattern_matching represents a basic pattern to respect for libraries to load
         * \example for example if the pattern is [shiva-system] then only libraries that have [shiva-system]
         * in their names will be loaded. [libshiva-system-plugin.so] will be loaded [libother-things.so] will not be
         * loaded.
         */
        explicit plugins_registry(shiva::fs::path &&plugins_directory, const std::string library_pattern_matching) noexcept;

        //! Public member functions

        /**
         * \return true if all symbols have been correctly loaded, false otherwise
         * \note This function allows you to load symbols from the template to create the object.
         * \note The symbols are loaded recursively from the folder you specified in the object's constructor.
         * \warning If one of the symbols could not be correctly loaded the function does not stop and proceeds to load the next plugin.
         * \warning If when browsing folders a corrupted file is spotted the function switch to loading the next plugin.
         */
        inline bool load_all_symbols() noexcept;

        /**
         * \return numbers of loaded plugins
         */
        inline size_t nb_plugins() const noexcept;

        /**
         * \tparam Functor Represents the functor to apply on each of the loaded symbols.
         * \note This function applies the functor as a parameter to each of the symbols
         *  that were previously loaded by the load_all_symbols function.
         */
        template <typename Functor>
        void apply_on_each_symbols(Functor &&functor);

    private:
        //! Private data members
        symbols_container symbols{};
        shiva::fs::path plugins_directory_{};
        const std::string plugins_library_pattern_matching_{};
        shiva::logging::logger log_{shiva::log::stdout_color_mt("plugins_registry")};
    };
}

//! Helpers Functions
namespace shiva::helpers
{
    bool is_shared_library(const fs::path &p) noexcept
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
}

//! plugins_registry implementation
namespace shiva::helpers
{
    //! Constructor
    template <typename CreatorSignature>
    plugins_registry<CreatorSignature>::plugins_registry(shiva::fs::path &&plugins_directory,
                                                         const std::string library_pattern_matching) noexcept :
        plugins_directory_{plugins_directory},
        plugins_library_pattern_matching_{std::move(library_pattern_matching)}
    {
        log_->info("plugins_registry directory: {}", plugins_directory.string());
        log_->info("plugins_registry successfully created.");
    }

    //! Public member functions
    template <typename CreatorSignature>
    bool plugins_registry<CreatorSignature>::load_all_symbols() noexcept
    {
        bool res{true};
        if (!fs::exists(plugins_directory_))
            return false;
        fs::recursive_directory_iterator endit;
        for (fs::recursive_directory_iterator it(plugins_directory_); it != endit; ++it) {
            if (!fs::is_regular_file(*it) ||
                !is_shared_library((*it).path()) ||
                (*it).path().filename().stem().string().find(plugins_library_pattern_matching_) == std::string::npos) {
                continue;
            }
            try {
                log_->info("path -> {}", it->path().string());
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

    template <typename CreatorSignature>
    size_t plugins_registry<CreatorSignature>::nb_plugins() const noexcept
    {
        return symbols.size();
    }

    template <typename CreatorSignature>
    template <typename Functor>
    void plugins_registry<CreatorSignature>::apply_on_each_symbols(Functor &&functor)
    {
        shiva::ranges::for_each(symbols, functor);
    }
}
