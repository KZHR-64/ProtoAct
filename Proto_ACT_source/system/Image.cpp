#pragma once
#include "Image.h"
#include "DxLib.h"

using namespace std;

//�R���X�g���N�^
Image::Image() {
	LoadMapchipConvertData(); //�}�b�v�`�b�v�ԍ��ϊ�����ǂݍ���
	LoadMapchipData(); //�}�b�v�`�b�v����ǂݍ���
	LoadBackData(); //�w�i����ǂݍ���
	LoadCharaData(); //�L�����̉摜����ǂݍ���
	LoadEffectData(); //�G�t�F�N�g�̉摜����ǂݍ���
	LoadBulletData(); //�e�̉摜����ǂݍ���
	LoadItemData(); //�A�C�e���̉摜����ǂݍ���
}

//�f�X�g���N�^
Image::~Image() {
	image_hundle.clear();
	mapchip_convert.clear();
	enemy_graphic_data.clear();
	effect_graphic_data.clear();
	bullet_graphic_data.clear();
	item_graphic_data.clear();
	mapchip_graphic_data.clear();
	back_data.clear();
	DeleteMapchipImage();
	DeleteBackImage();
	DeleteCharaImage();
	DeleteEffectImage();
	DeleteBulletImage();
	DeleteImage();
}

//������
void Image::Reset() {
	image_hundle.clear();
	DeleteBackImage();
	DeleteCharaImage();
	DeleteEffectImage();
	DeleteBulletImage();
	DeleteImage();
	LoadBackData(); //�w�i����ǂݍ���
	LoadCharaData(); //�L�����̉摜����ǂݍ���
	LoadEffectData(); //�G�t�F�N�g�̉摜����ǂݍ���
	LoadBulletData(); //�e�̉摜����ǂݍ���
	LoadItemData(); //�A�C�e���̉摜����ǂݍ���
	LoadItemData(); //�A�C�e���̉摜����ǂݍ���
}

//�}�b�v�`�b�v���̓ǂݍ���
void Image::LoadMapchipData() {
	int num;

	ifstream ifs("data/graphic/mapchip/mapchip_graphic.csv");

	//�Ȃ���ΏI��
	if (ifs.fail()) {
		return;
	}

	string str, s;
	//�t�@�C�������s�ǂ�
	while (getline(ifs, str)) {
		stringstream ss{ str };
		getline(ss, s, ',');
		num = atoi(s.c_str()); //�ԍ����擾
		getline(ss, s, ',');
		mapchip_graphic_data[num].name = "data/graphic/mapchip/" + s; //�t�@�C�������i�[
		getline(ss, s, ',');
		mapchip_graphic_data[num].num_x = atoi(s.c_str()); //�摜�̖����i���j��ݒ�
		getline(ss, s, ',');
		mapchip_graphic_data[num].num_y = atoi(s.c_str()); //�摜�̖����i�c�j��ݒ�
		getline(ss, s, ',');
		mapchip_graphic_data[num].size_x = atoi(s.c_str()); //�摜�̑傫���i���j��ݒ�
		getline(ss, s, ',');
		mapchip_graphic_data[num].size_y = atoi(s.c_str()); //�摜�̑傫���i�c�j��ݒ�
	}
	ifs.close();

}

//�}�b�v�`�b�v�ԍ��ϊ����̓ǂݍ���
void Image::LoadMapchipConvertData() {

	int num;

	ifstream ifs("data/graphic/mapchip/mapchip_convert.csv");

	//�Ȃ���ΏI��
	if (ifs.fail()) {
		return;
	}

	string str, s;
	//�t�@�C�������s�ǂ�
	while (getline(ifs, str)) {
		stringstream ss{ str };
		getline(ss, s, ',');
		num = atoi(s.c_str()); //�ԍ����擾
		getline(ss, s, ',');
		mapchip_convert[num].key_num = atoi(s.c_str()); //�匳�̉摜�ԍ���ݒ�
		getline(ss, s, ',');
		mapchip_convert[num].image_num = atoi(s.c_str()); //�g�p����摜�ԍ���ݒ�
	}
	ifs.close();
}

