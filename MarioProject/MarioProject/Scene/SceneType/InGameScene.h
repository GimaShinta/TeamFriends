#pragma once

#include"../SceneBase.h"
#include <vector>

// �C���Q�[���V�[���N���X
class InGameScene : public SceneBase//,  public ObjectManager
{
public:

	int image;	//�摜
	float scroll;	//�X�N���[����

private:
	// csv�̒l���i�[����\����
	struct ObjectMapData
	{
		char mode;
		int x_size;
		int y_size;
		int spos_x;
		int spos_y;
	};

private:
	// �N���X�|�C���^�ϐ�
	class Player* player;
	class Kuribo* kuribo;
	class Nokonoko* nokonoko;

	// �I�u�W�F�N�g�̏��z��
	std::vector<ObjectMapData> map_object;

	// ���������I�u�W�F�N�g���i�[����z��
	std::vector<GameObjectBase*> object_array;

	// �X�e�[�W�̏��z��
	std::vector<std::vector<char>> map_array;

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
	virtual void Draw(float delta_second) override;

	// �I��������
	virtual void Finalize() override;

	// ���݂̃V�[���^�C�v�i�I�[�o�[���C�h�K�{�j
	virtual eSceneType GetNowSceneType() const override;

private:
	// �摜�̓ǂݍ���
	void LoadImages();

	// csv��ǂݍ���ŃX�e�[�W�̏��z����쐬
	std::vector<std::vector<char>> LoadStageMapCSV();

	// �쐬�����X�e�[�W�̏��z����g���Ĕw�i��`��
	void DrawStageMap();

	// csv��ǂݍ���ŃI�u�W�F�N�g�̏��z����쐬
	void LoadStageObjectCSV();

	// �쐬�����I�u�W�F�N�g�̏��z����g���ăI�u�W�F�N�g�𐶐�
	void CreateMapObject();
};