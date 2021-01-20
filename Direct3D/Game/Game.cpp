#include <DirectXMath.h>	// DirectX�̎Z�p���C�u�����[
#include <DirectXColors.h>	// DirectX�̃J���[���C�u�����[
#include"Game.h"

using namespace DirectX;

#pragma region//�֐��̃v���g�^�C�v�錾
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
#pragma endregion

#pragma region//�A�v���P�[�V���������������܂�
void Game::Initialize(LPCWSTR windowTitle, int ScreenWidth, int ScreenHeight) {
	//�E�B���h�E�̃^�C�g��
	WindowTitle = windowTitle;
	//�E�B���h�E�̕�
	ScreenWidth = ScreenWidth;
	//�E�B���h�E�̍���
	ScreenHeight = ScreenHeight;
}
#pragma endregion

#pragma region//�E�B���h�E�̍쐬
bool Game::InitWindow()
{
	HINSTANCE hInstance = GetModuleHandle(NULL);

	//�E�B���h�E�N���X��o�^����
	const wchar_t CLASS_NAME[] = L"GameWindow";
	WNDCLASSEX wndClass = {};
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.lpfnWndProc = WindowProc; //�E�B���h�E�v���V�[�W�����w��
	wndClass.hInstance = hInstance;
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)COLOR_BACKGROUND;
	wndClass.lpszClassName = CLASS_NAME;
	if (!RegisterClassEx(&wndClass)) {
		return false;
	}

	//�N���C�A���g�̈悪�w�肵���𑜓x�ɂȂ�E�B���h�E�T�C�Y���v�Z
	RECT rect = { 0,0,ScreenWidth,ScreenHeight };
	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, FALSE, 0);

	//�E�B���h�E���쐬����
	auto hWnd = CreateWindowEx(
		0,
		CLASS_NAME,
		WindowTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		(rect.right - rect.left), (rect.bottom - rect.top),
		NULL, NULL, hInstance, NULL);
	if (hWnd == NULL) {
		return false;
	}

	//�E�B���h�E�̕\���w�����o�����߂ɃE�B���h�E�n���h�����w�肷��
	ShowWindow(hWnd, SW_SHOWNORMAL);
	UpdateWindow(hWnd);

	//���̏ꍇ��this�L�[���[�h���ȗ��ł��Ȃ�
	this->hWnd = hWnd;

	return true;
}
#pragma endregion

#pragma region// �E�B���h�E ���b�Z�[�W����������v���V�[�W���[
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_CLOSE:
		//�E�B���h�E�����
		if (MessageBox(hWnd, L"�E�B���h�E����܂����H", L"�m�F", MB_OKCANCEL) == IDOK) {
			DestroyWindow(hWnd);
		}
		return 0;

	case WM_DESTROY:
		//�A�v���P�[�V�������I��
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
#pragma endregion

