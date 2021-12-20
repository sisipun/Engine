#ifndef DIRECTX_MATH_H
#define DIRECTX_MATH_H

#include <DirectXMath.h>

DirectX::XMFLOAT3 extractRollPitchYaw(const DirectX::XMFLOAT4X4& transform);

DirectX::XMFLOAT3 extractTranslation(const DirectX::XMFLOAT4X4& transform);

#endif