//�w�i���̓ǂݍ���
void Image::LoadBackData() {

	int num;

	ifstream ifs("data/graphic/back/back_data.csv");

	//�Ȃ���ΏI��
	if (ifs.fail()) {
		return;
	}

	string str, s;
	//�t�@�C�������s�ǂ�
	while (getline(ifs, str)) {
		stringstream ss{ str };
		getline(ss, s, ',');
		num = atoi(s.c_str()); //�ԍ����擾
		getline(ss, s, ',');
		back_data[num].name = "data/graphic/back/" + s; //�t�@�C�������i�[
	}
	ifs.close();
}

//�L�����摜���̓ǂݍ���
void Image::LoadCharaData() {

	int num;

	ifstream ifs("data/graphic/character/character_graphic.csv");

	//�Ȃ���ΏI��
	if (ifs.fail()) {
		return;
	}

	string str, s;
	//�t�@�C�������s�ǂ�
	while (getline(ifs, str)) {
		stringstream ss{ str };
		getline(ss, s, ',');
		num = atoi(s.c_str()); //�ԍ����擾
		getline(ss, s, ',');
		enemy_graphic_data[num].name = "data/graphic/character/" + s; //�t�@�C�������i�[
		getline(ss, s, ',');
		enemy_graphic_data[num].num_x = atoi(s.c_str()); //�摜�̖����i���j��ݒ�
		getline(ss, s, ',');
		enemy_graphic_data[num].num_y = atoi(s.c_str()); //�摜�̖����i�c�j��ݒ�
		getline(ss, s, ',');
		enemy_graphic_data[num].size_x = atoi(s.c_str()); //�摜�̑傫���i���j��ݒ�
		getline(ss, s, ',');
		enemy_graphic_data[num].size_y = atoi(s.c_str()); //�摜�̑傫���i�c�j��ݒ�
	}
	ifs.close();
}

//�G�t�F�N�g�摜���̓ǂݍ���
void Image::LoadEffectData() {

	int num;

	ifstream ifs("data/graphic/effect/effect_graphic.csv");

	//�Ȃ���ΏI��
	if (ifs.fail()) {
		return;
	}

	string str, s;
	//�t�@�C�������s�ǂ�
	while (getline(ifs, str)) {
		stringstream ss{ str };
		getline(ss, s, ',');
		num = atoi(s.c_str()); //�ԍ����擾
		getline(ss, s, ',');
		effect_graphic_data[num].name = "data/graphic/effect/" + s; //�t�@�C�������i�[
		getline(ss, s, ',');
		effect_graphic_data[num].num_x = atoi(s.c_str()); //�摜�̖����i���j��ݒ�
		getline(ss, s, ',');
		effect_graphic_data[num].num_y = atoi(s.c_str()); //�摜�̖����i�c�j��ݒ�
		getline(ss, s, ',');
		effect_graphic_data[num].size_x = atoi(s.c_str()); //�摜�̑傫���i���j��ݒ�
		getline(ss, s, ',');
		effect_graphic_data[num].size_y = atoi(s.c_str()); //�摜�̑傫���i�c�j��ݒ�
	}
	ifs.close();
}

//�e�摜���̓ǂݍ���
void Image::LoadBulletData() {
	int num;

	ifstream ifs("data/graphic/bullet/bullet_graphic.csv");

	//�Ȃ���ΏI��
	if (ifs.fail()) {
		return;
	}

	string str, s;
	//�t�@�C�������s�ǂ�
	while (getline(ifs, str)) {
		stringstream ss{ str };
		getline(ss, s, ',');
		num = atoi(s.c_str()); //�ԍ����擾
		getline(ss, s, ',');
		bullet_graphic_data[num].name = "data/graphic/bullet/" + s; //�t�@�C�������i�[
		getline(ss, s, ',');
		bullet_graphic_data[num].num_x = atoi(s.c_str()); //�摜�̖����i���j��ݒ�
		getline(ss, s, ',');
		bullet_graphic_data[num].num_y = atoi(s.c_str()); //�摜�̖����i�c�j��ݒ�
		getline(ss, s, ',');
		bullet_graphic_data[num].size_x = atoi(s.c_str()); //�摜�̑傫���i���j��ݒ�
		getline(ss, s, ',');
		bullet_graphic_data[num].size_y = atoi(s.c_str()); //�摜�̑傫���i�c�j��ݒ�
	}
	ifs.close();
}

