from OpenGL.GL import *

import utils
import numpy as np

dimensions = utils.Coord(600, 600)
bounds = utils.Coord(7.5, 7.5)
viewport = utils.Viewport(bounds, 8, 8)
N = 50
vertices = np.zeros((N, N, 3))


def startup():
    glEnable(GL_DEPTH_TEST)
    glClearColor(0.5, 0.5, 0.5, 0.1)
    viewport(None, dimensions)
    make_egg_vertices()


def shutdown():
    pass


def egg_lines(coord: utils.Coord, color):
    glBegin(GL_LINES)
    glColor3ubv(color)

    glVertex3fv(vertices[coord.x][coord.y])
    glVertex3fv(vertices[coord.x + 1][coord.y])
    glEnd()

    glBegin(GL_LINES)
    glColor3ubv(color)

    glVertex3fv(vertices[coord.x][coord.y])
    glVertex3fv(vertices[coord.x][coord.y + 1])
    glEnd()


def egg_triangles(coord: utils.Coord, color):
    glBegin(GL_TRIANGLES)
    glColor3ubv(color)
    glVertex3fv(vertices[coord.x][coord.y])
    glVertex3fv(vertices[coord.x + 1][coord.y])
    glVertex3fv(vertices[coord.x][coord.y + 1])
    glEnd()

    glBegin(GL_TRIANGLES)
    glColor3ubv(color)
    glVertex3fv(vertices[coord.x + 1][coord.y + 1])
    glVertex3fv(vertices[coord.x + 1][coord.y])
    glVertex3fv(vertices[coord.x][coord.y + 1])
    glEnd()


def egg_strips(i, color):
    glBegin(GL_TRIANGLE_STRIP)
    glColor3ubv(color)
    for j in range(N - 1):
        glVertex3fv(vertices[i][j])
        glVertex3fv(vertices[i + 1][j + 1])
    glVertex3fv(vertices[-1][-1])
    glVertex3fv(vertices[0][0])
    glEnd()


def make_egg_vertices():
    for i in range(N):
        for j in range(N):
            u = i / (N - 1)
            v = j / (N - 1)
            vertices[i][j][0] = (-90 * u ** 5 + 225 * u ** 4 - 270 * u ** 3 + 180 * u ** 2 - 45 * u) * np.cos(np.pi * v)
            vertices[i][j][1] = 160 * u ** 4 - 320 * u ** 3 + 160 * u ** 2 - 5
            vertices[i][j][2] = (-90 * u ** 5 + 225 * u ** 4 - 270 * u ** 3 + 180 * u ** 2 - 45 * u) * np.sin(np.pi * v)


def render(time):
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT)
    glLoadIdentity()

    utils.spin(time * 180 / np.pi)

    utils.axes(6, 6, 6)

    for i in range(N - 1):
        egg_strips(vertices, i, [255, 172, 28])

    glFlush()


def main():
    utils.default_init(dimensions=dimensions,
                       startup=startup,
                       render=render,
                       shutdown=shutdown,
                       viewport=viewport)


if __name__ == '__main__':
    main()
