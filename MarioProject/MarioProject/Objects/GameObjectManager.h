#pragma once

#include "../Singleton.h"
#include "GameObjectBase.h"

#include <vector>
#include <string>

// �I�u�W�F�N�g�̐����Ɣj�����Ǘ�����N���X
class GameObjectManager : public Singleton<class T>
{
private:
	std::vector<GameObjectBase*> create_object;     // �����������I�u�W�F�N�g������z��i�����z��j
	std::vector<GameObjectBase*> destroy_object;	// �j���������I�u�W�F�N�g������z��i�폜�z��j
	std::vector<GameObjectBase*> game_object;	    // �C���Q�[���ɑ��݂���I�u�W�F�N�g������z��i�C���Q�[���z��j

	Vector2D screen_offset;// �X�N���[���I�t�Z�b�g�̓E�B���h�E��0,0�ʒu����ǂꂾ������Ă���̂��𔻒肷��̂Ɏg����

public:
	GameObjectManager();
	virtual ~GameObjectManager();

public:
	// �C���X�^���X�i�I�u�W�F�N�g�ւ̎Q�Ɓj�̍폜
	static void DeleteInstance();

public:
	// ����������
	virtual void Initialize();

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="delta_second">�P�t���[��������̎���</param>
	/// <returns></returns>
	virtual void Update(const float& delta_second);

	// �`�揈��
	virtual void Draw() const;

	// �I��������
	virtual void Finalize();

	// �����ł���I�u�W�F�N�g�����邩���`�F�b�N
	virtual void CheckCreateObject();

	// �폜�ł���I�u�W�F�N�g�����邩���`�F�b�N
	virtual void CheckDesroyObject();

	//virtual std::vector<GameObjectBase*>& CreateGameObject();

	/// <summary>
	/// �I�u�W�F�N�g�̐���
	/// </summary>
	/// <typeparam name="OBJECT">GameObjectBase���p�������N���X</typeparam>
	/// <param name="generate_location">��������ʒu���W</param>
	/// <returns>���������I�u�W�F�N�g�̃C���X�^���X�i�I�u�W�F�N�g�ւ̎Q�Ɓj</returns>
	template <class OBJECT>
	OBJECT* CreateObject(const Vector2D& generate_location)
	{
		// ��������Q�[���I�u�W�F�N�g�N���X�𓮓I�m��
		OBJECT* new_instance = new OBJECT();
		// GameObjectBase���p�����Ă��邩�m�F
		GameObjectBase* new_object = dynamic_cast<GameObjectBase*>(new_instance);
		// �G���[�`�F�b�N
		if (new_object == nullptr)
		{
			// ���I�m�ۂ����������̊J��
			delete new_instance;
			// ��O�e�L�X�g��ʒm
			throw std::string("�Q�[���I�u�W�F�N�g�������ł��܂���ł���");
			return nullptr;
		}
		// �V�[�����̐ݒ�
		new_object->SetOwnerScene(this);
		// �������ꂽ�I�u�W�F�N�g�̏���������������
		new_object->Initialize();
		// �������ꂽ�I�u�W�F�N�g�̈ʒu����ݒ�
		new_object->SetLocation(generate_location);
		// �����z��̖����Ɋi�[����
		create_object.push_back(new_object);
		// ���������I�u�W�F�N�g�̃|�C���^��Ԃ�
		return new_instance;
	}

	/// <summary>
	/// �I�u�W�F�N�g���폜����
	/// </summary>
	/// <param name="target">�폜�������I�u�W�F�N�g</param>
	void DestroyGameObject(GameObjectBase* target);

public:
	/// <summary>
	/// �����蔻��̃`�F�b�N
	/// </summary>
	/// <param name="target">�v���C���[</param>
	/// <param name="partner">�G�Ƃ��u���b�N�Ƃ�</param>
	virtual void CheckCollision(GameObjectBase* target, GameObjectBase* partner);

	// 
	const Vector2D GetScreenOffset() const;

private:
	// �C���Q�[���ɑ��݂���S�ẴI�u�W�F�N�g���폜
	void DestoryAllObject();

};
