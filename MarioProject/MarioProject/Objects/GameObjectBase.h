#pragma once

#include "../Utility/Vector2D.h"
#include "../Utility/Collision.h"

#define D_OBJECT_SIZE	(24.0f)			// �I�u�W�F�N�g�T�C�Y�i���ʁj

// �I�u�W�F�N���N���X
class GameObjectBase
{
protected:
	class GameObjectManager* owner_scene;   //
	Vector2D location;                      // �I�u�W�F�N�g�̃E�B���h�E�̈ʒu���W
	BoxCollision collision;                 // �����蔻����̕ێ�
	unsigned char z_layer;                  //

public:
	Vector2D box_size;              // �����蔻��T�C�Y

protected:
	int image;                      // �摜�p
	int animation_count;            // ��莞�Ԃ̓��B���̃J�E���g
	float animation_time;           // �A�j���[�V�����̊Ԋu

public:
	bool is_mobility;               //
	bool is_destroy;                // ����ł��邩�ǂ���

public:
	GameObjectBase();
	virtual ~GameObjectBase();

public:
	// ����������
	virtual void Initialize();

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="delta_second">�P�t���[��������̎���</param>
	/// <returns></returns>
	virtual void Update(float delata_second);

	/// <summary>
	/// �`�揈��
	/// </summary>
	/// <param name="delta_second"></param>
	/// <returns></returns>
	virtual void Draw(const Vector2D& screen_offset)const;

	// �I��������
	virtual void Finalize();

public:
	/// <summary>
	/// �q�b�g�����Ƃ��̏���
	/// </summary>
	/// <param name="hit_object">�v���C���[���Ƃ�����A�����͓G�Ƃ��u���b�N�Ɠ����������ƂɂȂ�</param>
	virtual void OnHitCollision(GameObjectBase* hit_object);

	/// <summary>
	/// �A�j���[�V��������
	/// </summary>
	/// <param name="delta_second">�P�t���[��������̎���</param>
	/// <param name="animation_image">�A�j���[�V�������摜</param>
	/// <param name="animation_num">�A�j���[�V��������</param>
	virtual void AnimationControl(float delta_second, std::vector<int>& animation_image, std::vector<int>& animation_num);
	/// <summary>
	/// �摜�̐ݒ�
	/// </summary>
	/// <param name="delta_second">�P�t���[��������̎���</param>
	/// <param name="animation_imag">�`�悵�����P�̉摜</param>
	virtual void AnimationControl(float delta_second, int animation_image);

public:
	void SetOwnerScene(class GameObjectManager* scene); // 
	void SetLocation(const Vector2D& location);         // �ʒu���W��ݒ肷��i��ɃI�u�W�F�N�g�̐����ʒu�����߂�j
	Vector2D& GetLocation();                            // ���݂̈ʒu���W���擾����
	Vector2D& GetBoxSize();                             // �I�u�W�F�N�g�̑傫�����擾����
	const BoxCollision& GetCollision()const;            // �I�u�W�F�N�g���������蔻����i����ƉE���̓_�Ƃ��j���擾����
	const unsigned char GetZLayer()const;               // 
	const bool& GetMobility()const;                     // 
};

