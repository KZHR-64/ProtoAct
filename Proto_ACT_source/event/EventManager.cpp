#pragma once
#include "DxLib.h"
#include "EventManager.h"
#include "eventlist\WaitEvent.h"
#include "eventlist\ClearEvent.h"
#include "eventlist\MissEvent.h"
#include "eventlist\TalkEvent.h"
#include "eventlist\ScrollSettingEvent.h"
#include "eventlist\PlayerMoveEvent.h"
#include "eventlist\EnemySettingEvent.h"
#include "eventlist\EffectSettingEvent.h"
#include "eventlist\PlayMusicEvent.h"
#include "eventlist\WaitBattleEvent.h"
#include "eventlist\ScrollResetEvent.h"
#include <math.h>

using namespace std;

EventManager::EventManager(){
	message_font = CreateFontToHandle("Meiryo UI", 20, 8, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, -1, 1); //フォント情報
	
	x = 0.0f;
	y = 0.0f;

	enemy_stop = false;
	player_stop = false;
	clear_flag = false;
	restart_flag = false;
}

EventManager::~EventManager(){
	//スタックを全開放
	while (!event_queue.empty())
	{
		event_queue.pop();
	}
	event_data.clear();
	DeleteFontToHandle(message_font);
}

//イベントを用意
void EventManager::SetStandby(string file_name) {

	int num;

	ifstream ifs(file_name);

	//なければ終了
	if (ifs.fail()) {
		DebugBreak();
	}

	string str, s;
	//ファイルから一行読み
	while (getline(ifs, str)) {
		// 改行コードを削除
		if (str[str.size() - 1] == '\n') str.erase(str.size() - 1);
		if (str[str.size() - 1] == '\r') str.erase(str.size() - 1);

		stringstream ss{ str };
		getline(ss, s, ','); //カンマまで読み込む
		num = atoi(s.c_str()); //番号を取得
		getline(ss, s, ','); //カンマまで読み込む
		event_data[num].position = (atoi(s.c_str()) == 1); //番号を取得
		getline(ss, s, ','); //カンマまで読み込む
		event_data[num].file_name = s; //使用するファイル名を取得
	}
	ifs.close();
}

//イベントを予約
void EventManager::SetEvent(int num) {
	shared_ptr<AbstractEvent> new_event;
	switch (num)
	{
	case 0:
		new_event = make_shared<WaitEvent>(this, 30, true, true);
		break;
	case 1:
		new_event = make_shared<ClearEvent>(this, 180, true, false);
		break;
	case 2:
		new_event = make_shared<MissEvent>(this, 180, true, false);
		break;
	default:
		new_event = make_shared<WaitEvent>(this, 30, true, true);
		break;
	}
	event_queue.push(new_event);

	//今入れたのが最初なら開始
	if (1 == event_queue.size()) {
		EventStart();
	}
}

//イベントを複数予約(ファイル番号)
void EventManager::SetEventList(int num, float ini_x, float ini_y) {

	int event_size = (int)event_queue.size(); //現在のイベント数

	//座標を設定
	x = ini_x;
	y = ini_y;

	ifstream ifs(event_data[num].file_name);

	//なければ終了
	if (ifs.fail()) {
		DebugBreak();
	}

	string str, s[4];
	//ファイルから一行読み
	while (getline(ifs, str)) {
		shared_ptr<AbstractEvent> new_event;

		// 改行コードを削除
		if (str[str.size() - 1] == '\n') str.erase(str.size() - 1);
		if (str[str.size() - 1] == '\r') str.erase(str.size() - 1);

		stringstream ss{ str };
		getline(ss, s[0], ','); //カンマまで読み込む
		getline(ss, s[1], ','); //カンマまで読み込む
		getline(ss, s[2], ','); //カンマまで読み込む
		getline(ss, s[3], ','); //カンマまで読み込む

		switch (atoi(s[0].c_str()))
		{
		case 0:
			new_event = make_shared<WaitEvent>(this, atoi(s[1].c_str()), atoi(s[2].c_str()) == 1, atoi(s[3].c_str()) == 1);
			break;
		case 1:
			new_event = make_shared<ClearEvent>(this, 180, true, false);
			break;
		case 2:
			new_event = make_shared<MissEvent>(this, 180, true, false);
			break;
		case 3:
			new_event = make_shared<TalkEvent>(this, s[1], s[2], true, true);
			break;
		case 4:
			new_event = make_shared<PlayerMoveEvent>(this, (float)atof(s[1].c_str()), (float)atof(s[2].c_str()), (float)atof(s[3].c_str()), true, true);
			break;
		case 5:
			new_event = make_shared<EnemySettingEvent>(this, atoi(s[1].c_str()), (float)atof(s[2].c_str()), (float)atof(s[3].c_str()), true, true);
			break;
		case 6:
			new_event = make_shared<EffectSettingEvent>(this, atoi(s[1].c_str()), (float)atof(s[2].c_str()), (float)atof(s[3].c_str()), true, true);
			break;
		case 7:
			new_event = make_shared<PlayMusicEvent>(this, atoi(s[1].c_str()), true, true);
			break;
		case 8:
			new_event = make_shared<WaitBattleEvent>(this, false, false);
			break;
		case 9:
			new_event = make_shared<ScrollSettingEvent>(this, atoi(s[1].c_str()), atoi(s[2].c_str()), true, true);
			break;
		case 10:
			new_event = make_shared<ScrollResetEvent>(this, true, true);
			break;
		default:
			new_event = make_shared<WaitEvent>(this, 30, true, true);
			break;
		}
		event_queue.push(new_event);
	}
	ifs.close();

	enemy_stop = true;
	player_stop = true;

	//前にイベントがなければ開始
	if (event_size == 0) {
		EventStart();
	}
}

