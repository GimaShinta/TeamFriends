#pragma once
#include "../BlockBase.h"

// �j��s�u���b�N�N���X
class Kai :
    public BlockBase
{
public:
	Kai();
	~Kai();

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

