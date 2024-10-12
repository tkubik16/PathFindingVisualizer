#include <Windows.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include <iostream>

#include "resource_manager.h"
#include "box_model.h"
#include "document.h"
#include "program.h"

// GLFW function declarations
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void window_pos_callback(GLFWwindow* window, int xpos, int ypos);
void window_content_scale_callback(GLFWwindow* window, float xscale, float yscale);

// The Width of the screen
unsigned int SCREEN_WIDTH = 1000;
// The height of the screen
unsigned int SCREEN_HEIGHT = 800;
float xscale , yscale;


Program* PathFindingVisualizer;
GLFWmonitor* currentMonitor = NULL;


int main(int argc, char* argv[])
{

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    glfwWindowHint(GLFW_RESIZABLE, true);

    int monitorCount;
    GLFWmonitor** monitors = glfwGetMonitors(&monitorCount);

    xscale = 1.0;
    yscale = 1.0;


    /*
    for (int i = 0; i < monitorCount; i++) {
        glfwGetMonitorContentScale(monitors[i], &xscale, &yscale);
        //std::cout << xscale << " " << yscale << std::endl;
    }
    */
    glfwGetMonitorContentScale(monitors[0], &xscale, &yscale);
    std::cout << "ContentScale: " << std::endl;
    std::cout << xscale << " " << yscale << std::endl;
    //PathFindingVisualizer.UpdateContentScale(xscale, yscale);
    xscale = 1.25;
    yscale = 1.25;
    PathFindingVisualizer = new Program(SCREEN_WIDTH * xscale, SCREEN_HEIGHT * yscale);
    PathFindingVisualizer->UpdateContentScale(xscale, yscale);
    //std::cout << "BeforeWindowCreation: " << PathFindingVisualizer->screenWidth << " " << PathFindingVisualizer->screenHeight << std::endl;
    

    GLFWwindow* window = glfwCreateWindow(PathFindingVisualizer->screenWidth, PathFindingVisualizer->screenHeight, "Path Finding Visualizer", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    

    

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetWindowPosCallback(window, window_pos_callback);
    glfwSetWindowContentScaleCallback(window, window_content_scale_callback);

    // OpenGL configuration
    // --------------------
    glViewport(0, 0, PathFindingVisualizer->screenWidth, PathFindingVisualizer->screenHeight);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // initialize program
    // ---------------
    PathFindingVisualizer->Init();

    // deltaTime variables
    // -------------------
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    //BoxModel box;
    //std::cout << box.content.height << " " << box.content.width << std::endl;
    //std::cout << box.margin.top << " " << box.margin.bottom << std::endl;

    


    while (!glfwWindowShouldClose(window))
    {
        // calculate delta time
        // --------------------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        glfwPollEvents();

        /*
        float fps = 60.0 / deltaTime;
        std::cout << "fps: " << fps << std::endl;
        */

        // manage user input
        // -----------------


        // update program state
        // -----------------


        // render
        // ------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        PathFindingVisualizer->Update(deltaTime);
        PathFindingVisualizer->Render();


        glfwSwapBuffers(window);
    }

    ResourceManager::Clear();
    
    glfwTerminate();
    return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    // when a user presses the escape key, we set the WindowShouldClose property to true, closing the application
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            PathFindingVisualizer->Keys[key] = true;
        else if (action == GLFW_RELEASE)
        {
            PathFindingVisualizer->Keys[key] = false;
            PathFindingVisualizer->KeysProcessed[key] = false;
        }
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    SCREEN_WIDTH = width;
    SCREEN_HEIGHT = height;
    //std::cout << width << ", " << height << std::endl;

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    //PathFindingVisualizer.screenWidth = width;
    //PathFindingVisualizer.screenHeight = height;

    

    // you want to rerender so that as you drag it you see it updating
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    //PathFindingVisualizer.Update();
    PathFindingVisualizer->UpdateScreenSize(width, height);
    PathFindingVisualizer->Render();


    glfwSwapBuffers(window);

}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    //std::cout << xpos << " " << ypos << std::endl;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    //TODO: maybe do the same thing as key presses but with button presses
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        int windowWidth, windowHeight;
        glfwGetWindowSize(window, &windowWidth, &windowHeight);

        int framebufferWidth, framebufferHeight;
        glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);

        double xPos, yPos;
        glfwGetCursorPos(window, &xPos, &yPos);
        //std::cout << xpos << " " << ypos << std::endl;

        // Convert GLFW's screen coordinates to pixel coordinates using the ratio between the window size and the framebuffer size
        double xPosInPixels = xPos * static_cast<double>(framebufferWidth) / windowWidth;
        double yPosInPixels = yPos * static_cast<double>(framebufferHeight) / windowHeight;

        // Shift to use OpenGL's convention of pixel centers being at half-integers
        xPosInPixels += 0.5;
        yPosInPixels += 0.5;

        // Invert along the y-axis
        yPosInPixels = framebufferHeight - yPosInPixels;


        PathFindingVisualizer->SampleBoxBuffer(xPosInPixels, yPosInPixels);
    }
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
        int windowWidth, windowHeight;
        glfwGetWindowSize(window, &windowWidth, &windowHeight);

        int framebufferWidth, framebufferHeight;
        glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);

        double xPos, yPos;
        glfwGetCursorPos(window, &xPos, &yPos);
        //std::cout << xpos << " " << ypos << std::endl;

        // Convert GLFW's screen coordinates to pixel coordinates using the ratio between the window size and the framebuffer size
        double xPosInPixels = xPos * static_cast<double>(framebufferWidth) / windowWidth;
        double yPosInPixels = yPos * static_cast<double>(framebufferHeight) / windowHeight;

        // Shift to use OpenGL's convention of pixel centers being at half-integers
        xPosInPixels += 0.5;
        yPosInPixels += 0.5;

        // Invert along the y-axis
        yPosInPixels = framebufferHeight - yPosInPixels;


        PathFindingVisualizer->SampleBoxBufferRightClick(xPosInPixels, yPosInPixels);
    }
        
}

void window_pos_callback(GLFWwindow* window, int xpos, int ypos) {
    
}

void window_content_scale_callback(GLFWwindow* window, float xscale, float yscale)
{
    std::cout << "window_content_scale_callback" << std::endl;
    std::cout << xscale << " " << yscale << std::endl;
    //PathFindingVisualizer.UpdateContentScale(xscale, yscale);
}