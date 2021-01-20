#include"Game.h"
#include "BasicVertexShader.h"
#include "BasicPixelShader.h"
#include "BasicGeometryShader.h"

#pragma region //���_�V�F�[�_�[�̊֐���`
//���̃N���X�̂����炵���C���X�^���X���쐬
BasicVertexShader* BasicVertexShader::Create(ID3D11Device* graphicDevice) {
	//���̃N���X�̃��������m��
	auto result = new BasicVertexShader();
	if (result == nullptr) {
		OutputDebugString(L"�������̊m�ۂɎ��s���܂����B");
		return nullptr;
	}

	//���_�V�F�[�_�[�̍쐬
	auto hr = graphicDevice->CreateVertexShader(
		g_BasicVertexShader,
		ARRAYSIZE(g_BasicVertexShader),
		NULL,
		&result->shader);
	if (FAILED(hr)) {
		return nullptr;
	}

	//����ɏ����������������ꍇ
	return result;
}

//���\�[�X�̉��
void BasicVertexShader::Release() {
	SAFE_RELEASE(shader);
	delete this;
}

//ID3D11�̃l�C�e�B�u�|�C���^�[�擾
ID3D11VertexShader* BasicVertexShader::GetNativePointer() {
	return shader;
}

//���̃V�F�[�_�[�̃o�C�g�R�[�h���擾���܂�
const BYTE* BasicVertexShader::GetBytecode() {
	return g_BasicVertexShader;
}
//�o�C�g�R�[�h�̃T�C�Y���擾���܂�
SIZE_T BasicVertexShader::GetBytecodeLength() {
	return ARRAYSIZE(g_BasicVertexShader)
		;
}
#pragma endregion

#pragma region//�W�I���g���V�F�[�_�[�̊֐���`
BasicGeometryShader* BasicGeometryShader::Create(ID3D11Device* graphicDevice) {
	//���̃N���X�̃��������m��
	auto result = new BasicGeometryShader();
	if (result == nullptr) {
		OutputDebugString(L"�������̊m�ۂɎ��s���܂����B");
		return nullptr;
	}

	//�W�I���g���V�F�[�_�[�̍쐬
	auto hr = graphicDevice->CreateGeometryShader(
		g_BasicGeometryShader,
		ARRAYSIZE(g_BasicGeometryShader),
		NULL,
		&result->shader);
	if (FAILED(hr)) {
		return nullptr;
	}

	//����ɏ����������������ꍇ
	return result;
}

//���\�[�X�̉��
void BasicGeometryShader::Release() {
	SAFE_RELEASE(shader);
	delete this;
}

//ID3D11�̃l�C�e�B�u�|�C���^�[�擾
ID3D11GeometryShader* BasicGeometryShader::GetNativePointer() {
	return shader;
}
#pragma endregion

#pragma region//�s�N�Z���V�F�[�_�[�̊֐���`
BasicPixelShader* BasicPixelShader::Create(ID3D11Device* graphicDevice) {
	//���̃N���X�̃��������m��
	auto result = new BasicPixelShader();
	if (result == nullptr) {
		OutputDebugString(L"�������̊m�ۂɎ��s���܂����B");
		return nullptr;
	}

	//�s�N�Z���V�F�[�_�[�̍쐬
	auto hr = graphicDevice->CreatePixelShader(
		g_BasicPixelShader,
		ARRAYSIZE(g_BasicPixelShader),
		NULL,
		&result->shader);
	if (FAILED(hr)) {
		return nullptr;
	}

	//����ɏ����������������ꍇ
	return result;
}

//���\�[�X�̉��
void BasicPixelShader::Release() {
	SAFE_RELEASE(shader);
	delete this;
}

//ID3D11�̃l�C�e�B�u�|�C���^�[�擾
ID3D11PixelShader* BasicPixelShader::GetNativePointer() {
	return shader;
}
#pragma endregion