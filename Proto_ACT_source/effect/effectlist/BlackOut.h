#pragma once
#include "../AbstractEffect.h"
#include "../Define.h"

//暗転

class BlackOut : public AbstractEffect {
private:
	int pal; //透明度
public:
	BlackOut(EffectManager* eff, int num, float ini_x, float ini_y); //コンストラクタ(番号、座標)
	~BlackOut(); //デストラクタ
	void AbsUpdate() override; //必ず行う更新
	void Update(std::shared_ptr<Sound> sound); //更新
	void Draw(std::shared_ptr<Image> image, std::shared_ptr<Camera> camera) override; //描画
};
