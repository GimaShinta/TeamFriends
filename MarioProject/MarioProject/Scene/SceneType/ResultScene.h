#pragma once

#include"../SceneBase.h"

// ���U���g�V�[���N���X
class ResultScene :public SceneBase
{
private:
	std::vector<int> ui_num;
	int mario_image;    //�}���I�̉摜
	int game_over_sound;
	int death_sound;

public:
	ResultScene();
	virtual ~ResultScene();

	// ����������
	virtual void Initialize() override;

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="delta_second">�P�t���[��������̎���</param>
	/// <returns></returns>
	virtual eSceneType Update(float delta_second) override;

	/// <summary>
	/// �`�揈��
	/// </summary>
	/// <param name="delta_second">�P�t���[��������̎���</param>
	/// <returns></returns>
	virtual void Draw(float delta_second) override;

	// �I���������i�g�����C���X�^���X�̍폜�Ƃ��j
	virtual void Finalize() override;

	// ���݂̃V�[���^�C�v�i�I�[�o�[���C�h�K�{�j
	virtual eSceneType GetNowSceneType() const override;
};