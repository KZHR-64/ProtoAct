#pragma once
#include "DxLib.h"
#include "DoorKey.h"

using namespace std;

//�R���X�g���N�^
DoorKey::DoorKey(ItemManager* man, int num, float ini_x, float ini_y) : AbstractItem(man, num, ini_x, ini_y) {
	SetHit(0.0f, 0.0f, 16.0f);
}

//�f�X�g���N�^
DoorKey::~DoorKey() {
	mark.reset();
}

//�A�C�e���擾���̏���
void DoorKey::ItemGet(shared_ptr<Player> player, shared_ptr<EffectManager> effect, shared_ptr<Sound> sound) {
	int num = player->GetKeyNum();
	player->SetKeyNum(num + 1); //���@�̎������𑝂₷
	sound->PlaySoundEffect(14); //���ʉ���炷
	mark->SetEndFlag(true); //�G�t�F�N�g������
}

//�K���s���X�V
void DoorKey::AbsUpdate() {

}

//�X�V
void DoorKey::Update(shared_ptr<Player> player, shared_ptr<EnemyManager> enemy, shared_ptr<EffectManager> effect, shared_ptr<Sound> sound) {
	if (time == 0) {
		mark = effect->SetEffect(16, x, y + 24.0f, 0.1f);
	}
	if (mark) {
		mark->SetX(x);
		mark->SetY(y + 24.0f);
	}
}

//�`��
void DoorKey::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera) {
	int hundle = image->GetItemImage(image_num, 0);

	camera->Draw(x, y, false, angle, hundle, 1.0f, DX_BLENDMODE_NOBLEND);
}