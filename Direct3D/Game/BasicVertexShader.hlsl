#include "BasicShader.hlsli"

//���C�g�̈ʒu���W(���s���� w=0,�_���� w=1)
static const float4 lightPosition = float4(1.0f, 2.0f, -2.0f, 0.0f);
//�}�e���A���̕\�ʃJ���[
static const float4 diffuseColor = float4(1, 1, 0, 1);

VSOutput main(VSInput input) {
	VSOutput output;

	//WVP�ϊ�
	output.position = mul(input.position, WorldViewProjection);

	//���[���h��Ԃ̒��_�ʒu
	float4 worldPosition = mul(input.position, World);
	//�ʂ���������w�����K���x�N�g��L(�_����)
	float3 light = normalize(lightPosition.xyz - lightPosition.w * worldPosition.xyz);

	//���[���h��ԏ�̖@���x�N�g��N
	float3 worldNormal = normalize(mul(input.normal, (float3x3)World));

	//�����o�[�g����
	float diffuse = max(dot(light, worldNormal), 0);
	output.color = float4(diffuse * diffuseColor.xyz, diffuseColor.w);

	return output;
}