#include "GameObjectBase.h"
#include "DxLib.h"

#include "GameObjectManager.h"
#include "../Utility/ResourceManager.h"
#include "../Application/Application.h"

GameObjectBase::GameObjectBase() :
	owner_scene(nullptr),
	location(0.0f),
	image(NULL),
	z_layer(0),
	is_mobility(false),
	is_destroy(false),
	animation_count(0),
	animation_time(0.0f),
	box_size(0.0f)
{
}

GameObjectBase::~GameObjectBase()
{
}

// ����������
void GameObjectBase::Initialize()
{
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="delata_second">�P�t���[��������̎���</param>
void GameObjectBase::Update(float delata_second)
{
	// �E�B���h�E�O�I�u�W�F�N�g�̍폜
	// �n�ʃI�u�W�F�N�g�̔z�u�ʒu�̊֌W��-400�ȉ��ɂȂ�����
	GameObjectManager* objm = Singleton<GameObjectManager>::GetInstance();
	if (this->location.x <= -400)
	{
		objm->DestroyGameObject(this);
	}
	if (this->location.y >= 720 + this->GetBoxSize().y)
	{
		objm->DestroyGameObject(this);
	}
}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="delta_second"></param>
/// <returns></returns>
void GameObjectBase::Draw(const Vector2D& screen_offset) const
{
	// �I�t�Z�b�g�l����ɉ摜�̕`����s��
	Vector2D graph_location = this->location + screen_offset;
	DrawRotaGraphF(graph_location.x, graph_location.y, 1.5, 0.0, image, TRUE);
}

// �I���������i�g�����C���X�^���X�Ȃǂ̍폜�j
void GameObjectBase::Finalize()
{
	GameObjectManager::DeleteInstance();
}

/// <summary>
/// �q�b�g�����Ƃ��̏���
/// </summary>
/// <param name="hit_object">�v���C���[���Ƃ�����A�����͓G�Ƃ��u���b�N�Ɠ����������ƂɂȂ�</param>
void GameObjectBase::OnHitCollision(GameObjectBase* hit_object)
{
}

/// <summary>
/// �A�j���[�V��������
/// </summary>
/// <param name="delta_second">�P�t���[��������̎���</param>
/// <param name="animation_image">�A�j���[�V�������摜</param>
/// <param name="animation_num">�A�j���[�V��������</param>
void GameObjectBase::AnimationControl(float delta_second, std::vector<int>& animation_image, std::vector<int>& animation_num)
{
	//�t���[�����[�g�Ŏ��Ԃ��v��
	animation_time += delta_second;
	//8�b�o������摜��؂�ւ���
	if (animation_time >= (1.0f / 16.0f))
	{
		//�v�����Ԃ̏�����
		animation_time = 0.0f;
		//���Ԍo�߃J�E���g�̑���
		animation_count++;
		//�J�E���g���A�j���[�V�����摜�̗v�f���ȏ�ɂȂ�����
		if (animation_count >= animation_num.size())
		{
			//�J�E���g�̏�����
			animation_count = 0;
		}
		// �A�j���[�V���������Ԃɑ�������
		image = animation_image[animation_num[animation_count]];
	}
}

/// <summary>
/// �摜�̐ݒ�
/// </summary>
/// <param name="delta_second">�P�t���[��������̎���</param>
/// <param name="animation_imag">�`�悵�����P�̉摜</param>
void GameObjectBase::AnimationControl(float delta_second, int animation_imag)
{
	image = animation_imag;
}

void GameObjectBase::SetOwnerScene(GameObjectManager* scene)
{
	this->owner_scene = scene;
}

/// <summary>
/// �ʒu���W�̐ݒ�
/// </summary>
/// <param name="location">�ݒ肵�����ʒu</param>
void GameObjectBase::SetLocation(const Vector2D& location)
{
	this->location = location;
}

/// <summary>
/// ���݂̈ʒu���W���擾����
/// </summary>
/// <returns>���݈ʒu</returns>
Vector2D& GameObjectBase::GetLocation()
{
	return location;
}

Vector2D& GameObjectBase::GetVelocity()
{
	return velocity;
}

void GameObjectBase::SetVelocity(float scroll)
{
	this->location.x = scroll;
}

/// <summary>
/// �I�u�W�F�N�g�T�C�Y�̎擾
/// </summary>
/// <returns>�I�u�W�F�N�g�̃T�C�Y</returns>
Vector2D& GameObjectBase::GetBoxSize()
{
	return box_size;
}

/// <summary>
/// �I�u�W�F�N�g�������Ă�R���W�������i����ƉE���̓_�Ƃ��j�̎擾
/// </summary>
/// <returns>�I�u�W�F�N�g�������Ă�R���W�������i����ƉE���̓_�Ƃ��j</returns>
const BoxCollision& GameObjectBase::GetCollision() const
{
	return collision;
}

const unsigned char GameObjectBase::GetZLayer() const
{
	return z_layer;
}

// ����
const bool& GameObjectBase::GetMobility() const
{
	return is_mobility;
}