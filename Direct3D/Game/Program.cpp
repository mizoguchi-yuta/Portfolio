//=============================================================================
// Program.cpp
// 
//=============================================================================
#include "Game.h"

// �G���g���[�|�C���g
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	Game game;

	//�A�v���P�[�V�����̋N���ݒ�
	game.Initialize(L"�Q�[���^�C�g��", 640, 480);
	//���b�Z�[�W���[�v�����s
	return game.Run();
}