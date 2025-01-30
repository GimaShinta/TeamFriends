#pragma once
#include "../BlockBase.h"

// �j��\�u���b�N
class Brick :
    public BlockBase
{
public:
	Brick();
	~Brick();

public:
	// ����������
	void Initialize() override;

	/// <summary>
	/// �`�揈��
	/// </summary>
	/// <param name="screen_offset"></param>
	void Draw(const Vector2D& screen_offset)const override;

	// �I��������
	void Finalize() override;
};

