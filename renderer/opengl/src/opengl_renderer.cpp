#include <pickle/opengl_renderer.h>

#include <fstream>
#include <sstream>

#include <glad/glad.h>

#include <pickle/logger.h>
#include <pickle/math.h>

void checkShaderCompilation(unsigned int shader)
{
    int success;
    char log[1024];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 1024, NULL, log);
        LOG_ERROR("Can't compile shader");
        LOG_ERROR(log);
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
        LOG_ERROR(log);
    }
}

pickle::renderer::OpenGLRenderer::OpenGLRenderer(SDL_Window *window, int width, int height) : window(window)
{
    context = SDL_GL_CreateContext(window);
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
    {
        LOG_ERROR("Can't load glad module");
    }

    std::ifstream vertexShaderFile("resource/default.vert");
    if (!vertexShaderFile)
    {
        LOG_ERROR("Can't read vertex file");
    }

    std::ifstream fragmentShaderFile("resource/default.frag");
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
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f,

        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,

        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,

        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,  0.0f, 1.0f, 1.0f};

    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void *) (6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}

pickle::renderer::OpenGLRenderer::~OpenGLRenderer()
{
    SDL_GL_DeleteContext(context);
}

void pickle::renderer::OpenGLRenderer::render() const
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(program);

    int lightDirectionUniform = glGetUniformLocation(program, "lightDirection");
    pickle::math::Vector<3, float> lightDirection = pickle::math::Vector<3, float>({1.0f, -1.0f, -1.0f});
    int cameraPositionUniform = glGetUniformLocation(program, "cameraPosition");
    pickle::math::Vector<3, float> cameraPosition = pickle::math::Vector<3, float>({-1.0f, 1.0f, -1.0f});
    int modelUniform = glGetUniformLocation(program, "model");
    pickle::math::Matrix<4, 4, float> modelMatrix = pickle::math::Matrix<4, 4, float>({
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    });
    int viewUniform = glGetUniformLocation(program, "view");
    pickle::math::Matrix<4, 4, float> viewMatix = pickle::math::lookAt(
        cameraPosition,
        pickle::math::Vector<3, float>({0.0f, 0.0f, 0.0f}),
        pickle::math::Vector<3, float>({0.0f, 1.0f, 0.0f}));
    int projectionUniform = glGetUniformLocation(program, "projection");
    pickle::math::Matrix<4, 4, float> projectionMatrix = pickle::math::perspective(
        pickle::math::radians(90.0f), 
        800.0f / 600.0f,
        0.01f, 
        100.0f);
    
    glUniform3f(lightDirectionUniform, lightDirection.data[0], lightDirection.data[1], lightDirection.data[2]);
    glUniform3f(cameraPositionUniform, cameraPosition.data[0], cameraPosition.data[1], cameraPosition.data[2]);
    glUniformMatrix4fv(modelUniform, 1, GL_FALSE, transpose(modelMatrix).data);
    glUniformMatrix4fv(viewUniform, 1, GL_FALSE, transpose(viewMatix).data);
    glUniformMatrix4fv(projectionUniform, 1, GL_FALSE, transpose(projectionMatrix).data);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);

    SDL_GL_SwapWindow(window);
}