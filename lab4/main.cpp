#include "Renderer.h"
#include "Egg.h"

int main()
{
    auto renderer = gk::lab4::Renderer{};
    renderer.setObject(std::make_unique<gk::lab4::Egg>(gk::lab4::Egg{30}));
    renderer.run(gk::Vector2i {600, 600}, false);
    return 0;
}