#pragma region//�O���t�B�b�N�f�o�C�X�̍쐬
bool Game::InitGraphicDevice() {
	//�֐��̎��s���ʂ��󂯎��ϐ�
	HRESULT hr = S_OK;

	//�f�o�C�X�쐬���̃I�v�V�����t���O
	UINT creationFlags = 0;
#if defined(_DEBUG)
	// DEBUG�r���h�̍ۂ�Direct3D�̃f�o�b�O�\���@�\����������
	creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

#pragma region//�쐬����X���b�v�`�F�[���̐ݒ�
	DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
	swapChainDesc.BufferDesc.Width = ScreenWidth;
	swapChainDesc.BufferDesc.Height = ScreenHeight;
	swapChainDesc.BufferDesc.RefreshRate = { 60,1 };
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.SampleDesc = { 1,0 };
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;// �V�F�[�_�[���\�[�X�Ƃ��Ďg�p���邱�Ƃ�ݒ�
	swapChainDesc.BufferCount = 2;
	swapChainDesc.OutputWindow = hWnd;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Windowed = TRUE;
#pragma endregion

#pragma region//�f�o�C�X�A�f�o�C�X�R���e�L�X�g�A�X���b�v�`�F�[�����쐬
	hr = D3D11CreateDeviceAndSwapChain(
		NULL,											// �r�f�I�A�_�v�^�[�BNULL���w�肷��ƃf�t�H���g�A�_�v�^�[
		D3D_DRIVER_TYPE_HARDWARE,	// �쐬����h���C�o�[�̎��
		0,													// �\�t�g�E�F�A���X�^���C�U�[����������DLL�̃n���h��
		creationFlags,									// �f�o�C�X�쐬���̃I�v�V�����t���O
		NULL,									// �쐬����@�\���x���BNULL���w�肵�ďȗ��ł���
		0,													// featureLevels�z��̐�
		D3D11_SDK_VERSION,					// ���ł�D3D11_SDK_VERSION
		&swapChainDesc,
		&swapChain,
		&graphicsDevice,							// [�o��]Direct3D 11 �f�o�C�X
		&fertureLevel,								// ���ۂɍ쐬���ꂽ�@�\���x��
		&immediateContext);						// [�o��]Direct3D 11 �f�o�C�X �R���e�L�X�g
	if (FAILED(hr)) {
		MessageBox(hWnd, L"Direct3D11�f�o�C�X���쐬�ł��܂���ł���", L"�G���[", MB_OK);
		return false;
	}
#pragma endregion

#pragma region//�o�b�N�o�b�t�@�[�̐ݒ�
	//�X���b�v�`�F�[������o�b�N�o�b�t�@�[���擾
	ID3D11Texture2D* backBaffer = nullptr;
	hr = swapChain->GetBuffer(0, IID_PPV_ARGS(&backBaffer));
	if (FAILED(hr)) {
		MessageBox(hWnd, L"�o�b�N�o�b�t�@�[���擾�ł��܂���ł����B", L"�G���[", MB_OK);
		return false;
	}
	//�o�b�N�o�b�t�@�[�ɃA�N�Z�X���邽�߂̃����_�[�^�[�Q�b�g�r���[���쐬
	hr = graphicsDevice->CreateRenderTargetView(backBaffer, NULL, &renderTargetViews[0]);
	if (FAILED(hr)) {
		MessageBox(hWnd, L"�����_�[�^�[�Q�b�g �r���[���쐬�ł��܂���ł����B", L"�G���[", MB_OK);
		return false;
	}
	//�o�b�N�o�b�t�@�[�ɃV�F�[�_�[����A�N�Z�X���邽�߂̃��\�[�X�r���[���쐬
	hr = graphicsDevice->CreateShaderResourceView(backBaffer, NULL, &renderTargetResourceView);
	if (FAILED(hr)) {
		MessageBox(hWnd, L"�����_�[�^�[�Q�b�g ���\�[�X �r���[���쐬�ł��܂���ł����B", L"�G���[", MB_OK);
		return false;
	}
	SAFE_RELEASE(backBaffer);
#pragma endregion

#pragma region//�e�N�X�`���A�V�F�[�_�[�̐ݒ�
	//�e�N�X�`���ƃV�F�[�_�[���\�[�X�r���[�̃t�H�[�}�b�g���쐬
	DXGI_FORMAT textureFormat = depthStencilFormat;
	DXGI_FORMAT resourceFormat = depthStencilFormat;
	switch (depthStencilFormat)
	{
	case DXGI_FORMAT_D16_UNORM:
		textureFormat = DXGI_FORMAT_R16_TYPELESS;
		resourceFormat = DXGI_FORMAT_R16_UNORM;
		break;
	case DXGI_FORMAT_D24_UNORM_S8_UINT: //���݂̐ݒ肾�Ƃ����ɂȂ�
		textureFormat = DXGI_FORMAT_R24G8_TYPELESS;
		resourceFormat = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
		break;
	case DXGI_FORMAT_D32_FLOAT:
		textureFormat = DXGI_FORMAT_R32_TYPELESS;
		resourceFormat = DXGI_FORMAT_R32_FLOAT;
		break;
	case DXGI_FORMAT_D32_FLOAT_S8X24_UINT:
		textureFormat = DXGI_FORMAT_R32G8X24_TYPELESS;
		resourceFormat = DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS;
		break;
	}
#pragma endregion

#pragma region//�[�x�X�e���V���̐ݒ�
	//�[�x�X�e���V�����쐬
	ID3D11Texture2D* depthStencil = nullptr;
	D3D11_TEXTURE2D_DESC depthStencilDesc = {};
	depthStencilDesc.Width = swapChainDesc.BufferDesc.Width;
	depthStencilDesc.Height = swapChainDesc.BufferDesc.Height;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = textureFormat;
	depthStencilDesc.SampleDesc = swapChainDesc.SampleDesc;
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;  // �V�F�[�_�[���\�[�X�Ƃ��Ďg�p���邱�Ƃ�ݒ�
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;
	hr = graphicsDevice->CreateTexture2D(&depthStencilDesc, NULL, &depthStencil);
	if (FAILED(hr)) {
		MessageBox(hWnd, L"�[�x�X�e���V�����쐬�ł��܂���ł����B", L"�G���[", MB_OK);
		return false;
	}
	//�[�x�X�e���V���ɃA�N�Z�X���邽�߂̃r���[���쐬
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc = {};
	depthStencilViewDesc.Format = depthStencilFormat;
	if (depthStencilDesc.SampleDesc.Count > 0) {
		depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
	}
	else {
		depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		depthStencilViewDesc.Texture2D.MipSlice = 0;
	}
	depthStencilViewDesc.Texture2D.MipSlice = 0;
	hr = graphicsDevice->CreateDepthStencilView(depthStencil, &depthStencilViewDesc, &depthStencilView);
	if (FAILED(hr)) {
		MessageBox(hWnd, L"�[�x�X�e���V�� �r���[���쐬�ł��܂���ł����B", L"�G���[", MB_OK);
		return false;
	}
	//�[�x�X�e���V���ɃV�F�[�_�[����A�N�Z�X���邽�߂̃��\�[�X�r���[��ǉ�
	D3D11_SHADER_RESOURCE_VIEW_DESC depthStencilResourceViewDesc = {};
	depthStencilResourceViewDesc.Format = resourceFormat;
	if (depthStencilDesc.SampleDesc.Count > 0) {
		depthStencilResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DMS;
	}
	else {
		depthStencilResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		depthStencilResourceViewDesc.Texture2D.MostDetailedMip = 0;
		depthStencilResourceViewDesc.Texture2D.MipLevels = 1;
	}
	hr = graphicsDevice->CreateShaderResourceView(
		depthStencil,
		&depthStencilResourceViewDesc,
		&depthStencilResourceView);
	if (FAILED(hr)) {
		MessageBox(hWnd, L"�[�x�X�e���V�� ���\�[�X �r���[���쐬�ł��܂���ł����B", L"�G���[", MB_OK);
		return false;
	}
	SAFE_RELEASE(depthStencil);
#pragma endregion

#pragma region//�r���[�|�[�g
	viewports[0].Width = static_cast<FLOAT>(ScreenWidth);
	viewports[0].Height = static_cast<FLOAT>(ScreenHeight);
	viewports[0].MinDepth = 0.0f;
	viewports[0].MaxDepth = 1.0f;
	viewports[0].TopLeftX = 0.0f;
	viewports[0].TopLeftY = 0.0f;
#pragma endregion

	return true;
}
#pragma endregion

