#pragma once

#include "../BlockBase.h"

// �n�ʃN���X
class Ground : public BlockBase
{
public:
	Ground();
	~Ground();

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

