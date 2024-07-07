#pragma once
#include <map>
#include <string>

typedef enum {
	//遊ぶステージ
	
} StageNum;

class Parameter {
private:
	std::map<std::string, int> stage_num; //ステージ関連の数値
	const std::string stage = "stage"; //ステージ番号を表すタグ

public:
	Parameter(); //コンストラクタ
	~Parameter(); //デストラクタ
	void CopyParam(Parameter &param); //値をコピー
	int GetStageNum(); //ステージ番号を返す
	void SetStageNum(int num); //ステージ番号を設定
};