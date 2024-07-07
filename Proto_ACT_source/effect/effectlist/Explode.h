#pragma once
#include "../AbstractEffect.h"
#include "../Define.h"

//爆発

class Explode : public AbstractEffect {
private:
	int hundle_num; //表示する画像
public:
	Explode(EffectManager* eff, int num, float ini_x, float ini_y); //コンストラクタ(番号、座標)
	~Explode(); //デストラクタ
	void AbsUpdate() override; //必ず行う更新
	void Update(std::shared_ptr<Sound> sound); //更新
	void Draw(std::shared_ptr<Image> image, std::shared_ptr<Camera> camera) override; //描画
};
