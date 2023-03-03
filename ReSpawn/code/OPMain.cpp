
#include "Model.h"
#include <GLFW/glfw3.h>
#include "Camera.h"



void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}


void processInput(GLFWwindow* window)
{
    static unsigned int lastTime = 0;
    auto& camera = Camera::GetInstance();
    camera.SetSpeed((glfwGetTime() - lastTime) * 1);
    lastTime = glfwGetTime();
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        camera.Front();
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
        camera.Back();
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        camera.Left();
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
        camera.Right();
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS){
        camera.Up();
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS){
        camera.Down();
    }
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    static int lastPosX = xpos;
    static int lastPosY = ypos;
    static float yaw = 0;
    static float pitch = 0;
    float sensitivity = 0.05;
    float offsetX = xpos - lastPosX;
    float offsetY = ypos - lastPosY;
    lastPosX = xpos;
    lastPosY = ypos;

    yaw += offsetX * sensitivity;
    pitch += offsetY * sensitivity;

    auto& camera = Camera::GetInstance();
    std::cout << yaw << " " << pitch << '\n';
    camera.MouseMove(yaw, pitch);
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }


    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    glViewport(0, 0, 800, 600);

    Model mnanModel("E:/ReSpawn/ReSpawn/resource/nanosuit/nanosuit.obj");

    Shader actorShader("E:/ReSpawn/ReSpawn/Shader/vertex_shader001", "E:/ReSpawn/ReSpawn/Shader/fragment_shader001");
    actorShader.Bind();
    glm::mat4 modelMat(1.f);
    {
        glm::vec3 trans(0.f, 0.f, 0.f);
        modelMat = glm::translate(modelMat, trans);
        //modelMat = glm::rotate(modelMat, glm::radians(0.f), glm::vec3(1.f, 0.f, 0.f));
        //modelMat = glm::scale(modelMat, glm::vec3(1.f, 1.f, 1.f));
        unsigned int location = glGetUniformLocation(actorShader.ID, "ModelMat");
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(modelMat));
    }

    {
        auto orthogonal =  glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);
        glm::mat4 proj = glm::perspective(glm::radians(90.0f), (float)800.f / (float)600.f, 0.1f, 1000.0f);
        unsigned int location = glGetUniformLocation(actorShader.ID, "ProjMat");
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(proj));
    }

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    /* Loop until the user closes the window */
    glEnable(GL_DEPTH_TEST);
    //glDepthMask(GL_FALSE);forbid depth write
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        actorShader.Bind();
        glm::mat4 view = Camera::GetInstance().GetLookAt();
        unsigned int location = glGetUniformLocation(actorShader.ID, "ViewMat");
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(view));
        mnanModel.Draw(actorShader);
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}


/*
float currentFrame = glfwGetTime();
deltaTime = currentFrame - lastFrame;
lastFrame = currentFrame;
*/