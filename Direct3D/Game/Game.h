#pragma once
#include<Windows.h>
#include<d3d11.h>
#include <DirectXMath.h>

#define SAFE_RELEASE(p) if((p)!=nullptr){(p)->Release();(p)=nullptr;}

//アプリケーション全体を表します。
class Game {
public:
	void Initialize(LPCWSTR windowTitle, int ScreenWidth, int ScreenHeight);
	int Run();

private:
	//ウィンドウのタイトル
	LPCWSTR WindowTitle = L"タイトル";
	//ウィンドウの幅
	int ScreenWidth = 640;
	//ウィンドウの高さ
	int ScreenHeight = 480;
	//ウィンドウのハンドル
	HWND hWnd = NULL;

	bool InitWindow();

	//Direct3D 11のデバイス
	ID3D11Device* graphicsDevice = nullptr;
	//Direct3d 11のデバイスコンテキスト
	ID3D11DeviceContext* immediateContext = nullptr;
	//Ditrect3D 11の機能レベル
	D3D_FEATURE_LEVEL fertureLevel = {};
	//スワップチェーン
	IDXGISwapChain* swapChain = nullptr;
	//レンダーターゲット
	ID3D11RenderTargetView* renderTargetViews[1];
	//バックバッファーをシェーダーで利用するためのリソースビュー
	ID3D11ShaderResourceView* renderTargetResourceView = nullptr;
	//深度ステンシルのフォーマット
	const DXGI_FORMAT depthStencilFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
	//深度ステンシル
	ID3D11DepthStencilView* depthStencilView = nullptr;
	//深度ステンシルをシェーダーで利用するためのリソースビュー
	ID3D11ShaderResourceView* depthStencilResourceView = nullptr;
	//画面クリアーに使用するカラー
	FLOAT clearColor[4] = { 153 / 255.0f, 50 / 255.0f, 204 / 255.0f, 1.0f };
	//ビューポート
	D3D11_VIEWPORT viewports[1] = {};

	//グラフィックデバイスを作成します
	bool InitGraphicDevice();
	//グラフィックリソースを解放します
	void ReleaseGraphicDevice();
};

//位置座標のみを頂点情報に持つデータを表します
struct VertexPosition {
	DirectX::XMFLOAT3 position;

	//この頂点情報をD3D11_INPUT_ELEMENT_DESCで表した配列を取得
	static const D3D11_INPUT_ELEMENT_DESC* GetInputElementDescs();
	//GetInputElementDescs()関数で取得される配列の要素数を取得
	static UINT GetInputElementDescsLength();
};

//位置座標と法線ベクトルを頂点情報に持つデータを表します
struct VertexPositionNormal {
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT3 normal;

	//この頂点情報をD3D11_INPUT_ELEMENT_DESCで表した配列を取得
	static const D3D11_INPUT_ELEMENT_DESC* GetInputElementDescs();
	//GetInputElementDescs()関数で取得される配列の要素数を取得
	static UINT GetInputElementDescsLength();
};

//頂点シェーダーを表します
class BasicVertexShader {
private:
	//D3D11リソース
	ID3D11VertexShader* shader = nullptr;

public:
	//このクラスの新しいインスタンスを作成します
	static BasicVertexShader* Create(ID3D11Device* graphicsDevice);
	//リソースを解放します
	void Release();
	//ID3D11のネイティブポインターを取得します
	ID3D11VertexShader* GetNativePointer();
	//このシェーダーのバイトコードを取得します
	const BYTE* GetBytecode();
	//バイトコードのサイズを取得します
	SIZE_T GetBytecodeLength();
};

//ジオメトリシェーダーを表します
class BasicGeometryShader {
private:
	//D3D11リソース
	ID3D11GeometryShader* shader = nullptr;

public:
	//このクラスの新しいインスタンスを作成します
	static BasicGeometryShader* Create(ID3D11Device* graphicsDevice);
	//リソースを解放します
	void Release();
	//ID3D11のネイティブポインターを取得します
	ID3D11GeometryShader* GetNativePointer();
};

//ピクセルシェーダーを表します
class BasicPixelShader {
private:
	//D3D11リソース
	ID3D11PixelShader* shader = nullptr;

public:
	//このクラスの新しいインスタンスを作成します
	static BasicPixelShader* Create(ID3D11Device* graphicsDevice);
	//リソースを解放します
	void Release();
	//ID3D11のネイティブポインターを取得します
	ID3D11PixelShader* GetNativePointer();
};

//頂点バッファーを表します
class VertexBuffer {
	//D3D11リソース
	ID3D11Buffer* buffer = nullptr;

public:
	//このクラスの新しいインスタンスを作成
	static VertexBuffer* Create(ID3D11Device* graphicDevice, UINT byteWidth);
	//リソースの解放
	void Release();
	//D3D11のネイティブポインター取得
	ID3D11Buffer* GetNativePointer();
	//バッファーにデータを設定
	void SetData(void* data);
};

//インデックスバッファーを表します
class IndexBuffer {
	//D3D11リソース
	ID3D11Buffer* buffer = nullptr;

public:
	//このクラスの新しいインスタンスを作成
	static IndexBuffer* Create(ID3D11Device* graphicDevice, UINT indexCount);
	//リソースの解放
	void Release();
	//D3D11のネイティブポインター取得
	ID3D11Buffer* GetNativePointer();
	//バッファーにデータを設定
	void SetData(UINT32* data);
};

//定数バッファーを表します
class ConstantBuffer {
	//D3D11リソース
	ID3D11Buffer* buffer = nullptr;

public:
	//このクラスの新しいインスタンスを作成
	static ConstantBuffer* Create(ID3D11Device* graphicDevice, UINT byteWidth);
	//リソースの解放
	void Release();
	//D3D11のネイティブポインター取得
	ID3D11Buffer* GetNativePointer();
	//バッファーにデータを設定
	void SetData(void* data);
};

//入力レイアウトを表します
class InputLayout {
	//D3D11リソース
	ID3D11InputLayout* inputLayout = nullptr;

public:
	//このクラスの新しいインスタンスを作成
	static InputLayout* Create(
		ID3D11Device* graphicDevice,
		const D3D11_INPUT_ELEMENT_DESC* inputElementDescs,
		UINT numElements,
		const void* shaderBytecodeWithInputSignature,
		SIZE_T bytecodeLength);
	//リソースの解放
	void Release();
	//D3D11のネイティブポインター取得
	ID3D11InputLayout* GetNativePointer();
};



