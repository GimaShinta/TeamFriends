#pragma once
#include "../BlockBase.h"

#define D_GRAVITY (30.0f)    //�d�͉����x(m/ss)

// �j��\�u���b�N
class Brick : public BlockBase
{
private:
	class Coin* coin;  //velocity�������p
	bool is_destruction;   // �󂵂����ǂ���

public:
	Brick();
	~Brick();

public:
	// ����������
	void Initialize() override;

	/// <summary>
    /// �X�V����
    /// </summary>
    /// <param name="delata_second">�P�t���[��������̎���</param>
	virtual void Update(float delta_second) override;

	/// <summary>
    /// �`�揈��
    /// </summary>
    /// <param name="screen_offset"></param>
	virtual void Draw(const Vector2D& screen_offset)const override;

	// �I��������
	void Finalize() override;

	/// <summary>
    /// �q�b�g������
    /// </summary>
    /// <param name="hit_object">������������</param>
	virtual void OnHitCollision(GameObjectBase* hit_object) override;
};