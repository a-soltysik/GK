#pragma once

#include <chrono>

namespace gk::utils
{

class Clock
{
public:
    using Time = int64_t;
    auto start() noexcept -> void ;
    auto stop() noexcept -> void;

    template<typename DurationType>
    [[nodiscard]]
    auto getTime() const -> int64_t
    {
        return std::chrono::duration_cast<DurationType>(stopPoint - startPoint).count();
    }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> startPoint;
    std::chrono::time_point<std::chrono::high_resolution_clock> stopPoint;
};

}