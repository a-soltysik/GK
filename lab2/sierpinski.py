from OpenGL.GL import *

import utils

dimensions = utils.Coord(1000, 1000)
bounds = utils.Coord(100, 100)
viewport = utils.Viewport(bounds)

background = [0.9, 0.9, 0.9]


def startup():
    glClearColor(background[0], background[1], background[2], 1)
    viewport(None, dimensions)


def shutdown():
    pass


def make_sierpinski_carpet(center: utils.Coord, sides: utils.Coord, level):
    if level <= 0:
        return

    new_sides = utils.Coord(sides.x / 3, sides.y / 3)

    utils.make_rectangle(center, sides, [0.5, 0.3, 0.6])
    utils.make_rectangle(center, new_sides, background)

    make_sierpinski_carpet(utils.Coord(center.x - new_sides.x, center.y + new_sides.y), new_sides, level - 1)
    make_sierpinski_carpet(utils.Coord(center.x, center.y + new_sides.y), new_sides, level - 1)
    make_sierpinski_carpet(utils.Coord(center.x + new_sides.x, center.y + new_sides.y), new_sides, level - 1)
    make_sierpinski_carpet(utils.Coord(center.x + new_sides.x, center.y), new_sides, level - 1)
    make_sierpinski_carpet(utils.Coord(center.x + new_sides.x, center.y - new_sides.y), new_sides, level - 1)
    make_sierpinski_carpet(utils.Coord(center.x, center.y - new_sides.y), new_sides, level - 1)
    make_sierpinski_carpet(utils.Coord(center.x - new_sides.x, center.y - new_sides.y), new_sides, level - 1)
    make_sierpinski_carpet(utils.Coord(center.x - new_sides.x, center.y), new_sides, level - 1)


def render(time):
    glClear(GL_COLOR_BUFFER_BIT)
    make_sierpinski_carpet(utils.Coord(0, 0), utils.Coord(200, 200), 5)
    glFlush()


def main():
    utils.default_init(dimensions=dimensions,
                       startup=startup,
                       render=render,
                       shutdown=shutdown,
                       viewport=viewport)


if __name__ == '__main__':
    main()
