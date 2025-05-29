#ifndef TIME_H
#define TIME_H

#include <GLFW/glfw3.h>

double get_current_time() {
    return glfwGetTime();
}

#endif //TIME_H
