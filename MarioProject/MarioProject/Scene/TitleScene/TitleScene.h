#pragma once

#include"../SceneBase.h"

class TitleScene :public SceneBase
{
private:

public:
	TitleScene();
	virtual ~TitleScene();

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