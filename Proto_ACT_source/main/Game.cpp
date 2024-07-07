#pragma once
#include "DxLib.h"
#include "Game.h"

using namespace std;

Game::Game(ModeManager* modeman, shared_ptr<EnvSetting> set, shared_ptr<Key> k, shared_ptr<Sound> sou, shared_ptr<Image> img, shared_ptr<Fps> f, shared_ptr<Camera> cam) : ModeBase(modeman, set, k, sou, img, f, cam) {
	stage_num = modemanager->GetStageNum();

	image->LoadCharaImage(); //キャラの画像をロード
	image->LoadMapchipImage(); //マップチップの画像をロード
	image->LoadBulletImage(); //弾の画像をロード
	image->LoadItemImage(); //アイテムの画像をロード
	player = make_shared<Player>();
	map = make_shared<MapChipManager>(stage_num);
	enemy = make_shared<EnemyManager>();
	bullet = make_shared<BulletManager>();
	item = make_shared<ItemManager>();
	event = make_shared<EventManager>();
	effect = make_shared<EffectManager>();

	live = 2; //残機を設定
	pause_flag = false; //ポーズ画面は閉じている
	cursor = 0; //カーソルを初期化

	map->MakeMap(player, enemy, item, event, image, sound, camera);
}

Game::~Game(){
	player.reset();
	map.reset();
	enemy.reset();
	bullet.reset();
	item.reset();
	event.reset();
	camera.reset();

	image->DeleteCharaImage();
	image->DeleteMapchipImage();
	image->DeleteBulletImage();
	image->DeleteItemImage();
	sound->StopBgm();
}

//事前のロード
void Game::Load() {
	if (loaded) return; //ロード済みなら終了

	loaded = true; //ロードしたフラグをtrueに
}

//再開
void Game::Restart() {
	player->Reset();
	event->Reset();
	enemy->Reset();
	bullet->Reset();
	effect->Reset();
	item->Reset();

	map->MakeMap(player, enemy, item, event, image, sound, camera);
}

//ゲームの更新
void Game::GameUpdate() {

	bool player_stop = event->GetPlayerStop();
	bool enemy_stop = event->GetEnemyStop();

	camera->SetScrollX(player->GetX());
	camera->SetScrollY(player->GetY());
	
	if (!player_stop) {
		map->Update(player, enemy, bullet, effect, image, key, sound, camera); //マップの更新
	}
	map->EventHitCheck(event, player->GetX(), player->GetY());
	event->Update(player, enemy, effect, map, key, sound);

	player_stop = event->GetPlayerStop();
	enemy_stop = event->GetEnemyStop();
	
	if (!player_stop) {
		player->Update(effect, key, sound); //自機の更新
	}
	item->Update(player, enemy, effect, sound); //アイテムの更新
	map->AdjustPosition(); //マップの位置調整
	player->AdjustPosition(map, (player_stop || enemy_stop)); //自機の位置調整
	if (!player_stop) {
		player->AttackCheck(bullet, effect, key, sound); //自機の攻撃
	}
	if (!enemy_stop) {
		enemy->Update(map, bullet, player, effect, sound, camera); //敵の更新
	}
	bullet->Update(player, enemy, item, effect, key, sound, camera); //弾の更新

	effect->Update(sound); //エフェクトの更新

	item->HitCheckPlayer(player, effect, sound);
	bullet->HitCheckMap(map);
	enemy->HitCheckBullet(bullet, effect, sound);
	//enemy->HitCheckEnemy(effect);
	player->HitCheckEnemy(enemy, effect, sound);
	player->HitCheckBullet(bullet, sound);

	enemy->SpawnCheck(camera);

	//マップ移動の操作が行われているか確認
	map->WarpHitCheck(event, key, sound, player->GetX(), player->GetY());

	//ワープ条件が揃ったら
	if (map->GetWarpFlag() && !event->GetPlayerStop()) {
		Restart(); //次のマップから再開
	}

	//まだクリア判定が出ていない状態で、ボスを倒したなら
	if (!event->GetClearFlag() && enemy->GetBeatBoss()) {
		event->SetEvent(1); //クリア動作のイベントを開始
	}

	//ミスしたなら
	if (player->GetHp() <= 0 && !player_stop) {
		event->AllEventEnd();
		event->SetEvent(2); //ミス動作のイベントを開始
	}

	//+が押されているなら
	if (key->KeyCheckOnce(Plus) /*&& !player_stop*/) {
		sound->PlaySoundEffect(1); //効果音を鳴らす
		pause_flag = true; //ポーズ画面を開く
	}
}

//ポーズ画面の更新
void Game::PauseUpdate() {
	//上か下が押されているなら
	if (key->KeyCheckOnce(Up) || key->KeyCheckOnce(Down)) {
		cursor = (cursor + 1) % 2; //カーソルを移動
	}

	//決定が押されているなら
	if (key->KeyCheckOnce(Jump)) {
		switch (cursor)
		{
		case 0:
			pause_flag = false; //ポーズ画面を閉じる
			break;
		case 1:
			//event->SetClearFlag(true); //ステージセレクトに戻るようにする
			modemanager->ChangeMode(Next_Back); //一つ前の画面に戻る
			break;
		default:
			break;
		}
	}

	//+が押されているなら
	if (key->KeyCheckOnce(Plus)) {
		pause_flag = false; //ポーズ画面を閉じる
	}
}

//更新
void Game::Update(){

	//ポーズ状態なら
	if (pause_flag) {
		PauseUpdate(); //ポーズ画面の更新
	}
	//そうでなければ
	else {
		GameUpdate(); //ゲームの更新
	}

	//クリアしたなら
	if (event->GetClearFlag()) {
		modemanager->ChangeMode(Next_Back); //一つ前の画面に戻る
	}

	//やりなおすなら
	if (event->GetRestartFlag()) {
		live--; //残機を減らす
		//残機があるなら
		if (0 <= live) {
			Restart(); //ミスしたマップから再開する
		}
		else
		{
			modemanager->ChangeMode(Next_Gameover, true); //モードをゲームオーバーに変更
		}
	}
}

//描画
void Game::Draw(){
	map->Draw(image, camera);
	enemy->Draw(image, camera);
	player->Draw(image, camera);
	item->Draw(image, camera);
	bullet->Draw(image, camera);
	effect->Draw(image, camera);
	event->Draw(image, camera);
	//DrawFormatString(0, 0, GetColor(0, 0, 255), "ゲーム%d%d%d%d", stage_num, enemy->GetBeatBoss(), enemy->GetBossFlag(), event->GetPlayerStop());

	//ポーズ状態なら
	if (pause_flag) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128); //描画モードを反映

		DrawBox(0, 0, WINDOW_X, WINDOW_Y, GetColor(0, 0, 0), true); //画面を暗くする

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //描画モードを戻す
		DrawFormatString(320, 240, GetColor(0, 0, 255), "ポーズ%d", cursor);
	}
}