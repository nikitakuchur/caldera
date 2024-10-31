#include <GLFW/glfw3.h>
#include <stdio.h>

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    printf("key: %d\n", key);
}

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    printf("mouse button: %d\n", button);
}

int main() {
    if (!glfwInit()) {
        return -1;
    }

    GLFWwindow *window = glfwCreateWindow(640, 480, "Game", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwSetKeyCallback(window, &key_callback);
    glfwSetMouseButtonCallback(window, &mouse_button_callback);
    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        //glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
