#pragma once
#include "../BlockBase.h"

// �n�e�i�u���b�N�N���X
class Hatena :
    public BlockBase
{
public:
	std::vector<int> hatena_animation;  // �n�e�i�u���b�N�̃A�j���[�V�����摜��ێ�
	bool is_kara;                       // �󂩂ǂ����itrue�Ȃ��Afalse�Ȃ�󂶂�Ȃ��j

public:
	Hatena();
	~Hatena();

public:
	// ����������
	void Initialize() override;
	// �I��������
	void Finalize() override;
};

