// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

int main(void)
{
    GLFWwindow *window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__  //                                                  Mac Specific -----|
    std::cout << "I'm apple machine" << std::endl; //                                   |
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //                             |
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);//                                         |
#endif // <----------------------------------------------------------------------------|

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(960, 540, "Hello World", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GL Version: " << (char *)glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    {

        float positions[] = {
            100.0f , 100.0f  , 0.0f , 0.0f, // 0
            200.5f , 100.0f  , 1.0f , 0.0f, // 1
            200.0f ,  200.0f  , 1.0f , 1.0f, // 2
            100.0f ,  200.0f  , 0.0f , 1.0f  // 3
        };

        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0};

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        VertexArray va;
        VertexBuffer vb(positions, 4 * 4 * sizeof(float));

        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        va.AddBuffer(vb , layout);

        IndexBuffer ib(indices, 6);

        // glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);
        glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f,540.0f, -1.0f, 1.0f);
        glm::vec4 vp(100.0f, 100.0f, 0.0f, 1.0f);

        glm::vec4 result = proj * vp;

        Shader shader("res/shaders/Basic.shader");
        shader.Bind();
        shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);

        shader.SetUniformMat4f("u_MVP", proj);

        Texture texture("res/textures/windows_logo.png");
        texture.Bind();
        shader.SetUniform1i("u_Texture", 0);

        va.Unbind();
        vb.Unbind();
        ib.Unbind();
        shader.Unbind();

        float r = 0.0f;
        float increment = 0.05f;

        Renderer renderer;

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            renderer.Clear();

            // glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // changes color of screen

            // shader.SetUniform4f("bgColor", 0.2f, 0.3f, 0.3f, 1.0f);

            shader.Bind();
            shader.SetUniform4f("u_Color",r, 0.3f, 0.8f, 1.0f);

            renderer.Draw(va, ib, shader); // draw the triangle
            GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

            if (r >= 1.0f)
                increment = -0.05f;
            else if (r <= 0.0f)
                increment = 0.05f;

            r += increment;

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }
    glfwTerminate();

    return 0;
}