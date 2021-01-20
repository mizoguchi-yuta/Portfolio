cbuffer ConstantBuffer {
	matrix World; //ワールド変換行列
	matrix View; //ビュー変換行列
	matrix Projection; //透視斜影変換行列
	matrix WorldViewProjection; //WVP行列
};

//頂点シェーダーへの入力
struct VSInput {
	float4 position: POSITION;
	float4 normal : NORMAL;
};

//頂点シェーダーからの出力
struct VSOutput {
	float4 position : SV_POSITION;
	float4 color : COLOR0;
};

//ジオメトリシェーダーへの入力
typedef VSOutput GSInput;

//ジオメトリシェーダーからの入力
struct GSOutput {
	float4 position : SV_POSITION;
	float4 color : COLOR0;
};

//ピクセルシェーダーへの入力
typedef GSOutput PSInput;