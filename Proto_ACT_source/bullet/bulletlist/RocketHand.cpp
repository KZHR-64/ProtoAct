#pragma once
#include "DxLib.h"
#include "RocketHand.h"

using namespace std;

//�R���X�g���N�^
RocketHand::RocketHand(BulletManager* man, int num, float ini_x, float ini_y, float ini_speed, float ini_angle) : AbstractBullet(man, num, ini_x, ini_y, ini_speed, ini_angle) {
	catch_item = 0;
	SetHit(0.0f, 0.0f, 24.0f);
}

//�f�X�g���N�^
RocketHand::~RocketHand() {
	catch_item.reset();
}

//�K���s���X�V
void RocketHand::AbsUpdate() {

}

//�����鎞�̓���
void RocketHand::Erase(shared_ptr<EffectManager> effect, shared_ptr<Sound> sound) {

}

//�X�V
void RocketHand::Update(shared_ptr<Player> player, shared_ptr<EnemyManager> enemy, shared_ptr<ItemManager> item, shared_ptr<EffectManager> effect, shared_ptr<Key> key, shared_ptr<Sound> sound, shared_ptr<Camera> camera) {
	float px = player->GetX();
	float py = player->GetY();

	//�A�C�e��������ł���Ȃ�
	if (catch_item != 0) {
		catch_item->SetX(x); //�A�C�e���̈ʒu��ݒ�
		catch_item->SetY(y);
	}
	//����ł��Ȃ��Ȃ�
	else {
		//�߂��ɃA�C�e��������Ȃ�
		for (auto& h : hit) {
			shared_ptr<AbstractItem> it = item->HitCheckChara(h.x, h.y, h.size);
			if (it != NULL) {
				catch_item = it; //�A�C�e��������
				catch_item->SetXSpeed(0.0f); //���x��0��
				catch_item->SetYSpeed(0.0f);
				catch_item->SetHitMap(false); //�}�b�v�Ƃ̓����蔻���false��
				break;
			}
		}
	}


	//��莞�Ԃ��߂����玩�@�֖߂��Ă���
	if (18 < time) {
		float back = Calculation::LockOn(x, y, px, py);
		sx = base_speed * cosf(back);
		sy = base_speed * sinf(back);

		//���@�ɋ߂Â����������
		if (fabsf(px - x) < 16.0f && fabsf(py - y) < 16.0f) {
			end_flag = true;
		}
	}

}

//�`��
void RocketHand::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera) {
	int hundle = image->GetBulletImage(image_num, 0);
	float draw_angle = angle;
	if (0.5f * PI < angle || angle < -0.5f * PI) {
		reverse = true;
		draw_angle += PI;
	}
	else {
		reverse = false;
	}
	camera->Draw(x, y, reverse, draw_angle, hundle, 1.0f, DX_BLENDMODE_NOBLEND);
}