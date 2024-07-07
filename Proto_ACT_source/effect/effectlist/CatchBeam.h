#pragma once
#include "../AbstractEffect.h"
#include "../Define.h"
#include "../single/Key.h"
#include "../single/Display.h"
#include "../single/Image.h"

//つかみビーム

class CatchBeam : public AbstractEffect {
private:
	int beam_num; //表示するビームの数
public:
	CatchBeam(EffectManager* eff, int num, float ini_x, float ini_y); //コンストラクタ(番号、座標)
	~CatchBeam(); //デストラクタ
	void Update(); //更新
	void Draw() override; //描画
};
