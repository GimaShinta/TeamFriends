#pragma once

//#include "../Objects/GameObjectManager.h"


// �V�[���̎��
enum class eSceneType
{
	eTitle,
	eInGame,
	eResult,
	eXit
};

// �V�[�����N���X
class SceneBase
{
public:
	//����������
	virtual void Initialize() {}

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="delta_second">1�t���[��������̎���</param>
	/// <returns></returns>
	virtual eSceneType Update(float delta_second)
	{
		//���݂̃V�[�������擾����
		return GetNowSceneType();
	}

	//�`�揈��
	virtual void Draw()
	{
		//�C���X�^���X�̎擾
		//GameObjectManager* obj_manager = Singleton<GameObjectManager>::GetInstance();
		//obj_manager->Draw();
	}

	//�I��������
	virtual void Finalize() {}

public:
	//���݂̃V�[�������擾����
	virtual const eSceneType GetNowSceneType()const = 0;
};