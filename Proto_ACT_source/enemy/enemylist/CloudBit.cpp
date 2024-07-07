#pragma once
#include "DxLib.h"
#include "CloudBit.h"

using namespace std;

//�R���X�g���N�^
CloudBit::CloudBit(EnemyManager* ene, int num, float ini_x, float ini_y) : AbstractEnemy(ene, num, ini_x, ini_y) {

	flying_flag = true;
	hit_map = false;

	SetHit(0.0f, 0.0f, 32.0f);
}

//�f�X�g���N�^
CloudBit::~CloudBit() {

}

//�K���s���X�V
void CloudBit::AbsUpdate() {
	
}

//���ꂽ���̓���
void CloudBit::Defeat(shared_ptr<EffectManager> effect, shared_ptr<Sound> sound) {
	end_flag = true; //������
	effect->SetEffect(1, x, y); //����
}

//�X�V
void CloudBit::Update(shared_ptr<Player> player, shared_ptr<BulletManager> bullet, shared_ptr<EffectManager> effect, shared_ptr<Sound> sound, shared_ptr<Camera> camera) {
	//��ɑS��
	hp = max_hp;
}

//�`��
void CloudBit::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera) {
	int hundle = image->GetCharaImage(image_num, 0);

	camera->Draw(x, y, reverse, angle, hundle, 1.0f, DX_BLENDMODE_ALPHA, trance);
}