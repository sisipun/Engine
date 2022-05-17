#include <pickle/directx_renderer.h>

#include <iostream>

pickle::renderer::DirectXRenderer::DirectXRenderer()
{
    std::cout << "Init DirectX" << std::endl;
}

pickle::renderer::DirectXRenderer::~DirectXRenderer()
{
}

void pickle::renderer::DirectXRenderer::render() const
{
    std::cout << "Render DirectX" << std::endl;
}