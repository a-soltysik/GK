from OpenGL.GL import *

import utils
import math

dimensions = utils.Coord(400, 400)
bounds = utils.Coord(dimensions.x / 2, dimensions.y / 2)
viewport = utils.Viewport(bounds)

background = [0.5, 0.5, 0.5]


def startup():
    glClearColor(background[0], background[1], background[2], 0)
    viewport(None, dimensions)
    make_mandelbrot_set(-2.0, 1.0, 1.5, -1.5)


def shutdown():
    pass


def is_convergent(point: utils.Coord, max_steps=50):
    z = complex(0, 0)
    p = complex(point.x, point.y)
    for _ in range(max_steps):
        z = z ** 2 + p
        if math.sqrt(z.real ** 2 + z.imag ** 2) >= 2:
            return False
    return True


def make_mandelbrot_set(left, right, top, bottom):
    glColor3ub(255, 0, 0)
    glBegin(GL_POINTS)
    for x in range(int(dimensions.x)):
        for y in range(int(dimensions.y)):
            coord = utils.Coord(left + (x * (right - left) / dimensions.x),
                                top + (y * (bottom - top) / dimensions.y))
            if is_convergent(coord):
                glVertex2i(int(x - bounds.x), int(y - bounds.y))

    glEnd()


def main():
    utils.one_frame_init(dimensions=dimensions,
                         startup=startup,
                         shutdown=shutdown,
                         viewport=viewport)


if __name__ == '__main__':
    main()
