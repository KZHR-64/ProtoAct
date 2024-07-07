#pragma once
#include "DxLib.h"
#include "EffectManager.h"
#include "effectlist/BlackOut.h"
#include "effectlist/Explode.h"
#include "effectlist/Smoke.h"
#include "effectlist/LightSphere.h"
#include "effectlist/MarkPoint.h"
#include <math.h>

using namespace std;

EffectManager::EffectManager(){
	SetData();
}

EffectManager::~EffectManager(){
	effect_data.clear();
	effect.clear();
}

//初期化
void EffectManager::Reset(){
	effect.clear();
}

//弾情報の設定
void EffectManager::SetData() {
	int num;
	ifstream ifs("data/effect/effect_data.csv");

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
		effect_data[num].type = atoi(s.c_str()); //種類を取得
		getline(ss, s, ','); //カンマまで読み込む
		effect_data[num].image = atoi(s.c_str()); //画像の番号を取得
	}
	ifs.close();

}

//エフェクトの配置
std::shared_ptr<AbstractEffect> EffectManager::SetEffect(int num, float ini_x, float ini_y, float ini_rate) {
	std::shared_ptr<AbstractEffect> new_effect;

	switch (effect_data[num].type)
	{
	case 0:
		new_effect = make_shared<BlackOut>(this, effect_data[num].image, ini_x, ini_y);
		break;
	case 1:
		new_effect = make_shared<Explode>(this, effect_data[num].image, ini_x, ini_y);
		break;
	case 2:
		new_effect = make_shared<Smoke>(this, effect_data[num].image, ini_x, ini_y);
		break;
	case 3:
		new_effect = make_shared<LightSphere>(this, effect_data[num].image, ini_x, ini_y);
		break;
	case 4:
		new_effect = make_shared<MarkPoint>(this, effect_data[num].image, ini_x, ini_y);
		break;
	default:
		new_effect = make_shared<Explode>(this, effect_data[num].image, ini_x, ini_y);
		break;
	}

	new_effect->SetExRate(ini_rate);

	effect.emplace_back(new_effect);

	return new_effect;
}

//更新
void EffectManager::Update(shared_ptr<Sound> sound){
	if (effect.size() == 0) return;
	for (auto& eff : effect) {
		eff->Update(sound);
		eff->SetX(eff->GetX() + eff->GetXSpeed());
		eff->SetY(eff->GetY() + eff->GetYSpeed());
		int time = eff->GetTime();
		time++;
		eff->SetTime(time);
	}

	for (auto eff = effect.begin(); eff != effect.end();) {
		//消去フラグがtrueなら消去
		if ((*eff)->GetEndFlag()) {
			eff = effect.erase(eff);
		}
		else {
			eff++;
		}
	}
}

//描画
void EffectManager::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera){
	if (effect.size() == 0) return;
	for (auto& eff : effect) {
		eff->Draw(image, camera);
	}
}