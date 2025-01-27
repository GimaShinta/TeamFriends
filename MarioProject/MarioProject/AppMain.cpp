#include "DxLib.h"
#include "Application/Application.h"

//���C���֐�
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	//�A�v���P�[�V�����𐶐�����
	Application app;

	try
	{
		//����������
		app.WakeUp();

		//���s����
		app.Run();

		//�I��������
		app.ShutDown();
	}
	catch (std::string error_log)
	{
		//�G���[���e���o�͂���
		return app.ErrorThrow(error_log);
	}

	//�I����Ԃ�ʒm����
	return D_SUCCESS;
}