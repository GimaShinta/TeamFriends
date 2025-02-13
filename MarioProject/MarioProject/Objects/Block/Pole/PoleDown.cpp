#include "PoleDown.h"

#include "../../../Utility/ResourceManager.h"

PoleDown::PoleDown()
{
}

PoleDown::~PoleDown()
{
}

// ����������
void PoleDown::Initialize()
{
	// ����t���O�̃I��
	is_mobility = true;

	//�摜�̐ݒ�
	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();
	image = rm->GetImages("Resource/Images/pole_down.png")[0];

	//�����蔻��̐ݒ�
	collision.is_blocking = true;
	collision.object_type = eObjectType::eGoal;
	collision.hit_object_type.push_back(eObjectType::ePlayer);

	// �����蔻��T�C�Y�̐ݒ�
	box_size = D_OBJECT_SIZE;
}

// �X�V����
void PoleDown::Update(float delta_second)
{
}

// �I��������
void PoleDown::Finalize()
{
	ResourceManager::DeleteInstance();
}

void PoleDown::OnHitCollision(GameObjectBase* hit_object)
{
}
