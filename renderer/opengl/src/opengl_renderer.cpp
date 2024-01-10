#include <pickle/opengl_renderer.h>

#include <fstream>
#include <sstream>

#include <glad/glad.h>

#include <pickle/logger.h>
#include <pickle/math.h>
#include <pickle/camera.h>
#include <pickle/light/direct_light.h>
#include <pickle/mesh.h>
#include <pickle/texture.h>

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

pickle::renderer::OpenGLRenderer::OpenGLRenderer(SDL_Window *window, int width, int height) : Renderer(width, height), window(window)
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
    Mesh mesh(std::vector<Vertex>{
        {pickle::math::Vector<3, float>({-0.5f, -0.5f, -0.5f}), pickle::math::Vector<3, float>({0.0f, 0.0f, -1.0f}), pickle::math::Vector<3, float>({1.0f, 0.0f, 0.0f})},
        {pickle::math::Vector<3, float>({-0.5f, 0.5f, -0.5f}), pickle::math::Vector<3, float>({0.0f, 0.0f, -1.0f}), pickle::math::Vector<3, float>({1.0f, 0.0f, 0.0f})},
        {pickle::math::Vector<3, float>({0.5f, -0.5f, -0.5f}), pickle::math::Vector<3, float>({0.0f, 0.0f, -1.0f}), pickle::math::Vector<3, float>({1.0f, 0.0f, 0.0f})},
        {pickle::math::Vector<3, float>({-0.5f, 0.5f, -0.5f}), pickle::math::Vector<3, float>({0.0f, 0.0f, -1.0f}), pickle::math::Vector<3, float>({1.0f, 0.0f, 0.0f})},
        {pickle::math::Vector<3, float>({0.5f, 0.5f, -0.5f}), pickle::math::Vector<3, float>({0.0f, 0.0f, -1.0f}), pickle::math::Vector<3, float>({1.0f, 0.0f, 0.0f})},
        {pickle::math::Vector<3, float>({0.5f, -0.5f, -0.5f}), pickle::math::Vector<3, float>({0.0f, 0.0f, -1.0f}), pickle::math::Vector<3, float>({1.0f, 0.0f, 0.0f})},
        {pickle::math::Vector<3, float>({-0.5f, -0.5f, 0.5f}), pickle::math::Vector<3, float>({0.0f, 0.0f, 1.0f}), pickle::math::Vector<3, float>({0.0f, 1.0f, 0.0f})},
        {pickle::math::Vector<3, float>({0.5f, -0.5f, 0.5f}), pickle::math::Vector<3, float>({0.0f, 0.0f, 1.0f}), pickle::math::Vector<3, float>({0.0f, 1.0f, 0.0f})},
        {pickle::math::Vector<3, float>({-0.5f, 0.5f, 0.5f}), pickle::math::Vector<3, float>({0.0f, 0.0f, 1.0f}), pickle::math::Vector<3, float>({0.0f, 1.0f, 0.0f})},
        {pickle::math::Vector<3, float>({-0.5f, 0.5f, 0.5f}), pickle::math::Vector<3, float>({0.0f, 0.0f, 1.0f}), pickle::math::Vector<3, float>({0.0f, 1.0f, 0.0f})},
        {pickle::math::Vector<3, float>({0.5f, -0.5f, 0.5f}), pickle::math::Vector<3, float>({0.0f, 0.0f, 1.0f}), pickle::math::Vector<3, float>({0.0f, 1.0f, 0.0f})},
        {pickle::math::Vector<3, float>({0.5f, 0.5f, 0.5f}), pickle::math::Vector<3, float>({0.0f, 0.0f, 1.0f}), pickle::math::Vector<3, float>({0.0f, 1.0f, 0.0f})},
        {pickle::math::Vector<3, float>({-0.5f, 0.5f, -0.5f}), pickle::math::Vector<3, float>({0.0f, 1.0f, 0.0f}), pickle::math::Vector<3, float>({0.0f, 0.0f, 1.0f})},
        {pickle::math::Vector<3, float>({-0.5f, 0.5f, 0.5f}), pickle::math::Vector<3, float>({0.0f, 1.0f, 0.0f}), pickle::math::Vector<3, float>({0.0f, 0.0f, 1.0f})},
        {pickle::math::Vector<3, float>({0.5f, 0.5f, -0.5f}), pickle::math::Vector<3, float>({0.0f, 1.0f, 0.0f}), pickle::math::Vector<3, float>({0.0f, 0.0f, 1.0f})},
        {pickle::math::Vector<3, float>({-0.5f, 0.5f, 0.5f}), pickle::math::Vector<3, float>({0.0f, 1.0f, 0.0f}), pickle::math::Vector<3, float>({0.0f, 0.0f, 1.0f})},
        {pickle::math::Vector<3, float>({0.5f, 0.5f, 0.5f}), pickle::math::Vector<3, float>({0.0f, 1.0f, 0.0f}), pickle::math::Vector<3, float>({0.0f, 0.0f, 1.0f})},
        {pickle::math::Vector<3, float>({0.5f, 0.5f, -0.5f}), pickle::math::Vector<3, float>({0.0f, 1.0f, 0.0f}), pickle::math::Vector<3, float>({0.0f, 0.0f, 1.0f})},
        {pickle::math::Vector<3, float>({-0.5f, -0.5f, -0.5f}), pickle::math::Vector<3, float>({0.0f, -1.0f, 0.0f}), pickle::math::Vector<3, float>({1.0f, 1.0f, 0.0f})},
        {pickle::math::Vector<3, float>({0.5f, -0.5f, -0.5f}), pickle::math::Vector<3, float>({0.0f, -1.0f, 0.0f}), pickle::math::Vector<3, float>({1.0f, 1.0f, 0.0f})},
        {pickle::math::Vector<3, float>({-0.5f, -0.5f, 0.5f}), pickle::math::Vector<3, float>({0.0f, -1.0f, 0.0f}), pickle::math::Vector<3, float>({1.0f, 1.0f, 0.0f})},
        {pickle::math::Vector<3, float>({-0.5f, -0.5f, 0.5f}), pickle::math::Vector<3, float>({0.0f, -1.0f, 0.0f}), pickle::math::Vector<3, float>({1.0f, 1.0f, 0.0f})},
        {pickle::math::Vector<3, float>({0.5f, -0.5f, -0.5f}), pickle::math::Vector<3, float>({0.0f, -1.0f, 0.0f}), pickle::math::Vector<3, float>({1.0f, 1.0f, 0.0f})},
        {pickle::math::Vector<3, float>({0.5f, -0.5f, 0.5f}), pickle::math::Vector<3, float>({0.0f, -1.0f, 0.0f}), pickle::math::Vector<3, float>({1.0f, 1.0f, 0.0f})},
        {pickle::math::Vector<3, float>({-0.5f, -0.5f, -0.5f}), pickle::math::Vector<3, float>({-1.0f, 0.0f, 0.0f}), pickle::math::Vector<3, float>({1.0f, 0.0f, 1.0f})},
        {pickle::math::Vector<3, float>({-0.5f, -0.5f, 0.5f}), pickle::math::Vector<3, float>({-1.0f, 0.0f, 0.0f}), pickle::math::Vector<3, float>({1.0f, 0.0f, 1.0f})},
        {pickle::math::Vector<3, float>({-0.5f, 0.5f, -0.5f}), pickle::math::Vector<3, float>({-1.0f, 0.0f, 0.0f}), pickle::math::Vector<3, float>({1.0f, 0.0f, 1.0f})},
        {pickle::math::Vector<3, float>({-0.5f, -0.5f, 0.5f}), pickle::math::Vector<3, float>({-1.0f, 0.0f, 0.0f}), pickle::math::Vector<3, float>({1.0f, 0.0f, 1.0f})},
        {pickle::math::Vector<3, float>({-0.5f, 0.5f, 0.5f}), pickle::math::Vector<3, float>({-1.0f, 0.0f, 0.0f}), pickle::math::Vector<3, float>({1.0f, 0.0f, 1.0f})},
        {pickle::math::Vector<3, float>({-0.5f, 0.5f, -0.5f}), pickle::math::Vector<3, float>({-1.0f, 0.0f, 0.0f}), pickle::math::Vector<3, float>({1.0f, 0.0f, 1.0f})},
        {pickle::math::Vector<3, float>({0.5f, -0.5f, -0.5f}), pickle::math::Vector<3, float>({1.0f, 0.0f, 0.0f}), pickle::math::Vector<3, float>({0.0f, 1.0f, 1.0f})},
        {pickle::math::Vector<3, float>({0.5f, 0.5f, -0.5f}), pickle::math::Vector<3, float>({1.0f, 0.0f, 0.0f}), pickle::math::Vector<3, float>({0.0f, 1.0f, 1.0f})},
        {pickle::math::Vector<3, float>({0.5f, -0.5f, 0.5f}), pickle::math::Vector<3, float>({1.0f, 0.0f, 0.0f}), pickle::math::Vector<3, float>({0.0f, 1.0f, 1.0f})},
        {pickle::math::Vector<3, float>({0.5f, -0.5f, 0.5f}), pickle::math::Vector<3, float>({1.0f, 0.0f, 0.0f}), pickle::math::Vector<3, float>({0.0f, 1.0f, 1.0f})},
        {pickle::math::Vector<3, float>({0.5f, 0.5f, -0.5f}), pickle::math::Vector<3, float>({1.0f, 0.0f, 0.0f}), pickle::math::Vector<3, float>({0.0f, 1.0f, 1.0f})},
        {pickle::math::Vector<3, float>({0.5f, 0.5f, 0.5f}), pickle::math::Vector<3, float>({1.0f, 0.0f, 0.0f}), pickle::math::Vector<3, float>({0.0f, 1.0f, 1.0f})}
    });
    const std::vector<pickle::renderer::Vertex>& vertices = mesh.getVertices();

    Texture texture("resource/test.jpg");

    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(pickle::renderer::Vertex), &vertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void *)(6 * sizeof(float)));
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
    pickle::renderer::Camera camera(
        pickle::math::Vector<3, float>({-1.0f, 1.0f, -1.0f}),
        pickle::math::Vector<3, float>({0.0f, 0.0f, 0.0f}));
    pickle::renderer::DirectLight light(
        pickle::math::Vector<3, float>({0.1f, 0.1f, 0.1f}),
        pickle::math::Vector<3, float>({1.0f, 1.0f, 1.0f}),
        pickle::math::Vector<3, float>({1.0f, 1.0f, 1.0f}),
        pickle::math::Vector<3, float>({1.0f, -1.0f, -1.0f}));

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(program);

    int lightDirectionUniform = glGetUniformLocation(program, "light.direction");
    int lightAmbientUniform = glGetUniformLocation(program, "light.ambient");
    int lightDiffuseUniform = glGetUniformLocation(program, "light.diffuse");
    int lightSpecularUniform = glGetUniformLocation(program, "light.specular");
    int cameraPositionUniform = glGetUniformLocation(program, "camera.position");
    int modelUniform = glGetUniformLocation(program, "model");
    pickle::math::Matrix<4, 4, float> modelMatrix = pickle::math::Matrix<4, 4, float>({1.0f, 0.0f, 0.0f, 0.0f,
                                                                                       0.0f, 1.0f, 0.0f, 0.0f,
                                                                                       0.0f, 0.0f, 1.0f, 0.0f,
                                                                                       0.0f, 0.0f, 0.0f, 1.0f});
    int viewUniform = glGetUniformLocation(program, "view");

    int projectionUniform = glGetUniformLocation(program, "projection");
    pickle::math::Matrix<4, 4, float> projectionMatrix = pickle::math::perspective<pickle::math::CoordinateSystemType::RIGHT_HANDED, pickle::math::CoordinateRange::NEGATIVE_TO_POSITIVE>(
        pickle::math::radians(90.0f),
        width / (float)height,
        0.01f,
        100.0f);

    pickle::math::Vector<3, float> lightDirection = light.getDirection();
    glUniform3f(lightDirectionUniform, lightDirection.data[0], lightDirection.data[1], lightDirection.data[2]);
    pickle::math::Vector<3, float> lightAmbient = light.getAmbient();
    glUniform3f(lightAmbientUniform, lightAmbient.data[0], lightAmbient.data[1], lightAmbient.data[2]);
    pickle::math::Vector<3, float> lightDiffuse = light.getDiffuse();
    glUniform3f(lightDiffuseUniform, lightDiffuse.data[0], lightDiffuse.data[1], lightDiffuse.data[2]);
    pickle::math::Vector<3, float> lightSpecular = light.getSpecular();
    glUniform3f(lightSpecularUniform, lightSpecular.data[0], lightSpecular.data[1], lightSpecular.data[2]);
    const pickle::math::Vector<3, float> &cameraPosition = camera.getPosition();
    glUniform3f(cameraPositionUniform, cameraPosition.data[0], cameraPosition.data[1], cameraPosition.data[2]);
    glUniformMatrix4fv(modelUniform, 1, GL_FALSE, transpose(modelMatrix).data);
    glUniformMatrix4fv(viewUniform, 1, GL_FALSE, transpose(camera.getView()).data);
    glUniformMatrix4fv(projectionUniform, 1, GL_FALSE, transpose(projectionMatrix).data);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);

    SDL_GL_SwapWindow(window);
}