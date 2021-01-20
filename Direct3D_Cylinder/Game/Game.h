#pragma once
#include<Windows.h>
#include<d3d11.h>
#include <DirectXMath.h>

#define SAFE_RELEASE(p) if((p)!=nullptr){(p)->Release();(p)=nullptr;}

//�A�v���P�[�V�����S�̂�\���܂��B
class Game {
public:
	void Initialize(LPCWSTR windowTitle, int ScreenWidth, int ScreenHeight);
	int Run();

private:
	//�E�B���h�E�̃^�C�g��
	LPCWSTR WindowTitle = L"�^�C�g��";
	//�E�B���h�E�̕�
	int ScreenWidth = 640;
	//�E�B���h�E�̍���
	int ScreenHeight = 480;
	//�E�B���h�E�̃n���h��
	HWND hWnd = NULL;

	bool InitWindow();

	//Direct3D 11�̃f�o�C�X
	ID3D11Device* graphicsDevice = nullptr;
	//Direct3d 11�̃f�o�C�X�R���e�L�X�g
	ID3D11DeviceContext* immediateContext = nullptr;
	//Ditrect3D 11�̋@�\���x��
	D3D_FEATURE_LEVEL fertureLevel = {};
	//�X���b�v�`�F�[��
	IDXGISwapChain* swapChain = nullptr;
	//�����_�[�^�[�Q�b�g
	ID3D11RenderTargetView* renderTargetViews[1];
	//�o�b�N�o�b�t�@�[���V�F�[�_�[�ŗ��p���邽�߂̃��\�[�X�r���[
	ID3D11ShaderResourceView* renderTargetResourceView = nullptr;
	//�[�x�X�e���V���̃t�H�[�}�b�g
	const DXGI_FORMAT depthStencilFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
	//�[�x�X�e���V��
	ID3D11DepthStencilView* depthStencilView = nullptr;
	//�[�x�X�e���V�����V�F�[�_�[�ŗ��p���邽�߂̃��\�[�X�r���[
	ID3D11ShaderResourceView* depthStencilResourceView = nullptr;
	//��ʃN���A�[�Ɏg�p����J���[
	FLOAT clearColor[4] = { 153 / 255.0f, 50 / 255.0f, 204 / 255.0f, 1.0f };
	//�r���[�|�[�g
	D3D11_VIEWPORT viewports[1] = {};

	//�O���t�B�b�N�f�o�C�X���쐬���܂�
	bool InitGraphicDevice();
	//�O���t�B�b�N���\�[�X��������܂�
	void ReleaseGraphicDevice();
};

//�ʒu���W�݂̂𒸓_���Ɏ��f�[�^��\���܂�
struct VertexPosition {
	DirectX::XMFLOAT3 position;

	//���̒��_����D3D11_INPUT_ELEMENT_DESC�ŕ\�����z����擾
	static const D3D11_INPUT_ELEMENT_DESC* GetInputElementDescs();
	//GetInputElementDescs()�֐��Ŏ擾�����z��̗v�f�����擾
	static UINT GetInputElementDescsLength();
};

//�ʒu���W�Ɩ@���x�N�g���𒸓_���Ɏ��f�[�^��\���܂�
struct VertexPositionNormal {
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT3 normal;

	//���̒��_����D3D11_INPUT_ELEMENT_DESC�ŕ\�����z����擾
	static const D3D11_INPUT_ELEMENT_DESC* GetInputElementDescs();
	//GetInputElementDescs()�֐��Ŏ擾�����z��̗v�f�����擾
	static UINT GetInputElementDescsLength();
};

//���_�V�F�[�_�[��\���܂�
class BasicVertexShader {
private:
	//D3D11���\�[�X
	ID3D11VertexShader* shader = nullptr;

public:
	//���̃N���X�̐V�����C���X�^���X���쐬���܂�
	static BasicVertexShader* Create(ID3D11Device* graphicsDevice);
	//���\�[�X��������܂�
	void Release();
	//ID3D11�̃l�C�e�B�u�|�C���^�[���擾���܂�
	ID3D11VertexShader* GetNativePointer();
	//���̃V�F�[�_�[�̃o�C�g�R�[�h���擾���܂�
	const BYTE* GetBytecode();
	//�o�C�g�R�[�h�̃T�C�Y���擾���܂�
	SIZE_T GetBytecodeLength();
};

