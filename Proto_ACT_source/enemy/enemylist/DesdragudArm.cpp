#pragma once
#include "DxLib.h"
#include "DesdragudArm.h"

using namespace std;

//�R���X�g���N�^
DesdragudArm::DesdragudArm(EnemyManager* ene, int num, float ini_x, float ini_y) : AbstractEnemy(ene, num, ini_x, ini_y) {
	SetHit(24.0f, 0.0f, 24.0f);
	SetHit(-24.0f, 0.0f, 24.0f);
	SetHit(48.0f, 0.0f, 24.0f);
	SetHit(-48.0f, 0.0f, 24.0f);
	hit_map = false;

}

//�f�X�g���N�^
DesdragudArm::~DesdragudArm() {

}

//�K���s���X�V
void DesdragudArm::AbsUpdate() {

}

//���ꂽ���̓���
void DesdragudArm::Defeat(shared_ptr<EffectManager> effect, shared_ptr<Sound> sound) {
	end_flag = true; //������
	effect->SetEffect(1, x, y); //����
}

//�X�V
void DesdragudArm::Update(shared_ptr<Player> player, shared_ptr<BulletManager> bullet, shared_ptr<EffectManager> effect, shared_ptr<Sound> sound, shared_ptr<Camera> camera) {

}

//�`��
void DesdragudArm::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera) {
	int hundle = image->GetCharaImage(image_num, 0);
	float draw_angle = (reverse) ? angle * -1.0f : angle;

	camera->Draw(x, y, reverse, draw_angle, hundle, 1.0f, DX_BLENDMODE_ALPHA, trance);
}