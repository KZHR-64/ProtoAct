#pragma once
#include "../character/CharacterBase.h"
#include "../Define.h"
#include "AbstractEffect.h"
#include "../camera/Camera.h"
#include <map>
#include <list>
#include <queue>
#include <memory>

class AbstractEffect;
class Camera;

struct EffectDataStruct
{
	//エフェクト情報の構造体
	int type; //種類
	int image; //表示する画像
};

class EffectManager {
private:
	std::map<int, EffectDataStruct> effect_data; //エフェクト情報
	std::list<std::shared_ptr<AbstractEffect>> effect; //エフェクト
	
	void SetData(); //エフェクト情報の設定

public:
	EffectManager(); //コンストラクタ
	~EffectManager(); //デストラクタ
	void Reset(); //初期化
	std::shared_ptr<AbstractEffect> SetEffect(int num, float ini_x, float ini_y, float ini_rate = 1.0f); //エフェクトの配置(データの番号、画像の番号、座標、表示倍率)

	void Update(std::shared_ptr<Sound> sound); //更新
	void Draw(std::shared_ptr<Image> image, std::shared_ptr<Camera> camera); //描画
};