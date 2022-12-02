#include "Triangle.h"
#include "Rectangle.h"
#include "Sierpinski.h"
#include "Mandelbrot.h"

int main()
{
    gk::lab2::Mandelbrot{}.run(gk::Vector2i {800, 800});
    return 0;
}
