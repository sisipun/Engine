#include <pickle/opengl_renderer.h>

#include <fstream>
#include <sstream>

#include <glad/glad.h>

#include <pickle/logger.h>

void checkShaderCompilation(unsigned int shader)
{
    int success;
    char log[1024];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 1024, NULL, log);
        LOG_ERROR("Can't compile shader");
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
        LOG_ERROR("Can't link programm");
    }
}

pickle::renderer::OpenGLRenderer::OpenGLRenderer(SDL_Window *window)
{
    this->window = window;
    context = SDL_GL_CreateContext(window);
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
    {
        LOG_ERROR("Can't load glad module");
    }

    std::ifstream vertexShaderFile("../resource/default.vert");
    if (!vertexShaderFile)
    {
        LOG_ERROR("Can't read vertex file");
    }

    std::ifstream fragmentShaderFile("../resource/default.frag");
    if (!fragmentShaderFile)
    {
        LOG_ERROR("Can't read fragment file");
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

    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vertexShader, 1, &vertexShaderContent, NULL);
    glShaderSource(fragmentShader, 1, &fragmentShaderContent, NULL);
    
    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);

    checkShaderCompilation(vertexShader);
    checkShaderCompilation(fragmentShader);

    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    checkProgramLinking(program);

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.5f, 0.5f, 0.0f};

    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

pickle::renderer::OpenGLRenderer::~OpenGLRenderer()
{
    SDL_GL_DeleteContext(context);
}

void pickle::renderer::OpenGLRenderer::render() const
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(program);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);

    SDL_GL_SwapWindow(window);
}