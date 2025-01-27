#pragma once

#include "../Singleton.h"
#include "SceneBase.h"

// �V�[���̐����Ɣj���Ǘ��A�؂�ւ��N���X
class SceneManager : public Singleton<class T>
{
private:
    SceneBase* current_scene;    //�V�[���̏�Ԃ�ێ�

public:
    SceneManager();
    ~SceneManager();

public:
    // �C���X�^���X(�I�u�W�F�N�g�ւ̎Q��)�̍폜
    static void DeleteInstance();

public:
    // ����������
    void Initialize();

    /// <summary>
    /// �X�V����
    /// </summary>
    /// <param name="delta_second">1�t���[��������̎���</param>
    /// <returns></returns>
    bool Update(float delta_second);

    /// <summary>
    /// �`�揈��
    /// </summary>
    /// <param name="delta_second">1�t���[��������̎���</param>
    void Draw(float delta_second);

    // �I��������
    void Finalize();

public:
    /// <summary>
    /// �V�[���̐؂�ւ�
    /// </summary>
    /// <param name="scene_type">�؂�ւ������V�[���̃^�C�v</param>
    void ChangeScene(eSceneType scene_type);

private:
    /// <summary>
    /// �V�[�����̐���
    /// </summary>
    /// <param name="scene_type">�����������V�[���̃^�C�v</param>
    /// <returns></returns>
    SceneBase* CreateScene(eSceneType scene_type);
};