//�W�I���g���V�F�[�_�[��\���܂�
class BasicGeometryShader {
private:
	//D3D11���\�[�X
	ID3D11GeometryShader* shader = nullptr;

public:
	//���̃N���X�̐V�����C���X�^���X���쐬���܂�
	static BasicGeometryShader* Create(ID3D11Device* graphicsDevice);
	//���\�[�X��������܂�
	void Release();
	//ID3D11�̃l�C�e�B�u�|�C���^�[���擾���܂�
	ID3D11GeometryShader* GetNativePointer();
};

//�s�N�Z���V�F�[�_�[��\���܂�
class BasicPixelShader {
private:
	//D3D11���\�[�X
	ID3D11PixelShader* shader = nullptr;

public:
	//���̃N���X�̐V�����C���X�^���X���쐬���܂�
	static BasicPixelShader* Create(ID3D11Device* graphicsDevice);
	//���\�[�X��������܂�
	void Release();
	//ID3D11�̃l�C�e�B�u�|�C���^�[���擾���܂�
	ID3D11PixelShader* GetNativePointer();
};

//���_�o�b�t�@�[��\���܂�
class VertexBuffer {
	//D3D11���\�[�X
	ID3D11Buffer* buffer = nullptr;

public:
	//���̃N���X�̐V�����C���X�^���X���쐬
	static VertexBuffer* Create(ID3D11Device* graphicDevice, UINT byteWidth);
	//���\�[�X�̉��
	void Release();
	//D3D11�̃l�C�e�B�u�|�C���^�[�擾
	ID3D11Buffer* GetNativePointer();
	//�o�b�t�@�[�Ƀf�[�^��ݒ�
	void SetData(void* data);
};

//�C���f�b�N�X�o�b�t�@�[��\���܂�
class IndexBuffer {
	//D3D11���\�[�X
	ID3D11Buffer* buffer = nullptr;

public:
	//���̃N���X�̐V�����C���X�^���X���쐬
	static IndexBuffer* Create(ID3D11Device* graphicDevice, UINT indexCount);
	//���\�[�X�̉��
	void Release();
	//D3D11�̃l�C�e�B�u�|�C���^�[�擾
	ID3D11Buffer* GetNativePointer();
	//�o�b�t�@�[�Ƀf�[�^��ݒ�
	void SetData(UINT32* data);
};

//�萔�o�b�t�@�[��\���܂�
class ConstantBuffer {
	//D3D11���\�[�X
	ID3D11Buffer* buffer = nullptr;

public:
	//���̃N���X�̐V�����C���X�^���X���쐬
	static ConstantBuffer* Create(ID3D11Device* graphicDevice, UINT byteWidth);
	//���\�[�X�̉��
	void Release();
	//D3D11�̃l�C�e�B�u�|�C���^�[�擾
	ID3D11Buffer* GetNativePointer();
	//�o�b�t�@�[�Ƀf�[�^��ݒ�
	void SetData(void* data);
};

//���̓��C�A�E�g��\���܂�
class InputLayout {
	//D3D11���\�[�X
	ID3D11InputLayout* inputLayout = nullptr;

public:
	//���̃N���X�̐V�����C���X�^���X���쐬
	static InputLayout* Create(
		ID3D11Device* graphicDevice,
		const D3D11_INPUT_ELEMENT_DESC* inputElementDescs,
		UINT numElements,
		const void* shaderBytecodeWithInputSignature,
		SIZE_T bytecodeLength);
	//���\�[�X�̉��
	void Release();
	//D3D11�̃l�C�e�B�u�|�C���^�[�擾
	ID3D11InputLayout* GetNativePointer();
};



