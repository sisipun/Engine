#include <SDL.h>
#include <glad/glad.h>

#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <numbers>

#include <pickle/vector.h>

float randomFloatNegative()
{
    return ((static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2)) - 1.0f) * 0.5f;
}

void checkShaderCompilation(unsigned int shader)
{
    int success;
    char log[1024];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 1024, NULL, log);
        std::cout << "Can't compile shader: " << log << std::endl;
    }
}

void checkProgramLinking(unsigned int program)
{
    int success;
    char log[1024];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(program, 1024, NULL, log);
        std::cout << "Can't link programm: " << log << std::endl;
    }
}

int main(int argc, char *argv[])
{
    float width = 800;
    float height = 600;
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Can't load SDL module" << std::endl;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_Window *window = SDL_CreateWindow("Animation", SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED, width, height,
                                          SDL_WINDOW_OPENGL);
    if (window == nullptr)
    {
        std::cout << "Can't create window" << std::endl;
    }

    SDL_GLContext context = SDL_GL_CreateContext(window);
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
    {
        std::cout << "Can't load glad module" << std::endl;
    }

    std::ifstream vertexShaderFile("../resource/shader.vert");
    std::ifstream fragmentShaderFile("../resource/tunnel.frag");

    if (!vertexShaderFile)
    {
        std::cout << "Can't read vertex file" << std::endl;
    }
    if (!fragmentShaderFile)
    {
        std::cout << "Can't read fragment file" << std::endl;
    }

    std::stringstream vertexShaderContentStream;
    std::stringstream fragmentShaderContentStream;

    vertexShaderContentStream << vertexShaderFile.rdbuf();
    fragmentShaderContentStream << fragmentShaderFile.rdbuf();

    vertexShaderFile.close();
    fragmentShaderFile.close();

    std::string vertexShaderContentString = vertexShaderContentStream.str();
    std::string fragmentShaderContentString = fragmentShaderContentStream.str();

    const char *vertexShaderContent = vertexShaderContentString.c_str();
    const char *fragmentShaderContent = fragmentShaderContentString.c_str();

    int vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    int fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vertexShaderId, 1, &vertexShaderContent, NULL);
    glShaderSource(fragmentShaderId, 1, &fragmentShaderContent, NULL);

    glCompileShader(vertexShaderId);
    glCompileShader(fragmentShaderId);

    checkShaderCompilation(vertexShaderId);
    checkShaderCompilation(fragmentShaderId);

    int shaderProgramId = glCreateProgram();
    glAttachShader(shaderProgramId, vertexShaderId);
    glAttachShader(shaderProgramId, fragmentShaderId);
    glLinkProgram(shaderProgramId);
    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);

    checkProgramLinking(shaderProgramId);

    float vertices[] = {
        -1.0f, -1.0f, 0.0f,
        -1.0f, 1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        -1.0f, 1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        1.0f, 1.0f, 0.0f};

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    bool quit = false;
    SDL_Event event;
    int mouseX, mouseY;

    float angle = 0.0f;
    const float rotationRadius = 0.1;
    const float angleStep = std::numbers::pi / 18.0;
    pickle::math::Vector<2, float> center({0.0f, 0.0f});

    std::vector<pickle::math::Vector<3, float>> circles;
    for (int i = 0; i < 20; i++)
    {
        center.data[0] = sin(angle) * rotationRadius;
        center.data[1] = cos(angle) * rotationRadius;
        circles.push_back(pickle::math::Vector<3, float>({center.data[0], center.data[1], (i * 1.0f / 20)}));
        angle += angleStep;
    }

    float speed = 0.002f;
    while (!quit)
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        SDL_GetMouseState(&mouseX, &mouseY);

        glUseProgram(shaderProgramId);
        int resolutionUniformId = glGetUniformLocation(shaderProgramId, "u_resolution");
        glUniform2f(resolutionUniformId, width, height);
        int timeUniformId = glGetUniformLocation(shaderProgramId, "u_time");
        glUniform1f(timeUniformId, SDL_GetTicks());
        int mouseUniformId = glGetUniformLocation(shaderProgramId, "u_mouse");
        glUniform2f(mouseUniformId, mouseX, mouseY);

        for (int i = 0; i < circles.size(); i++)
        {
            pickle::math::Vector<3, float> &circle = circles[i];
            circle.data[2] -= speed;
            if (circle.data[2] < 0.0f)
            {
                center.data[0] = sin(angle) * rotationRadius;
                center.data[1] = cos(angle) * rotationRadius;

                circle.data[0] = center.data[0];
                circle.data[1] = center.data[1];
                circle.data[2] = 1.0f;
                angle += angleStep;
            }

            int circleId = glGetUniformLocation(shaderProgramId, ("u_circles[" + std::to_string(i) + "]").c_str());
            glUniform3f(circleId, circle.data[0], circle.data[1], circle.data[2]);
        }

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);

        if (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
            }
        }
        SDL_GL_SwapWindow(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgramId);

    SDL_GL_DeleteContext(context);
    SDL_Quit();
}