#pragma once

#include"../SceneBase.h"

//�R�����g�A�E�g
//#include"../../Object/ObjectManager.h"

// �C���Q�[���V�[���N���X
class InGameScene : public SceneBase//,  public ObjectManager
{
public:
	InGameScene();
	virtual ~InGameScene();

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
	virtual void Draw(float delta_second) const override;

	// �I��������
	virtual void Finalize() override;

	// ���݂̃V�[���^�C�v�i�I�[�o�[���C�h�K�{�j
	virtual eSceneType GetNowSceneType() const override;
};