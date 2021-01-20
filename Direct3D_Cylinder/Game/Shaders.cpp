#include"Game.h"
#include "BasicVertexShader.h"
#include "BasicPixelShader.h"
#include "BasicGeometryShader.h"

#pragma region //頂点シェーダーの関数定義
//このクラスのあたらしいインスタンスを作成
BasicVertexShader* BasicVertexShader::Create(ID3D11Device* graphicDevice) {
	//このクラスのメモリを確保
	auto result = new BasicVertexShader();
	if (result == nullptr) {
		OutputDebugString(L"メモリの確保に失敗しました。");
		return nullptr;
	}

	//頂点シェーダーの作成
	auto hr = graphicDevice->CreateVertexShader(
		g_BasicVertexShader,
		ARRAYSIZE(g_BasicVertexShader),
		NULL,
		&result->shader);
	if (FAILED(hr)) {
		return nullptr;
	}

	//正常に初期化が完了した場合
	return result;
}

//リソースの解放
void BasicVertexShader::Release() {
	SAFE_RELEASE(shader);
	delete this;
}

//ID3D11のネイティブポインター取得
ID3D11VertexShader* BasicVertexShader::GetNativePointer() {
	return shader;
}

//このシェーダーのバイトコードを取得します
const BYTE* BasicVertexShader::GetBytecode() {
	return g_BasicVertexShader;
}
//バイトコードのサイズを取得します
SIZE_T BasicVertexShader::GetBytecodeLength() {
	return ARRAYSIZE(g_BasicVertexShader)
		;
}
#pragma endregion

#pragma region//ジオメトリシェーダーの関数定義
BasicGeometryShader* BasicGeometryShader::Create(ID3D11Device* graphicDevice) {
	//このクラスのメモリを確保
	auto result = new BasicGeometryShader();
	if (result == nullptr) {
		OutputDebugString(L"メモリの確保に失敗しました。");
		return nullptr;
	}

	//ジオメトリシェーダーの作成
	auto hr = graphicDevice->CreateGeometryShader(
		g_BasicGeometryShader,
		ARRAYSIZE(g_BasicGeometryShader),
		NULL,
		&result->shader);
	if (FAILED(hr)) {
		return nullptr;
	}

	//正常に初期化が完了した場合
	return result;
}

//リソースの解放
void BasicGeometryShader::Release() {
	SAFE_RELEASE(shader);
	delete this;
}

//ID3D11のネイティブポインター取得
ID3D11GeometryShader* BasicGeometryShader::GetNativePointer() {
	return shader;
}
#pragma endregion

#pragma region//ピクセルシェーダーの関数定義
BasicPixelShader* BasicPixelShader::Create(ID3D11Device* graphicDevice) {
	//このクラスのメモリを確保
	auto result = new BasicPixelShader();
	if (result == nullptr) {
		OutputDebugString(L"メモリの確保に失敗しました。");
		return nullptr;
	}

	//ピクセルシェーダーの作成
	auto hr = graphicDevice->CreatePixelShader(
		g_BasicPixelShader,
		ARRAYSIZE(g_BasicPixelShader),
		NULL,
		&result->shader);
	if (FAILED(hr)) {
		return nullptr;
	}

	//正常に初期化が完了した場合
	return result;
}

//リソースの解放
void BasicPixelShader::Release() {
	SAFE_RELEASE(shader);
	delete this;
}

//ID3D11のネイティブポインター取得
ID3D11PixelShader* BasicPixelShader::GetNativePointer() {
	return shader;
}
#pragma endregion