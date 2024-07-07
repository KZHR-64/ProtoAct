#pragma once
#include "ModeManager.h"
#include "..\tool\Display.h"
#include "..\tool\Calculation.h"
#include "..\camera\Camera.h"
#include "..\system\EnvSetting.h"
#include "..\system\Image.h"
#include "..\system\Key.h"
#include "..\system\Sound.h"
#include <memory>
#include <thread>
#include <vector>

class ModeManager;
class EffectManager;
class Camera;
class EnvSetting;
class Key;
class Sound;
class Image;

class ModeBase{
protected:
	ModeManager* modemanager; //シーン切替を伝えるポインタ
	std::shared_ptr<EnvSetting> setting; //設定関連のポインタ
	std::shared_ptr<Key> key; //キー関連のポインタ
	std::shared_ptr<Sound> sound; //音関連のポインタ
	std::shared_ptr<Image> image; //画像関連のポインタ
	std::shared_ptr<Fps> fps; //FPS関連のポインタ
	std::shared_ptr<Camera> camera; //カメラ関連のポインタ

	bool loaded; //ロードが完了したか
	bool start_flag; //切替直後か
public:
	ModeBase(ModeManager* modeman, std::shared_ptr<EnvSetting> set, std::shared_ptr<Key> k, std::shared_ptr<Sound> sou, std::shared_ptr<Image> img, std::shared_ptr<Fps> f, std::shared_ptr<Camera> cam);
	virtual ~ModeBase();
	bool GetLoaded(); //ロードが完了したか返す
	virtual void Load() = 0; //事前のロード
	virtual void Update() = 0; //更新
	virtual void Draw() = 0; //描画
};