#pragma once
#include "../AbstractEffect.h"
#include "../Define.h"

//目印

class MarkPoint : public AbstractEffect {
private:
	const float distance = 32.0f; //エフェクトの半径
	static const int particle_num = 4; //エフェクトの数
	int particle_time[particle_num]; //表示するエフェクトのタイマー
	const float particle_x[particle_num] = {-1.0f, 0.33f, -0.33f, 1.0f}; //表示するエフェクトの座標
public:
	MarkPoint(EffectManager* eff, int num, float ini_x, float ini_y); //コンストラクタ(番号、座標)
	~MarkPoint(); //デストラクタ
	void AbsUpdate() override; //必ず行う更新
	void Update(std::shared_ptr<Sound> sound); //更新
	void Draw(std::shared_ptr<Image> image, std::shared_ptr<Camera> camera) override; //描画
};
