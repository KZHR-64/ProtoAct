#pragma once
#include "DxLib.h"
#include "LockedDoor.h"

using namespace std;

//�R���X�g���N�^
LockedDoor::LockedDoor(MapChipManager* man, int num) : AbstractMapChip(man, num) {
	locked = true;
}

//�f�X�g���N�^
LockedDoor::~LockedDoor() {
	
}

//�K���s���X�V
void LockedDoor::AbsUpdate() {

}

//�X�V
void LockedDoor::Update(shared_ptr<Player> player, shared_ptr<EnemyManager> enemy, shared_ptr<BulletManager> bullet, shared_ptr<EffectManager> effect, shared_ptr<Key> key, shared_ptr<Sound> sound){
	//���@�̍��W���擾
	float px = player->GetX();
	float py = player->GetY();

	//�����������Ă���Ȃ�
	if (locked) {
		//���@���߂��Ȃ�
		if (fabsf(px - x) < 24.0f + 4.0f * size_x && fabsf(py - y - 4.0f * size_y) < 4.0f * size_y) {
			int key = player->GetKeyNum(); //���̖{�����擾
			//���������Ă���Ȃ�
			if (0 < key) {
				locked = false;//�J��
				time = 0; //���Ԃ�������
				player->SetKeyNum(key - 1); //��������
				sound->PlaySoundEffect(13); //���ʉ���炷
			}
		}
	}
	//�J������Ă���Ȃ�
	else {
		//��莞�Ԃ����������
		if (30 <= time) {
			live_flag = false;
		}
	}
}

//�`��
void LockedDoor::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera) {
	int hundle = image->GetMapchipImage(image_num);
	//�摜�̑傫�����擾
	int img_x;
	int img_y;
	GetGraphSize(hundle, &img_x, &img_y);
	int pal_mode = locked ? DX_BLENDMODE_NOBLEND : DX_BLENDMODE_ADD;
	int pal_add = locked ? 0 : 196;

	camera->Draw(x, y + (float)(img_y / 2), false, angle, hundle, 1.0f, pal_mode, pal_add);
}