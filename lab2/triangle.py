from OpenGL.GL import *

import math
import utils

dimensions = utils.Coord(400, 400)
bounds = utils.Coord(100, 100)
viewport = utils.Viewport(bounds)


def startup():
    glClearColor(0.5, 0.5, 0.5, 0.1)
    viewport(None, dimensions)


def shutdown():
    pass


def make_triangle(side):
    height = side * math.sqrt(3) / 2

    glBegin(GL_TRIANGLES)
    glColor3f(1.0, 0.0, 0.0)
    glVertex2f(-side / 2, -height / 2)

    glColor3f(0.0, 1.0, 0.0)
    glVertex2f(side / 2, -height / 2)

    glColor3f(0.0, 0.0, 1.0)
    glVertex2f(0.0, height / 2)
    glEnd()


def render(time):
    glClear(GL_COLOR_BUFFER_BIT)
    make_triangle(200)
    glFlush()


def main():
    utils.default_init(dimensions=dimensions,
                       startup=startup,
                       render=render,
                       shutdown=shutdown,
                       viewport=viewport)


if __name__ == '__main__':
    main()
