#pragma once
#include "ModeBase.h"
#include "..\effect\EffectManager.h"
#include <vector>
#include <iostream>
#include <string>
#include <sstream>

class Opening : public ModeBase {
private:

	int logo; //ロゴのハンドル
	int pal; //ロゴの透明度
	int time; //タイマー

public:
	Opening(ModeManager* modeman, std::shared_ptr<EnvSetting> set, std::shared_ptr<Key> k, std::shared_ptr<Sound> sou, std::shared_ptr<Image> img, std::shared_ptr<Fps> f, std::shared_ptr<Camera> cam);
	~Opening(); //デストラクタ
	void Load(); //事前のロード
	void Update(); //更新
	void Draw(); //描画
};