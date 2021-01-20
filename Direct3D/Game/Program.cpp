//=============================================================================
// Program.cpp
// 
//=============================================================================
#include "Game.h"

// エントリーポイント
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	Game game;

	//アプリケーションの起動設定
	game.Initialize(L"ゲームタイトル", 640, 480);
	//メッセージループを実行
	return game.Run();
}