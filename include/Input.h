#pragma once

#include "GLFW/glfw3.h"

namespace Input
{
    static bool IsKeyPressed(int keycode) { return glfwGetKey(glfwGetCurrentContext(), keycode) == GLFW_PRESS; }

};
