#include "DxLib.h"


int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{

	ChangeWindowMode(TRUE);


	if (DxLib_Init() == -1)
	{
		return -1;
	}



	printf("�e�X�g");

	printf("�e�X�g�ł��B");


	WaitKey();


	DxLib_End();


	return 0;
}