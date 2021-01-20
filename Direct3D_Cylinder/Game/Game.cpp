#include <DirectXMath.h>	// DirectXの算術ライブラリー
#include <DirectXColors.h>	// DirectXのカラーライブラリー
#include"Game.h"

using namespace DirectX;

#pragma region//関数のプロトタイプ宣言
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
#pragma endregion

#pragma region//アプリケーションを初期化します
void Game::Initialize(LPCWSTR windowTitle, int ScreenWidth, int ScreenHeight) {
	//ウィンドウのタイトル
	WindowTitle = windowTitle;
	//ウィンドウの幅
	ScreenWidth = ScreenWidth;
	//ウィンドウの高さ
	ScreenHeight = ScreenHeight;
}
#pragma endregion

#pragma region//ウィンドウの作成
bool Game::InitWindow()
{
	HINSTANCE hInstance = GetModuleHandle(NULL);

	//ウィンドウクラスを登録する
	const wchar_t CLASS_NAME[] = L"GameWindow";
	WNDCLASSEX wndClass = {};
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.lpfnWndProc = WindowProc; //ウィンドウプロシージャを指定
	wndClass.hInstance = hInstance;
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)COLOR_BACKGROUND;
	wndClass.lpszClassName = CLASS_NAME;
	if (!RegisterClassEx(&wndClass)) {
		return false;
	}

	//クライアント領域が指定した解像度になるウィンドウサイズを計算
	RECT rect = { 0,0,ScreenWidth,ScreenHeight };
	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, FALSE, 0);

	//ウィンドウを作成する
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

	//ウィンドウの表示指示を出すためにウィンドウハンドルを指定する
	ShowWindow(hWnd, SW_SHOWNORMAL);
	UpdateWindow(hWnd);

	//この場合はthisキーワードを省略できない
	this->hWnd = hWnd;

	return true;
}
#pragma endregion

#pragma region// ウィンドウ メッセージを処理するプロシージャー
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_CLOSE:
		//ウィンドウを閉じる
		if (MessageBox(hWnd, L"ウィンドウを閉じますか？", L"確認", MB_OKCANCEL) == IDOK) {
			DestroyWindow(hWnd);
		}
		return 0;

	case WM_DESTROY:
		//アプリケーションを終了
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
#pragma endregion