#pragma region//�O���t�B�b�N���\�[�X�̉���֐���`
void Game::ReleaseGraphicDevice() {
	SAFE_RELEASE(depthStencilResourceView);
	SAFE_RELEASE(depthStencilView);
	SAFE_RELEASE(renderTargetResourceView);
	SAFE_RELEASE(renderTargetViews[0]);
	SAFE_RELEASE(swapChain);
	SAFE_RELEASE(immediateContext);
	SAFE_RELEASE(graphicsDevice);
}
#pragma endregion

#pragma region //���b�Z�[�W���[�v�����s���܂��B
int Game::Run() {

	//�E�B���h�E���쐬
	if (!InitWindow()) {
		MessageBox(NULL, L"�E�B���h�E�̍쐬�Ɏ��s���܂����B", L"�G���[", MB_OK);
		return -1;
	}
	//�O���t�B�b�N�f�o�C�X���쐬
	if (!InitGraphicDevice()) {
		MessageBox(NULL, L"�O���t�B�b�N�f�o�C�X���������ł��܂���ł����B", L"���b�Z�[�W", MB_OK);
		return -1;
	}

	HRESULT hr = S_OK;

	//������
	const UINT32 divideCount = 1000;
	//���a
	const float radius = 1.0f;
	//����
	const float height = 4.0f;

	//���_�f�[�^�̔z��
	VertexPositionNormal vertices[divideCount + divideCount + 2 * divideCount] = {};

	//���
	for (size_t triangle = 0; triangle < divideCount; triangle++) {
		const auto angle = XM_2PI / divideCount * triangle;
		auto& vertex = vertices[triangle];
		//�ʒu���W
		vertex.position.x = radius * XMScalarCos(angle);
		vertex.position.y = height / 2;
		vertex.position.z = radius * -XMScalarSin(angle);
		//�@���x�N�g��
		vertex.normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	}
	//���
	for (size_t triangle = 0; triangle < divideCount; triangle++) {
		const auto angle = XM_2PI / divideCount * triangle;
		auto& vertex = vertices[triangle + divideCount];
		//�ʒu���W
		//vertices�z��ɂ͏�ʂ̒��_��(divideCount)�������炵�ăA�N�Z�X����
		vertex.position.x = radius * XMScalarCos(angle);
		vertex.position.y = -height / 2;
		vertex.position.z = radius * XMScalarSin(angle);
		//�@���x�N�g��
		vertex.normal = XMFLOAT3(0.0f, -1.0f, 0.0f);
	}
	//����
	for (size_t triangle = 0; triangle < divideCount; triangle++) {
		const auto angle = XM_2PI / divideCount * triangle;
		//vertices�z��ɂ͏��+��ʂ̒��_��(2*divideCount)�������炵�ăA�N�Z�X����
		auto& top = vertices[2 * triangle + 0 + 2 * divideCount];
		auto& bottom = vertices[2 * triangle + 1 + 2 * divideCount];

		//��ʑ����_
		//�@���x�N�g��
		top.normal = XMFLOAT3(XMScalarCos(angle), 0.0f, XMScalarSin(angle));
		//�ʒu���W
		top.position.x = radius * top.normal.x;
		top.position.y = height / 2;
		top.position.z = radius * top.normal.z;

		//��ʑ����_
		bottom.normal = top.normal;
		//�ʒu���W
		bottom.position.x = radius * bottom.normal.x;
		bottom.position.y = -height / 2;
		bottom.position.z = radius * bottom.normal.z;
	}

	//���_�o�b�t�@�[���쐬
	VertexBuffer* vertexBuffer = nullptr;
	vertexBuffer = VertexBuffer::Create(graphicsDevice, sizeof vertices);
	if (vertexBuffer == nullptr) {
		return -1;
	}
	//���\�[�X���X�V
	vertexBuffer->SetData(vertices);

	//�C���f�b�N�X�f�[�^�̔z��
	UINT32 indices[3 * (divideCount - 2) + 3 * (divideCount - 2) + 3 * 2 * divideCount] = {};
	//���
	for (UINT32 triangle = 0; triangle < divideCount - 2; triangle++) {
		indices[3 * triangle + 0] = 0;
		indices[3 * triangle + 1] = triangle + 1;
		indices[3 * triangle + 2] = triangle + 2;
	}
	//���
	for (UINT32 triangle = 0; triangle < divideCount - 2; triangle++) {
		const SIZE_T indexOffset = 3 * (divideCount - 2);
		indices[3 * triangle + 0 + indexOffset] = 0 + divideCount;
		indices[3 * triangle + 1 + indexOffset] = triangle + 1 + divideCount;
		indices[3 * triangle + 2 + indexOffset] = triangle + 2 + divideCount;
	}
	//����
	for (UINT32 triangle = 0; triangle < divideCount; triangle++) {
		const SIZE_T indexOffset = 3 * (divideCount - 2) + 3 * (divideCount - 2);

		indices[indexOffset + 6 * triangle + 0] = (2 * triangle + 0) % (2 * divideCount) + 2 * divideCount;
		indices[indexOffset + 6 * triangle + 1] = (2 * triangle + 2) % (2 * divideCount) + 2 * divideCount;
		indices[indexOffset + 6 * triangle + 2] = (2 * triangle + 1) % (2 * divideCount) + 2 * divideCount;
		indices[indexOffset + 6 * triangle + 3] = (2 * triangle + 3) % (2 * divideCount) + 2 * divideCount;
		indices[indexOffset + 6 * triangle + 4] = (2 * triangle + 1) % (2 * divideCount) + 2 * divideCount;
		indices[indexOffset + 6 * triangle + 5] = (2 * triangle + 2) % (2 * divideCount) + 2 * divideCount;
	}
	//�C���f�b�N�X�̐�
	UINT indexCount = ARRAYSIZE(indices);

	//�C���f�b�N�X�o�b�t�@�[�̍쐬
	IndexBuffer* indexBuffer = nullptr;
	indexBuffer = IndexBuffer::Create(graphicsDevice, indexCount);
	if (indexBuffer == nullptr) {
		return -1;
	}
	//���\�[�X���X�V
	indexBuffer->SetData(indices);

	//�萔�o�b�t�@�[����ăV�F�[�_�[�ɖ��t���[������s��f�[�^��\���܂��B
	struct MatricesPerFrame {
		DirectX::XMFLOAT4X4 worldMatrix;
		DirectX::XMFLOAT4X4 viewMatrix;
		DirectX::XMFLOAT4X4 projectionMatrix;
		DirectX::XMFLOAT4X4 worldViewProjectionMatrix;
	};

	//�萔�o�b�t�@�[���쐬
	ConstantBuffer* constantBuffer = nullptr;
	constantBuffer = ConstantBuffer::Create(graphicsDevice, sizeof(MatricesPerFrame));
	if (constantBuffer == nullptr) {
		return -1;
	}

	//���_�V�F�[�_�[�̍쐬
	BasicVertexShader* vertexShader = nullptr;
	vertexShader = BasicVertexShader::Create(graphicsDevice);
	if (vertexShader == nullptr) {
		OutputDebugString(L"���_�V�F�[�_�[�̍쐬�Ɏ��s���܂����B");
		return -1;
	}

	//�W�I���g���V�F�[�_�[�̍쐬
	BasicGeometryShader* geometryShader = nullptr;
	geometryShader = BasicGeometryShader::Create(graphicsDevice);
	if (geometryShader == nullptr) {
		OutputDebugString(L"�W�I���g���V�F�[�_�[�̍쐬�Ɏ��s���܂����B");
		return -1;
	}

	//�s�N�Z���V�F�[�_�[�̍쐬
	BasicPixelShader* pixelShader = nullptr;
	pixelShader = BasicPixelShader::Create(graphicsDevice);
	if (pixelShader == nullptr) {
		OutputDebugString(L"�s�N�Z���V�F�[�_�[���쐬�ł��܂���ł���");
		return -1;
	}

	/*
// ���_�o�b�t�@�[�̓��͗v�f�ɂ��Ă̋L�q
D3D11_INPUT_ELEMENT_DESC inputElementDesc = {};
inputElementDesc.SemanticName = "POSITION";
inputElementDesc.SemanticIndex = 0;
inputElementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
inputElementDesc.InputSlot = 0;
inputElementDesc.AlignedByteOffset = 0;
inputElementDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
inputElementDesc.InstanceDataStepRate = 0;
*/

//struct VertexPosition
//{
//	DirectX::XMFLOAT3 position;	// �ʒu���W
//};

	D3D11_INPUT_ELEMENT_DESC inputElementDescs[] = {
		{"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
	};
	//���̓��C�A�E�g���쐬
	InputLayout* inputLayout = nullptr;
	inputLayout = InputLayout::Create(
		graphicsDevice,
		VertexPositionNormal::GetInputElementDescs(),
		VertexPositionNormal::GetInputElementDescsLength(),
		vertexShader->GetBytecode(),
		vertexShader->GetBytecodeLength());
	if (inputLayout == nullptr) {
		return -1;
	}

	float time = 0;

	//���b�Z�[�W���[�v�����s
	MSG msg = {};
	while (true) {
		time += 0.01666f;

		//�萔�o�b�t�@�[�֓]������f�[�^���\�[�X������
		XMMATRIX worldMatrix = XMMatrixIdentity();
		worldMatrix *= XMMatrixScaling(1.0f, 1.0f, 1.0f);
		XMVECTOR axis = XMVectorSet(1, 1, 0, 0);
		worldMatrix *= XMMatrixRotationAxis(axis, time);
		worldMatrix *= XMMatrixTranslation(0.0f, 0.0f, 0.0f);

		//�r���[�s����v�Z
		XMVECTOR eyePosition = XMVectorSet(0, 1, -10, 1);
		XMVECTOR focusPosition = XMVectorSet(0, 1, 0, 1);
		XMVECTOR upDirection = XMVectorSet(0, 1, 0, 0);
		XMMATRIX viewMatrix = XMMatrixLookAtLH(eyePosition, focusPosition, upDirection);

		//�v���W�F�N�V�����s����v�Z
		float fovAngleY = 60.0f;
		float aspectRatio = 640 / 480.0f;
		float nearZ = 0.3f;
		float farZ = 1000.0f;
		XMMATRIX projectionMatrix = XMMatrixPerspectiveFovLH(XMConvertToRadians(fovAngleY), aspectRatio, nearZ, farZ);

		MatricesPerFrame matricesPerFrame = {};
		XMStoreFloat4x4(&matricesPerFrame.worldMatrix, XMMatrixTranspose(worldMatrix));
		XMStoreFloat4x4(&matricesPerFrame.viewMatrix, XMMatrixTranspose(viewMatrix));
		XMStoreFloat4x4(&matricesPerFrame.projectionMatrix, XMMatrixTranspose(projectionMatrix));
		XMStoreFloat4x4(&matricesPerFrame.worldViewProjectionMatrix, XMMatrixTranspose(worldMatrix * viewMatrix * projectionMatrix));

		//�萔�o�b�t�@�[���X�V
		constantBuffer->SetData(&matricesPerFrame);

		//�����_�[�^�[�Q�b�g��ݒ�
		immediateContext->OMSetRenderTargets(1, renderTargetViews, depthStencilView);
		//��ʂ��N���A�[
		immediateContext->ClearRenderTargetView(renderTargetViews[0], clearColor);
		immediateContext->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

		//�r���[�|�[�g��ݒ�
		immediateContext->RSSetViewports(1, viewports);

		//���_�o�b�t�@�[��ݒ�
		ID3D11Buffer* vertexBuffers[1] = { vertexBuffer->GetNativePointer() };
		UINT strides[1] = { sizeof(VertexPositionNormal) };
		UINT offsets[1] = { 0 };
		immediateContext->IASetVertexBuffers(0, ARRAYSIZE(vertexBuffers), vertexBuffers, strides, offsets);

		//�V�F�[�_�[��ݒ�
		immediateContext->VSSetShader(vertexShader->GetNativePointer(), NULL, 0);
		immediateContext->GSSetShader(geometryShader->GetNativePointer(), NULL, 0);
		immediateContext->PSSetShader(pixelShader->GetNativePointer(), NULL, 0);

		//���_�V�F�[�_�[�ɒ萔�o�b�t�@�[��ݒ�
		ID3D11Buffer* constantBuffers[1] = { constantBuffer->GetNativePointer() };
		immediateContext->VSSetConstantBuffers(0, 1, constantBuffers);

		//���_�o�b�t�@�[�ƒ��_�V�F�[�_�[�̑g�ݍ��킹�ɑΉ��������̓��C�A�E�g��ݒ�
		immediateContext->IASetInputLayout(inputLayout->GetNativePointer());

		//�v���~�e�B�u�g�|���W�[�Ƃ��ăg���C�A���O����ݒ�
		immediateContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		//�C���f�b�N�X�o�b�t�@�[��ݒ�
		immediateContext->IASetIndexBuffer(indexBuffer->GetNativePointer(), DXGI_FORMAT_R32_UINT, 0);

		//Direct3D�ɂ��`��
		immediateContext->DrawIndexed(ARRAYSIZE(indices), 0, 0);

		//�o�b�N�o�b�t�@�[�ɕ`�悵���C���[�W���f�B�X�v���C�ɕ\��
		hr = swapChain->Present(1, 0);
		if (FAILED(hr)) {
			MessageBox(hWnd,
				L"�O���t�B�b�N�f�o�C�X�������I�Ɏ��O���ꂽ���A�h���C�o�[���A�b�v�f�[�g����܂����B",
				L"�G���[", MB_OK);
			return -1;
		}

		//���̃E�B���h�E�̃��b�Z�[�W�����݂��邩�m�F
		if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) {
			if (!GetMessage(&msg, NULL, 0, 0)) {
				break;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	SAFE_RELEASE(vertexBuffer);
	SAFE_RELEASE(indexBuffer);
	SAFE_RELEASE(constantBuffer);
	SAFE_RELEASE(vertexShader);
	SAFE_RELEASE(geometryShader);
	SAFE_RELEASE(pixelShader);
	SAFE_RELEASE(inputLayout);

	ReleaseGraphicDevice();

	return (int)msg.wParam;
}
#pragma endregion
