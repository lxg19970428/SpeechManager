#pragma once
#include<iostream>
#include<vector>
#include<map>
#include<random>
#include<queue>
#include<numeric>
#include<fstream>
#include<ctime>
#include<string>
#include"Speaker.h"
using namespace std;
//设计演讲管理类
class SpeechManager {
public:
	//第一轮比赛选手编号
	vector<int> v1;

	//第一轮晋级选手编号
	vector<int> v2;

	//胜出前面三名选手编号
	vector<int> victory;

	//存放选手编号和对应选手
	map<int, Speaker> m_Speaker;

	//存放比赛轮数
	int Index;
	
public:

	SpeechManager();

	//展示菜单
	void show_Menu();

	//退出系统
	void exitSystem();

	//初始化容器
	void initSpeech();

	//创建选手
	void createSpeaker();

	//开始比赛
	void startSpeech();

	//抽签
	void speechDraw();

	//比赛
	void speechContest();

	//显示晋级结果
	void speechPromote();

	//保存比赛结果
	void saveScore();

	//读取比赛成绩
	void loadScore();

	//判断往届记录是否为空
	bool fileIsEmpty;

	//存放往届记录容器
	map<int, vector<string>> m_Record;

	//展示往届记录
	void showRecord();
	
	//清空记录
	void clearRecord();

	~SpeechManager();
};