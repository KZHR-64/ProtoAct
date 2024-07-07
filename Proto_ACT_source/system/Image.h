#pragma once
#include "../Define.h"
#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

struct CharaImageStruct{
	//�L�����N�^�[�摜�̍\����
	std::string name; //�t�@�C����
	int num_x; //�摜�̕�����(��)
	int num_y; //�摜�̕�����(�c)
	int size_x; //1���̑傫��(��)
	int size_y; //1���̑傫��(�c)
};

struct MapchipConvertStruct{
	//�}�b�v�`�b�v�ԍ��ϊ��̍\����
	int key_num; //�匳�̉摜�ԍ�
	int image_num; //�g�p����摜�ԍ�
};

class Image {
private:
	int player_image[28]; //���@�̉摜
	int map_image[44]; //�}�b�v�`�b�v�̉摜
	int warp_image; //���[�v�n�_�̉摜
	std::map<int, int> background; //�w�i�摜
	std::map<int, CharaImageStruct> back_data; //�w�i�摜�̏��
	std::map<int, std::vector<int>> enemy_image; //�L�����̉摜
	std::map<int, CharaImageStruct> enemy_graphic_data; //�L�����摜�̏��
	std::map<int, std::vector<int>> effect_image; //�G�t�F�N�g�̉摜
	std::map<int, CharaImageStruct> effect_graphic_data; //�G�t�F�N�g�摜�̏��
	std::map<int, std::vector<int>> bullet_image; //�e�̉摜
	std::map<int, CharaImageStruct> bullet_graphic_data; //�e�摜�̏��
	std::map<int, std::vector<int>> mapchip_image; //�}�b�v�`�b�v�̉摜
	std::map<int, CharaImageStruct> mapchip_graphic_data; //�}�b�v�`�b�v�摜�̏��
	std::map<int, MapchipConvertStruct> mapchip_convert; //�}�b�v�`�b�v�ԍ��ϊ����
	std::map<int, std::vector<int>> item_image; //�A�C�e���̉摜
	std::map<int, CharaImageStruct> item_graphic_data; //�A�C�e���摜�̏��
	std::vector<int> image_hundle; //�摜(�������擾�p)

	void LoadMapchipData(); //�}�b�v�`�b�v���̓ǂݍ���
	void LoadMapchipConvertData(); //�}�b�v�`�b�v�ԍ��ϊ����̓ǂݍ���
	void LoadBackData(); //�w�i���̓ǂݍ���
	void LoadCharaData(); //�L�����摜���̓ǂݍ���
	void LoadEffectData(); //�G�t�F�N�g�摜���̓ǂݍ���
	void LoadBulletData(); //�e�摜���̓ǂݍ���
	void LoadItemData(); //�A�C�e���摜���̓ǂݍ���

public:
	Image(); //�R���X�g���N�^
	~Image(); //�f�X�g���N�^

	void Reset(); //������

	void LoadMapImage(); //�}�b�v�`�b�v�̉摜�����[�h
	int GetMapImage(int num); //�}�b�v�`�b�v�̉摜��Ԃ�(�摜�̔ԍ�)
	int GetWarpImage(); //���[�v�n�_�̉摜��Ԃ�
	void DeleteMapImage(); //�}�b�v�`�b�v�̉摜���폜

	void LoadMapchipImage(); //�}�b�v�`�b�v�̉摜�����[�h
	int GetMapchipImage(int image_num); //�}�b�v�`�b�v�̉摜��Ԃ�(�摜�̔ԍ�)
	int GetMapchipImage(int map_num, int image_num); //�}�b�v�`�b�v�̉摜��Ԃ�(�}�b�v�`�b�v�̔ԍ��A�摜�̔ԍ�)
	void DeleteMapchipImage(); //�}�b�v�`�b�v�̉摜���폜

	void LoadBackImage(int num); //�w�i�̉摜�����[�h(�摜�̔ԍ�)
	int GetBackImage(int num); //�w�i�̉摜��Ԃ�(�摜�̔ԍ�)
	void DeleteBackImage(); //�w�i�̉摜���폜

	void LoadCharaImage(); //�L�����̉摜�����[�h
	int GetCharaImage(int enemy_num, int image_num); //�L�����̉摜��Ԃ�(�L�����̔ԍ��A�摜�̔ԍ�)
	void DeleteCharaImage(); //�L�����̉摜���폜

	void LoadEffectImage(); //�G�t�F�N�g�̉摜�����[�h
	int GetEffectImage(int effect_num, int image_num); //�G�t�F�N�g�̉摜��Ԃ�(�G�t�F�N�g�̔ԍ��A�摜�̔ԍ�)
	int GetEffectSize(int effect_num); //�G�t�F�N�g�̉摜����Ԃ�(�G�t�F�N�g�̔ԍ�)
	void DeleteEffectImage(); //�G�t�F�N�g�̉摜���폜

	void LoadBulletImage(); //�e�̉摜�����[�h
	int GetBulletImage(int bullet_num, int image_num); //�e�̉摜��Ԃ�(�e�̔ԍ��A�摜�̔ԍ�)
	void DeleteBulletImage(); //�e�̉摜���폜

	void LoadItemImage(); //�A�C�e���̉摜�����[�h
	int GetItemImage(int item_num, int image_num); //�A�C�e���̉摜��Ԃ�(�e�̔ԍ��A�摜�̔ԍ�)
	void DeleteItemImage(); //�A�C�e���̉摜���폜

	int LoadSingleImage(char file_name[64]); //���������摜��ǂݍ���(�t�@�C����)
	void DeleteImage(); //�摜���폜
};