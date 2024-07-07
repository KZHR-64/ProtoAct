#pragma once
#include "DxLib.h"

typedef enum {
	//���̉��
	Next_None,			//�ς��Ȃ�
	Next_Opening,		//�I�[�v�j���O���
	Next_Menu,			//���j���[���
	Next_StageSelect,	//�X�e�[�W�Z���N�g���
	Next_Game,			//�Q�[�����
	Next_Gameover,		//�Q�[���I�[�o�[���
	Next_Option,		//�I�v�V�������
	Next_Config,		//�L�[�R���t�B�O���
	Next_Back,			//�O�ɖ߂�
} NextMode;

const static int WINDOW_X = 1280; //��ʂ̑傫��(��)
const static int WINDOW_Y = 720; //��ʂ̑傫��(�c)

const static int BUTTON = 9; //�{�^���̑���
const static int RECORD = 12; //�ۑ�����A�{�^��������������
const static int STAGE_MAX = 3; //�X�e�[�W�̑���

const static int VOLUME_MAX = 100; //���ʂ̍ő�l

const static bool LEFT = false; //��������\��
const static bool RIGHT = true; //�E������\��

const static int HP_MAX = 6; //HP�̍ő�l
const static int JUMP_TIME_MAX = 16; //�W�����v�ŏ㏸���鎞��
const static float JUMP_SPEED = 12.0f; ////�W�����v�ŏ㏸����X�s�[�h�̍ő�
const static int DAMAGE_TIME_MAX = 10; //�_���[�W����̎���
const static int DAMAGE_INV_TIME = 60; //�_���[�W���󂯂��Ƃ��̖��G����
const static int CLEAR_MOVE_TIME_MAX = 300; //�N���A���̓��쎞��
const static int WEAPON_MAX = 4; //����̍ő吔

const static int MAPCHIP_MAX = 1024; //�}�b�v�`�b�v�̍ő吔

const static int BACKGROUND_MAX = 2; //�w�i�̍ő吔

const static float PI = 3.141592654f;	//�~����