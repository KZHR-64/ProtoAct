#pragma once
#include "../character/CharacterBase.h"
#include "MapChipManager.h"
#include "../Define.h"
#include "../player/Player.h"
#include "../bullet/BulletManager.h"
#include "../effect/EffectManager.h"
#include "../enemy/EnemyManager.h"
#include "../system/Key.h"
#include "../system/Image.h"
#include "../system/Sound.h"
#include "../tool/Display.h"
#include <memory>

class MapChipManager;
class BulletManager;
class Player;
class EnemyManager;
class EffectManager;

class AbstractMapChip : public CharacterBase{
protected:
	MapChipManager* manager;

	bool draw_flag; //�`�悷�邩
	int link_img_x1; //�A�������摜�ԍ��i���A�Ȃ��j
	int link_img_x2; //�A�������摜�ԍ��i���A�I�[�j
	int link_img_y1; //�A�������摜�ԍ��i�c�A�Ȃ��j
	int link_img_y2; //�A�������摜�ԍ��i�c�A�I�[�j
	float last_x; //��O��x���W
	float last_y; //��O��y���W
	int size_x; //���̑傫��
	int size_y; //�c�̑傫��
	bool hit_map; //���̃}�b�v�`�b�v�ɓ����邩
	bool through; //���蔲���邩
	int breakable; //�󂹂邩(0=�󂹂Ȃ��A1=�Ƃ��A2=�d��)
	float friction; //���C
	float move_x; //����Ă���L�����N�^�[�Ɋ����鑬�x
	float move_y; //����Ă���L�����N�^�[�Ɋ����鑬�x
	bool step; //�L����������Ă��邩
	bool hit_left; //�����ɍU��������������
	bool hit_right; //�E���ɍU��������������
	bool hit_top; //�㑤�ɍU��������������
	bool hit_bottom; //�����ɍU��������������
	int link_x; //�A�������}�b�v�`�b�v���i���j
	int link_y; //�A�������}�b�v�`�b�v���i�c�j
public:
	AbstractMapChip(MapChipManager* man, int num); //�R���X�g���N�^(�摜�̔ԍ�)
	~AbstractMapChip(); //�f�X�g���N�^

	bool GetLiveFlag(); //���삷�邩���擾
	void SetLiveFlag(bool flag); //���삷�邩��ݒ�
	bool GetDrawFlag(); //�`�悷�邩���擾
	void SetDrawFlag(bool flag); //�`�悷�邩��ݒ�
	void SetLinkImgX(int ini_x1, int ini_x2); //�A������摜��ݒ�iimage�ɑ������j
	void SetLinkImgY(int ini_y1, int ini_y2); //�A������摜��ݒ�
	float GetLastX(); //��O��x���W��Ԃ�
	void SetLastX(float set_x); //��O��x���W��ݒ�
	float GetLastY(); //��O��y���W��Ԃ�
	void SetLastY(float set_y); //��O��y���W��ݒ�
	float GetAmountX(); //x�����̈ړ��ʂ��擾
	float GetAmountY(); //y�����̈ړ��ʂ��擾
	int GetSizeX(); //�}�b�v�`�b�v�̉��̑傫����Ԃ�
	void SetSizeX(int set_size); //�}�b�v�`�b�v�̉��̑傫����ݒ�
	int GetSizeY(); //�}�b�v�`�b�v�̏c�̑傫����Ԃ�
	void SetSizeY(int set_size); //�}�b�v�`�b�v�̏c�̑傫����ݒ�
	bool GetHitMap(); //���̃}�b�v�ɓ����邩���擾
	void SetHitMap(bool flag); //���̃}�b�v�ɓ����邩��ݒ�
	bool GetThrough(); //���蔲���邩���擾
	void SetThrough(bool flag); //���蔲���邩��ݒ�
	int GetBreakable(); //�󂹂邩���擾
	void SetBreakable(int set_bre); //�󂹂邩��ݒ�
	float GetFriction(); //���C���擾
	void SetFriction(float set_fri); //���C���擾
	float GetMoveX(); //����Ă���L�����ɑ΂���x�����̑��x��Ԃ�
	void SetMoveX(float set_x); //����Ă���L�����ɑ΂���x�����̑��x��ݒ�
	float GetMoveY(); //����Ă���L�����ɑ΂���y�����̑��x��Ԃ�
	void SetMoveY(float set_y); //����Ă���L�����ɑ΂���y�����̑��x��ݒ�
	bool GetStep(); //�L����������Ă��邩���擾
	void SetStep(bool flag); //�L����������Ă��邩��ݒ�
	bool GetHitLeft(); //�����ɍU�����������������擾
	void SetHitLeft(bool flag); //�����ɍU����������������ݒ�
	bool GetHitRight(); //�E���ɍU�����������������擾
	void SetHitRight(bool flag); //�E���ɍU����������������ݒ�
	bool GetHitTop(); //�㑤�ɍU�����������������擾
	void SetHitTop(bool flag); //�㑤�ɍU����������������ݒ�
	bool GetHitBottom(); //�����ɍU�����������������擾
	void SetHitBottom(bool flag); //�����ɍU����������������ݒ�
	void SetLinkX(int ini_link); //�A�������}�b�v�`�b�v����ݒ�
	void SetLinkY(int ini_link); //�A�������}�b�v�`�b�v����ݒ�

	virtual void Update(std::shared_ptr<Player> player, std::shared_ptr<EnemyManager> enemy, std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect, std::shared_ptr<Key> key, std::shared_ptr<Sound> sound) = 0;
};