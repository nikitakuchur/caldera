#include "time.h"

#include <GLFW/glfw3.h>

f64 get_current_time() {
    return glfwGetTime();
}