//�A�C�e���摜���̓ǂݍ���
void Image::LoadItemData() {
	int num;

	ifstream ifs("data/graphic/item/item_graphic.csv");

	//�Ȃ���ΏI��
	if (ifs.fail()) {
		return;
	}

	string str, s;
	//�t�@�C�������s�ǂ�
	while (getline(ifs, str)) {
		stringstream ss{ str };
		getline(ss, s, ',');
		num = atoi(s.c_str()); //�ԍ����擾
		getline(ss, s, ',');
		item_graphic_data[num].name = "data/graphic/item/" + s; //�t�@�C�������i�[
		getline(ss, s, ',');
		item_graphic_data[num].num_x = atoi(s.c_str()); //�摜�̖����i���j��ݒ�
		getline(ss, s, ',');
		item_graphic_data[num].num_y = atoi(s.c_str()); //�摜�̖����i�c�j��ݒ�
		getline(ss, s, ',');
		item_graphic_data[num].size_x = atoi(s.c_str()); //�摜�̑傫���i���j��ݒ�
		getline(ss, s, ',');
		item_graphic_data[num].size_y = atoi(s.c_str()); //�摜�̑傫���i�c�j��ݒ�
	}
	ifs.close();
}

//�}�b�v�`�b�v�̉摜�����[�h
void Image::LoadMapImage() {
	LoadDivGraph("data/graphic/mapchip/mapchip.png", 44, 22, 2, 32, 32, map_image); //�}�b�v�`�b�v�̉摜�����[�h

	warp_image = LoadGraph("data/graphic/mapchip/warp.png"); //���[�v�n�_�̉摜�����[�h
}

//�}�b�v�`�b�v�̉摜��Ԃ�(�摜�̔ԍ�)
int Image::GetMapImage(int num) {
	return map_image[num];
}

//���[�v�n�_�̉摜��Ԃ� 
int Image::GetWarpImage() {
	return warp_image;
}

//�}�b�v�`�b�v�̉摜���폜
void Image::DeleteMapImage() {
	int size = sizeof(map_image) / sizeof(int);
	for (int i = 0; i < size; i++)
	{
		DeleteGraph(map_image[i]);
	}
	DeleteGraph(warp_image);
}

//�}�b�v�`�b�v�̉摜�����[�h
void Image::LoadMapchipImage() {
	// �L�����摜�̃��������m��
	for (auto& var : mapchip_graphic_data)
	{
		int image_num = var.second.num_x * var.second.num_y; //�摜�̑���
		int *eimage = new int[image_num]; //��U�摜������ϐ�

		LoadDivGraph(var.second.name.c_str(), image_num, var.second.num_x, var.second.num_y, var.second.size_x, var.second.size_y, eimage); //�摜�����[�h

		for (int i = 0; i < image_num; i++)
		{
			mapchip_image[var.first].push_back(eimage[i]); //�摜������
		}
	}
}

//�}�b�v�`�b�v�̉摜��Ԃ�
int Image::GetMapchipImage(int image_num) {
	int key_num = mapchip_convert[image_num].key_num;
	int image = mapchip_convert[image_num].image_num;

	//�摜��T��
	auto einum = mapchip_image.find(key_num); //�摜������
	//�������ꍇ
	if (einum != mapchip_image.end()) {
		if ((unsigned)image < mapchip_image[key_num].size()) {
			return mapchip_image[key_num][image]; //�摜��Ԃ�
		}
	}
	return -1;
}

//�}�b�v�`�b�v�̉摜��Ԃ�
int Image::GetMapchipImage(int map_num, int image_num) {
	//�摜��T��
	auto einum = mapchip_image.find(map_num); //�摜������
	//�������ꍇ
	if (einum != mapchip_image.end()) {
		if ((unsigned)image_num < mapchip_image[map_num].size()) {
			return mapchip_image[map_num][image_num]; //�摜��Ԃ�
		}
	}
	return -1;
}

