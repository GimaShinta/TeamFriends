#pragma once
#include "../BlockBase.h"

// �n�e�i�u���b�N�N���X
class Hatena :
    public BlockBase
{
public:
	std::vector<int> hatena_animation;  // �n�e�i�u���b�N�̃A�j���[�V�����摜��ێ�
	int kara_image;
	bool is_kara;                       // �󂩂ǂ����itrue�Ȃ��Afalse�Ȃ�󂶂�Ȃ��j

public:
	Hatena();
	~Hatena();

public:
	// ����������
	void Initialize() override;

	/// <summary>
    /// �X�V����
    /// </summary>
    /// <param name="delata_second">�P�t���[��������̎���</param>
	virtual void Update(float delata_second) override;

	// �I��������
	void Finalize() override;

	/// <summary>
    /// �q�b�g������
    /// </summary>
    /// <param name="hit_object">������������</param>
	virtual void OnHitCollision(GameObjectBase* hit_object) override;

};

