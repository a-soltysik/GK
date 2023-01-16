#include "TextureCacher.h"

#include <algorithm>
#include <fstream>

namespace gk::lab6
{

auto TextureCacher::setMaxTexturesCount(size_t maxTexturesCount) -> void
{
    this->maxTexturesCount = maxTexturesCount;
}

auto TextureCacher::loadTexture(const std::filesystem::path& path) -> gfx::Texture*
{
    const auto it = std::ranges::find_if(cache,
        [&path](const auto& current) {
            return std::filesystem::equivalent(current, path);
        }, &std::pair<std::filesystem::path, std::unique_ptr<gfx::Texture>>::first);

    if (it != cache.cend())
    {
        return it->second.get();
    }
    else
    {
        auto newTexture = loadExternalTexture(path);
        if (newTexture)
        {
            cache.emplace_back(path, std::make_unique<gfx::Texture>(std::move(newTexture.value())));

            if (cache.size() > maxTexturesCount)
            {
                cache.pop_front();
            }

            return cache.back().second.get();
        }

        return nullptr;
    }
}

auto TextureCacher::loadExternalTexture(const std::filesystem::path& path) -> std::optional<gfx::Texture>
{
    struct TgaFile
    {
        uint8_t imageTypeCode;
        uint16_t imageWidth;
        uint16_t imageHeight;
        uint8_t bitCount;
        std::vector<uint8_t> imageData;
    };

    auto fin = std::ifstream{path, std::ios::binary};

    if (!fin.good())
    {
        return {};
    }

    auto tga = TgaFile{};

    fin.ignore(2 * sizeof(uint8_t));
    fin.read(reinterpret_cast<char *>(&tga.imageTypeCode), sizeof(uint8_t));

    if (tga.imageTypeCode != 2 && tga.imageTypeCode != 3)
    {
        return {};
    }

    fin.ignore(9 * sizeof(char));
    fin.read(reinterpret_cast<char *>(&tga.imageWidth), sizeof(uint16_t));
    fin.read(reinterpret_cast<char *>(&tga.imageHeight), sizeof(uint16_t));
    fin.read(reinterpret_cast<char *>(&tga.bitCount), sizeof(uint8_t));

    fin.ignore(sizeof(char));

    const auto colorMode = tga.bitCount / 8u;
    const auto imageSize = size_t{tga.imageWidth} * size_t{tga.imageHeight} * size_t{colorMode};

    tga.imageData.resize(imageSize);

    fin.read(reinterpret_cast<char *>(tga.imageData.data()),
             static_cast<std::streamsize>(imageSize * sizeof(uint8_t)));

    for (auto i = size_t{0}; i < tga.imageData.size(); i += colorMode)
    {
        std::swap(tga.imageData[i], tga.imageData[i + 2]);
    }

    return {{
                tga.imageWidth,
                tga.imageHeight,
                colorMode == 3 ? GL_RGB8 : GL_RGBA8,
                static_cast<GLenum>(colorMode == 3 ? GL_RGB : GL_RGBA),
                std::move(tga.imageData)
            }};
}

}