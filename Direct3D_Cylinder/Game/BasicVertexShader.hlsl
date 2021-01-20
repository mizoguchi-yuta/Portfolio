#include "BasicShader.hlsli"

//ライトの位置座標(平行光源 w=0,点光源 w=1)
static const float4 lightPosition = float4(1.0f, 2.0f, -2.0f, 0.0f);
//マテリアルの表面カラー
static const float4 diffuseColor = float4(1, 1, 0, 1);

VSOutput main(VSInput input) {
	VSOutput output;

	//WVP変換
	output.position = mul(input.position, WorldViewProjection);

	//ワールド空間の頂点位置
	float4 worldPosition = mul(input.position, World);
	//面から光源を指す正規化ベクトルL(点光源)
	float3 light = normalize(lightPosition.xyz - lightPosition.w * worldPosition.xyz);

	//ワールド空間上の法線ベクトルN
	float3 worldNormal = normalize(mul(input.normal, (float3x3)World));

	//ランバート反射
	float diffuse = max(dot(light, worldNormal), 0);
	output.color = float4(diffuse * diffuseColor.xyz, diffuseColor.w);

	return output;
}