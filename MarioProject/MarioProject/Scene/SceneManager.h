#pragma once

#include "../Singleton.h"
#include "SceneBase.h"

// シーンの生成と破棄管理、切り替えクラス
class SceneManager : public Singleton<class T>
{
private:
    SceneBase* current_scene;    //シーンの状態を保持

public:
    SceneManager();
    ~SceneManager();

public:
    // インスタンスの削除
    static void DeleteInstance();

public:
    // 初期化処理
    void Initialize();

    /// <summary>
    /// 更新処理
    /// </summary>
    /// <param name="delta_second">1フレーム当たりの時間</param>
    /// <returns></returns>
    bool Update(float delta_second);

    /// <summary>
    /// 描画処理
    /// </summary>
    /// <param name="delta_second">1フレーム当たりの時間</param>
    void Draw(float delta_second);

    //終了時処理
    void Finalize();

public:
    /// <summary>
    /// シーンの切り替え
    /// </summary>
    /// <param name="scene_type">切り替えたいシーンのタイプ</param>
    void ChangeScene(eSceneType scene_type);

private:
    /// <summary>
    /// シーン情報の生成
    /// </summary>
    /// <param name="scene_type">生成したいシーンのタイプ</param>
    /// <returns></returns>
    SceneBase* CreateScene(eSceneType scene_type);
};