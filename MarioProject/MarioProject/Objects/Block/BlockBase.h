#pragma once
#include "../GameObjectBase.h"

// �u���b�N�̊��N���X
class BlockBase : public GameObjectBase
{
public:
	BlockBase();
	~BlockBase();

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
	/// <param name="hit_object">������������̃|�C���^</param>
	virtual void OnHitCollision(GameObjectBase* hit_object) override;

	/// <summary>
	/// �Q�[���I�W�F�N�g�̃T�C�Y�ύX
	/// </summary>
	/// <param name="x_size">x�̃T�C�Y</param>
	/// <param name="y_size">y�̃T�C�Y</param>
	void SetSizeData(int x_size, int y_size);
};

