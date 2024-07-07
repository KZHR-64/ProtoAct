#pragma once
#include "ModeBase.h"

struct ChoiceStruct
{
	//選択肢の構造体
	int image; //使用する画像
	float ex_rate; //表示倍率
};

class Menu : public ModeBase {
private:
	int count; //カウンター
	int cursor_pos; //カーソルの位置
	int logo; //タイトルロゴ

	ChoiceStruct choice[4]; //選択肢

	void Reset(); //初期化
public:
	Menu(ModeManager* modeman, std::shared_ptr<EnvSetting> set, std::shared_ptr<Key> k, std::shared_ptr<Sound> sou, std::shared_ptr<Image> img, std::shared_ptr<Fps> f, std::shared_ptr<Camera> cam);
	~Menu(); //デストラクタ
	void Load(); //事前のロード
	void Update(); //更新
	void Draw(); //描画
};