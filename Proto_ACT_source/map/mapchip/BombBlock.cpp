#pragma once
#include "DxLib.h"
#include "BombBlock.h"

using namespace std;

//�R���X�g���N�^
BombBlock::BombBlock(MapChipManager* man, int num) : AbstractMapChip(man, num) {

}

//�f�X�g���N�^
BombBlock::~BombBlock() {

}

//�K���s���X�V
void BombBlock::AbsUpdate() {

}

//�X�V
void BombBlock::Update(shared_ptr<Player> player, shared_ptr<EnemyManager> enemy, shared_ptr<BulletManager> bullet, shared_ptr<EffectManager> effect, shared_ptr<Key> key, shared_ptr<Sound> sound) {

	//������ۂɏ㉺���E�ɗU������
	if (end_flag) {
		shared_ptr<AbstractBullet> blast = bullet->SetBullet(4, x - (8.0f * size_x), y + 4.0f * size_y, 0.0f, 0.0f);
		blast->SetEndTime(2); //�����ɏ�����悤�ݒ�
		blast = bullet->SetBullet(4, x + (8.0f * size_x), y + 4.0f * size_y, 0.0f, 0.0f);
		blast->SetEndTime(2); //�����ɏ�����悤�ݒ�
		blast = bullet->SetBullet(4, x, y - (4.0f * size_y), 0.0f, 0.0f);
		blast->SetEndTime(2); //�����ɏ�����悤�ݒ�
		blast = bullet->SetBullet(4, x, y + (12.0f * size_y), 0.0f, 0.0f);
		blast->SetEndTime(2); //�����ɏ�����悤�ݒ�

		shared_ptr<AbstractEffect> exp = effect->SetEffect(1, x, y + 4.0f * size_y, 0.5f); //����
	}
}

//�`��
void BombBlock::Draw(shared_ptr<Image> image, shared_ptr<Camera> camera) {
	int hundle = image->GetMapchipImage(image_num);
	//�摜�̑傫�����擾
	int img_x;
	int img_y;
	GetGraphSize(hundle, &img_x, &img_y);

	camera->Draw(x, y + (float)(img_y / 2), false, angle, hundle, 1.0f, DX_BLENDMODE_NOBLEND);
}