#pragma once
#include "../AbstractEffect.h"
#include "../Define.h"

//�ڈ�

class MarkPoint : public AbstractEffect {
private:
	const float distance = 32.0f; //�G�t�F�N�g�̔��a
	static const int particle_num = 4; //�G�t�F�N�g�̐�
	int particle_time[particle_num]; //�\������G�t�F�N�g�̃^�C�}�[
	const float particle_x[particle_num] = {-1.0f, 0.33f, -0.33f, 1.0f}; //�\������G�t�F�N�g�̍��W
public:
	MarkPoint(EffectManager* eff, int num, float ini_x, float ini_y); //�R���X�g���N�^(�ԍ��A���W)
	~MarkPoint(); //�f�X�g���N�^
	void AbsUpdate() override; //�K���s���X�V
	void Update(std::shared_ptr<Sound> sound); //�X�V
	void Draw(std::shared_ptr<Image> image, std::shared_ptr<Camera> camera) override; //�`��
};
