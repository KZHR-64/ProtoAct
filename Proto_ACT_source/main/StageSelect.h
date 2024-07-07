#pragma once
#include "ModeBase.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

struct SubTitleStruct
{
	//サブタイトルの構造体
	int hundle; //サムネイルのハンドル
	bool select_flag; //選べるか
	std::string str1; //サブタイトル1行目
	std::string str2; //サブタイトル2行目
};

class StageSelect : public ModeBase {
private:
	void Reset(); //初期化
	void SetData(); //情報の更新
	int stage_num; //選択ステージ
	int cursor_pos_x; //カーソルの位置
	int cursor_pos_y; //カーソルの位置

	int message_font; //フォント情報

	SubTitleStruct subtitle[STAGE_MAX];
public:
	StageSelect(ModeManager* modeman, std::shared_ptr<EnvSetting> set, std::shared_ptr<Key> k, std::shared_ptr<Sound> sou, std::shared_ptr<Image> img, std::shared_ptr<Fps> f, std::shared_ptr<Camera> cam);
	~StageSelect(); //デストラクタ
	void Load(); //事前のロード
	void Update(); //更新
	void Draw(); //描画
};