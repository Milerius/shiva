//
// Created by roman Sztergbaum on 11/08/2018.
//

#include <system_error>
#include <shiva/error/shiva_error_code.hpp>

namespace
{
    struct shiva_err_category : std::error_category
    {
        const char *name() const noexcept override;
        std::string message(int ev) const override;
    };

    const char *shiva_err_category::name() const noexcept
    {
        return "shiva";
    }

    std::string shiva_err_category::message(int ev) const
    {
        switch (static_cast<shiva::error::code>(ev)) {
            case shiva::error::code::get_system_error:
                return "get_system error, maybe are you trying to get an unregistered system";

            default:
                return "(unrecognized error)";
        }
    }

    const shiva_err_category the_shiva_error_category{};
}

std::error_code make_error_code(shiva::error::code e)
{
    return {static_cast<int>(e), the_shiva_error_category};
}