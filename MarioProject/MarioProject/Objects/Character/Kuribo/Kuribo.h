#pragma once

#include "../CharacterBase.h"

// �N���{�[�N���X
class Kuribo :public CharacterBase
{
public:
	// �N���{�[�̏��
	enum eKUriboState
	{
		NORMAL,
		HUMARERU,
		DEAD
	};

public:
	Kuribo();
	~Kuribo();

public:
	// ����������
	void Initialize() override;

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="delta_second"></param>
	void Update(float delta_second) override;

	/// <summary>
	/// �`�揈��
	/// </summary>
	/// <param name="screen_offset"></param>
	void Draw(const Vector2D& screen_offset)const override;

	// �I��������
	void Finalize() override;

public:
	/// <summary>
	/// �q�b�g�����Ƃ��̏���
	/// </summary>
	/// <param name="hit_object">������������</param>
	void OnHitCollision(GameObjectBase* hit_object) override;
};

