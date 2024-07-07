#pragma once
#include "../AbstractEffect.h"
#include "../Define.h"
#include "../single/Key.h"
#include "../single/Display.h"
#include "../single/Image.h"

//増援信号

class CallSign : public AbstractEffect {
private:
	int hundle_num; //表示する画像
public:
	CallSign(EffectManager* eff, int num, float ini_x, float ini_y); //コンストラクタ(番号、座標)
	~CallSign(); //デストラクタ
	void Update(); //更新
	void Draw() override; //描画
};
