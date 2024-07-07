#pragma once
#include "ModeBase.h"

class GameBase;

class Gameover : public ModeBase {
private:
	void Reset(); //初期化
	
	int cursor_pos; //カーソルの位置
	int select_hundle[2]; //選択肢の画像

public:
	Gameover(ModeManager* modeman, std::shared_ptr<EnvSetting> set, std::shared_ptr<Key> k, std::shared_ptr<Sound> sou, std::shared_ptr<Image> img, std::shared_ptr<Fps> f, std::shared_ptr<Camera> cam);
	~Gameover(); //デストラクタ
	void Load(); //事前のロード
	void Update(); //更新
	void Draw(); //描画
};