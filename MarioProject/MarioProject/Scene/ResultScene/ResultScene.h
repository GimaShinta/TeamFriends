#pragma once
#pragma once

#include"../SceneBase.h"

class ResultScene :public SceneBase
{
private:

public:
	ResultScene();
	virtual ~ResultScene();

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