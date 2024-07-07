#pragma once
#include "DxLib.h"
#include "BeamWall.h"

using namespace std;

//�R���X�g���N�^
BeamWall::BeamWall(EnemyManager* ene, int num, float ini_x, float ini_y) : AbstractEnemy(ene, num, ini_x, ini_y) {
	
}

//�f�X�g���N�^
BeamWall::~BeamWall() {

}

//�K���s���X�V
void BeamWall::AbsUpdate() {

}

//���ꂽ���̓���
void BeamWall::Defeat(shared_ptr<EffectManager> effect, shared_ptr<Sound> sound) {
	end_flag = true; //������
	effect->SetEffect(1, x, y); //����
}

//�X�V
void BeamWall::Update(shared_ptr<Player> player, shared_ptr<BulletManager> bullet, shared_ptr<EffectManager> effect, shared_ptr<Sound> sound, shared_ptr<Camera> camera) {

	//��莞�Ԃ��Ƃɒe������
	if (time % 12 == 0 && 0 < time) {
		bullet->SetBullet(5, x, y - 32.0f, 12.0f, -0.5f * PI); //�e�𔭎�
		sound->PlaySoundEffect(7); //���ʉ���炷
	}
}

//�`��
void BeamWall::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera) {
	int hundle = image->GetCharaImage(image_num, 0);
	camera->Draw(x, y, reverse, angle, hundle, 1.0f, DX_BLENDMODE_ALPHA, trance);
}