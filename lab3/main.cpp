#include "Egg.h"
#include "Terrain.h"

int main()
{
    gk::Egg{}.run(gk::Vector2i {600, 600}, 30);
    return 0;
}
