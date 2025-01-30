#pragma once
#include "../BlockBase.h"

// ハテナブロッククラス
class Hatena :
    public BlockBase
{
public:
	std::vector<int> hatena_animation;  // ハテナブロックのアニメーション画像を保持
	bool is_kara;                       // 空かどうか（trueなら空、falseなら空じゃない）

public:
	Hatena();
	~Hatena();

public:
	// 初期化処理
	void Initialize() override;
	// 終了時処理
	void Finalize() override;
};

