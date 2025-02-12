#pragma once

#include "../GameObjectBase.h"

#define D_GRAVITY (30.0f)    //�d�͉����x(m/ss)

// �L�����N�^�[�x�[�X�N���X�i�����o�֐��̃I�[�o�[���C�h�K�{�j
class CharacterBase : public GameObjectBase
{
protected:
	float g_velocity;       // �d��
	std::vector<std::vector<char>> map_data;   // �}�b�v�̏��ێ�
	float world_location;                   // ���[���h���W�̕ێ��i�}�b�v�Ƃ̓����蔻��Ŏg���j

public:
	CharacterBase();
	~CharacterBase();

public:
	// ����������
	virtual void Initialize() override;

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="delata_second">�P�t���[��������̎���</param>
	virtual void Update(float delata_second) override;

	/// <summary>
	/// �`�揈��
	/// </summary>
	/// <param name="screen_offset"></param>
	virtual void Draw(const Vector2D& screen_offset)const override;

	// �I��������
	virtual void Finalize() override;

public:
	/// <summary>
	/// �q�b�g������
	/// </summary>
	/// <param name="hit_object">������������</param>
	virtual void OnHitCollision(GameObjectBase* hit_object) override;

public:
	/// <summary>
	/// �ړ�����
	/// </summary>
	/// <param name="delta_second">�P�t���[��������̎���</param>
	virtual void Movement(float delta_second);

	// �X�N���[�������ɍ��킹�ĉ���������
	void SetVelocity(const Vector2D& velocity);

	void SetScrollValue(float& scroll);

	/// <summary>
    /// �X�e�[�W�̏���ݒ�
    /// </summary>
    /// <param name="map">�C���Q�[���ō�����X�e�[�W�����Q�ƂŎ󂯎��</param>
	void SetMapData(const std::vector<std::vector<char>>& map);

	// �}�b�v�Ƃ̓����蔻��
	bool MapCollision();
};

