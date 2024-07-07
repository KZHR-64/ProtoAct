#pragma once
#include "ModeBase.h"
#include <iostream>
#include <string>
#include <sstream>

class KeyConfig : public ModeBase {
private:

	int message_font; //フォント情報

	std::map<int, std::string> key_map; //キーの番号に対応する文字

	int key_cursor; //カーソルの位置(キーコンフィグ)
	int pad_cursor; //カーソルの位置(パッドコンフィグ)

	Key_Func button[BUTTON]; //対応するボタン

	void Reset(); //初期化

public:
	KeyConfig(ModeManager* modeman, std::shared_ptr<EnvSetting> set, std::shared_ptr<Key> k, std::shared_ptr<Sound> sou, std::shared_ptr<Image> img, std::shared_ptr<Fps> f, std::shared_ptr<Camera> cam);
	~KeyConfig(); //デストラクタ
	void Load(); //事前のロード
	void Update(); //更新
	void Draw(); //描画
};