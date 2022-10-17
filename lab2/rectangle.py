from OpenGL.GL import *

import utils

dimensions = utils.Coord(400, 400)
bounds = utils.Coord(100, 100)
viewport = utils.Viewport(bounds)

background = [0.5, 0.5, 0.5]


def startup():
    glClearColor(background[0], background[1], background[2], 1)
    viewport(None, dimensions)


def shutdown():
    pass


def render(time):
    glClear(GL_COLOR_BUFFER_BIT)
    utils.make_distorted_rectangle(utils.Coord(0, 0), utils.Coord(150, 100), background, 1.0)
    glFlush()


def main():
    utils.default_init(dimensions=dimensions,
                       startup=startup,
                       render=render,
                       shutdown=shutdown,
                       viewport=viewport)


if __name__ == '__main__':
    main()
