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
	// �X�V����
	virtual void Update(float delata_second) override;
	// �`�揈��
	virtual void Draw(const Vector2D& screen_offset)const override;
	// �I��������
	virtual void Finalize() override;

public:
	// �q�b�g������
	virtual void OnHitCollision(GameObjectBase* hit_object) override;

public:
	// �ړ�����
	virtual void Movement(float delta_second);
	// �X�N���[�������ɍ��킹�ĉ���������
	void SetVelocity(const Vector2D& velocity);
};

