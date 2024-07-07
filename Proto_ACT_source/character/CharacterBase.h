#pragma once
#include "DxLib.h"
#include "..\system\Fps.h"
#include "..\system\Image.h"
#include "..\system\Key.h"
#include "..\system\Sound.h"
#include "..\camera\Camera.h"
#include "..\tool\Display.h"
#include "..\tool\Calculation.h"
#include <math.h>
#include <vector>
#include <memory>

struct HitStruct
{
	//�����蔻��̍\����
	float x; //x���W
	float y; //y���W
	float distance; //�{�̂Ƃ̒�������
	float angle; //�����̊p�x
	float size; //�傫��
	bool check_bottom = true; //�����̔�����s����
	bool check_top = true; //����̔�����s����
	bool check_left = true; //���̔�����s����
	bool check_right = true; //�E�̔�����s����
};

struct JointStruct
{
	//�Ԑڂ̍\����
	float x; //���W
	float y;
	float local_angle; //�����̊p�x
	float total_angle; //��ƍ��킹���p�x
	float angle_max; //�p�x�̏��
	float angle_min; //�p�x�̉���
	float axis_x; //��]���i�t�����j��x���W
	float axis_y; //��]���i�t�����j��y���W
	float dist; //��[�ւ̋���
};

class Key;
class Sound;
class Image;
class Fps;
class MapChipManager;
class Camera;

class CharacterBase{
protected:

	std::vector<HitStruct> hit; //�����蔻��

	bool live_flag; //�\�����邩
	bool end_flag; //�������邩
	int end_time; //������܂ł̎���
	bool hit_flag; //�����蔻��
	int image_num; //�\������摜
	int trance; //�����x
	int time; //�^�C�}�[
	int hp; //HP
	int max_hp; //HP�̍ő�l
	float x; //x���W
	float y; //y���W
	float base_x; //���X��x���W
	float base_y; //���X��y���W
	float sx; //x�����̑��x
	float sy; //y�����̑��x
	float angle; //�p�x
	float spin_speed; //��]���x
	bool reverse; //���]���Ă��邩
	float ex_rate; //�\���{��
	int jump_time; //�W�����v���Ă��鎞��
	bool jump_flag; //�W�����v���Ă��邩
	bool flying_flag; //���ł��邩
	bool damaged; //�_���[�W���󂯂Ă��邩
	int damage_time; //�_���[�W����̎���
	bool hit_map; //�}�b�v�`�b�v�ɓ����邩
	bool adjusted; //�}�b�v�`�b�v�ƐڐG������

	void SetJoint(JointStruct& joint, float ax, float ay, float set_x, float set_y, float angle_max, float angle_min); //�֐ߏ���ݒ�i�֐߁A��]���̈ʒu�A�����ʒu�A�p�x�̏���A�����j
	void SetHit(float cx, float cy, float hit_size); //�����蔻��̔z�u�ix,y���W�A�����蔻��̑傫���j
	void JointUpdate(std::vector<JointStruct>& joint, float bx, float by, float bangle); //�֐߂̈ʒu��ݒ�i�֐߁A��̍��W�A�p�x�j
	void IkSetting(std::vector<JointStruct>& joint, float speed, float dx, float dy); //�C���o�[�X�L�l�}�e�B�N�X�i�֐߁A���x�A�ڕW�̍��W�j
	void ZoomJoint(std::vector<JointStruct>& joint, float zoom_limit, float dx, float dy); //���֐߂�L�k������i�֐߁A�L�΂�����E�A�ڕW�̍��W�j

public:
	CharacterBase(); //�R���X�g���N�^
	virtual ~CharacterBase(); //�f�X�g���N�^

	bool GetEndFlag(); //�������邩���擾
	void SetEndFlag(bool flag); //�������邩��ݒ�
	int GetEndTime(); //���ł܂ł̎��Ԃ�Ԃ�
	void SetEndTime(int set_time); //���ł܂ł̎��Ԃ�ݒ�(����)
	bool GetHitFlag(); //�����蔻����擾
	void SetHitFlag(bool flag); //�����蔻���ݒ�
	void SetTrance(int set_trance); //�����x��ݒ�
	int GetTime(); //���Ԃ�Ԃ�
	void SetTime(int set_time); //���Ԃ�ݒ�(����)
	int GetHp(); //HP��Ԃ�
	void SetHp(int set_hp); //HP��ݒ�(HP)
	void SetMaxHp(int set_hp); //�ő�HP��ݒ�(HP)
	float GetX(); //x���W��Ԃ�
	void SetX(float set_x); //x���W��ݒ�
	float GetY(); //y���W��Ԃ�
	void SetY(float set_y); //y���W��ݒ�
	float GetBaseX(); //����x���W��Ԃ�
	void SetBaseX(float set_x); //����x���W��ݒ�
	float GetBaseY(); //����y���W��Ԃ�
	void SetBaseY(float set_y); //����y���W��ݒ�
	void SetSpeed(float speed); //�p�x����ɑ��x��ݒ�
	float GetXSpeed(); //x�����̑��x��Ԃ�
	void SetXSpeed(float set_x); //x�����̑��x��ݒ�
	float GetYSpeed(); //y�����̑��x��Ԃ�
	void SetYSpeed(float set_y); //y�����̑��x��ݒ�
	float GetAngle(); //�p�x���擾
	void SetAngle(float set_angle); //�p�x��ݒ�(�p�x)
	float GetSpinSpeed(); //��]���x���擾
	void SetSpinSpeed(float set_angle); //��]���x��ݒ�(�p�x)
	bool GetReverse(); //�������擾
	void SetReverse(bool flag); //������ݒ�
	void SetExRate(float set_rate); //�\���{����ݒ�
	bool GetFlying(); //���ł��邩���擾
	virtual void SetFlying(bool flag); //���ł��邩��ݒ�
	virtual bool GetDamaged(); //�_���[�W���󂯂Ă��邩���擾
	virtual bool GetHitMap(); //�}�b�v�`�b�v�ɓ����邩���擾
	virtual void SetHitMap(bool flag); //�}�b�v�`�b�v�ɓ����邩��ݒ�

	void HitUpdate(); //�����蔻��̍X�V
	void DrawHit(std::shared_ptr<Camera> camera); //�����蔻��̕`��

	virtual bool HitCheckChara(float cx, float cy, float hit_size, bool check_hit = true); //�L�����N�^�[�Ƃ̓����蔻��(�L������x,y���W�A�����蔻��̑傫���A�����蔻��̗L�����m�F���邩)
	virtual void Timer(); //�^�C�}�[�֘A�̍X�V

	virtual void AbsUpdate() = 0; //�K���s���X�V
	virtual void Draw(std::shared_ptr<Image> image, std::shared_ptr<Camera> camera) = 0; //�`��
};