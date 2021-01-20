#include "Game.h"

//このクラスの新しいインスタンスを作成
InputLayout* InputLayout::Create(
	ID3D11Device* graphicsDevice,
	const D3D11_INPUT_ELEMENT_DESC* inputElementDescs,
	UINT numElements,
	const void* shaderBytecodeWithInputSignature,
	SIZE_T bytecodeLength)
{
	//このクラスのメモリを確保
	auto result = new InputLayout();
	if (result == nullptr) {
		OutputDebugString(L"メモリの確保に失敗しました。");
		return nullptr;
	}

	//入力レイアウトを作成
	auto hr = graphicsDevice->CreateInputLayout(
		inputElementDescs,
		numElements,
		shaderBytecodeWithInputSignature,
		bytecodeLength,
		&result->inputLayout);
	if (FAILED(hr)) {
		OutputDebugString(L"入力レイアウトを作成できませんでした。");
		return nullptr;
	}

	return result;
}

//リソースの解放
void InputLayout::Release() {
	SAFE_RELEASE(inputLayout);
	delete this;
}

//D3D11のネイティブポインター取得
ID3D11InputLayout* InputLayout::GetNativePointer() {
	return inputLayout;
}