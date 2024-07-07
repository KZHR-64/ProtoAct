#pragma once
#include "../AbstractEffect.h"
#include "../Define.h"

//煙（小爆発）

class Smoke : public AbstractEffect {
private:
	int hundle_num; //表示する画像
public:
	Smoke(EffectManager* eff, int num, float ini_x, float ini_y); //コンストラクタ(番号、座標)
	~Smoke(); //デストラクタ
	void AbsUpdate() override; //必ず行う更新
	void Update(std::shared_ptr<Sound> sound); //更新
	void Draw(std::shared_ptr<Image> image, std::shared_ptr<Camera> camera) override; //描画
};
