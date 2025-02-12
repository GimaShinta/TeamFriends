#pragma once
#include "../BlockBase.h"

// �n�e�i�u���b�N�N���X
class Hatena :
    public BlockBase
{
private:
	int kara_image;
	bool is_kara;                       // �󂩂ǂ����itrue�Ȃ��Afalse�Ȃ�󂶂�Ȃ��j

private:
	std::vector<int> hatena_animation;  // �n�e�i�u���b�N�̃A�j���[�V�����摜��ێ�

private:
	std::vector<int> hatena_animation_num = { 0,1,2,3,2,1 }; // �A�j���[�V�����̏���

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
	virtual void Update(float delta_second) override;

	// �I��������
	void Finalize() override;

	/// <summary>
    /// �q�b�g������
    /// </summary>
    /// <param name="hit_object">������������</param>
	virtual void OnHitCollision(GameObjectBase* hit_object) override;

};

