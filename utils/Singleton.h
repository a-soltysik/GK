#pragma once

namespace gk::utils
{

template<typename T>
class Singleton
{
public:
    static auto instance() -> T&
    {
        static auto object = T{};
        return object;
    }
protected:
    Singleton() = default;
    Singleton(const Singleton&) = default;
    Singleton(Singleton&&) noexcept = default;
    auto operator=(const Singleton&) -> Singleton& = default;
    auto operator=(Singleton&&)  noexcept -> Singleton& = default;
    ~Singleton() = default;
};

}