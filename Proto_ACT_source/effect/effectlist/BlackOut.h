#pragma once
#include "../AbstractEffect.h"
#include "../Define.h"

//�Ó]

class BlackOut : public AbstractEffect {
private:
	int pal; //�����x
public:
	BlackOut(EffectManager* eff, int num, float ini_x, float ini_y); //�R���X�g���N�^(�ԍ��A���W)
	~BlackOut(); //�f�X�g���N�^
	void AbsUpdate() override; //�K���s���X�V
	void Update(std::shared_ptr<Sound> sound); //�X�V
	void Draw(std::shared_ptr<Image> image, std::shared_ptr<Camera> camera) override; //�`��
};
