import random

from OpenGL.GL import *

import utils
import numpy as np
from opensimplex import OpenSimplex

dimensions = utils.Coord(600, 600)
bounds = utils.Coord(100, 100)
viewport = utils.Viewport(bounds, 100, -100)
simplex = OpenSimplex(random.randint(0, 1000))
terrain_bounds = utils.Coord(90, 90)
N = 30
scale = 10
height_scale = 10
velocity = 0.8


def startup():
    glEnable(GL_DEPTH_TEST)
    glClearColor(0.5, 0.5, 0.5, 0.1)
    viewport(None, dimensions)


def shutdown():
    pass


def make_vertices(time):
    vertices = np.zeros((N, N, 3))

    for i in range(N):
        for j in range(N):
            vertices[i][j][0] = utils.lerp(utils.Coord(0, -terrain_bounds.x), utils.Coord(N, terrain_bounds.x), i)
            vertices[i][j][1] = simplex.noise2(i / N * scale + time * velocity,
                                               j / N * scale + time * velocity) * height_scale
            vertices[i][j][2] = utils.lerp(utils.Coord(0, -terrain_bounds.y), utils.Coord(N, terrain_bounds.x), j)

    return vertices


def display_vertices(vertices):
    for i in range(N - 1):
        glBegin(GL_TRIANGLE_STRIP)
        glColor3ubv([255, 128, 170])

        glVertex3fv(vertices[i][0])
        glVertex3fv(vertices[i + 1][0])

        for j in range(N - 1):
            glVertex3fv(vertices[i][j])
            glVertex3fv(vertices[i + 1][j + 1])

        glVertex3fv(vertices[i][N - 1])
        glVertex3fv(vertices[i + 1][N - 1])

        glEnd()


def render(time):
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE)

    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT)
    glLoadIdentity()

    utils.spin(time / 25 * 180 / np.pi)

    display_vertices(make_vertices(time))

    utils.axes(50, 50, 50)

    glFlush()


def main():
    utils.default_init(dimensions=dimensions,
                       startup=startup,
                       render=render,
                       shutdown=shutdown,
                       viewport=viewport)


if __name__ == '__main__':
    main()