//�}�b�v�`�b�v�̉摜���폜
void Image::DeleteMapchipImage() {
	// �}�b�v�`�b�v�摜�̃����������
	for (auto& var : mapchip_image)
	{
		const int size = var.second.size();
		for (int i = 0; i < size; i++)
		{
			DeleteGraph(var.second[i]);
		}
		var.second.clear(); //�����������
	}
	mapchip_image.clear(); //�����������
}

//�w�i�̉摜�����[�h
void Image::LoadBackImage(int num) {
	//�w�i����T��
	auto data_num = back_data.find(num);
	//�Ȃ������ꍇ
	if (data_num == back_data.end()) {
		return; //�I��
	}

	//�w�i��T��
	auto back_num = background.find(num); //�w�i������
	//�Ȃ������ꍇ
	if (back_num == background.end()) {
		background[num] = LoadGraph(back_data[num].name.c_str()); //�w�i�����[�h
	}
}

//�w�i�̉摜��Ԃ�(�摜�̔ԍ�)
int Image::GetBackImage(int num) {
	//�w�i��T��
	auto back_num = background.find(num); //�w�i������
	//�������ꍇ
	if (back_num != background.end()) {
		return background[num]; //�w�i��Ԃ�
	}
	return -1;
}

//�w�i�̉摜���폜
void Image::DeleteBackImage() {
	for (auto& var : background)
	{
		DeleteGraph(var.second);
	}
	background.clear(); //�����������
}

//�L�����̉摜�����[�h
void Image::LoadCharaImage() {
	// �L�����摜�̃��������m��
	for (auto& var : enemy_graphic_data)
	{
		int image_num = var.second.num_x * var.second.num_y; //�摜�̑���
		int *eimage = new int[image_num]; //��U�摜������ϐ�

		LoadDivGraph(var.second.name.c_str(), image_num, var.second.num_x, var.second.num_y, var.second.size_x, var.second.size_y, eimage); //�摜�����[�h

		for (int i = 0; i < image_num; i++)
		{
			enemy_image[var.first].push_back(eimage[i]); //�摜������
		}
	}
}

//�L�����̉摜��Ԃ�(�L�����̔ԍ��A�摜�̔ԍ�)
int Image::GetCharaImage(int enemy_num, int image_num) {
	//�摜��T��
	auto einum = enemy_image.find(enemy_num); //�摜������
	//�������ꍇ
	if (einum != enemy_image.end()) {
		if ((unsigned)image_num < enemy_image[enemy_num].size()) {
			return enemy_image[enemy_num][image_num]; //�摜��Ԃ�
		}
	}
	return -1;
}

//�L�����̉摜���폜
void Image::DeleteCharaImage() {
	// �L�����摜�̃����������
	for (auto& var : enemy_image)
	{
		const int size = var.second.size();
		for (int i = 0; i < size; i++)
		{
			DeleteGraph(var.second[i]);
		}
		var.second.clear(); //�����������
	}
	enemy_image.clear(); //�����������
}

//�G�t�F�N�g�̉摜�����[�h
void Image::LoadEffectImage() {
	// �G�t�F�N�g�摜�̃��������m��
	for (auto& var : effect_graphic_data)
	{
		int image_num = var.second.num_x * var.second.num_y; //�摜�̑���
		int *eimage = new int[image_num]; //��U�摜������ϐ�

		LoadDivGraph(var.second.name.c_str(), image_num, var.second.num_x, var.second.num_y, var.second.size_x, var.second.size_y, eimage); //�摜�����[�h

		for (int i = 0; i < image_num; i++)
		{
			effect_image[var.first].push_back(eimage[i]); //�摜������
		}
	}
}

//�G�t�F�N�g�̉摜��Ԃ�
int Image::GetEffectImage(int effect_num, int image_num) {
	//�摜��T��
	auto einum = effect_image.find(effect_num); //�摜������
	//�������ꍇ
	if (einum != effect_image.end()) {
		if ((unsigned)image_num < effect_image[effect_num].size()) {
			return effect_image[effect_num][image_num]; //�摜��Ԃ�
		}
	}
	return -1;
}

