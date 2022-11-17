#include "Egg.h"
#include "Terrain.h"

int main()
{
    gk::Terrain{}.run(gk::Vector2i {600, 600}, 30);
    return 0;
}
