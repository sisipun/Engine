#include <pickle/metal_renderer.h>

#include <pickle/logger.h>

pickle::renderer::MetalRenderer::MetalRenderer()
{
    LOG_INFO("Inited Metal");
}

pickle::renderer::MetalRenderer::~MetalRenderer()
{
}

void pickle::renderer::MetalRenderer::render() const
{
    LOG_INFO("Rendered Metal");
}