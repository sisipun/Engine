#include "dx_math.h"

DirectX::XMFLOAT3 extractRollPitchYaw(const DirectX::XMFLOAT4X4& transform)
{
	DirectX::XMFLOAT3 rotation;

	rotation.x = asinf(-transform._32);
	if (cosf(rotation.x) > 0.0001)
	{
		rotation.y = atan2f(transform._31, transform._33);
		rotation.z = atan2f(transform._12, transform._22);
	}
	else
	{
		rotation.y = 0.0f;
		rotation.z = atan2f(-transform._21, transform._11);
	}

	return rotation;
}

DirectX::XMFLOAT3 extractTranslation(const DirectX::XMFLOAT4X4& transform)
{
	return { transform._41, transform._42, transform._43 };
}
