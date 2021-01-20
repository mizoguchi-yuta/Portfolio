#include "Game.h"

#pragma region//���_�o�b�t�@�[�̊֐���`
//���̃N���X�̐V�����C���X�^���X���쐬
VertexBuffer* VertexBuffer::Create(ID3D11Device* graphicDevice, UINT byteWidth) {
	//���̃N���X�̃��������m��
	auto result = new VertexBuffer();
	if (result == nullptr) {
		OutputDebugString(L"�������̊m�ۂɎ��s���܂����B");
		return nullptr;
	}

	//�쐬���钸�_�o�b�t�@�[�ɂ��Ă̋L�q
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

//���\�[�X�̉��
void VertexBuffer::Release() {
	SAFE_RELEASE(buffer);
	delete this;
}

//D3D11�̃l�C�e�B�u�|�C���^�[�擾
ID3D11Buffer* VertexBuffer::GetNativePointer() {
	return buffer;
}

//�o�b�t�@�[�Ƀf�[�^��ݒ�
void VertexBuffer::SetData(void* data) {
	//ID3D11Device���擾
	ID3D11Device* graphicsDevice = nullptr;
	buffer->GetDevice(&graphicsDevice);

	//ID3D11DeviceContext���擾
	ID3D11DeviceContext* immediateContext = nullptr;
	graphicsDevice->GetImmediateContext(&immediateContext);

	//�o�b�t�@�Ƀf�[�^��]���i�R�s�[�j����
	immediateContext->UpdateSubresource(buffer, 0, NULL, data, 0, 0);

	//�擾�����C���^�[�t�F�[�X�����
	SAFE_RELEASE(immediateContext);
	SAFE_RELEASE(graphicsDevice);
}
#pragma endregion

#pragma region//�C���f�b�N�X�o�b�t�@�[�̊֐���`
//���̃N���X�̐V�����C���X�^���X���쐬
IndexBuffer* IndexBuffer::Create(ID3D11Device* graphicDevice, UINT indexCount) {
	//���̃N���X�̃��������m��
	auto result = new IndexBuffer();
	if (result == nullptr) {
		OutputDebugString(L"�������̊m�ۂɎ��s���܂����B");
		return nullptr;
	}

	//�쐬����C���f�b�N�X�o�b�t�@�[�ɂ��Ă̋L�q
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

//���\�[�X�̉��
void IndexBuffer::Release() {
	SAFE_RELEASE(buffer);
	delete this;
}

//D3D11�̃l�C�e�B�u�|�C���^�[�擾
ID3D11Buffer* IndexBuffer::GetNativePointer() {
	return buffer;
}

//�o�b�t�@�[�Ƀf�[�^��ݒ�
void IndexBuffer::SetData(UINT32* data) {
	//ID3D11Device���擾
	ID3D11Device* graphicsDevice = nullptr;
	buffer->GetDevice(&graphicsDevice);

	//ID3D11DeviceContext���擾
	ID3D11DeviceContext* immediateContext = nullptr;
	graphicsDevice->GetImmediateContext(&immediateContext);

	//�o�b�t�@�Ƀf�[�^��]���i�R�s�[�j����
	immediateContext->UpdateSubresource(buffer, 0, NULL, data, 0, 0);

	//�擾�����C���^�[�t�F�[�X�����
	SAFE_RELEASE(immediateContext);
	SAFE_RELEASE(graphicsDevice);
}
#pragma endregion

#pragma region//�萔�o�b�t�@�[�̊֐���`
//���̃N���X�̐V�����C���X�^���X���쐬
ConstantBuffer* ConstantBuffer::Create(ID3D11Device* graphicDevice, UINT byteWidth) {
	//���̃N���X�̃��������m��
	auto result = new ConstantBuffer();
	if (result == nullptr) {
		OutputDebugString(L"�������̊m�ۂɎ��s���܂����B");
		return nullptr;
	}

	//�쐬����萔�o�b�t�@�[�ɂ��Ă̋L�q
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

//���\�[�X�̉��
void ConstantBuffer::Release() {
	SAFE_RELEASE(buffer);
	delete this;
}

//D3D11�̃l�C�e�B�u�|�C���^�[�擾
ID3D11Buffer* ConstantBuffer::GetNativePointer() {
	return buffer;
}

//�o�b�t�@�[�Ƀf�[�^��ݒ�
void ConstantBuffer::SetData(void* data) {
	//ID3D11Device���擾
	ID3D11Device* graphicsDevice = nullptr;
	buffer->GetDevice(&graphicsDevice);

	//ID3D11DeviceContext���擾
	ID3D11DeviceContext* immediateContext = nullptr;
	graphicsDevice->GetImmediateContext(&immediateContext);

	//�o�b�t�@�Ƀf�[�^��]���i�R�s�[�j����
	immediateContext->UpdateSubresource(buffer, 0, NULL, data, 0, 0);

	//�擾�����C���^�[�t�F�[�X�����
	SAFE_RELEASE(immediateContext);
	SAFE_RELEASE(graphicsDevice);
}
#pragma endregion