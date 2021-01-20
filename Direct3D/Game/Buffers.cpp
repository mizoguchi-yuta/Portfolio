#include "Game.h"

#pragma region//頂点バッファーの関数定義
//このクラスの新しいインスタンスを作成
VertexBuffer* VertexBuffer::Create(ID3D11Device* graphicDevice, UINT byteWidth) {
	//このクラスのメモリを確保
	auto result = new VertexBuffer();
	if (result == nullptr) {
		OutputDebugString(L"メモリの確保に失敗しました。");
		return nullptr;
	}

	//作成する頂点バッファーについての記述
	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.ByteWidth = byteWidth;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	graphicDevice->CreateBuffer(&bufferDesc, nullptr, &result->buffer);

	return result;
}

//リソースの解放
void VertexBuffer::Release() {
	SAFE_RELEASE(buffer);
	delete this;
}

//D3D11のネイティブポインター取得
ID3D11Buffer* VertexBuffer::GetNativePointer() {
	return buffer;
}

//バッファーにデータを設定
void VertexBuffer::SetData(void* data) {
	//ID3D11Deviceを取得
	ID3D11Device* graphicsDevice = nullptr;
	buffer->GetDevice(&graphicsDevice);

	//ID3D11DeviceContextを取得
	ID3D11DeviceContext* immediateContext = nullptr;
	graphicsDevice->GetImmediateContext(&immediateContext);

	//バッファにデータを転送（コピー）する
	immediateContext->UpdateSubresource(buffer, 0, NULL, data, 0, 0);

	//取得したインターフェースを解放
	SAFE_RELEASE(immediateContext);
	SAFE_RELEASE(graphicsDevice);
}
#pragma endregion

#pragma region//インデックスバッファーの関数定義
//このクラスの新しいインスタンスを作成
IndexBuffer* IndexBuffer::Create(ID3D11Device* graphicDevice, UINT indexCount) {
	//このクラスのメモリを確保
	auto result = new IndexBuffer();
	if (result == nullptr) {
		OutputDebugString(L"メモリの確保に失敗しました。");
		return nullptr;
	}

	//作成するインデックスバッファーについての記述
	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.ByteWidth = indexCount * sizeof(UINT32);
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	graphicDevice->CreateBuffer(&bufferDesc, nullptr, &result->buffer);

	return result;
}

//リソースの解放
void IndexBuffer::Release() {
	SAFE_RELEASE(buffer);
	delete this;
}

//D3D11のネイティブポインター取得
ID3D11Buffer* IndexBuffer::GetNativePointer() {
	return buffer;
}

//バッファーにデータを設定
void IndexBuffer::SetData(UINT32* data) {
	//ID3D11Deviceを取得
	ID3D11Device* graphicsDevice = nullptr;
	buffer->GetDevice(&graphicsDevice);

	//ID3D11DeviceContextを取得
	ID3D11DeviceContext* immediateContext = nullptr;
	graphicsDevice->GetImmediateContext(&immediateContext);

	//バッファにデータを転送（コピー）する
	immediateContext->UpdateSubresource(buffer, 0, NULL, data, 0, 0);

	//取得したインターフェースを解放
	SAFE_RELEASE(immediateContext);
	SAFE_RELEASE(graphicsDevice);
}
#pragma endregion

#pragma region//定数バッファーの関数定義
//このクラスの新しいインスタンスを作成
ConstantBuffer* ConstantBuffer::Create(ID3D11Device* graphicDevice, UINT byteWidth) {
	//このクラスのメモリを確保
	auto result = new ConstantBuffer();
	if (result == nullptr) {
		OutputDebugString(L"メモリの確保に失敗しました。");
		return nullptr;
	}

	//作成する定数バッファーについての記述
	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.ByteWidth = byteWidth;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	graphicDevice->CreateBuffer(&bufferDesc, nullptr, &result->buffer);

	return result;
}

//リソースの解放
void ConstantBuffer::Release() {
	SAFE_RELEASE(buffer);
	delete this;
}

//D3D11のネイティブポインター取得
ID3D11Buffer* ConstantBuffer::GetNativePointer() {
	return buffer;
}

//バッファーにデータを設定
void ConstantBuffer::SetData(void* data) {
	//ID3D11Deviceを取得
	ID3D11Device* graphicsDevice = nullptr;
	buffer->GetDevice(&graphicsDevice);

	//ID3D11DeviceContextを取得
	ID3D11DeviceContext* immediateContext = nullptr;
	graphicsDevice->GetImmediateContext(&immediateContext);

	//バッファにデータを転送（コピー）する
	immediateContext->UpdateSubresource(buffer, 0, NULL, data, 0, 0);

	//取得したインターフェースを解放
	SAFE_RELEASE(immediateContext);
	SAFE_RELEASE(graphicsDevice);
}
#pragma endregion