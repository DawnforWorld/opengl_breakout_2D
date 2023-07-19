#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "check_gl.hpp" // includes glad/glad.h
#include <GLFW/glfw3.h> // must be placed behind glad/glad.h
#include <stdexcept>
#include <iostream>
#include <cstring>
#include <cstdlib>

static void draw_circle(const glm::vec3& color, float radius, const glm::mat4& model) {
    glColor3f(color[0], color[1], color[2]);

    constexpr int n = 100;
    constexpr float pi = 3.1415926535897f;

    float inner_radius = radius / 2;

    for (int i = 0; i < n; i++) {
        float angle = i / (float)n * (pi * 2 - pi / 3);
        float angle_next = (i + 1) / (float)n * (pi * 2 - pi / 3);

        glm::vec4 point0 = { inner_radius * sinf(angle), inner_radius * cosf(angle), 0.0f, 1.0f };
        glm::vec4 point1 = { radius * sinf(angle), radius * cosf(angle), 0.0f, 1.0f };
        glm::vec4 point2 = { radius * sinf(angle_next), radius * cosf(angle_next), 0.0f, 1.0f };
        glm::vec4 point3 = { inner_radius * sinf(angle_next), inner_radius * cosf(angle_next), 0.0f, 1.0f };

        point0 = model * point0;
        point1 = model * point1;
        point2 = model * point2;
        point3 = model * point3;

        glVertex3f(point0[0], point0[1], point0[2]);
        glVertex3f(point1[0], point1[1], point1[2]);
        glVertex3f(point2[0], point2[1], point2[2]);

        glVertex3f(point0[0], point0[1], point0[2]);
        glVertex3f(point2[0], point2[1], point2[2]);
        glVertex3f(point3[0], point3[1], point3[2]);
    }
}

static void render() {
    glBegin(GL_TRIANGLES);

    constexpr float pi = 3.1415926535897f;
    {
        glm::mat4 model = glm::mat4(1.0f);

        model = glm::translate(model, { 0.0f, 0.5f, 0.0f });
        model = glm::rotate(model, glm::radians(150.0f), { 0.0f, 0.0f, 1.0f });

        draw_circle({ 1.0f, 0.0f, 0.0f }, 0.5f, model);
    }

    float n = sqrt(0.25);
    {
        glm::mat4 model = glm::mat4(1.0f);

        model = glm::translate(model, { -n, -n, 0.0f });
        model = glm::rotate(model, glm::radians(-90.0f), { 0.0f, 0.0f, 1.0f });

        draw_circle({ 0.0f, 1.0f, 0.0f }, 0.5f, model);
    }

    {
        glm::mat4 model = glm::mat4(1.0f);

        model = glm::translate(model, { n, -n, 0.0f });
        model = glm::rotate(model, glm::radians(-30.0f), { 0.0f, 0.0f, 1.0f });

        draw_circle({ 0.0f, 0.0f, 1.0f }, 0.5f, model);
    }

    CHECK_GL(glEnd());
}

int main() {
    if (!glfwInit()) {
        const char *errmsg;
        glfwGetError(&errmsg);
        if (!errmsg) errmsg = "(no error)";
        std::cerr << "failed to initialize GLFW: " << errmsg << '\n';
        return -1;
    }

    // hint the version required: OpenGL 2.0
    constexpr int version = 20;
    glfwWindowHint(GLFW_OPENGL_API, GLFW_OPENGL_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, version / 10);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, version % 10);
    if (version >= 33) {
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    }

    // Create window
    GLFWwindow *window = glfwCreateWindow(640, 640, "Example", NULL, NULL);
    if (!window) {
        const char *errmsg;
        glfwGetError(&errmsg);
        if (!errmsg) errmsg = "(no error)";
        std::cerr << "GLFW failed to create window: " << errmsg << '\n';
        std::cerr << "==============================================\n";
        if (!strcmp(errmsg, "X11: The DISPLAY environment variable is missing")) {
            std::cerr << "You seems not running with graphic display\n";
        } else if (!strcmp(errmsg, "WGL: The driver does not appear to support OpenGL")) {
            std::cerr << "Please consider install an OpenGL driver, or use the mesa driver\n";
        } else if (!strcmp(errmsg, "WGL: Failed to create OpenGL context")) {
            std::cerr << "Your driver seems not supporting the required OpenGL version\n";
        }
        std::cerr << "- If you have a physical graphic card (e.g. NVIDIA), install it from your graphic card vendor official website: http://www.nvidia.com/Download/index.aspx\n";
        std::cerr << "- If you are using Windows, download opengl32.dll from https://pan.baidu.com/s/1TZ6nVJC7DZIuUarZrGJYow?pwd=opgl and place it into the same directory as this executable file (alternatively you may download opengl32sw.dll from Internet and rename it to opengl32.dll to place into the same directory as this executable file)\n";
        std::cerr << "- If you are using Linux or WSL1, install the mesa driver: https://ubuntuhandbook.org/index.php/2021/07/install-latest-mesa-ubuntu-20-04-21-04/";
        std::cerr << "- If you use WSL2, install WSLg: https://learn.microsoft.com/zh-cn/windows/wsl/tutorials/gui-apps\n";
        std::cerr << "- If you are using SSH remote server, try connect it using ssh -X <ip address>\n";
        std::cerr << "- If you are using MacOS, you probably want to use Windows or Linux instead for better OpenGL support\n";
        std::cerr << "- If you are using a Laptop with dual-cards, make sure you have switch to dedicated card (NVIDIA) instead of the integrated card (Intel)\n";
        std::cerr << "==============================================\n";
#ifdef _WIN32
        std::system("pause");
#endif
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Load glXXX function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        glfwTerminate();
        std::cerr << "GLAD failed to load GL functions\n";
        return -1;
    }
    std::cerr << "OpenGL version: " << glGetString(GL_VERSION) << '\n';

    CHECK_GL(glEnable(GL_POINT_SMOOTH));
    CHECK_GL(glEnable(GL_BLEND));
    CHECK_GL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    CHECK_GL(glPointSize(64.0f));

    // start main game loop
    while (!glfwWindowShouldClose(window)) {
        // render graphics
        CHECK_GL(glClear(GL_COLOR_BUFFER_BIT));
        render();
        // refresh screen
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