//初期化
void EventManager::Reset(){
	enemy_stop = false;
	player_stop = false;
	clear_flag = false;
	restart_flag = false;
	//スタックを全開放
	while (!event_queue.empty())
	{
		event_queue.pop();
	}
	event_data.clear();
}

//イベントを開始
void EventManager::EventStart() {
	//停止フラグを設定
	if (event_queue.empty()) {
		player_stop = false;
		enemy_stop = false;
		return;
	}
	player_stop = event_queue.front()->GetPlayerStop();
	enemy_stop = event_queue.front()->GetEnemyStop();
}

//終了したイベントを消去
void EventManager::EventEnd() {
	//停止フラグを解除
	player_stop = false;
	enemy_stop = false;

	event_queue.pop();

	//次があれば開始
	if (1 <= event_queue.size()) {
		EventStart();
	}
}

//イベントを全て消去
void EventManager::AllEventEnd() {
	//停止フラグを解除
	enemy_stop = false;
	player_stop = false;
	//スタックを全開放
	while (!event_queue.empty())
	{
		event_queue.pop();
	}
}

//自機を止めるか取得
bool EventManager::GetPlayerStop() {
	return player_stop;
}

//自機を止めるか設定
void EventManager::SetPlayerStop(bool flag) {
	player_stop = flag;
}

//敵を止めるか取得
bool EventManager::GetEnemyStop() {
	return enemy_stop;
}

//敵を止めるか設定
void EventManager::SetEnemyStop(bool flag) {
	enemy_stop = flag;
}

//クリアしたかを取得
bool EventManager::GetClearFlag() {
	return clear_flag;
}

//クリアしたかを設定
void EventManager::SetClearFlag(bool flag) {
	clear_flag = flag;
}

//やりなおすかを取得
bool EventManager::GetRestartFlag() {
	return restart_flag;
}

//やりなおすかを設定
void EventManager::SetRestartFlag(bool flag) {
	restart_flag = flag;
}

//フォント情報を取得
int EventManager::GetFont() {
	return message_font;
}

//参照する座標を取得
bool EventManager::GetPosition(int num) {
	if (event_data.size() < (unsigned)num) return false;
	return event_data[num].position;
}


//x座標を返す
float EventManager::GetX() {
	return x;
}

//y座標を返す
float EventManager::GetY() {
	return y;
}

//更新
void EventManager::Update(shared_ptr<Player> player, shared_ptr<EnemyManager> enemy, shared_ptr<EffectManager> effect, shared_ptr<MapChipManager> map, shared_ptr<Key> key, shared_ptr<Sound> sound){
	if (event_queue.empty()) return;
	
	int time = event_queue.front()->GetTime();
	if (time == 0 && player_stop) {
		player->SetXSpeed(0.0f);
		player->SetYSpeed(0.0f);
	}
	event_queue.front()->Update(player, enemy, effect, key, sound);
	time++;
	event_queue.front()->SetTime(time);
	//イベントが終了していたら消去
	if (event_queue.front()->GetEndFlag()) {
		EventEnd();
	}
}

//描画
void EventManager::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera){
	/*for (unsigned int i = 0; i < event_data.size(); i++) {
		DrawFormatString(128, 64 + (24 * i), GetColor(255, 0, 0), "%s", event_data[i].file_name);
	}*/

	if (event_queue.size() == 0) return;
	event_queue.front()->Draw(image, camera);

}