#pragma once
#include "ModeBase.h"

struct SettingStruct{
	//設定の構造体
	bool fps_flag;		//FPSを表示するか
	int volume_bgm;		//BGMの音量
	int volume_effect;	//効果音の音量
};

class Option : public ModeBase {
private:

	int cursor_pos; //カーソルの位置
	int count; //キーを押しているフレーム数
	int on_hundle; //ONのハンドル
	int off_hundle; //OFFのハンドル
	int graduation_hundle; //音量目盛のハンドル

	SettingStruct data_set;
	
	void Reset(); //初期化
	void SaveSetting(); //設定の保存

public:
	Option(ModeManager* modeman, std::shared_ptr<EnvSetting> set, std::shared_ptr<Key> k, std::shared_ptr<Sound> sou, std::shared_ptr<Image> img, std::shared_ptr<Fps> f, std::shared_ptr<Camera> cam);
	~Option(); //デストラクタ
	void Load(); //事前のロード
	void Update(); //更新
	void Draw(); //描画
};