#pragma region//グラフィックデバイスの作成
bool Game::InitGraphicDevice() {
	//関数の実行結果を受け取る変数
	HRESULT hr = S_OK;

	//デバイス作成時のオプションフラグ
	UINT creationFlags = 0;
#if defined(_DEBUG)
	// DEBUGビルドの際にDirect3Dのデバッグ表示機能を持たせる
	creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

#pragma region//作成するスワップチェーンの設定
	DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
	swapChainDesc.BufferDesc.Width = ScreenWidth;
	swapChainDesc.BufferDesc.Height = ScreenHeight;
	swapChainDesc.BufferDesc.RefreshRate = { 60,1 };
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.SampleDesc = { 1,0 };
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;// シェーダーリソースとして使用することを設定
	swapChainDesc.BufferCount = 2;
	swapChainDesc.OutputWindow = hWnd;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Windowed = TRUE;
#pragma endregion

#pragma region//デバイス、デバイスコンテキスト、スワップチェーンを作成
	hr = D3D11CreateDeviceAndSwapChain(
		NULL,											// ビデオアダプター。NULLを指定するとデフォルトアダプター
		D3D_DRIVER_TYPE_HARDWARE,	// 作成するドライバーの種類
		0,													// ソフトウェアラスタライザーを実装したDLLのハンドル
		creationFlags,									// デバイス作成時のオプションフラグ
		NULL,									// 作成する機能レベル。NULLを指定して省略できる
		0,													// featureLevels配列の数
		D3D11_SDK_VERSION,					// いつでもD3D11_SDK_VERSION
		&swapChainDesc,
		&swapChain,
		&graphicsDevice,							// [出力]Direct3D 11 デバイス
		&fertureLevel,								// 実際に作成された機能レベル
		&immediateContext);						// [出力]Direct3D 11 デバイス コンテキスト
	if (FAILED(hr)) {
		MessageBox(hWnd, L"Direct3D11デバイスを作成できませんでした", L"エラー", MB_OK);
		return false;
	}
#pragma endregion

#pragma region//バックバッファーの設定
	//スワップチェーンからバックバッファーを取得
	ID3D11Texture2D* backBaffer = nullptr;
	hr = swapChain->GetBuffer(0, IID_PPV_ARGS(&backBaffer));
	if (FAILED(hr)) {
		MessageBox(hWnd, L"バックバッファーを取得できませんでした。", L"エラー", MB_OK);
		return false;
	}
	//バックバッファーにアクセスするためのレンダーターゲットビューを作成
	hr = graphicsDevice->CreateRenderTargetView(backBaffer, NULL, &renderTargetViews[0]);
	if (FAILED(hr)) {
		MessageBox(hWnd, L"レンダーターゲット ビューを作成できませんでした。", L"エラー", MB_OK);
		return false;
	}
	//バックバッファーにシェーダーからアクセスするためのリソースビューを作成
	hr = graphicsDevice->CreateShaderResourceView(backBaffer, NULL, &renderTargetResourceView);
	if (FAILED(hr)) {
		MessageBox(hWnd, L"レンダーターゲット リソース ビューを作成できませんでした。", L"エラー", MB_OK);
		return false;
	}
	SAFE_RELEASE(backBaffer);
#pragma endregion

#pragma region//テクスチャ、シェーダーの設定
	//テクスチャとシェーダーリソースビューのフォーマットを作成
	DXGI_FORMAT textureFormat = depthStencilFormat;
	DXGI_FORMAT resourceFormat = depthStencilFormat;
	switch (depthStencilFormat)
	{
	case DXGI_FORMAT_D16_UNORM:
		textureFormat = DXGI_FORMAT_R16_TYPELESS;
		resourceFormat = DXGI_FORMAT_R16_UNORM;
		break;
	case DXGI_FORMAT_D24_UNORM_S8_UINT: //現在の設定だとここになる
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

#pragma region//深度ステンシルの設定
	//深度ステンシルを作成
	ID3D11Texture2D* depthStencil = nullptr;
	D3D11_TEXTURE2D_DESC depthStencilDesc = {};
	depthStencilDesc.Width = swapChainDesc.BufferDesc.Width;
	depthStencilDesc.Height = swapChainDesc.BufferDesc.Height;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = textureFormat;
	depthStencilDesc.SampleDesc = swapChainDesc.SampleDesc;
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;  // シェーダーリソースとして使用することを設定
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;
	hr = graphicsDevice->CreateTexture2D(&depthStencilDesc, NULL, &depthStencil);
	if (FAILED(hr)) {
		MessageBox(hWnd, L"深度ステンシルを作成できませんでした。", L"エラー", MB_OK);
		return false;
	}
	//深度ステンシルにアクセスするためのビューを作成
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
		MessageBox(hWnd, L"深度ステンシル ビューを作成できませんでした。", L"エラー", MB_OK);
		return false;
	}
	//深度ステンシルにシェーダーからアクセスするためのリソースビューを追加
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
		MessageBox(hWnd, L"深度ステンシル リソース ビューを作成できませんでした。", L"エラー", MB_OK);
		return false;
	}
	SAFE_RELEASE(depthStencil);
#pragma endregion

#pragma region//ビューポート
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

#pragma region//グラフィックリソースの解放関数定義
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

