#pragma once

// �V���O���g���e���v���[�g�N���X
template <class T>
class Singleton
{
protected:

	// �N���X�̎��̂������o�֐����ł��������ł��Ȃ��悤�ɂ���
	Singleton() = default;

	// �R�s�[�K�[�h
	Singleton(const Singleton&) = delete;
	Singleton& operator = (const Singleton&) = delete;
	// ~�R�s�[�K�[�h

	~Singleton() = default;

public:
	// �C���X�^���X�̎擾
	static T* GetInstance();
};

// �C���X�^���X�̎擾
template<class T>
inline T* Singleton<T>::GetInstance()
{
	// ���N���X�̃|�C���^�i���̂��A�h���X�̐�ŕۗL�j
	static T* instance = nullptr;

	// �C���X�^���X����������Ă��Ȃ��ꍇ�A��������
	if (instance == nullptr)
	{
		instance = new T();
	}

	// �C���X�^���X�̃|�C���^��ԋp����
	return instance;
}