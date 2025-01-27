#pragma once

#include"../SceneBase.h"

//�R�����g�A�E�g
//#include"../../Object/ObjectManager.h"

class InGameScene : public SceneBase//,  public ObjectManager
{

public:
	InGameScene();
	virtual ~InGameScene();

	//����������
	virtual void Initialize() override;

	//�X�V����
	virtual eSceneType Update(float delta_second) override;

	//�`�揈��
	virtual void Draw(float delta_second) const override;

	//�I��������
	virtual void Finalize() override;

	//���݂̃V�[���^�C�v�i�I�[�o�[���C�h�K�{�j
	virtual eSceneType GetNowSceneType() const override;
};