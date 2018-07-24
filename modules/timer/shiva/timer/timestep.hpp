//
// Created by roman Sztergbaum on 18/06/2018.
//

#pragma once

#include <chrono>
#include <shiva/timer/fps.hpp>

namespace shiva::timer
{
    class time_step
    {
    public:
        void start() noexcept
        {
            start_ = clock::now();
        }

        void start_frame() noexcept
        {
            auto deltaTime = clock::now() - start_;
            start_ = clock::now();
            lag_ += std::chrono::duration_cast<std::chrono::nanoseconds>(deltaTime);
        }

        bool is_update_required() const noexcept
        {
            return (lag_ >= fps_);
        }

        void perform_update() noexcept
        {
            lag_ -= fps_;
        }

        const float &get_fixed_delta_time() const noexcept
        {
            return fixed_delta_time;
        }

    private:
        using clock = std::chrono::steady_clock;
        std::chrono::nanoseconds lag_{0ns};
        std::chrono::nanoseconds fps_{_60fps};
        float fixed_delta_time{std::chrono::duration<float, std::ratio<1>>(fps_).count()};
        clock::time_point start_{clock::now()};
    };
}
