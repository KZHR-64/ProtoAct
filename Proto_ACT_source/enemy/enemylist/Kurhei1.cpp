#pragma once
#include "DxLib.h"
#include "Kurhei1.h"

using namespace std;

//�R���X�g���N�^
Kurhei1::Kurhei1(EnemyManager* ene, int num, float ini_x, float ini_y) : AbstractEnemy(ene, num, ini_x, ini_y) {
	flying_flag = true;
	hundle_num = 0;
	SetHit(0.0f, 0.0f, 32.0f);
}

//�f�X�g���N�^
Kurhei1::~Kurhei1() {

}

//�K���s���X�V
void Kurhei1::AbsUpdate() {
	//��莞�Ԃ��Ƃɉ摜��ύX
	if (time % 3 == 0) {
		hundle_num = (hundle_num + 1) % 2;
	}
}

//���ꂽ���̓���
void Kurhei1::Defeat(shared_ptr<EffectManager> effect, shared_ptr<Sound> sound) {
	end_time = 30; //������܂ł̎��Ԃ�ݒ�
	sy = 0.5f;
}

//�X�V
void Kurhei1::Update(shared_ptr<Player> player, shared_ptr<BulletManager> bullet, shared_ptr<EffectManager> effect, shared_ptr<Sound> sound, shared_ptr<Camera> camera) {
	//������܂ł̎��Ԃ��ݒ肳��Ă���Ȃ�
	if (end_time != -1) {
		//�����鐡�O�Ȃ�
		if (end_time == 1) {
			end_flag = true; //������
			effect->SetEffect(1, x, y); //����
		}
		//������O�Ȃ�
		else if (end_time % 12 == 0) {
			effect->SetEffect(2, x, y - 24.0f, 0.5f); //��
		}
		sy *= 1.1f; //�������x������
		return; //�I��
	}

	float px = player->GetX(); //���@�̍��W
	//���@�̂������������
	reverse = px < x;
}

//�`��
void Kurhei1::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera) {
	int hundle = image->GetCharaImage(image_num, hundle_num);
	camera->Draw(x, y, reverse, angle, hundle, 1.0f, DX_BLENDMODE_ALPHA, trance);
}