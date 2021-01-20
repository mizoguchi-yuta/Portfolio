#include "BasicShader.hlsli"

float4 main(PSInput input) : SV_TARGET
{
	return input.color;
//return float4(1.0f, 1.0f, 1.0f, 1.0f);
}