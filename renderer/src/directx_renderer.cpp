#include <pickle/directx_renderer.h>

#include <pickle/logger.h>

pickle::renderer::DirectXRenderer::DirectXRenderer()
{
    Logger::log("Init DirectX");
}

pickle::renderer::DirectXRenderer::~DirectXRenderer()
{
}

void pickle::renderer::DirectXRenderer::render() const
{
    Logger::log("Render DirectX");
}