//�G�t�F�N�g�̉摜����Ԃ�
int Image::GetEffectSize(int effect_num) {
	//�摜��T��
	auto einum = effect_image.find(effect_num); //�摜������
	//�������ꍇ
	if (einum != effect_image.end()) {
		return effect_image[effect_num].size(); //�摜��Ԃ�
	}
	return 0;
}

//�G�t�F�N�g�̉摜���폜
void Image::DeleteEffectImage() {
	// �G�t�F�N�g�摜�̃����������
	for (auto& var : effect_image)
	{
		const int size = var.second.size();
		for (int i = 0; i < size; i++)
		{
			DeleteGraph(var.second[i]);
		}
		var.second.clear(); //�����������
	}
	effect_image.clear(); //�����������
}

//�e�̉摜�����[�h
void Image::LoadBulletImage() {
	//�e�摜�̃��������m��
	for (auto& var : bullet_graphic_data)
	{
		int image_num = var.second.num_x * var.second.num_y; //�摜�̑���
		int *bimage = new int[image_num]; //��U�摜������ϐ�

		LoadDivGraph(var.second.name.c_str(), image_num, var.second.num_x, var.second.num_y, var.second.size_x, var.second.size_y, bimage); //�摜�����[�h

		for (int i = 0; i < image_num; i++)
		{
			bullet_image[var.first].push_back(bimage[i]); //�摜������
		}
	}
}

//�e�̉摜��Ԃ�
int Image::GetBulletImage(int bullet_num, int image_num) {
	//�摜��T��
	auto einum = bullet_image.find(bullet_num); //�摜������
	//�������ꍇ
	if (einum != bullet_image.end()) {
		if ((unsigned)image_num < bullet_image[bullet_num].size()) {
			return bullet_image[bullet_num][image_num]; //�摜��Ԃ�
		}
	}
	return -1;
}

//�e�̉摜���폜
void Image::DeleteBulletImage() {
	//�e�摜�̃����������
	for (auto& var : bullet_image)
	{
		const int size = var.second.size();
		for (int i = 0; i < size; i++)
		{
			DeleteGraph(var.second[i]);
		}
		var.second.clear(); //�����������
	}
	bullet_image.clear(); //�����������
}

//�A�C�e���̉摜�����[�h
void Image::LoadItemImage() {
	//�e�摜�̃��������m��
	for (auto& var : item_graphic_data)
	{
		int image_num = var.second.num_x * var.second.num_y; //�摜�̑���
		int* iimage = new int[image_num]; //��U�摜������ϐ�

		LoadDivGraph(var.second.name.c_str(), image_num, var.second.num_x, var.second.num_y, var.second.size_x, var.second.size_y, iimage); //�摜�����[�h

		for (int i = 0; i < image_num; i++)
		{
			item_image[var.first].push_back(iimage[i]); //�摜������
		}
	}
}

//�A�C�e���̉摜��Ԃ�
int Image::GetItemImage(int item_num, int image_num) {
	//�摜��T��
	auto inum = item_image.find(item_num); //�摜������
	//�������ꍇ
	if (inum != item_image.end()) {
		if ((unsigned)image_num < item_image[item_num].size()) {
			return item_image[item_num][image_num]; //�摜��Ԃ�
		}
	}
	return -1;
}

//�A�C�e���̉摜���폜
void Image::DeleteItemImage() {
	//�A�C�e���摜�̃����������
	for (auto& var : item_image)
	{
		const int size = var.second.size();
		for (int i = 0; i < size; i++)
		{
			DeleteGraph(var.second[i]);
		}
		var.second.clear(); //�����������
	}
	item_image.clear(); //�����������
}

//���������摜��ǂݍ���
int Image::LoadSingleImage(char file_name[64]) {
	int num = LoadGraph(file_name);
	image_hundle.push_back(num);
	return num;
}

//�摜���폜
void Image::DeleteImage() {
	//�摜�̃����������
	const int size = image_hundle.size();
	for (int i = 0; i < size; i++)
	{
		DeleteGraph(image_hundle[i]);
	}
	image_hundle.clear();
}