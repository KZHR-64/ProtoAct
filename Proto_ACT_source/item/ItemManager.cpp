#pragma once
#include "DxLib.h"
#include "ItemManager.h"
#include "itemlist\DoorKey.h"

using namespace std;

ItemManager::ItemManager() {
	SetData();
}

ItemManager::~ItemManager() {
	item.clear();
	item_data.clear();
}

//初期化
void ItemManager::Reset() {
	item.clear();
}

//アイテム情報の設定
void ItemManager::SetData() {
	int num;
	ifstream ifs("data/item/item_data.csv");

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
		item_data[num].type = atoi(s.c_str()); //種類を取得
		getline(ss, s, ','); //カンマまで読み込む
		item_data[num].image = atoi(s.c_str()); //画像の番号を取得
		getline(ss, s, ','); //カンマまで読み込む
		item_data[num].hit_player = (1 == atoi(s.c_str())); //自機に当たるかを取得
		getline(ss, s, ','); //カンマまで読み込む
		item_data[num].hit_enemy = (1 == atoi(s.c_str())); //敵に当たるかを取得
		getline(ss, s, ','); //カンマまで読み込む
		item_data[num].hit_map = (1 == atoi(s.c_str())); //マップチップに当たるかを取得
	}
	ifs.close();

}

//消えるか確認
void ItemManager::EraseCheck() {
	if (item.size() == 0) return;

	for (auto it = item.begin(); it != item.end();) {
		bool erase_flag = false; //消えるフラグ
		int end_time = (*it)->GetEndTime(); //消えるまでの時間

		//消えるまでの時間が0より大きいなら
		if (0 < end_time) {
			end_time--; //時間を減らす
			//時間が0になったら消える
			if (end_time <= 0) erase_flag = true;
			(*it)->SetEndTime(end_time); //時間を設定
		}

		//消去フラグがtrueなら消去
		if ((*it)->GetEndFlag() || erase_flag) {
			it = item.erase(it);
		}
		else {
			it++;
		}
	}
}

//アイテムをマップに配置
void ItemManager::SetStandby(string file_name) {
	int row = 0; //行
	int col = 0; //列

	ifstream ifs(file_name);
	
	//なければ終了
	if (ifs.fail()) {
		ifs.close();
		return;
	}
	
	string str, s;
	//ファイルから一行読み
	while (getline(ifs, str)) {
		stringstream ss{ str };
		//カンマ区切りで行を読み込み
		while (getline(ss, s, ',')) {

			//読み込んだ数値が-1でなければ
			int num = atoi(s.c_str());
			if (num != -1) {
				//アイテムを配置
				SetItem(num, 32.0f * col, 32.0f * row);
			}
			col++; //列数を増やす
		}

		//列数をリセットして行数を増やす
		col = 0;
		row++;
	}

	ifs.close();
}

//アイテムの配置
shared_ptr<AbstractItem> ItemManager::SetItem(int num, float ini_x, float ini_y) {
	shared_ptr<AbstractItem> new_item;

	switch (item_data[num].type)
	{
	case 0:
		new_item = make_shared<DoorKey>(this, item_data[num].image, ini_x, ini_y);
		break;
	default:
		new_item = make_shared<DoorKey>(this, item_data[num].image, ini_x, ini_y);
		break;
	}

	new_item->SetHitPlayer(item_data[num].hit_player); //自機に当たるか設定
	new_item->SetHitEnemy(item_data[num].hit_enemy); //敵に当たるか設定
	new_item->SetHitMap(item_data[num].hit_map); //マップチップに当たるか設定

	item.emplace_back(new_item);

	return new_item;
}

//マップチップとの当たり判定
void ItemManager::HitCheckMap(shared_ptr<MapChipManager> map) {
	if (item.size() == 0) return;
	for (auto& it : item) {
		if (!it->GetHitMap()) continue;
		it->HitCheckMap(map);
	}
}

//プレイヤーとの当たり判定
void ItemManager::HitCheckPlayer(shared_ptr<Player> player, shared_ptr<EffectManager> effect, shared_ptr<Sound> sound) {
	if (item.size() == 0) return;
	for (auto& it : item) {
		if (!it->GetHitPlayer()) continue;
		//自機に当たっているなら
		if (it->HitCheckPlayer(player)) {
			it->ItemGet(player, effect, sound); //アイテム取得時の処理
			it->SetEndFlag(true); //消滅フラグをtrueに
		}
	}
}

//キャラクターとの当たり判定
shared_ptr<AbstractItem> ItemManager::HitCheckChara(float cx, float cy, float hit_size) {
	if (item.size() == 0) return NULL;
	for (auto& it : item) {
		if (it->HitCheckChara(cx, cy, hit_size)) {
			return it;
		}
	}
	return NULL;
}

//更新
void ItemManager::Update(shared_ptr<Player> player, shared_ptr<EnemyManager> enemy, shared_ptr<EffectManager> effect, shared_ptr<Sound> sound) {
	if (item.size() == 0) return;
	for (auto& it : item) {

		it->Update(player, enemy, effect, sound);

		it->SetX(it->GetX() + it->GetXSpeed());
		it->SetY(it->GetY() + it->GetYSpeed());
		int time = it->GetTime();
		time++;
		it->SetTime(time);
		it->HitUpdate();
	}

	EraseCheck(); //アイテムを消すか確認
}

//描画
void ItemManager::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera) {
	if (item.size() == 0) return;
	for (auto& it : item) {
		it->Draw(image, camera);
		it->DrawHit(camera);
	}
	//DrawFormatString(64, 96, GetColor(255, 255, 255), "%d", item.size());
}