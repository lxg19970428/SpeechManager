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
//����ݽ�������
class SpeechManager {
public:
	//��һ�ֱ���ѡ�ֱ��
	vector<int> v1;

	//��һ�ֽ���ѡ�ֱ��
	vector<int> v2;

	//ʤ��ǰ������ѡ�ֱ��
	vector<int> victory;

	//���ѡ�ֱ�źͶ�Ӧѡ��
	map<int, Speaker> m_Speaker;

	//��ű�������
	int Index;
	
public:

	SpeechManager();

	//չʾ�˵�
	void show_Menu();

	//�˳�ϵͳ
	void exitSystem();

	//��ʼ������
	void initSpeech();

	//����ѡ��
	void createSpeaker();

	//��ʼ����
	void startSpeech();

	//��ǩ
	void speechDraw();

	//����
	void speechContest();

	//��ʾ�������
	void speechPromote();

	//����������
	void saveScore();

	//��ȡ�����ɼ�
	void loadScore();

	//�ж������¼�Ƿ�Ϊ��
	bool fileIsEmpty;

	//��������¼����
	map<int, vector<string>> m_Record;

	//չʾ�����¼
	void showRecord();
	
	//��ռ�¼
	void clearRecord();

	~SpeechManager();
};