#pragma region //メッセージループを実行します。
int Game::Run() {

	//ウィンドウを作成
	if (!InitWindow()) {
		MessageBox(NULL, L"ウィンドウの作成に失敗しました。", L"エラー", MB_OK);
		return -1;
	}
	//グラフィックデバイスを作成
	if (!InitGraphicDevice()) {
		MessageBox(NULL, L"グラフィックデバイスを初期化できませんでした。", L"メッセージ", MB_OK);
		return -1;
	}

	HRESULT hr = S_OK;

	//分割数
	const UINT32 divideCount = 1000;
	//半径
	const float radius = 1.0f;
	//高さ
	const float height = 4.0f;

	//頂点データの配列
	VertexPositionNormal vertices[divideCount + divideCount + 2 * divideCount] = {};

	//上面
	for (size_t triangle = 0; triangle < divideCount; triangle++) {
		const auto angle = XM_2PI / divideCount * triangle;
		auto& vertex = vertices[triangle];
		//位置座標
		vertex.position.x = radius * XMScalarCos(angle);
		vertex.position.y = height / 2;
		vertex.position.z = radius * -XMScalarSin(angle);
		//法線ベクトル
		vertex.normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	}
	//底面
	for (size_t triangle = 0; triangle < divideCount; triangle++) {
		const auto angle = XM_2PI / divideCount * triangle;
		auto& vertex = vertices[triangle + divideCount];
		//位置座標
		//vertices配列には上面の頂点数(divideCount)だけずらしてアクセスする
		vertex.position.x = radius * XMScalarCos(angle);
		vertex.position.y = -height / 2;
		vertex.position.z = radius * XMScalarSin(angle);
		//法線ベクトル
		vertex.normal = XMFLOAT3(0.0f, -1.0f, 0.0f);
	}
	//側面
	for (size_t triangle = 0; triangle < divideCount; triangle++) {
		const auto angle = XM_2PI / divideCount * triangle;
		//vertices配列には上面+底面の頂点数(2*divideCount)だけずらしてアクセスする
		auto& top = vertices[2 * triangle + 0 + 2 * divideCount];
		auto& bottom = vertices[2 * triangle + 1 + 2 * divideCount];

		//上面側頂点
		//法線ベクトル
		top.normal = XMFLOAT3(XMScalarCos(angle), 0.0f, XMScalarSin(angle));
		//位置座標
		top.position.x = radius * top.normal.x;
		top.position.y = height / 2;
		top.position.z = radius * top.normal.z;

		//底面側頂点
		bottom.normal = top.normal;
		//位置座標
		bottom.position.x = radius * bottom.normal.x;
		bottom.position.y = -height / 2;
		bottom.position.z = radius * bottom.normal.z;
	}

	//頂点バッファーを作成
	VertexBuffer* vertexBuffer = nullptr;
	vertexBuffer = VertexBuffer::Create(graphicsDevice, sizeof vertices);
	if (vertexBuffer == nullptr) {
		return -1;
	}
	//リソースを更新
	vertexBuffer->SetData(vertices);

	//インデックスデータの配列
	UINT32 indices[3 * (divideCount - 2) + 3 * (divideCount - 2) + 3 * 2 * divideCount] = {};
	//上面
	for (UINT32 triangle = 0; triangle < divideCount - 2; triangle++) {
		indices[3 * triangle + 0] = 0;
		indices[3 * triangle + 1] = triangle + 1;
		indices[3 * triangle + 2] = triangle + 2;
	}
	//底面
	for (UINT32 triangle = 0; triangle < divideCount - 2; triangle++) {
		const SIZE_T indexOffset = 3 * (divideCount - 2);
		indices[3 * triangle + 0 + indexOffset] = 0 + divideCount;
		indices[3 * triangle + 1 + indexOffset] = triangle + 1 + divideCount;
		indices[3 * triangle + 2 + indexOffset] = triangle + 2 + divideCount;
	}
	//側面
	for (UINT32 triangle = 0; triangle < divideCount; triangle++) {
		const SIZE_T indexOffset = 3 * (divideCount - 2) + 3 * (divideCount - 2);

		indices[indexOffset + 6 * triangle + 0] = (2 * triangle + 0) % (2 * divideCount) + 2 * divideCount;
		indices[indexOffset + 6 * triangle + 1] = (2 * triangle + 2) % (2 * divideCount) + 2 * divideCount;
		indices[indexOffset + 6 * triangle + 2] = (2 * triangle + 1) % (2 * divideCount) + 2 * divideCount;
		indices[indexOffset + 6 * triangle + 3] = (2 * triangle + 3) % (2 * divideCount) + 2 * divideCount;
		indices[indexOffset + 6 * triangle + 4] = (2 * triangle + 1) % (2 * divideCount) + 2 * divideCount;
		indices[indexOffset + 6 * triangle + 5] = (2 * triangle + 2) % (2 * divideCount) + 2 * divideCount;
	}
	//インデックスの数
	UINT indexCount = ARRAYSIZE(indices);

	//インデックスバッファーの作成
	IndexBuffer* indexBuffer = nullptr;
	indexBuffer = IndexBuffer::Create(graphicsDevice, indexCount);
	if (indexBuffer == nullptr) {
		return -1;
	}
	//リソースを更新
	indexBuffer->SetData(indices);

	//定数バッファーを介してシェーダーに毎フレーム送る行列データを表します。
	struct MatricesPerFrame {
		DirectX::XMFLOAT4X4 worldMatrix;
		DirectX::XMFLOAT4X4 viewMatrix;
		DirectX::XMFLOAT4X4 projectionMatrix;
		DirectX::XMFLOAT4X4 worldViewProjectionMatrix;
	};

	//定数バッファーを作成
	ConstantBuffer* constantBuffer = nullptr;
	constantBuffer = ConstantBuffer::Create(graphicsDevice, sizeof(MatricesPerFrame));
	if (constantBuffer == nullptr) {
		return -1;
	}

	//頂点シェーダーの作成
	BasicVertexShader* vertexShader = nullptr;
	vertexShader = BasicVertexShader::Create(graphicsDevice);
	if (vertexShader == nullptr) {
		OutputDebugString(L"頂点シェーダーの作成に失敗しました。");
		return -1;
	}

	//ジオメトリシェーダーの作成
	BasicGeometryShader* geometryShader = nullptr;
	geometryShader = BasicGeometryShader::Create(graphicsDevice);
	if (geometryShader == nullptr) {
		OutputDebugString(L"ジオメトリシェーダーの作成に失敗しました。");
		return -1;
	}

	//ピクセルシェーダーの作成
	BasicPixelShader* pixelShader = nullptr;
	pixelShader = BasicPixelShader::Create(graphicsDevice);
	if (pixelShader == nullptr) {
		OutputDebugString(L"ピクセルシェーダーを作成できませんでした");
		return -1;
	}

	/*
// 頂点バッファーの入力要素についての記述
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
//	DirectX::XMFLOAT3 position;	// 位置座標
//};

	D3D11_INPUT_ELEMENT_DESC inputElementDescs[] = {
		{"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
	};
	//入力レイアウトを作成
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

	//メッセージループを実行
	MSG msg = {};
	while (true) {
		time += 0.01666f;

		//定数バッファーへ転送するデータリソースを準備
		XMMATRIX worldMatrix = XMMatrixIdentity();
		worldMatrix *= XMMatrixScaling(1.0f, 1.0f, 1.0f);
		XMVECTOR axis = XMVectorSet(1, 1, 0, 0);
		worldMatrix *= XMMatrixRotationAxis(axis, time);
		worldMatrix *= XMMatrixTranslation(0.0f, 0.0f, 0.0f);

		//ビュー行列を計算
		XMVECTOR eyePosition = XMVectorSet(0, 1, -10, 1);
		XMVECTOR focusPosition = XMVectorSet(0, 1, 0, 1);
		XMVECTOR upDirection = XMVectorSet(0, 1, 0, 0);
		XMMATRIX viewMatrix = XMMatrixLookAtLH(eyePosition, focusPosition, upDirection);

		//プロジェクション行列を計算
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

		//定数バッファーを更新
		constantBuffer->SetData(&matricesPerFrame);

		//レンダーターゲットを設定
		immediateContext->OMSetRenderTargets(1, renderTargetViews, depthStencilView);
		//画面をクリアー
		immediateContext->ClearRenderTargetView(renderTargetViews[0], clearColor);
		immediateContext->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

		//ビューポートを設定
		immediateContext->RSSetViewports(1, viewports);

		//頂点バッファーを設定
		ID3D11Buffer* vertexBuffers[1] = { vertexBuffer->GetNativePointer() };
		UINT strides[1] = { sizeof(VertexPositionNormal) };
		UINT offsets[1] = { 0 };
		immediateContext->IASetVertexBuffers(0, ARRAYSIZE(vertexBuffers), vertexBuffers, strides, offsets);

		//シェーダーを設定
		immediateContext->VSSetShader(vertexShader->GetNativePointer(), NULL, 0);
		immediateContext->GSSetShader(geometryShader->GetNativePointer(), NULL, 0);
		immediateContext->PSSetShader(pixelShader->GetNativePointer(), NULL, 0);

		//頂点シェーダーに定数バッファーを設定
		ID3D11Buffer* constantBuffers[1] = { constantBuffer->GetNativePointer() };
		immediateContext->VSSetConstantBuffers(0, 1, constantBuffers);

		//頂点バッファーと頂点シェーダーの組み合わせに対応した入力レイアウトを設定
		immediateContext->IASetInputLayout(inputLayout->GetNativePointer());

		//プリミティブトポロジーとしてトライアングルを設定
		immediateContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		//インデックスバッファーを設定
		immediateContext->IASetIndexBuffer(indexBuffer->GetNativePointer(), DXGI_FORMAT_R32_UINT, 0);

		//Direct3Dによる描画
		immediateContext->DrawIndexed(ARRAYSIZE(indices), 0, 0);

		//バックバッファーに描画したイメージをディスプレイに表示
		hr = swapChain->Present(1, 0);
		if (FAILED(hr)) {
			MessageBox(hWnd,
				L"グラフィックデバイスが物理的に取り外されたか、ドライバーがアップデートされました。",
				L"エラー", MB_OK);
			return -1;
		}

		//このウィンドウのメッセージが存在するか確認
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
