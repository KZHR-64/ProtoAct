#pragma once
#include "ModeBase.h"

using namespace std;

ModeBase::ModeBase(ModeManager* modeman, shared_ptr<EnvSetting> set, shared_ptr<Key> k, shared_ptr<Sound> sou, shared_ptr<Image> img, shared_ptr<Fps> f, std::shared_ptr<Camera> cam) {

	modemanager = modeman;//シーン移行マネージャ
	setting = set; //設定関連
	key = k; //キー関連
	sound = sou; //音関連
	image = img; //画像関連
	fps = f; //FPS関連
	camera = cam; //カメラ関連

	loaded = false; //ロードしたフラグをfalseに
	start_flag = true; //切替直後フラグをtrueに

}

ModeBase::~ModeBase() {
	key.reset(); //権限を放棄
	sound.reset(); //権限を放棄
	image.reset(); //権限を放棄
	fps.reset(); //権限を放棄
	camera.reset(); //権限を放棄
}

//ロードが完了したか返す
bool ModeBase::GetLoaded() {
	return loaded;
}