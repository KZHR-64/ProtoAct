#pragma once
#include "ModeManager.h"
#include "KeyConfig.h"

class System {
private:

public:
	System(); //コンストラクタ
	~System(); //デストラクタ
	void Setting(); //初期設定の読み込み
	void Finalize(); //終了
	void Update(); //更新
};