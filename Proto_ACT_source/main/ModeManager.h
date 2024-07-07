#pragma once
#include "ModeBase.h"
#include "..\camera\Camera.h"
#include "..\system\EnvSetting.h"
#include "..\system\Fps.h"
#include "..\system\Image.h"
#include "..\system\Key.h"
#include "..\system\Sound.h"
#include <memory>
#include <stack>
#include <thread>

class ModeBase;
class Camera;
class EffectManager;
class DataSetting;
class Key;
class Sound;
class Image;
class Fps;

class ModeManager {
private:
	std::shared_ptr<EnvSetting> setting; //設定関連
	std::shared_ptr<Key> key; //キー関連
	std::shared_ptr<Sound> sound; //音関連
	std::shared_ptr<Image> image; //画像関連
	std::shared_ptr<Fps> fps; //FPS関連
	std::shared_ptr<Camera> camera; //カメラ関連

	std::vector<std::thread> load; //ロードのスレッド

	NextMode next; //次の画面
	bool blackout_flag; //暗転中か
	int blackout_time; //暗転時間
	bool erase; //今のモードを終了するか
	int stage_num; //選択したステージ番号

	std::stack<std::shared_ptr<ModeBase>> scene_stack; //シーンのスタック
	std::shared_ptr<ModeBase> scene_next; //次のシーン

	void Blackout(); //暗転
	
public:
	ModeManager(); //コンストラクタ
	~ModeManager(); //デストラクタ
	void Setting(); //初期設定
	int GetStageNum(); //ステージ番号を取得
	void SetStageNum(int set_num); //ステージ番号を設定
	void ChangeMode(NextMode nmode, bool erase_now = false); //次のモードにする(現在モードを消去するか)
	void Update(); //更新
	void Draw(); //描画
};