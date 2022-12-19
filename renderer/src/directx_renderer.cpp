#include <pickle/directx_renderer.h>

#include <pickle/logger.h>

pickle::renderer::DirectXRenderer::DirectXRenderer()
{
    LOG_INFO("Inited DirectX");
}

pickle::renderer::DirectXRenderer::~DirectXRenderer()
{
}

void pickle::renderer::DirectXRenderer::render() const
{
    LOG_INFO("Rendered DirectX");
}