import sys

from glfw.GLFW import *

from OpenGL.GL import *
from dataclasses import dataclass

import random


@dataclass
class Coord:
    x: float = 0.0
    y: float = 0.0


class Viewport:
    def __init__(self, bounds: Coord, near_depth=100, far_depth=-100):
        self.bounds = bounds
        self.near_depth = near_depth
        self.far_depth = far_depth

    def __call__(self, window, dimensions: Coord):
        if dimensions.y == 0:
            dimensions.y = 1
        if dimensions.x == 0:
            dimensions.x = 1
        aspect_ratio = dimensions.x / dimensions.y

        glMatrixMode(GL_PROJECTION)
        glViewport(0, 0, dimensions.x, dimensions.y)
        glLoadIdentity()

        if dimensions.x <= dimensions.y:
            glOrtho(-self.bounds.x,
                    self.bounds.x,
                    -self.bounds.y / aspect_ratio,
                    self.bounds.y / aspect_ratio,
                    self.near_depth,
                    self.far_depth)
        else:
            glOrtho(-self.bounds.x * aspect_ratio,
                    self.bounds.x * aspect_ratio,
                    -self.bounds.y,
                    -self.bounds.y,
                    self.near_depth,
                    self.far_depth)

        glMatrixMode(GL_MODELVIEW)
        glLoadIdentity()


def make_window(dimensions: Coord, viewport):
    if not glfwInit():
        sys.exit(-1)

    window = glfwCreateWindow(dimensions.x, dimensions.y, __file__, None, None)
    if not window:
        glfwTerminate()
        sys.exit(-1)

    glfwMakeContextCurrent(window)
    glfwSetFramebufferSizeCallback(window, viewport)
    glfwSwapInterval(1)
    return window


def default_init(dimensions: Coord, startup, render, shutdown, viewport, wait_for_event=False):
    window = make_window(dimensions, viewport)
    startup()
    while not glfwWindowShouldClose(window):
        render(glfwGetTime())
        glfwSwapBuffers(window)
        glfwWaitEvents() if wait_for_event else glfwPollEvents()

    shutdown()

    glfwTerminate()


def one_frame_init(dimensions: Coord, startup, shutdown, viewport):
    window = make_window(dimensions, viewport)
    startup()
    glfwSwapBuffers(window)

    while not glfwWindowShouldClose(window):
        glfwPollEvents()

    shutdown()

    glfwTerminate()


def make_rectangle(center: Coord, sides: Coord, color3_array):
    glBegin(GL_TRIANGLE_FAN)

    glColor3fv(color3_array)

    glVertex2f(center.x - (sides.x / 2), center.y + (sides.y / 2))
    glVertex2f(center.x + (sides.x / 2), center.y + (sides.y / 2))
    glVertex2f(center.x + (sides.x / 2), center.y - (sides.y / 2))
    glVertex2f(center.x - (sides.x / 2), center.y - (sides.y / 2))

    glEnd()


def make_distorted_rectangle(center: Coord, sides: Coord, color3_array, d):
    glBegin(GL_TRIANGLE_FAN)

    glColor3fv(color3_array)

    distortions = [1 + (random.random() * (1 if random.random() < 0.5 else -1)) * d for _ in range(4)]

    glVertex2f(center.x - (sides.x / 2) * distortions[0], center.y + (sides.y / 2) * distortions[0])
    glVertex2f(center.x + (sides.x / 2) * distortions[1], center.y + (sides.y / 2) * distortions[1])
    glVertex2f(center.x + (sides.x / 2) * distortions[2], center.y - (sides.y / 2) * distortions[2])
    glVertex2f(center.x - (sides.x / 2) * distortions[3], center.y - (sides.y / 2) * distortions[3])

    glEnd()


def lerp(val1: Coord, val2: Coord, x: float):
    return ((val2.y - val1.y) * x + val2.x * val1.y - val1.x * val2.y) / (val2.x - val1.x)


def axes(x, y, z):
    glBegin(GL_LINES)

    glColor3f(1.0, 0.0, 0.0)
    glVertex3f(-x, 0.0, 0.0)
    glVertex3f(x, 0.0, 0.0)

    glColor3f(0.0, 1.0, 0.0)
    glVertex3f(0.0, -y, 0.0)
    glVertex3f(0.0, y, 0.0)

    glColor3f(0.0, 0.0, 1.0)
    glVertex3f(0.0, 0.0, -z)
    glVertex3f(0.0, 0.0, z)
    glEnd()

def spin(angle):
    glRotatef(angle, 1.0, 0.0, 0.0)
    glRotatef(angle, 0.0, 1.0, 0.0)
    glRotatef(angle, 0.0, 0.0, 1.0)

