#pragma once
#include "Parameter.h"

Parameter::Parameter() {
	//stage_num[stage] = 1; //ステージ番号を初期化
}

Parameter::~Parameter() {
	stage_num.clear();
}

//値をコピー
void Parameter::CopyParam(Parameter &param) {
	for (auto var : param.stage_num)
	{
		stage_num[var.first] = var.second;
	}
}

int Parameter::GetStageNum() {
	//ステージ番号を返す
	auto num = stage_num.find(stage); //ステージ番号を検索
	if (num == stage_num.end()) {
		//なかった場合
		return 0; //とりあえず0を返す
	}
	else {
		//あった場合
		return num->second;
	}
	
}

void Parameter::SetStageNum(int num) {
	//ステージ番号を設定
	stage_num[stage] = num;
}