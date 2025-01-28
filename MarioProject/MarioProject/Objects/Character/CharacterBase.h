#pragma once

#include "../GameObjectBase.h"

// �L�����N�^�[�x�[�X�N���X�i�����o�֐��̃I�[�o�[���C�h�K�{�j
class CharacterBase : public GameObjectBase
{
protected:
	float g_velocity;       // �d��

public:
	Vector2D velocity;      // ���x

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
};

