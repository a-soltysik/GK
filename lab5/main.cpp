#include "Egg.h"
#include "Renderer.h"

int main()
{
    auto renderer = gk::lab5::Renderer{};
    renderer.setScene(std::make_unique<gk::lab5::Scene>());
    renderer.run(gk::Vector2i {600, 600}, false);
    return 0;
}
