#include "Clock.h"

namespace gk::utils
{

auto Clock::start() noexcept -> void
{
    startPoint = std::chrono::high_resolution_clock::now();
}

auto Clock::stop() noexcept -> void
{
    stopPoint = std::chrono::high_resolution_clock::now();
}

}