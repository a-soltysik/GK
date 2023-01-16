#pragma once

#include "Singleton.h"
#include "Texture.h"

#include <deque>
#include <filesystem>
#include <optional>

namespace gk::lab6
{

class TextureCacher : public utils::Singleton<TextureCacher>
{
public:
    auto setMaxTexturesCount(size_t maxTexturesCount) -> void;
    auto loadTexture(const std::filesystem::path& path) -> gfx::Texture*;

private:
    static auto loadExternalTexture(const std::filesystem::path& path) -> std::optional<gfx::Texture>;

    size_t maxTexturesCount = 5;
    std::deque<std::pair<std::filesystem::path, std::unique_ptr<gfx::Texture>>> cache;
};

}
