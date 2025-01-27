#pragma once

// �C���N���[�h
#include "../Singleton.h"
#include <string>

// �}�N����`
#define	D_SUCCESS		(0)		// ����
#define	D_FAILURE		(-1)	// ���s

#define D_WIN_MAX_X		(960)	// �X�N���[���T�C�Y�i���j
#define D_WIN_MAX_Y		(720)	// �X�N���[���T�C�Y�i�����j
#define D_COLOR_BIT		(32)	// �J���[�r�b�g

// �v���g�^�C�v�錾
// (class T�Ő����Ȃ��Ŏg�p)
class Application : public Singleton<class T>
{
private:
	// �I�����邩���Ȃ���
	bool end_check;

public:
	Application();
	~Application();

	/// <summary>
	/// dxlib����������
	/// </summary>
	void WakeUp();

	/// <summary>
	/// dxlib�X�V����
	/// </summary>
	void Run();

	/// <summary>
	/// dxlib�I��������
	/// </summary>
	void ShutDown();

private:
	/// <summary>
	/// dxlib�`�揈��
	/// </summary>
	void Graph()const;

public:
	// �t���[�����[�g�̐���
	void FreamControl();
	//�P�t���[��������̎��Ԃ��擾
	const float& GetDeltaSecond();
	//�G���[���e�̏�������
	int ErrorThrow(std::string error_log);
};

