#pragma once
#include "DxLib.h"
#include "ModeManager.h"
#include "Game.h"
#include "StageSelect.h"
#include "Option.h"
#include "KeyConfig.h"
#include "Opening.h"
#include "Menu.h"
#include "Gameover.h"

using namespace std;

ModeManager::ModeManager(){
	//image->LoadEffectImage();
	next = Next_None;
	erase = false;
	blackout_time = 0;
	blackout_flag = false; //暗転状態を初期化
	stage_num = 0; //ステージを初期化

	setting = make_shared<EnvSetting>(); //設定関連のポインタ
	key = make_shared<Key>(); //キー関連のポインタ
	sound = make_shared<Sound>(); //音関連のポインタ
	image = make_shared<Image>(); //画像関連のポインタ
	fps = make_shared<Fps>(); //FPS関連のポインタ
	camera = make_shared<Camera>(); //カメラ関連のポインタ

	sound->SetBgmVolume(setting->GetBgmVolume()); //音量を設定
	sound->SetSoundVolume(setting->GetSoundVolume()); //音量を設定
	fps->SetDrawFlag(setting->GetFpsFlag()); //FPSの表示を設定

}

ModeManager::~ModeManager()
{
	//スタックを全開放
	while (!scene_stack.empty())
	{
		scene_stack.pop();
	}
}

//ステージ番号を取得
int ModeManager::GetStageNum() {
	return stage_num;
}

//ステージ番号を設定
void ModeManager::SetStageNum(int set_num) {
	stage_num = set_num;
}

//初期設定
void ModeManager::Setting() {
	sound->LoadSoundEffect(); //効果音をロード
	image->LoadEffectImage();
	scene_stack.push(make_shared<Opening>(this, setting, key, sound, image, fps, camera)); //始めはオープニング画面
}

//暗転
void ModeManager::Blackout() {
	bool loaded = false; //ロードが完了したか

	blackout_time++; //暗転時間を増加

	//次のモードがあるなら
	if (scene_next && !load.empty()) {
		loaded = scene_next->GetLoaded(); //ロード完了フラグを取得
	}
	//ないなら
	else {
		loaded = true;
	}

	//暗転時間が一定に達し、ロードが完了した場合
	if (60 < blackout_time && loaded) {
		//ロードする内容があるなら
		if (!load.empty()) {
			//終わったことを確認する
			for (auto& l : load) {
				l.join();
			}
		}
		load.clear(); //ロードのスレッドを解放

		//現在のモードを消す場合
		if (erase) {
			scene_stack.pop();
		}
		//前の画面に戻る場合
		if (next == Next_Back) {
			scene_stack.pop(); //スタックをポップ
		}
		else {
			scene_stack.push(scene_next); //次のシーンをスタックに
			scene_next.reset(); //権限を放棄
		}
		blackout_flag = false; //暗転フラグをfalseに
	}
}

//次のモードにする
void ModeManager::ChangeMode(NextMode nmode, bool erase_now){
	next = nmode; //次の場面を設定
	blackout_flag = true; //暗転
	blackout_time = 0; //暗転時間を初期化
	erase = erase_now; //今のモードを消すか
	
	//次に移る
	switch (next) {
	case Next_Opening: //オープニングの場合
		scene_next = make_shared<Opening>(this, setting, key, sound, image, fps, camera); //次のモードを設定
		load.emplace_back(&ModeBase::Load, scene_next.get()); //スレッドにロードを追加
		break;
	case Next_Menu: //メニュー画面の場合
		scene_next = make_shared<Menu>(this, setting, key, sound, image, fps, camera); //次のモードを設定
		load.emplace_back(&ModeBase::Load, scene_next.get()); //スレッドにロードを追加
		break;
	case Next_StageSelect: //ステージセレクト画面の場合
		scene_next = make_shared<StageSelect>(this, setting, key, sound, image, fps, camera); //次のモードを設定
		load.emplace_back(&ModeBase::Load, scene_next.get()); //スレッドにロードを追加
		break;
	case Next_Game: //ゲーム画面の場合
		scene_next = make_shared<Game>(this, setting, key, sound, image, fps, camera); //次のモードを設定
		load.emplace_back(&ModeBase::Load, scene_next.get()); //スレッドにロードを追加
		break;
	case Next_Gameover: //ゲームオーバー画面の場合
		scene_next = make_shared<Gameover>(this, setting, key, sound, image, fps, camera); //次のモードを設定
		load.emplace_back(&ModeBase::Load, scene_next.get()); //スレッドにロードを追加
		break;
	case Next_Option: //オプション画面の場合
		scene_next = make_shared<Option>(this, setting, key, sound, image, fps, camera); //次のモードを設定
		load.emplace_back(&ModeBase::Load, scene_next.get()); //スレッドにロードを追加
		break;
	case Next_Config: //キーコンフィグ画面の場合
		scene_next = make_shared<KeyConfig>(this, setting, key, sound, image, fps, camera); //次のモードを設定
		load.emplace_back(&ModeBase::Load, scene_next.get()); //スレッドにロードを追加
		break;
	case Next_Back: //戻る場合
		break;
	default:
		break;
	}
}

//更新
void ModeManager::Update(){
	key->Update(); //キーを更新
	
	//暗転中の場合
	if (blackout_flag) {
		Blackout(); //暗転処理
	}
	else {
		scene_stack.top()->Update();
	}
}

//描画
void ModeManager::Draw(){
	scene_stack.top()->Draw();

	//暗転中の場合
	if (blackout_flag) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (256 / 60) * blackout_time); //描画モードを反映

		DrawBox(0, 0, WINDOW_X, WINDOW_Y, GetColor(0, 0, 0), true); //画面を暗くする

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //描画モードを戻す
	}

	//DrawFormatString(0, 640, GetColor(0, 0, 255), "%d %d", load.size(), scene_stack.size());

	fps->Draw(); //現在のFPSを描画
	fps->Wait();
}